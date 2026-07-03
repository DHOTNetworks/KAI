#ifndef KAI_ARGS_H
#define KAI_ARGS_H

#include <stdint.h>
#include <stdbool.h>

static int64_t _kai_argc = 0;
static char** _kai_argv = 0;

static void args_init(int64_t argc, char** argv) {
    _kai_argc = argc;
    _kai_argv = argv;
}

static int64_t args_len(void) {
    return _kai_argc;
}

static const char* args_get(int64_t index) {
    if (index < 0 || index >= _kai_argc) {
        return 0;
    }
    return _kai_argv[index];
}

static bool args_has(int64_t index) {
    return index >= 0 && index < _kai_argc;
}

#endif
