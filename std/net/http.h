#ifndef KAI_HTTP_H
#define KAI_HTTP_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#if defined(_WIN32)
#define strncasecmp _strnicmp
#endif

struct kai_http_header {
    char* name;
    int64_t name_len;
    char* value;
    int64_t value_len;
};

struct kai_http_request {
    char* method;
    int64_t method_len;
    char* path;
    int64_t path_len;
    int64_t minor_version;
    struct kai_http_header headers[64];
    int64_t num_headers;
    int64_t body_offset;
};

static inline int64_t kai_http_parse_request(char* buf, int64_t buflen, void* req_void) {
    struct kai_http_request* req = (struct kai_http_request*)req_void;
    req->num_headers = 0;
    req->method = NULL;
    req->method_len = 0;
    req->path = NULL;
    req->path_len = 0;
    req->minor_version = 0;
    req->body_offset = 0;

    char* p = buf;
    char* end = buf + buflen;

    // 1. Parse Method
    while (p < end && *p == ' ') p++;
    if (p >= end) return -2; // incomplete
    char* method_start = p;
    while (p < end && *p != ' ') p++;
    if (p >= end) return -2;
    req->method = method_start;
    req->method_len = p - method_start;
    p++; // skip space

    // 2. Parse Path
    while (p < end && *p == ' ') p++;
    if (p >= end) return -2;
    char* path_start = p;
    while (p < end && *p != ' ') p++;
    if (p >= end) return -2;
    req->path = path_start;
    req->path_len = p - path_start;
    p++; // skip space

    // 3. Parse HTTP version
    if (p + 8 > end) return -2;
    if (strncmp(p, "HTTP/1.", 7) != 0) return -1; // parse error
    req->minor_version = p[7] - '0';
    p += 8;
    while (p + 1 < end && (*p != '\r' || *(p+1) != '\n')) p++;
    if (p + 1 >= end) return -2;
    p += 2; // skip \r\n

    // 4. Parse Headers
    while (p + 1 < end) {
        if (*p == '\r' && *(p+1) == '\n') {
            p += 2;
            req->body_offset = p - buf;
            return p - buf; // bytes consumed
        }

        char* name_start = p;
        while (p < end && *p != ':' && *p != '\r') p++;
        if (p >= end) return -2;
        if (*p == '\r') return -1;
        int64_t name_len = p - name_start;
        p++; // skip ':'

        while (p < end && *p == ' ') p++;
        if (p >= end) return -2;

        char* val_start = p;
        while (p + 1 < end && (*p != '\r' || *(p+1) != '\n')) p++;
        if (p + 1 >= end) return -2;
        int64_t val_len = p - val_start;
        p += 2; // skip \r\n

        if (req->num_headers < 64) {
            req->headers[req->num_headers].name = name_start;
            req->headers[req->num_headers].name_len = name_len;
            req->headers[req->num_headers].value = val_start;
            req->headers[req->num_headers].value_len = val_len;
            req->num_headers++;
        }
    }

    return -2; // incomplete
}

static inline char* kai_http_get_header(void* req_void, const char* name, int64_t* out_len) {
    struct kai_http_request* req = (struct kai_http_request*)req_void;
    int64_t name_len = strlen(name);
    for (int64_t i = 0; i < req->num_headers; i++) {
        if (req->headers[i].name_len == name_len &&
            strncasecmp(req->headers[i].name, name, name_len) == 0) {
            *out_len = req->headers[i].value_len;
            return req->headers[i].value;
        }
    }
    *out_len = 0;
    return NULL;
}

static inline char* kai_http_get_method(void* req_void, int64_t* out_len) {
    *out_len = ((struct kai_http_request*)req_void)->method_len;
    return ((struct kai_http_request*)req_void)->method;
}

static inline char* kai_http_get_path(void* req_void, int64_t* out_len) {
    *out_len = ((struct kai_http_request*)req_void)->path_len;
    return ((struct kai_http_request*)req_void)->path;
}

static inline int64_t kai_http_get_minor_version(void* req_void) {
    return ((struct kai_http_request*)req_void)->minor_version;
}

static inline int64_t kai_http_get_body_offset(void* req_void) {
    return ((struct kai_http_request*)req_void)->body_offset;
}

static inline char* kai_http_invoke_handler(void* handler_ptr, void* req_ptr) {
    char* (*handler)(void*) = (char* (*)(void*))handler_ptr;
    return handler(req_ptr);
}

#endif
