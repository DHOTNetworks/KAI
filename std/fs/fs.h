#ifndef KAI_FS_H
#define KAI_FS_H

#include "../core/platform.h"

#include <stdlib.h>

#if KAI_OS_WIN
#include <windows.h>
#include <direct.h>
#include <stdio.h>
#else
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#endif

static inline bool kai_fs_exists(const char* path) {
#if KAI_OS_WIN
    DWORD dwAttrib = GetFileAttributesA(path);
    return (dwAttrib != INVALID_FILE_ATTRIBUTES);
#else
    struct stat buffer;
    return (stat(path, &buffer) == 0);
#endif
}

static inline bool kai_fs_is_dir(const char* path) {
#if KAI_OS_WIN
    DWORD dwAttrib = GetFileAttributesA(path);
    return (dwAttrib != INVALID_FILE_ATTRIBUTES && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
#else
    struct stat buffer;
    if (stat(path, &buffer) != 0) return false;
    return S_ISDIR(buffer.st_mode);
#endif
}

static inline bool kai_fs_mkdir(const char* path) {
#if KAI_OS_WIN
    return _mkdir(path) == 0;
#else
    return mkdir(path, 0777) == 0;
#endif
}

static inline bool kai_fs_remove(const char* path) {
#if KAI_OS_WIN
    DWORD dwAttrib = GetFileAttributesA(path);
    if (dwAttrib != INVALID_FILE_ATTRIBUTES && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY)) {
        return RemoveDirectoryA(path) != 0;
    }
    return DeleteFileA(path) != 0;
#else
    struct stat buffer;
    if (stat(path, &buffer) != 0) return false;
    if (S_ISDIR(buffer.st_mode)) {
        return rmdir(path) == 0;
    }
    return unlink(path) == 0;
#endif
}

#if KAI_OS_WIN
typedef struct {
    HANDLE handle;
    WIN32_FIND_DATAA findData;
    bool first;
} KaiDir;
#else
typedef struct {
    DIR* dir;
} KaiDir;
#endif

static inline void* kai_fs_opendir(const char* path) {
#if KAI_OS_WIN
    char search_path[MAX_PATH];
    snprintf(search_path, sizeof(search_path), "%s\\*", path);
    KaiDir* kd = malloc(sizeof(KaiDir));
    kd->handle = FindFirstFileA(search_path, &kd->findData);
    if (kd->handle == INVALID_HANDLE_VALUE) {
        free(kd);
        return NULL;
    }
    kd->first = true;
    return (void*)kd;
#else
    DIR* d = opendir(path);
    if (d == NULL) return NULL;
    KaiDir* kd = malloc(sizeof(KaiDir));
    kd->dir = d;
    return (void*)kd;
#endif
}

static inline char* kai_fs_readdir(void* handle) {
    if (handle == NULL) return NULL;
    KaiDir* kd = (KaiDir*)handle;
#if KAI_OS_WIN
    if (kd->first) {
        kd->first = false;
        return (char*)kd->findData.cFileName;
    }
    if (FindNextFileA(kd->handle, &kd->findData)) {
        return (char*)kd->findData.cFileName;
    }
    return NULL;
#else
    struct dirent* entry = readdir(kd->dir);
    if (entry == NULL) return NULL;
    return (char*)entry->d_name;
#endif
}

static inline void kai_fs_closedir(void* handle) {
    if (handle == NULL) return;
    KaiDir* kd = (KaiDir*)handle;
#if KAI_OS_WIN
    if (kd->handle != INVALID_HANDLE_VALUE) {
        FindClose(kd->handle);
    }
#else
    closedir(kd->dir);
#endif
    free(kd);
}

#endif
