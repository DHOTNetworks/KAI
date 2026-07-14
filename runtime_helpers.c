#define static
#define inline
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>

#include "std/llvm/core.h"
#include "std/fs/fs.h"
#include "std/os/os.h"

#undef static
#undef inline

// Implement get_exe_dir which delegates to kai_os_get_exe_dir
// (provided by compiler's runtime preamble)
// int64_t get_exe_dir(char* out_buf, int64_t max_len) {
//     return kai_os_get_exe_dir(out_buf, max_len);
// }

uint8_t* _kai_mmap(uint8_t* addr, int64_t length, int64_t prot, int64_t flags, int64_t fd, int64_t offset) {
#ifdef _WIN32
    return NULL;
#else
    return (uint8_t*)mmap(addr, length, prot, MAP_PRIVATE | MAP_ANONYMOUS, fd, offset);
#endif
}
