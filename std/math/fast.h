#ifndef KAI_FAST_MATH_H
#define KAI_FAST_MATH_H

#include <math.h>

#if defined(__aarch64__)
static inline double fast_sqrt(double val) {
    double res;
    __asm__ ("fsqrt %d0, %d1" : "=w"(res) : "w"(val));
    return res;
}
static inline double fast_abs(double val) {
    double res;
    __asm__ ("fabs %d0, %d1" : "=w"(res) : "w"(val));
    return res;
}
#elif defined(__x86_64__)
static inline double fast_sqrt(double val) {
    double res;
    __asm__ ("sqrtsd %1, %0" : "=x"(res) : "x"(val));
    return res;
}
static inline double fast_abs(double val) {
    double res = val;
    if (res < 0) res = -res;
    return res;
}
#else
static inline double fast_sqrt(double val) {
    return sqrt(val);
}
static inline double fast_abs(double val) {
    return fabs(val);
}
#endif

static inline double fast_sin(double val) { return sin(val); }
static inline double fast_cos(double val) { return cos(val); }
static inline double fast_tan(double val) { return tan(val); }
static inline double fast_log(double val) { return log(val); }
static inline double fast_exp(double val) { return exp(val); }
static inline double fast_pow(double base, double exponent) { return pow(base, exponent); }

#endif
