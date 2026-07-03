#include <string.h>
#include <stdlib.h>

char* _kai_str_concat(const char* l, const char* r) {
    size_t l1 = strlen(l);
    size_t l2 = strlen(r);
    if (l1 > 1000000 || l2 > 1000000 - l1) { return NULL; }
    size_t total = l1 + l2 + 1;
    char* buf = malloc(total);
    if (buf) { strcpy(buf, l); strcat(buf, r); }
    return buf;
}
