#ifndef KAI_ATOMIC_H
#define KAI_ATOMIC_H

#include <stdint.h>
#include <stdbool.h>

static inline int64_t atomic_add(void* ptr, int64_t delta) {
#if defined(__aarch64__)
    return __sync_add_and_fetch((int64_t*)ptr, delta);
#elif defined(__x86_64__)
    int64_t prev = delta;
    __asm__ volatile ("lock; xaddq %0, %1"
                      : "+r" (prev), "+m" (*(int64_t*)ptr)
                      : : "memory");
    return prev + delta;
#else
    return __sync_add_and_fetch((int64_t*)ptr, delta);
#endif
}

static inline bool atomic_cas(void* ptr, int64_t old_val, int64_t new_val) {
#if defined(__aarch64__)
    return __sync_bool_compare_and_swap((int64_t*)ptr, old_val, new_val);
#elif defined(__x86_64__)
    char res;
    __asm__ volatile ("lock; cmpxchgq %3, %1; sete %0"
                      : "=q" (res), "+m" (*(int64_t*)ptr)
                      : "a" (old_val), "r" (new_val)
                      : "memory");
    return res != 0;
#else
    return __sync_bool_compare_and_swap((int64_t*)ptr, old_val, new_val);
#endif
}

#endif
