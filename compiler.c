#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef __kai_std_str_concat_alloc
#define __kai_std_str_concat_alloc concatAlloc
#endif
#ifndef NO_GET_EXE_DIR
#include "std/os/os.h"
int64_t get_exe_dir(char* out_buf, int64_t max_len) {
    return kai_os_get_exe_dir(out_buf, max_len);
}
#endif

static char* __kai_str_sub(const char* s, int64_t start, int64_t end) {
    int64_t len = strlen(s);
    if (end > len) end = len;
    if (start < 0) start = 0;
    if (start >= end) {
        char* empty = malloc(1);
        if (empty) empty[0] = '\0';
        return empty;
    }
    int64_t sub_len = end - start;
    char* buf = malloc(sub_len + 1);
    if (buf) {
        memcpy(buf, s + start, sub_len);
        buf[sub_len] = '\0';
    }
    return buf;
}

static void* __kai_arr_sub(const void* arr, int64_t start, int64_t end, int64_t elem_size) {
    int64_t count = end - start;
    if (count <= 0) return NULL;
    size_t total = (size_t)count * (size_t)elem_size;
    void* buf = malloc(total);
    if (buf) memcpy(buf, (const char*)arr + start * elem_size, total);
    return buf;
}

/* C FFI Imports */
#include "std/fs/fs.h"
#include "std/llvm/core.h"
#ifndef MAP_FAILED
#define MAP_FAILED ((void*)-1)
#endif
#ifndef MAP_PRIVATE
#define MAP_PRIVATE 2
#endif
#ifndef MAP_ANONYMOUS
#ifdef __APPLE__
#define MAP_ANONYMOUS 0x1000
#else
#define MAP_ANONYMOUS 0x20
#endif
#endif
extern void* mmap(void* addr, unsigned long long length, int prot, int flags, int fd, long long offset);
extern int munmap(void* addr, unsigned long long length);

void __kai_print_int(int64_t v) {
    printf("%lld\n", (long long)(v));
}

void __kai_print_float(double v) {
    printf("%f\n", (double)(v));
}

static inline uint8_t* _kai_mmap(uint8_t* addr, int64_t length, int64_t prot, int64_t flags, int64_t fd, int64_t offset) {
    return (uint8_t*)mmap(addr, length, prot, MAP_PRIVATE | MAP_ANONYMOUS, fd, offset);
}

static inline int64_t _kai_munmap(uint8_t* addr, int64_t length) {
    return munmap(addr, length);
}

extern void __kai_panic(const char* msg);
#ifndef __KAI_NO_PANIC
void __kai_panic(const char* msg) {
    fprintf(stderr, "KAI PANIC: %s\n", msg);
    fflush(stderr);
    abort();
}
#endif

typedef struct CAlloc CAlloc;
typedef struct SlabHeader SlabHeader;
typedef struct FreeBlock FreeBlock;
typedef struct KaiAllocator KaiAllocator;
typedef struct Lexer Lexer;
typedef struct StringBuilder StringBuilder;
typedef struct Parser Parser;
typedef struct Token Token;
typedef struct DropVarEntry DropVarEntry;
typedef struct FieldInit FieldInit;
typedef struct Param Param;
typedef struct StructField StructField;
typedef struct Variant Variant;
typedef struct MatchCase MatchCase;
typedef struct StrInterpPart StrInterpPart;
typedef struct AsmOutput AsmOutput;
typedef struct AsmInput AsmInput;
typedef struct PatternNode PatternNode;
typedef struct ExprNode ExprNode;
typedef struct StmtNode StmtNode;
typedef struct Dir Dir;
typedef struct StringPool StringPool;
typedef struct PtrRefResult PtrRefResult;
typedef struct StructInfo StructInfo;
typedef struct FuncEffect FuncEffect;
typedef struct SymTrackState SymTrackState;
typedef struct TypeChecker TypeChecker;
typedef struct Symbol Symbol;
typedef struct SymbolTable SymbolTable;
typedef struct ImportResolver ImportResolver;
typedef struct Type Type;
typedef struct TypeArena TypeArena;
typedef struct StrMapEntry StrMapEntry;
typedef struct Codegen Codegen;
typedef struct StrBuf StrBuf;
typedef struct CgbMapEntry CgbMapEntry;
typedef struct CodegenBuilder CodegenBuilder;
typedef struct CCodeBuilder CCodeBuilder;
typedef struct CType CType;
typedef struct CExprNode CExprNode;
typedef struct CStmtNode CStmtNode;
typedef struct CDeclNode CDeclNode;
typedef struct CUnit CUnit;
typedef struct CPrinter CPrinter;
typedef struct LLVMStrMapEntry LLVMStrMapEntry;
typedef struct LLVMCodegen LLVMCodegen;
typedef struct ErrorInfo ErrorInfo;
typedef struct ErrorEntry ErrorEntry;
struct CAlloc {
    int64_t dummy;
    int64_t _pad;
};
struct SlabHeader {
    int64_t magic;
    int64_t obj_size;
    int64_t capacity;
    int64_t free_cnt;
    uint8_t* free_head;
    int64_t next_bump_idx;
    int64_t pad;
    uint8_t* next;
};
struct FreeBlock {
    uint8_t* next;
};
struct KaiAllocator {
    uint8_t* heads;
    int64_t used;
};
typedef enum {
    IoError_open_failed = 1,
} IoError;
typedef struct ArrayList_Token ArrayList_Token;
struct ArrayList_Token {
    Token* data;
    int64_t len;
    int64_t cap;
    KaiAllocator* allocator;
};
typedef struct ArrayList_Int ArrayList_Int;
struct ArrayList_Int {
    int64_t* data;
    int64_t len;
    int64_t cap;
    KaiAllocator* allocator;
};
struct Lexer {
    KaiAllocator* allocator;
    const char* source;
    const char* source_file;
    int64_t source_len;
    int64_t cursor;
    int64_t line;
    int64_t column;
    ArrayList_Token* tokens;
    ArrayList_Int* indent_stack;
    int64_t paren_depth;
    int64_t brace_depth;
    bool has_error;
    StringPool* pool;
};
struct StringBuilder {
    char* data;
    int64_t len;
    int64_t cap;
    KaiAllocator* allocator;
};
typedef struct ArrayList_ExprNode ArrayList_ExprNode;
struct ArrayList_ExprNode {
    ExprNode* data;
    int64_t len;
    int64_t cap;
    KaiAllocator* allocator;
};
typedef struct ArrayList_StmtNode ArrayList_StmtNode;
struct ArrayList_StmtNode {
    StmtNode* data;
    int64_t len;
    int64_t cap;
    KaiAllocator* allocator;
};
typedef struct ArrayList_PatternNode ArrayList_PatternNode;
struct ArrayList_PatternNode {
    PatternNode* data;
    int64_t len;
    int64_t cap;
    KaiAllocator* allocator;
};
struct Parser {
    KaiAllocator* allocator;
    const char* source_file;
    const char* source;
    ArrayList_Token* tokens;
    int64_t cursor;
    bool pending_gt;
    int64_t pending_gt_line;
    int64_t pending_gt_col;
    ArrayList_ExprNode* expr_pool;
    ArrayList_StmtNode* stmt_pool;
    ArrayList_PatternNode* pattern_pool;
    int64_t stmt_line;
    int64_t stmt_col;
    StringPool* pool;
};
typedef enum {
    TokenType_INT_LIT,
    TokenType_FLOAT_LIT,
    TokenType_BOOL_LIT,
    TokenType_CHAR_LIT,
    TokenType_STRING_LIT,
    TokenType_IDENTIFIER,
    TokenType_LET,
    TokenType_VAR,
    TokenType_FUNC,
    TokenType_IF,
    TokenType_ELSE,
    TokenType_WHILE,
    TokenType_FOR,
    TokenType_IN,
    TokenType_RETURN,
    TokenType_STRUCT,
    TokenType_IMPL,
    TokenType_MUT,
    TokenType_UNSAFE,
    TokenType_EXTERN,
    TokenType_ENUM,
    TokenType_MATCH,
    TokenType_CASE,
    TokenType_USE,
    TokenType_CHECK,
    TokenType_TRAIT,
    TokenType_PUB,
    TokenType_IMPORT,
    TokenType_CIMPORT,
    TokenType_FROM,
    TokenType_AS,
    TokenType_SIZEOF,
    TokenType_DEFER,
    TokenType_ERRDEFER,
    TokenType_NONE,
    TokenType_FN,
    TokenType_TRY,
    TokenType_CATCH,
    TokenType_OWN,
    TokenType_ERROR,
    TokenType_ASM,
    TokenType_VOLATILE,
    TokenType_PLUS,
    TokenType_MINUS,
    TokenType_MUL,
    TokenType_DIV,
    TokenType_MOD,
    TokenType_ASSIGN,
    TokenType_PLUS_ASSIGN,
    TokenType_MINUS_ASSIGN,
    TokenType_AND,
    TokenType_OR,
    TokenType_NOT,
    TokenType_PIPE,
    TokenType_BITXOR,
    TokenType_BITNOT,
    TokenType_LSHIFT,
    TokenType_RSHIFT,
    TokenType_EQ,
    TokenType_NE,
    TokenType_LT,
    TokenType_LE,
    TokenType_GT,
    TokenType_GE,
    TokenType_COLON,
    TokenType_ARROW,
    TokenType_FAT_ARROW,
    TokenType_COMMA,
    TokenType_LPAREN,
    TokenType_RPAREN,
    TokenType_LBRACKET,
    TokenType_RBRACKET,
    TokenType_LBRACE,
    TokenType_RBRACE,
    TokenType_DOTDOT,
    TokenType_DOTDOTEQ,
    TokenType_DOT,
    TokenType_AMP,
    TokenType_HASH,
    TokenType_QUESTION,
    TokenType_SEMICOLON,
    TokenType_BREAK,
    TokenType_CONTINUE,
    TokenType_NEWLINE,
    TokenType_INDENT,
    TokenType_DEDENT,
    TokenType_EOF,
} TokenType;
typedef enum {
    TokenValue_tv_none_TAG,
    TokenValue_tv_int_TAG,
    TokenValue_tv_float_TAG,
    TokenValue_tv_bool_TAG,
    TokenValue_tv_char_TAG,
    TokenValue_tv_str_TAG,
} TokenValue_tags;
typedef struct TokenValue TokenValue;
struct TokenValue {
    uint8_t tag;
    union {
        struct {
            int64_t v;
        } tv_int;
        struct {
            double v;
        } tv_float;
        struct {
            bool v;
        } tv_bool;
        struct {
            char v;
        } tv_char;
        struct {
            int64_t v;
        } tv_str;
    } payload;
};
struct Token {
    TokenType tok_type;
    TokenValue value;
    int64_t line;
    int64_t column;
};
struct DropVarEntry {
    const char* name;
    const char* base_type;
};
struct FieldInit {
    const char* name;
    int64_t value;
};
struct Param {
    const char* name;
    const char* ptype;
};
struct StructField {
    const char* name;
    const char* ftype;
};
typedef struct ArrayList_Param ArrayList_Param;
struct ArrayList_Param {
    Param* data;
    int64_t len;
    int64_t cap;
    KaiAllocator* allocator;
};
struct Variant {
    const char* vname;
    ArrayList_Param params;
};
struct MatchCase {
    int64_t pattern;
    int64_t body;
};
struct StrInterpPart {
    int64_t kind;
    const char* str_val;
    int64_t expr_idx;
};
struct AsmOutput {
    const char* name;
    const char* constraint;
    const char* type_name;
    int64_t expr_idx;
};
struct AsmInput {
    const char* name;
    const char* constraint;
    int64_t expr_idx;
};
typedef enum {
    PatternKind_pk_variant,
    PatternKind_pk_literal,
    PatternKind_pk_else,
} PatternKind;
typedef struct ArrayList_Str ArrayList_Str;
struct ArrayList_Str {
    const char** data;
    int64_t len;
    int64_t cap;
    KaiAllocator* allocator;
};
struct PatternNode {
    PatternKind kind;
    const char* variant_name;
    ArrayList_Str bindings;
    TokenValue lit_value;
};
typedef enum {
    ExprKind_ek_none,
    ExprKind_ek_literal,
    ExprKind_ek_str_interp,
    ExprKind_ek_identifier,
    ExprKind_ek_binary_op,
    ExprKind_ek_unary_op,
    ExprKind_ek_func_call,
    ExprKind_ek_struct_init,
    ExprKind_ek_field_access,
    ExprKind_ek_method_call,
    ExprKind_ek_index,
    ExprKind_ek_check,
    ExprKind_ek_slice,
    ExprKind_ek_range,
    ExprKind_ek_array,
    ExprKind_ek_tuple,
    ExprKind_ek_borrow,
    ExprKind_ek_deref,
    ExprKind_ek_try,
    ExprKind_ek_catch,
    ExprKind_ek_asm,
} ExprKind;
typedef struct ArrayList_StrInterpPart ArrayList_StrInterpPart;
struct ArrayList_StrInterpPart {
    StrInterpPart* data;
    int64_t len;
    int64_t cap;
    KaiAllocator* allocator;
};
typedef struct ArrayList_FieldInit ArrayList_FieldInit;
struct ArrayList_FieldInit {
    FieldInit* data;
    int64_t len;
    int64_t cap;
    KaiAllocator* allocator;
};
typedef struct ArrayList_AsmOutput ArrayList_AsmOutput;
struct ArrayList_AsmOutput {
    AsmOutput* data;
    int64_t len;
    int64_t cap;
    KaiAllocator* allocator;
};
typedef struct ArrayList_AsmInput ArrayList_AsmInput;
struct ArrayList_AsmInput {
    AsmInput* data;
    int64_t len;
    int64_t cap;
    KaiAllocator* allocator;
};
struct ExprNode {
    ExprKind kind;
    int64_t line;
    int64_t col;
    const char* inferred_type;
    int64_t resolved_symbol_idx;
    int64_t type_id;
    TokenValue lit_value;
    const char* lit_vkind;
    ArrayList_StrInterpPart interp_parts;
    const char* ident_name;
    ArrayList_Str ident_type_args;
    const char* binop_op;
    int64_t binop_left;
    int64_t binop_right;
    const char* unop_op;
    int64_t unop_operand;
    const char* func_name;
    ArrayList_Int func_args;
    ArrayList_Str func_type_args;
    const char* struct_name;
    ArrayList_FieldInit struct_fields;
    int64_t field_expr;
    const char* field_name;
    int64_t meth_expr;
    const char* meth_name;
    ArrayList_Int meth_args;
    int64_t idx_expr;
    int64_t idx_index;
    int64_t check_expr;
    int64_t slice_expr;
    int64_t slice_lower;
    int64_t slice_upper;
    bool slice_inclusive;
    int64_t range_start;
    int64_t range_end;
    bool range_inclusive;
    ArrayList_Int arr_elements;
    ArrayList_Int tup_elements;
    int64_t borrow_expr;
    bool borrow_mut;
    int64_t deref_expr;
    int64_t try_expr;
    int64_t catch_expr;
    const char* catch_var;
    int64_t catch_fallback;
    const char* asm_code;
    bool asm_is_volatile;
    ArrayList_AsmOutput asm_outputs;
    ArrayList_AsmInput asm_inputs;
    ArrayList_Str asm_clobbers;
};
typedef enum {
    StmtKind_sk_none,
    StmtKind_sk_block,
    StmtKind_sk_var_decl,
    StmtKind_sk_assignment,
    StmtKind_sk_func_decl,
    StmtKind_sk_struct_decl,
    StmtKind_sk_impl_block,
    StmtKind_sk_trait_decl,
    StmtKind_sk_enum_decl,
    StmtKind_sk_if,
    StmtKind_sk_if_let,
    StmtKind_sk_while,
    StmtKind_sk_for,
    StmtKind_sk_return,
    StmtKind_sk_print,
    StmtKind_sk_expr,
    StmtKind_sk_defer,
    StmtKind_sk_errdefer,
    StmtKind_sk_unsafe,
    StmtKind_sk_extern,
    StmtKind_sk_import,
    StmtKind_sk_cimport,
    StmtKind_sk_match,
    StmtKind_sk_error_decl,
    StmtKind_sk_break,
    StmtKind_sk_continue,
} StmtKind;
typedef struct ArrayList_StructField ArrayList_StructField;
struct ArrayList_StructField {
    StructField* data;
    int64_t len;
    int64_t cap;
    KaiAllocator* allocator;
};
typedef struct ArrayList_Variant ArrayList_Variant;
struct ArrayList_Variant {
    Variant* data;
    int64_t len;
    int64_t cap;
    KaiAllocator* allocator;
};
typedef struct ArrayList_DropVarEntry ArrayList_DropVarEntry;
struct ArrayList_DropVarEntry {
    DropVarEntry* data;
    int64_t len;
    int64_t cap;
    KaiAllocator* allocator;
};
typedef struct ArrayList_MatchCase ArrayList_MatchCase;
struct ArrayList_MatchCase {
    MatchCase* data;
    int64_t len;
    int64_t cap;
    KaiAllocator* allocator;
};
struct StmtNode {
    StmtKind kind;
    int64_t line;
    int64_t col;
    ArrayList_Int block_stmts;
    const char* vardecl_name;
    const char* vardecl_type;
    int64_t vardecl_value;
    bool vardecl_mut;
    int64_t assign_target;
    int64_t assign_value;
    const char* assign_op;
    const char* func_name;
    ArrayList_Param func_params;
    const char* func_return_type;
    int64_t func_body;
    const char* func_capability;
    ArrayList_Str func_type_params;
    bool func_public;
    const char* struct_name;
    ArrayList_StructField struct_fields;
    ArrayList_Str struct_type_params;
    ArrayList_Int struct_methods;
    ArrayList_Int struct_trait_impls;
    bool struct_public;
    const char* impl_struct_name;
    const char* impl_trait_name;
    ArrayList_Int impl_methods;
    const char* trait_name;
    ArrayList_Int trait_methods;
    bool trait_public;
    const char* enum_name;
    ArrayList_Variant enum_variants;
    ArrayList_Str enum_type_params;
    bool enum_public;
    int64_t if_cond;
    int64_t if_then;
    int64_t if_else;
    const char* iflet_var;
    int64_t iflet_expr;
    int64_t iflet_then;
    int64_t iflet_else;
    int64_t while_cond;
    int64_t while_body;
    const char* for_var;
    int64_t for_start;
    int64_t for_end;
    bool for_inclusive;
    int64_t for_body;
    int64_t return_value;
    int64_t print_value;
    int64_t expr_stmt;
    int64_t defer_body;
    int64_t errdefer_body;
    int64_t unsafe_body;
    const char* extern_name;
    ArrayList_Param extern_params;
    const char* extern_return;
    ArrayList_Str import_path;
    const char* import_alias;
    const char* cimport_header;
    const char* cimport_alias;
    ArrayList_DropVarEntry block_drop_vars;
    bool block_is_loop_body;
    int64_t match_expr;
    ArrayList_MatchCase match_cases;
    const char* error_name;
    ArrayList_Str error_variants;
};
struct Dir {
    void* handle;
};
struct StringPool {
    ArrayList_Str strings;
    KaiAllocator* allocator;
};
struct PtrRefResult {
    bool is_ptr;
    bool is_mut;
    const char* inner;
};
struct StructInfo {
    const char* name;
    bool has_drop;
};
struct FuncEffect {
    const char* func_name;
    ArrayList_Int free_param_indices;
};
struct SymTrackState {
    const char* name;
    int64_t table_idx;
    int64_t entry_idx;
    bool moved;
    bool freed;
};
typedef struct ArrayList_Type ArrayList_Type;
struct ArrayList_Type {
    Type* data;
    int64_t len;
    int64_t cap;
    KaiAllocator* allocator;
};
struct TypeArena {
    ArrayList_Type types;
    KaiAllocator* allocator;
};
typedef struct ArrayList_SymbolTable ArrayList_SymbolTable;
struct ArrayList_SymbolTable {
    SymbolTable* data;
    int64_t len;
    int64_t cap;
    KaiAllocator* allocator;
};
typedef struct ArrayList_StructInfo ArrayList_StructInfo;
struct ArrayList_StructInfo {
    StructInfo* data;
    int64_t len;
    int64_t cap;
    KaiAllocator* allocator;
};
typedef struct ArrayList_Bool ArrayList_Bool;
struct ArrayList_Bool {
    bool* data;
    int64_t len;
    int64_t cap;
    KaiAllocator* allocator;
};
typedef struct ArrayList_SymTrackState ArrayList_SymTrackState;
struct ArrayList_SymTrackState {
    SymTrackState* data;
    int64_t len;
    int64_t cap;
    KaiAllocator* allocator;
};
typedef struct ArrayList_FuncEffect ArrayList_FuncEffect;
struct ArrayList_FuncEffect {
    FuncEffect* data;
    int64_t len;
    int64_t cap;
    KaiAllocator* allocator;
};
struct TypeChecker {
    KaiAllocator* allocator;
    ArrayList_StmtNode* stmt_pool;
    ArrayList_ExprNode* expr_pool;
    ArrayList_PatternNode* pattern_pool;
    ArrayList_SymbolTable symbol_tables;
    int64_t current_table_idx;
    ArrayList_StructInfo struct_info;
    bool has_error;
    const char* current_func_ret_type;
    const char* source_file;
    const char* source;
    ImportResolver* import_resolver;
    StringPool* pool;
    TypeArena type_arena;
    ArrayList_Str imported_names;
    ArrayList_Bool import_used;
    ArrayList_Int import_lines;
    ArrayList_Int import_cols;
    int64_t loop_depth;
    ArrayList_SymTrackState scope_deferred_flat;
    ArrayList_Int scope_deferred_sizes;
    ArrayList_Int scope_deferred_counts;
    ArrayList_FuncEffect func_effects;
};
struct Symbol {
    const char* name;
    const char* type_name;
    bool is_mutable;
    const char* kind;
    const char* llvm_value;
    bool moved;
    bool freed;
    int64_t decl_stmt_idx;
};
typedef struct ArrayList_Symbol ArrayList_Symbol;
struct ArrayList_Symbol {
    Symbol* data;
    int64_t len;
    int64_t cap;
    KaiAllocator* allocator;
};
struct SymbolTable {
    ArrayList_Symbol entries;
    int64_t parent_idx;
    KaiAllocator* allocator;
};
struct ImportResolver {
    KaiAllocator* allocator;
    ArrayList_Str loaded_modules;
    ArrayList_Str cimport_headers;
    bool has_error;
    const char* error_message;
    int64_t error_stmt_idx;
    ArrayList_Str import_stack;
    StringPool* pool;
};
typedef enum {
    TypeKind_tk_void,
    TypeKind_tk_int,
    TypeKind_tk_float,
    TypeKind_tk_bool,
    TypeKind_tk_char,
    TypeKind_tk_str,
    TypeKind_tk_pointer,
    TypeKind_tk_slice,
    TypeKind_tk_struct,
    TypeKind_tk_enum,
    TypeKind_tk_error_union,
} TypeKind;
struct Type {
    TypeKind kind;
    const char* name;
    int64_t element_type_id;
    int64_t decl_stmt_idx;
    int64_t error_set_id;
};
struct StrMapEntry {
    const char* key;
    const char* value;
};
typedef struct ArrayList_StrMapEntry ArrayList_StrMapEntry;
struct ArrayList_StrMapEntry {
    StrMapEntry* data;
    int64_t len;
    int64_t cap;
    KaiAllocator* allocator;
};
struct Codegen {
    KaiAllocator* allocator;
    ArrayList_StmtNode* stmt_pool;
    ArrayList_ExprNode* expr_pool;
    ArrayList_PatternNode* pattern_pool;
    ImportResolver* import_resolver;
    StringPool* pool;
    StringBuilder output;
    StringBuilder struct_decls;
    StringBuilder func_decls;
    const char* cur_func_name;
    const char* cur_return_type;
    bool cur_method_is_init;
    ArrayList_StrMapEntry func_types;
    ArrayList_StrMapEntry var_types;
    ArrayList_Int block_stack;
    ArrayList_StrMapEntry generic_struct_decls;
    ArrayList_StrMapEntry generic_enum_decls;
    ArrayList_StrMapEntry generic_func_decls;
    ArrayList_StrMapEntry generic_impl_blocks;
    ArrayList_Str monomorphized_types;
    ArrayList_StrMapEntry current_type_map;
    ArrayList_StrMapEntry enum_decls;
    ArrayList_Str result_definitions;
    ArrayList_Int defer_stack;
    ArrayList_Int defer_depths;
    ArrayList_StrMapEntry func_param_types;
};
struct StrBuf {
    KaiAllocator* alloc;
    ArrayList_Str parts;
};
struct CgbMapEntry {
    const char* key;
    const char* value;
};
struct CCodeBuilder {
    KaiAllocator* alloc;
    ArrayList_Str lines;
    int64_t indent_level;
};
typedef struct ArrayList_CgbMapEntry ArrayList_CgbMapEntry;
struct ArrayList_CgbMapEntry {
    CgbMapEntry* data;
    int64_t len;
    int64_t cap;
    KaiAllocator* allocator;
};
typedef struct ArrayList_CExprNode ArrayList_CExprNode;
struct ArrayList_CExprNode {
    CExprNode* data;
    int64_t len;
    int64_t cap;
    KaiAllocator* allocator;
};
typedef struct ArrayList_CStmtNode ArrayList_CStmtNode;
struct ArrayList_CStmtNode {
    CStmtNode* data;
    int64_t len;
    int64_t cap;
    KaiAllocator* allocator;
};
struct CodegenBuilder {
    KaiAllocator* allocator;
    ArrayList_StmtNode* stmt_pool;
    ArrayList_ExprNode* expr_pool;
    ArrayList_PatternNode* pattern_pool;
    ImportResolver* import_resolver;
    StringPool* pool;
    CCodeBuilder builder;
    StrBuf struct_decls;
    StrBuf func_decls;
    StrBuf output_body;
    const char* cur_func_name;
    const char* cur_return_type;
    bool cur_method_is_init;
    ArrayList_CgbMapEntry func_types;
    ArrayList_CgbMapEntry var_types;
    ArrayList_Int block_stack;
    ArrayList_CgbMapEntry generic_struct_decls;
    ArrayList_CgbMapEntry generic_enum_decls;
    ArrayList_CgbMapEntry generic_func_decls;
    ArrayList_CgbMapEntry generic_impl_blocks;
    ArrayList_Str monomorphized_types;
    ArrayList_CgbMapEntry current_type_map;
    ArrayList_CgbMapEntry enum_decls;
    ArrayList_Str result_definitions;
    ArrayList_Int defer_stack;
    ArrayList_Int defer_depths;
    ArrayList_CgbMapEntry func_param_types;
    StrBuf type_defs;
    StrBuf monomorphized_bodies;
    ArrayList_CExprNode c_exprs;
    ArrayList_CStmtNode c_stmts;
};
struct CType {
    const char* base;
    int64_t pointer;
    bool is_const;
    bool is_unsigned;
    ArrayList_Str array_sizes;
};
typedef enum {
    CExprKind_ck_int_lit,
    CExprKind_ck_float_lit,
    CExprKind_ck_str_lit,
    CExprKind_ck_char_lit,
    CExprKind_ck_bool_lit,
    CExprKind_ck_ident,
    CExprKind_ck_binary,
    CExprKind_ck_unary,
    CExprKind_ck_call,
    CExprKind_ck_field,
    CExprKind_ck_arrow,
    CExprKind_ck_index,
    CExprKind_ck_cast,
    CExprKind_ck_compound,
    CExprKind_ck_ternary,
    CExprKind_ck_sizeof_type,
    CExprKind_ck_sizeof_expr,
    CExprKind_ck_assign,
    CExprKind_ck_comma,
    CExprKind_ck_stmt_expr,
    CExprKind_ck_member_access,
} CExprKind;
struct CExprNode {
    CExprKind kind;
    const char* int_val;
    const char* float_val;
    const char* str_val;
    const char* char_val;
    bool bool_val;
    const char* ident_name;
    int64_t binop_left;
    int64_t binop_right;
    const char* binop_op;
    int64_t unop_operand;
    const char* unop_op;
    bool is_prefix;
    int64_t call_func;
    ArrayList_Int call_args;
    const char* callee_name;
    int64_t field_expr;
    const char* field_name;
    int64_t idx_expr;
    int64_t idx_index;
    CType cast_type;
    int64_t cast_expr;
    CType compound_type;
    ArrayList_Str compound_fields;
    int64_t tern_cond;
    int64_t tern_then;
    int64_t tern_else;
    CType sizeof_type;
    int64_t sizeof_expr;
    int64_t assign_target;
    int64_t assign_value;
    const char* assign_op;
    int64_t comma_left;
    int64_t comma_right;
    ArrayList_Int stmts;
    int64_t stmt_result;
};
typedef enum {
    CStmtKind_cs_block,
    CStmtKind_cs_expr,
    CStmtKind_cs_if,
    CStmtKind_cs_while,
    CStmtKind_cs_for,
    CStmtKind_cs_do_while,
    CStmtKind_cs_return,
    CStmtKind_cs_break,
    CStmtKind_cs_continue,
    CStmtKind_cs_var_decl,
    CStmtKind_cs_switch,
    CStmtKind_cs_case,
    CStmtKind_cs_default,
    CStmtKind_cs_goto,
    CStmtKind_cs_label,
    CStmtKind_cs_asm,
} CStmtKind;
struct CStmtNode {
    CStmtKind kind;
    ArrayList_Int block_stmts;
    int64_t expr_stmt;
    int64_t if_cond;
    int64_t if_then;
    int64_t if_else;
    int64_t while_cond;
    int64_t while_body;
    int64_t for_init;
    int64_t for_cond;
    int64_t for_inc;
    int64_t for_body;
    int64_t do_body;
    int64_t do_cond;
    int64_t return_val;
    CType var_type;
    const char* var_name;
    int64_t var_init;
    int64_t switch_expr;
    const char* case_val;
    const char* label_name;
    const char* asm_code;
    bool asm_volatile;
};
struct CDeclNode {
    bool is_function;
    CType func_ret;
    const char* func_name;
    ArrayList_Str func_params;
    bool func_vararg;
    ArrayList_Int func_body;
    bool is_extern;
    CType var_type;
    const char* var_name;
    int64_t var_init;
    bool is_struct;
    const char* struct_name;
    ArrayList_Str struct_fields;
    bool is_enum;
    const char* enum_name;
    ArrayList_Str enum_variants;
    bool is_tagged_enum;
    const char* tagged_name;
    ArrayList_Str tagged_variants;
    bool is_tagged_union_struct;
    bool is_typedef;
    const char* typedef_alias;
    CType typedef_def;
};
typedef struct ArrayList_CDeclNode ArrayList_CDeclNode;
struct ArrayList_CDeclNode {
    CDeclNode* data;
    int64_t len;
    int64_t cap;
    KaiAllocator* allocator;
};
struct CUnit {
    ArrayList_Str includes;
    ArrayList_CDeclNode decls;
};
struct CPrinter {
    CCodeBuilder* builder;
    ArrayList_CExprNode* expr_pool;
    ArrayList_CStmtNode* stmt_pool;
};
struct LLVMStrMapEntry {
    const char* key;
    const char* value;
};
typedef struct ArrayList_LLVMStrMapEntry ArrayList_LLVMStrMapEntry;
struct ArrayList_LLVMStrMapEntry {
    LLVMStrMapEntry* data;
    int64_t len;
    int64_t cap;
    KaiAllocator* allocator;
};
struct LLVMCodegen {
    KaiAllocator* allocator;
    ArrayList_StmtNode* stmt_pool;
    ArrayList_ExprNode* expr_pool;
    ArrayList_PatternNode* pattern_pool;
    ImportResolver* import_resolver;
    StringPool* pool;
    void* ctx;
    void* module;
    void* builder;
    void* cur_func;
    const char* cur_func_name;
    void* cur_block;
    bool cur_method_is_init;
    void* cur_self_alloca;
    void* cur_struct_type;
    bool last_was_term;
    void* int1_type;
    void* int8_type;
    void* ptr_type;
    void* int32_type;
    void* int64_type;
    void* float_type;
    void* double_type;
    void* void_type;
    void* tmp_target;
    char* tmp_err;
    int64_t str_counter;
    ArrayList_Str func_type_names;
    ArrayList_Str func_type_returns;
    ArrayList_Int func_param_counts;
    ArrayList_Str func_type_param_types;
    ArrayList_Str func_cache_names;
    ArrayList_Int func_cache_vals;
    ArrayList_Int func_cache_types;
    ArrayList_Str local_alloca_names;
    ArrayList_Int local_alloca_vals;
    ArrayList_Int local_alloca_types;
    ArrayList_Str local_alloca_type_strs;
    ArrayList_Int local_alloca_decls;
    void* loop_cond_block;
    void* loop_merge_block;
    ArrayList_Str struct_cache_names;
    ArrayList_Int struct_cache_types;
    ArrayList_Int struct_cache_field_counts;
    ArrayList_Str enum_cache_names;
    ArrayList_Int enum_cache_types;
    ArrayList_Bool enum_has_payload;
    ArrayList_Str tuple_cache_names;
    ArrayList_Int tuple_cache_types;
    ArrayList_Int tuple_cache_field_counts;
    ArrayList_LLVMStrMapEntry current_type_map;
    ArrayList_LLVMStrMapEntry generic_struct_decls;
    ArrayList_LLVMStrMapEntry generic_enum_decls;
    ArrayList_Str monomorphized_types;
    ArrayList_Int method_indices;
    void* str_type;
    ArrayList_Str extern_func_names;
    ArrayList_Str kai_func_names;
};
struct ErrorInfo {
    const char* code;
    const char* title;
    const char* description;
    const char* fix;
};
struct ErrorEntry {
    const char* code;
    const char* message;
    const char* file;
};
typedef struct Result_Str_IoError Result_Str_IoError;
struct Result_Str_IoError {
    int64_t tag;
    const char* value;
};
typedef struct Result_Bool_IoError Result_Bool_IoError;
struct Result_Bool_IoError {
    int64_t tag;
    bool value;
};
typedef struct ArrayList_ArrayList_SymTrackState_ ArrayList_ArrayList_SymTrackState_;
struct ArrayList_ArrayList_SymTrackState_ {
    ArrayList_SymTrackState* data;
    int64_t len;
    int64_t cap;
    KaiAllocator* allocator;
};
typedef struct Optional_Char Optional_Char;
struct Optional_Char {
    bool has_value;
    char value;
};
typedef struct Optional_Int Optional_Int;
struct Optional_Int {
    bool has_value;
    int64_t value;
};

ArrayList_Token ArrayList_Token_init(KaiAllocator* allocator);
void ArrayList_Token_push(ArrayList_Token* self, Token item);
Token ArrayList_Token_get(ArrayList_Token* self, int64_t index);
void ArrayList_Token_set(ArrayList_Token* self, int64_t index, Token item);
Token ArrayList_Token_pop(ArrayList_Token* self);
int64_t ArrayList_Token_length(ArrayList_Token* self);
void ArrayList_Token_deinit(ArrayList_Token* self);
ArrayList_Int ArrayList_Int_init(KaiAllocator* allocator);
void ArrayList_Int_push(ArrayList_Int* self, int64_t item);
int64_t ArrayList_Int_get(ArrayList_Int* self, int64_t index);
void ArrayList_Int_set(ArrayList_Int* self, int64_t index, int64_t item);
int64_t ArrayList_Int_pop(ArrayList_Int* self);
int64_t ArrayList_Int_length(ArrayList_Int* self);
void ArrayList_Int_deinit(ArrayList_Int* self);
ArrayList_ExprNode ArrayList_ExprNode_init(KaiAllocator* allocator);
void ArrayList_ExprNode_push(ArrayList_ExprNode* self, ExprNode item);
ExprNode ArrayList_ExprNode_get(ArrayList_ExprNode* self, int64_t index);
void ArrayList_ExprNode_set(ArrayList_ExprNode* self, int64_t index, ExprNode item);
ExprNode ArrayList_ExprNode_pop(ArrayList_ExprNode* self);
int64_t ArrayList_ExprNode_length(ArrayList_ExprNode* self);
void ArrayList_ExprNode_deinit(ArrayList_ExprNode* self);
ArrayList_StmtNode ArrayList_StmtNode_init(KaiAllocator* allocator);
void ArrayList_StmtNode_push(ArrayList_StmtNode* self, StmtNode item);
StmtNode ArrayList_StmtNode_get(ArrayList_StmtNode* self, int64_t index);
void ArrayList_StmtNode_set(ArrayList_StmtNode* self, int64_t index, StmtNode item);
StmtNode ArrayList_StmtNode_pop(ArrayList_StmtNode* self);
int64_t ArrayList_StmtNode_length(ArrayList_StmtNode* self);
void ArrayList_StmtNode_deinit(ArrayList_StmtNode* self);
ArrayList_PatternNode ArrayList_PatternNode_init(KaiAllocator* allocator);
void ArrayList_PatternNode_push(ArrayList_PatternNode* self, PatternNode item);
PatternNode ArrayList_PatternNode_get(ArrayList_PatternNode* self, int64_t index);
void ArrayList_PatternNode_set(ArrayList_PatternNode* self, int64_t index, PatternNode item);
PatternNode ArrayList_PatternNode_pop(ArrayList_PatternNode* self);
int64_t ArrayList_PatternNode_length(ArrayList_PatternNode* self);
void ArrayList_PatternNode_deinit(ArrayList_PatternNode* self);
ArrayList_Param ArrayList_Param_init(KaiAllocator* allocator);
void ArrayList_Param_push(ArrayList_Param* self, Param item);
Param ArrayList_Param_get(ArrayList_Param* self, int64_t index);
void ArrayList_Param_set(ArrayList_Param* self, int64_t index, Param item);
Param ArrayList_Param_pop(ArrayList_Param* self);
int64_t ArrayList_Param_length(ArrayList_Param* self);
void ArrayList_Param_deinit(ArrayList_Param* self);
ArrayList_Str ArrayList_Str_init(KaiAllocator* allocator);
void ArrayList_Str_push(ArrayList_Str* self, const char* item);
const char* ArrayList_Str_get(ArrayList_Str* self, int64_t index);
void ArrayList_Str_set(ArrayList_Str* self, int64_t index, const char* item);
const char* ArrayList_Str_pop(ArrayList_Str* self);
int64_t ArrayList_Str_length(ArrayList_Str* self);
void ArrayList_Str_deinit(ArrayList_Str* self);
ArrayList_StrInterpPart ArrayList_StrInterpPart_init(KaiAllocator* allocator);
void ArrayList_StrInterpPart_push(ArrayList_StrInterpPart* self, StrInterpPart item);
StrInterpPart ArrayList_StrInterpPart_get(ArrayList_StrInterpPart* self, int64_t index);
void ArrayList_StrInterpPart_set(ArrayList_StrInterpPart* self, int64_t index, StrInterpPart item);
StrInterpPart ArrayList_StrInterpPart_pop(ArrayList_StrInterpPart* self);
int64_t ArrayList_StrInterpPart_length(ArrayList_StrInterpPart* self);
void ArrayList_StrInterpPart_deinit(ArrayList_StrInterpPart* self);
ArrayList_FieldInit ArrayList_FieldInit_init(KaiAllocator* allocator);
void ArrayList_FieldInit_push(ArrayList_FieldInit* self, FieldInit item);
FieldInit ArrayList_FieldInit_get(ArrayList_FieldInit* self, int64_t index);
void ArrayList_FieldInit_set(ArrayList_FieldInit* self, int64_t index, FieldInit item);
FieldInit ArrayList_FieldInit_pop(ArrayList_FieldInit* self);
int64_t ArrayList_FieldInit_length(ArrayList_FieldInit* self);
void ArrayList_FieldInit_deinit(ArrayList_FieldInit* self);
ArrayList_AsmOutput ArrayList_AsmOutput_init(KaiAllocator* allocator);
void ArrayList_AsmOutput_push(ArrayList_AsmOutput* self, AsmOutput item);
AsmOutput ArrayList_AsmOutput_get(ArrayList_AsmOutput* self, int64_t index);
void ArrayList_AsmOutput_set(ArrayList_AsmOutput* self, int64_t index, AsmOutput item);
AsmOutput ArrayList_AsmOutput_pop(ArrayList_AsmOutput* self);
int64_t ArrayList_AsmOutput_length(ArrayList_AsmOutput* self);
void ArrayList_AsmOutput_deinit(ArrayList_AsmOutput* self);
ArrayList_AsmInput ArrayList_AsmInput_init(KaiAllocator* allocator);
void ArrayList_AsmInput_push(ArrayList_AsmInput* self, AsmInput item);
AsmInput ArrayList_AsmInput_get(ArrayList_AsmInput* self, int64_t index);
void ArrayList_AsmInput_set(ArrayList_AsmInput* self, int64_t index, AsmInput item);
AsmInput ArrayList_AsmInput_pop(ArrayList_AsmInput* self);
int64_t ArrayList_AsmInput_length(ArrayList_AsmInput* self);
void ArrayList_AsmInput_deinit(ArrayList_AsmInput* self);
ArrayList_StructField ArrayList_StructField_init(KaiAllocator* allocator);
void ArrayList_StructField_push(ArrayList_StructField* self, StructField item);
StructField ArrayList_StructField_get(ArrayList_StructField* self, int64_t index);
void ArrayList_StructField_set(ArrayList_StructField* self, int64_t index, StructField item);
StructField ArrayList_StructField_pop(ArrayList_StructField* self);
int64_t ArrayList_StructField_length(ArrayList_StructField* self);
void ArrayList_StructField_deinit(ArrayList_StructField* self);
ArrayList_Variant ArrayList_Variant_init(KaiAllocator* allocator);
void ArrayList_Variant_push(ArrayList_Variant* self, Variant item);
Variant ArrayList_Variant_get(ArrayList_Variant* self, int64_t index);
void ArrayList_Variant_set(ArrayList_Variant* self, int64_t index, Variant item);
Variant ArrayList_Variant_pop(ArrayList_Variant* self);
int64_t ArrayList_Variant_length(ArrayList_Variant* self);
void ArrayList_Variant_deinit(ArrayList_Variant* self);
ArrayList_DropVarEntry ArrayList_DropVarEntry_init(KaiAllocator* allocator);
void ArrayList_DropVarEntry_push(ArrayList_DropVarEntry* self, DropVarEntry item);
DropVarEntry ArrayList_DropVarEntry_get(ArrayList_DropVarEntry* self, int64_t index);
void ArrayList_DropVarEntry_set(ArrayList_DropVarEntry* self, int64_t index, DropVarEntry item);
DropVarEntry ArrayList_DropVarEntry_pop(ArrayList_DropVarEntry* self);
int64_t ArrayList_DropVarEntry_length(ArrayList_DropVarEntry* self);
void ArrayList_DropVarEntry_deinit(ArrayList_DropVarEntry* self);
ArrayList_MatchCase ArrayList_MatchCase_init(KaiAllocator* allocator);
void ArrayList_MatchCase_push(ArrayList_MatchCase* self, MatchCase item);
MatchCase ArrayList_MatchCase_get(ArrayList_MatchCase* self, int64_t index);
void ArrayList_MatchCase_set(ArrayList_MatchCase* self, int64_t index, MatchCase item);
MatchCase ArrayList_MatchCase_pop(ArrayList_MatchCase* self);
int64_t ArrayList_MatchCase_length(ArrayList_MatchCase* self);
void ArrayList_MatchCase_deinit(ArrayList_MatchCase* self);
ArrayList_Type ArrayList_Type_init(KaiAllocator* allocator);
void ArrayList_Type_push(ArrayList_Type* self, Type item);
Type ArrayList_Type_get(ArrayList_Type* self, int64_t index);
void ArrayList_Type_set(ArrayList_Type* self, int64_t index, Type item);
Type ArrayList_Type_pop(ArrayList_Type* self);
int64_t ArrayList_Type_length(ArrayList_Type* self);
void ArrayList_Type_deinit(ArrayList_Type* self);
ArrayList_SymbolTable ArrayList_SymbolTable_init(KaiAllocator* allocator);
void ArrayList_SymbolTable_push(ArrayList_SymbolTable* self, SymbolTable item);
SymbolTable ArrayList_SymbolTable_get(ArrayList_SymbolTable* self, int64_t index);
void ArrayList_SymbolTable_set(ArrayList_SymbolTable* self, int64_t index, SymbolTable item);
SymbolTable ArrayList_SymbolTable_pop(ArrayList_SymbolTable* self);
int64_t ArrayList_SymbolTable_length(ArrayList_SymbolTable* self);
void ArrayList_SymbolTable_deinit(ArrayList_SymbolTable* self);
ArrayList_StructInfo ArrayList_StructInfo_init(KaiAllocator* allocator);
void ArrayList_StructInfo_push(ArrayList_StructInfo* self, StructInfo item);
StructInfo ArrayList_StructInfo_get(ArrayList_StructInfo* self, int64_t index);
void ArrayList_StructInfo_set(ArrayList_StructInfo* self, int64_t index, StructInfo item);
StructInfo ArrayList_StructInfo_pop(ArrayList_StructInfo* self);
int64_t ArrayList_StructInfo_length(ArrayList_StructInfo* self);
void ArrayList_StructInfo_deinit(ArrayList_StructInfo* self);
ArrayList_Bool ArrayList_Bool_init(KaiAllocator* allocator);
void ArrayList_Bool_push(ArrayList_Bool* self, bool item);
bool ArrayList_Bool_get(ArrayList_Bool* self, int64_t index);
void ArrayList_Bool_set(ArrayList_Bool* self, int64_t index, bool item);
bool ArrayList_Bool_pop(ArrayList_Bool* self);
int64_t ArrayList_Bool_length(ArrayList_Bool* self);
void ArrayList_Bool_deinit(ArrayList_Bool* self);
ArrayList_SymTrackState ArrayList_SymTrackState_init(KaiAllocator* allocator);
void ArrayList_SymTrackState_push(ArrayList_SymTrackState* self, SymTrackState item);
SymTrackState ArrayList_SymTrackState_get(ArrayList_SymTrackState* self, int64_t index);
void ArrayList_SymTrackState_set(ArrayList_SymTrackState* self, int64_t index, SymTrackState item);
SymTrackState ArrayList_SymTrackState_pop(ArrayList_SymTrackState* self);
int64_t ArrayList_SymTrackState_length(ArrayList_SymTrackState* self);
void ArrayList_SymTrackState_deinit(ArrayList_SymTrackState* self);
ArrayList_FuncEffect ArrayList_FuncEffect_init(KaiAllocator* allocator);
void ArrayList_FuncEffect_push(ArrayList_FuncEffect* self, FuncEffect item);
FuncEffect ArrayList_FuncEffect_get(ArrayList_FuncEffect* self, int64_t index);
void ArrayList_FuncEffect_set(ArrayList_FuncEffect* self, int64_t index, FuncEffect item);
FuncEffect ArrayList_FuncEffect_pop(ArrayList_FuncEffect* self);
int64_t ArrayList_FuncEffect_length(ArrayList_FuncEffect* self);
void ArrayList_FuncEffect_deinit(ArrayList_FuncEffect* self);
ArrayList_Symbol ArrayList_Symbol_init(KaiAllocator* allocator);
void ArrayList_Symbol_push(ArrayList_Symbol* self, Symbol item);
Symbol ArrayList_Symbol_get(ArrayList_Symbol* self, int64_t index);
void ArrayList_Symbol_set(ArrayList_Symbol* self, int64_t index, Symbol item);
Symbol ArrayList_Symbol_pop(ArrayList_Symbol* self);
int64_t ArrayList_Symbol_length(ArrayList_Symbol* self);
void ArrayList_Symbol_deinit(ArrayList_Symbol* self);
ArrayList_StrMapEntry ArrayList_StrMapEntry_init(KaiAllocator* allocator);
void ArrayList_StrMapEntry_push(ArrayList_StrMapEntry* self, StrMapEntry item);
StrMapEntry ArrayList_StrMapEntry_get(ArrayList_StrMapEntry* self, int64_t index);
void ArrayList_StrMapEntry_set(ArrayList_StrMapEntry* self, int64_t index, StrMapEntry item);
StrMapEntry ArrayList_StrMapEntry_pop(ArrayList_StrMapEntry* self);
int64_t ArrayList_StrMapEntry_length(ArrayList_StrMapEntry* self);
void ArrayList_StrMapEntry_deinit(ArrayList_StrMapEntry* self);
ArrayList_CgbMapEntry ArrayList_CgbMapEntry_init(KaiAllocator* allocator);
void ArrayList_CgbMapEntry_push(ArrayList_CgbMapEntry* self, CgbMapEntry item);
CgbMapEntry ArrayList_CgbMapEntry_get(ArrayList_CgbMapEntry* self, int64_t index);
void ArrayList_CgbMapEntry_set(ArrayList_CgbMapEntry* self, int64_t index, CgbMapEntry item);
CgbMapEntry ArrayList_CgbMapEntry_pop(ArrayList_CgbMapEntry* self);
int64_t ArrayList_CgbMapEntry_length(ArrayList_CgbMapEntry* self);
void ArrayList_CgbMapEntry_deinit(ArrayList_CgbMapEntry* self);
ArrayList_CExprNode ArrayList_CExprNode_init(KaiAllocator* allocator);
void ArrayList_CExprNode_push(ArrayList_CExprNode* self, CExprNode item);
CExprNode ArrayList_CExprNode_get(ArrayList_CExprNode* self, int64_t index);
void ArrayList_CExprNode_set(ArrayList_CExprNode* self, int64_t index, CExprNode item);
CExprNode ArrayList_CExprNode_pop(ArrayList_CExprNode* self);
int64_t ArrayList_CExprNode_length(ArrayList_CExprNode* self);
void ArrayList_CExprNode_deinit(ArrayList_CExprNode* self);
ArrayList_CStmtNode ArrayList_CStmtNode_init(KaiAllocator* allocator);
void ArrayList_CStmtNode_push(ArrayList_CStmtNode* self, CStmtNode item);
CStmtNode ArrayList_CStmtNode_get(ArrayList_CStmtNode* self, int64_t index);
void ArrayList_CStmtNode_set(ArrayList_CStmtNode* self, int64_t index, CStmtNode item);
CStmtNode ArrayList_CStmtNode_pop(ArrayList_CStmtNode* self);
int64_t ArrayList_CStmtNode_length(ArrayList_CStmtNode* self);
void ArrayList_CStmtNode_deinit(ArrayList_CStmtNode* self);
ArrayList_CDeclNode ArrayList_CDeclNode_init(KaiAllocator* allocator);
void ArrayList_CDeclNode_push(ArrayList_CDeclNode* self, CDeclNode item);
CDeclNode ArrayList_CDeclNode_get(ArrayList_CDeclNode* self, int64_t index);
void ArrayList_CDeclNode_set(ArrayList_CDeclNode* self, int64_t index, CDeclNode item);
CDeclNode ArrayList_CDeclNode_pop(ArrayList_CDeclNode* self);
int64_t ArrayList_CDeclNode_length(ArrayList_CDeclNode* self);
void ArrayList_CDeclNode_deinit(ArrayList_CDeclNode* self);
ArrayList_LLVMStrMapEntry ArrayList_LLVMStrMapEntry_init(KaiAllocator* allocator);
void ArrayList_LLVMStrMapEntry_push(ArrayList_LLVMStrMapEntry* self, LLVMStrMapEntry item);
LLVMStrMapEntry ArrayList_LLVMStrMapEntry_get(ArrayList_LLVMStrMapEntry* self, int64_t index);
void ArrayList_LLVMStrMapEntry_set(ArrayList_LLVMStrMapEntry* self, int64_t index, LLVMStrMapEntry item);
LLVMStrMapEntry ArrayList_LLVMStrMapEntry_pop(ArrayList_LLVMStrMapEntry* self);
int64_t ArrayList_LLVMStrMapEntry_length(ArrayList_LLVMStrMapEntry* self);
void ArrayList_LLVMStrMapEntry_deinit(ArrayList_LLVMStrMapEntry* self);
extern int64_t get_exe_dir(char* buf, int64_t max_len);
uint8_t* CAlloc_alloc(CAlloc* self, int64_t size, int64_t alignment);
uint8_t* CAlloc_realloc(CAlloc* self, uint8_t* ptr, int64_t old_size, int64_t new_size, int64_t alignment);
void CAlloc_free(CAlloc* self, uint8_t* ptr);
void CAlloc_deinit(CAlloc* self);
extern uint8_t* _kai_mmap(uint8_t* addr, int64_t length, int64_t prot, int64_t flags, int64_t fd, int64_t offset);
extern int64_t _kai_munmap(uint8_t* addr, int64_t length);
int64_t class_obj_size(int64_t idx);
int64_t class_for(int64_t sz);
bool is_small(int64_t sz);
int64_t page_align_up(int64_t n);
KaiAllocator KaiAllocator_init(void);
uint8_t* KaiAllocator_get_head(KaiAllocator* self, int64_t idx);
void KaiAllocator_set_head(KaiAllocator* self, int64_t idx, uint8_t* head);
uint8_t* KaiAllocator_allocate_slab(KaiAllocator* self, int64_t idx);
uint8_t* KaiAllocator_alloc_large(KaiAllocator* self, int64_t size);
void KaiAllocator_free_large(KaiAllocator* self, uint8_t* ptr);
uint8_t* KaiAllocator_alloc(KaiAllocator* self, int64_t size, int64_t align);
uint8_t* KaiAllocator_realloc(KaiAllocator* self, uint8_t* ptr, int64_t old_size, int64_t new_size, int64_t align);
void KaiAllocator_free(KaiAllocator* self, uint8_t* ptr);
void KaiAllocator_deinit(KaiAllocator* self);
KaiAllocator KaiAllocator_new(void);
Result_Str_IoError read_to_string(KaiAllocator* allocator, const char* path);
Result_Bool_IoError write_string(const char* path, const char* content);
const char* concatAlloc(const char* left, const char* right);
bool __kai_std_str_is_ascii_space(char byte);
char __kai_std_str_to_lower_byte(char byte);
char __kai_std_str_to_upper_byte(char byte);
const char* __kai_std_str_copy(char* buffer, const char* text);
const char* __kai_std_str_concat(char* buffer, const char* left, const char* right);
const char* __kai_std_str_repeat(char* buffer, const char* text, int64_t count);
const char* __kai_std_str_replace(char* buffer, const char* text, const char* old, const char* replacement);
const char* __kai_std_str_to_lower_ascii(char* buffer, const char* text);
const char* __kai_std_str_to_upper_ascii(char* buffer, const char* text);
const char* __kai_std_str_reverse(char* buffer, const char* text);
int64_t __kai_std_str_count_byte(const char* text, char byte);
bool __kai_std_str_starts_with(const char* text, const char* prefix);
bool __kai_std_str_ends_with(const char* text, const char* suffix);
bool __kai_std_str_contains(const char* text, const char* needle);
int64_t __kai_std_str_index_of(const char* text, const char* needle);
int64_t __kai_std_str_last_index_of(const char* text, const char* needle);
int64_t __kai_std_str_count(const char* text, const char* needle);
int64_t __kai_std_str_split_count(const char* text, const char* sep);
const char* __kai_std_str_split(const char* text, const char* sep, int64_t part_index);
bool __kai_std_str_eql_ignore_ascii_case(const char* left, const char* right);
const char* __kai_std_str_trim_ascii(const char* text);
const char* __kai_std_str_trim_start_ascii(const char* text);
const char* __kai_std_str_trim_end_ascii(const char* text);
int64_t __kai_std_str_field_count_ascii(const char* text);
const char* __kai_std_str_field_ascii(const char* text, int64_t field_index);
int64_t __kai_std_str_line_count(const char* text);
const char* __kai_std_str_line(const char* text, int64_t line_index);
int64_t __kai_std_str_word_count_ascii(const char* text);
TokenType keyword_type(const char* ident);
TokenValue make_keyword_value(const char* ident, TokenType ttype, StringPool* pool);
Lexer Lexer_init(KaiAllocator* allocator, const char* source, const char* source_file, StringPool* pool);
char Lexer_peek(Lexer* self, int64_t offset);
char Lexer_advance(Lexer* self);
void Lexer_emit(Lexer* self, TokenType ttype, TokenValue value);
void Lexer_emit_str(Lexer* self, TokenType ttype, const char* s);
void Lexer_lex_error(Lexer* self, const char* msg);
void Lexer_skip_line_comment(Lexer* self);
void Lexer_skip_block_comment(Lexer* self);
void Lexer_skip_whitespace(Lexer* self);
void Lexer_lex_identifier(Lexer* self);
void Lexer_lex_number(Lexer* self);
void Lexer_lex_string(Lexer* self);
void Lexer_lex_char(Lexer* self);
int64_t Lexer_compute_indent(Lexer* self);
void Lexer_lex(Lexer* self);
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
const char* tv_get_str(TokenValue val, StringPool* pool);
int64_t token_precedence(TokenType ttype);
const char* token_op_str(TokenType ttype);
const char* str_array_join(ArrayList_Str arr, const char* sep);
void parser_err(const char* source_file, const char* source, const char* code, const char* msg, int64_t line, int64_t col);
Parser Parser_init_with_pools(KaiAllocator* allocator, const char* source_file, ArrayList_Token* tokens, ArrayList_ExprNode* expr_pool, ArrayList_StmtNode* stmt_pool, ArrayList_PatternNode* pattern_pool, const char* source, StringPool* pool);
Parser Parser_init(KaiAllocator* allocator, const char* source_file, ArrayList_Token* tokens, const char* source, StringPool* pool);
Token Parser_peek(Parser* self, int64_t offset);
Token Parser_advance(Parser* self);
bool Parser_match_token(Parser* self, TokenType ttype);
Token Parser_expect(Parser* self, TokenType ttype);
void Parser_consume_newlines(Parser* self);
void Parser_expect_end_of_statement(Parser* self);
bool Parser_is_generic_instantiation(Parser* self);
int64_t Parser_ex_literal(Parser* self, TokenValue val, const char* vkind);
int64_t Parser_ex_ident(Parser* self, const char* name);
int64_t Parser_ex_ident_with(Parser* self, const char* name, ArrayList_Str targs);
int64_t Parser_ex_binop(Parser* self, const char* op, int64_t left, int64_t right);
int64_t Parser_ex_unop(Parser* self, const char* op, int64_t operand);
int64_t Parser_ex_call(Parser* self, const char* name, ArrayList_Int args);
int64_t Parser_ex_call_with(Parser* self, const char* name, ArrayList_Int args, ArrayList_Str targs);
int64_t Parser_ex_struct_init(Parser* self, const char* name, ArrayList_FieldInit fields);
int64_t Parser_ex_field(Parser* self, int64_t expr, const char* field);
int64_t Parser_ex_method(Parser* self, int64_t expr, const char* method, ArrayList_Int args);
int64_t Parser_ex_index(Parser* self, int64_t expr, int64_t idx);
int64_t Parser_ex_check(Parser* self, int64_t expr);
int64_t Parser_ex_slice(Parser* self, int64_t expr, int64_t lower, int64_t upper, bool is_inclusive);
int64_t Parser_ex_range(Parser* self, int64_t start, int64_t end, bool is_inclusive);
int64_t Parser_ex_array(Parser* self, ArrayList_Int elements);
int64_t Parser_ex_tuple(Parser* self, ArrayList_Int elements);
int64_t Parser_ex_borrow(Parser* self, int64_t expr, bool is_mut);
int64_t Parser_ex_deref(Parser* self, int64_t expr);
int64_t Parser_ex_try(Parser* self, int64_t expr);
int64_t Parser_ex_catch(Parser* self, int64_t expr, const char* var_name, int64_t fallback);
int64_t Parser_ex_asm(Parser* self, const char* code, bool is_volatile, ArrayList_AsmOutput outputs, ArrayList_AsmInput inputs, ArrayList_Str clobbers);
StmtNode Parser_mk_stmt_node(Parser* self, StmtKind kind);
int64_t Parser_st_block(Parser* self, ArrayList_Int stmts);
int64_t Parser_st_error(Parser* self, const char* name, ArrayList_Str variants);
int64_t Parser_st_var_decl(Parser* self, const char* name, const char* type_ann, int64_t value, bool is_mut);
int64_t Parser_st_assign(Parser* self, int64_t target, int64_t value, const char* op);
int64_t Parser_st_func(Parser* self, const char* name, ArrayList_Param params, const char* ret_type, int64_t body, const char* cap, ArrayList_Str tp);
int64_t Parser_st_struct(Parser* self, const char* name, ArrayList_StructField fields, ArrayList_Str tp, ArrayList_Int methods, ArrayList_Int impls);
int64_t Parser_st_impl(Parser* self, const char* struct_name, const char* trait_name, ArrayList_Int methods);
int64_t Parser_st_trait(Parser* self, const char* name, ArrayList_Int methods);
int64_t Parser_st_enum(Parser* self, const char* name, ArrayList_Variant variants, ArrayList_Str tp);
int64_t Parser_st_match(Parser* self, int64_t expr, ArrayList_MatchCase cases);
int64_t Parser_st_unsafe(Parser* self, int64_t body);
int64_t Parser_st_extern(Parser* self, const char* name, ArrayList_Param params, const char* ret);
int64_t Parser_st_if(Parser* self, int64_t cond, int64_t then_b, int64_t else_b);
int64_t Parser_st_if_let(Parser* self, const char* vname, int64_t expr, int64_t then_b, int64_t else_b);
int64_t Parser_st_while(Parser* self, int64_t cond, int64_t body);
int64_t Parser_st_for(Parser* self, const char* var_name, int64_t start, int64_t end, bool inc, int64_t body);
int64_t Parser_st_return(Parser* self, int64_t value);
int64_t Parser_st_expr(Parser* self, int64_t expr);
int64_t Parser_st_defer(Parser* self, int64_t body);
int64_t Parser_st_errdefer(Parser* self, int64_t body);
int64_t Parser_st_break(Parser* self);
int64_t Parser_st_continue(Parser* self);
int64_t Parser_st_import(Parser* self, ArrayList_Str path, const char* alias);
int64_t Parser_st_cimport(Parser* self, const char* header, const char* alias);
int64_t Parser_parse_program(Parser* self);
int64_t Parser_parse_statement(Parser* self);
const char* Parser_parse_type(Parser* self);
const char* Parser_parse_base_type(Parser* self);
ArrayList_Str Parser_parse_generic_params(Parser* self);
int64_t Parser_parse_var_decl(Parser* self, bool is_mutable);
int64_t Parser_parse_func_decl(Parser* self);
int64_t Parser_parse_struct_decl(Parser* self);
int64_t Parser_parse_impl_block(Parser* self);
int64_t Parser_parse_trait_decl(Parser* self);
int64_t Parser_parse_enum_decl(Parser* self);
int64_t Parser_parse_error_decl(Parser* self);
int64_t Parser_parse_match_stmt(Parser* self);
int64_t Parser_parse_pattern(Parser* self);
int64_t Parser_add_pattern(Parser* self, PatternNode p);
int64_t Parser_parse_unsafe_block(Parser* self);
int64_t Parser_parse_extern_decl(Parser* self);
int64_t Parser_parse_if_stmt(Parser* self);
int64_t Parser_parse_while_stmt(Parser* self);
int64_t Parser_parse_for_stmt(Parser* self);
int64_t Parser_parse_return_stmt(Parser* self);
int64_t Parser_parse_break_stmt(Parser* self);
int64_t Parser_parse_continue_stmt(Parser* self);
int64_t Parser_parse_defer_stmt(Parser* self);
int64_t Parser_parse_errdefer_stmt(Parser* self);
int64_t Parser_parse_expr_or_assignment_stmt(Parser* self);
int64_t Parser_parse_block(Parser* self);
int64_t Parser_parse_import_stmt(Parser* self);
int64_t Parser_parse_import_stmt_new(Parser* self);
int64_t Parser_parse_cimport_stmt(Parser* self);
int64_t Parser_parse_expression(Parser* self, int64_t precedence);
int64_t Parser_parse_primary(Parser* self);
extern void __kai_print_int(int64_t i);
extern void __kai_print_float(double f);
void print_separator(void);
void printi(int64_t i);
void printff(double f);
void prints(const char* s);
void printc(char c);
ArrayList_DropVarEntry empty_dropvarentry_array(void);
ArrayList_Str empty_str_array(void);
ArrayList_Int empty_int_array(void);
ArrayList_FieldInit empty_fieldinit_array(void);
ArrayList_Param empty_param_array(void);
ArrayList_StructField empty_structfield_array(void);
ArrayList_Variant empty_variant_array(void);
ArrayList_MatchCase empty_matchcase_array(void);
ArrayList_StrInterpPart empty_strinterp_array(void);
ArrayList_AsmOutput empty_asmoutput_array(void);
ArrayList_AsmInput empty_asminput_array(void);
ExprNode new_expr_node(ExprKind kind, int64_t line, int64_t col);
StmtNode new_stmt_node(StmtKind kind, int64_t line, int64_t col);
PatternNode new_pattern_node(PatternKind kind);
const char* get_source_line(const char* source, int64_t line_num);
int64_t find_last(const char* path, char c);
bool mkdir_p(const char* path);
const char* str_replace(const char* s, const char* old, const char* new_val);
const char* get_base_name(const char* path);
extern bool kai_fs_exists(const char* path);
extern bool kai_fs_is_dir(const char* path);
extern bool kai_fs_mkdir(const char* path);
extern bool kai_fs_remove(const char* path);
extern void* kai_fs_opendir(const char* path);
extern char* kai_fs_readdir(void* handle);
extern void kai_fs_closedir(void* handle);
bool fs_exists(const char* path);
bool fs_is_dir(const char* path);
bool fs_mkdir(const char* path);
bool fs_remove(const char* path);
Dir fs_opendir(const char* path);
const char* fs_readdir(Dir dir);
void fs_closedir(Dir dir);
StringPool StringPool_init(KaiAllocator* allocator);
int64_t StringPool_intern(StringPool* self, const char* s);
const char* StringPool_get(StringPool* self, int64_t id);
void StringPool_deinit(StringPool* self);
TypeChecker TypeChecker_init(KaiAllocator* allocator, ArrayList_StmtNode* stmt_pool, ArrayList_ExprNode* expr_pool, ArrayList_PatternNode* pattern_pool, const char* source_file, const char* source, ImportResolver* import_resolver, StringPool* pool);
void TypeChecker_err(TypeChecker* self, const char* code, const char* msg, int64_t line, int64_t col);
void TypeChecker_enter_scope(TypeChecker* self);
ArrayList_ArrayList_SymTrackState_ ArrayList_ArrayList_SymTrackState__init(KaiAllocator* allocator);
void ArrayList_ArrayList_SymTrackState__push(ArrayList_ArrayList_SymTrackState_* self, ArrayList_SymTrackState item);
ArrayList_SymTrackState ArrayList_ArrayList_SymTrackState__get(ArrayList_ArrayList_SymTrackState_* self, int64_t index);
void ArrayList_ArrayList_SymTrackState__set(ArrayList_ArrayList_SymTrackState_* self, int64_t index, ArrayList_SymTrackState item);
ArrayList_SymTrackState ArrayList_ArrayList_SymTrackState__pop(ArrayList_ArrayList_SymTrackState_* self);
int64_t ArrayList_ArrayList_SymTrackState__length(ArrayList_ArrayList_SymTrackState_* self);
void ArrayList_ArrayList_SymTrackState__deinit(ArrayList_ArrayList_SymTrackState_* self);
void TypeChecker_exit_scope(TypeChecker* self);
void TypeChecker_define_symbol(TypeChecker* self, const char* name, const char* type_name, bool is_mutable, const char* kind, int64_t decl_stmt_idx);
bool TypeChecker_check_program(TypeChecker* self, int64_t top_stmt_idx);
void TypeChecker_detect_imports(TypeChecker* self, int64_t top_stmt_idx);
void TypeChecker_register_struct_info(TypeChecker* self, int64_t top_stmt_idx);
bool TypeChecker_has_drop_method(TypeChecker* self, const char* type_name);
void TypeChecker_collect_block_drops(TypeChecker* self, int64_t stmt_idx);
bool TypeChecker_is_integer_type(TypeChecker* self, const char* type_name);
bool TypeChecker_is_numeric_type(TypeChecker* self, const char* type_name);
bool TypeChecker_is_builtin_type(TypeChecker* self, const char* name);
bool TypeChecker_is_struct_type(TypeChecker* self, const char* name);
bool TypeChecker_is_standard_c_func(TypeChecker* self, const char* name);
bool TypeChecker_fits_in_type(TypeChecker* self, int64_t val, const char* type_name);
bool TypeChecker_is_integer_literal(TypeChecker* self, int64_t expr_idx);
int64_t TypeChecker_int_literal_value(TypeChecker* self, ExprNode expr);
bool TypeChecker_is_copy_type(TypeChecker* self, const char* type_name);
PtrRefResult TypeChecker_parse_ptr_ref(TypeChecker* self, const char* type_str);
bool TypeChecker_types_compatible(TypeChecker* self, const char* target, const char* source);
int64_t TypeChecker_find_func_decl(TypeChecker* self, const char* name);
int64_t TypeChecker_find_method_decl(TypeChecker* self, const char* struct_name, const char* meth_name);
int64_t TypeChecker_find_struct_decl(TypeChecker* self, const char* name);
int64_t TypeChecker_find_enum_decl(TypeChecker* self, const char* name);
const char* TypeChecker_get_block_yield_type(TypeChecker* self, int64_t stmt_idx);
void TypeChecker_mark_expr_moved(TypeChecker* self, int64_t expr_idx);
void TypeChecker_mark_expr_freed(TypeChecker* self, int64_t expr_idx);
ArrayList_SymTrackState TypeChecker_capture_tracking_state(TypeChecker* self);
void TypeChecker_restore_tracking_state(TypeChecker* self, ArrayList_SymTrackState state);
void TypeChecker_merge_and_apply_tracking_state(TypeChecker* self, ArrayList_ArrayList_SymTrackState_ states);
const char* TypeChecker_get_expr_type(TypeChecker* self, int64_t expr_idx);
bool TypeChecker_expr_is_mutable(TypeChecker* self, int64_t expr_idx);
bool TypeChecker_is_enum_or_error_type(TypeChecker* self, const char* name);
bool TypeChecker_is_imported_name(TypeChecker* self, const char* name);
void TypeChecker_mark_import_used(TypeChecker* self, const char* name);
void TypeChecker_check_identifier(TypeChecker* self, int64_t expr_idx);
void TypeChecker_check_field_access(TypeChecker* self, int64_t expr_idx);
void TypeChecker_check_method_call(TypeChecker* self, int64_t expr_idx);
void TypeChecker_check_return_stmt(TypeChecker* self, int64_t stmt_idx);
void TypeChecker_check_stmt(TypeChecker* self, int64_t stmt_idx);
void TypeChecker_check_expr(TypeChecker* self, int64_t expr_idx);
void TypeChecker_check_expr_inner(TypeChecker* self, int64_t expr_idx);
int64_t TypeChecker_map_type_to_id(TypeChecker* self, const char* type_name);
int64_t TypeChecker_get_expr_type_id(TypeChecker* self, int64_t expr_idx);
SymbolTable SymbolTable_init(KaiAllocator* allocator, int64_t parent_idx);
void SymbolTable_define(SymbolTable* self, const char* name, const char* type_name, bool is_mutable, const char* kind, const char* llvm_value, int64_t decl_stmt_idx);
int64_t SymbolTable_lookup(SymbolTable* self, const char* name, ArrayList_SymbolTable* tables);
Symbol SymbolTable_lookup_symbol(SymbolTable* self, const char* name, ArrayList_SymbolTable* tables);
void SymbolTable_mark_moved(SymbolTable* self, const char* name, ArrayList_SymbolTable* tables);
void SymbolTable_mark_freed(SymbolTable* self, const char* name, ArrayList_SymbolTable* tables);
void SymbolTable_clear_moved(SymbolTable* self, const char* name, ArrayList_SymbolTable* tables);
void SymbolTable_clear_freed(SymbolTable* self, const char* name, ArrayList_SymbolTable* tables);
int64_t SymbolTable_lookup_current(SymbolTable* self, const char* name);
extern int64_t get_exe_dir(char* buf, int64_t max_len);
ImportResolver ImportResolver_init(KaiAllocator* allocator, StringPool* pool);
void ImportResolver_err_at(ImportResolver* self, const char* msg, int64_t stmt_idx);
void ImportResolver_err(ImportResolver* self, const char* msg);
void ImportResolver_record_cimport(ImportResolver* self, const char* header);
void ImportResolver_resolve_import(ImportResolver* self, int64_t stmt_idx, ArrayList_StmtNode* stmt_pool, ArrayList_ExprNode* expr_pool, ArrayList_PatternNode* pattern_pool);
void ImportResolver_resolve_all(ImportResolver* self, int64_t program_idx, ArrayList_StmtNode* stmt_pool, ArrayList_ExprNode* expr_pool, ArrayList_PatternNode* pattern_pool);
TypeArena TypeArena_init(KaiAllocator* allocator);
Type TypeArena_get_type(TypeArena* self, int64_t id);
int64_t TypeArena_intern_pointer(TypeArena* self, int64_t element_type_id);
int64_t TypeArena_intern_struct(TypeArena* self, const char* name, int64_t decl_stmt_idx);
int64_t TypeArena_intern_enum(TypeArena* self, const char* name, int64_t decl_stmt_idx);
void TypeArena_deinit(TypeArena* self);
extern int64_t get_exe_dir(char* buf, int64_t max_len);
extern char* strstr(const char* haystack, const char* needle);
extern const char* concatAlloc(const char* left, const char* right);
int64_t type_map_find(ArrayList_StrMapEntry* arr, const char* key);
const char* type_map_get(ArrayList_StrMapEntry* arr, const char* key);
void type_map_put(ArrayList_StrMapEntry* arr, const char* key, const char* value);
int64_t strlist_find(ArrayList_Str* arr, const char* key);
const char* Codegen_add_init_return(Codegen* self, const char* body_str, const char* struct_name);
Codegen Codegen_init(KaiAllocator* allocator, ArrayList_StmtNode* stmt_pool, ArrayList_ExprNode* expr_pool, ArrayList_PatternNode* pattern_pool, ImportResolver* import_resolver, StringPool* pool);
bool Codegen_is_pointer_type(Codegen* self, const char* t);
const char* Codegen_strip_module_prefix(Codegen* self, const char* name);
const char* Codegen_map_type(Codegen* self, const char* type_name);
const char* Codegen_substitute_generic_type(Codegen* self, const char* type_name);
const char* Codegen_trim_spaces(Codegen* self, const char* s);
const char* Codegen_clean_type_for_mangling(Codegen* self, const char* s);
int64_t Codegen_str_to_int(Codegen* self, const char* s);
ArrayList_Str Codegen_infer_type_args(Codegen* self, int64_t func_stmt_idx, int64_t expr_idx);
void Codegen_setup_current_type_map(Codegen* self, ArrayList_Str* type_params, ArrayList_Str* type_args);
void Codegen_monomorphize_struct(Codegen* self, int64_t stmt_idx, const char* concrete_name, ArrayList_Str* type_args);
void Codegen_monomorphize_enum(Codegen* self, int64_t stmt_idx, const char* concrete_name, ArrayList_Str* type_args);
void Codegen_monomorphize_methods(Codegen* self, const char* base_struct_name, const char* concrete_struct_name);
void Codegen_monomorphize_func(Codegen* self, int64_t func_stmt_idx, const char* mangled_name, ArrayList_Str* type_args);
const char* Codegen_extract_first_type_arg(Codegen* self, const char* type_name);
void Codegen_build_func_types(Codegen* self);
const char* Codegen_get_expr_type(Codegen* self, int64_t expr_idx);
const char* Codegen_gen_expr_with_expected_type(Codegen* self, int64_t expr_idx, const char* expected_type);
const char* Codegen_gen_expr(Codegen* self, int64_t expr_idx);
bool Codegen_str_contains(Codegen* self, const char* s, char target);
int64_t Codegen_str_find(Codegen* self, const char* s, char target);
bool Codegen_is_standard_c_func(Codegen* self, const char* name);
const char* Codegen_gen_stmt(Codegen* self, int64_t stmt_idx);
const char* Codegen_clean_enum_name(Codegen* self, const char* type_name);
bool Codegen_is_enum_type(Codegen* self, const char* type_name);
bool Codegen_enum_has_payload(Codegen* self, const char* enum_name);
const char* Codegen_escape_string(Codegen* self, const char* s);
ArrayList_Str Codegen__collect_loop_drops(Codegen* self);
void Codegen_emit_struct_body_with_deps(Codegen* self, int64_t stmt_idx, ArrayList_Str* emitted);
const char* Codegen_generate(Codegen* self, int64_t top_stmt_idx);
extern char* strstr(const char* haystack, const char* needle);
StrBuf StrBuf_init(KaiAllocator* a);
void StrBuf_append(StrBuf* self, const char* s);
const char* StrBuf_to_str(StrBuf* self);
int64_t cgb_map_find(ArrayList_CgbMapEntry* arr, const char* key);
const char* cgb_map_get(ArrayList_CgbMapEntry* arr, const char* key);
void cgb_map_put(ArrayList_CgbMapEntry* arr, const char* key, const char* value);
int64_t cgb_strlist_find(ArrayList_Str* arr, const char* key);
const char* CodegenBuilder_add_init_return(CodegenBuilder* self, const char* body_str, const char* struct_name);
CodegenBuilder CodegenBuilder_init(KaiAllocator* allocator, ArrayList_StmtNode* stmt_pool, ArrayList_ExprNode* expr_pool, ArrayList_PatternNode* pattern_pool, ImportResolver* import_resolver, StringPool* pool);
bool CodegenBuilder_is_pointer_type(CodegenBuilder* self, const char* t);
bool CodegenBuilder_is_numeric_type(CodegenBuilder* self, const char* t);
bool CodegenBuilder_is_integer_type(CodegenBuilder* self, const char* t);
bool CodegenBuilder_is_copy_type(CodegenBuilder* self, const char* type_name);
const char* CodegenBuilder_get_expr_type(CodegenBuilder* self, int64_t expr_idx);
const char* CodegenBuilder_escape_string(CodegenBuilder* self, const char* s);
int64_t CodegenBuilder_str_to_int(CodegenBuilder* self, const char* s);
const char* CodegenBuilder_cgb_clean_type_for_mangling(CodegenBuilder* self, const char* s);
void CodegenBuilder_monomorphize_struct(CodegenBuilder* self, const char* struct_name, const char* concrete_name, ArrayList_Str* type_args);
void CodegenBuilder_monomorphize_methods_for_struct(CodegenBuilder* self, const char* base_struct_name, const char* concrete_name, ArrayList_Str* param_names, ArrayList_Str* type_args);
void CodegenBuilder_monomorphize_enum(CodegenBuilder* self, const char* enum_name, const char* concrete_name, ArrayList_Str* type_args);
int64_t CodegenBuilder_str_to_int_safe(CodegenBuilder* self, const char* s);
const char* CodegenBuilder_substitute_type_params(CodegenBuilder* self, const char* type_name, ArrayList_Str* param_names, ArrayList_Str* arg_types);
const char* CodegenBuilder_extract_first_type_arg(CodegenBuilder* self, const char* type_name);
const char* CodegenBuilder_strip_module_prefix(CodegenBuilder* self, const char* name);
const char* CodegenBuilder_map_type(CodegenBuilder* self, const char* resolved_type);
bool CodegenBuilder_str_contains(CodegenBuilder* self, const char* s, char target);
int64_t CodegenBuilder_str_find(CodegenBuilder* self, const char* s, char target);
bool CodegenBuilder_is_fully_parenthesized(CodegenBuilder* self, const char* s);
const char* CodegenBuilder_format_cond(CodegenBuilder* self, const char* cond);
const char* CodegenBuilder_cgb_replace_format_specifiers(CodegenBuilder* self, const char* s);
bool CodegenBuilder_is_standard_c_func(CodegenBuilder* self, const char* name);
int64_t CodegenBuilder_push_expr(CodegenBuilder* self, CExprNode node);
const char* CodegenBuilder_gen_expr_str(CodegenBuilder* self, int64_t expr_idx);
const char* CodegenBuilder_expr_to_str(CodegenBuilder* self, int64_t c_idx);
const char* CodegenBuilder_gen_expr_with_expected_type(CodegenBuilder* self, int64_t expr_idx, const char* expected_type);
int64_t CodegenBuilder_gen_expr(CodegenBuilder* self, int64_t expr_idx);
void CodegenBuilder_gen_stmt(CodegenBuilder* self, int64_t stmt_idx);
void CodegenBuilder_gen_else_chain(CodegenBuilder* self, int64_t else_idx);
void CodegenBuilder_build_func_types(CodegenBuilder* self);
void CodegenBuilder_emit_struct_body_with_deps(CodegenBuilder* self, int64_t stmt_idx, ArrayList_Str* emitted);
const char* CodegenBuilder_generate(CodegenBuilder* self, int64_t top_stmt_idx);
extern const char* concatAlloc(const char* left, const char* right);
CCodeBuilder CCodeBuilder_init(KaiAllocator* allocator);
void CCodeBuilder_clear(CCodeBuilder* self);
void CCodeBuilder_emit_line(CCodeBuilder* self, const char* code);
void CCodeBuilder_emit_blank(CCodeBuilder* self);
void CCodeBuilder_emit_raw(CCodeBuilder* self, const char* code);
void CCodeBuilder_append_to_last_line(CCodeBuilder* self, const char* suffix);
void CCodeBuilder_emit_include(CCodeBuilder* self, const char* header, bool is_system);
void CCodeBuilder_emit_directive(CCodeBuilder* self, const char* code);
void CCodeBuilder_indent(CCodeBuilder* self);
void CCodeBuilder_dedent(CCodeBuilder* self);
void CCodeBuilder_begin_block(CCodeBuilder* self);
void CCodeBuilder_end_block(CCodeBuilder* self);
const char* CCodeBuilder_to_str(CCodeBuilder* self);
int64_t CCodeBuilder_line_count(CCodeBuilder* self);
const char* cb_escape_string(const char* s);
const char* cb_escape_asm(const char* s);
const char* cgb_char_to_str(char c);
const char* cgb_int_to_str(int64_t n);
CType ctype_new(const char* base, int64_t pointer, bool is_const, bool is_unsigned);
CType ctype_void(void);
CType ctype_int(void);
CType ctype_bool(void);
CType ctype_char(void);
CType ctype_float(void);
CType ctype_str(void);
CType ctype_ptr(CType inner);
CType ctype_const(CType inner);
const char* ctype_to_str(CType t);
CType ctype_from_kai(const char* kai_type);
CType ctype_copy(CType t);
CUnit cunit_new(ArrayList_Str includes, ArrayList_CDeclNode decls);
CExprNode cexpr_new_int(const char* val);
CExprNode cexpr_new_ident(const char* name);
CExprNode cexpr_new_binary(int64_t left, const char* op, int64_t right);
CExprNode cexpr_new_call(const char* callee, ArrayList_Int args);
CStmtNode cstmt_new_expr(int64_t expr_idx);
CStmtNode cstmt_new_block(ArrayList_Int stmts);
CStmtNode cstmt_new_if(int64_t cond, int64_t then_branch, int64_t else_branch);
CExprNode cexpr_new_float(const char* val);
CExprNode cexpr_new_str(const char* val);
CExprNode cexpr_new_bool(bool val);
CExprNode cexpr_new_char(const char* val);
CExprNode cexpr_new_unary(const char* op, int64_t operand, bool is_prefix);
CExprNode cexpr_new_compound(CType t, ArrayList_Str compound_fs);
CExprNode cexpr_new_field(int64_t base, const char* name);
CExprNode cexpr_new_arrow(int64_t base, const char* name);
CExprNode cexpr_new_index(int64_t base, int64_t idx_val);
CExprNode cexpr_new_cast(CType t, int64_t cast_e);
CExprNode cexpr_new_sizeof_type(CType t);
CDeclNode cdecl_new_func(const char* name, const char* ret_type, ArrayList_Str params, bool is_extern, bool is_vararg);
CPrinter CPrinter_init(CCodeBuilder* builder, ArrayList_CExprNode* expr_pool, ArrayList_CStmtNode* stmt_pool);
const char* CPrinter_print_expr(CPrinter* self, int64_t idx);
void CPrinter_print_stmt(CPrinter* self, int64_t idx);
void CPrinter_print_decl(CPrinter* self, CDeclNode decl);
void CPrinter_emit_runtime_preamble(CPrinter* self, ArrayList_Str* cimport_headers);
extern int64_t kai_fflush(void* stream);
LLVMCodegen LLVMCodegen_init(KaiAllocator* allocator, ArrayList_StmtNode* stmt_pool, ArrayList_ExprNode* expr_pool, ArrayList_PatternNode* pattern_pool, ImportResolver* import_resolver, StringPool* pool);
void LLVMCodegen_build_func_types(LLVMCodegen* self);
void LLVMCodegen_build_type_caches(LLVMCodegen* self);
const char* LLVMCodegen_get_generic_mangled_name(LLVMCodegen* self, const char* name);
const char* LLVMCodegen_get_func_return_type(LLVMCodegen* self, const char* name);
int64_t LLVMCodegen_get_func_param_count(LLVMCodegen* self, const char* name);
const char* LLVMCodegen_get_func_param_types(LLVMCodegen* self, const char* name);
void* LLVMCodegen_get_cached_func_type(LLVMCodegen* self, const char* name);
void* LLVMCodegen_c_abi_type(LLVMCodegen* self, const char* tname);
void* LLVMCodegen_build_llvm_func_type_from_params(LLVMCodegen* self, void* ret, const char* param_types_str, bool is_vararg, bool is_extern);
int64_t LLVMCodegen_get_func_param_count_by_types_str(LLVMCodegen* self, const char* param_types_str);
bool LLVMCodegen_is_extern_func(LLVMCodegen* self, const char* name);
void* LLVMCodegen_lookup_or_create_func(LLVMCodegen* self, const char* name);
void LLVMCodegen_foreach_method(LLVMCodegen* self, int64_t stmt_idx, bool decl_only);
void LLVMCodegen_emit_runtime_helpers(LLVMCodegen* self);
bool LLVMCodegen_generate(LLVMCodegen* self, int64_t top_stmt_idx, const char* obj_path);
void LLVMCodegen_emit_func_decl(LLVMCodegen* self, int64_t stmt_idx, const char* name);
void LLVMCodegen_emit_func_body(LLVMCodegen* self, int64_t stmt_idx, void* fn_val, const char* struct_name);
void* LLVMCodegen_coerce_return_value(LLVMCodegen* self, void* val, const char* ret_type_str, const char* actual_type_str);
const char* LLVMCodegen_strip_module_prefix(LLVMCodegen* self, const char* name);
void* LLVMCodegen_map_type(LLVMCodegen* self, const char* type_name);
void* LLVMCodegen_map_tuple_type(LLVMCodegen* self, const char* tuple_type_str);
void* LLVMCodegen_unwrap_str_for_c(LLVMCodegen* self, void* val);
void* LLVMCodegen_to_bool(LLVMCodegen* self, void* val);
void LLVMCodegen_ensure_reachable(LLVMCodegen* self);
void LLVMCodegen_gen_stmt(LLVMCodegen* self, int64_t stmt_idx);
void* LLVMCodegen_find_alloca_by_idx(LLVMCodegen* self, int64_t decl_idx, const char* name);
void* LLVMCodegen_find_alloca_type_by_idx(LLVMCodegen* self, int64_t decl_idx, const char* name);
void* LLVMCodegen_find_alloca(LLVMCodegen* self, const char* name);
void* LLVMCodegen_find_alloca_type(LLVMCodegen* self, const char* name);
const char* LLVMCodegen_get_expr_type(LLVMCodegen* self, int64_t expr_idx);
void* LLVMCodegen_gen_expr(LLVMCodegen* self, int64_t expr_idx);
int64_t LLVMCodegen_str_to_int(LLVMCodegen* self, const char* s);
double LLVMCodegen_str_to_float(LLVMCodegen* self, const char* s);
const char* LLVMCodegen_get_param_type_at_index(LLVMCodegen* self, const char* param_types_str, int64_t idx);
void* LLVMCodegen_prepare_arg(LLVMCodegen* self, void* arg_val, const char* param_type_str, bool callee_is_extern);
void* LLVMCodegen_gen_cast(LLVMCodegen* self, void* val, void* dest_type);
bool LLVMCodegen_is_struct_type(LLVMCodegen* self, const char* name);
bool LLVMCodegen_is_enum_type(LLVMCodegen* self, const char* name);
const char* LLVMCodegen_clean_type_for_mangling(LLVMCodegen* self, const char* s);
int64_t LLVMCodegen_str_find(LLVMCodegen* self, const char* s, char c);
bool LLVMCodegen_str_contains(LLVMCodegen* self, const char* s, char c);
const char* LLVMCodegen_substitute_generic_type_in_ftype(LLVMCodegen* self, const char* ftype, const char* clean_type, StmtNode stmt);
bool LLVMCodegen_emit_object(LLVMCodegen* self, const char* obj_path);
const char* LLVMCodegen_trim_spaces(LLVMCodegen* self, const char* s);
const char* LLVMCodegen_substitute_generic_type(LLVMCodegen* self, const char* name);
int64_t LLVMCodegen_find_struct_decl(LLVMCodegen* self, const char* clean_name);
int64_t LLVMCodegen_find_enum_decl(LLVMCodegen* self, const char* clean_name);
ArrayList_LLVMStrMapEntry LLVMCodegen_setup_type_map_from_mangled_name(LLVMCodegen* self, const char* base_name, const char* mangled_name, ArrayList_Str* param_names);
void LLVMCodegen_setup_current_type_map(LLVMCodegen* self, ArrayList_Str* param_names, ArrayList_Str* type_args);
void LLVMCodegen_monomorphize_struct(LLVMCodegen* self, int64_t stmt_idx, const char* concrete_name, ArrayList_Str* type_args);
void LLVMCodegen_monomorphize_enum(LLVMCodegen* self, int64_t stmt_idx, const char* concrete_name, ArrayList_Str* type_args);
const char* LLVMCodegen_substitute_type_params(LLVMCodegen* self, const char* type_name, ArrayList_Str* param_names, ArrayList_Str* arg_types);
bool LLVMCodegen_is_monomorphized_name(LLVMCodegen* self, const char* name);
void LLVMCodegen_monomorphize_methods_for_struct(LLVMCodegen* self, const char* base_struct_name, const char* concrete_name, ArrayList_Str* param_names, ArrayList_Str* type_args);
void LLVMCodegen_emit_func_body_mono(LLVMCodegen* self, int64_t stmt_idx, void* fn_val, const char* struct_name, ArrayList_Str* param_names, ArrayList_Str* type_args);
int64_t llvm_type_map_find(ArrayList_LLVMStrMapEntry* arr, const char* key);
const char* llvm_type_map_get(ArrayList_LLVMStrMapEntry* arr, const char* key);
void llvm_type_map_put(ArrayList_LLVMStrMapEntry* arr, const char* key, const char* value);
int64_t llvm_strlist_find(ArrayList_Str* arr, const char* key);
extern int64_t kai_fflush(void* stream);
const char* diag_fix_safety(const char* code);
const char* diag_repair_id(const char* code);
const char* diag_repair_summary(const char* code);
bool diagnostic_can_apply_edits(const char* code);
void print_json_string(const char* s);
void print_diag_json(const char* code, const char* message, const char* path, int64_t line, int64_t column, int64_t len_val, const char* expected, const char* actual, const char* help);
void print_fix_json(const char* code, bool applies);
void print_plan(const char* path, bool json_mode, ArrayList_Str* codes, ArrayList_Str* messages, ArrayList_Int* dlines, ArrayList_Int* dcolumns, ArrayList_Int* dlengths, ArrayList_Str* expected, ArrayList_Str* actual, ArrayList_Str* helpv);
void print_patch(const char* path, bool json_mode, bool apply, bool applied, ArrayList_Str* codes, ArrayList_Str* messages, ArrayList_Int* dlines, ArrayList_Int* dcolumns, ArrayList_Int* dlengths, ArrayList_Str* expected, ArrayList_Str* actual, ArrayList_Str* helpv, ArrayList_Int* patch_lines, ArrayList_Str* patch_old, ArrayList_Str* patch_new, ArrayList_Str* patch_codes);
int64_t run_fix(const char* fix_mode, const char* fix_file, bool json);
ErrorInfo get_error_info(const char* code);
bool __kai_std_ascii_is_digit(char byte);
bool __kai_std_ascii_is_lower(char byte);
bool __kai_std_ascii_is_upper(char byte);
bool __kai_std_ascii_is_alpha(char byte);
bool __kai_std_ascii_is_alnum(char byte);
bool __kai_std_ascii_is_whitespace(char byte);
bool __kai_std_ascii_is_hex_digit(char byte);
char __kai_std_ascii_to_lower(char byte);
char __kai_std_ascii_to_upper(char byte);
Optional_Char __kai_std_ascii_digit_value(char byte);
Optional_Char __kai_std_ascii_hex_value(char byte);
int64_t diag_clamp_offset(const char* bytes, int64_t offset);
int64_t diag_line_start(const char* bytes, int64_t offset);
int64_t diag_line_end(const char* bytes, int64_t offset);
int64_t diag_line(const char* bytes, int64_t offset);
int64_t diag_column(const char* bytes, int64_t offset);
const char* diag_line_text(const char* bytes, int64_t offset);
int64_t diag_range_len(const char* bytes, int64_t start, int64_t end);
const char* diag_range_text(const char* bytes, int64_t start, int64_t end);
Optional_Int diag_write_span(char* buffer, int64_t offset, const char* bytes);
Optional_Int diag_write_usize(char* buffer, int64_t offset, int64_t value);
const char* diag_format_location(char* buffer, const char* path, int64_t line, int64_t column);
const char* diag_format_offset_location(char* buffer, const char* path, const char* bytes, int64_t offset);
int64_t run_patch(int64_t argc, char** argv);
int64_t run_graph(int64_t argc, char** argv);
int64_t run_init(int64_t argc, char** argv);
extern int64_t get_exe_dir(char* buf, int64_t max_len);
int64_t run_skills(int64_t argc, char** argv);
int64_t run_explain(int64_t argc, char** argv);
int64_t run_build(int64_t argc, char** argv);

ArrayList_Token ArrayList_Token_init(KaiAllocator* allocator) {
    ArrayList_Token self = (ArrayList_Token){0};
    self.len = 0LL;
    self.cap = 4LL;
    self.allocator = allocator;
    {
    self.data = (Token*)(KaiAllocator_alloc(allocator, (self.cap * (int64_t)(sizeof(Token))), 1LL));
}
    return self;
}
void ArrayList_Token_push(ArrayList_Token* self, Token item) {
    if (self->len == self->cap) {
    int64_t new_cap = (self->cap * 2LL);
    {
    Token* new_data = (Token*)(KaiAllocator_alloc(self->allocator, (new_cap * (int64_t)(sizeof(Token))), 1LL));
    int64_t i = 0LL;
    while (i < self->len) {
    (new_data)[i] = (self->data)[i];
    i = (i + 1LL);
}
    KaiAllocator_free(self->allocator, (uint8_t*)(self->data));
    self->data = new_data;
    self->cap = new_cap;
}
}
    (self->data)[self->len] = item;
    self->len = (self->len + 1LL);
}
Token ArrayList_Token_get(ArrayList_Token* self, int64_t index) {
    if ((index < 0LL) || (index >= self->len)) {
    {
    exit(1LL);
}
}
    return (self->data)[index];
}
void ArrayList_Token_set(ArrayList_Token* self, int64_t index, Token item) {
    if ((index < 0LL) || (index >= self->len)) {
    {
    exit(1LL);
}
}
    (self->data)[index] = item;
}
Token ArrayList_Token_pop(ArrayList_Token* self) {
    if (self->len == 0LL) {
    {
    exit(1LL);
}
}
    self->len = (self->len - 1LL);
    return (self->data)[self->len];
}
int64_t ArrayList_Token_length(ArrayList_Token* self) {
    return self->len;
}
void ArrayList_Token_deinit(ArrayList_Token* self) {
    {
    KaiAllocator_free(self->allocator, (uint8_t*)(self->data));
}
}
ArrayList_Int ArrayList_Int_init(KaiAllocator* allocator) {
    ArrayList_Int self = (ArrayList_Int){0};
    self.len = 0LL;
    self.cap = 4LL;
    self.allocator = allocator;
    {
    self.data = (int64_t*)(KaiAllocator_alloc(allocator, (self.cap * (int64_t)(sizeof(int64_t))), 1LL));
}
    return self;
}
void ArrayList_Int_push(ArrayList_Int* self, int64_t item) {
    if (self->len == self->cap) {
    int64_t new_cap = (self->cap * 2LL);
    {
    int64_t* new_data = (int64_t*)(KaiAllocator_alloc(self->allocator, (new_cap * (int64_t)(sizeof(int64_t))), 1LL));
    int64_t i = 0LL;
    while (i < self->len) {
    (new_data)[i] = (self->data)[i];
    i = (i + 1LL);
}
    KaiAllocator_free(self->allocator, (uint8_t*)(self->data));
    self->data = new_data;
    self->cap = new_cap;
}
}
    (self->data)[self->len] = item;
    self->len = (self->len + 1LL);
}
int64_t ArrayList_Int_get(ArrayList_Int* self, int64_t index) {
    if ((index < 0LL) || (index >= self->len)) {
    {
    exit(1LL);
}
}
    return (self->data)[index];
}
void ArrayList_Int_set(ArrayList_Int* self, int64_t index, int64_t item) {
    if ((index < 0LL) || (index >= self->len)) {
    {
    exit(1LL);
}
}
    (self->data)[index] = item;
}
int64_t ArrayList_Int_pop(ArrayList_Int* self) {
    if (self->len == 0LL) {
    {
    exit(1LL);
}
}
    self->len = (self->len - 1LL);
    return (self->data)[self->len];
}
int64_t ArrayList_Int_length(ArrayList_Int* self) {
    return self->len;
}
void ArrayList_Int_deinit(ArrayList_Int* self) {
    {
    KaiAllocator_free(self->allocator, (uint8_t*)(self->data));
}
}
ArrayList_ExprNode ArrayList_ExprNode_init(KaiAllocator* allocator) {
    ArrayList_ExprNode self = (ArrayList_ExprNode){0};
    self.len = 0LL;
    self.cap = 4LL;
    self.allocator = allocator;
    {
    self.data = (ExprNode*)(KaiAllocator_alloc(allocator, (self.cap * (int64_t)(sizeof(ExprNode))), 1LL));
}
    return self;
}
void ArrayList_ExprNode_push(ArrayList_ExprNode* self, ExprNode item) {
    if (self->len == self->cap) {
    int64_t new_cap = (self->cap * 2LL);
    {
    ExprNode* new_data = (ExprNode*)(KaiAllocator_alloc(self->allocator, (new_cap * (int64_t)(sizeof(ExprNode))), 1LL));
    int64_t i = 0LL;
    while (i < self->len) {
    (new_data)[i] = (self->data)[i];
    i = (i + 1LL);
}
    KaiAllocator_free(self->allocator, (uint8_t*)(self->data));
    self->data = new_data;
    self->cap = new_cap;
}
}
    (self->data)[self->len] = item;
    self->len = (self->len + 1LL);
}
ExprNode ArrayList_ExprNode_get(ArrayList_ExprNode* self, int64_t index) {
    if ((index < 0LL) || (index >= self->len)) {
    {
    exit(1LL);
}
}
    return (self->data)[index];
}
void ArrayList_ExprNode_set(ArrayList_ExprNode* self, int64_t index, ExprNode item) {
    if ((index < 0LL) || (index >= self->len)) {
    {
    exit(1LL);
}
}
    (self->data)[index] = item;
}
ExprNode ArrayList_ExprNode_pop(ArrayList_ExprNode* self) {
    if (self->len == 0LL) {
    {
    exit(1LL);
}
}
    self->len = (self->len - 1LL);
    return (self->data)[self->len];
}
int64_t ArrayList_ExprNode_length(ArrayList_ExprNode* self) {
    return self->len;
}
void ArrayList_ExprNode_deinit(ArrayList_ExprNode* self) {
    {
    KaiAllocator_free(self->allocator, (uint8_t*)(self->data));
}
}
ArrayList_StmtNode ArrayList_StmtNode_init(KaiAllocator* allocator) {
    ArrayList_StmtNode self = (ArrayList_StmtNode){0};
    self.len = 0LL;
    self.cap = 4LL;
    self.allocator = allocator;
    {
    self.data = (StmtNode*)(KaiAllocator_alloc(allocator, (self.cap * (int64_t)(sizeof(StmtNode))), 1LL));
}
    return self;
}
void ArrayList_StmtNode_push(ArrayList_StmtNode* self, StmtNode item) {
    if (self->len == self->cap) {
    int64_t new_cap = (self->cap * 2LL);
    {
    StmtNode* new_data = (StmtNode*)(KaiAllocator_alloc(self->allocator, (new_cap * (int64_t)(sizeof(StmtNode))), 1LL));
    int64_t i = 0LL;
    while (i < self->len) {
    (new_data)[i] = (self->data)[i];
    i = (i + 1LL);
}
    KaiAllocator_free(self->allocator, (uint8_t*)(self->data));
    self->data = new_data;
    self->cap = new_cap;
}
}
    (self->data)[self->len] = item;
    self->len = (self->len + 1LL);
}
StmtNode ArrayList_StmtNode_get(ArrayList_StmtNode* self, int64_t index) {
    if ((index < 0LL) || (index >= self->len)) {
    {
    exit(1LL);
}
}
    return (self->data)[index];
}
void ArrayList_StmtNode_set(ArrayList_StmtNode* self, int64_t index, StmtNode item) {
    if ((index < 0LL) || (index >= self->len)) {
    {
    exit(1LL);
}
}
    (self->data)[index] = item;
}
StmtNode ArrayList_StmtNode_pop(ArrayList_StmtNode* self) {
    if (self->len == 0LL) {
    {
    exit(1LL);
}
}
    self->len = (self->len - 1LL);
    return (self->data)[self->len];
}
int64_t ArrayList_StmtNode_length(ArrayList_StmtNode* self) {
    return self->len;
}
void ArrayList_StmtNode_deinit(ArrayList_StmtNode* self) {
    {
    KaiAllocator_free(self->allocator, (uint8_t*)(self->data));
}
}
ArrayList_PatternNode ArrayList_PatternNode_init(KaiAllocator* allocator) {
    ArrayList_PatternNode self = (ArrayList_PatternNode){0};
    self.len = 0LL;
    self.cap = 4LL;
    self.allocator = allocator;
    {
    self.data = (PatternNode*)(KaiAllocator_alloc(allocator, (self.cap * (int64_t)(sizeof(PatternNode))), 1LL));
}
    return self;
}
void ArrayList_PatternNode_push(ArrayList_PatternNode* self, PatternNode item) {
    if (self->len == self->cap) {
    int64_t new_cap = (self->cap * 2LL);
    {
    PatternNode* new_data = (PatternNode*)(KaiAllocator_alloc(self->allocator, (new_cap * (int64_t)(sizeof(PatternNode))), 1LL));
    int64_t i = 0LL;
    while (i < self->len) {
    (new_data)[i] = (self->data)[i];
    i = (i + 1LL);
}
    KaiAllocator_free(self->allocator, (uint8_t*)(self->data));
    self->data = new_data;
    self->cap = new_cap;
}
}
    (self->data)[self->len] = item;
    self->len = (self->len + 1LL);
}
PatternNode ArrayList_PatternNode_get(ArrayList_PatternNode* self, int64_t index) {
    if ((index < 0LL) || (index >= self->len)) {
    {
    exit(1LL);
}
}
    return (self->data)[index];
}
void ArrayList_PatternNode_set(ArrayList_PatternNode* self, int64_t index, PatternNode item) {
    if ((index < 0LL) || (index >= self->len)) {
    {
    exit(1LL);
}
}
    (self->data)[index] = item;
}
PatternNode ArrayList_PatternNode_pop(ArrayList_PatternNode* self) {
    if (self->len == 0LL) {
    {
    exit(1LL);
}
}
    self->len = (self->len - 1LL);
    return (self->data)[self->len];
}
int64_t ArrayList_PatternNode_length(ArrayList_PatternNode* self) {
    return self->len;
}
void ArrayList_PatternNode_deinit(ArrayList_PatternNode* self) {
    {
    KaiAllocator_free(self->allocator, (uint8_t*)(self->data));
}
}
ArrayList_Param ArrayList_Param_init(KaiAllocator* allocator) {
    ArrayList_Param self = (ArrayList_Param){0};
    self.len = 0LL;
    self.cap = 4LL;
    self.allocator = allocator;
    {
    self.data = (Param*)(KaiAllocator_alloc(allocator, (self.cap * (int64_t)(sizeof(Param))), 1LL));
}
    return self;
}
void ArrayList_Param_push(ArrayList_Param* self, Param item) {
    if (self->len == self->cap) {
    int64_t new_cap = (self->cap * 2LL);
    {
    Param* new_data = (Param*)(KaiAllocator_alloc(self->allocator, (new_cap * (int64_t)(sizeof(Param))), 1LL));
    int64_t i = 0LL;
    while (i < self->len) {
    (new_data)[i] = (self->data)[i];
    i = (i + 1LL);
}
    KaiAllocator_free(self->allocator, (uint8_t*)(self->data));
    self->data = new_data;
    self->cap = new_cap;
}
}
    (self->data)[self->len] = item;
    self->len = (self->len + 1LL);
}
Param ArrayList_Param_get(ArrayList_Param* self, int64_t index) {
    if ((index < 0LL) || (index >= self->len)) {
    {
    exit(1LL);
}
}
    return (self->data)[index];
}
void ArrayList_Param_set(ArrayList_Param* self, int64_t index, Param item) {
    if ((index < 0LL) || (index >= self->len)) {
    {
    exit(1LL);
}
}
    (self->data)[index] = item;
}
Param ArrayList_Param_pop(ArrayList_Param* self) {
    if (self->len == 0LL) {
    {
    exit(1LL);
}
}
    self->len = (self->len - 1LL);
    return (self->data)[self->len];
}
int64_t ArrayList_Param_length(ArrayList_Param* self) {
    return self->len;
}
void ArrayList_Param_deinit(ArrayList_Param* self) {
    {
    KaiAllocator_free(self->allocator, (uint8_t*)(self->data));
}
}
ArrayList_Str ArrayList_Str_init(KaiAllocator* allocator) {
    ArrayList_Str self = (ArrayList_Str){0};
    self.len = 0LL;
    self.cap = 4LL;
    self.allocator = allocator;
    {
    self.data = (const char**)(KaiAllocator_alloc(allocator, (self.cap * (int64_t)(sizeof(const char*))), 1LL));
}
    return self;
}
void ArrayList_Str_push(ArrayList_Str* self, const char* item) {
    if (self->len == self->cap) {
    int64_t new_cap = (self->cap * 2LL);
    {
    const char** new_data = (const char**)(KaiAllocator_alloc(self->allocator, (new_cap * (int64_t)(sizeof(const char*))), 1LL));
    int64_t i = 0LL;
    while (i < self->len) {
    (new_data)[i] = (self->data)[i];
    i = (i + 1LL);
}
    KaiAllocator_free(self->allocator, (uint8_t*)(self->data));
    self->data = new_data;
    self->cap = new_cap;
}
}
    (self->data)[self->len] = item;
    self->len = (self->len + 1LL);
}
const char* ArrayList_Str_get(ArrayList_Str* self, int64_t index) {
    if ((index < 0LL) || (index >= self->len)) {
    {
    exit(1LL);
}
}
    return (self->data)[index];
}
void ArrayList_Str_set(ArrayList_Str* self, int64_t index, const char* item) {
    if ((index < 0LL) || (index >= self->len)) {
    {
    exit(1LL);
}
}
    (self->data)[index] = item;
}
const char* ArrayList_Str_pop(ArrayList_Str* self) {
    if (self->len == 0LL) {
    {
    exit(1LL);
}
}
    self->len = (self->len - 1LL);
    return (self->data)[self->len];
}
int64_t ArrayList_Str_length(ArrayList_Str* self) {
    return self->len;
}
void ArrayList_Str_deinit(ArrayList_Str* self) {
    {
    KaiAllocator_free(self->allocator, (uint8_t*)(self->data));
}
}
ArrayList_StrInterpPart ArrayList_StrInterpPart_init(KaiAllocator* allocator) {
    ArrayList_StrInterpPart self = (ArrayList_StrInterpPart){0};
    self.len = 0LL;
    self.cap = 4LL;
    self.allocator = allocator;
    {
    self.data = (StrInterpPart*)(KaiAllocator_alloc(allocator, (self.cap * (int64_t)(sizeof(StrInterpPart))), 1LL));
}
    return self;
}
void ArrayList_StrInterpPart_push(ArrayList_StrInterpPart* self, StrInterpPart item) {
    if (self->len == self->cap) {
    int64_t new_cap = (self->cap * 2LL);
    {
    StrInterpPart* new_data = (StrInterpPart*)(KaiAllocator_alloc(self->allocator, (new_cap * (int64_t)(sizeof(StrInterpPart))), 1LL));
    int64_t i = 0LL;
    while (i < self->len) {
    (new_data)[i] = (self->data)[i];
    i = (i + 1LL);
}
    KaiAllocator_free(self->allocator, (uint8_t*)(self->data));
    self->data = new_data;
    self->cap = new_cap;
}
}
    (self->data)[self->len] = item;
    self->len = (self->len + 1LL);
}
StrInterpPart ArrayList_StrInterpPart_get(ArrayList_StrInterpPart* self, int64_t index) {
    if ((index < 0LL) || (index >= self->len)) {
    {
    exit(1LL);
}
}
    return (self->data)[index];
}
void ArrayList_StrInterpPart_set(ArrayList_StrInterpPart* self, int64_t index, StrInterpPart item) {
    if ((index < 0LL) || (index >= self->len)) {
    {
    exit(1LL);
}
}
    (self->data)[index] = item;
}
StrInterpPart ArrayList_StrInterpPart_pop(ArrayList_StrInterpPart* self) {
    if (self->len == 0LL) {
    {
    exit(1LL);
}
}
    self->len = (self->len - 1LL);
    return (self->data)[self->len];
}
int64_t ArrayList_StrInterpPart_length(ArrayList_StrInterpPart* self) {
    return self->len;
}
void ArrayList_StrInterpPart_deinit(ArrayList_StrInterpPart* self) {
    {
    KaiAllocator_free(self->allocator, (uint8_t*)(self->data));
}
}
ArrayList_FieldInit ArrayList_FieldInit_init(KaiAllocator* allocator) {
    ArrayList_FieldInit self = (ArrayList_FieldInit){0};
    self.len = 0LL;
    self.cap = 4LL;
    self.allocator = allocator;
    {
    self.data = (FieldInit*)(KaiAllocator_alloc(allocator, (self.cap * (int64_t)(sizeof(FieldInit))), 1LL));
}
    return self;
}
void ArrayList_FieldInit_push(ArrayList_FieldInit* self, FieldInit item) {
    if (self->len == self->cap) {
    int64_t new_cap = (self->cap * 2LL);
    {
    FieldInit* new_data = (FieldInit*)(KaiAllocator_alloc(self->allocator, (new_cap * (int64_t)(sizeof(FieldInit))), 1LL));
    int64_t i = 0LL;
    while (i < self->len) {
    (new_data)[i] = (self->data)[i];
    i = (i + 1LL);
}
    KaiAllocator_free(self->allocator, (uint8_t*)(self->data));
    self->data = new_data;
    self->cap = new_cap;
}
}
    (self->data)[self->len] = item;
    self->len = (self->len + 1LL);
}
FieldInit ArrayList_FieldInit_get(ArrayList_FieldInit* self, int64_t index) {
    if ((index < 0LL) || (index >= self->len)) {
    {
    exit(1LL);
}
}
    return (self->data)[index];
}
void ArrayList_FieldInit_set(ArrayList_FieldInit* self, int64_t index, FieldInit item) {
    if ((index < 0LL) || (index >= self->len)) {
    {
    exit(1LL);
}
}
    (self->data)[index] = item;
}
FieldInit ArrayList_FieldInit_pop(ArrayList_FieldInit* self) {
    if (self->len == 0LL) {
    {
    exit(1LL);
}
}
    self->len = (self->len - 1LL);
    return (self->data)[self->len];
}
int64_t ArrayList_FieldInit_length(ArrayList_FieldInit* self) {
    return self->len;
}
void ArrayList_FieldInit_deinit(ArrayList_FieldInit* self) {
    {
    KaiAllocator_free(self->allocator, (uint8_t*)(self->data));
}
}
ArrayList_AsmOutput ArrayList_AsmOutput_init(KaiAllocator* allocator) {
    ArrayList_AsmOutput self = (ArrayList_AsmOutput){0};
    self.len = 0LL;
    self.cap = 4LL;
    self.allocator = allocator;
    {
    self.data = (AsmOutput*)(KaiAllocator_alloc(allocator, (self.cap * (int64_t)(sizeof(AsmOutput))), 1LL));
}
    return self;
}
void ArrayList_AsmOutput_push(ArrayList_AsmOutput* self, AsmOutput item) {
    if (self->len == self->cap) {
    int64_t new_cap = (self->cap * 2LL);
    {
    AsmOutput* new_data = (AsmOutput*)(KaiAllocator_alloc(self->allocator, (new_cap * (int64_t)(sizeof(AsmOutput))), 1LL));
    int64_t i = 0LL;
    while (i < self->len) {
    (new_data)[i] = (self->data)[i];
    i = (i + 1LL);
}
    KaiAllocator_free(self->allocator, (uint8_t*)(self->data));
    self->data = new_data;
    self->cap = new_cap;
}
}
    (self->data)[self->len] = item;
    self->len = (self->len + 1LL);
}
AsmOutput ArrayList_AsmOutput_get(ArrayList_AsmOutput* self, int64_t index) {
    if ((index < 0LL) || (index >= self->len)) {
    {
    exit(1LL);
}
}
    return (self->data)[index];
}
void ArrayList_AsmOutput_set(ArrayList_AsmOutput* self, int64_t index, AsmOutput item) {
    if ((index < 0LL) || (index >= self->len)) {
    {
    exit(1LL);
}
}
    (self->data)[index] = item;
}
AsmOutput ArrayList_AsmOutput_pop(ArrayList_AsmOutput* self) {
    if (self->len == 0LL) {
    {
    exit(1LL);
}
}
    self->len = (self->len - 1LL);
    return (self->data)[self->len];
}
int64_t ArrayList_AsmOutput_length(ArrayList_AsmOutput* self) {
    return self->len;
}
void ArrayList_AsmOutput_deinit(ArrayList_AsmOutput* self) {
    {
    KaiAllocator_free(self->allocator, (uint8_t*)(self->data));
}
}
ArrayList_AsmInput ArrayList_AsmInput_init(KaiAllocator* allocator) {
    ArrayList_AsmInput self = (ArrayList_AsmInput){0};
    self.len = 0LL;
    self.cap = 4LL;
    self.allocator = allocator;
    {
    self.data = (AsmInput*)(KaiAllocator_alloc(allocator, (self.cap * (int64_t)(sizeof(AsmInput))), 1LL));
}
    return self;
}
void ArrayList_AsmInput_push(ArrayList_AsmInput* self, AsmInput item) {
    if (self->len == self->cap) {
    int64_t new_cap = (self->cap * 2LL);
    {
    AsmInput* new_data = (AsmInput*)(KaiAllocator_alloc(self->allocator, (new_cap * (int64_t)(sizeof(AsmInput))), 1LL));
    int64_t i = 0LL;
    while (i < self->len) {
    (new_data)[i] = (self->data)[i];
    i = (i + 1LL);
}
    KaiAllocator_free(self->allocator, (uint8_t*)(self->data));
    self->data = new_data;
    self->cap = new_cap;
}
}
    (self->data)[self->len] = item;
    self->len = (self->len + 1LL);
}
AsmInput ArrayList_AsmInput_get(ArrayList_AsmInput* self, int64_t index) {
    if ((index < 0LL) || (index >= self->len)) {
    {
    exit(1LL);
}
}
    return (self->data)[index];
}
void ArrayList_AsmInput_set(ArrayList_AsmInput* self, int64_t index, AsmInput item) {
    if ((index < 0LL) || (index >= self->len)) {
    {
    exit(1LL);
}
}
    (self->data)[index] = item;
}
AsmInput ArrayList_AsmInput_pop(ArrayList_AsmInput* self) {
    if (self->len == 0LL) {
    {
    exit(1LL);
}
}
    self->len = (self->len - 1LL);
    return (self->data)[self->len];
}
int64_t ArrayList_AsmInput_length(ArrayList_AsmInput* self) {
    return self->len;
}
void ArrayList_AsmInput_deinit(ArrayList_AsmInput* self) {
    {
    KaiAllocator_free(self->allocator, (uint8_t*)(self->data));
}
}
ArrayList_StructField ArrayList_StructField_init(KaiAllocator* allocator) {
    ArrayList_StructField self = (ArrayList_StructField){0};
    self.len = 0LL;
    self.cap = 4LL;
    self.allocator = allocator;
    {
    self.data = (StructField*)(KaiAllocator_alloc(allocator, (self.cap * (int64_t)(sizeof(StructField))), 1LL));
}
    return self;
}
void ArrayList_StructField_push(ArrayList_StructField* self, StructField item) {
    if (self->len == self->cap) {
    int64_t new_cap = (self->cap * 2LL);
    {
    StructField* new_data = (StructField*)(KaiAllocator_alloc(self->allocator, (new_cap * (int64_t)(sizeof(StructField))), 1LL));
    int64_t i = 0LL;
    while (i < self->len) {
    (new_data)[i] = (self->data)[i];
    i = (i + 1LL);
}
    KaiAllocator_free(self->allocator, (uint8_t*)(self->data));
    self->data = new_data;
    self->cap = new_cap;
}
}
    (self->data)[self->len] = item;
    self->len = (self->len + 1LL);
}
StructField ArrayList_StructField_get(ArrayList_StructField* self, int64_t index) {
    if ((index < 0LL) || (index >= self->len)) {
    {
    exit(1LL);
}
}
    return (self->data)[index];
}
void ArrayList_StructField_set(ArrayList_StructField* self, int64_t index, StructField item) {
    if ((index < 0LL) || (index >= self->len)) {
    {
    exit(1LL);
}
}
    (self->data)[index] = item;
}
StructField ArrayList_StructField_pop(ArrayList_StructField* self) {
    if (self->len == 0LL) {
    {
    exit(1LL);
}
}
    self->len = (self->len - 1LL);
    return (self->data)[self->len];
}
int64_t ArrayList_StructField_length(ArrayList_StructField* self) {
    return self->len;
}
void ArrayList_StructField_deinit(ArrayList_StructField* self) {
    {
    KaiAllocator_free(self->allocator, (uint8_t*)(self->data));
}
}
ArrayList_Variant ArrayList_Variant_init(KaiAllocator* allocator) {
    ArrayList_Variant self = (ArrayList_Variant){0};
    self.len = 0LL;
    self.cap = 4LL;
    self.allocator = allocator;
    {
    self.data = (Variant*)(KaiAllocator_alloc(allocator, (self.cap * (int64_t)(sizeof(Variant))), 1LL));
}
    return self;
}
void ArrayList_Variant_push(ArrayList_Variant* self, Variant item) {
    if (self->len == self->cap) {
    int64_t new_cap = (self->cap * 2LL);
    {
    Variant* new_data = (Variant*)(KaiAllocator_alloc(self->allocator, (new_cap * (int64_t)(sizeof(Variant))), 1LL));
    int64_t i = 0LL;
    while (i < self->len) {
    (new_data)[i] = (self->data)[i];
    i = (i + 1LL);
}
    KaiAllocator_free(self->allocator, (uint8_t*)(self->data));
    self->data = new_data;
    self->cap = new_cap;
}
}
    (self->data)[self->len] = item;
    self->len = (self->len + 1LL);
}
Variant ArrayList_Variant_get(ArrayList_Variant* self, int64_t index) {
    if ((index < 0LL) || (index >= self->len)) {
    {
    exit(1LL);
}
}
    return (self->data)[index];
}
void ArrayList_Variant_set(ArrayList_Variant* self, int64_t index, Variant item) {
    if ((index < 0LL) || (index >= self->len)) {
    {
    exit(1LL);
}
}
    (self->data)[index] = item;
}
Variant ArrayList_Variant_pop(ArrayList_Variant* self) {
    if (self->len == 0LL) {
    {
    exit(1LL);
}
}
    self->len = (self->len - 1LL);
    return (self->data)[self->len];
}
int64_t ArrayList_Variant_length(ArrayList_Variant* self) {
    return self->len;
}
void ArrayList_Variant_deinit(ArrayList_Variant* self) {
    {
    KaiAllocator_free(self->allocator, (uint8_t*)(self->data));
}
}
ArrayList_DropVarEntry ArrayList_DropVarEntry_init(KaiAllocator* allocator) {
    ArrayList_DropVarEntry self = (ArrayList_DropVarEntry){0};
    self.len = 0LL;
    self.cap = 4LL;
    self.allocator = allocator;
    {
    self.data = (DropVarEntry*)(KaiAllocator_alloc(allocator, (self.cap * (int64_t)(sizeof(DropVarEntry))), 1LL));
}
    return self;
}
void ArrayList_DropVarEntry_push(ArrayList_DropVarEntry* self, DropVarEntry item) {
    if (self->len == self->cap) {
    int64_t new_cap = (self->cap * 2LL);
    {
    DropVarEntry* new_data = (DropVarEntry*)(KaiAllocator_alloc(self->allocator, (new_cap * (int64_t)(sizeof(DropVarEntry))), 1LL));
    int64_t i = 0LL;
    while (i < self->len) {
    (new_data)[i] = (self->data)[i];
    i = (i + 1LL);
}
    KaiAllocator_free(self->allocator, (uint8_t*)(self->data));
    self->data = new_data;
    self->cap = new_cap;
}
}
    (self->data)[self->len] = item;
    self->len = (self->len + 1LL);
}
DropVarEntry ArrayList_DropVarEntry_get(ArrayList_DropVarEntry* self, int64_t index) {
    if ((index < 0LL) || (index >= self->len)) {
    {
    exit(1LL);
}
}
    return (self->data)[index];
}
void ArrayList_DropVarEntry_set(ArrayList_DropVarEntry* self, int64_t index, DropVarEntry item) {
    if ((index < 0LL) || (index >= self->len)) {
    {
    exit(1LL);
}
}
    (self->data)[index] = item;
}
DropVarEntry ArrayList_DropVarEntry_pop(ArrayList_DropVarEntry* self) {
    if (self->len == 0LL) {
    {
    exit(1LL);
}
}
    self->len = (self->len - 1LL);
    return (self->data)[self->len];
}
int64_t ArrayList_DropVarEntry_length(ArrayList_DropVarEntry* self) {
    return self->len;
}
void ArrayList_DropVarEntry_deinit(ArrayList_DropVarEntry* self) {
    {
    KaiAllocator_free(self->allocator, (uint8_t*)(self->data));
}
}
ArrayList_MatchCase ArrayList_MatchCase_init(KaiAllocator* allocator) {
    ArrayList_MatchCase self = (ArrayList_MatchCase){0};
    self.len = 0LL;
    self.cap = 4LL;
    self.allocator = allocator;
    {
    self.data = (MatchCase*)(KaiAllocator_alloc(allocator, (self.cap * (int64_t)(sizeof(MatchCase))), 1LL));
}
    return self;
}
void ArrayList_MatchCase_push(ArrayList_MatchCase* self, MatchCase item) {
    if (self->len == self->cap) {
    int64_t new_cap = (self->cap * 2LL);
    {
    MatchCase* new_data = (MatchCase*)(KaiAllocator_alloc(self->allocator, (new_cap * (int64_t)(sizeof(MatchCase))), 1LL));
    int64_t i = 0LL;
    while (i < self->len) {
    (new_data)[i] = (self->data)[i];
    i = (i + 1LL);
}
    KaiAllocator_free(self->allocator, (uint8_t*)(self->data));
    self->data = new_data;
    self->cap = new_cap;
}
}
    (self->data)[self->len] = item;
    self->len = (self->len + 1LL);
}
MatchCase ArrayList_MatchCase_get(ArrayList_MatchCase* self, int64_t index) {
    if ((index < 0LL) || (index >= self->len)) {
    {
    exit(1LL);
}
}
    return (self->data)[index];
}
void ArrayList_MatchCase_set(ArrayList_MatchCase* self, int64_t index, MatchCase item) {
    if ((index < 0LL) || (index >= self->len)) {
    {
    exit(1LL);
}
}
    (self->data)[index] = item;
}
MatchCase ArrayList_MatchCase_pop(ArrayList_MatchCase* self) {
    if (self->len == 0LL) {
    {
    exit(1LL);
}
}
    self->len = (self->len - 1LL);
    return (self->data)[self->len];
}
int64_t ArrayList_MatchCase_length(ArrayList_MatchCase* self) {
    return self->len;
}
void ArrayList_MatchCase_deinit(ArrayList_MatchCase* self) {
    {
    KaiAllocator_free(self->allocator, (uint8_t*)(self->data));
}
}
ArrayList_Type ArrayList_Type_init(KaiAllocator* allocator) {
    ArrayList_Type self = (ArrayList_Type){0};
    self.len = 0LL;
    self.cap = 4LL;
    self.allocator = allocator;
    {
    self.data = (Type*)(KaiAllocator_alloc(allocator, (self.cap * (int64_t)(sizeof(Type))), 1LL));
}
    return self;
}
void ArrayList_Type_push(ArrayList_Type* self, Type item) {
    if (self->len == self->cap) {
    int64_t new_cap = (self->cap * 2LL);
    {
    Type* new_data = (Type*)(KaiAllocator_alloc(self->allocator, (new_cap * (int64_t)(sizeof(Type))), 1LL));
    int64_t i = 0LL;
    while (i < self->len) {
    (new_data)[i] = (self->data)[i];
    i = (i + 1LL);
}
    KaiAllocator_free(self->allocator, (uint8_t*)(self->data));
    self->data = new_data;
    self->cap = new_cap;
}
}
    (self->data)[self->len] = item;
    self->len = (self->len + 1LL);
}
Type ArrayList_Type_get(ArrayList_Type* self, int64_t index) {
    if ((index < 0LL) || (index >= self->len)) {
    {
    exit(1LL);
}
}
    return (self->data)[index];
}
void ArrayList_Type_set(ArrayList_Type* self, int64_t index, Type item) {
    if ((index < 0LL) || (index >= self->len)) {
    {
    exit(1LL);
}
}
    (self->data)[index] = item;
}
Type ArrayList_Type_pop(ArrayList_Type* self) {
    if (self->len == 0LL) {
    {
    exit(1LL);
}
}
    self->len = (self->len - 1LL);
    return (self->data)[self->len];
}
int64_t ArrayList_Type_length(ArrayList_Type* self) {
    return self->len;
}
void ArrayList_Type_deinit(ArrayList_Type* self) {
    {
    KaiAllocator_free(self->allocator, (uint8_t*)(self->data));
}
}
ArrayList_SymbolTable ArrayList_SymbolTable_init(KaiAllocator* allocator) {
    ArrayList_SymbolTable self = (ArrayList_SymbolTable){0};
    self.len = 0LL;
    self.cap = 4LL;
    self.allocator = allocator;
    {
    self.data = (SymbolTable*)(KaiAllocator_alloc(allocator, (self.cap * (int64_t)(sizeof(SymbolTable))), 1LL));
}
    return self;
}
void ArrayList_SymbolTable_push(ArrayList_SymbolTable* self, SymbolTable item) {
    if (self->len == self->cap) {
    int64_t new_cap = (self->cap * 2LL);
    {
    SymbolTable* new_data = (SymbolTable*)(KaiAllocator_alloc(self->allocator, (new_cap * (int64_t)(sizeof(SymbolTable))), 1LL));
    int64_t i = 0LL;
    while (i < self->len) {
    (new_data)[i] = (self->data)[i];
    i = (i + 1LL);
}
    KaiAllocator_free(self->allocator, (uint8_t*)(self->data));
    self->data = new_data;
    self->cap = new_cap;
}
}
    (self->data)[self->len] = item;
    self->len = (self->len + 1LL);
}
SymbolTable ArrayList_SymbolTable_get(ArrayList_SymbolTable* self, int64_t index) {
    if ((index < 0LL) || (index >= self->len)) {
    {
    exit(1LL);
}
}
    return (self->data)[index];
}
void ArrayList_SymbolTable_set(ArrayList_SymbolTable* self, int64_t index, SymbolTable item) {
    if ((index < 0LL) || (index >= self->len)) {
    {
    exit(1LL);
}
}
    (self->data)[index] = item;
}
SymbolTable ArrayList_SymbolTable_pop(ArrayList_SymbolTable* self) {
    if (self->len == 0LL) {
    {
    exit(1LL);
}
}
    self->len = (self->len - 1LL);
    return (self->data)[self->len];
}
int64_t ArrayList_SymbolTable_length(ArrayList_SymbolTable* self) {
    return self->len;
}
void ArrayList_SymbolTable_deinit(ArrayList_SymbolTable* self) {
    {
    KaiAllocator_free(self->allocator, (uint8_t*)(self->data));
}
}
ArrayList_StructInfo ArrayList_StructInfo_init(KaiAllocator* allocator) {
    ArrayList_StructInfo self = (ArrayList_StructInfo){0};
    self.len = 0LL;
    self.cap = 4LL;
    self.allocator = allocator;
    {
    self.data = (StructInfo*)(KaiAllocator_alloc(allocator, (self.cap * (int64_t)(sizeof(StructInfo))), 1LL));
}
    return self;
}
void ArrayList_StructInfo_push(ArrayList_StructInfo* self, StructInfo item) {
    if (self->len == self->cap) {
    int64_t new_cap = (self->cap * 2LL);
    {
    StructInfo* new_data = (StructInfo*)(KaiAllocator_alloc(self->allocator, (new_cap * (int64_t)(sizeof(StructInfo))), 1LL));
    int64_t i = 0LL;
    while (i < self->len) {
    (new_data)[i] = (self->data)[i];
    i = (i + 1LL);
}
    KaiAllocator_free(self->allocator, (uint8_t*)(self->data));
    self->data = new_data;
    self->cap = new_cap;
}
}
    (self->data)[self->len] = item;
    self->len = (self->len + 1LL);
}
StructInfo ArrayList_StructInfo_get(ArrayList_StructInfo* self, int64_t index) {
    if ((index < 0LL) || (index >= self->len)) {
    {
    exit(1LL);
}
}
    return (self->data)[index];
}
void ArrayList_StructInfo_set(ArrayList_StructInfo* self, int64_t index, StructInfo item) {
    if ((index < 0LL) || (index >= self->len)) {
    {
    exit(1LL);
}
}
    (self->data)[index] = item;
}
StructInfo ArrayList_StructInfo_pop(ArrayList_StructInfo* self) {
    if (self->len == 0LL) {
    {
    exit(1LL);
}
}
    self->len = (self->len - 1LL);
    return (self->data)[self->len];
}
int64_t ArrayList_StructInfo_length(ArrayList_StructInfo* self) {
    return self->len;
}
void ArrayList_StructInfo_deinit(ArrayList_StructInfo* self) {
    {
    KaiAllocator_free(self->allocator, (uint8_t*)(self->data));
}
}
ArrayList_Bool ArrayList_Bool_init(KaiAllocator* allocator) {
    ArrayList_Bool self = (ArrayList_Bool){0};
    self.len = 0LL;
    self.cap = 4LL;
    self.allocator = allocator;
    {
    self.data = (bool*)(KaiAllocator_alloc(allocator, (self.cap * (int64_t)(sizeof(bool))), 1LL));
}
    return self;
}
void ArrayList_Bool_push(ArrayList_Bool* self, bool item) {
    if (self->len == self->cap) {
    int64_t new_cap = (self->cap * 2LL);
    {
    bool* new_data = (bool*)(KaiAllocator_alloc(self->allocator, (new_cap * (int64_t)(sizeof(bool))), 1LL));
    int64_t i = 0LL;
    while (i < self->len) {
    (new_data)[i] = (self->data)[i];
    i = (i + 1LL);
}
    KaiAllocator_free(self->allocator, (uint8_t*)(self->data));
    self->data = new_data;
    self->cap = new_cap;
}
}
    (self->data)[self->len] = item;
    self->len = (self->len + 1LL);
}
bool ArrayList_Bool_get(ArrayList_Bool* self, int64_t index) {
    if ((index < 0LL) || (index >= self->len)) {
    {
    exit(1LL);
}
}
    return (self->data)[index];
}
void ArrayList_Bool_set(ArrayList_Bool* self, int64_t index, bool item) {
    if ((index < 0LL) || (index >= self->len)) {
    {
    exit(1LL);
}
}
    (self->data)[index] = item;
}
bool ArrayList_Bool_pop(ArrayList_Bool* self) {
    if (self->len == 0LL) {
    {
    exit(1LL);
}
}
    self->len = (self->len - 1LL);
    return (self->data)[self->len];
}
int64_t ArrayList_Bool_length(ArrayList_Bool* self) {
    return self->len;
}
void ArrayList_Bool_deinit(ArrayList_Bool* self) {
    {
    KaiAllocator_free(self->allocator, (uint8_t*)(self->data));
}
}
ArrayList_SymTrackState ArrayList_SymTrackState_init(KaiAllocator* allocator) {
    ArrayList_SymTrackState self = (ArrayList_SymTrackState){0};
    self.len = 0LL;
    self.cap = 4LL;
    self.allocator = allocator;
    {
    self.data = (SymTrackState*)(KaiAllocator_alloc(allocator, (self.cap * (int64_t)(sizeof(SymTrackState))), 1LL));
}
    return self;
}
void ArrayList_SymTrackState_push(ArrayList_SymTrackState* self, SymTrackState item) {
    if (self->len == self->cap) {
    int64_t new_cap = (self->cap * 2LL);
    {
    SymTrackState* new_data = (SymTrackState*)(KaiAllocator_alloc(self->allocator, (new_cap * (int64_t)(sizeof(SymTrackState))), 1LL));
    int64_t i = 0LL;
    while (i < self->len) {
    (new_data)[i] = (self->data)[i];
    i = (i + 1LL);
}
    KaiAllocator_free(self->allocator, (uint8_t*)(self->data));
    self->data = new_data;
    self->cap = new_cap;
}
}
    (self->data)[self->len] = item;
    self->len = (self->len + 1LL);
}
SymTrackState ArrayList_SymTrackState_get(ArrayList_SymTrackState* self, int64_t index) {
    if ((index < 0LL) || (index >= self->len)) {
    {
    exit(1LL);
}
}
    return (self->data)[index];
}
void ArrayList_SymTrackState_set(ArrayList_SymTrackState* self, int64_t index, SymTrackState item) {
    if ((index < 0LL) || (index >= self->len)) {
    {
    exit(1LL);
}
}
    (self->data)[index] = item;
}
SymTrackState ArrayList_SymTrackState_pop(ArrayList_SymTrackState* self) {
    if (self->len == 0LL) {
    {
    exit(1LL);
}
}
    self->len = (self->len - 1LL);
    return (self->data)[self->len];
}
int64_t ArrayList_SymTrackState_length(ArrayList_SymTrackState* self) {
    return self->len;
}
void ArrayList_SymTrackState_deinit(ArrayList_SymTrackState* self) {
    {
    KaiAllocator_free(self->allocator, (uint8_t*)(self->data));
}
}
ArrayList_FuncEffect ArrayList_FuncEffect_init(KaiAllocator* allocator) {
    ArrayList_FuncEffect self = (ArrayList_FuncEffect){0};
    self.len = 0LL;
    self.cap = 4LL;
    self.allocator = allocator;
    {
    self.data = (FuncEffect*)(KaiAllocator_alloc(allocator, (self.cap * (int64_t)(sizeof(FuncEffect))), 1LL));
}
    return self;
}
void ArrayList_FuncEffect_push(ArrayList_FuncEffect* self, FuncEffect item) {
    if (self->len == self->cap) {
    int64_t new_cap = (self->cap * 2LL);
    {
    FuncEffect* new_data = (FuncEffect*)(KaiAllocator_alloc(self->allocator, (new_cap * (int64_t)(sizeof(FuncEffect))), 1LL));
    int64_t i = 0LL;
    while (i < self->len) {
    (new_data)[i] = (self->data)[i];
    i = (i + 1LL);
}
    KaiAllocator_free(self->allocator, (uint8_t*)(self->data));
    self->data = new_data;
    self->cap = new_cap;
}
}
    (self->data)[self->len] = item;
    self->len = (self->len + 1LL);
}
FuncEffect ArrayList_FuncEffect_get(ArrayList_FuncEffect* self, int64_t index) {
    if ((index < 0LL) || (index >= self->len)) {
    {
    exit(1LL);
}
}
    return (self->data)[index];
}
void ArrayList_FuncEffect_set(ArrayList_FuncEffect* self, int64_t index, FuncEffect item) {
    if ((index < 0LL) || (index >= self->len)) {
    {
    exit(1LL);
}
}
    (self->data)[index] = item;
}
FuncEffect ArrayList_FuncEffect_pop(ArrayList_FuncEffect* self) {
    if (self->len == 0LL) {
    {
    exit(1LL);
}
}
    self->len = (self->len - 1LL);
    return (self->data)[self->len];
}
int64_t ArrayList_FuncEffect_length(ArrayList_FuncEffect* self) {
    return self->len;
}
void ArrayList_FuncEffect_deinit(ArrayList_FuncEffect* self) {
    {
    KaiAllocator_free(self->allocator, (uint8_t*)(self->data));
}
}
ArrayList_Symbol ArrayList_Symbol_init(KaiAllocator* allocator) {
    ArrayList_Symbol self = (ArrayList_Symbol){0};
    self.len = 0LL;
    self.cap = 4LL;
    self.allocator = allocator;
    {
    self.data = (Symbol*)(KaiAllocator_alloc(allocator, (self.cap * (int64_t)(sizeof(Symbol))), 1LL));
}
    return self;
}
void ArrayList_Symbol_push(ArrayList_Symbol* self, Symbol item) {
    if (self->len == self->cap) {
    int64_t new_cap = (self->cap * 2LL);
    {
    Symbol* new_data = (Symbol*)(KaiAllocator_alloc(self->allocator, (new_cap * (int64_t)(sizeof(Symbol))), 1LL));
    int64_t i = 0LL;
    while (i < self->len) {
    (new_data)[i] = (self->data)[i];
    i = (i + 1LL);
}
    KaiAllocator_free(self->allocator, (uint8_t*)(self->data));
    self->data = new_data;
    self->cap = new_cap;
}
}
    (self->data)[self->len] = item;
    self->len = (self->len + 1LL);
}
Symbol ArrayList_Symbol_get(ArrayList_Symbol* self, int64_t index) {
    if ((index < 0LL) || (index >= self->len)) {
    {
    exit(1LL);
}
}
    return (self->data)[index];
}
void ArrayList_Symbol_set(ArrayList_Symbol* self, int64_t index, Symbol item) {
    if ((index < 0LL) || (index >= self->len)) {
    {
    exit(1LL);
}
}
    (self->data)[index] = item;
}
Symbol ArrayList_Symbol_pop(ArrayList_Symbol* self) {
    if (self->len == 0LL) {
    {
    exit(1LL);
}
}
    self->len = (self->len - 1LL);
    return (self->data)[self->len];
}
int64_t ArrayList_Symbol_length(ArrayList_Symbol* self) {
    return self->len;
}
void ArrayList_Symbol_deinit(ArrayList_Symbol* self) {
    {
    KaiAllocator_free(self->allocator, (uint8_t*)(self->data));
}
}
ArrayList_StrMapEntry ArrayList_StrMapEntry_init(KaiAllocator* allocator) {
    ArrayList_StrMapEntry self = (ArrayList_StrMapEntry){0};
    self.len = 0LL;
    self.cap = 4LL;
    self.allocator = allocator;
    {
    self.data = (StrMapEntry*)(KaiAllocator_alloc(allocator, (self.cap * (int64_t)(sizeof(StrMapEntry))), 1LL));
}
    return self;
}
void ArrayList_StrMapEntry_push(ArrayList_StrMapEntry* self, StrMapEntry item) {
    if (self->len == self->cap) {
    int64_t new_cap = (self->cap * 2LL);
    {
    StrMapEntry* new_data = (StrMapEntry*)(KaiAllocator_alloc(self->allocator, (new_cap * (int64_t)(sizeof(StrMapEntry))), 1LL));
    int64_t i = 0LL;
    while (i < self->len) {
    (new_data)[i] = (self->data)[i];
    i = (i + 1LL);
}
    KaiAllocator_free(self->allocator, (uint8_t*)(self->data));
    self->data = new_data;
    self->cap = new_cap;
}
}
    (self->data)[self->len] = item;
    self->len = (self->len + 1LL);
}
StrMapEntry ArrayList_StrMapEntry_get(ArrayList_StrMapEntry* self, int64_t index) {
    if ((index < 0LL) || (index >= self->len)) {
    {
    exit(1LL);
}
}
    return (self->data)[index];
}
void ArrayList_StrMapEntry_set(ArrayList_StrMapEntry* self, int64_t index, StrMapEntry item) {
    if ((index < 0LL) || (index >= self->len)) {
    {
    exit(1LL);
}
}
    (self->data)[index] = item;
}
StrMapEntry ArrayList_StrMapEntry_pop(ArrayList_StrMapEntry* self) {
    if (self->len == 0LL) {
    {
    exit(1LL);
}
}
    self->len = (self->len - 1LL);
    return (self->data)[self->len];
}
int64_t ArrayList_StrMapEntry_length(ArrayList_StrMapEntry* self) {
    return self->len;
}
void ArrayList_StrMapEntry_deinit(ArrayList_StrMapEntry* self) {
    {
    KaiAllocator_free(self->allocator, (uint8_t*)(self->data));
}
}
ArrayList_CgbMapEntry ArrayList_CgbMapEntry_init(KaiAllocator* allocator) {
    ArrayList_CgbMapEntry self = (ArrayList_CgbMapEntry){0};
    self.len = 0LL;
    self.cap = 4LL;
    self.allocator = allocator;
    {
    self.data = (CgbMapEntry*)(KaiAllocator_alloc(allocator, (self.cap * (int64_t)(sizeof(CgbMapEntry))), 1LL));
}
    return self;
}
void ArrayList_CgbMapEntry_push(ArrayList_CgbMapEntry* self, CgbMapEntry item) {
    if (self->len == self->cap) {
    int64_t new_cap = (self->cap * 2LL);
    {
    CgbMapEntry* new_data = (CgbMapEntry*)(KaiAllocator_alloc(self->allocator, (new_cap * (int64_t)(sizeof(CgbMapEntry))), 1LL));
    int64_t i = 0LL;
    while (i < self->len) {
    (new_data)[i] = (self->data)[i];
    i = (i + 1LL);
}
    KaiAllocator_free(self->allocator, (uint8_t*)(self->data));
    self->data = new_data;
    self->cap = new_cap;
}
}
    (self->data)[self->len] = item;
    self->len = (self->len + 1LL);
}
CgbMapEntry ArrayList_CgbMapEntry_get(ArrayList_CgbMapEntry* self, int64_t index) {
    if ((index < 0LL) || (index >= self->len)) {
    {
    exit(1LL);
}
}
    return (self->data)[index];
}
void ArrayList_CgbMapEntry_set(ArrayList_CgbMapEntry* self, int64_t index, CgbMapEntry item) {
    if ((index < 0LL) || (index >= self->len)) {
    {
    exit(1LL);
}
}
    (self->data)[index] = item;
}
CgbMapEntry ArrayList_CgbMapEntry_pop(ArrayList_CgbMapEntry* self) {
    if (self->len == 0LL) {
    {
    exit(1LL);
}
}
    self->len = (self->len - 1LL);
    return (self->data)[self->len];
}
int64_t ArrayList_CgbMapEntry_length(ArrayList_CgbMapEntry* self) {
    return self->len;
}
void ArrayList_CgbMapEntry_deinit(ArrayList_CgbMapEntry* self) {
    {
    KaiAllocator_free(self->allocator, (uint8_t*)(self->data));
}
}
ArrayList_CExprNode ArrayList_CExprNode_init(KaiAllocator* allocator) {
    ArrayList_CExprNode self = (ArrayList_CExprNode){0};
    self.len = 0LL;
    self.cap = 4LL;
    self.allocator = allocator;
    {
    self.data = (CExprNode*)(KaiAllocator_alloc(allocator, (self.cap * (int64_t)(sizeof(CExprNode))), 1LL));
}
    return self;
}
void ArrayList_CExprNode_push(ArrayList_CExprNode* self, CExprNode item) {
    if (self->len == self->cap) {
    int64_t new_cap = (self->cap * 2LL);
    {
    CExprNode* new_data = (CExprNode*)(KaiAllocator_alloc(self->allocator, (new_cap * (int64_t)(sizeof(CExprNode))), 1LL));
    int64_t i = 0LL;
    while (i < self->len) {
    (new_data)[i] = (self->data)[i];
    i = (i + 1LL);
}
    KaiAllocator_free(self->allocator, (uint8_t*)(self->data));
    self->data = new_data;
    self->cap = new_cap;
}
}
    (self->data)[self->len] = item;
    self->len = (self->len + 1LL);
}
CExprNode ArrayList_CExprNode_get(ArrayList_CExprNode* self, int64_t index) {
    if ((index < 0LL) || (index >= self->len)) {
    {
    exit(1LL);
}
}
    return (self->data)[index];
}
void ArrayList_CExprNode_set(ArrayList_CExprNode* self, int64_t index, CExprNode item) {
    if ((index < 0LL) || (index >= self->len)) {
    {
    exit(1LL);
}
}
    (self->data)[index] = item;
}
CExprNode ArrayList_CExprNode_pop(ArrayList_CExprNode* self) {
    if (self->len == 0LL) {
    {
    exit(1LL);
}
}
    self->len = (self->len - 1LL);
    return (self->data)[self->len];
}
int64_t ArrayList_CExprNode_length(ArrayList_CExprNode* self) {
    return self->len;
}
void ArrayList_CExprNode_deinit(ArrayList_CExprNode* self) {
    {
    KaiAllocator_free(self->allocator, (uint8_t*)(self->data));
}
}
ArrayList_CStmtNode ArrayList_CStmtNode_init(KaiAllocator* allocator) {
    ArrayList_CStmtNode self = (ArrayList_CStmtNode){0};
    self.len = 0LL;
    self.cap = 4LL;
    self.allocator = allocator;
    {
    self.data = (CStmtNode*)(KaiAllocator_alloc(allocator, (self.cap * (int64_t)(sizeof(CStmtNode))), 1LL));
}
    return self;
}
void ArrayList_CStmtNode_push(ArrayList_CStmtNode* self, CStmtNode item) {
    if (self->len == self->cap) {
    int64_t new_cap = (self->cap * 2LL);
    {
    CStmtNode* new_data = (CStmtNode*)(KaiAllocator_alloc(self->allocator, (new_cap * (int64_t)(sizeof(CStmtNode))), 1LL));
    int64_t i = 0LL;
    while (i < self->len) {
    (new_data)[i] = (self->data)[i];
    i = (i + 1LL);
}
    KaiAllocator_free(self->allocator, (uint8_t*)(self->data));
    self->data = new_data;
    self->cap = new_cap;
}
}
    (self->data)[self->len] = item;
    self->len = (self->len + 1LL);
}
CStmtNode ArrayList_CStmtNode_get(ArrayList_CStmtNode* self, int64_t index) {
    if ((index < 0LL) || (index >= self->len)) {
    {
    exit(1LL);
}
}
    return (self->data)[index];
}
void ArrayList_CStmtNode_set(ArrayList_CStmtNode* self, int64_t index, CStmtNode item) {
    if ((index < 0LL) || (index >= self->len)) {
    {
    exit(1LL);
}
}
    (self->data)[index] = item;
}
CStmtNode ArrayList_CStmtNode_pop(ArrayList_CStmtNode* self) {
    if (self->len == 0LL) {
    {
    exit(1LL);
}
}
    self->len = (self->len - 1LL);
    return (self->data)[self->len];
}
int64_t ArrayList_CStmtNode_length(ArrayList_CStmtNode* self) {
    return self->len;
}
void ArrayList_CStmtNode_deinit(ArrayList_CStmtNode* self) {
    {
    KaiAllocator_free(self->allocator, (uint8_t*)(self->data));
}
}
ArrayList_CDeclNode ArrayList_CDeclNode_init(KaiAllocator* allocator) {
    ArrayList_CDeclNode self = (ArrayList_CDeclNode){0};
    self.len = 0LL;
    self.cap = 4LL;
    self.allocator = allocator;
    {
    self.data = (CDeclNode*)(KaiAllocator_alloc(allocator, (self.cap * (int64_t)(sizeof(CDeclNode))), 1LL));
}
    return self;
}
void ArrayList_CDeclNode_push(ArrayList_CDeclNode* self, CDeclNode item) {
    if (self->len == self->cap) {
    int64_t new_cap = (self->cap * 2LL);
    {
    CDeclNode* new_data = (CDeclNode*)(KaiAllocator_alloc(self->allocator, (new_cap * (int64_t)(sizeof(CDeclNode))), 1LL));
    int64_t i = 0LL;
    while (i < self->len) {
    (new_data)[i] = (self->data)[i];
    i = (i + 1LL);
}
    KaiAllocator_free(self->allocator, (uint8_t*)(self->data));
    self->data = new_data;
    self->cap = new_cap;
}
}
    (self->data)[self->len] = item;
    self->len = (self->len + 1LL);
}
CDeclNode ArrayList_CDeclNode_get(ArrayList_CDeclNode* self, int64_t index) {
    if ((index < 0LL) || (index >= self->len)) {
    {
    exit(1LL);
}
}
    return (self->data)[index];
}
void ArrayList_CDeclNode_set(ArrayList_CDeclNode* self, int64_t index, CDeclNode item) {
    if ((index < 0LL) || (index >= self->len)) {
    {
    exit(1LL);
}
}
    (self->data)[index] = item;
}
CDeclNode ArrayList_CDeclNode_pop(ArrayList_CDeclNode* self) {
    if (self->len == 0LL) {
    {
    exit(1LL);
}
}
    self->len = (self->len - 1LL);
    return (self->data)[self->len];
}
int64_t ArrayList_CDeclNode_length(ArrayList_CDeclNode* self) {
    return self->len;
}
void ArrayList_CDeclNode_deinit(ArrayList_CDeclNode* self) {
    {
    KaiAllocator_free(self->allocator, (uint8_t*)(self->data));
}
}
ArrayList_LLVMStrMapEntry ArrayList_LLVMStrMapEntry_init(KaiAllocator* allocator) {
    ArrayList_LLVMStrMapEntry self = (ArrayList_LLVMStrMapEntry){0};
    self.len = 0LL;
    self.cap = 4LL;
    self.allocator = allocator;
    {
    self.data = (LLVMStrMapEntry*)(KaiAllocator_alloc(allocator, (self.cap * (int64_t)(sizeof(LLVMStrMapEntry))), 1LL));
}
    return self;
}
void ArrayList_LLVMStrMapEntry_push(ArrayList_LLVMStrMapEntry* self, LLVMStrMapEntry item) {
    if (self->len == self->cap) {
    int64_t new_cap = (self->cap * 2LL);
    {
    LLVMStrMapEntry* new_data = (LLVMStrMapEntry*)(KaiAllocator_alloc(self->allocator, (new_cap * (int64_t)(sizeof(LLVMStrMapEntry))), 1LL));
    int64_t i = 0LL;
    while (i < self->len) {
    (new_data)[i] = (self->data)[i];
    i = (i + 1LL);
}
    KaiAllocator_free(self->allocator, (uint8_t*)(self->data));
    self->data = new_data;
    self->cap = new_cap;
}
}
    (self->data)[self->len] = item;
    self->len = (self->len + 1LL);
}
LLVMStrMapEntry ArrayList_LLVMStrMapEntry_get(ArrayList_LLVMStrMapEntry* self, int64_t index) {
    if ((index < 0LL) || (index >= self->len)) {
    {
    exit(1LL);
}
}
    return (self->data)[index];
}
void ArrayList_LLVMStrMapEntry_set(ArrayList_LLVMStrMapEntry* self, int64_t index, LLVMStrMapEntry item) {
    if ((index < 0LL) || (index >= self->len)) {
    {
    exit(1LL);
}
}
    (self->data)[index] = item;
}
LLVMStrMapEntry ArrayList_LLVMStrMapEntry_pop(ArrayList_LLVMStrMapEntry* self) {
    if (self->len == 0LL) {
    {
    exit(1LL);
}
}
    self->len = (self->len - 1LL);
    return (self->data)[self->len];
}
int64_t ArrayList_LLVMStrMapEntry_length(ArrayList_LLVMStrMapEntry* self) {
    return self->len;
}
void ArrayList_LLVMStrMapEntry_deinit(ArrayList_LLVMStrMapEntry* self) {
    {
    KaiAllocator_free(self->allocator, (uint8_t*)(self->data));
}
}
int main(int argc, char** argv) {
    (void)(concatAlloc("", ""));
    if (argc < 2LL) {
    printf("Usage: kai <command> [options]\n");
    printf("Commands:\n");
    printf("  init [path]     Create a new Kai project\n");
    printf("  build [args]    Build the project using build.kai\n");
    printf("  check <file>    Type-check only (no code generation)\n");
    printf("  run <file>      Compile and run a .kai file\n");
    printf("  <file>          Compile and run (shorthand)\n");
    printf("  patch <file>    Apply an operation-based edit\n");
    printf("  explain <code>  Explain an error code\n");
    printf("  skills          List available agent skills\n");
    printf("  fix <file>      Auto-fix diagnostics (--plan|--patch|--apply)\n");
    printf("  graph <file>    Export or query the AST graph\n");
    printf("Flags:\n");
    printf("  --json          Output diagnostics in JSON format\n");
    printf("  -o <file>       Specify output binary name\n");
    printf("  -c              Emit C code only (no linking)\n");
    printf("  -CC             Use builder-based codegen (experimental)\n");
    printf("  -llvm           Use LLVM backend (experimental)\n");
    printf("  -O0|-O1|-O2|-O3|-Os  Optimization level (default: -O2)\n");
    return 1LL;
}
    const char* first_arg = "";
    {
    first_arg = (const char*)((argv)[1LL]);
}
    {
    if (strcmp(first_arg, "explain") == 0LL) {
    return run_explain(argc, argv);
}
    if (strcmp(first_arg, "skills") == 0LL) {
    return run_skills(argc, argv);
}
    if (strcmp(first_arg, "init") == 0LL) {
    return run_init(argc, argv);
}
    if (strcmp(first_arg, "build") == 0LL) {
    return run_build(argc, argv);
}
    if (strcmp(first_arg, "patch") == 0LL) {
    return run_patch(argc, argv);
}
    if (strcmp(first_arg, "fix") == 0LL) {
    const char* fix_mode = "plan";
    const char* fix_file = "";
    bool json = false;
    int64_t i2 = 2LL;
    while (i2 < argc) {
    const char* a = (const char*)((argv)[i2]);
    if (strcmp(a, "--plan") == 0LL) {
    fix_mode = "plan";
} else if (strcmp(a, "--patch") == 0LL) {
    fix_mode = "patch";
} else if (strcmp(a, "--apply") == 0LL) {
    fix_mode = "apply";
} else if (strcmp(a, "--json") == 0LL) {
    json = true;
} else if (strcmp(fix_file, "") == 0) {
    fix_file = a;
}
    i2 = (i2 + 1LL);
}
    if (strlen(fix_file) == 0LL) {
    printf("Usage: kai fix (--plan|--patch|--apply) [--json] <file>\n");
    return 1LL;
}
    return run_fix(fix_mode, fix_file, json);
}
    if (strcmp(first_arg, "graph") == 0LL) {
    return run_graph(argc, argv);
}
}
    const char* input_file = "";
    bool is_run = false;
    {
    if (strcmp(first_arg, "run") == 0LL) {
    is_run = true;
}
}
    if (is_run) {
    if (argc < 3LL) {
    printf("Error: No input file specified\n");
    printf("Usage: kai run <file>\n");
    return 1LL;
}
    {
    input_file = (const char*)((argv)[2LL]);
}
} else {
    input_file = first_arg;
}
    const char* output_bin = "";
    bool emit_c_only = false;
    bool use_builder = false;
    bool use_llvm = false;
    const char* opt_level = "-O2";
    bool json_mode = false;
    bool check_only = false;
    int64_t i = 1LL;
    if (is_run) {
    i = 2LL;
}
    while (i < argc) {
    const char* arg = (const char*)((argv)[i]);
    bool matched = true;
    {
    if (strcmp(arg, "run") == 0LL) {
} else if (strcmp(arg, "-c") == 0LL) {
    emit_c_only = true;
} else if (strcmp(arg, "-CC") == 0LL) {
    use_builder = true;
} else if (strcmp(arg, "-llvm") == 0LL) {
    use_llvm = true;
} else if (strcmp(arg, "-o") == 0LL) {
    if ((i + 1LL) < argc) {
    i = (i + 1LL);
    output_bin = (const char*)((argv)[i]);
} else {
    printf("Error: -o requires an argument\n");
    return 1LL;
}
} else if (strcmp(arg, "-O0") == 0LL) {
    opt_level = "-O0";
} else if (strcmp(arg, "-O1") == 0LL) {
    opt_level = "-O1";
} else if (strcmp(arg, "-O2") == 0LL) {
    opt_level = "-O2";
} else if (strcmp(arg, "-O3") == 0LL) {
    opt_level = "-O3";
} else if (strcmp(arg, "-Os") == 0LL) {
    opt_level = "-Os";
} else if (strcmp(arg, "--json") == 0LL) {
    json_mode = true;
} else if (strcmp(arg, "check") == 0LL) {
    check_only = true;
} else {
    matched = false;
}
}
    if (matched == false) {
    if ((strlen(arg) > 0LL) && ((arg)[0LL] != ((char)(45LL)))) {
    input_file = arg;
}
}
    i = (i + 1LL);
}
    if (strlen(input_file) == 0LL) {
    printf("Error: No input file specified\n");
    return 1LL;
}
    KaiAllocator allocator = KaiAllocator_new();
    const char* exe_include_flag = "";
    const char* exe_lib_flag = "";
    const char* exe_dir = "";
    {
    char* buf = (char*)(KaiAllocator_alloc(&(allocator), 1024LL, 1LL));
    if (get_exe_dir(buf, 1024LL) == 0LL) {
    exe_dir = (const char*)(buf);
    exe_include_flag = concatAlloc("-I", exe_dir);
}
}
    const char* llvm_lib_dir = "/opt/homebrew/opt/llvm@21/lib";
    {
    void* f = fopen("/opt/homebrew/opt/llvm@21/lib/libLLVM.dylib", "r");
    if (f != (void*)(unsigned long long)(0LL)) {
    fclose(f);
    exe_lib_flag = concatAlloc("-L", llvm_lib_dir);
}
}
    const char* base = get_base_name(input_file);
    const char* bin_name = base;
    if (strlen(output_bin) > 0LL) {
    bin_name = output_bin;
}
    const char* c_file = concatAlloc(base, ".c");
    if (use_builder) {
    c_file = concatAlloc("CC", c_file);
}
    Result_Str_IoError source_res = read_to_string(&(allocator), input_file);
    if (source_res.tag != 0LL) {
    if (json_mode) {
    printf("{\"messages\":[{\"code\":\"E0099\",\"message\":\"Failed to read input file: '%s'\"}]}\n", input_file);
}
    return 4LL;
}
    const char* source = (const char*)(source_res.value);
    StringPool pool = StringPool_init(&(allocator));
    Lexer lexer = Lexer_init(&(allocator), source, input_file, &(pool));
    Lexer_lex(&(lexer));
    if (lexer.has_error) {
    if (json_mode) {
    printf("{\"messages\":[{\"code\":\"E0100\",\"message\":\"Lexer error\",\"file\":\"%s\"}],\"error\":true}\n", input_file);
}
    return 2LL;
}
    Parser parser = Parser_init(&(allocator), input_file, lexer.tokens, source, &(pool));
    int64_t program_idx = Parser_parse_program(&(parser));
    if (program_idx < 0LL) {
    if (json_mode) {
    printf("{\"messages\":[{\"code\":\"E0101\",\"message\":\"Parse error\",\"file\":\"%s\"}],\"error\":true}\n", input_file);
}
    return 3LL;
}
    ImportResolver resolver = ImportResolver_init(&(allocator), &(pool));
    TypeChecker checker = TypeChecker_init(&(allocator), parser.stmt_pool, parser.expr_pool, parser.pattern_pool, input_file, source, &(resolver), &(pool));
    bool success = TypeChecker_check_program(&(checker), program_idx);
    if (!success) {
    if (json_mode) {
    printf("{\"result\":\"typecheck_failed\",\"file\":\"%s\"}\n", input_file);
}
    return 4LL;
}
    if (check_only) {
    if (json_mode) {
    printf("{\"result\":\"ok\",\"file\":\"%s\"}\n", input_file);
}
    return 0LL;
}
    if (use_llvm) {
    LLVMCodegen llvm_gen = LLVMCodegen_init(&(allocator), parser.stmt_pool, parser.expr_pool, parser.pattern_pool, &(resolver), &(pool));
    const char* obj_file = concatAlloc(base, ".o");
    if (use_builder) {
    obj_file = concatAlloc("CC", obj_file);
}
    bool emit_ok = LLVMCodegen_generate(&(llvm_gen), program_idx, obj_file);
    if (!emit_ok) {
    return 5LL;
}
    if (emit_c_only) {
    return 0LL;
}
    const char* cmd = concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc("clang ", obj_file), " "), exe_dir), "/runtime_helpers.c "), exe_include_flag), " -I/opt/homebrew/opt/llvm@21/include "), exe_lib_flag), " -o "), bin_name), " -lLLVM");
    {
    return system((char*)(cmd));
}
}
    const char* output = "";
    if (use_builder) {
    CodegenBuilder builder_gen = CodegenBuilder_init(&(allocator), parser.stmt_pool, parser.expr_pool, parser.pattern_pool, &(resolver), &(pool));
    output = CodegenBuilder_generate(&(builder_gen), program_idx);
} else {
    Codegen gen = Codegen_init(&(allocator), parser.stmt_pool, parser.expr_pool, parser.pattern_pool, &(resolver), &(pool));
    output = Codegen_generate(&(gen), program_idx);
}
    Result_Bool_IoError write_res = write_string(c_file, output);
    if (write_res.tag != 0LL) {
    return 5LL;
}
    if (emit_c_only) {
    return 0LL;
}
    const char* cmd = concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc("clang ", exe_include_flag), " "), opt_level), " "), c_file), " -o "), bin_name);
    {
    return system((char*)(cmd));
}
}uint8_t* CAlloc_alloc(CAlloc* self, int64_t size, int64_t alignment) {
    {
    return malloc((size_t)(size));
}
}
uint8_t* CAlloc_realloc(CAlloc* self, uint8_t* ptr, int64_t old_size, int64_t new_size, int64_t alignment) {
    {
    return realloc((uint8_t*)(ptr), (size_t)(new_size));
}
}
void CAlloc_free(CAlloc* self, uint8_t* ptr) {
    {
    free((uint8_t*)(ptr));
}
}
void CAlloc_deinit(CAlloc* self) {
}
int64_t class_obj_size(int64_t idx) {
    return (8LL << idx);
}
int64_t class_for(int64_t sz) {
    if (sz <= 8LL) {
    return 0LL;
}
    if (sz <= 16LL) {
    return 1LL;
}
    if (sz <= 32LL) {
    return 2LL;
}
    if (sz <= 64LL) {
    return 3LL;
}
    if (sz <= 128LL) {
    return 4LL;
}
    if (sz <= 256LL) {
    return 5LL;
}
    if (sz <= 512LL) {
    return 6LL;
}
    if (sz <= 1024LL) {
    return 7LL;
}
    if (sz <= 2048LL) {
    return 8LL;
}
    if (sz <= 4096LL) {
    return 9LL;
}
    if (sz <= 8192LL) {
    return 10LL;
}
    if (sz <= 16384LL) {
    return 11LL;
}
    return (-1LL);
}
bool is_small(int64_t sz) {
    return (sz <= 16384LL);
}
int64_t page_align_up(int64_t n) {
    return ((n + 4095LL) & (-4096LL));
}
KaiAllocator KaiAllocator_init(void) {
    KaiAllocator self = (KaiAllocator){0};
    {
    uint8_t* ptr = _kai_mmap((uint8_t*)(unsigned long long)(0LL), 4096LL, 3LL, 4098LL, (-1LL), 0LL);
    self.heads = ptr;
    self.used = 0LL;
}
    return self;
}
uint8_t* KaiAllocator_get_head(KaiAllocator* self, int64_t idx) {
    {
    uint8_t** arr = (uint8_t**)(self->heads);
    return (arr)[idx];
}
}
void KaiAllocator_set_head(KaiAllocator* self, int64_t idx, uint8_t* head) {
    {
    uint8_t** arr = (uint8_t**)(self->heads);
    (arr)[idx] = head;
}
}
uint8_t* KaiAllocator_allocate_slab(KaiAllocator* self, int64_t idx) {
    {
    uint8_t* raw = _kai_mmap((uint8_t*)(unsigned long long)(0LL), 131072LL, 3LL, 4098LL, (-1LL), 0LL);
    if ((int64_t)(raw) == (-1LL)) {
    return (uint8_t*)(unsigned long long)(0LL);
}
    int64_t aligned_addr = (((int64_t)(raw) + 65535LL) & (-65536LL));
    uint8_t* slab = (uint8_t*)(unsigned long long)(aligned_addr);
    int64_t before = (aligned_addr - (int64_t)(raw));
    if (before > 0LL) {
    _kai_munmap(raw, before);
}
    int64_t after_start = (aligned_addr + 65536LL);
    int64_t after_len = (((int64_t)(raw) + 131072LL) - after_start);
    if (after_len > 0LL) {
    _kai_munmap((uint8_t*)(unsigned long long)(after_start), after_len);
}
    int64_t objsz = class_obj_size(idx);
    SlabHeader* hdr = (SlabHeader*)(slab);
    hdr->magic = 1262569811LL;
    hdr->obj_size = objsz;
    hdr->capacity = ((65536LL - 64LL) / objsz);
    hdr->free_cnt = 0LL;
    hdr->free_head = (uint8_t*)(unsigned long long)(0LL);
    hdr->next_bump_idx = 0LL;
    hdr->pad = 0LL;
    hdr->next = KaiAllocator_get_head(self, idx);
    KaiAllocator_set_head(self, idx, slab);
    return slab;
}
}
uint8_t* KaiAllocator_alloc_large(KaiAllocator* self, int64_t size) {
    {
    int64_t total = (size + 16LL);
    int64_t page_aligned = page_align_up(total);
    uint8_t* raw = _kai_mmap((uint8_t*)(unsigned long long)(0LL), (page_aligned + 65536LL), 3LL, 4098LL, (-1LL), 0LL);
    if ((int64_t)(raw) == (-1LL)) {
    return (uint8_t*)(unsigned long long)(0LL);
}
    int64_t aligned_addr = (((int64_t)(raw) + 65535LL) & (-65536LL));
    uint8_t* slab = (uint8_t*)(unsigned long long)(aligned_addr);
    ((int64_t*)(slab))[0LL] = (int64_t)(raw);
    ((int64_t*)(slab))[1LL] = size;
    self->used = (self->used + size);
    return (uint8_t*)(unsigned long long)((aligned_addr + 16LL));
}
}
void KaiAllocator_free_large(KaiAllocator* self, uint8_t* ptr) {
    {
    int64_t slab_addr = ((int64_t)(ptr) & (-65536LL));
    int64_t raw_ptr = ((int64_t*)((uint8_t*)(unsigned long long)(slab_addr)))[0LL];
    int64_t orig_size = ((int64_t*)((uint8_t*)(unsigned long long)(slab_addr)))[1LL];
    int64_t mmap_size = (page_align_up((orig_size + 16LL)) + 65536LL);
    self->used = (self->used - orig_size);
    _kai_munmap((uint8_t*)(unsigned long long)(raw_ptr), mmap_size);
}
}
uint8_t* KaiAllocator_alloc(KaiAllocator* self, int64_t size, int64_t align) {
    if (!is_small(size)) {
    return KaiAllocator_alloc_large(self, size);
}
    int64_t idx = class_for(size);
    int64_t objsz = class_obj_size(idx);
    {
    uint8_t* slab = KaiAllocator_get_head(self, idx);
    while (slab != (uint8_t*)(unsigned long long)(0LL)) {
    SlabHeader* hdr = (SlabHeader*)(slab);
    if (hdr->free_head != (uint8_t*)(unsigned long long)(0LL)) {
    uint8_t* ptr = hdr->free_head;
    hdr->free_head = ((FreeBlock*)(ptr))->next;
    hdr->free_cnt = (hdr->free_cnt - 1LL);
    self->used = (self->used + objsz);
    return ptr;
}
    if (hdr->next_bump_idx < hdr->capacity) {
    int64_t off = (64LL + (hdr->next_bump_idx * objsz));
    uint8_t* ptr = (uint8_t*)(unsigned long long)(((int64_t)(slab) + off));
    hdr->next_bump_idx = (hdr->next_bump_idx + 1LL);
    self->used = (self->used + objsz);
    return ptr;
}
    slab = hdr->next;
}
    uint8_t* ns = KaiAllocator_allocate_slab(self, idx);
    if (ns == (uint8_t*)(unsigned long long)(0LL)) {
    return (uint8_t*)(unsigned long long)(0LL);
}
    SlabHeader* hdr = (SlabHeader*)(ns);
    hdr->next_bump_idx = 1LL;
    self->used = (self->used + objsz);
    return (uint8_t*)(unsigned long long)(((int64_t)(ns) + 64LL));
}
}
uint8_t* KaiAllocator_realloc(KaiAllocator* self, uint8_t* ptr, int64_t old_size, int64_t new_size, int64_t align) {
    if (ptr == (uint8_t*)(unsigned long long)(0LL)) {
    return KaiAllocator_alloc(self, new_size, align);
}
    if (new_size <= old_size) {
    return ptr;
}
    {
    int64_t slab_addr = ((int64_t)(ptr) & (-65536LL));
    SlabHeader* hdr = (SlabHeader*)((uint8_t*)(unsigned long long)(slab_addr));
    if (hdr->magic == 1262569811LL) {
    if (new_size <= hdr->obj_size) {
    return ptr;
}
    uint8_t* np = KaiAllocator_alloc(self, new_size, align);
    if (np == (uint8_t*)(unsigned long long)(0LL)) {
    return (uint8_t*)(unsigned long long)(0LL);
}
    int64_t i = 0LL;
    while (i < old_size) {
    (np)[i] = (ptr)[i];
    i = (i + 1LL);
}
    KaiAllocator_free(self, ptr);
    return np;
}
}
    uint8_t* np = KaiAllocator_alloc(self, new_size, align);
    if (np == (uint8_t*)(unsigned long long)(0LL)) {
    return (uint8_t*)(unsigned long long)(0LL);
}
    {
    int64_t i = 0LL;
    while (i < old_size) {
    (np)[i] = (ptr)[i];
    i = (i + 1LL);
}
    KaiAllocator_free(self, ptr);
}
    return np;
}
void KaiAllocator_free(KaiAllocator* self, uint8_t* ptr) {
    if (ptr == (uint8_t*)(unsigned long long)(0LL)) {
    return;
}
    {
    int64_t slab_addr = ((int64_t)(ptr) & (-65536LL));
    SlabHeader* hdr = (SlabHeader*)((uint8_t*)(unsigned long long)(slab_addr));
    if (hdr->magic == 1262569811LL) {
    FreeBlock* fb = (FreeBlock*)(ptr);
    fb->next = hdr->free_head;
    hdr->free_head = (uint8_t*)(ptr);
    hdr->free_cnt = (hdr->free_cnt + 1LL);
} else {
    KaiAllocator_free_large(self, (uint8_t*)(ptr));
}
}
}
void KaiAllocator_deinit(KaiAllocator* self) {
    int64_t i = 0LL;
    while (i < 12LL) {
    {
    uint8_t* slab = KaiAllocator_get_head(self, i);
    while (slab != (uint8_t*)(unsigned long long)(0LL)) {
    uint8_t* next = ((SlabHeader*)(slab))->next;
    _kai_munmap(slab, 65536LL);
    slab = next;
}
}
    i = (i + 1LL);
}
    {
    _kai_munmap(self->heads, page_align_up(96LL));
}
}
KaiAllocator KaiAllocator_new(void) {
    KaiAllocator a = (KaiAllocator){ .heads = (uint8_t*)(unsigned long long)(0LL), .used = 0LL };
    a = KaiAllocator_init();
    return a;
}
Result_Str_IoError read_to_string(KaiAllocator* allocator, const char* path) {
    {
    void* file = fopen((char*)(path), (char*)("rb"));
    if ((char*)(file) == NULL) {
    return (Result_Str_IoError){ .tag = IoError_open_failed };
}
    fseek(file, 0LL, 2LL);
    int64_t size = ftell(file);
    rewind(file);
    char* buf = (char*)(KaiAllocator_alloc(allocator, (size + 1LL), 1LL));
    int64_t bytes_read = fread(buf, 1LL, size, file);
    (buf)[bytes_read] = ((char)(0LL));
    fclose(file);
    return (Result_Str_IoError){ .tag = 0, .value = (const char*)(buf) };
}
}
Result_Bool_IoError write_string(const char* path, const char* content) {
    {
    void* file = fopen((char*)(path), (char*)("wb"));
    if ((char*)(file) == NULL) {
    return (Result_Bool_IoError){ .tag = IoError_open_failed };
}
    int64_t len = strlen(content);
    int64_t bytes_written = fwrite((char*)(content), 1LL, len, file);
    fclose(file);
    return (Result_Bool_IoError){ .tag = 0, .value = true };
}
}
const char* concatAlloc(const char* left, const char* right) {
    int64_t left_len = strlen(left);
    int64_t right_len = strlen(right);
    int64_t total = ((left_len + right_len) + 1LL);
    char* buf = malloc(total);
    if (buf != (char*)(unsigned long long)(0LL)) {
    (void)(__kai_std_str_concat(buf, left, right));
    (buf)[(total - 1LL)] = ((char)(0LL));
}
    return (const char*)(buf);
}
bool __kai_std_str_is_ascii_space(char byte) {
    return (((byte == ((char)(32LL))) || (byte == ((char)(9LL)))) || ((byte == ((char)(10LL))) || (byte == ((char)(13LL)))));
}
char __kai_std_str_to_lower_byte(char byte) {
    if ((byte >= ((char)(65LL))) && (byte <= ((char)(90LL)))) {
    return (byte + ((char)(32LL)));
}
    return byte;
}
char __kai_std_str_to_upper_byte(char byte) {
    if ((byte >= ((char)(97LL))) && (byte <= ((char)(122LL)))) {
    return (byte - ((char)(32LL)));
}
    return byte;
}
const char* __kai_std_str_copy(char* buffer, const char* text) {
    int64_t len = strlen((const char*)(text));
    if (len > 100000000LL) {
    return NULL;
}
    int64_t index = 0LL;
    while (index < len) {
    (buffer)[index] = (text)[index];
    index = (index + 1LL);
}
    (buffer)[len] = ((char)(0LL));
    return __kai_str_sub(buffer, 0, len);
}
const char* __kai_std_str_concat(char* buffer, const char* left, const char* right) {
    int64_t left_len = strlen((const char*)(left));
    int64_t right_len = strlen((const char*)(right));
    if ((left_len > 100000000LL) || (right_len > (100000000LL - left_len))) {
    return NULL;
}
    int64_t index = 0LL;
    while (index < left_len) {
    (buffer)[index] = (left)[index];
    index = (index + 1LL);
}
    int64_t right_index = 0LL;
    while (right_index < right_len) {
    (buffer)[(left_len + right_index)] = (right)[right_index];
    right_index = (right_index + 1LL);
}
    (buffer)[(left_len + right_len)] = ((char)(0LL));
    return __kai_str_sub(buffer, 0, (left_len + right_len));
}
const char* __kai_std_str_repeat(char* buffer, const char* text, int64_t count) {
    int64_t len = strlen((const char*)(text));
    if ((count > 0LL) && (len > (100000000LL / count))) {
    return NULL;
}
    int64_t out = 0LL;
    int64_t repetition = 0LL;
    while (repetition < count) {
    int64_t index = 0LL;
    while (index < len) {
    (buffer)[out] = (text)[index];
    out = (out + 1LL);
    index = (index + 1LL);
}
    repetition = (repetition + 1LL);
}
    (buffer)[out] = ((char)(0LL));
    return __kai_str_sub(buffer, 0, out);
}
const char* __kai_std_str_replace(char* buffer, const char* text, const char* old, const char* replacement) {
    int64_t old_len = strlen((const char*)(old));
    if (old_len == 0LL) {
    return NULL;
}
    int64_t text_len = strlen((const char*)(text));
    int64_t read = 0LL;
    int64_t write = 0LL;
    while (read < text_len) {
    if ((old_len <= (text_len - read)) && __kai_std_str_starts_with(__kai_str_sub(text, read, strlen(text)), old)) {
    if (strlen((const char*)(replacement)) > (100000000LL - write)) {
    return NULL;
}
    int64_t new_index = 0LL;
    while (new_index < strlen((const char*)(replacement))) {
    (buffer)[write] = (replacement)[new_index];
    write = (write + 1LL);
    new_index = (new_index + 1LL);
}
    read = (read + old_len);
} else {
    if (write >= 100000000LL) {
    return NULL;
}
    (buffer)[write] = (text)[read];
    write = (write + 1LL);
    read = (read + 1LL);
}
}
    (buffer)[write] = ((char)(0LL));
    return __kai_str_sub(buffer, 0, write);
}
const char* __kai_std_str_to_lower_ascii(char* buffer, const char* text) {
    int64_t len = strlen((const char*)(text));
    if (len > 100000000LL) {
    return NULL;
}
    int64_t index = 0LL;
    while (index < len) {
    (buffer)[index] = __kai_std_str_to_lower_byte((text)[index]);
    index = (index + 1LL);
}
    (buffer)[len] = ((char)(0LL));
    return __kai_str_sub(buffer, 0, len);
}
const char* __kai_std_str_to_upper_ascii(char* buffer, const char* text) {
    int64_t len = strlen((const char*)(text));
    if (len > 100000000LL) {
    return NULL;
}
    int64_t index = 0LL;
    while (index < len) {
    (buffer)[index] = __kai_std_str_to_upper_byte((text)[index]);
    index = (index + 1LL);
}
    (buffer)[len] = ((char)(0LL));
    return __kai_str_sub(buffer, 0, len);
}
const char* __kai_std_str_reverse(char* buffer, const char* text) {
    int64_t len = strlen((const char*)(text));
    if (len > 100000000LL) {
    return NULL;
}
    int64_t index = 0LL;
    while (index < len) {
    (buffer)[index] = (text)[((len - 1LL) - index)];
    index = (index + 1LL);
}
    (buffer)[len] = ((char)(0LL));
    return __kai_str_sub(buffer, 0, len);
}
int64_t __kai_std_str_count_byte(const char* text, char byte) {
    int64_t index = 0LL;
    int64_t count = 0LL;
    while (index < strlen((const char*)(text))) {
    if ((text)[index] == byte) {
    count = (count + 1LL);
}
    index = (index + 1LL);
}
    return count;
}
bool __kai_std_str_starts_with(const char* text, const char* prefix) {
    int64_t prefix_len = strlen((const char*)(prefix));
    if (prefix_len > strlen((const char*)(text))) {
    return false;
}
    int64_t index = 0LL;
    while (index < prefix_len) {
    if ((text)[index] != (prefix)[index]) {
    return false;
}
    index = (index + 1LL);
}
    return true;
}
bool __kai_std_str_ends_with(const char* text, const char* suffix) {
    int64_t text_len = strlen((const char*)(text));
    int64_t suffix_len = strlen((const char*)(suffix));
    if (suffix_len > text_len) {
    return false;
}
    int64_t start = (text_len - suffix_len);
    int64_t index = 0LL;
    while (index < suffix_len) {
    if ((text)[(start + index)] != (suffix)[index]) {
    return false;
}
    index = (index + 1LL);
}
    return true;
}
bool __kai_std_str_contains(const char* text, const char* needle) {
    int64_t needle_len = strlen((const char*)(needle));
    if (needle_len == 0LL) {
    return true;
}
    int64_t text_len = strlen((const char*)(text));
    if (needle_len > text_len) {
    return false;
}
    int64_t last_start = (text_len - needle_len);
    int64_t start = 0LL;
    while (start <= last_start) {
    int64_t offset = 0LL;
    bool same = true;
    while (same && (offset < needle_len)) {
    if ((text)[(start + offset)] != (needle)[offset]) {
    same = false;
} else {
    offset = (offset + 1LL);
}
}
    if (same) {
    return true;
}
    start = (start + 1LL);
}
    return false;
}
int64_t __kai_std_str_index_of(const char* text, const char* needle) {
    int64_t needle_len = strlen((const char*)(needle));
    if (needle_len == 0LL) {
    return 0LL;
}
    int64_t text_len = strlen((const char*)(text));
    if (needle_len > text_len) {
    return text_len;
}
    int64_t last_start = (text_len - needle_len);
    int64_t start = 0LL;
    while (start <= last_start) {
    int64_t offset = 0LL;
    bool same = true;
    while (same && (offset < needle_len)) {
    if ((text)[(start + offset)] != (needle)[offset]) {
    same = false;
} else {
    offset = (offset + 1LL);
}
}
    if (same) {
    return start;
}
    start = (start + 1LL);
}
    return text_len;
}
int64_t __kai_std_str_last_index_of(const char* text, const char* needle) {
    int64_t needle_len = strlen((const char*)(needle));
    int64_t text_len = strlen((const char*)(text));
    if (needle_len == 0LL) {
    return text_len;
}
    if (needle_len > text_len) {
    return text_len;
}
    int64_t start = ((text_len - needle_len) + 1LL);
    while (start > 0LL) {
    start = (start - 1LL);
    int64_t offset = 0LL;
    bool same = true;
    while (same && (offset < needle_len)) {
    if ((text)[(start + offset)] != (needle)[offset]) {
    same = false;
} else {
    offset = (offset + 1LL);
}
}
    if (same) {
    return start;
}
}
    return text_len;
}
int64_t __kai_std_str_count(const char* text, const char* needle) {
    int64_t needle_len = strlen((const char*)(needle));
    if (needle_len == 0LL) {
    return (strlen((const char*)(text)) + 1LL);
}
    int64_t index = 0LL;
    int64_t count = 0LL;
    while (index <= strlen((const char*)(text))) {
    const char* rest = __kai_str_sub(text, index, strlen(text));
    int64_t found = __kai_std_str_index_of(rest, needle);
    if (found == strlen((const char*)(rest))) {
    return count;
}
    count = (count + 1LL);
    index = ((index + found) + needle_len);
}
    return count;
}
int64_t __kai_std_str_split_count(const char* text, const char* sep) {
    if (strlen((const char*)(sep)) == 0LL) {
    return 0LL;
}
    return (__kai_std_str_count(text, sep) + 1LL);
}
const char* __kai_std_str_split(const char* text, const char* sep, int64_t part_index) {
    int64_t sep_len = strlen((const char*)(sep));
    if (sep_len == 0LL) {
    return NULL;
}
    int64_t current = 0LL;
    int64_t start = 0LL;
    while (start <= strlen((const char*)(text))) {
    const char* rest = __kai_str_sub(text, start, strlen(text));
    int64_t found = __kai_std_str_index_of(rest, sep);
    int64_t end = (start + found);
    if (current == part_index) {
    return __kai_str_sub(text, start, end);
}
    if (found == strlen((const char*)(rest))) {
    return NULL;
}
    current = (current + 1LL);
    start = (end + sep_len);
}
    return NULL;
}
bool __kai_std_str_eql_ignore_ascii_case(const char* left, const char* right) {
    if (strlen((const char*)(left)) != strlen((const char*)(right))) {
    return false;
}
    int64_t index = 0LL;
    while (index < strlen((const char*)(left))) {
    if (__kai_std_str_to_lower_byte((left)[index]) != __kai_std_str_to_lower_byte((right)[index])) {
    return false;
}
    index = (index + 1LL);
}
    return true;
}
const char* __kai_std_str_trim_ascii(const char* text) {
    int64_t start = 0LL;
    int64_t end = strlen((const char*)(text));
    while ((start < end) && __kai_std_str_is_ascii_space((text)[start])) {
    start = (start + 1LL);
}
    while ((end > start) && __kai_std_str_is_ascii_space((text)[(end - 1LL)])) {
    end = (end - 1LL);
}
    return __kai_str_sub(text, start, end);
}
const char* __kai_std_str_trim_start_ascii(const char* text) {
    int64_t start = 0LL;
    while ((start < strlen((const char*)(text))) && __kai_std_str_is_ascii_space((text)[start])) {
    start = (start + 1LL);
}
    return __kai_str_sub(text, start, strlen(text));
}
const char* __kai_std_str_trim_end_ascii(const char* text) {
    int64_t end = strlen((const char*)(text));
    while ((end > 0LL) && __kai_std_str_is_ascii_space((text)[(end - 1LL)])) {
    end = (end - 1LL);
}
    return __kai_str_sub(text, 0, end);
}
int64_t __kai_std_str_field_count_ascii(const char* text) {
    return __kai_std_str_word_count_ascii(text);
}
const char* __kai_std_str_field_ascii(const char* text, int64_t field_index) {
    int64_t index = 0LL;
    int64_t current = 0LL;
    while (index < strlen((const char*)(text))) {
    while ((index < strlen((const char*)(text))) && __kai_std_str_is_ascii_space((text)[index])) {
    index = (index + 1LL);
}
    if (index >= strlen((const char*)(text))) {
    return NULL;
}
    int64_t start = index;
    while ((index < strlen((const char*)(text))) && (!__kai_std_str_is_ascii_space((text)[index]))) {
    index = (index + 1LL);
}
    if (current == field_index) {
    return __kai_str_sub(text, start, index);
}
    current = (current + 1LL);
}
    return NULL;
}
int64_t __kai_std_str_line_count(const char* text) {
    if (strlen((const char*)(text)) == 0LL) {
    return 0LL;
}
    int64_t count = 1LL;
    int64_t index = 0LL;
    while (index < strlen((const char*)(text))) {
    if (((text)[index] == ((char)(10LL))) && ((index + 1LL) < strlen((const char*)(text)))) {
    count = (count + 1LL);
}
    index = (index + 1LL);
}
    return count;
}
const char* __kai_std_str_line(const char* text, int64_t line_index) {
    if (strlen((const char*)(text)) == 0LL) {
    return NULL;
}
    int64_t current = 0LL;
    int64_t start = 0LL;
    int64_t index = 0LL;
    while (index <= strlen((const char*)(text))) {
    if ((index == strlen((const char*)(text))) || ((text)[index] == ((char)(10LL)))) {
    if ((index == strlen((const char*)(text))) && (start == strlen((const char*)(text)))) {
    return NULL;
}
    int64_t end = index;
    if ((end > start) && ((text)[(end - 1LL)] == ((char)(13LL)))) {
    end = (end - 1LL);
}
    if (current == line_index) {
    return __kai_str_sub(text, start, end);
}
    current = (current + 1LL);
    start = (index + 1LL);
}
    index = (index + 1LL);
}
    return NULL;
}
int64_t __kai_std_str_word_count_ascii(const char* text) {
    int64_t index = 0LL;
    int64_t count = 0LL;
    bool in_word = false;
    while (index < strlen((const char*)(text))) {
    if (__kai_std_str_is_ascii_space((text)[index])) {
    in_word = false;
} else if (!in_word) {
    count = (count + 1LL);
    in_word = true;
}
    index = (index + 1LL);
}
    return count;
}
TokenType keyword_type(const char* ident) {
    if (strcmp(ident, "let") == 0) {
    return TokenType_LET;
} else if (strcmp(ident, "var") == 0) {
    return TokenType_VAR;
} else if (strcmp(ident, "fn") == 0) {
    return TokenType_FUNC;
} else if (strcmp(ident, "if") == 0) {
    return TokenType_IF;
} else if (strcmp(ident, "else") == 0) {
    return TokenType_ELSE;
} else if (strcmp(ident, "while") == 0) {
    return TokenType_WHILE;
} else if (strcmp(ident, "for") == 0) {
    return TokenType_FOR;
} else if (strcmp(ident, "in") == 0) {
    return TokenType_IN;
} else if (strcmp(ident, "return") == 0) {
    return TokenType_RETURN;
} else if (strcmp(ident, "true") == 0) {
    return TokenType_BOOL_LIT;
} else if (strcmp(ident, "false") == 0) {
    return TokenType_BOOL_LIT;
} else if (strcmp(ident, "struct") == 0) {
    return TokenType_STRUCT;
} else if (strcmp(ident, "impl") == 0) {
    return TokenType_IMPL;
} else if (strcmp(ident, "mut") == 0) {
    return TokenType_MUT;
} else if (strcmp(ident, "unsafe") == 0) {
    return TokenType_UNSAFE;
} else if (strcmp(ident, "extern") == 0) {
    return TokenType_EXTERN;
} else if (strcmp(ident, "enum") == 0) {
    return TokenType_ENUM;
} else if (strcmp(ident, "match") == 0) {
    return TokenType_MATCH;
} else if (strcmp(ident, "case") == 0) {
    return TokenType_CASE;
} else if (strcmp(ident, "use") == 0) {
    return TokenType_USE;
} else if (strcmp(ident, "check") == 0) {
    return TokenType_CHECK;
} else if (strcmp(ident, "trait") == 0) {
    return TokenType_TRAIT;
} else if (strcmp(ident, "pub") == 0) {
    return TokenType_PUB;
} else if (strcmp(ident, "import") == 0) {
    return TokenType_IMPORT;
} else if (strcmp(ident, "cimport") == 0) {
    return TokenType_CIMPORT;
} else if (strcmp(ident, "from") == 0) {
    return TokenType_FROM;
} else if (strcmp(ident, "as") == 0) {
    return TokenType_AS;
} else if (strcmp(ident, "sizeof") == 0) {
    return TokenType_SIZEOF;
} else if (strcmp(ident, "defer") == 0) {
    return TokenType_DEFER;
} else if (strcmp(ident, "errdefer") == 0) {
    return TokenType_ERRDEFER;
} else if (strcmp(ident, "none") == 0) {
    return TokenType_NONE;
} else if (strcmp(ident, "try") == 0) {
    return TokenType_TRY;
} else if (strcmp(ident, "catch") == 0) {
    return TokenType_CATCH;
} else if (strcmp(ident, "own") == 0) {
    return TokenType_OWN;
} else if (strcmp(ident, "error") == 0) {
    return TokenType_ERROR;
} else if (strcmp(ident, "asm") == 0) {
    return TokenType_ASM;
} else if (strcmp(ident, "volatile") == 0) {
    return TokenType_VOLATILE;
} else if (strcmp(ident, "break") == 0) {
    return TokenType_BREAK;
} else if (strcmp(ident, "continue") == 0) {
    return TokenType_CONTINUE;
} else {
    return TokenType_IDENTIFIER;
}
}
TokenValue make_keyword_value(const char* ident, TokenType ttype, StringPool* pool) {
    if (ttype == TokenType_BOOL_LIT) {
    if (strcmp(ident, "true") == 0) {
    return (TokenValue){ .tag = TokenValue_tv_bool_TAG, .payload = { .tv_bool = { .v = true } } };
}
    return (TokenValue){ .tag = TokenValue_tv_bool_TAG, .payload = { .tv_bool = { .v = false } } };
}
    return (TokenValue){ .tag = TokenValue_tv_str_TAG, .payload = { .tv_str = { .v = StringPool_intern(pool, ident) } } };
}
Lexer Lexer_init(KaiAllocator* allocator, const char* source, const char* source_file, StringPool* pool) {
    Lexer self = (Lexer){0};
    self.allocator = allocator;
    self.source = source;
    self.cursor = 0LL;
    self.line = 1LL;
    self.column = 1LL;
    self.paren_depth = 0LL;
    self.brace_depth = 0LL;
    self.has_error = false;
    self.source_file = source_file;
    self.pool = pool;
    {
    self.tokens = (ArrayList_Token*)(KaiAllocator_alloc(allocator, sizeof(ArrayList_Token), 1LL));
    self.indent_stack = (ArrayList_Int*)(KaiAllocator_alloc(allocator, sizeof(ArrayList_Int), 1LL));
}
    *(self.tokens) = ArrayList_Token_init(allocator);
    *(self.indent_stack) = ArrayList_Int_init(allocator);
    ArrayList_Int_push(self.indent_stack, 0LL);
    {
    self.source_len = strlen(source);
}
    return self;
}
char Lexer_peek(Lexer* self, int64_t offset) {
    int64_t pos = (self->cursor + offset);
    if (pos >= self->source_len) {
    return ((char)(0LL));
}
    return (self->source)[pos];
}
char Lexer_advance(Lexer* self) {
    if (self->cursor >= self->source_len) {
    return ((char)(0LL));
}
    char c = (self->source)[self->cursor];
    self->cursor = (self->cursor + 1LL);
    if (c == '\n') {
    self->line = (self->line + 1LL);
    self->column = 1LL;
} else {
    self->column = (self->column + 1LL);
}
    return c;
}
void Lexer_emit(Lexer* self, TokenType ttype, TokenValue value) {
    ArrayList_Token_push(self->tokens, (Token){ .tok_type = ttype, .value = value, .line = self->line, .column = self->column });
}
void Lexer_emit_str(Lexer* self, TokenType ttype, const char* s) {
    Lexer_emit(self, ttype, (TokenValue){ .tag = TokenValue_tv_str_TAG, .payload = { .tv_str = { .v = StringPool_intern(self->pool, s) } } });
}
void Lexer_lex_error(Lexer* self, const char* msg) {
    parser_err(self->source_file, self->source, "E0100", msg, self->line, self->column);
    self->has_error = true;
}
void Lexer_skip_line_comment(Lexer* self) {
    while ((self->cursor < self->source_len) && (Lexer_peek(self, 0LL) != '\n')) {
    (void)(Lexer_advance(self));
}
}
void Lexer_skip_block_comment(Lexer* self) {
    (void)(Lexer_advance(self));
    while (self->cursor < self->source_len) {
    if ((Lexer_peek(self, 0LL) == '*') && (Lexer_peek(self, 1LL) == '/')) {
    (void)(Lexer_advance(self));
    (void)(Lexer_advance(self));
    return;
}
    (void)(Lexer_advance(self));
}
}
void Lexer_skip_whitespace(Lexer* self) {
    bool done = false;
    while ((self->cursor < self->source_len) && (!done)) {
    char c = Lexer_peek(self, 0LL);
    if (((c == ' ') || (c == '\t')) || (c == '\r')) {
    (void)(Lexer_advance(self));
} else if (c == '/') {
    if (Lexer_peek(self, 1LL) == '/') {
    Lexer_skip_line_comment(self);
} else if (Lexer_peek(self, 1LL) == '*') {
    Lexer_skip_block_comment(self);
} else {
    done = true;
}
} else {
    done = true;
}
}
}
void Lexer_lex_identifier(Lexer* self) {
    StringBuilder sb = StringBuilder_init(self->allocator);
    bool done = false;
    while ((self->cursor < self->source_len) && (!done)) {
    char c = Lexer_peek(self, 0LL);
    if (is_alnum(c) || (c == '_')) {
    StringBuilder_append_char(&(sb), Lexer_advance(self));
} else {
    done = true;
}
}
    const char* ident = StringBuilder_to_str(&(sb));
    TokenType ktype = keyword_type(ident);
    if (ktype == TokenType_IDENTIFIER) {
    Lexer_emit(self, TokenType_IDENTIFIER, (TokenValue){ .tag = TokenValue_tv_str_TAG, .payload = { .tv_str = { .v = StringPool_intern(self->pool, ident) } } });
} else if (ktype == TokenType_BOOL_LIT) {
    Lexer_emit(self, TokenType_BOOL_LIT, make_keyword_value(ident, TokenType_BOOL_LIT, self->pool));
} else {
    Lexer_emit(self, ktype, (TokenValue){ .tag = TokenValue_tv_str_TAG, .payload = { .tv_str = { .v = StringPool_intern(self->pool, ident) } } });
}
}
void Lexer_lex_number(Lexer* self) {
    StringBuilder sb = StringBuilder_init(self->allocator);
    bool done = false;
    while ((self->cursor < self->source_len) && (!done)) {
    char c = Lexer_peek(self, 0LL);
    if (is_digit(c)) {
    StringBuilder_append_char(&(sb), Lexer_advance(self));
} else {
    done = true;
}
}
    if ((Lexer_peek(self, 0LL) == '.') && (Lexer_peek(self, 1LL) != '.')) {
    StringBuilder_append_char(&(sb), Lexer_advance(self));
    done = false;
    while ((self->cursor < self->source_len) && (!done)) {
    char c = Lexer_peek(self, 0LL);
    if (is_digit(c)) {
    StringBuilder_append_char(&(sb), Lexer_advance(self));
} else {
    done = true;
}
}
    const char* num_str = StringBuilder_to_str(&(sb));
    Lexer_emit(self, TokenType_FLOAT_LIT, (TokenValue){ .tag = TokenValue_tv_str_TAG, .payload = { .tv_str = { .v = StringPool_intern(self->pool, num_str) } } });
} else {
    const char* num_str = StringBuilder_to_str(&(sb));
    Lexer_emit(self, TokenType_INT_LIT, (TokenValue){ .tag = TokenValue_tv_str_TAG, .payload = { .tv_str = { .v = StringPool_intern(self->pool, num_str) } } });
}
}
void Lexer_lex_string(Lexer* self) {
    (void)(Lexer_advance(self));
    StringBuilder sb = StringBuilder_init(self->allocator);
    bool done = false;
    while ((self->cursor < self->source_len) && (!done)) {
    char c = Lexer_peek(self, 0LL);
    if (c == '"') {
    done = true;
} else if (c == '\\') {
    (void)(Lexer_advance(self));
    char esc = Lexer_advance(self);
    if (esc == 'n') {
    StringBuilder_append_char(&(sb), '\n');
} else if (esc == 't') {
    StringBuilder_append_char(&(sb), '\t');
} else if (esc == 'r') {
    StringBuilder_append_char(&(sb), '\r');
} else if (esc == '"') {
    StringBuilder_append_char(&(sb), '"');
} else if (esc == '\\') {
    StringBuilder_append_char(&(sb), '\\');
} else {
    StringBuilder_append_char(&(sb), '\\');
    StringBuilder_append_char(&(sb), esc);
}
} else {
    StringBuilder_append_char(&(sb), Lexer_advance(self));
}
}
    if (self->cursor < self->source_len) {
    (void)(Lexer_advance(self));
}
    const char* s = StringBuilder_to_str(&(sb));
    Lexer_emit(self, TokenType_STRING_LIT, (TokenValue){ .tag = TokenValue_tv_str_TAG, .payload = { .tv_str = { .v = StringPool_intern(self->pool, s) } } });
}
void Lexer_lex_char(Lexer* self) {
    (void)(Lexer_advance(self));
    char c = Lexer_advance(self);
    char ch = ((char)(0LL));
    if (c == '\\') {
    char esc = Lexer_advance(self);
    if (esc == 'n') {
    ch = '\n';
} else if (esc == 't') {
    ch = '\t';
} else if (esc == 'r') {
    ch = '\r';
} else if (esc == '\'') {
    ch = '\'';
} else if (esc == '\\') {
    ch = '\\';
} else {
    ch = esc;
}
} else {
    ch = c;
}
    (void)(Lexer_advance(self));
    Lexer_emit(self, TokenType_CHAR_LIT, (TokenValue){ .tag = TokenValue_tv_char_TAG, .payload = { .tv_char = { .v = ch } } });
}
int64_t Lexer_compute_indent(Lexer* self) {
    int64_t indent = 0LL;
    int64_t temp = self->cursor;
    bool done = false;
    bool has_content = false;
    while ((temp < self->source_len) && (!done)) {
    char c = (self->source)[temp];
    if (c == ' ') {
    indent = (indent + 1LL);
    temp = (temp + 1LL);
} else if (c == '\t') {
    indent = (indent + 4LL);
    temp = (temp + 1LL);
} else if (c == '\r') {
    temp = (temp + 1LL);
} else if (c == '\n') {
    indent = 0LL;
    temp = (temp + 1LL);
} else if (((c == '/') && ((temp + 1LL) < self->source_len)) && ((self->source)[(temp + 1LL)] == '/')) {
    while ((temp < self->source_len) && ((self->source)[temp] != '\n')) {
    temp = (temp + 1LL);
}
    indent = 0LL;
} else if (((c == '/') && ((temp + 1LL) < self->source_len)) && ((self->source)[(temp + 1LL)] == '*')) {
    temp = (temp + 2LL);
    while ((temp < self->source_len) && (!((((temp + 1LL) < self->source_len) && ((self->source)[temp] == '*')) && ((self->source)[(temp + 1LL)] == '/')))) {
    if ((self->source)[temp] == '\n') {
    indent = 0LL;
}
    temp = (temp + 1LL);
}
    if (temp < self->source_len) {
    temp = (temp + 2LL);
}
} else {
    has_content = true;
    done = true;
}
}
    if (has_content) {
    return indent;
}
    return (-1LL);
}
void Lexer_lex(Lexer* self) {
    bool is_line_start = true;
    while (self->cursor < self->source_len) {
    if (false) {
    int64_t indent = Lexer_compute_indent(self);
    if (indent >= 0LL) {
    if ((self->paren_depth == 0LL) && (self->brace_depth == 0LL)) {
    int64_t current = ArrayList_Int_get(self->indent_stack, (ArrayList_Int_length(self->indent_stack) - 1LL));
    if (indent > current) {
    ArrayList_Int_push(self->indent_stack, indent);
    Lexer_emit(self, TokenType_INDENT, (TokenValue){ .tag = TokenValue_tv_int_TAG, .payload = { .tv_int = { .v = indent } } });
} else if (indent < current) {
    while (indent < ArrayList_Int_get(self->indent_stack, (ArrayList_Int_length(self->indent_stack) - 1LL))) {
    (void)(ArrayList_Int_pop(self->indent_stack));
    Lexer_emit(self, TokenType_DEDENT, (TokenValue){ .tag = TokenValue_tv_int_TAG, .payload = { .tv_int = { .v = indent } } });
}
    if (indent != ArrayList_Int_get(self->indent_stack, (ArrayList_Int_length(self->indent_stack) - 1LL))) {
    self->has_error = true;
}
}
}
}
    is_line_start = false;
}
    Lexer_skip_whitespace(self);
    if (self->cursor < self->source_len) {
    char c = Lexer_peek(self, 0LL);
    if (c == '\n') {
    (void)(Lexer_advance(self));
    if (self->paren_depth == 0LL) {
    int64_t last = ArrayList_Token_length(self->tokens);
    if (last > 0LL) {
    Token last_tok = ArrayList_Token_get(self->tokens, (last - 1LL));
    if (((last_tok.tok_type != TokenType_NEWLINE) && (last_tok.tok_type != TokenType_INDENT)) && (last_tok.tok_type != TokenType_DEDENT)) {
    Lexer_emit(self, TokenType_NEWLINE, (TokenValue){ .tag = TokenValue_tv_none_TAG });
}
}
}
    is_line_start = true;
} else if (is_alpha(c) || (c == '_')) {
    Lexer_lex_identifier(self);
} else if (is_digit(c)) {
    Lexer_lex_number(self);
} else if (c == '"') {
    Lexer_lex_string(self);
} else if (c == '\'') {
    Lexer_lex_char(self);
} else if ((c == '-') && (Lexer_peek(self, 1LL) == '>')) {
    (void)(Lexer_advance(self));
    (void)(Lexer_advance(self));
    Lexer_emit_str(self, TokenType_ARROW, "->");
} else if ((c == '=') && (Lexer_peek(self, 1LL) == '>')) {
    (void)(Lexer_advance(self));
    (void)(Lexer_advance(self));
    Lexer_emit_str(self, TokenType_FAT_ARROW, "=>");
} else if ((c == '+') && (Lexer_peek(self, 1LL) == '=')) {
    (void)(Lexer_advance(self));
    (void)(Lexer_advance(self));
    Lexer_emit_str(self, TokenType_PLUS_ASSIGN, "+=");
} else if ((c == '-') && (Lexer_peek(self, 1LL) == '=')) {
    (void)(Lexer_advance(self));
    (void)(Lexer_advance(self));
    Lexer_emit_str(self, TokenType_MINUS_ASSIGN, "-=");
} else if ((c == '=') && (Lexer_peek(self, 1LL) == '=')) {
    (void)(Lexer_advance(self));
    (void)(Lexer_advance(self));
    Lexer_emit_str(self, TokenType_EQ, "==");
} else if ((c == '!') && (Lexer_peek(self, 1LL) == '=')) {
    (void)(Lexer_advance(self));
    (void)(Lexer_advance(self));
    Lexer_emit_str(self, TokenType_NE, "!=");
} else if ((c == '<') && (Lexer_peek(self, 1LL) == '=')) {
    (void)(Lexer_advance(self));
    (void)(Lexer_advance(self));
    Lexer_emit_str(self, TokenType_LE, "<=");
} else if ((c == '>') && (Lexer_peek(self, 1LL) == '=')) {
    (void)(Lexer_advance(self));
    (void)(Lexer_advance(self));
    Lexer_emit_str(self, TokenType_GE, ">=");
} else if ((c == '&') && (Lexer_peek(self, 1LL) == '&')) {
    (void)(Lexer_advance(self));
    (void)(Lexer_advance(self));
    Lexer_emit_str(self, TokenType_AND, "&&");
} else if ((c == '|') && (Lexer_peek(self, 1LL) == '|')) {
    (void)(Lexer_advance(self));
    (void)(Lexer_advance(self));
    Lexer_emit_str(self, TokenType_OR, "||");
} else if ((c == '<') && (Lexer_peek(self, 1LL) == '<')) {
    (void)(Lexer_advance(self));
    (void)(Lexer_advance(self));
    Lexer_emit_str(self, TokenType_LSHIFT, "<<");
} else if ((c == '>') && (Lexer_peek(self, 1LL) == '>')) {
    (void)(Lexer_advance(self));
    (void)(Lexer_advance(self));
    Lexer_emit_str(self, TokenType_RSHIFT, ">>");
} else if (((c == '.') && (Lexer_peek(self, 1LL) == '.')) && (Lexer_peek(self, 2LL) == '=')) {
    (void)(Lexer_advance(self));
    (void)(Lexer_advance(self));
    (void)(Lexer_advance(self));
    Lexer_emit_str(self, TokenType_DOTDOTEQ, "..=");
} else if ((c == '.') && (Lexer_peek(self, 1LL) == '.')) {
    (void)(Lexer_advance(self));
    (void)(Lexer_advance(self));
    Lexer_emit_str(self, TokenType_DOTDOT, "..");
} else if (c == '+') {
    (void)(Lexer_advance(self));
    Lexer_emit_str(self, TokenType_PLUS, "+");
} else if (c == '-') {
    (void)(Lexer_advance(self));
    Lexer_emit_str(self, TokenType_MINUS, "-");
} else if (c == '*') {
    (void)(Lexer_advance(self));
    Lexer_emit_str(self, TokenType_MUL, "*");
} else if (c == '/') {
    (void)(Lexer_advance(self));
    Lexer_emit_str(self, TokenType_DIV, "/");
} else if (c == '%') {
    (void)(Lexer_advance(self));
    Lexer_emit_str(self, TokenType_MOD, "%");
} else if (c == '=') {
    (void)(Lexer_advance(self));
    Lexer_emit_str(self, TokenType_ASSIGN, "=");
} else if (c == '<') {
    (void)(Lexer_advance(self));
    Lexer_emit_str(self, TokenType_LT, "<");
} else if (c == '>') {
    (void)(Lexer_advance(self));
    Lexer_emit_str(self, TokenType_GT, ">");
} else if (c == ':') {
    (void)(Lexer_advance(self));
    Lexer_emit_str(self, TokenType_COLON, ":");
} else if (c == ';') {
    (void)(Lexer_advance(self));
    Lexer_emit_str(self, TokenType_SEMICOLON, ";");
} else if (c == ',') {
    (void)(Lexer_advance(self));
    Lexer_emit_str(self, TokenType_COMMA, ",");
} else if (c == '(') {
    (void)(Lexer_advance(self));
    self->paren_depth = (self->paren_depth + 1LL);
    Lexer_emit_str(self, TokenType_LPAREN, "(");
} else if (c == ')') {
    (void)(Lexer_advance(self));
    if (self->paren_depth > 0LL) {
    self->paren_depth = (self->paren_depth - 1LL);
}
    Lexer_emit_str(self, TokenType_RPAREN, ")");
} else if (c == '[') {
    (void)(Lexer_advance(self));
    self->paren_depth = (self->paren_depth + 1LL);
    Lexer_emit_str(self, TokenType_LBRACKET, "[");
} else if (c == ']') {
    (void)(Lexer_advance(self));
    if (self->paren_depth > 0LL) {
    self->paren_depth = (self->paren_depth - 1LL);
}
    Lexer_emit_str(self, TokenType_RBRACKET, "]");
} else if (c == '{') {
    (void)(Lexer_advance(self));
    self->brace_depth = (self->brace_depth + 1LL);
    Lexer_emit_str(self, TokenType_LBRACE, "{");
} else if (c == '}') {
    (void)(Lexer_advance(self));
    if (self->brace_depth > 0LL) {
    self->brace_depth = (self->brace_depth - 1LL);
}
    Lexer_emit_str(self, TokenType_RBRACE, "}");
} else if (c == '&') {
    (void)(Lexer_advance(self));
    Lexer_emit_str(self, TokenType_AMP, "&");
} else if (c == '#') {
    (void)(Lexer_advance(self));
    Lexer_emit_str(self, TokenType_HASH, "#");
} else if (c == '!') {
    (void)(Lexer_advance(self));
    Lexer_emit_str(self, TokenType_NOT, "!");
} else if (c == '?') {
    (void)(Lexer_advance(self));
    Lexer_emit_str(self, TokenType_QUESTION, "?");
} else if (c == '^') {
    (void)(Lexer_advance(self));
    Lexer_emit_str(self, TokenType_BITXOR, "^");
} else if (c == '~') {
    (void)(Lexer_advance(self));
    Lexer_emit_str(self, TokenType_BITNOT, "~");
} else if (c == '|') {
    (void)(Lexer_advance(self));
    Lexer_emit_str(self, TokenType_PIPE, "|");
} else if (c == '.') {
    (void)(Lexer_advance(self));
    Lexer_emit_str(self, TokenType_DOT, ".");
} else {
    (void)(Lexer_advance(self));
    parser_err(self->source_file, self->source, "E0100", concatAlloc(concatAlloc("unexpected character '", char_to_str(c)), "'"), self->line, self->column);
    self->has_error = true;
}
}
}
    while (false) {
    (void)(ArrayList_Int_pop(self->indent_stack));
    Lexer_emit(self, TokenType_DEDENT, (TokenValue){ .tag = TokenValue_tv_int_TAG, .payload = { .tv_int = { .v = 0LL } } });
}
    Lexer_emit(self, TokenType_EOF, (TokenValue){ .tag = TokenValue_tv_none_TAG });
}
char char_at(const char* s, int64_t i) {
    return (s)[i];
}
bool is_digit(char c) {
    return ((c >= ((char)(48LL))) && (c <= ((char)(57LL))));
}
bool is_alpha(char c) {
    return (((c >= ((char)(97LL))) && (c <= ((char)(122LL)))) || ((c >= ((char)(65LL))) && (c <= ((char)(90LL)))));
}
bool is_alnum(char c) {
    return (is_digit(c) || is_alpha(c));
}
bool is_space(char c) {
    return ((((((c == ((char)(32LL))) || (c == ((char)(9LL)))) || (c == ((char)(10LL)))) || (c == ((char)(13LL)))) || (c == ((char)(11LL)))) || (c == ((char)(12LL))));
}
char to_upper(char c) {
    if ((c >= ((char)(97LL))) && (c <= ((char)(122LL)))) {
    return (c - ((char)(32LL)));
}
    return c;
}
char to_lower(char c) {
    if ((c >= ((char)(65LL))) && (c <= ((char)(90LL)))) {
    return (c + ((char)(32LL)));
}
    return c;
}
int64_t length(const char* s) {
    {
    return strlen(s);
}
}
StringBuilder StringBuilder_init(KaiAllocator* allocator) {
    StringBuilder self = (StringBuilder){0};
    self.len = 0LL;
    self.cap = 16LL;
    self.allocator = allocator;
    {
    self.data = (char*)(KaiAllocator_alloc(allocator, (self.cap * (int64_t)(sizeof(char))), 1LL));
}
    return self;
}
void StringBuilder_append_char(StringBuilder* self, char c) {
    if ((self->len + 1LL) >= self->cap) {
    int64_t new_cap = (self->cap * 2LL);
    {
    char* new_data = (char*)(KaiAllocator_alloc(self->allocator, (new_cap * (int64_t)(sizeof(char))), 1LL));
    int64_t i = 0LL;
    while (i < self->len) {
    (new_data)[i] = (self->data)[i];
    i = (i + 1LL);
}
    KaiAllocator_free(self->allocator, (uint8_t*)(self->data));
    self->data = new_data;
    self->cap = new_cap;
}
}
    (self->data)[self->len] = c;
    self->len = (self->len + 1LL);
    (self->data)[self->len] = ((char)(0LL));
}
void StringBuilder_append_str(StringBuilder* self, const char* s) {
    int64_t i = 0LL;
    while ((s)[i] != ((char)(0LL))) {
    StringBuilder_append_char(self, (s)[i]);
    i = (i + 1LL);
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
    KaiAllocator_free(self->allocator, (uint8_t*)(self->data));
}
}
const char* int_to_str(int64_t n) {
    {
    KaiAllocator allocator = (KaiAllocator){ .heads = (uint8_t*)(unsigned long long)(0LL), .used = 0LL };
    allocator = KaiAllocator_init();
    StringBuilder sb = StringBuilder_init(&(allocator));
    int64_t num = n;
    if (num < 0LL) {
    StringBuilder_append_char(&(sb), ((char)(45LL)));
    num = (-num);
}
    int64_t divisor = 1LL;
    int64_t tmp = num;
    while (tmp >= 10LL) {
    divisor = (divisor * 10LL);
    tmp = (tmp / 10LL);
}
    while (divisor > 0LL) {
    int64_t digit = ((num / divisor) % 10LL);
    StringBuilder_append_char(&(sb), ((char)((48LL + digit))));
    divisor = (divisor / 10LL);
}
    return StringBuilder_to_str(&(sb));
}
}
const char* char_to_str(char c) {
    {
    KaiAllocator allocator = (KaiAllocator){ .heads = (uint8_t*)(unsigned long long)(0LL), .used = 0LL };
    allocator = KaiAllocator_init();
    StringBuilder sb = StringBuilder_init(&(allocator));
    StringBuilder_append_char(&(sb), c);
    return StringBuilder_to_str(&(sb));
}
}
const char* substring(const char* s, int64_t start, int64_t end) {
    {
    int64_t len = strlen(s);
    int64_t real_end = end;
    if (real_end > len) {
    real_end = len;
}
    int64_t real_start = start;
    if (real_start < 0LL) {
    real_start = 0LL;
}
    if (real_start >= real_end) {
    char* empty = (char*)(malloc((size_t)(1LL)));
    if (empty != (char*)(unsigned long long)(0LL)) {
    (empty)[0LL] = ((char)(0LL));
}
    return (const char*)(empty);
}
    int64_t sub_len = (real_end - real_start);
    char* buf = (char*)(malloc((size_t)((sub_len + 1LL))));
    if (buf != (char*)(unsigned long long)(0LL)) {
    int64_t i = 0LL;
    while (i < sub_len) {
    (buf)[i] = (s)[(real_start + i)];
    i = (i + 1LL);
}
    (buf)[sub_len] = ((char)(0LL));
}
    return (const char*)(buf);
}
}
const char* tv_get_str(TokenValue val, StringPool* pool) {
    const char* result = "";
    if (val.tag == TokenValue_tv_str_TAG) {
    int64_t id = val.payload.tv_str.v;

    result = StringPool_get(pool, id);
} else {
    {
    printf("error[E0101]: internal error: unexpected token value type tag = %ld\n", val.tag);
    exit(1LL);
}
} 
    return result;
}
int64_t token_precedence(TokenType ttype) {
    if (ttype == TokenType_DOT) {
    return 9LL;
} else if (ttype == TokenType_LBRACKET) {
    return 9LL;
} else if (ttype == TokenType_AS) {
    return 8LL;
} else if (((ttype == TokenType_MUL) || (ttype == TokenType_DIV)) || (ttype == TokenType_MOD)) {
    return 7LL;
} else if ((ttype == TokenType_PLUS) || (ttype == TokenType_MINUS)) {
    return 6LL;
} else if ((ttype == TokenType_LSHIFT) || (ttype == TokenType_RSHIFT)) {
    return 5LL;
} else if ((((((ttype == TokenType_EQ) || (ttype == TokenType_NE)) || (ttype == TokenType_LT)) || (ttype == TokenType_LE)) || (ttype == TokenType_GT)) || (ttype == TokenType_GE)) {
    return 4LL;
} else if (ttype == TokenType_AMP) {
    return 5LL;
} else if (ttype == TokenType_BITXOR) {
    return 4LL;
} else if (ttype == TokenType_PIPE) {
    return 3LL;
} else if (ttype == TokenType_CATCH) {
    return 2LL;
} else if (ttype == TokenType_AND) {
    return 2LL;
} else if (ttype == TokenType_OR) {
    return 1LL;
} else if ((ttype == TokenType_DOTDOT) || (ttype == TokenType_DOTDOTEQ)) {
    return 4LL;
}
    return 0LL;
}
const char* token_op_str(TokenType ttype) {
    if (ttype == TokenType_PLUS) {
    return "+";
} else if (ttype == TokenType_MINUS) {
    return "-";
} else if (ttype == TokenType_MUL) {
    return "*";
} else if (ttype == TokenType_DIV) {
    return "/";
} else if (ttype == TokenType_MOD) {
    return "%";
} else if (ttype == TokenType_ASSIGN) {
    return "=";
} else if (ttype == TokenType_PLUS_ASSIGN) {
    return "+=";
} else if (ttype == TokenType_MINUS_ASSIGN) {
    return "-=";
} else if (ttype == TokenType_EQ) {
    return "==";
} else if (ttype == TokenType_NE) {
    return "!=";
} else if (ttype == TokenType_LT) {
    return "<";
} else if (ttype == TokenType_LE) {
    return "<=";
} else if (ttype == TokenType_GT) {
    return ">";
} else if (ttype == TokenType_GE) {
    return ">=";
} else if (ttype == TokenType_AND) {
    return "&&";
} else if (ttype == TokenType_OR) {
    return "||";
} else if (ttype == TokenType_PIPE) {
    return "|";
} else if (ttype == TokenType_BITXOR) {
    return "^";
} else if (ttype == TokenType_AMP) {
    return "&";
} else if (ttype == TokenType_LSHIFT) {
    return "<<";
} else if (ttype == TokenType_RSHIFT) {
    return ">>";
} else if (ttype == TokenType_DOTDOT) {
    return "..";
} else if (ttype == TokenType_DOTDOTEQ) {
    return "..=";
} else if (ttype == TokenType_DOT) {
    return ".";
}
    return "?";
}
const char* str_array_join(ArrayList_Str arr, const char* sep) {
    if (ArrayList_Str_length(&(arr)) == 0LL) {
    return "";
}
    const char* result = ArrayList_Str_get(&(arr), 0LL);
    int64_t i = 1LL;
    while (i < ArrayList_Str_length(&(arr))) {
    result = concatAlloc(concatAlloc(result, sep), ArrayList_Str_get(&(arr), i));
    i = (i + 1LL);
}
    return result;
}
void parser_err(const char* source_file, const char* source, const char* code, const char* msg, int64_t line, int64_t col) {
    printf("%s:%ld:%ld: error[%s]: %s\n", source_file, line, col, code, msg);
    if (line >= 0LL) {
    const char* line_text = get_source_line(source, (line - 1LL));
    if (strlen(line_text) > 0LL) {
    printf("    %s\n", line_text);
    const char* caret = "    ";
    int64_t ci = 0LL;
    while ((ci < col) && (ci < strlen(line_text))) {
    if ((line_text)[ci] == ((char)(9LL))) {
    caret = concatAlloc(caret, "\t");
} else {
    caret = concatAlloc(caret, " ");
}
    ci = (ci + 1LL);
}
    caret = concatAlloc(caret, "^");
    printf("%s\n", caret);
}
}
}
Parser Parser_init_with_pools(KaiAllocator* allocator, const char* source_file, ArrayList_Token* tokens, ArrayList_ExprNode* expr_pool, ArrayList_StmtNode* stmt_pool, ArrayList_PatternNode* pattern_pool, const char* source, StringPool* pool) {
    Parser self = (Parser){0};
    self.allocator = allocator;
    self.source_file = source_file;
    self.source = source;
    self.tokens = tokens;
    self.cursor = 0LL;
    self.pending_gt = false;
    self.pending_gt_line = 0LL;
    self.pending_gt_col = 0LL;
    self.expr_pool = expr_pool;
    self.stmt_pool = stmt_pool;
    self.pattern_pool = pattern_pool;
    self.stmt_line = 0LL;
    self.stmt_col = 0LL;
    self.pool = pool;
    return self;
}
Parser Parser_init(KaiAllocator* allocator, const char* source_file, ArrayList_Token* tokens, const char* source, StringPool* pool) {
    Parser self = (Parser){0};
    self.allocator = allocator;
    self.source_file = source_file;
    self.source = source;
    self.tokens = tokens;
    self.cursor = 0LL;
    self.pending_gt = false;
    self.pending_gt_line = 0LL;
    self.pending_gt_col = 0LL;
    self.pool = pool;
    {
    self.expr_pool = (ArrayList_ExprNode*)(KaiAllocator_alloc(allocator, sizeof(ArrayList_ExprNode), 8LL));
    self.stmt_pool = (ArrayList_StmtNode*)(KaiAllocator_alloc(allocator, sizeof(ArrayList_StmtNode), 8LL));
    self.pattern_pool = (ArrayList_PatternNode*)(KaiAllocator_alloc(allocator, sizeof(ArrayList_PatternNode), 8LL));
}
    *(self.expr_pool) = ArrayList_ExprNode_init(allocator);
    *(self.stmt_pool) = ArrayList_StmtNode_init(allocator);
    *(self.pattern_pool) = ArrayList_PatternNode_init(allocator);
    self.stmt_line = 0LL;
    self.stmt_col = 0LL;
    return self;
}
Token Parser_peek(Parser* self, int64_t offset) {
    if (self->pending_gt && (offset == 0LL)) {
    return (Token){ .tok_type = TokenType_GT, .value = (TokenValue){ .tag = TokenValue_tv_str_TAG, .payload = { .tv_str = { .v = StringPool_intern(self->pool, ">") } } }, .line = self->pending_gt_line, .column = self->pending_gt_col };
}
    int64_t pos = (self->cursor + offset);
    if (pos >= ArrayList_Token_length(self->tokens)) {
    return ArrayList_Token_get(self->tokens, (ArrayList_Token_length(self->tokens) - 1LL));
}
    return ArrayList_Token_get(self->tokens, pos);
}
Token Parser_advance(Parser* self) {
    if (self->pending_gt) {
    self->pending_gt = false;
    return (Token){ .tok_type = TokenType_GT, .value = (TokenValue){ .tag = TokenValue_tv_str_TAG, .payload = { .tv_str = { .v = StringPool_intern(self->pool, ">") } } }, .line = self->pending_gt_line, .column = self->pending_gt_col };
}
    Token tok = Parser_peek(self, 0LL);
    if (tok.tok_type != TokenType_EOF) {
    self->cursor = (self->cursor + 1LL);
}
    return tok;
}
bool Parser_match_token(Parser* self, TokenType ttype) {
    if (Parser_peek(self, 0LL).tok_type == ttype) {
    (void)(Parser_advance(self));
    return true;
}
    return false;
}
Token Parser_expect(Parser* self, TokenType ttype) {
    if (self->pending_gt) {
    if (ttype == TokenType_GT) {
    self->pending_gt = false;
    return (Token){ .tok_type = TokenType_GT, .value = (TokenValue){ .tag = TokenValue_tv_str_TAG, .payload = { .tv_str = { .v = StringPool_intern(self->pool, ">") } } }, .line = self->pending_gt_line, .column = self->pending_gt_col };
}
    self->pending_gt = false;
}
    Token tok = Parser_peek(self, 0LL);
    if ((ttype == TokenType_GT) && (tok.tok_type == TokenType_RSHIFT)) {
    (void)(Parser_advance(self));
    self->pending_gt = true;
    self->pending_gt_line = tok.line;
    self->pending_gt_col = (tok.column + 1LL);
    return (Token){ .tok_type = TokenType_GT, .value = (TokenValue){ .tag = TokenValue_tv_str_TAG, .payload = { .tv_str = { .v = StringPool_intern(self->pool, ">") } } }, .line = tok.line, .column = tok.column };
}
    if (tok.tok_type == ttype) {
    return Parser_advance(self);
}
    {
    parser_err(self->source_file, self->source, "E0101", concatAlloc(concatAlloc(concatAlloc("expected token type ", int_to_str(((int64_t)(ttype)))), " but found "), int_to_str(((int64_t)(tok.tok_type)))), tok.line, tok.column);
    exit(1LL);
}
    return tok;
}
void Parser_consume_newlines(Parser* self) {
    while (Parser_match_token(self, TokenType_NEWLINE)) {
}
}
void Parser_expect_end_of_statement(Parser* self) {
    Token tok = Parser_peek(self, 0LL);
    if ((((tok.tok_type == TokenType_RBRACE) || (tok.tok_type == TokenType_DEDENT)) || (tok.tok_type == TokenType_EOF)) || (tok.tok_type == TokenType_LBRACE)) {
    return;
}
    if (tok.tok_type == TokenType_SEMICOLON) {
    (void)(Parser_advance(self));
    return;
}
    (void)(Parser_expect(self, TokenType_NEWLINE));
}
bool Parser_is_generic_instantiation(Parser* self) {
    if (Parser_peek(self, 1LL).tok_type != TokenType_LT) {
    return false;
}
    int64_t offset = 2LL;
    int64_t nested = 1LL;
    bool done = false;
    while (!done) {
    Token tok = Parser_peek(self, offset);
    if (((tok.tok_type == TokenType_EOF) || (tok.tok_type == TokenType_NEWLINE)) || (tok.tok_type == TokenType_SEMICOLON)) {
    return false;
}
    TokenType tt = tok.tok_type;
    if ((((((((tt == TokenType_IDENTIFIER) || (tt == TokenType_MUL)) || (tt == TokenType_AMP)) || (tt == TokenType_LBRACKET)) || (tt == TokenType_RBRACKET)) || (tt == TokenType_COMMA)) || (tt == TokenType_QUESTION)) || (tt == TokenType_MUT)) {
    done = false;
} else if (tt == TokenType_LT) {
    nested = (nested + 1LL);
} else if (tt == TokenType_GT) {
    nested = (nested - 1LL);
    if (nested <= 0LL) {
    return ((Parser_peek(self, (offset + 1LL)).tok_type == TokenType_LPAREN) || (Parser_peek(self, (offset + 1LL)).tok_type == TokenType_DOT));
}
} else if (tt == TokenType_RSHIFT) {
    nested = (nested - 2LL);
    if (nested <= 0LL) {
    return ((Parser_peek(self, (offset + 1LL)).tok_type == TokenType_LPAREN) || (Parser_peek(self, (offset + 1LL)).tok_type == TokenType_DOT));
}
} else {
    return false;
}
    offset = (offset + 1LL);
}
    return false;
}
int64_t Parser_ex_literal(Parser* self, TokenValue val, const char* vkind) {
    ExprNode node = new_expr_node(ExprKind_ek_literal, Parser_peek(self, 0LL).line, Parser_peek(self, 0LL).column);
    node.lit_value = val;
    node.lit_vkind = vkind;
    ArrayList_ExprNode_push(self->expr_pool, node);
    return (ArrayList_ExprNode_length(self->expr_pool) - 1LL);
}
int64_t Parser_ex_ident(Parser* self, const char* name) {
    ExprNode node = new_expr_node(ExprKind_ek_identifier, Parser_peek(self, 0LL).line, Parser_peek(self, 0LL).column);
    node.ident_name = name;
    ArrayList_ExprNode_push(self->expr_pool, node);
    return (ArrayList_ExprNode_length(self->expr_pool) - 1LL);
}
int64_t Parser_ex_ident_with(Parser* self, const char* name, ArrayList_Str targs) {
    ExprNode node = new_expr_node(ExprKind_ek_identifier, Parser_peek(self, 0LL).line, Parser_peek(self, 0LL).column);
    node.ident_name = name;
    node.ident_type_args = targs;
    ArrayList_ExprNode_push(self->expr_pool, node);
    return (ArrayList_ExprNode_length(self->expr_pool) - 1LL);
}
int64_t Parser_ex_binop(Parser* self, const char* op, int64_t left, int64_t right) {
    ExprNode node = new_expr_node(ExprKind_ek_binary_op, Parser_peek(self, 0LL).line, Parser_peek(self, 0LL).column);
    node.binop_op = op;
    node.binop_left = left;
    node.binop_right = right;
    ArrayList_ExprNode_push(self->expr_pool, node);
    return (ArrayList_ExprNode_length(self->expr_pool) - 1LL);
}
int64_t Parser_ex_unop(Parser* self, const char* op, int64_t operand) {
    ExprNode node = new_expr_node(ExprKind_ek_unary_op, Parser_peek(self, 0LL).line, Parser_peek(self, 0LL).column);
    node.unop_op = op;
    node.unop_operand = operand;
    ArrayList_ExprNode_push(self->expr_pool, node);
    return (ArrayList_ExprNode_length(self->expr_pool) - 1LL);
}
int64_t Parser_ex_call(Parser* self, const char* name, ArrayList_Int args) {
    ExprNode node = new_expr_node(ExprKind_ek_func_call, Parser_peek(self, 0LL).line, Parser_peek(self, 0LL).column);
    node.func_name = name;
    node.func_args = args;
    ArrayList_ExprNode_push(self->expr_pool, node);
    return (ArrayList_ExprNode_length(self->expr_pool) - 1LL);
}
int64_t Parser_ex_call_with(Parser* self, const char* name, ArrayList_Int args, ArrayList_Str targs) {
    ExprNode node = new_expr_node(ExprKind_ek_func_call, Parser_peek(self, 0LL).line, Parser_peek(self, 0LL).column);
    node.func_name = name;
    node.func_args = args;
    node.func_type_args = targs;
    ArrayList_ExprNode_push(self->expr_pool, node);
    return (ArrayList_ExprNode_length(self->expr_pool) - 1LL);
}
int64_t Parser_ex_struct_init(Parser* self, const char* name, ArrayList_FieldInit fields) {
    ExprNode node = new_expr_node(ExprKind_ek_struct_init, Parser_peek(self, 0LL).line, Parser_peek(self, 0LL).column);
    node.struct_name = name;
    node.struct_fields = fields;
    ArrayList_ExprNode_push(self->expr_pool, node);
    return (ArrayList_ExprNode_length(self->expr_pool) - 1LL);
}
int64_t Parser_ex_field(Parser* self, int64_t expr, const char* field) {
    ExprNode node = new_expr_node(ExprKind_ek_field_access, Parser_peek(self, 0LL).line, Parser_peek(self, 0LL).column);
    node.field_expr = expr;
    node.field_name = field;
    ArrayList_ExprNode_push(self->expr_pool, node);
    return (ArrayList_ExprNode_length(self->expr_pool) - 1LL);
}
int64_t Parser_ex_method(Parser* self, int64_t expr, const char* method, ArrayList_Int args) {
    ExprNode node = new_expr_node(ExprKind_ek_method_call, Parser_peek(self, 0LL).line, Parser_peek(self, 0LL).column);
    node.meth_expr = expr;
    node.meth_name = method;
    node.meth_args = args;
    ArrayList_ExprNode_push(self->expr_pool, node);
    return (ArrayList_ExprNode_length(self->expr_pool) - 1LL);
}
int64_t Parser_ex_index(Parser* self, int64_t expr, int64_t idx) {
    ExprNode node = new_expr_node(ExprKind_ek_index, Parser_peek(self, 0LL).line, Parser_peek(self, 0LL).column);
    node.idx_expr = expr;
    node.idx_index = idx;
    ArrayList_ExprNode_push(self->expr_pool, node);
    return (ArrayList_ExprNode_length(self->expr_pool) - 1LL);
}
int64_t Parser_ex_check(Parser* self, int64_t expr) {
    ExprNode node = new_expr_node(ExprKind_ek_check, Parser_peek(self, 0LL).line, Parser_peek(self, 0LL).column);
    node.check_expr = expr;
    ArrayList_ExprNode_push(self->expr_pool, node);
    return (ArrayList_ExprNode_length(self->expr_pool) - 1LL);
}
int64_t Parser_ex_slice(Parser* self, int64_t expr, int64_t lower, int64_t upper, bool is_inclusive) {
    ExprNode node = new_expr_node(ExprKind_ek_slice, Parser_peek(self, 0LL).line, Parser_peek(self, 0LL).column);
    node.slice_expr = expr;
    node.slice_lower = lower;
    node.slice_upper = upper;
    node.slice_inclusive = is_inclusive;
    ArrayList_ExprNode_push(self->expr_pool, node);
    return (ArrayList_ExprNode_length(self->expr_pool) - 1LL);
}
int64_t Parser_ex_range(Parser* self, int64_t start, int64_t end, bool is_inclusive) {
    ExprNode node = new_expr_node(ExprKind_ek_range, Parser_peek(self, 0LL).line, Parser_peek(self, 0LL).column);
    node.range_start = start;
    node.range_end = end;
    node.range_inclusive = is_inclusive;
    ArrayList_ExprNode_push(self->expr_pool, node);
    return (ArrayList_ExprNode_length(self->expr_pool) - 1LL);
}
int64_t Parser_ex_array(Parser* self, ArrayList_Int elements) {
    ExprNode node = new_expr_node(ExprKind_ek_array, Parser_peek(self, 0LL).line, Parser_peek(self, 0LL).column);
    node.arr_elements = elements;
    ArrayList_ExprNode_push(self->expr_pool, node);
    return (ArrayList_ExprNode_length(self->expr_pool) - 1LL);
}
int64_t Parser_ex_tuple(Parser* self, ArrayList_Int elements) {
    ExprNode node = new_expr_node(ExprKind_ek_tuple, Parser_peek(self, 0LL).line, Parser_peek(self, 0LL).column);
    node.tup_elements = elements;
    ArrayList_ExprNode_push(self->expr_pool, node);
    return (ArrayList_ExprNode_length(self->expr_pool) - 1LL);
}
int64_t Parser_ex_borrow(Parser* self, int64_t expr, bool is_mut) {
    ExprNode node = new_expr_node(ExprKind_ek_borrow, Parser_peek(self, 0LL).line, Parser_peek(self, 0LL).column);
    node.borrow_expr = expr;
    node.borrow_mut = is_mut;
    ArrayList_ExprNode_push(self->expr_pool, node);
    return (ArrayList_ExprNode_length(self->expr_pool) - 1LL);
}
int64_t Parser_ex_deref(Parser* self, int64_t expr) {
    ExprNode node = new_expr_node(ExprKind_ek_deref, Parser_peek(self, 0LL).line, Parser_peek(self, 0LL).column);
    node.deref_expr = expr;
    ArrayList_ExprNode_push(self->expr_pool, node);
    return (ArrayList_ExprNode_length(self->expr_pool) - 1LL);
}
int64_t Parser_ex_try(Parser* self, int64_t expr) {
    ExprNode node = new_expr_node(ExprKind_ek_try, Parser_peek(self, 0LL).line, Parser_peek(self, 0LL).column);
    node.try_expr = expr;
    ArrayList_ExprNode_push(self->expr_pool, node);
    return (ArrayList_ExprNode_length(self->expr_pool) - 1LL);
}
int64_t Parser_ex_catch(Parser* self, int64_t expr, const char* var_name, int64_t fallback) {
    ExprNode node = new_expr_node(ExprKind_ek_catch, Parser_peek(self, 0LL).line, Parser_peek(self, 0LL).column);
    node.catch_expr = expr;
    node.catch_var = var_name;
    node.catch_fallback = fallback;
    ArrayList_ExprNode_push(self->expr_pool, node);
    return (ArrayList_ExprNode_length(self->expr_pool) - 1LL);
}
int64_t Parser_ex_asm(Parser* self, const char* code, bool is_volatile, ArrayList_AsmOutput outputs, ArrayList_AsmInput inputs, ArrayList_Str clobbers) {
    ExprNode node = new_expr_node(ExprKind_ek_asm, Parser_peek(self, 0LL).line, Parser_peek(self, 0LL).column);
    node.asm_code = code;
    node.asm_is_volatile = is_volatile;
    node.asm_outputs = outputs;
    node.asm_inputs = inputs;
    node.asm_clobbers = clobbers;
    ArrayList_ExprNode_push(self->expr_pool, node);
    return (ArrayList_ExprNode_length(self->expr_pool) - 1LL);
}
StmtNode Parser_mk_stmt_node(Parser* self, StmtKind kind) {
    return new_stmt_node(kind, self->stmt_line, self->stmt_col);
}
int64_t Parser_st_block(Parser* self, ArrayList_Int stmts) {
    StmtNode node = Parser_mk_stmt_node(self, StmtKind_sk_block);
    node.block_stmts = stmts;
    ArrayList_StmtNode_push(self->stmt_pool, node);
    return (ArrayList_StmtNode_length(self->stmt_pool) - 1LL);
}
int64_t Parser_st_error(Parser* self, const char* name, ArrayList_Str variants) {
    StmtNode node = Parser_mk_stmt_node(self, StmtKind_sk_error_decl);
    node.error_name = name;
    node.error_variants = variants;
    ArrayList_StmtNode_push(self->stmt_pool, node);
    return (ArrayList_StmtNode_length(self->stmt_pool) - 1LL);
}
int64_t Parser_st_var_decl(Parser* self, const char* name, const char* type_ann, int64_t value, bool is_mut) {
    StmtNode node = Parser_mk_stmt_node(self, StmtKind_sk_var_decl);
    node.vardecl_name = name;
    node.vardecl_type = type_ann;
    node.vardecl_value = value;
    node.vardecl_mut = is_mut;
    ArrayList_StmtNode_push(self->stmt_pool, node);
    return (ArrayList_StmtNode_length(self->stmt_pool) - 1LL);
}
int64_t Parser_st_assign(Parser* self, int64_t target, int64_t value, const char* op) {
    StmtNode node = Parser_mk_stmt_node(self, StmtKind_sk_assignment);
    node.assign_target = target;
    node.assign_value = value;
    node.assign_op = op;
    ArrayList_StmtNode_push(self->stmt_pool, node);
    return (ArrayList_StmtNode_length(self->stmt_pool) - 1LL);
}
int64_t Parser_st_func(Parser* self, const char* name, ArrayList_Param params, const char* ret_type, int64_t body, const char* cap, ArrayList_Str tp) {
    StmtNode node = Parser_mk_stmt_node(self, StmtKind_sk_func_decl);
    node.func_name = name;
    node.func_params = params;
    node.func_return_type = ret_type;
    node.func_body = body;
    node.func_capability = cap;
    node.func_type_params = tp;
    ArrayList_StmtNode_push(self->stmt_pool, node);
    return (ArrayList_StmtNode_length(self->stmt_pool) - 1LL);
}
int64_t Parser_st_struct(Parser* self, const char* name, ArrayList_StructField fields, ArrayList_Str tp, ArrayList_Int methods, ArrayList_Int impls) {
    StmtNode node = Parser_mk_stmt_node(self, StmtKind_sk_struct_decl);
    node.struct_name = name;
    node.struct_fields = fields;
    node.struct_type_params = tp;
    node.struct_methods = methods;
    node.struct_trait_impls = impls;
    ArrayList_StmtNode_push(self->stmt_pool, node);
    StmtNode ctor = Parser_mk_stmt_node(self, StmtKind_sk_func_decl);
    ctor.func_name = concatAlloc(name, "_new");
    ctor.func_params = ArrayList_Param_init(self->allocator);
    ctor.func_return_type = name;
    ctor.func_body = (-1LL);
    ctor.func_type_params = tp;
    ArrayList_StmtNode_push(self->stmt_pool, ctor);
    return (ArrayList_StmtNode_length(self->stmt_pool) - 1LL);
}
int64_t Parser_st_impl(Parser* self, const char* struct_name, const char* trait_name, ArrayList_Int methods) {
    StmtNode node = Parser_mk_stmt_node(self, StmtKind_sk_impl_block);
    node.impl_struct_name = struct_name;
    node.impl_trait_name = trait_name;
    node.impl_methods = methods;
    ArrayList_StmtNode_push(self->stmt_pool, node);
    return (ArrayList_StmtNode_length(self->stmt_pool) - 1LL);
}
int64_t Parser_st_trait(Parser* self, const char* name, ArrayList_Int methods) {
    StmtNode node = Parser_mk_stmt_node(self, StmtKind_sk_trait_decl);
    node.trait_name = name;
    node.trait_methods = methods;
    ArrayList_StmtNode_push(self->stmt_pool, node);
    return (ArrayList_StmtNode_length(self->stmt_pool) - 1LL);
}
int64_t Parser_st_enum(Parser* self, const char* name, ArrayList_Variant variants, ArrayList_Str tp) {
    StmtNode node = Parser_mk_stmt_node(self, StmtKind_sk_enum_decl);
    node.enum_name = name;
    node.enum_variants = variants;
    node.enum_type_params = tp;
    ArrayList_StmtNode_push(self->stmt_pool, node);
    return (ArrayList_StmtNode_length(self->stmt_pool) - 1LL);
}
int64_t Parser_st_match(Parser* self, int64_t expr, ArrayList_MatchCase cases) {
    StmtNode node = Parser_mk_stmt_node(self, StmtKind_sk_match);
    node.match_expr = expr;
    node.match_cases = cases;
    ArrayList_StmtNode_push(self->stmt_pool, node);
    return (ArrayList_StmtNode_length(self->stmt_pool) - 1LL);
}
int64_t Parser_st_unsafe(Parser* self, int64_t body) {
    StmtNode node = Parser_mk_stmt_node(self, StmtKind_sk_unsafe);
    node.unsafe_body = body;
    ArrayList_StmtNode_push(self->stmt_pool, node);
    return (ArrayList_StmtNode_length(self->stmt_pool) - 1LL);
}
int64_t Parser_st_extern(Parser* self, const char* name, ArrayList_Param params, const char* ret) {
    StmtNode node = Parser_mk_stmt_node(self, StmtKind_sk_extern);
    node.extern_name = name;
    node.extern_params = params;
    node.extern_return = ret;
    ArrayList_StmtNode_push(self->stmt_pool, node);
    return (ArrayList_StmtNode_length(self->stmt_pool) - 1LL);
}
int64_t Parser_st_if(Parser* self, int64_t cond, int64_t then_b, int64_t else_b) {
    StmtNode node = Parser_mk_stmt_node(self, StmtKind_sk_if);
    node.if_cond = cond;
    node.if_then = then_b;
    node.if_else = else_b;
    ArrayList_StmtNode_push(self->stmt_pool, node);
    return (ArrayList_StmtNode_length(self->stmt_pool) - 1LL);
}
int64_t Parser_st_if_let(Parser* self, const char* vname, int64_t expr, int64_t then_b, int64_t else_b) {
    StmtNode node = Parser_mk_stmt_node(self, StmtKind_sk_if_let);
    node.iflet_var = vname;
    node.iflet_expr = expr;
    node.iflet_then = then_b;
    node.iflet_else = else_b;
    ArrayList_StmtNode_push(self->stmt_pool, node);
    return (ArrayList_StmtNode_length(self->stmt_pool) - 1LL);
}
int64_t Parser_st_while(Parser* self, int64_t cond, int64_t body) {
    StmtNode node = Parser_mk_stmt_node(self, StmtKind_sk_while);
    node.while_cond = cond;
    node.while_body = body;
    ArrayList_StmtNode_push(self->stmt_pool, node);
    return (ArrayList_StmtNode_length(self->stmt_pool) - 1LL);
}
int64_t Parser_st_for(Parser* self, const char* var_name, int64_t start, int64_t end, bool inc, int64_t body) {
    StmtNode node = Parser_mk_stmt_node(self, StmtKind_sk_for);
    node.for_var = var_name;
    node.for_start = start;
    node.for_end = end;
    node.for_inclusive = inc;
    node.for_body = body;
    ArrayList_StmtNode_push(self->stmt_pool, node);
    return (ArrayList_StmtNode_length(self->stmt_pool) - 1LL);
}
int64_t Parser_st_return(Parser* self, int64_t value) {
    StmtNode node = Parser_mk_stmt_node(self, StmtKind_sk_return);
    node.return_value = value;
    ArrayList_StmtNode_push(self->stmt_pool, node);
    return (ArrayList_StmtNode_length(self->stmt_pool) - 1LL);
}
int64_t Parser_st_expr(Parser* self, int64_t expr) {
    StmtNode node = Parser_mk_stmt_node(self, StmtKind_sk_expr);
    node.expr_stmt = expr;
    ArrayList_StmtNode_push(self->stmt_pool, node);
    return (ArrayList_StmtNode_length(self->stmt_pool) - 1LL);
}
int64_t Parser_st_defer(Parser* self, int64_t body) {
    StmtNode node = Parser_mk_stmt_node(self, StmtKind_sk_defer);
    node.defer_body = body;
    ArrayList_StmtNode_push(self->stmt_pool, node);
    return (ArrayList_StmtNode_length(self->stmt_pool) - 1LL);
}
int64_t Parser_st_errdefer(Parser* self, int64_t body) {
    StmtNode node = Parser_mk_stmt_node(self, StmtKind_sk_errdefer);
    node.errdefer_body = body;
    ArrayList_StmtNode_push(self->stmt_pool, node);
    return (ArrayList_StmtNode_length(self->stmt_pool) - 1LL);
}
int64_t Parser_st_break(Parser* self) {
    StmtNode node = Parser_mk_stmt_node(self, StmtKind_sk_break);
    ArrayList_StmtNode_push(self->stmt_pool, node);
    return (ArrayList_StmtNode_length(self->stmt_pool) - 1LL);
}
int64_t Parser_st_continue(Parser* self) {
    StmtNode node = Parser_mk_stmt_node(self, StmtKind_sk_continue);
    ArrayList_StmtNode_push(self->stmt_pool, node);
    return (ArrayList_StmtNode_length(self->stmt_pool) - 1LL);
}
int64_t Parser_st_import(Parser* self, ArrayList_Str path, const char* alias) {
    StmtNode node = Parser_mk_stmt_node(self, StmtKind_sk_import);
    node.import_path = path;
    node.import_alias = alias;
    ArrayList_StmtNode_push(self->stmt_pool, node);
    return (ArrayList_StmtNode_length(self->stmt_pool) - 1LL);
}
int64_t Parser_st_cimport(Parser* self, const char* header, const char* alias) {
    StmtNode node = Parser_mk_stmt_node(self, StmtKind_sk_cimport);
    node.cimport_header = header;
    node.cimport_alias = alias;
    ArrayList_StmtNode_push(self->stmt_pool, node);
    return (ArrayList_StmtNode_length(self->stmt_pool) - 1LL);
}
int64_t Parser_parse_program(Parser* self) {
    Parser_consume_newlines(self);
    ArrayList_Int stmts = ArrayList_Int_init(self->allocator);
    while (Parser_peek(self, 0LL).tok_type != TokenType_EOF) {
    int64_t stmt = Parser_parse_statement(self);
    if (stmt >= 0LL) {
    ArrayList_Int_push(&(stmts), stmt);
}
    Parser_consume_newlines(self);
}
    return Parser_st_block(self, stmts);
}
int64_t Parser_parse_statement(Parser* self) {
    Parser_consume_newlines(self);
    Token tok = Parser_peek(self, 0LL);
    self->stmt_line = tok.line;
    self->stmt_col = tok.column;
    bool is_public = false;
    if (tok.tok_type == TokenType_PUB) {
    (void)(Parser_advance(self));
    is_public = true;
    tok = Parser_peek(self, 0LL);
}
    if (tok.tok_type == TokenType_LET) {
    return Parser_parse_var_decl(self, false);
} else if (tok.tok_type == TokenType_VAR) {
    return Parser_parse_var_decl(self, true);
} else if (tok.tok_type == TokenType_ERROR) {
    return Parser_parse_error_decl(self);
} else if (tok.tok_type == TokenType_FUNC) {
    int64_t idx = Parser_parse_func_decl(self);
    if (is_public) {
    StmtNode n = ArrayList_StmtNode_get(self->stmt_pool, idx);
    n.func_public = true;
    ArrayList_StmtNode_set(self->stmt_pool, idx, n);
}
    return idx;
} else if (tok.tok_type == TokenType_STRUCT) {
    int64_t idx = Parser_parse_struct_decl(self);
    if (is_public) {
    StmtNode n = ArrayList_StmtNode_get(self->stmt_pool, idx);
    n.struct_public = true;
    ArrayList_StmtNode_set(self->stmt_pool, idx, n);
}
    return idx;
} else if (tok.tok_type == TokenType_IMPL) {
    return Parser_parse_impl_block(self);
} else if (tok.tok_type == TokenType_ENUM) {
    int64_t idx = Parser_parse_enum_decl(self);
    if (is_public) {
    StmtNode n = ArrayList_StmtNode_get(self->stmt_pool, idx);
    n.enum_public = true;
    ArrayList_StmtNode_set(self->stmt_pool, idx, n);
}
    return idx;
} else if (tok.tok_type == TokenType_MATCH) {
    return Parser_parse_match_stmt(self);
} else if (tok.tok_type == TokenType_UNSAFE) {
    return Parser_parse_unsafe_block(self);
} else if (tok.tok_type == TokenType_EXTERN) {
    return Parser_parse_extern_decl(self);
} else if (tok.tok_type == TokenType_IF) {
    return Parser_parse_if_stmt(self);
} else if (tok.tok_type == TokenType_WHILE) {
    return Parser_parse_while_stmt(self);
} else if (tok.tok_type == TokenType_FOR) {
    return Parser_parse_for_stmt(self);
} else if (tok.tok_type == TokenType_RETURN) {
    return Parser_parse_return_stmt(self);
} else if (tok.tok_type == TokenType_DEFER) {
    return Parser_parse_defer_stmt(self);
} else if (tok.tok_type == TokenType_ERRDEFER) {
    return Parser_parse_errdefer_stmt(self);
} else if (tok.tok_type == TokenType_BREAK) {
    return Parser_parse_break_stmt(self);
} else if (tok.tok_type == TokenType_CONTINUE) {
    return Parser_parse_continue_stmt(self);
} else if (tok.tok_type == TokenType_USE) {
    return Parser_parse_import_stmt(self);
} else if (tok.tok_type == TokenType_IMPORT) {
    return Parser_parse_import_stmt_new(self);
} else if (tok.tok_type == TokenType_CIMPORT) {
    return Parser_parse_cimport_stmt(self);
} else if (tok.tok_type == TokenType_TRAIT) {
    int64_t idx = Parser_parse_trait_decl(self);
    if (is_public) {
    StmtNode n = ArrayList_StmtNode_get(self->stmt_pool, idx);
    n.trait_public = true;
    ArrayList_StmtNode_set(self->stmt_pool, idx, n);
}
    return idx;
} else {
    return Parser_parse_expr_or_assignment_stmt(self);
}
}
const char* Parser_parse_type(Parser* self) {
    const char* base_type = Parser_parse_base_type(self);
    if (Parser_match_token(self, TokenType_NOT)) {
    const char* error_set = Parser_parse_type(self);
    return concatAlloc(concatAlloc(base_type, "!"), error_set);
}
    return base_type;
}
const char* Parser_parse_base_type(Parser* self) {
    if (Parser_match_token(self, TokenType_OWN)) {
    const char* inner = Parser_parse_type(self);
    return concatAlloc("own ", inner);
} else if (Parser_match_token(self, TokenType_QUESTION)) {
    return concatAlloc("?", Parser_parse_type(self));
} else if (Parser_match_token(self, TokenType_AMP)) {
    bool is_mut = false;
    if (Parser_match_token(self, TokenType_MUT)) {
    is_mut = true;
}
    const char* inner = Parser_parse_type(self);
    if (is_mut) {
    return concatAlloc("*mut ", inner);
}
    return concatAlloc("*", inner);
} else if (Parser_match_token(self, TokenType_MUL)) {
    bool is_mut = false;
    if (Parser_match_token(self, TokenType_MUT)) {
    is_mut = true;
}
    const char* inner = Parser_parse_type(self);
    if (is_mut) {
    return concatAlloc("*mut ", inner);
}
    return concatAlloc("*", inner);
} else if (Parser_match_token(self, TokenType_LBRACKET)) {
    (void)(Parser_expect(self, TokenType_RBRACKET));
    return concatAlloc("[]", Parser_parse_type(self));
} else if (Parser_match_token(self, TokenType_LPAREN)) {
    ArrayList_Str types = ArrayList_Str_init(self->allocator);
    if (Parser_peek(self, 0LL).tok_type != TokenType_RPAREN) {
    bool done = false;
    while (!done) {
    ArrayList_Str_push(&(types), Parser_parse_type(self));
    if (!Parser_match_token(self, TokenType_COMMA)) {
    done = true;
}
}
}
    (void)(Parser_expect(self, TokenType_RPAREN));
    return concatAlloc(concatAlloc("(", str_array_join(types, ", ")), ")");
} else {
    const char* name = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value, self->pool);
    if (Parser_peek(self, 0LL).tok_type == TokenType_LT) {
    (void)(Parser_advance(self));
    ArrayList_Str type_args = ArrayList_Str_init(self->allocator);
    bool done = false;
    while (!done) {
    ArrayList_Str_push(&(type_args), Parser_parse_type(self));
    if (!Parser_match_token(self, TokenType_COMMA)) {
    done = true;
}
}
    (void)(Parser_expect(self, TokenType_GT));
    return concatAlloc(concatAlloc(concatAlloc(name, "<"), str_array_join(type_args, ", ")), ">");
}
    return name;
}
}
ArrayList_Str Parser_parse_generic_params(Parser* self) {
    ArrayList_Str type_params = ArrayList_Str_init(self->allocator);
    if (Parser_peek(self, 0LL).tok_type == TokenType_LT) {
    (void)(Parser_advance(self));
    bool done = false;
    while (!done) {
    const char* tp_name = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value, self->pool);
    if (Parser_match_token(self, TokenType_COLON)) {
    ArrayList_Str_push(&(type_params), concatAlloc(concatAlloc(tp_name, ":"), tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value, self->pool)));
} else {
    ArrayList_Str_push(&(type_params), tp_name);
}
    if (!Parser_match_token(self, TokenType_COMMA)) {
    done = true;
}
}
    (void)(Parser_expect(self, TokenType_GT));
}
    return type_params;
}
int64_t Parser_parse_var_decl(Parser* self, bool is_mutable) {
    (void)(Parser_advance(self));
    if (Parser_peek(self, 0LL).tok_type == TokenType_LPAREN) {
    (void)(Parser_advance(self));
    ArrayList_Str names = ArrayList_Str_init(self->allocator);
    bool done = false;
    while (!done) {
    ArrayList_Str_push(&(names), tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value, self->pool));
    if (!Parser_match_token(self, TokenType_COMMA)) {
    done = true;
}
}
    (void)(Parser_expect(self, TokenType_RPAREN));
    (void)(Parser_expect(self, TokenType_ASSIGN));
    int64_t val_expr = Parser_parse_expression(self, 0LL);
    Parser_expect_end_of_statement(self);
    return Parser_st_var_decl(self, str_array_join(names, ","), "", val_expr, is_mutable);
}
    const char* name = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value, self->pool);
    const char* type_ann = "";
    if (Parser_match_token(self, TokenType_COLON)) {
    type_ann = Parser_parse_type(self);
}
    (void)(Parser_expect(self, TokenType_ASSIGN));
    int64_t val_expr = Parser_parse_expression(self, 0LL);
    Parser_expect_end_of_statement(self);
    return Parser_st_var_decl(self, name, type_ann, val_expr, is_mutable);
}
int64_t Parser_parse_func_decl(Parser* self) {
    (void)(Parser_advance(self));
    const char* name = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value, self->pool);
    ArrayList_Str type_params = Parser_parse_generic_params(self);
    (void)(Parser_expect(self, TokenType_LPAREN));
    ArrayList_Param params = ArrayList_Param_init(self->allocator);
    if (Parser_peek(self, 0LL).tok_type != TokenType_RPAREN) {
    bool done = false;
    while (!done) {
    const char* param_name = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value, self->pool);
    const char* param_type = "";
    if ((strcmp(param_name, "self") == 0) && (Parser_peek(self, 0LL).tok_type != TokenType_COLON)) {
    param_type = "self";
} else {
    (void)(Parser_expect(self, TokenType_COLON));
    param_type = Parser_parse_type(self);
}
    ArrayList_Param_push(&(params), (Param){ .name = param_name, .ptype = param_type });
    if (!Parser_match_token(self, TokenType_COMMA)) {
    done = true;
}
}
}
    (void)(Parser_expect(self, TokenType_RPAREN));
    const char* return_type = "";
    if (Parser_match_token(self, TokenType_ARROW)) {
    return_type = Parser_parse_type(self);
} else {
    Token next_tok = Parser_peek(self, 0LL);
    if (((((next_tok.tok_type == TokenType_IDENTIFIER) || (next_tok.tok_type == TokenType_LPAREN)) || (next_tok.tok_type == TokenType_MUL)) || (next_tok.tok_type == TokenType_AMP)) || (next_tok.tok_type == TokenType_LBRACKET)) {
    return_type = Parser_parse_type(self);
}
}
    const char* capability = "";
    if (Parser_match_token(self, TokenType_HASH)) {
    capability = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value, self->pool);
}
    Parser_expect_end_of_statement(self);
    int64_t saved_line = self->stmt_line;
    int64_t saved_col = self->stmt_col;
    int64_t body = Parser_parse_block(self);
    self->stmt_line = saved_line;
    self->stmt_col = saved_col;
    return Parser_st_func(self, name, params, return_type, body, capability, type_params);
}
int64_t Parser_parse_struct_decl(Parser* self) {
    (void)(Parser_advance(self));
    const char* name = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value, self->pool);
    ArrayList_Str type_params = Parser_parse_generic_params(self);
    Parser_expect_end_of_statement(self);
    (void)(Parser_expect(self, TokenType_LBRACE));
    ArrayList_StructField fields = ArrayList_StructField_init(self->allocator);
    ArrayList_Int methods = ArrayList_Int_init(self->allocator);
    ArrayList_Int trait_impls = ArrayList_Int_init(self->allocator);
    Parser_consume_newlines(self);
    while ((Parser_peek(self, 0LL).tok_type != TokenType_RBRACE) && (Parser_peek(self, 0LL).tok_type != TokenType_EOF)) {
    if (Parser_peek(self, 0LL).tok_type == TokenType_FUNC) {
    ArrayList_Int_push(&(methods), Parser_parse_func_decl(self));
} else if (Parser_peek(self, 0LL).tok_type == TokenType_IMPL) {
    (void)(Parser_advance(self));
    const char* trait_name = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value, self->pool);
    Parser_expect_end_of_statement(self);
    (void)(Parser_expect(self, TokenType_LBRACE));
    ArrayList_Int impl_methods = ArrayList_Int_init(self->allocator);
    Parser_consume_newlines(self);
    while ((Parser_peek(self, 0LL).tok_type != TokenType_RBRACE) && (Parser_peek(self, 0LL).tok_type != TokenType_EOF)) {
    ArrayList_Int_push(&(impl_methods), Parser_parse_func_decl(self));
    Parser_consume_newlines(self);
}
    (void)(Parser_expect(self, TokenType_RBRACE));
    ArrayList_Int_push(&(trait_impls), Parser_st_impl(self, name, trait_name, impl_methods));
} else {
    const char* fname = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value, self->pool);
    (void)(Parser_expect(self, TokenType_COLON));
    ArrayList_StructField_push(&(fields), (StructField){ .name = fname, .ftype = Parser_parse_type(self) });
    Parser_expect_end_of_statement(self);
}
    Parser_consume_newlines(self);
}
    (void)(Parser_expect(self, TokenType_RBRACE));
    return Parser_st_struct(self, name, fields, type_params, methods, trait_impls);
}
int64_t Parser_parse_impl_block(Parser* self) {
    (void)(Parser_advance(self));
    const char* first_name = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value, self->pool);
    const char* struct_name = "";
    const char* trait_name = "";
    if (Parser_peek(self, 0LL).tok_type == TokenType_FOR) {
    (void)(Parser_advance(self));
    trait_name = first_name;
    struct_name = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value, self->pool);
} else {
    struct_name = first_name;
}
    Parser_expect_end_of_statement(self);
    (void)(Parser_expect(self, TokenType_LBRACE));
    ArrayList_Int methods = ArrayList_Int_init(self->allocator);
    Parser_consume_newlines(self);
    while ((Parser_peek(self, 0LL).tok_type != TokenType_RBRACE) && (Parser_peek(self, 0LL).tok_type != TokenType_EOF)) {
    ArrayList_Int_push(&(methods), Parser_parse_func_decl(self));
    Parser_consume_newlines(self);
}
    (void)(Parser_expect(self, TokenType_RBRACE));
    return Parser_st_impl(self, struct_name, trait_name, methods);
}
int64_t Parser_parse_trait_decl(Parser* self) {
    (void)(Parser_advance(self));
    const char* name = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value, self->pool);
    Parser_expect_end_of_statement(self);
    (void)(Parser_expect(self, TokenType_LBRACE));
    ArrayList_Int methods = ArrayList_Int_init(self->allocator);
    Parser_consume_newlines(self);
    while ((Parser_peek(self, 0LL).tok_type != TokenType_RBRACE) && (Parser_peek(self, 0LL).tok_type != TokenType_EOF)) {
    ArrayList_Int_push(&(methods), Parser_parse_func_decl(self));
    Parser_consume_newlines(self);
}
    (void)(Parser_expect(self, TokenType_RBRACE));
    return Parser_st_trait(self, name, methods);
}
int64_t Parser_parse_enum_decl(Parser* self) {
    (void)(Parser_advance(self));
    const char* name = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value, self->pool);
    ArrayList_Str type_params = Parser_parse_generic_params(self);
    Parser_expect_end_of_statement(self);
    (void)(Parser_expect(self, TokenType_LBRACE));
    ArrayList_Variant variants = ArrayList_Variant_init(self->allocator);
    Parser_consume_newlines(self);
    while ((Parser_peek(self, 0LL).tok_type != TokenType_RBRACE) && (Parser_peek(self, 0LL).tok_type != TokenType_EOF)) {
    (void)(Parser_expect(self, TokenType_CASE));
    const char* v_name = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value, self->pool);
    ArrayList_Param v_params = ArrayList_Param_init(self->allocator);
    int64_t unnamed_count = 0LL;
    if (Parser_match_token(self, TokenType_LPAREN)) {
    if (Parser_peek(self, 0LL).tok_type != TokenType_RPAREN) {
    bool done = false;
    while (!done) {
    const char* pname_or_type = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value, self->pool);
    if (Parser_peek(self, 0LL).tok_type == TokenType_COLON) {
    (void)(Parser_advance(self));
    ArrayList_Param_push(&(v_params), (Param){ .name = pname_or_type, .ptype = Parser_parse_type(self) });
} else {
    const char* pname = "value";
    if (unnamed_count > 0LL) {
    pname = "value0";
}
    unnamed_count = (unnamed_count + 1LL);
    ArrayList_Param_push(&(v_params), (Param){ .name = pname, .ptype = pname_or_type });
}
    if (!Parser_match_token(self, TokenType_COMMA)) {
    done = true;
}
}
}
    (void)(Parser_expect(self, TokenType_RPAREN));
}
    ArrayList_Variant_push(&(variants), (Variant){ .vname = v_name, .params = v_params });
    Parser_expect_end_of_statement(self);
    Parser_consume_newlines(self);
}
    (void)(Parser_expect(self, TokenType_RBRACE));
    return Parser_st_enum(self, name, variants, type_params);
}
int64_t Parser_parse_error_decl(Parser* self) {
    (void)(Parser_advance(self));
    const char* name = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value, self->pool);
    Parser_expect_end_of_statement(self);
    (void)(Parser_expect(self, TokenType_LBRACE));
    ArrayList_Str variants = ArrayList_Str_init(self->allocator);
    Parser_consume_newlines(self);
    while ((Parser_peek(self, 0LL).tok_type != TokenType_RBRACE) && (Parser_peek(self, 0LL).tok_type != TokenType_EOF)) {
    if (Parser_match_token(self, TokenType_CASE)) {
    (void)(0LL);
}
    const char* v_name = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value, self->pool);
    ArrayList_Str_push(&(variants), v_name);
    Parser_expect_end_of_statement(self);
    Parser_consume_newlines(self);
}
    (void)(Parser_expect(self, TokenType_RBRACE));
    return Parser_st_error(self, name, variants);
}
int64_t Parser_parse_match_stmt(Parser* self) {
    (void)(Parser_advance(self));
    int64_t expr = Parser_parse_expression(self, 0LL);
    Parser_expect_end_of_statement(self);
    (void)(Parser_expect(self, TokenType_LBRACE));
    ArrayList_MatchCase cases = ArrayList_MatchCase_init(self->allocator);
    Parser_consume_newlines(self);
    int64_t saved_line = self->stmt_line;
    int64_t saved_col = self->stmt_col;
    while ((Parser_peek(self, 0LL).tok_type != TokenType_RBRACE) && (Parser_peek(self, 0LL).tok_type != TokenType_EOF)) {
    (void)(Parser_expect(self, TokenType_CASE));
    int64_t pattern = Parser_parse_pattern(self);
    (void)(Parser_expect(self, TokenType_FAT_ARROW));
    Parser_consume_newlines(self);
    int64_t body = (-1LL);
    if (Parser_peek(self, 0LL).tok_type == TokenType_LBRACE) {
    body = Parser_parse_block(self);
} else {
    ArrayList_Int stmts = ArrayList_Int_init(self->allocator);
    ArrayList_Int_push(&(stmts), Parser_parse_statement(self));
    body = Parser_st_block(self, stmts);
}
    ArrayList_MatchCase_push(&(cases), (MatchCase){ .pattern = pattern, .body = body });
    Parser_consume_newlines(self);
}
    (void)(Parser_expect(self, TokenType_RBRACE));
    self->stmt_line = saved_line;
    self->stmt_col = saved_col;
    return Parser_st_match(self, expr, cases);
}
int64_t Parser_parse_pattern(Parser* self) {
    Token tok = Parser_peek(self, 0LL);
    if (tok.tok_type == TokenType_DOT) {
    (void)(Parser_advance(self));
    const char* v_name = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value, self->pool);
    ArrayList_Str bindings = ArrayList_Str_init(self->allocator);
    if (Parser_match_token(self, TokenType_LPAREN)) {
    if (Parser_peek(self, 0LL).tok_type != TokenType_RPAREN) {
    bool done = false;
    while (!done) {
    ArrayList_Str_push(&(bindings), tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value, self->pool));
    if (!Parser_match_token(self, TokenType_COMMA)) {
    done = true;
}
}
}
    (void)(Parser_expect(self, TokenType_RPAREN));
}
    PatternNode node = new_pattern_node(PatternKind_pk_variant);
    node.variant_name = v_name;
    node.bindings = bindings;
    return Parser_add_pattern(self, node);
} else if (tok.tok_type == TokenType_ELSE) {
    (void)(Parser_advance(self));
    return Parser_add_pattern(self, new_pattern_node(PatternKind_pk_else));
} else if (((((tok.tok_type == TokenType_INT_LIT) || (tok.tok_type == TokenType_FLOAT_LIT)) || (tok.tok_type == TokenType_BOOL_LIT)) || (tok.tok_type == TokenType_STRING_LIT)) || (tok.tok_type == TokenType_CHAR_LIT)) {
    (void)(Parser_advance(self));
    PatternNode node = new_pattern_node(PatternKind_pk_literal);
    node.lit_value = tok.value;
    return Parser_add_pattern(self, node);
} else {
    {
    parser_err(self->source_file, self->source, "E0101", "unexpected token in pattern", tok.line, tok.column);
    exit(1LL);
}
    return (-1LL);
}
}
int64_t Parser_add_pattern(Parser* self, PatternNode p) {
    ArrayList_PatternNode_push(self->pattern_pool, p);
    return (ArrayList_PatternNode_length(self->pattern_pool) - 1LL);
}
int64_t Parser_parse_unsafe_block(Parser* self) {
    (void)(Parser_advance(self));
    Parser_expect_end_of_statement(self);
    int64_t saved_line = self->stmt_line;
    int64_t saved_col = self->stmt_col;
    int64_t body = Parser_parse_block(self);
    self->stmt_line = saved_line;
    self->stmt_col = saved_col;
    return Parser_st_unsafe(self, body);
}
int64_t Parser_parse_extern_decl(Parser* self) {
    (void)(Parser_advance(self));
    (void)(Parser_expect(self, TokenType_FUNC));
    const char* name = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value, self->pool);
    (void)(Parser_expect(self, TokenType_LPAREN));
    ArrayList_Param params = ArrayList_Param_init(self->allocator);
    if (Parser_peek(self, 0LL).tok_type != TokenType_RPAREN) {
    bool done = false;
    while (!done) {
    const char* param_name = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value, self->pool);
    (void)(Parser_expect(self, TokenType_COLON));
    ArrayList_Param_push(&(params), (Param){ .name = param_name, .ptype = Parser_parse_type(self) });
    if (!Parser_match_token(self, TokenType_COMMA)) {
    done = true;
}
}
}
    (void)(Parser_expect(self, TokenType_RPAREN));
    const char* return_type = "";
    if (Parser_match_token(self, TokenType_ARROW)) {
    return_type = Parser_parse_type(self);
} else {
    Token next_tok = Parser_peek(self, 0LL);
    if (((((next_tok.tok_type == TokenType_IDENTIFIER) || (next_tok.tok_type == TokenType_LPAREN)) || (next_tok.tok_type == TokenType_MUL)) || (next_tok.tok_type == TokenType_AMP)) || (next_tok.tok_type == TokenType_LBRACKET)) {
    return_type = Parser_parse_type(self);
}
}
    Parser_expect_end_of_statement(self);
    return Parser_st_extern(self, name, params, return_type);
}
int64_t Parser_parse_if_stmt(Parser* self) {
    (void)(Parser_advance(self));
    int64_t saved_line = self->stmt_line;
    int64_t saved_col = self->stmt_col;
    if (Parser_peek(self, 0LL).tok_type == TokenType_LET) {
    (void)(Parser_advance(self));
    const char* var_name = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value, self->pool);
    (void)(Parser_expect(self, TokenType_ASSIGN));
    int64_t cond_expr = Parser_parse_expression(self, 0LL);
    Parser_expect_end_of_statement(self);
    int64_t then_branch = Parser_parse_block(self);
    int64_t else_branch = (-1LL);
    Parser_consume_newlines(self);
    if (Parser_peek(self, 0LL).tok_type == TokenType_ELSE) {
    (void)(Parser_advance(self));
    if (Parser_peek(self, 0LL).tok_type == TokenType_IF) {
    ArrayList_Int stmts = ArrayList_Int_init(self->allocator);
    ArrayList_Int_push(&(stmts), Parser_parse_if_stmt(self));
    else_branch = Parser_st_block(self, stmts);
} else {
    Parser_expect_end_of_statement(self);
    else_branch = Parser_parse_block(self);
}
}
    self->stmt_line = saved_line;
    self->stmt_col = saved_col;
    return Parser_st_if_let(self, var_name, cond_expr, then_branch, else_branch);
}
    int64_t cond_expr = Parser_parse_expression(self, 0LL);
    Parser_expect_end_of_statement(self);
    int64_t then_branch = Parser_parse_block(self);
    int64_t else_branch = (-1LL);
    Parser_consume_newlines(self);
    if (Parser_peek(self, 0LL).tok_type == TokenType_ELSE) {
    (void)(Parser_advance(self));
    if (Parser_peek(self, 0LL).tok_type == TokenType_IF) {
    ArrayList_Int stmts = ArrayList_Int_init(self->allocator);
    ArrayList_Int_push(&(stmts), Parser_parse_if_stmt(self));
    else_branch = Parser_st_block(self, stmts);
} else {
    Parser_expect_end_of_statement(self);
    else_branch = Parser_parse_block(self);
}
}
    self->stmt_line = saved_line;
    self->stmt_col = saved_col;
    return Parser_st_if(self, cond_expr, then_branch, else_branch);
}
int64_t Parser_parse_while_stmt(Parser* self) {
    (void)(Parser_advance(self));
    int64_t cond_expr = Parser_parse_expression(self, 0LL);
    Parser_expect_end_of_statement(self);
    int64_t saved_line = self->stmt_line;
    int64_t saved_col = self->stmt_col;
    int64_t body = Parser_parse_block(self);
    self->stmt_line = saved_line;
    self->stmt_col = saved_col;
    return Parser_st_while(self, cond_expr, body);
}
int64_t Parser_parse_for_stmt(Parser* self) {
    (void)(Parser_advance(self));
    const char* var_name = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value, self->pool);
    (void)(Parser_expect(self, TokenType_IN));
    int64_t expr = Parser_parse_expression(self, 0LL);
    ExprNode expr_node = ArrayList_ExprNode_get(self->expr_pool, expr);
    int64_t range_start = (-1LL);
    int64_t range_end = (-1LL);
    bool is_inclusive = false;
    if (expr_node.kind == ExprKind_ek_range) {
    range_start = expr_node.range_start;
    range_end = expr_node.range_end;
    is_inclusive = expr_node.range_inclusive;
} else {
    {
    parser_err(self->source_file, self->source, "E0101", "invalid expression in for loop", Parser_peek(self, 0LL).line, Parser_peek(self, 0LL).column);
    exit(1LL);
}
}
    Parser_expect_end_of_statement(self);
    int64_t saved_line = self->stmt_line;
    int64_t saved_col = self->stmt_col;
    int64_t body = Parser_parse_block(self);
    self->stmt_line = saved_line;
    self->stmt_col = saved_col;
    return Parser_st_for(self, var_name, range_start, range_end, is_inclusive, body);
}
int64_t Parser_parse_return_stmt(Parser* self) {
    (void)(Parser_advance(self));
    int64_t val_expr = (-1LL);
    Token next = Parser_peek(self, 0LL);
    if ((((next.tok_type != TokenType_NEWLINE) && (next.tok_type != TokenType_RBRACE)) && (next.tok_type != TokenType_DEDENT)) && (next.tok_type != TokenType_EOF)) {
    val_expr = Parser_parse_expression(self, 0LL);
}
    Parser_expect_end_of_statement(self);
    return Parser_st_return(self, val_expr);
}
int64_t Parser_parse_break_stmt(Parser* self) {
    (void)(Parser_advance(self));
    Parser_expect_end_of_statement(self);
    return Parser_st_break(self);
}
int64_t Parser_parse_continue_stmt(Parser* self) {
    (void)(Parser_advance(self));
    Parser_expect_end_of_statement(self);
    return Parser_st_continue(self);
}
int64_t Parser_parse_defer_stmt(Parser* self) {
    (void)(Parser_advance(self));
    int64_t body = (-1LL);
    if ((Parser_peek(self, 0LL).tok_type == TokenType_NEWLINE) || (Parser_peek(self, 0LL).tok_type == TokenType_LBRACE)) {
    if (Parser_peek(self, 0LL).tok_type == TokenType_NEWLINE) {
    Parser_expect_end_of_statement(self);
}
    int64_t saved_line = self->stmt_line;
    int64_t saved_col = self->stmt_col;
    body = Parser_parse_block(self);
    self->stmt_line = saved_line;
    self->stmt_col = saved_col;
} else {
    body = Parser_parse_statement(self);
}
    return Parser_st_defer(self, body);
}
int64_t Parser_parse_errdefer_stmt(Parser* self) {
    (void)(Parser_advance(self));
    int64_t body = (-1LL);
    if ((Parser_peek(self, 0LL).tok_type == TokenType_NEWLINE) || (Parser_peek(self, 0LL).tok_type == TokenType_LBRACE)) {
    if (Parser_peek(self, 0LL).tok_type == TokenType_NEWLINE) {
    Parser_expect_end_of_statement(self);
}
    int64_t saved_line = self->stmt_line;
    int64_t saved_col = self->stmt_col;
    body = Parser_parse_block(self);
    self->stmt_line = saved_line;
    self->stmt_col = saved_col;
} else {
    body = Parser_parse_statement(self);
}
    return Parser_st_errdefer(self, body);
}
int64_t Parser_parse_expr_or_assignment_stmt(Parser* self) {
    int64_t expr = Parser_parse_expression(self, 0LL);
    Token next = Parser_peek(self, 0LL);
    if (((next.tok_type == TokenType_ASSIGN) || (next.tok_type == TokenType_PLUS_ASSIGN)) || (next.tok_type == TokenType_MINUS_ASSIGN)) {
    Token op_tok = Parser_advance(self);
    int64_t val_expr = Parser_parse_expression(self, 0LL);
    Parser_expect_end_of_statement(self);
    return Parser_st_assign(self, expr, val_expr, token_op_str(op_tok.tok_type));
}
    Parser_expect_end_of_statement(self);
    return Parser_st_expr(self, expr);
}
int64_t Parser_parse_block(Parser* self) {
    Parser_consume_newlines(self);
    ArrayList_Int stmts = ArrayList_Int_init(self->allocator);
    Token brace_tok = Parser_expect(self, TokenType_LBRACE);
    self->stmt_line = brace_tok.line;
    self->stmt_col = brace_tok.column;
    Parser_consume_newlines(self);
    while ((Parser_peek(self, 0LL).tok_type != TokenType_RBRACE) && (Parser_peek(self, 0LL).tok_type != TokenType_EOF)) {
    int64_t stmt = Parser_parse_statement(self);
    if (stmt >= 0LL) {
    ArrayList_Int_push(&(stmts), stmt);
}
    Parser_consume_newlines(self);
}
    if (Parser_peek(self, 0LL).tok_type == TokenType_EOF) {
    {
    parser_err(self->source_file, self->source, "E0101", "expected '}' but reached end of file", 0LL, 0LL);
    exit(1LL);
}
}
    (void)(Parser_advance(self));
    return Parser_st_block(self, stmts);
}
int64_t Parser_parse_import_stmt(Parser* self) {
    (void)(Parser_advance(self));
    ArrayList_Str path = ArrayList_Str_init(self->allocator);
    bool done = false;
    while (!done) {
    ArrayList_Str_push(&(path), tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value, self->pool));
    if (!Parser_match_token(self, TokenType_DOT)) {
    done = true;
}
}
    Parser_expect_end_of_statement(self);
    return Parser_st_import(self, path, "");
}
int64_t Parser_parse_import_stmt_new(Parser* self) {
    (void)(Parser_advance(self));
    const char* first_name = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value, self->pool);
    if (Parser_peek(self, 0LL).tok_type == TokenType_FROM) {
    (void)(Parser_advance(self));
    ArrayList_Str path = ArrayList_Str_init(self->allocator);
    bool done = false;
    while (!done) {
    ArrayList_Str_push(&(path), tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value, self->pool));
    if (!Parser_match_token(self, TokenType_DOT)) {
    done = true;
}
}
    const char* alias = first_name;
    if (Parser_peek(self, 0LL).tok_type == TokenType_AS) {
    (void)(Parser_advance(self));
    alias = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value, self->pool);
}
    Parser_expect_end_of_statement(self);
    return Parser_st_import(self, path, alias);
} else {
    ArrayList_Str path = ArrayList_Str_init(self->allocator);
    ArrayList_Str_push(&(path), first_name);
    while (Parser_match_token(self, TokenType_DOT)) {
    ArrayList_Str_push(&(path), tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value, self->pool));
}
    const char* alias = "";
    if (Parser_peek(self, 0LL).tok_type == TokenType_AS) {
    (void)(Parser_advance(self));
    alias = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value, self->pool);
}
    Parser_expect_end_of_statement(self);
    return Parser_st_import(self, path, alias);
}
}
int64_t Parser_parse_cimport_stmt(Parser* self) {
    (void)(Parser_advance(self));
    Token header_tok = Parser_expect(self, TokenType_STRING_LIT);
    const char* header = tv_get_str(header_tok.value, self->pool);
    const char* alias = "";
    if (Parser_peek(self, 0LL).tok_type == TokenType_AS) {
    (void)(Parser_advance(self));
    alias = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value, self->pool);
}
    Parser_expect_end_of_statement(self);
    return Parser_st_cimport(self, header, alias);
}
int64_t Parser_parse_expression(Parser* self, int64_t precedence) {
    int64_t left = Parser_parse_primary(self);
    bool done = false;
    while (!done) {
    Token op_tok = Parser_peek(self, 0LL);
    int64_t op_prec = token_precedence(op_tok.tok_type);
    if ((op_prec == 0LL) || (op_prec <= precedence)) {
    done = true;
} else {
    (void)(Parser_advance(self));
    if (op_tok.tok_type == TokenType_DOT) {
    const char* member_name = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value, self->pool);
    if (Parser_peek(self, 0LL).tok_type == TokenType_LPAREN) {
    (void)(Parser_advance(self));
    if ((Parser_peek(self, 0LL).tok_type == TokenType_IDENTIFIER) && (Parser_peek(self, 1LL).tok_type == TokenType_COLON)) {
    ArrayList_FieldInit fields = ArrayList_FieldInit_init(self->allocator);
    if (Parser_peek(self, 0LL).tok_type != TokenType_RPAREN) {
    bool fields_done = false;
    while (!fields_done) {
    const char* f_name = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value, self->pool);
    (void)(Parser_expect(self, TokenType_COLON));
    ArrayList_FieldInit_push(&(fields), (FieldInit){ .name = f_name, .value = Parser_parse_expression(self, 0LL) });
    if (!Parser_match_token(self, TokenType_COMMA)) {
    fields_done = true;
}
}
}
    (void)(Parser_expect(self, TokenType_RPAREN));
    ExprNode left_node = ArrayList_ExprNode_get(self->expr_pool, left);
    const char* full_name = "";
    if (left_node.kind == ExprKind_ek_identifier) {
    full_name = left_node.ident_name;
    if (ArrayList_Str_length(&(left_node.ident_type_args)) > 0LL) {
    full_name = concatAlloc(concatAlloc(concatAlloc(full_name, "<"), str_array_join(left_node.ident_type_args, ", ")), ">");
}
}
    left = Parser_ex_struct_init(self, concatAlloc(concatAlloc(full_name, "."), member_name), fields);
} else {
    ArrayList_Int args = ArrayList_Int_init(self->allocator);
    if (Parser_peek(self, 0LL).tok_type != TokenType_RPAREN) {
    bool args_done = false;
    while (!args_done) {
    ArrayList_Int_push(&(args), Parser_parse_expression(self, 0LL));
    if (!Parser_match_token(self, TokenType_COMMA)) {
    args_done = true;
}
}
}
    (void)(Parser_expect(self, TokenType_RPAREN));
    left = Parser_ex_method(self, left, member_name, args);
}
} else {
    left = Parser_ex_field(self, left, member_name);
}
} else if (op_tok.tok_type == TokenType_LBRACKET) {
    if ((Parser_peek(self, 0LL).tok_type == TokenType_DOTDOT) || (Parser_peek(self, 0LL).tok_type == TokenType_DOTDOTEQ)) {
    int64_t lower = (-1LL);
    int64_t upper = (-1LL);
    Token slice_tok = Parser_advance(self);
    bool is_inclusive = (slice_tok.tok_type == TokenType_DOTDOTEQ);
    if (Parser_peek(self, 0LL).tok_type != TokenType_RBRACKET) {
    upper = Parser_parse_expression(self, 0LL);
}
    left = Parser_ex_slice(self, left, lower, upper, is_inclusive);
} else {
    int64_t lower = Parser_parse_expression(self, 0LL);
    ExprNode lower_node = ArrayList_ExprNode_get(self->expr_pool, lower);
    if (lower_node.kind == ExprKind_ek_range) {
    left = Parser_ex_slice(self, left, lower_node.range_start, lower_node.range_end, lower_node.range_inclusive);
} else if ((Parser_peek(self, 0LL).tok_type == TokenType_DOTDOT) || (Parser_peek(self, 0LL).tok_type == TokenType_DOTDOTEQ)) {
    Token slice_tok = Parser_advance(self);
    bool is_inclusive = (slice_tok.tok_type == TokenType_DOTDOTEQ);
    int64_t upper = (-1LL);
    if (Parser_peek(self, 0LL).tok_type != TokenType_RBRACKET) {
    upper = Parser_parse_expression(self, 0LL);
}
    left = Parser_ex_slice(self, left, lower, upper, is_inclusive);
} else {
    left = Parser_ex_index(self, left, lower);
}
}
    (void)(Parser_expect(self, TokenType_RBRACKET));
} else if ((op_tok.tok_type == TokenType_DOTDOT) || (op_tok.tok_type == TokenType_DOTDOTEQ)) {
    bool is_inclusive = (op_tok.tok_type == TokenType_DOTDOTEQ);
    int64_t right = (-1LL);
    Token next = Parser_peek(self, 0LL);
    if (((((((next.tok_type != TokenType_RBRACKET) && (next.tok_type != TokenType_COMMA)) && (next.tok_type != TokenType_NEWLINE)) && (next.tok_type != TokenType_SEMICOLON)) && (next.tok_type != TokenType_RBRACE)) && (next.tok_type != TokenType_DEDENT)) && (next.tok_type != TokenType_EOF)) {
    right = Parser_parse_expression(self, op_prec);
}
    left = Parser_ex_range(self, left, right, is_inclusive);
} else if (op_tok.tok_type == TokenType_CATCH) {
    const char* var_name = "";
    if (Parser_match_token(self, TokenType_PIPE)) {
    var_name = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value, self->pool);
    (void)(Parser_expect(self, TokenType_PIPE));
}
    int64_t fallback = (-1LL);
    Token next = Parser_peek(self, 0LL);
    if (next.tok_type == TokenType_NEWLINE) {
    int64_t saved_line = self->stmt_line;
    int64_t saved_col = self->stmt_col;
    fallback = Parser_parse_block(self);
    self->stmt_line = saved_line;
    self->stmt_col = saved_col;
} else if (next.tok_type == TokenType_RETURN) {
    (void)(Parser_advance(self));
    int64_t ret_val = (-1LL);
    Token follow = Parser_peek(self, 0LL);
    if (((((follow.tok_type != TokenType_NEWLINE) && (follow.tok_type != TokenType_SEMICOLON)) && (follow.tok_type != TokenType_RBRACE)) && (follow.tok_type != TokenType_DEDENT)) && (follow.tok_type != TokenType_EOF)) {
    ret_val = Parser_parse_expression(self, 0LL);
}
    int64_t ret_stmt = Parser_st_return(self, ret_val);
    ArrayList_Int stmts = ArrayList_Int_init(self->allocator);
    ArrayList_Int_push(&(stmts), ret_stmt);
    fallback = Parser_st_block(self, stmts);
} else {
    int64_t expr_val = Parser_parse_expression(self, op_prec);
    int64_t expr_stmt = Parser_st_expr(self, expr_val);
    ArrayList_Int stmts = ArrayList_Int_init(self->allocator);
    ArrayList_Int_push(&(stmts), expr_stmt);
    fallback = Parser_st_block(self, stmts);
}
    left = Parser_ex_catch(self, left, var_name, fallback);
} else if (op_tok.tok_type == TokenType_AS) {
    const char* target_type = Parser_parse_type(self);
    ArrayList_Int args = ArrayList_Int_init(self->allocator);
    ArrayList_Int_push(&(args), left);
    ArrayList_Str targs = ArrayList_Str_init(self->allocator);
    ArrayList_Str_push(&(targs), target_type);
    left = Parser_ex_call_with(self, "as", args, targs);
} else {
    int64_t right = Parser_parse_expression(self, op_prec);
    left = Parser_ex_binop(self, token_op_str(op_tok.tok_type), left, right);
}
}
}
    return left;
}
int64_t Parser_parse_primary(Parser* self) {
    Token tok = Parser_peek(self, 0LL);
    if ((((tok.tok_type == TokenType_INT_LIT) || (tok.tok_type == TokenType_FLOAT_LIT)) || (tok.tok_type == TokenType_BOOL_LIT)) || (tok.tok_type == TokenType_CHAR_LIT)) {
    (void)(Parser_advance(self));
    const char* vkind = "";
    if (tok.tok_type == TokenType_INT_LIT) {
    vkind = "INT";
} else if (tok.tok_type == TokenType_FLOAT_LIT) {
    vkind = "FLOAT";
} else if (tok.tok_type == TokenType_BOOL_LIT) {
    vkind = "BOOL";
} else {
    vkind = "CHAR";
}
    return Parser_ex_literal(self, tok.value, vkind);
} else if (tok.tok_type == TokenType_NONE) {
    (void)(Parser_advance(self));
    return Parser_ex_literal(self, (TokenValue){ .tag = TokenValue_tv_none_TAG }, "NONE");
} else if (tok.tok_type == TokenType_STRING_LIT) {
    (void)(Parser_advance(self));
    return Parser_ex_literal(self, tok.value, "STRING");
} else if (tok.tok_type == TokenType_CHECK) {
    (void)(Parser_advance(self));
    return Parser_ex_check(self, Parser_parse_expression(self, 5LL));
} else if (tok.tok_type == TokenType_TRY) {
    (void)(Parser_advance(self));
    return Parser_ex_try(self, Parser_parse_expression(self, 5LL));
} else if (tok.tok_type == TokenType_OWN) {
    (void)(Parser_advance(self));
    return Parser_ex_unop(self, "own", Parser_parse_expression(self, 5LL));
} else if (tok.tok_type == TokenType_ASM) {
    (void)(Parser_advance(self));
    bool is_volatile = false;
    if (Parser_match_token(self, TokenType_VOLATILE)) {
    is_volatile = true;
}
    (void)(Parser_expect(self, TokenType_LPAREN));
    const char* asm_code = tv_get_str(Parser_expect(self, TokenType_STRING_LIT).value, self->pool);
    ArrayList_AsmOutput outputs = ArrayList_AsmOutput_init(self->allocator);
    ArrayList_AsmInput inputs = ArrayList_AsmInput_init(self->allocator);
    ArrayList_Str clobbers = ArrayList_Str_init(self->allocator);
    if (Parser_match_token(self, TokenType_COLON)) {
    bool done = false;
    while (!done) {
    TokenType next_tt = Parser_peek(self, 0LL).tok_type;
    if (((next_tt == TokenType_COLON) || (next_tt == TokenType_RPAREN)) || (next_tt == TokenType_EOF)) {
    done = true;
} else {
    (void)(Parser_expect(self, TokenType_LBRACKET));
    const char* out_name = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value, self->pool);
    (void)(Parser_expect(self, TokenType_RBRACKET));
    const char* constraint = tv_get_str(Parser_expect(self, TokenType_STRING_LIT).value, self->pool);
    (void)(Parser_expect(self, TokenType_LPAREN));
    const char* type_name = "";
    int64_t expr_idx = (-1LL);
    if (Parser_match_token(self, TokenType_ARROW)) {
    type_name = Parser_parse_type(self);
} else {
    expr_idx = Parser_parse_expression(self, 0LL);
}
    (void)(Parser_expect(self, TokenType_RPAREN));
    ArrayList_AsmOutput_push(&(outputs), (AsmOutput){ .name = out_name, .constraint = constraint, .type_name = type_name, .expr_idx = expr_idx });
    if (!Parser_match_token(self, TokenType_COMMA)) {
    done = true;
}
}
}
}
    if (Parser_match_token(self, TokenType_COLON)) {
    bool done = false;
    while (!done) {
    TokenType next_tt = Parser_peek(self, 0LL).tok_type;
    if (((next_tt == TokenType_COLON) || (next_tt == TokenType_RPAREN)) || (next_tt == TokenType_EOF)) {
    done = true;
} else {
    (void)(Parser_expect(self, TokenType_LBRACKET));
    const char* in_name = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value, self->pool);
    (void)(Parser_expect(self, TokenType_RBRACKET));
    const char* constraint = tv_get_str(Parser_expect(self, TokenType_STRING_LIT).value, self->pool);
    (void)(Parser_expect(self, TokenType_LPAREN));
    int64_t expr_idx = Parser_parse_expression(self, 0LL);
    (void)(Parser_expect(self, TokenType_RPAREN));
    ArrayList_AsmInput_push(&(inputs), (AsmInput){ .name = in_name, .constraint = constraint, .expr_idx = expr_idx });
    if (!Parser_match_token(self, TokenType_COMMA)) {
    done = true;
}
}
}
}
    if (Parser_match_token(self, TokenType_COLON)) {
    bool done = false;
    while (!done) {
    TokenType next_tt = Parser_peek(self, 0LL).tok_type;
    if ((next_tt == TokenType_RPAREN) || (next_tt == TokenType_EOF)) {
    done = true;
} else {
    const char* clobber = tv_get_str(Parser_expect(self, TokenType_STRING_LIT).value, self->pool);
    ArrayList_Str_push(&(clobbers), clobber);
    if (!Parser_match_token(self, TokenType_COMMA)) {
    done = true;
}
}
}
}
    (void)(Parser_expect(self, TokenType_RPAREN));
    return Parser_ex_asm(self, asm_code, is_volatile, outputs, inputs, clobbers);
} else if (tok.tok_type == TokenType_IDENTIFIER) {
    if (Parser_is_generic_instantiation(self)) {
    const char* ident = tv_get_str(Parser_advance(self).value, self->pool);
    (void)(Parser_advance(self));
    ArrayList_Str type_args = ArrayList_Str_init(self->allocator);
    bool done = false;
    while (!done) {
    ArrayList_Str_push(&(type_args), Parser_parse_type(self));
    if (!Parser_match_token(self, TokenType_COMMA)) {
    done = true;
}
}
    (void)(Parser_expect(self, TokenType_GT));
    ArrayList_Str id_type_args = ArrayList_Str_init(self->allocator);
    int64_t ci = 0LL;
    while (ci < ArrayList_Str_length(&(type_args))) {
    ArrayList_Str_push(&(id_type_args), ArrayList_Str_get(&(type_args), ci));
    ci = (ci + 1LL);
}
    if (Parser_peek(self, 0LL).tok_type == TokenType_LPAREN) {
    (void)(Parser_advance(self));
    if ((Parser_peek(self, 0LL).tok_type == TokenType_IDENTIFIER) && (Parser_peek(self, 1LL).tok_type == TokenType_COLON)) {
    ArrayList_FieldInit fields = ArrayList_FieldInit_init(self->allocator);
    if (Parser_peek(self, 0LL).tok_type != TokenType_RPAREN) {
    bool fields_done = false;
    while (!fields_done) {
    const char* f_name = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value, self->pool);
    (void)(Parser_expect(self, TokenType_COLON));
    ArrayList_FieldInit_push(&(fields), (FieldInit){ .name = f_name, .value = Parser_parse_expression(self, 0LL) });
    if (!Parser_match_token(self, TokenType_COMMA)) {
    fields_done = true;
}
}
}
    (void)(Parser_expect(self, TokenType_RPAREN));
    ArrayList_Str sa_type_args = ArrayList_Str_init(self->allocator);
    int64_t cj = 0LL;
    while (cj < ArrayList_Str_length(&(type_args))) {
    ArrayList_Str_push(&(sa_type_args), ArrayList_Str_get(&(type_args), cj));
    cj = (cj + 1LL);
}
    const char* type_args_str = str_array_join(sa_type_args, ", ");
    return Parser_ex_struct_init(self, concatAlloc(concatAlloc(concatAlloc(ident, "<"), type_args_str), ">"), fields);
}
    ArrayList_Int args = ArrayList_Int_init(self->allocator);
    if (Parser_peek(self, 0LL).tok_type != TokenType_RPAREN) {
    bool args_done = false;
    while (!args_done) {
    ArrayList_Int_push(&(args), Parser_parse_expression(self, 0LL));
    if (!Parser_match_token(self, TokenType_COMMA)) {
    args_done = true;
}
}
}
    (void)(Parser_expect(self, TokenType_RPAREN));
    return Parser_ex_call_with(self, ident, args, type_args);
}
    ExprNode id_node = new_expr_node(ExprKind_ek_identifier, Parser_peek(self, 0LL).line, Parser_peek(self, 0LL).column);
    id_node.ident_name = ident;
    id_node.ident_type_args = id_type_args;
    ArrayList_ExprNode_push(self->expr_pool, id_node);
    return (ArrayList_ExprNode_length(self->expr_pool) - 1LL);
} else if (Parser_peek(self, 1LL).tok_type == TokenType_LPAREN) {
    const char* ident = tv_get_str(Parser_advance(self).value, self->pool);
    (void)(Parser_advance(self));
    if ((Parser_peek(self, 0LL).tok_type == TokenType_IDENTIFIER) && (Parser_peek(self, 1LL).tok_type == TokenType_COLON)) {
    ArrayList_FieldInit fields = ArrayList_FieldInit_init(self->allocator);
    if (Parser_peek(self, 0LL).tok_type != TokenType_RPAREN) {
    bool fields_done = false;
    while (!fields_done) {
    const char* f_name = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value, self->pool);
    (void)(Parser_expect(self, TokenType_COLON));
    ArrayList_FieldInit_push(&(fields), (FieldInit){ .name = f_name, .value = Parser_parse_expression(self, 0LL) });
    if (!Parser_match_token(self, TokenType_COMMA)) {
    fields_done = true;
}
}
}
    (void)(Parser_expect(self, TokenType_RPAREN));
    return Parser_ex_struct_init(self, ident, fields);
} else {
    ArrayList_Int args = ArrayList_Int_init(self->allocator);
    if (Parser_peek(self, 0LL).tok_type != TokenType_RPAREN) {
    bool args_done = false;
    while (!args_done) {
    ArrayList_Int_push(&(args), Parser_parse_expression(self, 0LL));
    if (!Parser_match_token(self, TokenType_COMMA)) {
    args_done = true;
}
}
}
    (void)(Parser_expect(self, TokenType_RPAREN));
    return Parser_ex_call(self, ident, args);
}
} else {
    (void)(Parser_advance(self));
    return Parser_ex_ident(self, tv_get_str(tok.value, self->pool));
}
} else if (tok.tok_type == TokenType_MINUS) {
    (void)(Parser_advance(self));
    return Parser_ex_unop(self, "-", Parser_parse_expression(self, 7LL));
} else if (tok.tok_type == TokenType_NOT) {
    (void)(Parser_advance(self));
    return Parser_ex_unop(self, "!", Parser_parse_expression(self, 7LL));
} else if (tok.tok_type == TokenType_BITNOT) {
    (void)(Parser_advance(self));
    return Parser_ex_unop(self, "~", Parser_parse_expression(self, 7LL));
} else if (tok.tok_type == TokenType_SIZEOF) {
    (void)(Parser_advance(self));
    (void)(Parser_expect(self, TokenType_LPAREN));
    const char* type_name = Parser_parse_type(self);
    (void)(Parser_expect(self, TokenType_RPAREN));
    ArrayList_Str targs = ArrayList_Str_init(self->allocator);
    ArrayList_Str_push(&(targs), type_name);
    return Parser_ex_call_with(self, "size_of", ArrayList_Int_init(self->allocator), targs);
} else if (tok.tok_type == TokenType_AMP) {
    (void)(Parser_advance(self));
    bool is_mut = false;
    if (Parser_match_token(self, TokenType_MUT)) {
    is_mut = true;
}
    return Parser_ex_borrow(self, Parser_parse_expression(self, 8LL), is_mut);
} else if (tok.tok_type == TokenType_MUL) {
    (void)(Parser_advance(self));
    return Parser_ex_deref(self, Parser_parse_expression(self, 8LL));
} else if (tok.tok_type == TokenType_LBRACKET) {
    (void)(Parser_advance(self));
    ArrayList_Int elements = ArrayList_Int_init(self->allocator);
    if (Parser_peek(self, 0LL).tok_type != TokenType_RBRACKET) {
    bool done = false;
    while (!done) {
    ArrayList_Int_push(&(elements), Parser_parse_expression(self, 0LL));
    if (!Parser_match_token(self, TokenType_COMMA)) {
    done = true;
}
}
}
    (void)(Parser_expect(self, TokenType_RBRACKET));
    return Parser_ex_array(self, elements);
} else if (tok.tok_type == TokenType_LPAREN) {
    (void)(Parser_advance(self));
    int64_t first = Parser_parse_expression(self, 0LL);
    if (Parser_peek(self, 0LL).tok_type == TokenType_COMMA) {
    ArrayList_Int elements = ArrayList_Int_init(self->allocator);
    ArrayList_Int_push(&(elements), first);
    while (Parser_match_token(self, TokenType_COMMA)) {
    if (Parser_peek(self, 0LL).tok_type != TokenType_RPAREN) {
    ArrayList_Int_push(&(elements), Parser_parse_expression(self, 0LL));
}
}
    (void)(Parser_expect(self, TokenType_RPAREN));
    return Parser_ex_tuple(self, elements);
}
    (void)(Parser_expect(self, TokenType_RPAREN));
    return first;
} else {
    {
    parser_err(self->source_file, self->source, "E0101", concatAlloc(concatAlloc("unexpected token (type: ", int_to_str(((int64_t)(tok.tok_type)))), ")"), tok.line, tok.column);
    exit(1LL);
}
    return (-1LL);
}
}
void print_separator(void) {
    printf("---\n");
}
void printi(int64_t i) {
    __kai_print_int(i);
}
void printff(double f) {
    __kai_print_float(f);
}
void prints(const char* s) {
    printf("%s\n", s);
}
void printc(char c) {
    printf("%c\n", c);
}
ArrayList_DropVarEntry empty_dropvarentry_array(void) {
    return (ArrayList_DropVarEntry){ .data = (DropVarEntry*)(unsigned long long)(0LL), .len = 0LL, .cap = 0LL, .allocator = (KaiAllocator*)(unsigned long long)(0LL) };
}
ArrayList_Str empty_str_array(void) {
    return (ArrayList_Str){ .data = (const char**)(unsigned long long)(0LL), .len = 0LL, .cap = 0LL, .allocator = (KaiAllocator*)(unsigned long long)(0LL) };
}
ArrayList_Int empty_int_array(void) {
    return (ArrayList_Int){ .data = (int64_t*)(unsigned long long)(0LL), .len = 0LL, .cap = 0LL, .allocator = (KaiAllocator*)(unsigned long long)(0LL) };
}
ArrayList_FieldInit empty_fieldinit_array(void) {
    return (ArrayList_FieldInit){ .data = (FieldInit*)(unsigned long long)(0LL), .len = 0LL, .cap = 0LL, .allocator = (KaiAllocator*)(unsigned long long)(0LL) };
}
ArrayList_Param empty_param_array(void) {
    return (ArrayList_Param){ .data = (Param*)(unsigned long long)(0LL), .len = 0LL, .cap = 0LL, .allocator = (KaiAllocator*)(unsigned long long)(0LL) };
}
ArrayList_StructField empty_structfield_array(void) {
    return (ArrayList_StructField){ .data = (StructField*)(unsigned long long)(0LL), .len = 0LL, .cap = 0LL, .allocator = (KaiAllocator*)(unsigned long long)(0LL) };
}
ArrayList_Variant empty_variant_array(void) {
    return (ArrayList_Variant){ .data = (Variant*)(unsigned long long)(0LL), .len = 0LL, .cap = 0LL, .allocator = (KaiAllocator*)(unsigned long long)(0LL) };
}
ArrayList_MatchCase empty_matchcase_array(void) {
    return (ArrayList_MatchCase){ .data = (MatchCase*)(unsigned long long)(0LL), .len = 0LL, .cap = 0LL, .allocator = (KaiAllocator*)(unsigned long long)(0LL) };
}
ArrayList_StrInterpPart empty_strinterp_array(void) {
    return (ArrayList_StrInterpPart){ .data = (StrInterpPart*)(unsigned long long)(0LL), .len = 0LL, .cap = 0LL, .allocator = (KaiAllocator*)(unsigned long long)(0LL) };
}
ArrayList_AsmOutput empty_asmoutput_array(void) {
    return (ArrayList_AsmOutput){ .data = (AsmOutput*)(unsigned long long)(0LL), .len = 0LL, .cap = 0LL, .allocator = (KaiAllocator*)(unsigned long long)(0LL) };
}
ArrayList_AsmInput empty_asminput_array(void) {
    return (ArrayList_AsmInput){ .data = (AsmInput*)(unsigned long long)(0LL), .len = 0LL, .cap = 0LL, .allocator = (KaiAllocator*)(unsigned long long)(0LL) };
}
ExprNode new_expr_node(ExprKind kind, int64_t line, int64_t col) {
    ExprNode node = (ExprNode){ .kind = kind, .line = line, .col = col, .inferred_type = "", .resolved_symbol_idx = (-1LL), .type_id = (-1LL), .lit_value = (TokenValue){ .tag = TokenValue_tv_none_TAG }, .lit_vkind = "", .interp_parts = empty_strinterp_array(), .ident_name = "", .ident_type_args = empty_str_array(), .binop_op = "", .binop_left = (-1LL), .binop_right = (-1LL), .unop_op = "", .unop_operand = (-1LL), .func_name = "", .func_args = empty_int_array(), .func_type_args = empty_str_array(), .struct_name = "", .struct_fields = empty_fieldinit_array(), .field_expr = (-1LL), .field_name = "", .meth_expr = (-1LL), .meth_name = "", .meth_args = empty_int_array(), .idx_expr = (-1LL), .idx_index = (-1LL), .check_expr = (-1LL), .slice_expr = (-1LL), .slice_lower = (-1LL), .slice_upper = (-1LL), .slice_inclusive = false, .range_start = (-1LL), .range_end = (-1LL), .range_inclusive = false, .arr_elements = empty_int_array(), .tup_elements = empty_int_array(), .borrow_expr = (-1LL), .borrow_mut = false, .deref_expr = (-1LL), .try_expr = (-1LL), .catch_expr = (-1LL), .catch_var = "", .catch_fallback = (-1LL), .asm_code = "", .asm_is_volatile = false, .asm_outputs = empty_asmoutput_array(), .asm_inputs = empty_asminput_array(), .asm_clobbers = empty_str_array() };
    return node;
}
StmtNode new_stmt_node(StmtKind kind, int64_t line, int64_t col) {
    StmtNode node = (StmtNode){ .kind = kind, .line = line, .col = col, .block_stmts = empty_int_array(), .vardecl_name = "", .vardecl_type = "", .vardecl_value = (-1LL), .vardecl_mut = false, .assign_target = (-1LL), .assign_value = (-1LL), .assign_op = "", .func_name = "", .func_params = empty_param_array(), .func_return_type = "", .func_body = (-1LL), .func_capability = "", .func_type_params = empty_str_array(), .func_public = false, .struct_name = "", .struct_fields = empty_structfield_array(), .struct_type_params = empty_str_array(), .struct_methods = empty_int_array(), .struct_trait_impls = empty_int_array(), .struct_public = false, .impl_struct_name = "", .impl_trait_name = "", .impl_methods = empty_int_array(), .trait_name = "", .trait_methods = empty_int_array(), .trait_public = false, .enum_name = "", .enum_variants = empty_variant_array(), .enum_type_params = empty_str_array(), .enum_public = false, .if_cond = (-1LL), .if_then = (-1LL), .if_else = (-1LL), .iflet_var = "", .iflet_expr = (-1LL), .iflet_then = (-1LL), .iflet_else = (-1LL), .while_cond = (-1LL), .while_body = (-1LL), .for_var = "", .for_start = (-1LL), .for_end = (-1LL), .for_inclusive = false, .for_body = (-1LL), .return_value = (-1LL), .print_value = (-1LL), .expr_stmt = (-1LL), .defer_body = (-1LL), .errdefer_body = (-1LL), .unsafe_body = (-1LL), .extern_name = "", .extern_params = empty_param_array(), .extern_return = "", .import_path = empty_str_array(), .import_alias = "", .cimport_header = "", .cimport_alias = "", .block_drop_vars = empty_dropvarentry_array(), .block_is_loop_body = false, .match_expr = (-1LL), .match_cases = empty_matchcase_array(), .error_name = "", .error_variants = empty_str_array() };
    return node;
}
PatternNode new_pattern_node(PatternKind kind) {
    PatternNode node = (PatternNode){ .kind = kind, .variant_name = "", .bindings = empty_str_array(), .lit_value = (TokenValue){ .tag = TokenValue_tv_none_TAG } };
    return node;
}
const char* get_source_line(const char* source, int64_t line_num) {
    int64_t current = 0LL;
    int64_t line_start = 0LL;
    int64_t i = 0LL;
    int64_t len = strlen(source);
    while ((i < len) && (current < line_num)) {
    if ((source)[i] == ((char)(10LL))) {
    current = (current + 1LL);
    line_start = (i + 1LL);
}
    i = (i + 1LL);
}
    if (current != line_num) {
    return "";
}
    int64_t line_end = line_start;
    while ((line_end < len) && ((source)[line_end] != ((char)(10LL)))) {
    line_end = (line_end + 1LL);
}
    return substring(source, line_start, line_end);
}
int64_t find_last(const char* path, char c) {
    int64_t i = (strlen(path) - 1LL);
    while (i >= 0LL) {
    if ((path)[i] == c) {
    return i;
}
    i = (i - 1LL);
}
    return (-1LL);
}
bool mkdir_p(const char* path) {
    if (fs_exists(path)) {
    return true;
}
    int64_t slash_pos = find_last(path, ((char)(47LL)));
    if (slash_pos > 0LL) {
    const char* parent = substring(path, 0LL, slash_pos);
    if (!mkdir_p(parent)) {
    return false;
}
}
    return fs_mkdir(path);
}
const char* str_replace(const char* s, const char* old, const char* new_val) {
    int64_t s_len = strlen(s);
    int64_t old_len = strlen(old);
    if (old_len == 0LL) {
    return s;
}
    const char* result = "";
    int64_t i = 0LL;
    while (i < s_len) {
    int64_t j = 0LL;
    bool matched = true;
    while (j < old_len) {
    {
    if ((s)[(i + j)] != (old)[j]) {
    matched = false;
    break;
}
}
    j = (j + 1LL);
}
    if (matched) {
    result = concatAlloc(result, new_val);
    i = (i + old_len);
} else {
    result = concatAlloc(result, substring(s, i, (i + 1LL)));
    i = (i + 1LL);
}
}
    return result;
}
const char* get_base_name(const char* path) {
    int64_t last_slash = (-1LL);
    int64_t dot_pos = (-1LL);
    int64_t i = 0LL;
    int64_t l = strlen(path);
    while (i < l) {
    char c = (path)[i];
    if (c == ((char)(47LL))) {
    last_slash = i;
} else if (c == ((char)(46LL))) {
    dot_pos = i;
}
    i = (i + 1LL);
}
    int64_t start = 0LL;
    if (last_slash >= 0LL) {
    start = (last_slash + 1LL);
}
    int64_t end = l;
    if (dot_pos > last_slash) {
    end = dot_pos;
}
    return substring(path, start, end);
}
bool fs_exists(const char* path) {
    {
    return kai_fs_exists(path);
}
}
bool fs_is_dir(const char* path) {
    {
    return kai_fs_is_dir(path);
}
}
bool fs_mkdir(const char* path) {
    {
    return kai_fs_mkdir(path);
}
}
bool fs_remove(const char* path) {
    {
    return kai_fs_remove(path);
}
}
Dir fs_opendir(const char* path) {
    {
    return (Dir){ .handle = kai_fs_opendir(path) };
}
}
const char* fs_readdir(Dir dir) {
    {
    char* name_ptr = kai_fs_readdir(dir.handle);
    if (name_ptr == (char*)(unsigned long long)(0LL)) {
    return "";
}
    return (const char*)(name_ptr);
}
}
void fs_closedir(Dir dir) {
    {
    kai_fs_closedir(dir.handle);
}
}
StringPool StringPool_init(KaiAllocator* allocator) {
    StringPool self = (StringPool){0};
    self.allocator = allocator;
    self.strings = ArrayList_Str_init(allocator);
    return self;
}
int64_t StringPool_intern(StringPool* self, const char* s) {
    int64_t i = 0LL;
    while (i < ArrayList_Str_length(&(self->strings))) {
    if (strcmp(ArrayList_Str_get(&(self->strings), i), s) == 0) {
    return i;
}
    i = (i + 1LL);
}
    int64_t id = ArrayList_Str_length(&(self->strings));
    ArrayList_Str_push(&(self->strings), s);
    return id;
}
const char* StringPool_get(StringPool* self, int64_t id) {
    return ArrayList_Str_get(&(self->strings), id);
}
void StringPool_deinit(StringPool* self) {
    ArrayList_Str_deinit(&(self->strings));
}
TypeChecker TypeChecker_init(KaiAllocator* allocator, ArrayList_StmtNode* stmt_pool, ArrayList_ExprNode* expr_pool, ArrayList_PatternNode* pattern_pool, const char* source_file, const char* source, ImportResolver* import_resolver, StringPool* pool) {
    TypeChecker self = (TypeChecker){0};
    self.allocator = allocator;
    self.stmt_pool = stmt_pool;
    self.expr_pool = expr_pool;
    self.pattern_pool = pattern_pool;
    self.symbol_tables = ArrayList_SymbolTable_init(allocator);
    self.current_table_idx = (-1LL);
    self.struct_info = ArrayList_StructInfo_init(allocator);
    self.has_error = false;
    self.current_func_ret_type = "";
    self.source_file = source_file;
    self.source = source;
    self.import_resolver = import_resolver;
    self.pool = pool;
    self.type_arena = TypeArena_init(allocator);
    self.imported_names = ArrayList_Str_init(allocator);
    self.import_used = ArrayList_Bool_init(allocator);
    self.import_lines = ArrayList_Int_init(allocator);
    self.import_cols = ArrayList_Int_init(allocator);
    self.loop_depth = 0LL;
    self.scope_deferred_flat = ArrayList_SymTrackState_init(allocator);
    self.scope_deferred_sizes = ArrayList_Int_init(allocator);
    self.scope_deferred_counts = ArrayList_Int_init(allocator);
    self.func_effects = ArrayList_FuncEffect_init(allocator);
    return self;
}
void TypeChecker_err(TypeChecker* self, const char* code, const char* msg, int64_t line, int64_t col) {
    printf("%s:%ld:%ld: error[%s]: %s\n", self->source_file, line, col, code, msg);
    if (line >= 0LL) {
    const char* line_text = get_source_line(self->source, (line - 1LL));
    if (strlen(line_text) > 0LL) {
    printf("    %s\n", line_text);
    const char* caret = "    ";
    int64_t ci = 0LL;
    while ((ci < col) && (ci < strlen(line_text))) {
    if ((line_text)[ci] == ((char)(9LL))) {
    caret = concatAlloc(caret, "\t");
} else {
    caret = concatAlloc(caret, " ");
}
    ci = (ci + 1LL);
}
    caret = concatAlloc(caret, "^");
    printf("%s\n", caret);
}
}
    self->has_error = true;
}
void TypeChecker_enter_scope(TypeChecker* self) {
    SymbolTable new_table = (SymbolTable){ .entries = ArrayList_Symbol_init(self->allocator), .parent_idx = self->current_table_idx, .allocator = self->allocator };
    new_table = SymbolTable_init(self->allocator, self->current_table_idx);
    ArrayList_SymbolTable_push(&(self->symbol_tables), new_table);
    self->current_table_idx = (ArrayList_SymbolTable_length(&(self->symbol_tables)) - 1LL);
    ArrayList_Int_push(&(self->scope_deferred_counts), 0LL);
}
ArrayList_ArrayList_SymTrackState_ ArrayList_ArrayList_SymTrackState__init(KaiAllocator* allocator) {
    ArrayList_ArrayList_SymTrackState_ self = (ArrayList_ArrayList_SymTrackState_){0};
    self.len = 0LL;
    self.cap = 4LL;
    self.allocator = allocator;
    {
    self.data = (ArrayList_SymTrackState*)(KaiAllocator_alloc(allocator, (self.cap * (int64_t)(sizeof(ArrayList_SymTrackState))), 1LL));
}
    return self;
}
void ArrayList_ArrayList_SymTrackState__push(ArrayList_ArrayList_SymTrackState_* self, ArrayList_SymTrackState item) {
    if (self->len == self->cap) {
    int64_t new_cap = (self->cap * 2LL);
    {
    ArrayList_SymTrackState* new_data = (ArrayList_SymTrackState*)(KaiAllocator_alloc(self->allocator, (new_cap * (int64_t)(sizeof(ArrayList_SymTrackState))), 1LL));
    int64_t i = 0LL;
    while (i < self->len) {
    (new_data)[i] = (self->data)[i];
    i = (i + 1LL);
}
    KaiAllocator_free(self->allocator, (uint8_t*)(self->data));
    self->data = new_data;
    self->cap = new_cap;
}
}
    (self->data)[self->len] = item;
    self->len = (self->len + 1LL);
}
ArrayList_SymTrackState ArrayList_ArrayList_SymTrackState__get(ArrayList_ArrayList_SymTrackState_* self, int64_t index) {
    if ((index < 0LL) || (index >= self->len)) {
    {
    exit(1LL);
}
}
    return (self->data)[index];
}
void ArrayList_ArrayList_SymTrackState__set(ArrayList_ArrayList_SymTrackState_* self, int64_t index, ArrayList_SymTrackState item) {
    if ((index < 0LL) || (index >= self->len)) {
    {
    exit(1LL);
}
}
    (self->data)[index] = item;
}
ArrayList_SymTrackState ArrayList_ArrayList_SymTrackState__pop(ArrayList_ArrayList_SymTrackState_* self) {
    if (self->len == 0LL) {
    {
    exit(1LL);
}
}
    self->len = (self->len - 1LL);
    return (self->data)[self->len];
}
int64_t ArrayList_ArrayList_SymTrackState__length(ArrayList_ArrayList_SymTrackState_* self) {
    return self->len;
}
void ArrayList_ArrayList_SymTrackState__deinit(ArrayList_ArrayList_SymTrackState_* self) {
    {
    KaiAllocator_free(self->allocator, (uint8_t*)(self->data));
}
}
void TypeChecker_exit_scope(TypeChecker* self) {
    if (ArrayList_Int_length(&(self->scope_deferred_counts)) > 0LL) {
    int64_t snap_count = ArrayList_Int_get(&(self->scope_deferred_counts), (ArrayList_Int_length(&(self->scope_deferred_counts)) - 1LL));
    if (snap_count > 0LL) {
    int64_t total_sizes_idx = (ArrayList_Int_length(&(self->scope_deferred_sizes)) - snap_count);
    int64_t flat_idx = ArrayList_SymTrackState_length(&(self->scope_deferred_flat));
    int64_t walk = snap_count;
    int64_t begin = flat_idx;
    while (walk > 0LL) {
    int64_t sz = ArrayList_Int_get(&(self->scope_deferred_sizes), ((total_sizes_idx + walk) - 1LL));
    begin = (begin - sz);
    walk = (walk - 1LL);
}
    ArrayList_ArrayList_SymTrackState_ states = ArrayList_ArrayList_SymTrackState__init(self->allocator);
    int64_t si = 0LL;
    int64_t fi = begin;
    while (si < snap_count) {
    int64_t sz = ArrayList_Int_get(&(self->scope_deferred_sizes), (total_sizes_idx + si));
    ArrayList_SymTrackState snapshot = ArrayList_SymTrackState_init(self->allocator);
    int64_t ei = 0LL;
    while (ei < sz) {
    ArrayList_SymTrackState_push(&(snapshot), ArrayList_SymTrackState_get(&(self->scope_deferred_flat), fi));
    fi = (fi + 1LL);
    ei = (ei + 1LL);
}
    ArrayList_ArrayList_SymTrackState__push(&(states), snapshot);
    si = (si + 1LL);
}
    TypeChecker_merge_and_apply_tracking_state(self, states);
    int64_t pi = 0LL;
    while (pi < snap_count) {
    ArrayList_Int_pop(&(self->scope_deferred_sizes));
    pi = (pi + 1LL);
}
    int64_t pop_count = (ArrayList_SymTrackState_length(&(self->scope_deferred_flat)) - begin);
    while (pop_count > 0LL) {
    ArrayList_SymTrackState_pop(&(self->scope_deferred_flat));
    pop_count = (pop_count - 1LL);
}
}
    ArrayList_Int_pop(&(self->scope_deferred_counts));
}
    if (self->current_table_idx >= 0LL) {
    SymbolTable table = ArrayList_SymbolTable_get(&(self->symbol_tables), self->current_table_idx);
    self->current_table_idx = table.parent_idx;
}
}
void TypeChecker_define_symbol(TypeChecker* self, const char* name, const char* type_name, bool is_mutable, const char* kind, int64_t decl_stmt_idx) {
    if (self->current_table_idx >= 0LL) {
    SymbolTable table = ArrayList_SymbolTable_get(&(self->symbol_tables), self->current_table_idx);
    SymbolTable_define(&(table), name, type_name, is_mutable, kind, "", decl_stmt_idx);
    ArrayList_SymbolTable_set(&(self->symbol_tables), self->current_table_idx, table);
}
}
bool TypeChecker_check_program(TypeChecker* self, int64_t top_stmt_idx) {
    TypeChecker_register_struct_info(self, top_stmt_idx);
    TypeChecker_detect_imports(self, top_stmt_idx);
    ImportResolver_resolve_all(self->import_resolver, top_stmt_idx, self->stmt_pool, self->expr_pool, self->pattern_pool);
    if (self->import_resolver->has_error) {
    int64_t err_idx = self->import_resolver->error_stmt_idx;
    int64_t err_line = 0LL;
    int64_t err_col = 0LL;
    if (err_idx >= 0LL) {
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, err_idx);
    err_line = stmt.line;
    err_col = stmt.col;
}
    TypeChecker_err(self, "E0034", self->import_resolver->error_message, err_line, err_col);
    return false;
}
    TypeChecker_enter_scope(self);
    TypeChecker_check_stmt(self, top_stmt_idx);
    TypeChecker_exit_scope(self);
    int64_t ui = 0LL;
    while (ui < ArrayList_Str_length(&(self->imported_names))) {
    if (!ArrayList_Bool_get(&(self->import_used), ui)) {
    int64_t line = ArrayList_Int_get(&(self->import_lines), ui);
    int64_t col = ArrayList_Int_get(&(self->import_cols), ui);
    TypeChecker_err(self, "E0033", concatAlloc(concatAlloc("unused import: '", ArrayList_Str_get(&(self->imported_names), ui)), "'"), line, col);
}
    ui = (ui + 1LL);
}
    return (!self->has_error);
}
void TypeChecker_detect_imports(TypeChecker* self, int64_t top_stmt_idx) {
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, top_stmt_idx);
    if (stmt.kind == StmtKind_sk_block) {
    int64_t i = 0LL;
    while (i < ArrayList_Int_length(&(stmt.block_stmts))) {
    int64_t s_idx = ArrayList_Int_get(&(stmt.block_stmts), i);
    StmtNode s = ArrayList_StmtNode_get(self->stmt_pool, s_idx);
    if (s.kind == StmtKind_sk_import) {
    if (strlen(s.import_alias) > 0LL) {
    ArrayList_Str_push(&(self->imported_names), s.import_alias);
    ArrayList_Bool_push(&(self->import_used), false);
    ArrayList_Int_push(&(self->import_lines), s.line);
    ArrayList_Int_push(&(self->import_cols), s.col);
}
}
    i = (i + 1LL);
}
}
}
void TypeChecker_register_struct_info(TypeChecker* self, int64_t top_stmt_idx) {
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, top_stmt_idx);
    if (stmt.kind == StmtKind_sk_block) {
    int64_t i = 0LL;
    while (i < ArrayList_Int_length(&(stmt.block_stmts))) {
    int64_t s_idx = ArrayList_Int_get(&(stmt.block_stmts), i);
    StmtNode s = ArrayList_StmtNode_get(self->stmt_pool, s_idx);
    if (s.kind == StmtKind_sk_impl_block) {
    bool has_drop = false;
    int64_t j = 0LL;
    while (j < ArrayList_Int_length(&(s.impl_methods))) {
    int64_t m_idx = ArrayList_Int_get(&(s.impl_methods), j);
    StmtNode m = ArrayList_StmtNode_get(self->stmt_pool, m_idx);
    if (strcmp(m.func_name, "drop") == 0) {
    has_drop = true;
}
    j = (j + 1LL);
}
    ArrayList_StructInfo_push(&(self->struct_info), (StructInfo){ .name = s.impl_struct_name, .has_drop = has_drop });
}
    i = (i + 1LL);
}
}
}
bool TypeChecker_has_drop_method(TypeChecker* self, const char* type_name) {
    const char* clean_type = type_name;
    if ((strlen(type_name) > 4LL) && (strcmp(substring(type_name, 0LL, 4LL), "own ") == 0)) {
    clean_type = substring(type_name, 4LL, strlen(type_name));
}
    if ((strlen(clean_type) > 0LL) && ((((clean_type)[0LL] == ((char)(38LL))) || ((clean_type)[0LL] == ((char)(42LL)))) || ((clean_type)[0LL] == ((char)(63LL))))) {
    return false;
}
    int64_t i = 0LL;
    while (i < ArrayList_StructInfo_length(&(self->struct_info))) {
    StructInfo info = ArrayList_StructInfo_get(&(self->struct_info), i);
    if (strcmp(info.name, clean_type) == 0) {
    return info.has_drop;
}
    i = (i + 1LL);
}
    return false;
}
void TypeChecker_collect_block_drops(TypeChecker* self, int64_t stmt_idx) {
    if (self->current_table_idx < 0LL) {
    return;
}
    SymbolTable table = ArrayList_SymbolTable_get(&(self->symbol_tables), self->current_table_idx);
    ArrayList_DropVarEntry drop_vars = ArrayList_DropVarEntry_init(self->allocator);
    int64_t i = (ArrayList_Symbol_length(&(table.entries)) - 1LL);
    while (i >= 0LL) {
    Symbol sym = ArrayList_Symbol_get(&(table.entries), i);
    if ((((strcmp(sym.kind, "var") == 0) || (strcmp(sym.kind, "param") == 0)) && (!sym.moved)) && (!sym.freed)) {
    const char* base_type = sym.type_name;
    if (TypeChecker_has_drop_method(self, base_type)) {
    ArrayList_DropVarEntry_push(&(drop_vars), (DropVarEntry){ .name = sym.name, .base_type = base_type });
}
}
    i = (i - 1LL);
}
    StmtNode block_stmt = ArrayList_StmtNode_get(self->stmt_pool, stmt_idx);
    block_stmt.block_drop_vars = drop_vars;
    ArrayList_StmtNode_set(self->stmt_pool, stmt_idx, block_stmt);
}
bool TypeChecker_is_integer_type(TypeChecker* self, const char* type_name) {
    if (strcmp(type_name, "Int") == 0) {
    return true;
}
    if (strcmp(type_name, "i8") == 0) {
    return true;
}
    if (strcmp(type_name, "i16") == 0) {
    return true;
}
    if (strcmp(type_name, "i32") == 0) {
    return true;
}
    if (strcmp(type_name, "i64") == 0) {
    return true;
}
    if (strcmp(type_name, "u8") == 0) {
    return true;
}
    if (strcmp(type_name, "u16") == 0) {
    return true;
}
    if (strcmp(type_name, "u32") == 0) {
    return true;
}
    if (strcmp(type_name, "u64") == 0) {
    return true;
}
    if (strcmp(type_name, "usize") == 0) {
    return true;
}
    if (strcmp(type_name, "isize") == 0) {
    return true;
}
    return false;
}
bool TypeChecker_is_numeric_type(TypeChecker* self, const char* type_name) {
    if (TypeChecker_is_integer_type(self, type_name)) {
    return true;
}
    if (strcmp(type_name, "Float") == 0) {
    return true;
}
    return false;
}
bool TypeChecker_is_builtin_type(TypeChecker* self, const char* name) {
    return ((((((((strcmp(name, "Int") == 0) || (strcmp(name, "Float") == 0)) || (strcmp(name, "Bool") == 0)) || (strcmp(name, "Char") == 0)) || (strcmp(name, "Str") == 0)) || (strcmp(name, "Void") == 0)) || (strcmp(name, "NoneType") == 0)) || (strcmp(name, "usize") == 0));
}
bool TypeChecker_is_struct_type(TypeChecker* self, const char* name) {
    if (((strcmp(name, "ArrayList") == 0) || (strcmp(name, "HashMap") == 0)) || (strcmp(name, "StringBuilder") == 0)) {
    return true;
}
    int64_t i = 0LL;
    while (i < ArrayList_StmtNode_length(self->stmt_pool)) {
    StmtNode s = ArrayList_StmtNode_get(self->stmt_pool, i);
    if ((s.kind == StmtKind_sk_struct_decl) && (strcmp(s.struct_name, name) == 0)) {
    return true;
}
    i = (i + 1LL);
}
    return false;
}
bool TypeChecker_is_standard_c_func(TypeChecker* self, const char* name) {
    if (((strcmp(name, "malloc") == 0) || (strcmp(name, "realloc") == 0)) || (strcmp(name, "calloc") == 0)) {
    return true;
}
    if ((((strcmp(name, "printf") == 0) || (strcmp(name, "fprintf") == 0)) || (strcmp(name, "sprintf") == 0)) || (strcmp(name, "snprintf") == 0)) {
    return true;
}
    if (((((((strcmp(name, "fopen") == 0) || (strcmp(name, "fread") == 0)) || (strcmp(name, "fwrite") == 0)) || (strcmp(name, "fclose") == 0)) || (strcmp(name, "fseek") == 0)) || (strcmp(name, "ftell") == 0)) || (strcmp(name, "rewind") == 0)) {
    return true;
}
    if ((strcmp(name, "strlen") == 0) || (strcmp(name, "strcmp") == 0)) {
    return true;
}
    if ((strcmp(name, "exit") == 0) || (strcmp(name, "system") == 0)) {
    return true;
}
    if ((((strcmp(name, "isdigit") == 0) || (strcmp(name, "isalpha") == 0)) || (strcmp(name, "isalnum") == 0)) || (strcmp(name, "isspace") == 0)) {
    return true;
}
    if ((strcmp(name, "toupper") == 0) || (strcmp(name, "tolower") == 0)) {
    return true;
}
    if (strcmp(name, "atoll") == 0) {
    return true;
}
    if (strcmp(name, "sqrt") == 0) {
    return true;
}
    if (((strcmp(name, "memset") == 0) || (strcmp(name, "memcpy") == 0)) || (strcmp(name, "memmove") == 0)) {
    return true;
}
    if (strcmp(name, "abort") == 0) {
    return true;
}
    return false;
}
bool TypeChecker_fits_in_type(TypeChecker* self, int64_t val, const char* type_name) {
    if (strcmp(type_name, "i8") == 0) {
    return ((val >= (-128LL)) && (val <= 127LL));
}
    if (strcmp(type_name, "i16") == 0) {
    return ((val >= (-32768LL)) && (val <= 32767LL));
}
    if (strcmp(type_name, "i32") == 0) {
    return ((val >= (-2147483648LL)) && (val <= 2147483647LL));
}
    if (strcmp(type_name, "u8") == 0) {
    return ((val >= 0LL) && (val <= 255LL));
}
    if (strcmp(type_name, "u16") == 0) {
    return ((val >= 0LL) && (val <= 65535LL));
}
    if (strcmp(type_name, "u32") == 0) {
    return ((val >= 0LL) && (val <= 4294967295LL));
}
    if (strcmp(type_name, "u64") == 0) {
    return (val >= 0LL);
}
    if (((strcmp(type_name, "Int") == 0) || (strcmp(type_name, "i64") == 0)) || (strcmp(type_name, "isize") == 0)) {
    return true;
}
    if (strcmp(type_name, "usize") == 0) {
    return (val >= 0LL);
}
    return true;
}
bool TypeChecker_is_integer_literal(TypeChecker* self, int64_t expr_idx) {
    if (expr_idx < 0LL) {
    return false;
}
    ExprNode expr = ArrayList_ExprNode_get(self->expr_pool, expr_idx);
    return ((expr.kind == ExprKind_ek_literal) && (strcmp(expr.lit_vkind, "INT") == 0));
}
int64_t TypeChecker_int_literal_value(TypeChecker* self, ExprNode expr) {
    if (expr.lit_value.tag == TokenValue_tv_str_TAG) {
    int64_t v = expr.lit_value.payload.tv_str.v;

    const char* sval = StringPool_get(self->pool, v);
    int64_t len = strlen(sval);
    int64_t res = 0LL;
    int64_t pos = 0LL;
    while (pos < len) {
    const char* digit = substring(sval, pos, (pos + 1LL));
    if (strcmp(digit, "1") == 0) {
    res = ((res * 10LL) + 1LL);
} else if (strcmp(digit, "2") == 0) {
    res = ((res * 10LL) + 2LL);
} else if (strcmp(digit, "3") == 0) {
    res = ((res * 10LL) + 3LL);
} else if (strcmp(digit, "4") == 0) {
    res = ((res * 10LL) + 4LL);
} else if (strcmp(digit, "5") == 0) {
    res = ((res * 10LL) + 5LL);
} else if (strcmp(digit, "6") == 0) {
    res = ((res * 10LL) + 6LL);
} else if (strcmp(digit, "7") == 0) {
    res = ((res * 10LL) + 7LL);
} else if (strcmp(digit, "8") == 0) {
    res = ((res * 10LL) + 8LL);
} else if (strcmp(digit, "9") == 0) {
    res = ((res * 10LL) + 9LL);
} else {
    res = (res * 10LL);
}
    pos = (pos + 1LL);
}
    return res;
} else if (expr.lit_value.tag == TokenValue_tv_int_TAG) {
    int64_t v = expr.lit_value.payload.tv_int.v;

    return v;
} else {
    return 0LL;
} 
}
bool TypeChecker_is_copy_type(TypeChecker* self, const char* type_name) {
    if (TypeChecker_is_integer_type(self, type_name)) {
    return true;
}
    if (strcmp(type_name, "Float") == 0) {
    return true;
}
    if (strcmp(type_name, "Bool") == 0) {
    return true;
}
    if (strcmp(type_name, "Char") == 0) {
    return true;
}
    if (strcmp(type_name, "Str") == 0) {
    return true;
}
    if (strcmp(type_name, "Void") == 0) {
    return true;
}
    if (strcmp(type_name, "NoneType") == 0) {
    return true;
}
    if ((strlen(type_name) > 0LL) && (((type_name)[0LL] == ((char)(42LL))) || ((type_name)[0LL] == ((char)(38LL))))) {
    return true;
}
    return false;
}
PtrRefResult TypeChecker_parse_ptr_ref(TypeChecker* self, const char* type_str) {
    bool is_ptr = false;
    bool is_mut = false;
    const char* inner = type_str;
    if ((strlen(inner) > 0LL) && ((inner)[0LL] == ((char)(63LL)))) {
    inner = substring(inner, 1LL, strlen(inner));
}
    if ((strlen(inner) > 5LL) && (strcmp(substring(inner, 0LL, 5LL), "*mut ") == 0)) {
    is_ptr = true;
    is_mut = true;
    inner = substring(inner, 5LL, strlen(inner));
} else if ((strlen(inner) > 1LL) && ((inner)[0LL] == ((char)(42LL)))) {
    is_ptr = true;
    inner = substring(inner, 1LL, strlen(inner));
} else if ((strlen(inner) > 5LL) && (strcmp(substring(inner, 0LL, 5LL), "&mut ") == 0)) {
    is_ptr = true;
    is_mut = true;
    inner = substring(inner, 5LL, strlen(inner));
} else if ((strlen(inner) > 1LL) && ((inner)[0LL] == ((char)(38LL)))) {
    is_ptr = true;
    inner = substring(inner, 1LL, strlen(inner));
}
    return (PtrRefResult){ .is_ptr = is_ptr, .is_mut = is_mut, .inner = inner };
}
bool TypeChecker_types_compatible(TypeChecker* self, const char* target, const char* source) {
    const char* t = target;
    const char* s = source;
    if ((strlen(t) > 4LL) && (strcmp(substring(t, 0LL, 4LL), "own ") == 0)) {
    t = substring(t, 4LL, strlen(t));
}
    if ((strlen(s) > 4LL) && (strcmp(substring(s, 0LL, 4LL), "own ") == 0)) {
    s = substring(s, 4LL, strlen(s));
}
    if ((strcmp(t, "Void") == 0) || (strcmp(s, "Void") == 0)) {
    return true;
}
    if (strcmp(t, s) == 0) {
    return true;
}
    if ((((strlen(t) > 0LL) && ((t)[0LL] == ((char)(40LL)))) && (strlen(s) > 0LL)) && ((s)[0LL] == ((char)(40LL)))) {
    const char* t_inner = __kai_str_sub(t, 1LL, (strlen(t) - 1LL));
    ArrayList_Str t_list = ArrayList_Str_init(self->allocator);
    int64_t start = 0LL;
    int64_t i = 0LL;
    while (i < strlen(t_inner)) {
    if ((t_inner)[i] == ((char)(44LL))) {
    int64_t ts_start = start;
    while ((ts_start < i) && ((t_inner)[ts_start] == ((char)(32LL)))) {
    ts_start = (ts_start + 1LL);
}
    int64_t ts_end = i;
    while ((ts_end > ts_start) && ((t_inner)[(ts_end - 1LL)] == ((char)(32LL)))) {
    ts_end = (ts_end - 1LL);
}
    ArrayList_Str_push(&(t_list), __kai_str_sub(t_inner, ts_start, ts_end));
    start = (i + 1LL);
}
    i = (i + 1LL);
}
    int64_t ts_start = start;
    while ((ts_start < strlen(t_inner)) && ((t_inner)[ts_start] == ((char)(32LL)))) {
    ts_start = (ts_start + 1LL);
}
    int64_t ts_end = strlen(t_inner);
    while ((ts_end > ts_start) && ((t_inner)[(ts_end - 1LL)] == ((char)(32LL)))) {
    ts_end = (ts_end - 1LL);
}
    ArrayList_Str_push(&(t_list), __kai_str_sub(t_inner, ts_start, ts_end));
    const char* s_inner = __kai_str_sub(s, 1LL, (strlen(s) - 1LL));
    ArrayList_Str s_list = ArrayList_Str_init(self->allocator);
    start = 0LL;
    i = 0LL;
    while (i < strlen(s_inner)) {
    if ((s_inner)[i] == ((char)(44LL))) {
    int64_t ts_start = start;
    while ((ts_start < i) && ((s_inner)[ts_start] == ((char)(32LL)))) {
    ts_start = (ts_start + 1LL);
}
    int64_t ts_end = i;
    while ((ts_end > ts_start) && ((s_inner)[(ts_end - 1LL)] == ((char)(32LL)))) {
    ts_end = (ts_end - 1LL);
}
    ArrayList_Str_push(&(s_list), __kai_str_sub(s_inner, ts_start, ts_end));
    start = (i + 1LL);
}
    i = (i + 1LL);
}
    ts_start = start;
    while ((ts_start < strlen(s_inner)) && ((s_inner)[ts_start] == ((char)(32LL)))) {
    ts_start = (ts_start + 1LL);
}
    ts_end = strlen(s_inner);
    while ((ts_end > ts_start) && ((s_inner)[(ts_end - 1LL)] == ((char)(32LL)))) {
    ts_end = (ts_end - 1LL);
}
    ArrayList_Str_push(&(s_list), __kai_str_sub(s_inner, ts_start, ts_end));
    if (ArrayList_Str_length(&(t_list)) != ArrayList_Str_length(&(s_list))) {
    return false;
}
    int64_t ti = 0LL;
    while (ti < ArrayList_Str_length(&(t_list))) {
    if (!TypeChecker_types_compatible(self, ArrayList_Str_get(&(t_list), ti), ArrayList_Str_get(&(s_list), ti))) {
    return false;
}
    ti = (ti + 1LL);
}
    return true;
}
    if (TypeChecker_is_integer_type(self, t) && TypeChecker_is_integer_type(self, s)) {
    return false;
}
    if (((strcmp(t, "Str") == 0) && ((strcmp(s, "*Char") == 0) || (strcmp(s, "*Void") == 0))) || (((strcmp(t, "*Char") == 0) || (strcmp(t, "*Void") == 0)) && (strcmp(s, "Str") == 0))) {
    return true;
}
    if ((strlen(t) > 0LL) && ((t)[0LL] == ((char)(63LL)))) {
    if (strcmp(s, "NoneType") == 0) {
    return true;
}
    const char* t_inner = substring(t, 1LL, strlen(t));
    const char* s_inner = s;
    if ((strlen(s) > 0LL) && ((s)[0LL] == ((char)(63LL)))) {
    s_inner = substring(s, 1LL, strlen(s));
}
    return TypeChecker_types_compatible(self, t_inner, s_inner);
}
    int64_t excl_t = (-1LL);
    int64_t i = 0LL;
    while (i < strlen(t)) {
    if ((t)[i] == ((char)(33LL))) {
    excl_t = i;
}
    i = (i + 1LL);
}
    if (excl_t >= 0LL) {
    const char* target_val = substring(t, 0LL, excl_t);
    const char* target_err = substring(t, (excl_t + 1LL), strlen(t));
    int64_t excl_s = (-1LL);
    i = 0LL;
    while (i < strlen(s)) {
    if ((s)[i] == ((char)(33LL))) {
    excl_s = i;
}
    i = (i + 1LL);
}
    if (excl_s >= 0LL) {
    const char* source_val = substring(s, 0LL, excl_s);
    const char* source_err = substring(s, (excl_s + 1LL), strlen(s));
    return (TypeChecker_types_compatible(self, target_val, source_val) && TypeChecker_types_compatible(self, target_err, source_err));
}
    if (TypeChecker_types_compatible(self, target_val, s)) {
    return true;
}
    if (strcmp(s, target_err) == 0) {
    return true;
}
}
    bool t_is_slice = ((strlen(t) >= 2LL) && (strcmp(__kai_str_sub(t, 0LL, 2LL), "[]") == 0));
    bool s_is_slice = ((strlen(s) >= 2LL) && (strcmp(__kai_str_sub(s, 0LL, 2LL), "[]") == 0));
    if (t_is_slice || s_is_slice) {
    const char* t_inner = t;
    if (t_is_slice) {
    t_inner = __kai_str_sub(t, 2LL, strlen(t));
} else if ((strlen(t) > 0LL) && ((t)[0LL] == ((char)(42LL)))) {
    t_inner = __kai_str_sub(t, 1LL, strlen(t));
}
    const char* s_inner = s;
    if (s_is_slice) {
    s_inner = __kai_str_sub(s, 2LL, strlen(s));
} else if ((strlen(s) > 0LL) && ((s)[0LL] == ((char)(42LL)))) {
    s_inner = __kai_str_sub(s, 1LL, strlen(s));
}
    return TypeChecker_types_compatible(self, t_inner, s_inner);
}
    PtrRefResult t_ptr = TypeChecker_parse_ptr_ref(self, t);
    PtrRefResult s_ptr = TypeChecker_parse_ptr_ref(self, s);
    if (t_ptr.is_ptr != s_ptr.is_ptr) {
    return false;
}
    if (t_ptr.is_ptr) {
    if ((!s_ptr.is_mut) && t_ptr.is_mut) {
    return false;
}
    return TypeChecker_types_compatible(self, t_ptr.inner, s_ptr.inner);
}
    return false;
}
int64_t TypeChecker_find_func_decl(TypeChecker* self, const char* name) {
    int64_t idx = 0LL;
    while (idx < ArrayList_StmtNode_length(self->stmt_pool)) {
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, idx);
    if ((stmt.kind == StmtKind_sk_func_decl) && (strcmp(stmt.func_name, name) == 0)) {
    if ((ArrayList_Param_length(&(stmt.func_params)) > 0LL) && (strcmp(ArrayList_Param_get(&(stmt.func_params), 0LL).ptype, "self") == 0)) {
    idx = (idx + 1LL);
    continue;
}
    return idx;
}
    if ((stmt.kind == StmtKind_sk_extern) && (strcmp(stmt.extern_name, name) == 0)) {
    return idx;
}
    idx = (idx + 1LL);
}
    return (-1LL);
}
int64_t TypeChecker_find_method_decl(TypeChecker* self, const char* struct_name, const char* meth_name) {
    const char* clean_struct = struct_name;
    int64_t i = 0LL;
    const char* clean = "";
    while (i < strlen(clean_struct)) {
    char c = (clean_struct)[i];
    if ((c != ((char)(42LL))) && (c != ((char)(38LL)))) {
    clean = concatAlloc(clean, char_to_str(c));
}
    i = (i + 1LL);
}
    clean_struct = clean;
    if ((strlen(clean_struct) > 4LL) && (strcmp(substring(clean_struct, 0LL, 4LL), "mut ") == 0)) {
    clean_struct = substring(clean_struct, 4LL, strlen(clean_struct));
}
    int64_t lt_pos = (-1LL);
    i = 0LL;
    while (i < strlen(clean_struct)) {
    if ((clean_struct)[i] == ((char)(60LL))) {
    lt_pos = i;
}
    i = (i + 1LL);
}
    if (lt_pos >= 0LL) {
    clean_struct = substring(clean_struct, 0LL, lt_pos);
}
    int64_t idx = 0LL;
    while (idx < ArrayList_StmtNode_length(self->stmt_pool)) {
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, idx);
    if (stmt.kind == StmtKind_sk_impl_block) {
    const char* impl_name = stmt.impl_struct_name;
    int64_t impl_lt = (-1LL);
    int64_t j = 0LL;
    while (j < strlen(impl_name)) {
    if ((impl_name)[j] == ((char)(60LL))) {
    impl_lt = j;
}
    j = (j + 1LL);
}
    if (impl_lt >= 0LL) {
    impl_name = substring(impl_name, 0LL, impl_lt);
}
    if (strcmp(impl_name, clean_struct) == 0) {
    int64_t mi = 0LL;
    while (mi < ArrayList_Int_length(&(stmt.impl_methods))) {
    int64_t m_idx = ArrayList_Int_get(&(stmt.impl_methods), mi);
    StmtNode m = ArrayList_StmtNode_get(self->stmt_pool, m_idx);
    if (strcmp(m.func_name, meth_name) == 0) {
    return m_idx;
}
    mi = (mi + 1LL);
}
}
}
    idx = (idx + 1LL);
}
    return (-1LL);
}
int64_t TypeChecker_find_struct_decl(TypeChecker* self, const char* name) {
    int64_t idx = 0LL;
    while (idx < ArrayList_StmtNode_length(self->stmt_pool)) {
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, idx);
    if ((stmt.kind == StmtKind_sk_struct_decl) && (strcmp(stmt.struct_name, name) == 0)) {
    return idx;
}
    idx = (idx + 1LL);
}
    return (-1LL);
}
int64_t TypeChecker_find_enum_decl(TypeChecker* self, const char* name) {
    int64_t idx = 0LL;
    while (idx < ArrayList_StmtNode_length(self->stmt_pool)) {
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, idx);
    if ((stmt.kind == StmtKind_sk_enum_decl) && (strcmp(stmt.enum_name, name) == 0)) {
    return idx;
}
    idx = (idx + 1LL);
}
    return (-1LL);
}
const char* TypeChecker_get_block_yield_type(TypeChecker* self, int64_t stmt_idx) {
    if (stmt_idx < 0LL) {
    return "Void";
}
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, stmt_idx);
    if (stmt.kind == StmtKind_sk_block) {
    if (ArrayList_Int_length(&(stmt.block_stmts)) == 0LL) {
    return "Void";
}
    int64_t last_idx = ArrayList_Int_get(&(stmt.block_stmts), (ArrayList_Int_length(&(stmt.block_stmts)) - 1LL));
    StmtNode last_stmt = ArrayList_StmtNode_get(self->stmt_pool, last_idx);
    if (last_stmt.kind == StmtKind_sk_expr) {
    return TypeChecker_get_expr_type(self, last_stmt.expr_stmt);
}
    if (last_stmt.kind == StmtKind_sk_return) {
    return "Void";
}
}
    if (stmt.kind == StmtKind_sk_expr) {
    return TypeChecker_get_expr_type(self, stmt.expr_stmt);
}
    return "Void";
}
void TypeChecker_mark_expr_moved(TypeChecker* self, int64_t expr_idx) {
    if (expr_idx < 0LL) {
    return;
}
    int64_t inner = expr_idx;
    bool done = false;
    while (!done) {
    ExprNode e = ArrayList_ExprNode_get(self->expr_pool, inner);
    if (((e.kind == ExprKind_ek_func_call) && (strcmp(e.func_name, "as") == 0)) && (ArrayList_Int_length(&(e.func_args)) >= 1LL)) {
    inner = ArrayList_Int_get(&(e.func_args), 0LL);
} else if (e.kind == ExprKind_ek_field_access) {
    inner = e.field_expr;
} else {
    done = true;
}
}
    ExprNode expr = ArrayList_ExprNode_get(self->expr_pool, inner);
    if (expr.kind == ExprKind_ek_identifier) {
    const char* t = TypeChecker_get_expr_type(self, inner);
    if (!TypeChecker_is_copy_type(self, t)) {
    SymbolTable table = ArrayList_SymbolTable_get(&(self->symbol_tables), self->current_table_idx);
    SymbolTable_mark_moved(&(table), expr.ident_name, &(self->symbol_tables));
    ArrayList_SymbolTable_set(&(self->symbol_tables), self->current_table_idx, table);
}
}
}
void TypeChecker_mark_expr_freed(TypeChecker* self, int64_t expr_idx) {
    if (expr_idx < 0LL) {
    return;
}
    int64_t inner = expr_idx;
    bool done = false;
    while (!done) {
    ExprNode e = ArrayList_ExprNode_get(self->expr_pool, inner);
    if (((e.kind == ExprKind_ek_func_call) && (strcmp(e.func_name, "as") == 0)) && (ArrayList_Int_length(&(e.func_args)) >= 1LL)) {
    inner = ArrayList_Int_get(&(e.func_args), 0LL);
} else if (e.kind == ExprKind_ek_field_access) {
    inner = e.field_expr;
} else {
    done = true;
}
}
    ExprNode expr = ArrayList_ExprNode_get(self->expr_pool, inner);
    if (expr.kind == ExprKind_ek_identifier) {
    SymbolTable table = ArrayList_SymbolTable_get(&(self->symbol_tables), self->current_table_idx);
    Symbol sym = SymbolTable_lookup_symbol(&(table), expr.ident_name, &(self->symbol_tables));
    if (strlen(sym.name) > 0LL) {
    if (sym.freed) {
    TypeChecker_err(self, "E0032", concatAlloc(concatAlloc("double-free: '", expr.ident_name), "' is already freed"), expr.line, expr.col);
    return;
}
    if (sym.moved) {
    TypeChecker_err(self, "E0009", concatAlloc(concatAlloc("use of moved value: '", expr.ident_name), "'"), expr.line, expr.col);
    return;
}
    SymbolTable_mark_freed(&(table), expr.ident_name, &(self->symbol_tables));
    ArrayList_SymbolTable_set(&(self->symbol_tables), self->current_table_idx, table);
}
}
}
ArrayList_SymTrackState TypeChecker_capture_tracking_state(TypeChecker* self) {
    ArrayList_SymTrackState result = ArrayList_SymTrackState_init(self->allocator);
    int64_t tidx = self->current_table_idx;
    while (tidx >= 0LL) {
    SymbolTable table = ArrayList_SymbolTable_get(&(self->symbol_tables), tidx);
    int64_t i = 0LL;
    while (i < ArrayList_Symbol_length(&(table.entries))) {
    Symbol sym = ArrayList_Symbol_get(&(table.entries), i);
    ArrayList_SymTrackState_push(&(result), (SymTrackState){ .name = sym.name, .table_idx = tidx, .entry_idx = i, .moved = sym.moved, .freed = sym.freed });
    i = (i + 1LL);
}
    tidx = table.parent_idx;
}
    return result;
}
void TypeChecker_restore_tracking_state(TypeChecker* self, ArrayList_SymTrackState state) {
    int64_t i = 0LL;
    while (i < ArrayList_SymTrackState_length(&(state))) {
    SymTrackState s = ArrayList_SymTrackState_get(&(state), i);
    if ((s.table_idx >= 0LL) && (s.table_idx < ArrayList_SymbolTable_length(&(self->symbol_tables)))) {
    SymbolTable table = ArrayList_SymbolTable_get(&(self->symbol_tables), s.table_idx);
    if ((s.entry_idx >= 0LL) && (s.entry_idx < ArrayList_Symbol_length(&(table.entries)))) {
    Symbol sym = ArrayList_Symbol_get(&(table.entries), s.entry_idx);
    sym.moved = s.moved;
    sym.freed = s.freed;
    ArrayList_Symbol_set(&(table.entries), s.entry_idx, sym);
    ArrayList_SymbolTable_set(&(self->symbol_tables), s.table_idx, table);
}
}
    i = (i + 1LL);
}
}
void TypeChecker_merge_and_apply_tracking_state(TypeChecker* self, ArrayList_ArrayList_SymTrackState_ states) {
    ArrayList_SymTrackState merged = ArrayList_SymTrackState_init(self->allocator);
    int64_t si = 0LL;
    while (si < ArrayList_ArrayList_SymTrackState__length(&(states))) {
    ArrayList_SymTrackState state = ArrayList_ArrayList_SymTrackState__get(&(states), si);
    int64_t ei = 0LL;
    while (ei < ArrayList_SymTrackState_length(&(state))) {
    SymTrackState s = ArrayList_SymTrackState_get(&(state), ei);
    bool found = false;
    int64_t mi = 0LL;
    while (mi < ArrayList_SymTrackState_length(&(merged))) {
    SymTrackState m = ArrayList_SymTrackState_get(&(merged), mi);
    if ((m.table_idx == s.table_idx) && (m.entry_idx == s.entry_idx)) {
    SymTrackState updated = m;
    if (s.moved) {
    updated.moved = true;
}
    if (s.freed) {
    updated.freed = true;
}
    ArrayList_SymTrackState_set(&(merged), mi, updated);
    found = true;
    break;
}
    mi = (mi + 1LL);
}
    if (!found) {
    ArrayList_SymTrackState_push(&(merged), s);
}
    ei = (ei + 1LL);
}
    si = (si + 1LL);
}
    int64_t i = 0LL;
    while (i < ArrayList_SymTrackState_length(&(merged))) {
    SymTrackState s = ArrayList_SymTrackState_get(&(merged), i);
    if ((s.table_idx >= 0LL) && (s.table_idx < ArrayList_SymbolTable_length(&(self->symbol_tables)))) {
    SymbolTable table = ArrayList_SymbolTable_get(&(self->symbol_tables), s.table_idx);
    if ((s.entry_idx >= 0LL) && (s.entry_idx < ArrayList_Symbol_length(&(table.entries)))) {
    Symbol sym = ArrayList_Symbol_get(&(table.entries), s.entry_idx);
    sym.moved = s.moved;
    sym.freed = s.freed;
    ArrayList_Symbol_set(&(table.entries), s.entry_idx, sym);
    ArrayList_SymbolTable_set(&(self->symbol_tables), s.table_idx, table);
}
}
    i = (i + 1LL);
}
}
const char* TypeChecker_get_expr_type(TypeChecker* self, int64_t expr_idx) {
    if (expr_idx < 0LL) {
    return "Void";
}
    ExprNode expr = ArrayList_ExprNode_get(self->expr_pool, expr_idx);
    if (expr.kind == ExprKind_ek_literal) {
    const char* vkind = expr.lit_vkind;
    if (strcmp(vkind, "INT") == 0) {
    return "Int";
}
    if (strcmp(vkind, "FLOAT") == 0) {
    return "Float";
}
    if (strcmp(vkind, "STRING") == 0) {
    return "Str";
}
    if (strcmp(vkind, "BOOL") == 0) {
    return "Bool";
}
    if (strcmp(vkind, "CHAR") == 0) {
    return "Char";
}
    return "Void";
}
    if (expr.kind == ExprKind_ek_identifier) {
    const char* name = expr.ident_name;
    SymbolTable table = ArrayList_SymbolTable_get(&(self->symbol_tables), self->current_table_idx);
    Symbol sym = SymbolTable_lookup_symbol(&(table), name, &(self->symbol_tables));
    if (strlen(sym.name) > 0LL) {
    return sym.type_name;
}
    return "Void";
}
    if (expr.kind == ExprKind_ek_binary_op) {
    const char* op = expr.binop_op;
    if ((((((((strcmp(op, "==") == 0) || (strcmp(op, "!=") == 0)) || (strcmp(op, "<") == 0)) || (strcmp(op, ">") == 0)) || (strcmp(op, "<=") == 0)) || (strcmp(op, ">=") == 0)) || (strcmp(op, "&&") == 0)) || (strcmp(op, "||") == 0)) {
    return "Bool";
}
    return TypeChecker_get_expr_type(self, expr.binop_left);
}
    if (expr.kind == ExprKind_ek_unary_op) {
    const char* op = expr.unop_op;
    if (strcmp(op, "!") == 0) {
    return "Bool";
}
    return TypeChecker_get_expr_type(self, expr.unop_operand);
}
    if (expr.kind == ExprKind_ek_func_call) {
    const char* name = expr.func_name;
    if ((strcmp(name, "cast") == 0) || (strcmp(name, "as") == 0)) {
    return ArrayList_Str_get(&(expr.func_type_args), 0LL);
}
    if (strcmp(name, "size_of") == 0) {
    return "usize";
}
    if ((((strcmp(name, "Char") == 0) || (strcmp(name, "Int") == 0)) || (strcmp(name, "Float") == 0)) || (strcmp(name, "Bool") == 0)) {
    return name;
}
    bool is_struct = false;
    int64_t s_idx = 0LL;
    while (s_idx < ArrayList_StmtNode_length(self->stmt_pool)) {
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, s_idx);
    if ((stmt.kind == StmtKind_sk_struct_decl) && (strcmp(stmt.struct_name, name) == 0)) {
    is_struct = true;
}
    s_idx = (s_idx + 1LL);
}
    if (((strcmp(name, "ArrayList") == 0) || (strcmp(name, "HashMap") == 0)) || (strcmp(name, "StringBuilder") == 0)) {
    is_struct = true;
}
    if (is_struct) {
    if (ArrayList_Str_length(&(expr.func_type_args)) > 0LL) {
    return concatAlloc(concatAlloc(concatAlloc(concatAlloc("*", name), "<"), str_array_join(expr.func_type_args, ", ")), ">");
}
    return concatAlloc("*", name);
}
    int64_t func_idx = TypeChecker_find_func_decl(self, name);
    if (func_idx >= 0LL) {
    StmtNode decl = ArrayList_StmtNode_get(self->stmt_pool, func_idx);
    if (decl.kind == StmtKind_sk_func_decl) {
    return decl.func_return_type;
}
    if (decl.kind == StmtKind_sk_extern) {
    return decl.extern_return;
}
}
    SymbolTable table = ArrayList_SymbolTable_get(&(self->symbol_tables), self->current_table_idx);
    Symbol sym = SymbolTable_lookup_symbol(&(table), name, &(self->symbol_tables));
    if (strlen(sym.name) > 0LL) {
    return sym.type_name;
}
    return "Void";
}
    if (expr.kind == ExprKind_ek_field_access) {
    ExprNode base_node = ArrayList_ExprNode_get(self->expr_pool, expr.field_expr);
    if (base_node.kind == ExprKind_ek_identifier) {
    bool is_static = false;
    int64_t s_idx = 0LL;
    while (s_idx < ArrayList_StmtNode_length(self->stmt_pool)) {
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, s_idx);
    if (((stmt.kind == StmtKind_sk_enum_decl) && (strcmp(stmt.enum_name, base_node.ident_name) == 0)) || ((stmt.kind == StmtKind_sk_error_decl) && (strcmp(stmt.error_name, base_node.ident_name) == 0))) {
    is_static = true;
}
    s_idx = (s_idx + 1LL);
}
    if (is_static) {
    return base_node.ident_name;
}
}
    const char* base_type = TypeChecker_get_expr_type(self, expr.field_expr);
    if ((strlen(base_type) > 0LL) && ((base_type)[0LL] == ((char)(40LL)))) {
    const char* field_name = expr.field_name;
    if ((strlen(field_name) > 1LL) && ((field_name)[0LL] == ((char)(102LL)))) {
    int64_t idx_val = 0LL;
    int64_t fi = 1LL;
    bool valid = true;
    while (fi < strlen(field_name)) {
    char c = (field_name)[fi];
    if ((c >= ((char)(48LL))) && (c <= ((char)(57LL)))) {
    idx_val = ((idx_val * 10LL) + (((int64_t)(c)) - 48LL));
} else {
    valid = false;
}
    fi = (fi + 1LL);
}
    if (valid) {
    const char* inner_types = __kai_str_sub(base_type, 1LL, (strlen(base_type) - 1LL));
    ArrayList_Str types_list = ArrayList_Str_init(self->allocator);
    int64_t start = 0LL;
    int64_t i = 0LL;
    while (i < strlen(inner_types)) {
    if ((inner_types)[i] == ((char)(44LL))) {
    int64_t ts_start = start;
    while ((ts_start < i) && ((inner_types)[ts_start] == ((char)(32LL)))) {
    ts_start = (ts_start + 1LL);
}
    int64_t ts_end = i;
    while ((ts_end > ts_start) && ((inner_types)[(ts_end - 1LL)] == ((char)(32LL)))) {
    ts_end = (ts_end - 1LL);
}
    ArrayList_Str_push(&(types_list), __kai_str_sub(inner_types, ts_start, ts_end));
    start = (i + 1LL);
}
    i = (i + 1LL);
}
    int64_t ts_start = start;
    while ((ts_start < strlen(inner_types)) && ((inner_types)[ts_start] == ((char)(32LL)))) {
    ts_start = (ts_start + 1LL);
}
    int64_t ts_end = strlen(inner_types);
    while ((ts_end > ts_start) && ((inner_types)[(ts_end - 1LL)] == ((char)(32LL)))) {
    ts_end = (ts_end - 1LL);
}
    ArrayList_Str_push(&(types_list), __kai_str_sub(inner_types, ts_start, ts_end));
    if (idx_val < ArrayList_Str_length(&(types_list))) {
    return ArrayList_Str_get(&(types_list), idx_val);
}
}
}
}
    const char* clean_type = "";
    int64_t i = 0LL;
    while (i < strlen(base_type)) {
    char c = (base_type)[i];
    if ((c != ((char)(42LL))) && (c != ((char)(38LL)))) {
    clean_type = concatAlloc(clean_type, char_to_str(c));
}
    i = (i + 1LL);
}
    if ((strlen(clean_type) > 4LL) && (strcmp(substring(clean_type, 0LL, 4LL), "mut ") == 0)) {
    clean_type = substring(clean_type, 4LL, strlen(clean_type));
}
    int64_t s_idx = 0LL;
    while (s_idx < ArrayList_StmtNode_length(self->stmt_pool)) {
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, s_idx);
    if (stmt.kind == StmtKind_sk_struct_decl) {
    if (strcmp(stmt.struct_name, clean_type) == 0) {
    int64_t f_idx = 0LL;
    while (f_idx < ArrayList_StructField_length(&(stmt.struct_fields))) {
    StructField f = ArrayList_StructField_get(&(stmt.struct_fields), f_idx);
    if (strcmp(f.name, expr.field_name) == 0) {
    return f.ftype;
}
    f_idx = (f_idx + 1LL);
}
}
}
    s_idx = (s_idx + 1LL);
}
    return "Void";
}
    if (expr.kind == ExprKind_ek_index) {
    const char* base_type = TypeChecker_get_expr_type(self, expr.idx_expr);
    if (strcmp(base_type, "Str") == 0) {
    return "Char";
}
    if ((strlen(base_type) > 0LL) && ((base_type)[0LL] == ((char)(42LL)))) {
    return substring(base_type, 1LL, strlen(base_type));
}
    return "Void";
}
    if (expr.kind == ExprKind_ek_slice) {
    return TypeChecker_get_expr_type(self, expr.slice_expr);
}
    if (expr.kind == ExprKind_ek_range) {
    return "Range";
}
    if (expr.kind == ExprKind_ek_borrow) {
    const char* base_type = TypeChecker_get_expr_type(self, expr.borrow_expr);
    if (TypeChecker_expr_is_mutable(self, expr.borrow_expr)) {
    return concatAlloc("*mut ", base_type);
}
    return concatAlloc("*", base_type);
}
    if (expr.kind == ExprKind_ek_deref) {
    const char* base_type = TypeChecker_get_expr_type(self, expr.deref_expr);
    if ((strlen(base_type) > 5LL) && (strcmp(substring(base_type, 0LL, 5LL), "*mut ") == 0)) {
    return substring(base_type, 5LL, strlen(base_type));
}
    if ((strlen(base_type) > 5LL) && (strcmp(substring(base_type, 0LL, 5LL), "&mut ") == 0)) {
    return substring(base_type, 5LL, strlen(base_type));
}
    if ((strlen(base_type) > 0LL) && (((base_type)[0LL] == ((char)(42LL))) || ((base_type)[0LL] == ((char)(38LL))))) {
    return substring(base_type, 1LL, strlen(base_type));
}
    return "Void";
}
    if (expr.kind == ExprKind_ek_struct_init) {
    const char* sname = expr.struct_name;
    int64_t dot_pos = (-1LL);
    int64_t j = 0LL;
    while (j < strlen(sname)) {
    if ((sname)[j] == ((char)(46LL))) {
    dot_pos = j;
    break;
}
    j = (j + 1LL);
}
    if (dot_pos >= 0LL) {
    return substring(sname, 0LL, dot_pos);
}
    return sname;
}
    if (expr.kind == ExprKind_ek_method_call) {
    const char* recv_type = TypeChecker_get_expr_type(self, expr.meth_expr);
    const char* clean = "";
    int64_t i = 0LL;
    while (i < strlen(recv_type)) {
    char c = (recv_type)[i];
    if ((c != ((char)(42LL))) && (c != ((char)(38LL)))) {
    clean = concatAlloc(clean, char_to_str(c));
}
    i = (i + 1LL);
}
    if ((strlen(clean) > 4LL) && (strcmp(substring(clean, 0LL, 4LL), "mut ") == 0)) {
    clean = substring(clean, 4LL, strlen(clean));
}
    int64_t lt_pos = (-1LL);
    i = 0LL;
    while (i < strlen(clean)) {
    if ((clean)[i] == ((char)(60LL))) {
    lt_pos = i;
}
    i = (i + 1LL);
}
    if (lt_pos >= 0LL) {
    clean = substring(clean, 0LL, lt_pos);
}
    int64_t m_idx = TypeChecker_find_method_decl(self, recv_type, expr.meth_name);
    if (m_idx >= 0LL) {
    StmtNode decl = ArrayList_StmtNode_get(self->stmt_pool, m_idx);
    const char* ret_type = decl.func_return_type;
    if (((strlen(ret_type) == 1LL) && ((ret_type)[0LL] >= ((char)(65LL)))) && ((ret_type)[0LL] <= ((char)(90LL)))) {
    int64_t gt_pos = (-1LL);
    int64_t gi = 0LL;
    while (gi < strlen(recv_type)) {
    if ((recv_type)[gi] == ((char)(60LL))) {
    gt_pos = gi;
}
    gi = (gi + 1LL);
}
    if (gt_pos >= 0LL) {
    int64_t end_pos = strlen(recv_type);
    gi = (gt_pos + 1LL);
    while (gi < strlen(recv_type)) {
    if ((recv_type)[gi] == ((char)(62LL))) {
    end_pos = gi;
    gi = strlen(recv_type);
}
    gi = (gi + 1LL);
}
    if (end_pos > (gt_pos + 1LL)) {
    const char* first_param = substring(recv_type, (gt_pos + 1LL), end_pos);
    return first_param;
}
}
    return "Void";
}
    return ret_type;
}
    if (TypeChecker_is_imported_name(self, expr.meth_name)) {
    TypeChecker_mark_import_used(self, expr.meth_name);
}
    return "Void";
}
    if (expr.kind == ExprKind_ek_try) {
    const char* inner_ty = TypeChecker_get_expr_type(self, expr.try_expr);
    int64_t excl_pos = (-1LL);
    int64_t i = 0LL;
    while (i < strlen(inner_ty)) {
    if ((inner_ty)[i] == ((char)(33LL))) {
    excl_pos = i;
}
    i = (i + 1LL);
}
    if (excl_pos >= 0LL) {
    return substring(inner_ty, 0LL, excl_pos);
}
    return "Void";
}
    if (expr.kind == ExprKind_ek_catch) {
    const char* inner_ty = TypeChecker_get_expr_type(self, expr.catch_expr);
    if ((strlen(inner_ty) > 0LL) && ((inner_ty)[0LL] == ((char)(63LL)))) {
    return substring(inner_ty, 1LL, strlen(inner_ty));
}
    int64_t excl_pos = (-1LL);
    int64_t i = 0LL;
    while (i < strlen(inner_ty)) {
    if ((inner_ty)[i] == ((char)(33LL))) {
    excl_pos = i;
}
    i = (i + 1LL);
}
    if (excl_pos >= 0LL) {
    return substring(inner_ty, 0LL, excl_pos);
}
    return "Void";
}
    if (expr.kind == ExprKind_ek_tuple) {
    ArrayList_Str types = ArrayList_Str_init(self->allocator);
    int64_t i = 0LL;
    while (i < ArrayList_Int_length(&(expr.tup_elements))) {
    ArrayList_Str_push(&(types), TypeChecker_get_expr_type(self, ArrayList_Int_get(&(expr.tup_elements), i)));
    i = (i + 1LL);
}
    return concatAlloc(concatAlloc("(", str_array_join(types, ", ")), ")");
}
    return "Void";
}
bool TypeChecker_expr_is_mutable(TypeChecker* self, int64_t expr_idx) {
    if (expr_idx < 0LL) {
    return false;
}
    ExprNode expr = ArrayList_ExprNode_get(self->expr_pool, expr_idx);
    if (expr.kind == ExprKind_ek_identifier) {
    SymbolTable table = ArrayList_SymbolTable_get(&(self->symbol_tables), self->current_table_idx);
    Symbol sym = SymbolTable_lookup_symbol(&(table), expr.ident_name, &(self->symbol_tables));
    if (strlen(sym.name) > 0LL) {
    return sym.is_mutable;
}
}
    if (expr.kind == ExprKind_ek_field_access) {
    return TypeChecker_expr_is_mutable(self, expr.field_expr);
}
    if (expr.kind == ExprKind_ek_deref) {
    return true;
}
    return false;
}
bool TypeChecker_is_enum_or_error_type(TypeChecker* self, const char* name) {
    int64_t idx = 0LL;
    while (idx < ArrayList_StmtNode_length(self->stmt_pool)) {
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, idx);
    if ((stmt.kind == StmtKind_sk_enum_decl) && (strcmp(stmt.enum_name, name) == 0)) {
    return true;
}
    if ((stmt.kind == StmtKind_sk_error_decl) && (strcmp(stmt.error_name, name) == 0)) {
    return true;
}
    idx = (idx + 1LL);
}
    return false;
}
bool TypeChecker_is_imported_name(TypeChecker* self, const char* name) {
    int64_t i = 0LL;
    while (i < ArrayList_Str_length(&(self->imported_names))) {
    if (strcmp(ArrayList_Str_get(&(self->imported_names), i), name) == 0) {
    return true;
}
    i = (i + 1LL);
}
    return false;
}
void TypeChecker_mark_import_used(TypeChecker* self, const char* name) {
    int64_t i = 0LL;
    while (i < ArrayList_Str_length(&(self->imported_names))) {
    if (strcmp(ArrayList_Str_get(&(self->imported_names), i), name) == 0) {
    ArrayList_Bool_set(&(self->import_used), i, true);
    return;
}
    i = (i + 1LL);
}
}
void TypeChecker_check_identifier(TypeChecker* self, int64_t expr_idx) {
    ExprNode expr = ArrayList_ExprNode_get(self->expr_pool, expr_idx);
    const char* name = expr.ident_name;
    SymbolTable table = ArrayList_SymbolTable_get(&(self->symbol_tables), self->current_table_idx);
    Symbol sym = SymbolTable_lookup_symbol(&(table), name, &(self->symbol_tables));
    if (strlen(sym.name) > 0LL) {
    if (sym.freed) {
    TypeChecker_err(self, "E0031", concatAlloc(concatAlloc("use of freed value: '", name), "'"), expr.line, expr.col);
} else if (sym.moved) {
    TypeChecker_err(self, "E0009", concatAlloc(concatAlloc("use of moved value: '", name), "'"), expr.line, expr.col);
}
    expr.resolved_symbol_idx = sym.decl_stmt_idx;
    ArrayList_ExprNode_set(self->expr_pool, expr_idx, expr);
} else if (((!TypeChecker_is_enum_or_error_type(self, name)) && (!TypeChecker_is_builtin_type(self, name))) && (!TypeChecker_is_imported_name(self, name))) {
    TypeChecker_err(self, "E0019", concatAlloc(concatAlloc("undefined identifier: '", name), "'"), expr.line, expr.col);
}
    if (TypeChecker_is_imported_name(self, name)) {
    TypeChecker_mark_import_used(self, name);
}
}
void TypeChecker_check_field_access(TypeChecker* self, int64_t expr_idx) {
    ExprNode expr = ArrayList_ExprNode_get(self->expr_pool, expr_idx);
    const char* recv_type = TypeChecker_get_expr_type(self, expr.field_expr);
    if ((strlen(recv_type) > 0LL) && ((recv_type)[0LL] == ((char)(63LL)))) {
    TypeChecker_err(self, "E0011", concatAlloc(concatAlloc(concatAlloc(concatAlloc("cannot access field '", expr.field_name), "' on optional type '"), recv_type), "'. unwrap it first"), expr.line, expr.col);
}
}
void TypeChecker_check_method_call(TypeChecker* self, int64_t expr_idx) {
    ExprNode expr = ArrayList_ExprNode_get(self->expr_pool, expr_idx);
    const char* recv_type = TypeChecker_get_expr_type(self, expr.meth_expr);
    if ((strlen(recv_type) > 0LL) && ((recv_type)[0LL] == ((char)(63LL)))) {
    TypeChecker_err(self, "E0012", concatAlloc(concatAlloc(concatAlloc(concatAlloc("cannot call method '", expr.meth_name), "' on optional type '"), recv_type), "'. unwrap it first"), expr.line, expr.col);
}
}
void TypeChecker_check_return_stmt(TypeChecker* self, int64_t stmt_idx) {
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, stmt_idx);
    const char* val_type = "Void";
    if (stmt.return_value >= 0LL) {
    ExprNode expr = ArrayList_ExprNode_get(self->expr_pool, stmt.return_value);
    if (expr.kind == ExprKind_ek_borrow) {
    ExprNode borrowed = ArrayList_ExprNode_get(self->expr_pool, expr.borrow_expr);
    if (borrowed.kind == ExprKind_ek_identifier) {
    const char* name = borrowed.ident_name;
    SymbolTable table = ArrayList_SymbolTable_get(&(self->symbol_tables), self->current_table_idx);
    Symbol sym = SymbolTable_lookup_symbol(&(table), name, &(self->symbol_tables));
    if ((strcmp(sym.kind, "var") == 0) || (strcmp(sym.kind, "param") == 0)) {
    TypeChecker_err(self, "E0010", concatAlloc(concatAlloc("cannot return reference to local variable '", name), "'"), stmt.line, stmt.col);
}
}
}
    TypeChecker_check_expr(self, stmt.return_value);
    TypeChecker_mark_expr_moved(self, stmt.return_value);
    val_type = TypeChecker_get_expr_type(self, stmt.return_value);
}
    const char* expected_ret = self->current_func_ret_type;
    if ((strlen(expected_ret) > 0LL) && (strcmp(expected_ret, "<infer>") != 0)) {
    if (!TypeChecker_types_compatible(self, expected_ret, val_type)) {
    TypeChecker_err(self, "E0007", concatAlloc(concatAlloc(concatAlloc(concatAlloc("return type mismatch: expected '", expected_ret), "', got '"), val_type), "'"), stmt.line, stmt.col);
}
}
}
void TypeChecker_check_stmt(TypeChecker* self, int64_t stmt_idx) {
    if (stmt_idx < 0LL) {
    return;
}
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, stmt_idx);
    if (stmt.kind == StmtKind_sk_block) {
    TypeChecker_enter_scope(self);
    int64_t i = 0LL;
    while (i < ArrayList_Int_length(&(stmt.block_stmts))) {
    TypeChecker_check_stmt(self, ArrayList_Int_get(&(stmt.block_stmts), i));
    i = (i + 1LL);
}
    bool have_deferred = false;
    ArrayList_SymTrackState pre_drop_snapshot = ArrayList_SymTrackState_init(self->allocator);
    if (ArrayList_Int_length(&(self->scope_deferred_counts)) > 0LL) {
    int64_t snap_cnt = ArrayList_Int_get(&(self->scope_deferred_counts), (ArrayList_Int_length(&(self->scope_deferred_counts)) - 1LL));
    if (snap_cnt > 0LL) {
    pre_drop_snapshot = TypeChecker_capture_tracking_state(self);
    int64_t total_sizes_idx = (ArrayList_Int_length(&(self->scope_deferred_sizes)) - snap_cnt);
    int64_t b = ArrayList_SymTrackState_length(&(self->scope_deferred_flat));
    int64_t w = snap_cnt;
    while (w > 0LL) {
    int64_t sz = ArrayList_Int_get(&(self->scope_deferred_sizes), ((total_sizes_idx + w) - 1LL));
    b = (b - sz);
    w = (w - 1LL);
}
    ArrayList_ArrayList_SymTrackState_ states = ArrayList_ArrayList_SymTrackState__init(self->allocator);
    int64_t si = 0LL;
    int64_t fi = b;
    while (si < snap_cnt) {
    int64_t sz = ArrayList_Int_get(&(self->scope_deferred_sizes), (total_sizes_idx + si));
    ArrayList_SymTrackState snapshot = ArrayList_SymTrackState_init(self->allocator);
    int64_t ei = 0LL;
    while (ei < sz) {
    ArrayList_SymTrackState_push(&(snapshot), ArrayList_SymTrackState_get(&(self->scope_deferred_flat), fi));
    fi = (fi + 1LL);
    ei = (ei + 1LL);
}
    ArrayList_ArrayList_SymTrackState__push(&(states), snapshot);
    si = (si + 1LL);
}
    TypeChecker_merge_and_apply_tracking_state(self, states);
    have_deferred = true;
}
}
    TypeChecker_collect_block_drops(self, stmt_idx);
    if (have_deferred) {
    TypeChecker_restore_tracking_state(self, pre_drop_snapshot);
}
    TypeChecker_exit_scope(self);
    return;
}
    if (stmt.kind == StmtKind_sk_var_decl) {
    TypeChecker_check_expr(self, stmt.vardecl_value);
    const char* val_type = TypeChecker_get_expr_type(self, stmt.vardecl_value);
    const char* var_type = stmt.vardecl_type;
    if (strlen(var_type) == 0LL) {
    var_type = val_type;
} else if (TypeChecker_is_integer_type(self, var_type) && TypeChecker_is_integer_literal(self, stmt.vardecl_value)) {
    ExprNode val_expr = ArrayList_ExprNode_get(self->expr_pool, stmt.vardecl_value);
    int64_t v = TypeChecker_int_literal_value(self, val_expr);
    if (!TypeChecker_fits_in_type(self, v, var_type)) {
    TypeChecker_err(self, "E0030", concatAlloc(concatAlloc(concatAlloc(concatAlloc("integer literal ", int_to_str(v)), " does not fit in type '"), var_type), "'"), stmt.line, stmt.col);
}
} else if (!TypeChecker_types_compatible(self, var_type, val_type)) {
    TypeChecker_err(self, "E0001", concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc("type mismatch in declaration of '", stmt.vardecl_name), "': expected '"), var_type), "', got '"), val_type), "'"), stmt.line, stmt.col);
}
    TypeChecker_define_symbol(self, stmt.vardecl_name, var_type, stmt.vardecl_mut, "var", stmt_idx);
    if ((stmt.vardecl_value >= 0LL) && (!TypeChecker_is_copy_type(self, var_type))) {
    ExprNode src_expr = ArrayList_ExprNode_get(self->expr_pool, stmt.vardecl_value);
    int64_t src_ident = stmt.vardecl_value;
    bool done = false;
    while (!done) {
    if (((src_expr.kind == ExprKind_ek_func_call) && (strcmp(src_expr.func_name, "as") == 0)) && (ArrayList_Int_length(&(src_expr.func_args)) >= 1LL)) {
    src_ident = ArrayList_Int_get(&(src_expr.func_args), 0LL);
    src_expr = ArrayList_ExprNode_get(self->expr_pool, src_ident);
} else {
    done = true;
}
}
    if (src_expr.kind == ExprKind_ek_identifier) {
    SymbolTable table = ArrayList_SymbolTable_get(&(self->symbol_tables), self->current_table_idx);
    Symbol src_sym = SymbolTable_lookup_symbol(&(table), src_expr.ident_name, &(self->symbol_tables));
    if (strlen(src_sym.name) > 0LL) {
    if (src_sym.freed) {
    SymbolTable_mark_freed(&(table), stmt.vardecl_name, &(self->symbol_tables));
} else if (src_sym.moved) {
    SymbolTable_mark_moved(&(table), stmt.vardecl_name, &(self->symbol_tables));
}
    ArrayList_SymbolTable_set(&(self->symbol_tables), self->current_table_idx, table);
}
}
}
    TypeChecker_mark_expr_moved(self, stmt.vardecl_value);
    return;
}
    if (stmt.kind == StmtKind_sk_assignment) {
    if (stmt.assign_target >= 0LL) {
    int64_t root = stmt.assign_target;
    bool done = false;
    while (!done) {
    ExprNode e = ArrayList_ExprNode_get(self->expr_pool, root);
    if (e.kind == ExprKind_ek_field_access) {
    root = e.field_expr;
} else if (e.kind == ExprKind_ek_deref) {
    root = e.deref_expr;
} else {
    done = true;
}
}
    ExprNode re = ArrayList_ExprNode_get(self->expr_pool, root);
    if (re.kind == ExprKind_ek_identifier) {
    SymbolTable tbl = ArrayList_SymbolTable_get(&(self->symbol_tables), self->current_table_idx);
    Symbol rsym = SymbolTable_lookup_symbol(&(tbl), re.ident_name, &(self->symbol_tables));
    if (strlen(rsym.name) > 0LL) {
    if (rsym.moved) {
    SymbolTable_clear_moved(&(tbl), re.ident_name, &(self->symbol_tables));
}
    if (rsym.freed) {
    SymbolTable_clear_freed(&(tbl), re.ident_name, &(self->symbol_tables));
}
    ArrayList_SymbolTable_set(&(self->symbol_tables), self->current_table_idx, tbl);
}
}
}
    TypeChecker_check_expr(self, stmt.assign_target);
    TypeChecker_check_expr(self, stmt.assign_value);
    const char* target_type = "Void";
    if (stmt.assign_target >= 0LL) {
    target_type = TypeChecker_get_expr_type(self, stmt.assign_target);
    ExprNode target_expr = ArrayList_ExprNode_get(self->expr_pool, stmt.assign_target);
    if (target_expr.kind == ExprKind_ek_identifier) {
    SymbolTable table = ArrayList_SymbolTable_get(&(self->symbol_tables), self->current_table_idx);
    Symbol sym = SymbolTable_lookup_symbol(&(table), target_expr.ident_name, &(self->symbol_tables));
    if (strlen(sym.name) > 0LL) {
    if (sym.freed) {
    TypeChecker_err(self, "E0031", concatAlloc(concatAlloc("cannot assign to freed variable '", target_expr.ident_name), "'"), target_expr.line, target_expr.col);
} else if (!sym.is_mutable) {
    TypeChecker_err(self, "E0008", concatAlloc(concatAlloc("cannot assign to immutable variable '", target_expr.ident_name), "'"), target_expr.line, target_expr.col);
}
}
}
}
    const char* val_type = TypeChecker_get_expr_type(self, stmt.assign_value);
    if (TypeChecker_is_integer_type(self, target_type) && TypeChecker_is_integer_literal(self, stmt.assign_value)) {
    ExprNode val_expr = ArrayList_ExprNode_get(self->expr_pool, stmt.assign_value);
    int64_t v = TypeChecker_int_literal_value(self, val_expr);
    if (!TypeChecker_fits_in_type(self, v, target_type)) {
    TypeChecker_err(self, "E0030", concatAlloc(concatAlloc(concatAlloc(concatAlloc("integer literal ", int_to_str(v)), " does not fit in type '"), target_type), "'"), stmt.line, stmt.col);
}
} else if (!TypeChecker_types_compatible(self, target_type, val_type)) {
    const char* target_name = "<non-ident>";
    if (stmt.assign_target >= 0LL) {
    ExprNode target_expr = ArrayList_ExprNode_get(self->expr_pool, stmt.assign_target);
    if (target_expr.kind == ExprKind_ek_identifier) {
    target_name = target_expr.ident_name;
}
}
    TypeChecker_err(self, "E0002", concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc("type mismatch in assignment to '", target_name), "': expected '"), target_type), "', got '"), val_type), "'"), stmt.line, stmt.col);
}
    TypeChecker_mark_expr_moved(self, stmt.assign_value);
    return;
}
    if (stmt.kind == StmtKind_sk_func_decl) {
    const char* old_ret = self->current_func_ret_type;
    self->current_func_ret_type = stmt.func_return_type;
    TypeChecker_define_symbol(self, stmt.func_name, stmt.func_return_type, false, "func", stmt_idx);
    if (ArrayList_Str_length(&(stmt.func_type_params)) > 0LL) {
    return;
}
    TypeChecker_enter_scope(self);
    int64_t i = 0LL;
    while (i < ArrayList_Param_length(&(stmt.func_params))) {
    Param p = ArrayList_Param_get(&(stmt.func_params), i);
    TypeChecker_define_symbol(self, p.name, p.ptype, false, "param", stmt_idx);
    i = (i + 1LL);
}
    TypeChecker_check_stmt(self, stmt.func_body);
    if ((ArrayList_Str_length(&(stmt.func_type_params)) == 0LL) && (ArrayList_Param_length(&(stmt.func_params)) > 0LL)) {
    ArrayList_Int free_indices = ArrayList_Int_init(self->allocator);
    int64_t pi = 0LL;
    while (pi < ArrayList_Param_length(&(stmt.func_params))) {
    Param p = ArrayList_Param_get(&(stmt.func_params), pi);
    SymbolTable table = ArrayList_SymbolTable_get(&(self->symbol_tables), self->current_table_idx);
    Symbol sym = SymbolTable_lookup_symbol(&(table), p.name, &(self->symbol_tables));
    if ((strlen(sym.name) > 0LL) && sym.freed) {
    ArrayList_Int_push(&(free_indices), pi);
}
    pi = (pi + 1LL);
}
    if (ArrayList_Int_length(&(free_indices)) > 0LL) {
    FuncEffect effect = (FuncEffect){ .func_name = stmt.func_name, .free_param_indices = free_indices };
    ArrayList_FuncEffect_push(&(self->func_effects), effect);
}
}
    TypeChecker_exit_scope(self);
    self->current_func_ret_type = old_ret;
    return;
}
    if (stmt.kind == StmtKind_sk_trait_decl) {
    return;
}
    if (stmt.kind == StmtKind_sk_if) {
    TypeChecker_check_expr(self, stmt.if_cond);
    const char* cond_type = TypeChecker_get_expr_type(self, stmt.if_cond);
    if ((strcmp(cond_type, "Bool") != 0) && (strcmp(cond_type, "Void") != 0)) {
    TypeChecker_err(self, "E0024", concatAlloc(concatAlloc("if condition must be Bool, got '", cond_type), "'"), stmt.line, stmt.col);
}
    ArrayList_SymTrackState snapshot = TypeChecker_capture_tracking_state(self);
    TypeChecker_check_stmt(self, stmt.if_then);
    ArrayList_SymTrackState then_state = TypeChecker_capture_tracking_state(self);
    TypeChecker_restore_tracking_state(self, snapshot);
    TypeChecker_check_stmt(self, stmt.if_else);
    ArrayList_SymTrackState else_state = TypeChecker_capture_tracking_state(self);
    TypeChecker_restore_tracking_state(self, snapshot);
    ArrayList_ArrayList_SymTrackState_ states = ArrayList_ArrayList_SymTrackState__init(self->allocator);
    ArrayList_ArrayList_SymTrackState__push(&(states), then_state);
    ArrayList_ArrayList_SymTrackState__push(&(states), else_state);
    TypeChecker_merge_and_apply_tracking_state(self, states);
    return;
}
    if (stmt.kind == StmtKind_sk_if_let) {
    TypeChecker_check_expr(self, stmt.iflet_expr);
    const char* opt_type = TypeChecker_get_expr_type(self, stmt.iflet_expr);
    const char* unwrapped_type = opt_type;
    if ((strlen(opt_type) > 0LL) && ((opt_type)[0LL] == ((char)(63LL)))) {
    unwrapped_type = substring(opt_type, 1LL, strlen(opt_type));
}
    ArrayList_SymTrackState snapshot = TypeChecker_capture_tracking_state(self);
    TypeChecker_enter_scope(self);
    TypeChecker_define_symbol(self, stmt.iflet_var, unwrapped_type, false, "var", stmt_idx);
    TypeChecker_check_stmt(self, stmt.iflet_then);
    TypeChecker_exit_scope(self);
    ArrayList_SymTrackState then_state = TypeChecker_capture_tracking_state(self);
    TypeChecker_restore_tracking_state(self, snapshot);
    TypeChecker_check_stmt(self, stmt.iflet_else);
    ArrayList_SymTrackState else_state = TypeChecker_capture_tracking_state(self);
    TypeChecker_restore_tracking_state(self, snapshot);
    ArrayList_ArrayList_SymTrackState_ states = ArrayList_ArrayList_SymTrackState__init(self->allocator);
    ArrayList_ArrayList_SymTrackState__push(&(states), then_state);
    ArrayList_ArrayList_SymTrackState__push(&(states), else_state);
    TypeChecker_merge_and_apply_tracking_state(self, states);
    return;
}
    if (stmt.kind == StmtKind_sk_while) {
    TypeChecker_check_expr(self, stmt.while_cond);
    const char* cond_type = TypeChecker_get_expr_type(self, stmt.while_cond);
    if ((strcmp(cond_type, "Bool") != 0) && (strcmp(cond_type, "Void") != 0)) {
    TypeChecker_err(self, "E0024", concatAlloc(concatAlloc("while condition must be Bool, got '", cond_type), "'"), stmt.line, stmt.col);
}
    self->loop_depth = (self->loop_depth + 1LL);
    TypeChecker_check_stmt(self, stmt.while_body);
    self->loop_depth = (self->loop_depth - 1LL);
    return;
}
    if (stmt.kind == StmtKind_sk_for) {
    TypeChecker_check_expr(self, stmt.for_start);
    TypeChecker_check_expr(self, stmt.for_end);
    self->loop_depth = (self->loop_depth + 1LL);
    TypeChecker_enter_scope(self);
    const char* iter_type = TypeChecker_get_expr_type(self, stmt.for_start);
    if ((strlen(iter_type) == 0LL) || (strcmp(iter_type, "Void") == 0)) {
    iter_type = "Int";
}
    TypeChecker_define_symbol(self, stmt.for_var, iter_type, false, "var", stmt_idx);
    TypeChecker_check_stmt(self, stmt.for_body);
    TypeChecker_exit_scope(self);
    self->loop_depth = (self->loop_depth - 1LL);
    return;
}
    if (stmt.kind == StmtKind_sk_return) {
    TypeChecker_check_return_stmt(self, stmt_idx);
    return;
}
    if (stmt.kind == StmtKind_sk_expr) {
    TypeChecker_check_expr(self, stmt.expr_stmt);
    return;
}
    if (stmt.kind == StmtKind_sk_unsafe) {
    TypeChecker_check_stmt(self, stmt.unsafe_body);
    return;
}
    if (stmt.kind == StmtKind_sk_match) {
    TypeChecker_check_expr(self, stmt.match_expr);
    ArrayList_SymTrackState snapshot = TypeChecker_capture_tracking_state(self);
    ArrayList_ArrayList_SymTrackState_ arm_states = ArrayList_ArrayList_SymTrackState__init(self->allocator);
    int64_t i = 0LL;
    while (i < ArrayList_MatchCase_length(&(stmt.match_cases))) {
    TypeChecker_restore_tracking_state(self, snapshot);
    MatchCase mc = ArrayList_MatchCase_get(&(stmt.match_cases), i);
    TypeChecker_enter_scope(self);
    PatternNode pat = ArrayList_PatternNode_get(self->pattern_pool, mc.pattern);
    if (pat.kind == PatternKind_pk_variant) {
    const char* expr_type = TypeChecker_get_expr_type(self, stmt.match_expr);
    int64_t enum_idx = TypeChecker_find_enum_decl(self, expr_type);
    bool found_variant = false;
    Variant matched_var = (Variant){ .vname = "", .params = empty_param_array() };
    if (enum_idx != (-1LL)) {
    StmtNode enum_stmt = ArrayList_StmtNode_get(self->stmt_pool, enum_idx);
    int64_t vi = 0LL;
    while (vi < ArrayList_Variant_length(&(enum_stmt.enum_variants))) {
    Variant v = ArrayList_Variant_get(&(enum_stmt.enum_variants), vi);
    bool is_match = false;
    if (strcmp(v.vname, pat.variant_name) == 0) {
    is_match = true;
} else {
    const char* expected_suffix = concatAlloc(".", v.vname);
    int64_t suffix_len = strlen(expected_suffix);
    int64_t pat_len = strlen(pat.variant_name);
    if (pat_len > suffix_len) {
    const char* actual_suffix = substring(pat.variant_name, (pat_len - suffix_len), pat_len);
    if (strcmp(actual_suffix, expected_suffix) == 0) {
    is_match = true;
}
}
}
    if (is_match) {
    matched_var = v;
    found_variant = true;
    break;
}
    vi = (vi + 1LL);
}
}
    int64_t bi = 0LL;
    while (bi < ArrayList_Str_length(&(pat.bindings))) {
    const char* ptype = "Void";
    if (found_variant && (bi < ArrayList_Param_length(&(matched_var.params)))) {
    ptype = ArrayList_Param_get(&(matched_var.params), bi).ptype;
}
    TypeChecker_define_symbol(self, ArrayList_Str_get(&(pat.bindings), bi), ptype, false, "var", stmt_idx);
    bi = (bi + 1LL);
}
}
    TypeChecker_check_stmt(self, mc.body);
    TypeChecker_exit_scope(self);
    ArrayList_ArrayList_SymTrackState__push(&(arm_states), TypeChecker_capture_tracking_state(self));
    i = (i + 1LL);
}
    TypeChecker_restore_tracking_state(self, snapshot);
    if (ArrayList_ArrayList_SymTrackState__length(&(arm_states)) > 0LL) {
    TypeChecker_merge_and_apply_tracking_state(self, arm_states);
}
    return;
}
    if (stmt.kind == StmtKind_sk_impl_block) {
    int64_t i = 0LL;
    while (i < ArrayList_Int_length(&(stmt.impl_methods))) {
    int64_t m_idx = ArrayList_Int_get(&(stmt.impl_methods), i);
    StmtNode m = ArrayList_StmtNode_get(self->stmt_pool, m_idx);
    const char* mangled_name = concatAlloc(concatAlloc(stmt.impl_struct_name, "_"), m.func_name);
    TypeChecker_define_symbol(self, mangled_name, m.func_return_type, false, "func", m_idx);
    const char* old_ret = self->current_func_ret_type;
    self->current_func_ret_type = m.func_return_type;
    TypeChecker_enter_scope(self);
    TypeChecker_define_symbol(self, "self", stmt.impl_struct_name, true, "param", m_idx);
    int64_t pi = 1LL;
    while (pi < ArrayList_Param_length(&(m.func_params))) {
    Param p = ArrayList_Param_get(&(m.func_params), pi);
    TypeChecker_define_symbol(self, p.name, p.ptype, false, "param", m_idx);
    pi = (pi + 1LL);
}
    TypeChecker_check_stmt(self, m.func_body);
    TypeChecker_exit_scope(self);
    self->current_func_ret_type = old_ret;
    i = (i + 1LL);
}
    return;
}
    if (stmt.kind == StmtKind_sk_struct_decl) {
    return;
}
    if (stmt.kind == StmtKind_sk_enum_decl) {
    return;
}
    if (stmt.kind == StmtKind_sk_extern) {
    TypeChecker_define_symbol(self, stmt.extern_name, stmt.extern_return, false, "func", stmt_idx);
    return;
}
    if (stmt.kind == StmtKind_sk_import) {
    return;
}
    if (stmt.kind == StmtKind_sk_cimport) {
    return;
}
    if (stmt.kind == StmtKind_sk_error_decl) {
    return;
}
    if (stmt.kind == StmtKind_sk_break) {
    if (self->loop_depth <= 0LL) {
    TypeChecker_err(self, "E0029", "'break' outside of loop", stmt.line, stmt.col);
}
    return;
}
    if (stmt.kind == StmtKind_sk_continue) {
    if (self->loop_depth <= 0LL) {
    TypeChecker_err(self, "E0029", "'continue' outside of loop", stmt.line, stmt.col);
}
    return;
}
    if (stmt.kind == StmtKind_sk_defer) {
    ArrayList_SymTrackState snapshot = TypeChecker_capture_tracking_state(self);
    TypeChecker_check_stmt(self, stmt.defer_body);
    if (ArrayList_Int_length(&(self->scope_deferred_counts)) > 0LL) {
    int64_t idx = (ArrayList_Int_length(&(self->scope_deferred_counts)) - 1LL);
    ArrayList_SymTrackState post_state = TypeChecker_capture_tracking_state(self);
    int64_t ei = 0LL;
    while (ei < ArrayList_SymTrackState_length(&(post_state))) {
    ArrayList_SymTrackState_push(&(self->scope_deferred_flat), ArrayList_SymTrackState_get(&(post_state), ei));
    ei = (ei + 1LL);
}
    ArrayList_Int_push(&(self->scope_deferred_sizes), ArrayList_SymTrackState_length(&(post_state)));
    int64_t count = ArrayList_Int_get(&(self->scope_deferred_counts), idx);
    count = (count + 1LL);
    ArrayList_Int_set(&(self->scope_deferred_counts), idx, count);
}
    TypeChecker_restore_tracking_state(self, snapshot);
    return;
}
    if (stmt.kind == StmtKind_sk_errdefer) {
    ArrayList_SymTrackState snapshot = TypeChecker_capture_tracking_state(self);
    TypeChecker_check_stmt(self, stmt.errdefer_body);
    if (ArrayList_Int_length(&(self->scope_deferred_counts)) > 0LL) {
    int64_t idx = (ArrayList_Int_length(&(self->scope_deferred_counts)) - 1LL);
    ArrayList_SymTrackState post_state = TypeChecker_capture_tracking_state(self);
    int64_t ei = 0LL;
    while (ei < ArrayList_SymTrackState_length(&(post_state))) {
    ArrayList_SymTrackState_push(&(self->scope_deferred_flat), ArrayList_SymTrackState_get(&(post_state), ei));
    ei = (ei + 1LL);
}
    ArrayList_Int_push(&(self->scope_deferred_sizes), ArrayList_SymTrackState_length(&(post_state)));
    int64_t count = ArrayList_Int_get(&(self->scope_deferred_counts), idx);
    count = (count + 1LL);
    ArrayList_Int_set(&(self->scope_deferred_counts), idx, count);
}
    TypeChecker_restore_tracking_state(self, snapshot);
    return;
}
    if (stmt.kind == StmtKind_sk_print) {
    TypeChecker_check_expr(self, stmt.print_value);
    return;
}
}
void TypeChecker_check_expr(TypeChecker* self, int64_t expr_idx) {
    if (expr_idx < 0LL) {
    return;
}
    TypeChecker_check_expr_inner(self, expr_idx);
    ExprNode expr = ArrayList_ExprNode_get(self->expr_pool, expr_idx);
    const char* ty_name = TypeChecker_get_expr_type(self, expr_idx);
    expr.type_id = TypeChecker_map_type_to_id(self, ty_name);
    ArrayList_ExprNode_set(self->expr_pool, expr_idx, expr);
}
void TypeChecker_check_expr_inner(TypeChecker* self, int64_t expr_idx) {
    if (expr_idx < 0LL) {
    return;
}
    ExprNode expr = ArrayList_ExprNode_get(self->expr_pool, expr_idx);
    if (expr.kind == ExprKind_ek_identifier) {
    TypeChecker_check_identifier(self, expr_idx);
    return;
}
    if (expr.kind == ExprKind_ek_binary_op) {
    TypeChecker_check_expr(self, expr.binop_left);
    TypeChecker_check_expr(self, expr.binop_right);
    const char* left_type = TypeChecker_get_expr_type(self, expr.binop_left);
    const char* right_type = TypeChecker_get_expr_type(self, expr.binop_right);
    const char* op = expr.binop_op;
    if (strcmp(op, "+") == 0) {
    if (((!TypeChecker_is_numeric_type(self, left_type)) && (strcmp(left_type, "Str") != 0)) && (strcmp(left_type, "Void") != 0)) {
    TypeChecker_err(self, "E0025", concatAlloc(concatAlloc("left operand of '+' must be numeric or Str, got '", left_type), "'"), expr.line, expr.col);
}
    if (((!TypeChecker_is_numeric_type(self, right_type)) && (strcmp(right_type, "Str") != 0)) && (strcmp(right_type, "Void") != 0)) {
    TypeChecker_err(self, "E0025", concatAlloc(concatAlloc("right operand of '+' must be numeric or Str, got '", right_type), "'"), expr.line, expr.col);
}
} else if ((((strcmp(op, "-") == 0) || (strcmp(op, "*") == 0)) || (strcmp(op, "/") == 0)) || (strcmp(op, "%") == 0)) {
    if ((!TypeChecker_is_numeric_type(self, left_type)) && (strcmp(left_type, "Void") != 0)) {
    TypeChecker_err(self, "E0025", concatAlloc(concatAlloc(concatAlloc(concatAlloc("left operand of '", op), "' must be numeric, got '"), left_type), "'"), expr.line, expr.col);
}
    if ((!TypeChecker_is_numeric_type(self, right_type)) && (strcmp(right_type, "Void") != 0)) {
    TypeChecker_err(self, "E0025", concatAlloc(concatAlloc(concatAlloc(concatAlloc("right operand of '", op), "' must be numeric, got '"), right_type), "'"), expr.line, expr.col);
}
} else if ((strcmp(op, "&&") == 0) || (strcmp(op, "||") == 0)) {
    if ((strcmp(left_type, "Bool") != 0) && (strcmp(left_type, "Void") != 0)) {
    TypeChecker_err(self, "E0025", concatAlloc(concatAlloc(concatAlloc(concatAlloc("left operand of '", op), "' must be Bool, got '"), left_type), "'"), expr.line, expr.col);
}
    if ((strcmp(right_type, "Bool") != 0) && (strcmp(right_type, "Void") != 0)) {
    TypeChecker_err(self, "E0025", concatAlloc(concatAlloc(concatAlloc(concatAlloc("right operand of '", op), "' must be Bool, got '"), right_type), "'"), expr.line, expr.col);
}
} else if (((((strcmp(op, "|") == 0) || (strcmp(op, "^") == 0)) || (strcmp(op, "&") == 0)) || (strcmp(op, "<<") == 0)) || (strcmp(op, ">>") == 0)) {
    if ((!TypeChecker_is_integer_type(self, left_type)) && (strcmp(left_type, "Void") != 0)) {
    TypeChecker_err(self, "E0025", concatAlloc(concatAlloc(concatAlloc(concatAlloc("left operand of '", op), "' must be an integer type, got '"), left_type), "'"), expr.line, expr.col);
}
    if ((!TypeChecker_is_integer_type(self, right_type)) && (strcmp(right_type, "Void") != 0)) {
    TypeChecker_err(self, "E0025", concatAlloc(concatAlloc(concatAlloc(concatAlloc("right operand of '", op), "' must be an integer type, got '"), right_type), "'"), expr.line, expr.col);
}
} else if ((((((strcmp(op, "==") == 0) || (strcmp(op, "!=") == 0)) || (strcmp(op, "<") == 0)) || (strcmp(op, ">") == 0)) || (strcmp(op, "<=") == 0)) || (strcmp(op, ">=") == 0)) {
    if (((strcmp(left_type, "Void") != 0) && (strcmp(right_type, "Void") != 0)) && (!TypeChecker_types_compatible(self, left_type, right_type))) {
    TypeChecker_err(self, "E0025", concatAlloc(concatAlloc(concatAlloc(concatAlloc("type mismatch in comparison: '", left_type), "' and '"), right_type), "' are not compatible"), expr.line, expr.col);
}
}
    return;
}
    if (expr.kind == ExprKind_ek_unary_op) {
    TypeChecker_check_expr(self, expr.unop_operand);
    const char* operand_type = TypeChecker_get_expr_type(self, expr.unop_operand);
    const char* binop = expr.unop_op;
    if (strcmp(binop, "!") == 0) {
    if ((strcmp(operand_type, "Bool") != 0) && (strcmp(operand_type, "Void") != 0)) {
    TypeChecker_err(self, "E0026", concatAlloc(concatAlloc("operand of '!' must be Bool, got '", operand_type), "'"), expr.line, expr.col);
}
} else if (strcmp(binop, "-") == 0) {
    if ((!TypeChecker_is_numeric_type(self, operand_type)) && (strcmp(operand_type, "Void") != 0)) {
    TypeChecker_err(self, "E0026", concatAlloc(concatAlloc("operand of negation must be numeric, got '", operand_type), "'"), expr.line, expr.col);
}
} else if (strcmp(binop, "~") == 0) {
    if ((!TypeChecker_is_integer_type(self, operand_type)) && (strcmp(operand_type, "Void") != 0)) {
    TypeChecker_err(self, "E0026", concatAlloc(concatAlloc("operand of '~' must be an integer type, got '", operand_type), "'"), expr.line, expr.col);
}
}
    return;
}
    if (expr.kind == ExprKind_ek_func_call) {
    const char* name = expr.func_name;
    if (strcmp(name, "free") == 0) {
    int64_t i = 0LL;
    while (i < ArrayList_Int_length(&(expr.func_args))) {
    int64_t arg = ArrayList_Int_get(&(expr.func_args), i);
    TypeChecker_check_expr(self, arg);
    i = (i + 1LL);
}
    if (ArrayList_Int_length(&(expr.func_args)) >= 1LL) {
    TypeChecker_mark_expr_freed(self, ArrayList_Int_get(&(expr.func_args), 0LL));
}
    if (TypeChecker_is_imported_name(self, name)) {
    TypeChecker_mark_import_used(self, name);
}
} else if (strcmp(name, "as") == 0) {
    int64_t i = 0LL;
    while (i < ArrayList_Int_length(&(expr.func_args))) {
    int64_t arg = ArrayList_Int_get(&(expr.func_args), i);
    TypeChecker_check_expr(self, arg);
    i = (i + 1LL);
}
} else {
    int64_t i = 0LL;
    while (i < ArrayList_Int_length(&(expr.func_args))) {
    TypeChecker_check_expr(self, ArrayList_Int_get(&(expr.func_args), i));
    i = (i + 1LL);
}
    ArrayList_Int free_set = ArrayList_Int_init(self->allocator);
    int64_t ei = 0LL;
    while (ei < ArrayList_FuncEffect_length(&(self->func_effects))) {
    FuncEffect eff = ArrayList_FuncEffect_get(&(self->func_effects), ei);
    if (strcmp(eff.func_name, name) == 0) {
    int64_t fi = 0LL;
    while (fi < ArrayList_Int_length(&(eff.free_param_indices))) {
    ArrayList_Int_push(&(free_set), ArrayList_Int_get(&(eff.free_param_indices), fi));
    fi = (fi + 1LL);
}
}
    ei = (ei + 1LL);
}
    i = 0LL;
    while (i < ArrayList_Int_length(&(expr.func_args))) {
    bool is_freed = false;
    int64_t fi = 0LL;
    while (fi < ArrayList_Int_length(&(free_set))) {
    if (ArrayList_Int_get(&(free_set), fi) == i) {
    is_freed = true;
    break;
}
    fi = (fi + 1LL);
}
    if (is_freed) {
    TypeChecker_mark_expr_freed(self, ArrayList_Int_get(&(expr.func_args), i));
} else {
    TypeChecker_mark_expr_moved(self, ArrayList_Int_get(&(expr.func_args), i));
}
    i = (i + 1LL);
}
}
    if ((((((((((((strcmp(name, "cast") == 0) || (strcmp(name, "as") == 0)) || (strcmp(name, "size_of") == 0)) || (strcmp(name, "free") == 0)) || (strcmp(name, "Char") == 0)) || (strcmp(name, "Int") == 0)) || (strcmp(name, "Float") == 0)) || (strcmp(name, "Bool") == 0)) || (strcmp(name, "printf") == 0)) || (strcmp(name, "fprintf") == 0)) || (strcmp(name, "sprintf") == 0)) || (strcmp(name, "snprintf") == 0)) {
    return;
}
    int64_t func_idx = TypeChecker_find_func_decl(self, name);
    if (func_idx >= 0LL) {
    StmtNode decl = ArrayList_StmtNode_get(self->stmt_pool, func_idx);
    bool is_extern = (decl.kind == StmtKind_sk_extern);
    ArrayList_Param params = decl.func_params;
    ArrayList_Str type_params = decl.func_type_params;
    if (is_extern) {
    params = decl.extern_params;
    type_params = empty_str_array();
}
    if (ArrayList_Param_length(&(params)) != ArrayList_Int_length(&(expr.func_args))) {
    TypeChecker_err(self, "E0005", concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc("argument count mismatch for function '", name), "': expected "), int_to_str(ArrayList_Param_length(&(params)))), ", got "), int_to_str(ArrayList_Int_length(&(expr.func_args)))), expr.line, expr.col);
} else {
    if (ArrayList_Str_length(&(type_params)) > 0LL) {
    return;
}
    int64_t arg_i = 0LL;
    while (arg_i < ArrayList_Int_length(&(expr.func_args))) {
    int64_t arg = ArrayList_Int_get(&(expr.func_args), arg_i);
    Param param = ArrayList_Param_get(&(params), arg_i);
    const char* arg_type = TypeChecker_get_expr_type(self, arg);
    const char* ptype = param.ptype;
    bool is_generic_param = (((strlen(ptype) == 1LL) && ((ptype)[0LL] >= ((char)(65LL)))) && ((ptype)[0LL] <= ((char)(90LL))));
    if ((!is_generic_param) && (!TypeChecker_types_compatible(self, ptype, arg_type))) {
    if (TypeChecker_is_integer_type(self, ptype) && TypeChecker_is_integer_literal(self, arg)) {
    int64_t v = TypeChecker_int_literal_value(self, ArrayList_ExprNode_get(self->expr_pool, arg));
    if (!TypeChecker_fits_in_type(self, v, ptype)) {
    TypeChecker_err(self, "E0030", concatAlloc(concatAlloc(concatAlloc(concatAlloc("integer literal ", int_to_str(v)), " does not fit in type '"), ptype), "'"), expr.line, expr.col);
}
} else {
    TypeChecker_err(self, "E0003", concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc("argument type mismatch for function '", name), "', parameter '"), param.name), "': expected '"), ptype), "', got '"), arg_type), "'"), expr.line, expr.col);
}
}
    arg_i = (arg_i + 1LL);
}
}
} else if ((!TypeChecker_is_imported_name(self, name)) && (!TypeChecker_is_standard_c_func(self, name))) {
    if (TypeChecker_is_builtin_type(self, name) || TypeChecker_is_struct_type(self, name)) {
} else {
    TypeChecker_err(self, "E0020", concatAlloc(concatAlloc("undefined function: '", name), "'"), expr.line, expr.col);
}
}
    if (TypeChecker_is_imported_name(self, name)) {
    TypeChecker_mark_import_used(self, name);
} else {
    int64_t ui = 0LL;
    while (ui < ArrayList_Str_length(&(self->imported_names))) {
    const char* iname = ArrayList_Str_get(&(self->imported_names), ui);
    if (((strlen(name) > strlen(iname)) && (strcmp(__kai_str_sub(name, 0LL, strlen(iname)), iname) == 0)) && ((name)[strlen(iname)] == ((char)(95LL)))) {
    TypeChecker_mark_import_used(self, iname);
}
    ui = (ui + 1LL);
}
}
    return;
}
    if (expr.kind == ExprKind_ek_field_access) {
    TypeChecker_check_expr(self, expr.field_expr);
    TypeChecker_check_field_access(self, expr_idx);
    return;
}
    if (expr.kind == ExprKind_ek_method_call) {
    TypeChecker_check_expr(self, expr.meth_expr);
    TypeChecker_check_method_call(self, expr_idx);
    int64_t i = 0LL;
    while (i < ArrayList_Int_length(&(expr.meth_args))) {
    int64_t arg = ArrayList_Int_get(&(expr.meth_args), i);
    TypeChecker_check_expr(self, arg);
    if ((strcmp(expr.meth_name, "free") == 0) && (i == 0LL)) {
    TypeChecker_mark_expr_freed(self, arg);
} else {
    TypeChecker_mark_expr_moved(self, arg);
}
    i = (i + 1LL);
}
    const char* recv_type = TypeChecker_get_expr_type(self, expr.meth_expr);
    const char* meth_name = expr.meth_name;
    int64_t meth_idx = TypeChecker_find_method_decl(self, recv_type, meth_name);
    if (meth_idx >= 0LL) {
    StmtNode decl = ArrayList_StmtNode_get(self->stmt_pool, meth_idx);
    if (ArrayList_Param_length(&(decl.func_params)) != (ArrayList_Int_length(&(expr.meth_args)) + 1LL)) {
    TypeChecker_err(self, "E0006", concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc("argument count mismatch for method '", meth_name), "': expected "), int_to_str((ArrayList_Param_length(&(decl.func_params)) - 1LL))), ", got "), int_to_str(ArrayList_Int_length(&(expr.meth_args)))), expr.line, expr.col);
} else {
    int64_t arg_i = 0LL;
    while (arg_i < ArrayList_Int_length(&(expr.meth_args))) {
    int64_t arg = ArrayList_Int_get(&(expr.meth_args), arg_i);
    Param param = ArrayList_Param_get(&(decl.func_params), (arg_i + 1LL));
    const char* arg_type = TypeChecker_get_expr_type(self, arg);
    if (!TypeChecker_types_compatible(self, param.ptype, arg_type)) {
    if (TypeChecker_is_integer_type(self, param.ptype) && TypeChecker_is_integer_literal(self, arg)) {
    int64_t v = TypeChecker_int_literal_value(self, ArrayList_ExprNode_get(self->expr_pool, arg));
    if (!TypeChecker_fits_in_type(self, v, param.ptype)) {
    TypeChecker_err(self, "E0030", concatAlloc(concatAlloc(concatAlloc(concatAlloc("integer literal ", int_to_str(v)), " does not fit in type '"), param.ptype), "'"), expr.line, expr.col);
}
} else {
    TypeChecker_err(self, "E0003", concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc("argument type mismatch for method '", meth_name), "', parameter '"), param.name), "': expected '"), param.ptype), "', got '"), arg_type), "'"), expr.line, expr.col);
}
}
    arg_i = (arg_i + 1LL);
}
}
} else if ((strcmp(recv_type, "Void") != 0) && (!TypeChecker_is_imported_name(self, meth_name))) {
    TypeChecker_err(self, "E0022", concatAlloc(concatAlloc(concatAlloc(concatAlloc("undefined method: '", meth_name), "' for type '"), recv_type), "'"), expr.line, expr.col);
}
    if (TypeChecker_is_imported_name(self, meth_name)) {
    TypeChecker_mark_import_used(self, meth_name);
}
    return;
}
    if (expr.kind == ExprKind_ek_index) {
    TypeChecker_check_expr(self, expr.idx_expr);
    TypeChecker_check_expr(self, expr.idx_index);
    const char* index_type = TypeChecker_get_expr_type(self, expr.idx_index);
    if ((strcmp(index_type, "Int") != 0) && (strcmp(index_type, "Void") != 0)) {
    TypeChecker_err(self, "E0027", concatAlloc(concatAlloc("index must be Int, got '", index_type), "'"), expr.line, expr.col);
}
    const char* base_type = TypeChecker_get_expr_type(self, expr.idx_expr);
    if ((strcmp(base_type, "Str") != 0) && (strcmp(base_type, "Void") != 0)) {
    if ((strlen(base_type) == 0LL) || (((base_type)[0LL] != ((char)(42LL))) && ((base_type)[0LL] != ((char)(38LL))))) {
    if (!((strlen(base_type) >= 2LL) && (strcmp(__kai_str_sub(base_type, 0LL, 2LL), "[]") == 0))) {
    TypeChecker_err(self, "E0028", concatAlloc(concatAlloc("type '", base_type), "' is not indexable"), expr.line, expr.col);
}
}
}
    return;
}
    if (expr.kind == ExprKind_ek_slice) {
    TypeChecker_check_expr(self, expr.slice_expr);
    if (expr.slice_lower >= 0LL) {
    TypeChecker_check_expr(self, expr.slice_lower);
}
    if (expr.slice_upper >= 0LL) {
    TypeChecker_check_expr(self, expr.slice_upper);
}
    return;
}
    if (expr.kind == ExprKind_ek_range) {
    TypeChecker_check_expr(self, expr.range_start);
    TypeChecker_check_expr(self, expr.range_end);
    return;
}
    if (expr.kind == ExprKind_ek_borrow) {
    TypeChecker_check_expr(self, expr.borrow_expr);
    return;
}
    if (expr.kind == ExprKind_ek_deref) {
    TypeChecker_check_expr(self, expr.deref_expr);
    return;
}
    if (expr.kind == ExprKind_ek_struct_init) {
    int64_t i = 0LL;
    while (i < ArrayList_FieldInit_length(&(expr.struct_fields))) {
    FieldInit f = ArrayList_FieldInit_get(&(expr.struct_fields), i);
    TypeChecker_check_expr(self, f.value);
    TypeChecker_mark_expr_moved(self, f.value);
    i = (i + 1LL);
}
    const char* struct_name = expr.struct_name;
    int64_t dot_pos = (-1LL);
    int64_t j = 0LL;
    while (j < strlen(struct_name)) {
    if ((struct_name)[j] == ((char)(46LL))) {
    dot_pos = j;
    break;
}
    j = (j + 1LL);
}
    if (dot_pos >= 0LL) {
    const char* enum_name = substring(struct_name, 0LL, dot_pos);
    int64_t enum_idx = TypeChecker_find_enum_decl(self, enum_name);
    if (enum_idx < 0LL) {
    if (!TypeChecker_is_imported_name(self, enum_name)) {
    TypeChecker_err(self, "E0021", concatAlloc(concatAlloc("undefined enum: '", enum_name), "'"), expr.line, expr.col);
}
    return;
}
    StmtNode decl = ArrayList_StmtNode_get(self->stmt_pool, enum_idx);
    const char* var_name = substring(struct_name, (dot_pos + 1LL), strlen(struct_name));
    bool found_var = false;
    Variant matched_var = (Variant){ .vname = "", .params = empty_param_array() };
    int64_t vi = 0LL;
    while (vi < ArrayList_Variant_length(&(decl.enum_variants))) {
    Variant v = ArrayList_Variant_get(&(decl.enum_variants), vi);
    if (strcmp(v.vname, var_name) == 0) {
    found_var = true;
    matched_var = v;
    break;
}
    vi = (vi + 1LL);
}
    if (!found_var) {
    TypeChecker_err(self, "E0021", concatAlloc(concatAlloc(concatAlloc(concatAlloc("enum '", enum_name), "' has no variant '"), var_name), "'"), expr.line, expr.col);
    return;
}
    int64_t fi = 0LL;
    while (fi < ArrayList_FieldInit_length(&(expr.struct_fields))) {
    FieldInit f = ArrayList_FieldInit_get(&(expr.struct_fields), fi);
    bool found = false;
    int64_t pfi = 0LL;
    while (pfi < ArrayList_Param_length(&(matched_var.params))) {
    Param param = ArrayList_Param_get(&(matched_var.params), pfi);
    if (strcmp(param.name, f.name) == 0) {
    found = true;
    const char* val_type = TypeChecker_get_expr_type(self, f.value);
    if (!TypeChecker_types_compatible(self, param.ptype, val_type)) {
    TypeChecker_err(self, "E0003", concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc("type mismatch for enum variant field '", f.name), "': expected '"), param.ptype), "', got '"), val_type), "'"), expr.line, expr.col);
}
    break;
}
    pfi = (pfi + 1LL);
}
    if (!found) {
    TypeChecker_err(self, "E0022", concatAlloc(concatAlloc(concatAlloc(concatAlloc("enum variant '", var_name), "' has no field '"), f.name), "'"), expr.line, expr.col);
}
    fi = (fi + 1LL);
}
    return;
}
    int64_t struct_idx = TypeChecker_find_struct_decl(self, struct_name);
    if (struct_idx < 0LL) {
    if (!TypeChecker_is_imported_name(self, struct_name)) {
    TypeChecker_err(self, "E0021", concatAlloc(concatAlloc("undefined struct: '", struct_name), "'"), expr.line, expr.col);
}
    return;
}
    if (TypeChecker_is_imported_name(self, struct_name)) {
    TypeChecker_mark_import_used(self, struct_name);
}
    StmtNode decl = ArrayList_StmtNode_get(self->stmt_pool, struct_idx);
    int64_t fi = 0LL;
    while (fi < ArrayList_FieldInit_length(&(expr.struct_fields))) {
    FieldInit f = ArrayList_FieldInit_get(&(expr.struct_fields), fi);
    bool found = false;
    int64_t dfi = 0LL;
    while (dfi < ArrayList_StructField_length(&(decl.struct_fields))) {
    StructField df = ArrayList_StructField_get(&(decl.struct_fields), dfi);
    if (strcmp(df.name, f.name) == 0) {
    found = true;
    const char* val_type = TypeChecker_get_expr_type(self, f.value);
    if (!TypeChecker_types_compatible(self, df.ftype, val_type)) {
    TypeChecker_err(self, "E0004", concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc("type mismatch in initializer for field '", f.name), "' of struct '"), struct_name), "': expected '"), df.ftype), "', got '"), val_type), "'"), expr.line, expr.col);
}
}
    dfi = (dfi + 1LL);
}
    if (!found) {
    TypeChecker_err(self, "E0013", concatAlloc(concatAlloc(concatAlloc(concatAlloc("field '", f.name), "' does not exist in struct '"), struct_name), "'"), expr.line, expr.col);
}
    fi = (fi + 1LL);
}
    return;
}
    if (expr.kind == ExprKind_ek_try) {
    TypeChecker_check_expr(self, expr.try_expr);
    const char* inner_ty = TypeChecker_get_expr_type(self, expr.try_expr);
    if (strcmp(inner_ty, "Void") == 0) {
    return;
}
    int64_t excl_pos = (-1LL);
    int64_t i = 0LL;
    while (i < strlen(inner_ty)) {
    if ((inner_ty)[i] == ((char)(33LL))) {
    excl_pos = i;
}
    i = (i + 1LL);
}
    if (excl_pos < 0LL) {
    TypeChecker_err(self, "E0014", concatAlloc(concatAlloc("cannot use 'try' on non-error-union type '", inner_ty), "'"), expr.line, expr.col);
} else {
    const char* error_set = substring(inner_ty, (excl_pos + 1LL), strlen(inner_ty));
    const char* expected_ret = self->current_func_ret_type;
    int64_t func_excl = (-1LL);
    i = 0LL;
    while (i < strlen(expected_ret)) {
    if ((expected_ret)[i] == ((char)(33LL))) {
    func_excl = i;
}
    i = (i + 1LL);
}
    if (func_excl < 0LL) {
    TypeChecker_err(self, "E0015", concatAlloc(concatAlloc("cannot use 'try' in a function that returns non-error-union type '", expected_ret), "'"), expr.line, expr.col);
} else {
    const char* func_err = substring(expected_ret, (func_excl + 1LL), strlen(expected_ret));
    if (!TypeChecker_types_compatible(self, func_err, error_set)) {
    TypeChecker_err(self, "E0016", concatAlloc(concatAlloc(concatAlloc(concatAlloc("error set '", error_set), "' of try expression is not compatible with function error set '"), func_err), "'"), expr.line, expr.col);
}
}
}
    return;
}
    if (expr.kind == ExprKind_ek_catch) {
    TypeChecker_check_expr(self, expr.catch_expr);
    const char* inner_ty = TypeChecker_get_expr_type(self, expr.catch_expr);
    if (strcmp(inner_ty, "Void") == 0) {
    TypeChecker_enter_scope(self);
    if (strlen(expr.catch_var) > 0LL) {
    TypeChecker_define_symbol(self, expr.catch_var, "Void", false, "var", (-1LL));
}
    TypeChecker_check_stmt(self, expr.catch_fallback);
    TypeChecker_exit_scope(self);
    return;
}
    if ((strlen(inner_ty) > 0LL) && ((inner_ty)[0LL] == ((char)(63LL)))) {
    const char* val_type = substring(inner_ty, 1LL, strlen(inner_ty));
    TypeChecker_enter_scope(self);
    if (strlen(expr.catch_var) > 0LL) {
    TypeChecker_define_symbol(self, expr.catch_var, "Void", false, "var", (-1LL));
}
    TypeChecker_check_stmt(self, expr.catch_fallback);
    TypeChecker_exit_scope(self);
    const char* fallback_yields = TypeChecker_get_block_yield_type(self, expr.catch_fallback);
    if (!TypeChecker_types_compatible(self, val_type, fallback_yields)) {
    TypeChecker_err(self, "E0018", concatAlloc(concatAlloc(concatAlloc(concatAlloc("catch fallback type '", fallback_yields), "' is not compatible with expected type '"), val_type), "'"), expr.line, expr.col);
}
    return;
}
    int64_t excl_pos = (-1LL);
    int64_t i = 0LL;
    while (i < strlen(inner_ty)) {
    if ((inner_ty)[i] == ((char)(33LL))) {
    excl_pos = i;
}
    i = (i + 1LL);
}
    if (excl_pos < 0LL) {
    TypeChecker_err(self, "E0017", concatAlloc(concatAlloc("cannot use 'catch' on non-error-union type '", inner_ty), "'"), expr.line, expr.col);
} else {
    const char* val_type = substring(inner_ty, 0LL, excl_pos);
    const char* error_set = substring(inner_ty, (excl_pos + 1LL), strlen(inner_ty));
    TypeChecker_enter_scope(self);
    if (strlen(expr.catch_var) > 0LL) {
    TypeChecker_define_symbol(self, expr.catch_var, error_set, false, "var", (-1LL));
}
    TypeChecker_check_stmt(self, expr.catch_fallback);
    TypeChecker_exit_scope(self);
    const char* fallback_yields = TypeChecker_get_block_yield_type(self, expr.catch_fallback);
    if (!TypeChecker_types_compatible(self, val_type, fallback_yields)) {
    TypeChecker_err(self, "E0018", concatAlloc(concatAlloc(concatAlloc(concatAlloc("catch fallback type '", fallback_yields), "' is not compatible with expected type '"), val_type), "'"), expr.line, expr.col);
}
}
    return;
}
}
int64_t TypeChecker_map_type_to_id(TypeChecker* self, const char* type_name) {
    if ((strcmp(type_name, "Void") == 0) || (strlen(type_name) == 0LL)) {
    return 0LL;
}
    if (strcmp(type_name, "Int") == 0) {
    return 1LL;
}
    if (strcmp(type_name, "Float") == 0) {
    return 2LL;
}
    if (strcmp(type_name, "Bool") == 0) {
    return 3LL;
}
    if (strcmp(type_name, "Char") == 0) {
    return 4LL;
}
    if (strcmp(type_name, "Str") == 0) {
    return 5LL;
}
    if ((strlen(type_name) > 0LL) && ((type_name)[0LL] == ((char)(42LL)))) {
    const char* element = __kai_str_sub(type_name, 1LL, strlen(type_name));
    int64_t element_id = TypeChecker_map_type_to_id(self, element);
    return TypeArena_intern_pointer(&(self->type_arena), element_id);
}
    return TypeArena_intern_struct(&(self->type_arena), type_name, (-1LL));
}
int64_t TypeChecker_get_expr_type_id(TypeChecker* self, int64_t expr_idx) {
    if (expr_idx < 0LL) {
    return 0LL;
}
    ExprNode expr = ArrayList_ExprNode_get(self->expr_pool, expr_idx);
    if (expr.type_id >= 0LL) {
    return expr.type_id;
}
    const char* ty_name = TypeChecker_get_expr_type(self, expr_idx);
    return TypeChecker_map_type_to_id(self, ty_name);
}
SymbolTable SymbolTable_init(KaiAllocator* allocator, int64_t parent_idx) {
    SymbolTable self = (SymbolTable){0};
    self.allocator = allocator;
    self.entries = ArrayList_Symbol_init(allocator);
    self.parent_idx = parent_idx;
    return self;
}
void SymbolTable_define(SymbolTable* self, const char* name, const char* type_name, bool is_mutable, const char* kind, const char* llvm_value, int64_t decl_stmt_idx) {
    ArrayList_Symbol_push(&(self->entries), (Symbol){ .name = name, .type_name = type_name, .is_mutable = is_mutable, .kind = kind, .llvm_value = llvm_value, .moved = false, .freed = false, .decl_stmt_idx = decl_stmt_idx });
}
int64_t SymbolTable_lookup(SymbolTable* self, const char* name, ArrayList_SymbolTable* tables) {
    int64_t i = 0LL;
    while (i < ArrayList_Symbol_length(&(self->entries))) {
    if (strcmp(ArrayList_Symbol_get(&(self->entries), i).name, name) == 0) {
    return i;
}
    i = (i + 1LL);
}
    if (self->parent_idx >= 0LL) {
    SymbolTable parent = ArrayList_SymbolTable_get(tables, self->parent_idx);
    return SymbolTable_lookup(&(parent), name, tables);
}
    return (-1LL);
}
Symbol SymbolTable_lookup_symbol(SymbolTable* self, const char* name, ArrayList_SymbolTable* tables) {
    int64_t i = 0LL;
    while (i < ArrayList_Symbol_length(&(self->entries))) {
    if (strcmp(ArrayList_Symbol_get(&(self->entries), i).name, name) == 0) {
    return ArrayList_Symbol_get(&(self->entries), i);
}
    i = (i + 1LL);
}
    if (self->parent_idx >= 0LL) {
    SymbolTable parent = ArrayList_SymbolTable_get(tables, self->parent_idx);
    return SymbolTable_lookup_symbol(&(parent), name, tables);
}
    return (Symbol){ .name = "", .type_name = "", .is_mutable = false, .kind = "", .llvm_value = "", .moved = false, .freed = false, .decl_stmt_idx = (-1LL) };
}
void SymbolTable_mark_moved(SymbolTable* self, const char* name, ArrayList_SymbolTable* tables) {
    int64_t i = 0LL;
    while (i < ArrayList_Symbol_length(&(self->entries))) {
    if (strcmp(ArrayList_Symbol_get(&(self->entries), i).name, name) == 0) {
    Symbol sym = ArrayList_Symbol_get(&(self->entries), i);
    sym.moved = true;
    ArrayList_Symbol_set(&(self->entries), i, sym);
    return;
}
    i = (i + 1LL);
}
    if (self->parent_idx >= 0LL) {
    SymbolTable parent = ArrayList_SymbolTable_get(tables, self->parent_idx);
    SymbolTable_mark_moved(&(parent), name, tables);
    ArrayList_SymbolTable_set(tables, self->parent_idx, parent);
}
}
void SymbolTable_mark_freed(SymbolTable* self, const char* name, ArrayList_SymbolTable* tables) {
    int64_t i = 0LL;
    while (i < ArrayList_Symbol_length(&(self->entries))) {
    if (strcmp(ArrayList_Symbol_get(&(self->entries), i).name, name) == 0) {
    Symbol sym = ArrayList_Symbol_get(&(self->entries), i);
    sym.freed = true;
    ArrayList_Symbol_set(&(self->entries), i, sym);
    return;
}
    i = (i + 1LL);
}
    if (self->parent_idx >= 0LL) {
    SymbolTable parent = ArrayList_SymbolTable_get(tables, self->parent_idx);
    SymbolTable_mark_freed(&(parent), name, tables);
    ArrayList_SymbolTable_set(tables, self->parent_idx, parent);
}
}
void SymbolTable_clear_moved(SymbolTable* self, const char* name, ArrayList_SymbolTable* tables) {
    int64_t i = 0LL;
    while (i < ArrayList_Symbol_length(&(self->entries))) {
    if (strcmp(ArrayList_Symbol_get(&(self->entries), i).name, name) == 0) {
    Symbol sym = ArrayList_Symbol_get(&(self->entries), i);
    sym.moved = false;
    ArrayList_Symbol_set(&(self->entries), i, sym);
    return;
}
    i = (i + 1LL);
}
    if (self->parent_idx >= 0LL) {
    SymbolTable parent = ArrayList_SymbolTable_get(tables, self->parent_idx);
    SymbolTable_clear_moved(&(parent), name, tables);
    ArrayList_SymbolTable_set(tables, self->parent_idx, parent);
}
}
void SymbolTable_clear_freed(SymbolTable* self, const char* name, ArrayList_SymbolTable* tables) {
    int64_t i = 0LL;
    while (i < ArrayList_Symbol_length(&(self->entries))) {
    if (strcmp(ArrayList_Symbol_get(&(self->entries), i).name, name) == 0) {
    Symbol sym = ArrayList_Symbol_get(&(self->entries), i);
    sym.freed = false;
    ArrayList_Symbol_set(&(self->entries), i, sym);
    return;
}
    i = (i + 1LL);
}
    if (self->parent_idx >= 0LL) {
    SymbolTable parent = ArrayList_SymbolTable_get(tables, self->parent_idx);
    SymbolTable_clear_freed(&(parent), name, tables);
    ArrayList_SymbolTable_set(tables, self->parent_idx, parent);
}
}
int64_t SymbolTable_lookup_current(SymbolTable* self, const char* name) {
    int64_t i = 0LL;
    while (i < ArrayList_Symbol_length(&(self->entries))) {
    if (strcmp(ArrayList_Symbol_get(&(self->entries), i).name, name) == 0) {
    return i;
}
    i = (i + 1LL);
}
    return (-1LL);
}
ImportResolver ImportResolver_init(KaiAllocator* allocator, StringPool* pool) {
    ImportResolver self = (ImportResolver){0};
    self.allocator = allocator;
    self.loaded_modules = ArrayList_Str_init(allocator);
    self.cimport_headers = ArrayList_Str_init(allocator);
    self.has_error = false;
    self.error_message = "";
    self.error_stmt_idx = (-1LL);
    self.import_stack = ArrayList_Str_init(allocator);
    self.pool = pool;
    return self;
}
void ImportResolver_err_at(ImportResolver* self, const char* msg, int64_t stmt_idx) {
    if (!self->has_error) {
    self->has_error = true;
    self->error_message = msg;
    self->error_stmt_idx = stmt_idx;
}
}
void ImportResolver_err(ImportResolver* self, const char* msg) {
    ImportResolver_err_at(self, msg, (-1LL));
}
void ImportResolver_record_cimport(ImportResolver* self, const char* header) {
    bool found = false;
    int64_t i = 0LL;
    while (i < ArrayList_Str_length(&(self->cimport_headers))) {
    if (strcmp(ArrayList_Str_get(&(self->cimport_headers), i), header) == 0) {
    found = true;
}
    i = (i + 1LL);
}
    if (!found) {
    ArrayList_Str_push(&(self->cimport_headers), header);
}
}
void ImportResolver_resolve_import(ImportResolver* self, int64_t stmt_idx, ArrayList_StmtNode* stmt_pool, ArrayList_ExprNode* expr_pool, ArrayList_PatternNode* pattern_pool) {
    StmtNode stmt = ArrayList_StmtNode_get(stmt_pool, stmt_idx);
    ArrayList_Str path = stmt.import_path;
    const char* module_key = "";
    int64_t pi = 0LL;
    while (pi < ArrayList_Str_length(&(path))) {
    if (pi > 0LL) {
    module_key = concatAlloc(module_key, ".");
}
    module_key = concatAlloc(module_key, ArrayList_Str_get(&(path), pi));
    pi = (pi + 1LL);
}
    if (strcmp(module_key, "") == 0) {
    return;
}
    int64_t si = 0LL;
    while (si < ArrayList_Str_length(&(self->import_stack))) {
    if (strcmp(ArrayList_Str_get(&(self->import_stack), si), module_key) == 0) {
    ImportResolver_err_at(self, concatAlloc(concatAlloc("circular import detected: '", module_key), "'"), stmt_idx);
    return;
}
    si = (si + 1LL);
}
    int64_t li = 0LL;
    while (li < ArrayList_Str_length(&(self->loaded_modules))) {
    if (strcmp(ArrayList_Str_get(&(self->loaded_modules), li), module_key) == 0) {
    return;
}
    li = (li + 1LL);
}
    ArrayList_Str_push(&(self->import_stack), module_key);
    bool has_source = false;
    const char* source = "";
    const char* resolved_path = "";
    if ((ArrayList_Str_length(&(path)) > 0LL) && (strcmp(ArrayList_Str_get(&(path), 0LL), "std") == 0)) {
    const char* path_str = "";
    int64_t ii = 0LL;
    while (ii < ArrayList_Str_length(&(path))) {
    if (ii > 0LL) {
    path_str = concatAlloc(path_str, "/");
}
    path_str = concatAlloc(path_str, ArrayList_Str_get(&(path), ii));
    ii = (ii + 1LL);
}
    const char* rel_path = concatAlloc(path_str, ".kai");
    Result_Str_IoError s1 = read_to_string(self->allocator, rel_path);
    if ((s1.tag == 0LL) && (strlen(s1.value) > 0LL)) {
    source = s1.value;
    has_source = true;
    resolved_path = rel_path;
}
    if (!has_source) {
    {
    char* buf = (char*)(malloc(1024LL));
    if (get_exe_dir(buf, 1024LL) == 0LL) {
    const char* exe_dir = (const char*)(buf);
    const char* full_path = concatAlloc(concatAlloc(exe_dir, "/"), rel_path);
    Result_Str_IoError s2 = read_to_string(self->allocator, full_path);
    if ((s2.tag == 0LL) && (strlen(s2.value) > 0LL)) {
    source = s2.value;
    has_source = true;
    resolved_path = full_path;
}
    if (!has_source) {
    const char* parent_path = concatAlloc(concatAlloc(exe_dir, "/../"), rel_path);
    Result_Str_IoError s3 = read_to_string(self->allocator, parent_path);
    if ((s3.tag == 0LL) && (strlen(s3.value) > 0LL)) {
    source = s3.value;
    has_source = true;
    resolved_path = parent_path;
}
    if (!has_source) {
    const char* lib_path = concatAlloc(concatAlloc(exe_dir, "/../lib/kai/"), rel_path);
    Result_Str_IoError s4 = read_to_string(self->allocator, lib_path);
    if ((s4.tag == 0LL) && (strlen(s4.value) > 0LL)) {
    source = s4.value;
    has_source = true;
    resolved_path = lib_path;
}
}
}
}
}
}
} else if (ArrayList_Str_length(&(path)) > 0LL) {
    const char* path_str = "";
    int64_t ii = 0LL;
    while (ii < ArrayList_Str_length(&(path))) {
    if (ii > 0LL) {
    path_str = concatAlloc(path_str, "/");
}
    path_str = concatAlloc(path_str, ArrayList_Str_get(&(path), ii));
    ii = (ii + 1LL);
}
    const char* file_name = concatAlloc(path_str, ".kai");
    Result_Str_IoError s1 = read_to_string(self->allocator, file_name);
    if ((s1.tag == 0LL) && (strlen(s1.value) > 0LL)) {
    source = s1.value;
    has_source = true;
    resolved_path = file_name;
}
    if (!has_source) {
    const char* src_path = concatAlloc("src/", file_name);
    Result_Str_IoError s2 = read_to_string(self->allocator, src_path);
    if ((s2.tag == 0LL) && (strlen(s2.value) > 0LL)) {
    source = s2.value;
    has_source = true;
    resolved_path = src_path;
}
}
    if (!has_source) {
    {
    char* buf = (char*)(malloc(1024LL));
    if (get_exe_dir(buf, 1024LL) == 0LL) {
    const char* exe_dir = (const char*)(buf);
    const char* exe_src = concatAlloc(concatAlloc(exe_dir, "/../../src/"), file_name);
    Result_Str_IoError s3 = read_to_string(self->allocator, exe_src);
    if ((s3.tag == 0LL) && (strlen(s3.value) > 0LL)) {
    source = s3.value;
    has_source = true;
    resolved_path = exe_src;
}
}
}
}
}
    if (has_source) {
    ArrayList_Str_push(&(self->loaded_modules), module_key);
    Lexer lexer = Lexer_init(self->allocator, source, resolved_path, self->pool);
    Lexer_lex(&(lexer));
    if (lexer.has_error) {
    ArrayList_Str_pop(&(self->import_stack));
    ImportResolver_err_at(self, concatAlloc(concatAlloc("lexer error in imported module '", module_key), "'"), stmt_idx);
    return;
}
    Parser parser = Parser_init_with_pools(self->allocator, resolved_path, lexer.tokens, expr_pool, stmt_pool, pattern_pool, source, self->pool);
    int64_t program_idx = Parser_parse_program(&(parser));
    if (program_idx < 0LL) {
    ArrayList_Str_pop(&(self->import_stack));
    ImportResolver_err_at(self, concatAlloc(concatAlloc("parser error in imported module '", module_key), "'"), stmt_idx);
    return;
}
    StmtNode prog = ArrayList_StmtNode_get(stmt_pool, program_idx);
    if (prog.kind == StmtKind_sk_block) {
    int64_t pi = 0LL;
    while (pi < ArrayList_Int_length(&(prog.block_stmts))) {
    StmtNode sub = ArrayList_StmtNode_get(stmt_pool, ArrayList_Int_get(&(prog.block_stmts), pi));
    if (sub.kind == StmtKind_sk_import) {
    if (!self->has_error) {
    ImportResolver_resolve_import(self, ArrayList_Int_get(&(prog.block_stmts), pi), stmt_pool, expr_pool, pattern_pool);
}
}
    if (sub.kind == StmtKind_sk_cimport) {
    ImportResolver_record_cimport(self, sub.cimport_header);
}
    pi = (pi + 1LL);
}
}
    ArrayList_Str_pop(&(self->import_stack));
} else {
    ArrayList_Str_pop(&(self->import_stack));
    ImportResolver_err_at(self, concatAlloc(concatAlloc("module not found: '", module_key), "'"), stmt_idx);
}
}
void ImportResolver_resolve_all(ImportResolver* self, int64_t program_idx, ArrayList_StmtNode* stmt_pool, ArrayList_ExprNode* expr_pool, ArrayList_PatternNode* pattern_pool) {
    StmtNode prog = ArrayList_StmtNode_get(stmt_pool, program_idx);
    if (prog.kind == StmtKind_sk_block) {
    int64_t i = 0LL;
    while (i < ArrayList_Int_length(&(prog.block_stmts))) {
    int64_t s_idx = ArrayList_Int_get(&(prog.block_stmts), i);
    StmtNode s = ArrayList_StmtNode_get(stmt_pool, s_idx);
    if (s.kind == StmtKind_sk_import) {
    ImportResolver_resolve_import(self, s_idx, stmt_pool, expr_pool, pattern_pool);
}
    if (s.kind == StmtKind_sk_cimport) {
    ImportResolver_record_cimport(self, s.cimport_header);
}
    i = (i + 1LL);
}
}
}
TypeArena TypeArena_init(KaiAllocator* allocator) {
    TypeArena self = (TypeArena){0};
    self.allocator = allocator;
    self.types = ArrayList_Type_init(allocator);
    ArrayList_Type_push(&(self.types), (Type){ .kind = TypeKind_tk_void, .name = "Void", .element_type_id = (-1LL), .decl_stmt_idx = (-1LL), .error_set_id = (-1LL) });
    ArrayList_Type_push(&(self.types), (Type){ .kind = TypeKind_tk_int, .name = "Int", .element_type_id = (-1LL), .decl_stmt_idx = (-1LL), .error_set_id = (-1LL) });
    ArrayList_Type_push(&(self.types), (Type){ .kind = TypeKind_tk_float, .name = "Float", .element_type_id = (-1LL), .decl_stmt_idx = (-1LL), .error_set_id = (-1LL) });
    ArrayList_Type_push(&(self.types), (Type){ .kind = TypeKind_tk_bool, .name = "Bool", .element_type_id = (-1LL), .decl_stmt_idx = (-1LL), .error_set_id = (-1LL) });
    ArrayList_Type_push(&(self.types), (Type){ .kind = TypeKind_tk_char, .name = "Char", .element_type_id = (-1LL), .decl_stmt_idx = (-1LL), .error_set_id = (-1LL) });
    ArrayList_Type_push(&(self.types), (Type){ .kind = TypeKind_tk_str, .name = "Str", .element_type_id = (-1LL), .decl_stmt_idx = (-1LL), .error_set_id = (-1LL) });
    return self;
}
Type TypeArena_get_type(TypeArena* self, int64_t id) {
    return ArrayList_Type_get(&(self->types), id);
}
int64_t TypeArena_intern_pointer(TypeArena* self, int64_t element_type_id) {
    int64_t i = 0LL;
    while (i < ArrayList_Type_length(&(self->types))) {
    Type t = ArrayList_Type_get(&(self->types), i);
    if ((t.kind == TypeKind_tk_pointer) && (t.element_type_id == element_type_id)) {
    return i;
}
    i = (i + 1LL);
}
    Type el = ArrayList_Type_get(&(self->types), element_type_id);
    const char* name = concatAlloc("*", el.name);
    int64_t new_id = ArrayList_Type_length(&(self->types));
    ArrayList_Type_push(&(self->types), (Type){ .kind = TypeKind_tk_pointer, .name = name, .element_type_id = element_type_id, .decl_stmt_idx = (-1LL), .error_set_id = (-1LL) });
    return new_id;
}
int64_t TypeArena_intern_struct(TypeArena* self, const char* name, int64_t decl_stmt_idx) {
    int64_t i = 0LL;
    while (i < ArrayList_Type_length(&(self->types))) {
    Type t = ArrayList_Type_get(&(self->types), i);
    if ((t.kind == TypeKind_tk_struct) && (strcmp(t.name, name) == 0)) {
    return i;
}
    i = (i + 1LL);
}
    int64_t new_id = ArrayList_Type_length(&(self->types));
    ArrayList_Type_push(&(self->types), (Type){ .kind = TypeKind_tk_struct, .name = name, .element_type_id = (-1LL), .decl_stmt_idx = decl_stmt_idx, .error_set_id = (-1LL) });
    return new_id;
}
int64_t TypeArena_intern_enum(TypeArena* self, const char* name, int64_t decl_stmt_idx) {
    int64_t i = 0LL;
    while (i < ArrayList_Type_length(&(self->types))) {
    Type t = ArrayList_Type_get(&(self->types), i);
    if ((t.kind == TypeKind_tk_enum) && (strcmp(t.name, name) == 0)) {
    return i;
}
    i = (i + 1LL);
}
    int64_t new_id = ArrayList_Type_length(&(self->types));
    ArrayList_Type_push(&(self->types), (Type){ .kind = TypeKind_tk_enum, .name = name, .element_type_id = (-1LL), .decl_stmt_idx = decl_stmt_idx, .error_set_id = (-1LL) });
    return new_id;
}
void TypeArena_deinit(TypeArena* self) {
    ArrayList_Type_deinit(&(self->types));
}
int64_t type_map_find(ArrayList_StrMapEntry* arr, const char* key) {
    int64_t i = (ArrayList_StrMapEntry_length(arr) - 1LL);
    while (i >= 0LL) {
    if (strcmp(ArrayList_StrMapEntry_get(arr, i).key, key) == 0) {
    return i;
}
    i = (i - 1LL);
}
    return (-1LL);
}
const char* type_map_get(ArrayList_StrMapEntry* arr, const char* key) {
    int64_t idx = type_map_find(arr, key);
    if (idx < 0LL) {
    return "";
}
    return ArrayList_StrMapEntry_get(arr, idx).value;
}
void type_map_put(ArrayList_StrMapEntry* arr, const char* key, const char* value) {
    ArrayList_StrMapEntry_push(arr, (StrMapEntry){ .key = key, .value = value });
}
int64_t strlist_find(ArrayList_Str* arr, const char* key) {
    int64_t i = 0LL;
    while (i < ArrayList_Str_length(arr)) {
    if (strcmp(ArrayList_Str_get(arr, i), key) == 0) {
    return i;
}
    i = (i + 1LL);
}
    return (-1LL);
}
const char* Codegen_add_init_return(Codegen* self, const char* body_str, const char* struct_name) {
    const char* self_decl = concatAlloc(concatAlloc(concatAlloc(concatAlloc("    ", struct_name), " self = ("), struct_name), "){0};\n");
    int64_t body_len = strlen(body_str);
    const char* stripped_body = __kai_str_sub(body_str, 2LL, (body_len - 1LL));
    bool ends_with_return = false;
    {
    char* ret_ptr = strstr(stripped_body, "return self;");
    if (ret_ptr != (char*)(unsigned long long)(0LL)) {
    int64_t offset = ((int64_t)(ret_ptr) - (int64_t)(stripped_body));
    if (offset >= (strlen(stripped_body) - 20LL)) {
    ends_with_return = true;
}
}
}
    if (ends_with_return) {
    return concatAlloc(concatAlloc(concatAlloc("{\n", self_decl), stripped_body), "}");
}
    const char* self_ret = "    return self;\n}";
    return concatAlloc(concatAlloc(concatAlloc("{\n", self_decl), stripped_body), self_ret);
}
Codegen Codegen_init(KaiAllocator* allocator, ArrayList_StmtNode* stmt_pool, ArrayList_ExprNode* expr_pool, ArrayList_PatternNode* pattern_pool, ImportResolver* import_resolver, StringPool* pool) {
    Codegen self = (Codegen){0};
    self.allocator = allocator;
    self.stmt_pool = stmt_pool;
    self.expr_pool = expr_pool;
    self.pattern_pool = pattern_pool;
    self.import_resolver = import_resolver;
    self.pool = pool;
    self.output = StringBuilder_init(allocator);
    self.struct_decls = StringBuilder_init(allocator);
    self.func_decls = StringBuilder_init(allocator);
    self.cur_func_name = "";
    self.cur_return_type = "";
    self.cur_method_is_init = false;
    self.func_types = ArrayList_StrMapEntry_init(allocator);
    self.var_types = ArrayList_StrMapEntry_init(allocator);
    self.block_stack = ArrayList_Int_init(allocator);
    self.generic_struct_decls = ArrayList_StrMapEntry_init(allocator);
    self.generic_enum_decls = ArrayList_StrMapEntry_init(allocator);
    self.generic_func_decls = ArrayList_StrMapEntry_init(allocator);
    self.generic_impl_blocks = ArrayList_StrMapEntry_init(allocator);
    self.monomorphized_types = ArrayList_Str_init(allocator);
    self.current_type_map = ArrayList_StrMapEntry_init(allocator);
    self.enum_decls = ArrayList_StrMapEntry_init(allocator);
    self.result_definitions = ArrayList_Str_init(allocator);
    self.defer_stack = ArrayList_Int_init(allocator);
    self.defer_depths = ArrayList_Int_init(allocator);
    self.func_param_types = ArrayList_StrMapEntry_init(allocator);
    return self;
}
bool Codegen_is_pointer_type(Codegen* self, const char* t) {
    if (strlen(t) == 0LL) {
    return false;
}
    if (((t)[0LL] == ((char)(42LL))) || ((t)[0LL] == ((char)(38LL)))) {
    return true;
}
    if (strcmp(t, "Str") == 0) {
    return true;
}
    if ((strlen(t) >= 2LL) && (strcmp(__kai_str_sub(t, 0LL, 2LL), "[]") == 0)) {
    return true;
}
    return false;
}
const char* Codegen_strip_module_prefix(Codegen* self, const char* name) {
    int64_t last_dot = (-1LL);
    int64_t i = 0LL;
    while (i < strlen(name)) {
    if ((name)[i] == ((char)(46LL))) {
    last_dot = i;
}
    i = (i + 1LL);
}
    if (last_dot >= 0LL) {
    return __kai_str_sub(name, (last_dot + 1LL), strlen(name));
}
    return name;
}
const char* Codegen_map_type(Codegen* self, const char* type_name) {
    if (strlen(type_name) == 0LL) {
    return "void";
}
    const char* resolved_type = Codegen_strip_module_prefix(self, type_name);
    if (ArrayList_StrMapEntry_length(&(self->current_type_map)) > 0LL) {
    resolved_type = Codegen_substitute_generic_type(self, type_name);
}
    if ((strlen(resolved_type) > 0LL) && ((resolved_type)[0LL] == ((char)(40LL)))) {
    const char* clean_name = concatAlloc("Tuple_", Codegen_clean_type_for_mangling(self, resolved_type));
    if (strlist_find(&(self->result_definitions), clean_name) < 0LL) {
    ArrayList_Str_push(&(self->result_definitions), clean_name);
    const char* inner_types = __kai_str_sub(resolved_type, 1LL, (strlen(resolved_type) - 1LL));
    ArrayList_Str types_list = ArrayList_Str_init(self->allocator);
    int64_t start = 0LL;
    int64_t i = 0LL;
    while (i < strlen(inner_types)) {
    if ((inner_types)[i] == ((char)(44LL))) {
    ArrayList_Str_push(&(types_list), Codegen_trim_spaces(self, __kai_str_sub(inner_types, start, i)));
    start = (i + 1LL);
}
    i = (i + 1LL);
}
    ArrayList_Str_push(&(types_list), Codegen_trim_spaces(self, __kai_str_sub(inner_types, start, strlen(inner_types))));
    const char* struct_str = concatAlloc(concatAlloc(concatAlloc(concatAlloc("typedef struct ", clean_name), " "), clean_name), ";\n");
    struct_str = concatAlloc(concatAlloc(concatAlloc(struct_str, "struct "), clean_name), " {\n");
    int64_t ti = 0LL;
    while (ti < ArrayList_Str_length(&(types_list))) {
    struct_str = concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(struct_str, "    "), Codegen_map_type(self, ArrayList_Str_get(&(types_list), ti))), " f"), int_to_str(ti)), ";\n");
    ti = (ti + 1LL);
}
    struct_str = concatAlloc(struct_str, "};\n");
    (void)(StringBuilder_append(&(self->struct_decls), struct_str));
}
    return clean_name;
}
    if ((strlen(resolved_type) > 0LL) && ((resolved_type)[0LL] == ((char)(63LL)))) {
    const char* val_type = __kai_str_sub(resolved_type, 1LL, strlen(resolved_type));
    if (Codegen_is_pointer_type(self, val_type)) {
    return Codegen_map_type(self, val_type);
}
    const char* clean_val = Codegen_clean_type_for_mangling(self, val_type);
    const char* concrete_name = concatAlloc("Optional_", clean_val);
    if (strlist_find(&(self->result_definitions), concrete_name) < 0LL) {
    ArrayList_Str_push(&(self->result_definitions), concrete_name);
    const char* struct_str = concatAlloc(concatAlloc(concatAlloc(concatAlloc("typedef struct ", concrete_name), " "), concrete_name), ";\n");
    struct_str = concatAlloc(concatAlloc(concatAlloc(struct_str, "struct "), concrete_name), " {\n");
    struct_str = concatAlloc(struct_str, "    bool has_value;\n");
    struct_str = concatAlloc(concatAlloc(concatAlloc(struct_str, "    "), Codegen_map_type(self, val_type)), " value;\n");
    struct_str = concatAlloc(struct_str, "};\n");
    (void)(StringBuilder_append(&(self->struct_decls), struct_str));
}
    return concrete_name;
}
    if (Codegen_str_contains(self, resolved_type, ((char)(33LL)))) {
    int64_t excl_pos = Codegen_str_find(self, resolved_type, ((char)(33LL)));
    const char* val_type = __kai_str_sub(resolved_type, 0LL, excl_pos);
    const char* err_type = __kai_str_sub(resolved_type, (excl_pos + 1LL), strlen(resolved_type));
    const char* clean_val = Codegen_clean_type_for_mangling(self, val_type);
    const char* clean_err = Codegen_clean_type_for_mangling(self, err_type);
    const char* concrete_name = concatAlloc(concatAlloc(concatAlloc("Result_", clean_val), "_"), clean_err);
    if (strlist_find(&(self->result_definitions), concrete_name) < 0LL) {
    ArrayList_Str_push(&(self->result_definitions), concrete_name);
    const char* struct_str = concatAlloc(concatAlloc(concatAlloc(concatAlloc("typedef struct ", concrete_name), " "), concrete_name), ";\n");
    struct_str = concatAlloc(concatAlloc(concatAlloc(struct_str, "struct "), concrete_name), " {\n");
    struct_str = concatAlloc(struct_str, "    int64_t tag;\n");
    if (strcmp(val_type, "Void") != 0) {
    struct_str = concatAlloc(concatAlloc(concatAlloc(struct_str, "    "), Codegen_map_type(self, val_type)), " value;\n");
}
    struct_str = concatAlloc(struct_str, "};\n");
    (void)(StringBuilder_append(&(self->struct_decls), struct_str));
}
    return concrete_name;
}
    if ((strcmp(resolved_type, "Int") == 0) || (strcmp(resolved_type, "i64") == 0)) {
    return "int64_t";
}
    if (strcmp(resolved_type, "isize") == 0) {
    return "intptr_t";
}
    if (strcmp(resolved_type, "i8") == 0) {
    return "int8_t";
}
    if (strcmp(resolved_type, "i32") == 0) {
    return "int32_t";
}
    if (strcmp(resolved_type, "i16") == 0) {
    return "int16_t";
}
    if (strcmp(resolved_type, "u8") == 0) {
    return "uint8_t";
}
    if (strcmp(resolved_type, "u16") == 0) {
    return "uint16_t";
}
    if (strcmp(resolved_type, "u32") == 0) {
    return "uint32_t";
}
    if (strcmp(resolved_type, "u64") == 0) {
    return "uint64_t";
}
    if (strcmp(resolved_type, "usize") == 0) {
    return "size_t";
}
    if (strcmp(resolved_type, "Bool") == 0) {
    return "bool";
}
    if (strcmp(resolved_type, "Char") == 0) {
    return "char";
}
    if (strcmp(resolved_type, "Float") == 0) {
    return "double";
}
    if (strcmp(resolved_type, "Void") == 0) {
    return "void";
}
    if (strcmp(resolved_type, "Str") == 0) {
    return "const char*";
}
    if (strcmp(__kai_str_sub(resolved_type, 0LL, 2LL), "[]") == 0) {
    const char* inner = __kai_str_sub(resolved_type, 2LL, strlen(resolved_type));
    return concatAlloc(Codegen_map_type(self, inner), "*");
}
    if ((resolved_type)[0LL] == ((char)(42LL))) {
    if ((strlen(resolved_type) > 5LL) && (strcmp(__kai_str_sub(resolved_type, 0LL, 5LL), "*mut ") == 0)) {
    const char* inner = __kai_str_sub(resolved_type, 5LL, strlen(resolved_type));
    if (strcmp(inner, "Void") == 0) {
    return "void*";
}
    return concatAlloc(Codegen_map_type(self, inner), "*");
} else {
    const char* inner = __kai_str_sub(resolved_type, 1LL, strlen(resolved_type));
    if (strcmp(inner, "Void") == 0) {
    return "void*";
}
    return concatAlloc(Codegen_map_type(self, inner), "*");
}
}
    if ((resolved_type)[0LL] == ((char)(38LL))) {
    if ((strlen(resolved_type) > 5LL) && (strcmp(__kai_str_sub(resolved_type, 0LL, 5LL), "&mut ") == 0)) {
    const char* inner = __kai_str_sub(resolved_type, 5LL, strlen(resolved_type));
    return concatAlloc(Codegen_map_type(self, inner), "*");
} else {
    const char* inner = __kai_str_sub(resolved_type, 1LL, strlen(resolved_type));
    return concatAlloc(Codegen_map_type(self, inner), "*");
}
}
    if (Codegen_str_contains(self, resolved_type, ((char)(60LL)))) {
    int64_t lt_pos = Codegen_str_find(self, resolved_type, ((char)(60LL)));
    const char* base_name = __kai_str_sub(resolved_type, 0LL, lt_pos);
    const char* args_str = __kai_str_sub(resolved_type, (lt_pos + 1LL), (strlen(resolved_type) - 1LL));
    ArrayList_Str args = ArrayList_Str_init(self->allocator);
    int64_t start = 0LL;
    int64_t i = 0LL;
    while (i < strlen(args_str)) {
    char c = (args_str)[i];
    if (c == ((char)(44LL))) {
    ArrayList_Str_push(&(args), Codegen_trim_spaces(self, __kai_str_sub(args_str, start, i)));
    start = (i + 1LL);
}
    i = (i + 1LL);
}
    ArrayList_Str_push(&(args), Codegen_trim_spaces(self, __kai_str_sub(args_str, start, strlen(args_str))));
    const char* concrete_name = base_name;
    int64_t ai = 0LL;
    while (ai < ArrayList_Str_length(&(args))) {
    const char* raw_arg = ArrayList_Str_get(&(args), ai);
    const char* clean_arg = Codegen_clean_type_for_mangling(self, raw_arg);
    concrete_name = concatAlloc(concatAlloc(concrete_name, "_"), clean_arg);
    ai = (ai + 1LL);
}
    const char* struct_idx_str = type_map_get(&(self->generic_struct_decls), base_name);
    if (strlen(struct_idx_str) > 0LL) {
    if (strlist_find(&(self->monomorphized_types), concrete_name) < 0LL) {
    ArrayList_Str_push(&(self->monomorphized_types), concrete_name);
    Codegen_monomorphize_struct(self, Codegen_str_to_int(self, struct_idx_str), concrete_name, &(args));
}
    return concrete_name;
}
    const char* enum_idx_str = type_map_get(&(self->generic_enum_decls), base_name);
    if (strlen(enum_idx_str) > 0LL) {
    if (strlist_find(&(self->monomorphized_types), concrete_name) < 0LL) {
    ArrayList_Str_push(&(self->monomorphized_types), concrete_name);
    Codegen_monomorphize_enum(self, Codegen_str_to_int(self, enum_idx_str), concrete_name, &(args));
}
    return concrete_name;
}
    return concrete_name;
}
    return resolved_type;
}
const char* Codegen_substitute_generic_type(Codegen* self, const char* type_name) {
    const char* mapped = type_map_get(&(self->current_type_map), type_name);
    if (strlen(mapped) > 0LL) {
    return mapped;
}
    if ((type_name)[0LL] == ((char)(42LL))) {
    return concatAlloc("*", Codegen_substitute_generic_type(self, __kai_str_sub(type_name, 1LL, strlen(type_name))));
}
    if ((type_name)[0LL] == ((char)(38LL))) {
    if (strcmp(__kai_str_sub(type_name, 0LL, 5LL), "&mut ") == 0) {
    return concatAlloc("&mut ", Codegen_substitute_generic_type(self, __kai_str_sub(type_name, 5LL, strlen(type_name))));
}
    return concatAlloc("&", Codegen_substitute_generic_type(self, __kai_str_sub(type_name, 1LL, strlen(type_name))));
}
    if (Codegen_str_contains(self, type_name, ((char)(60LL)))) {
    int64_t lt_pos = Codegen_str_find(self, type_name, ((char)(60LL)));
    const char* base = __kai_str_sub(type_name, 0LL, lt_pos);
    const char* inner = __kai_str_sub(type_name, (lt_pos + 1LL), (strlen(type_name) - 1LL));
    const char* res = concatAlloc(base, "<");
    int64_t start = 0LL;
    int64_t i = 0LL;
    int64_t arg_count = 0LL;
    while (i < strlen(inner)) {
    char c = (inner)[i];
    if (c == ((char)(44LL))) {
    const char* arg = Codegen_trim_spaces(self, __kai_str_sub(inner, start, i));
    if (arg_count > 0LL) {
    res = concatAlloc(res, ", ");
}
    res = concatAlloc(res, Codegen_substitute_generic_type(self, arg));
    start = (i + 1LL);
    arg_count = (arg_count + 1LL);
}
    i = (i + 1LL);
}
    const char* arg = Codegen_trim_spaces(self, __kai_str_sub(inner, start, strlen(inner)));
    if (arg_count > 0LL) {
    res = concatAlloc(res, ", ");
}
    res = concatAlloc(res, Codegen_substitute_generic_type(self, arg));
    res = concatAlloc(res, ">");
    return res;
}
    return type_name;
}
const char* Codegen_trim_spaces(Codegen* self, const char* s) {
    int64_t start = 0LL;
    while ((start < strlen(s)) && ((s)[start] == ((char)(32LL)))) {
    start = (start + 1LL);
}
    int64_t end = strlen(s);
    while ((end > start) && ((s)[(end - 1LL)] == ((char)(32LL)))) {
    end = (end - 1LL);
}
    return __kai_str_sub(s, start, end);
}
const char* Codegen_clean_type_for_mangling(Codegen* self, const char* s) {
    const char* res = "";
    int64_t i = 0LL;
    while (i < strlen(s)) {
    char c = (s)[i];
    if (c == ((char)(42LL))) {
    res = concatAlloc(res, "ptr");
} else if (c == ((char)(38LL))) {
    res = concatAlloc(res, "ref");
} else if (c == ((char)(32LL))) {
    res = concatAlloc(res, "_");
} else if (c == ((char)(63LL))) {
    res = concatAlloc(res, "opt_");
} else if ((((((c == ((char)(60LL))) || (c == ((char)(62LL)))) || (c == ((char)(44LL)))) || (c == ((char)(33LL)))) || (c == ((char)(40LL)))) || (c == ((char)(41LL)))) {
    res = concatAlloc(res, "_");
} else {
    res = concatAlloc(res, char_to_str(c));
}
    i = (i + 1LL);
}
    return res;
}
int64_t Codegen_str_to_int(Codegen* self, const char* s) {
    int64_t res = 0LL;
    int64_t i = 0LL;
    while (i < strlen(s)) {
    char c = (s)[i];
    if ((c >= ((char)(48LL))) && (c <= ((char)(57LL)))) {
    res = ((res * 10LL) + (((int64_t)(c)) - 48LL));
}
    i = (i + 1LL);
}
    return res;
}
ArrayList_Str Codegen_infer_type_args(Codegen* self, int64_t func_stmt_idx, int64_t expr_idx) {
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, func_stmt_idx);
    ExprNode expr = ArrayList_ExprNode_get(self->expr_pool, expr_idx);
    ArrayList_Str type_args = ArrayList_Str_init(self->allocator);
    int64_t p_idx = 0LL;
    while (p_idx < ArrayList_Str_length(&(stmt.func_type_params))) {
    ArrayList_Str_push(&(type_args), "");
    p_idx = (p_idx + 1LL);
}
    int64_t arg_i = 0LL;
    while ((arg_i < ArrayList_Int_length(&(expr.func_args))) && (arg_i < ArrayList_Param_length(&(stmt.func_params)))) {
    int64_t arg = ArrayList_Int_get(&(expr.func_args), arg_i);
    Param param = ArrayList_Param_get(&(stmt.func_params), arg_i);
    const char* arg_type = Codegen_get_expr_type(self, arg);
    const char* ptype = param.ptype;
    const char* atype = arg_type;
    bool done = false;
    while (!done) {
    if ((strlen(ptype) > 0LL) && (((ptype)[0LL] == ((char)(42LL))) || ((ptype)[0LL] == ((char)(38LL))))) {
    ptype = __kai_str_sub(ptype, 1LL, strlen(ptype));
} else {
    done = true;
}
}
    done = false;
    while (!done) {
    if ((strlen(atype) > 0LL) && (((atype)[0LL] == ((char)(42LL))) || ((atype)[0LL] == ((char)(38LL))))) {
    atype = __kai_str_sub(atype, 1LL, strlen(atype));
} else {
    done = true;
}
}
    if ((strlen(ptype) >= 4LL) && (strcmp(__kai_str_sub(ptype, 0LL, 4LL), "mut ") == 0)) {
    ptype = __kai_str_sub(ptype, 4LL, strlen(ptype));
}
    if ((strlen(atype) >= 4LL) && (strcmp(__kai_str_sub(atype, 0LL, 4LL), "mut ") == 0)) {
    atype = __kai_str_sub(atype, 4LL, strlen(atype));
}
    bool is_param = false;
    if (((strlen(ptype) == 1LL) && ((ptype)[0LL] >= ((char)(65LL)))) && ((ptype)[0LL] <= ((char)(90LL)))) {
    is_param = true;
}
    if (is_param) {
    int64_t tp_i = 0LL;
    while (tp_i < ArrayList_Str_length(&(stmt.func_type_params))) {
    const char* tp_name = ArrayList_Str_get(&(stmt.func_type_params), tp_i);
    if (Codegen_str_contains(self, tp_name, ((char)(58LL)))) {
    int64_t colon_pos = Codegen_str_find(self, tp_name, ((char)(58LL)));
    tp_name = __kai_str_sub(tp_name, 0LL, colon_pos);
}
    if (strcmp(tp_name, ptype) == 0) {
    ArrayList_Str_set(&(type_args), tp_i, atype);
}
    tp_i = (tp_i + 1LL);
}
}
    arg_i = (arg_i + 1LL);
}
    int64_t i = 0LL;
    while (i < ArrayList_Str_length(&(type_args))) {
    if (strlen(ArrayList_Str_get(&(type_args), i)) == 0LL) {
    ArrayList_Str_set(&(type_args), i, "Int");
}
    i = (i + 1LL);
}
    return type_args;
}
void Codegen_setup_current_type_map(Codegen* self, ArrayList_Str* type_params, ArrayList_Str* type_args) {
    int64_t i = 0LL;
    while (i < ArrayList_Str_length(type_params)) {
    const char* param_name = Codegen_trim_spaces(self, ArrayList_Str_get(type_params, i));
    const char* arg_name = Codegen_trim_spaces(self, ArrayList_Str_get(type_args, i));
    if (Codegen_str_contains(self, param_name, ((char)(58LL)))) {
    int64_t colon_pos = Codegen_str_find(self, param_name, ((char)(58LL)));
    param_name = __kai_str_sub(param_name, 0LL, colon_pos);
}
    type_map_put(&(self->current_type_map), param_name, arg_name);
    i = (i + 1LL);
}
}
void Codegen_monomorphize_struct(Codegen* self, int64_t stmt_idx, const char* concrete_name, ArrayList_Str* type_args) {
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, stmt_idx);
    ArrayList_StrMapEntry old_type_map = self->current_type_map;
    self->current_type_map = ArrayList_StrMapEntry_init(self->allocator);
    Codegen_setup_current_type_map(self, &(stmt.struct_type_params), type_args);
    const char* typedef_str = concatAlloc(concatAlloc(concatAlloc(concatAlloc("typedef struct ", concrete_name), " "), concrete_name), ";\n");
    (void)(StringBuilder_append(&(self->struct_decls), typedef_str));
    const char* body = concatAlloc(concatAlloc("struct ", concrete_name), " {\n");
    int64_t i = 0LL;
    while (i < ArrayList_StructField_length(&(stmt.struct_fields))) {
    StructField f = ArrayList_StructField_get(&(stmt.struct_fields), i);
    const char* f_type = Codegen_map_type(self, f.ftype);
    body = concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(body, "    "), f_type), " "), f.name), ";\n");
    i = (i + 1LL);
}
    body = concatAlloc(body, "};\n");
    (void)(StringBuilder_append(&(self->struct_decls), body));
    Codegen_monomorphize_methods(self, stmt.struct_name, concrete_name);
    self->current_type_map = old_type_map;
}
void Codegen_monomorphize_enum(Codegen* self, int64_t stmt_idx, const char* concrete_name, ArrayList_Str* type_args) {
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, stmt_idx);
    ArrayList_StrMapEntry old_type_map = self->current_type_map;
    self->current_type_map = ArrayList_StrMapEntry_init(self->allocator);
    Codegen_setup_current_type_map(self, &(stmt.enum_type_params), type_args);
    const char* typedef_str = concatAlloc(concatAlloc(concatAlloc(concatAlloc("typedef struct ", concrete_name), " "), concrete_name), ";\n");
    (void)(StringBuilder_append(&(self->struct_decls), typedef_str));
    const char* tags_name = concatAlloc(concrete_name, "_tags");
    const char* tags_str = "typedef enum {\n";
    int64_t i = 0LL;
    while (i < ArrayList_Variant_length(&(stmt.enum_variants))) {
    Variant v = ArrayList_Variant_get(&(stmt.enum_variants), i);
    tags_str = concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(tags_str, "    "), concrete_name), "_"), v.vname), "_TAG,\n");
    i = (i + 1LL);
}
    tags_str = concatAlloc(concatAlloc(concatAlloc(tags_str, "} "), tags_name), ";\n");
    (void)(StringBuilder_append(&(self->struct_decls), tags_str));
    const char* body = concatAlloc(concatAlloc("struct ", concrete_name), " {\n");
    body = concatAlloc(body, "    uint8_t tag;\n");
    body = concatAlloc(body, "    union {\n");
    i = 0LL;
    while (i < ArrayList_Variant_length(&(stmt.enum_variants))) {
    Variant v = ArrayList_Variant_get(&(stmt.enum_variants), i);
    if (ArrayList_Param_length(&(v.params)) > 0LL) {
    body = concatAlloc(body, "        struct {\n");
    int64_t p_idx = 0LL;
    while (p_idx < ArrayList_Param_length(&(v.params))) {
    Param p = ArrayList_Param_get(&(v.params), p_idx);
    body = concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(body, "            "), Codegen_map_type(self, p.ptype)), " "), p.name), ";\n");
    p_idx = (p_idx + 1LL);
}
    body = concatAlloc(concatAlloc(concatAlloc(body, "        } "), v.vname), ";\n");
}
    i = (i + 1LL);
}
    body = concatAlloc(body, "    } payload;\n");
    body = concatAlloc(body, "};\n");
    (void)(StringBuilder_append(&(self->struct_decls), body));
    Codegen_monomorphize_methods(self, stmt.enum_name, concrete_name);
    self->current_type_map = old_type_map;
}
void Codegen_monomorphize_methods(Codegen* self, const char* base_struct_name, const char* concrete_struct_name) {
    int64_t idx = 0LL;
    while (idx < ArrayList_StmtNode_length(self->stmt_pool)) {
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, idx);
    if ((stmt.kind == StmtKind_sk_impl_block) && (strcmp(stmt.impl_struct_name, base_struct_name) == 0)) {
    int64_t j = 0LL;
    while (j < ArrayList_Int_length(&(stmt.impl_methods))) {
    int64_t m_idx = ArrayList_Int_get(&(stmt.impl_methods), j);
    StmtNode m_node = ArrayList_StmtNode_get(self->stmt_pool, m_idx);
    const char* method_name = m_node.func_name;
    bool is_init = ((((strcmp(method_name, "init") == 0) || (strcmp(m_node.func_return_type, base_struct_name) == 0)) || (strcmp(m_node.func_return_type, concatAlloc("*", base_struct_name)) == 0)) || (strcmp(m_node.func_return_type, concatAlloc("&", base_struct_name)) == 0));
    const char* ret_type = "";
    if (is_init) {
    ret_type = concrete_struct_name;
} else {
    ret_type = Codegen_map_type(self, m_node.func_return_type);
}
    const char* params_str = "";
    if (!is_init) {
    params_str = concatAlloc(concrete_struct_name, "* self");
}
    int64_t p_idx = 0LL;
    while (p_idx < ArrayList_Param_length(&(m_node.func_params))) {
    Param p = ArrayList_Param_get(&(m_node.func_params), p_idx);
    if (strcmp(p.name, "self") != 0) {
    if (strlen(params_str) > 0LL) {
    params_str = concatAlloc(params_str, ", ");
}
    params_str = concatAlloc(concatAlloc(concatAlloc(params_str, Codegen_map_type(self, p.ptype)), " "), p.name);
}
    p_idx = (p_idx + 1LL);
}
    if (strlen(params_str) == 0LL) {
    params_str = "void";
}
    const char* mangled_fn_name = concatAlloc(concatAlloc(concrete_struct_name, "_"), method_name);
    const char* concrete_ret = m_node.func_return_type;
    if (ArrayList_StrMapEntry_length(&(self->current_type_map)) > 0LL) {
    concrete_ret = Codegen_substitute_generic_type(self, concrete_ret);
}
    type_map_put(&(self->func_types), mangled_fn_name, concrete_ret);
    const char* old_fn = self->cur_func_name;
    const char* old_ret = self->cur_return_type;
    bool old_init = self->cur_method_is_init;
    self->cur_func_name = mangled_fn_name;
    if (is_init) {
    self->cur_return_type = base_struct_name;
} else {
    self->cur_return_type = m_node.func_return_type;
}
    self->cur_method_is_init = is_init;
    int64_t old_var_len = ArrayList_StrMapEntry_length(&(self->var_types));
    if (is_init) {
    type_map_put(&(self->var_types), "self", concrete_struct_name);
} else {
    type_map_put(&(self->var_types), "self", concatAlloc("*", concrete_struct_name));
}
    int64_t p_idx2 = 0LL;
    while (p_idx2 < ArrayList_Param_length(&(m_node.func_params))) {
    Param p = ArrayList_Param_get(&(m_node.func_params), p_idx2);
    if (strcmp(p.name, "self") != 0) {
    type_map_put(&(self->var_types), p.name, p.ptype);
}
    p_idx2 = (p_idx2 + 1LL);
}
    const char* body_str = Codegen_gen_stmt(self, m_node.func_body);
    while (ArrayList_StrMapEntry_length(&(self->var_types)) > old_var_len) {
    (void)(ArrayList_StrMapEntry_pop(&(self->var_types)));
}
    if (is_init) {
    body_str = Codegen_add_init_return(self, body_str, concrete_struct_name);
}
    const char* proto = concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(ret_type, " "), mangled_fn_name), "("), params_str), ");\n");
    const char* impl_str = concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(ret_type, " "), mangled_fn_name), "("), params_str), ") "), body_str), "\n");
    (void)(StringBuilder_append(&(self->func_decls), proto));
    (void)(StringBuilder_append(&(self->output), impl_str));
    self->cur_func_name = old_fn;
    self->cur_return_type = old_ret;
    self->cur_method_is_init = old_init;
    j = (j + 1LL);
}
}
    idx = (idx + 1LL);
}
}
void Codegen_monomorphize_func(Codegen* self, int64_t func_stmt_idx, const char* mangled_name, ArrayList_Str* type_args) {
    if (strlist_find(&(self->monomorphized_types), mangled_name) >= 0LL) {
    return;
}
    ArrayList_Str_push(&(self->monomorphized_types), mangled_name);
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, func_stmt_idx);
    ArrayList_StrMapEntry old_type_map = self->current_type_map;
    self->current_type_map = ArrayList_StrMapEntry_init(self->allocator);
    Codegen_setup_current_type_map(self, &(stmt.func_type_params), type_args);
    const char* concrete_ret_type = Codegen_substitute_generic_type(self, stmt.func_return_type);
    const char* mapped_ret = Codegen_map_type(self, concrete_ret_type);
    const char* params_str = "";
    int64_t p_idx = 0LL;
    while (p_idx < ArrayList_Param_length(&(stmt.func_params))) {
    Param p = ArrayList_Param_get(&(stmt.func_params), p_idx);
    if (p_idx > 0LL) {
    params_str = concatAlloc(params_str, ", ");
}
    const char* concrete_ptype = Codegen_substitute_generic_type(self, p.ptype);
    params_str = concatAlloc(concatAlloc(concatAlloc(params_str, Codegen_map_type(self, concrete_ptype)), " "), p.name);
    p_idx = (p_idx + 1LL);
}
    if (strlen(params_str) == 0LL) {
    params_str = "void";
}
    type_map_put(&(self->func_types), mangled_name, concrete_ret_type);
    const char* old_fn = self->cur_func_name;
    const char* old_ret = self->cur_return_type;
    bool old_init = self->cur_method_is_init;
    self->cur_func_name = mangled_name;
    self->cur_return_type = concrete_ret_type;
    self->cur_method_is_init = false;
    int64_t old_var_len = ArrayList_StrMapEntry_length(&(self->var_types));
    int64_t p_reg = 0LL;
    while (p_reg < ArrayList_Param_length(&(stmt.func_params))) {
    Param p = ArrayList_Param_get(&(stmt.func_params), p_reg);
    const char* concrete_ptype = Codegen_substitute_generic_type(self, p.ptype);
    type_map_put(&(self->var_types), p.name, concrete_ptype);
    p_reg = (p_reg + 1LL);
}
    ArrayList_Int old_block_stack = self->block_stack;
    ArrayList_Int old_defer_stack = self->defer_stack;
    ArrayList_Int old_defer_depths = self->defer_depths;
    self->block_stack = ArrayList_Int_init(self->allocator);
    self->defer_stack = ArrayList_Int_init(self->allocator);
    self->defer_depths = ArrayList_Int_init(self->allocator);
    const char* body_str = Codegen_gen_stmt(self, stmt.func_body);
    self->block_stack = old_block_stack;
    self->defer_stack = old_defer_stack;
    self->defer_depths = old_defer_depths;
    while (ArrayList_StrMapEntry_length(&(self->var_types)) > old_var_len) {
    (void)(ArrayList_StrMapEntry_pop(&(self->var_types)));
}
    const char* proto = concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(mapped_ret, " "), mangled_name), "("), params_str), ");\n");
    const char* impl_str = concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(mapped_ret, " "), mangled_name), "("), params_str), ") "), body_str), "\n");
    (void)(StringBuilder_append(&(self->func_decls), proto));
    (void)(StringBuilder_append(&(self->output), impl_str));
    self->cur_func_name = old_fn;
    self->cur_return_type = old_ret;
    self->cur_method_is_init = old_init;
    self->current_type_map = old_type_map;
}
const char* Codegen_extract_first_type_arg(Codegen* self, const char* type_name) {
    int64_t start = (-1LL);
    int64_t end = (-1LL);
    int64_t i = 0LL;
    while (i < strlen(type_name)) {
    char c = (type_name)[i];
    if (c == ((char)(60LL))) {
    start = (i + 1LL);
} else if (c == ((char)(44LL))) {
    end = i;
    break;
} else if (c == ((char)(62LL))) {
    end = i;
    break;
}
    i = (i + 1LL);
}
    if ((start >= 0LL) && (end >= 0LL)) {
    return __kai_str_sub(type_name, start, end);
}
    return "Int";
}
void Codegen_build_func_types(Codegen* self) {
    int64_t i = 0LL;
    while (i < ArrayList_StmtNode_length(self->stmt_pool)) {
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, i);
    if (stmt.kind == StmtKind_sk_func_decl) {
    type_map_put(&(self->func_types), stmt.func_name, stmt.func_return_type);
    int64_t p_i = 0LL;
    while (p_i < ArrayList_Param_length(&(stmt.func_params))) {
    Param p = ArrayList_Param_get(&(stmt.func_params), p_i);
    const char* p_key = concatAlloc(concatAlloc(stmt.func_name, "_param_"), int_to_str(p_i));
    type_map_put(&(self->func_param_types), p_key, p.ptype);
    p_i = (p_i + 1LL);
}
}
    if (stmt.kind == StmtKind_sk_extern) {
    type_map_put(&(self->func_types), stmt.extern_name, stmt.extern_return);
    int64_t p_i = 0LL;
    while (p_i < ArrayList_Param_length(&(stmt.extern_params))) {
    Param p = ArrayList_Param_get(&(stmt.extern_params), p_i);
    const char* p_key = concatAlloc(concatAlloc(stmt.extern_name, "_param_"), int_to_str(p_i));
    type_map_put(&(self->func_param_types), p_key, p.ptype);
    p_i = (p_i + 1LL);
}
}
    if (stmt.kind == StmtKind_sk_impl_block) {
    const char* struct_name = stmt.impl_struct_name;
    int64_t j = 0LL;
    while (j < ArrayList_Int_length(&(stmt.impl_methods))) {
    int64_t m_idx = ArrayList_Int_get(&(stmt.impl_methods), j);
    StmtNode m_node = ArrayList_StmtNode_get(self->stmt_pool, m_idx);
    const char* key = concatAlloc(concatAlloc(struct_name, "_"), m_node.func_name);
    const char* ret = m_node.func_return_type;
    if (strcmp(m_node.func_name, "init") == 0) {
    ret = struct_name;
}
    type_map_put(&(self->func_types), key, ret);
    int64_t p_i = 0LL;
    while (p_i < ArrayList_Param_length(&(m_node.func_params))) {
    Param p = ArrayList_Param_get(&(m_node.func_params), p_i);
    const char* p_key = concatAlloc(concatAlloc(key, "_param_"), int_to_str(p_i));
    type_map_put(&(self->func_param_types), p_key, p.ptype);
    p_i = (p_i + 1LL);
}
    j = (j + 1LL);
}
}
    if (stmt.kind == StmtKind_sk_struct_decl) {
    const char* struct_name = stmt.struct_name;
    int64_t ti = 0LL;
    while (ti < ArrayList_Int_length(&(stmt.struct_trait_impls))) {
    int64_t impl_idx = ArrayList_Int_get(&(stmt.struct_trait_impls), ti);
    StmtNode impl_node = ArrayList_StmtNode_get(self->stmt_pool, impl_idx);
    int64_t j = 0LL;
    while (j < ArrayList_Int_length(&(impl_node.impl_methods))) {
    int64_t m_idx = ArrayList_Int_get(&(impl_node.impl_methods), j);
    StmtNode m_node = ArrayList_StmtNode_get(self->stmt_pool, m_idx);
    const char* key = concatAlloc(concatAlloc(struct_name, "_"), m_node.func_name);
    const char* ret = m_node.func_return_type;
    if (strcmp(m_node.func_name, "init") == 0) {
    ret = struct_name;
}
    type_map_put(&(self->func_types), key, ret);
    int64_t p_i = 0LL;
    while (p_i < ArrayList_Param_length(&(m_node.func_params))) {
    Param p = ArrayList_Param_get(&(m_node.func_params), p_i);
    const char* p_key = concatAlloc(concatAlloc(key, "_param_"), int_to_str(p_i));
    type_map_put(&(self->func_param_types), p_key, p.ptype);
    p_i = (p_i + 1LL);
}
    j = (j + 1LL);
}
    ti = (ti + 1LL);
}
}
    i = (i + 1LL);
}
}
const char* Codegen_get_expr_type(Codegen* self, int64_t expr_idx) {
    if (expr_idx < 0LL) {
    return "Void";
}
    ExprNode expr = ArrayList_ExprNode_get(self->expr_pool, expr_idx);
    if (expr.kind == ExprKind_ek_literal) {
    const char* vkind = expr.lit_vkind;
    if (strcmp(vkind, "INT") == 0) {
    return "Int";
}
    if (strcmp(vkind, "FLOAT") == 0) {
    return "Float";
}
    if (strcmp(vkind, "STRING") == 0) {
    return "Str";
}
    if (strcmp(vkind, "BOOL") == 0) {
    return "Bool";
}
    if (strcmp(vkind, "CHAR") == 0) {
    return "Char";
}
    return "Void";
}
    if (expr.kind == ExprKind_ek_identifier) {
    const char* name = expr.ident_name;
    const char* var_t = type_map_get(&(self->var_types), name);
    if (strlen(var_t) > 0LL) {
    return var_t;
}
    const char* fn_t = type_map_get(&(self->func_types), name);
    if (strlen(fn_t) > 0LL) {
    return fn_t;
}
    char first_char = (name)[0LL];
    if ((first_char >= ((char)(65LL))) && (first_char <= ((char)(90LL)))) {
    if (ArrayList_Str_length(&(expr.ident_type_args)) > 0LL) {
    const char* full_name = concatAlloc(name, "<");
    int64_t tai = 0LL;
    while (tai < ArrayList_Str_length(&(expr.ident_type_args))) {
    if (tai > 0LL) {
    full_name = concatAlloc(full_name, ", ");
}
    full_name = concatAlloc(full_name, ArrayList_Str_get(&(expr.ident_type_args), tai));
    tai = (tai + 1LL);
}
    full_name = concatAlloc(full_name, ">");
    return full_name;
}
    return name;
}
    return "Void";
}
    if (expr.kind == ExprKind_ek_binary_op) {
    const char* op = expr.binop_op;
    if ((((((((strcmp(op, "==") == 0) || (strcmp(op, "!=") == 0)) || (strcmp(op, "<") == 0)) || (strcmp(op, ">") == 0)) || (strcmp(op, "<=") == 0)) || (strcmp(op, ">=") == 0)) || (strcmp(op, "&&") == 0)) || (strcmp(op, "||") == 0)) {
    return "Bool";
}
    return Codegen_get_expr_type(self, expr.binop_left);
}
    if (expr.kind == ExprKind_ek_unary_op) {
    const char* op = expr.unop_op;
    if (strcmp(op, "!") == 0) {
    return "Bool";
}
    return Codegen_get_expr_type(self, expr.unop_operand);
}
    if (expr.kind == ExprKind_ek_func_call) {
    const char* name = expr.func_name;
    if ((strcmp(name, "cast") == 0) || (strcmp(name, "as") == 0)) {
    return ArrayList_Str_get(&(expr.func_type_args), 0LL);
}
    if (strcmp(name, "size_of") == 0) {
    return "Int";
}
    if ((((strcmp(name, "Char") == 0) || (strcmp(name, "Int") == 0)) || (strcmp(name, "Float") == 0)) || (strcmp(name, "Bool") == 0)) {
    return name;
}
    bool is_struct = false;
    int64_t s_idx = 0LL;
    while (s_idx < ArrayList_StmtNode_length(self->stmt_pool)) {
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, s_idx);
    if ((stmt.kind == StmtKind_sk_struct_decl) && (strcmp(stmt.struct_name, name) == 0)) {
    is_struct = true;
}
    s_idx = (s_idx + 1LL);
}
    if (((strcmp(name, "ArrayList") == 0) || (strcmp(name, "HashMap") == 0)) || (strcmp(name, "StringBuilder") == 0)) {
    is_struct = true;
}
    if (is_struct) {
    if (ArrayList_Str_length(&(expr.func_type_args)) > 0LL) {
    return concatAlloc(concatAlloc(concatAlloc(name, "<"), str_array_join(expr.func_type_args, ", ")), ">");
}
    return name;
}
    const char* gf_idx_str = type_map_get(&(self->generic_func_decls), name);
    if (strlen(gf_idx_str) > 0LL) {
    int64_t gf_idx = Codegen_str_to_int(self, gf_idx_str);
    ArrayList_Str type_args = ArrayList_Str_init(self->allocator);
    if (ArrayList_Str_length(&(expr.func_type_args)) > 0LL) {
    int64_t j = 0LL;
    while (j < ArrayList_Str_length(&(expr.func_type_args))) {
    ArrayList_Str_push(&(type_args), ArrayList_Str_get(&(expr.func_type_args), j));
    j = (j + 1LL);
}
} else {
    type_args = Codegen_infer_type_args(self, gf_idx, expr_idx);
}
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, gf_idx);
    ArrayList_StrMapEntry old_type_map = self->current_type_map;
    self->current_type_map = ArrayList_StrMapEntry_init(self->allocator);
    Codegen_setup_current_type_map(self, &(stmt.func_type_params), &(type_args));
    const char* ret_t = Codegen_substitute_generic_type(self, stmt.func_return_type);
    self->current_type_map = old_type_map;
    return ret_t;
}
    const char* fn_t = type_map_get(&(self->func_types), name);
    if (strlen(fn_t) > 0LL) {
    return fn_t;
}
    int64_t si = 0LL;
    while (si < ArrayList_StmtNode_length(self->stmt_pool)) {
    StmtNode s = ArrayList_StmtNode_get(self->stmt_pool, si);
    if ((s.kind == StmtKind_sk_extern) && (strcmp(s.extern_name, name) == 0)) {
    return s.extern_return;
}
    if ((s.kind == StmtKind_sk_func_decl) && (strcmp(s.func_name, name) == 0)) {
    return s.func_return_type;
}
    si = (si + 1LL);
}
    return "Void";
}
    if (expr.kind == ExprKind_ek_field_access) {
    ExprNode base_node = ArrayList_ExprNode_get(self->expr_pool, expr.field_expr);
    if (base_node.kind == ExprKind_ek_identifier) {
    bool is_static = false;
    int64_t s_idx = 0LL;
    while (s_idx < ArrayList_StmtNode_length(self->stmt_pool)) {
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, s_idx);
    if (((stmt.kind == StmtKind_sk_enum_decl) && (strcmp(stmt.enum_name, base_node.ident_name) == 0)) || ((stmt.kind == StmtKind_sk_error_decl) && (strcmp(stmt.error_name, base_node.ident_name) == 0))) {
    is_static = true;
}
    s_idx = (s_idx + 1LL);
}
    if (is_static) {
    return base_node.ident_name;
}
}
    const char* base_type = Codegen_get_expr_type(self, expr.field_expr);
    const char* clean_type = "";
    int64_t i = 0LL;
    while (i < strlen(base_type)) {
    char c = (base_type)[i];
    if ((c != ((char)(42LL))) && (c != ((char)(38LL)))) {
    clean_type = concatAlloc(clean_type, char_to_str(c));
}
    i = (i + 1LL);
}
    if (strcmp(__kai_str_sub(clean_type, 0LL, 4LL), "mut ") == 0) {
    clean_type = __kai_str_sub(clean_type, 4LL, strlen(clean_type));
}
    int64_t s_idx = 0LL;
    while (s_idx < ArrayList_StmtNode_length(self->stmt_pool)) {
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, s_idx);
    if (stmt.kind == StmtKind_sk_struct_decl) {
    bool is_match = false;
    if (strcmp(stmt.struct_name, clean_type) == 0) {
    is_match = true;
} else if (Codegen_str_contains(self, clean_type, ((char)(95LL)))) {
    if (ArrayList_Str_length(&(stmt.struct_type_params)) > 0LL) {
    int64_t underscore_pos = Codegen_str_find(self, clean_type, ((char)(95LL)));
    const char* base_name = __kai_str_sub(clean_type, 0LL, underscore_pos);
    if (strcmp(stmt.struct_name, base_name) == 0) {
    is_match = true;
}
}
}
    if (is_match) {
    int64_t f_idx = 0LL;
    while (f_idx < ArrayList_StructField_length(&(stmt.struct_fields))) {
    StructField f = ArrayList_StructField_get(&(stmt.struct_fields), f_idx);
    if (strcmp(f.name, expr.field_name) == 0) {
    const char* ftype = f.ftype;
    if (ArrayList_StrMapEntry_length(&(self->current_type_map)) > 0LL) {
    ftype = Codegen_substitute_generic_type(self, ftype);
}
    return ftype;
}
    f_idx = (f_idx + 1LL);
}
}
}
    s_idx = (s_idx + 1LL);
}
    return "Void";
}
    if (expr.kind == ExprKind_ek_index) {
    const char* base_type = Codegen_get_expr_type(self, expr.idx_expr);
    if (strcmp(base_type, "Str") == 0) {
    return "Char";
}
    if ((strlen(base_type) >= 2LL) && (strcmp(__kai_str_sub(base_type, 0LL, 2LL), "[]") == 0)) {
    return __kai_str_sub(base_type, 2LL, strlen(base_type));
}
    if ((strlen(base_type) > 0LL) && ((base_type)[0LL] == ((char)(42LL)))) {
    return __kai_str_sub(base_type, 1LL, strlen(base_type));
}
    return "Void";
}
    if (expr.kind == ExprKind_ek_borrow) {
    return concatAlloc("&", Codegen_get_expr_type(self, expr.borrow_expr));
}
    if (expr.kind == ExprKind_ek_deref) {
    const char* base_type = Codegen_get_expr_type(self, expr.deref_expr);
    if ((strlen(base_type) > 5LL) && (strcmp(__kai_str_sub(base_type, 0LL, 5LL), "*mut ") == 0)) {
    return __kai_str_sub(base_type, 5LL, strlen(base_type));
}
    if ((strlen(base_type) > 5LL) && (strcmp(__kai_str_sub(base_type, 0LL, 5LL), "&mut ") == 0)) {
    return __kai_str_sub(base_type, 5LL, strlen(base_type));
}
    if (((base_type)[0LL] == ((char)(42LL))) || ((base_type)[0LL] == ((char)(38LL)))) {
    return __kai_str_sub(base_type, 1LL, strlen(base_type));
}
    return "Void";
}
    if (expr.kind == ExprKind_ek_struct_init) {
    const char* sname = expr.struct_name;
    int64_t dot_pos = Codegen_str_find(self, sname, ((char)(46LL)));
    if (dot_pos >= 0LL) {
    return __kai_str_sub(sname, 0LL, dot_pos);
}
    return sname;
}
    if (expr.kind == ExprKind_ek_method_call) {
    ExprNode receiver_node = ArrayList_ExprNode_get(self->expr_pool, expr.meth_expr);
    const char* method_name = expr.meth_name;
    const char* rec_type = Codegen_get_expr_type(self, expr.meth_expr);
    const char* clean_type = "";
    int64_t i = 0LL;
    while (i < strlen(rec_type)) {
    char c = (rec_type)[i];
    if ((c != ((char)(42LL))) && (c != ((char)(38LL)))) {
    clean_type = concatAlloc(clean_type, char_to_str(c));
}
    i = (i + 1LL);
}
    if (strcmp(__kai_str_sub(clean_type, 0LL, 4LL), "mut ") == 0) {
    clean_type = __kai_str_sub(clean_type, 4LL, strlen(clean_type));
}
    bool is_constructor = false;
    if (receiver_node.kind == ExprKind_ek_identifier) {
    const char* r_name = receiver_node.ident_name;
    char first_char = (r_name)[0LL];
    if ((first_char >= ((char)(65LL))) && (first_char <= ((char)(90LL)))) {
    is_constructor = true;
}
}
    if (strcmp(method_name, "init") == 0) {
    return clean_type;
}
    const char* key = concatAlloc(concatAlloc(clean_type, "_"), method_name);
    const char* ret = type_map_get(&(self->func_types), key);
    if (strlen(ret) > 0LL) {
    return ret;
}
    const char* clean_rec = rec_type;
    bool done = false;
    while (!done) {
    if ((strlen(clean_rec) > 0LL) && (((clean_rec)[0LL] == ((char)(42LL))) || ((clean_rec)[0LL] == ((char)(38LL))))) {
    clean_rec = __kai_str_sub(clean_rec, 1LL, strlen(clean_rec));
} else {
    done = true;
}
}
    if (strcmp(__kai_str_sub(clean_rec, 0LL, 4LL), "mut ") == 0) {
    clean_rec = __kai_str_sub(clean_rec, 4LL, strlen(clean_rec));
}
    if (Codegen_str_contains(self, clean_rec, ((char)(60LL)))) {
    int64_t lt_pos = Codegen_str_find(self, clean_rec, ((char)(60LL)));
    const char* base_struct = __kai_str_sub(clean_rec, 0LL, lt_pos);
    const char* args_str = __kai_str_sub(clean_rec, (lt_pos + 1LL), (strlen(clean_rec) - 1LL));
    ArrayList_Str args = ArrayList_Str_init(self->allocator);
    int64_t start = 0LL;
    int64_t ai = 0LL;
    while (ai < strlen(args_str)) {
    char c = (args_str)[ai];
    if (c == ((char)(44LL))) {
    ArrayList_Str_push(&(args), Codegen_trim_spaces(self, __kai_str_sub(args_str, start, ai)));
    start = (ai + 1LL);
}
    ai = (ai + 1LL);
}
    ArrayList_Str_push(&(args), Codegen_trim_spaces(self, __kai_str_sub(args_str, start, strlen(args_str))));
    int64_t struct_idx = (-1LL);
    int64_t si = 0LL;
    while (si < ArrayList_StmtNode_length(self->stmt_pool)) {
    StmtNode s = ArrayList_StmtNode_get(self->stmt_pool, si);
    if ((s.kind == StmtKind_sk_struct_decl) && (strcmp(s.struct_name, base_struct) == 0)) {
    struct_idx = si;
}
    si = (si + 1LL);
}
    if (struct_idx >= 0LL) {
    StmtNode s_decl = ArrayList_StmtNode_get(self->stmt_pool, struct_idx);
    ArrayList_StrMapEntry temp_map = ArrayList_StrMapEntry_init(self->allocator);
    int64_t pi = 0LL;
    while (pi < ArrayList_Str_length(&(s_decl.struct_type_params))) {
    const char* p_name = Codegen_trim_spaces(self, ArrayList_Str_get(&(s_decl.struct_type_params), pi));
    if (Codegen_str_contains(self, p_name, ((char)(58LL)))) {
    int64_t cp = Codegen_str_find(self, p_name, ((char)(58LL)));
    p_name = __kai_str_sub(p_name, 0LL, cp);
}
    const char* a_name = ArrayList_Str_get(&(args), pi);
    type_map_put(&(temp_map), p_name, a_name);
    pi = (pi + 1LL);
}
    int64_t impl_idx = 0LL;
    while (impl_idx < ArrayList_StmtNode_length(self->stmt_pool)) {
    StmtNode s_impl = ArrayList_StmtNode_get(self->stmt_pool, impl_idx);
    if ((s_impl.kind == StmtKind_sk_impl_block) && (strcmp(s_impl.impl_struct_name, base_struct) == 0)) {
    int64_t mi = 0LL;
    while (mi < ArrayList_Int_length(&(s_impl.impl_methods))) {
    StmtNode m_node = ArrayList_StmtNode_get(self->stmt_pool, ArrayList_Int_get(&(s_impl.impl_methods), mi));
    if (strcmp(m_node.func_name, method_name) == 0) {
    const char* ret_t = m_node.func_return_type;
    ArrayList_StrMapEntry old_type_map = self->current_type_map;
    self->current_type_map = temp_map;
    ret_t = Codegen_substitute_generic_type(self, ret_t);
    self->current_type_map = old_type_map;
    return ret_t;
}
    mi = (mi + 1LL);
}
}
    impl_idx = (impl_idx + 1LL);
}
}
}
    return "Void";
}
    if (expr.kind == ExprKind_ek_range) {
    return "Range";
}
    if (expr.kind == ExprKind_ek_slice) {
    if (strlen(expr.inferred_type) > 0LL) {
    return expr.inferred_type;
}
    return Codegen_get_expr_type(self, expr.slice_expr);
}
    if (expr.kind == ExprKind_ek_array) {
    return expr.inferred_type;
}
    if (expr.kind == ExprKind_ek_tuple) {
    return expr.inferred_type;
}
    if (expr.kind == ExprKind_ek_asm) {
    return expr.inferred_type;
}
    if (expr.kind == ExprKind_ek_try) {
    const char* inner_ty = Codegen_get_expr_type(self, expr.try_expr);
    int64_t excl_pos = Codegen_str_find(self, inner_ty, ((char)(33LL)));
    if (excl_pos >= 0LL) {
    return __kai_str_sub(inner_ty, 0LL, excl_pos);
}
    return inner_ty;
}
    if (expr.kind == ExprKind_ek_catch) {
    const char* inner_ty = Codegen_get_expr_type(self, expr.catch_expr);
    if ((strlen(inner_ty) > 0LL) && ((inner_ty)[0LL] == ((char)(63LL)))) {
    return __kai_str_sub(inner_ty, 1LL, strlen(inner_ty));
}
    int64_t excl_pos = Codegen_str_find(self, inner_ty, ((char)(33LL)));
    if (excl_pos >= 0LL) {
    return __kai_str_sub(inner_ty, 0LL, excl_pos);
}
    return inner_ty;
}
    return "Void";
}
const char* Codegen_gen_expr_with_expected_type(Codegen* self, int64_t expr_idx, const char* expected_type) {
    if (expr_idx < 0LL) {
    return "";
}
    ExprNode expr = ArrayList_ExprNode_get(self->expr_pool, expr_idx);
    const char* actual_type = Codegen_get_expr_type(self, expr_idx);
    if ((expr.kind == ExprKind_ek_literal) && (strcmp(expr.lit_vkind, "NONE") == 0)) {
    if ((strlen(expected_type) > 0LL) && ((expected_type)[0LL] == ((char)(63LL)))) {
    const char* val_type = __kai_str_sub(expected_type, 1LL, strlen(expected_type));
    if (Codegen_is_pointer_type(self, val_type)) {
    return "NULL";
}
    return concatAlloc(concatAlloc("(", Codegen_map_type(self, expected_type)), "){0}");
}
    return "NULL";
}
    const char* gen_val = Codegen_gen_expr(self, expr_idx);
    if ((strlen(expected_type) > 0LL) && ((expected_type)[0LL] == ((char)(63LL)))) {
    const char* val_type = __kai_str_sub(expected_type, 1LL, strlen(expected_type));
    if ((!Codegen_is_pointer_type(self, val_type)) && (strcmp(actual_type, val_type) == 0)) {
    return concatAlloc(concatAlloc(concatAlloc(concatAlloc("(", Codegen_map_type(self, expected_type)), "){ .has_value = true, .value = "), gen_val), " }");
}
}
    return gen_val;
}
const char* Codegen_gen_expr(Codegen* self, int64_t expr_idx) {
    if (expr_idx < 0LL) {
    return "";
}
    ExprNode expr = ArrayList_ExprNode_get(self->expr_pool, expr_idx);
    if (expr.kind == ExprKind_ek_try) {
    const char* inner_ty = Codegen_get_expr_type(self, expr.try_expr);
    int64_t excl_pos = Codegen_str_find(self, inner_ty, ((char)(33LL)));
    const char* inner = Codegen_gen_expr(self, expr.try_expr);
    if (excl_pos < 0LL) {
    return inner;
}
    const char* val_type = __kai_str_sub(inner_ty, 0LL, excl_pos);
    const char* result_ctype = Codegen_map_type(self, inner_ty);
    const char* ret_ctype = Codegen_map_type(self, self->cur_return_type);
    const char* try_code = concatAlloc(concatAlloc(concatAlloc(concatAlloc("({ ", result_ctype), " _kai_res = ("), inner), "); ");
    try_code = concatAlloc(try_code, "if (_kai_res.tag != 0) { ");
    try_code = concatAlloc(concatAlloc(try_code, ret_ctype), " _kai_err_ret; _kai_err_ret.tag = _kai_res.tag; return _kai_err_ret; } ");
    if (strcmp(val_type, "Void") == 0) {
    try_code = concatAlloc(try_code, "0; })");
} else {
    try_code = concatAlloc(try_code, "_kai_res.value; })");
}
    return try_code;
}
    if (expr.kind == ExprKind_ek_literal) {
    const char* vkind = expr.lit_vkind;
    if (strcmp(vkind, "INT") == 0) {
    if (expr.lit_value.tag == TokenValue_tv_str_TAG) {
    int64_t v = expr.lit_value.payload.tv_str.v;

    const char* s = StringPool_get(self->pool, v);
    return concatAlloc(s, "LL");
} else if (expr.lit_value.tag == TokenValue_tv_int_TAG) {
    int64_t v = expr.lit_value.payload.tv_int.v;

    return concatAlloc(int_to_str(v), "LL");
} else {
    return "0LL";
} 
}
    if (strcmp(vkind, "FLOAT") == 0) {
    if (expr.lit_value.tag == TokenValue_tv_str_TAG) {
    int64_t v = expr.lit_value.payload.tv_str.v;

    return StringPool_get(self->pool, v);
} else {
    return "0.0";
} 
}
    if (strcmp(vkind, "STRING") == 0) {
    if (expr.lit_value.tag == TokenValue_tv_str_TAG) {
    int64_t v = expr.lit_value.payload.tv_str.v;

    return concatAlloc(concatAlloc("\"", Codegen_escape_string(self, StringPool_get(self->pool, v))), "\"");
} else {
    return "\"\"";
} 
}
    if (strcmp(vkind, "BOOL") == 0) {
    if (expr.lit_value.tag == TokenValue_tv_bool_TAG) {
    bool v = expr.lit_value.payload.tv_bool.v;

    if (v) {
    return "true";
} else {
    return "false";
}
} else if (expr.lit_value.tag == TokenValue_tv_str_TAG) {
    int64_t v = expr.lit_value.payload.tv_str.v;

    bool is_true = false;
    {
    if (strcmp(StringPool_get(self->pool, v), "true") == 0LL) {
    is_true = true;
}
}
    if (is_true) {
    return "true";
}
    return "false";
} else {
    return "false";
} 
}
    if (strcmp(vkind, "CHAR") == 0) {
    if (expr.lit_value.tag == TokenValue_tv_char_TAG) {
    char v = expr.lit_value.payload.tv_char.v;

    if (v == ((char)(10LL))) {
    return "'\\n'";
}
    if (v == ((char)(13LL))) {
    return "'\\r'";
}
    if (v == ((char)(9LL))) {
    return "'\\t'";
}
    if (v == ((char)(92LL))) {
    return "'\\\\'";
}
    if (v == ((char)(39LL))) {
    return "'\\''";
}
    return concatAlloc(concatAlloc("'", char_to_str(v)), "'");
} else {
    return "'\\0'";
} 
}
    if (strcmp(vkind, "NONE") == 0) {
    return "NULL";
}
    return "0";
}
    if (expr.kind == ExprKind_ek_str_interp) {
    if (ArrayList_StrInterpPart_length(&(expr.interp_parts)) == 0LL) {
    return "\"\"";
}
    const char* result = "";
    int64_t i = 0LL;
    while (i < ArrayList_StrInterpPart_length(&(expr.interp_parts))) {
    StrInterpPart part = ArrayList_StrInterpPart_get(&(expr.interp_parts), i);
    const char* part_str = "";
    if (part.kind == 0LL) {
    part_str = concatAlloc(concatAlloc("\"", Codegen_escape_string(self, part.str_val)), "\"");
} else {
    const char* expr_val = Codegen_gen_expr(self, part.expr_idx);
    const char* expr_type = Codegen_get_expr_type(self, part.expr_idx);
    if (strcmp(expr_type, "Int") == 0) {
    part_str = concatAlloc(concatAlloc("int_to_str(", expr_val), ")");
} else if (strcmp(expr_type, "Char") == 0) {
    part_str = concatAlloc(concatAlloc("char_to_str(", expr_val), ")");
} else if (strcmp(expr_type, "Bool") == 0) {
    part_str = concatAlloc(concatAlloc("((", expr_val), ") ? \"true\" : \"false\")");
} else if (strcmp(expr_type, "Str") == 0) {
    part_str = expr_val;
} else {
    part_str = expr_val;
}
}
    if (i == 0LL) {
    result = part_str;
} else {
    result = concatAlloc(concatAlloc(concatAlloc(concatAlloc("concatAlloc(", result), ", "), part_str), ")");
}
    i = (i + 1LL);
}
    return result;
}
    if (expr.kind == ExprKind_ek_identifier) {
    return expr.ident_name;
}
    if (expr.kind == ExprKind_ek_binary_op) {
    const char* lhs = Codegen_gen_expr(self, expr.binop_left);
    const char* rhs = Codegen_gen_expr(self, expr.binop_right);
    const char* op = expr.binop_op;
    const char* lhs_type = Codegen_get_expr_type(self, expr.binop_left);
    const char* rhs_type = Codegen_get_expr_type(self, expr.binop_right);
    if ((strcmp(op, "==") == 0) || (strcmp(op, "!=") == 0)) {
    if (((strlen(lhs_type) > 0LL) && ((lhs_type)[0LL] == ((char)(63LL)))) && (strcmp(rhs, "NULL") == 0)) {
    const char* val_type = __kai_str_sub(lhs_type, 1LL, strlen(lhs_type));
    if (Codegen_is_pointer_type(self, val_type)) {
    return concatAlloc(concatAlloc(concatAlloc(concatAlloc("(", lhs), " "), op), " NULL)");
}
    if (strcmp(op, "==") == 0) {
    return concatAlloc(concatAlloc("(!", lhs), ".has_value)");
}
    return concatAlloc(concatAlloc("(", lhs), ".has_value)");
}
    if (((strlen(rhs_type) > 0LL) && ((rhs_type)[0LL] == ((char)(63LL)))) && (strcmp(lhs, "NULL") == 0)) {
    const char* val_type = __kai_str_sub(rhs_type, 1LL, strlen(rhs_type));
    if (Codegen_is_pointer_type(self, val_type)) {
    return concatAlloc(concatAlloc(concatAlloc(concatAlloc("(NULL ", op), " "), rhs), ")");
}
    if (strcmp(op, "==") == 0) {
    return concatAlloc(concatAlloc("(!", rhs), ".has_value)");
}
    return concatAlloc(concatAlloc("(", rhs), ".has_value)");
}
}
    ExprNode lhs_node = ArrayList_ExprNode_get(self->expr_pool, expr.binop_left);
    if (strcmp(lhs_type, "Str") == 0) {
    if (strcmp(op, "+") == 0) {
    return concatAlloc(concatAlloc(concatAlloc(concatAlloc("concatAlloc(", lhs), ", "), rhs), ")");
}
    if (strcmp(op, "==") == 0) {
    return concatAlloc(concatAlloc(concatAlloc(concatAlloc("(strcmp(", lhs), ", "), rhs), ") == 0)");
}
    if (strcmp(op, "!=") == 0) {
    return concatAlloc(concatAlloc(concatAlloc(concatAlloc("(strcmp(", lhs), ", "), rhs), ") != 0)");
}
}
    if (((strcmp(op, "==") == 0) || (strcmp(op, "!=") == 0)) && Codegen_is_enum_type(self, lhs_type)) {
    if (Codegen_enum_has_payload(self, lhs_type)) {
    bool is_ptr = false;
    if (((lhs_type)[0LL] == ((char)(42LL))) || ((lhs_type)[0LL] == ((char)(38LL)))) {
    is_ptr = true;
}
    const char* tag_op = ".";
    if (is_ptr) {
    tag_op = "->";
}
    const char* rhs_type = Codegen_get_expr_type(self, expr.binop_right);
    bool rhs_is_ptr = false;
    if (((rhs_type)[0LL] == ((char)(42LL))) || ((rhs_type)[0LL] == ((char)(38LL)))) {
    rhs_is_ptr = true;
}
    const char* rhs_tag_op = ".";
    if (rhs_is_ptr) {
    rhs_tag_op = "->";
}
    return concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc("((", lhs), ")"), tag_op), "tag "), op), " ("), rhs), ")"), rhs_tag_op), "tag)");
}
}
    return concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc("(", lhs), " "), op), " "), rhs), ")");
}
    if (expr.kind == ExprKind_ek_unary_op) {
    const char* operand = Codegen_gen_expr(self, expr.unop_operand);
    const char* op = expr.unop_op;
    if (strcmp(op, "own") == 0) {
    return operand;
}
    return concatAlloc(concatAlloc(concatAlloc("(", op), operand), ")");
}
    if (expr.kind == ExprKind_ek_func_call) {
    const char* name = expr.func_name;
    if ((strcmp(name, "cast") == 0) || (strcmp(name, "as") == 0)) {
    const char* target_type = ArrayList_Str_get(&(expr.func_type_args), 0LL);
    const char* operand_type = Codegen_get_expr_type(self, ArrayList_Int_get(&(expr.func_args), 0LL));
    bool is_target_ptr = (((strlen(target_type) > 0LL) && (((target_type)[0LL] == ((char)(42LL))) || ((target_type)[0LL] == ((char)(38LL))))) || (strcmp(target_type, "Str") == 0LL));
    bool is_operand_int = (((strcmp(operand_type, "Int") == 0LL) || (strcmp(operand_type, "Char") == 0LL)) || (strcmp(operand_type, "Bool") == 0LL));
    if (is_target_ptr && is_operand_int) {
    return concatAlloc(concatAlloc(concatAlloc(concatAlloc("(", Codegen_map_type(self, target_type)), ")(unsigned long long)("), Codegen_gen_expr(self, ArrayList_Int_get(&(expr.func_args), 0LL))), ")");
}
    return concatAlloc(concatAlloc(concatAlloc(concatAlloc("(", Codegen_map_type(self, target_type)), ")("), Codegen_gen_expr(self, ArrayList_Int_get(&(expr.func_args), 0LL))), ")");
}
    if (strcmp(name, "size_of") == 0) {
    return concatAlloc(concatAlloc("sizeof(", Codegen_map_type(self, ArrayList_Str_get(&(expr.func_type_args), 0LL))), ")");
}
    if ((((strcmp(name, "Char") == 0) || (strcmp(name, "Int") == 0)) || (strcmp(name, "Float") == 0)) || (strcmp(name, "Bool") == 0)) {
    const char* ctype = Codegen_map_type(self, name);
    const char* arg_val = Codegen_gen_expr(self, ArrayList_Int_get(&(expr.func_args), 0LL));
    return concatAlloc(concatAlloc(concatAlloc(concatAlloc("((", ctype), ")("), arg_val), "))");
}
    if (strcmp(name, "length") == 0) {
    const char* arg_val = Codegen_gen_expr(self, ArrayList_Int_get(&(expr.func_args), 0LL));
    return concatAlloc(concatAlloc("strlen(", arg_val), ")");
}
    bool is_struct = false;
    int64_t s_idx = 0LL;
    while (s_idx < ArrayList_StmtNode_length(self->stmt_pool)) {
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, s_idx);
    if ((stmt.kind == StmtKind_sk_struct_decl) && (strcmp(stmt.struct_name, name) == 0)) {
    is_struct = true;
}
    s_idx = (s_idx + 1LL);
}
    if (((strcmp(name, "ArrayList") == 0) || (strcmp(name, "HashMap") == 0)) || (strcmp(name, "StringBuilder") == 0)) {
    is_struct = true;
}
    const char* fn_name = name;
    ArrayList_Str type_args = ArrayList_Str_init(self->allocator);
    const char* gf_idx_str = type_map_get(&(self->generic_func_decls), name);
    if (strlen(gf_idx_str) > 0LL) {
    int64_t gf_idx = Codegen_str_to_int(self, gf_idx_str);
    if (ArrayList_Str_length(&(expr.func_type_args)) > 0LL) {
    int64_t j = 0LL;
    while (j < ArrayList_Str_length(&(expr.func_type_args))) {
    ArrayList_Str_push(&(type_args), ArrayList_Str_get(&(expr.func_type_args), j));
    j = (j + 1LL);
}
} else {
    type_args = Codegen_infer_type_args(self, gf_idx, expr_idx);
}
    int64_t j = 0LL;
    while (j < ArrayList_Str_length(&(type_args))) {
    fn_name = concatAlloc(concatAlloc(fn_name, "_"), Codegen_clean_type_for_mangling(self, ArrayList_Str_get(&(type_args), j)));
    j = (j + 1LL);
}
    Codegen_monomorphize_func(self, gf_idx, fn_name, &(type_args));
} else if (ArrayList_Str_length(&(expr.func_type_args)) > 0LL) {
    int64_t j = 0LL;
    while (j < ArrayList_Str_length(&(expr.func_type_args))) {
    fn_name = concatAlloc(concatAlloc(fn_name, "_"), Codegen_clean_type_for_mangling(self, ArrayList_Str_get(&(expr.func_type_args), j)));
    j = (j + 1LL);
}
}
    if (is_struct) {
    fn_name = concatAlloc(fn_name, "_init");
}
    const char* args_str = "";
    int64_t i = 0LL;
    while (i < ArrayList_Int_length(&(expr.func_args))) {
    if (i > 0LL) {
    args_str = concatAlloc(args_str, ", ");
}
    int64_t p_idx = i;
    if (is_struct) {
    p_idx = (i + 1LL);
}
    const char* p_key = concatAlloc(concatAlloc(fn_name, "_param_"), int_to_str(p_idx));
    const char* expected_type = type_map_get(&(self->func_param_types), p_key);
    args_str = concatAlloc(args_str, Codegen_gen_expr_with_expected_type(self, ArrayList_Int_get(&(expr.func_args), i), expected_type));
    i = (i + 1LL);
}
    return concatAlloc(concatAlloc(concatAlloc(fn_name, "("), args_str), ")");
}
    if (expr.kind == ExprKind_ek_field_access) {
    ExprNode base_node = ArrayList_ExprNode_get(self->expr_pool, expr.field_expr);
    if ((base_node.kind == ExprKind_ek_identifier) && Codegen_is_enum_type(self, base_node.ident_name)) {
    const char* enum_name = Codegen_map_type(self, Codegen_get_expr_type(self, expr.field_expr));
    const char* var_name = expr.field_name;
    if (Codegen_enum_has_payload(self, base_node.ident_name)) {
    return concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc("(", enum_name), "){ .tag = "), enum_name), "_"), var_name), "_TAG }");
} else {
    return concatAlloc(concatAlloc(enum_name, "_"), var_name);
}
}
    const char* base_val = Codegen_gen_expr(self, expr.field_expr);
    const char* base_type = Codegen_get_expr_type(self, expr.field_expr);
    bool is_ptr = false;
    bool is_self_ptr = (((base_node.kind == ExprKind_ek_identifier) && (strcmp(base_node.ident_name, "self") == 0)) && (!self->cur_method_is_init));
    if ((((base_type)[0LL] == ((char)(42LL))) || ((base_type)[0LL] == ((char)(38LL)))) || is_self_ptr) {
    is_ptr = true;
}
    const char* op = ".";
    if (is_ptr) {
    op = "->";
}
    bool is_complex = (((base_node.kind == ExprKind_ek_func_call) || (base_node.kind == ExprKind_ek_index)) || (base_node.kind == ExprKind_ek_deref));
    if (is_ptr && is_complex) {
    return concatAlloc(concatAlloc(concatAlloc(concatAlloc("(", base_val), ")"), op), expr.field_name);
}
    return concatAlloc(concatAlloc(base_val, op), expr.field_name);
}
    if (expr.kind == ExprKind_ek_index) {
    const char* base_val = Codegen_gen_expr(self, expr.idx_expr);
    const char* idx_val = Codegen_gen_expr(self, expr.idx_index);
    return concatAlloc(concatAlloc(concatAlloc(concatAlloc("(", base_val), ")["), idx_val), "]");
}
    if (expr.kind == ExprKind_ek_borrow) {
    return concatAlloc(concatAlloc("&(", Codegen_gen_expr(self, expr.borrow_expr)), ")");
}
    if (expr.kind == ExprKind_ek_deref) {
    return concatAlloc(concatAlloc("*(", Codegen_gen_expr(self, expr.deref_expr)), ")");
}
    if (expr.kind == ExprKind_ek_check) {
    return Codegen_gen_expr(self, expr.check_expr);
}
    if (expr.kind == ExprKind_ek_try) {
    return Codegen_gen_expr(self, expr.try_expr);
}
    if (expr.kind == ExprKind_ek_range) {
    const char* start = Codegen_gen_expr(self, expr.range_start);
    const char* end = Codegen_gen_expr(self, expr.range_end);
    const char* incl = "false";
    if (expr.range_inclusive) {
    incl = "true";
}
    return concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc("(Range){ .start = ", start), ", .end = "), end), ", .is_inclusive = "), incl), " }");
}
    if (expr.kind == ExprKind_ek_slice) {
    const char* base = Codegen_gen_expr(self, expr.slice_expr);
    const char* base_type = Codegen_get_expr_type(self, expr.slice_expr);
    const char* lower = "0";
    const char* upper = concatAlloc(concatAlloc("strlen(", base), ")");
    if (expr.slice_lower >= 0LL) {
    lower = Codegen_gen_expr(self, expr.slice_lower);
}
    if (expr.slice_upper >= 0LL) {
    upper = Codegen_gen_expr(self, expr.slice_upper);
}
    if ((strcmp(base_type, "Str") == 0) || (strcmp(base_type, "*Char") == 0)) {
    return concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc("__kai_str_sub(", base), ", "), lower), ", "), upper), ")");
}
    if ((strlen(base_type) >= 2LL) && (strcmp(__kai_str_sub(base_type, 0LL, 2LL), "[]") == 0)) {
    const char* inner_type = __kai_str_sub(base_type, 2LL, strlen(base_type));
    const char* mapped_inner = Codegen_map_type(self, inner_type);
    return concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc("__kai_arr_sub(", base), ", "), lower), ", "), upper), ", sizeof("), mapped_inner), "))");
}
    return base;
}
    if (expr.kind == ExprKind_ek_array) {
    ArrayList_Str elems = ArrayList_Str_init(self->allocator);
    int64_t i = 0LL;
    while (i < ArrayList_Int_length(&(expr.arr_elements))) {
    ArrayList_Str_push(&(elems), Codegen_gen_expr(self, ArrayList_Int_get(&(expr.arr_elements), i)));
    i = (i + 1LL);
}
    const char* elems_str = str_array_join(elems, ", ");
    if (strlen(elems_str) == 0LL) {
    elems_str = "0";
}
    const char* inner_ty = "Int";
    if ((strlen(expr.inferred_type) > 2LL) && (strcmp(__kai_str_sub(expr.inferred_type, 0LL, 2LL), "[]") == 0)) {
    inner_ty = __kai_str_sub(expr.inferred_type, 2LL, strlen(expr.inferred_type));
}
    const char* mapped_inner = Codegen_map_type(self, inner_ty);
    return concatAlloc(concatAlloc(concatAlloc(concatAlloc("(", mapped_inner), "[]){ "), elems_str), " }");
}
    if (expr.kind == ExprKind_ek_tuple) {
    if (strlen(expr.inferred_type) > 0LL) {
    const char* mapped_ty = Codegen_map_type(self, expr.inferred_type);
    ArrayList_Str elems = ArrayList_Str_init(self->allocator);
    int64_t i = 0LL;
    while (i < ArrayList_Int_length(&(expr.tup_elements))) {
    ArrayList_Str_push(&(elems), Codegen_gen_expr(self, ArrayList_Int_get(&(expr.tup_elements), i)));
    i = (i + 1LL);
}
    return concatAlloc(concatAlloc(concatAlloc(concatAlloc("(", mapped_ty), "){ "), str_array_join(elems, ", ")), " }");
}
    return "NULL";
}
    if (expr.kind == ExprKind_ek_asm) {
    ArrayList_Str decls = ArrayList_Str_init(self->allocator);
    ArrayList_Str out_ops = ArrayList_Str_init(self->allocator);
    int64_t i = 0LL;
    while (i < ArrayList_AsmOutput_length(&(expr.asm_outputs))) {
    AsmOutput out = ArrayList_AsmOutput_get(&(expr.asm_outputs), i);
    if (strlen(out.type_name) > 0LL) {
    const char* mapped_type = Codegen_map_type(self, out.type_name);
    const char* var_name = concatAlloc("asm_ret_", int_to_str(i));
    ArrayList_Str_push(&(decls), concatAlloc(concatAlloc(concatAlloc(mapped_type, " "), var_name), ";"));
    ArrayList_Str_push(&(out_ops), concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc("[", out.name), "] \""), out.constraint), "\" ("), var_name), ")"));
} else if (out.expr_idx >= 0LL) {
    const char* val_str = Codegen_gen_expr(self, out.expr_idx);
    ArrayList_Str_push(&(out_ops), concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc("[", out.name), "] \""), out.constraint), "\" ("), val_str), ")"));
}
    i = (i + 1LL);
}
    ArrayList_Str in_ops = ArrayList_Str_init(self->allocator);
    int64_t j = 0LL;
    while (j < ArrayList_AsmInput_length(&(expr.asm_inputs))) {
    AsmInput inp = ArrayList_AsmInput_get(&(expr.asm_inputs), j);
    const char* val_str = Codegen_gen_expr(self, inp.expr_idx);
    ArrayList_Str_push(&(in_ops), concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc("[", inp.name), "] \""), inp.constraint), "\" ("), val_str), ")"));
    j = (j + 1LL);
}
    ArrayList_Str clobs = ArrayList_Str_init(self->allocator);
    int64_t k = 0LL;
    while (k < ArrayList_Str_length(&(expr.asm_clobbers))) {
    ArrayList_Str_push(&(clobs), concatAlloc(concatAlloc("\"", ArrayList_Str_get(&(expr.asm_clobbers), k)), "\""));
    k = (k + 1LL);
}
    const char* volatile_prefix = "";
    if (expr.asm_is_volatile) {
    volatile_prefix = "volatile";
}
    const char* escaped_asm = "";
    int64_t c_idx = 0LL;
    while (c_idx < strlen(expr.asm_code)) {
    char c = (expr.asm_code)[c_idx];
    if (c == ((char)(10LL))) {
    escaped_asm = concatAlloc(escaped_asm, "\\n\\t");
} else if (c == ((char)(34LL))) {
    escaped_asm = concatAlloc(escaped_asm, "\\\"");
} else {
    escaped_asm = concatAlloc(escaped_asm, char_to_str(c));
}
    c_idx = (c_idx + 1LL);
}
    const char* asm_stmt = concatAlloc(concatAlloc(concatAlloc(concatAlloc("__asm__ ", volatile_prefix), " (\""), escaped_asm), "\"");
    if (((ArrayList_Str_length(&(out_ops)) > 0LL) || (ArrayList_Str_length(&(in_ops)) > 0LL)) || (ArrayList_Str_length(&(clobs)) > 0LL)) {
    asm_stmt = concatAlloc(concatAlloc(asm_stmt, " : "), str_array_join(out_ops, ", "));
}
    if ((ArrayList_Str_length(&(in_ops)) > 0LL) || (ArrayList_Str_length(&(clobs)) > 0LL)) {
    asm_stmt = concatAlloc(concatAlloc(asm_stmt, " : "), str_array_join(in_ops, ", "));
}
    if (ArrayList_Str_length(&(clobs)) > 0LL) {
    asm_stmt = concatAlloc(concatAlloc(asm_stmt, " : "), str_array_join(clobs, ", "));
}
    asm_stmt = concatAlloc(asm_stmt, ");");
    const char* res = "({\n";
    int64_t d_idx = 0LL;
    while (d_idx < ArrayList_Str_length(&(decls))) {
    res = concatAlloc(concatAlloc(concatAlloc(res, "    "), ArrayList_Str_get(&(decls), d_idx)), "\n");
    d_idx = (d_idx + 1LL);
}
    res = concatAlloc(concatAlloc(concatAlloc(res, "    "), asm_stmt), "\n");
    if (ArrayList_AsmOutput_length(&(expr.asm_outputs)) == 1LL) {
    AsmOutput out0 = ArrayList_AsmOutput_get(&(expr.asm_outputs), 0LL);
    if (strlen(out0.type_name) > 0LL) {
    res = concatAlloc(res, "    asm_ret_0;\n");
}
} else if (ArrayList_AsmOutput_length(&(expr.asm_outputs)) > 1LL) {
    ArrayList_Str types = ArrayList_Str_init(self->allocator);
    int64_t ti = 0LL;
    bool all_typed = true;
    while (ti < ArrayList_AsmOutput_length(&(expr.asm_outputs))) {
    AsmOutput out = ArrayList_AsmOutput_get(&(expr.asm_outputs), ti);
    if (strlen(out.type_name) == 0LL) {
    all_typed = false;
}
    ArrayList_Str_push(&(types), out.type_name);
    ti = (ti + 1LL);
}
    if (all_typed) {
    const char* tuple_type = concatAlloc(concatAlloc("(", str_array_join(types, ", ")), ")");
    const char* mapped_tuple = Codegen_map_type(self, tuple_type);
    ArrayList_Str vals = ArrayList_Str_init(self->allocator);
    int64_t vi = 0LL;
    while (vi < ArrayList_AsmOutput_length(&(expr.asm_outputs))) {
    ArrayList_Str_push(&(vals), concatAlloc("asm_ret_", int_to_str(vi)));
    vi = (vi + 1LL);
}
    res = concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(res, "    ("), mapped_tuple), "){ "), str_array_join(vals, ", ")), " };\n");
}
}
    res = concatAlloc(res, "})");
    return res;
}
    if (expr.kind == ExprKind_ek_struct_init) {
    bool is_enum = ((strlen(expr.struct_name) > 0LL) && Codegen_str_contains(self, expr.struct_name, ((char)(46LL))));
    if (is_enum) {
    int64_t dot_pos = Codegen_str_find(self, expr.struct_name, ((char)(46LL)));
    const char* enum_part = __kai_str_sub(expr.struct_name, 0LL, dot_pos);
    const char* variant_name = __kai_str_sub(expr.struct_name, (dot_pos + 1LL), strlen(expr.struct_name));
    const char* enum_name = Codegen_map_type(self, enum_part);
    const char* fields_str = "";
    int64_t i = 0LL;
    while (i < ArrayList_FieldInit_length(&(expr.struct_fields))) {
    FieldInit f = ArrayList_FieldInit_get(&(expr.struct_fields), i);
    if (i > 0LL) {
    fields_str = concatAlloc(fields_str, ", ");
}
    fields_str = concatAlloc(concatAlloc(concatAlloc(concatAlloc(fields_str, "."), f.name), " = "), Codegen_gen_expr(self, f.value));
    i = (i + 1LL);
}
    const char* payload_str = "";
    if (strlen(fields_str) > 0LL) {
    payload_str = concatAlloc(concatAlloc(concatAlloc(concatAlloc(", .payload = { .", variant_name), " = { "), fields_str), " } }");
}
    return concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc("(", enum_name), "){ .tag = "), enum_name), "_"), variant_name), "_TAG"), payload_str), " }");
} else {
    const char* struct_name = Codegen_map_type(self, expr.struct_name);
    const char* fields_str = "";
    int64_t i = 0LL;
    while (i < ArrayList_FieldInit_length(&(expr.struct_fields))) {
    FieldInit f = ArrayList_FieldInit_get(&(expr.struct_fields), i);
    if (i > 0LL) {
    fields_str = concatAlloc(fields_str, ", ");
}
    const char* field_type = "";
    int64_t si = 0LL;
    while (si < ArrayList_StmtNode_length(self->stmt_pool)) {
    StmtNode s = ArrayList_StmtNode_get(self->stmt_pool, si);
    if ((s.kind == StmtKind_sk_struct_decl) && (strcmp(s.struct_name, expr.struct_name) == 0)) {
    int64_t fi = 0LL;
    while (fi < ArrayList_StructField_length(&(s.struct_fields))) {
    StructField sf = ArrayList_StructField_get(&(s.struct_fields), fi);
    if (strcmp(sf.name, f.name) == 0) {
    field_type = sf.ftype;
}
    fi = (fi + 1LL);
}
}
    si = (si + 1LL);
}
    fields_str = concatAlloc(concatAlloc(concatAlloc(concatAlloc(fields_str, "."), f.name), " = "), Codegen_gen_expr_with_expected_type(self, f.value, field_type));
    i = (i + 1LL);
}
    return concatAlloc(concatAlloc(concatAlloc(concatAlloc("(", struct_name), "){ "), fields_str), " }");
}
}
    if (expr.kind == ExprKind_ek_method_call) {
    int64_t receiver_idx = expr.meth_expr;
    ExprNode receiver_node = ArrayList_ExprNode_get(self->expr_pool, receiver_idx);
    const char* method_name = expr.meth_name;
    const char* rec_type = Codegen_get_expr_type(self, expr.meth_expr);
    const char* clean_type = "";
    int64_t i = 0LL;
    while (i < strlen(rec_type)) {
    char c = (rec_type)[i];
    if ((c != ((char)(42LL))) && (c != ((char)(38LL)))) {
    clean_type = concatAlloc(clean_type, char_to_str(c));
}
    i = (i + 1LL);
}
    if (strcmp(__kai_str_sub(clean_type, 0LL, 4LL), "mut ") == 0) {
    clean_type = __kai_str_sub(clean_type, 4LL, strlen(clean_type));
}
    clean_type = Codegen_map_type(self, clean_type);
    bool is_constructor = false;
    if (receiver_node.kind == ExprKind_ek_identifier) {
    const char* r_name = receiver_node.ident_name;
    char first_char = (r_name)[0LL];
    if ((first_char >= ((char)(65LL))) && (first_char <= ((char)(90LL)))) {
    is_constructor = true;
    clean_type = Codegen_map_type(self, rec_type);
}
}
    const char* func_name = concatAlloc(concatAlloc(clean_type, "_"), method_name);
    if (type_map_find(&(self->func_types), func_name) < 0LL) {
    printf("error[E0023]: type '%s' has no method '%s' (looked up: '%s')\n", rec_type, method_name, func_name);
    int64_t d_i = 0LL;
    while (d_i < ArrayList_StrMapEntry_length(&(self->func_types))) {
    printf("  registered: %s\n", ArrayList_StrMapEntry_get(&(self->func_types), d_i).key);
    d_i = (d_i + 1LL);
}
    {
    exit(1LL);
}
}
    const char* args_str = "";
    if ((!is_constructor) && (strcmp(method_name, "init") != 0)) {
    const char* rec_val = Codegen_gen_expr(self, receiver_idx);
    const char* rec_inferred = Codegen_get_expr_type(self, receiver_idx);
    bool is_self_ptr = (((receiver_node.kind == ExprKind_ek_identifier) && (strcmp(receiver_node.ident_name, "self") == 0)) && (!self->cur_method_is_init));
    if ((((rec_inferred)[0LL] == ((char)(42LL))) || ((rec_inferred)[0LL] == ((char)(38LL)))) || is_self_ptr) {
    args_str = rec_val;
} else {
    bool is_complex = ((receiver_node.kind == ExprKind_ek_func_call) || (receiver_node.kind == ExprKind_ek_method_call));
    if (is_complex) {
    const char* tmp_type = Codegen_map_type(self, rec_inferred);
    args_str = concatAlloc(concatAlloc(concatAlloc(concatAlloc("({ ", tmp_type), " __tmp_recv = "), rec_val), "; &__tmp_recv; })");
} else {
    args_str = concatAlloc(concatAlloc("&(", rec_val), ")");
}
}
}
    int64_t ai = 0LL;
    while (ai < ArrayList_Int_length(&(expr.meth_args))) {
    if (strlen(args_str) > 0LL) {
    args_str = concatAlloc(args_str, ", ");
}
    const char* p_key = concatAlloc(concatAlloc(func_name, "_param_"), int_to_str((ai + 1LL)));
    const char* expected_type = type_map_get(&(self->func_param_types), p_key);
    args_str = concatAlloc(args_str, Codegen_gen_expr_with_expected_type(self, ArrayList_Int_get(&(expr.meth_args), ai), expected_type));
    ai = (ai + 1LL);
}
    if ((strcmp(method_name, "init") == 0) && (!is_constructor)) {
    const char* rec_val = Codegen_gen_expr(self, receiver_idx);
    const char* rec_inferred = Codegen_get_expr_type(self, receiver_idx);
    if (((rec_inferred)[0LL] == ((char)(42LL))) || ((rec_inferred)[0LL] == ((char)(38LL)))) {
    return concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc("*(", rec_val), ") = "), func_name), "("), args_str), ")");
}
    return concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(rec_val, " = "), func_name), "("), args_str), ")");
}
    return concatAlloc(concatAlloc(concatAlloc(func_name, "("), args_str), ")");
}
    if (expr.kind == ExprKind_ek_catch) {
    const char* inner = Codegen_gen_expr(self, expr.catch_expr);
    const char* inner_ty = Codegen_get_expr_type(self, expr.catch_expr);
    if ((strlen(inner_ty) > 0LL) && ((inner_ty)[0LL] == ((char)(63LL)))) {
    const char* val_type = __kai_str_sub(inner_ty, 1LL, strlen(inner_ty));
    const char* val_ctype = Codegen_map_type(self, val_type);
    const char* cond_ctype = Codegen_map_type(self, inner_ty);
    const char* fallback_code = "";
    bool fallback_is_stmt2 = false;
    if (expr.catch_fallback >= 0LL) {
    StmtNode fb_node = ArrayList_StmtNode_get(self->stmt_pool, expr.catch_fallback);
    if (fb_node.kind == StmtKind_sk_expr) {
    fallback_code = Codegen_gen_expr(self, fb_node.expr_stmt);
} else if (fb_node.kind == StmtKind_sk_block) {
    bool is_single_expr = false;
    int64_t expr_idx = (-1LL);
    if (ArrayList_Int_length(&(fb_node.block_stmts)) == 1LL) {
    StmtNode single_stmt = ArrayList_StmtNode_get(self->stmt_pool, ArrayList_Int_get(&(fb_node.block_stmts), 0LL));
    if (single_stmt.kind == StmtKind_sk_expr) {
    is_single_expr = true;
    expr_idx = single_stmt.expr_stmt;
}
}
    if (is_single_expr) {
    fallback_code = Codegen_gen_expr(self, expr_idx);
} else {
    fallback_code = Codegen_gen_stmt(self, expr.catch_fallback);
    fallback_is_stmt2 = true;
}
} else {
    fallback_code = Codegen_gen_stmt(self, expr.catch_fallback);
    fallback_is_stmt2 = true;
}
} else {
    fallback_code = "0";
}
    const char* catch_code = "({ ";
    if (Codegen_is_pointer_type(self, val_type)) {
    catch_code = concatAlloc(concatAlloc(concatAlloc(concatAlloc(catch_code, val_ctype), " _kai_opt = ("), inner), "); ");
    catch_code = concatAlloc(concatAlloc(catch_code, val_ctype), " _kai_cv; ");
    catch_code = concatAlloc(catch_code, "if (_kai_opt != NULL) { _kai_cv = _kai_opt; } ");
    if (fallback_is_stmt2) {
    catch_code = concatAlloc(concatAlloc(concatAlloc(catch_code, "else { "), fallback_code), " __builtin_unreachable(); } _kai_cv; })");
} else {
    catch_code = concatAlloc(concatAlloc(concatAlloc(catch_code, "else { _kai_cv = ("), fallback_code), "); } _kai_cv; })");
}
} else {
    catch_code = concatAlloc(concatAlloc(concatAlloc(concatAlloc(catch_code, cond_ctype), " _kai_opt = ("), inner), "); ");
    catch_code = concatAlloc(concatAlloc(catch_code, val_ctype), " _kai_cv; ");
    catch_code = concatAlloc(catch_code, "if (_kai_opt.has_value) { _kai_cv = _kai_opt.value; } ");
    if (fallback_is_stmt2) {
    catch_code = concatAlloc(concatAlloc(concatAlloc(catch_code, "else { "), fallback_code), " __builtin_unreachable(); } _kai_cv; })");
} else {
    catch_code = concatAlloc(concatAlloc(concatAlloc(catch_code, "else { _kai_cv = ("), fallback_code), "); } _kai_cv; })");
}
}
    return catch_code;
}
    int64_t excl_pos = Codegen_str_find(self, inner_ty, ((char)(33LL)));
    if (excl_pos < 0LL) {
    return inner;
}
    const char* val_type = __kai_str_sub(inner_ty, 0LL, excl_pos);
    const char* result_ctype = Codegen_map_type(self, inner_ty);
    const char* val_ctype = Codegen_map_type(self, val_type);
    const char* fallback_code = "";
    bool fallback_is_stmt = false;
    if (expr.catch_fallback >= 0LL) {
    StmtNode fb_node = ArrayList_StmtNode_get(self->stmt_pool, expr.catch_fallback);
    if (fb_node.kind == StmtKind_sk_expr) {
    fallback_code = Codegen_gen_expr(self, fb_node.expr_stmt);
} else if (fb_node.kind == StmtKind_sk_block) {
    bool is_single_expr = false;
    int64_t expr_idx = (-1LL);
    if (ArrayList_Int_length(&(fb_node.block_stmts)) == 1LL) {
    StmtNode single_stmt = ArrayList_StmtNode_get(self->stmt_pool, ArrayList_Int_get(&(fb_node.block_stmts), 0LL));
    if (single_stmt.kind == StmtKind_sk_expr) {
    is_single_expr = true;
    expr_idx = single_stmt.expr_stmt;
}
}
    if (is_single_expr) {
    fallback_code = Codegen_gen_expr(self, expr_idx);
} else {
    fallback_code = Codegen_gen_stmt(self, expr.catch_fallback);
    fallback_is_stmt = true;
}
} else {
    fallback_code = Codegen_gen_stmt(self, expr.catch_fallback);
    fallback_is_stmt = true;
}
} else {
    fallback_code = "0";
}
    const char* catch_code = concatAlloc(concatAlloc(concatAlloc(concatAlloc("({ ", result_ctype), " _kai_cr = ("), inner), "); ");
    if (strcmp(val_type, "Void") == 0) {
    catch_code = concatAlloc(catch_code, "if (_kai_cr.tag != 0) { ");
    if (strlen(expr.catch_var) > 0LL) {
    catch_code = concatAlloc(concatAlloc(concatAlloc(catch_code, "int64_t "), expr.catch_var), " = _kai_cr.tag; ");
}
    catch_code = concatAlloc(concatAlloc(catch_code, fallback_code), " } 0; })");
} else {
    catch_code = concatAlloc(concatAlloc(catch_code, val_ctype), " _kai_cv; ");
    catch_code = concatAlloc(catch_code, "if (_kai_cr.tag != 0) { ");
    if (strlen(expr.catch_var) > 0LL) {
    catch_code = concatAlloc(concatAlloc(concatAlloc(catch_code, "int64_t "), expr.catch_var), " = _kai_cr.tag; ");
}
    if (fallback_is_stmt) {
    catch_code = concatAlloc(concatAlloc(catch_code, fallback_code), " __builtin_unreachable(); ");
} else {
    catch_code = concatAlloc(concatAlloc(concatAlloc(catch_code, "_kai_cv = ("), fallback_code), "); ");
}
    catch_code = concatAlloc(catch_code, "} else { _kai_cv = _kai_cr.value; } _kai_cv; })");
}
    return catch_code;
}
    return "0";
}
bool Codegen_str_contains(Codegen* self, const char* s, char target) {
    int64_t i = 0LL;
    while (i < strlen(s)) {
    if ((s)[i] == target) {
    return true;
}
    i = (i + 1LL);
}
    return false;
}
int64_t Codegen_str_find(Codegen* self, const char* s, char target) {
    int64_t i = 0LL;
    while (i < strlen(s)) {
    if ((s)[i] == target) {
    return i;
}
    i = (i + 1LL);
}
    return (-1LL);
}
bool Codegen_is_standard_c_func(Codegen* self, const char* name) {
    int64_t l = strlen(name);
    if (l >= 4LL) {
    const char* sub4 = __kai_str_sub(name, 0LL, 4LL);
    bool is_llvm = false;
    {
    if (strcmp(sub4, "LLVM") == 0LL) {
    is_llvm = true;
}
}
    if (is_llvm) {
    return true;
}
}
    if (l >= 8LL) {
    const char* sub8 = __kai_str_sub(name, 0LL, 8LL);
    bool is_kai_llvm = false;
    {
    if (strcmp(sub8, "kai_LLVM") == 0LL) {
    is_kai_llvm = true;
}
}
    if (is_kai_llvm) {
    return true;
}
}
    if (l >= 13LL) {
    const char* sub13 = __kai_str_sub(name, 0LL, 13LL);
    bool is_kai_func = false;
    {
    if (strcmp(sub13, "kai_func_type") == 0LL) {
    is_kai_func = true;
}
}
    if (is_kai_func) {
    return true;
}
}
    if (l >= 14LL) {
    const char* sub14 = __kai_str_sub(name, 0LL, 14LL);
    bool is_kai_build = false;
    {
    if (strcmp(sub14, "kai_build_call") == 0LL) {
    is_kai_build = true;
}
}
    if (is_kai_build) {
    return true;
}
}
    if (strcmp(name, "atoll") == 0) {
    return true;
}
    if (strcmp(name, "malloc") == 0) {
    return true;
}
    if (strcmp(name, "free") == 0) {
    return true;
}
    if (strcmp(name, "realloc") == 0) {
    return true;
}
    if (strcmp(name, "calloc") == 0) {
    return true;
}
    if (strcmp(name, "isdigit") == 0) {
    return true;
}
    if (strcmp(name, "isalpha") == 0) {
    return true;
}
    if (strcmp(name, "isalnum") == 0) {
    return true;
}
    if (strcmp(name, "isspace") == 0) {
    return true;
}
    if (strcmp(name, "toupper") == 0) {
    return true;
}
    if (strcmp(name, "tolower") == 0) {
    return true;
}
    if (strcmp(name, "strlen") == 0) {
    return true;
}
    if (strcmp(name, "exit") == 0) {
    return true;
}
    if (strcmp(name, "system") == 0) {
    return true;
}
    if (strcmp(name, "fopen") == 0) {
    return true;
}
    if (strcmp(name, "fread") == 0) {
    return true;
}
    if (strcmp(name, "fwrite") == 0) {
    return true;
}
    if (strcmp(name, "fclose") == 0) {
    return true;
}
    if (strcmp(name, "fseek") == 0) {
    return true;
}
    if (strcmp(name, "ftell") == 0) {
    return true;
}
    if (strcmp(name, "rewind") == 0) {
    return true;
}
    if (strcmp(name, "strcmp") == 0) {
    return true;
}
    if (strcmp(name, "printf") == 0) {
    return true;
}
    if (strcmp(name, "fprintf") == 0) {
    return true;
}
    if (strcmp(name, "sprintf") == 0) {
    return true;
}
    if (strcmp(name, "snprintf") == 0) {
    return true;
}
    if (strcmp(name, "sqrt") == 0) {
    return true;
}
    return false;
}
const char* Codegen_gen_stmt(Codegen* self, int64_t stmt_idx) {
    if (stmt_idx < 0LL) {
    return "";
}
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, stmt_idx);
    if (stmt.kind == StmtKind_sk_block) {
    ArrayList_Int_push(&(self->block_stack), stmt_idx);
    ArrayList_Int_push(&(self->defer_depths), ArrayList_Int_length(&(self->defer_stack)));
    const char* block_str = "{\n";
    int64_t i = 0LL;
    while (i < ArrayList_Int_length(&(stmt.block_stmts))) {
    const char* s = Codegen_gen_stmt(self, ArrayList_Int_get(&(stmt.block_stmts), i));
    if (strlen(s) > 0LL) {
    block_str = concatAlloc(concatAlloc(concatAlloc(block_str, "    "), s), "\n");
}
    i = (i + 1LL);
}
    int64_t start_idx = ArrayList_Int_pop(&(self->defer_depths));
    while (ArrayList_Int_length(&(self->defer_stack)) > start_idx) {
    int64_t def_idx = ArrayList_Int_pop(&(self->defer_stack));
    StmtNode def_node = ArrayList_StmtNode_get(self->stmt_pool, def_idx);
    const char* s = Codegen_gen_stmt(self, def_node.defer_body);
    if (strlen(s) > 0LL) {
    block_str = concatAlloc(concatAlloc(concatAlloc(block_str, "    "), s), "\n");
}
}
    int64_t di = 0LL;
    while (di < ArrayList_DropVarEntry_length(&(stmt.block_drop_vars))) {
    DropVarEntry entry = ArrayList_DropVarEntry_get(&(stmt.block_drop_vars), di);
    block_str = concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(block_str, "    "), entry.base_type), "_drop(&"), entry.name), ");\n");
    di = (di + 1LL);
}
    block_str = concatAlloc(block_str, "}");
    (void)(ArrayList_Int_pop(&(self->block_stack)));
    return block_str;
}
    if (stmt.kind == StmtKind_sk_defer) {
    ArrayList_Int_push(&(self->defer_stack), stmt_idx);
    return "";
}
    if (stmt.kind == StmtKind_sk_var_decl) {
    const char* name = stmt.vardecl_name;
    const char* var_type_name = stmt.vardecl_type;
    if (strlen(var_type_name) == 0LL) {
    var_type_name = Codegen_get_expr_type(self, stmt.vardecl_value);
}
    const char* init_val = Codegen_gen_expr_with_expected_type(self, stmt.vardecl_value, var_type_name);
    if (strcmp(name, "_") == 0) {
    return concatAlloc(concatAlloc("(void)(", init_val), ");");
}
    const char* var_type = Codegen_map_type(self, var_type_name);
    type_map_put(&(self->var_types), name, var_type_name);
    return concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(var_type, " "), name), " = "), init_val), ";");
}
    if (stmt.kind == StmtKind_sk_assignment) {
    const char* lhs = Codegen_gen_expr(self, stmt.assign_target);
    const char* lhs_type = Codegen_get_expr_type(self, stmt.assign_target);
    const char* rhs = Codegen_gen_expr_with_expected_type(self, stmt.assign_value, lhs_type);
    const char* op = "=";
    if (strlen(stmt.assign_op) > 0LL) {
    op = stmt.assign_op;
}
    return concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(lhs, " "), op), " "), rhs), ";");
}
    if (stmt.kind == StmtKind_sk_func_decl) {
    if (ArrayList_Str_length(&(stmt.func_type_params)) > 0LL) {
    type_map_put(&(self->generic_func_decls), stmt.func_name, int_to_str(stmt_idx));
    return "";
}
    const char* name = stmt.func_name;
    const char* ret_type = Codegen_map_type(self, stmt.func_return_type);
    const char* params_str = "";
    int64_t i = 0LL;
    while (i < ArrayList_Param_length(&(stmt.func_params))) {
    Param p = ArrayList_Param_get(&(stmt.func_params), i);
    if (i > 0LL) {
    params_str = concatAlloc(params_str, ", ");
}
    params_str = concatAlloc(concatAlloc(concatAlloc(params_str, Codegen_map_type(self, p.ptype)), " "), p.name);
    i = (i + 1LL);
}
    if (strlen(params_str) == 0LL) {
    params_str = "void";
}
    const char* old_fn = self->cur_func_name;
    const char* old_ret = self->cur_return_type;
    bool old_init = self->cur_method_is_init;
    self->cur_func_name = name;
    self->cur_return_type = stmt.func_return_type;
    self->cur_method_is_init = false;
    int64_t old_var_len2 = ArrayList_StrMapEntry_length(&(self->var_types));
    int64_t p_reg2 = 0LL;
    while (p_reg2 < ArrayList_Param_length(&(stmt.func_params))) {
    Param p = ArrayList_Param_get(&(stmt.func_params), p_reg2);
    type_map_put(&(self->var_types), p.name, p.ptype);
    p_reg2 = (p_reg2 + 1LL);
}
    if (stmt.func_body < 0LL) {
    self->cur_func_name = old_fn;
    self->cur_return_type = old_ret;
    self->cur_method_is_init = old_init;
    return "";
}
    const char* body_str = Codegen_gen_stmt(self, stmt.func_body);
    while (ArrayList_StrMapEntry_length(&(self->var_types)) > old_var_len2) {
    (void)(ArrayList_StrMapEntry_pop(&(self->var_types)));
}
    const char* proto = "";
    const char* impl_str = "";
    if (strcmp(name, "main") == 0) {
    impl_str = concatAlloc("int main(int argc, char** argv) ", body_str);
} else {
    proto = concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(ret_type, " "), name), "("), params_str), ");\n");
    impl_str = concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(ret_type, " "), name), "("), params_str), ") "), body_str), "\n");
}
    if (strlen(proto) > 0LL) {
    (void)(StringBuilder_append(&(self->func_decls), proto));
}
    (void)(StringBuilder_append(&(self->output), impl_str));
    self->cur_func_name = old_fn;
    self->cur_return_type = old_ret;
    self->cur_method_is_init = old_init;
    return "";
}
    if (stmt.kind == StmtKind_sk_struct_decl) {
    if (ArrayList_Str_length(&(stmt.struct_type_params)) > 0LL) {
    type_map_put(&(self->generic_struct_decls), stmt.struct_name, int_to_str(stmt_idx));
}
    return "";
}
    if (stmt.kind == StmtKind_sk_trait_decl) {
    const char* method_names = "";
    int64_t mi = 0LL;
    while (mi < ArrayList_Int_length(&(stmt.trait_methods))) {
    StmtNode m_node = ArrayList_StmtNode_get(self->stmt_pool, ArrayList_Int_get(&(stmt.trait_methods), mi));
    if (mi > 0LL) {
    method_names = concatAlloc(method_names, ", ");
}
    method_names = concatAlloc(method_names, m_node.func_name);
    mi = (mi + 1LL);
}
    const char* comment = concatAlloc(concatAlloc(concatAlloc(concatAlloc("/* trait ", stmt.trait_name), ": "), method_names), " */\n");
    (void)(StringBuilder_append(&(self->struct_decls), comment));
    return "";
}
    if (stmt.kind == StmtKind_sk_error_decl) {
    type_map_put(&(self->enum_decls), stmt.error_name, int_to_str(stmt_idx));
    const char* name = Codegen_map_type(self, stmt.error_name);
    const char* enum_str = "typedef enum {\n";
    int64_t j = 0LL;
    while (j < ArrayList_Str_length(&(stmt.error_variants))) {
    const char* vname = ArrayList_Str_get(&(stmt.error_variants), j);
    enum_str = concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(enum_str, "    "), name), "_"), vname), " = "), int_to_str((j + 1LL))), ",\n");
    j = (j + 1LL);
}
    enum_str = concatAlloc(concatAlloc(concatAlloc(enum_str, "} "), name), ";\n");
    (void)(StringBuilder_append(&(self->struct_decls), enum_str));
    return "";
}
    if (stmt.kind == StmtKind_sk_enum_decl) {
    type_map_put(&(self->enum_decls), stmt.enum_name, int_to_str(stmt_idx));
    if (ArrayList_Str_length(&(stmt.enum_type_params)) > 0LL) {
    type_map_put(&(self->generic_enum_decls), stmt.enum_name, int_to_str(stmt_idx));
    return "";
}
    const char* name = Codegen_map_type(self, stmt.enum_name);
    bool has_payload = false;
    int64_t i = 0LL;
    while (i < ArrayList_Variant_length(&(stmt.enum_variants))) {
    Variant v = ArrayList_Variant_get(&(stmt.enum_variants), i);
    if (ArrayList_Param_length(&(v.params)) > 0LL) {
    has_payload = true;
}
    i = (i + 1LL);
}
    const char* enum_str = "";
    if (!has_payload) {
    enum_str = "typedef enum {\n";
    int64_t j = 0LL;
    while (j < ArrayList_Variant_length(&(stmt.enum_variants))) {
    Variant v = ArrayList_Variant_get(&(stmt.enum_variants), j);
    enum_str = concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(enum_str, "    "), name), "_"), v.vname), ",\n");
    j = (j + 1LL);
}
    enum_str = concatAlloc(concatAlloc(concatAlloc(enum_str, "} "), name), ";\n");
} else {
    const char* tags_name = concatAlloc(name, "_tags");
    enum_str = "typedef enum {\n";
    int64_t j = 0LL;
    while (j < ArrayList_Variant_length(&(stmt.enum_variants))) {
    Variant v = ArrayList_Variant_get(&(stmt.enum_variants), j);
    enum_str = concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(enum_str, "    "), name), "_"), v.vname), "_TAG,\n");
    j = (j + 1LL);
}
    enum_str = concatAlloc(concatAlloc(concatAlloc(enum_str, "} "), tags_name), ";\n");
    enum_str = concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(enum_str, "typedef struct "), name), " "), name), ";\n");
    enum_str = concatAlloc(concatAlloc(concatAlloc(enum_str, "struct "), name), " {\n");
    enum_str = concatAlloc(enum_str, "    uint8_t tag;\n");
    enum_str = concatAlloc(enum_str, "    union {\n");
    int64_t k = 0LL;
    while (k < ArrayList_Variant_length(&(stmt.enum_variants))) {
    Variant v = ArrayList_Variant_get(&(stmt.enum_variants), k);
    if (ArrayList_Param_length(&(v.params)) > 0LL) {
    enum_str = concatAlloc(enum_str, "        struct {\n");
    int64_t p_idx = 0LL;
    while (p_idx < ArrayList_Param_length(&(v.params))) {
    Param p = ArrayList_Param_get(&(v.params), p_idx);
    enum_str = concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(enum_str, "            "), Codegen_map_type(self, p.ptype)), " "), p.name), ";\n");
    p_idx = (p_idx + 1LL);
}
    enum_str = concatAlloc(concatAlloc(concatAlloc(enum_str, "        } "), v.vname), ";\n");
}
    k = (k + 1LL);
}
    enum_str = concatAlloc(enum_str, "    } payload;\n");
    enum_str = concatAlloc(enum_str, "};\n");
}
    (void)(StringBuilder_append(&(self->struct_decls), enum_str));
    return "";
}
    if (stmt.kind == StmtKind_sk_impl_block) {
    const char* struct_name = stmt.impl_struct_name;
    bool has_generic_struct = ((strlen(type_map_get(&(self->generic_struct_decls), struct_name)) > 0LL) || (strlen(type_map_get(&(self->generic_enum_decls), struct_name)) > 0LL));
    if (has_generic_struct || Codegen_str_contains(self, struct_name, ((char)(60LL)))) {
    type_map_put(&(self->generic_impl_blocks), struct_name, int_to_str(stmt_idx));
    return "";
}
    const char* mapped_struct_name = Codegen_map_type(self, struct_name);
    int64_t idx = 0LL;
    while (idx < ArrayList_Int_length(&(stmt.impl_methods))) {
    int64_t method_stmt_idx = ArrayList_Int_get(&(stmt.impl_methods), idx);
    StmtNode method_node = ArrayList_StmtNode_get(self->stmt_pool, method_stmt_idx);
    const char* method_name = method_node.func_name;
    bool is_init = ((((strcmp(method_name, "init") == 0) || (strcmp(method_node.func_return_type, struct_name) == 0)) || (strcmp(method_node.func_return_type, concatAlloc("*", struct_name)) == 0)) || (strcmp(method_node.func_return_type, concatAlloc("&", struct_name)) == 0));
    const char* ret_type = "";
    if (is_init) {
    ret_type = mapped_struct_name;
} else {
    ret_type = Codegen_map_type(self, method_node.func_return_type);
}
    const char* params_str = "";
    if (!is_init) {
    params_str = concatAlloc(mapped_struct_name, "* self");
}
    int64_t p_idx = 0LL;
    while (p_idx < ArrayList_Param_length(&(method_node.func_params))) {
    Param p = ArrayList_Param_get(&(method_node.func_params), p_idx);
    if (strcmp(p.name, "self") != 0) {
    if (strlen(params_str) > 0LL) {
    params_str = concatAlloc(params_str, ", ");
}
    params_str = concatAlloc(concatAlloc(concatAlloc(params_str, Codegen_map_type(self, p.ptype)), " "), p.name);
}
    p_idx = (p_idx + 1LL);
}
    if (strlen(params_str) == 0LL) {
    params_str = "void";
}
    const char* mangled_fn_name = concatAlloc(concatAlloc(mapped_struct_name, "_"), method_name);
    const char* old_fn = self->cur_func_name;
    const char* old_ret = self->cur_return_type;
    bool old_init = self->cur_method_is_init;
    self->cur_func_name = mangled_fn_name;
    if (is_init) {
    self->cur_return_type = struct_name;
} else {
    self->cur_return_type = method_node.func_return_type;
}
    self->cur_method_is_init = is_init;
    int64_t old_var_len = ArrayList_StrMapEntry_length(&(self->var_types));
    if (is_init) {
    type_map_put(&(self->var_types), "self", struct_name);
} else {
    type_map_put(&(self->var_types), "self", concatAlloc("*", struct_name));
}
    int64_t p_reg = 0LL;
    while (p_reg < ArrayList_Param_length(&(method_node.func_params))) {
    Param p = ArrayList_Param_get(&(method_node.func_params), p_reg);
    if (strcmp(p.name, "self") != 0) {
    type_map_put(&(self->var_types), p.name, p.ptype);
}
    p_reg = (p_reg + 1LL);
}
    const char* body_str = Codegen_gen_stmt(self, method_node.func_body);
    while (ArrayList_StrMapEntry_length(&(self->var_types)) > old_var_len) {
    (void)(ArrayList_StrMapEntry_pop(&(self->var_types)));
}
    if (is_init) {
    body_str = Codegen_add_init_return(self, body_str, mapped_struct_name);
}
    const char* proto = concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(ret_type, " "), mangled_fn_name), "("), params_str), ");\n");
    const char* impl_str = concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(ret_type, " "), mangled_fn_name), "("), params_str), ") "), body_str), "\n");
    (void)(StringBuilder_append(&(self->func_decls), proto));
    (void)(StringBuilder_append(&(self->output), impl_str));
    self->cur_func_name = old_fn;
    self->cur_return_type = old_ret;
    self->cur_method_is_init = old_init;
    idx = (idx + 1LL);
}
    return "";
}
    if (stmt.kind == StmtKind_sk_if) {
    const char* cond_val = Codegen_gen_expr(self, stmt.if_cond);
    const char* cond_str = "";
    if (((strlen(cond_val) > 1LL) && ((cond_val)[0LL] == ((char)(40LL)))) && ((cond_val)[(strlen(cond_val) - 1LL)] == ((char)(41LL)))) {
    cond_str = cond_val;
} else {
    cond_str = concatAlloc(concatAlloc("(", cond_val), ")");
}
    const char* if_str = concatAlloc(concatAlloc(concatAlloc("if ", cond_str), " "), Codegen_gen_stmt(self, stmt.if_then));
    if (stmt.if_else >= 0LL) {
    StmtNode else_node = ArrayList_StmtNode_get(self->stmt_pool, stmt.if_else);
    if ((else_node.kind == StmtKind_sk_block) && (ArrayList_Int_length(&(else_node.block_stmts)) == 1LL)) {
    int64_t single_stmt_idx = ArrayList_Int_get(&(else_node.block_stmts), 0LL);
    StmtNode single_stmt = ArrayList_StmtNode_get(self->stmt_pool, single_stmt_idx);
    if (single_stmt.kind == StmtKind_sk_if) {
    if_str = concatAlloc(concatAlloc(if_str, " else "), Codegen_gen_stmt(self, single_stmt_idx));
} else {
    if_str = concatAlloc(concatAlloc(if_str, " else "), Codegen_gen_stmt(self, stmt.if_else));
}
} else {
    if_str = concatAlloc(concatAlloc(if_str, " else "), Codegen_gen_stmt(self, stmt.if_else));
}
}
    return if_str;
}
    if (stmt.kind == StmtKind_sk_if_let) {
    const char* cond_val = Codegen_gen_expr(self, stmt.iflet_expr);
    const char* cond_type = Codegen_get_expr_type(self, stmt.iflet_expr);
    const char* unwrapped_type = __kai_str_sub(cond_type, 1LL, strlen(cond_type));
    const char* unwrapped_ctype = Codegen_map_type(self, unwrapped_type);
    const char* cond_ctype = Codegen_map_type(self, cond_type);
    int64_t old_var_len = ArrayList_StrMapEntry_length(&(self->var_types));
    type_map_put(&(self->var_types), stmt.iflet_var, unwrapped_type);
    const char* then_str = Codegen_gen_stmt(self, stmt.iflet_then);
    const char* else_str = "";
    if (stmt.iflet_else >= 0LL) {
    StmtNode else_node = ArrayList_StmtNode_get(self->stmt_pool, stmt.iflet_else);
    if ((else_node.kind == StmtKind_sk_block) && (ArrayList_Int_length(&(else_node.block_stmts)) == 1LL)) {
    int64_t single_stmt_idx = ArrayList_Int_get(&(else_node.block_stmts), 0LL);
    StmtNode single_stmt = ArrayList_StmtNode_get(self->stmt_pool, single_stmt_idx);
    if (single_stmt.kind == StmtKind_sk_if_let) {
    else_str = concatAlloc(" else ", Codegen_gen_stmt(self, single_stmt_idx));
} else {
    else_str = concatAlloc(" else ", Codegen_gen_stmt(self, stmt.iflet_else));
}
} else {
    else_str = concatAlloc(" else ", Codegen_gen_stmt(self, stmt.iflet_else));
}
}
    while (ArrayList_StrMapEntry_length(&(self->var_types)) > old_var_len) {
    (void)(ArrayList_StrMapEntry_pop(&(self->var_types)));
}
    const char* if_code = "";
    if (Codegen_is_pointer_type(self, unwrapped_type)) {
    if_code = concatAlloc(concatAlloc("if ((", cond_val), ") != NULL) {\n");
    if_code = concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(if_code, "    "), unwrapped_ctype), " "), stmt.iflet_var), " = "), cond_val), ";\n");
    if_code = concatAlloc(concatAlloc(concatAlloc(if_code, "    "), then_str), "\n");
    if_code = concatAlloc(concatAlloc(if_code, "}"), else_str);
} else {
    if_code = "{\n";
    if_code = concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(if_code, "    "), cond_ctype), " _kai_opt = "), cond_val), ";\n");
    if_code = concatAlloc(if_code, "    if (_kai_opt.has_value) {\n");
    if_code = concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(if_code, "        "), unwrapped_ctype), " "), stmt.iflet_var), " = _kai_opt.value;\n");
    if_code = concatAlloc(concatAlloc(concatAlloc(if_code, "        "), then_str), "\n");
    if_code = concatAlloc(concatAlloc(concatAlloc(if_code, "    }"), else_str), "\n");
    if_code = concatAlloc(if_code, "}");
}
    return if_code;
}
    if (stmt.kind == StmtKind_sk_while) {
    const char* cond_val = Codegen_gen_expr(self, stmt.while_cond);
    const char* cond_str = "";
    if (((strlen(cond_val) > 1LL) && ((cond_val)[0LL] == ((char)(40LL)))) && ((cond_val)[(strlen(cond_val) - 1LL)] == ((char)(41LL)))) {
    cond_str = cond_val;
} else {
    cond_str = concatAlloc(concatAlloc("(", cond_val), ")");
}
    if (stmt.while_body >= 0LL) {
    StmtNode body_stmt = ArrayList_StmtNode_get(self->stmt_pool, stmt.while_body);
    body_stmt.block_is_loop_body = true;
    ArrayList_StmtNode_set(self->stmt_pool, stmt.while_body, body_stmt);
}
    return concatAlloc(concatAlloc(concatAlloc("while ", cond_str), " "), Codegen_gen_stmt(self, stmt.while_body));
}
    if (stmt.kind == StmtKind_sk_for) {
    const char* iter_var = stmt.for_var;
    const char* start = Codegen_gen_expr(self, stmt.for_start);
    const char* end = Codegen_gen_expr(self, stmt.for_end);
    if (stmt.for_body >= 0LL) {
    StmtNode body_stmt = ArrayList_StmtNode_get(self->stmt_pool, stmt.for_body);
    body_stmt.block_is_loop_body = true;
    ArrayList_StmtNode_set(self->stmt_pool, stmt.for_body, body_stmt);
}
    const char* body = Codegen_gen_stmt(self, stmt.for_body);
    const char* cmp_asc = "<";
    const char* cmp_desc = ">";
    if (stmt.for_inclusive) {
    cmp_asc = "<=";
    cmp_desc = ">=";
}
    const char* for_str = concatAlloc(concatAlloc(concatAlloc(concatAlloc("for (int64_t ", iter_var), " = "), start), "; ");
    for_str = concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(for_str, "("), start), " <= "), end), ") ? ("), iter_var), " "), cmp_asc), " "), end), ") : ("), iter_var), " "), cmp_desc), " "), end), "); ");
    for_str = concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(for_str, "("), start), " <= "), end), ") ? ++"), iter_var), " : --"), iter_var), ") "), body);
    return for_str;
}
    if (stmt.kind == StmtKind_sk_return) {
    ArrayList_Str drop_calls = ArrayList_Str_init(self->allocator);
    int64_t bi = (ArrayList_Int_length(&(self->block_stack)) - 1LL);
    while (bi >= 0LL) {
    int64_t b_idx = ArrayList_Int_get(&(self->block_stack), bi);
    StmtNode b_node = ArrayList_StmtNode_get(self->stmt_pool, b_idx);
    int64_t start_idx = ArrayList_Int_get(&(self->defer_depths), bi);
    int64_t next_start_idx = ArrayList_Int_length(&(self->defer_stack));
    if (bi < (ArrayList_Int_length(&(self->block_stack)) - 1LL)) {
    next_start_idx = ArrayList_Int_get(&(self->defer_depths), (bi + 1LL));
}
    int64_t def_i = (next_start_idx - 1LL);
    while (def_i >= start_idx) {
    int64_t def_idx = ArrayList_Int_get(&(self->defer_stack), def_i);
    StmtNode def_node = ArrayList_StmtNode_get(self->stmt_pool, def_idx);
    const char* s = Codegen_gen_stmt(self, def_node.defer_body);
    if (strlen(s) > 0LL) {
    ArrayList_Str_push(&(drop_calls), s);
}
    def_i = (def_i - 1LL);
}
    int64_t di = 0LL;
    while (di < ArrayList_DropVarEntry_length(&(b_node.block_drop_vars))) {
    DropVarEntry entry = ArrayList_DropVarEntry_get(&(b_node.block_drop_vars), di);
    ArrayList_Str_push(&(drop_calls), concatAlloc(concatAlloc(concatAlloc(entry.base_type, "_drop(&"), entry.name), ");"));
    di = (di + 1LL);
}
    bi = (bi - 1LL);
}
    if (ArrayList_Str_length(&(drop_calls)) == 0LL) {
    if (stmt.return_value >= 0LL) {
    int64_t ret_excl_pos = Codegen_str_find(self, self->cur_return_type, ((char)(33LL)));
    if (ret_excl_pos >= 0LL) {
    const char* result_ctype = Codegen_map_type(self, self->cur_return_type);
    const char* val_payload_type = __kai_str_sub(self->cur_return_type, 0LL, ret_excl_pos);
    const char* err_type = __kai_str_sub(self->cur_return_type, (ret_excl_pos + 1LL), strlen(self->cur_return_type));
    ExprNode ret_node = ArrayList_ExprNode_get(self->expr_pool, stmt.return_value);
    bool is_error_variant = false;
    if (ret_node.kind == ExprKind_ek_field_access) {
    ExprNode base_node = ArrayList_ExprNode_get(self->expr_pool, ret_node.field_expr);
    if (base_node.kind == ExprKind_ek_identifier) {
    if (Codegen_is_enum_type(self, base_node.ident_name)) {
    is_error_variant = true;
}
}
}
    const char* val_str = Codegen_gen_expr(self, stmt.return_value);
    const char* expr_ty = Codegen_get_expr_type(self, stmt.return_value);
    int64_t expr_excl_pos = Codegen_str_find(self, expr_ty, ((char)(33LL)));
    if (expr_excl_pos >= 0LL) {
    return concatAlloc(concatAlloc("return ", val_str), ";");
}
    if (is_error_variant) {
    return concatAlloc(concatAlloc(concatAlloc(concatAlloc("return (", result_ctype), "){ .tag = "), val_str), " };");
}
    if (strcmp(val_payload_type, "Void") == 0) {
    return concatAlloc(concatAlloc("return (", result_ctype), "){ .tag = 0 };");
}
    return concatAlloc(concatAlloc(concatAlloc(concatAlloc("return (", result_ctype), "){ .tag = 0, .value = "), val_str), " };");
}
    return concatAlloc(concatAlloc("return ", Codegen_gen_expr_with_expected_type(self, stmt.return_value, self->cur_return_type)), ";");
}
    return "return;";
}
    if (stmt.return_value >= 0LL) {
    const char* val_str = Codegen_gen_expr_with_expected_type(self, stmt.return_value, self->cur_return_type);
    const char* val_type = Codegen_get_expr_type(self, stmt.return_value);
    if ((strcmp(val_type, "Void") == 0) || (strcmp(val_type, "NoneType") == 0)) {
    const char* res = concatAlloc(val_str, "; ");
    int64_t ci = 0LL;
    while (ci < ArrayList_Str_length(&(drop_calls))) {
    res = concatAlloc(concatAlloc(res, ArrayList_Str_get(&(drop_calls), ci)), " ");
    ci = (ci + 1LL);
}
    return concatAlloc(res, "return;");
}
    int64_t ret_excl_pos = Codegen_str_find(self, self->cur_return_type, ((char)(33LL)));
    const char* mapped_type = Codegen_map_type(self, self->cur_return_type);
    if (ret_excl_pos >= 0LL) {
    const char* val_payload_type = __kai_str_sub(self->cur_return_type, 0LL, ret_excl_pos);
    ExprNode ret_node = ArrayList_ExprNode_get(self->expr_pool, stmt.return_value);
    bool is_error_variant = false;
    if (ret_node.kind == ExprKind_ek_field_access) {
    ExprNode base_node = ArrayList_ExprNode_get(self->expr_pool, ret_node.field_expr);
    if (base_node.kind == ExprKind_ek_identifier) {
    if (Codegen_is_enum_type(self, base_node.ident_name)) {
    is_error_variant = true;
}
}
}
    const char* raw_val = Codegen_gen_expr(self, stmt.return_value);
    const char* expr_ty = Codegen_get_expr_type(self, stmt.return_value);
    int64_t expr_excl_pos = Codegen_str_find(self, expr_ty, ((char)(33LL)));
    const char* ret_expr = "";
    if (expr_excl_pos >= 0LL) {
    ret_expr = raw_val;
} else if (is_error_variant) {
    ret_expr = concatAlloc(concatAlloc(concatAlloc(concatAlloc("(", mapped_type), "){ .tag = "), raw_val), " }");
} else if (strcmp(val_payload_type, "Void") == 0) {
    ret_expr = concatAlloc(concatAlloc("(", mapped_type), "){ .tag = 0 }");
} else {
    ret_expr = concatAlloc(concatAlloc(concatAlloc(concatAlloc("(", mapped_type), "){ .tag = 0, .value = "), raw_val), " }");
}
    const char* res_str = "{\n";
    res_str = concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(res_str, "    "), mapped_type), " __ret_val = "), ret_expr), ";\n");
    int64_t ci = 0LL;
    while (ci < ArrayList_Str_length(&(drop_calls))) {
    res_str = concatAlloc(concatAlloc(concatAlloc(res_str, "    "), ArrayList_Str_get(&(drop_calls), ci)), "\n");
    ci = (ci + 1LL);
}
    res_str = concatAlloc(res_str, "    return __ret_val;\n");
    res_str = concatAlloc(res_str, "}");
    return res_str;
}
    const char* res_str = "{\n";
    res_str = concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(res_str, "    "), mapped_type), " __ret_val = "), val_str), ";\n");
    int64_t ci = 0LL;
    while (ci < ArrayList_Str_length(&(drop_calls))) {
    res_str = concatAlloc(concatAlloc(concatAlloc(res_str, "    "), ArrayList_Str_get(&(drop_calls), ci)), "\n");
    ci = (ci + 1LL);
}
    res_str = concatAlloc(res_str, "    return __ret_val;\n");
    res_str = concatAlloc(res_str, "}");
    return res_str;
} else {
    const char* res_str = "{\n";
    int64_t ci = 0LL;
    while (ci < ArrayList_Str_length(&(drop_calls))) {
    res_str = concatAlloc(concatAlloc(concatAlloc(res_str, "    "), ArrayList_Str_get(&(drop_calls), ci)), "\n");
    ci = (ci + 1LL);
}
    res_str = concatAlloc(res_str, "    return;\n");
    res_str = concatAlloc(res_str, "}");
    return res_str;
}
}
    if (stmt.kind == StmtKind_sk_expr) {
    return concatAlloc(Codegen_gen_expr(self, stmt.expr_stmt), ";");
}
    if (stmt.kind == StmtKind_sk_print) {
    int64_t arg = stmt.print_value;
    const char* val = Codegen_gen_expr(self, arg);
    const char* arg_type = Codegen_get_expr_type(self, arg);
    if (strcmp(arg_type, "Int") == 0) {
    return concatAlloc(concatAlloc("__kai_print_int(", val), ");");
}
    if (strcmp(arg_type, "Float") == 0) {
    return concatAlloc(concatAlloc("__kai_print_float(", val), ");");
}
    if (strcmp(arg_type, "Char") == 0) {
    return concatAlloc(concatAlloc("printf(\"%c\\n\", (char)(", val), "));");
}
    if (strcmp(arg_type, "Bool") == 0) {
    return concatAlloc(concatAlloc("printf(\"%s\\n\", (", val), ") ? \"true\" : \"false\");");
}
    return concatAlloc(concatAlloc("printf(\"%s\\n\", ", val), ");");
}
    if (stmt.kind == StmtKind_sk_unsafe) {
    return Codegen_gen_stmt(self, stmt.unsafe_body);
}
    if (stmt.kind == StmtKind_sk_extern) {
    const char* name = stmt.extern_name;
    if (Codegen_is_standard_c_func(self, name)) {
    return "";
}
    const char* ret_type = Codegen_map_type(self, stmt.extern_return);
    const char* params_str = "";
    int64_t i = 0LL;
    while (i < ArrayList_Param_length(&(stmt.extern_params))) {
    Param p = ArrayList_Param_get(&(stmt.extern_params), i);
    if (i > 0LL) {
    params_str = concatAlloc(params_str, ", ");
}
    params_str = concatAlloc(concatAlloc(concatAlloc(params_str, Codegen_map_type(self, p.ptype)), " "), p.name);
    i = (i + 1LL);
}
    if (strlen(params_str) == 0LL) {
    params_str = "void";
}
    const char* proto = concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc("extern ", ret_type), " "), name), "("), params_str), ");\n");
    (void)(StringBuilder_append(&(self->func_decls), proto));
    return "";
}
    if (stmt.kind == StmtKind_sk_cimport) {
    ImportResolver_record_cimport(self->import_resolver, stmt.cimport_header);
    return "";
}
    if (stmt.kind == StmtKind_sk_import) {
    return "";
}
    if (stmt.kind == StmtKind_sk_break) {
    ArrayList_Str drop_calls = Codegen__collect_loop_drops(self);
    if (ArrayList_Str_length(&(drop_calls)) == 0LL) {
    return "break;";
}
    const char* res_str = "{\n";
    int64_t ci = 0LL;
    while (ci < ArrayList_Str_length(&(drop_calls))) {
    res_str = concatAlloc(concatAlloc(concatAlloc(res_str, "    "), ArrayList_Str_get(&(drop_calls), ci)), "\n");
    ci = (ci + 1LL);
}
    res_str = concatAlloc(res_str, "    break;\n");
    res_str = concatAlloc(res_str, "}");
    return res_str;
}
    if (stmt.kind == StmtKind_sk_continue) {
    ArrayList_Str drop_calls = Codegen__collect_loop_drops(self);
    if (ArrayList_Str_length(&(drop_calls)) == 0LL) {
    return "continue;";
}
    const char* res_str = "{\n";
    int64_t ci = 0LL;
    while (ci < ArrayList_Str_length(&(drop_calls))) {
    res_str = concatAlloc(concatAlloc(concatAlloc(res_str, "    "), ArrayList_Str_get(&(drop_calls), ci)), "\n");
    ci = (ci + 1LL);
}
    res_str = concatAlloc(res_str, "    continue;\n");
    res_str = concatAlloc(res_str, "}");
    return res_str;
}
    if (stmt.kind == StmtKind_sk_match) {
    int64_t expr_idx = stmt.match_expr;
    const char* expr_val = Codegen_gen_expr(self, expr_idx);
    ExprNode expr_node = ArrayList_ExprNode_get(self->expr_pool, expr_idx);
    const char* expr_type = Codegen_get_expr_type(self, expr_idx);
    const char* mapped_expr_type = Codegen_map_type(self, expr_type);
    bool is_self_ptr = (((expr_node.kind == ExprKind_ek_identifier) && (strcmp(expr_node.ident_name, "self") == 0)) && (!self->cur_method_is_init));
    bool is_ptr = false;
    if ((((expr_type)[0LL] == ((char)(42LL))) || ((expr_type)[0LL] == ((char)(38LL)))) || is_self_ptr) {
    is_ptr = true;
}
    const char* op = ".";
    if (is_ptr) {
    op = "->";
}
    const char* match_str = "";
    int64_t case_idx = 0LL;
    while (case_idx < ArrayList_MatchCase_length(&(stmt.match_cases))) {
    MatchCase case_node = ArrayList_MatchCase_get(&(stmt.match_cases), case_idx);
    PatternNode pat_node = ArrayList_PatternNode_get(self->pattern_pool, case_node.pattern);
    const char* block_str = Codegen_gen_stmt(self, case_node.body);
    const char* cond = "";
    const char* bindings_str = "";
    if (pat_node.kind == PatternKind_pk_literal) {
    const char* lit_str = "";
    if (pat_node.lit_value.tag == TokenValue_tv_int_TAG) {
    int64_t v = pat_node.lit_value.payload.tv_int.v;

    lit_str = int_to_str(v);
} else if (pat_node.lit_value.tag == TokenValue_tv_str_TAG) {
    int64_t v = pat_node.lit_value.payload.tv_str.v;

    lit_str = concatAlloc(concatAlloc("\"", Codegen_escape_string(self, StringPool_get(self->pool, v))), "\"");
} else if (pat_node.lit_value.tag == TokenValue_tv_bool_TAG) {
    bool v = pat_node.lit_value.payload.tv_bool.v;

    if (v) {
    lit_str = "true";
} else {
    lit_str = "false";
}
} else if (pat_node.lit_value.tag == TokenValue_tv_char_TAG) {
    char v = pat_node.lit_value.payload.tv_char.v;

    if (v == ((char)(10LL))) {
    lit_str = "'\\n'";
} else if (v == ((char)(13LL))) {
    lit_str = "'\\r'";
} else if (v == ((char)(9LL))) {
    lit_str = "'\\t'";
} else if (v == ((char)(92LL))) {
    lit_str = "'\\\\'";
} else if (v == ((char)(39LL))) {
    lit_str = "'\\''";
} else {
    lit_str = concatAlloc(concatAlloc("'", char_to_str(v)), "'");
}
} else {
    lit_str = "0";
} 
    cond = concatAlloc(concatAlloc(expr_val, " == "), lit_str);
} else if (pat_node.kind == PatternKind_pk_variant) {
    const char* var_name = pat_node.variant_name;
    const char* base_type = mapped_expr_type;
    if ((strlen(base_type) > 0LL) && (((base_type)[(strlen(base_type) - 1LL)] == ((char)(42LL))) || ((base_type)[(strlen(base_type) - 1LL)] == ((char)(38LL))))) {
    base_type = __kai_str_sub(base_type, 0LL, (strlen(base_type) - 1LL));
}
    if ((strlen(base_type) > 0LL) && ((base_type)[0LL] == ((char)(42LL)))) {
    base_type = __kai_str_sub(base_type, 1LL, strlen(base_type));
}
    if (Codegen_enum_has_payload(self, expr_type)) {
    cond = concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(expr_val, op), "tag == "), base_type), "_"), var_name), "_TAG");
} else {
    cond = concatAlloc(concatAlloc(concatAlloc(concatAlloc(expr_val, " == "), base_type), "_"), var_name);
}
    const char* clean_enum_name = expr_type;
    bool done_clean = false;
    while (!done_clean) {
    if ((strlen(clean_enum_name) > 0LL) && (((clean_enum_name)[0LL] == ((char)(42LL))) || ((clean_enum_name)[0LL] == ((char)(38LL))))) {
    clean_enum_name = __kai_str_sub(clean_enum_name, 1LL, strlen(clean_enum_name));
} else {
    done_clean = true;
}
}
    int64_t underscore_pos = Codegen_str_find(self, clean_enum_name, ((char)(95LL)));
    if (underscore_pos >= 0LL) {
    clean_enum_name = __kai_str_sub(clean_enum_name, 0LL, underscore_pos);
}
    int64_t lt_pos = Codegen_str_find(self, clean_enum_name, ((char)(60LL)));
    if (lt_pos >= 0LL) {
    clean_enum_name = __kai_str_sub(clean_enum_name, 0LL, lt_pos);
}
    const char* enum_idx_str = type_map_get(&(self->enum_decls), clean_enum_name);
    bool found_var = false;
    Variant matched_var = (Variant){ .vname = "", .params = empty_param_array() };
    if (strlen(enum_idx_str) > 0LL) {
    StmtNode enum_stmt = ArrayList_StmtNode_get(self->stmt_pool, Codegen_str_to_int(self, enum_idx_str));
    int64_t vi = 0LL;
    while (vi < ArrayList_Variant_length(&(enum_stmt.enum_variants))) {
    Variant v = ArrayList_Variant_get(&(enum_stmt.enum_variants), vi);
    if (strcmp(v.vname, var_name) == 0) {
    found_var = true;
    matched_var = v;
    break;
}
    vi = (vi + 1LL);
}
}
    if (ArrayList_Str_length(&(pat_node.bindings)) > 0LL) {
    int64_t bi = 0LL;
    while (bi < ArrayList_Str_length(&(pat_node.bindings))) {
    const char* bind_name = ArrayList_Str_get(&(pat_node.bindings), bi);
    if (strcmp(bind_name, "_") != 0) {
    const char* bind_type = "Void";
    const char* field_name = "";
    if (found_var && (bi < ArrayList_Param_length(&(matched_var.params)))) {
    Param param = ArrayList_Param_get(&(matched_var.params), bi);
    bind_type = param.ptype;
    field_name = param.name;
}
    if (strcmp(bind_type, "T") == 0) {
    const char* t_type = type_map_get(&(self->current_type_map), "T");
    if (strlen(t_type) == 0LL) {
    t_type = Codegen_extract_first_type_arg(self, expr_type);
}
    bind_type = t_type;
} else if (strcmp(bind_type, "E") == 0) {
    const char* e_type = type_map_get(&(self->current_type_map), "E");
    if (strlen(e_type) == 0LL) {
    e_type = "Int";
}
    bind_type = e_type;
}
    const char* mapped_bind_type = Codegen_map_type(self, bind_type);
    const char* single_binding = concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc("    ", mapped_bind_type), " "), bind_name), " = "), expr_val), op), "payload."), var_name), "."), field_name), ";\n");
    bindings_str = concatAlloc(bindings_str, single_binding);
}
    bi = (bi + 1LL);
}
}
} else if (pat_node.kind == PatternKind_pk_else) {
    cond = "true";
}
    const char* prefix = "";
    if (case_idx == 0LL) {
    prefix = concatAlloc(concatAlloc("if (", cond), ")");
} else if (strcmp(cond, "true") == 0) {
    prefix = "else";
} else {
    prefix = concatAlloc(concatAlloc("else if (", cond), ")");
}
    const char* full_block = block_str;
    if (strlen(bindings_str) > 0LL) {
    int64_t body_len = strlen(block_str);
    full_block = concatAlloc(concatAlloc("{\n", bindings_str), __kai_str_sub(block_str, 1LL, body_len));
}
    match_str = concatAlloc(concatAlloc(concatAlloc(concatAlloc(match_str, prefix), " "), full_block), " ");
    case_idx = (case_idx + 1LL);
}
    return match_str;
}
    return "";
}
const char* Codegen_clean_enum_name(Codegen* self, const char* type_name) {
    const char* base_name = type_name;
    if (Codegen_str_contains(self, type_name, ((char)(60LL)))) {
    int64_t lt_pos = Codegen_str_find(self, type_name, ((char)(60LL)));
    base_name = __kai_str_sub(type_name, 0LL, lt_pos);
}
    if (strcmp(__kai_str_sub(base_name, 0LL, 4LL), "mut ") == 0) {
    base_name = __kai_str_sub(base_name, 4LL, strlen(base_name));
}
    bool done = false;
    while (!done) {
    if ((strlen(base_name) > 0LL) && (((base_name)[0LL] == ((char)(42LL))) || ((base_name)[0LL] == ((char)(38LL))))) {
    base_name = __kai_str_sub(base_name, 1LL, strlen(base_name));
} else {
    done = true;
}
}
    done = false;
    while (!done) {
    int64_t l = strlen(base_name);
    if ((l > 0LL) && (((base_name)[(l - 1LL)] == ((char)(42LL))) || ((base_name)[(l - 1LL)] == ((char)(38LL))))) {
    base_name = __kai_str_sub(base_name, 0LL, (l - 1LL));
} else {
    done = true;
}
}
    if (strlen(type_map_get(&(self->enum_decls), base_name)) == 0LL) {
    if (Codegen_str_contains(self, base_name, ((char)(95LL)))) {
    int64_t underscore_pos = Codegen_str_find(self, base_name, ((char)(95LL)));
    const char* fallback_name = __kai_str_sub(base_name, 0LL, underscore_pos);
    if (strlen(type_map_get(&(self->enum_decls), fallback_name)) > 0LL) {
    return fallback_name;
}
}
}
    return base_name;
}
bool Codegen_is_enum_type(Codegen* self, const char* type_name) {
    const char* clean_name = Codegen_clean_enum_name(self, type_name);
    return (strlen(type_map_get(&(self->enum_decls), clean_name)) > 0LL);
}
bool Codegen_enum_has_payload(Codegen* self, const char* enum_name) {
    const char* clean_name = Codegen_clean_enum_name(self, enum_name);
    const char* idx_str = type_map_get(&(self->enum_decls), clean_name);
    if (strlen(idx_str) == 0LL) {
    return false;
}
    StmtNode enum_stmt = ArrayList_StmtNode_get(self->stmt_pool, Codegen_str_to_int(self, idx_str));
    if (enum_stmt.kind == StmtKind_sk_error_decl) {
    return false;
}
    bool has_payload = false;
    int64_t vi = 0LL;
    while (vi < ArrayList_Variant_length(&(enum_stmt.enum_variants))) {
    Variant v = ArrayList_Variant_get(&(enum_stmt.enum_variants), vi);
    if (ArrayList_Param_length(&(v.params)) > 0LL) {
    has_payload = true;
}
    vi = (vi + 1LL);
}
    return has_payload;
}
const char* Codegen_escape_string(Codegen* self, const char* s) {
    const char* res = "";
    int64_t i = 0LL;
    while (i < strlen(s)) {
    char c = (s)[i];
    if (c == ((char)(10LL))) {
    res = concatAlloc(res, "\\n");
} else if (c == ((char)(13LL))) {
    res = concatAlloc(res, "\\r");
} else if (c == ((char)(9LL))) {
    res = concatAlloc(res, "\\t");
} else if (c == ((char)(92LL))) {
    res = concatAlloc(res, "\\\\");
} else if (c == ((char)(34LL))) {
    res = concatAlloc(res, "\\\"");
} else {
    res = concatAlloc(res, char_to_str(c));
}
    i = (i + 1LL);
}
    return res;
}
ArrayList_Str Codegen__collect_loop_drops(Codegen* self) {
    ArrayList_Str drop_calls = ArrayList_Str_init(self->allocator);
    int64_t bi = (ArrayList_Int_length(&(self->block_stack)) - 1LL);
    bool done = false;
    while ((bi >= 0LL) && (!done)) {
    int64_t b_idx = ArrayList_Int_get(&(self->block_stack), bi);
    StmtNode b_node = ArrayList_StmtNode_get(self->stmt_pool, b_idx);
    int64_t start_idx = ArrayList_Int_get(&(self->defer_depths), bi);
    int64_t next_start_idx = ArrayList_Int_length(&(self->defer_stack));
    if (bi < (ArrayList_Int_length(&(self->block_stack)) - 1LL)) {
    next_start_idx = ArrayList_Int_get(&(self->defer_depths), (bi + 1LL));
}
    int64_t def_i = (next_start_idx - 1LL);
    while (def_i >= start_idx) {
    int64_t def_idx = ArrayList_Int_get(&(self->defer_stack), def_i);
    StmtNode def_node = ArrayList_StmtNode_get(self->stmt_pool, def_idx);
    const char* s = Codegen_gen_stmt(self, def_node.defer_body);
    if (strlen(s) > 0LL) {
    ArrayList_Str_push(&(drop_calls), s);
}
    def_i = (def_i - 1LL);
}
    int64_t di = 0LL;
    while (di < ArrayList_DropVarEntry_length(&(b_node.block_drop_vars))) {
    DropVarEntry entry = ArrayList_DropVarEntry_get(&(b_node.block_drop_vars), di);
    ArrayList_Str_push(&(drop_calls), concatAlloc(concatAlloc(concatAlloc(entry.base_type, "_drop(&"), entry.name), ");"));
    di = (di + 1LL);
}
    if (b_node.block_is_loop_body) {
    done = true;
}
    bi = (bi - 1LL);
}
    return drop_calls;
}
void Codegen_emit_struct_body_with_deps(Codegen* self, int64_t stmt_idx, ArrayList_Str* emitted) {
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, stmt_idx);
    if (stmt.kind != StmtKind_sk_struct_decl) {
    return;
}
    if (ArrayList_Str_length(&(stmt.struct_type_params)) > 0LL) {
    return;
}
    const char* name = Codegen_map_type(self, stmt.struct_name);
    if (strlist_find(emitted, name) >= 0LL) {
    return;
}
    ArrayList_Str_push(emitted, name);
    int64_t fi = 0LL;
    while (fi < ArrayList_StructField_length(&(stmt.struct_fields))) {
    StructField f = ArrayList_StructField_get(&(stmt.struct_fields), fi);
    const char* ftype = f.ftype;
    {
    if (((strlen(ftype) > 0LL) && ((ftype)[0LL] != ((char)(42LL)))) && ((ftype)[0LL] != ((char)(38LL)))) {
    int64_t si = 0LL;
    while (si < ArrayList_StmtNode_length(self->stmt_pool)) {
    StmtNode s2 = ArrayList_StmtNode_get(self->stmt_pool, si);
    if ((s2.kind == StmtKind_sk_struct_decl) && (ArrayList_Str_length(&(s2.struct_type_params)) == 0LL)) {
    if (strcmp(s2.struct_name, ftype) == 0) {
    Codegen_emit_struct_body_with_deps(self, si, emitted);
}
}
    si = (si + 1LL);
}
}
}
    fi = (fi + 1LL);
}
    const char* struct_str = concatAlloc(concatAlloc("struct ", name), " {\n");
    int64_t i = 0LL;
    while (i < ArrayList_StructField_length(&(stmt.struct_fields))) {
    StructField f = ArrayList_StructField_get(&(stmt.struct_fields), i);
    struct_str = concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(struct_str, "    "), Codegen_map_type(self, f.ftype)), " "), f.name), ";\n");
    i = (i + 1LL);
}
    struct_str = concatAlloc(struct_str, "};\n");
    (void)(StringBuilder_append(&(self->struct_decls), struct_str));
    int64_t ti = 0LL;
    while (ti < ArrayList_Int_length(&(stmt.struct_trait_impls))) {
    int64_t impl_idx = ArrayList_Int_get(&(stmt.struct_trait_impls), ti);
    (void)(Codegen_gen_stmt(self, impl_idx));
    ti = (ti + 1LL);
}
}
const char* Codegen_generate(Codegen* self, int64_t top_stmt_idx) {
    int64_t g_i = 0LL;
    while (g_i < ArrayList_StmtNode_length(self->stmt_pool)) {
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, g_i);
    if (stmt.kind == StmtKind_sk_struct_decl) {
    if (ArrayList_Str_length(&(stmt.struct_type_params)) > 0LL) {
    type_map_put(&(self->generic_struct_decls), stmt.struct_name, int_to_str(g_i));
}
}
    if (stmt.kind == StmtKind_sk_enum_decl) {
    if (ArrayList_Str_length(&(stmt.enum_type_params)) > 0LL) {
    type_map_put(&(self->generic_enum_decls), stmt.enum_name, int_to_str(g_i));
}
}
    g_i = (g_i + 1LL);
}
    int64_t fd_i = 0LL;
    while (fd_i < ArrayList_StmtNode_length(self->stmt_pool)) {
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, fd_i);
    if ((stmt.kind == StmtKind_sk_struct_decl) && (ArrayList_Str_length(&(stmt.struct_type_params)) == 0LL)) {
    const char* name = Codegen_map_type(self, stmt.struct_name);
    (void)(StringBuilder_append(&(self->struct_decls), concatAlloc(concatAlloc(concatAlloc(concatAlloc("typedef struct ", name), " "), name), ";\n")));
}
    fd_i = (fd_i + 1LL);
}
    Codegen_build_func_types(self);
    ArrayList_Str emitted_structs = ArrayList_Str_init(self->allocator);
    int64_t s_i = 0LL;
    while (s_i < ArrayList_StmtNode_length(self->stmt_pool)) {
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, s_i);
    if (stmt.kind == StmtKind_sk_struct_decl) {
    Codegen_emit_struct_body_with_deps(self, s_i, &(emitted_structs));
}
    if (stmt.kind == StmtKind_sk_enum_decl) {
    (void)(Codegen_gen_stmt(self, s_i));
}
    if (stmt.kind == StmtKind_sk_error_decl) {
    (void)(Codegen_gen_stmt(self, s_i));
}
    s_i = (s_i + 1LL);
}
    int64_t f_i = 0LL;
    while (f_i < ArrayList_StmtNode_length(self->stmt_pool)) {
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, f_i);
    if (stmt.kind == StmtKind_sk_func_decl) {
    bool has_self = false;
    int64_t pi = 0LL;
    while (pi < ArrayList_Param_length(&(stmt.func_params))) {
    {
    if (strcmp(ArrayList_Param_get(&(stmt.func_params), pi).name, "self") == 0LL) {
    has_self = true;
}
}
    pi = (pi + 1LL);
}
    if ((!has_self) && (ArrayList_Str_length(&(stmt.func_type_params)) == 0LL)) {
    (void)(Codegen_gen_stmt(self, f_i));
}
}
    if (stmt.kind == StmtKind_sk_extern) {
    (void)(Codegen_gen_stmt(self, f_i));
}
    if (stmt.kind == StmtKind_sk_impl_block) {
    (void)(Codegen_gen_stmt(self, f_i));
}
    f_i = (f_i + 1LL);
}
    StringBuilder result = StringBuilder_init(self->allocator);
    StringBuilder_append(&(result), "#include <stdint.h>\n");
    StringBuilder_append(&(result), "#include <stdbool.h>\n");
    StringBuilder_append(&(result), "#include <stdio.h>\n");
    StringBuilder_append(&(result), "#include <stdlib.h>\n");
    StringBuilder_append(&(result), "#include <string.h>\n");
    StringBuilder_append(&(result), "#ifndef __kai_std_str_concat_alloc\n");
    StringBuilder_append(&(result), "#define __kai_std_str_concat_alloc concatAlloc\n");
    StringBuilder_append(&(result), "#endif\n");
    StringBuilder_append(&(result), "#ifndef NO_GET_EXE_DIR\n");
    StringBuilder_append(&(result), "#include \"std/os/os.h\"\n");
    StringBuilder_append(&(result), "int64_t get_exe_dir(char* out_buf, int64_t max_len) {\n");
    StringBuilder_append(&(result), "    return kai_os_get_exe_dir(out_buf, max_len);\n");
    StringBuilder_append(&(result), "}\n");
    StringBuilder_append(&(result), "#endif\n");
    StringBuilder_append(&(result), "\n");
    StringBuilder_append(&(result), "static char* __kai_str_sub(const char* s, int64_t start, int64_t end) {\n");
    StringBuilder_append(&(result), "    int64_t len = strlen(s);\n");
    StringBuilder_append(&(result), "    if (end > len) end = len;\n");
    StringBuilder_append(&(result), "    if (start < 0) start = 0;\n");
    StringBuilder_append(&(result), "    if (start >= end) {\n");
    StringBuilder_append(&(result), "        char* empty = malloc(1);\n");
    StringBuilder_append(&(result), "        if (empty) empty[0] = '\\0';\n");
    StringBuilder_append(&(result), "        return empty;\n");
    StringBuilder_append(&(result), "    }\n");
    StringBuilder_append(&(result), "    int64_t sub_len = end - start;\n");
    StringBuilder_append(&(result), "    char* buf = malloc(sub_len + 1);\n");
    StringBuilder_append(&(result), "    if (buf) {\n");
    StringBuilder_append(&(result), "        memcpy(buf, s + start, sub_len);\n");
    StringBuilder_append(&(result), "        buf[sub_len] = '\\0';\n");
    StringBuilder_append(&(result), "    }\n");
    StringBuilder_append(&(result), "    return buf;\n");
    StringBuilder_append(&(result), "}\n");
    StringBuilder_append(&(result), "\n");
    StringBuilder_append(&(result), "static void* __kai_arr_sub(const void* arr, int64_t start, int64_t end, int64_t elem_size) {\n");
    StringBuilder_append(&(result), "    int64_t count = end - start;\n");
    StringBuilder_append(&(result), "    if (count <= 0) return NULL;\n");
    StringBuilder_append(&(result), "    size_t total = (size_t)count * (size_t)elem_size;\n");
    StringBuilder_append(&(result), "    void* buf = malloc(total);\n");
    StringBuilder_append(&(result), "    if (buf) memcpy(buf, (const char*)arr + start * elem_size, total);\n");
    StringBuilder_append(&(result), "    return buf;\n");
    StringBuilder_append(&(result), "}\n");
    StringBuilder_append(&(result), "\n");
    int64_t ci = 0LL;
    bool has_cimports = false;
    while (ci < ArrayList_Str_length(&(self->import_resolver->cimport_headers))) {
    const char* hdr = ArrayList_Str_get(&(self->import_resolver->cimport_headers), ci);
    bool is_baseline = false;
    if (strcmp(hdr, "stdint.h") == 0) {
    is_baseline = true;
} else if (strcmp(hdr, "stdbool.h") == 0) {
    is_baseline = true;
} else if (strcmp(hdr, "stdio.h") == 0) {
    is_baseline = true;
} else if (strcmp(hdr, "stdlib.h") == 0) {
    is_baseline = true;
} else if (strcmp(hdr, "string.h") == 0) {
    is_baseline = true;
} else if (strcmp(hdr, "sys/mman.h") == 0) {
    is_baseline = true;
} else if (strcmp(hdr, "ctype.h") == 0) {
    is_baseline = true;
}
    if (!is_baseline) {
    if (!has_cimports) {
    StringBuilder_append(&(result), "/* C FFI Imports */\n");
    has_cimports = true;
}
    bool has_slash = false;
    bool dot_start = false;
    if (strlen(hdr) > 0LL) {
    int64_t hi = 0LL;
    while (hi < strlen(hdr)) {
    if ((hdr)[hi] == ((char)(47LL))) {
    has_slash = true;
}
    hi = (hi + 1LL);
}
    if ((hdr)[0LL] == ((char)(46LL))) {
    dot_start = true;
}
}
    if ((!has_slash) && (!dot_start)) {
    StringBuilder_append(&(result), concatAlloc(concatAlloc("#include <", hdr), ">\n"));
} else {
    StringBuilder_append(&(result), concatAlloc(concatAlloc("#include \"", hdr), "\"\n"));
}
}
    ci = (ci + 1LL);
}
    StringBuilder_append(&(result), "#ifndef MAP_FAILED\n");
    StringBuilder_append(&(result), "#define MAP_FAILED ((void*)-1)\n");
    StringBuilder_append(&(result), "#endif\n");
    StringBuilder_append(&(result), "#ifndef MAP_PRIVATE\n");
    StringBuilder_append(&(result), "#define MAP_PRIVATE 2\n");
    StringBuilder_append(&(result), "#endif\n");
    StringBuilder_append(&(result), "#ifndef MAP_ANONYMOUS\n");
    StringBuilder_append(&(result), "#ifdef __APPLE__\n");
    StringBuilder_append(&(result), "#define MAP_ANONYMOUS 0x1000\n");
    StringBuilder_append(&(result), "#else\n");
    StringBuilder_append(&(result), "#define MAP_ANONYMOUS 0x20\n");
    StringBuilder_append(&(result), "#endif\n");
    StringBuilder_append(&(result), "#endif\n");
    StringBuilder_append(&(result), "extern void* mmap(void* addr, unsigned long long length, int prot, int flags, int fd, long long offset);\n");
    StringBuilder_append(&(result), "extern int munmap(void* addr, unsigned long long length);\n");
    StringBuilder_append(&(result), "\n");
    StringBuilder_append(&(result), "void __kai_print_int(int64_t v) {\n");
    StringBuilder_append(&(result), "    printf(\"%lld\\n\", (long long)(v));\n");
    StringBuilder_append(&(result), "}\n");
    StringBuilder_append(&(result), "\n");
    StringBuilder_append(&(result), "void __kai_print_float(double v) {\n");
    StringBuilder_append(&(result), "    printf(\"%f\\n\", (double)(v));\n");
    StringBuilder_append(&(result), "}\n");
    StringBuilder_append(&(result), "\n");
    StringBuilder_append(&(result), "static inline uint8_t* _kai_mmap(uint8_t* addr, int64_t length, int64_t prot, int64_t flags, int64_t fd, int64_t offset) {\n");
    StringBuilder_append(&(result), "    return (uint8_t*)mmap(addr, length, prot, MAP_PRIVATE | MAP_ANONYMOUS, fd, offset);\n");
    StringBuilder_append(&(result), "}\n");
    StringBuilder_append(&(result), "\n");
    StringBuilder_append(&(result), "static inline int64_t _kai_munmap(uint8_t* addr, int64_t length) {\n");
    StringBuilder_append(&(result), "    return munmap(addr, length);\n");
    StringBuilder_append(&(result), "}\n");
    StringBuilder_append(&(result), "\n");
    StringBuilder_append(&(result), "extern void __kai_panic(const char* msg);\n");
    StringBuilder_append(&(result), "#ifndef __KAI_NO_PANIC\n");
    StringBuilder_append(&(result), "void __kai_panic(const char* msg) {\n");
    StringBuilder_append(&(result), "    fprintf(stderr, \"KAI PANIC: %s\\n\", msg);\n");
    StringBuilder_append(&(result), "    fflush(stderr);\n");
    StringBuilder_append(&(result), "    abort();\n");
    StringBuilder_append(&(result), "}\n");
    StringBuilder_append(&(result), "#endif\n");
    StringBuilder_append(&(result), "\n");
    StringBuilder_append(&(result), StringBuilder_to_str(&(self->struct_decls)));
    StringBuilder_append(&(result), "\n");
    StringBuilder_append(&(result), StringBuilder_to_str(&(self->func_decls)));
    StringBuilder_append(&(result), "\n");
    StringBuilder_append(&(result), StringBuilder_to_str(&(self->output)));
    return StringBuilder_to_str(&(result));
}
StrBuf StrBuf_init(KaiAllocator* a) {
    StrBuf self = (StrBuf){0};
    self.alloc = a;
    self.parts = ArrayList_Str_init(a);
    return self;
}
void StrBuf_append(StrBuf* self, const char* s) {
    ArrayList_Str_push(&(self->parts), s);
}
const char* StrBuf_to_str(StrBuf* self) {
    const char* result = "";
    int64_t i = 0LL;
    while (i < ArrayList_Str_length(&(self->parts))) {
    result = concatAlloc(result, ArrayList_Str_get(&(self->parts), i));
    i = (i + 1LL);
}
    return result;
}
int64_t cgb_map_find(ArrayList_CgbMapEntry* arr, const char* key) {
    int64_t i = (ArrayList_CgbMapEntry_length(arr) - 1LL);
    while (i >= 0LL) {
    if (strcmp(ArrayList_CgbMapEntry_get(arr, i).key, key) == 0) {
    return i;
}
    i = (i - 1LL);
}
    return (-1LL);
}
const char* cgb_map_get(ArrayList_CgbMapEntry* arr, const char* key) {
    int64_t idx = cgb_map_find(arr, key);
    if (idx < 0LL) {
    return "";
}
    return ArrayList_CgbMapEntry_get(arr, idx).value;
}
void cgb_map_put(ArrayList_CgbMapEntry* arr, const char* key, const char* value) {
    ArrayList_CgbMapEntry_push(arr, (CgbMapEntry){ .key = key, .value = value });
}
int64_t cgb_strlist_find(ArrayList_Str* arr, const char* key) {
    int64_t i = 0LL;
    while (i < ArrayList_Str_length(arr)) {
    if (strcmp(ArrayList_Str_get(arr, i), key) == 0) {
    return i;
}
    i = (i + 1LL);
}
    return (-1LL);
}
const char* CodegenBuilder_add_init_return(CodegenBuilder* self, const char* body_str, const char* struct_name) {
    const char* self_decl = concatAlloc(concatAlloc(concatAlloc(concatAlloc("    ", struct_name), " self = ("), struct_name), "){0};\n");
    const char* content = body_str;
    if ((strlen(content) >= 3LL) && ((content)[0LL] == ((char)(123LL)))) {
    int64_t end_pos = (strlen(content) - 1LL);
    bool done_trim = false;
    while (!done_trim) {
    if (end_pos <= 0LL) {
    done_trim = true;
} else {
    char ec = (content)[end_pos];
    if (((ec == ((char)(10LL))) || (ec == ((char)(13LL)))) || (ec == ((char)(32LL)))) {
    end_pos = (end_pos - 1LL);
} else {
    done_trim = true;
}
}
}
    if ((end_pos > 0LL) && ((content)[end_pos] == ((char)(125LL)))) {
    end_pos = (end_pos - 1LL);
}
    done_trim = false;
    while (!done_trim) {
    if (end_pos <= 0LL) {
    done_trim = true;
} else {
    char ec = (content)[end_pos];
    if (((ec == ((char)(10LL))) || (ec == ((char)(13LL)))) || (ec == ((char)(32LL)))) {
    end_pos = (end_pos - 1LL);
} else {
    done_trim = true;
}
}
}
    int64_t first_nl = 1LL;
    bool found_nl = false;
    while ((first_nl < end_pos) && (!found_nl)) {
    if ((content)[first_nl] == ((char)(10LL))) {
    found_nl = true;
} else {
    first_nl = (first_nl + 1LL);
}
}
    if (found_nl) {
    content = __kai_str_sub(content, (first_nl + 1LL), (end_pos + 1LL));
}
}
    bool ends_with_return = false;
    {
    char* ret_ptr = strstr(content, "return self;");
    if (ret_ptr != (char*)(unsigned long long)(0LL)) {
    int64_t offset = ((int64_t)(ret_ptr) - (int64_t)(content));
    if (offset >= (strlen(content) - 25LL)) {
    ends_with_return = true;
}
}
}
    if (ends_with_return) {
    return concatAlloc(concatAlloc(concatAlloc("{\n", self_decl), content), "}");
}
    return concatAlloc(concatAlloc(concatAlloc("{\n", self_decl), content), "    return self;\n}");
}
CodegenBuilder CodegenBuilder_init(KaiAllocator* allocator, ArrayList_StmtNode* stmt_pool, ArrayList_ExprNode* expr_pool, ArrayList_PatternNode* pattern_pool, ImportResolver* import_resolver, StringPool* pool) {
    CodegenBuilder self = (CodegenBuilder){0};
    self.allocator = allocator;
    self.stmt_pool = stmt_pool;
    self.expr_pool = expr_pool;
    self.pattern_pool = pattern_pool;
    self.import_resolver = import_resolver;
    self.pool = pool;
    self.builder = CCodeBuilder_init(allocator);
    self.struct_decls = StrBuf_init(allocator);
    self.func_decls = StrBuf_init(allocator);
    self.output_body = StrBuf_init(allocator);
    self.cur_func_name = "";
    self.cur_return_type = "";
    self.cur_method_is_init = false;
    self.func_types = ArrayList_CgbMapEntry_init(allocator);
    self.var_types = ArrayList_CgbMapEntry_init(allocator);
    self.block_stack = ArrayList_Int_init(allocator);
    self.generic_struct_decls = ArrayList_CgbMapEntry_init(allocator);
    self.generic_enum_decls = ArrayList_CgbMapEntry_init(allocator);
    self.generic_func_decls = ArrayList_CgbMapEntry_init(allocator);
    self.generic_impl_blocks = ArrayList_CgbMapEntry_init(allocator);
    self.monomorphized_types = ArrayList_Str_init(allocator);
    self.current_type_map = ArrayList_CgbMapEntry_init(allocator);
    self.enum_decls = ArrayList_CgbMapEntry_init(allocator);
    self.result_definitions = ArrayList_Str_init(allocator);
    self.monomorphized_bodies = StrBuf_init(allocator);
    self.defer_stack = ArrayList_Int_init(allocator);
    self.defer_depths = ArrayList_Int_init(allocator);
    self.func_param_types = ArrayList_CgbMapEntry_init(allocator);
    self.type_defs = StrBuf_init(allocator);
    self.c_exprs = ArrayList_CExprNode_init(allocator);
    self.c_stmts = ArrayList_CStmtNode_init(allocator);
    return self;
}
bool CodegenBuilder_is_pointer_type(CodegenBuilder* self, const char* t) {
    if (strlen(t) == 0LL) {
    return false;
}
    if (((t)[0LL] == ((char)(42LL))) || ((t)[0LL] == ((char)(38LL)))) {
    return true;
}
    if (strcmp(t, "Str") == 0) {
    return true;
}
    if ((strlen(t) >= 2LL) && (strcmp(__kai_str_sub(t, 0LL, 2LL), "[]") == 0)) {
    return true;
}
    return false;
}
bool CodegenBuilder_is_numeric_type(CodegenBuilder* self, const char* t) {
    if (((((strcmp(t, "Int") == 0) || (strcmp(t, "i8") == 0)) || (strcmp(t, "i16") == 0)) || (strcmp(t, "i32") == 0)) || (strcmp(t, "i64") == 0)) {
    return true;
}
    if ((((strcmp(t, "u8") == 0) || (strcmp(t, "u16") == 0)) || (strcmp(t, "u32") == 0)) || (strcmp(t, "u64") == 0)) {
    return true;
}
    if ((strcmp(t, "isize") == 0) || (strcmp(t, "usize") == 0)) {
    return true;
}
    if (strcmp(t, "Float") == 0) {
    return true;
}
    return false;
}
bool CodegenBuilder_is_integer_type(CodegenBuilder* self, const char* t) {
    if (((((strcmp(t, "Int") == 0) || (strcmp(t, "i8") == 0)) || (strcmp(t, "i16") == 0)) || (strcmp(t, "i32") == 0)) || (strcmp(t, "i64") == 0)) {
    return true;
}
    if ((((strcmp(t, "u8") == 0) || (strcmp(t, "u16") == 0)) || (strcmp(t, "u32") == 0)) || (strcmp(t, "u64") == 0)) {
    return true;
}
    if ((strcmp(t, "isize") == 0) || (strcmp(t, "usize") == 0)) {
    return true;
}
    return false;
}
bool CodegenBuilder_is_copy_type(CodegenBuilder* self, const char* type_name) {
    if (CodegenBuilder_is_integer_type(self, type_name)) {
    return true;
}
    if (strcmp(type_name, "Float") == 0) {
    return true;
}
    if (strcmp(type_name, "Bool") == 0) {
    return true;
}
    if (strcmp(type_name, "Char") == 0) {
    return true;
}
    if (strcmp(type_name, "Str") == 0) {
    return true;
}
    if (strcmp(type_name, "Void") == 0) {
    return true;
}
    if (strcmp(type_name, "NoneType") == 0) {
    return true;
}
    if ((strlen(type_name) > 0LL) && (((type_name)[0LL] == ((char)(42LL))) || ((type_name)[0LL] == ((char)(38LL))))) {
    return true;
}
    return false;
}
const char* CodegenBuilder_get_expr_type(CodegenBuilder* self, int64_t expr_idx) {
    if (expr_idx < 0LL) {
    return "Void";
}
    ExprNode expr = ArrayList_ExprNode_get(self->expr_pool, expr_idx);
    if (expr.kind == ExprKind_ek_literal) {
    const char* vkind = expr.lit_vkind;
    if (strcmp(vkind, "INT") == 0) {
    return "Int";
}
    if (strcmp(vkind, "FLOAT") == 0) {
    return "Float";
}
    if (strcmp(vkind, "STRING") == 0) {
    return "Str";
}
    if (strcmp(vkind, "BOOL") == 0) {
    return "Bool";
}
    if (strcmp(vkind, "CHAR") == 0) {
    return "Char";
}
    return "Void";
}
    if (expr.kind == ExprKind_ek_identifier) {
    const char* name = expr.ident_name;
    int64_t mapping = cgb_map_find(&(self->var_types), name);
    if (mapping >= 0LL) {
    return ArrayList_CgbMapEntry_get(&(self->var_types), mapping).value;
}
    if (strlen(name) > 0LL) {
    char first_char = (name)[0LL];
    if ((first_char >= ((char)(65LL))) && (first_char <= ((char)(90LL)))) {
    if (ArrayList_Str_length(&(expr.ident_type_args)) > 0LL) {
    const char* full_name = concatAlloc(name, "<");
    int64_t tai = 0LL;
    while (tai < ArrayList_Str_length(&(expr.ident_type_args))) {
    if (tai > 0LL) {
    full_name = concatAlloc(full_name, ", ");
}
    full_name = concatAlloc(full_name, ArrayList_Str_get(&(expr.ident_type_args), tai));
    tai = (tai + 1LL);
}
    full_name = concatAlloc(full_name, ">");
    return full_name;
}
    return name;
}
}
    return "Void";
}
    if (expr.kind == ExprKind_ek_binary_op) {
    if ((strcmp(expr.binop_op, "+") == 0) && (strcmp(CodegenBuilder_get_expr_type(self, expr.binop_left), "Str") == 0)) {
    return "Str";
}
    if ((((((strcmp(expr.binop_op, "==") == 0) || (strcmp(expr.binop_op, "!=") == 0)) || (strcmp(expr.binop_op, "<") == 0)) || (strcmp(expr.binop_op, ">") == 0)) || (strcmp(expr.binop_op, "<=") == 0)) || (strcmp(expr.binop_op, ">=") == 0)) {
    return "Bool";
}
    if ((strcmp(expr.binop_op, "&&") == 0) || (strcmp(expr.binop_op, "||") == 0)) {
    return "Bool";
}
    return CodegenBuilder_get_expr_type(self, expr.binop_left);
}
    if (expr.kind == ExprKind_ek_unary_op) {
    return CodegenBuilder_get_expr_type(self, expr.unop_operand);
}
    if (expr.kind == ExprKind_ek_func_call) {
    const char* name = expr.func_name;
    if ((strcmp(name, "cast") == 0) || (strcmp(name, "as") == 0)) {
    if (ArrayList_Str_length(&(expr.func_type_args)) > 0LL) {
    return ArrayList_Str_get(&(expr.func_type_args), 0LL);
}
    return "Void";
}
    if ((((strcmp(name, "Int") == 0) || (strcmp(name, "Float") == 0)) || (strcmp(name, "Bool") == 0)) || (strcmp(name, "Char") == 0)) {
    return "Int";
}
    if (strcmp(name, "size_of") == 0) {
    return "Int";
}
    if (strcmp(name, "length") == 0) {
    return "Int";
}
    bool is_struct = false;
    int64_t si = 0LL;
    while (si < ArrayList_StmtNode_length(self->stmt_pool)) {
    StmtNode s = ArrayList_StmtNode_get(self->stmt_pool, si);
    if ((s.kind == StmtKind_sk_struct_decl) && (strcmp(s.struct_name, name) == 0)) {
    is_struct = true;
}
    si = (si + 1LL);
}
    if (((strcmp(name, "ArrayList") == 0) || (strcmp(name, "HashMap") == 0)) || (strcmp(name, "StringBuilder") == 0)) {
    is_struct = true;
}
    if (is_struct) {
    if (ArrayList_Str_length(&(expr.func_type_args)) > 0LL) {
    const char* unmangled = concatAlloc(name, "<");
    int64_t tai = 0LL;
    while (tai < ArrayList_Str_length(&(expr.func_type_args))) {
    if (tai > 0LL) {
    unmangled = concatAlloc(unmangled, ", ");
}
    unmangled = concatAlloc(unmangled, ArrayList_Str_get(&(expr.func_type_args), tai));
    tai = (tai + 1LL);
}
    unmangled = concatAlloc(unmangled, ">");
    return unmangled;
}
    return name;
}
    int64_t fidx = cgb_map_find(&(self->func_types), name);
    if (fidx >= 0LL) {
    const char* func_type = ArrayList_CgbMapEntry_get(&(self->func_types), fidx).value;
    int64_t colon_pos = 0LL;
    while (colon_pos < strlen(func_type)) {
    if ((func_type)[colon_pos] == ((char)(58LL))) {
    return __kai_str_sub(func_type, (colon_pos + 1LL), strlen(func_type));
}
    colon_pos = (colon_pos + 1LL);
}
    if (strlen(func_type) > 0LL) {
    return func_type;
}
}
    int64_t fsi = 0LL;
    while (fsi < ArrayList_StmtNode_length(self->stmt_pool)) {
    StmtNode s = ArrayList_StmtNode_get(self->stmt_pool, fsi);
    if ((s.kind == StmtKind_sk_extern) && (strcmp(s.extern_name, name) == 0)) {
    return s.extern_return;
}
    if ((s.kind == StmtKind_sk_func_decl) && (strcmp(s.func_name, name) == 0)) {
    return s.func_return_type;
}
    fsi = (fsi + 1LL);
}
    return "Void";
}
    if (expr.kind == ExprKind_ek_index) {
    const char* base_type = CodegenBuilder_get_expr_type(self, expr.idx_expr);
    if (strcmp(base_type, "Str") == 0) {
    return "Char";
}
    if ((strlen(base_type) >= 2LL) && (strcmp(__kai_str_sub(base_type, 0LL, 2LL), "[]") == 0)) {
    return __kai_str_sub(base_type, 2LL, strlen(base_type));
}
    if ((strlen(base_type) > 0LL) && ((base_type)[0LL] == ((char)(42LL)))) {
    return __kai_str_sub(base_type, 1LL, strlen(base_type));
}
    return "Void";
}
    if (expr.kind == ExprKind_ek_field_access) {
    const char* base_type = CodegenBuilder_get_expr_type(self, expr.field_expr);
    if ((strlen(base_type) > 0LL) && ((base_type)[0LL] == ((char)(40LL)))) {
    const char* field_name = expr.field_name;
    if ((strlen(field_name) > 1LL) && ((field_name)[0LL] == ((char)(102LL)))) {
    int64_t idx_val = 0LL;
    int64_t fi = 1LL;
    bool valid = true;
    while (fi < strlen(field_name)) {
    char c = (field_name)[fi];
    if ((c >= ((char)(48LL))) && (c <= ((char)(57LL)))) {
    idx_val = ((idx_val * 10LL) + (((int64_t)(c)) - 48LL));
} else {
    valid = false;
}
    fi = (fi + 1LL);
}
    if (valid) {
    const char* inner_types = __kai_str_sub(base_type, 1LL, (strlen(base_type) - 1LL));
    ArrayList_Str types_list = ArrayList_Str_init(self->allocator);
    int64_t start = 0LL;
    int64_t i = 0LL;
    while (i < strlen(inner_types)) {
    if ((inner_types)[i] == ((char)(44LL))) {
    int64_t ts_start = start;
    while ((ts_start < i) && ((inner_types)[ts_start] == ((char)(32LL)))) {
    ts_start = (ts_start + 1LL);
}
    int64_t ts_end = i;
    while ((ts_end > ts_start) && ((inner_types)[(ts_end - 1LL)] == ((char)(32LL)))) {
    ts_end = (ts_end - 1LL);
}
    ArrayList_Str_push(&(types_list), __kai_str_sub(inner_types, ts_start, ts_end));
    start = (i + 1LL);
}
    i = (i + 1LL);
}
    int64_t ts_start = start;
    while ((ts_start < strlen(inner_types)) && ((inner_types)[ts_start] == ((char)(32LL)))) {
    ts_start = (ts_start + 1LL);
}
    int64_t ts_end = strlen(inner_types);
    while ((ts_end > ts_start) && ((inner_types)[(ts_end - 1LL)] == ((char)(32LL)))) {
    ts_end = (ts_end - 1LL);
}
    ArrayList_Str_push(&(types_list), __kai_str_sub(inner_types, ts_start, ts_end));
    if (idx_val < ArrayList_Str_length(&(types_list))) {
    return ArrayList_Str_get(&(types_list), idx_val);
}
}
}
}
    const char* clean_base = base_type;
    bool done_strip = false;
    while (!done_strip) {
    if ((strlen(clean_base) > 0LL) && (((clean_base)[0LL] == ((char)(42LL))) || ((clean_base)[0LL] == ((char)(38LL))))) {
    clean_base = __kai_str_sub(clean_base, 1LL, strlen(clean_base));
} else if ((strlen(clean_base) > 5LL) && (strcmp(__kai_str_sub(clean_base, 0LL, 5LL), "*mut ") == 0)) {
    clean_base = __kai_str_sub(clean_base, 5LL, strlen(clean_base));
} else {
    done_strip = true;
}
}
    int64_t fi = 0LL;
    while (fi < ArrayList_StmtNode_length(self->stmt_pool)) {
    StmtNode s = ArrayList_StmtNode_get(self->stmt_pool, fi);
    if (s.kind == StmtKind_sk_struct_decl) {
    bool is_match = false;
    if (strcmp(s.struct_name, clean_base) == 0) {
    is_match = true;
} else if (CodegenBuilder_str_contains(self, clean_base, ((char)(95LL)))) {
    if (ArrayList_Str_length(&(s.struct_type_params)) > 0LL) {
    int64_t underscore_pos = CodegenBuilder_str_find(self, clean_base, ((char)(95LL)));
    if (underscore_pos >= 0LL) {
    const char* base_name = __kai_str_sub(clean_base, 0LL, underscore_pos);
    if (strcmp(s.struct_name, base_name) == 0) {
    is_match = true;
}
}
}
}
    if (is_match) {
    int64_t ff = 0LL;
    while (ff < ArrayList_StructField_length(&(s.struct_fields))) {
    if (strcmp(ArrayList_StructField_get(&(s.struct_fields), ff).name, expr.field_name) == 0) {
    return ArrayList_StructField_get(&(s.struct_fields), ff).ftype;
}
    ff = (ff + 1LL);
}
}
}
    fi = (fi + 1LL);
}
    return "Void";
}
    if (expr.kind == ExprKind_ek_struct_init) {
    const char* sname = expr.struct_name;
    int64_t dot_pos = CodegenBuilder_str_find(self, sname, ((char)(46LL)));
    if (dot_pos >= 0LL) {
    return __kai_str_sub(sname, 0LL, dot_pos);
}
    return sname;
}
    if (expr.kind == ExprKind_ek_method_call) {
    const char* rec_type = CodegenBuilder_get_expr_type(self, expr.meth_expr);
    const char* clean_type = "";
    int64_t ci = 0LL;
    while (ci < strlen(rec_type)) {
    char c = (rec_type)[ci];
    if ((c != ((char)(42LL))) && (c != ((char)(38LL)))) {
    clean_type = concatAlloc(clean_type, cgb_char_to_str(c));
}
    ci = (ci + 1LL);
}
    if ((strlen(clean_type) >= 4LL) && (strcmp(__kai_str_sub(clean_type, 0LL, 4LL), "mut ") == 0)) {
    clean_type = __kai_str_sub(clean_type, 4LL, strlen(clean_type));
}
    clean_type = CodegenBuilder_map_type(self, clean_type);
    const char* key = concatAlloc(concatAlloc(clean_type, "_"), expr.meth_name);
    int64_t fidx = cgb_map_find(&(self->func_types), key);
    if (fidx >= 0LL) {
    return ArrayList_CgbMapEntry_get(&(self->func_types), fidx).value;
}
    return "Void";
}
    if (expr.kind == ExprKind_ek_borrow) {
    return concatAlloc("&", CodegenBuilder_get_expr_type(self, expr.borrow_expr));
}
    if (expr.kind == ExprKind_ek_deref) {
    const char* base_type = CodegenBuilder_get_expr_type(self, expr.deref_expr);
    if ((strlen(base_type) > 5LL) && (strcmp(__kai_str_sub(base_type, 0LL, 5LL), "*mut ") == 0)) {
    return __kai_str_sub(base_type, 5LL, strlen(base_type));
}
    if ((strlen(base_type) > 5LL) && (strcmp(__kai_str_sub(base_type, 0LL, 5LL), "&mut ") == 0)) {
    return __kai_str_sub(base_type, 5LL, strlen(base_type));
}
    if (((base_type)[0LL] == ((char)(42LL))) || ((base_type)[0LL] == ((char)(38LL)))) {
    return __kai_str_sub(base_type, 1LL, strlen(base_type));
}
    return "Void";
}
    if (expr.kind == ExprKind_ek_range) {
    return "Range";
}
    if (expr.kind == ExprKind_ek_slice) {
    if (strlen(expr.inferred_type) > 0LL) {
    return expr.inferred_type;
}
    const char* base_type = CodegenBuilder_get_expr_type(self, expr.slice_expr);
    if ((strcmp(base_type, "Str") == 0) || (strcmp(base_type, "*Char") == 0)) {
    return "Str";
}
    return base_type;
}
    if (expr.kind == ExprKind_ek_array) {
    return expr.inferred_type;
}
    if (expr.kind == ExprKind_ek_tuple) {
    if (strlen(expr.inferred_type) > 0LL) {
    return expr.inferred_type;
}
    ArrayList_Str types = ArrayList_Str_init(self->allocator);
    int64_t i = 0LL;
    while (i < ArrayList_Int_length(&(expr.tup_elements))) {
    ArrayList_Str_push(&(types), CodegenBuilder_get_expr_type(self, ArrayList_Int_get(&(expr.tup_elements), i)));
    i = (i + 1LL);
}
    const char* res = "(";
    int64_t j = 0LL;
    while (j < ArrayList_Str_length(&(types))) {
    if (j > 0LL) {
    res = concatAlloc(res, ", ");
}
    res = concatAlloc(res, ArrayList_Str_get(&(types), j));
    j = (j + 1LL);
}
    res = concatAlloc(res, ")");
    return res;
}
    if (expr.kind == ExprKind_ek_asm) {
    return expr.inferred_type;
}
    if (expr.kind == ExprKind_ek_try) {
    const char* inner_ty = CodegenBuilder_get_expr_type(self, expr.try_expr);
    if (CodegenBuilder_str_contains(self, inner_ty, ((char)(33LL)))) {
    int64_t excl_pos = CodegenBuilder_str_find(self, inner_ty, ((char)(33LL)));
    if (excl_pos >= 0LL) {
    return __kai_str_sub(inner_ty, 0LL, excl_pos);
}
}
    return inner_ty;
}
    if (expr.kind == ExprKind_ek_catch) {
    const char* inner_ty = CodegenBuilder_get_expr_type(self, expr.catch_expr);
    if ((strlen(inner_ty) > 0LL) && ((inner_ty)[0LL] == ((char)(63LL)))) {
    return __kai_str_sub(inner_ty, 1LL, strlen(inner_ty));
}
    if (CodegenBuilder_str_contains(self, inner_ty, ((char)(33LL)))) {
    int64_t excl_pos = CodegenBuilder_str_find(self, inner_ty, ((char)(33LL)));
    if (excl_pos >= 0LL) {
    return __kai_str_sub(inner_ty, 0LL, excl_pos);
}
}
    return inner_ty;
}
    return "Void";
}
const char* CodegenBuilder_escape_string(CodegenBuilder* self, const char* s) {
    const char* res = "";
    int64_t i = 0LL;
    while (i < strlen(s)) {
    char c = (s)[i];
    if (c == ((char)(10LL))) {
    res = concatAlloc(res, "\\n");
} else if (c == ((char)(13LL))) {
    res = concatAlloc(res, "\\r");
} else if (c == ((char)(9LL))) {
    res = concatAlloc(res, "\\t");
} else if (c == ((char)(92LL))) {
    res = concatAlloc(res, "\\\\");
} else if (c == ((char)(34LL))) {
    res = concatAlloc(res, "\\\"");
} else {
    res = concatAlloc(res, cgb_char_to_str(c));
}
    i = (i + 1LL);
}
    return res;
}
int64_t CodegenBuilder_str_to_int(CodegenBuilder* self, const char* s) {
    int64_t res = 0LL;
    int64_t i = 0LL;
    while (i < strlen(s)) {
    char c = (s)[i];
    if ((c >= ((char)(48LL))) && (c <= ((char)(57LL)))) {
    res = ((res * 10LL) + (((int64_t)(c)) - 48LL));
}
    i = (i + 1LL);
}
    return res;
}
const char* CodegenBuilder_cgb_clean_type_for_mangling(CodegenBuilder* self, const char* s) {
    const char* result = "";
    int64_t i = 0LL;
    while (i < strlen(s)) {
    char c = (s)[i];
    if (c == ((char)(42LL))) {
    result = concatAlloc(result, "ptr");
} else if (c == ((char)(38LL))) {
    result = concatAlloc(result, "ref");
} else if (c == ((char)(32LL))) {
    result = concatAlloc(result, "_");
} else if (((((((c == ((char)(60LL))) || (c == ((char)(62LL)))) || (c == ((char)(44LL)))) || (c == ((char)(33LL)))) || (c == ((char)(63LL)))) || (c == ((char)(40LL)))) || (c == ((char)(41LL)))) {
    result = concatAlloc(result, "_");
} else {
    result = concatAlloc(result, cgb_char_to_str(c));
}
    i = (i + 1LL);
}
    return result;
}
void CodegenBuilder_monomorphize_struct(CodegenBuilder* self, const char* struct_name, const char* concrete_name, ArrayList_Str* type_args) {
    const char* stmt_idx_str = cgb_map_get(&(self->generic_struct_decls), struct_name);
    if (strlen(stmt_idx_str) == 0LL) {
    return;
}
    int64_t stmt_idx = CodegenBuilder_str_to_int_safe(self, stmt_idx_str);
    if (stmt_idx < 0LL) {
    return;
}
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, stmt_idx);
    StrBuf_append(&(self->struct_decls), concatAlloc(concatAlloc(concatAlloc(concatAlloc("typedef struct ", concrete_name), " "), concrete_name), ";\n"));
    StrBuf_append(&(self->struct_decls), concatAlloc(concatAlloc("struct ", concrete_name), " {\n"));
    int64_t fi = 0LL;
    while (fi < ArrayList_StructField_length(&(stmt.struct_fields))) {
    StructField f = ArrayList_StructField_get(&(stmt.struct_fields), fi);
    const char* resolved_ftype = CodegenBuilder_substitute_type_params(self, f.ftype, &(stmt.struct_type_params), type_args);
    StrBuf_append(&(self->struct_decls), concatAlloc(concatAlloc(concatAlloc(concatAlloc("    ", CodegenBuilder_map_type(self, resolved_ftype)), " "), f.name), ";\n"));
    fi = (fi + 1LL);
}
    StrBuf_append(&(self->struct_decls), "};\n");
    CodegenBuilder_monomorphize_methods_for_struct(self, struct_name, concrete_name, &(stmt.struct_type_params), type_args);
}
void CodegenBuilder_monomorphize_methods_for_struct(CodegenBuilder* self, const char* base_struct_name, const char* concrete_name, ArrayList_Str* param_names, ArrayList_Str* type_args) {
    int64_t si = 0LL;
    while (si < ArrayList_StmtNode_length(self->stmt_pool)) {
    StmtNode s = ArrayList_StmtNode_get(self->stmt_pool, si);
    if ((s.kind == StmtKind_sk_impl_block) && (strcmp(s.impl_struct_name, base_struct_name) == 0)) {
    int64_t j = 0LL;
    while (j < ArrayList_Int_length(&(s.impl_methods))) {
    int64_t m_idx = ArrayList_Int_get(&(s.impl_methods), j);
    StmtNode m_node = ArrayList_StmtNode_get(self->stmt_pool, m_idx);
    const char* method_name = m_node.func_name;
    bool is_init = ((((strcmp(method_name, "init") == 0) || (strcmp(m_node.func_return_type, base_struct_name) == 0)) || (strcmp(m_node.func_return_type, concatAlloc("*", base_struct_name)) == 0)) || (strcmp(m_node.func_return_type, concatAlloc("&", base_struct_name)) == 0));
    const char* mangled_fn = concatAlloc(concatAlloc(concrete_name, "_"), method_name);
    const char* ret = m_node.func_return_type;
    if (ArrayList_Str_length(param_names) > 0LL) {
    ret = CodegenBuilder_substitute_type_params(self, ret, param_names, type_args);
}
    if (is_init) {
    ret = concrete_name;
}
    const char* ret_type = CodegenBuilder_map_type(self, ret);
    const char* params_str = "";
    if (!is_init) {
    params_str = concatAlloc(concrete_name, "* self");
}
    int64_t pi = 0LL;
    while (pi < ArrayList_Param_length(&(m_node.func_params))) {
    Param p = ArrayList_Param_get(&(m_node.func_params), pi);
    bool is_self = false;
    {
    if (strcmp(p.name, "self") == 0LL) {
    is_self = true;
}
}
    if (!is_self) {
    if (strlen(params_str) > 0LL) {
    params_str = concatAlloc(params_str, ", ");
}
    const char* ptype = p.ptype;
    if (ArrayList_Str_length(param_names) > 0LL) {
    ptype = CodegenBuilder_substitute_type_params(self, ptype, param_names, type_args);
}
    params_str = concatAlloc(concatAlloc(concatAlloc(params_str, CodegenBuilder_map_type(self, ptype)), " "), p.name);
}
    pi = (pi + 1LL);
}
    if (strlen(params_str) == 0LL) {
    params_str = "void";
}
    cgb_map_put(&(self->func_types), mangled_fn, ret);
    ArrayList_Str mono_params = ArrayList_Str_init(self->allocator);
    if (!is_init) {
    ArrayList_Str_push(&(mono_params), concatAlloc(concrete_name, "* self"));
}
    int64_t pi_mono = 0LL;
    while (pi_mono < ArrayList_Param_length(&(m_node.func_params))) {
    Param p = ArrayList_Param_get(&(m_node.func_params), pi_mono);
    bool is_self2 = false;
    {
    if (strcmp(p.name, "self") == 0LL) {
    is_self2 = true;
}
}
    if (!is_self2) {
    const char* ptype = p.ptype;
    if (ArrayList_Str_length(param_names) > 0LL) {
    ptype = CodegenBuilder_substitute_type_params(self, ptype, param_names, type_args);
}
    ArrayList_Str_push(&(mono_params), concatAlloc(concatAlloc(CodegenBuilder_map_type(self, ptype), " "), p.name));
}
    pi_mono = (pi_mono + 1LL);
}
    if (ArrayList_Str_length(&(mono_params)) == 0LL) {
    ArrayList_Str_push(&(mono_params), "void");
}
    CDeclNode mono_decl = cdecl_new_func(mangled_fn, ret_type, mono_params, false, false);
    CCodeBuilder local_builder = (CCodeBuilder){ .alloc = self->allocator, .lines = ArrayList_Str_init(self->allocator), .indent_level = 0LL };
    local_builder = CCodeBuilder_init(self->allocator);
    CPrinter printer = (CPrinter){ .builder = &(local_builder), .expr_pool = &(self->c_exprs), .stmt_pool = &(self->c_stmts) };
    CPrinter_print_decl(&(printer), mono_decl);
    StrBuf_append(&(self->func_decls), CCodeBuilder_to_str(&(local_builder)));
    int64_t body_idx = m_node.func_body;
    if (body_idx >= 0LL) {
    StmtNode body_stmt = ArrayList_StmtNode_get(self->stmt_pool, body_idx);
    if (body_stmt.kind == StmtKind_sk_block) {
    ArrayList_CgbMapEntry old_type_map = self->current_type_map;
    self->current_type_map = ArrayList_CgbMapEntry_init(self->allocator);
    int64_t tpi = 0LL;
    while (tpi < ArrayList_Str_length(param_names)) {
    cgb_map_put(&(self->current_type_map), ArrayList_Str_get(param_names, tpi), ArrayList_Str_get(type_args, tpi));
    tpi = (tpi + 1LL);
}
    ArrayList_CgbMapEntry saved_var_types = self->var_types;
    self->var_types = ArrayList_CgbMapEntry_init(self->allocator);
    ArrayList_Int saved_block_stack = self->block_stack;
    self->block_stack = ArrayList_Int_init(self->allocator);
    if (is_init) {
    cgb_map_put(&(self->var_types), "self", concrete_name);
} else {
    cgb_map_put(&(self->var_types), "self", concatAlloc("*", concrete_name));
}
    int64_t pi2 = 0LL;
    while (pi2 < ArrayList_Param_length(&(m_node.func_params))) {
    Param p2 = ArrayList_Param_get(&(m_node.func_params), pi2);
    bool is_self2 = false;
    {
    if (strcmp(p2.name, "self") == 0LL) {
    is_self2 = true;
}
}
    if (!is_self2) {
    const char* ptype = p2.ptype;
    if (ArrayList_Str_length(param_names) > 0LL) {
    ptype = CodegenBuilder_substitute_type_params(self, ptype, param_names, type_args);
}
    cgb_map_put(&(self->var_types), p2.name, ptype);
}
    pi2 = (pi2 + 1LL);
}
    const char* saved_func_name = self->cur_func_name;
    const char* saved_return_type = self->cur_return_type;
    bool saved_method_is_init = self->cur_method_is_init;
    self->cur_func_name = mangled_fn;
    self->cur_return_type = ret;
    self->cur_method_is_init = is_init;
    CCodeBuilder saved_builder = self->builder;
    self->builder = CCodeBuilder_init(self->allocator);
    CCodeBuilder_emit_line(&(self->builder), concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(ret_type, " "), mangled_fn), "("), params_str), ")"));
    CodegenBuilder_gen_stmt(self, body_idx);
    const char* body_str = CCodeBuilder_to_str(&(self->builder));
    if (is_init) {
    int64_t brace_pos = 0LL;
    while (brace_pos < strlen(body_str)) {
    if ((body_str)[brace_pos] == ((char)(123LL))) {
    break;
}
    brace_pos = (brace_pos + 1LL);
}
    const char* header = __kai_str_sub(body_str, 0LL, brace_pos);
    const char* raw_body = __kai_str_sub(body_str, brace_pos, strlen(body_str));
    body_str = concatAlloc(header, CodegenBuilder_add_init_return(self, raw_body, concrete_name));
}
    StrBuf_append(&(self->monomorphized_bodies), body_str);
    self->builder = saved_builder;
    self->cur_func_name = saved_func_name;
    self->cur_return_type = saved_return_type;
    self->cur_method_is_init = saved_method_is_init;
    self->current_type_map = old_type_map;
    self->var_types = saved_var_types;
    self->block_stack = saved_block_stack;
}
}
    j = (j + 1LL);
}
}
    si = (si + 1LL);
}
}
void CodegenBuilder_monomorphize_enum(CodegenBuilder* self, const char* enum_name, const char* concrete_name, ArrayList_Str* type_args) {
    const char* stmt_idx_str = cgb_map_get(&(self->generic_enum_decls), enum_name);
    if (strlen(stmt_idx_str) == 0LL) {
    return;
}
    int64_t stmt_idx = CodegenBuilder_str_to_int_safe(self, stmt_idx_str);
    if (stmt_idx < 0LL) {
    return;
}
}
int64_t CodegenBuilder_str_to_int_safe(CodegenBuilder* self, const char* s) {
    int64_t result = 0LL;
    int64_t i = 0LL;
    bool neg = false;
    if ((strlen(s) > 0LL) && ((s)[0LL] == ((char)(45LL)))) {
    neg = true;
    i = 1LL;
}
    while (i < strlen(s)) {
    char c = (s)[i];
    if ((c >= ((char)(48LL))) && (c <= ((char)(57LL)))) {
    result = ((result * 10LL) + (((int64_t)(c)) - 48LL));
} else {
    return (-1LL);
}
    i = (i + 1LL);
}
    if (neg) {
    result = (-result);
}
    return result;
}
const char* CodegenBuilder_substitute_type_params(CodegenBuilder* self, const char* type_name, ArrayList_Str* param_names, ArrayList_Str* arg_types) {
    if (ArrayList_Str_length(param_names) == 0LL) {
    return type_name;
}
    const char* result = type_name;
    int64_t i = 0LL;
    while (i < ArrayList_Str_length(param_names)) {
    const char* pn = ArrayList_Str_get(param_names, i);
    const char* arg = ArrayList_Str_get(arg_types, i);
    {
    if (strstr(result, pn) != (char*)(unsigned long long)(0LL)) {
    int64_t ri = 0LL;
    const char* new_res = "";
    int64_t pn_len = strlen(pn);
    while (ri < strlen(result)) {
    bool matches = true;
    int64_t mi = 0LL;
    while (mi < pn_len) {
    if ((ri + mi) >= strlen(result)) {
    matches = false;
    break;
}
    if ((result)[(ri + mi)] != (pn)[mi]) {
    matches = false;
    break;
}
    mi = (mi + 1LL);
}
    if (matches) {
    new_res = concatAlloc(new_res, arg);
    ri = (ri + pn_len);
} else {
    new_res = concatAlloc(new_res, cgb_char_to_str((result)[ri]));
    ri = (ri + 1LL);
}
}
    result = new_res;
}
}
    i = (i + 1LL);
}
    return result;
}
const char* CodegenBuilder_extract_first_type_arg(CodegenBuilder* self, const char* type_name) {
    int64_t start = (-1LL);
    int64_t end = (-1LL);
    int64_t i = 0LL;
    while (i < strlen(type_name)) {
    char c = (type_name)[i];
    if (c == ((char)(60LL))) {
    start = (i + 1LL);
} else if (c == ((char)(44LL))) {
    end = i;
    break;
} else if (c == ((char)(62LL))) {
    end = i;
    break;
}
    i = (i + 1LL);
}
    if ((start >= 0LL) && (end >= 0LL)) {
    return __kai_str_sub(type_name, start, end);
}
    return "Int";
}
const char* CodegenBuilder_strip_module_prefix(CodegenBuilder* self, const char* name) {
    int64_t last_dot = (-1LL);
    int64_t i = 0LL;
    while (i < strlen(name)) {
    if ((name)[i] == ((char)(46LL))) {
    last_dot = i;
}
    i = (i + 1LL);
}
    if (last_dot >= 0LL) {
    return __kai_str_sub(name, (last_dot + 1LL), strlen(name));
}
    return name;
}
const char* CodegenBuilder_map_type(CodegenBuilder* self, const char* resolved_type) {
    const char* orig = CodegenBuilder_strip_module_prefix(self, resolved_type);
    if (strlen(orig) == 0LL) {
    return "void";
}
    if (ArrayList_CgbMapEntry_length(&(self->current_type_map)) > 0LL) {
    int64_t tmi = 0LL;
    while (tmi < ArrayList_CgbMapEntry_length(&(self->current_type_map))) {
    CgbMapEntry entry = ArrayList_CgbMapEntry_get(&(self->current_type_map), tmi);
    if (strcmp(entry.key, orig) == 0) {
    return CodegenBuilder_map_type(self, entry.value);
}
    tmi = (tmi + 1LL);
}
}
    if ((strlen(orig) > 0LL) && ((orig)[0LL] == ((char)(40LL)))) {
    const char* clean_name = concatAlloc("Tuple_", CodegenBuilder_cgb_clean_type_for_mangling(self, orig));
    if (cgb_strlist_find(&(self->monomorphized_types), clean_name) < 0LL) {
    ArrayList_Str_push(&(self->monomorphized_types), clean_name);
    const char* inner_types = __kai_str_sub(orig, 1LL, (strlen(orig) - 1LL));
    ArrayList_Str types_list = ArrayList_Str_init(self->allocator);
    int64_t start = 0LL;
    int64_t i = 0LL;
    while (i < strlen(inner_types)) {
    if ((inner_types)[i] == ((char)(44LL))) {
    int64_t ts_start = start;
    while ((ts_start < i) && ((inner_types)[ts_start] == ((char)(32LL)))) {
    ts_start = (ts_start + 1LL);
}
    int64_t ts_end = i;
    while ((ts_end > ts_start) && ((inner_types)[(ts_end - 1LL)] == ((char)(32LL)))) {
    ts_end = (ts_end - 1LL);
}
    ArrayList_Str_push(&(types_list), __kai_str_sub(inner_types, ts_start, ts_end));
    start = (i + 1LL);
}
    i = (i + 1LL);
}
    int64_t ts_start = start;
    while ((ts_start < strlen(inner_types)) && ((inner_types)[ts_start] == ((char)(32LL)))) {
    ts_start = (ts_start + 1LL);
}
    int64_t ts_end = strlen(inner_types);
    while ((ts_end > ts_start) && ((inner_types)[(ts_end - 1LL)] == ((char)(32LL)))) {
    ts_end = (ts_end - 1LL);
}
    ArrayList_Str_push(&(types_list), __kai_str_sub(inner_types, ts_start, ts_end));
    StrBuf_append(&(self->struct_decls), concatAlloc(concatAlloc(concatAlloc(concatAlloc("typedef struct ", clean_name), " "), clean_name), ";\n"));
    StrBuf_append(&(self->struct_decls), concatAlloc(concatAlloc("struct ", clean_name), " {\n"));
    int64_t ti = 0LL;
    while (ti < ArrayList_Str_length(&(types_list))) {
    StrBuf_append(&(self->struct_decls), concatAlloc(concatAlloc(concatAlloc(concatAlloc("    ", CodegenBuilder_map_type(self, ArrayList_Str_get(&(types_list), ti))), " f"), cgb_int_to_str(ti)), ";\n"));
    ti = (ti + 1LL);
}
    StrBuf_append(&(self->struct_decls), "};\n");
}
    return clean_name;
}
    if ((strcmp(orig, "Int") == 0) || (strcmp(orig, "i64") == 0)) {
    return "int64_t";
}
    if (strcmp(orig, "i8") == 0) {
    return "int8_t";
}
    if (strcmp(orig, "i16") == 0) {
    return "int16_t";
}
    if (strcmp(orig, "i32") == 0) {
    return "int32_t";
}
    if (strcmp(orig, "u8") == 0) {
    return "uint8_t";
}
    if (strcmp(orig, "u16") == 0) {
    return "uint16_t";
}
    if (strcmp(orig, "u32") == 0) {
    return "uint32_t";
}
    if (strcmp(orig, "u64") == 0) {
    return "uint64_t";
}
    if (strcmp(orig, "usize") == 0) {
    return "size_t";
}
    if (strcmp(orig, "isize") == 0) {
    return "intptr_t";
}
    if (strcmp(orig, "Void") == 0) {
    return "void";
}
    if (strcmp(orig, "Bool") == 0) {
    return "bool";
}
    if (strcmp(orig, "Char") == 0) {
    return "char";
}
    if (strcmp(orig, "Float") == 0) {
    return "double";
}
    if (strcmp(orig, "Str") == 0) {
    return "const char*";
}
    if (strcmp(orig, "NoneType") == 0) {
    return "void";
}
    if (strcmp(orig, "TokenValue") == 0) {
    return "TokenValue";
}
    if (strcmp(orig, "TokenType") == 0) {
    return "TokenType";
}
    int64_t ptr_count = 0LL;
    const char* inner = orig;
    bool changed = true;
    while (changed) {
    changed = false;
    if ((strlen(inner) > 0LL) && ((inner)[0LL] == ((char)(42LL)))) {
    ptr_count = (ptr_count + 1LL);
    inner = __kai_str_sub(inner, 1LL, strlen(inner));
    changed = true;
} else if ((strlen(inner) > 0LL) && ((inner)[0LL] == ((char)(38LL)))) {
    ptr_count = (ptr_count + 1LL);
    inner = __kai_str_sub(inner, 1LL, strlen(inner));
    changed = true;
} else if ((strlen(inner) >= 2LL) && (strcmp(__kai_str_sub(inner, 0LL, 2LL), "[]") == 0)) {
    ptr_count = (ptr_count + 1LL);
    inner = __kai_str_sub(inner, 2LL, strlen(inner));
    changed = true;
} else if ((strlen(inner) > 5LL) && (strcmp(__kai_str_sub(inner, 0LL, 5LL), "*mut ") == 0)) {
    ptr_count = (ptr_count + 1LL);
    inner = __kai_str_sub(inner, 5LL, strlen(inner));
    changed = true;
}
}
    const char* base = inner;
    if ((strlen(base) > 0LL) && ((base)[0LL] == ((char)(40LL)))) {
    const char* clean_name = concatAlloc("Tuple_", CodegenBuilder_cgb_clean_type_for_mangling(self, base));
    if (cgb_strlist_find(&(self->monomorphized_types), clean_name) < 0LL) {
    ArrayList_Str_push(&(self->monomorphized_types), clean_name);
    const char* inner_types = __kai_str_sub(base, 1LL, (strlen(base) - 1LL));
    ArrayList_Str types_list = ArrayList_Str_init(self->allocator);
    int64_t start = 0LL;
    int64_t i = 0LL;
    while (i < strlen(inner_types)) {
    if ((inner_types)[i] == ((char)(44LL))) {
    int64_t ts_start = start;
    while ((ts_start < i) && ((inner_types)[ts_start] == ((char)(32LL)))) {
    ts_start = (ts_start + 1LL);
}
    int64_t ts_end = i;
    while ((ts_end > ts_start) && ((inner_types)[(ts_end - 1LL)] == ((char)(32LL)))) {
    ts_end = (ts_end - 1LL);
}
    ArrayList_Str_push(&(types_list), __kai_str_sub(inner_types, ts_start, ts_end));
    start = (i + 1LL);
}
    i = (i + 1LL);
}
    int64_t ts_start = start;
    while ((ts_start < strlen(inner_types)) && ((inner_types)[ts_start] == ((char)(32LL)))) {
    ts_start = (ts_start + 1LL);
}
    int64_t ts_end = strlen(inner_types);
    while ((ts_end > ts_start) && ((inner_types)[(ts_end - 1LL)] == ((char)(32LL)))) {
    ts_end = (ts_end - 1LL);
}
    ArrayList_Str_push(&(types_list), __kai_str_sub(inner_types, ts_start, ts_end));
    StrBuf_append(&(self->struct_decls), concatAlloc(concatAlloc(concatAlloc(concatAlloc("typedef struct ", clean_name), " "), clean_name), ";\n"));
    StrBuf_append(&(self->struct_decls), concatAlloc(concatAlloc("struct ", clean_name), " {\n"));
    int64_t ti = 0LL;
    while (ti < ArrayList_Str_length(&(types_list))) {
    StrBuf_append(&(self->struct_decls), concatAlloc(concatAlloc(concatAlloc(concatAlloc("    ", CodegenBuilder_map_type(self, ArrayList_Str_get(&(types_list), ti))), " f"), cgb_int_to_str(ti)), ";\n"));
    ti = (ti + 1LL);
}
    StrBuf_append(&(self->struct_decls), "};\n");
}
    base = clean_name;
}
    if (ArrayList_CgbMapEntry_length(&(self->current_type_map)) > 0LL) {
    int64_t tmi2 = 0LL;
    while (tmi2 < ArrayList_CgbMapEntry_length(&(self->current_type_map))) {
    CgbMapEntry entry = ArrayList_CgbMapEntry_get(&(self->current_type_map), tmi2);
    if (strcmp(entry.key, base) == 0) {
    if (ptr_count > 0LL) {
    const char* mapped = CodegenBuilder_map_type(self, entry.value);
    int64_t pi2 = 0LL;
    while (pi2 < ptr_count) {
    mapped = concatAlloc(mapped, "*");
    pi2 = (pi2 + 1LL);
}
    return mapped;
}
    return CodegenBuilder_map_type(self, entry.value);
}
    tmi2 = (tmi2 + 1LL);
}
}
    if ((strcmp(base, "Int") == 0) || (strcmp(base, "i64") == 0)) {
    base = "int64_t";
} else if (strcmp(base, "i8") == 0) {
    base = "int8_t";
} else if (strcmp(base, "i16") == 0) {
    base = "int16_t";
} else if (strcmp(base, "i32") == 0) {
    base = "int32_t";
} else if (strcmp(base, "u8") == 0) {
    base = "uint8_t";
} else if (strcmp(base, "u16") == 0) {
    base = "uint16_t";
} else if (strcmp(base, "u32") == 0) {
    base = "uint32_t";
} else if (strcmp(base, "u64") == 0) {
    base = "uint64_t";
} else if (strcmp(base, "usize") == 0) {
    base = "size_t";
} else if (strcmp(base, "isize") == 0) {
    base = "intptr_t";
} else if (strcmp(base, "Void") == 0) {
    base = "void";
} else if (strcmp(base, "Bool") == 0) {
    base = "bool";
} else if (strcmp(base, "Char") == 0) {
    base = "char";
} else if (strcmp(base, "Float") == 0) {
    base = "double";
} else if (strcmp(base, "Str") == 0) {
    base = "const char*";
} else if (strcmp(base, "NoneType") == 0) {
    base = "void";
} else if (strcmp(base, "TokenValue") == 0) {
    base = "TokenValue";
} else if (strcmp(base, "TokenType") == 0) {
    base = "TokenType";
} else if (CodegenBuilder_str_contains(self, base, ((char)(33LL)))) {
    int64_t excl_pos = CodegenBuilder_str_find(self, base, ((char)(33LL)));
    const char* val_type = __kai_str_sub(base, 0LL, excl_pos);
    const char* err_type = __kai_str_sub(base, (excl_pos + 1LL), strlen(base));
    const char* clean_val = CodegenBuilder_cgb_clean_type_for_mangling(self, val_type);
    const char* clean_err = CodegenBuilder_cgb_clean_type_for_mangling(self, err_type);
    const char* concrete_name = concatAlloc(concatAlloc(concatAlloc("Result_", clean_val), "_"), clean_err);
    if (cgb_strlist_find(&(self->monomorphized_types), concrete_name) < 0LL) {
    ArrayList_Str_push(&(self->monomorphized_types), concrete_name);
    StrBuf_append(&(self->struct_decls), concatAlloc(concatAlloc(concatAlloc(concatAlloc("typedef struct ", concrete_name), " "), concrete_name), ";\n"));
    StrBuf_append(&(self->struct_decls), concatAlloc(concatAlloc("struct ", concrete_name), " {\n"));
    StrBuf_append(&(self->struct_decls), "    int64_t tag;\n");
    if (strcmp(val_type, "Void") != 0) {
    StrBuf_append(&(self->struct_decls), concatAlloc(concatAlloc("    ", CodegenBuilder_map_type(self, val_type)), " value;\n"));
}
    StrBuf_append(&(self->struct_decls), "};\n");
}
    base = concrete_name;
} else if (CodegenBuilder_str_contains(self, base, ((char)(63LL)))) {
    int64_t q_pos = CodegenBuilder_str_find(self, base, ((char)(63LL)));
    if (q_pos == 0LL) {
    const char* val_type = __kai_str_sub(base, 1LL, strlen(base));
    if (CodegenBuilder_is_pointer_type(self, val_type)) {
    base = CodegenBuilder_map_type(self, val_type);
} else {
    const char* clean_val2 = CodegenBuilder_cgb_clean_type_for_mangling(self, val_type);
    const char* concrete_name = concatAlloc("Optional_", clean_val2);
    if (cgb_strlist_find(&(self->monomorphized_types), concrete_name) < 0LL) {
    ArrayList_Str_push(&(self->monomorphized_types), concrete_name);
    StrBuf_append(&(self->struct_decls), concatAlloc(concatAlloc(concatAlloc(concatAlloc("typedef struct ", concrete_name), " "), concrete_name), ";\n"));
    StrBuf_append(&(self->struct_decls), concatAlloc(concatAlloc("struct ", concrete_name), " {\n"));
    StrBuf_append(&(self->struct_decls), "    bool has_value;\n");
    StrBuf_append(&(self->struct_decls), concatAlloc(concatAlloc("    ", CodegenBuilder_map_type(self, val_type)), " value;\n"));
    StrBuf_append(&(self->struct_decls), "};\n");
}
    base = concrete_name;
}
}
} else if (CodegenBuilder_str_contains(self, base, ((char)(60LL)))) {
    int64_t lt_pos = CodegenBuilder_str_find(self, base, ((char)(60LL)));
    const char* base_name = __kai_str_sub(base, 0LL, lt_pos);
    const char* args_str2 = __kai_str_sub(base, (lt_pos + 1LL), (strlen(base) - 1LL));
    const char* concrete_name = base_name;
    ArrayList_Str args_list = ArrayList_Str_init(self->allocator);
    int64_t start2 = 0LL;
    while (start2 < strlen(args_str2)) {
    while ((start2 < strlen(args_str2)) && ((args_str2)[start2] == ((char)(32LL)))) {
    start2 = (start2 + 1LL);
}
    if (start2 >= strlen(args_str2)) {
    break;
}
    int64_t end2 = start2;
    while ((end2 < strlen(args_str2)) && ((args_str2)[end2] != ((char)(44LL)))) {
    end2 = (end2 + 1LL);
}
    const char* arg = __kai_str_sub(args_str2, start2, end2);
    const char* clean_arg = CodegenBuilder_cgb_clean_type_for_mangling(self, arg);
    ArrayList_Str_push(&(args_list), arg);
    if (strlen(concrete_name) > 0LL) {
    concrete_name = concatAlloc(concrete_name, "_");
}
    concrete_name = concatAlloc(concrete_name, clean_arg);
    start2 = (end2 + 1LL);
}
    const char* struct_idx_str = cgb_map_get(&(self->generic_struct_decls), base_name);
    if (strlen(struct_idx_str) > 0LL) {
    if (cgb_strlist_find(&(self->monomorphized_types), concrete_name) < 0LL) {
    ArrayList_Str_push(&(self->monomorphized_types), concrete_name);
    CodegenBuilder_monomorphize_struct(self, base_name, concrete_name, &(args_list));
}
    base = concrete_name;
} else {
    const char* enum_idx_str = cgb_map_get(&(self->generic_enum_decls), base_name);
    if (strlen(enum_idx_str) > 0LL) {
    if (cgb_strlist_find(&(self->monomorphized_types), concrete_name) < 0LL) {
    ArrayList_Str_push(&(self->monomorphized_types), concrete_name);
    CodegenBuilder_monomorphize_enum(self, base_name, concrete_name, &(args_list));
}
    base = concrete_name;
} else {
    base = concrete_name;
}
}
}
    const char* result = base;
    int64_t pi = 0LL;
    while (pi < ptr_count) {
    result = concatAlloc(result, "*");
    pi = (pi + 1LL);
}
    return result;
}
bool CodegenBuilder_str_contains(CodegenBuilder* self, const char* s, char target) {
    int64_t i = 0LL;
    while (i < strlen(s)) {
    if ((s)[i] == target) {
    return true;
}
    i = (i + 1LL);
}
    return false;
}
int64_t CodegenBuilder_str_find(CodegenBuilder* self, const char* s, char target) {
    int64_t i = 0LL;
    while (i < strlen(s)) {
    if ((s)[i] == target) {
    return i;
}
    i = (i + 1LL);
}
    return (-1LL);
}
bool CodegenBuilder_is_fully_parenthesized(CodegenBuilder* self, const char* s) {
    if (strlen(s) < 2LL) {
    return false;
}
    if (((s)[0LL] != ((char)(40LL))) || ((s)[(strlen(s) - 1LL)] != ((char)(41LL)))) {
    return false;
}
    int64_t depth = 0LL;
    int64_t i = 0LL;
    while (i < (strlen(s) - 1LL)) {
    char c = (s)[i];
    if (c == ((char)(39LL))) {
    i = (i + 1LL);
    while ((i < (strlen(s) - 1LL)) && ((s)[i] != ((char)(39LL)))) {
    if ((s)[i] == ((char)(92LL))) {
    i = (i + 1LL);
}
    i = (i + 1LL);
}
} else if (c == ((char)(34LL))) {
    i = (i + 1LL);
    while ((i < (strlen(s) - 1LL)) && ((s)[i] != ((char)(34LL)))) {
    if ((s)[i] == ((char)(92LL))) {
    i = (i + 1LL);
}
    i = (i + 1LL);
}
} else if (c == ((char)(40LL))) {
    depth = (depth + 1LL);
} else if (c == ((char)(41LL))) {
    depth = (depth - 1LL);
}
    if (depth == 0LL) {
    return false;
}
    i = (i + 1LL);
}
    return true;
}
const char* CodegenBuilder_format_cond(CodegenBuilder* self, const char* cond) {
    if (CodegenBuilder_is_fully_parenthesized(self, cond)) {
    return cond;
}
    return concatAlloc(concatAlloc("(", cond), ")");
}
const char* CodegenBuilder_cgb_replace_format_specifiers(CodegenBuilder* self, const char* s) {
    const char* result = "";
    int64_t i = 0LL;
    while (i < strlen(s)) {
    if ((((i < (strlen(s) - 2LL)) && ((s)[i] == ((char)(37LL)))) && ((s)[(i + 1LL)] == ((char)(108LL)))) && ((s)[(i + 2LL)] == ((char)(100LL)))) {
    result = concatAlloc(result, "%\" PRId64 \"");
    i = (i + 3LL);
} else {
    result = concatAlloc(result, cgb_char_to_str((s)[i]));
    i = (i + 1LL);
}
}
    return result;
}
bool CodegenBuilder_is_standard_c_func(CodegenBuilder* self, const char* name) {
    int64_t l = strlen(name);
    if (l >= 4LL) {
    const char* sub4 = __kai_str_sub(name, 0LL, 4LL);
    bool is_llvm = false;
    {
    if (strcmp(sub4, "LLVM") == 0LL) {
    is_llvm = true;
}
}
    if (is_llvm) {
    return true;
}
}
    if (l >= 8LL) {
    const char* sub8 = __kai_str_sub(name, 0LL, 8LL);
    bool is_kai_llvm = false;
    {
    if (strcmp(sub8, "kai_LLVM") == 0LL) {
    is_kai_llvm = true;
}
}
    if (is_kai_llvm) {
    return true;
}
}
    if (l >= 13LL) {
    const char* sub13 = __kai_str_sub(name, 0LL, 13LL);
    bool is_kai_func = false;
    {
    if (strcmp(sub13, "kai_func_type") == 0LL) {
    is_kai_func = true;
}
}
    if (is_kai_func) {
    return true;
}
}
    if (l >= 14LL) {
    const char* sub14 = __kai_str_sub(name, 0LL, 14LL);
    bool is_kai_build = false;
    {
    if (strcmp(sub14, "kai_build_call") == 0LL) {
    is_kai_build = true;
}
}
    if (is_kai_build) {
    return true;
}
}
    if (strcmp(name, "atoll") == 0) {
    return true;
}
    if (strcmp(name, "malloc") == 0) {
    return true;
}
    if (strcmp(name, "free") == 0) {
    return true;
}
    if (strcmp(name, "realloc") == 0) {
    return true;
}
    if (strcmp(name, "calloc") == 0) {
    return true;
}
    if (strcmp(name, "isdigit") == 0) {
    return true;
}
    if (strcmp(name, "isalpha") == 0) {
    return true;
}
    if (strcmp(name, "isalnum") == 0) {
    return true;
}
    if (strcmp(name, "isspace") == 0) {
    return true;
}
    if (strcmp(name, "toupper") == 0) {
    return true;
}
    if (strcmp(name, "tolower") == 0) {
    return true;
}
    if (strcmp(name, "strlen") == 0) {
    return true;
}
    if (strcmp(name, "exit") == 0) {
    return true;
}
    if (strcmp(name, "system") == 0) {
    return true;
}
    if (strcmp(name, "fopen") == 0) {
    return true;
}
    if (strcmp(name, "fread") == 0) {
    return true;
}
    if (strcmp(name, "fwrite") == 0) {
    return true;
}
    if (strcmp(name, "fclose") == 0) {
    return true;
}
    if (strcmp(name, "fseek") == 0) {
    return true;
}
    if (strcmp(name, "ftell") == 0) {
    return true;
}
    if (strcmp(name, "rewind") == 0) {
    return true;
}
    if (strcmp(name, "strcmp") == 0) {
    return true;
}
    if (strcmp(name, "printf") == 0) {
    return true;
}
    if (strcmp(name, "fprintf") == 0) {
    return true;
}
    if (strcmp(name, "sprintf") == 0) {
    return true;
}
    if (strcmp(name, "snprintf") == 0) {
    return true;
}
    if (strcmp(name, "sqrt") == 0) {
    return true;
}
    return false;
}
int64_t CodegenBuilder_push_expr(CodegenBuilder* self, CExprNode node) {
    int64_t idx = ArrayList_CExprNode_length(&(self->c_exprs));
    ArrayList_CExprNode_push(&(self->c_exprs), node);
    return idx;
}
const char* CodegenBuilder_gen_expr_str(CodegenBuilder* self, int64_t expr_idx) {
    int64_t c_idx = CodegenBuilder_gen_expr(self, expr_idx);
    if (c_idx < 0LL) {
    return "";
}
    CPrinter printer = (CPrinter){ .builder = &(self->builder), .expr_pool = &(self->c_exprs), .stmt_pool = &(self->c_stmts) };
    return CPrinter_print_expr(&(printer), c_idx);
}
const char* CodegenBuilder_expr_to_str(CodegenBuilder* self, int64_t c_idx) {
    if (c_idx < 0LL) {
    return "";
}
    CPrinter printer = (CPrinter){ .builder = &(self->builder), .expr_pool = &(self->c_exprs), .stmt_pool = &(self->c_stmts) };
    return CPrinter_print_expr(&(printer), c_idx);
}
const char* CodegenBuilder_gen_expr_with_expected_type(CodegenBuilder* self, int64_t expr_idx, const char* expected_type) {
    if (expr_idx < 0LL) {
    return "";
}
    ExprNode expr = ArrayList_ExprNode_get(self->expr_pool, expr_idx);
    const char* actual_type = CodegenBuilder_get_expr_type(self, expr_idx);
    if ((expr.kind == ExprKind_ek_literal) && (strcmp(expr.lit_vkind, "NONE") == 0)) {
    if ((strlen(expected_type) > 0LL) && ((expected_type)[0LL] == ((char)(63LL)))) {
    const char* val_type = __kai_str_sub(expected_type, 1LL, strlen(expected_type));
    if (CodegenBuilder_is_pointer_type(self, val_type)) {
    return "NULL";
}
    return concatAlloc(concatAlloc("(", CodegenBuilder_map_type(self, expected_type)), "){0}");
}
    return "NULL";
}
    const char* gen_val = CodegenBuilder_gen_expr_str(self, expr_idx);
    if ((strlen(actual_type) > 0LL) && ((actual_type)[0LL] == ((char)(42LL)))) {
    const char* pointer_target = __kai_str_sub(actual_type, 1LL, strlen(actual_type));
    if (strcmp(pointer_target, expected_type) == 0) {
    return concatAlloc("*", gen_val);
}
}
    if ((strlen(expected_type) > 0LL) && ((expected_type)[0LL] == ((char)(63LL)))) {
    const char* val_type = __kai_str_sub(expected_type, 1LL, strlen(expected_type));
    if ((!CodegenBuilder_is_pointer_type(self, val_type)) && (strcmp(actual_type, val_type) == 0)) {
    return concatAlloc(concatAlloc(concatAlloc(concatAlloc("(", CodegenBuilder_map_type(self, expected_type)), "){ .has_value = true, .value = "), gen_val), " }");
}
}
    int64_t excl_pos = (-1LL);
    int64_t ei = 0LL;
    while (ei < strlen(expected_type)) {
    if ((expected_type)[ei] == ((char)(33LL))) {
    excl_pos = ei;
}
    ei = (ei + 1LL);
}
    if (excl_pos >= 0LL) {
    const char* val_payload = __kai_str_sub(expected_type, 0LL, excl_pos);
    const char* mapped_type = CodegenBuilder_map_type(self, expected_type);
    bool actual_has_excl = false;
    int64_t aei = 0LL;
    while (aei < strlen(actual_type)) {
    if ((actual_type)[aei] == ((char)(33LL))) {
    actual_has_excl = true;
}
    aei = (aei + 1LL);
}
    if (actual_has_excl) {
    return gen_val;
}
    if ((strcmp(actual_type, "Void") == 0) && (strcmp(val_payload, "Void") != 0)) {
    return concatAlloc(concatAlloc(concatAlloc(concatAlloc("(", mapped_type), "){ .tag = "), gen_val), " }");
}
    if (strcmp(val_payload, "Void") == 0) {
    return concatAlloc(concatAlloc("(", mapped_type), "){ .tag = 0 }");
}
    return concatAlloc(concatAlloc(concatAlloc(concatAlloc("(", mapped_type), "){ .tag = 0, .value = "), gen_val), " }");
}
    return gen_val;
}
int64_t CodegenBuilder_gen_expr(CodegenBuilder* self, int64_t expr_idx) {
    if (expr_idx < 0LL) {
    return (-1LL);
}
    ExprNode expr = ArrayList_ExprNode_get(self->expr_pool, expr_idx);
    if (expr.kind == ExprKind_ek_literal) {
    const char* vkind = expr.lit_vkind;
    if (strcmp(vkind, "INT") == 0) {
    const char* val_str = "0";
    if (expr.lit_value.tag == TokenValue_tv_str_TAG) {
    int64_t v = expr.lit_value.payload.tv_str.v;

    val_str = StringPool_get(self->pool, v);
} else if (expr.lit_value.tag == TokenValue_tv_int_TAG) {
    int64_t v = expr.lit_value.payload.tv_int.v;

    val_str = cgb_int_to_str(v);
} else {
} 
    return CodegenBuilder_push_expr(self, cexpr_new_int(val_str));
}
    if (strcmp(vkind, "FLOAT") == 0) {
    const char* val_str = "0.0";
    if (expr.lit_value.tag == TokenValue_tv_str_TAG) {
    int64_t v = expr.lit_value.payload.tv_str.v;

    val_str = StringPool_get(self->pool, v);
} else {
} 
    return CodegenBuilder_push_expr(self, cexpr_new_float(val_str));
}
    if (strcmp(vkind, "STRING") == 0) {
    const char* val_str = "\"\"";
    if (expr.lit_value.tag == TokenValue_tv_str_TAG) {
    int64_t v = expr.lit_value.payload.tv_str.v;

    val_str = concatAlloc(concatAlloc("\"", CodegenBuilder_cgb_replace_format_specifiers(self, CodegenBuilder_escape_string(self, StringPool_get(self->pool, v)))), "\"");
} else {
} 
    return CodegenBuilder_push_expr(self, cexpr_new_str(val_str));
}
    if (strcmp(vkind, "BOOL") == 0) {
    bool bval = false;
    if (expr.lit_value.tag == TokenValue_tv_bool_TAG) {
    bool v = expr.lit_value.payload.tv_bool.v;

    bval = v;
} else {
} 
    return CodegenBuilder_push_expr(self, cexpr_new_bool(bval));
}
    if (strcmp(vkind, "CHAR") == 0) {
    const char* lit_str = "'\\0'";
    if (expr.lit_value.tag == TokenValue_tv_char_TAG) {
    char v = expr.lit_value.payload.tv_char.v;

    if (v == ((char)(10LL))) {
    lit_str = "'\\n'";
} else if (v == ((char)(13LL))) {
    lit_str = "'\\r'";
} else if (v == ((char)(9LL))) {
    lit_str = "'\\t'";
} else if (v == ((char)(92LL))) {
    lit_str = "'\\\\'";
} else if (v == ((char)(39LL))) {
    lit_str = "'\\''";
} else {
    lit_str = concatAlloc(concatAlloc("'", cgb_char_to_str(v)), "'");
}
} else {
} 
    return CodegenBuilder_push_expr(self, cexpr_new_char(lit_str));
}
    if (strcmp(vkind, "NONE") == 0) {
    return CodegenBuilder_push_expr(self, cexpr_new_ident("((void*)0)"));
}
    return CodegenBuilder_push_expr(self, cexpr_new_ident(""));
}
    if (expr.kind == ExprKind_ek_identifier) {
    return CodegenBuilder_push_expr(self, cexpr_new_ident(expr.ident_name));
}
    if (expr.kind == ExprKind_ek_binary_op) {
    const char* lhs_type = CodegenBuilder_get_expr_type(self, expr.binop_left);
    int64_t left_idx = CodegenBuilder_gen_expr(self, expr.binop_left);
    const char* op = expr.binop_op;
    int64_t right_idx = CodegenBuilder_gen_expr(self, expr.binop_right);
    const char* rhs_type = CodegenBuilder_get_expr_type(self, expr.binop_right);
    const char* left = CodegenBuilder_expr_to_str(self, left_idx);
    const char* right = CodegenBuilder_expr_to_str(self, right_idx);
    if ((strcmp(op, "==") == 0) || (strcmp(op, "!=") == 0)) {
    if (((strlen(lhs_type) > 0LL) && ((lhs_type)[0LL] == ((char)(63LL)))) && ((strcmp(right, "NULL") == 0) || (strcmp(right, "((void*)0)") == 0))) {
    const char* val_type = __kai_str_sub(lhs_type, 1LL, strlen(lhs_type));
    if (CodegenBuilder_is_pointer_type(self, val_type)) {
    return CodegenBuilder_push_expr(self, cexpr_new_ident(concatAlloc(concatAlloc(concatAlloc(concatAlloc("(", left), " "), op), " NULL)")));
}
    if (strcmp(op, "==") == 0) {
    return CodegenBuilder_push_expr(self, cexpr_new_ident(concatAlloc(concatAlloc("(!", left), ".has_value)")));
}
    return CodegenBuilder_push_expr(self, cexpr_new_ident(concatAlloc(concatAlloc("(", left), ".has_value)")));
}
    if (((strlen(rhs_type) > 0LL) && ((rhs_type)[0LL] == ((char)(63LL)))) && ((strcmp(left, "NULL") == 0) || (strcmp(left, "((void*)0)") == 0))) {
    const char* val_type = __kai_str_sub(rhs_type, 1LL, strlen(rhs_type));
    if (CodegenBuilder_is_pointer_type(self, val_type)) {
    return CodegenBuilder_push_expr(self, cexpr_new_ident(concatAlloc(concatAlloc(concatAlloc(concatAlloc("(NULL ", op), " "), right), ")")));
}
    if (strcmp(op, "==") == 0) {
    return CodegenBuilder_push_expr(self, cexpr_new_ident(concatAlloc(concatAlloc("(!", right), ".has_value)")));
}
    return CodegenBuilder_push_expr(self, cexpr_new_ident(concatAlloc(concatAlloc("(", right), ".has_value)")));
}
}
    if (strcmp(lhs_type, "Str") == 0) {
    if (strcmp(op, "+") == 0) {
    ArrayList_Int str_args = ArrayList_Int_init(self->allocator);
    ArrayList_Int_push(&(str_args), left_idx);
    ArrayList_Int_push(&(str_args), right_idx);
    return CodegenBuilder_push_expr(self, cexpr_new_call("concatAlloc", str_args));
}
    if (strcmp(op, "==") == 0) {
    ArrayList_Int cmp_args = ArrayList_Int_init(self->allocator);
    ArrayList_Int_push(&(cmp_args), left_idx);
    ArrayList_Int_push(&(cmp_args), right_idx);
    int64_t cmp_idx = CodegenBuilder_push_expr(self, cexpr_new_call("strcmp", cmp_args));
    int64_t zero_idx = CodegenBuilder_push_expr(self, cexpr_new_int("0"));
    return CodegenBuilder_push_expr(self, cexpr_new_binary(cmp_idx, "==", zero_idx));
}
    if (strcmp(op, "!=") == 0) {
    ArrayList_Int cmp_args = ArrayList_Int_init(self->allocator);
    ArrayList_Int_push(&(cmp_args), left_idx);
    ArrayList_Int_push(&(cmp_args), right_idx);
    int64_t cmp_idx = CodegenBuilder_push_expr(self, cexpr_new_call("strcmp", cmp_args));
    int64_t zero_idx = CodegenBuilder_push_expr(self, cexpr_new_int("0"));
    return CodegenBuilder_push_expr(self, cexpr_new_binary(cmp_idx, "!=", zero_idx));
}
}
    return CodegenBuilder_push_expr(self, cexpr_new_binary(left_idx, op, right_idx));
}
    if (expr.kind == ExprKind_ek_unary_op) {
    int64_t operand_idx = CodegenBuilder_gen_expr(self, expr.unop_operand);
    const char* op = expr.unop_op;
    if (((strcmp(op, "-") == 0) || (strcmp(op, "!") == 0)) || (strcmp(op, "~") == 0)) {
    return CodegenBuilder_push_expr(self, cexpr_new_unary(op, operand_idx, true));
}
    return operand_idx;
}
    if (expr.kind == ExprKind_ek_func_call) {
    const char* name = expr.func_name;
    if ((strcmp(name, "cast") == 0) || (strcmp(name, "as") == 0)) {
    const char* target_type = ArrayList_Str_get(&(expr.func_type_args), 0LL);
    if (strlen(target_type) > 0LL) {
    int64_t arg_idx = CodegenBuilder_gen_expr(self, ArrayList_Int_get(&(expr.func_args), 0LL));
    const char* ctype = CodegenBuilder_map_type(self, target_type);
    const char* src_type = CodegenBuilder_get_expr_type(self, ArrayList_Int_get(&(expr.func_args), 0LL));
    CType ct = ctype_new(ctype, 0LL, false, false);
    if (CodegenBuilder_is_pointer_type(self, target_type) && (strcmp(src_type, "Int") == 0)) {
    CType ull = ctype_new("unsigned long long", 0LL, false, false);
    int64_t inner_cast = CodegenBuilder_push_expr(self, cexpr_new_cast(ull, arg_idx));
    return CodegenBuilder_push_expr(self, cexpr_new_cast(ct, inner_cast));
}
    if ((strcmp(target_type, "Int") == 0) && CodegenBuilder_is_pointer_type(self, src_type)) {
    CType ull = ctype_new("unsigned long long", 0LL, false, false);
    int64_t inner_cast = CodegenBuilder_push_expr(self, cexpr_new_cast(ull, arg_idx));
    return CodegenBuilder_push_expr(self, cexpr_new_cast(ct, inner_cast));
}
    return CodegenBuilder_push_expr(self, cexpr_new_cast(ct, arg_idx));
}
    return CodegenBuilder_gen_expr(self, ArrayList_Int_get(&(expr.func_args), 0LL));
}
    if ((strcmp(name, "sizeof") == 0) || (strcmp(name, "size_of") == 0)) {
    const char* target_type = ArrayList_Str_get(&(expr.func_type_args), 0LL);
    if (strlen(target_type) > 0LL) {
    const char* mapped = CodegenBuilder_map_type(self, target_type);
    return CodegenBuilder_push_expr(self, cexpr_new_sizeof_type(ctype_new(mapped, 0LL, false, false)));
}
    return CodegenBuilder_push_expr(self, cexpr_new_int("0"));
}
    if ((((strcmp(name, "Int") == 0) || (strcmp(name, "Float") == 0)) || (strcmp(name, "Bool") == 0)) || (strcmp(name, "Char") == 0)) {
    if (ArrayList_Int_length(&(expr.func_args)) >= 1LL) {
    int64_t arg_idx = CodegenBuilder_gen_expr(self, ArrayList_Int_get(&(expr.func_args), 0LL));
    const char* ctype_str = "int64_t";
    if (strcmp(name, "Float") == 0) {
    ctype_str = "double";
} else if (strcmp(name, "Bool") == 0) {
    ctype_str = "bool";
} else if (strcmp(name, "Char") == 0) {
    ctype_str = "char";
}
    const char* src_type = CodegenBuilder_get_expr_type(self, ArrayList_Int_get(&(expr.func_args), 0LL));
    if ((strcmp(name, "Int") == 0) && (strcmp(src_type, "Int") == 0)) {
    return arg_idx;
}
    if ((strcmp(name, "Bool") == 0) && (strcmp(src_type, "Bool") == 0)) {
    return arg_idx;
}
    if ((strcmp(name, "Float") == 0) && (strcmp(src_type, "Float") == 0)) {
    return arg_idx;
}
    if ((strcmp(name, "Char") == 0) && (strcmp(src_type, "Char") == 0)) {
    return arg_idx;
}
    CType ct = ctype_new(ctype_str, 0LL, false, false);
    return CodegenBuilder_push_expr(self, cexpr_new_cast(ct, arg_idx));
}
    return CodegenBuilder_push_expr(self, cexpr_new_int("0"));
}
    if (strcmp(name, "length") == 0) {
    if (ArrayList_Int_length(&(expr.func_args)) >= 1LL) {
    int64_t arg_idx = CodegenBuilder_gen_expr(self, ArrayList_Int_get(&(expr.func_args), 0LL));
    ArrayList_Int len_args = ArrayList_Int_init(self->allocator);
    ArrayList_Int_push(&(len_args), arg_idx);
    return CodegenBuilder_push_expr(self, cexpr_new_call("strlen", len_args));
}
    return CodegenBuilder_push_expr(self, cexpr_new_int("0"));
}
    const char* fn_name = name;
    bool is_struct = false;
    int64_t si = 0LL;
    while (si < ArrayList_StmtNode_length(self->stmt_pool)) {
    StmtNode s = ArrayList_StmtNode_get(self->stmt_pool, si);
    if ((s.kind == StmtKind_sk_struct_decl) && (strcmp(s.struct_name, name) == 0)) {
    is_struct = true;
}
    si = (si + 1LL);
}
    if (((strcmp(name, "ArrayList") == 0) || (strcmp(name, "HashMap") == 0)) || (strcmp(name, "StringBuilder") == 0)) {
    is_struct = true;
}
    if (is_struct) {
    if (ArrayList_Str_length(&(expr.func_type_args)) > 0LL) {
    fn_name = name;
    int64_t tai = 0LL;
    while (tai < ArrayList_Str_length(&(expr.func_type_args))) {
    const char* clean = CodegenBuilder_cgb_clean_type_for_mangling(self, ArrayList_Str_get(&(expr.func_type_args), tai));
    fn_name = concatAlloc(concatAlloc(fn_name, "_"), clean);
    tai = (tai + 1LL);
}
    fn_name = concatAlloc(fn_name, "_init");
} else {
    fn_name = concatAlloc(name, "_init");
}
}
    ArrayList_Int call_args = ArrayList_Int_init(self->allocator);
    int64_t ai = 0LL;
    while (ai < ArrayList_Int_length(&(expr.func_args))) {
    int64_t p_idx = ai;
    if (is_struct) {
    p_idx = (ai + 1LL);
}
    const char* p_key = concatAlloc(concatAlloc(fn_name, "_param_"), cgb_int_to_str(p_idx));
    const char* expected_type = cgb_map_get(&(self->func_param_types), p_key);
    const char* arg_str = CodegenBuilder_gen_expr_with_expected_type(self, ArrayList_Int_get(&(expr.func_args), ai), expected_type);
    ArrayList_Int_push(&(call_args), CodegenBuilder_push_expr(self, cexpr_new_ident(arg_str)));
    ai = (ai + 1LL);
}
    return CodegenBuilder_push_expr(self, cexpr_new_call(fn_name, call_args));
}
    if (expr.kind == ExprKind_ek_index) {
    int64_t base_idx = CodegenBuilder_gen_expr(self, expr.idx_expr);
    int64_t idx_val_idx = CodegenBuilder_gen_expr(self, expr.idx_index);
    return CodegenBuilder_push_expr(self, cexpr_new_index(base_idx, idx_val_idx));
}
    if (expr.kind == ExprKind_ek_borrow) {
    int64_t operand_idx = CodegenBuilder_gen_expr(self, expr.borrow_expr);
    return CodegenBuilder_push_expr(self, cexpr_new_unary("&", operand_idx, true));
}
    if (expr.kind == ExprKind_ek_deref) {
    int64_t operand_idx = CodegenBuilder_gen_expr(self, expr.deref_expr);
    return CodegenBuilder_push_expr(self, cexpr_new_unary("*", operand_idx, true));
}
    if (expr.kind == ExprKind_ek_field_access) {
    ExprNode base_node = ArrayList_ExprNode_get(self->expr_pool, expr.field_expr);
    if (base_node.kind == ExprKind_ek_identifier) {
    const char* ident = base_node.ident_name;
    int64_t ei = 0LL;
    while (ei < ArrayList_StmtNode_length(self->stmt_pool)) {
    StmtNode s = ArrayList_StmtNode_get(self->stmt_pool, ei);
    if ((s.kind == StmtKind_sk_enum_decl) && (strcmp(s.enum_name, ident) == 0)) {
    const char* ename = CodegenBuilder_map_type(self, ident);
    const char* var_name = expr.field_name;
    bool has_payload = false;
    int64_t vi = 0LL;
    while (vi < ArrayList_Variant_length(&(s.enum_variants))) {
    Variant v = ArrayList_Variant_get(&(s.enum_variants), vi);
    if ((strcmp(v.vname, var_name) == 0) && (ArrayList_Param_length(&(v.params)) > 0LL)) {
    has_payload = true;
}
    vi = (vi + 1LL);
}
    if (has_payload) {
    return CodegenBuilder_push_expr(self, cexpr_new_ident(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc("(", ename), "){ .tag = "), ename), "_"), var_name), "_TAG }")));
}
    bool any_payload = false;
    vi = 0LL;
    while (vi < ArrayList_Variant_length(&(s.enum_variants))) {
    Variant v = ArrayList_Variant_get(&(s.enum_variants), vi);
    if (ArrayList_Param_length(&(v.params)) > 0LL) {
    any_payload = true;
}
    vi = (vi + 1LL);
}
    if (any_payload) {
    return CodegenBuilder_push_expr(self, cexpr_new_ident(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc("(", ename), "){ .tag = "), ename), "_"), var_name), "_TAG }")));
}
    return CodegenBuilder_push_expr(self, cexpr_new_ident(concatAlloc(concatAlloc(ename, "_"), var_name)));
}
    if ((s.kind == StmtKind_sk_error_decl) && (strcmp(s.error_name, ident) == 0)) {
    const char* ename = CodegenBuilder_map_type(self, ident);
    return CodegenBuilder_push_expr(self, cexpr_new_ident(concatAlloc(concatAlloc(ename, "_"), expr.field_name)));
}
    ei = (ei + 1LL);
}
}
    int64_t base_idx = CodegenBuilder_gen_expr(self, expr.field_expr);
    const char* base_type = CodegenBuilder_get_expr_type(self, expr.field_expr);
    bool is_arrow = false;
    if ((strlen(base_type) > 0LL) && ((base_type)[0LL] == ((char)(42LL)))) {
    is_arrow = true;
} else if ((strlen(base_type) > 4LL) && (strcmp(__kai_str_sub(base_type, 0LL, 4LL), "*mut ") == 0)) {
    is_arrow = true;
}
    if (is_arrow) {
    return CodegenBuilder_push_expr(self, cexpr_new_arrow(base_idx, expr.field_name));
}
    return CodegenBuilder_push_expr(self, cexpr_new_field(base_idx, expr.field_name));
}
    if (expr.kind == ExprKind_ek_method_call) {
    ExprNode receiver_node = ArrayList_ExprNode_get(self->expr_pool, expr.meth_expr);
    const char* rec_type = CodegenBuilder_get_expr_type(self, expr.meth_expr);
    const char* clean_type = "";
    int64_t ci = 0LL;
    while (ci < strlen(rec_type)) {
    char c = (rec_type)[ci];
    if ((c != ((char)(42LL))) && (c != ((char)(38LL)))) {
    clean_type = concatAlloc(clean_type, cgb_char_to_str(c));
}
    ci = (ci + 1LL);
}
    if ((strlen(clean_type) >= 4LL) && (strcmp(__kai_str_sub(clean_type, 0LL, 4LL), "mut ") == 0)) {
    clean_type = __kai_str_sub(clean_type, 4LL, strlen(clean_type));
}
    clean_type = CodegenBuilder_map_type(self, clean_type);
    bool is_constructor = false;
    if (receiver_node.kind == ExprKind_ek_identifier) {
    const char* r_name = receiver_node.ident_name;
    if (((r_name)[0LL] >= ((char)(65LL))) && ((r_name)[0LL] <= ((char)(90LL)))) {
    is_constructor = true;
}
}
    const char* func_name = concatAlloc(concatAlloc(clean_type, "_"), expr.meth_name);
    const char* args_str = "";
    if ((!is_constructor) && (strcmp(expr.meth_name, "init") != 0)) {
    const char* rec_val = CodegenBuilder_gen_expr_str(self, expr.meth_expr);
    const char* rec_inferred = CodegenBuilder_get_expr_type(self, expr.meth_expr);
    bool is_self_ptr = (((receiver_node.kind == ExprKind_ek_identifier) && (strcmp(receiver_node.ident_name, "self") == 0)) && (!self->cur_method_is_init));
    if ((strlen(rec_inferred) > 0LL) && ((((rec_inferred)[0LL] == ((char)(42LL))) || ((rec_inferred)[0LL] == ((char)(38LL)))) || is_self_ptr)) {
    args_str = rec_val;
} else {
    args_str = concatAlloc(concatAlloc("&(", rec_val), ")");
}
}
    int64_t ai = 0LL;
    while (ai < ArrayList_Int_length(&(expr.meth_args))) {
    if (strlen(args_str) > 0LL) {
    args_str = concatAlloc(args_str, ", ");
}
    const char* p_key = concatAlloc(concatAlloc(func_name, "_param_"), cgb_int_to_str((ai + 1LL)));
    const char* expected_type = cgb_map_get(&(self->func_param_types), p_key);
    args_str = concatAlloc(args_str, CodegenBuilder_gen_expr_with_expected_type(self, ArrayList_Int_get(&(expr.meth_args), ai), expected_type));
    ai = (ai + 1LL);
}
    if ((strcmp(expr.meth_name, "init") == 0) && (!is_constructor)) {
    const char* rec_val = CodegenBuilder_gen_expr_str(self, expr.meth_expr);
    const char* rec_inferred = CodegenBuilder_get_expr_type(self, expr.meth_expr);
    if ((strlen(rec_inferred) > 0LL) && (((rec_inferred)[0LL] == ((char)(42LL))) || ((rec_inferred)[0LL] == ((char)(38LL))))) {
    return CodegenBuilder_push_expr(self, cexpr_new_ident(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc("*(", rec_val), ") = "), func_name), "("), args_str), ")")));
}
    return CodegenBuilder_push_expr(self, cexpr_new_ident(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(rec_val, " = "), func_name), "("), args_str), ")")));
}
    return CodegenBuilder_push_expr(self, cexpr_new_ident(concatAlloc(concatAlloc(concatAlloc(func_name, "("), args_str), ")")));
}
    if (expr.kind == ExprKind_ek_slice) {
    int64_t base_idx = CodegenBuilder_gen_expr(self, expr.slice_expr);
    const char* base_type = CodegenBuilder_get_expr_type(self, expr.slice_expr);
    if ((strcmp(base_type, "Str") == 0) || (strcmp(base_type, "*Char") == 0)) {
    int64_t lower_idx = CodegenBuilder_push_expr(self, cexpr_new_int("0"));
    if (expr.slice_lower >= 0LL) {
    lower_idx = CodegenBuilder_gen_expr(self, expr.slice_lower);
}
    int64_t upper_idx = lower_idx;
    if (expr.slice_upper >= 0LL) {
    upper_idx = CodegenBuilder_gen_expr(self, expr.slice_upper);
} else {
    ArrayList_Int strlen_args = ArrayList_Int_init(self->allocator);
    ArrayList_Int_push(&(strlen_args), base_idx);
    upper_idx = CodegenBuilder_push_expr(self, cexpr_new_call("strlen", strlen_args));
}
    ArrayList_Int args = ArrayList_Int_init(self->allocator);
    ArrayList_Int_push(&(args), base_idx);
    ArrayList_Int_push(&(args), lower_idx);
    ArrayList_Int_push(&(args), upper_idx);
    return CodegenBuilder_push_expr(self, cexpr_new_call("__kai_str_sub", args));
}
    if ((strlen(base_type) >= 2LL) && (strcmp(__kai_str_sub(base_type, 0LL, 2LL), "[]") == 0)) {
    const char* inner_type = __kai_str_sub(base_type, 2LL, strlen(base_type));
    const char* mapped_inner = CodegenBuilder_map_type(self, inner_type);
    int64_t lower_idx = CodegenBuilder_push_expr(self, cexpr_new_int("0"));
    if (expr.slice_lower >= 0LL) {
    lower_idx = CodegenBuilder_gen_expr(self, expr.slice_lower);
}
    int64_t upper_idx = lower_idx;
    if (expr.slice_upper >= 0LL) {
    upper_idx = CodegenBuilder_gen_expr(self, expr.slice_upper);
} else {
    ArrayList_Int strlen_args = ArrayList_Int_init(self->allocator);
    ArrayList_Int_push(&(strlen_args), base_idx);
    upper_idx = CodegenBuilder_push_expr(self, cexpr_new_call("strlen", strlen_args));
}
    ArrayList_Int args = ArrayList_Int_init(self->allocator);
    ArrayList_Int_push(&(args), base_idx);
    ArrayList_Int_push(&(args), lower_idx);
    ArrayList_Int_push(&(args), upper_idx);
    ArrayList_Int_push(&(args), CodegenBuilder_push_expr(self, cexpr_new_sizeof_type(ctype_new(mapped_inner, 0LL, false, false))));
    return CodegenBuilder_push_expr(self, cexpr_new_call("__kai_arr_sub", args));
}
    return base_idx;
}
    if (expr.kind == ExprKind_ek_struct_init) {
    if (CodegenBuilder_str_contains(self, expr.struct_name, ((char)(46LL)))) {
    int64_t dot_pos = CodegenBuilder_str_find(self, expr.struct_name, ((char)(46LL)));
    const char* enum_part = __kai_str_sub(expr.struct_name, 0LL, dot_pos);
    const char* variant_name = __kai_str_sub(expr.struct_name, (dot_pos + 1LL), strlen(expr.struct_name));
    const char* enum_name = CodegenBuilder_map_type(self, enum_part);
    const char* fields_str = "";
    int64_t i = 0LL;
    while (i < ArrayList_FieldInit_length(&(expr.struct_fields))) {
    FieldInit f = ArrayList_FieldInit_get(&(expr.struct_fields), i);
    if (i > 0LL) {
    fields_str = concatAlloc(fields_str, ", ");
}
    fields_str = concatAlloc(concatAlloc(concatAlloc(concatAlloc(fields_str, "."), f.name), " = "), CodegenBuilder_gen_expr_str(self, f.value));
    i = (i + 1LL);
}
    const char* payload_str = "";
    if (strlen(fields_str) > 0LL) {
    payload_str = concatAlloc(concatAlloc(concatAlloc(concatAlloc(", .", variant_name), " = { "), fields_str), " }");
}
    return CodegenBuilder_push_expr(self, cexpr_new_ident(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc("(", enum_name), "){ .tag = "), enum_name), "_"), variant_name), "_TAG"), payload_str), " }")));
}
    const char* struct_name = CodegenBuilder_map_type(self, expr.struct_name);
    ArrayList_Str fields = ArrayList_Str_init(self->allocator);
    int64_t i = 0LL;
    while (i < ArrayList_FieldInit_length(&(expr.struct_fields))) {
    FieldInit f = ArrayList_FieldInit_get(&(expr.struct_fields), i);
    const char* field_type = "";
    int64_t si = 0LL;
    while (si < ArrayList_StmtNode_length(self->stmt_pool)) {
    StmtNode s = ArrayList_StmtNode_get(self->stmt_pool, si);
    if ((s.kind == StmtKind_sk_struct_decl) && (strcmp(s.struct_name, expr.struct_name) == 0)) {
    int64_t fi = 0LL;
    while (fi < ArrayList_StructField_length(&(s.struct_fields))) {
    StructField sf = ArrayList_StructField_get(&(s.struct_fields), fi);
    if (strcmp(sf.name, f.name) == 0) {
    field_type = sf.ftype;
}
    fi = (fi + 1LL);
}
}
    si = (si + 1LL);
}
    const char* val_str = CodegenBuilder_gen_expr_with_expected_type(self, f.value, field_type);
    ArrayList_Str_push(&(fields), concatAlloc(concatAlloc(concatAlloc(".", f.name), " = "), val_str));
    i = (i + 1LL);
}
    CType ct = ctype_new(struct_name, 0LL, false, false);
    return CodegenBuilder_push_expr(self, cexpr_new_compound(ct, fields));
}
    if (expr.kind == ExprKind_ek_array) {
    ArrayList_Str field_strs = ArrayList_Str_init(self->allocator);
    int64_t i = 0LL;
    while (i < ArrayList_Int_length(&(expr.arr_elements))) {
    int64_t elem_idx = CodegenBuilder_gen_expr(self, ArrayList_Int_get(&(expr.arr_elements), i));
    ArrayList_Str_push(&(field_strs), CodegenBuilder_expr_to_str(self, elem_idx));
    i = (i + 1LL);
}
    if (ArrayList_Str_length(&(field_strs)) == 0LL) {
    ArrayList_Str_push(&(field_strs), "0");
}
    const char* inner_ty = "Int";
    if ((strlen(expr.inferred_type) > 2LL) && (strcmp(__kai_str_sub(expr.inferred_type, 0LL, 2LL), "[]") == 0)) {
    inner_ty = __kai_str_sub(expr.inferred_type, 2LL, strlen(expr.inferred_type));
}
    const char* mapped_inner = CodegenBuilder_map_type(self, inner_ty);
    CType ct = ctype_new(concatAlloc(mapped_inner, "[]"), 0LL, false, false);
    return CodegenBuilder_push_expr(self, cexpr_new_compound(ct, field_strs));
}
    if (expr.kind == ExprKind_ek_tuple) {
    if (strlen(expr.inferred_type) > 0LL) {
    const char* mapped_ty = CodegenBuilder_map_type(self, expr.inferred_type);
    const char* elems_str = "";
    int64_t i = 0LL;
    while (i < ArrayList_Int_length(&(expr.tup_elements))) {
    if (i > 0LL) {
    elems_str = concatAlloc(elems_str, ", ");
}
    elems_str = concatAlloc(elems_str, CodegenBuilder_gen_expr_str(self, ArrayList_Int_get(&(expr.tup_elements), i)));
    i = (i + 1LL);
}
    return CodegenBuilder_push_expr(self, cexpr_new_ident(concatAlloc(concatAlloc(concatAlloc(concatAlloc("(", mapped_ty), "){ "), elems_str), " }")));
}
    return CodegenBuilder_push_expr(self, cexpr_new_ident("NULL"));
}
    if (expr.kind == ExprKind_ek_range) {
    int64_t start_idx = CodegenBuilder_gen_expr(self, expr.range_start);
    int64_t end_idx = CodegenBuilder_gen_expr(self, expr.range_end);
    const char* incl = "false";
    if (expr.range_inclusive) {
    incl = "true";
}
    ArrayList_Str fields = ArrayList_Str_init(self->allocator);
    ArrayList_Str_push(&(fields), concatAlloc(".start = ", CodegenBuilder_expr_to_str(self, start_idx)));
    ArrayList_Str_push(&(fields), concatAlloc(".end = ", CodegenBuilder_expr_to_str(self, end_idx)));
    ArrayList_Str_push(&(fields), concatAlloc(".is_inclusive = ", incl));
    CType ct = ctype_new("Range", 0LL, false, false);
    return CodegenBuilder_push_expr(self, cexpr_new_compound(ct, fields));
}
    if (expr.kind == ExprKind_ek_str_interp) {
    if (ArrayList_StrInterpPart_length(&(expr.interp_parts)) == 0LL) {
    return CodegenBuilder_push_expr(self, cexpr_new_str("\"\""));
}
    const char* result = "";
    int64_t i = 0LL;
    while (i < ArrayList_StrInterpPart_length(&(expr.interp_parts))) {
    StrInterpPart part = ArrayList_StrInterpPart_get(&(expr.interp_parts), i);
    const char* part_str = "";
    if (part.kind == 0LL) {
    part_str = concatAlloc(concatAlloc("\"", CodegenBuilder_escape_string(self, part.str_val)), "\"");
} else {
    const char* expr_val = CodegenBuilder_gen_expr_str(self, part.expr_idx);
    const char* expr_type = CodegenBuilder_get_expr_type(self, part.expr_idx);
    if (strcmp(expr_type, "Int") == 0) {
    part_str = concatAlloc(concatAlloc("cgb_int_to_str(", expr_val), ")");
} else if (strcmp(expr_type, "Char") == 0) {
    part_str = concatAlloc(concatAlloc("cgb_char_to_str(", expr_val), ")");
} else if (strcmp(expr_type, "Bool") == 0) {
    part_str = concatAlloc(concatAlloc("((", expr_val), ") ? \"true\" : \"false\")");
} else {
    part_str = expr_val;
}
}
    if (i == 0LL) {
    result = part_str;
} else {
    result = concatAlloc(concatAlloc(concatAlloc(concatAlloc("concatAlloc(", result), ", "), part_str), ")");
}
    i = (i + 1LL);
}
    return CodegenBuilder_push_expr(self, cexpr_new_ident(result));
}
    if (expr.kind == ExprKind_ek_try) {
    const char* inner_ty = CodegenBuilder_get_expr_type(self, expr.try_expr);
    int64_t excl_pos = CodegenBuilder_str_find(self, inner_ty, ((char)(33LL)));
    const char* inner = CodegenBuilder_gen_expr_str(self, expr.try_expr);
    if (excl_pos < 0LL) {
    return CodegenBuilder_push_expr(self, cexpr_new_ident(inner));
}
    const char* val_type = __kai_str_sub(inner_ty, 0LL, excl_pos);
    const char* result_ctype = CodegenBuilder_map_type(self, inner_ty);
    const char* ret_ctype = CodegenBuilder_map_type(self, self->cur_return_type);
    const char* try_code = concatAlloc(concatAlloc(concatAlloc(concatAlloc("({ ", result_ctype), " _kai_res = ("), inner), "); ");
    try_code = concatAlloc(try_code, "if (_kai_res.tag != 0) { ");
    try_code = concatAlloc(concatAlloc(try_code, ret_ctype), " _kai_err_ret; _kai_err_ret.tag = _kai_res.tag; return _kai_err_ret; } ");
    if (strcmp(val_type, "Void") == 0) {
    try_code = concatAlloc(try_code, "0; })");
} else {
    try_code = concatAlloc(try_code, "_kai_res.value; })");
}
    return CodegenBuilder_push_expr(self, cexpr_new_ident(try_code));
}
    if (expr.kind == ExprKind_ek_catch) {
    const char* inner = CodegenBuilder_gen_expr_str(self, expr.catch_expr);
    const char* inner_ty = CodegenBuilder_get_expr_type(self, expr.catch_expr);
    if ((strlen(inner_ty) > 0LL) && ((inner_ty)[0LL] == ((char)(63LL)))) {
    const char* val_type = __kai_str_sub(inner_ty, 1LL, strlen(inner_ty));
    const char* val_ctype = CodegenBuilder_map_type(self, val_type);
    const char* cond_ctype = CodegenBuilder_map_type(self, inner_ty);
    const char* fallback_code = "";
    bool fallback_is_stmt2 = false;
    if (expr.catch_fallback >= 0LL) {
    StmtNode fb_node = ArrayList_StmtNode_get(self->stmt_pool, expr.catch_fallback);
    if (fb_node.kind == StmtKind_sk_expr) {
    fallback_code = CodegenBuilder_gen_expr_str(self, fb_node.expr_stmt);
} else if (fb_node.kind == StmtKind_sk_block) {
    bool is_single_expr = false;
    int64_t expr_idx2 = (-1LL);
    if (ArrayList_Int_length(&(fb_node.block_stmts)) == 1LL) {
    StmtNode single_stmt = ArrayList_StmtNode_get(self->stmt_pool, ArrayList_Int_get(&(fb_node.block_stmts), 0LL));
    if (single_stmt.kind == StmtKind_sk_expr) {
    is_single_expr = true;
    expr_idx2 = single_stmt.expr_stmt;
}
}
    if (is_single_expr) {
    fallback_code = CodegenBuilder_gen_expr_str(self, expr_idx2);
} else {
    CCodeBuilder saved_builder = self->builder;
    self->builder = CCodeBuilder_init(self->allocator);
    CodegenBuilder_gen_stmt(self, expr.catch_fallback);
    fallback_code = CCodeBuilder_to_str(&(self->builder));
    self->builder = saved_builder;
    fallback_is_stmt2 = true;
}
} else {
    CCodeBuilder saved_builder = self->builder;
    self->builder = CCodeBuilder_init(self->allocator);
    CodegenBuilder_gen_stmt(self, expr.catch_fallback);
    fallback_code = CCodeBuilder_to_str(&(self->builder));
    self->builder = saved_builder;
    fallback_is_stmt2 = true;
}
} else {
    fallback_code = "0";
}
    const char* catch_code = "({ ";
    if (CodegenBuilder_is_pointer_type(self, val_type)) {
    catch_code = concatAlloc(concatAlloc(concatAlloc(concatAlloc(catch_code, val_ctype), " _kai_opt = ("), inner), "); ");
    catch_code = concatAlloc(concatAlloc(catch_code, val_ctype), " _kai_cv; ");
    catch_code = concatAlloc(catch_code, "if (_kai_opt != NULL) { _kai_cv = _kai_opt; } ");
    if (fallback_is_stmt2) {
    catch_code = concatAlloc(concatAlloc(concatAlloc(catch_code, "else { "), fallback_code), " __builtin_unreachable(); } _kai_cv; })");
} else {
    catch_code = concatAlloc(concatAlloc(concatAlloc(catch_code, "else { _kai_cv = ("), fallback_code), "); } _kai_cv; })");
}
} else {
    catch_code = concatAlloc(concatAlloc(concatAlloc(concatAlloc(catch_code, cond_ctype), " _kai_opt = ("), inner), "); ");
    catch_code = concatAlloc(concatAlloc(catch_code, val_ctype), " _kai_cv; ");
    catch_code = concatAlloc(catch_code, "if (_kai_opt.has_value) { _kai_cv = _kai_opt.value; } ");
    if (fallback_is_stmt2) {
    catch_code = concatAlloc(concatAlloc(concatAlloc(catch_code, "else { "), fallback_code), " __builtin_unreachable(); } _kai_cv; })");
} else {
    catch_code = concatAlloc(concatAlloc(concatAlloc(catch_code, "else { _kai_cv = ("), fallback_code), "); } _kai_cv; })");
}
}
    return CodegenBuilder_push_expr(self, cexpr_new_ident(catch_code));
}
    int64_t excl_pos = CodegenBuilder_str_find(self, inner_ty, ((char)(33LL)));
    if (excl_pos < 0LL) {
    return CodegenBuilder_push_expr(self, cexpr_new_ident(inner));
}
    const char* val_type = __kai_str_sub(inner_ty, 0LL, excl_pos);
    const char* result_ctype = CodegenBuilder_map_type(self, inner_ty);
    const char* val_ctype = CodegenBuilder_map_type(self, val_type);
    const char* fallback_code = "";
    bool fallback_is_stmt = false;
    if (expr.catch_fallback >= 0LL) {
    StmtNode fb_node = ArrayList_StmtNode_get(self->stmt_pool, expr.catch_fallback);
    if (fb_node.kind == StmtKind_sk_expr) {
    fallback_code = CodegenBuilder_gen_expr_str(self, fb_node.expr_stmt);
} else if (fb_node.kind == StmtKind_sk_block) {
    bool is_single_expr = false;
    int64_t expr_idx2 = (-1LL);
    if (ArrayList_Int_length(&(fb_node.block_stmts)) == 1LL) {
    StmtNode single_stmt = ArrayList_StmtNode_get(self->stmt_pool, ArrayList_Int_get(&(fb_node.block_stmts), 0LL));
    if (single_stmt.kind == StmtKind_sk_expr) {
    is_single_expr = true;
    expr_idx2 = single_stmt.expr_stmt;
}
}
    if (is_single_expr) {
    fallback_code = CodegenBuilder_gen_expr_str(self, expr_idx2);
} else {
    CCodeBuilder saved_builder = self->builder;
    self->builder = CCodeBuilder_init(self->allocator);
    CodegenBuilder_gen_stmt(self, expr.catch_fallback);
    fallback_code = CCodeBuilder_to_str(&(self->builder));
    self->builder = saved_builder;
    fallback_is_stmt = true;
}
} else {
    CCodeBuilder saved_builder = self->builder;
    self->builder = CCodeBuilder_init(self->allocator);
    CodegenBuilder_gen_stmt(self, expr.catch_fallback);
    fallback_code = CCodeBuilder_to_str(&(self->builder));
    self->builder = saved_builder;
    fallback_is_stmt = true;
}
} else {
    fallback_code = "0";
}
    const char* catch_code = concatAlloc(concatAlloc(concatAlloc(concatAlloc("({ ", result_ctype), " _kai_cr = ("), inner), "); ");
    if (strcmp(val_type, "Void") == 0) {
    catch_code = concatAlloc(catch_code, "if (_kai_cr.tag != 0) { ");
    if (strlen(expr.catch_var) > 0LL) {
    catch_code = concatAlloc(concatAlloc(concatAlloc(catch_code, "int64_t "), expr.catch_var), " = _kai_cr.tag; ");
}
    catch_code = concatAlloc(concatAlloc(catch_code, fallback_code), " } 0; })");
} else {
    catch_code = concatAlloc(concatAlloc(catch_code, val_ctype), " _kai_cv; ");
    catch_code = concatAlloc(catch_code, "if (_kai_cr.tag != 0) { ");
    if (strlen(expr.catch_var) > 0LL) {
    catch_code = concatAlloc(concatAlloc(concatAlloc(catch_code, "int64_t "), expr.catch_var), " = _kai_cr.tag; ");
}
    if (fallback_is_stmt) {
    catch_code = concatAlloc(concatAlloc(catch_code, fallback_code), " __builtin_unreachable(); ");
} else {
    catch_code = concatAlloc(concatAlloc(concatAlloc(catch_code, "_kai_cv = ("), fallback_code), "); ");
}
    catch_code = concatAlloc(catch_code, "} else { _kai_cv = _kai_cr.value; } _kai_cv; })");
}
    return CodegenBuilder_push_expr(self, cexpr_new_ident(catch_code));
}
    if (expr.kind == ExprKind_ek_check) {
    return CodegenBuilder_gen_expr(self, expr.check_expr);
}
    if (expr.kind == ExprKind_ek_asm) {
    const char* decls_str = "";
    const char* out_ops_str = "";
    int64_t i = 0LL;
    while (i < ArrayList_AsmOutput_length(&(expr.asm_outputs))) {
    AsmOutput out = ArrayList_AsmOutput_get(&(expr.asm_outputs), i);
    if (strlen(out.type_name) > 0LL) {
    const char* mapped_type = CodegenBuilder_map_type(self, out.type_name);
    const char* var_name = concatAlloc("asm_ret_", cgb_int_to_str(i));
    if (strlen(decls_str) > 0LL) {
    decls_str = concatAlloc(decls_str, " ");
}
    decls_str = concatAlloc(concatAlloc(concatAlloc(concatAlloc(decls_str, mapped_type), " "), var_name), ";");
    if (strlen(out_ops_str) > 0LL) {
    out_ops_str = concatAlloc(out_ops_str, ", ");
}
    out_ops_str = concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(out_ops_str, "["), out.name), "] \""), out.constraint), "\" ("), var_name), ")");
} else if (out.expr_idx >= 0LL) {
    const char* val_str = CodegenBuilder_gen_expr_str(self, out.expr_idx);
    if (strlen(out_ops_str) > 0LL) {
    out_ops_str = concatAlloc(out_ops_str, ", ");
}
    out_ops_str = concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(out_ops_str, "["), out.name), "] \""), out.constraint), "\" ("), val_str), ")");
}
    i = (i + 1LL);
}
    const char* in_ops_str = "";
    int64_t j = 0LL;
    while (j < ArrayList_AsmInput_length(&(expr.asm_inputs))) {
    AsmInput inp = ArrayList_AsmInput_get(&(expr.asm_inputs), j);
    const char* val_str = CodegenBuilder_gen_expr_str(self, inp.expr_idx);
    if (strlen(in_ops_str) > 0LL) {
    in_ops_str = concatAlloc(in_ops_str, ", ");
}
    in_ops_str = concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(in_ops_str, "["), inp.name), "] \""), inp.constraint), "\" ("), val_str), ")");
    j = (j + 1LL);
}
    const char* clobs_str = "";
    int64_t k = 0LL;
    while (k < ArrayList_Str_length(&(expr.asm_clobbers))) {
    if (strlen(clobs_str) > 0LL) {
    clobs_str = concatAlloc(clobs_str, ", ");
}
    clobs_str = concatAlloc(concatAlloc(concatAlloc(clobs_str, "\""), ArrayList_Str_get(&(expr.asm_clobbers), k)), "\"");
    k = (k + 1LL);
}
    const char* volatile_prefix = "";
    if (expr.asm_is_volatile) {
    volatile_prefix = "volatile";
}
    const char* escaped_asm = "";
    int64_t c_idx = 0LL;
    while (c_idx < strlen(expr.asm_code)) {
    char c = (expr.asm_code)[c_idx];
    if (c == ((char)(10LL))) {
    escaped_asm = concatAlloc(escaped_asm, "\\n\\t");
} else if (c == ((char)(34LL))) {
    escaped_asm = concatAlloc(escaped_asm, "\\\"");
} else {
    escaped_asm = concatAlloc(escaped_asm, cgb_char_to_str(c));
}
    c_idx = (c_idx + 1LL);
}
    const char* asm_stmt = concatAlloc(concatAlloc(concatAlloc(concatAlloc("__asm__ ", volatile_prefix), " (\""), escaped_asm), "\"");
    if (((strlen(out_ops_str) > 0LL) || (strlen(in_ops_str) > 0LL)) || (strlen(clobs_str) > 0LL)) {
    if (strlen(out_ops_str) == 0LL) {
    out_ops_str = " ";
}
    if (strlen(in_ops_str) == 0LL) {
    in_ops_str = " ";
}
    if (strlen(clobs_str) == 0LL) {
    clobs_str = " ";
}
    asm_stmt = concatAlloc(concatAlloc(asm_stmt, " : "), out_ops_str);
    asm_stmt = concatAlloc(concatAlloc(asm_stmt, " : "), in_ops_str);
    asm_stmt = concatAlloc(concatAlloc(asm_stmt, " : "), clobs_str);
}
    asm_stmt = concatAlloc(asm_stmt, ");");
    const char* res = concatAlloc(concatAlloc("({\n", decls_str), "\n");
    res = concatAlloc(concatAlloc(concatAlloc(res, "    "), asm_stmt), "\n");
    if (ArrayList_AsmOutput_length(&(expr.asm_outputs)) == 1LL) {
    AsmOutput out0 = ArrayList_AsmOutput_get(&(expr.asm_outputs), 0LL);
    if (strlen(out0.type_name) > 0LL) {
    res = concatAlloc(res, "    asm_ret_0;\n");
}
} else if (ArrayList_AsmOutput_length(&(expr.asm_outputs)) > 1LL) {
    const char* types_str = "";
    int64_t ti = 0LL;
    bool all_typed = true;
    while (ti < ArrayList_AsmOutput_length(&(expr.asm_outputs))) {
    AsmOutput out = ArrayList_AsmOutput_get(&(expr.asm_outputs), ti);
    if (strlen(out.type_name) == 0LL) {
    all_typed = false;
}
    if (strlen(types_str) > 0LL) {
    types_str = concatAlloc(types_str, ", ");
}
    types_str = concatAlloc(types_str, out.type_name);
    ti = (ti + 1LL);
}
    if (all_typed) {
    const char* tuple_type = concatAlloc(concatAlloc("(", types_str), ")");
    const char* mapped_tuple = CodegenBuilder_map_type(self, tuple_type);
    const char* vals_str = "";
    int64_t vi = 0LL;
    while (vi < ArrayList_AsmOutput_length(&(expr.asm_outputs))) {
    if (strlen(vals_str) > 0LL) {
    vals_str = concatAlloc(vals_str, ", ");
}
    vals_str = concatAlloc(concatAlloc(vals_str, "asm_ret_"), cgb_int_to_str(vi));
    vi = (vi + 1LL);
}
    res = concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(res, "    ("), mapped_tuple), "){ "), vals_str), " };\n");
}
}
    res = concatAlloc(res, "})");
    return CodegenBuilder_push_expr(self, cexpr_new_ident(res));
}
    return CodegenBuilder_push_expr(self, cexpr_new_ident(""));
}
void CodegenBuilder_gen_stmt(CodegenBuilder* self, int64_t stmt_idx) {
    if (stmt_idx < 0LL) {
    return;
}
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, stmt_idx);
    if (stmt.kind == StmtKind_sk_block) {
    CCodeBuilder_emit_line(&(self->builder), "{");
    CCodeBuilder_indent(&(self->builder));
    int64_t i = 0LL;
    while (i < ArrayList_Int_length(&(stmt.block_stmts))) {
    CodegenBuilder_gen_stmt(self, ArrayList_Int_get(&(stmt.block_stmts), i));
    i = (i + 1LL);
}
    CCodeBuilder_dedent(&(self->builder));
    CCodeBuilder_emit_line(&(self->builder), "}");
    return;
}
    if (stmt.kind == StmtKind_sk_var_decl) {
    const char* var_type = stmt.vardecl_type;
    const char* var_name = stmt.vardecl_name;
    int64_t var_value = stmt.vardecl_value;
    bool is_discard = ((var_value >= 0LL) && ((strcmp(var_name, "_") == 0) || ((strlen(var_type) == 0LL) && ((strcmp(CodegenBuilder_get_expr_type(self, var_value), "Void") == 0) || (strcmp(CodegenBuilder_get_expr_type(self, var_value), "NoneType") == 0)))));
    if (is_discard) {
    CCodeBuilder_emit_line(&(self->builder), concatAlloc(concatAlloc("(void)(", CodegenBuilder_gen_expr_str(self, var_value)), ");"));
    cgb_map_put(&(self->var_types), var_name, "Void");
    return;
}
    if (strlen(var_type) == 0LL) {
    const char* val_type = CodegenBuilder_get_expr_type(self, var_value);
    const char* ctype = CodegenBuilder_map_type(self, val_type);
    cgb_map_put(&(self->var_types), var_name, val_type);
    if (var_value >= 0LL) {
    CCodeBuilder_emit_line(&(self->builder), concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(ctype, " "), var_name), " = "), CodegenBuilder_gen_expr_str(self, var_value)), ";"));
} else {
    CCodeBuilder_emit_line(&(self->builder), concatAlloc(concatAlloc(concatAlloc(ctype, " "), var_name), ";"));
}
} else {
    const char* ctype = CodegenBuilder_map_type(self, var_type);
    cgb_map_put(&(self->var_types), var_name, var_type);
    if (var_value >= 0LL) {
    CCodeBuilder_emit_line(&(self->builder), concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(ctype, " "), var_name), " = "), CodegenBuilder_gen_expr_str(self, var_value)), ";"));
} else {
    CCodeBuilder_emit_line(&(self->builder), concatAlloc(concatAlloc(concatAlloc(ctype, " "), var_name), ";"));
}
}
    return;
}
    if (stmt.kind == StmtKind_sk_assignment) {
    const char* target = CodegenBuilder_gen_expr_str(self, stmt.assign_target);
    const char* lhs_type = CodegenBuilder_get_expr_type(self, stmt.assign_target);
    const char* rhs = CodegenBuilder_gen_expr_with_expected_type(self, stmt.assign_value, lhs_type);
    const char* op = "=";
    if (strlen(stmt.assign_op) > 0LL) {
    op = stmt.assign_op;
}
    CCodeBuilder_emit_line(&(self->builder), concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(target, " "), op), " "), rhs), ";"));
    return;
}
    if (stmt.kind == StmtKind_sk_return) {
    ArrayList_Str drop_calls = ArrayList_Str_init(self->allocator);
    int64_t bi = (ArrayList_Int_length(&(self->block_stack)) - 1LL);
    while (bi >= 0LL) {
    int64_t b_idx = ArrayList_Int_get(&(self->block_stack), bi);
    StmtNode b_node = ArrayList_StmtNode_get(self->stmt_pool, b_idx);
    int64_t start_idx = 0LL;
    if (bi < ArrayList_Int_length(&(self->defer_depths))) {
    start_idx = ArrayList_Int_get(&(self->defer_depths), bi);
}
    int64_t next_start_idx = ArrayList_Int_length(&(self->defer_stack));
    if ((bi < (ArrayList_Int_length(&(self->block_stack)) - 1LL)) && ((bi + 1LL) < ArrayList_Int_length(&(self->defer_depths)))) {
    next_start_idx = ArrayList_Int_get(&(self->defer_depths), (bi + 1LL));
}
    int64_t def_i = (next_start_idx - 1LL);
    while (def_i >= start_idx) {
    if (def_i < ArrayList_Int_length(&(self->defer_stack))) {
    int64_t def_idx = ArrayList_Int_get(&(self->defer_stack), def_i);
    StmtNode def_node = ArrayList_StmtNode_get(self->stmt_pool, def_idx);
    CodegenBuilder_gen_stmt(self, def_node.defer_body);
}
    def_i = (def_i - 1LL);
}
    int64_t di = 0LL;
    while (di < ArrayList_DropVarEntry_length(&(b_node.block_drop_vars))) {
    DropVarEntry entry = ArrayList_DropVarEntry_get(&(b_node.block_drop_vars), di);
    ArrayList_Str_push(&(drop_calls), concatAlloc(concatAlloc(concatAlloc(entry.base_type, "_drop(&"), entry.name), ");"));
    di = (di + 1LL);
}
    bi = (bi - 1LL);
}
    if (ArrayList_Str_length(&(drop_calls)) == 0LL) {
    if (stmt.return_value >= 0LL) {
    const char* val = CodegenBuilder_gen_expr_with_expected_type(self, stmt.return_value, self->cur_return_type);
    if (self->cur_method_is_init) {
    ExprNode expr = ArrayList_ExprNode_get(self->expr_pool, stmt.return_value);
    if ((expr.kind != ExprKind_ek_identifier) && (expr.kind != ExprKind_ek_literal)) {
    CCodeBuilder_emit_line(&(self->builder), concatAlloc(val, ";"));
}
} else {
    CCodeBuilder_emit_line(&(self->builder), concatAlloc(concatAlloc("return ", val), ";"));
}
} else {
    CCodeBuilder_emit_line(&(self->builder), "return;");
}
} else if (stmt.return_value >= 0LL) {
    const char* val_str = CodegenBuilder_gen_expr_with_expected_type(self, stmt.return_value, self->cur_return_type);
    const char* val_type = CodegenBuilder_get_expr_type(self, stmt.return_value);
    if ((strcmp(val_type, "Void") == 0) || (strcmp(val_type, "NoneType") == 0)) {
    CCodeBuilder_emit_line(&(self->builder), concatAlloc(val_str, ";"));
    int64_t ci = 0LL;
    while (ci < ArrayList_Str_length(&(drop_calls))) {
    CCodeBuilder_emit_line(&(self->builder), ArrayList_Str_get(&(drop_calls), ci));
    ci = (ci + 1LL);
}
    CCodeBuilder_emit_line(&(self->builder), "return;");
} else {
    CCodeBuilder_begin_block(&(self->builder));
    CCodeBuilder_emit_line(&(self->builder), concatAlloc(concatAlloc("int64_t __ret_val = ", val_str), ";"));
    int64_t ci = 0LL;
    while (ci < ArrayList_Str_length(&(drop_calls))) {
    CCodeBuilder_emit_line(&(self->builder), ArrayList_Str_get(&(drop_calls), ci));
    ci = (ci + 1LL);
}
    CCodeBuilder_emit_line(&(self->builder), "return __ret_val;");
    CCodeBuilder_end_block(&(self->builder));
}
} else {
    CCodeBuilder_begin_block(&(self->builder));
    int64_t ci = 0LL;
    while (ci < ArrayList_Str_length(&(drop_calls))) {
    CCodeBuilder_emit_line(&(self->builder), ArrayList_Str_get(&(drop_calls), ci));
    ci = (ci + 1LL);
}
    CCodeBuilder_emit_line(&(self->builder), "return;");
    CCodeBuilder_end_block(&(self->builder));
}
    return;
}
    if (stmt.kind == StmtKind_sk_if) {
    const char* cond = CodegenBuilder_gen_expr_str(self, stmt.if_cond);
    CCodeBuilder_emit_line(&(self->builder), concatAlloc("if ", CodegenBuilder_format_cond(self, cond)));
    CodegenBuilder_gen_stmt(self, stmt.if_then);
    if (stmt.if_else >= 0LL) {
    CodegenBuilder_gen_else_chain(self, stmt.if_else);
}
    return;
}
    if (stmt.kind == StmtKind_sk_if_let) {
    const char* cond_val = CodegenBuilder_gen_expr_str(self, stmt.iflet_expr);
    const char* cond_type = CodegenBuilder_get_expr_type(self, stmt.iflet_expr);
    const char* unwrapped_type = __kai_str_sub(cond_type, 1LL, strlen(cond_type));
    const char* unwrapped_ctype = CodegenBuilder_map_type(self, unwrapped_type);
    const char* cond_ctype = CodegenBuilder_map_type(self, cond_type);
    int64_t old_var_len = ArrayList_CgbMapEntry_length(&(self->var_types));
    cgb_map_put(&(self->var_types), stmt.iflet_var, unwrapped_type);
    if (CodegenBuilder_is_pointer_type(self, unwrapped_type)) {
    CCodeBuilder_emit_line(&(self->builder), concatAlloc(concatAlloc("if ((", cond_val), ") != NULL)"));
    CCodeBuilder_begin_block(&(self->builder));
    CCodeBuilder_emit_line(&(self->builder), concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(unwrapped_ctype, " "), stmt.iflet_var), " = "), cond_val), ";"));
    CodegenBuilder_gen_stmt(self, stmt.iflet_then);
    CCodeBuilder_end_block(&(self->builder));
} else {
    CCodeBuilder_begin_block(&(self->builder));
    CCodeBuilder_emit_line(&(self->builder), concatAlloc(concatAlloc(concatAlloc(cond_ctype, " _kai_opt = "), cond_val), ";"));
    CCodeBuilder_emit_line(&(self->builder), "if (_kai_opt.has_value)");
    CCodeBuilder_begin_block(&(self->builder));
    CCodeBuilder_emit_line(&(self->builder), concatAlloc(concatAlloc(concatAlloc(unwrapped_ctype, " "), stmt.iflet_var), " = _kai_opt.value;"));
    CodegenBuilder_gen_stmt(self, stmt.iflet_then);
    CCodeBuilder_end_block(&(self->builder));
    CCodeBuilder_end_block(&(self->builder));
}
    if (stmt.iflet_else >= 0LL) {
    StmtNode else_node = ArrayList_StmtNode_get(self->stmt_pool, stmt.iflet_else);
    if (else_node.kind == StmtKind_sk_if_let) {
    CCodeBuilder_append_to_last_line(&(self->builder), " else");
    CodegenBuilder_gen_stmt(self, stmt.iflet_else);
} else {
    CCodeBuilder_append_to_last_line(&(self->builder), " else");
    CodegenBuilder_gen_stmt(self, stmt.iflet_else);
}
}
    while (ArrayList_CgbMapEntry_length(&(self->var_types)) > old_var_len) {
    (void)(ArrayList_CgbMapEntry_pop(&(self->var_types)));
}
    return;
}
    if (stmt.kind == StmtKind_sk_while) {
    const char* cond = CodegenBuilder_gen_expr_str(self, stmt.while_cond);
    CCodeBuilder_emit_line(&(self->builder), concatAlloc("while ", CodegenBuilder_format_cond(self, cond)));
    if (stmt.while_body >= 0LL) {
    StmtNode body_stmt = ArrayList_StmtNode_get(self->stmt_pool, stmt.while_body);
    body_stmt.block_is_loop_body = true;
    ArrayList_StmtNode_set(self->stmt_pool, stmt.while_body, body_stmt);
}
    CodegenBuilder_gen_stmt(self, stmt.while_body);
    return;
}
    if (stmt.kind == StmtKind_sk_for) {
    const char* iter_var = stmt.for_var;
    const char* start = CodegenBuilder_gen_expr_str(self, stmt.for_start);
    const char* end = CodegenBuilder_gen_expr_str(self, stmt.for_end);
    if (stmt.for_body >= 0LL) {
    StmtNode body_stmt = ArrayList_StmtNode_get(self->stmt_pool, stmt.for_body);
    body_stmt.block_is_loop_body = true;
    ArrayList_StmtNode_set(self->stmt_pool, stmt.for_body, body_stmt);
}
    const char* cmp_asc = "<";
    const char* cmp_desc = ">";
    if (stmt.for_inclusive) {
    cmp_asc = "<=";
    cmp_desc = ">=";
}
    CCodeBuilder_emit_line(&(self->builder), concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc("for (int64_t ", iter_var), " = "), start), "; ("), start), " <= "), end), ") ? ("), iter_var), " "), cmp_asc), " "), end), ") : ("), iter_var), " "), cmp_desc), " "), end), "); ("), start), " <= "), end), ") ? ++"), iter_var), " : --"), iter_var), ")"));
    CodegenBuilder_gen_stmt(self, stmt.for_body);
    return;
}
    if (stmt.kind == StmtKind_sk_break) {
    ArrayList_Str drop_calls = ArrayList_Str_init(self->allocator);
    int64_t bi = (ArrayList_Int_length(&(self->block_stack)) - 1LL);
    bool done = false;
    while ((bi >= 0LL) && (!done)) {
    int64_t b_idx = ArrayList_Int_get(&(self->block_stack), bi);
    StmtNode b_node = ArrayList_StmtNode_get(self->stmt_pool, b_idx);
    int64_t start_idx = 0LL;
    if (bi < ArrayList_Int_length(&(self->defer_depths))) {
    start_idx = ArrayList_Int_get(&(self->defer_depths), bi);
}
    int64_t next_start_idx = ArrayList_Int_length(&(self->defer_stack));
    if ((bi < (ArrayList_Int_length(&(self->block_stack)) - 1LL)) && ((bi + 1LL) < ArrayList_Int_length(&(self->defer_depths)))) {
    next_start_idx = ArrayList_Int_get(&(self->defer_depths), (bi + 1LL));
}
    int64_t def_i = (next_start_idx - 1LL);
    while (def_i >= start_idx) {
    if (def_i < ArrayList_Int_length(&(self->defer_stack))) {
    int64_t def_idx = ArrayList_Int_get(&(self->defer_stack), def_i);
    StmtNode def_node = ArrayList_StmtNode_get(self->stmt_pool, def_idx);
    CodegenBuilder_gen_stmt(self, def_node.defer_body);
}
    def_i = (def_i - 1LL);
}
    int64_t di = 0LL;
    while (di < ArrayList_DropVarEntry_length(&(b_node.block_drop_vars))) {
    DropVarEntry entry = ArrayList_DropVarEntry_get(&(b_node.block_drop_vars), di);
    ArrayList_Str_push(&(drop_calls), concatAlloc(concatAlloc(concatAlloc(entry.base_type, "_drop(&"), entry.name), ");"));
    di = (di + 1LL);
}
    if (b_node.block_is_loop_body) {
    done = true;
}
    bi = (bi - 1LL);
}
    if (ArrayList_Str_length(&(drop_calls)) == 0LL) {
    ArrayList_Int block_stmts = ArrayList_Int_init(self->allocator);
    CStmtNode cnode = (CStmtNode){ .kind = CStmtKind_cs_break, .block_stmts = block_stmts, .expr_stmt = (-1LL), .if_cond = (-1LL), .if_then = (-1LL), .if_else = (-1LL), .while_cond = (-1LL), .while_body = (-1LL), .for_init = (-1LL), .for_cond = (-1LL), .for_inc = (-1LL), .for_body = (-1LL), .do_body = (-1LL), .do_cond = (-1LL), .return_val = (-1LL), .var_type = ctype_void(), .var_name = "", .var_init = (-1LL), .switch_expr = (-1LL), .case_val = "", .label_name = "", .asm_code = "", .asm_volatile = false };
    int64_t c_idx = ArrayList_CStmtNode_length(&(self->c_stmts));
    ArrayList_CStmtNode_push(&(self->c_stmts), cnode);
    CPrinter printer = (CPrinter){ .builder = &(self->builder), .expr_pool = &(self->c_exprs), .stmt_pool = &(self->c_stmts) };
    CPrinter_print_stmt(&(printer), c_idx);
} else {
    CCodeBuilder_begin_block(&(self->builder));
    int64_t ci = 0LL;
    while (ci < ArrayList_Str_length(&(drop_calls))) {
    CCodeBuilder_emit_line(&(self->builder), ArrayList_Str_get(&(drop_calls), ci));
    ci = (ci + 1LL);
}
    CCodeBuilder_emit_line(&(self->builder), "break;");
    CCodeBuilder_end_block(&(self->builder));
}
    return;
}
    if (stmt.kind == StmtKind_sk_continue) {
    ArrayList_Str drop_calls = ArrayList_Str_init(self->allocator);
    int64_t bi = (ArrayList_Int_length(&(self->block_stack)) - 1LL);
    bool done = false;
    while ((bi >= 0LL) && (!done)) {
    int64_t b_idx = ArrayList_Int_get(&(self->block_stack), bi);
    StmtNode b_node = ArrayList_StmtNode_get(self->stmt_pool, b_idx);
    int64_t start_idx = 0LL;
    if (bi < ArrayList_Int_length(&(self->defer_depths))) {
    start_idx = ArrayList_Int_get(&(self->defer_depths), bi);
}
    int64_t next_start_idx = ArrayList_Int_length(&(self->defer_stack));
    if ((bi < (ArrayList_Int_length(&(self->block_stack)) - 1LL)) && ((bi + 1LL) < ArrayList_Int_length(&(self->defer_depths)))) {
    next_start_idx = ArrayList_Int_get(&(self->defer_depths), (bi + 1LL));
}
    int64_t def_i = (next_start_idx - 1LL);
    while (def_i >= start_idx) {
    if (def_i < ArrayList_Int_length(&(self->defer_stack))) {
    int64_t def_idx = ArrayList_Int_get(&(self->defer_stack), def_i);
    StmtNode def_node = ArrayList_StmtNode_get(self->stmt_pool, def_idx);
    CodegenBuilder_gen_stmt(self, def_node.defer_body);
}
    def_i = (def_i - 1LL);
}
    int64_t di = 0LL;
    while (di < ArrayList_DropVarEntry_length(&(b_node.block_drop_vars))) {
    DropVarEntry entry = ArrayList_DropVarEntry_get(&(b_node.block_drop_vars), di);
    ArrayList_Str_push(&(drop_calls), concatAlloc(concatAlloc(concatAlloc(entry.base_type, "_drop(&"), entry.name), ");"));
    di = (di + 1LL);
}
    if (b_node.block_is_loop_body) {
    done = true;
}
    bi = (bi - 1LL);
}
    if (ArrayList_Str_length(&(drop_calls)) == 0LL) {
    ArrayList_Int block_stmts = ArrayList_Int_init(self->allocator);
    CStmtNode cnode = (CStmtNode){ .kind = CStmtKind_cs_continue, .block_stmts = block_stmts, .expr_stmt = (-1LL), .if_cond = (-1LL), .if_then = (-1LL), .if_else = (-1LL), .while_cond = (-1LL), .while_body = (-1LL), .for_init = (-1LL), .for_cond = (-1LL), .for_inc = (-1LL), .for_body = (-1LL), .do_body = (-1LL), .do_cond = (-1LL), .return_val = (-1LL), .var_type = ctype_void(), .var_name = "", .var_init = (-1LL), .switch_expr = (-1LL), .case_val = "", .label_name = "", .asm_code = "", .asm_volatile = false };
    int64_t c_idx = ArrayList_CStmtNode_length(&(self->c_stmts));
    ArrayList_CStmtNode_push(&(self->c_stmts), cnode);
    CPrinter printer = (CPrinter){ .builder = &(self->builder), .expr_pool = &(self->c_exprs), .stmt_pool = &(self->c_stmts) };
    CPrinter_print_stmt(&(printer), c_idx);
} else {
    CCodeBuilder_begin_block(&(self->builder));
    int64_t ci = 0LL;
    while (ci < ArrayList_Str_length(&(drop_calls))) {
    CCodeBuilder_emit_line(&(self->builder), ArrayList_Str_get(&(drop_calls), ci));
    ci = (ci + 1LL);
}
    CCodeBuilder_emit_line(&(self->builder), "continue;");
    CCodeBuilder_end_block(&(self->builder));
}
    return;
}
    if (stmt.kind == StmtKind_sk_print) {
    int64_t arg = stmt.print_value;
    const char* val = CodegenBuilder_gen_expr_str(self, arg);
    const char* arg_type = CodegenBuilder_get_expr_type(self, arg);
    if (strcmp(arg_type, "Int") == 0) {
    CCodeBuilder_emit_line(&(self->builder), concatAlloc(concatAlloc("__kai_print_int(", val), ");"));
} else if (strcmp(arg_type, "Float") == 0) {
    CCodeBuilder_emit_line(&(self->builder), concatAlloc(concatAlloc("__kai_print_float(", val), ");"));
} else if (strcmp(arg_type, "Char") == 0) {
    CCodeBuilder_emit_line(&(self->builder), concatAlloc(concatAlloc("printf(\"%c\\n\", (char)(", val), "));"));
} else if (strcmp(arg_type, "Bool") == 0) {
    CCodeBuilder_emit_line(&(self->builder), concatAlloc(concatAlloc("printf(\"%s\\n\", (", val), ") ? \"true\" : \"false\");"));
} else {
    CCodeBuilder_emit_line(&(self->builder), concatAlloc(concatAlloc("printf(\"%s\\n\", ", val), ");"));
}
    return;
}
    if (stmt.kind == StmtKind_sk_unsafe) {
    CodegenBuilder_gen_stmt(self, stmt.unsafe_body);
    return;
}
    if (stmt.kind == StmtKind_sk_defer) {
    ArrayList_Int_push(&(self->defer_stack), stmt_idx);
    return;
}
    if (stmt.kind == StmtKind_sk_match) {
    int64_t expr_idx = stmt.match_expr;
    const char* expr_val = CodegenBuilder_gen_expr_str(self, expr_idx);
    ExprNode expr_node = ArrayList_ExprNode_get(self->expr_pool, expr_idx);
    const char* expr_type = CodegenBuilder_get_expr_type(self, expr_idx);
    const char* mapped_expr_type = CodegenBuilder_map_type(self, expr_type);
    bool is_self_ptr = (((expr_node.kind == ExprKind_ek_identifier) && (strcmp(expr_node.ident_name, "self") == 0)) && (!self->cur_method_is_init));
    bool is_ptr = false;
    if ((strlen(expr_type) > 0LL) && ((((expr_type)[0LL] == ((char)(42LL))) || ((expr_type)[0LL] == ((char)(38LL)))) || is_self_ptr)) {
    is_ptr = true;
}
    const char* op = ".";
    if (is_ptr) {
    op = "->";
}
    int64_t case_idx = 0LL;
    while (case_idx < ArrayList_MatchCase_length(&(stmt.match_cases))) {
    MatchCase case_node = ArrayList_MatchCase_get(&(stmt.match_cases), case_idx);
    PatternNode pat_node = ArrayList_PatternNode_get(self->pattern_pool, case_node.pattern);
    const char* cond = "";
    const char* bindings_str = "";
    bool has_non_underscore_bindings = false;
    bool found_var = false;
    Variant matched_var = (Variant){ .vname = "", .params = empty_param_array() };
    const char* var_name = "";
    if (pat_node.kind == PatternKind_pk_literal) {
    const char* lit_str = "";
    if (pat_node.lit_value.tag == TokenValue_tv_int_TAG) {
    int64_t v = pat_node.lit_value.payload.tv_int.v;

    lit_str = cgb_int_to_str(v);
} else if (pat_node.lit_value.tag == TokenValue_tv_str_TAG) {
    int64_t v = pat_node.lit_value.payload.tv_str.v;

    lit_str = concatAlloc(concatAlloc("\"", CodegenBuilder_escape_string(self, StringPool_get(self->pool, v))), "\"");
} else if (pat_node.lit_value.tag == TokenValue_tv_bool_TAG) {
    bool v = pat_node.lit_value.payload.tv_bool.v;

    if (v) {
    lit_str = "true";
} else {
    lit_str = "false";
}
} else if (pat_node.lit_value.tag == TokenValue_tv_char_TAG) {
    char v = pat_node.lit_value.payload.tv_char.v;

    if (v == ((char)(10LL))) {
    lit_str = "'\\n'";
} else if (v == ((char)(13LL))) {
    lit_str = "'\\r'";
} else if (v == ((char)(9LL))) {
    lit_str = "'\\t'";
} else if (v == ((char)(92LL))) {
    lit_str = "'\\\\'";
} else if (v == ((char)(39LL))) {
    lit_str = "'\\''";
} else {
    lit_str = concatAlloc(concatAlloc("'", cgb_char_to_str(v)), "'");
}
} else {
    lit_str = "0";
} 
    cond = concatAlloc(concatAlloc(expr_val, " == "), lit_str);
} else if (pat_node.kind == PatternKind_pk_variant) {
    var_name = pat_node.variant_name;
    const char* base_type = mapped_expr_type;
    if ((strlen(base_type) > 0LL) && (((base_type)[(strlen(base_type) - 1LL)] == ((char)(42LL))) || ((base_type)[(strlen(base_type) - 1LL)] == ((char)(38LL))))) {
    base_type = __kai_str_sub(base_type, 0LL, (strlen(base_type) - 1LL));
}
    if ((strlen(base_type) > 0LL) && ((base_type)[0LL] == ((char)(42LL)))) {
    base_type = __kai_str_sub(base_type, 1LL, strlen(base_type));
}
    bool has_payload = false;
    const char* enum_idx_str = cgb_map_get(&(self->enum_decls), expr_type);
    if (strlen(enum_idx_str) == 0LL) {
    const char* clean_base = expr_type;
    bool done_clean = false;
    while (!done_clean) {
    if ((strlen(clean_base) > 0LL) && (((clean_base)[0LL] == ((char)(42LL))) || ((clean_base)[0LL] == ((char)(38LL))))) {
    clean_base = __kai_str_sub(clean_base, 1LL, strlen(clean_base));
} else {
    done_clean = true;
}
}
    enum_idx_str = cgb_map_get(&(self->enum_decls), clean_base);
}
    if (strlen(enum_idx_str) > 0LL) {
    StmtNode enum_stmt = ArrayList_StmtNode_get(self->stmt_pool, CodegenBuilder_str_to_int(self, enum_idx_str));
    int64_t vi = 0LL;
    while (vi < ArrayList_Variant_length(&(enum_stmt.enum_variants))) {
    Variant v = ArrayList_Variant_get(&(enum_stmt.enum_variants), vi);
    if (ArrayList_Param_length(&(v.params)) > 0LL) {
    has_payload = true;
}
    vi = (vi + 1LL);
}
}
    if (has_payload) {
    cond = concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(expr_val, op), "tag == "), base_type), "_"), var_name), "_TAG");
} else {
    cond = concatAlloc(concatAlloc(concatAlloc(concatAlloc(expr_val, " == "), base_type), "_"), var_name);
}
    if (ArrayList_Str_length(&(pat_node.bindings)) > 0LL) {
    int64_t bi = 0LL;
    while (bi < ArrayList_Str_length(&(pat_node.bindings))) {
    if (strcmp(ArrayList_Str_get(&(pat_node.bindings), bi), "_") != 0) {
    has_non_underscore_bindings = true;
    break;
}
    bi = (bi + 1LL);
}
}
    if (strlen(enum_idx_str) > 0LL) {
    StmtNode enum_stmt = ArrayList_StmtNode_get(self->stmt_pool, CodegenBuilder_str_to_int(self, enum_idx_str));
    int64_t vi = 0LL;
    while (vi < ArrayList_Variant_length(&(enum_stmt.enum_variants))) {
    Variant v = ArrayList_Variant_get(&(enum_stmt.enum_variants), vi);
    if (strcmp(v.vname, var_name) == 0) {
    found_var = true;
    matched_var = v;
    break;
}
    vi = (vi + 1LL);
}
}
} else if (pat_node.kind == PatternKind_pk_else) {
    cond = "true";
}
    if (case_idx == 0LL) {
    CCodeBuilder_emit_line(&(self->builder), concatAlloc("if ", CodegenBuilder_format_cond(self, cond)));
} else if (strcmp(cond, "true") == 0) {
    CCodeBuilder_append_to_last_line(&(self->builder), " else");
} else {
    CCodeBuilder_append_to_last_line(&(self->builder), concatAlloc(" else if ", CodegenBuilder_format_cond(self, cond)));
}
    if (has_non_underscore_bindings) {
    CCodeBuilder_begin_block(&(self->builder));
    int64_t bi = 0LL;
    while (bi < ArrayList_Str_length(&(pat_node.bindings))) {
    const char* bind_name = ArrayList_Str_get(&(pat_node.bindings), bi);
    if (strcmp(bind_name, "_") != 0) {
    const char* bind_type = "Void";
    const char* field_name = "";
    if (found_var && (bi < ArrayList_Param_length(&(matched_var.params)))) {
    Param param = ArrayList_Param_get(&(matched_var.params), bi);
    bind_type = param.ptype;
    field_name = param.name;
}
    if (strcmp(bind_type, "T") == 0) {
    const char* t_type = cgb_map_get(&(self->current_type_map), "T");
    if (strlen(t_type) == 0LL) {
    t_type = CodegenBuilder_extract_first_type_arg(self, expr_type);
}
    bind_type = t_type;
} else if (strcmp(bind_type, "E") == 0) {
    const char* e_type = cgb_map_get(&(self->current_type_map), "E");
    if (strlen(e_type) == 0LL) {
    e_type = "Int";
}
    bind_type = e_type;
}
    const char* mapped_bind_type = CodegenBuilder_map_type(self, bind_type);
    const char* single_binding = concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(mapped_bind_type, " "), bind_name), " = "), expr_val), op), var_name), "."), field_name), ";");
    CCodeBuilder_emit_line(&(self->builder), single_binding);
}
    bi = (bi + 1LL);
}
    CodegenBuilder_gen_stmt(self, case_node.body);
    CCodeBuilder_end_block(&(self->builder));
} else {
    CodegenBuilder_gen_stmt(self, case_node.body);
}
    case_idx = (case_idx + 1LL);
}
    return;
}
    if (stmt.kind == StmtKind_sk_expr) {
    ExprNode expr = ArrayList_ExprNode_get(self->expr_pool, stmt.expr_stmt);
    if ((expr.kind != ExprKind_ek_identifier) && (expr.kind != ExprKind_ek_literal)) {
    int64_t c_expr_idx = CodegenBuilder_gen_expr(self, stmt.expr_stmt);
    if (c_expr_idx >= 0LL) {
    CStmtNode c_stmt = cstmt_new_expr(c_expr_idx);
    int64_t c_stmt_idx = ArrayList_CStmtNode_length(&(self->c_stmts));
    ArrayList_CStmtNode_push(&(self->c_stmts), c_stmt);
    CPrinter printer = (CPrinter){ .builder = &(self->builder), .expr_pool = &(self->c_exprs), .stmt_pool = &(self->c_stmts) };
    CPrinter_print_stmt(&(printer), c_stmt_idx);
}
}
    return;
}
    if (stmt.kind == StmtKind_sk_func_decl) {
    return;
}
    if (stmt.kind == StmtKind_sk_extern) {
    return;
}
    if (stmt.kind == StmtKind_sk_struct_decl) {
    return;
}
    if (stmt.kind == StmtKind_sk_enum_decl) {
    return;
}
    if (stmt.kind == StmtKind_sk_impl_block) {
    return;
}
    if (stmt.kind == StmtKind_sk_import) {
    return;
}
    if (stmt.kind == StmtKind_sk_cimport) {
    ImportResolver_record_cimport(self->import_resolver, stmt.cimport_header);
    return;
}
    if (stmt.kind == StmtKind_sk_trait_decl) {
    return;
}
    if (stmt.kind == StmtKind_sk_error_decl) {
    return;
}
}
void CodegenBuilder_gen_else_chain(CodegenBuilder* self, int64_t else_idx) {
    StmtNode else_node = ArrayList_StmtNode_get(self->stmt_pool, else_idx);
    if ((else_node.kind == StmtKind_sk_block) && (ArrayList_Int_length(&(else_node.block_stmts)) == 1LL)) {
    int64_t single_stmt_idx = ArrayList_Int_get(&(else_node.block_stmts), 0LL);
    StmtNode single_stmt = ArrayList_StmtNode_get(self->stmt_pool, single_stmt_idx);
    if (single_stmt.kind == StmtKind_sk_if) {
    const char* inner_cond = CodegenBuilder_gen_expr_str(self, single_stmt.if_cond);
    CCodeBuilder_append_to_last_line(&(self->builder), concatAlloc(" else if ", CodegenBuilder_format_cond(self, inner_cond)));
    CodegenBuilder_gen_stmt(self, single_stmt.if_then);
    if (single_stmt.if_else >= 0LL) {
    CodegenBuilder_gen_else_chain(self, single_stmt.if_else);
}
    return;
}
}
    CCodeBuilder_append_to_last_line(&(self->builder), " else");
    CodegenBuilder_gen_stmt(self, else_idx);
}
void CodegenBuilder_build_func_types(CodegenBuilder* self) {
    int64_t i = 0LL;
    while (i < ArrayList_StmtNode_length(self->stmt_pool)) {
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, i);
    if (stmt.kind == StmtKind_sk_struct_decl) {
    if (ArrayList_Str_length(&(stmt.struct_type_params)) > 0LL) {
    cgb_map_put(&(self->generic_struct_decls), stmt.struct_name, cgb_int_to_str(i));
}
}
    if (stmt.kind == StmtKind_sk_enum_decl) {
    if (ArrayList_Str_length(&(stmt.enum_type_params)) > 0LL) {
    cgb_map_put(&(self->generic_enum_decls), stmt.enum_name, cgb_int_to_str(i));
}
}
    i = (i + 1LL);
}
    int64_t i1 = 0LL;
    while (i1 < ArrayList_StmtNode_length(self->stmt_pool)) {
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, i1);
    if ((stmt.kind == StmtKind_sk_struct_decl) && (ArrayList_Str_length(&(stmt.struct_type_params)) == 0LL)) {
    const char* cname = CodegenBuilder_map_type(self, stmt.struct_name);
    CDeclNode struct_decl = (CDeclNode){ .is_function = false, .func_ret = ctype_void(), .func_name = "", .func_params = ArrayList_Str_init(self->allocator), .func_vararg = false, .func_body = ArrayList_Int_init(self->allocator), .is_extern = false, .var_type = ctype_void(), .var_name = "", .var_init = (-1LL), .is_struct = false, .struct_name = "", .struct_fields = ArrayList_Str_init(self->allocator), .is_enum = false, .enum_name = "", .enum_variants = ArrayList_Str_init(self->allocator), .is_tagged_enum = false, .tagged_name = "", .tagged_variants = ArrayList_Str_init(self->allocator), .is_tagged_union_struct = false, .is_typedef = true, .typedef_alias = cname, .typedef_def = ctype_new(concatAlloc("struct ", cname), 0LL, false, false) };
    CCodeBuilder local_builder = (CCodeBuilder){ .alloc = self->allocator, .lines = ArrayList_Str_init(self->allocator), .indent_level = 0LL };
    local_builder = CCodeBuilder_init(self->allocator);
    CPrinter printer = (CPrinter){ .builder = &(local_builder), .expr_pool = &(self->c_exprs), .stmt_pool = &(self->c_stmts) };
    CPrinter_print_decl(&(printer), struct_decl);
    StrBuf_append(&(self->type_defs), CCodeBuilder_to_str(&(local_builder)));
}
    if ((stmt.kind == StmtKind_sk_enum_decl) && (ArrayList_Str_length(&(stmt.enum_type_params)) == 0LL)) {
    cgb_map_put(&(self->enum_decls), stmt.enum_name, cgb_int_to_str(i1));
    const char* cename = CodegenBuilder_map_type(self, stmt.enum_name);
    bool has_payload = false;
    int64_t vi = 0LL;
    while (vi < ArrayList_Variant_length(&(stmt.enum_variants))) {
    Variant v = ArrayList_Variant_get(&(stmt.enum_variants), vi);
    if (ArrayList_Param_length(&(v.params)) > 0LL) {
    has_payload = true;
}
    vi = (vi + 1LL);
}
    if (!has_payload) {
    ArrayList_Str variants_list = ArrayList_Str_init(self->allocator);
    int64_t vi2 = 0LL;
    while (vi2 < ArrayList_Variant_length(&(stmt.enum_variants))) {
    Variant v = ArrayList_Variant_get(&(stmt.enum_variants), vi2);
    ArrayList_Str_push(&(variants_list), concatAlloc(concatAlloc(concatAlloc(concatAlloc("    ", cename), "_"), v.vname), ","));
    vi2 = (vi2 + 1LL);
}
    CDeclNode enum_decl = (CDeclNode){ .is_function = false, .func_ret = ctype_void(), .func_name = "", .func_params = ArrayList_Str_init(self->allocator), .func_vararg = false, .func_body = ArrayList_Int_init(self->allocator), .is_extern = false, .var_type = ctype_void(), .var_name = "", .var_init = (-1LL), .is_struct = false, .struct_name = "", .struct_fields = ArrayList_Str_init(self->allocator), .is_enum = true, .enum_name = cename, .enum_variants = variants_list, .is_tagged_enum = false, .tagged_name = "", .tagged_variants = ArrayList_Str_init(self->allocator), .is_tagged_union_struct = false, .is_typedef = false, .typedef_alias = "", .typedef_def = ctype_void() };
    CCodeBuilder local_builder = (CCodeBuilder){ .alloc = self->allocator, .lines = ArrayList_Str_init(self->allocator), .indent_level = 0LL };
    local_builder = CCodeBuilder_init(self->allocator);
    CPrinter printer = (CPrinter){ .builder = &(local_builder), .expr_pool = &(self->c_exprs), .stmt_pool = &(self->c_stmts) };
    CPrinter_print_decl(&(printer), enum_decl);
    StrBuf_append(&(self->type_defs), CCodeBuilder_to_str(&(local_builder)));
} else {
    const char* tags_name = concatAlloc(cename, "_tags");
    ArrayList_Str variants_list = ArrayList_Str_init(self->allocator);
    int64_t vi3 = 0LL;
    while (vi3 < ArrayList_Variant_length(&(stmt.enum_variants))) {
    Variant v = ArrayList_Variant_get(&(stmt.enum_variants), vi3);
    ArrayList_Str_push(&(variants_list), concatAlloc(concatAlloc(concatAlloc(concatAlloc("    ", cename), "_"), v.vname), "_TAG,"));
    vi3 = (vi3 + 1LL);
}
    CDeclNode enum_decl = (CDeclNode){ .is_function = false, .func_ret = ctype_void(), .func_name = "", .func_params = ArrayList_Str_init(self->allocator), .func_vararg = false, .func_body = ArrayList_Int_init(self->allocator), .is_extern = false, .var_type = ctype_void(), .var_name = "", .var_init = (-1LL), .is_struct = false, .struct_name = "", .struct_fields = ArrayList_Str_init(self->allocator), .is_enum = true, .enum_name = tags_name, .enum_variants = variants_list, .is_tagged_enum = false, .tagged_name = "", .tagged_variants = ArrayList_Str_init(self->allocator), .is_tagged_union_struct = false, .is_typedef = false, .typedef_alias = "", .typedef_def = ctype_void() };
    CCodeBuilder local_builder = (CCodeBuilder){ .alloc = self->allocator, .lines = ArrayList_Str_init(self->allocator), .indent_level = 0LL };
    local_builder = CCodeBuilder_init(self->allocator);
    CPrinter printer = (CPrinter){ .builder = &(local_builder), .expr_pool = &(self->c_exprs), .stmt_pool = &(self->c_stmts) };
    CPrinter_print_decl(&(printer), enum_decl);
    StrBuf_append(&(self->type_defs), CCodeBuilder_to_str(&(local_builder)));
    CDeclNode struct_decl = (CDeclNode){ .is_function = false, .func_ret = ctype_void(), .func_name = "", .func_params = ArrayList_Str_init(self->allocator), .func_vararg = false, .func_body = ArrayList_Int_init(self->allocator), .is_extern = false, .var_type = ctype_void(), .var_name = "", .var_init = (-1LL), .is_struct = false, .struct_name = "", .struct_fields = ArrayList_Str_init(self->allocator), .is_enum = false, .enum_name = "", .enum_variants = ArrayList_Str_init(self->allocator), .is_tagged_enum = false, .tagged_name = "", .tagged_variants = ArrayList_Str_init(self->allocator), .is_tagged_union_struct = false, .is_typedef = true, .typedef_alias = cename, .typedef_def = ctype_new(concatAlloc("struct ", cename), 0LL, false, false) };
    CCodeBuilder local_builder2 = (CCodeBuilder){ .alloc = self->allocator, .lines = ArrayList_Str_init(self->allocator), .indent_level = 0LL };
    local_builder2 = CCodeBuilder_init(self->allocator);
    CPrinter printer2 = (CPrinter){ .builder = &(local_builder2), .expr_pool = &(self->c_exprs), .stmt_pool = &(self->c_stmts) };
    CPrinter_print_decl(&(printer2), struct_decl);
    StrBuf_append(&(self->type_defs), CCodeBuilder_to_str(&(local_builder2)));
}
}
    if (stmt.kind == StmtKind_sk_error_decl) {
    const char* cename = CodegenBuilder_map_type(self, stmt.error_name);
    ArrayList_Str variants_list = ArrayList_Str_init(self->allocator);
    int64_t vi5 = 0LL;
    while (vi5 < ArrayList_Str_length(&(stmt.error_variants))) {
    const char* vname = ArrayList_Str_get(&(stmt.error_variants), vi5);
    ArrayList_Str_push(&(variants_list), concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc("    ", cename), "_"), vname), " = "), cgb_int_to_str((vi5 + 1LL))), ","));
    vi5 = (vi5 + 1LL);
}
    CDeclNode enum_decl = (CDeclNode){ .is_function = false, .func_ret = ctype_void(), .func_name = "", .func_params = ArrayList_Str_init(self->allocator), .func_vararg = false, .func_body = ArrayList_Int_init(self->allocator), .is_extern = false, .var_type = ctype_void(), .var_name = "", .var_init = (-1LL), .is_struct = false, .struct_name = "", .struct_fields = ArrayList_Str_init(self->allocator), .is_enum = true, .enum_name = cename, .enum_variants = variants_list, .is_tagged_enum = false, .tagged_name = "", .tagged_variants = ArrayList_Str_init(self->allocator), .is_tagged_union_struct = false, .is_typedef = false, .typedef_alias = "", .typedef_def = ctype_void() };
    CCodeBuilder local_builder = (CCodeBuilder){ .alloc = self->allocator, .lines = ArrayList_Str_init(self->allocator), .indent_level = 0LL };
    local_builder = CCodeBuilder_init(self->allocator);
    CPrinter printer = (CPrinter){ .builder = &(local_builder), .expr_pool = &(self->c_exprs), .stmt_pool = &(self->c_stmts) };
    CPrinter_print_decl(&(printer), enum_decl);
    StrBuf_append(&(self->type_defs), CCodeBuilder_to_str(&(local_builder)));
}
    i1 = (i1 + 1LL);
}
    int64_t i2a = 0LL;
    while (i2a < ArrayList_StmtNode_length(self->stmt_pool)) {
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, i2a);
    if (stmt.kind == StmtKind_sk_func_decl) {
    bool has_self_param = false;
    int64_t pi = 0LL;
    while (pi < ArrayList_Param_length(&(stmt.func_params))) {
    Param p = ArrayList_Param_get(&(stmt.func_params), pi);
    {
    if (strcmp(p.name, "self") == 0LL) {
    has_self_param = true;
}
}
    pi = (pi + 1LL);
}
    if (!has_self_param) {
    const char* params_str = "";
    int64_t pi2 = 0LL;
    while (pi2 < ArrayList_Param_length(&(stmt.func_params))) {
    Param p = ArrayList_Param_get(&(stmt.func_params), pi2);
    if (pi2 > 0LL) {
    params_str = concatAlloc(params_str, ", ");
}
    const char* ctype = CodegenBuilder_map_type(self, p.ptype);
    params_str = concatAlloc(concatAlloc(concatAlloc(params_str, ctype), " "), p.name);
    pi2 = (pi2 + 1LL);
}
    const char* func_type_str = concatAlloc(concatAlloc(params_str, ":"), stmt.func_return_type);
    cgb_map_put(&(self->func_types), stmt.func_name, func_type_str);
    int64_t p_i = 0LL;
    while (p_i < ArrayList_Param_length(&(stmt.func_params))) {
    Param p = ArrayList_Param_get(&(stmt.func_params), p_i);
    const char* p_key = concatAlloc(concatAlloc(stmt.func_name, "_param_"), cgb_int_to_str(p_i));
    cgb_map_put(&(self->func_param_types), p_key, p.ptype);
    p_i = (p_i + 1LL);
}
}
}
    if (stmt.kind == StmtKind_sk_extern) {
    cgb_map_put(&(self->func_types), stmt.extern_name, stmt.extern_return);
    int64_t p_i = 0LL;
    while (p_i < ArrayList_Param_length(&(stmt.extern_params))) {
    Param p = ArrayList_Param_get(&(stmt.extern_params), p_i);
    const char* p_key = concatAlloc(concatAlloc(stmt.extern_name, "_param_"), cgb_int_to_str(p_i));
    cgb_map_put(&(self->func_param_types), p_key, p.ptype);
    p_i = (p_i + 1LL);
}
}
    if (stmt.kind == StmtKind_sk_impl_block) {
    const char* struct_name = stmt.impl_struct_name;
    if ((cgb_map_find(&(self->generic_struct_decls), struct_name) < 0LL) && (cgb_map_find(&(self->generic_enum_decls), struct_name) < 0LL)) {
    int64_t j = 0LL;
    while (j < ArrayList_Int_length(&(stmt.impl_methods))) {
    int64_t m_idx = ArrayList_Int_get(&(stmt.impl_methods), j);
    StmtNode m_node = ArrayList_StmtNode_get(self->stmt_pool, m_idx);
    const char* method_name = m_node.func_name;
    bool is_init = ((((strcmp(method_name, "init") == 0) || (strcmp(m_node.func_return_type, struct_name) == 0)) || (strcmp(m_node.func_return_type, concatAlloc("*", struct_name)) == 0)) || (strcmp(m_node.func_return_type, concatAlloc("&", struct_name)) == 0));
    const char* key = concatAlloc(concatAlloc(struct_name, "_"), method_name);
    const char* ret = m_node.func_return_type;
    if (is_init) {
    ret = struct_name;
}
    cgb_map_put(&(self->func_types), key, ret);
    int64_t p_i = 0LL;
    while (p_i < ArrayList_Param_length(&(m_node.func_params))) {
    Param p = ArrayList_Param_get(&(m_node.func_params), p_i);
    const char* p_key = concatAlloc(concatAlloc(key, "_param_"), cgb_int_to_str(p_i));
    cgb_map_put(&(self->func_param_types), p_key, p.ptype);
    p_i = (p_i + 1LL);
}
    j = (j + 1LL);
}
}
}
    i2a = (i2a + 1LL);
}
    int64_t i2 = 0LL;
    while (i2 < ArrayList_StmtNode_length(self->stmt_pool)) {
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, i2);
    {
    printf("Phase 3b: i2=%d, stmt.kind=%d\n", i2, stmt.kind);
}
    if (stmt.kind == StmtKind_sk_func_decl) {
    bool has_self_param = false;
    int64_t pi = 0LL;
    while (pi < ArrayList_Param_length(&(stmt.func_params))) {
    Param p = ArrayList_Param_get(&(stmt.func_params), pi);
    {
    if (strcmp(p.name, "self") == 0LL) {
    has_self_param = true;
}
}
    pi = (pi + 1LL);
}
    if (has_self_param) {
} else if (ArrayList_Str_length(&(stmt.func_type_params)) > 0LL) {
} else if (stmt.func_body < 0LL) {
} else {
    {
    printf("gen_func_decl: name=%s, param_count=%d, body_idx=%d\n", stmt.func_name, ArrayList_Param_length(&(stmt.func_params)), stmt.func_body);
}
    self->var_types = ArrayList_CgbMapEntry_init(self->allocator);
    self->block_stack = ArrayList_Int_init(self->allocator);
    const char* params_str = "";
    int64_t pi2 = 0LL;
    while (pi2 < ArrayList_Param_length(&(stmt.func_params))) {
    Param p = ArrayList_Param_get(&(stmt.func_params), pi2);
    if (pi2 > 0LL) {
    params_str = concatAlloc(params_str, ", ");
}
    const char* ctype = CodegenBuilder_map_type(self, p.ptype);
    params_str = concatAlloc(concatAlloc(concatAlloc(params_str, ctype), " "), p.name);
    cgb_map_put(&(self->var_types), p.name, p.ptype);
    pi2 = (pi2 + 1LL);
}
    const char* ret_type = CodegenBuilder_map_type(self, stmt.func_return_type);
    self->cur_func_name = stmt.func_name;
    self->cur_return_type = stmt.func_return_type;
    self->cur_method_is_init = false;
    bool is_main = false;
    {
    if (strcmp(stmt.func_name, "main") == 0LL) {
    is_main = true;
}
}
    const char* decl_ret = ret_type;
    const char* decl_params = params_str;
    const char* impl_header = concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(ret_type, " "), stmt.func_name), "("), params_str), ")");
    if (is_main) {
    decl_ret = "int";
    decl_params = "int argc, char** argv";
    impl_header = "int main(int argc, char** argv)";
}
    if (!is_main) {
    ArrayList_Str params_list = ArrayList_Str_init(self->allocator);
    int64_t pi3 = 0LL;
    while (pi3 < ArrayList_Param_length(&(stmt.func_params))) {
    Param p = ArrayList_Param_get(&(stmt.func_params), pi3);
    ArrayList_Str_push(&(params_list), concatAlloc(concatAlloc(CodegenBuilder_map_type(self, p.ptype), " "), p.name));
    pi3 = (pi3 + 1LL);
}
    CDeclNode func_decl = cdecl_new_func(stmt.func_name, decl_ret, params_list, false, false);
    CCodeBuilder local_builder = (CCodeBuilder){ .alloc = self->allocator, .lines = ArrayList_Str_init(self->allocator), .indent_level = 0LL };
    local_builder = CCodeBuilder_init(self->allocator);
    CPrinter printer = (CPrinter){ .builder = &(local_builder), .expr_pool = &(self->c_exprs), .stmt_pool = &(self->c_stmts) };
    CPrinter_print_decl(&(printer), func_decl);
    StrBuf_append(&(self->func_decls), CCodeBuilder_to_str(&(local_builder)));
}
    int64_t body_idx = stmt.func_body;
    if (body_idx >= 0LL) {
    StmtNode body_stmt = ArrayList_StmtNode_get(self->stmt_pool, body_idx);
    if (body_stmt.kind == StmtKind_sk_block) {
    CCodeBuilder_emit_line(&(self->builder), impl_header);
    CodegenBuilder_gen_stmt(self, body_idx);
    StrBuf_append(&(self->output_body), CCodeBuilder_to_str(&(self->builder)));
    CCodeBuilder_clear(&(self->builder));
}
}
}
}
    if (stmt.kind == StmtKind_sk_extern) {
    if (!CodegenBuilder_is_standard_c_func(self, stmt.extern_name)) {
    {
    const char* params_str = "";
    int64_t pi3 = 0LL;
    while (pi3 < ArrayList_Param_length(&(stmt.extern_params))) {
    Param p = ArrayList_Param_get(&(stmt.extern_params), pi3);
    if (pi3 > 0LL) {
    params_str = concatAlloc(params_str, ", ");
}
    params_str = concatAlloc(concatAlloc(concatAlloc(params_str, CodegenBuilder_map_type(self, p.ptype)), " "), p.name);
    pi3 = (pi3 + 1LL);
}
    const char* ret_type = CodegenBuilder_map_type(self, stmt.extern_return);
    ArrayList_Str ex_params = ArrayList_Str_init(self->allocator);
    int64_t pi4 = 0LL;
    while (pi4 < ArrayList_Param_length(&(stmt.extern_params))) {
    Param p = ArrayList_Param_get(&(stmt.extern_params), pi4);
    ArrayList_Str_push(&(ex_params), concatAlloc(concatAlloc(CodegenBuilder_map_type(self, p.ptype), " "), p.name));
    pi4 = (pi4 + 1LL);
}
    CDeclNode ext_decl = cdecl_new_func(stmt.extern_name, ret_type, ex_params, true, false);
    CCodeBuilder local_builder = (CCodeBuilder){ .alloc = self->allocator, .lines = ArrayList_Str_init(self->allocator), .indent_level = 0LL };
    local_builder = CCodeBuilder_init(self->allocator);
    CPrinter printer = (CPrinter){ .builder = &(local_builder), .expr_pool = &(self->c_exprs), .stmt_pool = &(self->c_stmts) };
    CPrinter_print_decl(&(printer), ext_decl);
    StrBuf_append(&(self->func_decls), CCodeBuilder_to_str(&(local_builder)));
}
}
}
    if (stmt.kind == StmtKind_sk_impl_block) {
    const char* struct_name = stmt.impl_struct_name;
    if ((cgb_map_find(&(self->generic_struct_decls), struct_name) >= 0LL) || (cgb_map_find(&(self->generic_enum_decls), struct_name) >= 0LL)) {
    i2 = (i2 + 1LL);
    continue;
}
    const char* mapped_name = CodegenBuilder_map_type(self, struct_name);
    int64_t j = 0LL;
    while (j < ArrayList_Int_length(&(stmt.impl_methods))) {
    int64_t m_idx = ArrayList_Int_get(&(stmt.impl_methods), j);
    StmtNode m_node = ArrayList_StmtNode_get(self->stmt_pool, m_idx);
    const char* method_name = m_node.func_name;
    bool is_init = ((((strcmp(method_name, "init") == 0) || (strcmp(m_node.func_return_type, struct_name) == 0)) || (strcmp(m_node.func_return_type, concatAlloc("*", struct_name)) == 0)) || (strcmp(m_node.func_return_type, concatAlloc("&", struct_name)) == 0));
    self->var_types = ArrayList_CgbMapEntry_init(self->allocator);
    self->block_stack = ArrayList_Int_init(self->allocator);
    const char* params_str = "";
    if (!is_init) {
    params_str = concatAlloc(mapped_name, "* self");
    cgb_map_put(&(self->var_types), "self", concatAlloc("*", struct_name));
} else {
    cgb_map_put(&(self->var_types), "self", struct_name);
}
    int64_t pi2 = 0LL;
    while (pi2 < ArrayList_Param_length(&(m_node.func_params))) {
    Param p = ArrayList_Param_get(&(m_node.func_params), pi2);
    bool is_self = false;
    {
    if (strcmp(p.name, "self") == 0LL) {
    is_self = true;
}
}
    if (!is_self) {
    if (strlen(params_str) > 0LL) {
    params_str = concatAlloc(params_str, ", ");
}
    const char* ctype = CodegenBuilder_map_type(self, p.ptype);
    params_str = concatAlloc(concatAlloc(concatAlloc(params_str, ctype), " "), p.name);
    cgb_map_put(&(self->var_types), p.name, p.ptype);
}
    pi2 = (pi2 + 1LL);
}
    if (strlen(params_str) == 0LL) {
    params_str = "void";
}
    const char* ret = m_node.func_return_type;
    if (is_init) {
    ret = struct_name;
}
    const char* ret_type = CodegenBuilder_map_type(self, ret);
    const char* mangled_fn = concatAlloc(concatAlloc(mapped_name, "_"), method_name);
    self->cur_func_name = mangled_fn;
    self->cur_return_type = ret;
    self->cur_method_is_init = is_init;
    ArrayList_Str impl_params = ArrayList_Str_init(self->allocator);
    if (!is_init) {
    ArrayList_Str_push(&(impl_params), concatAlloc(mapped_name, "* self"));
}
    int64_t pi3 = 0LL;
    while (pi3 < ArrayList_Param_length(&(m_node.func_params))) {
    Param p = ArrayList_Param_get(&(m_node.func_params), pi3);
    bool is_self2 = false;
    {
    if (strcmp(p.name, "self") == 0LL) {
    is_self2 = true;
}
}
    if (!is_self2) {
    ArrayList_Str_push(&(impl_params), concatAlloc(concatAlloc(CodegenBuilder_map_type(self, p.ptype), " "), p.name));
}
    pi3 = (pi3 + 1LL);
}
    if (ArrayList_Str_length(&(impl_params)) == 0LL) {
    ArrayList_Str_push(&(impl_params), "void");
}
    CDeclNode impl_decl = cdecl_new_func(mangled_fn, ret_type, impl_params, false, false);
    CCodeBuilder local_builder = (CCodeBuilder){ .alloc = self->allocator, .lines = ArrayList_Str_init(self->allocator), .indent_level = 0LL };
    local_builder = CCodeBuilder_init(self->allocator);
    CPrinter printer = (CPrinter){ .builder = &(local_builder), .expr_pool = &(self->c_exprs), .stmt_pool = &(self->c_stmts) };
    CPrinter_print_decl(&(printer), impl_decl);
    StrBuf_append(&(self->func_decls), CCodeBuilder_to_str(&(local_builder)));
    int64_t body_idx = m_node.func_body;
    if (body_idx >= 0LL) {
    StmtNode body_stmt = ArrayList_StmtNode_get(self->stmt_pool, body_idx);
    if (body_stmt.kind == StmtKind_sk_block) {
    CCodeBuilder_emit_line(&(self->builder), concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(ret_type, " "), mangled_fn), "("), params_str), ")"));
    CodegenBuilder_gen_stmt(self, body_idx);
    const char* body_str = CCodeBuilder_to_str(&(self->builder));
    if (is_init) {
    int64_t brace_pos = 0LL;
    while (brace_pos < strlen(body_str)) {
    if ((body_str)[brace_pos] == ((char)(123LL))) {
    break;
}
    brace_pos = (brace_pos + 1LL);
}
    const char* header = __kai_str_sub(body_str, 0LL, brace_pos);
    const char* raw_body = __kai_str_sub(body_str, brace_pos, strlen(body_str));
    body_str = concatAlloc(header, CodegenBuilder_add_init_return(self, raw_body, mapped_name));
}
    StrBuf_append(&(self->output_body), body_str);
    CCodeBuilder_clear(&(self->builder));
}
}
    j = (j + 1LL);
}
}
    i2 = (i2 + 1LL);
}
    ArrayList_Str emitted_struct_bodies = ArrayList_Str_init(self->allocator);
    int64_t i4 = 0LL;
    while (i4 < ArrayList_StmtNode_length(self->stmt_pool)) {
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, i4);
    if (stmt.kind == StmtKind_sk_struct_decl) {
    CodegenBuilder_emit_struct_body_with_deps(self, i4, &(emitted_struct_bodies));
}
    if (stmt.kind == StmtKind_sk_enum_decl) {
    const char* ename = stmt.enum_name;
    if (ArrayList_Str_length(&(stmt.enum_type_params)) == 0LL) {
    const char* cename = CodegenBuilder_map_type(self, ename);
    bool has_payload = false;
    int64_t vi = 0LL;
    while (vi < ArrayList_Variant_length(&(stmt.enum_variants))) {
    Variant v = ArrayList_Variant_get(&(stmt.enum_variants), vi);
    if (ArrayList_Param_length(&(v.params)) > 0LL) {
    has_payload = true;
}
    vi = (vi + 1LL);
}
    if (has_payload) {
    ArrayList_Str variants_list = ArrayList_Str_init(self->allocator);
    int64_t vi4 = 0LL;
    while (vi4 < ArrayList_Variant_length(&(stmt.enum_variants))) {
    Variant v = ArrayList_Variant_get(&(stmt.enum_variants), vi4);
    if (ArrayList_Param_length(&(v.params)) > 0LL) {
    const char* variant_str = "struct { ";
    int64_t pi3 = 0LL;
    while (pi3 < ArrayList_Param_length(&(v.params))) {
    if (pi3 > 0LL) {
    variant_str = concatAlloc(variant_str, " ");
}
    Param p = ArrayList_Param_get(&(v.params), pi3);
    variant_str = concatAlloc(concatAlloc(concatAlloc(concatAlloc(variant_str, CodegenBuilder_map_type(self, p.ptype)), " "), p.name), ";");
    pi3 = (pi3 + 1LL);
}
    variant_str = concatAlloc(concatAlloc(concatAlloc(variant_str, " } "), v.vname), ";");
    ArrayList_Str_push(&(variants_list), variant_str);
}
    vi4 = (vi4 + 1LL);
}
    CDeclNode union_decl = (CDeclNode){ .is_function = false, .func_ret = ctype_void(), .func_name = "", .func_params = ArrayList_Str_init(self->allocator), .func_vararg = false, .func_body = ArrayList_Int_init(self->allocator), .is_extern = false, .var_type = ctype_void(), .var_name = "", .var_init = (-1LL), .is_struct = false, .struct_name = cename, .struct_fields = ArrayList_Str_init(self->allocator), .is_enum = false, .enum_name = "", .enum_variants = ArrayList_Str_init(self->allocator), .is_tagged_enum = false, .tagged_name = "", .tagged_variants = variants_list, .is_tagged_union_struct = true, .is_typedef = false, .typedef_alias = "", .typedef_def = ctype_void() };
    CCodeBuilder local_builder = (CCodeBuilder){ .alloc = self->allocator, .lines = ArrayList_Str_init(self->allocator), .indent_level = 0LL };
    local_builder = CCodeBuilder_init(self->allocator);
    CPrinter printer = (CPrinter){ .builder = &(local_builder), .expr_pool = &(self->c_exprs), .stmt_pool = &(self->c_stmts) };
    CPrinter_print_decl(&(printer), union_decl);
    StrBuf_append(&(self->struct_decls), CCodeBuilder_to_str(&(local_builder)));
}
}
}
    i4 = (i4 + 1LL);
}
}
void CodegenBuilder_emit_struct_body_with_deps(CodegenBuilder* self, int64_t stmt_idx, ArrayList_Str* emitted) {
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, stmt_idx);
    if (stmt.kind != StmtKind_sk_struct_decl) {
    return;
}
    if (ArrayList_Str_length(&(stmt.struct_type_params)) > 0LL) {
    return;
}
    const char* cname = CodegenBuilder_map_type(self, stmt.struct_name);
    if (cgb_strlist_find(emitted, cname) >= 0LL) {
    return;
}
    ArrayList_Str_push(emitted, cname);
    int64_t fi = 0LL;
    while (fi < ArrayList_StructField_length(&(stmt.struct_fields))) {
    StructField f = ArrayList_StructField_get(&(stmt.struct_fields), fi);
    const char* ftype = f.ftype;
    {
    if (((strlen(ftype) > 0LL) && ((ftype)[0LL] != ((char)(42LL)))) && ((ftype)[0LL] != ((char)(38LL)))) {
    int64_t si = 0LL;
    while (si < ArrayList_StmtNode_length(self->stmt_pool)) {
    StmtNode s2 = ArrayList_StmtNode_get(self->stmt_pool, si);
    if ((s2.kind == StmtKind_sk_struct_decl) && (ArrayList_Str_length(&(s2.struct_type_params)) == 0LL)) {
    if (strcmp(s2.struct_name, ftype) == 0) {
    CodegenBuilder_emit_struct_body_with_deps(self, si, emitted);
}
}
    si = (si + 1LL);
}
}
}
    fi = (fi + 1LL);
}
    ArrayList_Str fields = ArrayList_Str_init(self->allocator);
    int64_t fi2 = 0LL;
    while (fi2 < ArrayList_StructField_length(&(stmt.struct_fields))) {
    StructField f = ArrayList_StructField_get(&(stmt.struct_fields), fi2);
    ArrayList_Str_push(&(fields), concatAlloc(concatAlloc(concatAlloc(CodegenBuilder_map_type(self, f.ftype), " "), f.name), ";"));
    fi2 = (fi2 + 1LL);
}
    CDeclNode body_decl = (CDeclNode){ .is_function = false, .func_ret = ctype_void(), .func_name = "", .func_params = ArrayList_Str_init(self->allocator), .func_vararg = false, .func_body = ArrayList_Int_init(self->allocator), .is_extern = false, .var_type = ctype_void(), .var_name = "", .var_init = (-1LL), .is_struct = true, .struct_name = cname, .struct_fields = fields, .is_enum = false, .enum_name = "", .enum_variants = ArrayList_Str_init(self->allocator), .is_tagged_enum = false, .tagged_name = "", .tagged_variants = ArrayList_Str_init(self->allocator), .is_tagged_union_struct = false, .is_typedef = false, .typedef_alias = "", .typedef_def = ctype_void() };
    CCodeBuilder local_builder = (CCodeBuilder){ .alloc = self->allocator, .lines = ArrayList_Str_init(self->allocator), .indent_level = 0LL };
    local_builder = CCodeBuilder_init(self->allocator);
    CPrinter printer = (CPrinter){ .builder = &(local_builder), .expr_pool = &(self->c_exprs), .stmt_pool = &(self->c_stmts) };
    CPrinter_print_decl(&(printer), body_decl);
    StrBuf_append(&(self->struct_decls), CCodeBuilder_to_str(&(local_builder)));
    int64_t ti = 0LL;
    while (ti < ArrayList_Int_length(&(stmt.struct_trait_impls))) {
    int64_t impl_idx = ArrayList_Int_get(&(stmt.struct_trait_impls), ti);
    StmtNode impl_node = ArrayList_StmtNode_get(self->stmt_pool, impl_idx);
    int64_t j = 0LL;
    while (j < ArrayList_Int_length(&(impl_node.impl_methods))) {
    int64_t m_idx = ArrayList_Int_get(&(impl_node.impl_methods), j);
    StmtNode m_node = ArrayList_StmtNode_get(self->stmt_pool, m_idx);
    const char* key = concatAlloc(concatAlloc(stmt.struct_name, "_"), m_node.func_name);
    const char* ret = m_node.func_return_type;
    if (strcmp(m_node.func_name, "init") == 0) {
    ret = stmt.struct_name;
}
    cgb_map_put(&(self->func_types), key, ret);
    int64_t p_i = 0LL;
    while (p_i < ArrayList_Param_length(&(m_node.func_params))) {
    Param p = ArrayList_Param_get(&(m_node.func_params), p_i);
    const char* p_key = concatAlloc(concatAlloc(key, "_param_"), cgb_int_to_str(p_i));
    cgb_map_put(&(self->func_param_types), p_key, p.ptype);
    p_i = (p_i + 1LL);
}
    j = (j + 1LL);
}
    ti = (ti + 1LL);
}
}
const char* CodegenBuilder_generate(CodegenBuilder* self, int64_t top_stmt_idx) {
    CodegenBuilder_build_func_types(self);
    StrBuf result = StrBuf_init(self->allocator);
    result = StrBuf_init(self->allocator);
    CCodeBuilder preamble_builder = (CCodeBuilder){ .alloc = self->allocator, .lines = ArrayList_Str_init(self->allocator), .indent_level = 0LL };
    preamble_builder = CCodeBuilder_init(self->allocator);
    CPrinter preamble_printer = (CPrinter){ .builder = &(preamble_builder), .expr_pool = &(self->c_exprs), .stmt_pool = &(self->c_stmts) };
    CPrinter_emit_runtime_preamble(&(preamble_printer), &(self->import_resolver->cimport_headers));
    const char* preamble_str = CCodeBuilder_to_str(&(preamble_builder));
    StrBuf_append(&(result), preamble_str);
    StrBuf_append(&(result), "\n");
    StrBuf_append(&(result), StrBuf_to_str(&(self->type_defs)));
    StrBuf_append(&(result), "\n");
    StrBuf_append(&(result), StrBuf_to_str(&(self->struct_decls)));
    StrBuf_append(&(result), "\n");
    const char* func_decl_str = StrBuf_to_str(&(self->func_decls));
    if (strlen(func_decl_str) > 0LL) {
    StrBuf_append(&(result), func_decl_str);
    StrBuf_append(&(result), "\n");
}
    const char* output_body_str = StrBuf_to_str(&(self->output_body));
    if (strlen(output_body_str) > 0LL) {
    StrBuf_append(&(result), output_body_str);
}
    const char* monomorphized_str = StrBuf_to_str(&(self->monomorphized_bodies));
    if (strlen(monomorphized_str) > 0LL) {
    StrBuf_append(&(result), monomorphized_str);
}
    const char* _final_r = StrBuf_to_str(&(result));
    return _final_r;
}
CCodeBuilder CCodeBuilder_init(KaiAllocator* allocator) {
    CCodeBuilder self = (CCodeBuilder){0};
    self.alloc = allocator;
    self.lines = ArrayList_Str_init(allocator);
    self.indent_level = 0LL;
    return self;
}
void CCodeBuilder_clear(CCodeBuilder* self) {
    self->lines = ArrayList_Str_init(self->alloc);
    self->indent_level = 0LL;
}
void CCodeBuilder_emit_line(CCodeBuilder* self, const char* code) {
    const char* indent_str = "";
    int64_t i = 0LL;
    while (i < self->indent_level) {
    indent_str = concatAlloc(indent_str, "    ");
    i = (i + 1LL);
}
    ArrayList_Str_push(&(self->lines), concatAlloc(indent_str, code));
}
void CCodeBuilder_emit_blank(CCodeBuilder* self) {
    ArrayList_Str_push(&(self->lines), "");
}
void CCodeBuilder_emit_raw(CCodeBuilder* self, const char* code) {
    ArrayList_Str_push(&(self->lines), code);
}
void CCodeBuilder_append_to_last_line(CCodeBuilder* self, const char* suffix) {
    if (ArrayList_Str_length(&(self->lines)) > 0LL) {
    int64_t idx = (ArrayList_Str_length(&(self->lines)) - 1LL);
    const char* last = ArrayList_Str_get(&(self->lines), idx);
    ArrayList_Str_set(&(self->lines), idx, concatAlloc(last, suffix));
}
}
void CCodeBuilder_emit_include(CCodeBuilder* self, const char* header, bool is_system) {
    if (is_system) {
    ArrayList_Str_push(&(self->lines), concatAlloc(concatAlloc("#include <", header), ">"));
} else {
    ArrayList_Str_push(&(self->lines), concatAlloc(concatAlloc("#include \"", header), "\""));
}
}
void CCodeBuilder_emit_directive(CCodeBuilder* self, const char* code) {
    ArrayList_Str_push(&(self->lines), code);
}
void CCodeBuilder_indent(CCodeBuilder* self) {
    self->indent_level = (self->indent_level + 1LL);
}
void CCodeBuilder_dedent(CCodeBuilder* self) {
    if (self->indent_level > 0LL) {
    self->indent_level = (self->indent_level - 1LL);
}
}
void CCodeBuilder_begin_block(CCodeBuilder* self) {
    CCodeBuilder_emit_line(self, "{");
    CCodeBuilder_indent(self);
}
void CCodeBuilder_end_block(CCodeBuilder* self) {
    CCodeBuilder_dedent(self);
    CCodeBuilder_emit_line(self, "}");
}
const char* CCodeBuilder_to_str(CCodeBuilder* self) {
    const char* result = "";
    int64_t i = 0LL;
    while (i < ArrayList_Str_length(&(self->lines))) {
    if (i > 0LL) {
    result = concatAlloc(result, "\n");
}
    result = concatAlloc(result, ArrayList_Str_get(&(self->lines), i));
    i = (i + 1LL);
}
    result = concatAlloc(result, "\n");
    return result;
}
int64_t CCodeBuilder_line_count(CCodeBuilder* self) {
    return ArrayList_Str_length(&(self->lines));
}
const char* cb_escape_string(const char* s) {
    const char* res = "";
    int64_t i = 0LL;
    while (i < strlen(s)) {
    char c = (s)[i];
    if (c == ((char)(10LL))) {
    res = concatAlloc(res, "\\n");
} else if (c == ((char)(13LL))) {
    res = concatAlloc(res, "\\r");
} else if (c == ((char)(9LL))) {
    res = concatAlloc(res, "\\t");
} else if (c == ((char)(92LL))) {
    res = concatAlloc(res, "\\\\");
} else if (c == ((char)(34LL))) {
    res = concatAlloc(res, "\\\"");
} else {
    res = concatAlloc(res, cgb_char_to_str(c));
}
    i = (i + 1LL);
}
    return res;
}
const char* cb_escape_asm(const char* s) {
    const char* res = "";
    int64_t i = 0LL;
    while (i < strlen(s)) {
    char c = (s)[i];
    if (c == ((char)(10LL))) {
    res = concatAlloc(res, "\\n\\t");
} else if (c == ((char)(34LL))) {
    res = concatAlloc(res, "\\\"");
} else {
    res = concatAlloc(res, cgb_char_to_str(c));
}
    i = (i + 1LL);
}
    return res;
}
const char* cgb_char_to_str(char c) {
    {
    char* buf = (char*)(malloc(2LL));
    if (buf != (char*)(unsigned long long)(0LL)) {
    (buf)[0LL] = c;
    (buf)[1LL] = ((char)(0LL));
}
    return (const char*)(buf);
}
}
const char* cgb_int_to_str(int64_t n) {
    if (n == 0LL) {
    return "0";
}
    int64_t num = n;
    int64_t digits = 0LL;
    int64_t tmp = num;
    if (tmp < 0LL) {
    tmp = (-tmp);
}
    while (tmp > 0LL) {
    digits = (digits + 1LL);
    tmp = (tmp / 10LL);
}
    bool negative = false;
    if (num < 0LL) {
    negative = true;
    num = (-num);
}
    int64_t total_len = digits;
    if (negative) {
    total_len = (total_len + 1LL);
}
    {
    char* buf = (char*)(malloc((int64_t)((total_len + 1LL))));
    if (buf != (char*)(unsigned long long)(0LL)) {
    int64_t pos = total_len;
    (buf)[pos] = ((char)(0LL));
    while ((pos > 0LL) && (digits > 0LL)) {
    pos = (pos - 1LL);
    digits = (digits - 1LL);
    int64_t dv = (num % 10LL);
    (buf)[pos] = ((char)((48LL + dv)));
    num = (num / 10LL);
}
    if (negative) {
    pos = (pos - 1LL);
    (buf)[pos] = ((char)(45LL));
}
}
    return (const char*)(buf);
}
}
CType ctype_new(const char* base, int64_t pointer, bool is_const, bool is_unsigned) {
    CType t = (CType){ .base = base, .pointer = pointer, .is_const = is_const, .is_unsigned = is_unsigned, .array_sizes = (ArrayList_Str){ .data = (const char**)(unsigned long long)(0LL), .len = 0LL, .cap = 0LL, .allocator = (KaiAllocator*)(unsigned long long)(0LL) } };
    return t;
}
CType ctype_void(void) {
    return ctype_new("void", 0LL, false, false);
}
CType ctype_int(void) {
    return ctype_new("int64_t", 0LL, false, false);
}
CType ctype_bool(void) {
    return ctype_new("bool", 0LL, false, false);
}
CType ctype_char(void) {
    return ctype_new("char", 0LL, false, false);
}
CType ctype_float(void) {
    return ctype_new("double", 0LL, false, false);
}
CType ctype_str(void) {
    return ctype_new("char", 1LL, true, false);
}
CType ctype_ptr(CType inner) {
    CType t = inner;
    t.pointer = (t.pointer + 1LL);
    return t;
}
CType ctype_const(CType inner) {
    CType t = inner;
    t.is_const = true;
    return t;
}
const char* ctype_to_str(CType t) {
    const char* result = "";
    if (t.is_const) {
    result = "const ";
}
    if (t.is_unsigned) {
    result = concatAlloc(result, "unsigned ");
}
    result = concatAlloc(result, t.base);
    int64_t i = 0LL;
    while (i < t.pointer) {
    result = concatAlloc(result, "*");
    i = (i + 1LL);
}
    int64_t j = 0LL;
    while (j < ArrayList_Str_length(&(t.array_sizes))) {
    result = concatAlloc(concatAlloc(concatAlloc(result, "["), ArrayList_Str_get(&(t.array_sizes), j)), "]");
    j = (j + 1LL);
}
    return result;
}
CType ctype_from_kai(const char* kai_type) {
    if (strcmp(kai_type, "Int") == 0) {
    return ctype_int();
}
    if (strcmp(kai_type, "i8") == 0) {
    return ctype_new("int8_t", 0LL, false, false);
}
    if (strcmp(kai_type, "i32") == 0) {
    return ctype_new("int32_t", 0LL, false, false);
}
    if (strcmp(kai_type, "i16") == 0) {
    return ctype_new("int16_t", 0LL, false, false);
}
    if (strcmp(kai_type, "i64") == 0) {
    return ctype_new("int64_t", 0LL, false, false);
}
    if (strcmp(kai_type, "isize") == 0) {
    return ctype_new("intptr_t", 0LL, false, false);
}
    if (strcmp(kai_type, "u8") == 0) {
    return ctype_new("uint8_t", 0LL, false, true);
}
    if (strcmp(kai_type, "u16") == 0) {
    return ctype_new("uint16_t", 0LL, false, true);
}
    if (strcmp(kai_type, "u32") == 0) {
    return ctype_new("uint32_t", 0LL, false, true);
}
    if (strcmp(kai_type, "u64") == 0) {
    return ctype_new("uint64_t", 0LL, false, true);
}
    if (strcmp(kai_type, "usize") == 0) {
    return ctype_new("size_t", 0LL, false, true);
}
    if (strcmp(kai_type, "Bool") == 0) {
    return ctype_bool();
}
    if (strcmp(kai_type, "Char") == 0) {
    return ctype_char();
}
    if (strcmp(kai_type, "Float") == 0) {
    return ctype_float();
}
    if (strcmp(kai_type, "Void") == 0) {
    return ctype_void();
}
    if (strcmp(kai_type, "Str") == 0) {
    return ctype_str();
}
    return ctype_new(kai_type, 0LL, false, false);
}
CType ctype_copy(CType t) {
    ArrayList_Str sizes = (ArrayList_Str){ .data = (const char**)(unsigned long long)(0LL), .len = 0LL, .cap = 0LL, .allocator = (KaiAllocator*)(unsigned long long)(0LL) };
    return (CType){ .base = t.base, .pointer = t.pointer, .is_const = t.is_const, .is_unsigned = t.is_unsigned, .array_sizes = sizes };
}
CUnit cunit_new(ArrayList_Str includes, ArrayList_CDeclNode decls) {
    return (CUnit){ .includes = includes, .decls = decls };
}
CExprNode cexpr_new_int(const char* val) {
    ArrayList_Int args = (ArrayList_Int){ .data = (int64_t*)(unsigned long long)(0LL), .len = 0LL, .cap = 0LL, .allocator = (KaiAllocator*)(unsigned long long)(0LL) };
    ArrayList_Str fields = (ArrayList_Str){ .data = (const char**)(unsigned long long)(0LL), .len = 0LL, .cap = 0LL, .allocator = (KaiAllocator*)(unsigned long long)(0LL) };
    return (CExprNode){ .kind = CExprKind_ck_int_lit, .int_val = val, .float_val = "", .str_val = "", .char_val = "", .bool_val = false, .ident_name = "", .binop_left = (-1LL), .binop_right = (-1LL), .binop_op = "", .unop_operand = (-1LL), .unop_op = "", .is_prefix = false, .call_func = (-1LL), .call_args = args, .callee_name = "", .field_expr = (-1LL), .field_name = "", .idx_expr = (-1LL), .idx_index = (-1LL), .cast_type = ctype_void(), .cast_expr = (-1LL), .compound_type = ctype_void(), .compound_fields = fields, .tern_cond = (-1LL), .tern_then = (-1LL), .tern_else = (-1LL), .sizeof_type = ctype_void(), .sizeof_expr = (-1LL), .assign_target = (-1LL), .assign_value = (-1LL), .assign_op = "", .comma_left = (-1LL), .comma_right = (-1LL), .stmts = (ArrayList_Int){ .data = (int64_t*)(unsigned long long)(0LL), .len = 0LL, .cap = 0LL, .allocator = (KaiAllocator*)(unsigned long long)(0LL) }, .stmt_result = (-1LL) };
}
CExprNode cexpr_new_ident(const char* name) {
    ArrayList_Int args = (ArrayList_Int){ .data = (int64_t*)(unsigned long long)(0LL), .len = 0LL, .cap = 0LL, .allocator = (KaiAllocator*)(unsigned long long)(0LL) };
    ArrayList_Str fields = (ArrayList_Str){ .data = (const char**)(unsigned long long)(0LL), .len = 0LL, .cap = 0LL, .allocator = (KaiAllocator*)(unsigned long long)(0LL) };
    return (CExprNode){ .kind = CExprKind_ck_ident, .int_val = "", .float_val = "", .str_val = "", .char_val = "", .bool_val = false, .ident_name = name, .binop_left = (-1LL), .binop_right = (-1LL), .binop_op = "", .unop_operand = (-1LL), .unop_op = "", .is_prefix = false, .call_func = (-1LL), .call_args = args, .callee_name = "", .field_expr = (-1LL), .field_name = "", .idx_expr = (-1LL), .idx_index = (-1LL), .cast_type = ctype_void(), .cast_expr = (-1LL), .compound_type = ctype_void(), .compound_fields = fields, .tern_cond = (-1LL), .tern_then = (-1LL), .tern_else = (-1LL), .sizeof_type = ctype_void(), .sizeof_expr = (-1LL), .assign_target = (-1LL), .assign_value = (-1LL), .assign_op = "", .comma_left = (-1LL), .comma_right = (-1LL), .stmts = (ArrayList_Int){ .data = (int64_t*)(unsigned long long)(0LL), .len = 0LL, .cap = 0LL, .allocator = (KaiAllocator*)(unsigned long long)(0LL) }, .stmt_result = (-1LL) };
}
CExprNode cexpr_new_binary(int64_t left, const char* op, int64_t right) {
    ArrayList_Int args = (ArrayList_Int){ .data = (int64_t*)(unsigned long long)(0LL), .len = 0LL, .cap = 0LL, .allocator = (KaiAllocator*)(unsigned long long)(0LL) };
    ArrayList_Str fields = (ArrayList_Str){ .data = (const char**)(unsigned long long)(0LL), .len = 0LL, .cap = 0LL, .allocator = (KaiAllocator*)(unsigned long long)(0LL) };
    return (CExprNode){ .kind = CExprKind_ck_binary, .int_val = "", .float_val = "", .str_val = "", .char_val = "", .bool_val = false, .ident_name = "", .binop_left = left, .binop_right = right, .binop_op = op, .unop_operand = (-1LL), .unop_op = "", .is_prefix = false, .call_func = (-1LL), .call_args = args, .callee_name = "", .field_expr = (-1LL), .field_name = "", .idx_expr = (-1LL), .idx_index = (-1LL), .cast_type = ctype_void(), .cast_expr = (-1LL), .compound_type = ctype_void(), .compound_fields = fields, .tern_cond = (-1LL), .tern_then = (-1LL), .tern_else = (-1LL), .sizeof_type = ctype_void(), .sizeof_expr = (-1LL), .assign_target = (-1LL), .assign_value = (-1LL), .assign_op = "", .comma_left = (-1LL), .comma_right = (-1LL), .stmts = (ArrayList_Int){ .data = (int64_t*)(unsigned long long)(0LL), .len = 0LL, .cap = 0LL, .allocator = (KaiAllocator*)(unsigned long long)(0LL) }, .stmt_result = (-1LL) };
}
CExprNode cexpr_new_call(const char* callee, ArrayList_Int args) {
    ArrayList_Str fields = (ArrayList_Str){ .data = (const char**)(unsigned long long)(0LL), .len = 0LL, .cap = 0LL, .allocator = (KaiAllocator*)(unsigned long long)(0LL) };
    return (CExprNode){ .kind = CExprKind_ck_call, .int_val = "", .float_val = "", .str_val = "", .char_val = "", .bool_val = false, .ident_name = "", .binop_left = (-1LL), .binop_right = (-1LL), .binop_op = "", .unop_operand = (-1LL), .unop_op = "", .is_prefix = false, .call_func = (-1LL), .call_args = args, .callee_name = callee, .field_expr = (-1LL), .field_name = "", .idx_expr = (-1LL), .idx_index = (-1LL), .cast_type = ctype_void(), .cast_expr = (-1LL), .compound_type = ctype_void(), .compound_fields = fields, .tern_cond = (-1LL), .tern_then = (-1LL), .tern_else = (-1LL), .sizeof_type = ctype_void(), .sizeof_expr = (-1LL), .assign_target = (-1LL), .assign_value = (-1LL), .assign_op = "", .comma_left = (-1LL), .comma_right = (-1LL), .stmts = (ArrayList_Int){ .data = (int64_t*)(unsigned long long)(0LL), .len = 0LL, .cap = 0LL, .allocator = (KaiAllocator*)(unsigned long long)(0LL) }, .stmt_result = (-1LL) };
}
CStmtNode cstmt_new_expr(int64_t expr_idx) {
    ArrayList_Int block_stmts = (ArrayList_Int){ .data = (int64_t*)(unsigned long long)(0LL), .len = 0LL, .cap = 0LL, .allocator = (KaiAllocator*)(unsigned long long)(0LL) };
    return (CStmtNode){ .kind = CStmtKind_cs_expr, .block_stmts = block_stmts, .expr_stmt = expr_idx, .if_cond = (-1LL), .if_then = (-1LL), .if_else = (-1LL), .while_cond = (-1LL), .while_body = (-1LL), .for_init = (-1LL), .for_cond = (-1LL), .for_inc = (-1LL), .for_body = (-1LL), .do_body = (-1LL), .do_cond = (-1LL), .return_val = (-1LL), .var_type = ctype_void(), .var_name = "", .var_init = (-1LL), .switch_expr = (-1LL), .case_val = "", .label_name = "", .asm_code = "", .asm_volatile = false };
}
CStmtNode cstmt_new_block(ArrayList_Int stmts) {
    return (CStmtNode){ .kind = CStmtKind_cs_block, .block_stmts = stmts, .expr_stmt = (-1LL), .if_cond = (-1LL), .if_then = (-1LL), .if_else = (-1LL), .while_cond = (-1LL), .while_body = (-1LL), .for_init = (-1LL), .for_cond = (-1LL), .for_inc = (-1LL), .for_body = (-1LL), .do_body = (-1LL), .do_cond = (-1LL), .return_val = (-1LL), .var_type = ctype_void(), .var_name = "", .var_init = (-1LL), .switch_expr = (-1LL), .case_val = "", .label_name = "", .asm_code = "", .asm_volatile = false };
}
CStmtNode cstmt_new_if(int64_t cond, int64_t then_branch, int64_t else_branch) {
    ArrayList_Int block_stmts = (ArrayList_Int){ .data = (int64_t*)(unsigned long long)(0LL), .len = 0LL, .cap = 0LL, .allocator = (KaiAllocator*)(unsigned long long)(0LL) };
    return (CStmtNode){ .kind = CStmtKind_cs_if, .block_stmts = block_stmts, .expr_stmt = (-1LL), .if_cond = cond, .if_then = then_branch, .if_else = else_branch, .while_cond = (-1LL), .while_body = (-1LL), .for_init = (-1LL), .for_cond = (-1LL), .for_inc = (-1LL), .for_body = (-1LL), .do_body = (-1LL), .do_cond = (-1LL), .return_val = (-1LL), .var_type = ctype_void(), .var_name = "", .var_init = (-1LL), .switch_expr = (-1LL), .case_val = "", .label_name = "", .asm_code = "", .asm_volatile = false };
}
CExprNode cexpr_new_float(const char* val) {
    ArrayList_Int args = (ArrayList_Int){ .data = (int64_t*)(unsigned long long)(0LL), .len = 0LL, .cap = 0LL, .allocator = (KaiAllocator*)(unsigned long long)(0LL) };
    ArrayList_Str fields = (ArrayList_Str){ .data = (const char**)(unsigned long long)(0LL), .len = 0LL, .cap = 0LL, .allocator = (KaiAllocator*)(unsigned long long)(0LL) };
    return (CExprNode){ .kind = CExprKind_ck_float_lit, .int_val = "", .float_val = val, .str_val = "", .char_val = "", .bool_val = false, .ident_name = "", .binop_left = (-1LL), .binop_right = (-1LL), .binop_op = "", .unop_operand = (-1LL), .unop_op = "", .is_prefix = false, .call_func = (-1LL), .call_args = args, .callee_name = "", .field_expr = (-1LL), .field_name = "", .idx_expr = (-1LL), .idx_index = (-1LL), .cast_type = ctype_void(), .cast_expr = (-1LL), .compound_type = ctype_void(), .compound_fields = fields, .tern_cond = (-1LL), .tern_then = (-1LL), .tern_else = (-1LL), .sizeof_type = ctype_void(), .sizeof_expr = (-1LL), .assign_target = (-1LL), .assign_value = (-1LL), .assign_op = "", .comma_left = (-1LL), .comma_right = (-1LL), .stmts = (ArrayList_Int){ .data = (int64_t*)(unsigned long long)(0LL), .len = 0LL, .cap = 0LL, .allocator = (KaiAllocator*)(unsigned long long)(0LL) }, .stmt_result = (-1LL) };
}
CExprNode cexpr_new_str(const char* val) {
    ArrayList_Int args = (ArrayList_Int){ .data = (int64_t*)(unsigned long long)(0LL), .len = 0LL, .cap = 0LL, .allocator = (KaiAllocator*)(unsigned long long)(0LL) };
    ArrayList_Str fields = (ArrayList_Str){ .data = (const char**)(unsigned long long)(0LL), .len = 0LL, .cap = 0LL, .allocator = (KaiAllocator*)(unsigned long long)(0LL) };
    return (CExprNode){ .kind = CExprKind_ck_str_lit, .int_val = "", .float_val = "", .str_val = val, .char_val = "", .bool_val = false, .ident_name = "", .binop_left = (-1LL), .binop_right = (-1LL), .binop_op = "", .unop_operand = (-1LL), .unop_op = "", .is_prefix = false, .call_func = (-1LL), .call_args = args, .callee_name = "", .field_expr = (-1LL), .field_name = "", .idx_expr = (-1LL), .idx_index = (-1LL), .cast_type = ctype_void(), .cast_expr = (-1LL), .compound_type = ctype_void(), .compound_fields = fields, .tern_cond = (-1LL), .tern_then = (-1LL), .tern_else = (-1LL), .sizeof_type = ctype_void(), .sizeof_expr = (-1LL), .assign_target = (-1LL), .assign_value = (-1LL), .assign_op = "", .comma_left = (-1LL), .comma_right = (-1LL), .stmts = (ArrayList_Int){ .data = (int64_t*)(unsigned long long)(0LL), .len = 0LL, .cap = 0LL, .allocator = (KaiAllocator*)(unsigned long long)(0LL) }, .stmt_result = (-1LL) };
}
CExprNode cexpr_new_bool(bool val) {
    ArrayList_Int args = (ArrayList_Int){ .data = (int64_t*)(unsigned long long)(0LL), .len = 0LL, .cap = 0LL, .allocator = (KaiAllocator*)(unsigned long long)(0LL) };
    ArrayList_Str fields = (ArrayList_Str){ .data = (const char**)(unsigned long long)(0LL), .len = 0LL, .cap = 0LL, .allocator = (KaiAllocator*)(unsigned long long)(0LL) };
    return (CExprNode){ .kind = CExprKind_ck_bool_lit, .int_val = "", .float_val = "", .str_val = "", .char_val = "", .bool_val = val, .ident_name = "", .binop_left = (-1LL), .binop_right = (-1LL), .binop_op = "", .unop_operand = (-1LL), .unop_op = "", .is_prefix = false, .call_func = (-1LL), .call_args = args, .callee_name = "", .field_expr = (-1LL), .field_name = "", .idx_expr = (-1LL), .idx_index = (-1LL), .cast_type = ctype_void(), .cast_expr = (-1LL), .compound_type = ctype_void(), .compound_fields = fields, .tern_cond = (-1LL), .tern_then = (-1LL), .tern_else = (-1LL), .sizeof_type = ctype_void(), .sizeof_expr = (-1LL), .assign_target = (-1LL), .assign_value = (-1LL), .assign_op = "", .comma_left = (-1LL), .comma_right = (-1LL), .stmts = (ArrayList_Int){ .data = (int64_t*)(unsigned long long)(0LL), .len = 0LL, .cap = 0LL, .allocator = (KaiAllocator*)(unsigned long long)(0LL) }, .stmt_result = (-1LL) };
}
CExprNode cexpr_new_char(const char* val) {
    ArrayList_Int args = (ArrayList_Int){ .data = (int64_t*)(unsigned long long)(0LL), .len = 0LL, .cap = 0LL, .allocator = (KaiAllocator*)(unsigned long long)(0LL) };
    ArrayList_Str fields = (ArrayList_Str){ .data = (const char**)(unsigned long long)(0LL), .len = 0LL, .cap = 0LL, .allocator = (KaiAllocator*)(unsigned long long)(0LL) };
    return (CExprNode){ .kind = CExprKind_ck_char_lit, .int_val = "", .float_val = "", .str_val = "", .char_val = val, .bool_val = false, .ident_name = "", .binop_left = (-1LL), .binop_right = (-1LL), .binop_op = "", .unop_operand = (-1LL), .unop_op = "", .is_prefix = false, .call_func = (-1LL), .call_args = args, .callee_name = "", .field_expr = (-1LL), .field_name = "", .idx_expr = (-1LL), .idx_index = (-1LL), .cast_type = ctype_void(), .cast_expr = (-1LL), .compound_type = ctype_void(), .compound_fields = fields, .tern_cond = (-1LL), .tern_then = (-1LL), .tern_else = (-1LL), .sizeof_type = ctype_void(), .sizeof_expr = (-1LL), .assign_target = (-1LL), .assign_value = (-1LL), .assign_op = "", .comma_left = (-1LL), .comma_right = (-1LL), .stmts = (ArrayList_Int){ .data = (int64_t*)(unsigned long long)(0LL), .len = 0LL, .cap = 0LL, .allocator = (KaiAllocator*)(unsigned long long)(0LL) }, .stmt_result = (-1LL) };
}
CExprNode cexpr_new_unary(const char* op, int64_t operand, bool is_prefix) {
    ArrayList_Int args = (ArrayList_Int){ .data = (int64_t*)(unsigned long long)(0LL), .len = 0LL, .cap = 0LL, .allocator = (KaiAllocator*)(unsigned long long)(0LL) };
    ArrayList_Str fields = (ArrayList_Str){ .data = (const char**)(unsigned long long)(0LL), .len = 0LL, .cap = 0LL, .allocator = (KaiAllocator*)(unsigned long long)(0LL) };
    return (CExprNode){ .kind = CExprKind_ck_unary, .int_val = "", .float_val = "", .str_val = "", .char_val = "", .bool_val = false, .ident_name = "", .binop_left = (-1LL), .binop_right = (-1LL), .binop_op = "", .unop_operand = operand, .unop_op = op, .is_prefix = is_prefix, .call_func = (-1LL), .call_args = args, .callee_name = "", .field_expr = (-1LL), .field_name = "", .idx_expr = (-1LL), .idx_index = (-1LL), .cast_type = ctype_void(), .cast_expr = (-1LL), .compound_type = ctype_void(), .compound_fields = fields, .tern_cond = (-1LL), .tern_then = (-1LL), .tern_else = (-1LL), .sizeof_type = ctype_void(), .sizeof_expr = (-1LL), .assign_target = (-1LL), .assign_value = (-1LL), .assign_op = "", .comma_left = (-1LL), .comma_right = (-1LL), .stmts = (ArrayList_Int){ .data = (int64_t*)(unsigned long long)(0LL), .len = 0LL, .cap = 0LL, .allocator = (KaiAllocator*)(unsigned long long)(0LL) }, .stmt_result = (-1LL) };
}
CExprNode cexpr_new_compound(CType t, ArrayList_Str compound_fs) {
    ArrayList_Int args = (ArrayList_Int){ .data = (int64_t*)(unsigned long long)(0LL), .len = 0LL, .cap = 0LL, .allocator = (KaiAllocator*)(unsigned long long)(0LL) };
    return (CExprNode){ .kind = CExprKind_ck_compound, .int_val = "", .float_val = "", .str_val = "", .char_val = "", .bool_val = false, .ident_name = "", .binop_left = (-1LL), .binop_right = (-1LL), .binop_op = "", .unop_operand = (-1LL), .unop_op = "", .is_prefix = false, .call_func = (-1LL), .call_args = args, .callee_name = "", .field_expr = (-1LL), .field_name = "", .idx_expr = (-1LL), .idx_index = (-1LL), .cast_type = ctype_void(), .cast_expr = (-1LL), .compound_type = t, .compound_fields = compound_fs, .tern_cond = (-1LL), .tern_then = (-1LL), .tern_else = (-1LL), .sizeof_type = ctype_void(), .sizeof_expr = (-1LL), .assign_target = (-1LL), .assign_value = (-1LL), .assign_op = "", .comma_left = (-1LL), .comma_right = (-1LL), .stmts = (ArrayList_Int){ .data = (int64_t*)(unsigned long long)(0LL), .len = 0LL, .cap = 0LL, .allocator = (KaiAllocator*)(unsigned long long)(0LL) }, .stmt_result = (-1LL) };
}
CExprNode cexpr_new_field(int64_t base, const char* name) {
    ArrayList_Int args = (ArrayList_Int){ .data = (int64_t*)(unsigned long long)(0LL), .len = 0LL, .cap = 0LL, .allocator = (KaiAllocator*)(unsigned long long)(0LL) };
    ArrayList_Str fields = (ArrayList_Str){ .data = (const char**)(unsigned long long)(0LL), .len = 0LL, .cap = 0LL, .allocator = (KaiAllocator*)(unsigned long long)(0LL) };
    return (CExprNode){ .kind = CExprKind_ck_field, .int_val = "", .float_val = "", .str_val = "", .char_val = "", .bool_val = false, .ident_name = "", .binop_left = (-1LL), .binop_right = (-1LL), .binop_op = "", .unop_operand = (-1LL), .unop_op = "", .is_prefix = false, .call_func = (-1LL), .call_args = args, .callee_name = "", .field_expr = base, .field_name = name, .idx_expr = (-1LL), .idx_index = (-1LL), .cast_type = ctype_void(), .cast_expr = (-1LL), .compound_type = ctype_void(), .compound_fields = fields, .tern_cond = (-1LL), .tern_then = (-1LL), .tern_else = (-1LL), .sizeof_type = ctype_void(), .sizeof_expr = (-1LL), .assign_target = (-1LL), .assign_value = (-1LL), .assign_op = "", .comma_left = (-1LL), .comma_right = (-1LL), .stmts = (ArrayList_Int){ .data = (int64_t*)(unsigned long long)(0LL), .len = 0LL, .cap = 0LL, .allocator = (KaiAllocator*)(unsigned long long)(0LL) }, .stmt_result = (-1LL) };
}
CExprNode cexpr_new_arrow(int64_t base, const char* name) {
    ArrayList_Int args = (ArrayList_Int){ .data = (int64_t*)(unsigned long long)(0LL), .len = 0LL, .cap = 0LL, .allocator = (KaiAllocator*)(unsigned long long)(0LL) };
    ArrayList_Str fields = (ArrayList_Str){ .data = (const char**)(unsigned long long)(0LL), .len = 0LL, .cap = 0LL, .allocator = (KaiAllocator*)(unsigned long long)(0LL) };
    return (CExprNode){ .kind = CExprKind_ck_arrow, .int_val = "", .float_val = "", .str_val = "", .char_val = "", .bool_val = false, .ident_name = "", .binop_left = (-1LL), .binop_right = (-1LL), .binop_op = "", .unop_operand = (-1LL), .unop_op = "", .is_prefix = false, .call_func = (-1LL), .call_args = args, .callee_name = "", .field_expr = base, .field_name = name, .idx_expr = (-1LL), .idx_index = (-1LL), .cast_type = ctype_void(), .cast_expr = (-1LL), .compound_type = ctype_void(), .compound_fields = fields, .tern_cond = (-1LL), .tern_then = (-1LL), .tern_else = (-1LL), .sizeof_type = ctype_void(), .sizeof_expr = (-1LL), .assign_target = (-1LL), .assign_value = (-1LL), .assign_op = "", .comma_left = (-1LL), .comma_right = (-1LL), .stmts = (ArrayList_Int){ .data = (int64_t*)(unsigned long long)(0LL), .len = 0LL, .cap = 0LL, .allocator = (KaiAllocator*)(unsigned long long)(0LL) }, .stmt_result = (-1LL) };
}
CExprNode cexpr_new_index(int64_t base, int64_t idx_val) {
    ArrayList_Int args = (ArrayList_Int){ .data = (int64_t*)(unsigned long long)(0LL), .len = 0LL, .cap = 0LL, .allocator = (KaiAllocator*)(unsigned long long)(0LL) };
    ArrayList_Str fields = (ArrayList_Str){ .data = (const char**)(unsigned long long)(0LL), .len = 0LL, .cap = 0LL, .allocator = (KaiAllocator*)(unsigned long long)(0LL) };
    return (CExprNode){ .kind = CExprKind_ck_index, .int_val = "", .float_val = "", .str_val = "", .char_val = "", .bool_val = false, .ident_name = "", .binop_left = (-1LL), .binop_right = (-1LL), .binop_op = "", .unop_operand = (-1LL), .unop_op = "", .is_prefix = false, .call_func = (-1LL), .call_args = args, .callee_name = "", .field_expr = (-1LL), .field_name = "", .idx_expr = base, .idx_index = idx_val, .cast_type = ctype_void(), .cast_expr = (-1LL), .compound_type = ctype_void(), .compound_fields = fields, .tern_cond = (-1LL), .tern_then = (-1LL), .tern_else = (-1LL), .sizeof_type = ctype_void(), .sizeof_expr = (-1LL), .assign_target = (-1LL), .assign_value = (-1LL), .assign_op = "", .comma_left = (-1LL), .comma_right = (-1LL), .stmts = (ArrayList_Int){ .data = (int64_t*)(unsigned long long)(0LL), .len = 0LL, .cap = 0LL, .allocator = (KaiAllocator*)(unsigned long long)(0LL) }, .stmt_result = (-1LL) };
}
CExprNode cexpr_new_cast(CType t, int64_t cast_e) {
    ArrayList_Int args = (ArrayList_Int){ .data = (int64_t*)(unsigned long long)(0LL), .len = 0LL, .cap = 0LL, .allocator = (KaiAllocator*)(unsigned long long)(0LL) };
    ArrayList_Str fields = (ArrayList_Str){ .data = (const char**)(unsigned long long)(0LL), .len = 0LL, .cap = 0LL, .allocator = (KaiAllocator*)(unsigned long long)(0LL) };
    return (CExprNode){ .kind = CExprKind_ck_cast, .int_val = "", .float_val = "", .str_val = "", .char_val = "", .bool_val = false, .ident_name = "", .binop_left = (-1LL), .binop_right = (-1LL), .binop_op = "", .unop_operand = (-1LL), .unop_op = "", .is_prefix = false, .call_func = (-1LL), .call_args = args, .callee_name = "", .field_expr = (-1LL), .field_name = "", .idx_expr = (-1LL), .idx_index = (-1LL), .cast_type = t, .cast_expr = cast_e, .compound_type = ctype_void(), .compound_fields = fields, .tern_cond = (-1LL), .tern_then = (-1LL), .tern_else = (-1LL), .sizeof_type = ctype_void(), .sizeof_expr = (-1LL), .assign_target = (-1LL), .assign_value = (-1LL), .assign_op = "", .comma_left = (-1LL), .comma_right = (-1LL), .stmts = (ArrayList_Int){ .data = (int64_t*)(unsigned long long)(0LL), .len = 0LL, .cap = 0LL, .allocator = (KaiAllocator*)(unsigned long long)(0LL) }, .stmt_result = (-1LL) };
}
CExprNode cexpr_new_sizeof_type(CType t) {
    ArrayList_Int args = (ArrayList_Int){ .data = (int64_t*)(unsigned long long)(0LL), .len = 0LL, .cap = 0LL, .allocator = (KaiAllocator*)(unsigned long long)(0LL) };
    ArrayList_Str fields = (ArrayList_Str){ .data = (const char**)(unsigned long long)(0LL), .len = 0LL, .cap = 0LL, .allocator = (KaiAllocator*)(unsigned long long)(0LL) };
    return (CExprNode){ .kind = CExprKind_ck_sizeof_type, .int_val = "", .float_val = "", .str_val = "", .char_val = "", .bool_val = false, .ident_name = "", .binop_left = (-1LL), .binop_right = (-1LL), .binop_op = "", .unop_operand = (-1LL), .unop_op = "", .is_prefix = false, .call_func = (-1LL), .call_args = args, .callee_name = "", .field_expr = (-1LL), .field_name = "", .idx_expr = (-1LL), .idx_index = (-1LL), .cast_type = ctype_void(), .cast_expr = (-1LL), .compound_type = ctype_void(), .compound_fields = fields, .tern_cond = (-1LL), .tern_then = (-1LL), .tern_else = (-1LL), .sizeof_type = t, .sizeof_expr = (-1LL), .assign_target = (-1LL), .assign_value = (-1LL), .assign_op = "", .comma_left = (-1LL), .comma_right = (-1LL), .stmts = (ArrayList_Int){ .data = (int64_t*)(unsigned long long)(0LL), .len = 0LL, .cap = 0LL, .allocator = (KaiAllocator*)(unsigned long long)(0LL) }, .stmt_result = (-1LL) };
}
CDeclNode cdecl_new_func(const char* name, const char* ret_type, ArrayList_Str params, bool is_extern, bool is_vararg) {
    ArrayList_Int empty_stmts = (ArrayList_Int){ .data = (int64_t*)(unsigned long long)(0LL), .len = 0LL, .cap = 0LL, .allocator = (KaiAllocator*)(unsigned long long)(0LL) };
    ArrayList_Str empty_strs = (ArrayList_Str){ .data = (const char**)(unsigned long long)(0LL), .len = 0LL, .cap = 0LL, .allocator = (KaiAllocator*)(unsigned long long)(0LL) };
    return (CDeclNode){ .is_function = true, .func_ret = ctype_new(ret_type, 0LL, false, false), .func_name = name, .func_params = params, .func_vararg = is_vararg, .func_body = empty_stmts, .is_extern = is_extern, .var_type = ctype_void(), .var_name = "", .var_init = (-1LL), .is_struct = false, .struct_name = "", .struct_fields = empty_strs, .is_enum = false, .enum_name = "", .enum_variants = empty_strs, .is_tagged_enum = false, .tagged_name = "", .tagged_variants = empty_strs, .is_tagged_union_struct = false, .is_typedef = false, .typedef_alias = "", .typedef_def = ctype_void() };
}
CPrinter CPrinter_init(CCodeBuilder* builder, ArrayList_CExprNode* expr_pool, ArrayList_CStmtNode* stmt_pool) {
    CPrinter self = (CPrinter){0};
    self.builder = builder;
    self.expr_pool = expr_pool;
    self.stmt_pool = stmt_pool;
    return self;
}
const char* CPrinter_print_expr(CPrinter* self, int64_t idx) {
    if (idx < 0LL) {
    return "";
}
    CExprNode node = ArrayList_CExprNode_get(self->expr_pool, idx);
    if (node.kind == CExprKind_ck_int_lit) {
    return concatAlloc(node.int_val, "LL");
}
    if (node.kind == CExprKind_ck_float_lit) {
    return node.float_val;
}
    if (node.kind == CExprKind_ck_str_lit) {
    return node.str_val;
}
    if (node.kind == CExprKind_ck_char_lit) {
    return node.char_val;
}
    if (node.kind == CExprKind_ck_bool_lit) {
    if (node.bool_val) {
    return "true";
}
    return "false";
}
    if (node.kind == CExprKind_ck_ident) {
    return node.ident_name;
}
    if (node.kind == CExprKind_ck_binary) {
    const char* left = CPrinter_print_expr(self, node.binop_left);
    const char* right = CPrinter_print_expr(self, node.binop_right);
    return concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc("(", left), " "), node.binop_op), " "), right), ")");
}
    if (node.kind == CExprKind_ck_unary) {
    const char* operand = CPrinter_print_expr(self, node.unop_operand);
    if (node.is_prefix) {
    return concatAlloc(concatAlloc(concatAlloc("(", node.unop_op), operand), ")");
}
    return concatAlloc(concatAlloc(concatAlloc("(", operand), node.unop_op), ")");
}
    if (node.kind == CExprKind_ck_call) {
    const char* args_str = "";
    int64_t i = 0LL;
    while (i < ArrayList_Int_length(&(node.call_args))) {
    if (i > 0LL) {
    args_str = concatAlloc(args_str, ", ");
}
    args_str = concatAlloc(args_str, CPrinter_print_expr(self, ArrayList_Int_get(&(node.call_args), i)));
    i = (i + 1LL);
}
    return concatAlloc(concatAlloc(concatAlloc(node.callee_name, "("), args_str), ")");
}
    if (node.kind == CExprKind_ck_field) {
    const char* base = CPrinter_print_expr(self, node.field_expr);
    return concatAlloc(concatAlloc(base, "."), node.field_name);
}
    if (node.kind == CExprKind_ck_arrow) {
    const char* base = CPrinter_print_expr(self, node.field_expr);
    return concatAlloc(concatAlloc(base, "->"), node.field_name);
}
    if (node.kind == CExprKind_ck_index) {
    const char* base = CPrinter_print_expr(self, node.idx_expr);
    const char* idx = CPrinter_print_expr(self, node.idx_index);
    return concatAlloc(concatAlloc(concatAlloc(base, "["), idx), "]");
}
    if (node.kind == CExprKind_ck_cast) {
    const char* base = CPrinter_print_expr(self, node.cast_expr);
    const char* target = ctype_to_str(node.cast_type);
    return concatAlloc(concatAlloc(concatAlloc(concatAlloc("((", target), ")("), base), "))");
}
    if (node.kind == CExprKind_ck_ternary) {
    const char* cond = CPrinter_print_expr(self, node.tern_cond);
    const char* then_expr = CPrinter_print_expr(self, node.tern_then);
    const char* else_expr = CPrinter_print_expr(self, node.tern_else);
    return concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc("(", cond), " ? "), then_expr), " : "), else_expr), ")");
}
    if (node.kind == CExprKind_ck_sizeof_type) {
    return concatAlloc(concatAlloc("sizeof(", ctype_to_str(node.sizeof_type)), ")");
}
    if (node.kind == CExprKind_ck_sizeof_expr) {
    const char* base = CPrinter_print_expr(self, node.sizeof_expr);
    return concatAlloc(concatAlloc("sizeof(", base), ")");
}
    if (node.kind == CExprKind_ck_assign) {
    const char* target = CPrinter_print_expr(self, node.assign_target);
    const char* val = CPrinter_print_expr(self, node.assign_value);
    return concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc("(", target), " "), node.assign_op), " "), val), ")");
}
    if (node.kind == CExprKind_ck_compound) {
    const char* type_str = ctype_to_str(node.compound_type);
    const char* fields_str = "";
    int64_t ci = 0LL;
    while (ci < ArrayList_Str_length(&(node.compound_fields))) {
    if (ci > 0LL) {
    fields_str = concatAlloc(fields_str, ", ");
}
    fields_str = concatAlloc(fields_str, ArrayList_Str_get(&(node.compound_fields), ci));
    ci = (ci + 1LL);
}
    if (strlen(fields_str) > 0LL) {
    return concatAlloc(concatAlloc(concatAlloc(concatAlloc("(", type_str), "){ "), fields_str), " }");
}
    return concatAlloc(concatAlloc("(", type_str), "){0}");
}
    if (node.kind == CExprKind_ck_stmt_expr) {
    CCodeBuilder temp_builder = CCodeBuilder_init(self->builder->alloc);
    CPrinter temp_printer = (CPrinter){ .builder = &(temp_builder), .expr_pool = self->expr_pool, .stmt_pool = self->stmt_pool };
    CCodeBuilder_emit_line(&(temp_builder), "({");
    CCodeBuilder_indent(&(temp_builder));
    int64_t si = 0LL;
    while (si < ArrayList_Int_length(&(node.stmts))) {
    CPrinter_print_stmt(&(temp_printer), ArrayList_Int_get(&(node.stmts), si));
    si = (si + 1LL);
}
    if (node.stmt_result >= 0LL) {
    CCodeBuilder_emit_line(&(temp_builder), concatAlloc(CPrinter_print_expr(self, node.stmt_result), ";"));
}
    CCodeBuilder_dedent(&(temp_builder));
    CCodeBuilder_emit_line(&(temp_builder), "})");
    return CCodeBuilder_to_str(&(temp_builder));
}
    return "";
}
void CPrinter_print_stmt(CPrinter* self, int64_t idx) {
    if (idx < 0LL) {
    return;
}
    CStmtNode node = ArrayList_CStmtNode_get(self->stmt_pool, idx);
    if (node.kind == CStmtKind_cs_block) {
    CCodeBuilder_begin_block(self->builder);
    int64_t i = 0LL;
    while (i < ArrayList_Int_length(&(node.block_stmts))) {
    CPrinter_print_stmt(self, ArrayList_Int_get(&(node.block_stmts), i));
    i = (i + 1LL);
}
    CCodeBuilder_end_block(self->builder);
}
    if (node.kind == CStmtKind_cs_expr) {
    CCodeBuilder_emit_line(self->builder, concatAlloc(CPrinter_print_expr(self, node.expr_stmt), ";"));
}
    if (node.kind == CStmtKind_cs_if) {
    const char* cond = CPrinter_print_expr(self, node.if_cond);
    CCodeBuilder_emit_line(self->builder, concatAlloc(concatAlloc("if (", cond), ")"));
    CPrinter_print_stmt(self, node.if_then);
    if (node.if_else >= 0LL) {
    CStmtNode else_node = ArrayList_CStmtNode_get(self->stmt_pool, node.if_else);
    if (else_node.kind == CStmtKind_cs_if) {
    const char* inner_cond = CPrinter_print_expr(self, else_node.if_cond);
    CCodeBuilder_append_to_last_line(self->builder, concatAlloc(concatAlloc(" else if (", inner_cond), ")"));
    CPrinter_print_stmt(self, else_node.if_then);
    if (else_node.if_else >= 0LL) {
    CPrinter_print_stmt(self, else_node.if_else);
}
} else {
    CCodeBuilder_append_to_last_line(self->builder, " else");
    CPrinter_print_stmt(self, node.if_else);
}
}
}
    if (node.kind == CStmtKind_cs_while) {
    const char* cond = CPrinter_print_expr(self, node.while_cond);
    CCodeBuilder_emit_line(self->builder, concatAlloc(concatAlloc("while (", cond), ")"));
    CPrinter_print_stmt(self, node.while_body);
}
    if (node.kind == CStmtKind_cs_return) {
    if (node.return_val >= 0LL) {
    const char* val = CPrinter_print_expr(self, node.return_val);
    CCodeBuilder_emit_line(self->builder, concatAlloc(concatAlloc("return ", val), ";"));
} else {
    CCodeBuilder_emit_line(self->builder, "return;");
}
}
    if (node.kind == CStmtKind_cs_break) {
    CCodeBuilder_emit_line(self->builder, "break;");
}
    if (node.kind == CStmtKind_cs_continue) {
    CCodeBuilder_emit_line(self->builder, "continue;");
}
    if (node.kind == CStmtKind_cs_var_decl) {
    const char* type_str = ctype_to_str(node.var_type);
    if (node.var_init >= 0LL) {
    const char* init_val = CPrinter_print_expr(self, node.var_init);
    CCodeBuilder_emit_line(self->builder, concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(type_str, " "), node.var_name), " = "), init_val), ";"));
} else {
    CCodeBuilder_emit_line(self->builder, concatAlloc(concatAlloc(concatAlloc(type_str, " "), node.var_name), ";"));
}
}
}
void CPrinter_print_decl(CPrinter* self, CDeclNode decl) {
    if (decl.is_typedef) {
    const char* def_str = ctype_to_str(decl.typedef_def);
    CCodeBuilder_emit_line(self->builder, concatAlloc(concatAlloc(concatAlloc(concatAlloc("typedef ", def_str), " "), decl.typedef_alias), ";"));
    return;
}
    if (decl.is_struct) {
    CCodeBuilder_emit_line(self->builder, concatAlloc(concatAlloc("struct ", decl.struct_name), " {"));
    CCodeBuilder_indent(self->builder);
    int64_t i = 0LL;
    while (i < ArrayList_Str_length(&(decl.struct_fields))) {
    CCodeBuilder_emit_line(self->builder, ArrayList_Str_get(&(decl.struct_fields), i));
    i = (i + 1LL);
}
    CCodeBuilder_dedent(self->builder);
    CCodeBuilder_emit_line(self->builder, "};");
    return;
}
    if (decl.is_enum) {
    CCodeBuilder_emit_line(self->builder, "typedef enum {");
    CCodeBuilder_indent(self->builder);
    int64_t i = 0LL;
    while (i < ArrayList_Str_length(&(decl.enum_variants))) {
    CCodeBuilder_emit_line(self->builder, ArrayList_Str_get(&(decl.enum_variants), i));
    i = (i + 1LL);
}
    CCodeBuilder_dedent(self->builder);
    CCodeBuilder_emit_line(self->builder, concatAlloc(concatAlloc("} ", decl.enum_name), ";"));
    return;
}
    if (decl.is_tagged_union_struct) {
    CCodeBuilder_emit_line(self->builder, concatAlloc(concatAlloc("struct ", decl.struct_name), " {"));
    CCodeBuilder_indent(self->builder);
    CCodeBuilder_emit_line(self->builder, "uint8_t tag;");
    CCodeBuilder_emit_line(self->builder, "union {");
    CCodeBuilder_indent(self->builder);
    int64_t vi = 0LL;
    while (vi < ArrayList_Str_length(&(decl.tagged_variants))) {
    CCodeBuilder_emit_line(self->builder, ArrayList_Str_get(&(decl.tagged_variants), vi));
    vi = (vi + 1LL);
}
    CCodeBuilder_dedent(self->builder);
    CCodeBuilder_emit_line(self->builder, "};");
    CCodeBuilder_dedent(self->builder);
    CCodeBuilder_emit_line(self->builder, "};");
    return;
}
    if (decl.is_function) {
    const char* params_str = "";
    int64_t i = 0LL;
    while (i < ArrayList_Str_length(&(decl.func_params))) {
    if (i > 0LL) {
    params_str = concatAlloc(params_str, ", ");
}
    params_str = concatAlloc(params_str, ArrayList_Str_get(&(decl.func_params), i));
    i = (i + 1LL);
}
    if (decl.func_vararg) {
    if (strlen(params_str) > 0LL) {
    params_str = concatAlloc(params_str, ", ...");
} else {
    params_str = "...";
}
}
    const char* ret_str = ctype_to_str(decl.func_ret);
    const char* header = concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(ret_str, " "), decl.func_name), "("), params_str), ")");
    if (decl.is_extern) {
    CCodeBuilder_emit_line(self->builder, concatAlloc(concatAlloc("extern ", header), ";"));
    return;
}
    if (ArrayList_Int_length(&(decl.func_body)) == 0LL) {
    CCodeBuilder_emit_line(self->builder, concatAlloc(header, ";"));
} else {
    CCodeBuilder_emit_line(self->builder, header);
    CCodeBuilder_begin_block(self->builder);
    int64_t j = 0LL;
    while (j < ArrayList_Int_length(&(decl.func_body))) {
    CPrinter_print_stmt(self, ArrayList_Int_get(&(decl.func_body), j));
    j = (j + 1LL);
}
    CCodeBuilder_end_block(self->builder);
}
}
}
void CPrinter_emit_runtime_preamble(CPrinter* self, ArrayList_Str* cimport_headers) {
    CCodeBuilder_emit_line(self->builder, "/* BUILDER CODEGEN ACTIVE */");
    CCodeBuilder_emit_line(self->builder, "#include <stdint.h>");
    CCodeBuilder_emit_line(self->builder, "#include <stdbool.h>");
    CCodeBuilder_emit_line(self->builder, "#include <stdio.h>");
    CCodeBuilder_emit_line(self->builder, "#include <stdlib.h>");
    CCodeBuilder_emit_line(self->builder, "#include <string.h>");
    CCodeBuilder_emit_line(self->builder, "#include <inttypes.h>");
    CCodeBuilder_emit_line(self->builder, "#ifndef NO_GET_EXE_DIR");
    CCodeBuilder_emit_line(self->builder, "#include \"std/os/os.h\"");
    CCodeBuilder_emit_line(self->builder, "int64_t get_exe_dir(char* out_buf, int64_t max_len) {");
    CCodeBuilder_emit_line(self->builder, "    return kai_os_get_exe_dir(out_buf, max_len);");
    CCodeBuilder_emit_line(self->builder, "}");
    CCodeBuilder_emit_line(self->builder, "#endif");
    CCodeBuilder_emit_blank(self->builder);
    CCodeBuilder_emit_line(self->builder, "static char* __kai_str_sub(const char* s, int64_t start, int64_t end) {");
    CCodeBuilder_emit_line(self->builder, "    int64_t len = strlen(s);");
    CCodeBuilder_emit_line(self->builder, "    if (end > len) end = len;");
    CCodeBuilder_emit_line(self->builder, "    if (start < 0) start = 0;");
    CCodeBuilder_emit_line(self->builder, "    if (start >= end) {");
    CCodeBuilder_emit_line(self->builder, "        char* empty = malloc(1);");
    CCodeBuilder_emit_line(self->builder, "        if (empty) empty[0] = '\\0';");
    CCodeBuilder_emit_line(self->builder, "        return empty;");
    CCodeBuilder_emit_line(self->builder, "    }");
    CCodeBuilder_emit_line(self->builder, "    int64_t sub_len = end - start;");
    CCodeBuilder_emit_line(self->builder, "    char* buf = malloc(sub_len + 1);");
    CCodeBuilder_emit_line(self->builder, "    if (buf) {");
    CCodeBuilder_emit_line(self->builder, "        memcpy(buf, s + start, sub_len);");
    CCodeBuilder_emit_line(self->builder, "        buf[sub_len] = '\\0';");
    CCodeBuilder_emit_line(self->builder, "    }");
    CCodeBuilder_emit_line(self->builder, "    return buf;");
    CCodeBuilder_emit_line(self->builder, "}");
    CCodeBuilder_emit_blank(self->builder);
    CCodeBuilder_emit_line(self->builder, "static void* __kai_arr_sub(const void* arr, int64_t start, int64_t end, int64_t elem_size) {");
    CCodeBuilder_emit_line(self->builder, "    int64_t count = end - start;");
    CCodeBuilder_emit_line(self->builder, "    if (count <= 0) return NULL;");
    CCodeBuilder_emit_line(self->builder, "    size_t total = (size_t)count * (size_t)elem_size;");
    CCodeBuilder_emit_line(self->builder, "    void* buf = malloc(total);");
    CCodeBuilder_emit_line(self->builder, "    if (buf) memcpy(buf, (const char*)arr + start * elem_size, total);");
    CCodeBuilder_emit_line(self->builder, "    return buf;");
    CCodeBuilder_emit_line(self->builder, "}");
    CCodeBuilder_emit_blank(self->builder);
    int64_t ci = 0LL;
    bool has_cimports = false;
    while (ci < ArrayList_Str_length(cimport_headers)) {
    const char* hdr = ArrayList_Str_get(cimport_headers, ci);
    bool is_baseline = false;
    if (strcmp(hdr, "stdint.h") == 0) {
    is_baseline = true;
} else if (strcmp(hdr, "stdbool.h") == 0) {
    is_baseline = true;
} else if (strcmp(hdr, "stdio.h") == 0) {
    is_baseline = true;
} else if (strcmp(hdr, "stdlib.h") == 0) {
    is_baseline = true;
} else if (strcmp(hdr, "string.h") == 0) {
    is_baseline = true;
} else if (strcmp(hdr, "sys/mman.h") == 0) {
    is_baseline = true;
} else if (strcmp(hdr, "ctype.h") == 0) {
    is_baseline = true;
}
    if (!is_baseline) {
    if (!has_cimports) {
    CCodeBuilder_emit_line(self->builder, "/* C FFI Imports */");
    has_cimports = true;
}
    bool has_slash = false;
    bool dot_start = false;
    if (strlen(hdr) > 0LL) {
    int64_t hi = 0LL;
    while (hi < strlen(hdr)) {
    if ((hdr)[hi] == ((char)(47LL))) {
    has_slash = true;
}
    hi = (hi + 1LL);
}
    if ((hdr)[0LL] == ((char)(46LL))) {
    dot_start = true;
}
}
    if ((!has_slash) && (!dot_start)) {
    CCodeBuilder_emit_line(self->builder, concatAlloc(concatAlloc("#include <", hdr), ">"));
} else {
    CCodeBuilder_emit_line(self->builder, concatAlloc(concatAlloc("#include \"", hdr), "\""));
}
}
    ci = (ci + 1LL);
}
    CCodeBuilder_emit_line(self->builder, "#ifndef MAP_FAILED");
    CCodeBuilder_emit_line(self->builder, "#define MAP_FAILED ((void*)-1)");
    CCodeBuilder_emit_line(self->builder, "#endif");
    CCodeBuilder_emit_line(self->builder, "#ifndef MAP_PRIVATE");
    CCodeBuilder_emit_line(self->builder, "#define MAP_PRIVATE 2");
    CCodeBuilder_emit_line(self->builder, "#endif");
    CCodeBuilder_emit_line(self->builder, "#ifndef MAP_ANONYMOUS");
    CCodeBuilder_emit_line(self->builder, "#ifdef __APPLE__");
    CCodeBuilder_emit_line(self->builder, "#define MAP_ANONYMOUS 0x1000");
    CCodeBuilder_emit_line(self->builder, "#else");
    CCodeBuilder_emit_line(self->builder, "#define MAP_ANONYMOUS 0x20");
    CCodeBuilder_emit_line(self->builder, "#endif");
    CCodeBuilder_emit_line(self->builder, "#endif");
    CCodeBuilder_emit_line(self->builder, "extern void* mmap(void* addr, unsigned long long length, int prot, int flags, int fd, long long offset);");
    CCodeBuilder_emit_line(self->builder, "extern int munmap(void* addr, unsigned long long length);");
    CCodeBuilder_emit_blank(self->builder);
    CCodeBuilder_emit_line(self->builder, "void __kai_print_int(int64_t v) {");
    CCodeBuilder_emit_line(self->builder, "    printf(\"%lld\\n\", (long long)(v));");
    CCodeBuilder_emit_line(self->builder, "}");
    CCodeBuilder_emit_blank(self->builder);
    CCodeBuilder_emit_line(self->builder, "void __kai_print_float(double v) {");
    CCodeBuilder_emit_line(self->builder, "    printf(\"%f\\n\", (double)(v));");
    CCodeBuilder_emit_line(self->builder, "}");
    CCodeBuilder_emit_blank(self->builder);
    CCodeBuilder_emit_line(self->builder, "static inline uint8_t* _kai_mmap(uint8_t* addr, int64_t length, int64_t prot, int64_t flags, int64_t fd, int64_t offset) {");
    CCodeBuilder_emit_line(self->builder, "    return (uint8_t*)mmap(addr, length, prot, MAP_PRIVATE | MAP_ANONYMOUS, fd, offset);");
    CCodeBuilder_emit_line(self->builder, "}");
    CCodeBuilder_emit_blank(self->builder);
    CCodeBuilder_emit_line(self->builder, "static inline int64_t _kai_munmap(uint8_t* addr, int64_t length) {");
    CCodeBuilder_emit_line(self->builder, "    return munmap(addr, length);");
    CCodeBuilder_emit_line(self->builder, "}");
    CCodeBuilder_emit_blank(self->builder);
    CCodeBuilder_emit_line(self->builder, "extern void __kai_panic(const char* msg);");
    CCodeBuilder_emit_line(self->builder, "#ifndef __KAI_NO_PANIC");
    CCodeBuilder_emit_line(self->builder, "void __kai_panic(const char* msg) {");
    CCodeBuilder_emit_line(self->builder, "    fprintf(stderr, \"KAI PANIC: %s\\n\", msg);");
    CCodeBuilder_emit_line(self->builder, "    fflush(stderr);");
    CCodeBuilder_emit_line(self->builder, "    abort();");
    CCodeBuilder_emit_line(self->builder, "}");
    CCodeBuilder_emit_line(self->builder, "#endif");
    CCodeBuilder_emit_blank(self->builder);
}
LLVMCodegen LLVMCodegen_init(KaiAllocator* allocator, ArrayList_StmtNode* stmt_pool, ArrayList_ExprNode* expr_pool, ArrayList_PatternNode* pattern_pool, ImportResolver* import_resolver, StringPool* pool) {
    LLVMCodegen self = (LLVMCodegen){0};
    self.allocator = allocator;
    self.stmt_pool = stmt_pool;
    self.expr_pool = expr_pool;
    self.pattern_pool = pattern_pool;
    self.import_resolver = import_resolver;
    self.pool = pool;
    self.ctx = LLVMContextCreate();
    self.module = LLVMModuleCreateWithNameInContext("kai_module", self.ctx);
    self.builder = LLVMCreateBuilderInContext(self.ctx);
    self.cur_func = (void*)(unsigned long long)(0LL);
    self.cur_block = (void*)(unsigned long long)(0LL);
    self.last_was_term = false;
    self.int1_type = LLVMInt1TypeInContext(self.ctx);
    self.int8_type = LLVMInt8TypeInContext(self.ctx);
    self.ptr_type = LLVMPointerType(self.int8_type, 0LL);
    self.int32_type = LLVMInt32TypeInContext(self.ctx);
    self.int64_type = LLVMInt64TypeInContext(self.ctx);
    self.float_type = LLVMFloatTypeInContext(self.ctx);
    self.double_type = LLVMDoubleTypeInContext(self.ctx);
    self.void_type = LLVMVoidTypeInContext(self.ctx);
    self.tmp_target = (void*)(unsigned long long)(0LL);
    self.tmp_err = (char*)(unsigned long long)(0LL);
    self.str_counter = 0LL;
    self.func_type_names = ArrayList_Str_init(allocator);
    self.func_type_returns = ArrayList_Str_init(allocator);
    self.func_param_counts = ArrayList_Int_init(allocator);
    self.func_type_param_types = ArrayList_Str_init(allocator);
    self.func_cache_names = ArrayList_Str_init(allocator);
    self.func_cache_vals = ArrayList_Int_init(allocator);
    self.func_cache_types = ArrayList_Int_init(allocator);
    self.local_alloca_names = ArrayList_Str_init(allocator);
    self.local_alloca_vals = ArrayList_Int_init(allocator);
    self.local_alloca_types = ArrayList_Int_init(allocator);
    self.local_alloca_type_strs = ArrayList_Str_init(allocator);
    self.local_alloca_decls = ArrayList_Int_init(allocator);
    self.loop_cond_block = (void*)(unsigned long long)(0LL);
    self.loop_merge_block = (void*)(unsigned long long)(0LL);
    self.struct_cache_names = ArrayList_Str_init(allocator);
    self.struct_cache_types = ArrayList_Int_init(allocator);
    self.struct_cache_field_counts = ArrayList_Int_init(allocator);
    self.enum_cache_names = ArrayList_Str_init(allocator);
    self.enum_cache_types = ArrayList_Int_init(allocator);
    self.enum_has_payload = ArrayList_Bool_init(allocator);
    self.tuple_cache_names = ArrayList_Str_init(allocator);
    self.tuple_cache_types = ArrayList_Int_init(allocator);
    self.tuple_cache_field_counts = ArrayList_Int_init(allocator);
    self.current_type_map = ArrayList_LLVMStrMapEntry_init(allocator);
    self.generic_struct_decls = ArrayList_LLVMStrMapEntry_init(allocator);
    self.generic_enum_decls = ArrayList_LLVMStrMapEntry_init(allocator);
    self.monomorphized_types = ArrayList_Str_init(allocator);
    self.method_indices = ArrayList_Int_init(allocator);
    self.extern_func_names = ArrayList_Str_init(allocator);
    self.kai_func_names = ArrayList_Str_init(allocator);
    self.str_type = LLVMStructCreateNamed(self.ctx, "Str");
    ArrayList_Int str_fields = ArrayList_Int_init(allocator);
    ArrayList_Int_push(&(str_fields), (int64_t)(self.ptr_type));
    ArrayList_Int_push(&(str_fields), (int64_t)(self.int64_type));
    LLVMStructSetBody(self.str_type, (void*)(str_fields.data), 2LL, false);
    return self;
}
void LLVMCodegen_build_func_types(LLVMCodegen* self) {
    self->method_indices = ArrayList_Int_init(self->allocator);
    int64_t i = 0LL;
    while (i < ArrayList_StmtNode_length(self->stmt_pool)) {
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, i);
    if (stmt.kind == StmtKind_sk_impl_block) {
    int64_t mi = 0LL;
    while (mi < ArrayList_Int_length(&(stmt.impl_methods))) {
    ArrayList_Int_push(&(self->method_indices), ArrayList_Int_get(&(stmt.impl_methods), mi));
    mi = (mi + 1LL);
}
}
    if (stmt.kind == StmtKind_sk_struct_decl) {
    int64_t mi = 0LL;
    while (mi < ArrayList_Int_length(&(stmt.struct_methods))) {
    ArrayList_Int_push(&(self->method_indices), ArrayList_Int_get(&(stmt.struct_methods), mi));
    mi = (mi + 1LL);
}
}
    if (stmt.kind == StmtKind_sk_trait_decl) {
    int64_t mi = 0LL;
    while (mi < ArrayList_Int_length(&(stmt.trait_methods))) {
    ArrayList_Int_push(&(self->method_indices), ArrayList_Int_get(&(stmt.trait_methods), mi));
    mi = (mi + 1LL);
}
}
    i = (i + 1LL);
}
    i = 0LL;
    while (i < ArrayList_StmtNode_length(self->stmt_pool)) {
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, i);
    if (stmt.kind == StmtKind_sk_func_decl) {
    bool is_method = false;
    int64_t mi = 0LL;
    while (mi < ArrayList_Int_length(&(self->method_indices))) {
    if (ArrayList_Int_get(&(self->method_indices), mi) == i) {
    is_method = true;
    break;
}
    mi = (mi + 1LL);
}
    if (is_method) {
    i = (i + 1LL);
    continue;
}
    ArrayList_Str_push(&(self->func_type_names), stmt.func_name);
    ArrayList_Str_push(&(self->func_type_returns), stmt.func_return_type);
    ArrayList_Int_push(&(self->func_param_counts), ArrayList_Param_length(&(stmt.func_params)));
    const char* pts = "";
    int64_t pi = 0LL;
    while (pi < ArrayList_Param_length(&(stmt.func_params))) {
    if (pi > 0LL) {
    pts = concatAlloc(pts, ",");
}
    pts = concatAlloc(pts, ArrayList_Param_get(&(stmt.func_params), pi).ptype);
    pi = (pi + 1LL);
}
    ArrayList_Str_push(&(self->func_type_param_types), pts);
    if (stmt.func_body >= 0LL) {
    ArrayList_Str_push(&(self->kai_func_names), stmt.func_name);
}
}
    if (stmt.kind == StmtKind_sk_extern) {
    ArrayList_Str_push(&(self->func_type_names), stmt.extern_name);
    ArrayList_Str_push(&(self->func_type_returns), stmt.extern_return);
    ArrayList_Int_push(&(self->func_param_counts), ArrayList_Param_length(&(stmt.extern_params)));
    const char* pts = "";
    int64_t pi = 0LL;
    while (pi < ArrayList_Param_length(&(stmt.extern_params))) {
    if (pi > 0LL) {
    pts = concatAlloc(pts, ",");
}
    pts = concatAlloc(pts, ArrayList_Param_get(&(stmt.extern_params), pi).ptype);
    pi = (pi + 1LL);
}
    ArrayList_Str_push(&(self->func_type_param_types), pts);
    ArrayList_Str_push(&(self->extern_func_names), stmt.extern_name);
}
    if (stmt.kind == StmtKind_sk_impl_block) {
    if (!LLVMCodegen_is_monomorphized_name(self, stmt.impl_struct_name)) {
    int64_t mi = 0LL;
    while (mi < ArrayList_Int_length(&(stmt.impl_methods))) {
    int64_t method_idx = ArrayList_Int_get(&(stmt.impl_methods), mi);
    StmtNode method_stmt = ArrayList_StmtNode_get(self->stmt_pool, method_idx);
    if (method_stmt.kind == StmtKind_sk_func_decl) {
    const char* mangled_name = concatAlloc(concatAlloc(stmt.impl_struct_name, "_"), method_stmt.func_name);
    ArrayList_Str_push(&(self->func_type_names), mangled_name);
    const char* ret = method_stmt.func_return_type;
    bool is_init = (strcmp(method_stmt.func_name, "init") == 0);
    if (is_init) {
    ret = stmt.impl_struct_name;
}
    ArrayList_Str_push(&(self->func_type_returns), ret);
    int64_t param_count = ArrayList_Param_length(&(method_stmt.func_params));
    if (is_init) {
    param_count = (param_count - 1LL);
}
    ArrayList_Int_push(&(self->func_param_counts), param_count);
    const char* pts = "";
    int64_t pi = 0LL;
    while (pi < ArrayList_Param_length(&(method_stmt.func_params))) {
    Param param = ArrayList_Param_get(&(method_stmt.func_params), pi);
    if (is_init && (strcmp(param.name, "self") == 0)) {
    pi = (pi + 1LL);
    continue;
}
    if (strlen(pts) > 0LL) {
    pts = concatAlloc(pts, ",");
}
    const char* ptype_str = param.ptype;
    if (strcmp(param.name, "self") == 0) {
    ptype_str = concatAlloc("*", stmt.impl_struct_name);
}
    pts = concatAlloc(pts, ptype_str);
    pi = (pi + 1LL);
}
    ArrayList_Str_push(&(self->func_type_param_types), pts);
}
    mi = (mi + 1LL);
}
}
}
    if (stmt.kind == StmtKind_sk_struct_decl) {
    if (!LLVMCodegen_is_monomorphized_name(self, stmt.struct_name)) {
    int64_t mi = 0LL;
    while (mi < ArrayList_Int_length(&(stmt.struct_methods))) {
    int64_t method_idx = ArrayList_Int_get(&(stmt.struct_methods), mi);
    StmtNode method_stmt = ArrayList_StmtNode_get(self->stmt_pool, method_idx);
    if (method_stmt.kind == StmtKind_sk_func_decl) {
    const char* mangled_name = concatAlloc(concatAlloc(stmt.struct_name, "_"), method_stmt.func_name);
    ArrayList_Str_push(&(self->func_type_names), mangled_name);
    ArrayList_Str_push(&(self->func_type_returns), method_stmt.func_return_type);
    ArrayList_Int_push(&(self->func_param_counts), ArrayList_Param_length(&(method_stmt.func_params)));
    const char* pts = "";
    int64_t pi = 0LL;
    while (pi < ArrayList_Param_length(&(method_stmt.func_params))) {
    if (pi > 0LL) {
    pts = concatAlloc(pts, ",");
}
    const char* ptype_str = ArrayList_Param_get(&(method_stmt.func_params), pi).ptype;
    if (strcmp(ArrayList_Param_get(&(method_stmt.func_params), pi).name, "self") == 0) {
    ptype_str = concatAlloc("*", stmt.struct_name);
}
    pts = concatAlloc(pts, ptype_str);
    pi = (pi + 1LL);
}
    ArrayList_Str_push(&(self->func_type_param_types), pts);
}
    mi = (mi + 1LL);
}
}
}
    i = (i + 1LL);
}
}
void LLVMCodegen_build_type_caches(LLVMCodegen* self) {
    int64_t i = 0LL;
    while (i < ArrayList_StmtNode_length(self->stmt_pool)) {
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, i);
    if ((stmt.kind == StmtKind_sk_struct_decl) && (ArrayList_Str_length(&(stmt.struct_type_params)) == 0LL)) {
    const char* sname = stmt.struct_name;
    void* existing_ty = LLVMGetTypeByName2(self->ctx, sname);
    if (existing_ty == (void*)(unsigned long long)(0LL)) {
    (void)(LLVMStructCreateNamed(self->ctx, sname));
}
}
    i = (i + 1LL);
}
    i = 0LL;
    while (i < ArrayList_StmtNode_length(self->stmt_pool)) {
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, i);
    if (stmt.kind == StmtKind_sk_struct_decl) {
    if (ArrayList_Str_length(&(stmt.struct_type_params)) > 0LL) {
    llvm_type_map_put(&(self->generic_struct_decls), stmt.struct_name, int_to_str(i));
    i = (i + 1LL);
    continue;
}
    const char* sname = stmt.struct_name;
    int64_t field_count = ArrayList_StructField_length(&(stmt.struct_fields));
    void* named_ty = LLVMGetTypeByName2(self->ctx, sname);
    if (named_ty == (void*)(unsigned long long)(0LL)) {
    named_ty = LLVMStructCreateNamed(self->ctx, sname);
}
    if (field_count > 0LL) {
    ArrayList_Int field_types = ArrayList_Int_init(self->allocator);
    int64_t fi = 0LL;
    while (fi < field_count) {
    StructField f = ArrayList_StructField_get(&(stmt.struct_fields), fi);
    void* fty = LLVMCodegen_map_type(self, f.ftype);
    if ((fty == self->void_type) || (fty == (void*)(unsigned long long)(0LL))) {
    ArrayList_Int_push(&(field_types), (int64_t)(self->int64_type));
} else {
    ArrayList_Int_push(&(field_types), (int64_t)(fty));
}
    fi = (fi + 1LL);
}
    LLVMStructSetBody(named_ty, (void*)(field_types.data), field_count, false);
}
    ArrayList_Str_push(&(self->struct_cache_names), sname);
    ArrayList_Int_push(&(self->struct_cache_types), (int64_t)(named_ty));
    ArrayList_Int_push(&(self->struct_cache_field_counts), field_count);
}
    if (stmt.kind == StmtKind_sk_enum_decl) {
    if (ArrayList_Str_length(&(stmt.enum_type_params)) > 0LL) {
    llvm_type_map_put(&(self->generic_enum_decls), stmt.enum_name, int_to_str(i));
    i = (i + 1LL);
    continue;
}
    const char* ename = stmt.enum_name;
    bool has_payload = false;
    int64_t vi = 0LL;
    while (vi < ArrayList_Variant_length(&(stmt.enum_variants))) {
    Variant v = ArrayList_Variant_get(&(stmt.enum_variants), vi);
    if (ArrayList_Param_length(&(v.params)) > 0LL) {
    has_payload = true;
}
    vi = (vi + 1LL);
}
    if (has_payload) {
    void* named_ty = LLVMStructCreateNamed(self->ctx, ename);
    ArrayList_Int field_types = ArrayList_Int_init(self->allocator);
    ArrayList_Int_push(&(field_types), (int64_t)(self->int8_type));
    void* payload_ty = LLVMArrayType(self->int64_type, 16LL);
    ArrayList_Int_push(&(field_types), (int64_t)(payload_ty));
    LLVMStructSetBody(named_ty, (void*)(field_types.data), 2LL, false);
    ArrayList_Str_push(&(self->enum_cache_names), ename);
    ArrayList_Int_push(&(self->enum_cache_types), (int64_t)(named_ty));
    ArrayList_Bool_push(&(self->enum_has_payload), true);
} else {
    ArrayList_Str_push(&(self->enum_cache_names), ename);
    ArrayList_Int_push(&(self->enum_cache_types), (int64_t)(self->int64_type));
    ArrayList_Bool_push(&(self->enum_has_payload), false);
}
}
    i = (i + 1LL);
}
    void* range_ty = LLVMStructCreateNamed(self->ctx, "Range");
    ArrayList_Int range_fields = ArrayList_Int_init(self->allocator);
    ArrayList_Int_push(&(range_fields), (int64_t)(self->int64_type));
    ArrayList_Int_push(&(range_fields), (int64_t)(self->int64_type));
    ArrayList_Int_push(&(range_fields), (int64_t)(self->int1_type));
    LLVMStructSetBody(range_ty, (void*)(range_fields.data), 3LL, false);
    ArrayList_Str_push(&(self->struct_cache_names), "Range");
    ArrayList_Int_push(&(self->struct_cache_types), (int64_t)(range_ty));
    ArrayList_Int_push(&(self->struct_cache_field_counts), 3LL);
}
const char* LLVMCodegen_get_generic_mangled_name(LLVMCodegen* self, const char* name) {
    if (LLVMCodegen_str_contains(self, name, ((char)(60LL)))) {
    int64_t lt_pos = LLVMCodegen_str_find(self, name, ((char)(60LL)));
    int64_t gt_pos = LLVMCodegen_str_find(self, name, ((char)(62LL)));
    if (((lt_pos >= 0LL) && (gt_pos >= 0LL)) && (gt_pos > lt_pos)) {
    const char* base_name = __kai_str_sub(name, 0LL, lt_pos);
    const char* suffix = __kai_str_sub(name, (gt_pos + 1LL), strlen(name));
    return concatAlloc(base_name, suffix);
}
}
    if ((strlen(name) > 10LL) && (strcmp(__kai_str_sub(name, 0LL, 10LL), "ArrayList_") == 0)) {
    int64_t last_u = (strlen(name) - 1LL);
    while ((last_u > 0LL) && ((name)[last_u] != ((char)(95LL)))) {
    last_u = (last_u - 1LL);
}
    if (last_u > 9LL) {
    return concatAlloc("ArrayList_", __kai_str_sub(name, (last_u + 1LL), strlen(name)));
}
}
    if ((strlen(name) > 8LL) && (strcmp(__kai_str_sub(name, 0LL, 8LL), "HashMap_") == 0)) {
    int64_t last_u = (strlen(name) - 1LL);
    while ((last_u > 0LL) && ((name)[last_u] != ((char)(95LL)))) {
    last_u = (last_u - 1LL);
}
    if (last_u > 7LL) {
    return concatAlloc("HashMap_", __kai_str_sub(name, (last_u + 1LL), strlen(name)));
}
}
    return name;
}
const char* LLVMCodegen_get_func_return_type(LLVMCodegen* self, const char* name) {
    int64_t i = 0LL;
    while (i < ArrayList_Str_length(&(self->func_type_names))) {
    if (strcmp(ArrayList_Str_get(&(self->func_type_names), i), name) == 0) {
    return ArrayList_Str_get(&(self->func_type_returns), i);
}
    i = (i + 1LL);
}
    const char* resolved = LLVMCodegen_get_generic_mangled_name(self, name);
    if (strcmp(resolved, name) != 0) {
    i = 0LL;
    while (i < ArrayList_Str_length(&(self->func_type_names))) {
    if (strcmp(ArrayList_Str_get(&(self->func_type_names), i), resolved) == 0) {
    return ArrayList_Str_get(&(self->func_type_returns), i);
}
    i = (i + 1LL);
}
}
    return "";
}
int64_t LLVMCodegen_get_func_param_count(LLVMCodegen* self, const char* name) {
    int64_t i = 0LL;
    while (i < ArrayList_Str_length(&(self->func_type_names))) {
    if (strcmp(ArrayList_Str_get(&(self->func_type_names), i), name) == 0) {
    return ArrayList_Int_get(&(self->func_param_counts), i);
}
    i = (i + 1LL);
}
    const char* resolved = LLVMCodegen_get_generic_mangled_name(self, name);
    if (strcmp(resolved, name) != 0) {
    i = 0LL;
    while (i < ArrayList_Str_length(&(self->func_type_names))) {
    if (strcmp(ArrayList_Str_get(&(self->func_type_names), i), resolved) == 0) {
    return ArrayList_Int_get(&(self->func_param_counts), i);
}
    i = (i + 1LL);
}
}
    return 0LL;
}
const char* LLVMCodegen_get_func_param_types(LLVMCodegen* self, const char* name) {
    int64_t i = 0LL;
    while (i < ArrayList_Str_length(&(self->func_type_names))) {
    if (strcmp(ArrayList_Str_get(&(self->func_type_names), i), name) == 0) {
    return ArrayList_Str_get(&(self->func_type_param_types), i);
}
    i = (i + 1LL);
}
    const char* resolved = LLVMCodegen_get_generic_mangled_name(self, name);
    if (strcmp(resolved, name) != 0) {
    i = 0LL;
    while (i < ArrayList_Str_length(&(self->func_type_names))) {
    if (strcmp(ArrayList_Str_get(&(self->func_type_names), i), resolved) == 0) {
    return ArrayList_Str_get(&(self->func_type_param_types), i);
}
    i = (i + 1LL);
}
}
    return "";
}
void* LLVMCodegen_get_cached_func_type(LLVMCodegen* self, const char* name) {
    int64_t i = 0LL;
    while (i < ArrayList_Str_length(&(self->func_cache_names))) {
    if (strcmp(ArrayList_Str_get(&(self->func_cache_names), i), name) == 0) {
    return (void*)(unsigned long long)(ArrayList_Int_get(&(self->func_cache_types), i));
}
    i = (i + 1LL);
}
    return (void*)(unsigned long long)(0LL);
}
void* LLVMCodegen_c_abi_type(LLVMCodegen* self, const char* tname) {
    if (((strcmp(tname, "Str") == 0) || (strcmp(tname, "*Str") == 0)) || (strcmp(tname, "&Str") == 0)) {
    return self->ptr_type;
}
    return LLVMCodegen_map_type(self, tname);
}
void* LLVMCodegen_build_llvm_func_type_from_params(LLVMCodegen* self, void* ret, const char* param_types_str, bool is_vararg, bool is_extern) {
    int64_t param_count = LLVMCodegen_get_func_param_count_by_types_str(self, param_types_str);
    if (param_count == 0LL) {
    return kai_func_type_0(ret);
}
    ArrayList_Int param_type_array = ArrayList_Int_init(self->allocator);
    int64_t start = 0LL;
    int64_t pi = 0LL;
    while (pi < strlen(param_types_str)) {
    if ((param_types_str)[pi] == ((char)(44LL))) {
    const char* tname = __kai_str_sub(param_types_str, start, pi);
    void* t = (void*)(unsigned long long)(0LL);
    if (is_extern) {
    t = LLVMCodegen_c_abi_type(self, tname);
} else {
    t = LLVMCodegen_map_type(self, tname);
}
    if ((t == (void*)(unsigned long long)(0LL)) || (t == self->void_type)) {
    ArrayList_Int_push(&(param_type_array), (int64_t)(self->int64_type));
} else {
    ArrayList_Int_push(&(param_type_array), (int64_t)(t));
}
    start = (pi + 1LL);
}
    pi = (pi + 1LL);
}
    if (start < strlen(param_types_str)) {
    const char* tname = __kai_str_sub(param_types_str, start, strlen(param_types_str));
    void* t = (void*)(unsigned long long)(0LL);
    if (is_extern) {
    t = LLVMCodegen_c_abi_type(self, tname);
} else {
    t = LLVMCodegen_map_type(self, tname);
}
    if ((t == (void*)(unsigned long long)(0LL)) || (t == self->void_type)) {
    ArrayList_Int_push(&(param_type_array), (int64_t)(self->int64_type));
} else {
    ArrayList_Int_push(&(param_type_array), (int64_t)(t));
}
}
    int64_t count = ArrayList_Int_length(&(param_type_array));
    if (count == 0LL) {
    return kai_func_type_0(ret);
}
    if (count == 1LL) {
    return kai_func_type_1(ret, (void*)(unsigned long long)(ArrayList_Int_get(&(param_type_array), 0LL)), is_vararg);
}
    if (count == 2LL) {
    return kai_func_type_2(ret, (void*)(unsigned long long)(ArrayList_Int_get(&(param_type_array), 0LL)), (void*)(unsigned long long)(ArrayList_Int_get(&(param_type_array), 1LL)), is_vararg);
}
    return LLVMFunctionType(ret, (void*)(param_type_array.data), count, is_vararg);
}
int64_t LLVMCodegen_get_func_param_count_by_types_str(LLVMCodegen* self, const char* param_types_str) {
    if (strlen(param_types_str) == 0LL) {
    return 0LL;
}
    int64_t count = 1LL;
    int64_t i = 0LL;
    while (i < strlen(param_types_str)) {
    if ((param_types_str)[i] == ((char)(44LL))) {
    count = (count + 1LL);
}
    i = (i + 1LL);
}
    return count;
}
bool LLVMCodegen_is_extern_func(LLVMCodegen* self, const char* name) {
    int64_t ki = 0LL;
    while (ki < ArrayList_Str_length(&(self->kai_func_names))) {
    if (strcmp(ArrayList_Str_get(&(self->kai_func_names), ki), name) == 0) {
    return false;
}
    ki = (ki + 1LL);
}
    int64_t i = 0LL;
    while (i < ArrayList_Str_length(&(self->extern_func_names))) {
    if (strcmp(ArrayList_Str_get(&(self->extern_func_names), i), name) == 0) {
    return true;
}
    i = (i + 1LL);
}
    return false;
}
void* LLVMCodegen_lookup_or_create_func(LLVMCodegen* self, const char* name) {
    int64_t i = 0LL;
    while (i < ArrayList_Str_length(&(self->func_cache_names))) {
    if (strcmp(ArrayList_Str_get(&(self->func_cache_names), i), name) == 0) {
    return (void*)(unsigned long long)(ArrayList_Int_get(&(self->func_cache_vals), i));
}
    i = (i + 1LL);
}
    void* existing = LLVMGetNamedFunction(self->module, name);
    bool is_ext = LLVMCodegen_is_extern_func(self, name);
    if (existing != (void*)(unsigned long long)(0LL)) {
    ArrayList_Str_push(&(self->func_cache_names), name);
    ArrayList_Int_push(&(self->func_cache_vals), (int64_t)(existing));
    const char* ret_type_str = LLVMCodegen_get_func_return_type(self, name);
    void* llvm_ret = (void*)(unsigned long long)(0LL);
    if (is_ext) {
    llvm_ret = LLVMCodegen_c_abi_type(self, ret_type_str);
} else {
    llvm_ret = LLVMCodegen_map_type(self, ret_type_str);
}
    bool is_vararg = (strcmp(name, "printf") == 0);
    const char* param_types_str = LLVMCodegen_get_func_param_types(self, name);
    void* fn_type = (void*)(unsigned long long)(0LL);
    if (is_vararg) {
    void* ptype = LLVMCodegen_map_type(self, "*Char");
    fn_type = kai_func_type_1(llvm_ret, ptype, true);
} else if (strlen(param_types_str) > 0LL) {
    fn_type = LLVMCodegen_build_llvm_func_type_from_params(self, llvm_ret, param_types_str, false, is_ext);
} else {
    fn_type = kai_func_type_0(llvm_ret);
}
    if (fn_type == (void*)(unsigned long long)(0LL)) {
    fn_type = kai_func_type_1(llvm_ret, self->ptr_type, false);
}
    ArrayList_Int_push(&(self->func_cache_types), (int64_t)(fn_type));
    return existing;
}
    const char* ret_type_str = LLVMCodegen_get_func_return_type(self, name);
    void* llvm_ret = (void*)(unsigned long long)(0LL);
    if (is_ext) {
    llvm_ret = LLVMCodegen_c_abi_type(self, ret_type_str);
} else {
    llvm_ret = LLVMCodegen_map_type(self, ret_type_str);
}
    bool is_vararg = (strcmp(name, "printf") == 0);
    const char* param_types_str = LLVMCodegen_get_func_param_types(self, name);
    void* fn_type = (void*)(unsigned long long)(0LL);
    if (is_vararg) {
    void* ptype = LLVMCodegen_map_type(self, "*Char");
    fn_type = kai_func_type_1(llvm_ret, ptype, true);
} else if (strlen(param_types_str) > 0LL) {
    fn_type = LLVMCodegen_build_llvm_func_type_from_params(self, llvm_ret, param_types_str, false, is_ext);
} else {
    fn_type = kai_func_type_0(llvm_ret);
}
    if (fn_type == (void*)(unsigned long long)(0LL)) {
    fn_type = kai_func_type_1(llvm_ret, self->ptr_type, false);
}
    void* fn_val = LLVMAddFunction(self->module, name, fn_type);
    ArrayList_Str_push(&(self->func_cache_names), name);
    ArrayList_Int_push(&(self->func_cache_vals), (int64_t)(fn_val));
    ArrayList_Int_push(&(self->func_cache_types), (int64_t)(fn_type));
    return fn_val;
}
void LLVMCodegen_foreach_method(LLVMCodegen* self, int64_t stmt_idx, bool decl_only) {
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, stmt_idx);
    if (stmt.kind == StmtKind_sk_impl_block) {
    bool is_generic_impl = false;
    int64_t si = 0LL;
    while (si < ArrayList_StmtNode_length(self->stmt_pool)) {
    StmtNode sn = ArrayList_StmtNode_get(self->stmt_pool, si);
    if (((sn.kind == StmtKind_sk_struct_decl) && (strcmp(sn.struct_name, stmt.impl_struct_name) == 0)) && (ArrayList_Str_length(&(sn.struct_type_params)) > 0LL)) {
    is_generic_impl = true;
    break;
}
    si = (si + 1LL);
}
    if (is_generic_impl) {
    return;
}
    int64_t mi = 0LL;
    while (mi < ArrayList_Int_length(&(stmt.impl_methods))) {
    int64_t method_idx = ArrayList_Int_get(&(stmt.impl_methods), mi);
    StmtNode method_stmt = ArrayList_StmtNode_get(self->stmt_pool, method_idx);
    if (method_stmt.kind == StmtKind_sk_func_decl) {
    const char* mangled_name = concatAlloc(concatAlloc(stmt.impl_struct_name, "_"), method_stmt.func_name);
    if (decl_only) {
    LLVMCodegen_emit_func_decl(self, method_idx, mangled_name);
} else if (method_stmt.func_body >= 0LL) {
    void* fn_val = LLVMCodegen_lookup_or_create_func(self, mangled_name);
    LLVMCodegen_emit_func_body(self, method_idx, fn_val, stmt.impl_struct_name);
}
}
    mi = (mi + 1LL);
}
}
    if (stmt.kind == StmtKind_sk_struct_decl) {
    if (ArrayList_Str_length(&(stmt.struct_type_params)) > 0LL) {
    return;
}
    int64_t mi = 0LL;
    while (mi < ArrayList_Int_length(&(stmt.struct_methods))) {
    int64_t method_idx = ArrayList_Int_get(&(stmt.struct_methods), mi);
    StmtNode method_stmt = ArrayList_StmtNode_get(self->stmt_pool, method_idx);
    if (method_stmt.kind == StmtKind_sk_func_decl) {
    const char* mangled_name = concatAlloc(concatAlloc(stmt.struct_name, "_"), method_stmt.func_name);
    if (decl_only) {
    LLVMCodegen_emit_func_decl(self, method_idx, mangled_name);
} else if (method_stmt.func_body >= 0LL) {
    void* fn_val = LLVMCodegen_lookup_or_create_func(self, mangled_name);
    LLVMCodegen_emit_func_body(self, method_idx, fn_val, stmt.struct_name);
}
}
    mi = (mi + 1LL);
}
}
}
void LLVMCodegen_emit_runtime_helpers(LLVMCodegen* self) {
    void* old_block = self->cur_block;
    void* old_func = self->cur_func;
    void* print_int_ty = kai_func_type_1(self->void_type, self->int64_type, false);
    void* print_int_fn = LLVMAddFunction(self->module, "__kai_print_int", print_int_ty);
    void* b1 = LLVMAppendBasicBlockInContext(self->ctx, print_int_fn, "entry");
    LLVMPositionBuilderAtEnd(self->builder, b1);
    void* p_int_val = LLVMGetParam(print_int_fn, 0LL);
    void* printf_fn = LLVMCodegen_lookup_or_create_func(self, "printf");
    void* format_str = LLVMBuildGlobalStringPtr(self->builder, "%lld\n", "fmt_int");
    void* printf_ty = LLVMCodegen_get_cached_func_type(self, "printf");
    (void)(kai_build_call_2(self->builder, printf_ty, printf_fn, format_str, p_int_val, ""));
    LLVMBuildRetVoid(self->builder);
    void* print_float_ty = kai_func_type_1(self->void_type, self->double_type, false);
    void* print_float_fn = LLVMAddFunction(self->module, "__kai_print_float", print_float_ty);
    void* b2 = LLVMAppendBasicBlockInContext(self->ctx, print_float_fn, "entry");
    LLVMPositionBuilderAtEnd(self->builder, b2);
    void* p_float_val = LLVMGetParam(print_float_fn, 0LL);
    void* format_float = LLVMBuildGlobalStringPtr(self->builder, "%f\n", "fmt_float");
    (void)(kai_build_call_2(self->builder, printf_ty, printf_fn, format_float, p_float_val, ""));
    LLVMBuildRetVoid(self->builder);
    void* munmap_ty = kai_func_type_2(self->int32_type, self->ptr_type, self->int64_type, false);
    void* munmap_fn = LLVMAddFunction(self->module, "munmap", munmap_ty);
    void* kai_munmap_ty = kai_func_type_2(self->int64_type, self->ptr_type, self->int64_type, false);
    void* kai_munmap_fn = LLVMAddFunction(self->module, "_kai_munmap", kai_munmap_ty);
    void* bm = LLVMAppendBasicBlockInContext(self->ctx, kai_munmap_fn, "entry");
    LLVMPositionBuilderAtEnd(self->builder, bm);
    void* munmap_addr = LLVMGetParam(kai_munmap_fn, 0LL);
    void* munmap_len = LLVMGetParam(kai_munmap_fn, 1LL);
    void* munmap_ret = kai_build_call_2(self->builder, munmap_ty, munmap_fn, munmap_addr, munmap_len, "");
    void* munmap_ext = LLVMBuildSExt(self->builder, munmap_ret, self->int64_type, "");
    LLVMBuildRet(self->builder, munmap_ext);
    void* map_anon = LLVMConstInt(self->int32_type, 4096LL, false);
    void* mmap_fn = LLVMAddFunction(self->module, "mmap", kai_func_type_0(self->ptr_type));
    self->cur_block = old_block;
    self->cur_func = old_func;
    if (self->cur_block != (void*)(unsigned long long)(0LL)) {
    LLVMPositionBuilderAtEnd(self->builder, self->cur_block);
}
}
bool LLVMCodegen_generate(LLVMCodegen* self, int64_t top_stmt_idx, const char* obj_path) {
    LLVMCodegen_build_func_types(self);
    LLVMCodegen_build_type_caches(self);
    LLVMCodegen_emit_runtime_helpers(self);
    int64_t i = 0LL;
    while (i < ArrayList_StmtNode_length(self->stmt_pool)) {
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, i);
    if (stmt.kind == StmtKind_sk_func_decl) {
    bool is_method = false;
    int64_t mi = 0LL;
    while (mi < ArrayList_Int_length(&(self->method_indices))) {
    if (ArrayList_Int_get(&(self->method_indices), mi) == i) {
    is_method = true;
    break;
}
    mi = (mi + 1LL);
}
    if (!is_method) {
    LLVMCodegen_emit_func_decl(self, i, "");
}
}
    if (stmt.kind == StmtKind_sk_extern) {
    LLVMCodegen_lookup_or_create_func(self, stmt.extern_name);
}
    if (stmt.kind == StmtKind_sk_impl_block) {
    if (!LLVMCodegen_is_monomorphized_name(self, stmt.impl_struct_name)) {
    LLVMCodegen_foreach_method(self, i, true);
}
}
    if (stmt.kind == StmtKind_sk_struct_decl) {
    if (!LLVMCodegen_is_monomorphized_name(self, stmt.struct_name)) {
    LLVMCodegen_foreach_method(self, i, true);
}
}
    i = (i + 1LL);
}
    i = 0LL;
    while (i < ArrayList_StmtNode_length(self->stmt_pool)) {
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, i);
    if (stmt.kind == StmtKind_sk_func_decl) {
    bool has_self_param = false;
    int64_t pi = 0LL;
    while (pi < ArrayList_Param_length(&(stmt.func_params))) {
    Param p = ArrayList_Param_get(&(stmt.func_params), pi);
    {
    if (strcmp(p.name, "self") == 0LL) {
    has_self_param = true;
}
}
    pi = (pi + 1LL);
}
    if (has_self_param) {
} else if (ArrayList_Str_length(&(stmt.func_type_params)) > 0LL) {
} else if (stmt.func_body < 0LL) {
} else {
    bool is_method = false;
    int64_t mi = 0LL;
    while (mi < ArrayList_Int_length(&(self->method_indices))) {
    if (ArrayList_Int_get(&(self->method_indices), mi) == i) {
    is_method = true;
    break;
}
    mi = (mi + 1LL);
}
    if (!is_method) {
    void* fn_val = LLVMCodegen_lookup_or_create_func(self, stmt.func_name);
    LLVMCodegen_emit_func_body(self, i, fn_val, "");
}
}
}
    if (stmt.kind == StmtKind_sk_impl_block) {
    if (!LLVMCodegen_is_monomorphized_name(self, stmt.impl_struct_name)) {
    LLVMCodegen_foreach_method(self, i, false);
}
}
    if (stmt.kind == StmtKind_sk_struct_decl) {
    if (!LLVMCodegen_is_monomorphized_name(self, stmt.struct_name)) {
    LLVMCodegen_foreach_method(self, i, false);
}
}
    i = (i + 1LL);
}
    return LLVMCodegen_emit_object(self, obj_path);
}
void LLVMCodegen_emit_func_decl(LLVMCodegen* self, int64_t stmt_idx, const char* name) {
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, stmt_idx);
    const char* decl_name = name;
    if (strlen(decl_name) == 0LL) {
    decl_name = stmt.func_name;
}
    (void)(LLVMCodegen_lookup_or_create_func(self, decl_name));
}
void LLVMCodegen_emit_func_body(LLVMCodegen* self, int64_t stmt_idx, void* fn_val, const char* struct_name) {
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, stmt_idx);
    if (fn_val == (void*)(unsigned long long)(0LL)) {
    return;
}
    self->cur_func = fn_val;
    if (strlen(struct_name) > 0LL) {
    self->cur_func_name = concatAlloc(concatAlloc(struct_name, "_"), stmt.func_name);
} else {
    self->cur_func_name = stmt.func_name;
}
    {
    printf("emit_func_body: compiling %s\n", self->cur_func_name);
}
    self->cur_block = LLVMAppendBasicBlockInContext(self->ctx, self->cur_func, "entry");
    LLVMPositionBuilderAtEnd(self->builder, self->cur_block);
    self->last_was_term = false;
    self->local_alloca_names = ArrayList_Str_init(self->allocator);
    self->local_alloca_vals = ArrayList_Int_init(self->allocator);
    self->local_alloca_types = ArrayList_Int_init(self->allocator);
    self->local_alloca_type_strs = ArrayList_Str_init(self->allocator);
    self->local_alloca_decls = ArrayList_Int_init(self->allocator);
    self->loop_cond_block = (void*)(unsigned long long)(0LL);
    self->loop_merge_block = (void*)(unsigned long long)(0LL);
    bool is_init = ((strcmp(stmt.func_name, "init") == 0) && (strlen(struct_name) > 0LL));
    self->cur_method_is_init = is_init;
    self->cur_self_alloca = (void*)(unsigned long long)(0LL);
    self->cur_struct_type = (void*)(unsigned long long)(0LL);
    if (is_init) {
    self->cur_struct_type = LLVMCodegen_map_type(self, struct_name);
}
    int64_t pi = 0LL;
    while (pi < ArrayList_Param_length(&(stmt.func_params))) {
    Param param = ArrayList_Param_get(&(stmt.func_params), pi);
    void* param_llvm_type = LLVMCodegen_map_type(self, param.ptype);
    const char* param_type_str = param.ptype;
    if (is_init && (strcmp(param.name, "self") == 0)) {
    param_llvm_type = self->cur_struct_type;
    param_type_str = struct_name;
    void* alloca_val = LLVMBuildAlloca(self->builder, param_llvm_type, "self");
    LLVMBuildStore(self->builder, LLVMConstNull(param_llvm_type), alloca_val);
    self->cur_self_alloca = alloca_val;
    ArrayList_Str_push(&(self->local_alloca_names), "self");
    ArrayList_Int_push(&(self->local_alloca_vals), (int64_t)(alloca_val));
    ArrayList_Int_push(&(self->local_alloca_types), (int64_t)(param_llvm_type));
    ArrayList_Str_push(&(self->local_alloca_type_strs), param_type_str);
    ArrayList_Int_push(&(self->local_alloca_decls), stmt_idx);
    pi = (pi + 1LL);
    continue;
}
    void* param_val = (void*)(unsigned long long)(0LL);
    if (is_init) {
    param_val = LLVMGetParam(self->cur_func, (pi - 1LL));
} else {
    param_val = LLVMGetParam(self->cur_func, pi);
}
    if ((strcmp(param.name, "self") == 0) && (strlen(struct_name) > 0LL)) {
    param_llvm_type = LLVMCodegen_map_type(self, concatAlloc("*", struct_name));
    param_type_str = concatAlloc("*", struct_name);
}
    void* alloca_val = LLVMBuildAlloca(self->builder, param_llvm_type, param.name);
    LLVMBuildStore(self->builder, param_val, alloca_val);
    ArrayList_Str_push(&(self->local_alloca_names), param.name);
    ArrayList_Int_push(&(self->local_alloca_vals), (int64_t)(alloca_val));
    ArrayList_Int_push(&(self->local_alloca_types), (int64_t)(param_llvm_type));
    ArrayList_Str_push(&(self->local_alloca_type_strs), param_type_str);
    ArrayList_Int_push(&(self->local_alloca_decls), stmt_idx);
    pi = (pi + 1LL);
}
    LLVMCodegen_gen_stmt(self, stmt.func_body);
    if (!self->last_was_term) {
    if (is_init) {
    void* loaded_self = LLVMBuildLoad2(self->builder, self->cur_struct_type, self->cur_self_alloca, "");
    LLVMBuildRet(self->builder, loaded_self);
} else {
    const char* ret_type_str = LLVMCodegen_get_func_return_type(self, self->cur_func_name);
    void* ret_type = LLVMCodegen_map_type(self, ret_type_str);
    if ((ret_type == self->void_type) || (ret_type == (void*)(unsigned long long)(0LL))) {
    LLVMBuildRetVoid(self->builder);
} else {
    LLVMBuildRet(self->builder, LLVMConstNull(ret_type));
}
}
    self->last_was_term = true;
}
}
void* LLVMCodegen_coerce_return_value(LLVMCodegen* self, void* val, const char* ret_type_str, const char* actual_type_str) {
    if (val == (void*)(unsigned long long)(0LL)) {
    return val;
}
    if (strcmp(ret_type_str, "?Str") == 0) {
    if (LLVMTypeOf(val) == self->str_type) {
    return LLVMCodegen_unwrap_str_for_c(self, val);
}
}
    if ((strlen(ret_type_str) > 0LL) && ((ret_type_str)[0LL] == ((char)(63LL)))) {
    void* val_ty = LLVMTypeOf(val);
    int64_t val_kind = LLVMGetTypeKind(val_ty);
    void* declared_ty = LLVMCodegen_map_type(self, ret_type_str);
    if (val_ty != declared_ty) {
    if (val_kind == LLVMIntegerTypeKind) {
    return LLVMBuildIntToPtr(self->builder, val, declared_ty, "");
}
    if (val_kind == LLVMPointerTypeKind) {
    return LLVMBuildBitCast(self->builder, val, declared_ty, "");
}
}
}
    if (LLVMCodegen_str_contains(self, ret_type_str, ((char)(33LL)))) {
    int64_t excl_pos = LLVMCodegen_str_find(self, ret_type_str, ((char)(33LL)));
    const char* val_payload = __kai_str_sub(ret_type_str, 0LL, excl_pos);
    const char* err_type = __kai_str_sub(ret_type_str, (excl_pos + 1LL), strlen(ret_type_str));
    void* mapped_type = LLVMCodegen_map_type(self, ret_type_str);
    void* val_ty = LLVMTypeOf(val);
    if (val_ty == mapped_type) {
    return val;
}
    if ((strcmp(actual_type_str, err_type) == 0) || (strcmp(actual_type_str, "IoError") == 0)) {
    void* tag_val = LLVMCodegen_gen_cast(self, val, self->int64_type);
    void* undef_struct = LLVMGetUndef(mapped_type);
    void* with_tag = kai_LLVMBuildInsertValue(self->builder, undef_struct, tag_val, 0LL, ".tag");
    return with_tag;
}
    void* tag_val = LLVMConstInt(self->int64_type, 0LL, false);
    void* undef_struct = LLVMGetUndef(mapped_type);
    void* with_tag = kai_LLVMBuildInsertValue(self->builder, undef_struct, tag_val, 0LL, ".tag");
    if (strcmp(val_payload, "Void") != 0) {
    void* coerced_val = LLVMCodegen_coerce_return_value(self, val, val_payload, actual_type_str);
    return kai_LLVMBuildInsertValue(self->builder, with_tag, coerced_val, 1LL, ".value");
}
    return with_tag;
}
    void* val_ty = LLVMTypeOf(val);
    int64_t val_kind = LLVMGetTypeKind(val_ty);
    if (val_kind != LLVMIntegerTypeKind) {
    return val;
}
    void* declared_ty = LLVMCodegen_map_type(self, ret_type_str);
    if ((declared_ty == (void*)(unsigned long long)(0LL)) || (declared_ty == self->void_type)) {
    return val;
}
    int64_t declared_kind = LLVMGetTypeKind(declared_ty);
    if (declared_kind != LLVMIntegerTypeKind) {
    return val;
}
    if (val_ty == declared_ty) {
    return val;
}
    int64_t val_width = kai_LLVMGetIntTypeWidth(val_ty);
    int64_t declared_width = kai_LLVMGetIntTypeWidth(declared_ty);
    if (val_width < declared_width) {
    return LLVMBuildZExt(self->builder, val, declared_ty, "");
}
    if (val_width > declared_width) {
    return LLVMBuildTrunc(self->builder, val, declared_ty, "");
}
    return val;
}
const char* LLVMCodegen_strip_module_prefix(LLVMCodegen* self, const char* name) {
    int64_t last_dot = (-1LL);
    int64_t i = 0LL;
    while (i < strlen(name)) {
    if ((name)[i] == ((char)(46LL))) {
    last_dot = i;
}
    i = (i + 1LL);
}
    if (last_dot >= 0LL) {
    return __kai_str_sub(name, (last_dot + 1LL), strlen(name));
}
    return name;
}
void* LLVMCodegen_map_type(LLVMCodegen* self, const char* type_name) {
    const char* resolved_type = LLVMCodegen_strip_module_prefix(self, type_name);
    if (ArrayList_LLVMStrMapEntry_length(&(self->current_type_map)) > 0LL) {
    resolved_type = LLVMCodegen_substitute_generic_type(self, resolved_type);
}
    if ((strlen(resolved_type) > 0LL) && ((resolved_type)[0LL] == ((char)(63LL)))) {
    return self->ptr_type;
}
    if ((strlen(resolved_type) > 0LL) && (((resolved_type)[0LL] == ((char)(42LL))) || ((resolved_type)[0LL] == ((char)(38LL))))) {
    return self->ptr_type;
}
    if (((strlen(resolved_type) > 2LL) && ((resolved_type)[0LL] == ((char)(91LL)))) && ((resolved_type)[1LL] == ((char)(93LL)))) {
    return self->ptr_type;
}
    if (LLVMCodegen_str_contains(self, resolved_type, ((char)(33LL)))) {
    int64_t excl_pos = LLVMCodegen_str_find(self, resolved_type, ((char)(33LL)));
    const char* val_type = __kai_str_sub(resolved_type, 0LL, excl_pos);
    const char* err_type = __kai_str_sub(resolved_type, (excl_pos + 1LL), strlen(resolved_type));
    const char* clean_val = LLVMCodegen_clean_type_for_mangling(self, val_type);
    const char* clean_err = LLVMCodegen_clean_type_for_mangling(self, err_type);
    const char* concrete_name = concatAlloc(concatAlloc(concatAlloc("Result_", clean_val), "_"), clean_err);
    int64_t si = 0LL;
    bool found = false;
    void* cached_ty = (void*)(unsigned long long)(0LL);
    while (si < ArrayList_Str_length(&(self->struct_cache_names))) {
    if (strcmp(ArrayList_Str_get(&(self->struct_cache_names), si), concrete_name) == 0) {
    found = true;
    cached_ty = (void*)(unsigned long long)(ArrayList_Int_get(&(self->struct_cache_types), si));
    break;
}
    si = (si + 1LL);
}
    if (found) {
    return cached_ty;
}
    void* existing_ty = LLVMGetTypeByName2(self->ctx, concrete_name);
    if ((existing_ty != (void*)(unsigned long long)(0LL)) && (existing_ty != self->void_type)) {
    ArrayList_Str_push(&(self->struct_cache_names), concrete_name);
    ArrayList_Int_push(&(self->struct_cache_types), (int64_t)(existing_ty));
    ArrayList_Int_push(&(self->struct_cache_field_counts), 2LL);
    return existing_ty;
}
    void* named_ty = LLVMStructCreateNamed(self->ctx, concrete_name);
    ArrayList_Int field_types = ArrayList_Int_init(self->allocator);
    ArrayList_Int_push(&(field_types), (int64_t)(self->int64_type));
    int64_t field_count = 1LL;
    if (strcmp(val_type, "Void") != 0) {
    void* val_llvm_ty = LLVMCodegen_map_type(self, val_type);
    if ((val_llvm_ty != self->void_type) && (val_llvm_ty != (void*)(unsigned long long)(0LL))) {
    ArrayList_Int_push(&(field_types), (int64_t)(val_llvm_ty));
    field_count = 2LL;
}
}
    LLVMStructSetBody(named_ty, (void*)(field_types.data), field_count, false);
    ArrayList_Str_push(&(self->struct_cache_names), concrete_name);
    ArrayList_Int_push(&(self->struct_cache_types), (int64_t)(named_ty));
    ArrayList_Int_push(&(self->struct_cache_field_counts), field_count);
    return named_ty;
}
    if (LLVMCodegen_str_contains(self, resolved_type, ((char)(60LL)))) {
    int64_t lt_pos = LLVMCodegen_str_find(self, resolved_type, ((char)(60LL)));
    const char* base_name = __kai_str_sub(resolved_type, 0LL, lt_pos);
    const char* args_str = __kai_str_sub(resolved_type, (lt_pos + 1LL), (strlen(resolved_type) - 1LL));
    ArrayList_Str args = ArrayList_Str_init(self->allocator);
    int64_t start = 0LL;
    int64_t i = 0LL;
    while (i < strlen(args_str)) {
    char c = (args_str)[i];
    if (c == ((char)(44LL))) {
    ArrayList_Str_push(&(args), LLVMCodegen_trim_spaces(self, __kai_str_sub(args_str, start, i)));
    start = (i + 1LL);
}
    i = (i + 1LL);
}
    ArrayList_Str_push(&(args), LLVMCodegen_trim_spaces(self, __kai_str_sub(args_str, start, strlen(args_str))));
    const char* concrete_name = base_name;
    int64_t ai = 0LL;
    while (ai < ArrayList_Str_length(&(args))) {
    const char* raw_arg = ArrayList_Str_get(&(args), ai);
    const char* clean_arg = LLVMCodegen_clean_type_for_mangling(self, raw_arg);
    concrete_name = concatAlloc(concatAlloc(concrete_name, "_"), clean_arg);
    ai = (ai + 1LL);
}
    const char* struct_idx_str = llvm_type_map_get(&(self->generic_struct_decls), base_name);
    if (strlen(struct_idx_str) > 0LL) {
    if (llvm_strlist_find(&(self->monomorphized_types), concrete_name) < 0LL) {
    ArrayList_Str_push(&(self->monomorphized_types), concrete_name);
    LLVMCodegen_monomorphize_struct(self, LLVMCodegen_str_to_int(self, struct_idx_str), concrete_name, &(args));
}
    int64_t si = 0LL;
    while (si < ArrayList_Str_length(&(self->struct_cache_names))) {
    if (strcmp(ArrayList_Str_get(&(self->struct_cache_names), si), concrete_name) == 0) {
    return (void*)(unsigned long long)(ArrayList_Int_get(&(self->struct_cache_types), si));
}
    si = (si + 1LL);
}
}
    const char* enum_idx_str = llvm_type_map_get(&(self->generic_enum_decls), base_name);
    if (strlen(enum_idx_str) > 0LL) {
    if (llvm_strlist_find(&(self->monomorphized_types), concrete_name) < 0LL) {
    ArrayList_Str_push(&(self->monomorphized_types), concrete_name);
    LLVMCodegen_monomorphize_enum(self, LLVMCodegen_str_to_int(self, enum_idx_str), concrete_name, &(args));
}
    int64_t ei = 0LL;
    while (ei < ArrayList_Str_length(&(self->enum_cache_names))) {
    if (strcmp(ArrayList_Str_get(&(self->enum_cache_names), ei), concrete_name) == 0) {
    return (void*)(unsigned long long)(ArrayList_Int_get(&(self->enum_cache_types), ei));
}
    ei = (ei + 1LL);
}
}
}
    int64_t si = 0LL;
    while (si < ArrayList_Str_length(&(self->struct_cache_names))) {
    if (strcmp(ArrayList_Str_get(&(self->struct_cache_names), si), resolved_type) == 0) {
    return (void*)(unsigned long long)(ArrayList_Int_get(&(self->struct_cache_types), si));
}
    si = (si + 1LL);
}
    int64_t ei = 0LL;
    while (ei < ArrayList_Str_length(&(self->enum_cache_names))) {
    if (strcmp(ArrayList_Str_get(&(self->enum_cache_names), ei), resolved_type) == 0) {
    return (void*)(unsigned long long)(ArrayList_Int_get(&(self->enum_cache_types), ei));
}
    ei = (ei + 1LL);
}
    if (((((strcmp(resolved_type, "Int") == 0) || (strcmp(resolved_type, "Int64") == 0)) || (strcmp(resolved_type, "UInt64") == 0)) || (strcmp(resolved_type, "UInt32") == 0)) || (strcmp(resolved_type, "UInt16") == 0)) {
    return self->int64_type;
}
    if (((strcmp(resolved_type, "UInt8") == 0) || (strcmp(resolved_type, "u8") == 0)) || (strcmp(resolved_type, "i8") == 0)) {
    return self->int8_type;
}
    if ((((strcmp(resolved_type, "Int32") == 0) || (strcmp(resolved_type, "Int16") == 0)) || (strcmp(resolved_type, "i32") == 0)) || (strcmp(resolved_type, "u32") == 0)) {
    return self->int32_type;
}
    if (strcmp(resolved_type, "Int8") == 0) {
    return self->int8_type;
}
    if (strcmp(resolved_type, "Bool") == 0) {
    return self->int1_type;
}
    if (strcmp(resolved_type, "Float") == 0) {
    return self->double_type;
}
    if (strcmp(resolved_type, "Str") == 0) {
    return self->str_type;
}
    if (strcmp(resolved_type, "*Char") == 0) {
    return self->ptr_type;
}
    if (strcmp(resolved_type, "Char") == 0) {
    return self->int8_type;
}
    if (strcmp(resolved_type, "*Void") == 0) {
    return self->ptr_type;
}
    if ((strlen(resolved_type) > 0LL) && (((resolved_type)[0LL] == ((char)(42LL))) || ((resolved_type)[0LL] == ((char)(38LL))))) {
    return self->ptr_type;
}
    if (((strlen(resolved_type) > 2LL) && ((resolved_type)[0LL] == ((char)(91LL)))) && ((resolved_type)[1LL] == ((char)(93LL)))) {
    return self->ptr_type;
}
    if ((strcmp(resolved_type, "Void") == 0) || (strlen(resolved_type) == 0LL)) {
    return self->void_type;
}
    void* named_ty = LLVMGetTypeByName2(self->ctx, resolved_type);
    if ((named_ty != (void*)(unsigned long long)(0LL)) && (named_ty != self->void_type)) {
    ArrayList_Str_push(&(self->struct_cache_names), resolved_type);
    ArrayList_Int_push(&(self->struct_cache_types), (int64_t)(named_ty));
    ArrayList_Int_push(&(self->struct_cache_field_counts), 0LL);
    return named_ty;
}
    return self->int64_type;
}
void* LLVMCodegen_map_tuple_type(LLVMCodegen* self, const char* tuple_type_str) {
    int64_t ti = 0LL;
    while (ti < ArrayList_Str_length(&(self->tuple_cache_names))) {
    if (strcmp(ArrayList_Str_get(&(self->tuple_cache_names), ti), tuple_type_str) == 0) {
    return (void*)(unsigned long long)(ArrayList_Int_get(&(self->tuple_cache_types), ti));
}
    ti = (ti + 1LL);
}
    int64_t len = strlen(tuple_type_str);
    if (((len < 2LL) || ((tuple_type_str)[0LL] != ((char)(40LL)))) || ((tuple_type_str)[(len - 1LL)] != ((char)(41LL)))) {
    return self->void_type;
}
    const char* inner = __kai_str_sub(tuple_type_str, 1LL, (len - 1LL));
    ArrayList_Int field_types = ArrayList_Int_init(self->allocator);
    int64_t start = 0LL;
    int64_t i = 0LL;
    while (i < strlen(inner)) {
    if ((inner)[i] == ((char)(44LL))) {
    const char* ty_name = __kai_str_sub(inner, start, i);
    void* llvm_ty = LLVMCodegen_map_type(self, ty_name);
    if ((llvm_ty == self->void_type) || (llvm_ty == (void*)(unsigned long long)(0LL))) {
    ArrayList_Int_push(&(field_types), (int64_t)(self->int64_type));
} else {
    ArrayList_Int_push(&(field_types), (int64_t)(llvm_ty));
}
    i = (i + 2LL);
    start = i;
} else {
    i = (i + 1LL);
}
}
    if (start < strlen(inner)) {
    const char* ty_name = __kai_str_sub(inner, start, strlen(inner));
    void* llvm_ty = LLVMCodegen_map_type(self, ty_name);
    if ((llvm_ty == self->void_type) || (llvm_ty == (void*)(unsigned long long)(0LL))) {
    ArrayList_Int_push(&(field_types), (int64_t)(self->int64_type));
} else {
    ArrayList_Int_push(&(field_types), (int64_t)(llvm_ty));
}
}
    if (ArrayList_Int_length(&(field_types)) == 0LL) {
    return self->void_type;
}
    void* named_ty = LLVMStructCreateNamed(self->ctx, tuple_type_str);
    LLVMStructSetBody(named_ty, (void*)(field_types.data), ArrayList_Int_length(&(field_types)), false);
    ArrayList_Str_push(&(self->tuple_cache_names), tuple_type_str);
    ArrayList_Int_push(&(self->tuple_cache_types), (int64_t)(named_ty));
    ArrayList_Int_push(&(self->tuple_cache_field_counts), ArrayList_Int_length(&(field_types)));
    return named_ty;
}
void* LLVMCodegen_unwrap_str_for_c(LLVMCodegen* self, void* val) {
    if (val == (void*)(unsigned long long)(0LL)) {
    return val;
}
    void* val_ty = LLVMTypeOf(val);
    if (val_ty == self->str_type) {
    return kai_LLVMBuildExtractValue(self->builder, val, 0LL, ".c.ptr");
}
    return val;
}
void* LLVMCodegen_to_bool(LLVMCodegen* self, void* val) {
    if (val == (void*)(unsigned long long)(0LL)) {
    return LLVMConstInt(self->int1_type, 0LL, false);
}
    void* val_type = LLVMTypeOf(val);
    if (val_type == self->int1_type) {
    return val;
}
    void* zero = LLVMConstNull(val_type);
    void* cmp = LLVMBuildICmp(self->builder, LLVMIntNE, val, zero, "");
    return cmp;
}
void LLVMCodegen_ensure_reachable(LLVMCodegen* self) {
    if (self->last_was_term) {
    self->cur_block = LLVMAppendBasicBlockInContext(self->ctx, self->cur_func, "dead");
    LLVMPositionBuilderAtEnd(self->builder, self->cur_block);
    self->last_was_term = false;
}
}
void LLVMCodegen_gen_stmt(LLVMCodegen* self, int64_t stmt_idx) {
    if (stmt_idx < 0LL) {
    return;
}
    LLVMCodegen_ensure_reachable(self);
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, stmt_idx);
    if (stmt.kind == StmtKind_sk_block) {
    int64_t i = 0LL;
    while (i < ArrayList_Int_length(&(stmt.block_stmts))) {
    LLVMCodegen_gen_stmt(self, ArrayList_Int_get(&(stmt.block_stmts), i));
    i = (i + 1LL);
}
    return;
}
    if (stmt.kind == StmtKind_sk_return) {
    if (self->cur_method_is_init) {
    void* loaded_self = LLVMBuildLoad2(self->builder, self->cur_struct_type, self->cur_self_alloca, "");
    LLVMBuildRet(self->builder, loaded_self);
} else if (stmt.return_value >= 0LL) {
    void* val = LLVMCodegen_gen_expr(self, stmt.return_value);
    if (val != (void*)(unsigned long long)(0LL)) {
    const char* ret_type_str = LLVMCodegen_get_func_return_type(self, self->cur_func_name);
    void* ret_val = val;
    void* ret_llvm_ty = LLVMCodegen_map_type(self, ret_type_str);
    if ((ret_llvm_ty != self->void_type) && (ret_llvm_ty != (void*)(unsigned long long)(0LL))) {
    int64_t val_kind = LLVMGetTypeKind(LLVMTypeOf(val));
    int64_t ret_kind = LLVMGetTypeKind(ret_llvm_ty);
    if ((ret_kind == LLVMStructTypeKind) && (val_kind == LLVMPointerTypeKind)) {
    ret_val = LLVMBuildLoad2(self->builder, ret_llvm_ty, val, "");
}
}
    const char* actual_type_str = LLVMCodegen_get_expr_type(self, stmt.return_value);
    ret_val = LLVMCodegen_coerce_return_value(self, ret_val, ret_type_str, actual_type_str);
    LLVMBuildRet(self->builder, ret_val);
} else {
    const char* ret_type_str = LLVMCodegen_get_func_return_type(self, self->cur_func_name);
    void* ret_llvm_ty = LLVMCodegen_map_type(self, ret_type_str);
    if ((ret_llvm_ty == self->void_type) || (ret_llvm_ty == (void*)(unsigned long long)(0LL))) {
    LLVMBuildRetVoid(self->builder);
} else {
    LLVMBuildRet(self->builder, LLVMConstNull(ret_llvm_ty));
}
}
} else {
    LLVMBuildRetVoid(self->builder);
}
    self->last_was_term = true;
    return;
}
    if (stmt.kind == StmtKind_sk_expr) {
    if (stmt.expr_stmt >= 0LL) {
    (void)(LLVMCodegen_gen_expr(self, stmt.expr_stmt));
}
    return;
}
    if (stmt.kind == StmtKind_sk_var_decl) {
    const char* var_name = stmt.vardecl_name;
    const char* var_type_str = stmt.vardecl_type;
    if (((strcmp(var_name, "_") == 0) || (strcmp(var_type_str, "Void") == 0)) || (strcmp(var_type_str, "NoneType") == 0)) {
    if (stmt.vardecl_value >= 0LL) {
    (void)(LLVMCodegen_gen_expr(self, stmt.vardecl_value));
}
    return;
}
    if (stmt.vardecl_value >= 0LL) {
    ExprNode init_expr = ArrayList_ExprNode_get(self->expr_pool, stmt.vardecl_value);
    if (init_expr.kind == ExprKind_ek_array) {
    const char* inner_type_str = "Int";
    if (((strlen(init_expr.inferred_type) > 2LL) && ((init_expr.inferred_type)[0LL] == ((char)(91LL)))) && ((init_expr.inferred_type)[1LL] == ((char)(93LL)))) {
    inner_type_str = __kai_str_sub(init_expr.inferred_type, 2LL, strlen(init_expr.inferred_type));
}
    void* inner_llvm_type = LLVMCodegen_map_type(self, inner_type_str);
    if ((inner_llvm_type == self->void_type) || (inner_llvm_type == (void*)(unsigned long long)(0LL))) {
    inner_llvm_type = self->int64_type;
}
    int64_t count = ArrayList_Int_length(&(init_expr.arr_elements));
    void* arr_type = inner_llvm_type;
    if (count > 0LL) {
    arr_type = LLVMArrayType(inner_llvm_type, count);
}
    void* alloca_val = LLVMBuildAlloca(self->builder, arr_type, var_name);
    if (count > 0LL) {
    void* el_ptr_ty = LLVMPointerType(inner_llvm_type, 0LL);
    void* casted = LLVMBuildBitCast(self->builder, alloca_val, el_ptr_ty, "");
    int64_t ai = 0LL;
    while (ai < count) {
    void* elem_val = LLVMCodegen_gen_expr(self, ArrayList_Int_get(&(init_expr.arr_elements), ai));
    if (elem_val != (void*)(unsigned long long)(0LL)) {
    ArrayList_Int indices = ArrayList_Int_init(self->allocator);
    ArrayList_Int_push(&(indices), (int64_t)(LLVMConstInt(self->int64_type, ai, false)));
    void* gep = LLVMBuildGEP2(self->builder, inner_llvm_type, casted, (void*)(indices.data), 1LL, "");
    LLVMBuildStore(self->builder, elem_val, gep);
}
    ai = (ai + 1LL);
}
}
    ArrayList_Str_push(&(self->local_alloca_names), var_name);
    ArrayList_Int_push(&(self->local_alloca_vals), (int64_t)(alloca_val));
    ArrayList_Int_push(&(self->local_alloca_types), (int64_t)(arr_type));
    const char* arr_type_str = stmt.vardecl_type;
    if (strlen(arr_type_str) == 0LL) {
    arr_type_str = concatAlloc("[]", inner_type_str);
}
    ArrayList_Str_push(&(self->local_alloca_type_strs), arr_type_str);
    ArrayList_Int_push(&(self->local_alloca_decls), stmt_idx);
    return;
}
}
    if (strlen(var_type_str) == 0LL) {
    if (stmt.vardecl_value >= 0LL) {
    var_type_str = LLVMCodegen_get_expr_type(self, stmt.vardecl_value);
}
}
    if ((strlen(var_type_str) == 0LL) && (stmt.vardecl_value >= 0LL)) {
    ExprNode init_expr = ArrayList_ExprNode_get(self->expr_pool, stmt.vardecl_value);
    if ((init_expr.kind == ExprKind_ek_func_call) && ((strcmp(init_expr.func_name, "as") == 0) || (strcmp(init_expr.func_name, "cast") == 0))) {
    if (ArrayList_Str_length(&(init_expr.func_type_args)) > 0LL) {
    var_type_str = ArrayList_Str_get(&(init_expr.func_type_args), 0LL);
}
}
}
    void* generated_init = (void*)(unsigned long long)(0LL);
    if ((strlen(var_type_str) == 0LL) && (stmt.vardecl_value >= 0LL)) {
    generated_init = LLVMCodegen_gen_expr(self, stmt.vardecl_value);
    if (generated_init != (void*)(unsigned long long)(0LL)) {
    void* init_llvm_ty = LLVMTypeOf(generated_init);
    if (init_llvm_ty == self->str_type) {
    var_type_str = "Str";
}
}
}
    void* var_type = LLVMCodegen_map_type(self, var_type_str);
    if (var_type == self->void_type) {
    if (generated_init != (void*)(unsigned long long)(0LL)) {
    var_type = LLVMTypeOf(generated_init);
}
}
    if ((var_type == self->void_type) || (var_type == (void*)(unsigned long long)(0LL))) {
    var_type = self->int64_type;
}
    void* alloca_val = LLVMBuildAlloca(self->builder, var_type, var_name);
    if (stmt.vardecl_value >= 0LL) {
    void* init_val = generated_init;
    if (init_val == (void*)(unsigned long long)(0LL)) {
    init_val = LLVMCodegen_gen_expr(self, stmt.vardecl_value);
}
    if (init_val != (void*)(unsigned long long)(0LL)) {
    void* init_llvm_ty = LLVMTypeOf(init_val);
    if (init_llvm_ty == self->void_type) {
} else {
    int64_t init_kind = LLVMGetTypeKind(init_llvm_ty);
    int64_t dest_kind = LLVMGetTypeKind(var_type);
    if ((init_kind == LLVMPointerTypeKind) && (dest_kind == LLVMStructTypeKind)) {
    void* loaded = LLVMBuildLoad2(self->builder, var_type, init_val, "");
    LLVMBuildStore(self->builder, loaded, alloca_val);
} else if ((init_kind == LLVMStructTypeKind) && (dest_kind == LLVMPointerTypeKind)) {
    void* struct_alloca = LLVMBuildAlloca(self->builder, init_llvm_ty, ".tmp_struct");
    LLVMBuildStore(self->builder, init_val, struct_alloca);
    LLVMBuildStore(self->builder, struct_alloca, alloca_val);
} else {
    LLVMBuildStore(self->builder, init_val, alloca_val);
}
}
}
}
    ArrayList_Str_push(&(self->local_alloca_names), var_name);
    ArrayList_Int_push(&(self->local_alloca_vals), (int64_t)(alloca_val));
    ArrayList_Int_push(&(self->local_alloca_types), (int64_t)(var_type));
    ArrayList_Str_push(&(self->local_alloca_type_strs), var_type_str);
    ArrayList_Int_push(&(self->local_alloca_decls), stmt_idx);
    return;
}
    if (stmt.kind == StmtKind_sk_assignment) {
    void* val = LLVMCodegen_gen_expr(self, stmt.assign_value);
    if (val != (void*)(unsigned long long)(0LL)) {
    void* val_ty = LLVMTypeOf(val);
    if (val_ty == self->void_type) {
    return;
}
    ExprNode target_expr = ArrayList_ExprNode_get(self->expr_pool, stmt.assign_target);
    if (target_expr.kind == ExprKind_ek_identifier) {
    const char* var_name = target_expr.ident_name;
    void* alloca = LLVMCodegen_find_alloca(self, var_name);
    if (alloca != (void*)(unsigned long long)(0LL)) {
    LLVMBuildStore(self->builder, val, alloca);
}
} else if (target_expr.kind == ExprKind_ek_field_access) {
    void* base_val = LLVMCodegen_gen_expr(self, target_expr.field_expr);
    if (base_val != (void*)(unsigned long long)(0LL)) {
    const char* base_type = LLVMCodegen_get_expr_type(self, target_expr.field_expr);
    const char* clean_base_type = base_type;
    while ((strlen(clean_base_type) > 0LL) && (((clean_base_type)[0LL] == ((char)(42LL))) || ((clean_base_type)[0LL] == ((char)(38LL))))) {
    clean_base_type = __kai_str_sub(clean_base_type, 1LL, strlen(clean_base_type));
}
    int64_t struct_decl_idx = LLVMCodegen_find_struct_decl(self, clean_base_type);
    int64_t field_idx = (-1LL);
    bool found_field = false;
    if (struct_decl_idx >= 0LL) {
    StmtNode sn = ArrayList_StmtNode_get(self->stmt_pool, struct_decl_idx);
    int64_t fj = 0LL;
    while (fj < ArrayList_StructField_length(&(sn.struct_fields))) {
    if (strcmp(ArrayList_StructField_get(&(sn.struct_fields), fj).name, target_expr.field_name) == 0) {
    field_idx = fj;
    found_field = true;
    break;
}
    fj = (fj + 1LL);
}
}
    if (found_field) {
    void* struct_ty = LLVMCodegen_map_type(self, clean_base_type);
    if ((struct_ty != (void*)(unsigned long long)(0LL)) && (struct_ty != self->void_type)) {
    void* base_ptr = base_val;
    void* base_llvm_ty2 = LLVMTypeOf(base_val);
    int64_t base_kind2 = LLVMGetTypeKind(base_llvm_ty2);
    if (base_kind2 == LLVMStructTypeKind) {
    void* tmp = LLVMBuildAlloca(self->builder, struct_ty, ".tmp.assign");
    LLVMBuildStore(self->builder, base_val, tmp);
    base_ptr = tmp;
}
    void* gep = LLVMBuildStructGEP2(self->builder, struct_ty, base_ptr, field_idx, target_expr.field_name);
    LLVMBuildStore(self->builder, val, gep);
}
}
}
} else if (target_expr.kind == ExprKind_ek_index) {
    void* base_val = LLVMCodegen_gen_expr(self, target_expr.idx_expr);
    void* idx_val = LLVMCodegen_gen_expr(self, target_expr.idx_index);
    if ((base_val != (void*)(unsigned long long)(0LL)) && (idx_val != (void*)(unsigned long long)(0LL))) {
    void* store_ptr = base_val;
    void* base_llvm_ty4 = LLVMTypeOf(base_val);
    if (base_llvm_ty4 == self->str_type) {
    store_ptr = LLVMCodegen_unwrap_str_for_c(self, base_val);
}
    const char* el_type_str = LLVMCodegen_get_expr_type(self, stmt.assign_target);
    void* el_ty = LLVMCodegen_map_type(self, el_type_str);
    if ((el_ty == (void*)(unsigned long long)(0LL)) || (el_ty == self->void_type)) {
    el_ty = LLVMTypeOf(val);
}
    void* store_val = LLVMCodegen_gen_cast(self, val, el_ty);
    void* gep_idx2 = idx_val;
    void* idx_ty2 = LLVMTypeOf(idx_val);
    if (idx_ty2 != self->int64_type) {
    gep_idx2 = LLVMBuildSExt(self->builder, idx_val, self->int64_type, "");
}
    void* el_ptr_ty2 = LLVMPointerType(el_ty, 0LL);
    void* casted2 = LLVMBuildBitCast(self->builder, store_ptr, el_ptr_ty2, "");
    ArrayList_Int indices2 = ArrayList_Int_init(self->allocator);
    ArrayList_Int_push(&(indices2), (int64_t)(gep_idx2));
    void* gep2 = LLVMBuildGEP2(self->builder, el_ty, casted2, (void*)(indices2.data), 1LL, "");
    LLVMBuildStore(self->builder, store_val, gep2);
}
}
}
    return;
}
    if (stmt.kind == StmtKind_sk_for) {
    void* start_val = LLVMCodegen_gen_expr(self, stmt.for_start);
    void* end_val = LLVMCodegen_gen_expr(self, stmt.for_end);
    if ((start_val == (void*)(unsigned long long)(0LL)) || (end_val == (void*)(unsigned long long)(0LL))) {
    return;
}
    const char* var_name = stmt.for_var;
    int64_t prev_alloca_len = ArrayList_Str_length(&(self->local_alloca_names));
    void* alloca_val = LLVMBuildAlloca(self->builder, self->int64_type, var_name);
    ArrayList_Str_push(&(self->local_alloca_names), var_name);
    ArrayList_Int_push(&(self->local_alloca_vals), (int64_t)(alloca_val));
    ArrayList_Int_push(&(self->local_alloca_types), (int64_t)(self->int64_type));
    ArrayList_Int_push(&(self->local_alloca_decls), stmt_idx);
    LLVMBuildStore(self->builder, start_val, alloca_val);
    void* cond_block = LLVMAppendBasicBlockInContext(self->ctx, self->cur_func, "for_cond");
    void* body_block = LLVMAppendBasicBlockInContext(self->ctx, self->cur_func, "for_body");
    void* inc_block = LLVMAppendBasicBlockInContext(self->ctx, self->cur_func, "for_inc");
    void* merge_block = LLVMAppendBasicBlockInContext(self->ctx, self->cur_func, "for_merge");
    void* prev_cond = self->loop_cond_block;
    void* prev_merge = self->loop_merge_block;
    self->loop_cond_block = cond_block;
    self->loop_merge_block = merge_block;
    LLVMBuildBr(self->builder, cond_block);
    LLVMPositionBuilderAtEnd(self->builder, cond_block);
    self->last_was_term = false;
    void* cur_val = LLVMBuildLoad2(self->builder, self->int64_type, alloca_val, "");
    if (stmt.for_inclusive) {
    void* cmp = LLVMBuildICmp(self->builder, LLVMIntSLE, cur_val, end_val, "");
    LLVMBuildCondBr(self->builder, cmp, body_block, merge_block);
} else {
    void* cmp = LLVMBuildICmp(self->builder, LLVMIntSLT, cur_val, end_val, "");
    LLVMBuildCondBr(self->builder, cmp, body_block, merge_block);
}
    LLVMPositionBuilderAtEnd(self->builder, body_block);
    self->last_was_term = false;
    LLVMCodegen_gen_stmt(self, stmt.for_body);
    if (!self->last_was_term) {
    LLVMBuildBr(self->builder, inc_block);
}
    LLVMPositionBuilderAtEnd(self->builder, inc_block);
    self->last_was_term = false;
    void* one = LLVMConstInt(self->int64_type, 1LL, false);
    void* inc_val = LLVMBuildLoad2(self->builder, self->int64_type, alloca_val, "");
    void* updated = LLVMBuildAdd(self->builder, inc_val, one, "");
    LLVMBuildStore(self->builder, updated, alloca_val);
    LLVMBuildBr(self->builder, cond_block);
    self->loop_cond_block = prev_cond;
    self->loop_merge_block = prev_merge;
    while (ArrayList_Str_length(&(self->local_alloca_names)) > prev_alloca_len) {
    (void)(ArrayList_Str_pop(&(self->local_alloca_names)));
    (void)(ArrayList_Int_pop(&(self->local_alloca_vals)));
    (void)(ArrayList_Int_pop(&(self->local_alloca_types)));
}
    LLVMPositionBuilderAtEnd(self->builder, merge_block);
    self->last_was_term = false;
    return;
}
    if (stmt.kind == StmtKind_sk_break) {
    if (self->loop_merge_block != (void*)(unsigned long long)(0LL)) {
    LLVMBuildBr(self->builder, self->loop_merge_block);
    self->last_was_term = true;
}
    return;
}
    if (stmt.kind == StmtKind_sk_continue) {
    if (self->loop_cond_block != (void*)(unsigned long long)(0LL)) {
    LLVMBuildBr(self->builder, self->loop_cond_block);
    self->last_was_term = true;
}
    return;
}
    if (stmt.kind == StmtKind_sk_if_let) {
    void* cond_val = LLVMCodegen_gen_expr(self, stmt.iflet_expr);
    if (cond_val == (void*)(unsigned long long)(0LL)) {
    return;
}
    void* then_block = LLVMAppendBasicBlockInContext(self->ctx, self->cur_func, "ifthen");
    void* merge_block = LLVMAppendBasicBlockInContext(self->ctx, self->cur_func, "iflet_merge");
    void* iflet_var_type = self->int64_type;
    void* bound_type = LLVMTypeOf(cond_val);
    if (bound_type != (void*)(unsigned long long)(0LL)) {
    iflet_var_type = bound_type;
}
    void* iflet_alloca = LLVMBuildAlloca(self->builder, iflet_var_type, stmt.iflet_var);
    LLVMBuildStore(self->builder, cond_val, iflet_alloca);
    int64_t prev_len = ArrayList_Str_length(&(self->local_alloca_names));
    ArrayList_Str_push(&(self->local_alloca_names), stmt.iflet_var);
    ArrayList_Int_push(&(self->local_alloca_vals), (int64_t)(iflet_alloca));
    ArrayList_Int_push(&(self->local_alloca_types), (int64_t)(iflet_var_type));
    ArrayList_Int_push(&(self->local_alloca_decls), stmt_idx);
    if (stmt.iflet_else >= 0LL) {
    void* else_block = LLVMAppendBasicBlockInContext(self->ctx, self->cur_func, "iflelse");
    void* is_nonzero = LLVMCodegen_to_bool(self, cond_val);
    LLVMBuildCondBr(self->builder, is_nonzero, then_block, else_block);
    LLVMPositionBuilderAtEnd(self->builder, then_block);
    self->last_was_term = false;
    LLVMCodegen_gen_stmt(self, stmt.iflet_then);
    if (!self->last_was_term) {
    LLVMBuildBr(self->builder, merge_block);
}
    LLVMPositionBuilderAtEnd(self->builder, else_block);
    self->last_was_term = false;
    LLVMCodegen_gen_stmt(self, stmt.iflet_else);
    if (!self->last_was_term) {
    LLVMBuildBr(self->builder, merge_block);
}
} else {
    void* is_nonzero = LLVMCodegen_to_bool(self, cond_val);
    LLVMBuildCondBr(self->builder, is_nonzero, then_block, merge_block);
    LLVMPositionBuilderAtEnd(self->builder, then_block);
    self->last_was_term = false;
    LLVMCodegen_gen_stmt(self, stmt.iflet_then);
    if (!self->last_was_term) {
    LLVMBuildBr(self->builder, merge_block);
}
}
    while (ArrayList_Str_length(&(self->local_alloca_names)) > prev_len) {
    (void)(ArrayList_Str_pop(&(self->local_alloca_names)));
    (void)(ArrayList_Int_pop(&(self->local_alloca_vals)));
    (void)(ArrayList_Int_pop(&(self->local_alloca_types)));
}
    LLVMPositionBuilderAtEnd(self->builder, merge_block);
    self->last_was_term = false;
    return;
}
    if (stmt.kind == StmtKind_sk_while) {
    void* cond_block = LLVMAppendBasicBlockInContext(self->ctx, self->cur_func, "while_cond");
    void* body_block = LLVMAppendBasicBlockInContext(self->ctx, self->cur_func, "while_body");
    void* merge_block = LLVMAppendBasicBlockInContext(self->ctx, self->cur_func, "while_merge");
    void* prev_cond = self->loop_cond_block;
    void* prev_merge = self->loop_merge_block;
    self->loop_cond_block = cond_block;
    self->loop_merge_block = merge_block;
    LLVMBuildBr(self->builder, cond_block);
    LLVMPositionBuilderAtEnd(self->builder, cond_block);
    self->last_was_term = false;
    void* cond_val = LLVMCodegen_to_bool(self, LLVMCodegen_gen_expr(self, stmt.while_cond));
    LLVMBuildCondBr(self->builder, cond_val, body_block, merge_block);
    LLVMPositionBuilderAtEnd(self->builder, body_block);
    self->last_was_term = false;
    LLVMCodegen_gen_stmt(self, stmt.while_body);
    if (!self->last_was_term) {
    LLVMBuildBr(self->builder, cond_block);
}
    self->loop_cond_block = prev_cond;
    self->loop_merge_block = prev_merge;
    LLVMPositionBuilderAtEnd(self->builder, merge_block);
    self->last_was_term = false;
    return;
}
    if (stmt.kind == StmtKind_sk_if) {
    void* cond_val = LLVMCodegen_to_bool(self, LLVMCodegen_gen_expr(self, stmt.if_cond));
    void* then_block = LLVMAppendBasicBlockInContext(self->ctx, self->cur_func, "then");
    void* merge_block = LLVMAppendBasicBlockInContext(self->ctx, self->cur_func, "if_merge");
    if (stmt.if_else >= 0LL) {
    void* else_block = LLVMAppendBasicBlockInContext(self->ctx, self->cur_func, "else");
    LLVMBuildCondBr(self->builder, cond_val, then_block, else_block);
    LLVMPositionBuilderAtEnd(self->builder, then_block);
    self->last_was_term = false;
    LLVMCodegen_gen_stmt(self, stmt.if_then);
    if (!self->last_was_term) {
    LLVMBuildBr(self->builder, merge_block);
}
    LLVMPositionBuilderAtEnd(self->builder, else_block);
    self->last_was_term = false;
    LLVMCodegen_gen_stmt(self, stmt.if_else);
    if (!self->last_was_term) {
    LLVMBuildBr(self->builder, merge_block);
}
} else {
    LLVMBuildCondBr(self->builder, cond_val, then_block, merge_block);
    LLVMPositionBuilderAtEnd(self->builder, then_block);
    self->last_was_term = false;
    LLVMCodegen_gen_stmt(self, stmt.if_then);
    if (!self->last_was_term) {
    LLVMBuildBr(self->builder, merge_block);
}
}
    LLVMPositionBuilderAtEnd(self->builder, merge_block);
    self->last_was_term = false;
    return;
}
    if (stmt.kind == StmtKind_sk_defer) {
    LLVMCodegen_gen_stmt(self, stmt.defer_body);
    return;
}
    if (stmt.kind == StmtKind_sk_print) {
    void* val = LLVMCodegen_gen_expr(self, stmt.print_value);
    if (val == (void*)(unsigned long long)(0LL)) {
    return;
}
    void* printf_fn = LLVMCodegen_lookup_or_create_func(self, "printf");
    void* val_type = LLVMTypeOf(val);
    if (val_type == self->int64_type) {
    void* fmt_str = LLVMBuildGlobalStringPtr(self->builder, "%lld\n", ".fmt_int");
    void* p_char = LLVMCodegen_map_type(self, "*Char");
    void* fn_ty = kai_func_type_2(self->int64_type, p_char, self->int64_type, true);
    (void)(kai_build_call_2(self->builder, fn_ty, printf_fn, fmt_str, val, ""));
} else if (val_type == self->double_type) {
    void* fmt_str = LLVMBuildGlobalStringPtr(self->builder, "%f\n", ".fmt_float");
    void* p_char = LLVMCodegen_map_type(self, "*Char");
    void* fn_ty = kai_func_type_2(self->int64_type, p_char, self->double_type, true);
    (void)(kai_build_call_2(self->builder, fn_ty, printf_fn, fmt_str, val, ""));
} else if (val != (void*)(unsigned long long)(0LL)) {
    void* fmt_str = LLVMBuildGlobalStringPtr(self->builder, "%s\n", ".fmt_str");
    void* p_char = LLVMCodegen_map_type(self, "*Char");
    void* fn_ty = kai_func_type_2(self->int64_type, p_char, self->ptr_type, true);
    (void)(kai_build_call_2(self->builder, fn_ty, printf_fn, fmt_str, val, ""));
}
    return;
}
    if (stmt.kind == StmtKind_sk_errdefer) {
    LLVMCodegen_gen_stmt(self, stmt.errdefer_body);
    return;
}
    if (stmt.kind == StmtKind_sk_unsafe) {
    LLVMCodegen_gen_stmt(self, stmt.unsafe_body);
    return;
}
    if (stmt.kind == StmtKind_sk_func_decl) {
    return;
}
    if (stmt.kind == StmtKind_sk_extern) {
    return;
}
    if (stmt.kind == StmtKind_sk_struct_decl) {
    return;
}
    if (stmt.kind == StmtKind_sk_enum_decl) {
    return;
}
    if (stmt.kind == StmtKind_sk_trait_decl) {
    return;
}
    if (stmt.kind == StmtKind_sk_import) {
    return;
}
    if (stmt.kind == StmtKind_sk_cimport) {
    return;
}
    if (stmt.kind == StmtKind_sk_error_decl) {
    return;
}
    if (stmt.kind == StmtKind_sk_none) {
    return;
}
    if (stmt.kind == StmtKind_sk_impl_block) {
    int64_t mi = 0LL;
    while (mi < ArrayList_Int_length(&(stmt.impl_methods))) {
    int64_t method_idx = ArrayList_Int_get(&(stmt.impl_methods), mi);
    StmtNode method_stmt = ArrayList_StmtNode_get(self->stmt_pool, method_idx);
    if (method_stmt.kind == StmtKind_sk_func_decl) {
    void* fn_val = LLVMCodegen_lookup_or_create_func(self, method_stmt.func_name);
    LLVMCodegen_emit_func_body(self, method_idx, fn_val, stmt.impl_struct_name);
}
    mi = (mi + 1LL);
}
    return;
}
    if (stmt.kind == StmtKind_sk_match) {
    void* match_expr_val = LLVMCodegen_gen_expr(self, stmt.match_expr);
    if (match_expr_val == (void*)(unsigned long long)(0LL)) {
    return;
}
    ExprNode match_expr_node = ArrayList_ExprNode_get(self->expr_pool, stmt.match_expr);
    const char* match_expr_type = LLVMCodegen_get_expr_type(self, stmt.match_expr);
    const char* clean_type = match_expr_type;
    if (strlen(clean_type) == 0LL) {
    void* rec_ty = LLVMTypeOf(match_expr_val);
    const char* ty_str = (const char*)(LLVMPrintTypeToString(rec_ty));
    int64_t start_idx = 0LL;
    if ((strlen(ty_str) > 8LL) && (strcmp(__kai_str_sub(ty_str, 0LL, 8LL), "%struct.") == 0)) {
    start_idx = 8LL;
} else if ((strlen(ty_str) > 1LL) && ((ty_str)[0LL] == ((char)(37LL)))) {
    start_idx = 1LL;
}
    int64_t end_idx = strlen(ty_str);
    while ((end_idx > start_idx) && ((((ty_str)[(end_idx - 1LL)] == ((char)(42LL))) || ((ty_str)[(end_idx - 1LL)] == ((char)(38LL)))) || ((ty_str)[(end_idx - 1LL)] == ((char)(32LL))))) {
    end_idx = (end_idx - 1LL);
}
    if (end_idx > start_idx) {
    clean_type = __kai_str_sub(ty_str, start_idx, end_idx);
}
}
    while ((strlen(clean_type) > 0LL) && (((clean_type)[0LL] == ((char)(42LL))) || ((clean_type)[0LL] == ((char)(38LL))))) {
    clean_type = __kai_str_sub(clean_type, 1LL, strlen(clean_type));
}
    if ((strlen(clean_type) >= 4LL) && (strcmp(__kai_str_sub(clean_type, 0LL, 4LL), "mut ") == 0)) {
    clean_type = __kai_str_sub(clean_type, 4LL, strlen(clean_type));
}
    void* mapped_type = LLVMCodegen_map_type(self, clean_type);
    void* llvm_match_type = mapped_type;
    if (llvm_match_type == (void*)(unsigned long long)(0LL)) {
    llvm_match_type = self->int64_type;
}
    bool is_ptr = false;
    if ((strlen(match_expr_type) > 0LL) && (((match_expr_type)[0LL] == ((char)(42LL))) || ((match_expr_type)[0LL] == ((char)(38LL))))) {
    is_ptr = true;
}
    void* match_end_block = LLVMAppendBasicBlockInContext(self->ctx, self->cur_func, "match_end");
    int64_t case_idx = 0LL;
    while (case_idx < ArrayList_MatchCase_length(&(stmt.match_cases))) {
    MatchCase case_node = ArrayList_MatchCase_get(&(stmt.match_cases), case_idx);
    PatternNode pat_node = ArrayList_PatternNode_get(self->pattern_pool, case_node.pattern);
    void* then_block = LLVMAppendBasicBlockInContext(self->ctx, self->cur_func, "match_then");
    void* merge_block = (void*)(unsigned long long)(0LL);
    if (case_idx < (ArrayList_MatchCase_length(&(stmt.match_cases)) - 1LL)) {
    merge_block = LLVMAppendBasicBlockInContext(self->ctx, self->cur_func, "match_next");
} else {
    merge_block = match_end_block;
}
    if (pat_node.kind == PatternKind_pk_literal) {
    void* lit_val = (void*)(unsigned long long)(0LL);
    if (pat_node.lit_value.tag == TokenValue_tv_int_TAG) {
    int64_t v = pat_node.lit_value.payload.tv_int.v;

    lit_val = LLVMConstInt(self->int64_type, v, false);
} else if (pat_node.lit_value.tag == TokenValue_tv_bool_TAG) {
    bool v = pat_node.lit_value.payload.tv_bool.v;

    if (v) {
    lit_val = LLVMConstInt(self->int1_type, 1LL, false);
} else {
    lit_val = LLVMConstInt(self->int1_type, 0LL, false);
}
} else {
    lit_val = LLVMConstInt(self->int64_type, 0LL, false);
} 
    void* cmp = LLVMBuildICmp(self->builder, LLVMIntEQ, match_expr_val, lit_val, "");
    LLVMBuildCondBr(self->builder, cmp, then_block, merge_block);
} else if (pat_node.kind == PatternKind_pk_variant) {
    int64_t target_tag_idx = 0LL;
    int64_t enum_stmt_idx = 0LL;
    while (enum_stmt_idx < ArrayList_StmtNode_length(self->stmt_pool)) {
    StmtNode s = ArrayList_StmtNode_get(self->stmt_pool, enum_stmt_idx);
    if ((s.kind == StmtKind_sk_enum_decl) && (strcmp(s.enum_name, clean_type) == 0)) {
    int64_t vi = 0LL;
    while (vi < ArrayList_Variant_length(&(s.enum_variants))) {
    if (strcmp(ArrayList_Variant_get(&(s.enum_variants), vi).vname, pat_node.variant_name) == 0) {
    target_tag_idx = vi;
    break;
}
    vi = (vi + 1LL);
}
}
    enum_stmt_idx = (enum_stmt_idx + 1LL);
}
    bool has_payload_enum = false;
    const char* stripped_clean_type = LLVMCodegen_strip_module_prefix(self, clean_type);
    int64_t ei = 0LL;
    while (ei < ArrayList_Str_length(&(self->enum_cache_names))) {
    if ((strcmp(ArrayList_Str_get(&(self->enum_cache_names), ei), stripped_clean_type) == 0) && ArrayList_Bool_get(&(self->enum_has_payload), ei)) {
    has_payload_enum = true;
}
    ei = (ei + 1LL);
}
    if (has_payload_enum) {
    void* gep = LLVMBuildStructGEP2(self->builder, llvm_match_type, match_expr_val, 0LL, ".tag");
    void* actual_tag = LLVMBuildLoad2(self->builder, self->int8_type, gep, "");
    void* tag_val = LLVMConstInt(self->int8_type, target_tag_idx, false);
    void* cmp = LLVMBuildICmp(self->builder, LLVMIntEQ, actual_tag, tag_val, "");
    LLVMBuildCondBr(self->builder, cmp, then_block, merge_block);
    LLVMPositionBuilderAtEnd(self->builder, then_block);
    self->last_was_term = false;
    int64_t enum_stmt_idx2 = 0LL;
    bool found_enum = false;
    Variant matched_var = (Variant){ .vname = "", .params = empty_param_array() };
    while (enum_stmt_idx2 < ArrayList_StmtNode_length(self->stmt_pool)) {
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, enum_stmt_idx2);
    if ((stmt.kind == StmtKind_sk_enum_decl) && (strcmp(stmt.enum_name, clean_type) == 0)) {
    int64_t vi = 0LL;
    while (vi < ArrayList_Variant_length(&(stmt.enum_variants))) {
    Variant v = ArrayList_Variant_get(&(stmt.enum_variants), vi);
    if (strcmp(v.vname, pat_node.variant_name) == 0) {
    matched_var = v;
    found_enum = true;
}
    vi = (vi + 1LL);
}
}
    enum_stmt_idx2 = (enum_stmt_idx2 + 1LL);
}
    if (found_enum) {
    ArrayList_Int variant_field_types = ArrayList_Int_init(self->allocator);
    int64_t p_idx = 0LL;
    while (p_idx < ArrayList_Param_length(&(matched_var.params))) {
    Param p = ArrayList_Param_get(&(matched_var.params), p_idx);
    void* p_llvm_ty = LLVMCodegen_map_type(self, p.ptype);
    ArrayList_Int_push(&(variant_field_types), (int64_t)(p_llvm_ty));
    p_idx = (p_idx + 1LL);
}
    void* variant_struct_ty = LLVMStructTypeInContext(self->ctx, (void*)(variant_field_types.data), ArrayList_Int_length(&(variant_field_types)), false);
    void* payload_gep = LLVMBuildStructGEP2(self->builder, llvm_match_type, match_expr_val, 1LL, ".payload");
    void* casted_payload_ptr = LLVMBuildBitCast(self->builder, payload_gep, LLVMPointerType(variant_struct_ty, 0LL), "");
    int64_t bi = 0LL;
    while (bi < ArrayList_Str_length(&(pat_node.bindings))) {
    const char* bind_name = ArrayList_Str_get(&(pat_node.bindings), bi);
    if ((strcmp(bind_name, "_") != 0) && (bi < ArrayList_Param_length(&(matched_var.params)))) {
    Param param = ArrayList_Param_get(&(matched_var.params), bi);
    void* p_llvm_ty = LLVMCodegen_map_type(self, param.ptype);
    void* dest_gep = LLVMBuildStructGEP2(self->builder, variant_struct_ty, casted_payload_ptr, bi, "");
    void* loaded_val = LLVMBuildLoad2(self->builder, p_llvm_ty, dest_gep, "");
    void* bind_alloca = LLVMBuildAlloca(self->builder, p_llvm_ty, bind_name);
    LLVMBuildStore(self->builder, loaded_val, bind_alloca);
    ArrayList_Str_push(&(self->local_alloca_names), bind_name);
    ArrayList_Int_push(&(self->local_alloca_vals), (int64_t)(bind_alloca));
    ArrayList_Int_push(&(self->local_alloca_types), (int64_t)(p_llvm_ty));
    ArrayList_Str_push(&(self->local_alloca_type_strs), param.ptype);
    ArrayList_Int_push(&(self->local_alloca_decls), stmt_idx);
}
    bi = (bi + 1LL);
}
}
} else {
    void* tag_val = LLVMConstInt(self->int64_type, target_tag_idx, false);
    void* cmp = LLVMBuildICmp(self->builder, LLVMIntEQ, match_expr_val, tag_val, "");
    LLVMBuildCondBr(self->builder, cmp, then_block, merge_block);
}
} else if (pat_node.kind == PatternKind_pk_else) {
    LLVMBuildBr(self->builder, then_block);
}
    LLVMPositionBuilderAtEnd(self->builder, then_block);
    self->last_was_term = false;
    LLVMCodegen_gen_stmt(self, case_node.body);
    if (!self->last_was_term) {
    LLVMBuildBr(self->builder, match_end_block);
}
    LLVMPositionBuilderAtEnd(self->builder, merge_block);
    self->last_was_term = false;
    case_idx = (case_idx + 1LL);
}
    return;
}
}
void* LLVMCodegen_find_alloca_by_idx(LLVMCodegen* self, int64_t decl_idx, const char* name) {
    int64_t i = (ArrayList_Int_length(&(self->local_alloca_decls)) - 1LL);
    while (i >= 0LL) {
    if ((ArrayList_Int_get(&(self->local_alloca_decls), i) == decl_idx) && (strcmp(ArrayList_Str_get(&(self->local_alloca_names), i), name) == 0)) {
    return (void*)(unsigned long long)(ArrayList_Int_get(&(self->local_alloca_vals), i));
}
    i = (i - 1LL);
}
    return (void*)(unsigned long long)(0LL);
}
void* LLVMCodegen_find_alloca_type_by_idx(LLVMCodegen* self, int64_t decl_idx, const char* name) {
    int64_t i = (ArrayList_Int_length(&(self->local_alloca_decls)) - 1LL);
    while (i >= 0LL) {
    if ((ArrayList_Int_get(&(self->local_alloca_decls), i) == decl_idx) && (strcmp(ArrayList_Str_get(&(self->local_alloca_names), i), name) == 0)) {
    return (void*)(unsigned long long)(ArrayList_Int_get(&(self->local_alloca_types), i));
}
    i = (i - 1LL);
}
    return (void*)(unsigned long long)(0LL);
}
void* LLVMCodegen_find_alloca(LLVMCodegen* self, const char* name) {
    int64_t i = (ArrayList_Str_length(&(self->local_alloca_names)) - 1LL);
    while (i >= 0LL) {
    if (strcmp(ArrayList_Str_get(&(self->local_alloca_names), i), name) == 0) {
    return (void*)(unsigned long long)(ArrayList_Int_get(&(self->local_alloca_vals), i));
}
    i = (i - 1LL);
}
    return (void*)(unsigned long long)(0LL);
}
void* LLVMCodegen_find_alloca_type(LLVMCodegen* self, const char* name) {
    int64_t i = (ArrayList_Str_length(&(self->local_alloca_names)) - 1LL);
    while (i >= 0LL) {
    if (strcmp(ArrayList_Str_get(&(self->local_alloca_names), i), name) == 0) {
    return (void*)(unsigned long long)(ArrayList_Int_get(&(self->local_alloca_types), i));
}
    i = (i - 1LL);
}
    return (void*)(unsigned long long)(0LL);
}
const char* LLVMCodegen_get_expr_type(LLVMCodegen* self, int64_t expr_idx) {
    if (expr_idx < 0LL) {
    return "";
}
    ExprNode expr = ArrayList_ExprNode_get(self->expr_pool, expr_idx);
    if (strlen(expr.inferred_type) > 0LL) {
    return expr.inferred_type;
}
    if (expr.kind == ExprKind_ek_literal) {
    if (strcmp(expr.lit_vkind, "INT") == 0) {
    return "Int";
}
    if (strcmp(expr.lit_vkind, "STRING") == 0) {
    return "Str";
}
    if (strcmp(expr.lit_vkind, "FLOAT") == 0) {
    return "Float";
}
    if (strcmp(expr.lit_vkind, "BOOL") == 0) {
    return "Bool";
}
    if (strcmp(expr.lit_vkind, "CHAR") == 0) {
    return "Char";
}
}
    if (expr.kind == ExprKind_ek_str_interp) {
    return "Str";
}
    if (expr.kind == ExprKind_ek_range) {
    return "Range";
}
    if (expr.kind == ExprKind_ek_struct_init) {
    bool is_enum = ((strlen(expr.struct_name) > 0LL) && LLVMCodegen_str_contains(self, expr.struct_name, ((char)(46LL))));
    if (is_enum) {
    int64_t dot_pos = LLVMCodegen_str_find(self, expr.struct_name, ((char)(46LL)));
    return __kai_str_sub(expr.struct_name, 0LL, dot_pos);
}
    return expr.struct_name;
}
    if (expr.kind == ExprKind_ek_array) {
    if (ArrayList_Int_length(&(expr.func_args)) > 0LL) {
    return concatAlloc("[]", LLVMCodegen_get_expr_type(self, ArrayList_Int_get(&(expr.func_args), 0LL)));
}
    return "[]Void";
}
    if (expr.kind == ExprKind_ek_tuple) {
    const char* t_str = "(";
    int64_t ti = 0LL;
    while (ti < ArrayList_Int_length(&(expr.func_args))) {
    if (ti > 0LL) {
    t_str = concatAlloc(t_str, ", ");
}
    t_str = concatAlloc(t_str, LLVMCodegen_get_expr_type(self, ArrayList_Int_get(&(expr.func_args), ti)));
    ti = (ti + 1LL);
}
    t_str = concatAlloc(t_str, ")");
    return t_str;
}
    if (expr.kind == ExprKind_ek_identifier) {
    int64_t vi = (ArrayList_Str_length(&(self->local_alloca_names)) - 1LL);
    while (vi >= 0LL) {
    if (strcmp(ArrayList_Str_get(&(self->local_alloca_names), vi), expr.ident_name) == 0) {
    return ArrayList_Str_get(&(self->local_alloca_type_strs), vi);
}
    vi = (vi - 1LL);
}
    if (LLVMCodegen_is_struct_type(self, expr.ident_name) || LLVMCodegen_is_enum_type(self, expr.ident_name)) {
    return expr.ident_name;
}
}
    if (expr.kind == ExprKind_ek_func_call) {
    const char* lookup_name = expr.func_name;
    if (LLVMCodegen_is_struct_type(self, lookup_name)) {
    const char* struct_type_name = lookup_name;
    if (ArrayList_Str_length(&(expr.func_type_args)) > 0LL) {
    int64_t tai = 0LL;
    while (tai < ArrayList_Str_length(&(expr.func_type_args))) {
    const char* clean_arg = LLVMCodegen_clean_type_for_mangling(self, ArrayList_Str_get(&(expr.func_type_args), tai));
    struct_type_name = concatAlloc(concatAlloc(struct_type_name, "_"), clean_arg);
    tai = (tai + 1LL);
}
}
    return struct_type_name;
}
    if ((strcmp(lookup_name, "as") == 0) || (strcmp(lookup_name, "cast") == 0)) {
    if (ArrayList_Str_length(&(expr.func_type_args)) > 0LL) {
    return ArrayList_Str_get(&(expr.func_type_args), 0LL);
}
}
    int64_t i = 0LL;
    while (i < ArrayList_Str_length(&(self->func_type_names))) {
    if (strcmp(ArrayList_Str_get(&(self->func_type_names), i), lookup_name) == 0) {
    return ArrayList_Str_get(&(self->func_type_returns), i);
}
    i = (i + 1LL);
}
}
    if (expr.kind == ExprKind_ek_method_call) {
    const char* receiver_type = LLVMCodegen_get_expr_type(self, expr.meth_expr);
    const char* clean_type = receiver_type;
    if (strlen(clean_type) == 0LL) {
    return "";
}
    while ((strlen(clean_type) > 0LL) && (((clean_type)[0LL] == ((char)(42LL))) || ((clean_type)[0LL] == ((char)(38LL))))) {
    clean_type = __kai_str_sub(clean_type, 1LL, strlen(clean_type));
}
    if ((strlen(clean_type) >= 4LL) && (strcmp(__kai_str_sub(clean_type, 0LL, 4LL), "mut ") == 0)) {
    clean_type = __kai_str_sub(clean_type, 4LL, strlen(clean_type));
}
    const char* mangled_type = LLVMCodegen_clean_type_for_mangling(self, clean_type);
    const char* func_name = concatAlloc(concatAlloc(mangled_type, "_"), expr.meth_name);
    return LLVMCodegen_get_func_return_type(self, func_name);
}
    if (expr.kind == ExprKind_ek_field_access) {
    const char* base_type = LLVMCodegen_get_expr_type(self, expr.field_expr);
    const char* clean_type = base_type;
    while ((strlen(clean_type) > 0LL) && (((clean_type)[0LL] == ((char)(42LL))) || ((clean_type)[0LL] == ((char)(38LL))))) {
    clean_type = __kai_str_sub(clean_type, 1LL, strlen(clean_type));
}
    if ((strlen(clean_type) >= 4LL) && (strcmp(__kai_str_sub(clean_type, 0LL, 4LL), "mut ") == 0)) {
    clean_type = __kai_str_sub(clean_type, 4LL, strlen(clean_type));
}
    if (LLVMCodegen_is_enum_type(self, clean_type)) {
    return clean_type;
}
    bool is_error_union = false;
    int64_t excl_idx = (-1LL);
    if (LLVMCodegen_str_contains(self, clean_type, ((char)(33LL)))) {
    is_error_union = true;
    excl_idx = LLVMCodegen_str_find(self, clean_type, ((char)(33LL)));
} else if ((strlen(clean_type) > 7LL) && (strcmp(__kai_str_sub(clean_type, 0LL, 7LL), "Result_") == 0)) {
    is_error_union = true;
}
    if (is_error_union) {
    if (strcmp(expr.field_name, "tag") == 0) {
    return "Int";
}
    if (strcmp(expr.field_name, "value") == 0) {
    if (excl_idx >= 0LL) {
    return __kai_str_sub(clean_type, 0LL, excl_idx);
}
    int64_t last_under = (-1LL);
    int64_t ui = (strlen(clean_type) - 1LL);
    while (ui >= 0LL) {
    if ((clean_type)[ui] == ((char)(95LL))) {
    last_under = ui;
    break;
}
    ui = (ui - 1LL);
}
    if (last_under > 7LL) {
    return __kai_str_sub(clean_type, 7LL, last_under);
}
}
}
    int64_t struct_decl_idx = LLVMCodegen_find_struct_decl(self, clean_type);
    if (struct_decl_idx >= 0LL) {
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, struct_decl_idx);
    int64_t f_idx = 0LL;
    while (f_idx < ArrayList_StructField_length(&(stmt.struct_fields))) {
    StructField f = ArrayList_StructField_get(&(stmt.struct_fields), f_idx);
    if (strcmp(f.name, expr.field_name) == 0) {
    const char* ftype = f.ftype;
    if (ArrayList_Str_length(&(stmt.struct_type_params)) > 0LL) {
    ArrayList_LLVMStrMapEntry old_map = self->current_type_map;
    self->current_type_map = LLVMCodegen_setup_type_map_from_mangled_name(self, stmt.struct_name, clean_type, &(stmt.struct_type_params));
    const char* resolved_ftype = LLVMCodegen_substitute_generic_type(self, ftype);
    ftype = resolved_ftype;
    self->current_type_map = old_map;
}
    return ftype;
}
    f_idx = (f_idx + 1LL);
}
}
    return "Void";
}
    if (expr.kind == ExprKind_ek_index) {
    const char* base_type = LLVMCodegen_get_expr_type(self, expr.idx_expr);
    if (((strlen(base_type) > 2LL) && ((base_type)[0LL] == ((char)(91LL)))) && ((base_type)[1LL] == ((char)(93LL)))) {
    return __kai_str_sub(base_type, 2LL, strlen(base_type));
}
    if ((strlen(base_type) > 0LL) && ((base_type)[0LL] == ((char)(42LL)))) {
    return __kai_str_sub(base_type, 1LL, strlen(base_type));
}
    return "Void";
}
    if (expr.kind == ExprKind_ek_borrow) {
    const char* opty = LLVMCodegen_get_expr_type(self, expr.borrow_expr);
    return concatAlloc("*", opty);
}
    if (expr.kind == ExprKind_ek_deref) {
    const char* opty = LLVMCodegen_get_expr_type(self, expr.deref_expr);
    if ((strlen(opty) > 0LL) && (((opty)[0LL] == ((char)(42LL))) || ((opty)[0LL] == ((char)(38LL))))) {
    return __kai_str_sub(opty, 1LL, strlen(opty));
}
    return "Void";
}
    return "";
}
void* LLVMCodegen_gen_expr(LLVMCodegen* self, int64_t expr_idx) {
    if (expr_idx < 0LL) {
    return (void*)(unsigned long long)(0LL);
}
    LLVMCodegen_ensure_reachable(self);
    ExprNode expr = ArrayList_ExprNode_get(self->expr_pool, expr_idx);
    if (expr.kind == ExprKind_ek_literal) {
    if (strcmp(expr.lit_vkind, "INT") == 0) {
    int64_t val = 0LL;
    if (expr.lit_value.tag == TokenValue_tv_int_TAG) {
    int64_t v = expr.lit_value.payload.tv_int.v;

    val = v;
} else if (expr.lit_value.tag == TokenValue_tv_str_TAG) {
    int64_t v = expr.lit_value.payload.tv_str.v;

    val = LLVMCodegen_str_to_int(self, StringPool_get(self->pool, v));
} else {
} 
    return LLVMConstInt(self->int64_type, val, false);
}
    if (strcmp(expr.lit_vkind, "FLOAT") == 0) {
    double val = 0.0;
    if (expr.lit_value.tag == TokenValue_tv_float_TAG) {
    double v = expr.lit_value.payload.tv_float.v;

    val = v;
} else if (expr.lit_value.tag == TokenValue_tv_str_TAG) {
    int64_t v = expr.lit_value.payload.tv_str.v;

    val = LLVMCodegen_str_to_float(self, StringPool_get(self->pool, v));
} else {
} 
    return LLVMConstReal(self->double_type, val);
}
    if (strcmp(expr.lit_vkind, "BOOL") == 0) {
    bool bval = false;
    if (expr.lit_value.tag == TokenValue_tv_bool_TAG) {
    bool v = expr.lit_value.payload.tv_bool.v;

    bval = v;
} else {
} 
    if (bval) {
    return LLVMConstInt(self->int1_type, 1LL, false);
}
    return LLVMConstInt(self->int1_type, 0LL, false);
}
    if (strcmp(expr.lit_vkind, "STRING") == 0) {
    const char* sval = "";
    if (expr.lit_value.tag == TokenValue_tv_str_TAG) {
    int64_t v = expr.lit_value.payload.tv_str.v;

    sval = StringPool_get(self->pool, v);
} else {
} 
    const char* gname = concatAlloc(".str", int_to_str(self->str_counter));
    self->str_counter = (self->str_counter + 1LL);
    void* ptr_val = LLVMBuildGlobalStringPtr(self->builder, sval, gname);
    void* null_str = LLVMConstNull(self->str_type);
    void* with_ptr = kai_LLVMBuildInsertValue(self->builder, null_str, ptr_val, 0LL, ".str.ptr");
    void* len_val = LLVMConstInt(self->int64_type, strlen(sval), false);
    return kai_LLVMBuildInsertValue(self->builder, with_ptr, len_val, 1LL, ".str");
}
    if (strcmp(expr.lit_vkind, "CHAR") == 0) {
    int64_t val = 0LL;
    if (expr.lit_value.tag == TokenValue_tv_char_TAG) {
    char v = expr.lit_value.payload.tv_char.v;

    val = (int64_t)(v);
} else if (expr.lit_value.tag == TokenValue_tv_int_TAG) {
    int64_t v = expr.lit_value.payload.tv_int.v;

    val = v;
} else {
} 
    return LLVMConstInt(self->int8_type, val, false);
}
    if (strcmp(expr.lit_vkind, "NONE") == 0) {
    return (void*)(unsigned long long)(0LL);
}
    return (void*)(unsigned long long)(0LL);
}
    if (expr.kind == ExprKind_ek_identifier) {
    void* alloca = (void*)(unsigned long long)(0LL);
    void* elem_ty = (void*)(unsigned long long)(0LL);
    if (expr.resolved_symbol_idx >= 0LL) {
    alloca = LLVMCodegen_find_alloca_by_idx(self, expr.resolved_symbol_idx, expr.ident_name);
    elem_ty = LLVMCodegen_find_alloca_type_by_idx(self, expr.resolved_symbol_idx, expr.ident_name);
}
    if (alloca == (void*)(unsigned long long)(0LL)) {
    alloca = LLVMCodegen_find_alloca(self, expr.ident_name);
    elem_ty = LLVMCodegen_find_alloca_type(self, expr.ident_name);
}
    if (alloca != (void*)(unsigned long long)(0LL)) {
    if (elem_ty == (void*)(unsigned long long)(0LL)) {
    elem_ty = self->int64_type;
}
    bool is_aggregate = false;
    if (elem_ty != self->str_type) {
    int64_t ty_kind = LLVMGetTypeKind(elem_ty);
    if ((ty_kind == LLVMArrayTypeKind) || (ty_kind == LLVMStructTypeKind)) {
    is_aggregate = true;
}
}
    if (is_aggregate) {
    return alloca;
}
    return LLVMBuildLoad2(self->builder, elem_ty, alloca, expr.ident_name);
}
    return (void*)(unsigned long long)(0LL);
}
    if (expr.kind == ExprKind_ek_func_call) {
    const char* name = expr.func_name;
    if ((((strcmp(name, "Char") == 0) || (strcmp(name, "Int") == 0)) || (strcmp(name, "Float") == 0)) || (strcmp(name, "Bool") == 0)) {
    if (ArrayList_Int_length(&(expr.func_args)) > 0LL) {
    void* val = LLVMCodegen_gen_expr(self, ArrayList_Int_get(&(expr.func_args), 0LL));
    if (val == (void*)(unsigned long long)(0LL)) {
    return (void*)(unsigned long long)(0LL);
}
    void* dest_type = LLVMCodegen_map_type(self, name);
    return LLVMCodegen_gen_cast(self, val, dest_type);
}
    return (void*)(unsigned long long)(0LL);
}
    if ((strcmp(name, "as") == 0) || (strcmp(name, "cast") == 0)) {
    void* val = LLVMCodegen_gen_expr(self, ArrayList_Int_get(&(expr.func_args), 0LL));
    const char* dest_type_str = ArrayList_Str_get(&(expr.func_type_args), 0LL);
    void* dest_type = LLVMCodegen_map_type(self, dest_type_str);
    return LLVMCodegen_gen_cast(self, val, dest_type);
}
    if (strcmp(name, "size_of") == 0) {
    const char* dest_type_str = ArrayList_Str_get(&(expr.func_type_args), 0LL);
    void* dest_type = LLVMCodegen_map_type(self, dest_type_str);
    return LLVMSizeOf(dest_type);
}
    const char* target_fn_name = expr.func_name;
    if (LLVMCodegen_is_struct_type(self, expr.func_name)) {
    if (ArrayList_Str_length(&(expr.func_type_args)) > 0LL) {
    int64_t tai = 0LL;
    while (tai < ArrayList_Str_length(&(expr.func_type_args))) {
    const char* clean = LLVMCodegen_clean_type_for_mangling(self, ArrayList_Str_get(&(expr.func_type_args), tai));
    target_fn_name = concatAlloc(concatAlloc(target_fn_name, "_"), clean);
    tai = (tai + 1LL);
}
    target_fn_name = concatAlloc(target_fn_name, "_init");
} else {
    target_fn_name = concatAlloc(expr.func_name, "_init");
}
}
    void* fn_val = LLVMCodegen_lookup_or_create_func(self, target_fn_name);
    if (fn_val == (void*)(unsigned long long)(0LL)) {
    return (void*)(unsigned long long)(0LL);
}
    void* fn_ty = LLVMCodegen_get_cached_func_type(self, target_fn_name);
    if (fn_ty == (void*)(unsigned long long)(0LL)) {
    return (void*)(unsigned long long)(0LL);
}
    void* fn_ret_ty = LLVMGetReturnType(fn_ty);
    const char* param_types_str = LLVMCodegen_get_func_param_types(self, target_fn_name);
    int64_t arg_count = ArrayList_Int_length(&(expr.func_args));
    bool callee_is_extern = LLVMCodegen_is_extern_func(self, target_fn_name);
    ArrayList_Int args_val_array = ArrayList_Int_init(self->allocator);
    int64_t ai = 0LL;
    while (ai < arg_count) {
    int64_t expr_arg = ArrayList_Int_get(&(expr.func_args), ai);
    void* raw_arg = LLVMCodegen_gen_expr(self, expr_arg);
    const char* param_ty_str = LLVMCodegen_get_param_type_at_index(self, param_types_str, ai);
    void* prepared = LLVMCodegen_prepare_arg(self, raw_arg, param_ty_str, callee_is_extern);
    if (prepared == (void*)(unsigned long long)(0LL)) {
    return (void*)(unsigned long long)(0LL);
}
    ArrayList_Int_push(&(args_val_array), (int64_t)(prepared));
    ai = (ai + 1LL);
}
    return LLVMBuildCall2(self->builder, fn_ty, fn_val, (void*)(args_val_array.data), arg_count, "");
}
    if (expr.kind == ExprKind_ek_unary_op) {
    void* operand = LLVMCodegen_gen_expr(self, expr.unop_operand);
    if (operand == (void*)(unsigned long long)(0LL)) {
    return (void*)(unsigned long long)(0LL);
}
    if (strcmp(expr.unop_op, "!") == 0) {
    void* op_type = LLVMTypeOf(operand);
    if (op_type == self->int1_type) {
    void* zero = LLVMConstInt(self->int1_type, 0LL, false);
    void* is_zero = LLVMBuildICmp(self->builder, LLVMIntEQ, operand, zero, "");
    return LLVMBuildZExt(self->builder, is_zero, self->int64_type, "");
} else {
    void* zero = LLVMConstInt(self->int64_type, 0LL, false);
    void* is_zero = LLVMBuildICmp(self->builder, LLVMIntEQ, operand, zero, "");
    return LLVMBuildZExt(self->builder, is_zero, self->int64_type, "");
}
}
    if (strcmp(expr.unop_op, "-") == 0) {
    void* op_ty = LLVMTypeOf(operand);
    if (op_ty == self->double_type) {
    return LLVMBuildFNeg(self->builder, operand, "");
}
    return LLVMBuildNeg(self->builder, operand, "");
}
    if (strcmp(expr.unop_op, "~") == 0) {
    return LLVMBuildNot(self->builder, operand, "");
}
    return (void*)(unsigned long long)(0LL);
}
    if (expr.kind == ExprKind_ek_binary_op) {
    void* lhs = LLVMCodegen_gen_expr(self, expr.binop_left);
    void* rhs = LLVMCodegen_gen_expr(self, expr.binop_right);
    if ((lhs == (void*)(unsigned long long)(0LL)) || (rhs == (void*)(unsigned long long)(0LL))) {
    return (void*)(unsigned long long)(0LL);
}
    const char* op = expr.binop_op;
    void* lhs_ty = LLVMTypeOf(lhs);
    const char* left_type = LLVMCodegen_get_expr_type(self, expr.binop_left);
    const char* right_type = LLVMCodegen_get_expr_type(self, expr.binop_right);
    const char* expr_type_str = LLVMCodegen_get_expr_type(self, expr_idx);
    bool is_left_str = (((lhs_ty == self->str_type) || (strcmp(left_type, "Str") == 0)) || (strcmp(left_type, "*Char") == 0));
    bool is_right_str = (((LLVMTypeOf(rhs) == self->str_type) || (strcmp(right_type, "Str") == 0)) || (strcmp(right_type, "*Char") == 0));
    int64_t rhs_kind_for_str = LLVMGetTypeKind(LLVMTypeOf(rhs));
    int64_t lhs_kind_for_str = LLVMGetTypeKind(lhs_ty);
    bool both_are_str_compat = (((rhs_kind_for_str == LLVMPointerTypeKind) || (LLVMTypeOf(rhs) == self->str_type)) && ((lhs_kind_for_str == LLVMPointerTypeKind) || (lhs_ty == self->str_type)));
    if (((is_left_str || is_right_str) && (strcmp(op, "+") == 0)) && both_are_str_compat) {
    void* lhs_str = LLVMCodegen_gen_cast(self, lhs, self->str_type);
    void* rhs_str = LLVMCodegen_gen_cast(self, rhs, self->str_type);
    void* concat_fn = LLVMCodegen_lookup_or_create_func(self, "concatAlloc");
    if (concat_fn != (void*)(unsigned long long)(0LL)) {
    void* concat_ty = LLVMCodegen_get_cached_func_type(self, "concatAlloc");
    if (concat_ty != (void*)(unsigned long long)(0LL)) {
    ArrayList_Int args_array = ArrayList_Int_init(self->allocator);
    ArrayList_Int_push(&(args_array), (int64_t)(lhs_str));
    ArrayList_Int_push(&(args_array), (int64_t)(rhs_str));
    void* raw_result = LLVMBuildCall2(self->builder, concat_ty, concat_fn, (void*)(args_array.data), 2LL, "");
    if (strcmp(expr_type_str, "*Char") == 0) {
    return LLVMCodegen_unwrap_str_for_c(self, raw_result);
}
    return raw_result;
}
}
    return (void*)(unsigned long long)(0LL);
}
    if (((((strcmp(left_type, "Str") == 0) || (strcmp(right_type, "Str") == 0)) || (lhs_ty == self->str_type)) || (LLVMTypeOf(rhs) == self->str_type)) && ((strcmp(op, "==") == 0) || (strcmp(op, "!=") == 0))) {
    void* lhs_ptr = LLVMCodegen_unwrap_str_for_c(self, lhs);
    void* rhs_ptr = LLVMCodegen_unwrap_str_for_c(self, rhs);
    void* strcmp_fn = LLVMCodegen_lookup_or_create_func(self, "strcmp");
    if (strcmp_fn != (void*)(unsigned long long)(0LL)) {
    void* strcmp_ty = LLVMCodegen_get_cached_func_type(self, "strcmp");
    if (strcmp_ty != (void*)(unsigned long long)(0LL)) {
    void* cmp_result = kai_build_call_2(self->builder, strcmp_ty, strcmp_fn, lhs_ptr, rhs_ptr, "");
    void* zero = LLVMConstInt(self->int64_type, 0LL, false);
    if (strcmp(op, "==") == 0) {
    void* eq = LLVMBuildICmp(self->builder, LLVMIntEQ, cmp_result, zero, "");
    return LLVMBuildZExt(self->builder, eq, self->int64_type, "");
} else {
    void* ne = LLVMBuildICmp(self->builder, LLVMIntNE, cmp_result, zero, "");
    return LLVMBuildZExt(self->builder, ne, self->int64_type, "");
}
}
}
    return (void*)(unsigned long long)(0LL);
}
    bool is_float = (lhs_ty == self->double_type);
    if (is_float) {
    if (strcmp(op, "+") == 0) {
    return LLVMBuildFAdd(self->builder, lhs, rhs, "");
}
    if (strcmp(op, "-") == 0) {
    return LLVMBuildFSub(self->builder, lhs, rhs, "");
}
    if (strcmp(op, "*") == 0) {
    return LLVMBuildFMul(self->builder, lhs, rhs, "");
}
    if (strcmp(op, "/") == 0) {
    return LLVMBuildFDiv(self->builder, lhs, rhs, "");
}
    if (strcmp(op, "==") == 0) {
    void* cmp = LLVMBuildFCmp(self->builder, LLVMRealOEQ, lhs, rhs, "");
    return LLVMBuildZExt(self->builder, cmp, self->int64_type, "");
}
    if (strcmp(op, "!=") == 0) {
    void* cmp = LLVMBuildFCmp(self->builder, LLVMRealONE, lhs, rhs, "");
    return LLVMBuildZExt(self->builder, cmp, self->int64_type, "");
}
    if (strcmp(op, "<") == 0) {
    void* cmp = LLVMBuildFCmp(self->builder, LLVMRealOLT, lhs, rhs, "");
    return LLVMBuildZExt(self->builder, cmp, self->int64_type, "");
}
    if (strcmp(op, ">") == 0) {
    void* cmp = LLVMBuildFCmp(self->builder, LLVMRealOGT, lhs, rhs, "");
    return LLVMBuildZExt(self->builder, cmp, self->int64_type, "");
}
    if (strcmp(op, "<=") == 0) {
    void* cmp = LLVMBuildFCmp(self->builder, LLVMRealOLE, lhs, rhs, "");
    return LLVMBuildZExt(self->builder, cmp, self->int64_type, "");
}
    if (strcmp(op, ">=") == 0) {
    void* cmp = LLVMBuildFCmp(self->builder, LLVMRealOGE, lhs, rhs, "");
    return LLVMBuildZExt(self->builder, cmp, self->int64_type, "");
}
    return (void*)(unsigned long long)(0LL);
}
    if (strcmp(op, "+") == 0) {
    return LLVMBuildAdd(self->builder, lhs, rhs, "");
}
    if (strcmp(op, "-") == 0) {
    return LLVMBuildSub(self->builder, lhs, rhs, "");
}
    if (strcmp(op, "*") == 0) {
    return LLVMBuildMul(self->builder, lhs, rhs, "");
}
    if (strcmp(op, "/") == 0) {
    return LLVMBuildSDiv(self->builder, lhs, rhs, "");
}
    if (strcmp(op, "%") == 0) {
    return LLVMBuildSRem(self->builder, lhs, rhs, "");
}
    if (strcmp(op, "&") == 0) {
    return LLVMBuildAnd(self->builder, lhs, rhs, "");
}
    if (strcmp(op, "|") == 0) {
    return LLVMBuildOr(self->builder, lhs, rhs, "");
}
    if (strcmp(op, "^") == 0) {
    return LLVMBuildXor(self->builder, lhs, rhs, "");
}
    if (strcmp(op, "<<") == 0) {
    return LLVMBuildShl(self->builder, lhs, rhs, "");
}
    if (strcmp(op, ">>") == 0) {
    return LLVMBuildAShr(self->builder, lhs, rhs, "");
}
    void* cmp_lhs = lhs;
    void* cmp_rhs = rhs;
    void* rhs_ty = LLVMTypeOf(rhs);
    int64_t lhs_kind = LLVMGetTypeKind(lhs_ty);
    int64_t rhs_kind = LLVMGetTypeKind(rhs_ty);
    if ((lhs_kind == LLVMIntegerTypeKind) && (rhs_kind == LLVMIntegerTypeKind)) {
    int64_t lhs_w = kai_LLVMGetIntTypeWidth(lhs_ty);
    int64_t rhs_w = kai_LLVMGetIntTypeWidth(rhs_ty);
    if (lhs_w < rhs_w) {
    cmp_lhs = LLVMBuildSExt(self->builder, lhs, rhs_ty, "");
} else if (rhs_w < lhs_w) {
    cmp_rhs = LLVMBuildSExt(self->builder, rhs, lhs_ty, "");
}
}
    if (strcmp(op, "==") == 0) {
    int64_t cl_kind = LLVMGetTypeKind(LLVMTypeOf(cmp_lhs));
    int64_t cr_kind = LLVMGetTypeKind(LLVMTypeOf(cmp_rhs));
    if ((cl_kind == LLVMPointerTypeKind) && (cr_kind == LLVMIntegerTypeKind)) {
    cmp_rhs = LLVMConstNull(LLVMTypeOf(cmp_lhs));
} else if ((cl_kind == LLVMIntegerTypeKind) && (cr_kind == LLVMPointerTypeKind)) {
    cmp_lhs = LLVMBuildPtrToInt(self->builder, cmp_lhs, self->int64_type, "");
    cmp_rhs = LLVMConstInt(self->int64_type, 0LL, false);
}
    void* cmp = LLVMBuildICmp(self->builder, LLVMIntEQ, cmp_lhs, cmp_rhs, "");
    return LLVMBuildZExt(self->builder, cmp, self->int64_type, "");
}
    if (strcmp(op, "!=") == 0) {
    int64_t cl_kind2 = LLVMGetTypeKind(LLVMTypeOf(cmp_lhs));
    int64_t cr_kind2 = LLVMGetTypeKind(LLVMTypeOf(cmp_rhs));
    if ((cl_kind2 == LLVMPointerTypeKind) && (cr_kind2 == LLVMIntegerTypeKind)) {
    cmp_rhs = LLVMConstNull(LLVMTypeOf(cmp_lhs));
} else if ((cl_kind2 == LLVMIntegerTypeKind) && (cr_kind2 == LLVMPointerTypeKind)) {
    cmp_lhs = LLVMBuildPtrToInt(self->builder, cmp_lhs, self->int64_type, "");
    cmp_rhs = LLVMConstInt(self->int64_type, 0LL, false);
}
    void* cmp = LLVMBuildICmp(self->builder, LLVMIntNE, cmp_lhs, cmp_rhs, "");
    return LLVMBuildZExt(self->builder, cmp, self->int64_type, "");
}
    if (strcmp(op, "<") == 0) {
    void* cmp = LLVMBuildICmp(self->builder, LLVMIntSLT, cmp_lhs, cmp_rhs, "");
    return LLVMBuildZExt(self->builder, cmp, self->int64_type, "");
}
    if (strcmp(op, ">") == 0) {
    void* cmp = LLVMBuildICmp(self->builder, LLVMIntSGT, cmp_lhs, cmp_rhs, "");
    return LLVMBuildZExt(self->builder, cmp, self->int64_type, "");
}
    if (strcmp(op, "<=") == 0) {
    void* cmp = LLVMBuildICmp(self->builder, LLVMIntSLE, cmp_lhs, cmp_rhs, "");
    return LLVMBuildZExt(self->builder, cmp, self->int64_type, "");
}
    if (strcmp(op, ">=") == 0) {
    void* cmp = LLVMBuildICmp(self->builder, LLVMIntSGE, cmp_lhs, cmp_rhs, "");
    return LLVMBuildZExt(self->builder, cmp, self->int64_type, "");
}
    if (strcmp(op, "&&") == 0) {
    void* zero = LLVMConstInt(self->int64_type, 0LL, false);
    void* lhs_i64 = lhs;
    void* rhs_i64 = rhs;
    if (LLVMTypeOf(lhs) != self->int64_type) {
    lhs_i64 = LLVMBuildSExt(self->builder, lhs, self->int64_type, "");
}
    if (LLVMTypeOf(rhs) != self->int64_type) {
    rhs_i64 = LLVMBuildSExt(self->builder, rhs, self->int64_type, "");
}
    void* lhs_ne = LLVMBuildICmp(self->builder, LLVMIntNE, lhs_i64, zero, "");
    void* rhs_ne = LLVMBuildICmp(self->builder, LLVMIntNE, rhs_i64, zero, "");
    void* and = LLVMBuildAnd(self->builder, lhs_ne, rhs_ne, "");
    return LLVMBuildZExt(self->builder, and, self->int64_type, "");
}
    if (strcmp(op, "||") == 0) {
    void* zero = LLVMConstInt(self->int64_type, 0LL, false);
    void* lhs_i64 = lhs;
    void* rhs_i64 = rhs;
    if (LLVMTypeOf(lhs) != self->int64_type) {
    lhs_i64 = LLVMBuildSExt(self->builder, lhs, self->int64_type, "");
}
    if (LLVMTypeOf(rhs) != self->int64_type) {
    rhs_i64 = LLVMBuildSExt(self->builder, rhs, self->int64_type, "");
}
    void* lhs_ne = LLVMBuildICmp(self->builder, LLVMIntNE, lhs_i64, zero, "");
    void* rhs_ne = LLVMBuildICmp(self->builder, LLVMIntNE, rhs_i64, zero, "");
    void* or = LLVMBuildOr(self->builder, lhs_ne, rhs_ne, "");
    return LLVMBuildZExt(self->builder, or, self->int64_type, "");
}
    return (void*)(unsigned long long)(0LL);
}
    if (expr.kind == ExprKind_ek_check) {
    return LLVMCodegen_gen_expr(self, expr.check_expr);
}
    if (expr.kind == ExprKind_ek_borrow) {
    return LLVMCodegen_gen_expr(self, expr.borrow_expr);
}
    if (expr.kind == ExprKind_ek_deref) {
    return LLVMCodegen_gen_expr(self, expr.deref_expr);
}
    if (expr.kind == ExprKind_ek_try) {
    return LLVMCodegen_gen_expr(self, expr.try_expr);
}
    if (expr.kind == ExprKind_ek_catch) {
    void* inner = LLVMCodegen_gen_expr(self, expr.catch_expr);
    if (expr.catch_fallback >= 0LL) {
    void* fallback = LLVMCodegen_gen_expr(self, expr.catch_fallback);
    if (inner == (void*)(unsigned long long)(0LL)) {
    return fallback;
}
    if (fallback == (void*)(unsigned long long)(0LL)) {
    return inner;
}
    void* is_ok = LLVMCodegen_to_bool(self, inner);
    if (is_ok == (void*)(unsigned long long)(0LL)) {
    return fallback;
}
    void* cond_val = is_ok;
    if (LLVMTypeOf(cond_val) != self->int1_type) {
    void* zero = LLVMConstNull(LLVMTypeOf(cond_val));
    cond_val = LLVMBuildICmp(self->builder, LLVMIntNE, cond_val, zero, "");
}
    void* cast_fallback = fallback;
    if (LLVMTypeOf(inner) != LLVMTypeOf(fallback)) {
    cast_fallback = LLVMCodegen_gen_cast(self, fallback, LLVMTypeOf(inner));
}
    return LLVMBuildSelect(self->builder, cond_val, inner, cast_fallback, "");
}
    return inner;
}
    if (expr.kind == ExprKind_ek_array) {
    const char* inner_type_str = "Int";
    if (((strlen(expr.inferred_type) > 2LL) && ((expr.inferred_type)[0LL] == ((char)(91LL)))) && ((expr.inferred_type)[1LL] == ((char)(93LL)))) {
    inner_type_str = __kai_str_sub(expr.inferred_type, 2LL, strlen(expr.inferred_type));
}
    void* inner_llvm_type = LLVMCodegen_map_type(self, inner_type_str);
    if ((inner_llvm_type == self->void_type) || (inner_llvm_type == (void*)(unsigned long long)(0LL))) {
    inner_llvm_type = self->int64_type;
}
    int64_t count = ArrayList_Int_length(&(expr.arr_elements));
    if (count == 0LL) {
    return LLVMBuildAlloca(self->builder, inner_llvm_type, ".arr_empty");
}
    void* arr_type = LLVMArrayType(inner_llvm_type, count);
    void* arr_ptr = LLVMBuildAlloca(self->builder, arr_type, ".arr");
    void* el_ptr_ty = LLVMPointerType(inner_llvm_type, 0LL);
    void* casted = LLVMBuildBitCast(self->builder, arr_ptr, el_ptr_ty, "");
    int64_t ai = 0LL;
    while (ai < count) {
    void* elem_val = LLVMCodegen_gen_expr(self, ArrayList_Int_get(&(expr.arr_elements), ai));
    if (elem_val != (void*)(unsigned long long)(0LL)) {
    ArrayList_Int indices = ArrayList_Int_init(self->allocator);
    void* idx_val = LLVMConstInt(self->int64_type, ai, false);
    ArrayList_Int_push(&(indices), (int64_t)(idx_val));
    void* gep = LLVMBuildGEP2(self->builder, inner_llvm_type, casted, (void*)(indices.data), 1LL, "");
    LLVMBuildStore(self->builder, elem_val, gep);
}
    ai = (ai + 1LL);
}
    return arr_ptr;
}
    if (expr.kind == ExprKind_ek_index) {
    void* base_val = LLVMCodegen_gen_expr(self, expr.idx_expr);
    if (base_val == (void*)(unsigned long long)(0LL)) {
    return (void*)(unsigned long long)(0LL);
}
    void* idx_val = LLVMCodegen_gen_expr(self, expr.idx_index);
    if (idx_val == (void*)(unsigned long long)(0LL)) {
    return (void*)(unsigned long long)(0LL);
}
    const char* inner_type_str = "Int";
    ExprNode base_expr2 = ArrayList_ExprNode_get(self->expr_pool, expr.idx_expr);
    const char* base_type_for_index = LLVMCodegen_get_expr_type(self, expr.idx_expr);
    if (strlen(base_type_for_index) == 0LL) {
    base_type_for_index = base_expr2.inferred_type;
}
    if (strcmp(base_type_for_index, "Str") == 0) {
    inner_type_str = "Char";
} else if (((strlen(base_type_for_index) > 2LL) && ((base_type_for_index)[0LL] == ((char)(91LL)))) && ((base_type_for_index)[1LL] == ((char)(93LL)))) {
    inner_type_str = __kai_str_sub(base_type_for_index, 2LL, strlen(base_type_for_index));
} else if ((strlen(base_type_for_index) > 0LL) && ((base_type_for_index)[0LL] == ((char)(42LL)))) {
    inner_type_str = __kai_str_sub(base_type_for_index, 1LL, strlen(base_type_for_index));
} else if (((strlen(base_expr2.inferred_type) > 2LL) && ((base_expr2.inferred_type)[0LL] == ((char)(91LL)))) && ((base_expr2.inferred_type)[1LL] == ((char)(93LL)))) {
    inner_type_str = __kai_str_sub(base_expr2.inferred_type, 2LL, strlen(base_expr2.inferred_type));
} else if ((strlen(base_expr2.inferred_type) > 0LL) && ((base_expr2.inferred_type)[0LL] == ((char)(42LL)))) {
    inner_type_str = __kai_str_sub(base_expr2.inferred_type, 1LL, strlen(base_expr2.inferred_type));
}
    void* inner_llvm_type = LLVMCodegen_map_type(self, inner_type_str);
    if ((inner_llvm_type == self->void_type) || (inner_llvm_type == (void*)(unsigned long long)(0LL))) {
    inner_llvm_type = self->int64_type;
}
    void* base_ptr2 = base_val;
    void* base_llvm_ty3 = LLVMTypeOf(base_val);
    if (base_llvm_ty3 == self->str_type) {
    base_ptr2 = LLVMCodegen_unwrap_str_for_c(self, base_val);
    inner_llvm_type = self->int8_type;
} else if (LLVMGetTypeKind(base_llvm_ty3) == LLVMStructTypeKind) {
    return (void*)(unsigned long long)(0LL);
}
    void* gep_idx = idx_val;
    void* idx_ty = LLVMTypeOf(idx_val);
    if (idx_ty != self->int64_type) {
    gep_idx = LLVMBuildSExt(self->builder, idx_val, self->int64_type, "");
}
    void* el_ptr_ty = LLVMPointerType(inner_llvm_type, 0LL);
    void* casted = LLVMBuildBitCast(self->builder, base_ptr2, el_ptr_ty, "");
    ArrayList_Int indices = ArrayList_Int_init(self->allocator);
    ArrayList_Int_push(&(indices), (int64_t)(gep_idx));
    void* gep = LLVMBuildGEP2(self->builder, inner_llvm_type, casted, (void*)(indices.data), 1LL, "");
    void* loaded = LLVMBuildLoad2(self->builder, inner_llvm_type, gep, "");
    if (inner_llvm_type == self->int8_type) {
    return LLVMBuildSExt(self->builder, loaded, self->int64_type, "");
}
    return loaded;
}
    if (expr.kind == ExprKind_ek_range) {
    void* range_ty = LLVMCodegen_map_type(self, "Range");
    if ((range_ty == self->void_type) || (range_ty == (void*)(unsigned long long)(0LL))) {
    return (void*)(unsigned long long)(0LL);
}
    void* start_val = LLVMCodegen_gen_expr(self, expr.range_start);
    void* end_val = LLVMCodegen_gen_expr(self, expr.range_end);
    if ((start_val == (void*)(unsigned long long)(0LL)) || (end_val == (void*)(unsigned long long)(0LL))) {
    return (void*)(unsigned long long)(0LL);
}
    int64_t incl_int = 0LL;
    if (expr.range_inclusive) {
    incl_int = 1LL;
}
    void* incl_val = LLVMConstInt(self->int1_type, incl_int, false);
    void* alloca_val = LLVMBuildAlloca(self->builder, range_ty, ".range");
    void* start_gep = LLVMBuildStructGEP2(self->builder, range_ty, alloca_val, 0LL, ".start");
    LLVMBuildStore(self->builder, start_val, start_gep);
    void* end_gep = LLVMBuildStructGEP2(self->builder, range_ty, alloca_val, 1LL, ".end");
    LLVMBuildStore(self->builder, end_val, end_gep);
    void* incl_gep = LLVMBuildStructGEP2(self->builder, range_ty, alloca_val, 2LL, ".incl");
    LLVMBuildStore(self->builder, incl_val, incl_gep);
    return alloca_val;
}
    if (expr.kind == ExprKind_ek_slice) {
    void* base_val = LLVMCodegen_gen_expr(self, expr.slice_expr);
    if (base_val == (void*)(unsigned long long)(0LL)) {
    return (void*)(unsigned long long)(0LL);
}
    void* base_llvm_ty = LLVMTypeOf(base_val);
    if (base_llvm_ty == self->str_type) {
    void* str_alloca = LLVMBuildAlloca(self->builder, self->str_type, ".parent.str");
    LLVMBuildStore(self->builder, base_val, str_alloca);
    void* ptr_gep = LLVMBuildStructGEP2(self->builder, self->str_type, str_alloca, 0LL, ".parent.ptr.gep");
    void* parent_ptr = LLVMBuildLoad2(self->builder, self->ptr_type, ptr_gep, ".parent.ptr");
    void* len_gep = LLVMBuildStructGEP2(self->builder, self->str_type, str_alloca, 1LL, ".parent.len.gep");
    void* parent_len = LLVMBuildLoad2(self->builder, self->int64_type, len_gep, ".parent.len");
    void* lower_val = LLVMConstInt(self->int64_type, 0LL, false);
    if (expr.slice_lower >= 0LL) {
    lower_val = LLVMCodegen_gen_expr(self, expr.slice_lower);
    if (lower_val == (void*)(unsigned long long)(0LL)) {
    return (void*)(unsigned long long)(0LL);
}
}
    void* upper_val = parent_len;
    if (expr.slice_upper >= 0LL) {
    upper_val = LLVMCodegen_gen_expr(self, expr.slice_upper);
    if (upper_val == (void*)(unsigned long long)(0LL)) {
    return (void*)(unsigned long long)(0LL);
}
    void* cmp = LLVMBuildICmp(self->builder, LLVMIntSGT, upper_val, parent_len, "");
    upper_val = LLVMBuildSelect(self->builder, cmp, parent_len, upper_val, ".upper.clamped");
}
    void* lower_gt_upper = LLVMBuildICmp(self->builder, LLVMIntSGT, lower_val, upper_val, "");
    upper_val = LLVMBuildSelect(self->builder, lower_gt_upper, lower_val, upper_val, ".upper.fixed");
    ArrayList_Int gep_indices = ArrayList_Int_init(self->allocator);
    ArrayList_Int_push(&(gep_indices), (int64_t)(lower_val));
    void* new_ptr = LLVMBuildGEP2(self->builder, self->int8_type, parent_ptr, (void*)(gep_indices.data), 1LL, ".slice.ptr");
    void* new_len = LLVMBuildSub(self->builder, upper_val, lower_val, ".slice.len");
    void* result_alloca = LLVMBuildAlloca(self->builder, self->str_type, ".slice.str");
    void* res_ptr_gep = LLVMBuildStructGEP2(self->builder, self->str_type, result_alloca, 0LL, ".slice.ptr.gep");
    LLVMBuildStore(self->builder, new_ptr, res_ptr_gep);
    void* res_len_gep = LLVMBuildStructGEP2(self->builder, self->str_type, result_alloca, 1LL, ".slice.len.gep");
    LLVMBuildStore(self->builder, new_len, res_len_gep);
    return LLVMBuildLoad2(self->builder, self->str_type, result_alloca, ".slice.str");
}
    void* lower_val = LLVMConstInt(self->int64_type, 0LL, false);
    if (expr.slice_lower >= 0LL) {
    lower_val = LLVMCodegen_gen_expr(self, expr.slice_lower);
    if (lower_val == (void*)(unsigned long long)(0LL)) {
    return (void*)(unsigned long long)(0LL);
}
}
    ArrayList_Int indices = ArrayList_Int_init(self->allocator);
    ArrayList_Int_push(&(indices), (int64_t)(lower_val));
    return LLVMBuildGEP2(self->builder, self->int8_type, base_val, (void*)(indices.data), 1LL, ".slice");
}
    if (expr.kind == ExprKind_ek_tuple) {
    if (strlen(expr.inferred_type) > 0LL) {
    void* tuple_ty = LLVMCodegen_map_tuple_type(self, expr.inferred_type);
    if ((tuple_ty == self->void_type) || (tuple_ty == (void*)(unsigned long long)(0LL))) {
    return (void*)(unsigned long long)(0LL);
}
    void* alloca_val = LLVMBuildAlloca(self->builder, tuple_ty, ".tuple");
    int64_t ei = 0LL;
    while (ei < ArrayList_Int_length(&(expr.tup_elements))) {
    void* elem_val = LLVMCodegen_gen_expr(self, ArrayList_Int_get(&(expr.tup_elements), ei));
    if (elem_val != (void*)(unsigned long long)(0LL)) {
    void* gep = LLVMBuildStructGEP2(self->builder, tuple_ty, alloca_val, ei, ".elem");
    LLVMBuildStore(self->builder, elem_val, gep);
}
    ei = (ei + 1LL);
}
    return alloca_val;
}
    return (void*)(unsigned long long)(0LL);
}
    if (expr.kind == ExprKind_ek_struct_init) {
    const char* struct_name = expr.struct_name;
    bool is_enum_variant = false;
    int64_t dot_pos = (-1LL);
    int64_t ei = 0LL;
    while (ei < strlen(struct_name)) {
    if ((struct_name)[ei] == ((char)(46LL))) {
    dot_pos = ei;
}
    ei = (ei + 1LL);
}
    if (dot_pos >= 0LL) {
    is_enum_variant = true;
}
    if (is_enum_variant) {
    const char* enum_part = __kai_str_sub(struct_name, 0LL, dot_pos);
    const char* variant_name = __kai_str_sub(struct_name, (dot_pos + 1LL), strlen(struct_name));
    int64_t tag_idx = 0LL;
    bool found_tag = false;
    int64_t enum_stmt_idx = 0LL;
    while (enum_stmt_idx < ArrayList_StmtNode_length(self->stmt_pool)) {
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, enum_stmt_idx);
    if ((stmt.kind == StmtKind_sk_enum_decl) && (strcmp(stmt.enum_name, enum_part) == 0)) {
    int64_t vi = 0LL;
    while (vi < ArrayList_Variant_length(&(stmt.enum_variants))) {
    if (strcmp(ArrayList_Variant_get(&(stmt.enum_variants), vi).vname, variant_name) == 0) {
    tag_idx = vi;
    found_tag = true;
}
    vi = (vi + 1LL);
}
}
    enum_stmt_idx = (enum_stmt_idx + 1LL);
}
    bool has_payload = false;
    const char* stripped_enum_part = LLVMCodegen_strip_module_prefix(self, enum_part);
    int64_t ei_chk = 0LL;
    while (ei_chk < ArrayList_Str_length(&(self->enum_cache_names))) {
    if (strcmp(ArrayList_Str_get(&(self->enum_cache_names), ei_chk), stripped_enum_part) == 0) {
    has_payload = ArrayList_Bool_get(&(self->enum_has_payload), ei_chk);
}
    ei_chk = (ei_chk + 1LL);
}
    if (!has_payload) {
    return LLVMConstInt(self->int64_type, tag_idx, false);
}
    void* enum_ty = LLVMCodegen_map_type(self, enum_part);
    if ((enum_ty == self->void_type) || (enum_ty == (void*)(unsigned long long)(0LL))) {
    return (void*)(unsigned long long)(0LL);
}
    void* alloca_val = LLVMBuildAlloca(self->builder, enum_ty, ".enum_var");
    void* tag_gep = LLVMBuildStructGEP2(self->builder, enum_ty, alloca_val, 0LL, ".tag");
    LLVMBuildStore(self->builder, LLVMConstInt(self->int8_type, tag_idx, false), tag_gep);
    if (ArrayList_FieldInit_length(&(expr.struct_fields)) > 0LL) {
    ArrayList_Int variant_field_types = ArrayList_Int_init(self->allocator);
    ArrayList_Int field_vals = ArrayList_Int_init(self->allocator);
    int64_t fi = 0LL;
    while (fi < ArrayList_FieldInit_length(&(expr.struct_fields))) {
    FieldInit f = ArrayList_FieldInit_get(&(expr.struct_fields), fi);
    void* field_val = LLVMCodegen_gen_expr(self, f.value);
    if (field_val != (void*)(unsigned long long)(0LL)) {
    ArrayList_Int_push(&(variant_field_types), (int64_t)(LLVMTypeOf(field_val)));
    ArrayList_Int_push(&(field_vals), (int64_t)(field_val));
}
    fi = (fi + 1LL);
}
    void* variant_struct_ty = LLVMStructTypeInContext(self->ctx, (void*)(variant_field_types.data), ArrayList_Int_length(&(variant_field_types)), false);
    void* payload_gep = LLVMBuildStructGEP2(self->builder, enum_ty, alloca_val, 1LL, ".payload");
    void* casted_payload_ptr = LLVMBuildBitCast(self->builder, payload_gep, LLVMPointerType(variant_struct_ty, 0LL), "");
    int64_t sfi = 0LL;
    while (sfi < ArrayList_Int_length(&(field_vals))) {
    void* f_val = (void*)(unsigned long long)(ArrayList_Int_get(&(field_vals), sfi));
    void* dest_gep = LLVMBuildStructGEP2(self->builder, variant_struct_ty, casted_payload_ptr, sfi, "");
    LLVMBuildStore(self->builder, f_val, dest_gep);
    sfi = (sfi + 1LL);
}
}
    return alloca_val;
}
    void* struct_ty = LLVMCodegen_map_type(self, struct_name);
    if ((struct_ty == self->void_type) || (struct_ty == (void*)(unsigned long long)(0LL))) {
    return (void*)(unsigned long long)(0LL);
}
    void* alloca_val = LLVMBuildAlloca(self->builder, struct_ty, ".struct");
    int64_t fi = 0LL;
    while (fi < ArrayList_FieldInit_length(&(expr.struct_fields))) {
    FieldInit f = ArrayList_FieldInit_get(&(expr.struct_fields), fi);
    void* field_val = LLVMCodegen_gen_expr(self, f.value);
    if (field_val != (void*)(unsigned long long)(0LL)) {
    void* gep = LLVMBuildStructGEP2(self->builder, struct_ty, alloca_val, fi, f.name);
    int64_t fv_kind = LLVMGetTypeKind(LLVMTypeOf(field_val));
    void* field_llvm_ty = LLVMStructGetTypeAtIndex(struct_ty, fi);
    int64_t field_kind = LLVMGetTypeKind(field_llvm_ty);
    if ((fv_kind == LLVMPointerTypeKind) && (field_kind == LLVMStructTypeKind)) {
    field_val = LLVMBuildLoad2(self->builder, field_llvm_ty, field_val, "");
}
    LLVMBuildStore(self->builder, field_val, gep);
}
    fi = (fi + 1LL);
}
    return alloca_val;
}
    if (expr.kind == ExprKind_ek_field_access) {
    bool is_enum_member_ref = false;
    ExprNode base_expr = ArrayList_ExprNode_get(self->expr_pool, expr.field_expr);
    if (base_expr.kind == ExprKind_ek_identifier) {
    if (LLVMCodegen_is_enum_type(self, base_expr.ident_name)) {
    is_enum_member_ref = true;
}
}
    if (is_enum_member_ref) {
    const char* enum_name = base_expr.ident_name;
    const char* variant_name = expr.field_name;
    int64_t tag_idx = 0LL;
    bool found_tag = false;
    int64_t enum_stmt_idx = 0LL;
    while (enum_stmt_idx < ArrayList_StmtNode_length(self->stmt_pool)) {
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, enum_stmt_idx);
    if ((stmt.kind == StmtKind_sk_enum_decl) && (strcmp(stmt.enum_name, enum_name) == 0)) {
    int64_t vi = 0LL;
    while (vi < ArrayList_Variant_length(&(stmt.enum_variants))) {
    if (strcmp(ArrayList_Variant_get(&(stmt.enum_variants), vi).vname, variant_name) == 0) {
    tag_idx = vi;
    found_tag = true;
}
    vi = (vi + 1LL);
}
}
    enum_stmt_idx = (enum_stmt_idx + 1LL);
}
    bool has_payload = false;
    const char* stripped_enum_name = LLVMCodegen_strip_module_prefix(self, enum_name);
    int64_t ei_chk = 0LL;
    while (ei_chk < ArrayList_Str_length(&(self->enum_cache_names))) {
    if (strcmp(ArrayList_Str_get(&(self->enum_cache_names), ei_chk), stripped_enum_name) == 0) {
    has_payload = ArrayList_Bool_get(&(self->enum_has_payload), ei_chk);
}
    ei_chk = (ei_chk + 1LL);
}
    if (!has_payload) {
    return LLVMConstInt(self->int64_type, tag_idx, false);
} else {
    void* enum_ty = LLVMCodegen_map_type(self, enum_name);
    if ((enum_ty == self->void_type) || (enum_ty == (void*)(unsigned long long)(0LL))) {
    return (void*)(unsigned long long)(0LL);
}
    void* alloca_val = LLVMBuildAlloca(self->builder, enum_ty, ".enum_var");
    void* tag_gep = LLVMBuildStructGEP2(self->builder, enum_ty, alloca_val, 0LL, ".tag");
    LLVMBuildStore(self->builder, LLVMConstInt(self->int8_type, tag_idx, false), tag_gep);
    return LLVMBuildLoad2(self->builder, enum_ty, alloca_val, "");
}
}
    void* base_val = LLVMCodegen_gen_expr(self, expr.field_expr);
    if (base_val == (void*)(unsigned long long)(0LL)) {
    return (void*)(unsigned long long)(0LL);
}
    const char* base_type = LLVMCodegen_get_expr_type(self, expr.field_expr);
    if (strlen(base_type) == 0LL) {
    void* base_llvm_ty = LLVMTypeOf(base_val);
    const char* ty_str = (const char*)(LLVMPrintTypeToString(base_llvm_ty));
    int64_t start_idx = 0LL;
    if ((strlen(ty_str) > 8LL) && (strcmp(__kai_str_sub(ty_str, 0LL, 8LL), "%struct.") == 0)) {
    start_idx = 8LL;
} else if ((strlen(ty_str) > 1LL) && ((ty_str)[0LL] == ((char)(37LL)))) {
    start_idx = 1LL;
}
    int64_t end_idx = strlen(ty_str);
    while ((end_idx > start_idx) && ((((ty_str)[(end_idx - 1LL)] == ((char)(42LL))) || ((ty_str)[(end_idx - 1LL)] == ((char)(38LL)))) || ((ty_str)[(end_idx - 1LL)] == ((char)(32LL))))) {
    end_idx = (end_idx - 1LL);
}
    if (end_idx > start_idx) {
    base_type = __kai_str_sub(ty_str, start_idx, end_idx);
}
}
    const char* clean_base_type = base_type;
    while ((strlen(clean_base_type) > 0LL) && (((clean_base_type)[0LL] == ((char)(42LL))) || ((clean_base_type)[0LL] == ((char)(38LL))))) {
    clean_base_type = __kai_str_sub(clean_base_type, 1LL, strlen(clean_base_type));
}
    int64_t field_idx = (-1LL);
    bool found_field = false;
    int64_t struct_decl_idx = (-1LL);
    bool is_error_union = false;
    if (LLVMCodegen_str_contains(self, clean_base_type, ((char)(33LL)))) {
    is_error_union = true;
} else if ((strlen(clean_base_type) > 7LL) && (strcmp(__kai_str_sub(clean_base_type, 0LL, 7LL), "Result_") == 0)) {
    is_error_union = true;
}
    if (is_error_union) {
    if (strcmp(expr.field_name, "tag") == 0) {
    field_idx = 0LL;
    found_field = true;
} else if (strcmp(expr.field_name, "value") == 0) {
    field_idx = 1LL;
    found_field = true;
}
} else {
    struct_decl_idx = LLVMCodegen_find_struct_decl(self, clean_base_type);
    if (struct_decl_idx >= 0LL) {
    StmtNode s = ArrayList_StmtNode_get(self->stmt_pool, struct_decl_idx);
    int64_t fii = 0LL;
    while (fii < ArrayList_StructField_length(&(s.struct_fields))) {
    if (strcmp(ArrayList_StructField_get(&(s.struct_fields), fii).name, expr.field_name) == 0) {
    field_idx = fii;
    found_field = true;
    break;
}
    fii = (fii + 1LL);
}
}
}
    if (!found_field) {
    return (void*)(unsigned long long)(0LL);
}
    void* struct_ty = LLVMCodegen_map_type(self, clean_base_type);
    if ((struct_ty == (void*)(unsigned long long)(0LL)) || (struct_ty == self->void_type)) {
    return (void*)(unsigned long long)(0LL);
}
    void* base_ptr = base_val;
    void* base_llvm_ty = LLVMTypeOf(base_val);
    int64_t base_kind = LLVMGetTypeKind(base_llvm_ty);
    if (base_kind == LLVMStructTypeKind) {
    void* tmp = LLVMBuildAlloca(self->builder, struct_ty, ".tmp.field");
    LLVMBuildStore(self->builder, base_val, tmp);
    base_ptr = tmp;
}
    void* gep = LLVMBuildStructGEP2(self->builder, struct_ty, base_ptr, field_idx, expr.field_name);
    const char* field_type_str = "Int";
    if (found_field && (struct_decl_idx >= 0LL)) {
    StmtNode s2 = ArrayList_StmtNode_get(self->stmt_pool, struct_decl_idx);
    if ((field_idx >= 0LL) && (field_idx < ArrayList_StructField_length(&(s2.struct_fields)))) {
    field_type_str = ArrayList_StructField_get(&(s2.struct_fields), field_idx).ftype;
    if (ArrayList_Str_length(&(s2.struct_type_params)) > 0LL) {
    ArrayList_LLVMStrMapEntry old_map = self->current_type_map;
    self->current_type_map = LLVMCodegen_setup_type_map_from_mangled_name(self, s2.struct_name, clean_base_type, &(s2.struct_type_params));
    const char* resolved_field_ty = LLVMCodegen_substitute_generic_type(self, field_type_str);
    field_type_str = resolved_field_ty;
    self->current_type_map = old_map;
}
}
}
    void* field_llvm_type = LLVMCodegen_map_type(self, field_type_str);
    bool is_aggregate = false;
    if (((field_llvm_type != (void*)(unsigned long long)(0LL)) && (field_llvm_type != self->void_type)) && (field_llvm_type != self->str_type)) {
    int64_t ty_kind = LLVMGetTypeKind(field_llvm_type);
    if ((ty_kind == LLVMStructTypeKind) || (ty_kind == LLVMArrayTypeKind)) {
    is_aggregate = true;
}
}
    if (is_aggregate) {
    return gep;
}
    if ((field_llvm_type == (void*)(unsigned long long)(0LL)) || (field_llvm_type == self->void_type)) {
    return LLVMBuildLoad2(self->builder, self->int64_type, gep, "");
}
    return LLVMBuildLoad2(self->builder, field_llvm_type, gep, expr.field_name);
}
    if (expr.kind == ExprKind_ek_method_call) {
    void* receiver_val = LLVMCodegen_gen_expr(self, expr.meth_expr);
    if (receiver_val == (void*)(unsigned long long)(0LL)) {
    return (void*)(unsigned long long)(0LL);
}
    const char* receiver_type = LLVMCodegen_get_expr_type(self, expr.meth_expr);
    const char* clean_type = receiver_type;
    if (strlen(clean_type) == 0LL) {
    void* rec_ty = LLVMTypeOf(receiver_val);
    const char* ty_str = (const char*)(LLVMPrintTypeToString(rec_ty));
    int64_t start_idx = 0LL;
    if ((strlen(ty_str) > 8LL) && (strcmp(__kai_str_sub(ty_str, 0LL, 8LL), "%struct.") == 0)) {
    start_idx = 8LL;
} else if ((strlen(ty_str) > 1LL) && ((ty_str)[0LL] == ((char)(37LL)))) {
    start_idx = 1LL;
}
    int64_t end_idx = strlen(ty_str);
    while ((end_idx > start_idx) && ((((ty_str)[(end_idx - 1LL)] == ((char)(42LL))) || ((ty_str)[(end_idx - 1LL)] == ((char)(38LL)))) || ((ty_str)[(end_idx - 1LL)] == ((char)(32LL))))) {
    end_idx = (end_idx - 1LL);
}
    if (end_idx > start_idx) {
    clean_type = __kai_str_sub(ty_str, start_idx, end_idx);
}
}
    while ((strlen(clean_type) > 0LL) && (((clean_type)[0LL] == ((char)(42LL))) || ((clean_type)[0LL] == ((char)(38LL))))) {
    clean_type = __kai_str_sub(clean_type, 1LL, strlen(clean_type));
}
    if ((strlen(clean_type) >= 4LL) && (strcmp(__kai_str_sub(clean_type, 0LL, 4LL), "mut ") == 0)) {
    clean_type = __kai_str_sub(clean_type, 4LL, strlen(clean_type));
}
    const char* mangled_type = LLVMCodegen_clean_type_for_mangling(self, clean_type);
    const char* func_name = concatAlloc(concatAlloc(mangled_type, "_"), expr.meth_name);
    void* fn_val = LLVMCodegen_lookup_or_create_func(self, func_name);
    if (fn_val == (void*)(unsigned long long)(0LL)) {
    return (void*)(unsigned long long)(0LL);
}
    void* fn_ty = LLVMCodegen_get_cached_func_type(self, func_name);
    if (fn_ty == (void*)(unsigned long long)(0LL)) {
    return (void*)(unsigned long long)(0LL);
}
    bool is_init = (strcmp(expr.meth_name, "init") == 0);
    ArrayList_Int arg_vals = ArrayList_Int_init(self->allocator);
    if (!is_init) {
    ArrayList_Int_push(&(arg_vals), (int64_t)(receiver_val));
}
    const char* param_types_str = LLVMCodegen_get_func_param_types(self, func_name);
    int64_t ai = 0LL;
    while (ai < ArrayList_Int_length(&(expr.meth_args))) {
    void* raw_arg = LLVMCodegen_gen_expr(self, ArrayList_Int_get(&(expr.meth_args), ai));
    int64_t param_idx = (ai + 1LL);
    if (is_init) {
    param_idx = ai;
}
    const char* param_ty_str = LLVMCodegen_get_param_type_at_index(self, param_types_str, param_idx);
    void* av = LLVMCodegen_prepare_arg(self, raw_arg, param_ty_str, false);
    if (av != (void*)(unsigned long long)(0LL)) {
    ArrayList_Int_push(&(arg_vals), (int64_t)(av));
} else {
    ArrayList_Int_push(&(arg_vals), (int64_t)(LLVMConstInt(self->int64_type, 0LL, false)));
}
    ai = (ai + 1LL);
}
    void* call_res = LLVMBuildCall2(self->builder, fn_ty, fn_val, (void*)(arg_vals.data), ArrayList_Int_length(&(arg_vals)), "");
    if (is_init) {
    if (call_res != (void*)(unsigned long long)(0LL)) {
    LLVMBuildStore(self->builder, call_res, receiver_val);
}
    return receiver_val;
}
    return call_res;
}
    if (expr.kind == ExprKind_ek_asm) {
    const char* constraints_str = "";
    int64_t oi = 0LL;
    while (oi < ArrayList_AsmOutput_length(&(expr.asm_outputs))) {
    AsmOutput out = ArrayList_AsmOutput_get(&(expr.asm_outputs), oi);
    if (strlen(constraints_str) > 0LL) {
    constraints_str = concatAlloc(constraints_str, ",");
}
    constraints_str = concatAlloc(concatAlloc(constraints_str, "="), out.constraint);
    oi = (oi + 1LL);
}
    int64_t ii = 0LL;
    while (ii < ArrayList_AsmInput_length(&(expr.asm_inputs))) {
    AsmInput inp = ArrayList_AsmInput_get(&(expr.asm_inputs), ii);
    if (strlen(constraints_str) > 0LL) {
    constraints_str = concatAlloc(constraints_str, ",");
}
    constraints_str = concatAlloc(constraints_str, inp.constraint);
    ii = (ii + 1LL);
}
    int64_t ci = 0LL;
    while (ci < ArrayList_Str_length(&(expr.asm_clobbers))) {
    if (strlen(constraints_str) > 0LL) {
    constraints_str = concatAlloc(constraints_str, ",");
}
    constraints_str = concatAlloc(concatAlloc(concatAlloc(constraints_str, "~{"), ArrayList_Str_get(&(expr.asm_clobbers), ci)), "}");
    ci = (ci + 1LL);
}
    int64_t total_inputs = ArrayList_AsmInput_length(&(expr.asm_inputs));
    ArrayList_Int inp_vals = ArrayList_Int_init(self->allocator);
    ArrayList_Int param_types = ArrayList_Int_init(self->allocator);
    int64_t inp_idx = 0LL;
    while (inp_idx < total_inputs) {
    AsmInput inp = ArrayList_AsmInput_get(&(expr.asm_inputs), inp_idx);
    void* iv = LLVMCodegen_gen_expr(self, inp.expr_idx);
    if (iv == (void*)(unsigned long long)(0LL)) {
    ArrayList_Int_push(&(inp_vals), (int64_t)(LLVMConstInt(self->int64_type, 0LL, false)));
    ArrayList_Int_push(&(param_types), (int64_t)(self->int64_type));
} else {
    ArrayList_Int_push(&(inp_vals), (int64_t)(iv));
    ArrayList_Int_push(&(param_types), (int64_t)(LLVMTypeOf(iv)));
}
    inp_idx = (inp_idx + 1LL);
}
    void* ret_ty = self->void_type;
    if (strlen(expr.inferred_type) > 0LL) {
    void* mt = LLVMCodegen_map_type(self, expr.inferred_type);
    if ((mt != self->void_type) && (mt != (void*)(unsigned long long)(0LL))) {
    ret_ty = mt;
}
} else if ((ArrayList_AsmOutput_length(&(expr.asm_outputs)) > 0LL) && (strlen(ArrayList_AsmOutput_get(&(expr.asm_outputs), 0LL).type_name) > 0LL)) {
    void* mt = LLVMCodegen_map_type(self, ArrayList_AsmOutput_get(&(expr.asm_outputs), 0LL).type_name);
    if ((mt != self->void_type) && (mt != (void*)(unsigned long long)(0LL))) {
    ret_ty = mt;
}
}
    void* fn_ty = LLVMFunctionType(ret_ty, (void*)(param_types.data), total_inputs, false);
    const char* asm_str = expr.asm_code;
    void* asm_val = kai_LLVMGetInlineAsm(fn_ty, (char*)(asm_str), strlen(asm_str), (char*)(constraints_str), strlen(constraints_str), expr.asm_is_volatile, false, 0LL, false);
    if (asm_val == (void*)(unsigned long long)(0LL)) {
    return (void*)(unsigned long long)(0LL);
}
    return LLVMBuildCall2(self->builder, fn_ty, asm_val, (void*)(inp_vals.data), total_inputs, "");
}
    if (expr.kind == ExprKind_ek_str_interp) {
    if (ArrayList_StrInterpPart_length(&(expr.interp_parts)) == 0LL) {
    return LLVMBuildGlobalStringPtr(self->builder, "", ".str_empty");
}
    const char* result_str = "";
    int64_t i = 0LL;
    while (i < ArrayList_StrInterpPart_length(&(expr.interp_parts))) {
    StrInterpPart part = ArrayList_StrInterpPart_get(&(expr.interp_parts), i);
    if (part.kind == 0LL) {
    result_str = concatAlloc(result_str, part.str_val);
} else {
    void* expr_val = LLVMCodegen_gen_expr(self, part.expr_idx);
    (void)(expr_val);
}
    i = (i + 1LL);
}
    const char* gname = concatAlloc(".str", int_to_str(self->str_counter));
    self->str_counter = (self->str_counter + 1LL);
    void* ptr_val = LLVMBuildGlobalStringPtr(self->builder, result_str, gname);
    void* null_str = LLVMConstNull(self->str_type);
    void* with_ptr = kai_LLVMBuildInsertValue(self->builder, null_str, ptr_val, 0LL, ".str.ptr");
    void* len_val = LLVMConstInt(self->int64_type, strlen(result_str), false);
    return kai_LLVMBuildInsertValue(self->builder, with_ptr, len_val, 1LL, ".str");
}
    if (expr.kind == ExprKind_ek_none) {
    return (void*)(unsigned long long)(0LL);
}
    return (void*)(unsigned long long)(0LL);
}
int64_t LLVMCodegen_str_to_int(LLVMCodegen* self, const char* s) {
    int64_t result = 0LL;
    int64_t i = 0LL;
    bool neg = false;
    if ((strlen(s) > 0LL) && ((s)[0LL] == ((char)(45LL)))) {
    neg = true;
    i = 1LL;
}
    while (i < strlen(s)) {
    char c = (s)[i];
    if ((c >= ((char)(48LL))) && (c <= ((char)(57LL)))) {
    result = ((result * 10LL) + ((int64_t)(c) - 48LL));
}
    i = (i + 1LL);
}
    if (neg) {
    result = (-result);
}
    return result;
}
double LLVMCodegen_str_to_float(LLVMCodegen* self, const char* s) {
    double result = 0.0;
    int64_t i = 0LL;
    bool neg = false;
    if ((strlen(s) > 0LL) && ((s)[0LL] == ((char)(45LL)))) {
    neg = true;
    i = 1LL;
}
    while (((i < strlen(s)) && ((s)[i] >= ((char)(48LL)))) && ((s)[i] <= ((char)(57LL)))) {
    result = ((result * 10.0) + (double)(((int64_t)((s)[i]) - 48LL)));
    i = (i + 1LL);
}
    if ((i < strlen(s)) && ((s)[i] == ((char)(46LL)))) {
    i = (i + 1LL);
    double divisor = 10.0;
    while (((i < strlen(s)) && ((s)[i] >= ((char)(48LL)))) && ((s)[i] <= ((char)(57LL)))) {
    result = (result + ((double)(((int64_t)((s)[i]) - 48LL)) / divisor));
    divisor = (divisor * 10.0);
    i = (i + 1LL);
}
}
    if (neg) {
    result = (-result);
}
    return result;
}
const char* LLVMCodegen_get_param_type_at_index(LLVMCodegen* self, const char* param_types_str, int64_t idx) {
    if (strlen(param_types_str) == 0LL) {
    return "";
}
    int64_t start = 0LL;
    int64_t curr_idx = 0LL;
    int64_t pi = 0LL;
    while (pi < strlen(param_types_str)) {
    if ((param_types_str)[pi] == ((char)(44LL))) {
    if (curr_idx == idx) {
    return __kai_str_sub(param_types_str, start, pi);
}
    start = (pi + 1LL);
    curr_idx = (curr_idx + 1LL);
}
    pi = (pi + 1LL);
}
    if (curr_idx == idx) {
    return __kai_str_sub(param_types_str, start, strlen(param_types_str));
}
    return "";
}
void* LLVMCodegen_prepare_arg(LLVMCodegen* self, void* arg_val, const char* param_type_str, bool callee_is_extern) {
    bool is_str = (((strcmp(param_type_str, "Str") == 0) || (strcmp(param_type_str, "*Str") == 0)) || (strcmp(param_type_str, "&Str") == 0));
    if (is_str) {
    if (callee_is_extern) {
    return LLVMCodegen_unwrap_str_for_c(self, arg_val);
} else {
    if (arg_val == (void*)(unsigned long long)(0LL)) {
    return LLVMConstNull(self->str_type);
}
    return LLVMCodegen_gen_cast(self, arg_val, self->str_type);
}
}
    void* param_llvm_ty = LLVMCodegen_map_type(self, param_type_str);
    void* effective_ty = param_llvm_ty;
    if ((param_llvm_ty == self->void_type) || (param_llvm_ty == (void*)(unsigned long long)(0LL))) {
    effective_ty = self->ptr_type;
}
    if (arg_val == (void*)(unsigned long long)(0LL)) {
    return LLVMConstNull(effective_ty);
}
    if (strlen(param_type_str) == 0LL) {
    return arg_val;
}
    int64_t ty_kind = LLVMGetTypeKind(effective_ty);
    if (ty_kind == LLVMStructTypeKind) {
    void* arg_ty = LLVMTypeOf(arg_val);
    if (arg_ty == effective_ty) {
    return arg_val;
}
    int64_t arg_kind = LLVMGetTypeKind(arg_ty);
    if (arg_kind == LLVMPointerTypeKind) {
    return LLVMBuildLoad2(self->builder, effective_ty, arg_val, "");
}
    return LLVMConstNull(effective_ty);
}
    return LLVMCodegen_gen_cast(self, arg_val, effective_ty);
}
void* LLVMCodegen_gen_cast(LLVMCodegen* self, void* val, void* dest_type) {
    if ((val == (void*)(unsigned long long)(0LL)) || (dest_type == (void*)(unsigned long long)(0LL))) {
    return val;
}
    void* src_type = LLVMTypeOf(val);
    if (src_type == dest_type) {
    return val;
}
    int64_t src_kind = LLVMGetTypeKind(src_type);
    int64_t dest_kind = LLVMGetTypeKind(dest_type);
    if (((dest_kind == LLVMStructTypeKind) && (src_kind == LLVMPointerTypeKind)) && (dest_type != self->str_type)) {
    return LLVMBuildLoad2(self->builder, dest_type, val, "");
}
    if ((src_kind == LLVMPointerTypeKind) && (dest_type == self->str_type)) {
    void* undef_s = LLVMGetUndef(self->str_type);
    void* with_p = LLVMBuildInsertValue(self->builder, undef_s, val, 0LL, "");
    void* fn_val = LLVMGetNamedFunction(self->module, "strlen");
    void* strlen_ty = kai_func_type_1(self->int64_type, self->ptr_type, false);
    if (fn_val == (void*)(unsigned long long)(0LL)) {
    fn_val = LLVMAddFunction(self->module, "strlen", strlen_ty);
}
    void* len_val = kai_build_call_1(self->builder, strlen_ty, fn_val, val, "");
    void* with_l = LLVMBuildInsertValue(self->builder, with_p, len_val, 1LL, "");
    return with_l;
}
    if ((src_type == self->str_type) && (dest_kind == LLVMPointerTypeKind)) {
    return LLVMBuildExtractValue(self->builder, val, 0LL, "");
}
    if ((src_type == self->str_type) && (dest_kind == LLVMIntegerTypeKind)) {
    void* raw_ptr = LLVMBuildExtractValue(self->builder, val, 0LL, "");
    return LLVMBuildPtrToInt(self->builder, raw_ptr, dest_type, "");
}
    if ((src_kind == LLVMPointerTypeKind) && (dest_kind == LLVMPointerTypeKind)) {
    return LLVMBuildBitCast(self->builder, val, dest_type, "");
}
    if ((src_kind == LLVMPointerTypeKind) && (dest_kind == LLVMIntegerTypeKind)) {
    return LLVMBuildPtrToInt(self->builder, val, dest_type, "");
}
    if ((src_kind == LLVMIntegerTypeKind) && (dest_kind == LLVMPointerTypeKind)) {
    return LLVMBuildIntToPtr(self->builder, val, dest_type, "");
}
    if ((src_kind == LLVMIntegerTypeKind) && (dest_kind == LLVMIntegerTypeKind)) {
    int64_t src_width = kai_LLVMGetIntTypeWidth(src_type);
    int64_t dest_width = kai_LLVMGetIntTypeWidth(dest_type);
    if (src_width < dest_width) {
    return LLVMBuildZExt(self->builder, val, dest_type, "");
} else if (src_width > dest_width) {
    return LLVMBuildTrunc(self->builder, val, dest_type, "");
}
    return val;
}
    if ((src_kind == LLVMFloatTypeKind) || (src_kind == LLVMDoubleTypeKind)) {
    if (dest_kind == LLVMIntegerTypeKind) {
    return LLVMBuildFPToSI(self->builder, val, dest_type, "");
}
}
    if ((dest_kind == LLVMFloatTypeKind) || (dest_kind == LLVMDoubleTypeKind)) {
    if (src_kind == LLVMIntegerTypeKind) {
    return LLVMBuildSIToFP(self->builder, val, dest_type, "");
}
}
    return LLVMBuildBitCast(self->builder, val, dest_type, "");
}
bool LLVMCodegen_is_struct_type(LLVMCodegen* self, const char* name) {
    if (((strcmp(name, "ArrayList") == 0) || (strcmp(name, "HashMap") == 0)) || (strcmp(name, "StringBuilder") == 0)) {
    return true;
}
    return (LLVMCodegen_find_struct_decl(self, name) >= 0LL);
}
bool LLVMCodegen_is_enum_type(LLVMCodegen* self, const char* name) {
    return (LLVMCodegen_find_enum_decl(self, name) >= 0LL);
}
const char* LLVMCodegen_clean_type_for_mangling(LLVMCodegen* self, const char* s) {
    if (LLVMCodegen_str_contains(self, s, ((char)(60LL)))) {
    int64_t lt_pos = LLVMCodegen_str_find(self, s, ((char)(60LL)));
    const char* base_name = __kai_str_sub(s, 0LL, lt_pos);
    const char* args_str = __kai_str_sub(s, (lt_pos + 1LL), (strlen(s) - 1LL));
    ArrayList_Str args = ArrayList_Str_init(self->allocator);
    int64_t start = 0LL;
    int64_t i = 0LL;
    while (i < strlen(args_str)) {
    char c = (args_str)[i];
    if (c == ((char)(44LL))) {
    ArrayList_Str_push(&(args), LLVMCodegen_trim_spaces(self, __kai_str_sub(args_str, start, i)));
    start = (i + 1LL);
}
    i = (i + 1LL);
}
    ArrayList_Str_push(&(args), LLVMCodegen_trim_spaces(self, __kai_str_sub(args_str, start, strlen(args_str))));
    const char* concrete_name = base_name;
    int64_t ai = 0LL;
    while (ai < ArrayList_Str_length(&(args))) {
    const char* raw_arg = ArrayList_Str_get(&(args), ai);
    const char* clean_arg = LLVMCodegen_clean_type_for_mangling(self, raw_arg);
    concrete_name = concatAlloc(concatAlloc(concrete_name, "_"), clean_arg);
    ai = (ai + 1LL);
}
    return concrete_name;
}
    const char* result = "";
    int64_t i = 0LL;
    while (i < strlen(s)) {
    char c = (s)[i];
    if (c == ((char)(42LL))) {
    result = concatAlloc(result, "ptr");
} else if (c == ((char)(38LL))) {
    result = concatAlloc(result, "ref");
} else if (c == ((char)(32LL))) {
    result = concatAlloc(result, "_");
} else if (((((((c == ((char)(60LL))) || (c == ((char)(62LL)))) || (c == ((char)(44LL)))) || (c == ((char)(33LL)))) || (c == ((char)(63LL)))) || (c == ((char)(40LL)))) || (c == ((char)(41LL)))) {
    result = concatAlloc(result, "_");
} else {
    result = concatAlloc(result, char_to_str(c));
}
    i = (i + 1LL);
}
    return result;
}
int64_t LLVMCodegen_str_find(LLVMCodegen* self, const char* s, char c) {
    int64_t i = 0LL;
    while (i < strlen(s)) {
    if ((s)[i] == c) {
    return i;
}
    i = (i + 1LL);
}
    return (-1LL);
}
bool LLVMCodegen_str_contains(LLVMCodegen* self, const char* s, char c) {
    return (LLVMCodegen_str_find(self, s, c) >= 0LL);
}
const char* LLVMCodegen_substitute_generic_type_in_ftype(LLVMCodegen* self, const char* ftype, const char* clean_type, StmtNode stmt) {
    int64_t lt_pos = LLVMCodegen_str_find(self, clean_type, ((char)(60LL)));
    int64_t gt_pos = LLVMCodegen_str_find(self, clean_type, ((char)(62LL)));
    if (((lt_pos < 0LL) || (gt_pos < 0LL)) || (gt_pos <= lt_pos)) {
    return ftype;
}
    const char* arg_str = __kai_str_sub(clean_type, (lt_pos + 1LL), gt_pos);
    if (ArrayList_Str_length(&(stmt.struct_type_params)) > 0LL) {
    const char* param_name = ArrayList_Str_get(&(stmt.struct_type_params), 0LL);
    if (strcmp(ftype, param_name) == 0) {
    return arg_str;
}
    if (strcmp(ftype, concatAlloc("*", param_name)) == 0) {
    return concatAlloc("*", arg_str);
}
    if (strcmp(ftype, concatAlloc("[]", param_name)) == 0) {
    return concatAlloc("[]", arg_str);
}
}
    return ftype;
}
bool LLVMCodegen_emit_object(LLVMCodegen* self, const char* obj_path) {
    LLVMDumpModule(self->module);
    char* verify_err = (char*)(unsigned long long)(0LL);
    int64_t verify_res = LLVMVerifyModule(self->module, 2LL, (void*)(&(verify_err)));
    if (verify_res != 0LL) {
    if (verify_err != (char*)(unsigned long long)(0LL)) {
    printf("LLVM Module Verification failed: %s\n", verify_err);
    kai_fflush(stdout);
}
}
    kai_LLVMInitializeAllTargetInfos();
    kai_LLVMInitializeAllTargets();
    kai_LLVMInitializeAllTargetMCs();
    kai_LLVMInitializeAllAsmPrinters();
    kai_LLVMInitializeAllAsmParsers();
    self->tmp_target = (void*)(unsigned long long)(0LL);
    self->tmp_err = (char*)(unsigned long long)(0LL);
    LLVMSetTarget(self->module, (const char*)(LLVMGetDefaultTargetTriple()));
    LLVMGetTargetFromTriple((const char*)(LLVMGetDefaultTargetTriple()), (void*)(&(self->tmp_target)), (void*)(&(self->tmp_err)));
    void* machine = LLVMCreateTargetMachine(self->tmp_target, (const char*)(LLVMGetDefaultTargetTriple()), "", "", LLVMCodeGenLevelNone, LLVMRelocDefault, LLVMCodeModelDefault);
    char* ir_str = LLVMPrintModuleToString(self->module);
    printf("%s\n", ir_str);
    kai_fflush(stdout);
    int64_t emit_res = LLVMTargetMachineEmitToFile(machine, self->module, (char*)(obj_path), LLVMObjectFile, &(self->tmp_err));
    printf("LLVMTargetMachineEmitToFile returned: %d\n", emit_res);
    kai_fflush(stdout);
    if (self->tmp_err != (char*)(unsigned long long)(0LL)) {
    printf("LLVMTargetMachineEmitToFile error: %s\n", self->tmp_err);
    kai_fflush(stdout);
    LLVMDisposeMessage(self->tmp_err);
}
    LLVMDisposeTargetMachine(machine);
    return (emit_res == 0LL);
}
const char* LLVMCodegen_trim_spaces(LLVMCodegen* self, const char* s) {
    int64_t start = 0LL;
    while ((start < strlen(s)) && (((((s)[start] == ((char)(32LL))) || ((s)[start] == ((char)(9LL)))) || ((s)[start] == ((char)(10LL)))) || ((s)[start] == ((char)(13LL))))) {
    start = (start + 1LL);
}
    int64_t end = strlen(s);
    while ((end > start) && (((((s)[(end - 1LL)] == ((char)(32LL))) || ((s)[(end - 1LL)] == ((char)(9LL)))) || ((s)[(end - 1LL)] == ((char)(10LL)))) || ((s)[(end - 1LL)] == ((char)(13LL))))) {
    end = (end - 1LL);
}
    return __kai_str_sub(s, start, end);
}
const char* LLVMCodegen_substitute_generic_type(LLVMCodegen* self, const char* name) {
    int64_t i = 0LL;
    while (i < ArrayList_LLVMStrMapEntry_length(&(self->current_type_map))) {
    LLVMStrMapEntry entry = ArrayList_LLVMStrMapEntry_get(&(self->current_type_map), i);
    if (strcmp(entry.key, name) == 0) {
    return entry.value;
}
    i = (i + 1LL);
}
    return name;
}
int64_t LLVMCodegen_find_struct_decl(LLVMCodegen* self, const char* clean_name) {
    const char* stripped_clean = LLVMCodegen_strip_module_prefix(self, clean_name);
    int64_t si = 0LL;
    while (si < ArrayList_StmtNode_length(self->stmt_pool)) {
    StmtNode s = ArrayList_StmtNode_get(self->stmt_pool, si);
    if (s.kind == StmtKind_sk_struct_decl) {
    const char* decl_name = LLVMCodegen_strip_module_prefix(self, s.struct_name);
    if (strcmp(decl_name, stripped_clean) == 0) {
    return si;
}
    if (ArrayList_Str_length(&(s.struct_type_params)) > 0LL) {
    const char* prefix = concatAlloc(decl_name, "_");
    if ((strlen(stripped_clean) > strlen(prefix)) && (strcmp(__kai_str_sub(stripped_clean, 0LL, strlen(prefix)), prefix) == 0)) {
    return si;
}
}
}
    si = (si + 1LL);
}
    return (-1LL);
}
int64_t LLVMCodegen_find_enum_decl(LLVMCodegen* self, const char* clean_name) {
    const char* stripped_clean = LLVMCodegen_strip_module_prefix(self, clean_name);
    int64_t si = 0LL;
    while (si < ArrayList_StmtNode_length(self->stmt_pool)) {
    StmtNode s = ArrayList_StmtNode_get(self->stmt_pool, si);
    if (s.kind == StmtKind_sk_enum_decl) {
    const char* decl_name = LLVMCodegen_strip_module_prefix(self, s.enum_name);
    if (strcmp(decl_name, stripped_clean) == 0) {
    return si;
}
    if (ArrayList_Str_length(&(s.enum_type_params)) > 0LL) {
    const char* prefix = concatAlloc(decl_name, "_");
    if ((strlen(stripped_clean) > strlen(prefix)) && (strcmp(__kai_str_sub(stripped_clean, 0LL, strlen(prefix)), prefix) == 0)) {
    return si;
}
}
}
    si = (si + 1LL);
}
    return (-1LL);
}
ArrayList_LLVMStrMapEntry LLVMCodegen_setup_type_map_from_mangled_name(LLVMCodegen* self, const char* base_name, const char* mangled_name, ArrayList_Str* param_names) {
    ArrayList_LLVMStrMapEntry map = ArrayList_LLVMStrMapEntry_init(self->allocator);
    const char* prefix = concatAlloc(base_name, "_");
    if (strlen(mangled_name) <= strlen(prefix)) {
    return map;
}
    const char* suffix = __kai_str_sub(mangled_name, strlen(prefix), strlen(mangled_name));
    int64_t start = 0LL;
    int64_t i = 0LL;
    int64_t arg_idx = 0LL;
    while ((i < strlen(suffix)) && (arg_idx < ArrayList_Str_length(param_names))) {
    if ((suffix)[i] == ((char)(95LL))) {
    const char* arg = __kai_str_sub(suffix, start, i);
    ArrayList_LLVMStrMapEntry_push(&(map), (LLVMStrMapEntry){ .key = ArrayList_Str_get(param_names, arg_idx), .value = arg });
    arg_idx = (arg_idx + 1LL);
    start = (i + 1LL);
}
    i = (i + 1LL);
}
    if ((start < strlen(suffix)) && (arg_idx < ArrayList_Str_length(param_names))) {
    const char* arg = __kai_str_sub(suffix, start, strlen(suffix));
    ArrayList_LLVMStrMapEntry_push(&(map), (LLVMStrMapEntry){ .key = ArrayList_Str_get(param_names, arg_idx), .value = arg });
}
    return map;
}
void LLVMCodegen_setup_current_type_map(LLVMCodegen* self, ArrayList_Str* param_names, ArrayList_Str* type_args) {
    int64_t i = 0LL;
    while ((i < ArrayList_Str_length(param_names)) && (i < ArrayList_Str_length(type_args))) {
    ArrayList_LLVMStrMapEntry_push(&(self->current_type_map), (LLVMStrMapEntry){ .key = ArrayList_Str_get(param_names, i), .value = ArrayList_Str_get(type_args, i) });
    i = (i + 1LL);
}
}
void LLVMCodegen_monomorphize_struct(LLVMCodegen* self, int64_t stmt_idx, const char* concrete_name, ArrayList_Str* type_args) {
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, stmt_idx);
    ArrayList_LLVMStrMapEntry old_type_map = self->current_type_map;
    self->current_type_map = ArrayList_LLVMStrMapEntry_init(self->allocator);
    LLVMCodegen_setup_current_type_map(self, &(stmt.struct_type_params), type_args);
    int64_t field_count = ArrayList_StructField_length(&(stmt.struct_fields));
    void* named_ty = LLVMStructCreateNamed(self->ctx, concrete_name);
    if (field_count > 0LL) {
    ArrayList_Int field_types = ArrayList_Int_init(self->allocator);
    int64_t fi = 0LL;
    while (fi < field_count) {
    StructField f = ArrayList_StructField_get(&(stmt.struct_fields), fi);
    void* fty = LLVMCodegen_map_type(self, f.ftype);
    if ((fty == self->void_type) || (fty == (void*)(unsigned long long)(0LL))) {
    ArrayList_Int_push(&(field_types), (int64_t)(self->int64_type));
} else {
    ArrayList_Int_push(&(field_types), (int64_t)(fty));
}
    fi = (fi + 1LL);
}
    LLVMStructSetBody(named_ty, (void*)(field_types.data), field_count, false);
}
    ArrayList_Str_push(&(self->struct_cache_names), concrete_name);
    ArrayList_Int_push(&(self->struct_cache_types), (int64_t)(named_ty));
    ArrayList_Int_push(&(self->struct_cache_field_counts), field_count);
    self->current_type_map = old_type_map;
    LLVMCodegen_monomorphize_methods_for_struct(self, stmt.struct_name, concrete_name, &(stmt.struct_type_params), type_args);
}
void LLVMCodegen_monomorphize_enum(LLVMCodegen* self, int64_t stmt_idx, const char* concrete_name, ArrayList_Str* type_args) {
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, stmt_idx);
    ArrayList_LLVMStrMapEntry old_type_map = self->current_type_map;
    self->current_type_map = ArrayList_LLVMStrMapEntry_init(self->allocator);
    LLVMCodegen_setup_current_type_map(self, &(stmt.enum_type_params), type_args);
    bool has_payload = false;
    int64_t vi = 0LL;
    while (vi < ArrayList_Variant_length(&(stmt.enum_variants))) {
    Variant v = ArrayList_Variant_get(&(stmt.enum_variants), vi);
    if (ArrayList_Param_length(&(v.params)) > 0LL) {
    has_payload = true;
}
    vi = (vi + 1LL);
}
    if (has_payload) {
    void* named_ty = LLVMStructCreateNamed(self->ctx, concrete_name);
    ArrayList_Int field_types = ArrayList_Int_init(self->allocator);
    ArrayList_Int_push(&(field_types), (int64_t)(self->int8_type));
    void* payload_ty = LLVMArrayType(self->int64_type, 16LL);
    ArrayList_Int_push(&(field_types), (int64_t)(payload_ty));
    LLVMStructSetBody(named_ty, (void*)(field_types.data), 2LL, false);
    ArrayList_Str_push(&(self->enum_cache_names), concrete_name);
    ArrayList_Int_push(&(self->enum_cache_types), (int64_t)(named_ty));
    ArrayList_Bool_push(&(self->enum_has_payload), true);
} else {
    ArrayList_Str_push(&(self->enum_cache_names), concrete_name);
    ArrayList_Int_push(&(self->enum_cache_types), (int64_t)(self->int64_type));
    ArrayList_Bool_push(&(self->enum_has_payload), false);
}
    self->current_type_map = old_type_map;
    LLVMCodegen_monomorphize_methods_for_struct(self, stmt.enum_name, concrete_name, &(stmt.enum_type_params), type_args);
}
const char* LLVMCodegen_substitute_type_params(LLVMCodegen* self, const char* type_name, ArrayList_Str* param_names, ArrayList_Str* arg_types) {
    if (ArrayList_Str_length(param_names) == 0LL) {
    return type_name;
}
    const char* result = type_name;
    int64_t i = 0LL;
    while (i < ArrayList_Str_length(param_names)) {
    const char* pn = ArrayList_Str_get(param_names, i);
    const char* arg = ArrayList_Str_get(arg_types, i);
    if (LLVMCodegen_str_contains(self, result, (pn)[0LL])) {
    int64_t ri = 0LL;
    const char* new_res = "";
    int64_t pn_len = strlen(pn);
    while (ri < strlen(result)) {
    bool matches = true;
    int64_t mi = 0LL;
    while (mi < pn_len) {
    if ((ri + mi) >= strlen(result)) {
    matches = false;
    break;
}
    if ((result)[(ri + mi)] != (pn)[mi]) {
    matches = false;
    break;
}
    mi = (mi + 1LL);
}
    if (matches) {
    new_res = concatAlloc(new_res, arg);
    ri = (ri + pn_len);
} else {
    new_res = concatAlloc(new_res, char_to_str((result)[ri]));
    ri = (ri + 1LL);
}
}
    result = new_res;
}
    i = (i + 1LL);
}
    return result;
}
bool LLVMCodegen_is_monomorphized_name(LLVMCodegen* self, const char* name) {
    int64_t len = strlen(name);
    if ((len > 10LL) && (strcmp(__kai_str_sub(name, 0LL, 10LL), "ArrayList_") == 0)) {
    return true;
}
    if ((len > 8LL) && (strcmp(__kai_str_sub(name, 0LL, 8LL), "HashMap_") == 0)) {
    return true;
}
    if ((len > 14LL) && (strcmp(__kai_str_sub(name, 0LL, 14LL), "StringBuilder_") == 0)) {
    return true;
}
    if ((len > 7LL) && (strcmp(__kai_str_sub(name, 0LL, 7LL), "Result_") == 0)) {
    return true;
}
    if ((len > 9LL) && (strcmp(__kai_str_sub(name, 0LL, 9LL), "optional_") == 0)) {
    return true;
}
    return false;
}
void LLVMCodegen_monomorphize_methods_for_struct(LLVMCodegen* self, const char* base_struct_name, const char* concrete_name, ArrayList_Str* param_names, ArrayList_Str* type_args) {
    int64_t si = 0LL;
    while (si < ArrayList_StmtNode_length(self->stmt_pool)) {
    StmtNode s = ArrayList_StmtNode_get(self->stmt_pool, si);
    if ((s.kind == StmtKind_sk_impl_block) && (strcmp(s.impl_struct_name, base_struct_name) == 0)) {
    int64_t j = 0LL;
    while (j < ArrayList_Int_length(&(s.impl_methods))) {
    int64_t m_idx = ArrayList_Int_get(&(s.impl_methods), j);
    StmtNode m_node = ArrayList_StmtNode_get(self->stmt_pool, m_idx);
    const char* method_name = m_node.func_name;
    bool is_init = ((((strcmp(method_name, "init") == 0) || (strcmp(m_node.func_return_type, base_struct_name) == 0)) || (strcmp(m_node.func_return_type, concatAlloc("*", base_struct_name)) == 0)) || (strcmp(m_node.func_return_type, concatAlloc("&", base_struct_name)) == 0));
    const char* mangled_fn = concatAlloc(concatAlloc(concrete_name, "_"), method_name);
    const char* ret = m_node.func_return_type;
    if (ArrayList_Str_length(param_names) > 0LL) {
    ret = LLVMCodegen_substitute_type_params(self, ret, param_names, type_args);
}
    if (is_init) {
    ret = concrete_name;
}
    ArrayList_Str_push(&(self->func_type_names), mangled_fn);
    ArrayList_Str_push(&(self->func_type_returns), ret);
    int64_t param_count = ArrayList_Param_length(&(m_node.func_params));
    if (is_init) {
    param_count = (param_count - 1LL);
}
    ArrayList_Int_push(&(self->func_param_counts), param_count);
    const char* pts = "";
    int64_t pi = 0LL;
    while (pi < ArrayList_Param_length(&(m_node.func_params))) {
    Param p = ArrayList_Param_get(&(m_node.func_params), pi);
    if (is_init && (strcmp(p.name, "self") == 0)) {
    pi = (pi + 1LL);
    continue;
}
    if (strlen(pts) > 0LL) {
    pts = concatAlloc(pts, ",");
}
    const char* ptype_str = p.ptype;
    if (strcmp(p.name, "self") == 0) {
    ptype_str = concatAlloc("*", concrete_name);
} else if (ArrayList_Str_length(param_names) > 0LL) {
    ptype_str = LLVMCodegen_substitute_type_params(self, ptype_str, param_names, type_args);
}
    pts = concatAlloc(pts, ptype_str);
    pi = (pi + 1LL);
}
    ArrayList_Str_push(&(self->func_type_param_types), pts);
    ArrayList_LLVMStrMapEntry saved_outer_type_map = self->current_type_map;
    self->current_type_map = ArrayList_LLVMStrMapEntry_init(self->allocator);
    void* fn_val = LLVMCodegen_lookup_or_create_func(self, mangled_fn);
    self->current_type_map = saved_outer_type_map;
    if (fn_val != (void*)(unsigned long long)(0LL)) {
    void* saved_func = self->cur_func;
    const char* saved_func_name = self->cur_func_name;
    void* saved_block = self->cur_block;
    bool saved_method_is_init = self->cur_method_is_init;
    void* saved_self_alloca = self->cur_self_alloca;
    void* saved_struct_type = self->cur_struct_type;
    bool saved_last_was_term = self->last_was_term;
    ArrayList_Str saved_local_alloca_names = self->local_alloca_names;
    ArrayList_Int saved_local_alloca_vals = self->local_alloca_vals;
    ArrayList_Int saved_local_alloca_types = self->local_alloca_types;
    ArrayList_Str saved_local_alloca_type_strs = self->local_alloca_type_strs;
    ArrayList_Int saved_local_alloca_decls = self->local_alloca_decls;
    void* saved_loop_cond = self->loop_cond_block;
    void* saved_loop_merge = self->loop_merge_block;
    void* saved_ip = LLVMGetInsertBlock(self->builder);
    LLVMCodegen_emit_func_body_mono(self, m_idx, fn_val, concrete_name, param_names, type_args);
    self->cur_func = saved_func;
    self->cur_func_name = saved_func_name;
    self->cur_block = saved_block;
    self->cur_method_is_init = saved_method_is_init;
    self->cur_self_alloca = saved_self_alloca;
    self->cur_struct_type = saved_struct_type;
    self->last_was_term = saved_last_was_term;
    self->local_alloca_names = saved_local_alloca_names;
    self->local_alloca_vals = saved_local_alloca_vals;
    self->local_alloca_types = saved_local_alloca_types;
    self->local_alloca_type_strs = saved_local_alloca_type_strs;
    self->local_alloca_decls = saved_local_alloca_decls;
    self->loop_cond_block = saved_loop_cond;
    self->loop_merge_block = saved_loop_merge;
    if (saved_ip != (void*)(unsigned long long)(0LL)) {
    LLVMPositionBuilderAtEnd(self->builder, saved_ip);
}
}
    j = (j + 1LL);
}
}
    si = (si + 1LL);
}
}
void LLVMCodegen_emit_func_body_mono(LLVMCodegen* self, int64_t stmt_idx, void* fn_val, const char* struct_name, ArrayList_Str* param_names, ArrayList_Str* type_args) {
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, stmt_idx);
    if (fn_val == (void*)(unsigned long long)(0LL)) {
    return;
}
    self->cur_func = fn_val;
    self->cur_func_name = concatAlloc(concatAlloc(struct_name, "_"), stmt.func_name);
    self->cur_block = LLVMAppendBasicBlockInContext(self->ctx, self->cur_func, "mono_entry");
    LLVMPositionBuilderAtEnd(self->builder, self->cur_block);
    self->last_was_term = false;
    self->local_alloca_names = ArrayList_Str_init(self->allocator);
    self->local_alloca_vals = ArrayList_Int_init(self->allocator);
    self->local_alloca_types = ArrayList_Int_init(self->allocator);
    self->local_alloca_type_strs = ArrayList_Str_init(self->allocator);
    self->local_alloca_decls = ArrayList_Int_init(self->allocator);
    self->loop_cond_block = (void*)(unsigned long long)(0LL);
    self->loop_merge_block = (void*)(unsigned long long)(0LL);
    bool is_init = (strcmp(stmt.func_name, "init") == 0);
    self->cur_method_is_init = is_init;
    self->cur_self_alloca = (void*)(unsigned long long)(0LL);
    self->cur_struct_type = (void*)(unsigned long long)(0LL);
    if (is_init) {
    self->cur_struct_type = LLVMCodegen_map_type(self, struct_name);
}
    ArrayList_LLVMStrMapEntry old_type_map = self->current_type_map;
    self->current_type_map = ArrayList_LLVMStrMapEntry_init(self->allocator);
    LLVMCodegen_setup_current_type_map(self, param_names, type_args);
    int64_t pi = 0LL;
    while (pi < ArrayList_Param_length(&(stmt.func_params))) {
    Param param = ArrayList_Param_get(&(stmt.func_params), pi);
    {
    printf("emit_func_body_mono: function %s, param.name = %s, pi = %d\n", self->cur_func_name, param.name, pi);
}
    const char* ptype_str = param.ptype;
    if ((strcmp(ptype_str, "self") != 0) && (strcmp(param.name, "self") != 0)) {
    ptype_str = LLVMCodegen_substitute_type_params(self, ptype_str, param_names, type_args);
}
    void* param_llvm_type = LLVMCodegen_map_type(self, ptype_str);
    const char* param_type_str = ptype_str;
    if (is_init && (strcmp(param.name, "self") == 0)) {
    param_llvm_type = self->cur_struct_type;
    param_type_str = struct_name;
    void* alloca_val = LLVMBuildAlloca(self->builder, param_llvm_type, "self");
    LLVMBuildStore(self->builder, LLVMConstNull(param_llvm_type), alloca_val);
    self->cur_self_alloca = alloca_val;
    ArrayList_Str_push(&(self->local_alloca_names), "self");
    ArrayList_Int_push(&(self->local_alloca_vals), (int64_t)(alloca_val));
    ArrayList_Int_push(&(self->local_alloca_types), (int64_t)(param_llvm_type));
    ArrayList_Str_push(&(self->local_alloca_type_strs), param_type_str);
    ArrayList_Int_push(&(self->local_alloca_decls), stmt_idx);
    pi = (pi + 1LL);
    continue;
}
    void* param_val = (void*)(unsigned long long)(0LL);
    if (is_init) {
    param_val = LLVMGetParam(self->cur_func, (pi - 1LL));
} else {
    param_val = LLVMGetParam(self->cur_func, pi);
}
    if (strcmp(param.name, "self") == 0) {
    param_llvm_type = LLVMCodegen_map_type(self, concatAlloc("*", struct_name));
    param_type_str = concatAlloc("*", struct_name);
}
    void* alloca_val = LLVMBuildAlloca(self->builder, param_llvm_type, param.name);
    LLVMBuildStore(self->builder, param_val, alloca_val);
    ArrayList_Str_push(&(self->local_alloca_names), param.name);
    ArrayList_Int_push(&(self->local_alloca_vals), (int64_t)(alloca_val));
    ArrayList_Int_push(&(self->local_alloca_types), (int64_t)(param_llvm_type));
    ArrayList_Str_push(&(self->local_alloca_type_strs), param_type_str);
    ArrayList_Int_push(&(self->local_alloca_decls), stmt_idx);
    pi = (pi + 1LL);
}
    LLVMCodegen_gen_stmt(self, stmt.func_body);
    if (!self->last_was_term) {
    if (is_init) {
    void* loaded_self = LLVMBuildLoad2(self->builder, self->cur_struct_type, self->cur_self_alloca, "");
    LLVMBuildRet(self->builder, loaded_self);
} else {
    const char* ret_type_str = LLVMCodegen_get_func_return_type(self, self->cur_func_name);
    void* ret_type = LLVMCodegen_map_type(self, ret_type_str);
    if ((ret_type == self->void_type) || (ret_type == (void*)(unsigned long long)(0LL))) {
    LLVMBuildRetVoid(self->builder);
} else {
    LLVMBuildRet(self->builder, LLVMConstNull(ret_type));
}
}
}
    self->current_type_map = old_type_map;
}
int64_t llvm_type_map_find(ArrayList_LLVMStrMapEntry* arr, const char* key) {
    int64_t i = (ArrayList_LLVMStrMapEntry_length(arr) - 1LL);
    while (i >= 0LL) {
    if (strcmp(ArrayList_LLVMStrMapEntry_get(arr, i).key, key) == 0) {
    return i;
}
    i = (i - 1LL);
}
    return (-1LL);
}
const char* llvm_type_map_get(ArrayList_LLVMStrMapEntry* arr, const char* key) {
    int64_t idx = llvm_type_map_find(arr, key);
    if (idx < 0LL) {
    return "";
}
    return ArrayList_LLVMStrMapEntry_get(arr, idx).value;
}
void llvm_type_map_put(ArrayList_LLVMStrMapEntry* arr, const char* key, const char* value) {
    ArrayList_LLVMStrMapEntry_push(arr, (LLVMStrMapEntry){ .key = key, .value = value });
}
int64_t llvm_strlist_find(ArrayList_Str* arr, const char* key) {
    int64_t i = 0LL;
    while (i < ArrayList_Str_length(arr)) {
    if (strcmp(ArrayList_Str_get(arr, i), key) == 0) {
    return i;
}
    i = (i + 1LL);
}
    return (-1LL);
}
const char* diag_fix_safety(const char* code) {
    if (strcmp(code, "E0008") == 0LL) {
    return "behavior-preserving";
}
    if (strcmp(code, "E0020") == 0LL) {
    return "requires-human-review";
}
    return "requires-human-review";
}
const char* diag_repair_id(const char* code) {
    if (strcmp(code, "E0008") == 0LL) {
    return "make-binding-mutable";
}
    if (strcmp(code, "E0020") == 0LL) {
    return "declare-missing-symbol";
}
    return "manual-review";
}
const char* diag_repair_summary(const char* code) {
    if (strcmp(code, "E0008") == 0LL) {
    return "Change the root binding to `var` before passing it to a mutable API.";
}
    if (strcmp(code, "E0020") == 0LL) {
    return "Declare the referenced function, import the module that provides it, or correct the identifier spelling.";
}
    return "Inspect the diagnostic fields and choose a repair manually.";
}
bool diagnostic_can_apply_edits(const char* code) {
    if ((strcmp(code, "E0008") == 0LL) && (strcmp(diag_fix_safety(code), "behavior-preserving") == 0LL)) {
    return true;
}
    return false;
}
void print_json_string(const char* s) {
    int64_t len = strlen(s);
    int64_t i = 0LL;
    while (i < len) {
    {
    char c = (s)[i];
    if (c == ((char)(34LL))) {
    printf("\\\"");
} else if (c == ((char)(92LL))) {
    printf("\\\\");
} else if (c == ((char)(10LL))) {
    printf("\\n");
} else {
    printf("%c", c);
}
}
    i = (i + 1LL);
}
}
void print_diag_json(const char* code, const char* message, const char* path, int64_t line, int64_t column, int64_t len_val, const char* expected, const char* actual, const char* help) {
    printf("{\"code\":\"");
    print_json_string(code);
    printf("\",\"message\":\"");
    print_json_string(message);
    printf("\",\"path\":\"");
    print_json_string(path);
    printf("\",\"line\":%ld,\"column\":%ld,\"length\":%ld", line, column, len_val);
    printf(",\"expected\":\"");
    print_json_string(expected);
    printf("\",\"actual\":\"");
    print_json_string(actual);
    printf("\",\"help\":\"");
    print_json_string(help);
    printf("\",\"fixSafety\":\"");
    print_json_string(diag_fix_safety(code));
    printf("\",\"repair\":{\"id\":\"");
    print_json_string(diag_repair_id(code));
    printf("\",\"summary\":\"");
    print_json_string(diag_repair_summary(code));
    printf("\"}}");
}
void print_fix_json(const char* code, bool applies) {
    printf("{\"id\":\"");
    print_json_string(diag_repair_id(code));
    printf("\",\"diagnosticCode\":\"");
    print_json_string(code);
    printf("\",\"safety\":\"");
    print_json_string(diag_fix_safety(code));
    printf("\",\"summary\":\"");
    print_json_string(diag_repair_summary(code));
    if (applies) {
    printf("\",\"appliesEdits\":true}");
} else {
    printf("\",\"appliesEdits\":false}");
}
}
void print_plan(const char* path, bool json_mode, ArrayList_Str* codes, ArrayList_Str* messages, ArrayList_Int* dlines, ArrayList_Int* dcolumns, ArrayList_Int* dlengths, ArrayList_Str* expected, ArrayList_Str* actual, ArrayList_Str* helpv) {
    int64_t count = ArrayList_Str_length(codes);
    if (!json_mode) {
    if (count == 0LL) {
    printf("No diagnostics found in '%s'\n", path);
    return;
}
    printf("Found %ld diagnostic(s) in '%s':\n", count, path);
    int64_t i = 0LL;
    while (i < count) {
    const char* cd = ArrayList_Str_get(codes, i);
    printf("%s:%ld:%ld %s: %s\n", path, ArrayList_Int_get(dlines, i), ArrayList_Int_get(dcolumns, i), cd, ArrayList_Str_get(messages, i));
    printf("  expected: %s\n", ArrayList_Str_get(expected, i));
    printf("  actual: %s\n", ArrayList_Str_get(actual, i));
    printf("  help: %s\n", ArrayList_Str_get(helpv, i));
    printf("  explain: kai explain %s\n", cd);
    i = (i + 1LL);
}
    return;
}
    bool has_diag = (count > 0LL);
    printf("{\n  \"schemaVersion\": 1,\n  \"ok\": ");
    if (has_diag) {
    printf("false");
} else {
    printf("true");
}
    printf(",\n  \"mode\": \"plan\",\n  \"appliesEdits\": false,\n  \"safetyLevels\": [\"format-only\",\"behavior-preserving\",\"api-changing\",\"target-changing\",\"requires-human-review\"],\n  \"input\": \"");
    print_json_string(path);
    printf("\",\n  \"selfHostRepairPolicy\": {\"unsupportedFeatureSafety\":\"requires-human-review\",\"compatibilityFallback\":\"removed\",\"directFallback\":\"never-c-bridge\"},\n  \"diagnostics\": [");
    int64_t i2 = 0LL;
    while (i2 < count) {
    if (i2 > 0LL) {
    printf(",");
}
    printf("\n    ");
    print_diag_json(ArrayList_Str_get(codes, i2), ArrayList_Str_get(messages, i2), path, ArrayList_Int_get(dlines, i2), ArrayList_Int_get(dcolumns, i2), ArrayList_Int_get(dlengths, i2), ArrayList_Str_get(expected, i2), ArrayList_Str_get(actual, i2), ArrayList_Str_get(helpv, i2));
    i2 = (i2 + 1LL);
}
    printf("\n  ],\n  \"fixes\": [");
    i2 = 0LL;
    while (i2 < count) {
    if (i2 > 0LL) {
    printf(",");
}
    printf("\n    ");
    const char* cd = ArrayList_Str_get(codes, i2);
    print_fix_json(cd, diagnostic_can_apply_edits(cd));
    i2 = (i2 + 1LL);
}
    printf("\n  ]\n}\n");
}
void print_patch(const char* path, bool json_mode, bool apply, bool applied, ArrayList_Str* codes, ArrayList_Str* messages, ArrayList_Int* dlines, ArrayList_Int* dcolumns, ArrayList_Int* dlengths, ArrayList_Str* expected, ArrayList_Str* actual, ArrayList_Str* helpv, ArrayList_Int* patch_lines, ArrayList_Str* patch_old, ArrayList_Str* patch_new, ArrayList_Str* patch_codes) {
    int64_t count = ArrayList_Str_length(codes);
    int64_t patch_count = ArrayList_Str_length(patch_codes);
    if (!json_mode) {
    if (patch_count > 0LL) {
    printf("Diff for '%s':\n", path);
    int64_t pi = 0LL;
    while (pi < patch_count) {
    const char* old_line = ArrayList_Str_get(patch_old, pi);
    const char* new_line = ArrayList_Str_get(patch_new, pi);
    printf("- %s\n+ %s\n", old_line, new_line);
    pi = (pi + 1LL);
}
}
    if (count > patch_count) {
    printf("(%ld issue(s) without auto-fix — use kai patch to address them)\n", (count - patch_count));
}
    if (apply) {
    if (applied) {
    printf("Applied %ld fix(es) to '%s'\n", patch_count, path);
} else {
    printf("No behavior-preserving edits to apply in '%s'\n", path);
}
}
    return;
}
    bool has_diag = (count > 0LL);
    bool can_apply_total = ((count > 0LL) && (patch_count > 0LL));
    printf("{\n  \"schemaVersion\": 1,\n  \"ok\": ");
    if (has_diag) {
    printf("false");
} else {
    printf("true");
}
    printf(",\n  \"mode\": \"");
    if (apply) {
    printf("apply");
} else {
    printf("patch");
}
    printf("\",\n  \"appliesEdits\": ");
    if (apply) {
    printf("true");
} else {
    printf("false");
}
    printf(",\n  \"applied\": ");
    if (applied) {
    printf("true");
} else {
    printf("false");
}
    printf(",\n  \"input\": \"");
    print_json_string(path);
    printf("\",\n  \"selfHostRepairPolicy\": {\"unsupportedFeatureSafety\":\"requires-human-review\",\"compatibilityFallback\":\"removed\",\"directFallback\":\"never-c-bridge\"}");
    printf(",\n  \"diagnostics\": [");
    int64_t i2 = 0LL;
    while (i2 < count) {
    if (i2 > 0LL) {
    printf(",");
}
    printf("\n    ");
    print_diag_json(ArrayList_Str_get(codes, i2), ArrayList_Str_get(messages, i2), path, ArrayList_Int_get(dlines, i2), ArrayList_Int_get(dcolumns, i2), ArrayList_Int_get(dlengths, i2), ArrayList_Str_get(expected, i2), ArrayList_Str_get(actual, i2), ArrayList_Str_get(helpv, i2));
    i2 = (i2 + 1LL);
}
    printf("\n  ],\n  \"fixes\": [");
    i2 = 0LL;
    while (i2 < count) {
    if (i2 > 0LL) {
    printf(",");
}
    printf("\n    ");
    const char* cd = ArrayList_Str_get(codes, i2);
    print_fix_json(cd, diagnostic_can_apply_edits(cd));
    i2 = (i2 + 1LL);
}
    printf("\n  ],\n  \"patches\": [");
    i2 = 0LL;
    while (i2 < patch_count) {
    if (i2 > 0LL) {
    printf(",");
}
    printf("\n    {\"path\":\"");
    print_json_string(path);
    printf("\",\"line\":%ld,\"old\":\"", ArrayList_Int_get(patch_lines, i2));
    print_json_string(ArrayList_Str_get(patch_old, i2));
    printf("\",\"new\":\"");
    print_json_string(ArrayList_Str_get(patch_new, i2));
    printf("\"}");
    i2 = (i2 + 1LL);
}
    printf("\n  ]\n}\n");
}
int64_t run_fix(const char* fix_mode, const char* fix_file, bool json) {
    KaiAllocator fix_alloc = KaiAllocator_new();
    Result_Str_IoError src_res = read_to_string(&(fix_alloc), fix_file);
    if (src_res.tag != 0LL) {
    printf("Error: Could not read '%s'\n", fix_file);
    return 1LL;
}
    const char* source = (const char*)(src_res.value);
    int64_t src_len_val = strlen(source);
    if (!json) {
    StringPool fix_pool = StringPool_init(&(fix_alloc));
    Lexer fix_lexer = Lexer_init(&(fix_alloc), source, fix_file, &(fix_pool));
    Lexer_lex(&(fix_lexer));
    if (!fix_lexer.has_error) {
    Parser fix_parser = Parser_init(&(fix_alloc), fix_file, fix_lexer.tokens, source, &(fix_pool));
    int64_t prog_idx = Parser_parse_program(&(fix_parser));
    if (prog_idx >= 0LL) {
    ImportResolver resolver = ImportResolver_init(&(fix_alloc), &(fix_pool));
    TypeChecker chk = TypeChecker_init(&(fix_alloc), fix_parser.stmt_pool, fix_parser.expr_pool, fix_parser.pattern_pool, fix_file, source, &(resolver), &(fix_pool));
    bool ttmp = TypeChecker_check_program(&(chk), prog_idx);
    if (ttmp) {
} else {
}
}
}
}
    ArrayList_Str vars = ArrayList_Str_init(&(fix_alloc));
    ArrayList_Int var_lines = ArrayList_Int_init(&(fix_alloc));
    ArrayList_Bool var_mut = ArrayList_Bool_init(&(fix_alloc));
    ArrayList_Int var_columns = ArrayList_Int_init(&(fix_alloc));
    ArrayList_Str declared_fns = ArrayList_Str_init(&(fix_alloc));
    ArrayList_Str builtins = ArrayList_Str_init(&(fix_alloc));
    ArrayList_Str_push(&(builtins), "printf");
    ArrayList_Str_push(&(builtins), "system");
    ArrayList_Str_push(&(builtins), "strcmp");
    ArrayList_Str_push(&(builtins), "get_exe_dir");
    ArrayList_Str_push(&(builtins), "malloc");
    ArrayList_Str_push(&(builtins), "realloc");
    ArrayList_Str_push(&(builtins), "memcpy");
    ArrayList_Str_push(&(builtins), "memset");
    int64_t line_start = 0LL;
    int64_t line_num = 0LL;
    while (line_start <= src_len_val) {
    int64_t line_end = line_start;
    while (line_end < src_len_val) {
    {
    if ((source)[line_end] == ((char)(10LL))) {
    break;
}
}
    line_end = (line_end + 1LL);
}
    if (line_end > src_len_val) {
    line_end = src_len_val;
}
    int64_t line_len = (line_end - line_start);
    if (line_len > 0LL) {
    const char* line_text = substring(source, line_start, line_end);
    int64_t di = 0LL;
    while (di < line_len) {
    {
    char c = (line_text)[di];
    if ((c != ((char)(32LL))) && (c != ((char)(9LL)))) {
    break;
}
}
    di = (di + 1LL);
}
    if ((di + 3LL) <= line_len) {
    {
    if ((((line_text)[di] == ((char)(102LL))) && ((line_text)[(di + 1LL)] == ((char)(110LL)))) && ((line_text)[(di + 2LL)] == ((char)(32LL)))) {
    int64_t dn_start = (di + 3LL);
    int64_t dn_end = dn_start;
    while (dn_end < line_len) {
    if ((line_text)[dn_end] == ((char)(40LL))) {
    break;
}
    dn_end = (dn_end + 1LL);
}
    if ((dn_end > dn_start) && (dn_end < line_len)) {
    int64_t name_end2 = (dn_end - 1LL);
    while (name_end2 >= dn_start) {
    char c2 = (line_text)[name_end2];
    if ((c2 != ((char)(32LL))) && (c2 != ((char)(9LL)))) {
    break;
}
    name_end2 = (name_end2 - 1LL);
}
    const char* fn_name = substring(line_text, dn_start, (name_end2 + 1LL));
    ArrayList_Str_push(&(declared_fns), fn_name);
}
}
}
}
    if ((di + 10LL) <= line_len) {
    {
    if (((((((((((line_text)[di] == ((char)(101LL))) && ((line_text)[(di + 1LL)] == ((char)(120LL)))) && ((line_text)[(di + 2LL)] == ((char)(116LL)))) && ((line_text)[(di + 3LL)] == ((char)(101LL)))) && ((line_text)[(di + 4LL)] == ((char)(114LL)))) && ((line_text)[(di + 5LL)] == ((char)(110LL)))) && ((line_text)[(di + 6LL)] == ((char)(32LL)))) && ((line_text)[(di + 7LL)] == ((char)(102LL)))) && ((line_text)[(di + 8LL)] == ((char)(110LL)))) && ((line_text)[(di + 9LL)] == ((char)(32LL)))) {
    int64_t dn_start = (di + 10LL);
    int64_t dn_end = dn_start;
    while (dn_end < line_len) {
    if ((line_text)[dn_end] == ((char)(40LL))) {
    break;
}
    dn_end = (dn_end + 1LL);
}
    if ((dn_end > dn_start) && (dn_end < line_len)) {
    int64_t name_end2 = (dn_end - 1LL);
    while (name_end2 >= dn_start) {
    char c2 = (line_text)[name_end2];
    if ((c2 != ((char)(32LL))) && (c2 != ((char)(9LL)))) {
    break;
}
    name_end2 = (name_end2 - 1LL);
}
    const char* fn_name = substring(line_text, dn_start, (name_end2 + 1LL));
    ArrayList_Str_push(&(declared_fns), fn_name);
}
}
}
}
    int64_t li = 0LL;
    while (li < line_len) {
    {
    char c = (line_text)[li];
    if ((c != ((char)(32LL))) && (c != ((char)(9LL)))) {
    break;
}
}
    li = (li + 1LL);
}
    if ((li + 4LL) <= line_len) {
    {
    if (((((line_text)[li] == ((char)(108LL))) && ((line_text)[(li + 1LL)] == ((char)(101LL)))) && ((line_text)[(li + 2LL)] == ((char)(116LL)))) && ((line_text)[(li + 3LL)] == ((char)(32LL)))) {
    int64_t vstart = (li + 4LL);
    int64_t vend = vstart;
    while (vend < line_len) {
    char c = (line_text)[vend];
    if ((((c == ((char)(32LL))) || (c == ((char)(61LL)))) || (c == ((char)(58LL)))) || (c == ((char)(9LL)))) {
    break;
}
    vend = (vend + 1LL);
}
    if (vend > vstart) {
    const char* vname = substring(line_text, vstart, vend);
    ArrayList_Str_push(&(vars), vname);
    ArrayList_Int_push(&(var_lines), line_num);
    ArrayList_Bool_push(&(var_mut), false);
    ArrayList_Int_push(&(var_columns), (li + 1LL));
}
}
}
}
    int64_t ai = 0LL;
    while (ai < line_len) {
    {
    char c = (line_text)[ai];
    if ((c != ((char)(32LL))) && (c != ((char)(9LL)))) {
    break;
}
}
    ai = (ai + 1LL);
}
    if (ai < line_len) {
    int64_t eq_pos = (-1LL);
    int64_t vi = ai;
    while (vi < line_len) {
    {
    if ((line_text)[vi] == ((char)(61LL))) {
    eq_pos = vi;
    break;
}
}
    vi = (vi + 1LL);
}
    if (eq_pos > ai) {
    bool has_let_prefix = false;
    if ((ai + 4LL) <= eq_pos) {
    const char* let_prefix = substring(line_text, ai, (ai + 4LL));
    if (strcmp(let_prefix, "let ") == 0LL) {
    has_let_prefix = true;
}
}
    if ((!has_let_prefix) && (eq_pos > 0LL)) {
    int64_t before_eq = (eq_pos - 1LL);
    while (before_eq >= ai) {
    {
    char c = (line_text)[before_eq];
    if ((c != ((char)(32LL))) && (c != ((char)(9LL)))) {
    break;
}
}
    before_eq = (before_eq - 1LL);
}
    int64_t assign_start = before_eq;
    while (assign_start >= ai) {
    {
    char c = (line_text)[assign_start];
    if ((c == ((char)(32LL))) || (c == ((char)(9LL)))) {
    break;
}
}
    assign_start = (assign_start - 1LL);
}
    assign_start = (assign_start + 1LL);
    if (assign_start <= before_eq) {
    const char* assign_var = substring(line_text, assign_start, (before_eq + 1LL));
    int64_t vi2 = 0LL;
    while (vi2 < ArrayList_Str_length(&(vars))) {
    {
    if ((strcmp(assign_var, ArrayList_Str_get(&(vars), vi2)) == 0LL) && (!ArrayList_Bool_get(&(var_mut), vi2))) {
    ArrayList_Bool_set(&(var_mut), vi2, true);
}
}
    vi2 = (vi2 + 1LL);
}
}
}
}
}
}
    line_start = (line_end + 1LL);
    line_num = (line_num + 1LL);
}
    ArrayList_Str undef_fns = ArrayList_Str_init(&(fix_alloc));
    ArrayList_Int undef_lines = ArrayList_Int_init(&(fix_alloc));
    ArrayList_Int undef_columns = ArrayList_Int_init(&(fix_alloc));
    ArrayList_Int undef_lengths = ArrayList_Int_init(&(fix_alloc));
    line_start = 0LL;
    line_num = 0LL;
    while (line_start <= src_len_val) {
    int64_t line_end = line_start;
    while (line_end < src_len_val) {
    {
    if ((source)[line_end] == ((char)(10LL))) {
    break;
}
}
    line_end = (line_end + 1LL);
}
    if (line_end > src_len_val) {
    line_end = src_len_val;
}
    int64_t line_len = (line_end - line_start);
    if (line_len > 0LL) {
    const char* line_text = substring(source, line_start, line_end);
    int64_t ci = 0LL;
    while (ci < (line_len - 1LL)) {
    {
    char c = (line_text)[ci];
    if (__kai_std_ascii_is_alpha(c) || (c == ((char)(95LL)))) {
    int64_t name_start = ci;
    int64_t name_end = ci;
    while (name_end < line_len) {
    char nc = (line_text)[name_end];
    if (__kai_std_ascii_is_alnum(nc) || (nc == ((char)(95LL)))) {
    name_end = (name_end + 1LL);
} else {
    break;
}
}
    if (((name_end > name_start) && (name_end < line_len)) && ((line_text)[name_end] == ((char)(40LL)))) {
    const char* call_name = substring(line_text, name_start, name_end);
    bool is_decl = false;
    if (name_start >= 3LL) {
    const char* prefix = substring(line_text, (name_start - 3LL), name_start);
    if (strcmp(prefix, "fn ") == 0LL) {
    is_decl = true;
}
}
    if ((!is_decl) && (name_start >= 10LL)) {
    const char* exprefix = substring(line_text, (name_start - 10LL), name_start);
    if (strcmp(exprefix, "extern fn ") == 0LL) {
    is_decl = true;
}
}
    if (((!is_decl) && (name_start > 0LL)) && ((line_text)[(name_start - 1LL)] == ((char)(46LL)))) {
    is_decl = true;
}
    if (!is_decl) {
    bool known = false;
    int64_t ki = 0LL;
    while (ki < ArrayList_Str_length(&(declared_fns))) {
    {
    if (strcmp(call_name, ArrayList_Str_get(&(declared_fns), ki)) == 0LL) {
    known = true;
    break;
}
}
    ki = (ki + 1LL);
}
    if (!known) {
    int64_t bi = 0LL;
    while (bi < ArrayList_Str_length(&(builtins))) {
    {
    if (strcmp(call_name, ArrayList_Str_get(&(builtins), bi)) == 0LL) {
    known = true;
    break;
}
}
    bi = (bi + 1LL);
}
}
    if (!known) {
    if (((((((strcmp(call_name, "Int") == 0LL) || (strcmp(call_name, "Float") == 0LL)) || (strcmp(call_name, "Bool") == 0LL)) || (strcmp(call_name, "Char") == 0LL)) || (strcmp(call_name, "Str") == 0LL)) || (strcmp(call_name, "Void") == 0LL)) || (strcmp(call_name, "ArrayList") == 0LL)) {
    known = true;
}
}
    if (!known) {
    bool already = false;
    int64_t ai2 = 0LL;
    while (ai2 < ArrayList_Str_length(&(undef_fns))) {
    {
    if (strcmp(call_name, ArrayList_Str_get(&(undef_fns), ai2)) == 0LL) {
    already = true;
    break;
}
}
    ai2 = (ai2 + 1LL);
}
    if (!already) {
    ArrayList_Str_push(&(undef_fns), call_name);
    ArrayList_Int_push(&(undef_lines), line_num);
    ArrayList_Int_push(&(undef_columns), (name_start + 1LL));
    ArrayList_Int_push(&(undef_lengths), (name_end - name_start));
}
}
}
    ci = name_end;
}
}
}
    ci = (ci + 1LL);
}
}
    line_start = (line_end + 1LL);
    line_num = (line_num + 1LL);
}
    ArrayList_Str diag_codes = ArrayList_Str_init(&(fix_alloc));
    ArrayList_Str diag_messages = ArrayList_Str_init(&(fix_alloc));
    ArrayList_Int diag_lines = ArrayList_Int_init(&(fix_alloc));
    ArrayList_Int diag_columns = ArrayList_Int_init(&(fix_alloc));
    ArrayList_Int diag_lengths = ArrayList_Int_init(&(fix_alloc));
    ArrayList_Str diag_expected = ArrayList_Str_init(&(fix_alloc));
    ArrayList_Str diag_actual = ArrayList_Str_init(&(fix_alloc));
    ArrayList_Str diag_help = ArrayList_Str_init(&(fix_alloc));
    ArrayList_Int patch_lines_arr = ArrayList_Int_init(&(fix_alloc));
    ArrayList_Str patch_old_arr = ArrayList_Str_init(&(fix_alloc));
    ArrayList_Str patch_new_arr = ArrayList_Str_init(&(fix_alloc));
    ArrayList_Str patch_codes_arr = ArrayList_Str_init(&(fix_alloc));
    int64_t vi3 = 0LL;
    while (vi3 < ArrayList_Str_length(&(vars))) {
    if (ArrayList_Bool_get(&(var_mut), vi3)) {
    const char* vname = ArrayList_Str_get(&(vars), vi3);
    int64_t vline = ArrayList_Int_get(&(var_lines), vi3);
    int64_t vcol = ArrayList_Int_get(&(var_columns), vi3);
    ErrorInfo einfo = get_error_info("E0008");
    ArrayList_Str_push(&(diag_codes), "E0008");
    ArrayList_Str_push(&(diag_messages), einfo.title);
    ArrayList_Int_push(&(diag_lines), vline);
    ArrayList_Int_push(&(diag_columns), vcol);
    ArrayList_Int_push(&(diag_lengths), 3LL);
    ArrayList_Str_push(&(diag_expected), "Declare with 'var' instead of 'let'");
    ArrayList_Str_push(&(diag_actual), vname);
    ArrayList_Str_push(&(diag_help), einfo.fix);
    const char* old_line_text = "";
    int64_t line_offset = 0LL;
    int64_t line_num2 = 0LL;
    while (line_offset < src_len_val) {
    if (line_num2 == vline) {
    old_line_text = diag_line_text(source, line_offset);
    line_offset = src_len_val;
} else {
    line_offset = (diag_line_end(source, line_offset) + 1LL);
    if (line_offset > src_len_val) {
    line_offset = src_len_val;
}
}
    line_num2 = (line_num2 + 1LL);
}
    if (strlen(old_line_text) > 0LL) {
    const char* new_line_text = str_replace(old_line_text, "let ", "var ");
    ArrayList_Int_push(&(patch_lines_arr), vline);
    ArrayList_Str_push(&(patch_old_arr), old_line_text);
    ArrayList_Str_push(&(patch_new_arr), new_line_text);
    ArrayList_Str_push(&(patch_codes_arr), "E0008");
}
}
    vi3 = (vi3 + 1LL);
}
    int64_t ui = 0LL;
    while (ui < ArrayList_Str_length(&(undef_fns))) {
    const char* fn_name = ArrayList_Str_get(&(undef_fns), ui);
    int64_t fn_line = ArrayList_Int_get(&(undef_lines), ui);
    int64_t fn_col = ArrayList_Int_get(&(undef_columns), ui);
    int64_t fn_len = ArrayList_Int_get(&(undef_lengths), ui);
    ErrorInfo einfo = get_error_info("E0020");
    ArrayList_Str_push(&(diag_codes), "E0020");
    ArrayList_Str_push(&(diag_messages), einfo.title);
    ArrayList_Int_push(&(diag_lines), fn_line);
    ArrayList_Int_push(&(diag_columns), fn_col);
    ArrayList_Int_push(&(diag_lengths), fn_len);
    ArrayList_Str_push(&(diag_expected), "Declare the referenced function, import the module that provides it, or correct the identifier spelling");
    ArrayList_Str_push(&(diag_actual), fn_name);
    ArrayList_Str_push(&(diag_help), einfo.fix);
    ui = (ui + 1LL);
}
    int64_t total_count = ArrayList_Str_length(&(diag_codes));
    int64_t patch_count = ArrayList_Str_length(&(patch_codes_arr));
    bool can_apply = (patch_count > 0LL);
    if (strcmp(fix_mode, "plan") == 0LL) {
    print_plan(fix_file, json, &(diag_codes), &(diag_messages), &(diag_lines), &(diag_columns), &(diag_lengths), &(diag_expected), &(diag_actual), &(diag_help));
    return 0LL;
}
    if ((strcmp(fix_mode, "patch") == 0LL) || (strcmp(fix_mode, "apply") == 0LL)) {
    bool is_apply = (strcmp(fix_mode, "apply") == 0LL);
    bool applied = false;
    if (is_apply && can_apply) {
    const char* modified_source = "";
    int64_t offset = 0LL;
    int64_t line_num3 = 0LL;
    while (offset < src_len_val) {
    const char* line_text = diag_line_text(source, offset);
    int64_t line_end = diag_line_end(source, offset);
    bool found_patch = false;
    int64_t pi = 0LL;
    while (pi < patch_count) {
    if (ArrayList_Int_get(&(patch_lines_arr), pi) == line_num3) {
    found_patch = true;
    modified_source = concatAlloc(modified_source, ArrayList_Str_get(&(patch_new_arr), pi));
}
    pi = (pi + 1LL);
}
    if (!found_patch) {
    modified_source = concatAlloc(modified_source, line_text);
}
    offset = (line_end + 1LL);
    if (offset > src_len_val) {
    break;
}
    modified_source = concatAlloc(modified_source, "\n");
    line_num3 = (line_num3 + 1LL);
}
    Result_Bool_IoError write_res = write_string(fix_file, modified_source);
    if (write_res.tag == 0LL) {
    applied = true;
}
}
    print_patch(fix_file, json, is_apply, applied, &(diag_codes), &(diag_messages), &(diag_lines), &(diag_columns), &(diag_lengths), &(diag_expected), &(diag_actual), &(diag_help), &(patch_lines_arr), &(patch_old_arr), &(patch_new_arr), &(patch_codes_arr));
    if ((is_apply && can_apply) && (!applied)) {
    return 1LL;
}
    return 0LL;
}
    printf("Error: fix requires a mode (--plan, --patch, or --apply)\n");
    return 1LL;
}
ErrorInfo get_error_info(const char* code) {
    if (strcmp(code, "E0001") == 0) {
    return (ErrorInfo){ .code = code, .title = "Type mismatch in declaration", .description = "The declared type of a variable does not match the type of the initializer expression.", .fix = "Change the declared type to match the initializer, or change the initializer expression to produce the declared type." };
}
    if (strcmp(code, "E0002") == 0) {
    return (ErrorInfo){ .code = code, .title = "Type mismatch in assignment", .description = "The type of the value being assigned does not match the type of the target variable.", .fix = "Assign a value of the correct type, or change the variable's type." };
}
    if (strcmp(code, "E0003") == 0) {
    return (ErrorInfo){ .code = code, .title = "Argument type mismatch", .description = "A function or method call argument type does not match the parameter type.", .fix = "Pass an argument of the expected type, or cast it using the 'as' operator if appropriate." };
}
    if (strcmp(code, "E0004") == 0) {
    return (ErrorInfo){ .code = code, .title = "Field type mismatch in struct initializer", .description = "A struct field initializer value type does not match the field's declared type.", .fix = "Provide a value of the correct type for the field, or change the field's type in the struct definition." };
}
    if (strcmp(code, "E0005") == 0) {
    return (ErrorInfo){ .code = code, .title = "Argument count mismatch in function call", .description = "The number of arguments provided in a function call does not match the function's parameter count.", .fix = "Add or remove arguments to match the function signature." };
}
    if (strcmp(code, "E0006") == 0) {
    return (ErrorInfo){ .code = code, .title = "Argument count mismatch in method call", .description = "The number of arguments provided in a method call does not match the method's parameter count.", .fix = "Add or remove arguments to match the method signature." };
}
    if (strcmp(code, "E0007") == 0) {
    return (ErrorInfo){ .code = code, .title = "Return type mismatch", .description = "The type of the returned value does not match the function's declared return type.", .fix = "Return a value of the correct type, or change the function's return type declaration." };
}
    if (strcmp(code, "E0008") == 0) {
    return (ErrorInfo){ .code = code, .title = "Cannot assign to immutable variable", .description = "An immutable variable (declared with 'let') cannot be reassigned.", .fix = "Declare the variable with 'var' instead of 'let', or use a different variable." };
}
    if (strcmp(code, "E0009") == 0) {
    return (ErrorInfo){ .code = code, .title = "Use of moved value", .description = "A value has been moved and cannot be used again. In Kai, non-copy types are moved on assignment or function call.", .fix = "Clone the value before moving it, or restructure the code to avoid using the value after the move." };
}
    if (strcmp(code, "E0010") == 0) {
    return (ErrorInfo){ .code = code, .title = "Cannot return reference to local variable", .description = "Returning a reference to a local variable would create a dangling pointer, since the local is destroyed when the function returns.", .fix = "Return the value by value instead of by reference, or ensure the referenced data outlives the function." };
}
    if (strcmp(code, "E0011") == 0) {
    return (ErrorInfo){ .code = code, .title = "Field access on optional type", .description = "Cannot directly access a field on an optional type. The optional must be unwrapped first.", .fix = "Use 'catch' with a fallback to unwrap the optional, then access the field." };
}
    if (strcmp(code, "E0012") == 0) {
    return (ErrorInfo){ .code = code, .title = "Method call on optional type", .description = "Cannot call a method directly on an optional type. The optional must be unwrapped first.", .fix = "Use 'catch' with a fallback to unwrap the optional, then call the method." };
}
    if (strcmp(code, "E0013") == 0) {
    return (ErrorInfo){ .code = code, .title = "Field does not exist in struct", .description = "The specified field name does not exist in the struct definition.", .fix = "Check the spelling of the field name, or add the field to the struct definition." };
}
    if (strcmp(code, "E0014") == 0) {
    return (ErrorInfo){ .code = code, .title = "Cannot use 'try' on non-error-union type", .description = "The 'try' operator can only be used on error union types (T!E), not on regular types.", .fix = "Ensure the expression has an error union type, or handle errors differently." };
}
    if (strcmp(code, "E0015") == 0) {
    return (ErrorInfo){ .code = code, .title = "Cannot use 'try' in non-error-returning function", .description = "The 'try' operator can only be used inside functions that return an error union type.", .fix = "Change the function's return type to an error union, or use 'catch' instead of 'try'." };
}
    if (strcmp(code, "E0016") == 0) {
    return (ErrorInfo){ .code = code, .title = "Error set mismatch in 'try'", .description = "The error set of the 'try' expression is not compatible with the function's error return type.", .fix = "Ensure the error types are compatible, or convert between error sets." };
}
    if (strcmp(code, "E0017") == 0) {
    return (ErrorInfo){ .code = code, .title = "Cannot use 'catch' on non-optional, non-error-union type", .description = "The 'catch' operator requires an optional or error union type.", .fix = "Ensure the expression is an optional or error union type before using 'catch'." };
}
    if (strcmp(code, "E0018") == 0) {
    return (ErrorInfo){ .code = code, .title = "Catch fallback type mismatch", .description = "The type of the 'catch' fallback expression does not match the expected unwrapped type.", .fix = "Change the fallback expression to produce the correct type." };
}
    if (strcmp(code, "E0019") == 0) {
    return (ErrorInfo){ .code = code, .title = "Undefined identifier", .description = "An identifier was used but not declared in the current scope or any parent scope.", .fix = "Declare the identifier before use, check the spelling, or import it from the appropriate module." };
}
    if (strcmp(code, "E0020") == 0) {
    return (ErrorInfo){ .code = code, .title = "Undefined function", .description = "A function was called but not declared or imported in the current scope.", .fix = "Declare the function with 'fn', declare it as 'extern fn', or import it from the appropriate module. Check the spelling." };
}
    if (strcmp(code, "E0021") == 0) {
    return (ErrorInfo){ .code = code, .title = "Undefined struct", .description = "A struct type was used but not declared in the current compilation unit.", .fix = "Define the struct with 'struct', import it, or check the spelling of the struct name." };
}
    if (strcmp(code, "E0022") == 0) {
    return (ErrorInfo){ .code = code, .title = "Undefined method", .description = "A method was called on a type that does not have that method in any 'impl' block.", .fix = "Add an 'impl' block with the method, check the spelling of the method name, or check the receiver type." };
}
    if (strcmp(code, "E0031") == 0) {
    return (ErrorInfo){ .code = code, .title = "Use of freed value", .description = "A value was used after it had been freed. Memory-safe languages prevent accessing freed memory.", .fix = "Restructure the code to avoid using the value after it has been freed. Consider using a longer-lived allocation or deferring the free operation." };
}
    if (strcmp(code, "E0032") == 0) {
    return (ErrorInfo){ .code = code, .title = "Double free", .description = "A value was freed more than once. Freeing the same memory twice can lead to heap corruption and security vulnerabilities.", .fix = "Ensure each allocation is freed exactly once. Remove the duplicate free call, or use a flag to track whether the value has already been freed." };
}
    if (strcmp(code, "E0033") == 0) {
    return (ErrorInfo){ .code = code, .title = "Unused import", .description = "An imported symbol was never used in the current compilation unit.", .fix = "Remove the unused import, or use the imported symbol in the code." };
}
    if (strcmp(code, "E0034") == 0) {
    return (ErrorInfo){ .code = code, .title = "Import resolution error", .description = "The import resolver could not find or load the specified module. This can happen when the module file doesn't exist, contains syntax errors, or creates a circular dependency.", .fix = "Check that the module path is correct, the file exists, and the module doesn't circularly import itself. Verify the file's syntax is valid." };
}
    if (strcmp(code, "E0100") == 0) {
    return (ErrorInfo){ .code = code, .title = "Lexer error", .description = "The lexer encountered an unexpected character or syntax that could not be tokenized.", .fix = "Check for unexpected characters, unclosed strings, or invalid syntax near the reported position." };
}
    if (strcmp(code, "E0101") == 0) {
    return (ErrorInfo){ .code = code, .title = "Parser error", .description = "The parser encountered a token that does not match the expected grammar rule.", .fix = "Check the syntax near the reported position. Common causes: missing semicolons, unmatched brackets, or incorrect keyword usage." };
}
    return (ErrorInfo){ .code = code, .title = "Unknown error code", .description = "No additional information is available for this error code.", .fix = "Refer to the Kai language documentation for more information." };
}
bool __kai_std_ascii_is_digit(char byte) {
    return ((byte >= ((char)(48LL))) && (byte <= ((char)(57LL))));
}
bool __kai_std_ascii_is_lower(char byte) {
    return ((byte >= ((char)(97LL))) && (byte <= ((char)(122LL))));
}
bool __kai_std_ascii_is_upper(char byte) {
    return ((byte >= ((char)(65LL))) && (byte <= ((char)(90LL))));
}
bool __kai_std_ascii_is_alpha(char byte) {
    return (__kai_std_ascii_is_lower(byte) || __kai_std_ascii_is_upper(byte));
}
bool __kai_std_ascii_is_alnum(char byte) {
    return (__kai_std_ascii_is_alpha(byte) || __kai_std_ascii_is_digit(byte));
}
bool __kai_std_ascii_is_whitespace(char byte) {
    return ((((byte == ((char)(32LL))) || (byte == ((char)(9LL)))) || (byte == ((char)(10LL)))) || (byte == ((char)(13LL))));
}
bool __kai_std_ascii_is_hex_digit(char byte) {
    return ((__kai_std_ascii_is_digit(byte) || ((byte >= ((char)(65LL))) && (byte <= ((char)(70LL))))) || ((byte >= ((char)(97LL))) && (byte <= ((char)(102LL)))));
}
char __kai_std_ascii_to_lower(char byte) {
    if (__kai_std_ascii_is_upper(byte)) {
    return (byte + ((char)(32LL)));
}
    return byte;
}
char __kai_std_ascii_to_upper(char byte) {
    if (__kai_std_ascii_is_lower(byte)) {
    return (byte - ((char)(32LL)));
}
    return byte;
}
Optional_Char __kai_std_ascii_digit_value(char byte) {
    if (__kai_std_ascii_is_digit(byte)) {
    return (Optional_Char){ .has_value = true, .value = (byte - ((char)(48LL))) };
}
    return (Optional_Char){0};
}
Optional_Char __kai_std_ascii_hex_value(char byte) {
    if (__kai_std_ascii_is_digit(byte)) {
    return (Optional_Char){ .has_value = true, .value = (byte - ((char)(48LL))) };
}
    if ((byte >= ((char)(65LL))) && (byte <= ((char)(70LL)))) {
    return (Optional_Char){ .has_value = true, .value = (byte - ((char)(55LL))) };
}
    if ((byte >= ((char)(97LL))) && (byte <= ((char)(102LL)))) {
    return (Optional_Char){ .has_value = true, .value = (byte - ((char)(87LL))) };
}
    return (Optional_Char){0};
}
int64_t diag_clamp_offset(const char* bytes, int64_t offset) {
    if (offset > strlen((const char*)(bytes))) {
    return strlen((const char*)(bytes));
}
    return offset;
}
int64_t diag_line_start(const char* bytes, int64_t offset) {
    int64_t cursor = diag_clamp_offset(bytes, offset);
    int64_t start = cursor;
    while ((start > 0LL) && ((bytes)[(start - 1LL)] != ((char)(10LL)))) {
    start = (start - 1LL);
}
    return start;
}
int64_t diag_line_end(const char* bytes, int64_t offset) {
    int64_t end = diag_clamp_offset(bytes, offset);
    while ((end < strlen((const char*)(bytes))) && ((bytes)[end] != ((char)(10LL)))) {
    end = (end + 1LL);
}
    if ((end > 0LL) && ((bytes)[(end - 1LL)] == ((char)(13LL)))) {
    return (end - 1LL);
}
    return end;
}
int64_t diag_line(const char* bytes, int64_t offset) {
    int64_t cursor = diag_clamp_offset(bytes, offset);
    int64_t line = 1LL;
    int64_t index = 0LL;
    while (index < cursor) {
    if ((bytes)[index] == ((char)(10LL))) {
    line = (line + 1LL);
}
    index = (index + 1LL);
}
    return line;
}
int64_t diag_column(const char* bytes, int64_t offset) {
    int64_t cursor = diag_clamp_offset(bytes, offset);
    int64_t start = diag_line_start(bytes, cursor);
    return ((cursor - start) + 1LL);
}
const char* diag_line_text(const char* bytes, int64_t offset) {
    int64_t start = diag_line_start(bytes, offset);
    int64_t end = diag_line_end(bytes, offset);
    return substring(bytes, start, end);
}
int64_t diag_range_len(const char* bytes, int64_t start, int64_t end) {
    int64_t first = diag_clamp_offset(bytes, start);
    int64_t last = diag_clamp_offset(bytes, end);
    if (last < first) {
    return 0LL;
}
    return (last - first);
}
const char* diag_range_text(const char* bytes, int64_t start, int64_t end) {
    int64_t first = diag_clamp_offset(bytes, start);
    int64_t last = diag_clamp_offset(bytes, end);
    if (last < first) {
    return substring(bytes, first, first);
}
    return substring(bytes, first, last);
}
Optional_Int diag_write_span(char* buffer, int64_t offset, const char* bytes) {
    if (offset > 1000000LL) {
    return (Optional_Int){0};
}
    if (strlen((const char*)(bytes)) > (1000000LL - offset)) {
    return (Optional_Int){0};
}
    int64_t index = 0LL;
    while (index < strlen((const char*)(bytes))) {
    (buffer)[(offset + index)] = (bytes)[index];
    index = (index + 1LL);
}
    return (Optional_Int){ .has_value = true, .value = (offset + strlen((const char*)(bytes))) };
}
Optional_Int diag_write_usize(char* buffer, int64_t offset, int64_t value) {
    if (offset > 1000000LL) {
    return (Optional_Int){0};
}
    int64_t digits = 1LL;
    int64_t scan = value;
    while (scan >= 10LL) {
    digits = (digits + 1LL);
    scan = (scan / 10LL);
}
    if ((offset + digits) > 1000000LL) {
    return (Optional_Int){0};
}
    int64_t cursor = (offset + digits);
    int64_t current = value;
    while (cursor > offset) {
    cursor = (cursor - 1LL);
    char digit = (char)((current % 10LL));
    (buffer)[cursor] = (((char)(48LL)) + digit);
    current = (current / 10LL);
}
    return (Optional_Int){ .has_value = true, .value = (offset + digits) };
}
const char* diag_format_location(char* buffer, const char* path, int64_t line, int64_t column) {
    int64_t offset = 0LL;
    Optional_Int wrote_path = diag_write_span(buffer, offset, path);
    if (!wrote_path.has_value) {
    return NULL;
}
    offset = ({ Optional_Int _kai_opt = (wrote_path); int64_t _kai_cv; if (_kai_opt.has_value) { _kai_cv = _kai_opt.value; } else { _kai_cv = (0LL); } _kai_cv; });
    Optional_Int first_colon = diag_write_span(buffer, offset, ":");
    if (!first_colon.has_value) {
    return NULL;
}
    offset = ({ Optional_Int _kai_opt = (first_colon); int64_t _kai_cv; if (_kai_opt.has_value) { _kai_cv = _kai_opt.value; } else { _kai_cv = (0LL); } _kai_cv; });
    Optional_Int wrote_line = diag_write_usize(buffer, offset, line);
    if (!wrote_line.has_value) {
    return NULL;
}
    offset = ({ Optional_Int _kai_opt = (wrote_line); int64_t _kai_cv; if (_kai_opt.has_value) { _kai_cv = _kai_opt.value; } else { _kai_cv = (0LL); } _kai_cv; });
    Optional_Int second_colon = diag_write_span(buffer, offset, ":");
    if (!second_colon.has_value) {
    return NULL;
}
    offset = ({ Optional_Int _kai_opt = (second_colon); int64_t _kai_cv; if (_kai_opt.has_value) { _kai_cv = _kai_opt.value; } else { _kai_cv = (0LL); } _kai_cv; });
    Optional_Int wrote_column = diag_write_usize(buffer, offset, column);
    if (wrote_column.has_value) {
    return substring(buffer, 0LL, ({ Optional_Int _kai_opt = (wrote_column); int64_t _kai_cv; if (_kai_opt.has_value) { _kai_cv = _kai_opt.value; } else { _kai_cv = (0LL); } _kai_cv; }));
}
    return NULL;
}
const char* diag_format_offset_location(char* buffer, const char* path, const char* bytes, int64_t offset) {
    return diag_format_location(buffer, path, diag_line(bytes, offset), diag_column(bytes, offset));
}
int64_t run_patch(int64_t argc, char** argv) {
    if (argc < 4LL) {
    printf("Usage: kai patch <file> --op <operation> [args...]\n");
    printf("Operations:\n");
    printf("  addMain                    Append a main function\n");
    printf("  addFn <name>               Append a function stub\n");
    printf("  addParam <fn> <name> <type> Add a parameter to a function\n");
    printf("  upsertFunction <name> <ret> Update or create a function\n");
    printf("  appendStmt <text>          Append a statement\n");
    printf("  replaceText --old <t> --new <t>  Global text replacement\n");
    printf("  setConst <name> <value>    Change a const value\n");
    return 1LL;
}
    KaiAllocator allocator = KaiAllocator_new();
    const char* patch_file = "";
    const char* operation = "";
    const char* op_arg1 = "";
    const char* op_arg2 = "";
    bool json = false;
    int64_t i = 2LL;
    while (i < argc) {
    const char* arg = (const char*)((argv)[i]);
    {
    if (strcmp(arg, "--json") == 0LL) {
    json = true;
} else if (strcmp(arg, "--op") == 0LL) {
    if ((i + 1LL) < argc) {
    i = (i + 1LL);
    operation = (const char*)((argv)[i]);
}
} else if (strcmp(arg, "--old") == 0LL) {
    if ((i + 1LL) < argc) {
    i = (i + 1LL);
    op_arg1 = (const char*)((argv)[i]);
}
} else if (strcmp(arg, "--new") == 0LL) {
    if ((i + 1LL) < argc) {
    i = (i + 1LL);
    op_arg2 = (const char*)((argv)[i]);
}
} else if (strcmp(patch_file, "") == 0) {
    patch_file = arg;
}
}
    i = (i + 1LL);
}
    if (strlen(patch_file) == 0LL) {
    printf("Error: No input file specified\n");
    return 1LL;
}
    if (strlen(operation) == 0LL) {
    printf("Error: No operation specified (use --op)\n");
    return 1LL;
}
    Result_Str_IoError source_res = read_to_string(&(allocator), patch_file);
    if (source_res.tag != 0LL) {
    printf("Error: Could not read '%s'\n", patch_file);
    return 1LL;
}
    const char* source = (const char*)(source_res.value);
    const char* modified = "";
    const char* op_name = operation;
    {
    if (strcmp(op_name, "addMain") == 0LL) {
    modified = concatAlloc(source, "\nfn main() Int {\n    printf(\"hello\\n\")\n    return 0\n}\n");
} else if (strcmp(op_name, "addFn") == 0LL) {
    const char* fn_name = op_arg1;
    if (strlen(fn_name) == 0LL) {
    int64_t j = 3LL;
    while (j < argc) {
    {
    const char* a = (const char*)((argv)[j]);
    bool is_flag = ((((strcmp(a, "--op") == 0LL) || (strcmp(a, "--json") == 0LL)) || (strcmp(a, "--old") == 0LL)) || (strcmp(a, "--new") == 0LL));
    if ((((((!is_flag) && (strcmp(a, patch_file) != 0LL)) && (strcmp(a, "addMain") != 0LL)) && (strcmp(a, "addFn") != 0LL)) && (strcmp(a, "setConst") != 0LL)) && (strcmp(a, "replaceText") != 0LL)) {
    if (strcmp(fn_name, "") == 0) {
    fn_name = a;
}
}
}
    j = (j + 1LL);
}
}
    if (strlen(fn_name) == 0LL) {
    printf("Error: addFn requires a function name\n");
    printf("Usage: kai patch <file> --op addFn <name>\n");
    return 1LL;
}
    modified = concatAlloc(concatAlloc(concatAlloc(source, "\nfn "), fn_name), "() Void {\n\n}\n");
} else if (strcmp(op_name, "setConst") == 0LL) {
    const char* const_name = op_arg1;
    const char* const_val = op_arg2;
    if ((strlen(const_name) == 0LL) || (strlen(const_val) == 0LL)) {
    int64_t j = 3LL;
    while (j < argc) {
    {
    const char* a = (const char*)((argv)[j]);
    bool is_flag = ((((strcmp(a, "--op") == 0LL) || (strcmp(a, "--json") == 0LL)) || (strcmp(a, "--old") == 0LL)) || (strcmp(a, "--new") == 0LL));
    if ((((((!is_flag) && (strcmp(a, patch_file) != 0LL)) && (strcmp(a, "setConst") != 0LL)) && (strcmp(a, "addMain") != 0LL)) && (strcmp(a, "addFn") != 0LL)) && (strcmp(a, "replaceText") != 0LL)) {
    if (strcmp(const_name, "") == 0) {
    const_name = a;
} else if (strcmp(const_val, "") == 0) {
    const_val = a;
}
}
}
    j = (j + 1LL);
}
}
    if ((strlen(const_name) == 0LL) || (strlen(const_val) == 0LL)) {
    printf("Error: setConst requires <name> and <value>\n");
    printf("Usage: kai patch <file> --op setConst <name> <value>\n");
    return 1LL;
}
    const char* pattern = concatAlloc(concatAlloc("const ", const_name), " = ");
    int64_t pattern_len = strlen(pattern);
    int64_t src_len = strlen(source);
    bool found_const = false;
    int64_t pos_c = 0LL;
    while (pos_c <= (src_len - pattern_len)) {
    bool matched_c = true;
    int64_t j2 = 0LL;
    while (j2 < pattern_len) {
    {
    if ((source)[(pos_c + j2)] != (pattern)[j2]) {
    matched_c = false;
    break;
}
}
    j2 = (j2 + 1LL);
}
    if (matched_c) {
    int64_t end = (pos_c + pattern_len);
    while (end < src_len) {
    {
    char c = (source)[end];
    if ((c == ((char)(10LL))) || (c == ((char)(59LL)))) {
    break;
}
}
    end = (end + 1LL);
}
    const char* before = substring(source, 0LL, (pos_c + pattern_len));
    const char* after = substring(source, end, src_len);
    modified = concatAlloc(concatAlloc(before, const_val), after);
    found_const = true;
    break;
}
    pos_c = (pos_c + 1LL);
}
    if (!found_const) {
    printf("Error: const '%s' not found in '%s'\n", const_name, patch_file);
    return 1LL;
}
} else if (strcmp(op_name, "replaceText") == 0LL) {
    if (strlen(op_arg1) == 0LL) {
    printf("Error: replaceText requires --old <text>\n");
    return 1LL;
}
    if (strlen(op_arg2) == 0LL) {
    printf("Error: replaceText requires --new <text>\n");
    return 1LL;
}
    modified = str_replace(source, op_arg1, op_arg2);
} else if (strcmp(op_name, "addParam") == 0LL) {
    const char* fn_name = op_arg1;
    const char* param_name = op_arg2;
    const char* param_type = "";
    if ((strlen(fn_name) == 0LL) || (strlen(param_name) == 0LL)) {
    int64_t j = 3LL;
    while (j < argc) {
    {
    const char* a = (const char*)((argv)[j]);
    bool is_flag = ((strcmp(a, "--op") == 0LL) || (strcmp(a, "--json") == 0LL));
    if (((!is_flag) && (strcmp(a, patch_file) != 0LL)) && (strcmp(a, "addParam") != 0LL)) {
    if (strcmp(fn_name, "") == 0) {
    fn_name = a;
} else if (strcmp(param_name, "") == 0) {
    param_name = a;
} else if (strcmp(param_type, "") == 0) {
    param_type = a;
}
}
}
    j = (j + 1LL);
}
} else {
    int64_t j = 3LL;
    while (j < argc) {
    {
    const char* a = (const char*)((argv)[j]);
    bool is_flag = ((strcmp(a, "--op") == 0LL) || (strcmp(a, "--json") == 0LL));
    if (((((!is_flag) && (strcmp(a, patch_file) != 0LL)) && (strcmp(a, "addParam") != 0LL)) && (strcmp(a, fn_name) != 0LL)) && (strcmp(a, param_name) != 0LL)) {
    if (strcmp(param_type, "") == 0) {
    param_type = a;
}
}
}
    j = (j + 1LL);
}
}
    if ((strlen(fn_name) == 0LL) || (strlen(param_name) == 0LL)) {
    printf("Error: addParam requires <fn_name> <param_name> [param_type]\n");
    printf("Usage: kai patch <file> --op addParam <fn> <name> <type>\n");
    return 1LL;
}
    if (strlen(param_type) == 0LL) {
    param_type = "Int";
}
    const char* search = concatAlloc(concatAlloc("fn ", fn_name), "(");
    int64_t search_len = strlen(search);
    int64_t src_len = strlen(source);
    bool found_fn = false;
    int64_t pos = 0LL;
    while (pos <= (src_len - search_len)) {
    bool m = true;
    int64_t j2 = 0LL;
    while (j2 < search_len) {
    {
    if ((source)[(pos + j2)] != (search)[j2]) {
    m = false;
    break;
}
}
    j2 = (j2 + 1LL);
}
    if (m) {
    int64_t paren_end = (pos + search_len);
    int64_t depth = 1LL;
    while ((paren_end < src_len) && (depth > 0LL)) {
    {
    char c = (source)[paren_end];
    if (c == ((char)(40LL))) {
    depth = (depth + 1LL);
} else if (c == ((char)(41LL))) {
    depth = (depth - 1LL);
}
}
    paren_end = (paren_end + 1LL);
}
    int64_t insert_pos = (paren_end - 1LL);
    const char* prefix = substring(source, 0LL, insert_pos);
    const char* suffix = substring(source, insert_pos, src_len);
    const char* params_section = substring(source, (pos + search_len), (paren_end - 1LL));
    bool has_params = false;
    int64_t pi = 0LL;
    while (pi < strlen(params_section)) {
    char c = (params_section)[pi];
    if ((c != ((char)(32LL))) && (c != ((char)(9LL)))) {
    has_params = true;
    break;
}
    pi = (pi + 1LL);
}
    if (has_params) {
    modified = concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(prefix, ", "), param_name), ": "), param_type), suffix);
} else {
    modified = concatAlloc(concatAlloc(concatAlloc(concatAlloc(prefix, param_name), ": "), param_type), suffix);
}
    found_fn = true;
    break;
}
    pos = (pos + 1LL);
}
    if (!found_fn) {
    printf("Error: function '%s' not found in '%s'\n", fn_name, patch_file);
    return 1LL;
}
} else if (strcmp(op_name, "upsertFunction") == 0LL) {
    const char* fn_name = op_arg1;
    const char* ret_type = op_arg2;
    if ((strlen(fn_name) == 0LL) || (strlen(ret_type) == 0LL)) {
    int64_t j = 3LL;
    while (j < argc) {
    {
    const char* a = (const char*)((argv)[j]);
    bool is_flag = ((strcmp(a, "--op") == 0LL) || (strcmp(a, "--json") == 0LL));
    if (((!is_flag) && (strcmp(a, patch_file) != 0LL)) && (strcmp(a, "upsertFunction") != 0LL)) {
    if (strcmp(fn_name, "") == 0) {
    fn_name = a;
} else if (strcmp(ret_type, "") == 0) {
    ret_type = a;
}
}
}
    j = (j + 1LL);
}
}
    if (strlen(fn_name) == 0LL) {
    printf("Error: upsertFunction requires <name> [return_type]\n");
    printf("Usage: kai patch <file> --op upsertFunction <name> <return_type>\n");
    return 1LL;
}
    if (strlen(ret_type) == 0LL) {
    ret_type = "Void";
}
    const char* search = concatAlloc(concatAlloc("fn ", fn_name), "(");
    int64_t search_len = strlen(search);
    int64_t src_len = strlen(source);
    bool found_fn = false;
    int64_t pos = 0LL;
    while (pos <= (src_len - search_len)) {
    bool m = true;
    int64_t j2 = 0LL;
    while (j2 < search_len) {
    {
    if ((source)[(pos + j2)] != (search)[j2]) {
    m = false;
    break;
}
}
    j2 = (j2 + 1LL);
}
    if (m) {
    int64_t paren_end = (pos + search_len);
    int64_t depth = 1LL;
    while ((paren_end < src_len) && (depth > 0LL)) {
    {
    char c = (source)[paren_end];
    if (c == ((char)(40LL))) {
    depth = (depth + 1LL);
} else if (c == ((char)(41LL))) {
    depth = (depth - 1LL);
}
}
    paren_end = (paren_end + 1LL);
}
    int64_t ret_start = paren_end;
    while (ret_start < src_len) {
    {
    char c = (source)[ret_start];
    if ((c != ((char)(32LL))) && (c != ((char)(9LL)))) {
    break;
}
}
    ret_start = (ret_start + 1LL);
}
    int64_t ret_end = ret_start;
    while (ret_end < src_len) {
    {
    char c = (source)[ret_end];
    if ((((c == ((char)(32LL))) || (c == ((char)(9LL)))) || (c == ((char)(10LL)))) || (c == ((char)(123LL)))) {
    break;
}
}
    ret_end = (ret_end + 1LL);
}
    if (ret_end > ret_start) {
    const char* before = substring(source, 0LL, ret_start);
    const char* after = substring(source, ret_end, src_len);
    modified = concatAlloc(concatAlloc(before, ret_type), after);
} else {
    modified = source;
}
    found_fn = true;
    break;
}
    pos = (pos + 1LL);
}
    if (!found_fn) {
    modified = concatAlloc(concatAlloc(concatAlloc(concatAlloc(concatAlloc(source, "\nfn "), fn_name), "() "), ret_type), " {\n\n}\n");
}
} else if (strcmp(op_name, "appendStmt") == 0LL) {
    const char* stmt_text = op_arg1;
    if (strlen(stmt_text) == 0LL) {
    int64_t j = 3LL;
    while (j < argc) {
    {
    const char* a = (const char*)((argv)[j]);
    bool is_flag = ((strcmp(a, "--op") == 0LL) || (strcmp(a, "--json") == 0LL));
    if (((!is_flag) && (strcmp(a, patch_file) != 0LL)) && (strcmp(a, "appendStmt") != 0LL)) {
    if (strcmp(stmt_text, "") == 0) {
    stmt_text = a;
}
}
}
    j = (j + 1LL);
}
}
    if (strlen(stmt_text) == 0LL) {
    printf("Error: appendStmt requires <text>\n");
    return 1LL;
}
    modified = concatAlloc(concatAlloc(concatAlloc(source, "\n"), stmt_text), "\n");
} else {
    printf("Error: Unknown operation '%s'\n", op_name);
    printf("Supported: addMain, addFn, addParam, upsertFunction, appendStmt, setConst, replaceText\n");
    return 1LL;
}
}
    Result_Bool_IoError write_res = write_string(patch_file, modified);
    if (write_res.tag != 0LL) {
    printf("Error: Could not write '%s'\n", patch_file);
    return 1LL;
}
    if (json) {
    printf("{\"result\":\"patched\",\"file\":\"%s\",\"operation\":\"%s\"}\n", patch_file, op_name);
}
    return 0LL;
}
int64_t run_graph(int64_t argc, char** argv) {
    if (argc < 3LL) {
    printf("Usage: kai graph (export|query) <file> [options]\n");
    printf("  export <file>    Export AST as JSON\n");
    printf("  query <file>     Query program structure\n");
    return 1LL;
}
    const char* graph_sub = "";
    {
    graph_sub = (const char*)((argv)[2LL]);
}
    const char* graph_file = "";
    const char* graph_fn = "";
    bool graph_json = false;
    int64_t i3 = 3LL;
    while (i3 < argc) {
    {
    const char* a = (const char*)((argv)[i3]);
    if (strcmp(a, "--json") == 0LL) {
    graph_json = true;
} else if (strcmp(a, "--fn") == 0LL) {
    if ((i3 + 1LL) < argc) {
    i3 = (i3 + 1LL);
    graph_fn = (const char*)((argv)[i3]);
}
} else if (strcmp(graph_file, "") == 0) {
    graph_file = a;
}
}
    i3 = (i3 + 1LL);
}
    if (strlen(graph_file) == 0LL) {
    printf("Error: No input file specified\n");
    return 1LL;
}
    KaiAllocator graph_alloc = KaiAllocator_new();
    Result_Str_IoError src_res2 = read_to_string(&(graph_alloc), graph_file);
    if (src_res2.tag != 0LL) {
    printf("Error: Could not read '%s'\n", graph_file);
    return 1LL;
}
    const char* graph_source = (const char*)(src_res2.value);
    StringPool graph_pool = StringPool_init(&(graph_alloc));
    Lexer graph_lexer = Lexer_init(&(graph_alloc), graph_source, graph_file, &(graph_pool));
    Lexer_lex(&(graph_lexer));
    if (graph_lexer.has_error) {
    printf("Error: Lexer error in '%s'\n", graph_file);
    return 1LL;
}
    Parser graph_parser = Parser_init(&(graph_alloc), graph_file, graph_lexer.tokens, graph_source, &(graph_pool));
    int64_t graph_program_idx = Parser_parse_program(&(graph_parser));
    if (graph_program_idx < 0LL) {
    printf("Error: Parse error in '%s'\n", graph_file);
    return 1LL;
}
    {
    if (strcmp(graph_sub, "export") == 0LL) {
    printf("{\"file\":\"%s\",\"stmts\":[\n", graph_file);
    int64_t si = 0LL;
    int64_t stmt_count = ArrayList_StmtNode_length(graph_parser.stmt_pool);
    while (si < stmt_count) {
    StmtNode stmt = ArrayList_StmtNode_get(graph_parser.stmt_pool, si);
    if (si > 0LL) {
    printf(",\n");
}
    printf("{\"id\":%ld,\"kind\":", si);
    StmtKind sk = stmt.kind;
    if (sk == 0LL) {
    printf("\"none\"");
} else if (sk == 1LL) {
    printf("\"block\"");
} else if (sk == 2LL) {
    printf("\"var_decl\"");
} else if (sk == 3LL) {
    printf("\"assignment\"");
} else if (sk == 4LL) {
    printf("\"func_decl\"");
} else if (sk == 5LL) {
    printf("\"struct_decl\"");
} else if (sk == 6LL) {
    printf("\"impl_block\"");
} else if (sk == 7LL) {
    printf("\"trait_decl\"");
} else if (sk == 8LL) {
    printf("\"enum_decl\"");
} else if (sk == 9LL) {
    printf("\"if\"");
} else if (sk == 10LL) {
    printf("\"if_let\"");
} else if (sk == 11LL) {
    printf("\"while\"");
} else if (sk == 12LL) {
    printf("\"for\"");
} else if (sk == 13LL) {
    printf("\"return\"");
} else if (sk == 14LL) {
    printf("\"print\"");
} else if (sk == 15LL) {
    printf("\"expr\"");
} else if (sk == 16LL) {
    printf("\"defer\"");
} else if (sk == 17LL) {
    printf("\"unsafe\"");
} else if (sk == 18LL) {
    printf("\"extern\"");
} else if (sk == 19LL) {
    printf("\"import\"");
} else if (sk == 20LL) {
    printf("\"cimport\"");
} else if (sk == 21LL) {
    printf("\"match\"");
} else if (sk == 22LL) {
    printf("\"error_decl\"");
} else if (sk == 23LL) {
    printf("\"break\"");
} else if (sk == 24LL) {
    printf("\"continue\"");
} else {
    printf("\"unknown\"");
}
    if (strlen(stmt.func_name) > 0LL) {
    printf(",\"name\":\"%s\"", stmt.func_name);
}
    if (strlen(stmt.struct_name) > 0LL) {
    printf(",\"name\":\"%s\"", stmt.struct_name);
}
    if (strlen(stmt.enum_name) > 0LL) {
    printf(",\"name\":\"%s\"", stmt.enum_name);
}
    if (strlen(stmt.vardecl_name) > 0LL) {
    printf(",\"var\":\"%s\"", stmt.vardecl_name);
}
    if (strlen(stmt.vardecl_type) > 0LL) {
    printf(",\"type\":\"%s\"", stmt.vardecl_type);
}
    if (strlen(stmt.func_return_type) > 0LL) {
    printf(",\"return_type\":\"%s\"", stmt.func_return_type);
}
    printf("}");
    si = (si + 1LL);
}
    printf("],\n\"exprs\":[\n");
    int64_t ei = 0LL;
    int64_t expr_count = ArrayList_ExprNode_length(graph_parser.expr_pool);
    while (ei < expr_count) {
    ExprNode expr = ArrayList_ExprNode_get(graph_parser.expr_pool, ei);
    if (ei > 0LL) {
    printf(",\n");
}
    printf("{\"id\":%ld,\"kind\":", ei);
    ExprKind ek = expr.kind;
    if (ek == 0LL) {
    printf("\"none\"");
} else if (ek == 1LL) {
    printf("\"literal\"");
} else if (ek == 2LL) {
    printf("\"str_interp\"");
} else if (ek == 3LL) {
    printf("\"identifier\"");
} else if (ek == 4LL) {
    printf("\"binary_op\"");
} else if (ek == 5LL) {
    printf("\"unary_op\"");
} else if (ek == 6LL) {
    printf("\"func_call\"");
} else if (ek == 7LL) {
    printf("\"struct_init\"");
} else if (ek == 8LL) {
    printf("\"field_access\"");
} else if (ek == 9LL) {
    printf("\"method_call\"");
} else if (ek == 10LL) {
    printf("\"index\"");
} else if (ek == 11LL) {
    printf("\"check\"");
} else if (ek == 12LL) {
    printf("\"slice\"");
} else if (ek == 13LL) {
    printf("\"range\"");
} else if (ek == 14LL) {
    printf("\"array\"");
} else if (ek == 15LL) {
    printf("\"tuple\"");
} else if (ek == 16LL) {
    printf("\"borrow\"");
} else if (ek == 17LL) {
    printf("\"deref\"");
} else if (ek == 18LL) {
    printf("\"try\"");
} else if (ek == 19LL) {
    printf("\"catch\"");
} else if (ek == 20LL) {
    printf("\"asm\"");
} else {
    printf("\"unknown\"");
}
    if (strlen(expr.ident_name) > 0LL) {
    printf(",\"name\":\"%s\"", expr.ident_name);
}
    if (strlen(expr.func_name) > 0LL) {
    printf(",\"func\":\"%s\"", expr.func_name);
}
    if (strlen(expr.struct_name) > 0LL) {
    printf(",\"struct\":\"%s\"", expr.struct_name);
}
    if (strlen(expr.inferred_type) > 0LL) {
    printf(",\"type\":\"%s\"", expr.inferred_type);
}
    if (strlen(expr.binop_op) > 0LL) {
    printf(",\"op\":\"%s\"", expr.binop_op);
}
    if (strlen(expr.unop_op) > 0LL) {
    printf(",\"op\":\"%s\"", expr.unop_op);
}
    printf("}");
    ei = (ei + 1LL);
}
    printf("]}\n");
} else if (strcmp(graph_sub, "query") == 0LL) {
    if (strlen(graph_fn) > 0LL) {
    bool found = false;
    int64_t si2 = 0LL;
    int64_t stmt_count2 = ArrayList_StmtNode_length(graph_parser.stmt_pool);
    while (si2 < stmt_count2) {
    StmtNode stmt2 = ArrayList_StmtNode_get(graph_parser.stmt_pool, si2);
    if ((stmt2.kind == 4LL) && (strcmp(stmt2.func_name, graph_fn) == 0LL)) {
    printf("function: %s\n", stmt2.func_name);
    printf("  return: %s\n", stmt2.func_return_type);
    printf("  params: ");
    int64_t param_count = ArrayList_Param_length(&(stmt2.func_params));
    int64_t pi = 0LL;
    while (pi < param_count) {
    Param p = ArrayList_Param_get(&(stmt2.func_params), pi);
    printf("%s: %s", p.name, p.ptype);
    pi = (pi + 1LL);
    if (pi < param_count) {
    printf(", ");
}
}
    printf("\n");
    found = true;
}
    si2 = (si2 + 1LL);
}
    if (!found) {
    printf("function '%s' not found\n", graph_fn);
}
} else {
    StmtNode root = ArrayList_StmtNode_get(graph_parser.stmt_pool, graph_program_idx);
    printf("file: %s\n", graph_file);
    int64_t si3 = 0LL;
    while (si3 < ArrayList_Int_length(&(root.block_stmts))) {
    int64_t idx = ArrayList_Int_get(&(root.block_stmts), si3);
    StmtNode stmt3 = ArrayList_StmtNode_get(graph_parser.stmt_pool, idx);
    if (stmt3.kind == 4LL) {
    printf("  fn %s(%s) %s\n", stmt3.func_name, "", stmt3.func_return_type);
} else if (stmt3.kind == 5LL) {
    printf("  struct %s\n", stmt3.struct_name);
} else if (stmt3.kind == 8LL) {
    printf("  enum %s\n", stmt3.enum_name);
} else if (stmt3.kind == 22LL) {
    printf("  error %s\n", stmt3.error_name);
} else if (stmt3.kind == 2LL) {
    printf("  var %s: %s\n", stmt3.vardecl_name, stmt3.vardecl_type);
}
    si3 = (si3 + 1LL);
}
}
} else {
    printf("Error: Unknown graph subcommand '%s'\n", graph_sub);
    printf("Supported: export, query\n");
    return 1LL;
}
}
    return 0LL;
}
int64_t run_init(int64_t argc, char** argv) {
    const char* project_path = ".";
    const char* template = "cli";
    int64_t i = 2LL;
    while (i < argc) {
    const char* arg = (const char*)((argv)[i]);
    {
    if (strcmp(arg, "--template") == 0LL) {
    if ((i + 1LL) < argc) {
    i = (i + 1LL);
    template = (const char*)((argv)[i]);
} else {
    printf("Error: --template requires an argument (cli|lib)\n");
    return 1LL;
}
} else if (strcmp(project_path, ".") == 0) {
    project_path = arg;
}
}
    i = (i + 1LL);
}
    const char* src_dir = concatAlloc(project_path, "/src");
    if (!mkdir_p(src_dir)) {
    printf("Error: Could not create directory '%s'\n", src_dir);
    return 1LL;
}
    if (strcmp(template, "lib") == 0) {
    const char* main_content = concatAlloc(concatAlloc("// ", project_path), "\n// Library entry point\n\n");
    Result_Bool_IoError write_res = write_string(concatAlloc(src_dir, "/lib.kai"), main_content);
    if (write_res.tag != 0LL) {
    printf("Error: Could not write lib.kai\n");
    return 1LL;
}
} else {
    const char* main_content = concatAlloc(concatAlloc(concatAlloc(concatAlloc("// ", project_path), "\n// Imports\nimport std.io.print\n\n// Entry point\n\nfn main() Int {\n    printf(\"Hello! from "), project_path), "\\n\")\n    return 0\n}\n");
    Result_Bool_IoError write_res = write_string(concatAlloc(src_dir, "/main.kai"), main_content);
    if (write_res.tag != 0LL) {
    printf("Error: Could not write main.kai\n");
    return 1LL;
}
}
    printf("Created Kai project at '%s' (template: %s)\n", project_path, template);
    return 0LL;
}
int64_t run_skills(int64_t argc, char** argv) {
    KaiAllocator allocator = KaiAllocator_new();
    const char* exe_dir = "";
    {
    char* buf = (char*)(KaiAllocator_alloc(&(allocator), 1024LL, 1LL));
    if (get_exe_dir(buf, 1024LL) == 0LL) {
    exe_dir = (const char*)(buf);
}
}
    if (argc < 3LL) {
    printf("Available skills:\n");
    printf("  agent       - Agent workflow guide\n");
    printf("  diagnostics - Diagnostic reference for AI agents\n");
    printf("\nUse 'kai skills get <topic>' to load a skill.\n");
    return 0LL;
}
    const char* sub = "";
    {
    sub = (const char*)((argv)[2LL]);
}
    bool is_get = false;
    {
    if (strcmp(sub, "get") == 0LL) {
    is_get = true;
}
}
    if (is_get) {
    if (argc < 4LL) {
    printf("Usage: kai skills get <topic>\n");
    return 1LL;
}
    const char* topic = "";
    {
    topic = (const char*)((argv)[3LL]);
}
    const char* skill_path = concatAlloc(concatAlloc(concatAlloc(exe_dir, "/skill-data/"), topic), ".md");
    Result_Str_IoError res = read_to_string(&(allocator), skill_path);
    if (res.tag != 0LL) {
    printf("skill not found: '%s'\n", topic);
    printf("Available: agent, diagnostics\n");
    return 1LL;
}
    const char* content = (const char*)(res.value);
    printf("%s\n", content);
    return 0LL;
}
    printf("Usage: kai skills get <topic>\n");
    return 1LL;
}
int64_t run_explain(int64_t argc, char** argv) {
    if (argc < 3LL) {
    printf("Usage: kai explain <error-code>\n");
    return 1LL;
}
    const char* code = "";
    {
    code = (const char*)((argv)[2LL]);
}
    ErrorInfo info = get_error_info(code);
    printf("error[%s]: %s\n", code, info.title);
    printf("  %s\n", info.description);
    printf("  Suggested fix: %s\n", info.fix);
    return 0LL;
}
int64_t run_build(int64_t argc, char** argv) {
    KaiAllocator allocator = KaiAllocator_new();
    Result_Str_IoError s = read_to_string(&(allocator), "build.kai");
    if (s.tag != 0LL) {
    printf("Error: build.kai not found in the current directory.\n");
    return 1LL;
}
    const char* compiler_path = "kai";
    {
    compiler_path = (const char*)((argv)[0LL]);
}
    const char* wrapper_code = concatAlloc(concatAlloc("import Builder from std.build\nimport build from build\nimport concatAlloc from std.lib.str\n\nfn main(argc: Int, argv: **Char) Int {\n    var allocator = KaiAllocator_new()\n    var b = Builder(&allocator, argc, argv)\n    b.compiler_path = \"", compiler_path), "\"\n    build(&b as *Builder)\n    if !b.run() {\n        return 1\n    }\n    return 0\n}\n");
    Result_Bool_IoError write_res = write_string("_build_wrapper.kai", wrapper_code);
    if (write_res.tag != 0LL) {
    printf("Error: Could not write temporary build wrapper.\n");
    return 1LL;
}
    const char* compile_cmd = concatAlloc(compiler_path, " _build_wrapper.kai -o _build_wrapper");
    {
    int64_t status = system((char*)(compile_cmd));
    if (status != 0LL) {
    printf("Error: Failed to compile build.kai wrapper.\n");
    system((char*)("rm -f _build_wrapper.kai _build_wrapper.c CC_build_wrapper.c _build_wrapper CC_build_wrapper"));
    return status;
}
}
    const char* run_cmd = "./_build_wrapper";
    int64_t i = 2LL;
    while (i < argc) {
    {
    run_cmd = concatAlloc(concatAlloc(run_cmd, " "), (const char*)((argv)[i]));
}
    i = (i + 1LL);
}
    int64_t run_status = 0LL;
    {
    run_status = system((char*)(run_cmd));
}
    {
    system((char*)("rm -f _build_wrapper.kai _build_wrapper.c CC_build_wrapper.c _build_wrapper CC_build_wrapper"));
}
    return run_status;
}
