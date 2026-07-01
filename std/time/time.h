#ifndef KAI_TIME_H
#define KAI_TIME_H

#if defined(_WIN32)
#include <windows.h>
#else
#include <time.h>
#include <sys/time.h>
#endif

#include <stdint.h>

static inline int64_t kai_time_monotonic_ns(void) {
#if defined(_WIN32)
    LARGE_INTEGER count, freq;
    if (QueryPerformanceCounter(&count) && QueryPerformanceFrequency(&freq)) {
        return (int64_t)((double)count.QuadPart / (double)freq.QuadPart * 1e9);
    }
    return 0;
#else
    struct timespec ts;
    if (clock_gettime(CLOCK_MONOTONIC, &ts) == 0) {
        return (int64_t)ts.tv_sec * 1000000000LL + (int64_t)ts.tv_nsec;
    }
    return 0;
#endif
}

static inline int64_t kai_time_system_ms(void) {
#if defined(_WIN32)
    FILETIME ft;
    GetSystemTimeAsFileTime(&ft);
    ULARGE_INTEGER u;
    u.LowPart = ft.dwLowDateTime;
    u.HighPart = ft.dwHighDateTime;
    return (int64_t)((u.QuadPart - 116444736000000000ULL) / 10000ULL);
#else
    struct timeval tv;
    if (gettimeofday(&tv, NULL) == 0) {
        return (int64_t)tv.tv_sec * 1000LL + (int64_t)tv.tv_usec / 1000LL;
    }
    return 0;
#endif
}

#endif
