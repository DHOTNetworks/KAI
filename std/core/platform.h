#ifndef KAI_PLATFORM_H
#define KAI_PLATFORM_H

//== Platform Detection
//   Single source of truth for OS-level platform conditionals.
//   Every .h file in std/*/ should #include this instead of
//   duplicating #if defined(_WIN32) guards.

//--- OS detection ---

#if defined(_WIN32) || defined(_WIN64)
#  define KAI_OS_WIN 1
#elif defined(__APPLE__)
#  define KAI_OS_MAC 1
#else
#  define KAI_OS_LINUX 1
#endif

//--- Baseline C types (needed by every FFI header) ---

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

//--- Feature-test macros ---

#ifndef _GNU_SOURCE
#  define _GNU_SOURCE
#endif

//--- Windows compatibility shims ---

#if KAI_OS_WIN
#  ifndef strncasecmp
#    define strncasecmp _strnicmp
#  endif
#  ifndef strcasecmp
#    define strcasecmp _stricmp
#  endif
#endif

#endif // KAI_PLATFORM_H
