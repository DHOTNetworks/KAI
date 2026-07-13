/* BUILDER CODEGEN ACTIVE */
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#ifndef NO_GET_EXE_DIR
#include "std/os/os.h"
int64_t get_exe_dir(char* out_buf, int64_t max_len) {
    return kai_os_get_exe_dir(out_buf, max_len);
}
#endif

static char* __kai_str_sub(const char* s, int64_t start, int64_t end) {
    int64_t len = strlen(s);
    if (end > len) end = len;
    if (start < 0) start = 0;
    if (start >= end) {
        char* empty = malloc(1);
        if (empty) empty[0] = '\0';
        return empty;
    }
    int64_t sub_len = end - start;
    char* buf = malloc(sub_len + 1);
    if (buf) {
        memcpy(buf, s + start, sub_len);
        buf[sub_len] = '\0';
    }
    return buf;
}

static void* __kai_arr_sub(const void* arr, int64_t start, int64_t end, int64_t elem_size) {
    int64_t count = end - start;
    if (count <= 0) return NULL;
    size_t total = (size_t)count * (size_t)elem_size;
    void* buf = malloc(total);
    if (buf) memcpy(buf, (const char*)arr + start * elem_size, total);
    return buf;
}

#ifndef MAP_FAILED
#define MAP_FAILED ((void*)-1)
#endif
#ifndef MAP_PRIVATE
#define MAP_PRIVATE 2
#endif
#ifndef MAP_ANONYMOUS
#ifdef __APPLE__
#define MAP_ANONYMOUS 0x1000
#else
#define MAP_ANONYMOUS 0x20
#endif
#endif
extern void* mmap(void* addr, unsigned long long length, int prot, int flags, int fd, long long offset);
extern int munmap(void* addr, unsigned long long length);

void __kai_print_int(int64_t v) {
    printf("%lld\n", (long long)(v));
}

void __kai_print_float(double v) {
    printf("%f\n", (double)(v));
}

static inline uint8_t* _kai_mmap(uint8_t* addr, int64_t length, int64_t prot, int64_t flags, int64_t fd, int64_t offset) {
    return (uint8_t*)mmap(addr, length, prot, MAP_PRIVATE | MAP_ANONYMOUS, fd, offset);
}

static inline int64_t _kai_munmap(uint8_t* addr, int64_t length) {
    return munmap(addr, length);
}

extern void __kai_panic(const char* msg);
#ifndef __KAI_NO_PANIC
void __kai_panic(const char* msg) {
    fprintf(stderr, "KAI PANIC: %s\n", msg);
    fflush(stderr);
    abort();
}
#endif




extern int64_t get_exe_dir();

int main(int argc, char** argv)
{
}
