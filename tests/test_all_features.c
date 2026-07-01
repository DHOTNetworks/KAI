#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if !defined(_WIN32)
#include <sys/mman.h>
#endif
#include <ctype.h>

#if defined(_WIN32)
#include <windows.h>
#elif defined(__APPLE__)
#include <mach-o/dyld.h>
#include <limits.h>
#else
#include <unistd.h>
#include <limits.h>
#endif

int64_t get_exe_dir(char* out_buf, int64_t max_len) {
#if defined(_WIN32)
    DWORD len = GetModuleFileNameA(NULL, out_buf, max_len);
    if (len == 0 || len >= max_len) return -1;
    for (int i = len - 1; i >= 0; i--) {
        if (out_buf[i] == '\\' || out_buf[i] == '/') {
            out_buf[i] = '\0';
            break;
        }
    }
    return 0;
#elif defined(__APPLE__)
    char path[PATH_MAX];
    uint32_t size = sizeof(path);
    if (_NSGetExecutablePath(path, &size) != 0) return -1;
    char real_path[PATH_MAX];
    if (realpath(path, real_path) == NULL) return -1;
    char* last_slash = strrchr(real_path, '/');
    if (last_slash == NULL) return -1;
    *last_slash = '\0';
    strncpy(out_buf, real_path, max_len);
    out_buf[max_len - 1] = '\0';
    return 0;
#else
    char path[PATH_MAX];
    ssize_t len = readlink("/proc/self/exe", path, sizeof(path) - 1);
    if (len == -1) return -1;
    path[len] = '\0';
    char real_path[PATH_MAX];
    if (realpath(path, real_path) == NULL) return -1;
    char* last_slash = strrchr(real_path, '/');
    if (last_slash == NULL) return -1;
    *last_slash = '\0';
    strncpy(out_buf, real_path, max_len);
    out_buf[max_len - 1] = '\0';
    return 0;
#endif
}


static inline void print_int(int64_t i) { printf("%lld\n", (long long)i); }
__thread void* _kai_current_allocator = NULL;
void _kai_set_current_allocator(void* allocator);
char* _kai_str_concat(const char* l, const char* r);

/* trait Allocator: alloc, realloc, free, deinit */
typedef struct CAlloc CAlloc;
struct CAlloc {
    int64_t dummy;
    int64_t _pad;
};
typedef struct SlabHeader SlabHeader;
struct SlabHeader {
    int64_t magic;
    int64_t obj_size;
    int64_t capacity;
    int64_t free_cnt;
    char* free_head;
    int64_t next_bump_idx;
    int64_t pad;
    char* next;
};
typedef struct FreeBlock FreeBlock;
struct FreeBlock {
    char* next;
};
typedef struct KaiAllocator KaiAllocator;
struct KaiAllocator {
    char* heads;
    int64_t used;
};
typedef struct StringBuilder StringBuilder;
struct StringBuilder {
    char* data;
    int64_t len;
    int64_t cap;
    KaiAllocator* allocator;
};
typedef enum {
    FileError_not_found = 1,
    FileError_permission_denied = 2,
} FileError;
/* trait Describable: describe */
typedef struct Point Point;
struct Point {
    int64_t x;
    int64_t y;
};
typedef struct Result_Int_FileError Result_Int_FileError;
struct Result_Int_FileError {
    int64_t tag;
    int64_t value;
};
typedef struct Optional_Int Optional_Int;
struct Optional_Int {
    bool has_value;
    int64_t value;
};

