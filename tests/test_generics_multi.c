#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <ctype.h>

static inline void print_int(int64_t i) { printf("%lld\n", (long long)i); }


int64_t select_first_Int_Str(int64_t first, const char* second);

int64_t select_first_Int_Str(int64_t first, const char* second) {
    return first;
}
int main(int argc, char** argv) {
    int64_t a = select_first_Int_Str(456, "hello");
    printf("%lld\n", (long long)(a));
    printf("%s\n", "\n");
    return 0;
}