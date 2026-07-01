#ifndef KAI_OS_H
#define KAI_OS_H

#if defined(_WIN32)
#include <windows.h>
#include <process.h>
#else
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#endif

#include <stdint.h>

static inline void kai_os_sleep_ms(int64_t ms) {
#if defined(_WIN32)
    Sleep((DWORD)ms);
#else
    struct timespec ts;
    ts.tv_sec = ms / 1000;
    ts.tv_nsec = (ms % 1000) * 1000000;
    nanosleep(&ts, NULL);
#endif
}

static inline int64_t kai_os_getpid(void) {
#if defined(_WIN32)
    return (int64_t)GetCurrentProcessId();
#else
    return (int64_t)getpid();
#endif
}

static inline char* kai_os_getenv(const char* name) {
    return getenv(name);
}

static inline int64_t kai_os_setenv(const char* name, const char* val) {
#if defined(_WIN32)
    return SetEnvironmentVariableA(name, val) ? 0 : -1;
#else
    return setenv(name, val, 1);
#endif
}

#endif
