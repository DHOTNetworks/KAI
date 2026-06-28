#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <ctype.h>

static inline void print_int(int64_t i) { printf("%lld\n", (long long)i); }


int64_t identity_Int(int64_t x);

int64_t identity_Int(int64_t x) {
    return x;
}
int main(int argc, char** argv) {
    int64_t v = identity_Int(42);
    printf("%lld\n", (long long)(v));
    printf("%s\n", "\n");
    return 0;
}