#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <ctype.h>

static inline void print_int(int64_t i) { printf("%lld\n", (long long)i); }


void render_Int(int64_t shape);

void render_Int(int64_t shape) {
    int64_t_missing_method(&(shape));
}
int main(int argc, char** argv) {
    render_Int(42);
    return 0;
}