char* CAlloc_alloc(CAlloc* self, int64_t size, int64_t alignment);
char* CAlloc_realloc(CAlloc* self, char* ptr, int64_t old_size, int64_t new_size, int64_t alignment);
void CAlloc_free(CAlloc* self, char* ptr);
void CAlloc_deinit(CAlloc* self);
int64_t class_obj_size(int64_t idx);
int64_t class_for(int64_t sz);
bool is_small(int64_t sz);
int64_t page_align_up(int64_t n);
KaiAllocator KaiAllocator_init(void);
char* KaiAllocator_get_head(KaiAllocator* self, int64_t idx);
void KaiAllocator_set_head(KaiAllocator* self, int64_t idx, char* head);
char* KaiAllocator_allocate_slab(KaiAllocator* self, int64_t idx);
char* KaiAllocator_alloc_large(KaiAllocator* self, int64_t size);
void KaiAllocator_free_large(KaiAllocator* self, char* ptr);
char* KaiAllocator_alloc(KaiAllocator* self, int64_t size, int64_t align);
char* KaiAllocator_realloc(KaiAllocator* self, char* ptr, int64_t old_size, int64_t new_size, int64_t align);
void KaiAllocator_free(KaiAllocator* self, char* ptr);
void KaiAllocator_deinit(KaiAllocator* self);
char char_at(const char* s, int64_t i);
bool is_digit(char c);
bool is_alpha(char c);
bool is_alnum(char c);
bool is_space(char c);
char to_upper(char c);
char to_lower(char c);
int64_t length(const char* s);
StringBuilder StringBuilder_init(KaiAllocator* allocator);
void StringBuilder_append_char(StringBuilder* self, char c);
void StringBuilder_append_str(StringBuilder* self, const char* s);
void StringBuilder_append(StringBuilder* self, const char* s);
const char* StringBuilder_to_str(StringBuilder* self);
void StringBuilder_deinit(StringBuilder* self);
const char* int_to_str(int64_t n);
const char* char_to_str(char c);
const char* substring(const char* s, int64_t start, int64_t end);
extern void _kai_set_current_allocator(void* allocator);
const char* Point_describe(Point* self);
Result_Int_FileError divide_or_error(bool flag);
Optional_Int get_optional_value(bool flag);
int64_t identity_Int(int64_t val);

void _kai_set_current_allocator(void* allocator) {
    _kai_current_allocator = allocator;
}
char* _kai_str_concat(const char* l, const char* r) {
    size_t l1 = strlen(l);
    size_t l2 = strlen(r);
    size_t total = l1 + l2 + 1;
    char* buf = NULL;
    if (_kai_current_allocator) {
        buf = KaiAllocator_alloc((KaiAllocator*)_kai_current_allocator, total, 1);
    } else {
        buf = malloc(total);
    }
    if (buf) { strcpy(buf, l); strcat(buf, r); }
    return buf;
}

