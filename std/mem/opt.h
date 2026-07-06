#ifndef KAI_MEM_OPT_H
#define KAI_MEM_OPT_H

#include <stdint.h>

static inline void opt_memcpy(void* dest, void* src, int64_t n) {
#if defined(__x86_64__)
    __asm__ volatile ("rep movsb"
                      : "+D"(dest), "+S"(src), "+c"(n)
                      :
                      : "memory");
#else
    __builtin_memcpy(dest, src, n);
#endif
}

static inline void opt_memset(void* s, int64_t c, int64_t n) {
#if defined(__x86_64__)
    __asm__ volatile ("rep stosb"
                      : "+D"(s), "+c"(n)
                      : "a"(c)
                      : "memory");
#else
    __builtin_memset(s, c, n);
#endif
}

#endif
