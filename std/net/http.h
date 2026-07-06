#ifndef KAI_HTTP_H
#define KAI_HTTP_H

#include "../core/platform.h"

#include <string.h>
#include <stdlib.h>

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

int64_t kai_http_parse_request(char* buf, int64_t buflen, void* req_void);
char* kai_http_get_header(void* req_void, const char* name, int64_t* out_len);
char* kai_http_get_method(void* req_void, int64_t* out_len);
char* kai_http_get_path(void* req_void, int64_t* out_len);
int64_t kai_http_get_minor_version(void* req_void);
int64_t kai_http_get_body_offset(void* req_void);
char* kai_http_invoke_handler(void* handler_ptr, void* req_ptr);

#endif