char* CAlloc_alloc(CAlloc* self, int64_t size, int64_t alignment) {
    {
    return malloc(size);
}
}
char* CAlloc_realloc(CAlloc* self, char* ptr, int64_t old_size, int64_t new_size, int64_t alignment) {
    {
    return realloc(ptr, new_size);
}
}
void CAlloc_free(CAlloc* self, char* ptr) {
    {
    free(ptr);
}
}
void CAlloc_deinit(CAlloc* self) {
}
int64_t class_obj_size(int64_t idx) {
    return (8 << idx);
}
int64_t class_for(int64_t sz) {
    if (sz <= 8) {
    return 0;
}
    if (sz <= 16) {
    return 1;
}
    if (sz <= 32) {
    return 2;
}
    if (sz <= 64) {
    return 3;
}
    if (sz <= 128) {
    return 4;
}
    if (sz <= 256) {
    return 5;
}
    if (sz <= 512) {
    return 6;
}
    if (sz <= 1024) {
    return 7;
}
    if (sz <= 2048) {
    return 8;
}
    if (sz <= 4096) {
    return 9;
}
    if (sz <= 8192) {
    return 10;
}
    if (sz <= 16384) {
    return 11;
}
    return (-1);
}
bool is_small(int64_t sz) {
    return (sz <= 16384);
}
int64_t page_align_up(int64_t n) {
    return ((n + 4095) & (-4096));
}
KaiAllocator KaiAllocator_init(void) {
    KaiAllocator self = (KaiAllocator){0};
    {
    char* ptr = mmap((char*)(0), 4096, 3, 4098, (-1), 0);
    self.heads = ptr;
    self.used = 0;
}
    return self;
}
char* KaiAllocator_get_head(KaiAllocator* self, int64_t idx) {
    {
    char** arr = (char**)(self->heads);
    return (arr)[idx];
}
}
void KaiAllocator_set_head(KaiAllocator* self, int64_t idx, char* head) {
    {
    char** arr = (char**)(self->heads);
    (arr)[idx] = head;
}
}
char* KaiAllocator_allocate_slab(KaiAllocator* self, int64_t idx) {
    {
    char* raw = mmap((char*)(0), 131072, 3, 4098, (-1), 0);
    if ((int64_t)(raw) == (-1)) {
    return (char*)(0);
}
    int64_t aligned_addr = (((int64_t)(raw) + 65535) & (-65536));
    char* slab = (char*)(aligned_addr);
    int64_t before = (aligned_addr - (int64_t)(raw));
    if (before > 0) {
    munmap(raw, before);
}
    int64_t after_start = (aligned_addr + 65536);
    int64_t after_len = (((int64_t)(raw) + 131072) - after_start);
    if (after_len > 0) {
    munmap((char*)(after_start), after_len);
}
    int64_t objsz = class_obj_size(idx);
    SlabHeader* hdr = (SlabHeader*)(slab);
    hdr->magic = 1262569811;
    hdr->obj_size = objsz;
    hdr->capacity = ((65536 - 64) / objsz);
    hdr->free_cnt = 0;
    hdr->free_head = (char*)(0);
    hdr->next_bump_idx = 0;
    hdr->pad = 0;
    hdr->next = KaiAllocator_get_head(self, idx);
    KaiAllocator_set_head(self, idx, slab);
    return slab;
}
}
char* KaiAllocator_alloc_large(KaiAllocator* self, int64_t size) {
    {
    int64_t total = (size + 16);
    int64_t page_aligned = page_align_up(total);
    char* raw = mmap((char*)(0), (page_aligned + 65536), 3, 4098, (-1), 0);
    if ((int64_t)(raw) == (-1)) {
    return (char*)(0);
}
    int64_t aligned_addr = (((int64_t)(raw) + 65535) & (-65536));
    char* slab = (char*)(aligned_addr);
    ((int64_t*)(slab))[0] = (int64_t)(raw);
    ((int64_t*)(slab))[1] = size;
    self->used = (self->used + size);
    return (char*)((aligned_addr + 16));
}
}
void KaiAllocator_free_large(KaiAllocator* self, char* ptr) {
    {
    int64_t slab_addr = ((int64_t)(ptr) & (-65536));
    int64_t raw_ptr = ((int64_t*)((char*)(slab_addr)))[0];
    int64_t orig_size = ((int64_t*)((char*)(slab_addr)))[1];
    int64_t mmap_size = (page_align_up((orig_size + 16)) + 65536);
    self->used = (self->used - orig_size);
    munmap((char*)(raw_ptr), mmap_size);
}
}
char* KaiAllocator_alloc(KaiAllocator* self, int64_t size, int64_t align) {
    if (!is_small(size)) {
    return KaiAllocator_alloc_large(self, size);
}
    int64_t idx = class_for(size);
    int64_t objsz = class_obj_size(idx);
    {
    char* slab = KaiAllocator_get_head(self, idx);
    while (slab != (char*)(0)) {
    SlabHeader* hdr = (SlabHeader*)(slab);
    if (hdr->free_head != (char*)(0)) {
    char* ptr = hdr->free_head;
    hdr->free_head = ((FreeBlock*)(ptr))->next;
    hdr->free_cnt = (hdr->free_cnt - 1);
    self->used = (self->used + objsz);
    return ptr;
}
    if (hdr->next_bump_idx < hdr->capacity) {
    int64_t off = (64 + (hdr->next_bump_idx * objsz));
    char* ptr = (char*)(((int64_t)(slab) + off));
    hdr->next_bump_idx = (hdr->next_bump_idx + 1);
    self->used = (self->used + objsz);
    return ptr;
}
    slab = hdr->next;
}
    char* ns = KaiAllocator_allocate_slab(self, idx);
    if (ns == (char*)(0)) {
    return (char*)(0);
}
    SlabHeader* hdr = (SlabHeader*)(ns);
    hdr->next_bump_idx = 1;
    self->used = (self->used + objsz);
    return (char*)(((int64_t)(ns) + 64));
}
}
char* KaiAllocator_realloc(KaiAllocator* self, char* ptr, int64_t old_size, int64_t new_size, int64_t align) {
    if (ptr == (char*)(0)) {
    return KaiAllocator_alloc(self, new_size, align);
}
    if (new_size <= old_size) {
    return ptr;
}
    {
    int64_t slab_addr = ((int64_t)(ptr) & (-65536));
    SlabHeader* hdr = (SlabHeader*)((char*)(slab_addr));
    if (hdr->magic == 1262569811) {
    if (new_size <= hdr->obj_size) {
    return ptr;
}
    char* np = KaiAllocator_alloc(self, new_size, align);
    if (np == (char*)(0)) {
    return (char*)(0);
}
    int64_t i = 0;
    while (i < old_size) {
    (np)[i] = (ptr)[i];
    i = (i + 1);
}
    KaiAllocator_free(self, ptr);
    return np;
}
}
    char* np = KaiAllocator_alloc(self, new_size, align);
    if (np == (char*)(0)) {
    return (char*)(0);
}
    {
    int64_t i = 0;
    while (i < old_size) {
    (np)[i] = (ptr)[i];
    i = (i + 1);
}
    KaiAllocator_free(self, ptr);
}
    return np;
}
void KaiAllocator_free(KaiAllocator* self, char* ptr) {
    if (ptr == (char*)(0)) {
    return;
}
    {
    int64_t slab_addr = ((int64_t)(ptr) & (-65536));
    SlabHeader* hdr = (SlabHeader*)((char*)(slab_addr));
    if (hdr->magic == 1262569811) {
    FreeBlock* fb = (FreeBlock*)(ptr);
    fb->next = hdr->free_head;
    hdr->free_head = ptr;
    hdr->free_cnt = (hdr->free_cnt + 1);
} else {
    KaiAllocator_free_large(self, ptr);
}
}
}
void KaiAllocator_deinit(KaiAllocator* self) {
    int64_t i = 0;
    while (i < 12) {
    {
    char* slab = KaiAllocator_get_head(self, i);
    while (slab != (char*)(0)) {
    char* next = ((SlabHeader*)(slab))->next;
    munmap(slab, 65536);
    slab = next;
}
}
    i = (i + 1);
}
    {
    munmap(self->heads, page_align_up(96));
}
}
char char_at(const char* s, int64_t i) {
    return (s)[i];
}
bool is_digit(char c) {
    {
    return isdigit(c);
}
}
bool is_alpha(char c) {
    {
    return isalpha(c);
}
}
bool is_alnum(char c) {
    {
    return isalnum(c);
}
}
bool is_space(char c) {
    {
    return isspace(c);
}
}
char to_upper(char c) {
    {
    return toupper(c);
}
}
char to_lower(char c) {
    {
    return tolower(c);
}
}
int64_t length(const char* s) {
    {
    return strlen(s);
}
}
StringBuilder StringBuilder_init(KaiAllocator* allocator) {
    StringBuilder self = (StringBuilder){0};
    self.len = 0;
    self.cap = 16;
    self.allocator = allocator;
    {
    self.data = (char*)(KaiAllocator_alloc(allocator, (self.cap * sizeof(char)), 1));
}
    return self;
}
void StringBuilder_append_char(StringBuilder* self, char c) {
    if ((self->len + 1) >= self->cap) {
    int64_t new_cap = (self->cap * 2);
    {
    char* new_data = (char*)(KaiAllocator_alloc(self->allocator, (new_cap * sizeof(char)), 1));
    int64_t i = 0;
    while (i < self->len) {
    (new_data)[i] = (self->data)[i];
    i = (i + 1);
}
    KaiAllocator_free(self->allocator, self->data);
    self->data = new_data;
    self->cap = new_cap;
}
}
    (self->data)[self->len] = c;
    self->len = (self->len + 1);
    (self->data)[self->len] = ((char)(0));
}
void StringBuilder_append_str(StringBuilder* self, const char* s) {
    int64_t i = 0;
    while ((s)[i] != ((char)(0))) {
    StringBuilder_append_char(self, (s)[i]);
    i = (i + 1);
}
}
void StringBuilder_append(StringBuilder* self, const char* s) {
    StringBuilder_append_str(self, s);
}
const char* StringBuilder_to_str(StringBuilder* self) {
    return (const char*)(self->data);
}
void StringBuilder_deinit(StringBuilder* self) {
    {
    KaiAllocator_free(self->allocator, self->data);
}
}
const char* int_to_str(int64_t n) {
    {
    KaiAllocator allocator = (KaiAllocator){ .heads = (char*)(0), .used = 0 };
    allocator = KaiAllocator_init();
    KaiAllocator* alloc_ptr = (KaiAllocator*)(&(allocator));
    StringBuilder sb = StringBuilder_init(alloc_ptr);
    int64_t num = n;
    if (num < 0) {
    StringBuilder_append_char(&(sb), ((char)(45)));
    num = (-num);
}
    int64_t divisor = 1;
    int64_t tmp = num;
    while (tmp >= 10) {
    divisor = (divisor * 10);
    tmp = (tmp / 10);
}
    while (divisor > 0) {
    int64_t digit = ((num / divisor) % 10);
    StringBuilder_append_char(&(sb), ((char)((48 + digit))));
    divisor = (divisor / 10);
}
    return StringBuilder_to_str(&(sb));
}
}
const char* char_to_str(char c) {
    {
    KaiAllocator allocator = (KaiAllocator){ .heads = (char*)(0), .used = 0 };
    allocator = KaiAllocator_init();
    StringBuilder sb = StringBuilder_init((KaiAllocator*)(&(allocator)));
    StringBuilder_append_char(&(sb), c);
    return StringBuilder_to_str(&(sb));
}
}
const char* substring(const char* s, int64_t start, int64_t end) {
    {
    KaiAllocator allocator = (KaiAllocator){ .heads = (char*)(0), .used = 0 };
    allocator = KaiAllocator_init();
    StringBuilder sb = StringBuilder_init((KaiAllocator*)(&(allocator)));
    int64_t i = start;
    if (i < 0) {
    i = 0;
}
    while (((s)[i] != ((char)(0))) && (i < end)) {
    StringBuilder_append_char(&(sb), (s)[i]);
    i = (i + 1);
}
    return StringBuilder_to_str(&(sb));
}
}
const char* Point_describe(Point* self) {
    return _kai_str_concat(_kai_str_concat(_kai_str_concat(_kai_str_concat("Point(", int_to_str(self->x)), ", "), int_to_str(self->y)), ")");
}
Result_Int_FileError divide_or_error(bool flag) {
    if (flag) {
    return (Result_Int_FileError){ .tag = 0, .value = 42 };
}
    return (Result_Int_FileError){ .tag = FileError_not_found };
}
Optional_Int get_optional_value(bool flag) {
    if (flag) {
    return (Optional_Int){ .has_value = true, .value = 42 };
}
    return (Optional_Int){0};
}
int64_t identity_Int(int64_t val) {
    return val;
}
int main(int argc, char** argv) {
    KaiAllocator allocator = (KaiAllocator){ .heads = (char*)(0), .used = 0 };
    allocator = KaiAllocator_init();
    _kai_set_current_allocator((void*)(&(allocator)));
    int64_t a = 10;
    int64_t b = 20;
    b = (b + a);
    printf("%s\n", "Arithmetic check: ");
    print_int(b);
    printf("%s\n", "\n");
    Point p = (Point){ .x = 3, .y = 4 };
    printf("%s\n", "Trait check: ");
    printf("%s\n", Point_describe(&(p)));
    printf("%s\n", "\n");
    int64_t id_int = identity_Int(100);
    printf("%s\n", "Generics check: ");
    print_int(id_int);
    printf("%s\n", "\n");
    int64_t res_ok = ({ Result_Int_FileError _kai_cr = (divide_or_error(true)); int64_t _kai_cv; if (_kai_cr.tag != 0) { int64_t err = _kai_cr.tag; _kai_cv = (({
    99;
})); } else { _kai_cv = _kai_cr.value; } _kai_cv; });
    int64_t res_err = ({ Result_Int_FileError _kai_cr = (divide_or_error(false)); int64_t _kai_cv; if (_kai_cr.tag != 0) { int64_t err = _kai_cr.tag; _kai_cv = (({
    100;
})); } else { _kai_cv = _kai_cr.value; } _kai_cv; });
    printf("%s\n", "Error Union OK: ");
    print_int(res_ok);
    printf("%s\n", "\n");
    printf("%s\n", "Error Union Catch: ");
    print_int(res_err);
    printf("%s\n", "\n");
    Optional_Int opt_some = get_optional_value(true);
    Optional_Int opt_none = get_optional_value(false);
    {
    Optional_Int _kai_opt = opt_some;
    if (_kai_opt.has_value) {
        int64_t val = _kai_opt.value;
        {
    printf("%s\n", "Optional if-let: ");
    print_int(val);
    printf("%s\n", "\n");
}
    }
}
    int64_t fallback = ({ Optional_Int _kai_opt = (opt_none); int64_t _kai_cv; if (_kai_opt.has_value) { _kai_cv = _kai_opt.value; } else { _kai_cv = (({
    99;
})); } _kai_cv; });
    printf("%s\n", "Optional catch: ");
    print_int(fallback);
    printf("%s\n", "\n");
    int64_t sum = 0;
    int64_t i = 0;
    while (i < 5) {
    sum = (sum + i);
    i = (i + 1);
}
    printf("%s\n", "While loop sum: ");
    print_int(sum);
    printf("%s\n", "\n");
    {
    int64_t* ptr = &(b);
    printf("%s\n", "Unsafe ptr read: ");
    print_int(*(ptr));
    printf("%s\n", "\n");
}
    {
    int64_t __ret_val = 0;
    {
    printf("%s\n", "Final defer run: Success\n");
}
    return __ret_val;
}
    {
    printf("%s\n", "Final defer run: Success\n");
}
}