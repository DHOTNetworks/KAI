/* Runtime helpers for the Kai LLVM backend self-hosting build.
 * Provides non-static implementations of get_exe_dir and kai_fs_* symbols
 * that the LLVM-backend-compiled compiler.ll references.
 */

#if defined(_WIN32)
#include <direct.h>
#include <windows.h>
#else
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#endif

#if defined(__APPLE__)
#include <limits.h>
#include <mach-o/dyld.h>
#else
#include <limits.h>
#endif

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

__thread void* _kai_current_allocator = NULL;

void _kai_set_current_allocator(void* allocator) {
    _kai_current_allocator = allocator;
}


/* ============================================================
 * get_exe_dir
 * ============================================================ */
int64_t get_exe_dir(char *out_buf, int64_t max_len) {
#if defined(_WIN32)
  DWORD len = GetModuleFileNameA(NULL, out_buf, (DWORD)max_len);
  if (len == 0 || len >= (DWORD)max_len)
    return -1;
  for (int i = (int)len - 1; i >= 0; i--) {
    if (out_buf[i] == '\\' || out_buf[i] == '/') {
      out_buf[i] = '\0';
      break;
    }
  }
  return 0;
#elif defined(__APPLE__)
  char path[4096];
  uint32_t sz = sizeof(path);
  if (_NSGetExecutablePath(path, &sz) != 0)
    return -1;
  char real_path[4096];
  if (realpath(path, real_path) == NULL)
    return -1;
  char *s = strrchr(real_path, '/');
  if (!s)
    return -1;
  *s = '\0';
  strncpy(out_buf, real_path, (size_t)max_len);
  out_buf[max_len - 1] = '\0';
  return 0;
#else
  char path[4096];
  ssize_t n = readlink("/proc/self/exe", path, sizeof(path) - 1);
  if (n == -1)
    return -1;
  path[n] = '\0';
  char real_path[4096];
  if (realpath(path, real_path) == NULL)
    return -1;
  char *s = strrchr(real_path, '/');
  if (!s)
    return -1;
  *s = '\0';
  strncpy(out_buf, real_path, (size_t)max_len);
  out_buf[max_len - 1] = '\0';
  return 0;
#endif
}

/* ============================================================
 * kai_fs_* — non-static wrappers (LLVM IR can't call static inlines)
 * ============================================================ */

bool kai_fs_exists(const char *path) {
#if defined(_WIN32)
  return GetFileAttributesA(path) != INVALID_FILE_ATTRIBUTES;
#else
  struct stat buf;
  return stat(path, &buf) == 0;
#endif
}

bool kai_fs_is_dir(const char *path) {
#if defined(_WIN32)
  DWORD a = GetFileAttributesA(path);
  return (a != INVALID_FILE_ATTRIBUTES) && (a & FILE_ATTRIBUTE_DIRECTORY);
#else
  struct stat buf;
  return (stat(path, &buf) == 0) && S_ISDIR(buf.st_mode);
#endif
}

bool kai_fs_mkdir(const char *path) {
#if defined(_WIN32)
  return _mkdir(path) == 0;
#else
  return mkdir(path, 0777) == 0;
#endif
}

bool kai_fs_remove(const char *path) {
#if defined(_WIN32)
  DWORD a = GetFileAttributesA(path);
  if (a != INVALID_FILE_ATTRIBUTES && (a & FILE_ATTRIBUTE_DIRECTORY))
    return RemoveDirectoryA(path) != 0;
  return DeleteFileA(path) != 0;
#else
  struct stat buf;
  if (stat(path, &buf) != 0)
    return false;
  return S_ISDIR(buf.st_mode) ? (rmdir(path) == 0) : (unlink(path) == 0);
#endif
}

void *kai_fs_opendir(const char *path) {
#if defined(_WIN32)
  char search[4096];
  snprintf(search, sizeof(search), "%s\\*", path);
  WIN32_FIND_DATAA fd;
  HANDLE h = FindFirstFileA(search, &fd);
  if (h == INVALID_HANDLE_VALUE)
    return NULL;
  /* pack handle+first into malloc'd buffer */
  void **slot = malloc(sizeof(void *) * 2);
  slot[0] = h;
  slot[1] = NULL;
  return slot;
#else
  return (void *)opendir(path);
#endif
}

char *kai_fs_readdir(void *handle) {
  if (!handle)
    return NULL;
#if defined(_WIN32)
  void **slot = (void **)handle;
  HANDLE h = (HANDLE)slot[0];
  WIN32_FIND_DATAA fd;
  while (FindNextFileA(h, &fd)) {
    if (strcmp(fd.cFileName, ".") == 0 || strcmp(fd.cFileName, "..") == 0)
      continue;
    return strdup(fd.cFileName);
  }
  return NULL;
#else
  struct dirent *e;
  while ((e = readdir((DIR *)handle)) != NULL) {
    if (strcmp(e->d_name, ".") == 0 || strcmp(e->d_name, "..") == 0)
      continue;
    return e->d_name;
  }
  return NULL;
#endif
}

void kai_fs_closedir(void *handle) {
  if (!handle)
    return;
#if defined(_WIN32)
  void **slot = (void **)handle;
  FindClose((HANDLE)slot[0]);
  free(slot);
#else
  closedir((DIR *)handle);
#endif
}
