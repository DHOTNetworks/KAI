#ifndef KAI_OS_H
#define KAI_OS_H

#include "../core/platform.h"

#include <stdlib.h>
#include <string.h>

#if KAI_OS_WIN
#include <windows.h>
#include <process.h>
#elif KAI_OS_MAC
#include <mach-o/dyld.h>
#include <limits.h>
#include <unistd.h>
#include <time.h>
#else
#include <unistd.h>
#include <limits.h>
#include <time.h>
#endif

static inline void kai_os_sleep_ms(int64_t ms) {
#if KAI_OS_WIN
    Sleep((DWORD)ms);
#else
    struct timespec ts;
    ts.tv_sec = ms / 1000;
    ts.tv_nsec = (ms % 1000) * 1000000;
    nanosleep(&ts, NULL);
#endif
}

static inline int64_t kai_os_getpid(void) {
#if KAI_OS_WIN
    return (int64_t)GetCurrentProcessId();
#else
    return (int64_t)getpid();
#endif
}

static inline char* kai_os_getenv(const char* name) {
    return getenv(name);
}

static inline int64_t kai_os_setenv(const char* name, const char* val) {
#if KAI_OS_WIN
    return SetEnvironmentVariableA(name, val) ? 0 : -1;
#else
    return setenv(name, val, 1);
#endif
}

//== Get executable directory (3-platform)

static inline int64_t kai_os_get_exe_dir(char* out_buf, int64_t max_len) {
#if KAI_OS_WIN
    DWORD len = GetModuleFileNameA(NULL, out_buf, (DWORD)max_len);
    if (len == 0 || len >= (DWORD)max_len) return -1;
    for (int i = len - 1; i >= 0; i--) {
        if (out_buf[i] == '\\' || out_buf[i] == '/') {
            out_buf[i] = '\0';
            return 0;
        }
    }
    return -1;
#elif KAI_OS_MAC
    char path[PATH_MAX];
    uint32_t size = sizeof(path);
    if (_NSGetExecutablePath(path, &size) != 0) return -1;
    char real_path[PATH_MAX];
    if (realpath(path, real_path) == NULL) return -1;
    char* last_slash = strrchr(real_path, '/');
    if (last_slash == NULL) return -1;
    *last_slash = '\0';
    strncpy(out_buf, real_path, max_len);
    out_buf[max_len - 1] = '\0';
    return 0;
#else
    char path[PATH_MAX];
    ssize_t len = readlink("/proc/self/exe", path, sizeof(path) - 1);
    if (len == -1) return -1;
    path[len] = '\0';
    char real_path[PATH_MAX];
    if (realpath(path, real_path) == NULL) return -1;
    char* last_slash = strrchr(real_path, '/');
    if (last_slash == NULL) return -1;
    *last_slash = '\0';
    strncpy(out_buf, real_path, max_len);
    out_buf[max_len - 1] = '\0';
    return 0;
#endif
}

#endif
