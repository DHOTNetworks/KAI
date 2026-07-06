#ifndef KAI_THREAD_H
#define KAI_THREAD_H

#if defined(_WIN32)
#include <windows.h>
#else
#include <pthread.h>
#include <stdlib.h>
#endif

#include <stdint.h>

static inline void* kai_thread_spawn(void* f_ptr, void* arg) {
#if defined(_WIN32)
    HANDLE thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)f_ptr, arg, 0, NULL);
    return (void*)thread;
#else
    pthread_t* thread = malloc(sizeof(pthread_t));
    void* (*f)(void*) = (void* (*)(void*))f_ptr;
    if (pthread_create(thread, NULL, f, arg) != 0) {
        free(thread);
        return NULL;
    }
    return (void*)thread;
#endif
}

static inline void* kai_thread_join(void* handle) {
    if (handle == NULL) return NULL;
#if defined(_WIN32)
    WaitForSingleObject((HANDLE)handle, INFINITE);
    CloseHandle((HANDLE)handle);
    return NULL;
#else
    pthread_t* thread = (pthread_t*)handle;
    void* retval = NULL;
    pthread_join(*thread, &retval);
    free(thread);
    return retval;
#endif
}

static inline void* kai_mutex_init(void) {
#if defined(_WIN32)
    CRITICAL_SECTION* cs = malloc(sizeof(CRITICAL_SECTION));
    InitializeCriticalSection(cs);
    return (void*)cs;
#else
    pthread_mutex_t* mutex = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(mutex, NULL);
    return (void*)mutex;
#endif
}

static inline void kai_mutex_lock(void* handle) {
    if (handle == NULL) return;
#if defined(_WIN32)
    EnterCriticalSection((CRITICAL_SECTION*)handle);
#else
    pthread_mutex_lock((pthread_mutex_t*)handle);
#endif
}

static inline void kai_mutex_unlock(void* handle) {
    if (handle == NULL) return;
#if defined(_WIN32)
    LeaveCriticalSection((CRITICAL_SECTION*)handle);
#else
    pthread_mutex_unlock((pthread_mutex_t*)handle);
#endif
}

static inline void kai_mutex_destroy(void* handle) {
    if (handle == NULL) return;
#if defined(_WIN32)
    DeleteCriticalSection((CRITICAL_SECTION*)handle);
    free(handle);
#else
    pthread_mutex_destroy((pthread_mutex_t*)handle);
    free(handle);
#endif
}

#endif
