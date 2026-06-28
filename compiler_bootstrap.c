#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <ctype.h>

static inline void print_int(int64_t i) { printf("%lld\n", (long long)i); }

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
typedef struct Result_Str_Int Result_Str_Int;
typedef enum {
    Result_Str_Int_ok_TAG,
    Result_Str_Int_err_TAG,
} Result_Str_Int_tags;
struct Result_Str_Int {
    uint8_t tag;
    union {
        struct {
            const char* value;
        } ok;
        struct {
            int64_t value;
        } err;
    } payload;
};
typedef struct Result_Bool_Int Result_Bool_Int;
typedef enum {
    Result_Bool_Int_ok_TAG,
    Result_Bool_Int_err_TAG,
} Result_Bool_Int_tags;
struct Result_Bool_Int {
    uint8_t tag;
    union {
        struct {
            bool value;
        } ok;
        struct {
            int64_t value;
        } err;
    } payload;
};
typedef struct StringBuilder StringBuilder;
struct StringBuilder {
    char* data;
    int64_t len;
    int64_t cap;
    KaiAllocator* allocator;
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
    TokenType_PRINT,
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
            const char* v;
        } tv_str;
    } payload;
};
typedef struct Token Token;
struct Token {
    TokenType tok_type;
    TokenValue value;
    int64_t line;
    int64_t column;
};
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
typedef struct Lexer Lexer;
struct Lexer {
    KaiAllocator* allocator;
    const char* source;
    int64_t source_len;
    int64_t cursor;
    int64_t line;
    int64_t column;
    ArrayList_Token* tokens;
    ArrayList_Int* indent_stack;
    int64_t paren_depth;
    int64_t brace_depth;
    bool has_error;
};
typedef struct DropVarEntry DropVarEntry;
struct DropVarEntry {
    const char* name;
    const char* base_type;
};
typedef struct FieldInit FieldInit;
struct FieldInit {
    const char* name;
    int64_t value;
};
typedef struct Param Param;
struct Param {
    const char* name;
    const char* ptype;
};
typedef struct StructField StructField;
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
typedef struct Variant Variant;
struct Variant {
    const char* vname;
    ArrayList_Param params;
};
typedef struct MatchCase MatchCase;
struct MatchCase {
    int64_t pattern;
    int64_t body;
};
typedef struct StrInterpPart StrInterpPart;
struct StrInterpPart {
    int64_t kind;
    const char* str_val;
    int64_t expr_idx;
};
typedef struct AsmOutput AsmOutput;
struct AsmOutput {
    const char* name;
    const char* constraint;
    const char* type_name;
    int64_t expr_idx;
};
typedef struct AsmInput AsmInput;
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
typedef struct PatternNode PatternNode;
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
typedef struct ExprNode ExprNode;
struct ExprNode {
    ExprKind kind;
    const char* inferred_type;
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
typedef struct StmtNode StmtNode;
struct StmtNode {
    StmtKind kind;
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
typedef struct Parser Parser;
struct Parser {
    KaiAllocator* allocator;
    ArrayList_Token* tokens;
    int64_t cursor;
    bool pending_gt;
    int64_t pending_gt_line;
    int64_t pending_gt_col;
    ArrayList_ExprNode* expr_pool;
    ArrayList_StmtNode* stmt_pool;
    ArrayList_PatternNode* pattern_pool;
};
typedef struct Symbol Symbol;
struct Symbol {
    const char* name;
    const char* type_name;
    bool is_mutable;
    const char* kind;
    const char* llvm_value;
    bool moved;
};
typedef struct ArrayList_Symbol ArrayList_Symbol;
struct ArrayList_Symbol {
    Symbol* data;
    int64_t len;
    int64_t cap;
    KaiAllocator* allocator;
};
typedef struct SymbolTable SymbolTable;
struct SymbolTable {
    ArrayList_Symbol entries;
    int64_t parent_idx;
    KaiAllocator* allocator;
};
typedef struct ArrayList_SymbolTable ArrayList_SymbolTable;
struct ArrayList_SymbolTable {
    SymbolTable* data;
    int64_t len;
    int64_t cap;
    KaiAllocator* allocator;
};
typedef struct PtrRefResult PtrRefResult;
struct PtrRefResult {
    bool is_ptr;
    bool is_mut;
    const char* inner;
};
typedef struct StructInfo StructInfo;
struct StructInfo {
    const char* name;
    bool has_drop;
};
typedef struct ArrayList_StructInfo ArrayList_StructInfo;
struct ArrayList_StructInfo {
    StructInfo* data;
    int64_t len;
    int64_t cap;
    KaiAllocator* allocator;
};
typedef struct TypeChecker TypeChecker;
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
};
typedef struct StrMapEntry StrMapEntry;
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
typedef struct Codegen Codegen;
struct Codegen {
    KaiAllocator* allocator;
    ArrayList_StmtNode* stmt_pool;
    ArrayList_ExprNode* expr_pool;
    ArrayList_PatternNode* pattern_pool;
    StringBuilder output;
    StringBuilder struct_decls;
    StringBuilder func_decls;
    const char* cur_func_name;
    const char* cur_return_type;
    bool cur_method_is_init;
    ArrayList_StrMapEntry func_types;
    ArrayList_StrMapEntry var_types;
    ArrayList_Str loaded_modules;
    ArrayList_Str cimport_headers;
    ArrayList_Int block_stack;
    ArrayList_StrMapEntry generic_struct_decls;
    ArrayList_StrMapEntry generic_enum_decls;
    ArrayList_StrMapEntry generic_func_decls;
    ArrayList_StrMapEntry generic_impl_blocks;
    ArrayList_Str monomorphized_types;
    ArrayList_StrMapEntry current_type_map;
    ArrayList_StrMapEntry enum_decls;
    ArrayList_Str result_definitions;
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
bool Result_Str_Int_is_ok(Result_Str_Int* self);
bool Result_Str_Int_is_err(Result_Str_Int* self);
const char* Result_Str_Int_unwrap(Result_Str_Int* self);
Result_Str_Int read_to_string(KaiAllocator* allocator, const char* path);
bool Result_Bool_Int_is_ok(Result_Bool_Int* self);
bool Result_Bool_Int_is_err(Result_Bool_Int* self);
bool Result_Bool_Int_unwrap(Result_Bool_Int* self);
Result_Bool_Int write_string(const char* path, const char* content);
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
TokenType keyword_type(const char* ident);
TokenValue make_keyword_value(const char* ident, TokenType ttype);
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
Lexer Lexer_init(KaiAllocator* allocator, const char* source);
char Lexer_peek(Lexer* self, int64_t offset);
char Lexer_advance(Lexer* self);
void Lexer_emit(Lexer* self, TokenType ttype, TokenValue value);
void Lexer_lex_error(Lexer* self);
void Lexer_skip_line_comment(Lexer* self);
void Lexer_skip_block_comment(Lexer* self);
void Lexer_skip_whitespace(Lexer* self);
void Lexer_lex_identifier(Lexer* self);
void Lexer_lex_number(Lexer* self);
void Lexer_lex_string(Lexer* self);
void Lexer_lex_char(Lexer* self);
int64_t Lexer_compute_indent(Lexer* self);
void Lexer_lex(Lexer* self);
extern void print(const char* s);
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
ExprNode new_expr_node(ExprKind kind);
StmtNode new_stmt_node(StmtKind kind);
PatternNode new_pattern_node(PatternKind kind);
const char* tv_get_str(TokenValue val);
int64_t token_precedence(TokenType ttype);
const char* token_op_str(TokenType ttype);
const char* str_array_join(ArrayList_Str arr, const char* sep);
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
Parser Parser_init_with_pools(KaiAllocator* allocator, ArrayList_Token* tokens, ArrayList_ExprNode* expr_pool, ArrayList_StmtNode* stmt_pool, ArrayList_PatternNode* pattern_pool);
Parser Parser_init(KaiAllocator* allocator, ArrayList_Token* tokens);
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
int64_t Parser_st_print(Parser* self, int64_t value);
int64_t Parser_st_expr(Parser* self, int64_t expr);
int64_t Parser_st_defer(Parser* self, int64_t body);
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
int64_t Parser_parse_print_stmt(Parser* self);
int64_t Parser_parse_defer_stmt(Parser* self);
int64_t Parser_parse_expr_or_assignment_stmt(Parser* self);
int64_t Parser_parse_block(Parser* self);
int64_t Parser_parse_import_stmt(Parser* self);
int64_t Parser_parse_import_stmt_new(Parser* self);
int64_t Parser_parse_cimport_stmt(Parser* self);
int64_t Parser_parse_expression(Parser* self, int64_t precedence);
int64_t Parser_parse_primary(Parser* self);
ArrayList_Symbol ArrayList_Symbol_init(KaiAllocator* allocator);
void ArrayList_Symbol_push(ArrayList_Symbol* self, Symbol item);
Symbol ArrayList_Symbol_get(ArrayList_Symbol* self, int64_t index);
void ArrayList_Symbol_set(ArrayList_Symbol* self, int64_t index, Symbol item);
Symbol ArrayList_Symbol_pop(ArrayList_Symbol* self);
int64_t ArrayList_Symbol_length(ArrayList_Symbol* self);
void ArrayList_Symbol_deinit(ArrayList_Symbol* self);
SymbolTable SymbolTable_init(KaiAllocator* allocator, int64_t parent_idx);
void SymbolTable_define(SymbolTable* self, const char* name, const char* type_name, bool is_mutable, const char* kind, const char* llvm_value);
ArrayList_SymbolTable ArrayList_SymbolTable_init(KaiAllocator* allocator);
void ArrayList_SymbolTable_push(ArrayList_SymbolTable* self, SymbolTable item);
SymbolTable ArrayList_SymbolTable_get(ArrayList_SymbolTable* self, int64_t index);
void ArrayList_SymbolTable_set(ArrayList_SymbolTable* self, int64_t index, SymbolTable item);
SymbolTable ArrayList_SymbolTable_pop(ArrayList_SymbolTable* self);
int64_t ArrayList_SymbolTable_length(ArrayList_SymbolTable* self);
void ArrayList_SymbolTable_deinit(ArrayList_SymbolTable* self);
int64_t SymbolTable_lookup(SymbolTable* self, const char* name, ArrayList_SymbolTable* tables);
Symbol SymbolTable_lookup_symbol(SymbolTable* self, const char* name, ArrayList_SymbolTable* tables);
void SymbolTable_mark_moved(SymbolTable* self, const char* name, ArrayList_SymbolTable* tables);
int64_t SymbolTable_lookup_current(SymbolTable* self, const char* name);
ArrayList_StructInfo ArrayList_StructInfo_init(KaiAllocator* allocator);
void ArrayList_StructInfo_push(ArrayList_StructInfo* self, StructInfo item);
StructInfo ArrayList_StructInfo_get(ArrayList_StructInfo* self, int64_t index);
void ArrayList_StructInfo_set(ArrayList_StructInfo* self, int64_t index, StructInfo item);
StructInfo ArrayList_StructInfo_pop(ArrayList_StructInfo* self);
int64_t ArrayList_StructInfo_length(ArrayList_StructInfo* self);
void ArrayList_StructInfo_deinit(ArrayList_StructInfo* self);
TypeChecker TypeChecker_init(KaiAllocator* allocator, ArrayList_StmtNode* stmt_pool, ArrayList_ExprNode* expr_pool, ArrayList_PatternNode* pattern_pool);
void TypeChecker_enter_scope(TypeChecker* self);
void TypeChecker_exit_scope(TypeChecker* self);
void TypeChecker_define_symbol(TypeChecker* self, const char* name, const char* type_name, bool is_mutable, const char* kind);
bool TypeChecker_check_program(TypeChecker* self, int64_t top_stmt_idx);
void TypeChecker_register_struct_info(TypeChecker* self, int64_t top_stmt_idx);
bool TypeChecker_has_drop_method(TypeChecker* self, const char* type_name);
void TypeChecker_collect_block_drops(TypeChecker* self, int64_t stmt_idx);
bool TypeChecker_is_copy_type(TypeChecker* self, const char* type_name);
PtrRefResult TypeChecker_parse_ptr_ref(TypeChecker* self, const char* type_str);
bool TypeChecker_types_compatible(TypeChecker* self, const char* target, const char* source);
int64_t TypeChecker_find_func_decl(TypeChecker* self, const char* name);
int64_t TypeChecker_find_method_decl(TypeChecker* self, const char* struct_name, const char* meth_name);
int64_t TypeChecker_find_struct_decl(TypeChecker* self, const char* name);
const char* TypeChecker_get_block_yield_type(TypeChecker* self, int64_t stmt_idx);
void TypeChecker_mark_expr_moved(TypeChecker* self, int64_t expr_idx);
const char* TypeChecker_get_expr_type(TypeChecker* self, int64_t expr_idx);
bool TypeChecker_expr_is_mutable(TypeChecker* self, int64_t expr_idx);
void TypeChecker_check_identifier(TypeChecker* self, int64_t expr_idx);
void TypeChecker_check_field_access(TypeChecker* self, int64_t expr_idx);
void TypeChecker_check_method_call(TypeChecker* self, int64_t expr_idx);
void TypeChecker_check_return_stmt(TypeChecker* self, int64_t stmt_idx);
void TypeChecker_check_stmt(TypeChecker* self, int64_t stmt_idx);
void TypeChecker_check_expr(TypeChecker* self, int64_t expr_idx);
ArrayList_StrMapEntry ArrayList_StrMapEntry_init(KaiAllocator* allocator);
void ArrayList_StrMapEntry_push(ArrayList_StrMapEntry* self, StrMapEntry item);
StrMapEntry ArrayList_StrMapEntry_get(ArrayList_StrMapEntry* self, int64_t index);
void ArrayList_StrMapEntry_set(ArrayList_StrMapEntry* self, int64_t index, StrMapEntry item);
StrMapEntry ArrayList_StrMapEntry_pop(ArrayList_StrMapEntry* self);
int64_t ArrayList_StrMapEntry_length(ArrayList_StrMapEntry* self);
void ArrayList_StrMapEntry_deinit(ArrayList_StrMapEntry* self);
int64_t type_map_find(ArrayList_StrMapEntry* arr, const char* key);
const char* type_map_get(ArrayList_StrMapEntry* arr, const char* key);
void type_map_put(ArrayList_StrMapEntry* arr, const char* key, const char* value);
int64_t strlist_find(ArrayList_Str* arr, const char* key);
Codegen Codegen_init(KaiAllocator* allocator, ArrayList_StmtNode* stmt_pool, ArrayList_ExprNode* expr_pool, ArrayList_PatternNode* pattern_pool);
const char* Codegen_map_type(Codegen* self, const char* type_name);
const char* Codegen_substitute_generic_type(Codegen* self, const char* type_name);
const char* Codegen_trim_spaces(Codegen* self, const char* s);
const char* Codegen_clean_type_for_mangling(Codegen* self, const char* s);
int64_t Codegen_str_to_int(Codegen* self, const char* s);
void Codegen_setup_current_type_map(Codegen* self, ArrayList_Str* type_params, ArrayList_Str* type_args);
void Codegen_monomorphize_struct(Codegen* self, int64_t stmt_idx, const char* concrete_name, ArrayList_Str* type_args);
void Codegen_monomorphize_enum(Codegen* self, int64_t stmt_idx, const char* concrete_name, ArrayList_Str* type_args);
void Codegen_monomorphize_methods(Codegen* self, const char* base_struct_name, const char* concrete_struct_name);
const char* Codegen_extract_first_type_arg(Codegen* self, const char* type_name);
void Codegen_build_func_types(Codegen* self);
const char* Codegen_get_expr_type(Codegen* self, int64_t expr_idx);
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
const char* Codegen_generate(Codegen* self, int64_t top_stmt_idx);
const char* get_base_name(KaiAllocator* allocator, const char* path);

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
    int64_t total = (size + 8);
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
    int64_t mmap_size = (page_align_up((orig_size + 8)) + 65536);
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
bool Result_Str_Int_is_ok(Result_Str_Int* self) {
    if (self->tag == Result_Str_Int_ok_TAG) {
    const char* v = self->payload.ok.value;

    return true;
} else {
    return false;
} 
}
bool Result_Str_Int_is_err(Result_Str_Int* self) {
    return (Result_Str_Int_is_ok(self) == false);
}
const char* Result_Str_Int_unwrap(Result_Str_Int* self) {
    if (self->tag == Result_Str_Int_ok_TAG) {
    const char* val = self->payload.ok.value;

    return val;
} else {
    {
    exit(1);
}
} 
}
Result_Str_Int read_to_string(KaiAllocator* allocator, const char* path) {
    {
    void* file = fopen((char*)(path), (char*)("rb"));
    if ((char*)(file) == NULL) {
    return (Result_Str_Int){ .tag = Result_Str_Int_err_TAG, .payload = { .err = { .value = 1 } } };
}
    fseek(file, 0, 2);
    int64_t size = ftell(file);
    rewind(file);
    char* buf = (char*)(KaiAllocator_alloc(allocator, (size + 1), 1));
    int64_t bytes_read = fread(buf, 1, size, file);
    (buf)[bytes_read] = ((char)(0));
    fclose(file);
    return (Result_Str_Int){ .tag = Result_Str_Int_ok_TAG, .payload = { .ok = { .value = (const char*)(buf) } } };
}
}
bool Result_Bool_Int_is_ok(Result_Bool_Int* self) {
    if (self->tag == Result_Bool_Int_ok_TAG) {
    bool v = self->payload.ok.value;

    return true;
} else {
    return false;
} 
}
bool Result_Bool_Int_is_err(Result_Bool_Int* self) {
    return (Result_Bool_Int_is_ok(self) == false);
}
bool Result_Bool_Int_unwrap(Result_Bool_Int* self) {
    if (self->tag == Result_Bool_Int_ok_TAG) {
    bool val = self->payload.ok.value;

    return val;
} else {
    {
    exit(1);
}
} 
}
Result_Bool_Int write_string(const char* path, const char* content) {
    {
    void* file = fopen((char*)(path), (char*)("wb"));
    if ((char*)(file) == NULL) {
    return (Result_Bool_Int){ .tag = Result_Bool_Int_err_TAG, .payload = { .err = { .value = 1 } } };
}
    int64_t len = strlen(content);
    int64_t bytes_written = fwrite((char*)(content), 1, len, file);
    fclose(file);
    return (Result_Bool_Int){ .tag = Result_Bool_Int_ok_TAG, .payload = { .ok = { .value = true } } };
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
TokenType keyword_type(const char* ident) {
    if (strcmp(ident, "let") == 0) {
    return TokenType_LET;
} else if (strcmp(ident, "var") == 0) {
    return TokenType_VAR;
} else if (strcmp(ident, "func") == 0) {
    return TokenType_FUNC;
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
TokenValue make_keyword_value(const char* ident, TokenType ttype) {
    if (ttype == TokenType_BOOL_LIT) {
    if (strcmp(ident, "true") == 0) {
    return (TokenValue){ .tag = TokenValue_tv_bool_TAG, .payload = { .tv_bool = { .v = true } } };
}
    return (TokenValue){ .tag = TokenValue_tv_bool_TAG, .payload = { .tv_bool = { .v = false } } };
}
    return (TokenValue){ .tag = TokenValue_tv_str_TAG, .payload = { .tv_str = { .v = ident } } };
}
ArrayList_Token ArrayList_Token_init(KaiAllocator* allocator) {
    ArrayList_Token self = (ArrayList_Token){0};
    self.len = 0;
    self.cap = 4;
    self.allocator = allocator;
    {
    self.data = (Token*)(KaiAllocator_alloc(allocator, (self.cap * sizeof(Token)), 1));
}
    return self;
}
void ArrayList_Token_push(ArrayList_Token* self, Token item) {
    if (self->len == self->cap) {
    int64_t new_cap = (self->cap * 2);
    {
    Token* new_data = (Token*)(KaiAllocator_alloc(self->allocator, (new_cap * sizeof(Token)), 1));
    int64_t i = 0;
    while (i < self->len) {
    (new_data)[i] = (self->data)[i];
    i = (i + 1);
}
    KaiAllocator_free(self->allocator, (char*)(self->data));
    self->data = new_data;
    self->cap = new_cap;
}
}
    (self->data)[self->len] = item;
    self->len = (self->len + 1);
}
Token ArrayList_Token_get(ArrayList_Token* self, int64_t index) {
    if ((index < 0) || (index >= self->len)) {
    {
    exit(1);
}
}
    return (self->data)[index];
}
void ArrayList_Token_set(ArrayList_Token* self, int64_t index, Token item) {
    if ((index < 0) || (index >= self->len)) {
    {
    exit(1);
}
}
    (self->data)[index] = item;
}
Token ArrayList_Token_pop(ArrayList_Token* self) {
    if (self->len == 0) {
    {
    exit(1);
}
}
    self->len = (self->len - 1);
    return (self->data)[self->len];
}
int64_t ArrayList_Token_length(ArrayList_Token* self) {
    return self->len;
}
void ArrayList_Token_deinit(ArrayList_Token* self) {
    {
    KaiAllocator_free(self->allocator, (char*)(self->data));
}
}
ArrayList_Int ArrayList_Int_init(KaiAllocator* allocator) {
    ArrayList_Int self = (ArrayList_Int){0};
    self.len = 0;
    self.cap = 4;
    self.allocator = allocator;
    {
    self.data = (int64_t*)(KaiAllocator_alloc(allocator, (self.cap * sizeof(int64_t)), 1));
}
    return self;
}
void ArrayList_Int_push(ArrayList_Int* self, int64_t item) {
    if (self->len == self->cap) {
    int64_t new_cap = (self->cap * 2);
    {
    int64_t* new_data = (int64_t*)(KaiAllocator_alloc(self->allocator, (new_cap * sizeof(int64_t)), 1));
    int64_t i = 0;
    while (i < self->len) {
    (new_data)[i] = (self->data)[i];
    i = (i + 1);
}
    KaiAllocator_free(self->allocator, (char*)(self->data));
    self->data = new_data;
    self->cap = new_cap;
}
}
    (self->data)[self->len] = item;
    self->len = (self->len + 1);
}
int64_t ArrayList_Int_get(ArrayList_Int* self, int64_t index) {
    if ((index < 0) || (index >= self->len)) {
    {
    exit(1);
}
}
    return (self->data)[index];
}
void ArrayList_Int_set(ArrayList_Int* self, int64_t index, int64_t item) {
    if ((index < 0) || (index >= self->len)) {
    {
    exit(1);
}
}
    (self->data)[index] = item;
}
int64_t ArrayList_Int_pop(ArrayList_Int* self) {
    if (self->len == 0) {
    {
    exit(1);
}
}
    self->len = (self->len - 1);
    return (self->data)[self->len];
}
int64_t ArrayList_Int_length(ArrayList_Int* self) {
    return self->len;
}
void ArrayList_Int_deinit(ArrayList_Int* self) {
    {
    KaiAllocator_free(self->allocator, (char*)(self->data));
}
}
Lexer Lexer_init(KaiAllocator* allocator, const char* source) {
    Lexer self = (Lexer){0};
    self.allocator = allocator;
    self.source = source;
    self.cursor = 0;
    self.line = 1;
    self.column = 1;
    self.paren_depth = 0;
    self.brace_depth = 0;
    self.has_error = false;
    {
    self.tokens = (ArrayList_Token*)(KaiAllocator_alloc(allocator, sizeof(ArrayList_Token), 1));
    self.indent_stack = (ArrayList_Int*)(KaiAllocator_alloc(allocator, sizeof(ArrayList_Int), 1));
}
    *(self.tokens) = ArrayList_Token_init(allocator);
    *(self.indent_stack) = ArrayList_Int_init(allocator);
    ArrayList_Int_push(self.indent_stack, 0);
    {
    self.source_len = strlen(source);
}
    return self;
}
char Lexer_peek(Lexer* self, int64_t offset) {
    int64_t pos = (self->cursor + offset);
    if (pos >= self->source_len) {
    return ((char)(0));
}
    return (self->source)[pos];
}
char Lexer_advance(Lexer* self) {
    if (self->cursor >= self->source_len) {
    return ((char)(0));
}
    char c = (self->source)[self->cursor];
    self->cursor = (self->cursor + 1);
    if (c == '\n') {
    self->line = (self->line + 1);
    self->column = 1;
} else {
    self->column = (self->column + 1);
}
    return c;
}
void Lexer_emit(Lexer* self, TokenType ttype, TokenValue value) {
    ArrayList_Token_push(self->tokens, (Token){ .tok_type = ttype, .value = value, .line = self->line, .column = self->column });
}
void Lexer_lex_error(Lexer* self) {
    self->has_error = true;
}
void Lexer_skip_line_comment(Lexer* self) {
    while ((self->cursor < self->source_len) && (Lexer_peek(self, 0) != '\n')) {
    (void)(Lexer_advance(self));
}
}
void Lexer_skip_block_comment(Lexer* self) {
    (void)(Lexer_advance(self));
    while (self->cursor < self->source_len) {
    if ((Lexer_peek(self, 0) == '*') && (Lexer_peek(self, 1) == '/')) {
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
    char c = Lexer_peek(self, 0);
    if (((c == ' ') || (c == '\t')) || (c == '\r')) {
    (void)(Lexer_advance(self));
} else if (c == '/') {
    if (Lexer_peek(self, 1) == '/') {
    Lexer_skip_line_comment(self);
} else if (Lexer_peek(self, 1) == '*') {
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
    char c = Lexer_peek(self, 0);
    if (is_alnum(c) || (c == '_')) {
    StringBuilder_append_char(&(sb), Lexer_advance(self));
} else {
    done = true;
}
}
    const char* ident = StringBuilder_to_str(&(sb));
    TokenType ktype = keyword_type(ident);
    if (ktype == TokenType_IDENTIFIER) {
    Lexer_emit(self, TokenType_IDENTIFIER, (TokenValue){ .tag = TokenValue_tv_str_TAG, .payload = { .tv_str = { .v = ident } } });
} else if (ktype == TokenType_BOOL_LIT) {
    Lexer_emit(self, TokenType_BOOL_LIT, make_keyword_value(ident, TokenType_BOOL_LIT));
} else {
    Lexer_emit(self, ktype, (TokenValue){ .tag = TokenValue_tv_str_TAG, .payload = { .tv_str = { .v = ident } } });
}
}
void Lexer_lex_number(Lexer* self) {
    StringBuilder sb = StringBuilder_init(self->allocator);
    bool done = false;
    while ((self->cursor < self->source_len) && (!done)) {
    char c = Lexer_peek(self, 0);
    if (is_digit(c)) {
    StringBuilder_append_char(&(sb), Lexer_advance(self));
} else {
    done = true;
}
}
    if ((Lexer_peek(self, 0) == '.') && (Lexer_peek(self, 1) != '.')) {
    StringBuilder_append_char(&(sb), Lexer_advance(self));
    done = false;
    while ((self->cursor < self->source_len) && (!done)) {
    char c = Lexer_peek(self, 0);
    if (is_digit(c)) {
    StringBuilder_append_char(&(sb), Lexer_advance(self));
} else {
    done = true;
}
}
    const char* num_str = StringBuilder_to_str(&(sb));
    Lexer_emit(self, TokenType_FLOAT_LIT, (TokenValue){ .tag = TokenValue_tv_str_TAG, .payload = { .tv_str = { .v = num_str } } });
} else {
    const char* num_str = StringBuilder_to_str(&(sb));
    Lexer_emit(self, TokenType_INT_LIT, (TokenValue){ .tag = TokenValue_tv_str_TAG, .payload = { .tv_str = { .v = num_str } } });
}
}
void Lexer_lex_string(Lexer* self) {
    (void)(Lexer_advance(self));
    StringBuilder sb = StringBuilder_init(self->allocator);
    bool done = false;
    while ((self->cursor < self->source_len) && (!done)) {
    char c = Lexer_peek(self, 0);
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
    Lexer_emit(self, TokenType_STRING_LIT, (TokenValue){ .tag = TokenValue_tv_str_TAG, .payload = { .tv_str = { .v = s } } });
}
void Lexer_lex_char(Lexer* self) {
    (void)(Lexer_advance(self));
    char c = Lexer_advance(self);
    char ch = ((char)(0));
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
    int64_t indent = 0;
    int64_t temp = self->cursor;
    bool done = false;
    bool has_content = false;
    while ((temp < self->source_len) && (!done)) {
    char c = (self->source)[temp];
    if (c == ' ') {
    indent = (indent + 1);
    temp = (temp + 1);
} else if (c == '\t') {
    indent = (indent + 4);
    temp = (temp + 1);
} else if (c == '\r') {
    temp = (temp + 1);
} else if (c == '\n') {
    indent = 0;
    temp = (temp + 1);
} else if (((c == '/') && ((temp + 1) < self->source_len)) && ((self->source)[(temp + 1)] == '/')) {
    while ((temp < self->source_len) && ((self->source)[temp] != '\n')) {
    temp = (temp + 1);
}
    indent = 0;
} else if (((c == '/') && ((temp + 1) < self->source_len)) && ((self->source)[(temp + 1)] == '*')) {
    temp = (temp + 2);
    while ((temp < self->source_len) && (!((((temp + 1) < self->source_len) && ((self->source)[temp] == '*')) && ((self->source)[(temp + 1)] == '/')))) {
    if ((self->source)[temp] == '\n') {
    indent = 0;
}
    temp = (temp + 1);
}
    if (temp < self->source_len) {
    temp = (temp + 2);
}
} else {
    has_content = true;
    done = true;
}
}
    if (has_content) {
    return indent;
}
    return (-1);
}
void Lexer_lex(Lexer* self) {
    bool is_line_start = true;
    while (self->cursor < self->source_len) {
    if (false) {
    int64_t indent = Lexer_compute_indent(self);
    if (indent >= 0) {
    if ((self->paren_depth == 0) && (self->brace_depth == 0)) {
    int64_t current = ArrayList_Int_get(self->indent_stack, (ArrayList_Int_length(self->indent_stack) - 1));
    if (indent > current) {
    ArrayList_Int_push(self->indent_stack, indent);
    Lexer_emit(self, TokenType_INDENT, (TokenValue){ .tag = TokenValue_tv_int_TAG, .payload = { .tv_int = { .v = indent } } });
} else if (indent < current) {
    while (indent < ArrayList_Int_get(self->indent_stack, (ArrayList_Int_length(self->indent_stack) - 1))) {
    (void)(ArrayList_Int_pop(self->indent_stack));
    Lexer_emit(self, TokenType_DEDENT, (TokenValue){ .tag = TokenValue_tv_int_TAG, .payload = { .tv_int = { .v = indent } } });
}
    if (indent != ArrayList_Int_get(self->indent_stack, (ArrayList_Int_length(self->indent_stack) - 1))) {
    self->has_error = true;
}
}
}
}
    is_line_start = false;
}
    Lexer_skip_whitespace(self);
    if (self->cursor < self->source_len) {
    char c = Lexer_peek(self, 0);
    if (c == '\n') {
    (void)(Lexer_advance(self));
    if (self->paren_depth == 0) {
    int64_t last = ArrayList_Token_length(self->tokens);
    if (last > 0) {
    Token last_tok = ArrayList_Token_get(self->tokens, (last - 1));
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
} else if ((c == '-') && (Lexer_peek(self, 1) == '>')) {
    (void)(Lexer_advance(self));
    (void)(Lexer_advance(self));
    Lexer_emit(self, TokenType_ARROW, (TokenValue){ .tag = TokenValue_tv_str_TAG, .payload = { .tv_str = { .v = "->" } } });
} else if ((c == '=') && (Lexer_peek(self, 1) == '>')) {
    (void)(Lexer_advance(self));
    (void)(Lexer_advance(self));
    Lexer_emit(self, TokenType_FAT_ARROW, (TokenValue){ .tag = TokenValue_tv_str_TAG, .payload = { .tv_str = { .v = "=>" } } });
} else if ((c == '+') && (Lexer_peek(self, 1) == '=')) {
    (void)(Lexer_advance(self));
    (void)(Lexer_advance(self));
    Lexer_emit(self, TokenType_PLUS_ASSIGN, (TokenValue){ .tag = TokenValue_tv_str_TAG, .payload = { .tv_str = { .v = "+=" } } });
} else if ((c == '-') && (Lexer_peek(self, 1) == '=')) {
    (void)(Lexer_advance(self));
    (void)(Lexer_advance(self));
    Lexer_emit(self, TokenType_MINUS_ASSIGN, (TokenValue){ .tag = TokenValue_tv_str_TAG, .payload = { .tv_str = { .v = "-=" } } });
} else if ((c == '=') && (Lexer_peek(self, 1) == '=')) {
    (void)(Lexer_advance(self));
    (void)(Lexer_advance(self));
    Lexer_emit(self, TokenType_EQ, (TokenValue){ .tag = TokenValue_tv_str_TAG, .payload = { .tv_str = { .v = "==" } } });
} else if ((c == '!') && (Lexer_peek(self, 1) == '=')) {
    (void)(Lexer_advance(self));
    (void)(Lexer_advance(self));
    Lexer_emit(self, TokenType_NE, (TokenValue){ .tag = TokenValue_tv_str_TAG, .payload = { .tv_str = { .v = "!=" } } });
} else if ((c == '<') && (Lexer_peek(self, 1) == '=')) {
    (void)(Lexer_advance(self));
    (void)(Lexer_advance(self));
    Lexer_emit(self, TokenType_LE, (TokenValue){ .tag = TokenValue_tv_str_TAG, .payload = { .tv_str = { .v = "<=" } } });
} else if ((c == '>') && (Lexer_peek(self, 1) == '=')) {
    (void)(Lexer_advance(self));
    (void)(Lexer_advance(self));
    Lexer_emit(self, TokenType_GE, (TokenValue){ .tag = TokenValue_tv_str_TAG, .payload = { .tv_str = { .v = ">=" } } });
} else if ((c == '&') && (Lexer_peek(self, 1) == '&')) {
    (void)(Lexer_advance(self));
    (void)(Lexer_advance(self));
    Lexer_emit(self, TokenType_AND, (TokenValue){ .tag = TokenValue_tv_str_TAG, .payload = { .tv_str = { .v = "&&" } } });
} else if ((c == '|') && (Lexer_peek(self, 1) == '|')) {
    (void)(Lexer_advance(self));
    (void)(Lexer_advance(self));
    Lexer_emit(self, TokenType_OR, (TokenValue){ .tag = TokenValue_tv_str_TAG, .payload = { .tv_str = { .v = "||" } } });
} else if ((c == '<') && (Lexer_peek(self, 1) == '<')) {
    (void)(Lexer_advance(self));
    (void)(Lexer_advance(self));
    Lexer_emit(self, TokenType_LSHIFT, (TokenValue){ .tag = TokenValue_tv_str_TAG, .payload = { .tv_str = { .v = "<<" } } });
} else if ((c == '>') && (Lexer_peek(self, 1) == '>')) {
    (void)(Lexer_advance(self));
    (void)(Lexer_advance(self));
    Lexer_emit(self, TokenType_RSHIFT, (TokenValue){ .tag = TokenValue_tv_str_TAG, .payload = { .tv_str = { .v = ">>" } } });
} else if (((c == '.') && (Lexer_peek(self, 1) == '.')) && (Lexer_peek(self, 2) == '=')) {
    (void)(Lexer_advance(self));
    (void)(Lexer_advance(self));
    (void)(Lexer_advance(self));
    Lexer_emit(self, TokenType_DOTDOTEQ, (TokenValue){ .tag = TokenValue_tv_str_TAG, .payload = { .tv_str = { .v = "..=" } } });
} else if ((c == '.') && (Lexer_peek(self, 1) == '.')) {
    (void)(Lexer_advance(self));
    (void)(Lexer_advance(self));
    Lexer_emit(self, TokenType_DOTDOT, (TokenValue){ .tag = TokenValue_tv_str_TAG, .payload = { .tv_str = { .v = ".." } } });
} else if (c == '+') {
    (void)(Lexer_advance(self));
    Lexer_emit(self, TokenType_PLUS, (TokenValue){ .tag = TokenValue_tv_str_TAG, .payload = { .tv_str = { .v = "+" } } });
} else if (c == '-') {
    (void)(Lexer_advance(self));
    Lexer_emit(self, TokenType_MINUS, (TokenValue){ .tag = TokenValue_tv_str_TAG, .payload = { .tv_str = { .v = "-" } } });
} else if (c == '*') {
    (void)(Lexer_advance(self));
    Lexer_emit(self, TokenType_MUL, (TokenValue){ .tag = TokenValue_tv_str_TAG, .payload = { .tv_str = { .v = "*" } } });
} else if (c == '/') {
    (void)(Lexer_advance(self));
    Lexer_emit(self, TokenType_DIV, (TokenValue){ .tag = TokenValue_tv_str_TAG, .payload = { .tv_str = { .v = "/" } } });
} else if (c == '%') {
    (void)(Lexer_advance(self));
    Lexer_emit(self, TokenType_MOD, (TokenValue){ .tag = TokenValue_tv_str_TAG, .payload = { .tv_str = { .v = "%" } } });
} else if (c == '=') {
    (void)(Lexer_advance(self));
    Lexer_emit(self, TokenType_ASSIGN, (TokenValue){ .tag = TokenValue_tv_str_TAG, .payload = { .tv_str = { .v = "=" } } });
} else if (c == '<') {
    (void)(Lexer_advance(self));
    Lexer_emit(self, TokenType_LT, (TokenValue){ .tag = TokenValue_tv_str_TAG, .payload = { .tv_str = { .v = "<" } } });
} else if (c == '>') {
    (void)(Lexer_advance(self));
    Lexer_emit(self, TokenType_GT, (TokenValue){ .tag = TokenValue_tv_str_TAG, .payload = { .tv_str = { .v = ">" } } });
} else if (c == ':') {
    (void)(Lexer_advance(self));
    Lexer_emit(self, TokenType_COLON, (TokenValue){ .tag = TokenValue_tv_str_TAG, .payload = { .tv_str = { .v = ":" } } });
} else if (c == ';') {
    (void)(Lexer_advance(self));
    Lexer_emit(self, TokenType_SEMICOLON, (TokenValue){ .tag = TokenValue_tv_str_TAG, .payload = { .tv_str = { .v = ";" } } });
} else if (c == ',') {
    (void)(Lexer_advance(self));
    Lexer_emit(self, TokenType_COMMA, (TokenValue){ .tag = TokenValue_tv_str_TAG, .payload = { .tv_str = { .v = "," } } });
} else if (c == '(') {
    (void)(Lexer_advance(self));
    self->paren_depth = (self->paren_depth + 1);
    Lexer_emit(self, TokenType_LPAREN, (TokenValue){ .tag = TokenValue_tv_str_TAG, .payload = { .tv_str = { .v = "(" } } });
} else if (c == ')') {
    (void)(Lexer_advance(self));
    if (self->paren_depth > 0) {
    self->paren_depth = (self->paren_depth - 1);
}
    Lexer_emit(self, TokenType_RPAREN, (TokenValue){ .tag = TokenValue_tv_str_TAG, .payload = { .tv_str = { .v = ")" } } });
} else if (c == '[') {
    (void)(Lexer_advance(self));
    self->paren_depth = (self->paren_depth + 1);
    Lexer_emit(self, TokenType_LBRACKET, (TokenValue){ .tag = TokenValue_tv_str_TAG, .payload = { .tv_str = { .v = "[" } } });
} else if (c == ']') {
    (void)(Lexer_advance(self));
    if (self->paren_depth > 0) {
    self->paren_depth = (self->paren_depth - 1);
}
    Lexer_emit(self, TokenType_RBRACKET, (TokenValue){ .tag = TokenValue_tv_str_TAG, .payload = { .tv_str = { .v = "]" } } });
} else if (c == '{') {
    (void)(Lexer_advance(self));
    self->brace_depth = (self->brace_depth + 1);
    Lexer_emit(self, TokenType_LBRACE, (TokenValue){ .tag = TokenValue_tv_str_TAG, .payload = { .tv_str = { .v = "{" } } });
} else if (c == '}') {
    (void)(Lexer_advance(self));
    if (self->brace_depth > 0) {
    self->brace_depth = (self->brace_depth - 1);
}
    Lexer_emit(self, TokenType_RBRACE, (TokenValue){ .tag = TokenValue_tv_str_TAG, .payload = { .tv_str = { .v = "}" } } });
} else if (c == '&') {
    (void)(Lexer_advance(self));
    Lexer_emit(self, TokenType_AMP, (TokenValue){ .tag = TokenValue_tv_str_TAG, .payload = { .tv_str = { .v = "&" } } });
} else if (c == '#') {
    (void)(Lexer_advance(self));
    Lexer_emit(self, TokenType_HASH, (TokenValue){ .tag = TokenValue_tv_str_TAG, .payload = { .tv_str = { .v = "#" } } });
} else if (c == '!') {
    (void)(Lexer_advance(self));
    Lexer_emit(self, TokenType_NOT, (TokenValue){ .tag = TokenValue_tv_str_TAG, .payload = { .tv_str = { .v = "!" } } });
} else if (c == '?') {
    (void)(Lexer_advance(self));
    Lexer_emit(self, TokenType_QUESTION, (TokenValue){ .tag = TokenValue_tv_str_TAG, .payload = { .tv_str = { .v = "?" } } });
} else if (c == '^') {
    (void)(Lexer_advance(self));
    Lexer_emit(self, TokenType_BITXOR, (TokenValue){ .tag = TokenValue_tv_str_TAG, .payload = { .tv_str = { .v = "^" } } });
} else if (c == '~') {
    (void)(Lexer_advance(self));
    Lexer_emit(self, TokenType_BITNOT, (TokenValue){ .tag = TokenValue_tv_str_TAG, .payload = { .tv_str = { .v = "~" } } });
} else if (c == '|') {
    (void)(Lexer_advance(self));
    Lexer_emit(self, TokenType_PIPE, (TokenValue){ .tag = TokenValue_tv_str_TAG, .payload = { .tv_str = { .v = "|" } } });
} else if (c == '.') {
    (void)(Lexer_advance(self));
    Lexer_emit(self, TokenType_DOT, (TokenValue){ .tag = TokenValue_tv_str_TAG, .payload = { .tv_str = { .v = "." } } });
}
}
}
    while (false) {
    (void)(ArrayList_Int_pop(self->indent_stack));
    Lexer_emit(self, TokenType_DEDENT, (TokenValue){ .tag = TokenValue_tv_int_TAG, .payload = { .tv_int = { .v = 0 } } });
}
    Lexer_emit(self, TokenType_EOF, (TokenValue){ .tag = TokenValue_tv_none_TAG });
}
ArrayList_Param ArrayList_Param_init(KaiAllocator* allocator) {
    ArrayList_Param self = (ArrayList_Param){0};
    self.len = 0;
    self.cap = 4;
    self.allocator = allocator;
    {
    self.data = (Param*)(KaiAllocator_alloc(allocator, (self.cap * sizeof(Param)), 1));
}
    return self;
}
void ArrayList_Param_push(ArrayList_Param* self, Param item) {
    if (self->len == self->cap) {
    int64_t new_cap = (self->cap * 2);
    {
    Param* new_data = (Param*)(KaiAllocator_alloc(self->allocator, (new_cap * sizeof(Param)), 1));
    int64_t i = 0;
    while (i < self->len) {
    (new_data)[i] = (self->data)[i];
    i = (i + 1);
}
    KaiAllocator_free(self->allocator, (char*)(self->data));
    self->data = new_data;
    self->cap = new_cap;
}
}
    (self->data)[self->len] = item;
    self->len = (self->len + 1);
}
Param ArrayList_Param_get(ArrayList_Param* self, int64_t index) {
    if ((index < 0) || (index >= self->len)) {
    {
    exit(1);
}
}
    return (self->data)[index];
}
void ArrayList_Param_set(ArrayList_Param* self, int64_t index, Param item) {
    if ((index < 0) || (index >= self->len)) {
    {
    exit(1);
}
}
    (self->data)[index] = item;
}
Param ArrayList_Param_pop(ArrayList_Param* self) {
    if (self->len == 0) {
    {
    exit(1);
}
}
    self->len = (self->len - 1);
    return (self->data)[self->len];
}
int64_t ArrayList_Param_length(ArrayList_Param* self) {
    return self->len;
}
void ArrayList_Param_deinit(ArrayList_Param* self) {
    {
    KaiAllocator_free(self->allocator, (char*)(self->data));
}
}
ArrayList_Str ArrayList_Str_init(KaiAllocator* allocator) {
    ArrayList_Str self = (ArrayList_Str){0};
    self.len = 0;
    self.cap = 4;
    self.allocator = allocator;
    {
    self.data = (const char**)(KaiAllocator_alloc(allocator, (self.cap * sizeof(const char*)), 1));
}
    return self;
}
void ArrayList_Str_push(ArrayList_Str* self, const char* item) {
    if (self->len == self->cap) {
    int64_t new_cap = (self->cap * 2);
    {
    const char** new_data = (const char**)(KaiAllocator_alloc(self->allocator, (new_cap * sizeof(const char*)), 1));
    int64_t i = 0;
    while (i < self->len) {
    (new_data)[i] = (self->data)[i];
    i = (i + 1);
}
    KaiAllocator_free(self->allocator, (char*)(self->data));
    self->data = new_data;
    self->cap = new_cap;
}
}
    (self->data)[self->len] = item;
    self->len = (self->len + 1);
}
const char* ArrayList_Str_get(ArrayList_Str* self, int64_t index) {
    if ((index < 0) || (index >= self->len)) {
    {
    exit(1);
}
}
    return (self->data)[index];
}
void ArrayList_Str_set(ArrayList_Str* self, int64_t index, const char* item) {
    if ((index < 0) || (index >= self->len)) {
    {
    exit(1);
}
}
    (self->data)[index] = item;
}
const char* ArrayList_Str_pop(ArrayList_Str* self) {
    if (self->len == 0) {
    {
    exit(1);
}
}
    self->len = (self->len - 1);
    return (self->data)[self->len];
}
int64_t ArrayList_Str_length(ArrayList_Str* self) {
    return self->len;
}
void ArrayList_Str_deinit(ArrayList_Str* self) {
    {
    KaiAllocator_free(self->allocator, (char*)(self->data));
}
}
ArrayList_StrInterpPart ArrayList_StrInterpPart_init(KaiAllocator* allocator) {
    ArrayList_StrInterpPart self = (ArrayList_StrInterpPart){0};
    self.len = 0;
    self.cap = 4;
    self.allocator = allocator;
    {
    self.data = (StrInterpPart*)(KaiAllocator_alloc(allocator, (self.cap * sizeof(StrInterpPart)), 1));
}
    return self;
}
void ArrayList_StrInterpPart_push(ArrayList_StrInterpPart* self, StrInterpPart item) {
    if (self->len == self->cap) {
    int64_t new_cap = (self->cap * 2);
    {
    StrInterpPart* new_data = (StrInterpPart*)(KaiAllocator_alloc(self->allocator, (new_cap * sizeof(StrInterpPart)), 1));
    int64_t i = 0;
    while (i < self->len) {
    (new_data)[i] = (self->data)[i];
    i = (i + 1);
}
    KaiAllocator_free(self->allocator, (char*)(self->data));
    self->data = new_data;
    self->cap = new_cap;
}
}
    (self->data)[self->len] = item;
    self->len = (self->len + 1);
}
StrInterpPart ArrayList_StrInterpPart_get(ArrayList_StrInterpPart* self, int64_t index) {
    if ((index < 0) || (index >= self->len)) {
    {
    exit(1);
}
}
    return (self->data)[index];
}
void ArrayList_StrInterpPart_set(ArrayList_StrInterpPart* self, int64_t index, StrInterpPart item) {
    if ((index < 0) || (index >= self->len)) {
    {
    exit(1);
}
}
    (self->data)[index] = item;
}
StrInterpPart ArrayList_StrInterpPart_pop(ArrayList_StrInterpPart* self) {
    if (self->len == 0) {
    {
    exit(1);
}
}
    self->len = (self->len - 1);
    return (self->data)[self->len];
}
int64_t ArrayList_StrInterpPart_length(ArrayList_StrInterpPart* self) {
    return self->len;
}
void ArrayList_StrInterpPart_deinit(ArrayList_StrInterpPart* self) {
    {
    KaiAllocator_free(self->allocator, (char*)(self->data));
}
}
ArrayList_FieldInit ArrayList_FieldInit_init(KaiAllocator* allocator) {
    ArrayList_FieldInit self = (ArrayList_FieldInit){0};
    self.len = 0;
    self.cap = 4;
    self.allocator = allocator;
    {
    self.data = (FieldInit*)(KaiAllocator_alloc(allocator, (self.cap * sizeof(FieldInit)), 1));
}
    return self;
}
void ArrayList_FieldInit_push(ArrayList_FieldInit* self, FieldInit item) {
    if (self->len == self->cap) {
    int64_t new_cap = (self->cap * 2);
    {
    FieldInit* new_data = (FieldInit*)(KaiAllocator_alloc(self->allocator, (new_cap * sizeof(FieldInit)), 1));
    int64_t i = 0;
    while (i < self->len) {
    (new_data)[i] = (self->data)[i];
    i = (i + 1);
}
    KaiAllocator_free(self->allocator, (char*)(self->data));
    self->data = new_data;
    self->cap = new_cap;
}
}
    (self->data)[self->len] = item;
    self->len = (self->len + 1);
}
FieldInit ArrayList_FieldInit_get(ArrayList_FieldInit* self, int64_t index) {
    if ((index < 0) || (index >= self->len)) {
    {
    exit(1);
}
}
    return (self->data)[index];
}
void ArrayList_FieldInit_set(ArrayList_FieldInit* self, int64_t index, FieldInit item) {
    if ((index < 0) || (index >= self->len)) {
    {
    exit(1);
}
}
    (self->data)[index] = item;
}
FieldInit ArrayList_FieldInit_pop(ArrayList_FieldInit* self) {
    if (self->len == 0) {
    {
    exit(1);
}
}
    self->len = (self->len - 1);
    return (self->data)[self->len];
}
int64_t ArrayList_FieldInit_length(ArrayList_FieldInit* self) {
    return self->len;
}
void ArrayList_FieldInit_deinit(ArrayList_FieldInit* self) {
    {
    KaiAllocator_free(self->allocator, (char*)(self->data));
}
}
ArrayList_AsmOutput ArrayList_AsmOutput_init(KaiAllocator* allocator) {
    ArrayList_AsmOutput self = (ArrayList_AsmOutput){0};
    self.len = 0;
    self.cap = 4;
    self.allocator = allocator;
    {
    self.data = (AsmOutput*)(KaiAllocator_alloc(allocator, (self.cap * sizeof(AsmOutput)), 1));
}
    return self;
}
void ArrayList_AsmOutput_push(ArrayList_AsmOutput* self, AsmOutput item) {
    if (self->len == self->cap) {
    int64_t new_cap = (self->cap * 2);
    {
    AsmOutput* new_data = (AsmOutput*)(KaiAllocator_alloc(self->allocator, (new_cap * sizeof(AsmOutput)), 1));
    int64_t i = 0;
    while (i < self->len) {
    (new_data)[i] = (self->data)[i];
    i = (i + 1);
}
    KaiAllocator_free(self->allocator, (char*)(self->data));
    self->data = new_data;
    self->cap = new_cap;
}
}
    (self->data)[self->len] = item;
    self->len = (self->len + 1);
}
AsmOutput ArrayList_AsmOutput_get(ArrayList_AsmOutput* self, int64_t index) {
    if ((index < 0) || (index >= self->len)) {
    {
    exit(1);
}
}
    return (self->data)[index];
}
void ArrayList_AsmOutput_set(ArrayList_AsmOutput* self, int64_t index, AsmOutput item) {
    if ((index < 0) || (index >= self->len)) {
    {
    exit(1);
}
}
    (self->data)[index] = item;
}
AsmOutput ArrayList_AsmOutput_pop(ArrayList_AsmOutput* self) {
    if (self->len == 0) {
    {
    exit(1);
}
}
    self->len = (self->len - 1);
    return (self->data)[self->len];
}
int64_t ArrayList_AsmOutput_length(ArrayList_AsmOutput* self) {
    return self->len;
}
void ArrayList_AsmOutput_deinit(ArrayList_AsmOutput* self) {
    {
    KaiAllocator_free(self->allocator, (char*)(self->data));
}
}
ArrayList_AsmInput ArrayList_AsmInput_init(KaiAllocator* allocator) {
    ArrayList_AsmInput self = (ArrayList_AsmInput){0};
    self.len = 0;
    self.cap = 4;
    self.allocator = allocator;
    {
    self.data = (AsmInput*)(KaiAllocator_alloc(allocator, (self.cap * sizeof(AsmInput)), 1));
}
    return self;
}
void ArrayList_AsmInput_push(ArrayList_AsmInput* self, AsmInput item) {
    if (self->len == self->cap) {
    int64_t new_cap = (self->cap * 2);
    {
    AsmInput* new_data = (AsmInput*)(KaiAllocator_alloc(self->allocator, (new_cap * sizeof(AsmInput)), 1));
    int64_t i = 0;
    while (i < self->len) {
    (new_data)[i] = (self->data)[i];
    i = (i + 1);
}
    KaiAllocator_free(self->allocator, (char*)(self->data));
    self->data = new_data;
    self->cap = new_cap;
}
}
    (self->data)[self->len] = item;
    self->len = (self->len + 1);
}
AsmInput ArrayList_AsmInput_get(ArrayList_AsmInput* self, int64_t index) {
    if ((index < 0) || (index >= self->len)) {
    {
    exit(1);
}
}
    return (self->data)[index];
}
void ArrayList_AsmInput_set(ArrayList_AsmInput* self, int64_t index, AsmInput item) {
    if ((index < 0) || (index >= self->len)) {
    {
    exit(1);
}
}
    (self->data)[index] = item;
}
AsmInput ArrayList_AsmInput_pop(ArrayList_AsmInput* self) {
    if (self->len == 0) {
    {
    exit(1);
}
}
    self->len = (self->len - 1);
    return (self->data)[self->len];
}
int64_t ArrayList_AsmInput_length(ArrayList_AsmInput* self) {
    return self->len;
}
void ArrayList_AsmInput_deinit(ArrayList_AsmInput* self) {
    {
    KaiAllocator_free(self->allocator, (char*)(self->data));
}
}
ArrayList_StructField ArrayList_StructField_init(KaiAllocator* allocator) {
    ArrayList_StructField self = (ArrayList_StructField){0};
    self.len = 0;
    self.cap = 4;
    self.allocator = allocator;
    {
    self.data = (StructField*)(KaiAllocator_alloc(allocator, (self.cap * sizeof(StructField)), 1));
}
    return self;
}
void ArrayList_StructField_push(ArrayList_StructField* self, StructField item) {
    if (self->len == self->cap) {
    int64_t new_cap = (self->cap * 2);
    {
    StructField* new_data = (StructField*)(KaiAllocator_alloc(self->allocator, (new_cap * sizeof(StructField)), 1));
    int64_t i = 0;
    while (i < self->len) {
    (new_data)[i] = (self->data)[i];
    i = (i + 1);
}
    KaiAllocator_free(self->allocator, (char*)(self->data));
    self->data = new_data;
    self->cap = new_cap;
}
}
    (self->data)[self->len] = item;
    self->len = (self->len + 1);
}
StructField ArrayList_StructField_get(ArrayList_StructField* self, int64_t index) {
    if ((index < 0) || (index >= self->len)) {
    {
    exit(1);
}
}
    return (self->data)[index];
}
void ArrayList_StructField_set(ArrayList_StructField* self, int64_t index, StructField item) {
    if ((index < 0) || (index >= self->len)) {
    {
    exit(1);
}
}
    (self->data)[index] = item;
}
StructField ArrayList_StructField_pop(ArrayList_StructField* self) {
    if (self->len == 0) {
    {
    exit(1);
}
}
    self->len = (self->len - 1);
    return (self->data)[self->len];
}
int64_t ArrayList_StructField_length(ArrayList_StructField* self) {
    return self->len;
}
void ArrayList_StructField_deinit(ArrayList_StructField* self) {
    {
    KaiAllocator_free(self->allocator, (char*)(self->data));
}
}
ArrayList_Variant ArrayList_Variant_init(KaiAllocator* allocator) {
    ArrayList_Variant self = (ArrayList_Variant){0};
    self.len = 0;
    self.cap = 4;
    self.allocator = allocator;
    {
    self.data = (Variant*)(KaiAllocator_alloc(allocator, (self.cap * sizeof(Variant)), 1));
}
    return self;
}
void ArrayList_Variant_push(ArrayList_Variant* self, Variant item) {
    if (self->len == self->cap) {
    int64_t new_cap = (self->cap * 2);
    {
    Variant* new_data = (Variant*)(KaiAllocator_alloc(self->allocator, (new_cap * sizeof(Variant)), 1));
    int64_t i = 0;
    while (i < self->len) {
    (new_data)[i] = (self->data)[i];
    i = (i + 1);
}
    KaiAllocator_free(self->allocator, (char*)(self->data));
    self->data = new_data;
    self->cap = new_cap;
}
}
    (self->data)[self->len] = item;
    self->len = (self->len + 1);
}
Variant ArrayList_Variant_get(ArrayList_Variant* self, int64_t index) {
    if ((index < 0) || (index >= self->len)) {
    {
    exit(1);
}
}
    return (self->data)[index];
}
void ArrayList_Variant_set(ArrayList_Variant* self, int64_t index, Variant item) {
    if ((index < 0) || (index >= self->len)) {
    {
    exit(1);
}
}
    (self->data)[index] = item;
}
Variant ArrayList_Variant_pop(ArrayList_Variant* self) {
    if (self->len == 0) {
    {
    exit(1);
}
}
    self->len = (self->len - 1);
    return (self->data)[self->len];
}
int64_t ArrayList_Variant_length(ArrayList_Variant* self) {
    return self->len;
}
void ArrayList_Variant_deinit(ArrayList_Variant* self) {
    {
    KaiAllocator_free(self->allocator, (char*)(self->data));
}
}
ArrayList_DropVarEntry ArrayList_DropVarEntry_init(KaiAllocator* allocator) {
    ArrayList_DropVarEntry self = (ArrayList_DropVarEntry){0};
    self.len = 0;
    self.cap = 4;
    self.allocator = allocator;
    {
    self.data = (DropVarEntry*)(KaiAllocator_alloc(allocator, (self.cap * sizeof(DropVarEntry)), 1));
}
    return self;
}
void ArrayList_DropVarEntry_push(ArrayList_DropVarEntry* self, DropVarEntry item) {
    if (self->len == self->cap) {
    int64_t new_cap = (self->cap * 2);
    {
    DropVarEntry* new_data = (DropVarEntry*)(KaiAllocator_alloc(self->allocator, (new_cap * sizeof(DropVarEntry)), 1));
    int64_t i = 0;
    while (i < self->len) {
    (new_data)[i] = (self->data)[i];
    i = (i + 1);
}
    KaiAllocator_free(self->allocator, (char*)(self->data));
    self->data = new_data;
    self->cap = new_cap;
}
}
    (self->data)[self->len] = item;
    self->len = (self->len + 1);
}
DropVarEntry ArrayList_DropVarEntry_get(ArrayList_DropVarEntry* self, int64_t index) {
    if ((index < 0) || (index >= self->len)) {
    {
    exit(1);
}
}
    return (self->data)[index];
}
void ArrayList_DropVarEntry_set(ArrayList_DropVarEntry* self, int64_t index, DropVarEntry item) {
    if ((index < 0) || (index >= self->len)) {
    {
    exit(1);
}
}
    (self->data)[index] = item;
}
DropVarEntry ArrayList_DropVarEntry_pop(ArrayList_DropVarEntry* self) {
    if (self->len == 0) {
    {
    exit(1);
}
}
    self->len = (self->len - 1);
    return (self->data)[self->len];
}
int64_t ArrayList_DropVarEntry_length(ArrayList_DropVarEntry* self) {
    return self->len;
}
void ArrayList_DropVarEntry_deinit(ArrayList_DropVarEntry* self) {
    {
    KaiAllocator_free(self->allocator, (char*)(self->data));
}
}
ArrayList_MatchCase ArrayList_MatchCase_init(KaiAllocator* allocator) {
    ArrayList_MatchCase self = (ArrayList_MatchCase){0};
    self.len = 0;
    self.cap = 4;
    self.allocator = allocator;
    {
    self.data = (MatchCase*)(KaiAllocator_alloc(allocator, (self.cap * sizeof(MatchCase)), 1));
}
    return self;
}
void ArrayList_MatchCase_push(ArrayList_MatchCase* self, MatchCase item) {
    if (self->len == self->cap) {
    int64_t new_cap = (self->cap * 2);
    {
    MatchCase* new_data = (MatchCase*)(KaiAllocator_alloc(self->allocator, (new_cap * sizeof(MatchCase)), 1));
    int64_t i = 0;
    while (i < self->len) {
    (new_data)[i] = (self->data)[i];
    i = (i + 1);
}
    KaiAllocator_free(self->allocator, (char*)(self->data));
    self->data = new_data;
    self->cap = new_cap;
}
}
    (self->data)[self->len] = item;
    self->len = (self->len + 1);
}
MatchCase ArrayList_MatchCase_get(ArrayList_MatchCase* self, int64_t index) {
    if ((index < 0) || (index >= self->len)) {
    {
    exit(1);
}
}
    return (self->data)[index];
}
void ArrayList_MatchCase_set(ArrayList_MatchCase* self, int64_t index, MatchCase item) {
    if ((index < 0) || (index >= self->len)) {
    {
    exit(1);
}
}
    (self->data)[index] = item;
}
MatchCase ArrayList_MatchCase_pop(ArrayList_MatchCase* self) {
    if (self->len == 0) {
    {
    exit(1);
}
}
    self->len = (self->len - 1);
    return (self->data)[self->len];
}
int64_t ArrayList_MatchCase_length(ArrayList_MatchCase* self) {
    return self->len;
}
void ArrayList_MatchCase_deinit(ArrayList_MatchCase* self) {
    {
    KaiAllocator_free(self->allocator, (char*)(self->data));
}
}
ArrayList_DropVarEntry empty_dropvarentry_array(void) {
    return (ArrayList_DropVarEntry){ .data = (DropVarEntry*)(0), .len = 0, .cap = 0, .allocator = (KaiAllocator*)(0) };
}
ArrayList_Str empty_str_array(void) {
    return (ArrayList_Str){ .data = (const char**)(0), .len = 0, .cap = 0, .allocator = (KaiAllocator*)(0) };
}
ArrayList_Int empty_int_array(void) {
    return (ArrayList_Int){ .data = (int64_t*)(0), .len = 0, .cap = 0, .allocator = (KaiAllocator*)(0) };
}
ArrayList_FieldInit empty_fieldinit_array(void) {
    return (ArrayList_FieldInit){ .data = (FieldInit*)(0), .len = 0, .cap = 0, .allocator = (KaiAllocator*)(0) };
}
ArrayList_Param empty_param_array(void) {
    return (ArrayList_Param){ .data = (Param*)(0), .len = 0, .cap = 0, .allocator = (KaiAllocator*)(0) };
}
ArrayList_StructField empty_structfield_array(void) {
    return (ArrayList_StructField){ .data = (StructField*)(0), .len = 0, .cap = 0, .allocator = (KaiAllocator*)(0) };
}
ArrayList_Variant empty_variant_array(void) {
    return (ArrayList_Variant){ .data = (Variant*)(0), .len = 0, .cap = 0, .allocator = (KaiAllocator*)(0) };
}
ArrayList_MatchCase empty_matchcase_array(void) {
    return (ArrayList_MatchCase){ .data = (MatchCase*)(0), .len = 0, .cap = 0, .allocator = (KaiAllocator*)(0) };
}
ArrayList_StrInterpPart empty_strinterp_array(void) {
    return (ArrayList_StrInterpPart){ .data = (StrInterpPart*)(0), .len = 0, .cap = 0, .allocator = (KaiAllocator*)(0) };
}
ArrayList_AsmOutput empty_asmoutput_array(void) {
    return (ArrayList_AsmOutput){ .data = (AsmOutput*)(0), .len = 0, .cap = 0, .allocator = (KaiAllocator*)(0) };
}
ArrayList_AsmInput empty_asminput_array(void) {
    return (ArrayList_AsmInput){ .data = (AsmInput*)(0), .len = 0, .cap = 0, .allocator = (KaiAllocator*)(0) };
}
ExprNode new_expr_node(ExprKind kind) {
    ExprNode node = (ExprNode){ .kind = kind, .inferred_type = "", .lit_value = (TokenValue){ .tag = TokenValue_tv_none_TAG }, .lit_vkind = "", .interp_parts = empty_strinterp_array(), .ident_name = "", .ident_type_args = empty_str_array(), .binop_op = "", .binop_left = (-1), .binop_right = (-1), .unop_op = "", .unop_operand = (-1), .func_name = "", .func_args = empty_int_array(), .func_type_args = empty_str_array(), .struct_name = "", .struct_fields = empty_fieldinit_array(), .field_expr = (-1), .field_name = "", .meth_expr = (-1), .meth_name = "", .meth_args = empty_int_array(), .idx_expr = (-1), .idx_index = (-1), .check_expr = (-1), .slice_expr = (-1), .slice_lower = (-1), .slice_upper = (-1), .slice_inclusive = false, .range_start = (-1), .range_end = (-1), .range_inclusive = false, .arr_elements = empty_int_array(), .tup_elements = empty_int_array(), .borrow_expr = (-1), .borrow_mut = false, .deref_expr = (-1), .try_expr = (-1), .catch_expr = (-1), .catch_var = "", .catch_fallback = (-1), .asm_code = "", .asm_is_volatile = false, .asm_outputs = empty_asmoutput_array(), .asm_inputs = empty_asminput_array(), .asm_clobbers = empty_str_array() };
    return node;
}
StmtNode new_stmt_node(StmtKind kind) {
    StmtNode node = (StmtNode){ .kind = kind, .block_stmts = empty_int_array(), .vardecl_name = "", .vardecl_type = "", .vardecl_value = (-1), .vardecl_mut = false, .assign_target = (-1), .assign_value = (-1), .assign_op = "", .func_name = "", .func_params = empty_param_array(), .func_return_type = "", .func_body = (-1), .func_capability = "", .func_type_params = empty_str_array(), .func_public = false, .struct_name = "", .struct_fields = empty_structfield_array(), .struct_type_params = empty_str_array(), .struct_methods = empty_int_array(), .struct_trait_impls = empty_int_array(), .struct_public = false, .impl_struct_name = "", .impl_trait_name = "", .impl_methods = empty_int_array(), .trait_name = "", .trait_methods = empty_int_array(), .trait_public = false, .enum_name = "", .enum_variants = empty_variant_array(), .enum_type_params = empty_str_array(), .enum_public = false, .if_cond = (-1), .if_then = (-1), .if_else = (-1), .iflet_var = "", .iflet_expr = (-1), .iflet_then = (-1), .iflet_else = (-1), .while_cond = (-1), .while_body = (-1), .for_var = "", .for_start = (-1), .for_end = (-1), .for_inclusive = false, .for_body = (-1), .return_value = (-1), .print_value = (-1), .expr_stmt = (-1), .defer_body = (-1), .unsafe_body = (-1), .extern_name = "", .extern_params = empty_param_array(), .extern_return = "", .import_path = empty_str_array(), .import_alias = "", .cimport_header = "", .cimport_alias = "", .block_drop_vars = empty_dropvarentry_array(), .block_is_loop_body = false, .match_expr = (-1), .match_cases = empty_matchcase_array(), .error_name = "", .error_variants = empty_str_array() };
    return node;
}
PatternNode new_pattern_node(PatternKind kind) {
    PatternNode node = (PatternNode){ .kind = kind, .variant_name = "", .bindings = empty_str_array(), .lit_value = (TokenValue){ .tag = TokenValue_tv_none_TAG } };
    return node;
}
const char* tv_get_str(TokenValue val) {
    const char* result = "";
    if (val.tag == TokenValue_tv_str_TAG) {
    const char* s = val.payload.tv_str.v;

    result = s;
} else {
    {
    printf("%s\n", "tv_get_str failed!");
    exit(1);
}
} 
    return result;
}
int64_t token_precedence(TokenType ttype) {
    if (ttype == TokenType_DOT) {
    return 9;
} else if (ttype == TokenType_LBRACKET) {
    return 8;
} else if (ttype == TokenType_AS) {
    return 8;
} else if (((ttype == TokenType_MUL) || (ttype == TokenType_DIV)) || (ttype == TokenType_MOD)) {
    return 7;
} else if ((ttype == TokenType_PLUS) || (ttype == TokenType_MINUS)) {
    return 6;
} else if ((ttype == TokenType_LSHIFT) || (ttype == TokenType_RSHIFT)) {
    return 5;
} else if ((((((ttype == TokenType_EQ) || (ttype == TokenType_NE)) || (ttype == TokenType_LT)) || (ttype == TokenType_LE)) || (ttype == TokenType_GT)) || (ttype == TokenType_GE)) {
    return 4;
} else if (((ttype == TokenType_PIPE) || (ttype == TokenType_BITXOR)) || (ttype == TokenType_AMP)) {
    return 3;
} else if (ttype == TokenType_CATCH) {
    return 3;
} else if (ttype == TokenType_AND) {
    return 2;
} else if (ttype == TokenType_OR) {
    return 1;
} else if ((ttype == TokenType_DOTDOT) || (ttype == TokenType_DOTDOTEQ)) {
    return 4;
}
    return 0;
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
    if (ArrayList_Str_length(&(arr)) == 0) {
    return "";
}
    const char* result = ArrayList_Str_get(&(arr), 0);
    int64_t i = 1;
    while (i < ArrayList_Str_length(&(arr))) {
    result = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = result;
  const char* const _tmp_r = sep;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ArrayList_Str_get(&(arr), i);
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    i = (i + 1);
}
    return result;
}
ArrayList_ExprNode ArrayList_ExprNode_init(KaiAllocator* allocator) {
    ArrayList_ExprNode self = (ArrayList_ExprNode){0};
    self.len = 0;
    self.cap = 4;
    self.allocator = allocator;
    {
    self.data = (ExprNode*)(KaiAllocator_alloc(allocator, (self.cap * sizeof(ExprNode)), 1));
}
    return self;
}
void ArrayList_ExprNode_push(ArrayList_ExprNode* self, ExprNode item) {
    if (self->len == self->cap) {
    int64_t new_cap = (self->cap * 2);
    {
    ExprNode* new_data = (ExprNode*)(KaiAllocator_alloc(self->allocator, (new_cap * sizeof(ExprNode)), 1));
    int64_t i = 0;
    while (i < self->len) {
    (new_data)[i] = (self->data)[i];
    i = (i + 1);
}
    KaiAllocator_free(self->allocator, (char*)(self->data));
    self->data = new_data;
    self->cap = new_cap;
}
}
    (self->data)[self->len] = item;
    self->len = (self->len + 1);
}
ExprNode ArrayList_ExprNode_get(ArrayList_ExprNode* self, int64_t index) {
    if ((index < 0) || (index >= self->len)) {
    {
    exit(1);
}
}
    return (self->data)[index];
}
void ArrayList_ExprNode_set(ArrayList_ExprNode* self, int64_t index, ExprNode item) {
    if ((index < 0) || (index >= self->len)) {
    {
    exit(1);
}
}
    (self->data)[index] = item;
}
ExprNode ArrayList_ExprNode_pop(ArrayList_ExprNode* self) {
    if (self->len == 0) {
    {
    exit(1);
}
}
    self->len = (self->len - 1);
    return (self->data)[self->len];
}
int64_t ArrayList_ExprNode_length(ArrayList_ExprNode* self) {
    return self->len;
}
void ArrayList_ExprNode_deinit(ArrayList_ExprNode* self) {
    {
    KaiAllocator_free(self->allocator, (char*)(self->data));
}
}
ArrayList_StmtNode ArrayList_StmtNode_init(KaiAllocator* allocator) {
    ArrayList_StmtNode self = (ArrayList_StmtNode){0};
    self.len = 0;
    self.cap = 4;
    self.allocator = allocator;
    {
    self.data = (StmtNode*)(KaiAllocator_alloc(allocator, (self.cap * sizeof(StmtNode)), 1));
}
    return self;
}
void ArrayList_StmtNode_push(ArrayList_StmtNode* self, StmtNode item) {
    if (self->len == self->cap) {
    int64_t new_cap = (self->cap * 2);
    {
    StmtNode* new_data = (StmtNode*)(KaiAllocator_alloc(self->allocator, (new_cap * sizeof(StmtNode)), 1));
    int64_t i = 0;
    while (i < self->len) {
    (new_data)[i] = (self->data)[i];
    i = (i + 1);
}
    KaiAllocator_free(self->allocator, (char*)(self->data));
    self->data = new_data;
    self->cap = new_cap;
}
}
    (self->data)[self->len] = item;
    self->len = (self->len + 1);
}
StmtNode ArrayList_StmtNode_get(ArrayList_StmtNode* self, int64_t index) {
    if ((index < 0) || (index >= self->len)) {
    {
    exit(1);
}
}
    return (self->data)[index];
}
void ArrayList_StmtNode_set(ArrayList_StmtNode* self, int64_t index, StmtNode item) {
    if ((index < 0) || (index >= self->len)) {
    {
    exit(1);
}
}
    (self->data)[index] = item;
}
StmtNode ArrayList_StmtNode_pop(ArrayList_StmtNode* self) {
    if (self->len == 0) {
    {
    exit(1);
}
}
    self->len = (self->len - 1);
    return (self->data)[self->len];
}
int64_t ArrayList_StmtNode_length(ArrayList_StmtNode* self) {
    return self->len;
}
void ArrayList_StmtNode_deinit(ArrayList_StmtNode* self) {
    {
    KaiAllocator_free(self->allocator, (char*)(self->data));
}
}
ArrayList_PatternNode ArrayList_PatternNode_init(KaiAllocator* allocator) {
    ArrayList_PatternNode self = (ArrayList_PatternNode){0};
    self.len = 0;
    self.cap = 4;
    self.allocator = allocator;
    {
    self.data = (PatternNode*)(KaiAllocator_alloc(allocator, (self.cap * sizeof(PatternNode)), 1));
}
    return self;
}
void ArrayList_PatternNode_push(ArrayList_PatternNode* self, PatternNode item) {
    if (self->len == self->cap) {
    int64_t new_cap = (self->cap * 2);
    {
    PatternNode* new_data = (PatternNode*)(KaiAllocator_alloc(self->allocator, (new_cap * sizeof(PatternNode)), 1));
    int64_t i = 0;
    while (i < self->len) {
    (new_data)[i] = (self->data)[i];
    i = (i + 1);
}
    KaiAllocator_free(self->allocator, (char*)(self->data));
    self->data = new_data;
    self->cap = new_cap;
}
}
    (self->data)[self->len] = item;
    self->len = (self->len + 1);
}
PatternNode ArrayList_PatternNode_get(ArrayList_PatternNode* self, int64_t index) {
    if ((index < 0) || (index >= self->len)) {
    {
    exit(1);
}
}
    return (self->data)[index];
}
void ArrayList_PatternNode_set(ArrayList_PatternNode* self, int64_t index, PatternNode item) {
    if ((index < 0) || (index >= self->len)) {
    {
    exit(1);
}
}
    (self->data)[index] = item;
}
PatternNode ArrayList_PatternNode_pop(ArrayList_PatternNode* self) {
    if (self->len == 0) {
    {
    exit(1);
}
}
    self->len = (self->len - 1);
    return (self->data)[self->len];
}
int64_t ArrayList_PatternNode_length(ArrayList_PatternNode* self) {
    return self->len;
}
void ArrayList_PatternNode_deinit(ArrayList_PatternNode* self) {
    {
    KaiAllocator_free(self->allocator, (char*)(self->data));
}
}
Parser Parser_init_with_pools(KaiAllocator* allocator, ArrayList_Token* tokens, ArrayList_ExprNode* expr_pool, ArrayList_StmtNode* stmt_pool, ArrayList_PatternNode* pattern_pool) {
    Parser self = (Parser){0};
    self.allocator = allocator;
    self.tokens = tokens;
    self.cursor = 0;
    self.pending_gt = false;
    self.pending_gt_line = 0;
    self.pending_gt_col = 0;
    self.expr_pool = expr_pool;
    self.stmt_pool = stmt_pool;
    self.pattern_pool = pattern_pool;
    return self;
    return self;
}
Parser Parser_init(KaiAllocator* allocator, ArrayList_Token* tokens) {
    Parser self = (Parser){0};
    self.allocator = allocator;
    self.tokens = tokens;
    self.cursor = 0;
    self.pending_gt = false;
    self.pending_gt_line = 0;
    self.pending_gt_col = 0;
    {
    self.expr_pool = (ArrayList_ExprNode*)(KaiAllocator_alloc(allocator, sizeof(ArrayList_ExprNode), 8));
    self.stmt_pool = (ArrayList_StmtNode*)(KaiAllocator_alloc(allocator, sizeof(ArrayList_StmtNode), 8));
    self.pattern_pool = (ArrayList_PatternNode*)(KaiAllocator_alloc(allocator, sizeof(ArrayList_PatternNode), 8));
}
    *(self.expr_pool) = ArrayList_ExprNode_init(allocator);
    *(self.stmt_pool) = ArrayList_StmtNode_init(allocator);
    *(self.pattern_pool) = ArrayList_PatternNode_init(allocator);
    return self;
}
Token Parser_peek(Parser* self, int64_t offset) {
    if (self->pending_gt && (offset == 0)) {
    return (Token){ .tok_type = TokenType_GT, .value = (TokenValue){ .tag = TokenValue_tv_str_TAG, .payload = { .tv_str = { .v = ">" } } }, .line = self->pending_gt_line, .column = self->pending_gt_col };
}
    int64_t pos = (self->cursor + offset);
    if (pos >= ArrayList_Token_length(self->tokens)) {
    return ArrayList_Token_get(self->tokens, (ArrayList_Token_length(self->tokens) - 1));
}
    return ArrayList_Token_get(self->tokens, pos);
}
Token Parser_advance(Parser* self) {
    if (self->pending_gt) {
    self->pending_gt = false;
    return (Token){ .tok_type = TokenType_GT, .value = (TokenValue){ .tag = TokenValue_tv_str_TAG, .payload = { .tv_str = { .v = ">" } } }, .line = self->pending_gt_line, .column = self->pending_gt_col };
}
    Token tok = Parser_peek(self, 0);
    if (tok.tok_type != TokenType_EOF) {
    self->cursor = (self->cursor + 1);
}
    return tok;
}
bool Parser_match_token(Parser* self, TokenType ttype) {
    if (Parser_peek(self, 0).tok_type == ttype) {
    (void)(Parser_advance(self));
    return true;
}
    return false;
}
Token Parser_expect(Parser* self, TokenType ttype) {
    if (self->pending_gt) {
    if (ttype == TokenType_GT) {
    self->pending_gt = false;
    return (Token){ .tok_type = TokenType_GT, .value = (TokenValue){ .tag = TokenValue_tv_str_TAG, .payload = { .tv_str = { .v = ">" } } }, .line = self->pending_gt_line, .column = self->pending_gt_col };
}
    self->pending_gt = false;
}
    Token tok = Parser_peek(self, 0);
    if ((ttype == TokenType_GT) && (tok.tok_type == TokenType_RSHIFT)) {
    (void)(Parser_advance(self));
    self->pending_gt = true;
    self->pending_gt_line = tok.line;
    self->pending_gt_col = (tok.column + 1);
    return (Token){ .tok_type = TokenType_GT, .value = (TokenValue){ .tag = TokenValue_tv_str_TAG, .payload = { .tv_str = { .v = ">" } } }, .line = tok.line, .column = tok.column };
}
    if (tok.tok_type == ttype) {
    return Parser_advance(self);
}
    {
    printf("%s\n", "expect failed! found token at line:");
    print_int(tok.line);
    printf("%s\n", "col:");
    print_int(tok.column);
    printf("%s\n", "expected tag:");
    print_int(((int64_t)(ttype)));
    printf("%s\n", "found tag:");
    print_int(((int64_t)(tok.tok_type)));
    if (tok.tok_type == TokenType_INT_LIT) {
    exit(0);
} else if (tok.tok_type == TokenType_FLOAT_LIT) {
    exit(1);
} else if (tok.tok_type == TokenType_BOOL_LIT) {
    exit(2);
} else if (tok.tok_type == TokenType_CHAR_LIT) {
    exit(3);
} else if (tok.tok_type == TokenType_STRING_LIT) {
    exit(4);
} else if (tok.tok_type == TokenType_IDENTIFIER) {
    exit(5);
} else if (tok.tok_type == TokenType_LET) {
    exit(6);
} else if (tok.tok_type == TokenType_VAR) {
    exit(7);
} else if (tok.tok_type == TokenType_FUNC) {
    exit(8);
} else if (tok.tok_type == TokenType_IF) {
    exit(9);
} else if (tok.tok_type == TokenType_ELSE) {
    exit(10);
} else if (tok.tok_type == TokenType_WHILE) {
    exit(11);
} else if (tok.tok_type == TokenType_FOR) {
    exit(12);
} else if (tok.tok_type == TokenType_IN) {
    exit(13);
} else if (tok.tok_type == TokenType_RETURN) {
    exit(14);
} else if (tok.tok_type == TokenType_PRINT) {
    exit(15);
} else if (tok.tok_type == TokenType_STRUCT) {
    exit(16);
} else if (tok.tok_type == TokenType_IMPL) {
    exit(17);
} else if (tok.tok_type == TokenType_MUT) {
    exit(18);
} else if (tok.tok_type == TokenType_UNSAFE) {
    exit(19);
} else if (tok.tok_type == TokenType_EXTERN) {
    exit(20);
} else if (tok.tok_type == TokenType_ENUM) {
    exit(21);
} else if (tok.tok_type == TokenType_MATCH) {
    exit(22);
} else if (tok.tok_type == TokenType_CASE) {
    exit(23);
} else if (tok.tok_type == TokenType_USE) {
    exit(24);
} else if (tok.tok_type == TokenType_CHECK) {
    exit(25);
} else if (tok.tok_type == TokenType_TRAIT) {
    exit(26);
} else if (tok.tok_type == TokenType_PUB) {
    exit(27);
} else if (tok.tok_type == TokenType_IMPORT) {
    exit(28);
} else if (tok.tok_type == TokenType_CIMPORT) {
    exit(99);
} else if (tok.tok_type == TokenType_FROM) {
    exit(29);
} else if (tok.tok_type == TokenType_AS) {
    exit(30);
} else if (tok.tok_type == TokenType_SIZEOF) {
    exit(31);
} else if (tok.tok_type == TokenType_DEFER) {
    exit(32);
} else if (tok.tok_type == TokenType_NONE) {
    exit(33);
} else if (tok.tok_type == TokenType_FN) {
    exit(34);
} else if (tok.tok_type == TokenType_TRY) {
    exit(35);
} else if (tok.tok_type == TokenType_CATCH) {
    exit(36);
} else if (tok.tok_type == TokenType_OWN) {
    exit(37);
} else if (tok.tok_type == TokenType_ERROR) {
    exit(38);
} else if (tok.tok_type == TokenType_ASM) {
    exit(39);
} else if (tok.tok_type == TokenType_VOLATILE) {
    exit(40);
} else if (tok.tok_type == TokenType_PLUS) {
    exit(41);
} else if (tok.tok_type == TokenType_MINUS) {
    exit(42);
} else if (tok.tok_type == TokenType_MUL) {
    exit(43);
} else if (tok.tok_type == TokenType_DIV) {
    exit(44);
} else if (tok.tok_type == TokenType_MOD) {
    exit(45);
} else if (tok.tok_type == TokenType_ASSIGN) {
    exit(46);
} else if (tok.tok_type == TokenType_PLUS_ASSIGN) {
    exit(47);
} else if (tok.tok_type == TokenType_MINUS_ASSIGN) {
    exit(48);
} else if (tok.tok_type == TokenType_AND) {
    exit(49);
} else if (tok.tok_type == TokenType_OR) {
    exit(50);
} else if (tok.tok_type == TokenType_NOT) {
    exit(51);
} else if (tok.tok_type == TokenType_PIPE) {
    exit(52);
} else if (tok.tok_type == TokenType_BITXOR) {
    exit(53);
} else if (tok.tok_type == TokenType_BITNOT) {
    exit(54);
} else if (tok.tok_type == TokenType_LSHIFT) {
    exit(55);
} else if (tok.tok_type == TokenType_RSHIFT) {
    exit(56);
} else if (tok.tok_type == TokenType_EQ) {
    exit(57);
} else if (tok.tok_type == TokenType_NE) {
    exit(58);
} else if (tok.tok_type == TokenType_LT) {
    exit(59);
} else if (tok.tok_type == TokenType_LE) {
    exit(60);
} else if (tok.tok_type == TokenType_GT) {
    exit(61);
} else if (tok.tok_type == TokenType_GE) {
    exit(62);
} else if (tok.tok_type == TokenType_COLON) {
    exit(63);
} else if (tok.tok_type == TokenType_ARROW) {
    exit(64);
} else if (tok.tok_type == TokenType_FAT_ARROW) {
    exit(65);
} else if (tok.tok_type == TokenType_COMMA) {
    exit(66);
} else if (tok.tok_type == TokenType_LPAREN) {
    exit(67);
} else if (tok.tok_type == TokenType_RPAREN) {
    exit(68);
} else if (tok.tok_type == TokenType_LBRACKET) {
    exit(69);
} else if (tok.tok_type == TokenType_RBRACKET) {
    exit(70);
} else if (tok.tok_type == TokenType_LBRACE) {
    exit(71);
} else if (tok.tok_type == TokenType_RBRACE) {
    exit(72);
} else if (tok.tok_type == TokenType_DOTDOT) {
    exit(73);
} else if (tok.tok_type == TokenType_DOTDOTEQ) {
    exit(74);
} else if (tok.tok_type == TokenType_DOT) {
    exit(75);
} else if (tok.tok_type == TokenType_AMP) {
    exit(76);
} else if (tok.tok_type == TokenType_HASH) {
    exit(77);
} else if (tok.tok_type == TokenType_QUESTION) {
    exit(78);
} else if (tok.tok_type == TokenType_SEMICOLON) {
    exit(85);
} else if (tok.tok_type == TokenType_BREAK) {
    exit(83);
} else if (tok.tok_type == TokenType_CONTINUE) {
    exit(84);
} else if (tok.tok_type == TokenType_NEWLINE) {
    exit(79);
} else if (tok.tok_type == TokenType_INDENT) {
    exit(80);
} else if (tok.tok_type == TokenType_DEDENT) {
    exit(81);
} else if (tok.tok_type == TokenType_EOF) {
    exit(82);
} 
    exit(255);
}
    return tok;
}
void Parser_consume_newlines(Parser* self) {
    bool done = false;
    while (!done) {
    if (Parser_match_token(self, TokenType_NEWLINE)) {
    done = false;
} else {
    done = true;
}
}
}
void Parser_expect_end_of_statement(Parser* self) {
    Token tok = Parser_peek(self, 0);
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
    if (Parser_peek(self, 1).tok_type != TokenType_LT) {
    return false;
}
    int64_t offset = 2;
    int64_t nested = 1;
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
    nested = (nested + 1);
} else if (tt == TokenType_GT) {
    nested = (nested - 1);
    if (nested <= 0) {
    return ((Parser_peek(self, (offset + 1)).tok_type == TokenType_LPAREN) || (Parser_peek(self, (offset + 1)).tok_type == TokenType_DOT));
}
} else if (tt == TokenType_RSHIFT) {
    nested = (nested - 2);
    if (nested <= 0) {
    return ((Parser_peek(self, (offset + 1)).tok_type == TokenType_LPAREN) || (Parser_peek(self, (offset + 1)).tok_type == TokenType_DOT));
}
} else {
    return false;
}
    offset = (offset + 1);
}
    return false;
}
int64_t Parser_ex_literal(Parser* self, TokenValue val, const char* vkind) {
    ExprNode node = new_expr_node(ExprKind_ek_literal);
    node.lit_value = val;
    node.lit_vkind = vkind;
    ArrayList_ExprNode_push(self->expr_pool, node);
    return (ArrayList_ExprNode_length(self->expr_pool) - 1);
}
int64_t Parser_ex_ident(Parser* self, const char* name) {
    ExprNode node = new_expr_node(ExprKind_ek_identifier);
    node.ident_name = name;
    ArrayList_ExprNode_push(self->expr_pool, node);
    return (ArrayList_ExprNode_length(self->expr_pool) - 1);
}
int64_t Parser_ex_ident_with(Parser* self, const char* name, ArrayList_Str targs) {
    ExprNode node = new_expr_node(ExprKind_ek_identifier);
    node.ident_name = name;
    node.ident_type_args = targs;
    ArrayList_ExprNode_push(self->expr_pool, node);
    return (ArrayList_ExprNode_length(self->expr_pool) - 1);
}
int64_t Parser_ex_binop(Parser* self, const char* op, int64_t left, int64_t right) {
    ExprNode node = new_expr_node(ExprKind_ek_binary_op);
    node.binop_op = op;
    node.binop_left = left;
    node.binop_right = right;
    ArrayList_ExprNode_push(self->expr_pool, node);
    return (ArrayList_ExprNode_length(self->expr_pool) - 1);
}
int64_t Parser_ex_unop(Parser* self, const char* op, int64_t operand) {
    ExprNode node = new_expr_node(ExprKind_ek_unary_op);
    node.unop_op = op;
    node.unop_operand = operand;
    ArrayList_ExprNode_push(self->expr_pool, node);
    return (ArrayList_ExprNode_length(self->expr_pool) - 1);
}
int64_t Parser_ex_call(Parser* self, const char* name, ArrayList_Int args) {
    ExprNode node = new_expr_node(ExprKind_ek_func_call);
    node.func_name = name;
    node.func_args = args;
    ArrayList_ExprNode_push(self->expr_pool, node);
    return (ArrayList_ExprNode_length(self->expr_pool) - 1);
}
int64_t Parser_ex_call_with(Parser* self, const char* name, ArrayList_Int args, ArrayList_Str targs) {
    ExprNode node = new_expr_node(ExprKind_ek_func_call);
    node.func_name = name;
    node.func_args = args;
    node.func_type_args = targs;
    ArrayList_ExprNode_push(self->expr_pool, node);
    return (ArrayList_ExprNode_length(self->expr_pool) - 1);
}
int64_t Parser_ex_struct_init(Parser* self, const char* name, ArrayList_FieldInit fields) {
    ExprNode node = new_expr_node(ExprKind_ek_struct_init);
    node.struct_name = name;
    node.struct_fields = fields;
    ArrayList_ExprNode_push(self->expr_pool, node);
    return (ArrayList_ExprNode_length(self->expr_pool) - 1);
}
int64_t Parser_ex_field(Parser* self, int64_t expr, const char* field) {
    ExprNode node = new_expr_node(ExprKind_ek_field_access);
    node.field_expr = expr;
    node.field_name = field;
    ArrayList_ExprNode_push(self->expr_pool, node);
    return (ArrayList_ExprNode_length(self->expr_pool) - 1);
}
int64_t Parser_ex_method(Parser* self, int64_t expr, const char* method, ArrayList_Int args) {
    ExprNode node = new_expr_node(ExprKind_ek_method_call);
    node.meth_expr = expr;
    node.meth_name = method;
    node.meth_args = args;
    ArrayList_ExprNode_push(self->expr_pool, node);
    return (ArrayList_ExprNode_length(self->expr_pool) - 1);
}
int64_t Parser_ex_index(Parser* self, int64_t expr, int64_t idx) {
    ExprNode node = new_expr_node(ExprKind_ek_index);
    node.idx_expr = expr;
    node.idx_index = idx;
    ArrayList_ExprNode_push(self->expr_pool, node);
    return (ArrayList_ExprNode_length(self->expr_pool) - 1);
}
int64_t Parser_ex_check(Parser* self, int64_t expr) {
    ExprNode node = new_expr_node(ExprKind_ek_check);
    node.check_expr = expr;
    ArrayList_ExprNode_push(self->expr_pool, node);
    return (ArrayList_ExprNode_length(self->expr_pool) - 1);
}
int64_t Parser_ex_slice(Parser* self, int64_t expr, int64_t lower, int64_t upper, bool is_inclusive) {
    ExprNode node = new_expr_node(ExprKind_ek_slice);
    node.slice_expr = expr;
    node.slice_lower = lower;
    node.slice_upper = upper;
    node.slice_inclusive = is_inclusive;
    ArrayList_ExprNode_push(self->expr_pool, node);
    return (ArrayList_ExprNode_length(self->expr_pool) - 1);
}
int64_t Parser_ex_range(Parser* self, int64_t start, int64_t end, bool is_inclusive) {
    ExprNode node = new_expr_node(ExprKind_ek_range);
    node.range_start = start;
    node.range_end = end;
    node.range_inclusive = is_inclusive;
    ArrayList_ExprNode_push(self->expr_pool, node);
    return (ArrayList_ExprNode_length(self->expr_pool) - 1);
}
int64_t Parser_ex_array(Parser* self, ArrayList_Int elements) {
    ExprNode node = new_expr_node(ExprKind_ek_array);
    node.arr_elements = elements;
    ArrayList_ExprNode_push(self->expr_pool, node);
    return (ArrayList_ExprNode_length(self->expr_pool) - 1);
}
int64_t Parser_ex_tuple(Parser* self, ArrayList_Int elements) {
    ExprNode node = new_expr_node(ExprKind_ek_tuple);
    node.tup_elements = elements;
    ArrayList_ExprNode_push(self->expr_pool, node);
    return (ArrayList_ExprNode_length(self->expr_pool) - 1);
}
int64_t Parser_ex_borrow(Parser* self, int64_t expr, bool is_mut) {
    ExprNode node = new_expr_node(ExprKind_ek_borrow);
    node.borrow_expr = expr;
    node.borrow_mut = is_mut;
    ArrayList_ExprNode_push(self->expr_pool, node);
    return (ArrayList_ExprNode_length(self->expr_pool) - 1);
}
int64_t Parser_ex_deref(Parser* self, int64_t expr) {
    ExprNode node = new_expr_node(ExprKind_ek_deref);
    node.deref_expr = expr;
    ArrayList_ExprNode_push(self->expr_pool, node);
    return (ArrayList_ExprNode_length(self->expr_pool) - 1);
}
int64_t Parser_ex_try(Parser* self, int64_t expr) {
    ExprNode node = new_expr_node(ExprKind_ek_try);
    node.try_expr = expr;
    ArrayList_ExprNode_push(self->expr_pool, node);
    return (ArrayList_ExprNode_length(self->expr_pool) - 1);
}
int64_t Parser_ex_catch(Parser* self, int64_t expr, const char* var_name, int64_t fallback) {
    ExprNode node = new_expr_node(ExprKind_ek_catch);
    node.catch_expr = expr;
    node.catch_var = var_name;
    node.catch_fallback = fallback;
    ArrayList_ExprNode_push(self->expr_pool, node);
    return (ArrayList_ExprNode_length(self->expr_pool) - 1);
}
int64_t Parser_ex_asm(Parser* self, const char* code, bool is_volatile, ArrayList_AsmOutput outputs, ArrayList_AsmInput inputs, ArrayList_Str clobbers) {
    ExprNode node = new_expr_node(ExprKind_ek_asm);
    node.asm_code = code;
    node.asm_is_volatile = is_volatile;
    node.asm_outputs = outputs;
    node.asm_inputs = inputs;
    node.asm_clobbers = clobbers;
    ArrayList_ExprNode_push(self->expr_pool, node);
    return (ArrayList_ExprNode_length(self->expr_pool) - 1);
}
int64_t Parser_st_block(Parser* self, ArrayList_Int stmts) {
    StmtNode node = new_stmt_node(StmtKind_sk_block);
    node.block_stmts = stmts;
    ArrayList_StmtNode_push(self->stmt_pool, node);
    return (ArrayList_StmtNode_length(self->stmt_pool) - 1);
}
int64_t Parser_st_error(Parser* self, const char* name, ArrayList_Str variants) {
    StmtNode node = new_stmt_node(StmtKind_sk_error_decl);
    node.error_name = name;
    node.error_variants = variants;
    ArrayList_StmtNode_push(self->stmt_pool, node);
    return (ArrayList_StmtNode_length(self->stmt_pool) - 1);
}
int64_t Parser_st_var_decl(Parser* self, const char* name, const char* type_ann, int64_t value, bool is_mut) {
    StmtNode node = new_stmt_node(StmtKind_sk_var_decl);
    node.vardecl_name = name;
    node.vardecl_type = type_ann;
    node.vardecl_value = value;
    node.vardecl_mut = is_mut;
    ArrayList_StmtNode_push(self->stmt_pool, node);
    return (ArrayList_StmtNode_length(self->stmt_pool) - 1);
}
int64_t Parser_st_assign(Parser* self, int64_t target, int64_t value, const char* op) {
    StmtNode node = new_stmt_node(StmtKind_sk_assignment);
    node.assign_target = target;
    node.assign_value = value;
    node.assign_op = op;
    ArrayList_StmtNode_push(self->stmt_pool, node);
    return (ArrayList_StmtNode_length(self->stmt_pool) - 1);
}
int64_t Parser_st_func(Parser* self, const char* name, ArrayList_Param params, const char* ret_type, int64_t body, const char* cap, ArrayList_Str tp) {
    StmtNode node = new_stmt_node(StmtKind_sk_func_decl);
    node.func_name = name;
    node.func_params = params;
    node.func_return_type = ret_type;
    node.func_body = body;
    node.func_capability = cap;
    node.func_type_params = tp;
    ArrayList_StmtNode_push(self->stmt_pool, node);
    return (ArrayList_StmtNode_length(self->stmt_pool) - 1);
}
int64_t Parser_st_struct(Parser* self, const char* name, ArrayList_StructField fields, ArrayList_Str tp, ArrayList_Int methods, ArrayList_Int impls) {
    StmtNode node = new_stmt_node(StmtKind_sk_struct_decl);
    node.struct_name = name;
    node.struct_fields = fields;
    node.struct_type_params = tp;
    node.struct_methods = methods;
    node.struct_trait_impls = impls;
    ArrayList_StmtNode_push(self->stmt_pool, node);
    return (ArrayList_StmtNode_length(self->stmt_pool) - 1);
}
int64_t Parser_st_impl(Parser* self, const char* struct_name, const char* trait_name, ArrayList_Int methods) {
    StmtNode node = new_stmt_node(StmtKind_sk_impl_block);
    node.impl_struct_name = struct_name;
    node.impl_trait_name = trait_name;
    node.impl_methods = methods;
    ArrayList_StmtNode_push(self->stmt_pool, node);
    return (ArrayList_StmtNode_length(self->stmt_pool) - 1);
}
int64_t Parser_st_trait(Parser* self, const char* name, ArrayList_Int methods) {
    StmtNode node = new_stmt_node(StmtKind_sk_trait_decl);
    node.trait_name = name;
    node.trait_methods = methods;
    ArrayList_StmtNode_push(self->stmt_pool, node);
    return (ArrayList_StmtNode_length(self->stmt_pool) - 1);
}
int64_t Parser_st_enum(Parser* self, const char* name, ArrayList_Variant variants, ArrayList_Str tp) {
    StmtNode node = new_stmt_node(StmtKind_sk_enum_decl);
    node.enum_name = name;
    node.enum_variants = variants;
    node.enum_type_params = tp;
    ArrayList_StmtNode_push(self->stmt_pool, node);
    return (ArrayList_StmtNode_length(self->stmt_pool) - 1);
}
int64_t Parser_st_match(Parser* self, int64_t expr, ArrayList_MatchCase cases) {
    StmtNode node = new_stmt_node(StmtKind_sk_match);
    node.match_expr = expr;
    node.match_cases = cases;
    ArrayList_StmtNode_push(self->stmt_pool, node);
    return (ArrayList_StmtNode_length(self->stmt_pool) - 1);
}
int64_t Parser_st_unsafe(Parser* self, int64_t body) {
    StmtNode node = new_stmt_node(StmtKind_sk_unsafe);
    node.unsafe_body = body;
    ArrayList_StmtNode_push(self->stmt_pool, node);
    return (ArrayList_StmtNode_length(self->stmt_pool) - 1);
}
int64_t Parser_st_extern(Parser* self, const char* name, ArrayList_Param params, const char* ret) {
    StmtNode node = new_stmt_node(StmtKind_sk_extern);
    node.extern_name = name;
    node.extern_params = params;
    node.extern_return = ret;
    ArrayList_StmtNode_push(self->stmt_pool, node);
    return (ArrayList_StmtNode_length(self->stmt_pool) - 1);
}
int64_t Parser_st_if(Parser* self, int64_t cond, int64_t then_b, int64_t else_b) {
    StmtNode node = new_stmt_node(StmtKind_sk_if);
    node.if_cond = cond;
    node.if_then = then_b;
    node.if_else = else_b;
    ArrayList_StmtNode_push(self->stmt_pool, node);
    return (ArrayList_StmtNode_length(self->stmt_pool) - 1);
}
int64_t Parser_st_if_let(Parser* self, const char* vname, int64_t expr, int64_t then_b, int64_t else_b) {
    StmtNode node = new_stmt_node(StmtKind_sk_if_let);
    node.iflet_var = vname;
    node.iflet_expr = expr;
    node.iflet_then = then_b;
    node.iflet_else = else_b;
    ArrayList_StmtNode_push(self->stmt_pool, node);
    return (ArrayList_StmtNode_length(self->stmt_pool) - 1);
}
int64_t Parser_st_while(Parser* self, int64_t cond, int64_t body) {
    StmtNode node = new_stmt_node(StmtKind_sk_while);
    node.while_cond = cond;
    node.while_body = body;
    ArrayList_StmtNode_push(self->stmt_pool, node);
    return (ArrayList_StmtNode_length(self->stmt_pool) - 1);
}
int64_t Parser_st_for(Parser* self, const char* var_name, int64_t start, int64_t end, bool inc, int64_t body) {
    StmtNode node = new_stmt_node(StmtKind_sk_for);
    node.for_var = var_name;
    node.for_start = start;
    node.for_end = end;
    node.for_inclusive = inc;
    node.for_body = body;
    ArrayList_StmtNode_push(self->stmt_pool, node);
    return (ArrayList_StmtNode_length(self->stmt_pool) - 1);
}
int64_t Parser_st_return(Parser* self, int64_t value) {
    StmtNode node = new_stmt_node(StmtKind_sk_return);
    node.return_value = value;
    ArrayList_StmtNode_push(self->stmt_pool, node);
    return (ArrayList_StmtNode_length(self->stmt_pool) - 1);
}
int64_t Parser_st_print(Parser* self, int64_t value) {
    StmtNode node = new_stmt_node(StmtKind_sk_print);
    node.print_value = value;
    ArrayList_StmtNode_push(self->stmt_pool, node);
    return (ArrayList_StmtNode_length(self->stmt_pool) - 1);
}
int64_t Parser_st_expr(Parser* self, int64_t expr) {
    StmtNode node = new_stmt_node(StmtKind_sk_expr);
    node.expr_stmt = expr;
    ArrayList_StmtNode_push(self->stmt_pool, node);
    return (ArrayList_StmtNode_length(self->stmt_pool) - 1);
}
int64_t Parser_st_defer(Parser* self, int64_t body) {
    StmtNode node = new_stmt_node(StmtKind_sk_defer);
    node.defer_body = body;
    ArrayList_StmtNode_push(self->stmt_pool, node);
    return (ArrayList_StmtNode_length(self->stmt_pool) - 1);
}
int64_t Parser_st_break(Parser* self) {
    StmtNode node = new_stmt_node(StmtKind_sk_break);
    ArrayList_StmtNode_push(self->stmt_pool, node);
    return (ArrayList_StmtNode_length(self->stmt_pool) - 1);
}
int64_t Parser_st_continue(Parser* self) {
    StmtNode node = new_stmt_node(StmtKind_sk_continue);
    ArrayList_StmtNode_push(self->stmt_pool, node);
    return (ArrayList_StmtNode_length(self->stmt_pool) - 1);
}
int64_t Parser_st_import(Parser* self, ArrayList_Str path, const char* alias) {
    StmtNode node = new_stmt_node(StmtKind_sk_import);
    node.import_path = path;
    node.import_alias = alias;
    ArrayList_StmtNode_push(self->stmt_pool, node);
    return (ArrayList_StmtNode_length(self->stmt_pool) - 1);
}
int64_t Parser_st_cimport(Parser* self, const char* header, const char* alias) {
    StmtNode node = new_stmt_node(StmtKind_sk_cimport);
    node.cimport_header = header;
    node.cimport_alias = alias;
    ArrayList_StmtNode_push(self->stmt_pool, node);
    return (ArrayList_StmtNode_length(self->stmt_pool) - 1);
}
int64_t Parser_parse_program(Parser* self) {
    Parser_consume_newlines(self);
    ArrayList_Int stmts = ArrayList_Int_init(self->allocator);
    while (Parser_peek(self, 0).tok_type != TokenType_EOF) {
    int64_t stmt = Parser_parse_statement(self);
    if (stmt >= 0) {
    ArrayList_Int_push(&(stmts), stmt);
}
    Parser_consume_newlines(self);
}
    return Parser_st_block(self, stmts);
}
int64_t Parser_parse_statement(Parser* self) {
    Parser_consume_newlines(self);
    Token tok = Parser_peek(self, 0);
    bool is_public = false;
    if (tok.tok_type == TokenType_PUB) {
    (void)(Parser_advance(self));
    is_public = true;
    tok = Parser_peek(self, 0);
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
} else if (tok.tok_type == TokenType_PRINT) {
    return Parser_parse_print_stmt(self);
} else if (tok.tok_type == TokenType_DEFER) {
    return Parser_parse_defer_stmt(self);
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
    return /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = base_type;
  const char* const _tmp_r = "!";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = error_set;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    return base_type;
}
const char* Parser_parse_base_type(Parser* self) {
    if (Parser_match_token(self, TokenType_OWN)) {
    const char* inner = Parser_parse_type(self);
    return /* Str concat */ ({
  const char* const _tmp_l = "own ";
  const char* const _tmp_r = inner;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
} else if (Parser_match_token(self, TokenType_QUESTION)) {
    return /* Str concat */ ({
  const char* const _tmp_l = "?";
  const char* const _tmp_r = Parser_parse_type(self);
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
} else if (Parser_match_token(self, TokenType_AMP)) {
    bool is_mut = false;
    if (Parser_match_token(self, TokenType_MUT)) {
    is_mut = true;
}
    const char* inner = Parser_parse_type(self);
    if (is_mut) {
    return /* Str concat */ ({
  const char* const _tmp_l = "*mut ";
  const char* const _tmp_r = inner;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    return /* Str concat */ ({
  const char* const _tmp_l = "*";
  const char* const _tmp_r = inner;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
} else if (Parser_match_token(self, TokenType_MUL)) {
    bool is_mut = false;
    if (Parser_match_token(self, TokenType_MUT)) {
    is_mut = true;
}
    const char* inner = Parser_parse_type(self);
    if (is_mut) {
    return /* Str concat */ ({
  const char* const _tmp_l = "*mut ";
  const char* const _tmp_r = inner;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    return /* Str concat */ ({
  const char* const _tmp_l = "*";
  const char* const _tmp_r = inner;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
} else if (Parser_match_token(self, TokenType_LBRACKET)) {
    (void)(Parser_expect(self, TokenType_RBRACKET));
    return /* Str concat */ ({
  const char* const _tmp_l = "[]";
  const char* const _tmp_r = Parser_parse_type(self);
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
} else if (Parser_match_token(self, TokenType_LPAREN)) {
    ArrayList_Str types = ArrayList_Str_init(self->allocator);
    if (Parser_peek(self, 0).tok_type != TokenType_RPAREN) {
    bool done = false;
    while (!done) {
    ArrayList_Str_push(&(types), Parser_parse_type(self));
    if (!Parser_match_token(self, TokenType_COMMA)) {
    done = true;
}
}
}
    (void)(Parser_expect(self, TokenType_RPAREN));
    return /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "(";
  const char* const _tmp_r = str_array_join(types, ", ");
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ")";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
} else {
    const char* name = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value);
    if (Parser_peek(self, 0).tok_type == TokenType_LT) {
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
    return /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = name;
  const char* const _tmp_r = "<";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = str_array_join(type_args, ", ");
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ">";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    return name;
}
}
ArrayList_Str Parser_parse_generic_params(Parser* self) {
    ArrayList_Str type_params = ArrayList_Str_init(self->allocator);
    if (Parser_peek(self, 0).tok_type == TokenType_LT) {
    (void)(Parser_advance(self));
    bool done = false;
    while (!done) {
    const char* tp_name = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value);
    if (Parser_match_token(self, TokenType_COLON)) {
    ArrayList_Str_push(&(type_params), /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = tp_name;
  const char* const _tmp_r = ":";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value);
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
}));
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
    if (Parser_peek(self, 0).tok_type == TokenType_LPAREN) {
    (void)(Parser_advance(self));
    ArrayList_Str names = ArrayList_Str_init(self->allocator);
    bool done = false;
    while (!done) {
    ArrayList_Str_push(&(names), tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value));
    if (!Parser_match_token(self, TokenType_COMMA)) {
    done = true;
}
}
    (void)(Parser_expect(self, TokenType_RPAREN));
    (void)(Parser_expect(self, TokenType_ASSIGN));
    int64_t val_expr = Parser_parse_expression(self, 0);
    Parser_expect_end_of_statement(self);
    return Parser_st_var_decl(self, str_array_join(names, ","), "", val_expr, is_mutable);
}
    const char* name = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value);
    const char* type_ann = "";
    if (Parser_match_token(self, TokenType_COLON)) {
    type_ann = Parser_parse_type(self);
}
    (void)(Parser_expect(self, TokenType_ASSIGN));
    int64_t val_expr = Parser_parse_expression(self, 0);
    Parser_expect_end_of_statement(self);
    return Parser_st_var_decl(self, name, type_ann, val_expr, is_mutable);
}
int64_t Parser_parse_func_decl(Parser* self) {
    (void)(Parser_advance(self));
    const char* name = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value);
    ArrayList_Str type_params = Parser_parse_generic_params(self);
    (void)(Parser_expect(self, TokenType_LPAREN));
    ArrayList_Param params = ArrayList_Param_init(self->allocator);
    if (Parser_peek(self, 0).tok_type != TokenType_RPAREN) {
    bool done = false;
    while (!done) {
    const char* param_name = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value);
    const char* param_type = "";
    if ((strcmp(param_name, "self") == 0) && (Parser_peek(self, 0).tok_type != TokenType_COLON)) {
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
    Token next_tok = Parser_peek(self, 0);
    if (((((next_tok.tok_type == TokenType_IDENTIFIER) || (next_tok.tok_type == TokenType_LPAREN)) || (next_tok.tok_type == TokenType_MUL)) || (next_tok.tok_type == TokenType_AMP)) || (next_tok.tok_type == TokenType_LBRACKET)) {
    return_type = Parser_parse_type(self);
}
}
    const char* capability = "";
    if (Parser_match_token(self, TokenType_HASH)) {
    capability = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value);
}
    Parser_expect_end_of_statement(self);
    int64_t body = Parser_parse_block(self);
    return Parser_st_func(self, name, params, return_type, body, capability, type_params);
}
int64_t Parser_parse_struct_decl(Parser* self) {
    (void)(Parser_advance(self));
    const char* name = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value);
    ArrayList_Str type_params = Parser_parse_generic_params(self);
    Parser_expect_end_of_statement(self);
    (void)(Parser_expect(self, TokenType_LBRACE));
    ArrayList_StructField fields = ArrayList_StructField_init(self->allocator);
    ArrayList_Int methods = ArrayList_Int_init(self->allocator);
    ArrayList_Int trait_impls = ArrayList_Int_init(self->allocator);
    Parser_consume_newlines(self);
    while ((Parser_peek(self, 0).tok_type != TokenType_RBRACE) && (Parser_peek(self, 0).tok_type != TokenType_EOF)) {
    if (Parser_peek(self, 0).tok_type == TokenType_FUNC) {
    ArrayList_Int_push(&(methods), Parser_parse_func_decl(self));
} else if (Parser_peek(self, 0).tok_type == TokenType_IMPL) {
    (void)(Parser_advance(self));
    const char* trait_name = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value);
    Parser_expect_end_of_statement(self);
    (void)(Parser_expect(self, TokenType_LBRACE));
    ArrayList_Int impl_methods = ArrayList_Int_init(self->allocator);
    Parser_consume_newlines(self);
    while ((Parser_peek(self, 0).tok_type != TokenType_RBRACE) && (Parser_peek(self, 0).tok_type != TokenType_EOF)) {
    ArrayList_Int_push(&(impl_methods), Parser_parse_func_decl(self));
    Parser_consume_newlines(self);
}
    (void)(Parser_expect(self, TokenType_RBRACE));
    ArrayList_Int_push(&(trait_impls), Parser_st_impl(self, name, trait_name, impl_methods));
} else {
    const char* fname = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value);
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
    const char* first_name = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value);
    const char* struct_name = "";
    const char* trait_name = "";
    if (Parser_peek(self, 0).tok_type == TokenType_FOR) {
    (void)(Parser_advance(self));
    trait_name = first_name;
    struct_name = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value);
} else {
    struct_name = first_name;
}
    Parser_expect_end_of_statement(self);
    (void)(Parser_expect(self, TokenType_LBRACE));
    ArrayList_Int methods = ArrayList_Int_init(self->allocator);
    Parser_consume_newlines(self);
    while ((Parser_peek(self, 0).tok_type != TokenType_RBRACE) && (Parser_peek(self, 0).tok_type != TokenType_EOF)) {
    ArrayList_Int_push(&(methods), Parser_parse_func_decl(self));
    Parser_consume_newlines(self);
}
    (void)(Parser_expect(self, TokenType_RBRACE));
    return Parser_st_impl(self, struct_name, trait_name, methods);
}
int64_t Parser_parse_trait_decl(Parser* self) {
    (void)(Parser_advance(self));
    const char* name = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value);
    Parser_expect_end_of_statement(self);
    (void)(Parser_expect(self, TokenType_LBRACE));
    ArrayList_Int methods = ArrayList_Int_init(self->allocator);
    Parser_consume_newlines(self);
    while ((Parser_peek(self, 0).tok_type != TokenType_RBRACE) && (Parser_peek(self, 0).tok_type != TokenType_EOF)) {
    ArrayList_Int_push(&(methods), Parser_parse_func_decl(self));
    Parser_consume_newlines(self);
}
    (void)(Parser_expect(self, TokenType_RBRACE));
    return Parser_st_trait(self, name, methods);
}
int64_t Parser_parse_enum_decl(Parser* self) {
    (void)(Parser_advance(self));
    const char* name = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value);
    ArrayList_Str type_params = Parser_parse_generic_params(self);
    Parser_expect_end_of_statement(self);
    (void)(Parser_expect(self, TokenType_LBRACE));
    ArrayList_Variant variants = ArrayList_Variant_init(self->allocator);
    Parser_consume_newlines(self);
    while ((Parser_peek(self, 0).tok_type != TokenType_RBRACE) && (Parser_peek(self, 0).tok_type != TokenType_EOF)) {
    (void)(Parser_expect(self, TokenType_CASE));
    const char* v_name = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value);
    ArrayList_Param v_params = ArrayList_Param_init(self->allocator);
    int64_t unnamed_count = 0;
    if (Parser_match_token(self, TokenType_LPAREN)) {
    if (Parser_peek(self, 0).tok_type != TokenType_RPAREN) {
    bool done = false;
    while (!done) {
    const char* pname_or_type = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value);
    if (Parser_peek(self, 0).tok_type == TokenType_COLON) {
    (void)(Parser_advance(self));
    ArrayList_Param_push(&(v_params), (Param){ .name = pname_or_type, .ptype = Parser_parse_type(self) });
} else {
    const char* pname = "value";
    if (unnamed_count > 0) {
    pname = "value0";
}
    unnamed_count = (unnamed_count + 1);
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
    const char* name = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value);
    Parser_expect_end_of_statement(self);
    (void)(Parser_expect(self, TokenType_LBRACE));
    ArrayList_Str variants = ArrayList_Str_init(self->allocator);
    Parser_consume_newlines(self);
    while ((Parser_peek(self, 0).tok_type != TokenType_RBRACE) && (Parser_peek(self, 0).tok_type != TokenType_EOF)) {
    if (Parser_match_token(self, TokenType_CASE)) {
    (void)(0);
}
    const char* v_name = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value);
    ArrayList_Str_push(&(variants), v_name);
    Parser_expect_end_of_statement(self);
    Parser_consume_newlines(self);
}
    (void)(Parser_expect(self, TokenType_RBRACE));
    return Parser_st_error(self, name, variants);
}
int64_t Parser_parse_match_stmt(Parser* self) {
    (void)(Parser_advance(self));
    int64_t expr = Parser_parse_expression(self, 0);
    Parser_expect_end_of_statement(self);
    (void)(Parser_expect(self, TokenType_LBRACE));
    ArrayList_MatchCase cases = ArrayList_MatchCase_init(self->allocator);
    Parser_consume_newlines(self);
    while ((Parser_peek(self, 0).tok_type != TokenType_RBRACE) && (Parser_peek(self, 0).tok_type != TokenType_EOF)) {
    (void)(Parser_expect(self, TokenType_CASE));
    int64_t pattern = Parser_parse_pattern(self);
    (void)(Parser_expect(self, TokenType_FAT_ARROW));
    Parser_consume_newlines(self);
    int64_t body = (-1);
    if (Parser_peek(self, 0).tok_type == TokenType_LBRACE) {
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
    return Parser_st_match(self, expr, cases);
}
int64_t Parser_parse_pattern(Parser* self) {
    Token tok = Parser_peek(self, 0);
    if (tok.tok_type == TokenType_DOT) {
    (void)(Parser_advance(self));
    const char* v_name = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value);
    ArrayList_Str bindings = ArrayList_Str_init(self->allocator);
    if (Parser_match_token(self, TokenType_LPAREN)) {
    if (Parser_peek(self, 0).tok_type != TokenType_RPAREN) {
    bool done = false;
    while (!done) {
    ArrayList_Str_push(&(bindings), tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value));
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
    printf("%s\n", "parse_pattern failed!");
    exit(1);
}
    return (-1);
}
}
int64_t Parser_add_pattern(Parser* self, PatternNode p) {
    ArrayList_PatternNode_push(self->pattern_pool, p);
    return (ArrayList_PatternNode_length(self->pattern_pool) - 1);
}
int64_t Parser_parse_unsafe_block(Parser* self) {
    (void)(Parser_advance(self));
    Parser_expect_end_of_statement(self);
    return Parser_st_unsafe(self, Parser_parse_block(self));
}
int64_t Parser_parse_extern_decl(Parser* self) {
    (void)(Parser_advance(self));
    (void)(Parser_expect(self, TokenType_FUNC));
    const char* name = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value);
    (void)(Parser_expect(self, TokenType_LPAREN));
    ArrayList_Param params = ArrayList_Param_init(self->allocator);
    if (Parser_peek(self, 0).tok_type != TokenType_RPAREN) {
    bool done = false;
    while (!done) {
    const char* param_name = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value);
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
    Token next_tok = Parser_peek(self, 0);
    if (((((next_tok.tok_type == TokenType_IDENTIFIER) || (next_tok.tok_type == TokenType_LPAREN)) || (next_tok.tok_type == TokenType_MUL)) || (next_tok.tok_type == TokenType_AMP)) || (next_tok.tok_type == TokenType_LBRACKET)) {
    return_type = Parser_parse_type(self);
}
}
    Parser_expect_end_of_statement(self);
    return Parser_st_extern(self, name, params, return_type);
}
int64_t Parser_parse_if_stmt(Parser* self) {
    (void)(Parser_advance(self));
    if (Parser_peek(self, 0).tok_type == TokenType_LET) {
    (void)(Parser_advance(self));
    const char* var_name = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value);
    (void)(Parser_expect(self, TokenType_ASSIGN));
    int64_t cond_expr = Parser_parse_expression(self, 0);
    Parser_expect_end_of_statement(self);
    int64_t then_branch = Parser_parse_block(self);
    int64_t else_branch = (-1);
    Parser_consume_newlines(self);
    if (Parser_peek(self, 0).tok_type == TokenType_ELSE) {
    (void)(Parser_advance(self));
    if (Parser_peek(self, 0).tok_type == TokenType_IF) {
    ArrayList_Int stmts = ArrayList_Int_init(self->allocator);
    ArrayList_Int_push(&(stmts), Parser_parse_if_stmt(self));
    else_branch = Parser_st_block(self, stmts);
} else {
    Parser_expect_end_of_statement(self);
    else_branch = Parser_parse_block(self);
}
}
    return Parser_st_if_let(self, var_name, cond_expr, then_branch, else_branch);
}
    int64_t cond_expr = Parser_parse_expression(self, 0);
    Parser_expect_end_of_statement(self);
    int64_t then_branch = Parser_parse_block(self);
    int64_t else_branch = (-1);
    Parser_consume_newlines(self);
    if (Parser_peek(self, 0).tok_type == TokenType_ELSE) {
    (void)(Parser_advance(self));
    if (Parser_peek(self, 0).tok_type == TokenType_IF) {
    ArrayList_Int stmts = ArrayList_Int_init(self->allocator);
    ArrayList_Int_push(&(stmts), Parser_parse_if_stmt(self));
    else_branch = Parser_st_block(self, stmts);
} else {
    Parser_expect_end_of_statement(self);
    else_branch = Parser_parse_block(self);
}
}
    return Parser_st_if(self, cond_expr, then_branch, else_branch);
}
int64_t Parser_parse_while_stmt(Parser* self) {
    (void)(Parser_advance(self));
    int64_t cond_expr = Parser_parse_expression(self, 0);
    Parser_expect_end_of_statement(self);
    return Parser_st_while(self, cond_expr, Parser_parse_block(self));
}
int64_t Parser_parse_for_stmt(Parser* self) {
    (void)(Parser_advance(self));
    const char* var_name = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value);
    (void)(Parser_expect(self, TokenType_IN));
    int64_t expr = Parser_parse_expression(self, 0);
    ExprNode expr_node = ArrayList_ExprNode_get(self->expr_pool, expr);
    int64_t range_start = (-1);
    int64_t range_end = (-1);
    bool is_inclusive = false;
    if (expr_node.kind == ExprKind_ek_range) {
    range_start = expr_node.range_start;
    range_end = expr_node.range_end;
    is_inclusive = expr_node.range_inclusive;
} else {
    {
    printf("%s\n", "parse_for_stmt failed!");
    exit(1);
}
}
    Parser_expect_end_of_statement(self);
    return Parser_st_for(self, var_name, range_start, range_end, is_inclusive, Parser_parse_block(self));
}
int64_t Parser_parse_return_stmt(Parser* self) {
    (void)(Parser_advance(self));
    int64_t val_expr = (-1);
    Token next = Parser_peek(self, 0);
    if ((((next.tok_type != TokenType_NEWLINE) && (next.tok_type != TokenType_RBRACE)) && (next.tok_type != TokenType_DEDENT)) && (next.tok_type != TokenType_EOF)) {
    val_expr = Parser_parse_expression(self, 0);
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
int64_t Parser_parse_print_stmt(Parser* self) {
    (void)(Parser_advance(self));
    (void)(Parser_expect(self, TokenType_LPAREN));
    int64_t val_expr = Parser_parse_expression(self, 0);
    (void)(Parser_expect(self, TokenType_RPAREN));
    Parser_expect_end_of_statement(self);
    return Parser_st_print(self, val_expr);
}
int64_t Parser_parse_defer_stmt(Parser* self) {
    (void)(Parser_advance(self));
    int64_t body = (-1);
    if (Parser_peek(self, 0).tok_type == TokenType_NEWLINE) {
    Parser_expect_end_of_statement(self);
    body = Parser_parse_block(self);
} else {
    body = Parser_parse_statement(self);
}
    return Parser_st_defer(self, body);
}
int64_t Parser_parse_expr_or_assignment_stmt(Parser* self) {
    int64_t expr = Parser_parse_expression(self, 0);
    Token next = Parser_peek(self, 0);
    if (((next.tok_type == TokenType_ASSIGN) || (next.tok_type == TokenType_PLUS_ASSIGN)) || (next.tok_type == TokenType_MINUS_ASSIGN)) {
    Token op_tok = Parser_advance(self);
    int64_t val_expr = Parser_parse_expression(self, 0);
    Parser_expect_end_of_statement(self);
    return Parser_st_assign(self, expr, val_expr, token_op_str(op_tok.tok_type));
}
    Parser_expect_end_of_statement(self);
    return Parser_st_expr(self, expr);
}
int64_t Parser_parse_block(Parser* self) {
    Parser_consume_newlines(self);
    ArrayList_Int stmts = ArrayList_Int_init(self->allocator);
    (void)(Parser_expect(self, TokenType_LBRACE));
    Parser_consume_newlines(self);
    while ((Parser_peek(self, 0).tok_type != TokenType_RBRACE) && (Parser_peek(self, 0).tok_type != TokenType_EOF)) {
    int64_t stmt = Parser_parse_statement(self);
    if (stmt >= 0) {
    ArrayList_Int_push(&(stmts), stmt);
}
    Parser_consume_newlines(self);
}
    if (Parser_peek(self, 0).tok_type == TokenType_EOF) {
    {
    printf("%s\n", "parse_block LBRACE EOF failed!");
    exit(1);
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
    ArrayList_Str_push(&(path), tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value));
    if (!Parser_match_token(self, TokenType_DOT)) {
    done = true;
}
}
    Parser_expect_end_of_statement(self);
    return Parser_st_import(self, path, "");
}
int64_t Parser_parse_import_stmt_new(Parser* self) {
    (void)(Parser_advance(self));
    const char* first_name = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value);
    if (Parser_peek(self, 0).tok_type == TokenType_FROM) {
    (void)(Parser_advance(self));
    ArrayList_Str path = ArrayList_Str_init(self->allocator);
    bool done = false;
    while (!done) {
    ArrayList_Str_push(&(path), tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value));
    if (!Parser_match_token(self, TokenType_DOT)) {
    done = true;
}
}
    const char* alias = "";
    if (Parser_peek(self, 0).tok_type == TokenType_AS) {
    (void)(Parser_advance(self));
    alias = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value);
}
    Parser_expect_end_of_statement(self);
    return Parser_st_import(self, path, alias);
} else {
    ArrayList_Str path = ArrayList_Str_init(self->allocator);
    ArrayList_Str_push(&(path), first_name);
    while (Parser_match_token(self, TokenType_DOT)) {
    ArrayList_Str_push(&(path), tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value));
}
    const char* alias = "";
    if (Parser_peek(self, 0).tok_type == TokenType_AS) {
    (void)(Parser_advance(self));
    alias = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value);
}
    Parser_expect_end_of_statement(self);
    return Parser_st_import(self, path, alias);
}
}
int64_t Parser_parse_cimport_stmt(Parser* self) {
    (void)(Parser_advance(self));
    Token header_tok = Parser_expect(self, TokenType_STRING_LIT);
    const char* header = tv_get_str(header_tok.value);
    const char* alias = "";
    if (Parser_peek(self, 0).tok_type == TokenType_AS) {
    (void)(Parser_advance(self));
    alias = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value);
}
    Parser_expect_end_of_statement(self);
    return Parser_st_cimport(self, header, alias);
}
int64_t Parser_parse_expression(Parser* self, int64_t precedence) {
    int64_t left = Parser_parse_primary(self);
    bool done = false;
    while (!done) {
    Token op_tok = Parser_peek(self, 0);
    int64_t op_prec = token_precedence(op_tok.tok_type);
    if ((op_prec == 0) || (op_prec <= precedence)) {
    done = true;
} else {
    (void)(Parser_advance(self));
    if (op_tok.tok_type == TokenType_DOT) {
    const char* member_name = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value);
    if (Parser_peek(self, 0).tok_type == TokenType_LPAREN) {
    (void)(Parser_advance(self));
    if ((Parser_peek(self, 0).tok_type == TokenType_IDENTIFIER) && (Parser_peek(self, 1).tok_type == TokenType_COLON)) {
    ArrayList_FieldInit fields = ArrayList_FieldInit_init(self->allocator);
    if (Parser_peek(self, 0).tok_type != TokenType_RPAREN) {
    bool fields_done = false;
    while (!fields_done) {
    const char* f_name = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value);
    (void)(Parser_expect(self, TokenType_COLON));
    ArrayList_FieldInit_push(&(fields), (FieldInit){ .name = f_name, .value = Parser_parse_expression(self, 0) });
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
    if (ArrayList_Str_length(&(left_node.ident_type_args)) > 0) {
    full_name = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = full_name;
  const char* const _tmp_r = "<";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = str_array_join(left_node.ident_type_args, ", ");
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ">";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
}
    left = Parser_ex_struct_init(self, /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = full_name;
  const char* const _tmp_r = ".";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = member_name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
}), fields);
} else {
    ArrayList_Int args = ArrayList_Int_init(self->allocator);
    if (Parser_peek(self, 0).tok_type != TokenType_RPAREN) {
    bool args_done = false;
    while (!args_done) {
    ArrayList_Int_push(&(args), Parser_parse_expression(self, 0));
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
    if ((Parser_peek(self, 0).tok_type == TokenType_DOTDOT) || (Parser_peek(self, 0).tok_type == TokenType_DOTDOTEQ)) {
    int64_t lower = (-1);
    int64_t upper = (-1);
    Token slice_tok = Parser_advance(self);
    bool is_inclusive = (slice_tok.tok_type == TokenType_DOTDOTEQ);
    if (Parser_peek(self, 0).tok_type != TokenType_RBRACKET) {
    upper = Parser_parse_expression(self, 0);
}
    left = Parser_ex_slice(self, left, lower, upper, is_inclusive);
} else {
    int64_t lower = Parser_parse_expression(self, 0);
    ExprNode lower_node = ArrayList_ExprNode_get(self->expr_pool, lower);
    if (lower_node.kind == ExprKind_ek_range) {
    left = Parser_ex_slice(self, left, lower_node.range_start, lower_node.range_end, lower_node.range_inclusive);
} else if ((Parser_peek(self, 0).tok_type == TokenType_DOTDOT) || (Parser_peek(self, 0).tok_type == TokenType_DOTDOTEQ)) {
    Token slice_tok = Parser_advance(self);
    bool is_inclusive = (slice_tok.tok_type == TokenType_DOTDOTEQ);
    int64_t upper = (-1);
    if (Parser_peek(self, 0).tok_type != TokenType_RBRACKET) {
    upper = Parser_parse_expression(self, 0);
}
    left = Parser_ex_slice(self, left, lower, upper, is_inclusive);
} else {
    left = Parser_ex_index(self, left, lower);
}
}
    (void)(Parser_expect(self, TokenType_RBRACKET));
} else if ((op_tok.tok_type == TokenType_DOTDOT) || (op_tok.tok_type == TokenType_DOTDOTEQ)) {
    bool is_inclusive = (op_tok.tok_type == TokenType_DOTDOTEQ);
    int64_t right = (-1);
    Token next = Parser_peek(self, 0);
    if (((((((next.tok_type != TokenType_RBRACKET) && (next.tok_type != TokenType_COMMA)) && (next.tok_type != TokenType_NEWLINE)) && (next.tok_type != TokenType_SEMICOLON)) && (next.tok_type != TokenType_RBRACE)) && (next.tok_type != TokenType_DEDENT)) && (next.tok_type != TokenType_EOF)) {
    right = Parser_parse_expression(self, op_prec);
}
    left = Parser_ex_range(self, left, right, is_inclusive);
} else if (op_tok.tok_type == TokenType_CATCH) {
    const char* var_name = "";
    if (Parser_match_token(self, TokenType_PIPE)) {
    var_name = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value);
    (void)(Parser_expect(self, TokenType_PIPE));
}
    int64_t fallback = (-1);
    Token next = Parser_peek(self, 0);
    if (next.tok_type == TokenType_NEWLINE) {
    fallback = Parser_parse_block(self);
} else if (next.tok_type == TokenType_RETURN) {
    (void)(Parser_advance(self));
    int64_t ret_val = (-1);
    Token follow = Parser_peek(self, 0);
    if (((((follow.tok_type != TokenType_NEWLINE) && (follow.tok_type != TokenType_SEMICOLON)) && (follow.tok_type != TokenType_RBRACE)) && (follow.tok_type != TokenType_DEDENT)) && (follow.tok_type != TokenType_EOF)) {
    ret_val = Parser_parse_expression(self, 0);
}
    int64_t ret_stmt = Parser_st_return(self, ret_val);
    ArrayList_Int stmts = ArrayList_Int_init(self->allocator);
    ArrayList_Int_push(&(stmts), ret_stmt);
    fallback = Parser_st_block(self, stmts);
} else if (next.tok_type == TokenType_PRINT) {
    (void)(Parser_advance(self));
    int64_t pr_val = Parser_parse_expression(self, 0);
    int64_t pr_stmt = Parser_st_print(self, pr_val);
    ArrayList_Int stmts = ArrayList_Int_init(self->allocator);
    ArrayList_Int_push(&(stmts), pr_stmt);
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
    Token tok = Parser_peek(self, 0);
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
    return Parser_ex_check(self, Parser_parse_expression(self, 5));
} else if (tok.tok_type == TokenType_TRY) {
    (void)(Parser_advance(self));
    return Parser_ex_try(self, Parser_parse_expression(self, 5));
} else if (tok.tok_type == TokenType_OWN) {
    (void)(Parser_advance(self));
    return Parser_ex_unop(self, "own", Parser_parse_expression(self, 5));
} else if (tok.tok_type == TokenType_ASM) {
    (void)(Parser_advance(self));
    bool is_volatile = false;
    if (Parser_match_token(self, TokenType_VOLATILE)) {
    is_volatile = true;
}
    (void)(Parser_expect(self, TokenType_LPAREN));
    const char* asm_code = tv_get_str(Parser_expect(self, TokenType_STRING_LIT).value);
    ArrayList_AsmOutput outputs = ArrayList_AsmOutput_init(self->allocator);
    ArrayList_AsmInput inputs = ArrayList_AsmInput_init(self->allocator);
    ArrayList_Str clobbers = ArrayList_Str_init(self->allocator);
    if (Parser_match_token(self, TokenType_COLON)) {
    bool done = false;
    while (!done) {
    TokenType next_tt = Parser_peek(self, 0).tok_type;
    if (((next_tt == TokenType_COLON) || (next_tt == TokenType_RPAREN)) || (next_tt == TokenType_EOF)) {
    done = true;
} else {
    (void)(Parser_expect(self, TokenType_LBRACKET));
    const char* out_name = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value);
    (void)(Parser_expect(self, TokenType_RBRACKET));
    const char* constraint = tv_get_str(Parser_expect(self, TokenType_STRING_LIT).value);
    (void)(Parser_expect(self, TokenType_LPAREN));
    const char* type_name = "";
    int64_t expr_idx = (-1);
    if (Parser_match_token(self, TokenType_ARROW)) {
    type_name = Parser_parse_type(self);
} else {
    expr_idx = Parser_parse_expression(self, 0);
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
    TokenType next_tt = Parser_peek(self, 0).tok_type;
    if (((next_tt == TokenType_COLON) || (next_tt == TokenType_RPAREN)) || (next_tt == TokenType_EOF)) {
    done = true;
} else {
    (void)(Parser_expect(self, TokenType_LBRACKET));
    const char* in_name = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value);
    (void)(Parser_expect(self, TokenType_RBRACKET));
    const char* constraint = tv_get_str(Parser_expect(self, TokenType_STRING_LIT).value);
    (void)(Parser_expect(self, TokenType_LPAREN));
    int64_t expr_idx = Parser_parse_expression(self, 0);
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
    TokenType next_tt = Parser_peek(self, 0).tok_type;
    if ((next_tt == TokenType_RPAREN) || (next_tt == TokenType_EOF)) {
    done = true;
} else {
    const char* clobber = tv_get_str(Parser_expect(self, TokenType_STRING_LIT).value);
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
    const char* ident = tv_get_str(Parser_advance(self).value);
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
    int64_t ci = 0;
    while (ci < ArrayList_Str_length(&(type_args))) {
    ArrayList_Str_push(&(id_type_args), ArrayList_Str_get(&(type_args), ci));
    ci = (ci + 1);
}
    if (Parser_peek(self, 0).tok_type == TokenType_LPAREN) {
    (void)(Parser_advance(self));
    if ((Parser_peek(self, 0).tok_type == TokenType_IDENTIFIER) && (Parser_peek(self, 1).tok_type == TokenType_COLON)) {
    ArrayList_FieldInit fields = ArrayList_FieldInit_init(self->allocator);
    if (Parser_peek(self, 0).tok_type != TokenType_RPAREN) {
    bool fields_done = false;
    while (!fields_done) {
    const char* f_name = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value);
    (void)(Parser_expect(self, TokenType_COLON));
    ArrayList_FieldInit_push(&(fields), (FieldInit){ .name = f_name, .value = Parser_parse_expression(self, 0) });
    if (!Parser_match_token(self, TokenType_COMMA)) {
    fields_done = true;
}
}
}
    (void)(Parser_expect(self, TokenType_RPAREN));
    ArrayList_Str sa_type_args = ArrayList_Str_init(self->allocator);
    int64_t cj = 0;
    while (cj < ArrayList_Str_length(&(type_args))) {
    ArrayList_Str_push(&(sa_type_args), ArrayList_Str_get(&(type_args), cj));
    cj = (cj + 1);
}
    const char* type_args_str = str_array_join(sa_type_args, ", ");
    return Parser_ex_struct_init(self, /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = ident;
  const char* const _tmp_r = "<";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = type_args_str;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ">";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
}), fields);
}
    ArrayList_Int args = ArrayList_Int_init(self->allocator);
    if (Parser_peek(self, 0).tok_type != TokenType_RPAREN) {
    bool args_done = false;
    while (!args_done) {
    ArrayList_Int_push(&(args), Parser_parse_expression(self, 0));
    if (!Parser_match_token(self, TokenType_COMMA)) {
    args_done = true;
}
}
}
    (void)(Parser_expect(self, TokenType_RPAREN));
    return Parser_ex_call_with(self, ident, args, type_args);
}
    ExprNode id_node = new_expr_node(ExprKind_ek_identifier);
    id_node.ident_name = ident;
    id_node.ident_type_args = id_type_args;
    ArrayList_ExprNode_push(self->expr_pool, id_node);
    return (ArrayList_ExprNode_length(self->expr_pool) - 1);
} else if (Parser_peek(self, 1).tok_type == TokenType_LPAREN) {
    const char* ident = tv_get_str(Parser_advance(self).value);
    (void)(Parser_advance(self));
    if ((Parser_peek(self, 0).tok_type == TokenType_IDENTIFIER) && (Parser_peek(self, 1).tok_type == TokenType_COLON)) {
    ArrayList_FieldInit fields = ArrayList_FieldInit_init(self->allocator);
    if (Parser_peek(self, 0).tok_type != TokenType_RPAREN) {
    bool fields_done = false;
    while (!fields_done) {
    const char* f_name = tv_get_str(Parser_expect(self, TokenType_IDENTIFIER).value);
    (void)(Parser_expect(self, TokenType_COLON));
    ArrayList_FieldInit_push(&(fields), (FieldInit){ .name = f_name, .value = Parser_parse_expression(self, 0) });
    if (!Parser_match_token(self, TokenType_COMMA)) {
    fields_done = true;
}
}
}
    (void)(Parser_expect(self, TokenType_RPAREN));
    return Parser_ex_struct_init(self, ident, fields);
} else {
    ArrayList_Int args = ArrayList_Int_init(self->allocator);
    if (Parser_peek(self, 0).tok_type != TokenType_RPAREN) {
    bool args_done = false;
    while (!args_done) {
    ArrayList_Int_push(&(args), Parser_parse_expression(self, 0));
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
    return Parser_ex_ident(self, tv_get_str(tok.value));
}
} else if (tok.tok_type == TokenType_MINUS) {
    (void)(Parser_advance(self));
    return Parser_ex_unop(self, "-", Parser_parse_expression(self, 7));
} else if (tok.tok_type == TokenType_NOT) {
    (void)(Parser_advance(self));
    return Parser_ex_unop(self, "!", Parser_parse_expression(self, 7));
} else if (tok.tok_type == TokenType_BITNOT) {
    (void)(Parser_advance(self));
    return Parser_ex_unop(self, "~", Parser_parse_expression(self, 7));
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
    return Parser_ex_borrow(self, Parser_parse_expression(self, 8), is_mut);
} else if (tok.tok_type == TokenType_MUL) {
    (void)(Parser_advance(self));
    return Parser_ex_deref(self, Parser_parse_expression(self, 8));
} else if (tok.tok_type == TokenType_LBRACKET) {
    (void)(Parser_advance(self));
    ArrayList_Int elements = ArrayList_Int_init(self->allocator);
    if (Parser_peek(self, 0).tok_type != TokenType_RBRACKET) {
    bool done = false;
    while (!done) {
    ArrayList_Int_push(&(elements), Parser_parse_expression(self, 0));
    if (!Parser_match_token(self, TokenType_COMMA)) {
    done = true;
}
}
}
    (void)(Parser_expect(self, TokenType_RBRACKET));
    return Parser_ex_array(self, elements);
} else if (tok.tok_type == TokenType_LPAREN) {
    (void)(Parser_advance(self));
    int64_t first = Parser_parse_expression(self, 0);
    if (Parser_peek(self, 0).tok_type == TokenType_COMMA) {
    ArrayList_Int elements = ArrayList_Int_init(self->allocator);
    ArrayList_Int_push(&(elements), first);
    while (Parser_match_token(self, TokenType_COMMA)) {
    if (Parser_peek(self, 0).tok_type != TokenType_RPAREN) {
    ArrayList_Int_push(&(elements), Parser_parse_expression(self, 0));
}
}
    (void)(Parser_expect(self, TokenType_RPAREN));
    return Parser_ex_tuple(self, elements);
}
    (void)(Parser_expect(self, TokenType_RPAREN));
    return first;
} else {
    {
    printf("%s\n", "parse_primary failed!");
    printf("%s\n", "Line: ");
    print_int(tok.line);
    printf("%s\n", "Col: ");
    print_int(tok.column);
    printf("%s\n", "Token type int: ");
    print_int(((int64_t)(tok.tok_type)));
    exit(1);
}
    return (-1);
}
}
ArrayList_Symbol ArrayList_Symbol_init(KaiAllocator* allocator) {
    ArrayList_Symbol self = (ArrayList_Symbol){0};
    self.len = 0;
    self.cap = 4;
    self.allocator = allocator;
    {
    self.data = (Symbol*)(KaiAllocator_alloc(allocator, (self.cap * sizeof(Symbol)), 1));
}
    return self;
}
void ArrayList_Symbol_push(ArrayList_Symbol* self, Symbol item) {
    if (self->len == self->cap) {
    int64_t new_cap = (self->cap * 2);
    {
    Symbol* new_data = (Symbol*)(KaiAllocator_alloc(self->allocator, (new_cap * sizeof(Symbol)), 1));
    int64_t i = 0;
    while (i < self->len) {
    (new_data)[i] = (self->data)[i];
    i = (i + 1);
}
    KaiAllocator_free(self->allocator, (char*)(self->data));
    self->data = new_data;
    self->cap = new_cap;
}
}
    (self->data)[self->len] = item;
    self->len = (self->len + 1);
}
Symbol ArrayList_Symbol_get(ArrayList_Symbol* self, int64_t index) {
    if ((index < 0) || (index >= self->len)) {
    {
    exit(1);
}
}
    return (self->data)[index];
}
void ArrayList_Symbol_set(ArrayList_Symbol* self, int64_t index, Symbol item) {
    if ((index < 0) || (index >= self->len)) {
    {
    exit(1);
}
}
    (self->data)[index] = item;
}
Symbol ArrayList_Symbol_pop(ArrayList_Symbol* self) {
    if (self->len == 0) {
    {
    exit(1);
}
}
    self->len = (self->len - 1);
    return (self->data)[self->len];
}
int64_t ArrayList_Symbol_length(ArrayList_Symbol* self) {
    return self->len;
}
void ArrayList_Symbol_deinit(ArrayList_Symbol* self) {
    {
    KaiAllocator_free(self->allocator, (char*)(self->data));
}
}
SymbolTable SymbolTable_init(KaiAllocator* allocator, int64_t parent_idx) {
    SymbolTable self = (SymbolTable){0};
    self.allocator = allocator;
    self.entries = ArrayList_Symbol_init(allocator);
    self.parent_idx = parent_idx;
    return self;
}
void SymbolTable_define(SymbolTable* self, const char* name, const char* type_name, bool is_mutable, const char* kind, const char* llvm_value) {
    ArrayList_Symbol_push(&(self->entries), (Symbol){ .name = name, .type_name = type_name, .is_mutable = is_mutable, .kind = kind, .llvm_value = llvm_value, .moved = false });
}
ArrayList_SymbolTable ArrayList_SymbolTable_init(KaiAllocator* allocator) {
    ArrayList_SymbolTable self = (ArrayList_SymbolTable){0};
    self.len = 0;
    self.cap = 4;
    self.allocator = allocator;
    {
    self.data = (SymbolTable*)(KaiAllocator_alloc(allocator, (self.cap * sizeof(SymbolTable)), 1));
}
    return self;
}
void ArrayList_SymbolTable_push(ArrayList_SymbolTable* self, SymbolTable item) {
    if (self->len == self->cap) {
    int64_t new_cap = (self->cap * 2);
    {
    SymbolTable* new_data = (SymbolTable*)(KaiAllocator_alloc(self->allocator, (new_cap * sizeof(SymbolTable)), 1));
    int64_t i = 0;
    while (i < self->len) {
    (new_data)[i] = (self->data)[i];
    i = (i + 1);
}
    KaiAllocator_free(self->allocator, (char*)(self->data));
    self->data = new_data;
    self->cap = new_cap;
}
}
    (self->data)[self->len] = item;
    self->len = (self->len + 1);
}
SymbolTable ArrayList_SymbolTable_get(ArrayList_SymbolTable* self, int64_t index) {
    if ((index < 0) || (index >= self->len)) {
    {
    exit(1);
}
}
    return (self->data)[index];
}
void ArrayList_SymbolTable_set(ArrayList_SymbolTable* self, int64_t index, SymbolTable item) {
    if ((index < 0) || (index >= self->len)) {
    {
    exit(1);
}
}
    (self->data)[index] = item;
}
SymbolTable ArrayList_SymbolTable_pop(ArrayList_SymbolTable* self) {
    if (self->len == 0) {
    {
    exit(1);
}
}
    self->len = (self->len - 1);
    return (self->data)[self->len];
}
int64_t ArrayList_SymbolTable_length(ArrayList_SymbolTable* self) {
    return self->len;
}
void ArrayList_SymbolTable_deinit(ArrayList_SymbolTable* self) {
    {
    KaiAllocator_free(self->allocator, (char*)(self->data));
}
}
int64_t SymbolTable_lookup(SymbolTable* self, const char* name, ArrayList_SymbolTable* tables) {
    int64_t i = 0;
    while (i < ArrayList_Symbol_length(&(self->entries))) {
    if (strcmp(ArrayList_Symbol_get(&(self->entries), i).name, name) == 0) {
    return i;
}
    i = (i + 1);
}
    if (self->parent_idx >= 0) {
    SymbolTable parent = ArrayList_SymbolTable_get(tables, self->parent_idx);
    return SymbolTable_lookup(&(parent), name, tables);
}
    return (-1);
}
Symbol SymbolTable_lookup_symbol(SymbolTable* self, const char* name, ArrayList_SymbolTable* tables) {
    int64_t i = 0;
    while (i < ArrayList_Symbol_length(&(self->entries))) {
    if (strcmp(ArrayList_Symbol_get(&(self->entries), i).name, name) == 0) {
    return ArrayList_Symbol_get(&(self->entries), i);
}
    i = (i + 1);
}
    if (self->parent_idx >= 0) {
    SymbolTable parent = ArrayList_SymbolTable_get(tables, self->parent_idx);
    return SymbolTable_lookup_symbol(&(parent), name, tables);
}
    return (Symbol){ .name = "", .type_name = "", .is_mutable = false, .kind = "", .llvm_value = "", .moved = false };
}
void SymbolTable_mark_moved(SymbolTable* self, const char* name, ArrayList_SymbolTable* tables) {
    int64_t i = 0;
    while (i < ArrayList_Symbol_length(&(self->entries))) {
    if (strcmp(ArrayList_Symbol_get(&(self->entries), i).name, name) == 0) {
    Symbol sym = ArrayList_Symbol_get(&(self->entries), i);
    sym.moved = true;
    ArrayList_Symbol_set(&(self->entries), i, sym);
    return;
}
    i = (i + 1);
}
    if (self->parent_idx >= 0) {
    SymbolTable parent = ArrayList_SymbolTable_get(tables, self->parent_idx);
    SymbolTable_mark_moved(&(parent), name, tables);
    ArrayList_SymbolTable_set(tables, self->parent_idx, parent);
}
}
int64_t SymbolTable_lookup_current(SymbolTable* self, const char* name) {
    int64_t i = 0;
    while (i < ArrayList_Symbol_length(&(self->entries))) {
    if (strcmp(ArrayList_Symbol_get(&(self->entries), i).name, name) == 0) {
    return i;
}
    i = (i + 1);
}
    return (-1);
}
ArrayList_StructInfo ArrayList_StructInfo_init(KaiAllocator* allocator) {
    ArrayList_StructInfo self = (ArrayList_StructInfo){0};
    self.len = 0;
    self.cap = 4;
    self.allocator = allocator;
    {
    self.data = (StructInfo*)(KaiAllocator_alloc(allocator, (self.cap * sizeof(StructInfo)), 1));
}
    return self;
}
void ArrayList_StructInfo_push(ArrayList_StructInfo* self, StructInfo item) {
    if (self->len == self->cap) {
    int64_t new_cap = (self->cap * 2);
    {
    StructInfo* new_data = (StructInfo*)(KaiAllocator_alloc(self->allocator, (new_cap * sizeof(StructInfo)), 1));
    int64_t i = 0;
    while (i < self->len) {
    (new_data)[i] = (self->data)[i];
    i = (i + 1);
}
    KaiAllocator_free(self->allocator, (char*)(self->data));
    self->data = new_data;
    self->cap = new_cap;
}
}
    (self->data)[self->len] = item;
    self->len = (self->len + 1);
}
StructInfo ArrayList_StructInfo_get(ArrayList_StructInfo* self, int64_t index) {
    if ((index < 0) || (index >= self->len)) {
    {
    exit(1);
}
}
    return (self->data)[index];
}
void ArrayList_StructInfo_set(ArrayList_StructInfo* self, int64_t index, StructInfo item) {
    if ((index < 0) || (index >= self->len)) {
    {
    exit(1);
}
}
    (self->data)[index] = item;
}
StructInfo ArrayList_StructInfo_pop(ArrayList_StructInfo* self) {
    if (self->len == 0) {
    {
    exit(1);
}
}
    self->len = (self->len - 1);
    return (self->data)[self->len];
}
int64_t ArrayList_StructInfo_length(ArrayList_StructInfo* self) {
    return self->len;
}
void ArrayList_StructInfo_deinit(ArrayList_StructInfo* self) {
    {
    KaiAllocator_free(self->allocator, (char*)(self->data));
}
}
TypeChecker TypeChecker_init(KaiAllocator* allocator, ArrayList_StmtNode* stmt_pool, ArrayList_ExprNode* expr_pool, ArrayList_PatternNode* pattern_pool) {
    TypeChecker self = (TypeChecker){0};
    self.allocator = allocator;
    self.stmt_pool = stmt_pool;
    self.expr_pool = expr_pool;
    self.pattern_pool = pattern_pool;
    self.symbol_tables = ArrayList_SymbolTable_init(allocator);
    self.current_table_idx = (-1);
    self.struct_info = ArrayList_StructInfo_init(allocator);
    self.has_error = false;
    self.current_func_ret_type = "";
    return self;
}
void TypeChecker_enter_scope(TypeChecker* self) {
    SymbolTable new_table = (SymbolTable){ .entries = ArrayList_Symbol_init(self->allocator), .parent_idx = self->current_table_idx, .allocator = self->allocator };
    new_table = SymbolTable_init(self->allocator, self->current_table_idx);
    ArrayList_SymbolTable_push(&(self->symbol_tables), new_table);
    self->current_table_idx = (ArrayList_SymbolTable_length(&(self->symbol_tables)) - 1);
}
void TypeChecker_exit_scope(TypeChecker* self) {
    if (self->current_table_idx >= 0) {
    SymbolTable table = ArrayList_SymbolTable_get(&(self->symbol_tables), self->current_table_idx);
    self->current_table_idx = table.parent_idx;
}
}
void TypeChecker_define_symbol(TypeChecker* self, const char* name, const char* type_name, bool is_mutable, const char* kind) {
    if (self->current_table_idx >= 0) {
    SymbolTable table = ArrayList_SymbolTable_get(&(self->symbol_tables), self->current_table_idx);
    SymbolTable_define(&(table), name, type_name, is_mutable, kind, "");
    ArrayList_SymbolTable_set(&(self->symbol_tables), self->current_table_idx, table);
}
}
bool TypeChecker_check_program(TypeChecker* self, int64_t top_stmt_idx) {
    TypeChecker_register_struct_info(self, top_stmt_idx);
    TypeChecker_enter_scope(self);
    TypeChecker_check_stmt(self, top_stmt_idx);
    TypeChecker_exit_scope(self);
    return (!self->has_error);
}
void TypeChecker_register_struct_info(TypeChecker* self, int64_t top_stmt_idx) {
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, top_stmt_idx);
    if (stmt.kind == StmtKind_sk_block) {
    int64_t i = 0;
    while (i < ArrayList_Int_length(&(stmt.block_stmts))) {
    int64_t s_idx = ArrayList_Int_get(&(stmt.block_stmts), i);
    StmtNode s = ArrayList_StmtNode_get(self->stmt_pool, s_idx);
    if (s.kind == StmtKind_sk_impl_block) {
    bool has_drop = false;
    int64_t j = 0;
    while (j < ArrayList_Int_length(&(s.impl_methods))) {
    int64_t m_idx = ArrayList_Int_get(&(s.impl_methods), j);
    StmtNode m = ArrayList_StmtNode_get(self->stmt_pool, m_idx);
    if (strcmp(m.func_name, "drop") == 0) {
    has_drop = true;
}
    j = (j + 1);
}
    ArrayList_StructInfo_push(&(self->struct_info), (StructInfo){ .name = s.impl_struct_name, .has_drop = has_drop });
}
    i = (i + 1);
}
}
}
bool TypeChecker_has_drop_method(TypeChecker* self, const char* type_name) {
    const char* clean_type = type_name;
    if ((strlen(type_name) > 4) && (strcmp(substring(type_name, 0, 4), "own ") == 0)) {
    clean_type = substring(type_name, 4, strlen(type_name));
}
    if ((strlen(clean_type) > 0) && ((((clean_type)[0] == ((char)(38))) || ((clean_type)[0] == ((char)(42)))) || ((clean_type)[0] == ((char)(63))))) {
    return false;
}
    int64_t i = 0;
    while (i < ArrayList_StructInfo_length(&(self->struct_info))) {
    StructInfo info = ArrayList_StructInfo_get(&(self->struct_info), i);
    if (strcmp(info.name, clean_type) == 0) {
    return info.has_drop;
}
    i = (i + 1);
}
    return false;
}
void TypeChecker_collect_block_drops(TypeChecker* self, int64_t stmt_idx) {
    if (self->current_table_idx < 0) {
    return;
}
    SymbolTable table = ArrayList_SymbolTable_get(&(self->symbol_tables), self->current_table_idx);
    ArrayList_DropVarEntry drop_vars = ArrayList_DropVarEntry_init(self->allocator);
    int64_t i = (ArrayList_Symbol_length(&(table.entries)) - 1);
    while (i >= 0) {
    Symbol sym = ArrayList_Symbol_get(&(table.entries), i);
    if (((strcmp(sym.kind, "var") == 0) || (strcmp(sym.kind, "param") == 0)) && (!sym.moved)) {
    const char* base_type = sym.type_name;
    if (TypeChecker_has_drop_method(self, base_type)) {
    ArrayList_DropVarEntry_push(&(drop_vars), (DropVarEntry){ .name = sym.name, .base_type = base_type });
}
}
    i = (i - 1);
}
    StmtNode block_stmt = ArrayList_StmtNode_get(self->stmt_pool, stmt_idx);
    block_stmt.block_drop_vars = drop_vars;
    ArrayList_StmtNode_set(self->stmt_pool, stmt_idx, block_stmt);
}
bool TypeChecker_is_copy_type(TypeChecker* self, const char* type_name) {
    if (strcmp(type_name, "Int") == 0) {
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
    if ((strlen(type_name) > 0) && (((type_name)[0] == ((char)(42))) || ((type_name)[0] == ((char)(38))))) {
    return true;
}
    return false;
}
PtrRefResult TypeChecker_parse_ptr_ref(TypeChecker* self, const char* type_str) {
    bool is_ptr = false;
    bool is_mut = false;
    const char* inner = type_str;
    if ((strlen(inner) > 0) && ((inner)[0] == ((char)(63)))) {
    inner = substring(inner, 1, strlen(inner));
}
    if ((strlen(inner) > 5) && (strcmp(substring(inner, 0, 5), "*mut ") == 0)) {
    is_ptr = true;
    is_mut = true;
    inner = substring(inner, 5, strlen(inner));
} else if ((strlen(inner) > 1) && ((inner)[0] == ((char)(42)))) {
    is_ptr = true;
    inner = substring(inner, 1, strlen(inner));
} else if ((strlen(inner) > 5) && (strcmp(substring(inner, 0, 5), "&mut ") == 0)) {
    is_ptr = true;
    is_mut = true;
    inner = substring(inner, 5, strlen(inner));
} else if ((strlen(inner) > 1) && ((inner)[0] == ((char)(38)))) {
    is_ptr = true;
    inner = substring(inner, 1, strlen(inner));
}
    return (PtrRefResult){ .is_ptr = is_ptr, .is_mut = is_mut, .inner = inner };
}
bool TypeChecker_types_compatible(TypeChecker* self, const char* target, const char* source) {
    const char* t = target;
    const char* s = source;
    if ((strlen(t) > 4) && (strcmp(substring(t, 0, 4), "own ") == 0)) {
    t = substring(t, 4, strlen(t));
}
    if ((strlen(s) > 4) && (strcmp(substring(s, 0, 4), "own ") == 0)) {
    s = substring(s, 4, strlen(s));
}
    if ((strcmp(t, "Void") == 0) || (strcmp(s, "Void") == 0)) {
    return true;
}
    if ((strcmp(t, "Allocator") == 0) && ((strcmp(s, "KaiAllocator") == 0) || (strcmp(s, "CAlloc") == 0))) {
    return true;
}
    if (strcmp(t, s) == 0) {
    return true;
}
    if ((strlen(t) > 0) && ((t)[0] == ((char)(63)))) {
    if (strcmp(s, "NoneType") == 0) {
    return true;
}
    const char* t_inner = substring(t, 1, strlen(t));
    const char* s_inner = s;
    if ((strlen(s) > 0) && ((s)[0] == ((char)(63)))) {
    s_inner = substring(s, 1, strlen(s));
}
    return TypeChecker_types_compatible(self, t_inner, s_inner);
}
    int64_t excl_t = (-1);
    int64_t i = 0;
    while (i < strlen(t)) {
    if ((t)[i] == ((char)(33))) {
    excl_t = i;
}
    i = (i + 1);
}
    if (excl_t >= 0) {
    const char* target_val = substring(t, 0, excl_t);
    const char* target_err = substring(t, (excl_t + 1), strlen(t));
    int64_t excl_s = (-1);
    i = 0;
    while (i < strlen(s)) {
    if ((s)[i] == ((char)(33))) {
    excl_s = i;
}
    i = (i + 1);
}
    if (excl_s >= 0) {
    const char* source_val = substring(s, 0, excl_s);
    const char* source_err = substring(s, (excl_s + 1), strlen(s));
    return (TypeChecker_types_compatible(self, target_val, source_val) && TypeChecker_types_compatible(self, target_err, source_err));
}
    if (TypeChecker_types_compatible(self, target_val, s)) {
    return true;
}
    if (strcmp(s, target_err) == 0) {
    return true;
}
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
    int64_t idx = 0;
    while (idx < ArrayList_StmtNode_length(self->stmt_pool)) {
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, idx);
    if ((stmt.kind == StmtKind_sk_func_decl) && (strcmp(stmt.func_name, name) == 0)) {
    return idx;
}
    idx = (idx + 1);
}
    return (-1);
}
int64_t TypeChecker_find_method_decl(TypeChecker* self, const char* struct_name, const char* meth_name) {
    const char* clean_struct = struct_name;
    int64_t i = 0;
    const char* clean = "";
    while (i < strlen(clean_struct)) {
    char c = (clean_struct)[i];
    if ((c != ((char)(42))) && (c != ((char)(38)))) {
    clean = /* Str concat */ ({
  const char* const _tmp_l = clean;
  const char* const _tmp_r = char_to_str(c);
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    i = (i + 1);
}
    clean_struct = clean;
    if ((strlen(clean_struct) > 4) && (strcmp(substring(clean_struct, 0, 4), "mut ") == 0)) {
    clean_struct = substring(clean_struct, 4, strlen(clean_struct));
}
    int64_t lt_pos = (-1);
    i = 0;
    while (i < strlen(clean_struct)) {
    if ((clean_struct)[i] == ((char)(60))) {
    lt_pos = i;
}
    i = (i + 1);
}
    if (lt_pos >= 0) {
    clean_struct = substring(clean_struct, 0, lt_pos);
}
    int64_t idx = 0;
    while (idx < ArrayList_StmtNode_length(self->stmt_pool)) {
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, idx);
    if (stmt.kind == StmtKind_sk_impl_block) {
    const char* impl_name = stmt.impl_struct_name;
    int64_t impl_lt = (-1);
    int64_t j = 0;
    while (j < strlen(impl_name)) {
    if ((impl_name)[j] == ((char)(60))) {
    impl_lt = j;
}
    j = (j + 1);
}
    if (impl_lt >= 0) {
    impl_name = substring(impl_name, 0, impl_lt);
}
    if (strcmp(impl_name, clean_struct) == 0) {
    int64_t mi = 0;
    while (mi < ArrayList_Int_length(&(stmt.impl_methods))) {
    int64_t m_idx = ArrayList_Int_get(&(stmt.impl_methods), mi);
    StmtNode m = ArrayList_StmtNode_get(self->stmt_pool, m_idx);
    if (strcmp(m.func_name, meth_name) == 0) {
    return m_idx;
}
    mi = (mi + 1);
}
}
}
    idx = (idx + 1);
}
    return (-1);
}
int64_t TypeChecker_find_struct_decl(TypeChecker* self, const char* name) {
    int64_t idx = 0;
    while (idx < ArrayList_StmtNode_length(self->stmt_pool)) {
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, idx);
    if ((stmt.kind == StmtKind_sk_struct_decl) && (strcmp(stmt.struct_name, name) == 0)) {
    return idx;
}
    idx = (idx + 1);
}
    return (-1);
}
const char* TypeChecker_get_block_yield_type(TypeChecker* self, int64_t stmt_idx) {
    if (stmt_idx < 0) {
    return "Void";
}
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, stmt_idx);
    if (stmt.kind == StmtKind_sk_block) {
    if (ArrayList_Int_length(&(stmt.block_stmts)) == 0) {
    return "Void";
}
    int64_t last_idx = ArrayList_Int_get(&(stmt.block_stmts), (ArrayList_Int_length(&(stmt.block_stmts)) - 1));
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
    if (expr_idx < 0) {
    return;
}
    ExprNode expr = ArrayList_ExprNode_get(self->expr_pool, expr_idx);
    if (expr.kind == ExprKind_ek_identifier) {
    const char* t = TypeChecker_get_expr_type(self, expr_idx);
    if (!TypeChecker_is_copy_type(self, t)) {
    SymbolTable table = ArrayList_SymbolTable_get(&(self->symbol_tables), self->current_table_idx);
    SymbolTable_mark_moved(&(table), expr.ident_name, &(self->symbol_tables));
    ArrayList_SymbolTable_set(&(self->symbol_tables), self->current_table_idx, table);
}
}
}
const char* TypeChecker_get_expr_type(TypeChecker* self, int64_t expr_idx) {
    if (expr_idx < 0) {
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
    if (strlen(sym.name) > 0) {
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
    return ArrayList_Str_get(&(expr.func_type_args), 0);
}
    if (strcmp(name, "size_of") == 0) {
    return "Int";
}
    if ((((strcmp(name, "Char") == 0) || (strcmp(name, "Int") == 0)) || (strcmp(name, "Float") == 0)) || (strcmp(name, "Bool") == 0)) {
    return name;
}
    bool is_struct = false;
    int64_t s_idx = 0;
    while (s_idx < ArrayList_StmtNode_length(self->stmt_pool)) {
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, s_idx);
    if ((stmt.kind == StmtKind_sk_struct_decl) && (strcmp(stmt.struct_name, name) == 0)) {
    is_struct = true;
}
    s_idx = (s_idx + 1);
}
    if (((strcmp(name, "ArrayList") == 0) || (strcmp(name, "HashMap") == 0)) || (strcmp(name, "StringBuilder") == 0)) {
    is_struct = true;
}
    if (is_struct) {
    if (ArrayList_Str_length(&(expr.func_type_args)) > 0) {
    return /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = name;
  const char* const _tmp_r = "<";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = str_array_join(expr.func_type_args, ", ");
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ">";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    return name;
}
    SymbolTable table = ArrayList_SymbolTable_get(&(self->symbol_tables), self->current_table_idx);
    Symbol sym = SymbolTable_lookup_symbol(&(table), name, &(self->symbol_tables));
    if (strlen(sym.name) > 0) {
    return sym.type_name;
}
    return "Void";
}
    if (expr.kind == ExprKind_ek_field_access) {
    ExprNode base_node = ArrayList_ExprNode_get(self->expr_pool, expr.field_expr);
    if (base_node.kind == ExprKind_ek_identifier) {
    bool is_static = false;
    int64_t s_idx = 0;
    while (s_idx < ArrayList_StmtNode_length(self->stmt_pool)) {
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, s_idx);
    if (((stmt.kind == StmtKind_sk_enum_decl) && (strcmp(stmt.enum_name, base_node.ident_name) == 0)) || ((stmt.kind == StmtKind_sk_error_decl) && (strcmp(stmt.error_name, base_node.ident_name) == 0))) {
    is_static = true;
}
    s_idx = (s_idx + 1);
}
    if (is_static) {
    return base_node.ident_name;
}
}
    const char* base_type = TypeChecker_get_expr_type(self, expr.field_expr);
    const char* clean_type = "";
    int64_t i = 0;
    while (i < strlen(base_type)) {
    char c = (base_type)[i];
    if ((c != ((char)(42))) && (c != ((char)(38)))) {
    clean_type = /* Str concat */ ({
  const char* const _tmp_l = clean_type;
  const char* const _tmp_r = char_to_str(c);
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    i = (i + 1);
}
    if ((strlen(clean_type) > 4) && (strcmp(substring(clean_type, 0, 4), "mut ") == 0)) {
    clean_type = substring(clean_type, 4, strlen(clean_type));
}
    int64_t s_idx = 0;
    while (s_idx < ArrayList_StmtNode_length(self->stmt_pool)) {
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, s_idx);
    if (stmt.kind == StmtKind_sk_struct_decl) {
    if (strcmp(stmt.struct_name, clean_type) == 0) {
    int64_t f_idx = 0;
    while (f_idx < ArrayList_StructField_length(&(stmt.struct_fields))) {
    StructField f = ArrayList_StructField_get(&(stmt.struct_fields), f_idx);
    if (strcmp(f.name, expr.field_name) == 0) {
    return f.ftype;
}
    f_idx = (f_idx + 1);
}
}
}
    s_idx = (s_idx + 1);
}
    return "Void";
}
    if (expr.kind == ExprKind_ek_index) {
    const char* base_type = TypeChecker_get_expr_type(self, expr.idx_expr);
    if (strcmp(base_type, "Str") == 0) {
    return "Char";
}
    if ((strlen(base_type) > 0) && ((base_type)[0] == ((char)(42)))) {
    return substring(base_type, 1, strlen(base_type));
}
    return "Void";
}
    if (expr.kind == ExprKind_ek_borrow) {
    const char* base_type = TypeChecker_get_expr_type(self, expr.borrow_expr);
    if (TypeChecker_expr_is_mutable(self, expr.borrow_expr)) {
    return /* Str concat */ ({
  const char* const _tmp_l = "*mut ";
  const char* const _tmp_r = base_type;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    return /* Str concat */ ({
  const char* const _tmp_l = "*";
  const char* const _tmp_r = base_type;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    if (expr.kind == ExprKind_ek_deref) {
    const char* base_type = TypeChecker_get_expr_type(self, expr.deref_expr);
    if ((strlen(base_type) > 5) && (strcmp(substring(base_type, 0, 5), "*mut ") == 0)) {
    return substring(base_type, 5, strlen(base_type));
}
    if ((strlen(base_type) > 5) && (strcmp(substring(base_type, 0, 5), "&mut ") == 0)) {
    return substring(base_type, 5, strlen(base_type));
}
    if ((strlen(base_type) > 0) && (((base_type)[0] == ((char)(42))) || ((base_type)[0] == ((char)(38))))) {
    return substring(base_type, 1, strlen(base_type));
}
    return "Void";
}
    if (expr.kind == ExprKind_ek_struct_init) {
    return expr.struct_name;
}
    if (expr.kind == ExprKind_ek_try) {
    const char* inner_ty = TypeChecker_get_expr_type(self, expr.try_expr);
    int64_t excl_pos = (-1);
    int64_t i = 0;
    while (i < strlen(inner_ty)) {
    if ((inner_ty)[i] == ((char)(33))) {
    excl_pos = i;
}
    i = (i + 1);
}
    if (excl_pos >= 0) {
    return substring(inner_ty, 0, excl_pos);
}
    return "Void";
}
    if (expr.kind == ExprKind_ek_catch) {
    const char* inner_ty = TypeChecker_get_expr_type(self, expr.catch_expr);
    int64_t excl_pos = (-1);
    int64_t i = 0;
    while (i < strlen(inner_ty)) {
    if ((inner_ty)[i] == ((char)(33))) {
    excl_pos = i;
}
    i = (i + 1);
}
    if (excl_pos >= 0) {
    return substring(inner_ty, 0, excl_pos);
}
    return "Void";
}
    return "Void";
}
bool TypeChecker_expr_is_mutable(TypeChecker* self, int64_t expr_idx) {
    if (expr_idx < 0) {
    return false;
}
    ExprNode expr = ArrayList_ExprNode_get(self->expr_pool, expr_idx);
    if (expr.kind == ExprKind_ek_identifier) {
    SymbolTable table = ArrayList_SymbolTable_get(&(self->symbol_tables), self->current_table_idx);
    Symbol sym = SymbolTable_lookup_symbol(&(table), expr.ident_name, &(self->symbol_tables));
    if (strlen(sym.name) > 0) {
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
void TypeChecker_check_identifier(TypeChecker* self, int64_t expr_idx) {
    ExprNode expr = ArrayList_ExprNode_get(self->expr_pool, expr_idx);
    const char* name = expr.ident_name;
    SymbolTable table = ArrayList_SymbolTable_get(&(self->symbol_tables), self->current_table_idx);
    Symbol sym = SymbolTable_lookup_symbol(&(table), name, &(self->symbol_tables));
    if (strlen(sym.name) > 0) {
    if (sym.moved) {
    printf("%s\n", "error[E0010]: Cannot use '");
    printf("%s\n", name);
    printf("%s\n", "' after it has been moved\n");
    self->has_error = true;
}
}
}
void TypeChecker_check_field_access(TypeChecker* self, int64_t expr_idx) {
    ExprNode expr = ArrayList_ExprNode_get(self->expr_pool, expr_idx);
    const char* recv_type = TypeChecker_get_expr_type(self, expr.field_expr);
    if ((strlen(recv_type) > 0) && ((recv_type)[0] == ((char)(63)))) {
    printf("%s\n", "error[E0001]: Cannot access field '");
    printf("%s\n", expr.field_name);
    printf("%s\n", "' on optional type '");
    printf("%s\n", recv_type);
    printf("%s\n", "'. Unwrap it first.\n");
    self->has_error = true;
}
}
void TypeChecker_check_method_call(TypeChecker* self, int64_t expr_idx) {
    ExprNode expr = ArrayList_ExprNode_get(self->expr_pool, expr_idx);
    const char* recv_type = TypeChecker_get_expr_type(self, expr.meth_expr);
    if ((strlen(recv_type) > 0) && ((recv_type)[0] == ((char)(63)))) {
    printf("%s\n", "error[E0001]: Cannot call method '");
    printf("%s\n", expr.meth_name);
    printf("%s\n", "' on optional type '");
    printf("%s\n", recv_type);
    printf("%s\n", "'. Unwrap it first.\n");
    self->has_error = true;
}
}
void TypeChecker_check_return_stmt(TypeChecker* self, int64_t stmt_idx) {
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, stmt_idx);
    const char* val_type = "Void";
    if (stmt.return_value >= 0) {
    ExprNode expr = ArrayList_ExprNode_get(self->expr_pool, stmt.return_value);
    if (expr.kind == ExprKind_ek_borrow) {
    ExprNode borrowed = ArrayList_ExprNode_get(self->expr_pool, expr.borrow_expr);
    if (borrowed.kind == ExprKind_ek_identifier) {
    const char* name = borrowed.ident_name;
    SymbolTable table = ArrayList_SymbolTable_get(&(self->symbol_tables), self->current_table_idx);
    Symbol sym = SymbolTable_lookup_symbol(&(table), name, &(self->symbol_tables));
    if ((strcmp(sym.kind, "var") == 0) || (strcmp(sym.kind, "param") == 0)) {
    printf("%s\n", "error[E0001]: Cannot return reference to local variable '");
    printf("%s\n", name);
    printf("%s\n", "'\n");
    self->has_error = true;
}
}
}
    TypeChecker_check_expr(self, stmt.return_value);
    TypeChecker_mark_expr_moved(self, stmt.return_value);
    val_type = TypeChecker_get_expr_type(self, stmt.return_value);
}
    const char* expected_ret = self->current_func_ret_type;
    if ((strlen(expected_ret) > 0) && (strcmp(expected_ret, "<infer>") != 0)) {
    if (!TypeChecker_types_compatible(self, expected_ret, val_type)) {
    printf("%s\n", "error[E0001]: Return type mismatch: expected '");
    printf("%s\n", expected_ret);
    printf("%s\n", "', got '");
    printf("%s\n", val_type);
    printf("%s\n", "'\n");
    self->has_error = true;
}
}
}
void TypeChecker_check_stmt(TypeChecker* self, int64_t stmt_idx) {
    if (stmt_idx < 0) {
    return;
}
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, stmt_idx);
    if (stmt.kind == StmtKind_sk_block) {
    TypeChecker_enter_scope(self);
    int64_t i = 0;
    while (i < ArrayList_Int_length(&(stmt.block_stmts))) {
    TypeChecker_check_stmt(self, ArrayList_Int_get(&(stmt.block_stmts), i));
    i = (i + 1);
}
    TypeChecker_collect_block_drops(self, stmt_idx);
    TypeChecker_exit_scope(self);
    return;
}
    if (stmt.kind == StmtKind_sk_var_decl) {
    TypeChecker_check_expr(self, stmt.vardecl_value);
    const char* val_type = TypeChecker_get_expr_type(self, stmt.vardecl_value);
    const char* var_type = stmt.vardecl_type;
    if (strlen(var_type) == 0) {
    var_type = val_type;
} else if (!TypeChecker_types_compatible(self, var_type, val_type)) {
    printf("%s\n", "error[E0001]: Type mismatch in declaration of '");
    printf("%s\n", stmt.vardecl_name);
    printf("%s\n", "': expected '");
    printf("%s\n", var_type);
    printf("%s\n", "', got '");
    printf("%s\n", val_type);
    printf("%s\n", "'\n");
    self->has_error = true;
}
    TypeChecker_define_symbol(self, stmt.vardecl_name, var_type, stmt.vardecl_mut, "var");
    TypeChecker_mark_expr_moved(self, stmt.vardecl_value);
    return;
}
    if (stmt.kind == StmtKind_sk_assignment) {
    TypeChecker_check_expr(self, stmt.assign_target);
    TypeChecker_check_expr(self, stmt.assign_value);
    const char* target_type = "Void";
    if (stmt.assign_target >= 0) {
    target_type = TypeChecker_get_expr_type(self, stmt.assign_target);
    ExprNode target_expr = ArrayList_ExprNode_get(self->expr_pool, stmt.assign_target);
    if (target_expr.kind == ExprKind_ek_identifier) {
    SymbolTable table = ArrayList_SymbolTable_get(&(self->symbol_tables), self->current_table_idx);
    Symbol sym = SymbolTable_lookup_symbol(&(table), target_expr.ident_name, &(self->symbol_tables));
    if ((strlen(sym.name) > 0) && (!sym.is_mutable)) {
    printf("%s\n", "error[E0001]: Cannot assign to immutable variable '");
    printf("%s\n", target_expr.ident_name);
    printf("%s\n", "'\n");
    self->has_error = true;
}
}
}
    const char* val_type = TypeChecker_get_expr_type(self, stmt.assign_value);
    if (!TypeChecker_types_compatible(self, target_type, val_type)) {
    printf("%s\n", "error[E0001]: Type mismatch in assignment: target name: '");
    if (stmt.assign_target >= 0) {
    ExprNode target_expr = ArrayList_ExprNode_get(self->expr_pool, stmt.assign_target);
    if (target_expr.kind == ExprKind_ek_identifier) {
    printf("%s\n", target_expr.ident_name);
} else {
    printf("%s\n", "<non-ident>");
}
}
    printf("%s\n", "', target is '");
    printf("%s\n", target_type);
    printf("%s\n", "', value is '");
    printf("%s\n", val_type);
    printf("%s\n", "'\n");
    self->has_error = true;
}
    TypeChecker_mark_expr_moved(self, stmt.assign_value);
    return;
}
    if (stmt.kind == StmtKind_sk_func_decl) {
    const char* old_ret = self->current_func_ret_type;
    self->current_func_ret_type = stmt.func_return_type;
    TypeChecker_define_symbol(self, stmt.func_name, stmt.func_return_type, false, "func");
    TypeChecker_enter_scope(self);
    int64_t i = 0;
    while (i < ArrayList_Param_length(&(stmt.func_params))) {
    Param p = ArrayList_Param_get(&(stmt.func_params), i);
    TypeChecker_define_symbol(self, p.name, p.ptype, false, "param");
    i = (i + 1);
}
    TypeChecker_check_stmt(self, stmt.func_body);
    TypeChecker_exit_scope(self);
    self->current_func_ret_type = old_ret;
    return;
}
    if (stmt.kind == StmtKind_sk_if) {
    TypeChecker_check_expr(self, stmt.if_cond);
    TypeChecker_check_stmt(self, stmt.if_then);
    TypeChecker_check_stmt(self, stmt.if_else);
    return;
}
    if (stmt.kind == StmtKind_sk_if_let) {
    TypeChecker_check_expr(self, stmt.iflet_expr);
    const char* opt_type = TypeChecker_get_expr_type(self, stmt.iflet_expr);
    const char* unwrapped_type = opt_type;
    if ((strlen(opt_type) > 0) && ((opt_type)[0] == ((char)(63)))) {
    unwrapped_type = substring(opt_type, 1, strlen(opt_type));
}
    TypeChecker_enter_scope(self);
    TypeChecker_define_symbol(self, stmt.iflet_var, unwrapped_type, false, "var");
    TypeChecker_check_stmt(self, stmt.iflet_then);
    TypeChecker_exit_scope(self);
    TypeChecker_check_stmt(self, stmt.iflet_else);
    return;
}
    if (stmt.kind == StmtKind_sk_while) {
    TypeChecker_check_expr(self, stmt.while_cond);
    TypeChecker_check_stmt(self, stmt.while_body);
    return;
}
    if (stmt.kind == StmtKind_sk_for) {
    TypeChecker_check_expr(self, stmt.for_start);
    TypeChecker_check_expr(self, stmt.for_end);
    TypeChecker_enter_scope(self);
    TypeChecker_define_symbol(self, stmt.for_var, "Int", false, "var");
    TypeChecker_check_stmt(self, stmt.for_body);
    TypeChecker_exit_scope(self);
    return;
}
    if (stmt.kind == StmtKind_sk_return) {
    TypeChecker_check_return_stmt(self, stmt_idx);
    return;
}
    if (stmt.kind == StmtKind_sk_print) {
    TypeChecker_check_expr(self, stmt.print_value);
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
    int64_t i = 0;
    while (i < ArrayList_MatchCase_length(&(stmt.match_cases))) {
    MatchCase mc = ArrayList_MatchCase_get(&(stmt.match_cases), i);
    TypeChecker_enter_scope(self);
    PatternNode pat = ArrayList_PatternNode_get(self->pattern_pool, mc.pattern);
    if (pat.kind == PatternKind_pk_variant) {
    int64_t bi = 0;
    while (bi < ArrayList_Str_length(&(pat.bindings))) {
    TypeChecker_define_symbol(self, ArrayList_Str_get(&(pat.bindings), bi), "Void", false, "var");
    bi = (bi + 1);
}
}
    TypeChecker_check_stmt(self, mc.body);
    TypeChecker_exit_scope(self);
    i = (i + 1);
}
    return;
}
    if (stmt.kind == StmtKind_sk_impl_block) {
    int64_t i = 0;
    while (i < ArrayList_Int_length(&(stmt.impl_methods))) {
    int64_t m_idx = ArrayList_Int_get(&(stmt.impl_methods), i);
    StmtNode m = ArrayList_StmtNode_get(self->stmt_pool, m_idx);
    const char* mangled_name = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = stmt.impl_struct_name;
  const char* const _tmp_r = "_";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = m.func_name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    TypeChecker_define_symbol(self, mangled_name, m.func_return_type, false, "func");
    const char* old_ret = self->current_func_ret_type;
    self->current_func_ret_type = m.func_return_type;
    TypeChecker_enter_scope(self);
    TypeChecker_define_symbol(self, "self", stmt.impl_struct_name, true, "param");
    int64_t pi = 1;
    while (pi < ArrayList_Param_length(&(m.func_params))) {
    Param p = ArrayList_Param_get(&(m.func_params), pi);
    TypeChecker_define_symbol(self, p.name, p.ptype, false, "param");
    pi = (pi + 1);
}
    TypeChecker_check_stmt(self, m.func_body);
    TypeChecker_exit_scope(self);
    self->current_func_ret_type = old_ret;
    i = (i + 1);
}
    return;
}
    if (stmt.kind == StmtKind_sk_error_decl) {
    return;
}
}
void TypeChecker_check_expr(TypeChecker* self, int64_t expr_idx) {
    if (expr_idx < 0) {
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
    return;
}
    if (expr.kind == ExprKind_ek_unary_op) {
    TypeChecker_check_expr(self, expr.unop_operand);
    return;
}
    if (expr.kind == ExprKind_ek_func_call) {
    int64_t i = 0;
    while (i < ArrayList_Int_length(&(expr.func_args))) {
    int64_t arg = ArrayList_Int_get(&(expr.func_args), i);
    TypeChecker_check_expr(self, arg);
    TypeChecker_mark_expr_moved(self, arg);
    i = (i + 1);
}
    const char* name = expr.func_name;
    if (((((((strcmp(name, "cast") == 0) || (strcmp(name, "as") == 0)) || (strcmp(name, "size_of") == 0)) || (strcmp(name, "Char") == 0)) || (strcmp(name, "Int") == 0)) || (strcmp(name, "Float") == 0)) || (strcmp(name, "Bool") == 0)) {
    return;
}
    int64_t func_idx = TypeChecker_find_func_decl(self, name);
    if (func_idx >= 0) {
    StmtNode decl = ArrayList_StmtNode_get(self->stmt_pool, func_idx);
    if (ArrayList_Param_length(&(decl.func_params)) != ArrayList_Int_length(&(expr.func_args))) {
    printf("%s\n", "error[E0001]: Argument count mismatch for function '");
    printf("%s\n", name);
    printf("%s\n", "': expected ");
    printf("%s\n", int_to_str(ArrayList_Param_length(&(decl.func_params))));
    printf("%s\n", ", got ");
    printf("%s\n", int_to_str(ArrayList_Int_length(&(expr.func_args))));
    printf("%s\n", "\n");
    self->has_error = true;
} else {
    int64_t arg_i = 0;
    while (arg_i < ArrayList_Int_length(&(expr.func_args))) {
    int64_t arg = ArrayList_Int_get(&(expr.func_args), arg_i);
    Param param = ArrayList_Param_get(&(decl.func_params), arg_i);
    const char* arg_type = TypeChecker_get_expr_type(self, arg);
    if (!TypeChecker_types_compatible(self, param.ptype, arg_type)) {
    printf("%s\n", "error[E0001]: Argument type mismatch for function '");
    printf("%s\n", name);
    printf("%s\n", "', parameter '");
    printf("%s\n", param.name);
    printf("%s\n", "': expected '");
    printf("%s\n", param.ptype);
    printf("%s\n", "', got '");
    printf("%s\n", arg_type);
    printf("%s\n", "'\n");
    self->has_error = true;
}
    arg_i = (arg_i + 1);
}
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
    int64_t i = 0;
    while (i < ArrayList_Int_length(&(expr.meth_args))) {
    int64_t arg = ArrayList_Int_get(&(expr.meth_args), i);
    TypeChecker_check_expr(self, arg);
    TypeChecker_mark_expr_moved(self, arg);
    i = (i + 1);
}
    const char* recv_type = TypeChecker_get_expr_type(self, expr.meth_expr);
    const char* meth_name = expr.meth_name;
    int64_t meth_idx = TypeChecker_find_method_decl(self, recv_type, meth_name);
    if (meth_idx >= 0) {
    StmtNode decl = ArrayList_StmtNode_get(self->stmt_pool, meth_idx);
    if (ArrayList_Param_length(&(decl.func_params)) != (ArrayList_Int_length(&(expr.meth_args)) + 1)) {
    printf("%s\n", "error[E0001]: Argument count mismatch for method '");
    printf("%s\n", meth_name);
    printf("%s\n", "': expected ");
    printf("%s\n", int_to_str((ArrayList_Param_length(&(decl.func_params)) - 1)));
    printf("%s\n", ", got ");
    printf("%s\n", int_to_str(ArrayList_Int_length(&(expr.meth_args))));
    printf("%s\n", "\n");
    self->has_error = true;
} else {
    int64_t arg_i = 0;
    while (arg_i < ArrayList_Int_length(&(expr.meth_args))) {
    int64_t arg = ArrayList_Int_get(&(expr.meth_args), arg_i);
    Param param = ArrayList_Param_get(&(decl.func_params), (arg_i + 1));
    const char* arg_type = TypeChecker_get_expr_type(self, arg);
    if (!TypeChecker_types_compatible(self, param.ptype, arg_type)) {
    printf("%s\n", "error[E0001]: Argument type mismatch for method '");
    printf("%s\n", meth_name);
    printf("%s\n", "', parameter '");
    printf("%s\n", param.name);
    printf("%s\n", "': expected '");
    printf("%s\n", param.ptype);
    printf("%s\n", "', got '");
    printf("%s\n", arg_type);
    printf("%s\n", "'\n");
    self->has_error = true;
}
    arg_i = (arg_i + 1);
}
}
}
    return;
}
    if (expr.kind == ExprKind_ek_index) {
    TypeChecker_check_expr(self, expr.idx_expr);
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
    int64_t i = 0;
    while (i < ArrayList_FieldInit_length(&(expr.struct_fields))) {
    FieldInit f = ArrayList_FieldInit_get(&(expr.struct_fields), i);
    TypeChecker_check_expr(self, f.value);
    TypeChecker_mark_expr_moved(self, f.value);
    i = (i + 1);
}
    const char* struct_name = expr.struct_name;
    int64_t struct_idx = TypeChecker_find_struct_decl(self, struct_name);
    if (struct_idx >= 0) {
    StmtNode decl = ArrayList_StmtNode_get(self->stmt_pool, struct_idx);
    int64_t fi = 0;
    while (fi < ArrayList_FieldInit_length(&(expr.struct_fields))) {
    FieldInit f = ArrayList_FieldInit_get(&(expr.struct_fields), fi);
    bool found = false;
    int64_t dfi = 0;
    while (dfi < ArrayList_StructField_length(&(decl.struct_fields))) {
    StructField df = ArrayList_StructField_get(&(decl.struct_fields), dfi);
    if (strcmp(df.name, f.name) == 0) {
    found = true;
    const char* val_type = TypeChecker_get_expr_type(self, f.value);
    if (!TypeChecker_types_compatible(self, df.ftype, val_type)) {
    printf("%s\n", "error[E0001]: Type mismatch in initializer for field '");
    printf("%s\n", f.name);
    printf("%s\n", "' of struct '");
    printf("%s\n", struct_name);
    printf("%s\n", "': expected '");
    printf("%s\n", df.ftype);
    printf("%s\n", "', got '");
    printf("%s\n", val_type);
    printf("%s\n", "'\n");
    self->has_error = true;
}
}
    dfi = (dfi + 1);
}
    if (!found) {
    printf("%s\n", "error[E0001]: Field '");
    printf("%s\n", f.name);
    printf("%s\n", "' does not exist in struct '");
    printf("%s\n", struct_name);
    printf("%s\n", "'\n");
    self->has_error = true;
}
    fi = (fi + 1);
}
}
    return;
}
    if (expr.kind == ExprKind_ek_try) {
    TypeChecker_check_expr(self, expr.try_expr);
    const char* inner_ty = TypeChecker_get_expr_type(self, expr.try_expr);
    int64_t excl_pos = (-1);
    int64_t i = 0;
    while (i < strlen(inner_ty)) {
    if ((inner_ty)[i] == ((char)(33))) {
    excl_pos = i;
}
    i = (i + 1);
}
    if (excl_pos < 0) {
    printf("%s\n", "error[E0001]: Cannot use 'try' on non-error union type '");
    printf("%s\n", inner_ty);
    printf("%s\n", "'\n");
    self->has_error = true;
} else {
    const char* error_set = substring(inner_ty, (excl_pos + 1), strlen(inner_ty));
    const char* expected_ret = self->current_func_ret_type;
    int64_t func_excl = (-1);
    i = 0;
    while (i < strlen(expected_ret)) {
    if ((expected_ret)[i] == ((char)(33))) {
    func_excl = i;
}
    i = (i + 1);
}
    if (func_excl < 0) {
    printf("%s\n", "error[E0001]: Cannot use 'try' in a function that returns non-error union type '");
    printf("%s\n", expected_ret);
    printf("%s\n", "'\n");
    self->has_error = true;
} else {
    const char* func_err = substring(expected_ret, (func_excl + 1), strlen(expected_ret));
    if (!TypeChecker_types_compatible(self, func_err, error_set)) {
    printf("%s\n", "error[E0001]: Error set '");
    printf("%s\n", error_set);
    printf("%s\n", "' of try expression is not compatible with function error set '");
    printf("%s\n", func_err);
    printf("%s\n", "'\n");
    self->has_error = true;
}
}
}
    return;
}
    if (expr.kind == ExprKind_ek_catch) {
    TypeChecker_check_expr(self, expr.catch_expr);
    const char* inner_ty = TypeChecker_get_expr_type(self, expr.catch_expr);
    int64_t excl_pos = (-1);
    int64_t i = 0;
    while (i < strlen(inner_ty)) {
    if ((inner_ty)[i] == ((char)(33))) {
    excl_pos = i;
}
    i = (i + 1);
}
    if (excl_pos < 0) {
    printf("%s\n", "error[E0001]: Cannot use 'catch' on non-error union type '");
    printf("%s\n", inner_ty);
    printf("%s\n", "'\n");
    self->has_error = true;
} else {
    const char* val_type = substring(inner_ty, 0, excl_pos);
    const char* error_set = substring(inner_ty, (excl_pos + 1), strlen(inner_ty));
    TypeChecker_enter_scope(self);
    if (strlen(expr.catch_var) > 0) {
    TypeChecker_define_symbol(self, expr.catch_var, error_set, false, "var");
}
    TypeChecker_check_stmt(self, expr.catch_fallback);
    TypeChecker_exit_scope(self);
    const char* fallback_yields = TypeChecker_get_block_yield_type(self, expr.catch_fallback);
    if (!TypeChecker_types_compatible(self, val_type, fallback_yields)) {
    printf("%s\n", "error[E0001]: Catch fallback type '");
    printf("%s\n", fallback_yields);
    printf("%s\n", "' is not compatible with expected type '");
    printf("%s\n", val_type);
    printf("%s\n", "'\n");
    self->has_error = true;
}
}
    return;
}
}
ArrayList_StrMapEntry ArrayList_StrMapEntry_init(KaiAllocator* allocator) {
    ArrayList_StrMapEntry self = (ArrayList_StrMapEntry){0};
    self.len = 0;
    self.cap = 4;
    self.allocator = allocator;
    {
    self.data = (StrMapEntry*)(KaiAllocator_alloc(allocator, (self.cap * sizeof(StrMapEntry)), 1));
}
    return self;
}
void ArrayList_StrMapEntry_push(ArrayList_StrMapEntry* self, StrMapEntry item) {
    if (self->len == self->cap) {
    int64_t new_cap = (self->cap * 2);
    {
    StrMapEntry* new_data = (StrMapEntry*)(KaiAllocator_alloc(self->allocator, (new_cap * sizeof(StrMapEntry)), 1));
    int64_t i = 0;
    while (i < self->len) {
    (new_data)[i] = (self->data)[i];
    i = (i + 1);
}
    KaiAllocator_free(self->allocator, (char*)(self->data));
    self->data = new_data;
    self->cap = new_cap;
}
}
    (self->data)[self->len] = item;
    self->len = (self->len + 1);
}
StrMapEntry ArrayList_StrMapEntry_get(ArrayList_StrMapEntry* self, int64_t index) {
    if ((index < 0) || (index >= self->len)) {
    {
    exit(1);
}
}
    return (self->data)[index];
}
void ArrayList_StrMapEntry_set(ArrayList_StrMapEntry* self, int64_t index, StrMapEntry item) {
    if ((index < 0) || (index >= self->len)) {
    {
    exit(1);
}
}
    (self->data)[index] = item;
}
StrMapEntry ArrayList_StrMapEntry_pop(ArrayList_StrMapEntry* self) {
    if (self->len == 0) {
    {
    exit(1);
}
}
    self->len = (self->len - 1);
    return (self->data)[self->len];
}
int64_t ArrayList_StrMapEntry_length(ArrayList_StrMapEntry* self) {
    return self->len;
}
void ArrayList_StrMapEntry_deinit(ArrayList_StrMapEntry* self) {
    {
    KaiAllocator_free(self->allocator, (char*)(self->data));
}
}
int64_t type_map_find(ArrayList_StrMapEntry* arr, const char* key) {
    int64_t i = (ArrayList_StrMapEntry_length(arr) - 1);
    while (i >= 0) {
    if (strcmp(ArrayList_StrMapEntry_get(arr, i).key, key) == 0) {
    return i;
}
    i = (i - 1);
}
    return (-1);
}
const char* type_map_get(ArrayList_StrMapEntry* arr, const char* key) {
    int64_t idx = type_map_find(arr, key);
    if (idx < 0) {
    return "";
}
    return ArrayList_StrMapEntry_get(arr, idx).value;
}
void type_map_put(ArrayList_StrMapEntry* arr, const char* key, const char* value) {
    ArrayList_StrMapEntry_push(arr, (StrMapEntry){ .key = key, .value = value });
}
int64_t strlist_find(ArrayList_Str* arr, const char* key) {
    int64_t i = 0;
    while (i < ArrayList_Str_length(arr)) {
    if (strcmp(ArrayList_Str_get(arr, i), key) == 0) {
    return i;
}
    i = (i + 1);
}
    return (-1);
}
Codegen Codegen_init(KaiAllocator* allocator, ArrayList_StmtNode* stmt_pool, ArrayList_ExprNode* expr_pool, ArrayList_PatternNode* pattern_pool) {
    Codegen self = (Codegen){0};
    self.allocator = allocator;
    self.stmt_pool = stmt_pool;
    self.expr_pool = expr_pool;
    self.pattern_pool = pattern_pool;
    self.output = StringBuilder_init(allocator);
    self.struct_decls = StringBuilder_init(allocator);
    self.func_decls = StringBuilder_init(allocator);
    self.cur_func_name = "";
    self.cur_return_type = "";
    self.cur_method_is_init = false;
    self.func_types = ArrayList_StrMapEntry_init(allocator);
    self.var_types = ArrayList_StrMapEntry_init(allocator);
    self.loaded_modules = ArrayList_Str_init(allocator);
    self.cimport_headers = ArrayList_Str_init(allocator);
    self.block_stack = ArrayList_Int_init(allocator);
    self.generic_struct_decls = ArrayList_StrMapEntry_init(allocator);
    self.generic_enum_decls = ArrayList_StrMapEntry_init(allocator);
    self.generic_func_decls = ArrayList_StrMapEntry_init(allocator);
    self.generic_impl_blocks = ArrayList_StrMapEntry_init(allocator);
    self.monomorphized_types = ArrayList_Str_init(allocator);
    self.current_type_map = ArrayList_StrMapEntry_init(allocator);
    self.enum_decls = ArrayList_StrMapEntry_init(allocator);
    self.result_definitions = ArrayList_Str_init(allocator);
    return self;
}
const char* Codegen_map_type(Codegen* self, const char* type_name) {
    if (strlen(type_name) == 0) {
    return "void";
}
    const char* resolved_type = type_name;
    if (ArrayList_StrMapEntry_length(&(self->current_type_map)) > 0) {
    resolved_type = Codegen_substitute_generic_type(self, type_name);
}
    if (Codegen_str_contains(self, resolved_type, ((char)(33)))) {
    int64_t excl_pos = Codegen_str_find(self, resolved_type, ((char)(33)));
    const char* val_type = substring(resolved_type, 0, excl_pos);
    const char* err_type = substring(resolved_type, (excl_pos + 1), strlen(resolved_type));
    const char* clean_val = Codegen_clean_type_for_mangling(self, val_type);
    const char* clean_err = Codegen_clean_type_for_mangling(self, err_type);
    const char* concrete_name = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "Result_";
  const char* const _tmp_r = clean_val;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "_";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = clean_err;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    if (strlist_find(&(self->result_definitions), concrete_name) < 0) {
    ArrayList_Str_push(&(self->result_definitions), concrete_name);
    const char* struct_str = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "typedef struct ";
  const char* const _tmp_r = concrete_name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = " ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = concrete_name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ";\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    struct_str = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = struct_str;
  const char* const _tmp_r = "struct ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = concrete_name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = " {\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    struct_str = /* Str concat */ ({
  const char* const _tmp_l = struct_str;
  const char* const _tmp_r = "    int64_t tag;\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    if (strcmp(val_type, "Void") != 0) {
    struct_str = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = struct_str;
  const char* const _tmp_r = "    ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = Codegen_map_type(self, val_type);
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = " value;\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    struct_str = /* Str concat */ ({
  const char* const _tmp_l = struct_str;
  const char* const _tmp_r = "};\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    (void)(StringBuilder_append(&(self->struct_decls), struct_str));
}
    return concrete_name;
}
    if (strcmp(resolved_type, "Int") == 0) {
    return "int64_t";
}
    if (strcmp(resolved_type, "Int8") == 0) {
    return "int8_t";
}
    if (strcmp(resolved_type, "Int32") == 0) {
    return "int32_t";
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
    if (strcmp(resolved_type, "Allocator") == 0) {
    return "KaiAllocator";
}
    if (strcmp(substring(resolved_type, 0, 2), "[]") == 0) {
    const char* inner = substring(resolved_type, 2, strlen(resolved_type));
    return /* Str concat */ ({
  const char* const _tmp_l = Codegen_map_type(self, inner);
  const char* const _tmp_r = "*";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    if ((resolved_type)[0] == ((char)(42))) {
    if ((strlen(resolved_type) > 5) && (strcmp(substring(resolved_type, 0, 5), "*mut ") == 0)) {
    const char* inner = substring(resolved_type, 5, strlen(resolved_type));
    if (strcmp(inner, "Void") == 0) {
    return "void*";
}
    return /* Str concat */ ({
  const char* const _tmp_l = Codegen_map_type(self, inner);
  const char* const _tmp_r = "*";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
} else {
    const char* inner = substring(resolved_type, 1, strlen(resolved_type));
    if (strcmp(inner, "Void") == 0) {
    return "void*";
}
    return /* Str concat */ ({
  const char* const _tmp_l = Codegen_map_type(self, inner);
  const char* const _tmp_r = "*";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
}
    if ((resolved_type)[0] == ((char)(38))) {
    if ((strlen(resolved_type) > 5) && (strcmp(substring(resolved_type, 0, 5), "&mut ") == 0)) {
    const char* inner = substring(resolved_type, 5, strlen(resolved_type));
    return /* Str concat */ ({
  const char* const _tmp_l = Codegen_map_type(self, inner);
  const char* const _tmp_r = "*";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
} else {
    const char* inner = substring(resolved_type, 1, strlen(resolved_type));
    return /* Str concat */ ({
  const char* const _tmp_l = Codegen_map_type(self, inner);
  const char* const _tmp_r = "*";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
}
    if (Codegen_str_contains(self, resolved_type, ((char)(60)))) {
    int64_t lt_pos = Codegen_str_find(self, resolved_type, ((char)(60)));
    const char* base_name = substring(resolved_type, 0, lt_pos);
    const char* args_str = substring(resolved_type, (lt_pos + 1), (strlen(resolved_type) - 1));
    ArrayList_Str args = ArrayList_Str_init(self->allocator);
    int64_t start = 0;
    int64_t i = 0;
    while (i < strlen(args_str)) {
    char c = (args_str)[i];
    if (c == ((char)(44))) {
    ArrayList_Str_push(&(args), Codegen_trim_spaces(self, substring(args_str, start, i)));
    start = (i + 1);
}
    i = (i + 1);
}
    ArrayList_Str_push(&(args), Codegen_trim_spaces(self, substring(args_str, start, strlen(args_str))));
    const char* concrete_name = base_name;
    int64_t ai = 0;
    while (ai < ArrayList_Str_length(&(args))) {
    const char* raw_arg = ArrayList_Str_get(&(args), ai);
    const char* clean_arg = Codegen_clean_type_for_mangling(self, raw_arg);
    concrete_name = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = concrete_name;
  const char* const _tmp_r = "_";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = clean_arg;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    ai = (ai + 1);
}
    const char* struct_idx_str = type_map_get(&(self->generic_struct_decls), base_name);
    if (strlen(struct_idx_str) > 0) {
    if (strlist_find(&(self->monomorphized_types), concrete_name) < 0) {
    ArrayList_Str_push(&(self->monomorphized_types), concrete_name);
    Codegen_monomorphize_struct(self, Codegen_str_to_int(self, struct_idx_str), concrete_name, &(args));
}
    return concrete_name;
}
    const char* enum_idx_str = type_map_get(&(self->generic_enum_decls), base_name);
    if (strlen(enum_idx_str) > 0) {
    if (strlist_find(&(self->monomorphized_types), concrete_name) < 0) {
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
    if (strlen(mapped) > 0) {
    return mapped;
}
    if ((type_name)[0] == ((char)(42))) {
    return /* Str concat */ ({
  const char* const _tmp_l = "*";
  const char* const _tmp_r = Codegen_substitute_generic_type(self, substring(type_name, 1, strlen(type_name)));
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    if ((type_name)[0] == ((char)(38))) {
    if (strcmp(substring(type_name, 0, 5), "&mut ") == 0) {
    return /* Str concat */ ({
  const char* const _tmp_l = "&mut ";
  const char* const _tmp_r = Codegen_substitute_generic_type(self, substring(type_name, 5, strlen(type_name)));
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    return /* Str concat */ ({
  const char* const _tmp_l = "&";
  const char* const _tmp_r = Codegen_substitute_generic_type(self, substring(type_name, 1, strlen(type_name)));
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    if (Codegen_str_contains(self, type_name, ((char)(60)))) {
    int64_t lt_pos = Codegen_str_find(self, type_name, ((char)(60)));
    const char* base = substring(type_name, 0, lt_pos);
    const char* inner = substring(type_name, (lt_pos + 1), (strlen(type_name) - 1));
    const char* res = /* Str concat */ ({
  const char* const _tmp_l = base;
  const char* const _tmp_r = "<";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    int64_t start = 0;
    int64_t i = 0;
    int64_t arg_count = 0;
    while (i < strlen(inner)) {
    char c = (inner)[i];
    if (c == ((char)(44))) {
    const char* arg = Codegen_trim_spaces(self, substring(inner, start, i));
    if (arg_count > 0) {
    res = /* Str concat */ ({
  const char* const _tmp_l = res;
  const char* const _tmp_r = ", ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    res = /* Str concat */ ({
  const char* const _tmp_l = res;
  const char* const _tmp_r = Codegen_substitute_generic_type(self, arg);
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    start = (i + 1);
    arg_count = (arg_count + 1);
}
    i = (i + 1);
}
    const char* arg = Codegen_trim_spaces(self, substring(inner, start, strlen(inner)));
    if (arg_count > 0) {
    res = /* Str concat */ ({
  const char* const _tmp_l = res;
  const char* const _tmp_r = ", ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    res = /* Str concat */ ({
  const char* const _tmp_l = res;
  const char* const _tmp_r = Codegen_substitute_generic_type(self, arg);
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    res = /* Str concat */ ({
  const char* const _tmp_l = res;
  const char* const _tmp_r = ">";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    return res;
}
    return type_name;
}
const char* Codegen_trim_spaces(Codegen* self, const char* s) {
    int64_t start = 0;
    while ((start < strlen(s)) && ((s)[start] == ((char)(32)))) {
    start = (start + 1);
}
    int64_t end = strlen(s);
    while ((end > start) && ((s)[(end - 1)] == ((char)(32)))) {
    end = (end - 1);
}
    return substring(s, start, end);
}
const char* Codegen_clean_type_for_mangling(Codegen* self, const char* s) {
    const char* res = "";
    int64_t i = 0;
    while (i < strlen(s)) {
    char c = (s)[i];
    if (c == ((char)(42))) {
    res = /* Str concat */ ({
  const char* const _tmp_l = res;
  const char* const _tmp_r = "ptr";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
} else if (c == ((char)(38))) {
    res = /* Str concat */ ({
  const char* const _tmp_l = res;
  const char* const _tmp_r = "ref";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
} else if (c == ((char)(32))) {
    res = /* Str concat */ ({
  const char* const _tmp_l = res;
  const char* const _tmp_r = "_";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
} else if ((((c == ((char)(60))) || (c == ((char)(62)))) || (c == ((char)(44)))) || (c == ((char)(33)))) {
    res = /* Str concat */ ({
  const char* const _tmp_l = res;
  const char* const _tmp_r = "_";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
} else {
    res = /* Str concat */ ({
  const char* const _tmp_l = res;
  const char* const _tmp_r = char_to_str(c);
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    i = (i + 1);
}
    return res;
}
int64_t Codegen_str_to_int(Codegen* self, const char* s) {
    int64_t res = 0;
    int64_t i = 0;
    while (i < strlen(s)) {
    char c = (s)[i];
    if ((c >= ((char)(48))) && (c <= ((char)(57)))) {
    res = ((res * 10) + (((int64_t)(c)) - 48));
}
    i = (i + 1);
}
    return res;
}
void Codegen_setup_current_type_map(Codegen* self, ArrayList_Str* type_params, ArrayList_Str* type_args) {
    int64_t i = 0;
    while (i < ArrayList_Str_length(type_params)) {
    const char* param_name = Codegen_trim_spaces(self, ArrayList_Str_get(type_params, i));
    const char* arg_name = Codegen_trim_spaces(self, ArrayList_Str_get(type_args, i));
    if (Codegen_str_contains(self, param_name, ((char)(58)))) {
    int64_t colon_pos = Codegen_str_find(self, param_name, ((char)(58)));
    param_name = substring(param_name, 0, colon_pos);
}
    type_map_put(&(self->current_type_map), param_name, arg_name);
    i = (i + 1);
}
}
void Codegen_monomorphize_struct(Codegen* self, int64_t stmt_idx, const char* concrete_name, ArrayList_Str* type_args) {
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, stmt_idx);
    ArrayList_StrMapEntry old_type_map = self->current_type_map;
    self->current_type_map = ArrayList_StrMapEntry_init(self->allocator);
    Codegen_setup_current_type_map(self, &(stmt.struct_type_params), type_args);
    const char* typedef_str = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "typedef struct ";
  const char* const _tmp_r = concrete_name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = " ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = concrete_name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ";\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    (void)(StringBuilder_append(&(self->struct_decls), typedef_str));
    const char* body = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "struct ";
  const char* const _tmp_r = concrete_name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = " {\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    int64_t i = 0;
    while (i < ArrayList_StructField_length(&(stmt.struct_fields))) {
    StructField f = ArrayList_StructField_get(&(stmt.struct_fields), i);
    const char* f_type = Codegen_map_type(self, f.ftype);
    body = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = body;
  const char* const _tmp_r = "    ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = f_type;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = " ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = f.name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ";\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    i = (i + 1);
}
    body = /* Str concat */ ({
  const char* const _tmp_l = body;
  const char* const _tmp_r = "};\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    (void)(StringBuilder_append(&(self->struct_decls), body));
    Codegen_monomorphize_methods(self, stmt.struct_name, concrete_name);
    self->current_type_map = old_type_map;
}
void Codegen_monomorphize_enum(Codegen* self, int64_t stmt_idx, const char* concrete_name, ArrayList_Str* type_args) {
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, stmt_idx);
    ArrayList_StrMapEntry old_type_map = self->current_type_map;
    self->current_type_map = ArrayList_StrMapEntry_init(self->allocator);
    Codegen_setup_current_type_map(self, &(stmt.enum_type_params), type_args);
    const char* typedef_str = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "typedef struct ";
  const char* const _tmp_r = concrete_name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = " ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = concrete_name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ";\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    (void)(StringBuilder_append(&(self->struct_decls), typedef_str));
    const char* tags_name = /* Str concat */ ({
  const char* const _tmp_l = concrete_name;
  const char* const _tmp_r = "_tags";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    const char* tags_str = "typedef enum {\n";
    int64_t i = 0;
    while (i < ArrayList_Variant_length(&(stmt.enum_variants))) {
    Variant v = ArrayList_Variant_get(&(stmt.enum_variants), i);
    tags_str = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = tags_str;
  const char* const _tmp_r = "    ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = concrete_name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "_";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = v.vname;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "_TAG,\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    i = (i + 1);
}
    tags_str = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = tags_str;
  const char* const _tmp_r = "} ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = tags_name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ";\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    (void)(StringBuilder_append(&(self->struct_decls), tags_str));
    const char* body = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "struct ";
  const char* const _tmp_r = concrete_name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = " {\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    body = /* Str concat */ ({
  const char* const _tmp_l = body;
  const char* const _tmp_r = "    uint8_t tag;\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    body = /* Str concat */ ({
  const char* const _tmp_l = body;
  const char* const _tmp_r = "    union {\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    i = 0;
    while (i < ArrayList_Variant_length(&(stmt.enum_variants))) {
    Variant v = ArrayList_Variant_get(&(stmt.enum_variants), i);
    if (ArrayList_Param_length(&(v.params)) > 0) {
    body = /* Str concat */ ({
  const char* const _tmp_l = body;
  const char* const _tmp_r = "        struct {\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    int64_t p_idx = 0;
    while (p_idx < ArrayList_Param_length(&(v.params))) {
    Param p = ArrayList_Param_get(&(v.params), p_idx);
    body = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = body;
  const char* const _tmp_r = "            ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = Codegen_map_type(self, p.ptype);
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = " ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = p.name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ";\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    p_idx = (p_idx + 1);
}
    body = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = body;
  const char* const _tmp_r = "        } ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = v.vname;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ";\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    i = (i + 1);
}
    body = /* Str concat */ ({
  const char* const _tmp_l = body;
  const char* const _tmp_r = "    } payload;\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    body = /* Str concat */ ({
  const char* const _tmp_l = body;
  const char* const _tmp_r = "};\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    (void)(StringBuilder_append(&(self->struct_decls), body));
    Codegen_monomorphize_methods(self, stmt.enum_name, concrete_name);
    self->current_type_map = old_type_map;
}
void Codegen_monomorphize_methods(Codegen* self, const char* base_struct_name, const char* concrete_struct_name) {
    int64_t idx = 0;
    while (idx < ArrayList_StmtNode_length(self->stmt_pool)) {
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, idx);
    if ((stmt.kind == StmtKind_sk_impl_block) && (strcmp(stmt.impl_struct_name, base_struct_name) == 0)) {
    int64_t j = 0;
    while (j < ArrayList_Int_length(&(stmt.impl_methods))) {
    int64_t m_idx = ArrayList_Int_get(&(stmt.impl_methods), j);
    StmtNode m_node = ArrayList_StmtNode_get(self->stmt_pool, m_idx);
    const char* method_name = m_node.func_name;
    bool is_init = ((((strcmp(method_name, "init") == 0) || (strcmp(m_node.func_return_type, base_struct_name) == 0)) || (strcmp(m_node.func_return_type, /* Str concat */ ({
  const char* const _tmp_l = "*";
  const char* const _tmp_r = base_struct_name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
})) == 0)) || (strcmp(m_node.func_return_type, /* Str concat */ ({
  const char* const _tmp_l = "&";
  const char* const _tmp_r = base_struct_name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
})) == 0));
    const char* ret_type = "";
    if (is_init) {
    ret_type = concrete_struct_name;
} else {
    ret_type = Codegen_map_type(self, m_node.func_return_type);
}
    const char* params_str = "";
    if (!is_init) {
    params_str = /* Str concat */ ({
  const char* const _tmp_l = concrete_struct_name;
  const char* const _tmp_r = "* self";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    int64_t p_idx = 0;
    while (p_idx < ArrayList_Param_length(&(m_node.func_params))) {
    Param p = ArrayList_Param_get(&(m_node.func_params), p_idx);
    if (strcmp(p.name, "self") != 0) {
    if (strlen(params_str) > 0) {
    params_str = /* Str concat */ ({
  const char* const _tmp_l = params_str;
  const char* const _tmp_r = ", ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    params_str = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = params_str;
  const char* const _tmp_r = Codegen_map_type(self, p.ptype);
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = " ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = p.name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    p_idx = (p_idx + 1);
}
    if (strlen(params_str) == 0) {
    params_str = "void";
}
    const char* mangled_fn_name = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = concrete_struct_name;
  const char* const _tmp_r = "_";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = method_name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    const char* concrete_ret = m_node.func_return_type;
    if (ArrayList_StrMapEntry_length(&(self->current_type_map)) > 0) {
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
    type_map_put(&(self->var_types), "self", /* Str concat */ ({
  const char* const _tmp_l = "*";
  const char* const _tmp_r = concrete_struct_name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
}));
}
    int64_t p_idx2 = 0;
    while (p_idx2 < ArrayList_Param_length(&(m_node.func_params))) {
    Param p = ArrayList_Param_get(&(m_node.func_params), p_idx2);
    if (strcmp(p.name, "self") != 0) {
    type_map_put(&(self->var_types), p.name, p.ptype);
}
    p_idx2 = (p_idx2 + 1);
}
    const char* body_str = Codegen_gen_stmt(self, m_node.func_body);
    while (ArrayList_StrMapEntry_length(&(self->var_types)) > old_var_len) {
    (void)(ArrayList_StrMapEntry_pop(&(self->var_types)));
}
    if (is_init) {
    const char* self_decl = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "    ";
  const char* const _tmp_r = concrete_struct_name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = " self = (";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = concrete_struct_name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "){0};\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    const char* self_ret = "    return self;\n}";
    int64_t body_len = strlen(body_str);
    body_str = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "{\n";
  const char* const _tmp_r = self_decl;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = substring(body_str, 2, (body_len - 1));
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = self_ret;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    const char* proto = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = ret_type;
  const char* const _tmp_r = " ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = mangled_fn_name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "(";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = params_str;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ");\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    const char* impl_str = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = ret_type;
  const char* const _tmp_r = " ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = mangled_fn_name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "(";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = params_str;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ") ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = body_str;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    (void)(StringBuilder_append(&(self->func_decls), proto));
    (void)(StringBuilder_append(&(self->output), impl_str));
    self->cur_func_name = old_fn;
    self->cur_return_type = old_ret;
    self->cur_method_is_init = old_init;
    j = (j + 1);
}
}
    idx = (idx + 1);
}
}
const char* Codegen_extract_first_type_arg(Codegen* self, const char* type_name) {
    int64_t start = (-1);
    int64_t end = (-1);
    int64_t i = 0;
    while (i < strlen(type_name)) {
    char c = (type_name)[i];
    if (c == ((char)(60))) {
    start = (i + 1);
} else if (c == ((char)(44))) {
    end = i;
    break;
} else if (c == ((char)(62))) {
    end = i;
    break;
}
    i = (i + 1);
}
    if ((start >= 0) && (end >= 0)) {
    return substring(type_name, start, end);
}
    return "Int";
}
void Codegen_build_func_types(Codegen* self) {
    int64_t i = 0;
    while (i < ArrayList_StmtNode_length(self->stmt_pool)) {
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, i);
    if (stmt.kind == StmtKind_sk_func_decl) {
    type_map_put(&(self->func_types), stmt.func_name, stmt.func_return_type);
}
    if (stmt.kind == StmtKind_sk_extern) {
    type_map_put(&(self->func_types), stmt.extern_name, stmt.extern_return);
}
    if (stmt.kind == StmtKind_sk_impl_block) {
    const char* struct_name = stmt.impl_struct_name;
    int64_t j = 0;
    while (j < ArrayList_Int_length(&(stmt.impl_methods))) {
    int64_t m_idx = ArrayList_Int_get(&(stmt.impl_methods), j);
    StmtNode m_node = ArrayList_StmtNode_get(self->stmt_pool, m_idx);
    const char* key = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = struct_name;
  const char* const _tmp_r = "_";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = m_node.func_name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    const char* ret = m_node.func_return_type;
    if (strcmp(m_node.func_name, "init") == 0) {
    ret = struct_name;
}
    type_map_put(&(self->func_types), key, ret);
    j = (j + 1);
}
}
    i = (i + 1);
}
}
const char* Codegen_get_expr_type(Codegen* self, int64_t expr_idx) {
    if (expr_idx < 0) {
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
    if (strlen(var_t) > 0) {
    return var_t;
}
    const char* fn_t = type_map_get(&(self->func_types), name);
    if (strlen(fn_t) > 0) {
    return fn_t;
}
    char first_char = (name)[0];
    if ((first_char >= ((char)(65))) && (first_char <= ((char)(90)))) {
    if (ArrayList_Str_length(&(expr.ident_type_args)) > 0) {
    const char* full_name = /* Str concat */ ({
  const char* const _tmp_l = name;
  const char* const _tmp_r = "<";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    int64_t tai = 0;
    while (tai < ArrayList_Str_length(&(expr.ident_type_args))) {
    if (tai > 0) {
    full_name = /* Str concat */ ({
  const char* const _tmp_l = full_name;
  const char* const _tmp_r = ", ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    full_name = /* Str concat */ ({
  const char* const _tmp_l = full_name;
  const char* const _tmp_r = ArrayList_Str_get(&(expr.ident_type_args), tai);
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    tai = (tai + 1);
}
    full_name = /* Str concat */ ({
  const char* const _tmp_l = full_name;
  const char* const _tmp_r = ">";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
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
    return ArrayList_Str_get(&(expr.func_type_args), 0);
}
    if (strcmp(name, "size_of") == 0) {
    return "Int";
}
    if ((((strcmp(name, "Char") == 0) || (strcmp(name, "Int") == 0)) || (strcmp(name, "Float") == 0)) || (strcmp(name, "Bool") == 0)) {
    return name;
}
    bool is_struct = false;
    int64_t s_idx = 0;
    while (s_idx < ArrayList_StmtNode_length(self->stmt_pool)) {
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, s_idx);
    if ((stmt.kind == StmtKind_sk_struct_decl) && (strcmp(stmt.struct_name, name) == 0)) {
    is_struct = true;
}
    s_idx = (s_idx + 1);
}
    if (((strcmp(name, "ArrayList") == 0) || (strcmp(name, "HashMap") == 0)) || (strcmp(name, "StringBuilder") == 0)) {
    is_struct = true;
}
    if (is_struct) {
    if (ArrayList_Str_length(&(expr.func_type_args)) > 0) {
    return /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = name;
  const char* const _tmp_r = "<";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = str_array_join(expr.func_type_args, ", ");
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ">";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    return name;
}
    const char* fn_t = type_map_get(&(self->func_types), name);
    if (strlen(fn_t) > 0) {
    return fn_t;
}
    return "Void";
}
    if (expr.kind == ExprKind_ek_field_access) {
    const char* base_type = Codegen_get_expr_type(self, expr.field_expr);
    const char* clean_type = "";
    int64_t i = 0;
    while (i < strlen(base_type)) {
    char c = (base_type)[i];
    if ((c != ((char)(42))) && (c != ((char)(38)))) {
    clean_type = /* Str concat */ ({
  const char* const _tmp_l = clean_type;
  const char* const _tmp_r = char_to_str(c);
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    i = (i + 1);
}
    if (strcmp(substring(clean_type, 0, 4), "mut ") == 0) {
    clean_type = substring(clean_type, 4, strlen(clean_type));
}
    int64_t s_idx = 0;
    while (s_idx < ArrayList_StmtNode_length(self->stmt_pool)) {
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, s_idx);
    if (stmt.kind == StmtKind_sk_struct_decl) {
    bool is_match = false;
    if (strcmp(stmt.struct_name, clean_type) == 0) {
    is_match = true;
} else if (Codegen_str_contains(self, clean_type, ((char)(95)))) {
    int64_t underscore_pos = Codegen_str_find(self, clean_type, ((char)(95)));
    const char* base_name = substring(clean_type, 0, underscore_pos);
    if (strcmp(stmt.struct_name, base_name) == 0) {
    is_match = true;
}
}
    if (is_match) {
    int64_t f_idx = 0;
    while (f_idx < ArrayList_StructField_length(&(stmt.struct_fields))) {
    StructField f = ArrayList_StructField_get(&(stmt.struct_fields), f_idx);
    if (strcmp(f.name, expr.field_name) == 0) {
    const char* ftype = f.ftype;
    if (ArrayList_StrMapEntry_length(&(self->current_type_map)) > 0) {
    ftype = Codegen_substitute_generic_type(self, ftype);
}
    return ftype;
}
    f_idx = (f_idx + 1);
}
}
}
    s_idx = (s_idx + 1);
}
    return "Void";
}
    if (expr.kind == ExprKind_ek_index) {
    const char* base_type = Codegen_get_expr_type(self, expr.idx_expr);
    if (strcmp(base_type, "Str") == 0) {
    return "Char";
}
    if ((base_type)[0] == ((char)(42))) {
    return substring(base_type, 1, strlen(base_type));
}
    return "Void";
}
    if (expr.kind == ExprKind_ek_borrow) {
    return /* Str concat */ ({
  const char* const _tmp_l = "&";
  const char* const _tmp_r = Codegen_get_expr_type(self, expr.borrow_expr);
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    if (expr.kind == ExprKind_ek_deref) {
    const char* base_type = Codegen_get_expr_type(self, expr.deref_expr);
    if ((strlen(base_type) > 5) && (strcmp(substring(base_type, 0, 5), "*mut ") == 0)) {
    return substring(base_type, 5, strlen(base_type));
}
    if ((strlen(base_type) > 5) && (strcmp(substring(base_type, 0, 5), "&mut ") == 0)) {
    return substring(base_type, 5, strlen(base_type));
}
    if (((base_type)[0] == ((char)(42))) || ((base_type)[0] == ((char)(38)))) {
    return substring(base_type, 1, strlen(base_type));
}
    return "Void";
}
    if (expr.kind == ExprKind_ek_struct_init) {
    return expr.struct_name;
}
    if (expr.kind == ExprKind_ek_method_call) {
    ExprNode receiver_node = ArrayList_ExprNode_get(self->expr_pool, expr.meth_expr);
    const char* method_name = expr.meth_name;
    const char* rec_type = Codegen_get_expr_type(self, expr.meth_expr);
    const char* clean_type = "";
    int64_t i = 0;
    while (i < strlen(rec_type)) {
    char c = (rec_type)[i];
    if ((c != ((char)(42))) && (c != ((char)(38)))) {
    clean_type = /* Str concat */ ({
  const char* const _tmp_l = clean_type;
  const char* const _tmp_r = char_to_str(c);
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    i = (i + 1);
}
    if (strcmp(substring(clean_type, 0, 4), "mut ") == 0) {
    clean_type = substring(clean_type, 4, strlen(clean_type));
}
    bool is_constructor = false;
    if (receiver_node.kind == ExprKind_ek_identifier) {
    const char* r_name = receiver_node.ident_name;
    char first_char = (r_name)[0];
    if ((first_char >= ((char)(65))) && (first_char <= ((char)(90)))) {
    is_constructor = true;
}
}
    if (strcmp(method_name, "init") == 0) {
    return clean_type;
}
    const char* key = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = clean_type;
  const char* const _tmp_r = "_";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = method_name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    const char* ret = type_map_get(&(self->func_types), key);
    if (strlen(ret) > 0) {
    return ret;
}
    const char* clean_rec = rec_type;
    bool done = false;
    while (!done) {
    if ((strlen(clean_rec) > 0) && (((clean_rec)[0] == ((char)(42))) || ((clean_rec)[0] == ((char)(38))))) {
    clean_rec = substring(clean_rec, 1, strlen(clean_rec));
} else {
    done = true;
}
}
    if (strcmp(substring(clean_rec, 0, 4), "mut ") == 0) {
    clean_rec = substring(clean_rec, 4, strlen(clean_rec));
}
    if (Codegen_str_contains(self, clean_rec, ((char)(60)))) {
    int64_t lt_pos = Codegen_str_find(self, clean_rec, ((char)(60)));
    const char* base_struct = substring(clean_rec, 0, lt_pos);
    const char* args_str = substring(clean_rec, (lt_pos + 1), (strlen(clean_rec) - 1));
    ArrayList_Str args = ArrayList_Str_init(self->allocator);
    int64_t start = 0;
    int64_t ai = 0;
    while (ai < strlen(args_str)) {
    char c = (args_str)[ai];
    if (c == ((char)(44))) {
    ArrayList_Str_push(&(args), Codegen_trim_spaces(self, substring(args_str, start, ai)));
    start = (ai + 1);
}
    ai = (ai + 1);
}
    ArrayList_Str_push(&(args), Codegen_trim_spaces(self, substring(args_str, start, strlen(args_str))));
    int64_t struct_idx = (-1);
    int64_t si = 0;
    while (si < ArrayList_StmtNode_length(self->stmt_pool)) {
    StmtNode s = ArrayList_StmtNode_get(self->stmt_pool, si);
    if ((s.kind == StmtKind_sk_struct_decl) && (strcmp(s.struct_name, base_struct) == 0)) {
    struct_idx = si;
}
    si = (si + 1);
}
    if (struct_idx >= 0) {
    StmtNode s_decl = ArrayList_StmtNode_get(self->stmt_pool, struct_idx);
    ArrayList_StrMapEntry temp_map = ArrayList_StrMapEntry_init(self->allocator);
    int64_t pi = 0;
    while (pi < ArrayList_Str_length(&(s_decl.struct_type_params))) {
    const char* p_name = Codegen_trim_spaces(self, ArrayList_Str_get(&(s_decl.struct_type_params), pi));
    if (Codegen_str_contains(self, p_name, ((char)(58)))) {
    int64_t cp = Codegen_str_find(self, p_name, ((char)(58)));
    p_name = substring(p_name, 0, cp);
}
    const char* a_name = ArrayList_Str_get(&(args), pi);
    type_map_put(&(temp_map), p_name, a_name);
    pi = (pi + 1);
}
    int64_t impl_idx = 0;
    while (impl_idx < ArrayList_StmtNode_length(self->stmt_pool)) {
    StmtNode s_impl = ArrayList_StmtNode_get(self->stmt_pool, impl_idx);
    if ((s_impl.kind == StmtKind_sk_impl_block) && (strcmp(s_impl.impl_struct_name, base_struct) == 0)) {
    int64_t mi = 0;
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
    mi = (mi + 1);
}
}
    impl_idx = (impl_idx + 1);
}
}
}
    return "Void";
}
    if (expr.kind == ExprKind_ek_range) {
    return "Range";
}
    if (expr.kind == ExprKind_ek_slice) {
    return expr.inferred_type;
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
    int64_t excl_pos = Codegen_str_find(self, inner_ty, ((char)(33)));
    if (excl_pos >= 0) {
    return substring(inner_ty, 0, excl_pos);
}
    return inner_ty;
}
    if (expr.kind == ExprKind_ek_catch) {
    const char* inner_ty = Codegen_get_expr_type(self, expr.catch_expr);
    int64_t excl_pos = Codegen_str_find(self, inner_ty, ((char)(33)));
    if (excl_pos >= 0) {
    return substring(inner_ty, 0, excl_pos);
}
    return inner_ty;
}
    return "Void";
}
const char* Codegen_gen_expr(Codegen* self, int64_t expr_idx) {
    if (expr_idx < 0) {
    return "";
}
    ExprNode expr = ArrayList_ExprNode_get(self->expr_pool, expr_idx);
    if (expr.kind == ExprKind_ek_try) {
    const char* inner_ty = Codegen_get_expr_type(self, expr.try_expr);
    int64_t excl_pos = Codegen_str_find(self, inner_ty, ((char)(33)));
    const char* inner = Codegen_gen_expr(self, expr.try_expr);
    if (excl_pos < 0) {
    return inner;
}
    const char* val_type = substring(inner_ty, 0, excl_pos);
    const char* result_ctype = Codegen_map_type(self, inner_ty);
    const char* ret_ctype = Codegen_map_type(self, self->cur_return_type);
    const char* try_code = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "({ ";
  const char* const _tmp_r = result_ctype;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = " _kai_res = (";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = inner;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "); ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    try_code = /* Str concat */ ({
  const char* const _tmp_l = try_code;
  const char* const _tmp_r = "if (_kai_res.tag != 0) { ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    try_code = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = try_code;
  const char* const _tmp_r = ret_ctype;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = " _kai_err_ret; _kai_err_ret.tag = _kai_res.tag; return _kai_err_ret; } ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    if (strcmp(val_type, "Void") == 0) {
    try_code = /* Str concat */ ({
  const char* const _tmp_l = try_code;
  const char* const _tmp_r = "0; })";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
} else {
    try_code = /* Str concat */ ({
  const char* const _tmp_l = try_code;
  const char* const _tmp_r = "_kai_res.value; })";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    return try_code;
}
    if (expr.kind == ExprKind_ek_literal) {
    const char* vkind = expr.lit_vkind;
    if (strcmp(vkind, "INT") == 0) {
    if (expr.lit_value.tag == TokenValue_tv_str_TAG) {
    const char* v = expr.lit_value.payload.tv_str.v;

    return v;
} else if (expr.lit_value.tag == TokenValue_tv_int_TAG) {
    int64_t v = expr.lit_value.payload.tv_int.v;

    return int_to_str(v);
} else {
    return "0";
} 
}
    if (strcmp(vkind, "FLOAT") == 0) {
    if (expr.lit_value.tag == TokenValue_tv_str_TAG) {
    const char* v = expr.lit_value.payload.tv_str.v;

    return v;
} else {
    return "0.0";
} 
}
    if (strcmp(vkind, "STRING") == 0) {
    if (expr.lit_value.tag == TokenValue_tv_str_TAG) {
    const char* v = expr.lit_value.payload.tv_str.v;

    return /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "\"";
  const char* const _tmp_r = Codegen_escape_string(self, v);
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "\"";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
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
    const char* v = expr.lit_value.payload.tv_str.v;

    bool is_true = false;
    {
    if (strcmp(v, "true") == 0) {
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

    if (v == ((char)(10))) {
    return "'\\n'";
}
    if (v == ((char)(13))) {
    return "'\\r'";
}
    if (v == ((char)(9))) {
    return "'\\t'";
}
    if (v == ((char)(92))) {
    return "'\\\\'";
}
    if (v == ((char)(39))) {
    return "'\\''";
}
    return /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "'";
  const char* const _tmp_r = char_to_str(v);
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "'";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
} else {
    return "'\\0'";
} 
}
    if (strcmp(vkind, "NONE") == 0) {
    return "NULL";
}
    return "0";
}
    if (expr.kind == ExprKind_ek_identifier) {
    return expr.ident_name;
}
    if (expr.kind == ExprKind_ek_binary_op) {
    const char* lhs = Codegen_gen_expr(self, expr.binop_left);
    const char* rhs = Codegen_gen_expr(self, expr.binop_right);
    const char* op = expr.binop_op;
    ExprNode lhs_node = ArrayList_ExprNode_get(self->expr_pool, expr.binop_left);
    const char* lhs_type = Codegen_get_expr_type(self, expr.binop_left);
    if (strcmp(lhs_type, "Str") == 0) {
    if (strcmp(op, "+") == 0) {
    return /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "/* Str concat */ ({\n  const char* const _tmp_l = ";
  const char* const _tmp_r = lhs;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ";\n  const char* const _tmp_r = ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = rhs;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ";\n  size_t l1 = strlen(_tmp_l);\n  size_t l2 = strlen(_tmp_r);\n  char* buf = malloc(l1 + l2 + 1);\n  strcpy(buf, _tmp_l);\n  strcat(buf, _tmp_r);\n  buf;\n})";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    if (strcmp(op, "==") == 0) {
    return /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "(strcmp(";
  const char* const _tmp_r = lhs;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ", ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = rhs;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ") == 0)";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    if (strcmp(op, "!=") == 0) {
    return /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "(strcmp(";
  const char* const _tmp_r = lhs;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ", ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = rhs;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ") != 0)";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
}
    if (((strcmp(op, "==") == 0) || (strcmp(op, "!=") == 0)) && Codegen_is_enum_type(self, lhs_type)) {
    if (Codegen_enum_has_payload(self, lhs_type)) {
    bool is_ptr = false;
    if (((lhs_type)[0] == ((char)(42))) || ((lhs_type)[0] == ((char)(38)))) {
    is_ptr = true;
}
    const char* tag_op = ".";
    if (is_ptr) {
    tag_op = "->";
}
    const char* rhs_type = Codegen_get_expr_type(self, expr.binop_right);
    bool rhs_is_ptr = false;
    if (((rhs_type)[0] == ((char)(42))) || ((rhs_type)[0] == ((char)(38)))) {
    rhs_is_ptr = true;
}
    const char* rhs_tag_op = ".";
    if (rhs_is_ptr) {
    rhs_tag_op = "->";
}
    return /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "((";
  const char* const _tmp_r = lhs;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ")";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = tag_op;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "tag ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = op;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = " (";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = rhs;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ")";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = rhs_tag_op;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "tag)";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
}
    return /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "(";
  const char* const _tmp_r = lhs;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = " ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = op;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = " ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = rhs;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ")";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    if (expr.kind == ExprKind_ek_unary_op) {
    const char* operand = Codegen_gen_expr(self, expr.unop_operand);
    const char* op = expr.unop_op;
    if (strcmp(op, "own") == 0) {
    return operand;
}
    return /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "(";
  const char* const _tmp_r = op;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = operand;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ")";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    if (expr.kind == ExprKind_ek_func_call) {
    const char* name = expr.func_name;
    if ((strcmp(name, "cast") == 0) || (strcmp(name, "as") == 0)) {
    return /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "(";
  const char* const _tmp_r = Codegen_map_type(self, ArrayList_Str_get(&(expr.func_type_args), 0));
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ")(";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = Codegen_gen_expr(self, ArrayList_Int_get(&(expr.func_args), 0));
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ")";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    if (strcmp(name, "size_of") == 0) {
    return /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "sizeof(";
  const char* const _tmp_r = Codegen_map_type(self, ArrayList_Str_get(&(expr.func_type_args), 0));
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ")";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    if ((((strcmp(name, "Char") == 0) || (strcmp(name, "Int") == 0)) || (strcmp(name, "Float") == 0)) || (strcmp(name, "Bool") == 0)) {
    const char* ctype = Codegen_map_type(self, name);
    const char* arg_val = Codegen_gen_expr(self, ArrayList_Int_get(&(expr.func_args), 0));
    return /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "((";
  const char* const _tmp_r = ctype;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ")(";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = arg_val;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "))";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    if (strcmp(name, "length") == 0) {
    const char* arg_val = Codegen_gen_expr(self, ArrayList_Int_get(&(expr.func_args), 0));
    return /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "strlen(";
  const char* const _tmp_r = arg_val;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ")";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    if (strcmp(name, "print") == 0) {
    int64_t arg = ArrayList_Int_get(&(expr.func_args), 0);
    const char* val = Codegen_gen_expr(self, arg);
    const char* arg_type = Codegen_get_expr_type(self, arg);
    if (strcmp(arg_type, "Int") == 0) {
    return /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "printf(\"%lld\\n\", (long long)(";
  const char* const _tmp_r = val;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "))";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    if (strcmp(arg_type, "Float") == 0) {
    return /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "printf(\"%f\\n\", (double)(";
  const char* const _tmp_r = val;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "))";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    if (strcmp(arg_type, "Char") == 0) {
    return /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "printf(\"%c\\n\", (char)(";
  const char* const _tmp_r = val;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "))";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    if (strcmp(arg_type, "Bool") == 0) {
    return /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "printf(\"%s\\n\", (";
  const char* const _tmp_r = val;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ") ? \"true\" : \"false\")";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    return /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "printf(\"%s\\n\", ";
  const char* const _tmp_r = val;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ")";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    bool is_struct = false;
    int64_t s_idx = 0;
    while (s_idx < ArrayList_StmtNode_length(self->stmt_pool)) {
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, s_idx);
    if ((stmt.kind == StmtKind_sk_struct_decl) && (strcmp(stmt.struct_name, name) == 0)) {
    is_struct = true;
}
    s_idx = (s_idx + 1);
}
    if (((strcmp(name, "ArrayList") == 0) || (strcmp(name, "HashMap") == 0)) || (strcmp(name, "StringBuilder") == 0)) {
    is_struct = true;
}
    const char* fn_name = name;
    if (ArrayList_Str_length(&(expr.func_type_args)) > 0) {
    int64_t j = 0;
    while (j < ArrayList_Str_length(&(expr.func_type_args))) {
    fn_name = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = fn_name;
  const char* const _tmp_r = "_";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = Codegen_clean_type_for_mangling(self, ArrayList_Str_get(&(expr.func_type_args), j));
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    j = (j + 1);
}
}
    if (is_struct) {
    fn_name = /* Str concat */ ({
  const char* const _tmp_l = fn_name;
  const char* const _tmp_r = "_init";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    const char* args_str = "";
    int64_t i = 0;
    while (i < ArrayList_Int_length(&(expr.func_args))) {
    if (i > 0) {
    args_str = /* Str concat */ ({
  const char* const _tmp_l = args_str;
  const char* const _tmp_r = ", ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    args_str = /* Str concat */ ({
  const char* const _tmp_l = args_str;
  const char* const _tmp_r = Codegen_gen_expr(self, ArrayList_Int_get(&(expr.func_args), i));
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    i = (i + 1);
}
    return /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = fn_name;
  const char* const _tmp_r = "(";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = args_str;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ")";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    if (expr.kind == ExprKind_ek_field_access) {
    ExprNode base_node = ArrayList_ExprNode_get(self->expr_pool, expr.field_expr);
    if ((base_node.kind == ExprKind_ek_identifier) && Codegen_is_enum_type(self, base_node.ident_name)) {
    const char* enum_name = Codegen_map_type(self, Codegen_get_expr_type(self, expr.field_expr));
    const char* var_name = expr.field_name;
    if (Codegen_enum_has_payload(self, base_node.ident_name)) {
    return /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "(";
  const char* const _tmp_r = enum_name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "){ .tag = ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = enum_name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "_";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = var_name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "_TAG }";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
} else {
    return /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = enum_name;
  const char* const _tmp_r = "_";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = var_name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
}
    const char* base_val = Codegen_gen_expr(self, expr.field_expr);
    const char* base_type = Codegen_get_expr_type(self, expr.field_expr);
    bool is_ptr = false;
    bool is_self_ptr = (((base_node.kind == ExprKind_ek_identifier) && (strcmp(base_node.ident_name, "self") == 0)) && (!self->cur_method_is_init));
    if ((((base_type)[0] == ((char)(42))) || ((base_type)[0] == ((char)(38)))) || is_self_ptr) {
    is_ptr = true;
}
    const char* op = ".";
    if (is_ptr) {
    op = "->";
}
    bool is_complex = (((base_node.kind == ExprKind_ek_func_call) || (base_node.kind == ExprKind_ek_index)) || (base_node.kind == ExprKind_ek_deref));
    if (is_ptr && is_complex) {
    return /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "(";
  const char* const _tmp_r = base_val;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ")";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = op;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = expr.field_name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    return /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = base_val;
  const char* const _tmp_r = op;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = expr.field_name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    if (expr.kind == ExprKind_ek_index) {
    const char* base_val = Codegen_gen_expr(self, expr.idx_expr);
    const char* idx_val = Codegen_gen_expr(self, expr.idx_index);
    return /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "(";
  const char* const _tmp_r = base_val;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ")[";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = idx_val;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "]";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    if (expr.kind == ExprKind_ek_borrow) {
    return /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "&(";
  const char* const _tmp_r = Codegen_gen_expr(self, expr.borrow_expr);
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ")";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    if (expr.kind == ExprKind_ek_deref) {
    return /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "*(";
  const char* const _tmp_r = Codegen_gen_expr(self, expr.deref_expr);
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ")";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
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
    return /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "(Range){ .start = ";
  const char* const _tmp_r = start;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ", .end = ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = end;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ", .is_inclusive = ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = incl;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = " }";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    if (expr.kind == ExprKind_ek_slice) {
    return Codegen_gen_expr(self, expr.slice_expr);
}
    if (expr.kind == ExprKind_ek_array) {
    ArrayList_Str elems = ArrayList_Str_init(self->allocator);
    int64_t i = 0;
    while (i < ArrayList_Int_length(&(expr.arr_elements))) {
    ArrayList_Str_push(&(elems), Codegen_gen_expr(self, ArrayList_Int_get(&(expr.arr_elements), i)));
    i = (i + 1);
}
    const char* elems_str = str_array_join(elems, ", ");
    if (strlen(elems_str) == 0) {
    elems_str = "0";
}
    const char* inner_ty = "Int";
    if ((strlen(expr.inferred_type) > 2) && (strcmp(substring(expr.inferred_type, 0, 2), "[]") == 0)) {
    inner_ty = substring(expr.inferred_type, 2, strlen(expr.inferred_type));
}
    const char* mapped_inner = Codegen_map_type(self, inner_ty);
    return /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "(";
  const char* const _tmp_r = mapped_inner;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "[]){ ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = elems_str;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = " }";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    if (expr.kind == ExprKind_ek_tuple) {
    if (strlen(expr.inferred_type) > 0) {
    const char* mapped_ty = Codegen_map_type(self, expr.inferred_type);
    ArrayList_Str elems = ArrayList_Str_init(self->allocator);
    int64_t i = 0;
    while (i < ArrayList_Int_length(&(expr.tup_elements))) {
    ArrayList_Str_push(&(elems), Codegen_gen_expr(self, ArrayList_Int_get(&(expr.tup_elements), i)));
    i = (i + 1);
}
    return /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "(";
  const char* const _tmp_r = mapped_ty;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "){ ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = str_array_join(elems, ", ");
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = " }";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    return "NULL";
}
    if (expr.kind == ExprKind_ek_asm) {
    ArrayList_Str decls = ArrayList_Str_init(self->allocator);
    ArrayList_Str out_ops = ArrayList_Str_init(self->allocator);
    int64_t i = 0;
    while (i < ArrayList_AsmOutput_length(&(expr.asm_outputs))) {
    AsmOutput out = ArrayList_AsmOutput_get(&(expr.asm_outputs), i);
    if (strlen(out.type_name) > 0) {
    const char* mapped_type = Codegen_map_type(self, out.type_name);
    const char* var_name = /* Str concat */ ({
  const char* const _tmp_l = "asm_ret_";
  const char* const _tmp_r = int_to_str(i);
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    ArrayList_Str_push(&(decls), /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = mapped_type;
  const char* const _tmp_r = " ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = var_name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ";";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
}));
    ArrayList_Str_push(&(out_ops), /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "[";
  const char* const _tmp_r = out.name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "] \"";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = out.constraint;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "\" (";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = var_name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ")";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
}));
} else if (out.expr_idx >= 0) {
    const char* val_str = Codegen_gen_expr(self, out.expr_idx);
    ArrayList_Str_push(&(out_ops), /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "[";
  const char* const _tmp_r = out.name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "] \"";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = out.constraint;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "\" (";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = val_str;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ")";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
}));
}
    i = (i + 1);
}
    ArrayList_Str in_ops = ArrayList_Str_init(self->allocator);
    int64_t j = 0;
    while (j < ArrayList_AsmInput_length(&(expr.asm_inputs))) {
    AsmInput inp = ArrayList_AsmInput_get(&(expr.asm_inputs), j);
    const char* val_str = Codegen_gen_expr(self, inp.expr_idx);
    ArrayList_Str_push(&(in_ops), /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "[";
  const char* const _tmp_r = inp.name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "] \"";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = inp.constraint;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "\" (";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = val_str;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ")";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
}));
    j = (j + 1);
}
    ArrayList_Str clobs = ArrayList_Str_init(self->allocator);
    int64_t k = 0;
    while (k < ArrayList_Str_length(&(expr.asm_clobbers))) {
    ArrayList_Str_push(&(clobs), /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "\"";
  const char* const _tmp_r = ArrayList_Str_get(&(expr.asm_clobbers), k);
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "\"";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
}));
    k = (k + 1);
}
    const char* volatile_prefix = "";
    if (expr.asm_is_volatile) {
    volatile_prefix = "volatile";
}
    const char* escaped_asm = "";
    int64_t c_idx = 0;
    while (c_idx < strlen(expr.asm_code)) {
    char c = (expr.asm_code)[c_idx];
    if (c == ((char)(10))) {
    escaped_asm = /* Str concat */ ({
  const char* const _tmp_l = escaped_asm;
  const char* const _tmp_r = "\\n\\t";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
} else if (c == ((char)(34))) {
    escaped_asm = /* Str concat */ ({
  const char* const _tmp_l = escaped_asm;
  const char* const _tmp_r = "\\\"";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
} else {
    escaped_asm = /* Str concat */ ({
  const char* const _tmp_l = escaped_asm;
  const char* const _tmp_r = char_to_str(c);
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    c_idx = (c_idx + 1);
}
    const char* asm_stmt = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "__asm__ ";
  const char* const _tmp_r = volatile_prefix;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = " (\"";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = escaped_asm;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "\"";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    if (((ArrayList_Str_length(&(out_ops)) > 0) || (ArrayList_Str_length(&(in_ops)) > 0)) || (ArrayList_Str_length(&(clobs)) > 0)) {
    asm_stmt = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = asm_stmt;
  const char* const _tmp_r = " : ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = str_array_join(out_ops, ", ");
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    if ((ArrayList_Str_length(&(in_ops)) > 0) || (ArrayList_Str_length(&(clobs)) > 0)) {
    asm_stmt = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = asm_stmt;
  const char* const _tmp_r = " : ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = str_array_join(in_ops, ", ");
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    if (ArrayList_Str_length(&(clobs)) > 0) {
    asm_stmt = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = asm_stmt;
  const char* const _tmp_r = " : ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = str_array_join(clobs, ", ");
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    asm_stmt = /* Str concat */ ({
  const char* const _tmp_l = asm_stmt;
  const char* const _tmp_r = ");";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    const char* res = "({\n";
    int64_t d_idx = 0;
    while (d_idx < ArrayList_Str_length(&(decls))) {
    res = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = res;
  const char* const _tmp_r = "    ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ArrayList_Str_get(&(decls), d_idx);
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    d_idx = (d_idx + 1);
}
    res = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = res;
  const char* const _tmp_r = "    ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = asm_stmt;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    if (ArrayList_AsmOutput_length(&(expr.asm_outputs)) == 1) {
    AsmOutput out0 = ArrayList_AsmOutput_get(&(expr.asm_outputs), 0);
    if (strlen(out0.type_name) > 0) {
    res = /* Str concat */ ({
  const char* const _tmp_l = res;
  const char* const _tmp_r = "    asm_ret_0;\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
} else if (ArrayList_AsmOutput_length(&(expr.asm_outputs)) > 1) {
    ArrayList_Str types = ArrayList_Str_init(self->allocator);
    int64_t ti = 0;
    bool all_typed = true;
    while (ti < ArrayList_AsmOutput_length(&(expr.asm_outputs))) {
    AsmOutput out = ArrayList_AsmOutput_get(&(expr.asm_outputs), ti);
    if (strlen(out.type_name) == 0) {
    all_typed = false;
}
    ArrayList_Str_push(&(types), out.type_name);
    ti = (ti + 1);
}
    if (all_typed) {
    const char* tuple_type = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "(";
  const char* const _tmp_r = str_array_join(types, ", ");
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ")";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    const char* mapped_tuple = Codegen_map_type(self, tuple_type);
    ArrayList_Str vals = ArrayList_Str_init(self->allocator);
    int64_t vi = 0;
    while (vi < ArrayList_AsmOutput_length(&(expr.asm_outputs))) {
    ArrayList_Str_push(&(vals), /* Str concat */ ({
  const char* const _tmp_l = "asm_ret_";
  const char* const _tmp_r = int_to_str(vi);
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
}));
    vi = (vi + 1);
}
    res = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = res;
  const char* const _tmp_r = "    (";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = mapped_tuple;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "){ ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = str_array_join(vals, ", ");
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = " };\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
}
    res = /* Str concat */ ({
  const char* const _tmp_l = res;
  const char* const _tmp_r = "})";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    return res;
}
    if (expr.kind == ExprKind_ek_struct_init) {
    bool is_enum = ((strlen(expr.struct_name) > 0) && Codegen_str_contains(self, expr.struct_name, ((char)(46))));
    if (is_enum) {
    int64_t dot_pos = Codegen_str_find(self, expr.struct_name, ((char)(46)));
    const char* enum_part = substring(expr.struct_name, 0, dot_pos);
    const char* variant_name = substring(expr.struct_name, (dot_pos + 1), strlen(expr.struct_name));
    const char* enum_name = Codegen_map_type(self, enum_part);
    const char* fields_str = "";
    int64_t i = 0;
    while (i < ArrayList_FieldInit_length(&(expr.struct_fields))) {
    FieldInit f = ArrayList_FieldInit_get(&(expr.struct_fields), i);
    if (i > 0) {
    fields_str = /* Str concat */ ({
  const char* const _tmp_l = fields_str;
  const char* const _tmp_r = ", ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    fields_str = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = fields_str;
  const char* const _tmp_r = ".";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = f.name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = " = ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = Codegen_gen_expr(self, f.value);
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    i = (i + 1);
}
    const char* payload_str = "";
    if (strlen(fields_str) > 0) {
    payload_str = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = ", .payload = { .";
  const char* const _tmp_r = variant_name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = " = { ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = fields_str;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = " } }";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    return /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "(";
  const char* const _tmp_r = enum_name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "){ .tag = ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = enum_name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "_";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = variant_name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "_TAG";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = payload_str;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = " }";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
} else {
    const char* struct_name = Codegen_map_type(self, expr.struct_name);
    const char* fields_str = "";
    int64_t i = 0;
    while (i < ArrayList_FieldInit_length(&(expr.struct_fields))) {
    FieldInit f = ArrayList_FieldInit_get(&(expr.struct_fields), i);
    if (i > 0) {
    fields_str = /* Str concat */ ({
  const char* const _tmp_l = fields_str;
  const char* const _tmp_r = ", ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    fields_str = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = fields_str;
  const char* const _tmp_r = ".";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = f.name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = " = ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = Codegen_gen_expr(self, f.value);
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    i = (i + 1);
}
    return /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "(";
  const char* const _tmp_r = struct_name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "){ ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = fields_str;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = " }";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
}
    if (expr.kind == ExprKind_ek_method_call) {
    int64_t receiver_idx = expr.meth_expr;
    ExprNode receiver_node = ArrayList_ExprNode_get(self->expr_pool, receiver_idx);
    const char* method_name = expr.meth_name;
    const char* rec_type = Codegen_get_expr_type(self, expr.meth_expr);
    const char* clean_type = "";
    int64_t i = 0;
    while (i < strlen(rec_type)) {
    char c = (rec_type)[i];
    if ((c != ((char)(42))) && (c != ((char)(38)))) {
    clean_type = /* Str concat */ ({
  const char* const _tmp_l = clean_type;
  const char* const _tmp_r = char_to_str(c);
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    i = (i + 1);
}
    if (strcmp(substring(clean_type, 0, 4), "mut ") == 0) {
    clean_type = substring(clean_type, 4, strlen(clean_type));
}
    clean_type = Codegen_map_type(self, clean_type);
    bool is_constructor = false;
    if (receiver_node.kind == ExprKind_ek_identifier) {
    const char* r_name = receiver_node.ident_name;
    char first_char = (r_name)[0];
    if ((first_char >= ((char)(65))) && (first_char <= ((char)(90)))) {
    is_constructor = true;
    clean_type = Codegen_map_type(self, rec_type);
}
}
    const char* func_name = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = clean_type;
  const char* const _tmp_r = "_";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = method_name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    const char* args_str = "";
    if ((!is_constructor) && (strcmp(method_name, "init") != 0)) {
    const char* rec_val = Codegen_gen_expr(self, receiver_idx);
    const char* rec_inferred = Codegen_get_expr_type(self, receiver_idx);
    bool is_self_ptr = (((receiver_node.kind == ExprKind_ek_identifier) && (strcmp(receiver_node.ident_name, "self") == 0)) && (!self->cur_method_is_init));
    if ((((rec_inferred)[0] == ((char)(42))) || ((rec_inferred)[0] == ((char)(38)))) || is_self_ptr) {
    args_str = rec_val;
} else {
    args_str = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "&(";
  const char* const _tmp_r = rec_val;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ")";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
}
    int64_t ai = 0;
    while (ai < ArrayList_Int_length(&(expr.meth_args))) {
    if (strlen(args_str) > 0) {
    args_str = /* Str concat */ ({
  const char* const _tmp_l = args_str;
  const char* const _tmp_r = ", ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    args_str = /* Str concat */ ({
  const char* const _tmp_l = args_str;
  const char* const _tmp_r = Codegen_gen_expr(self, ArrayList_Int_get(&(expr.meth_args), ai));
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    ai = (ai + 1);
}
    if ((strcmp(method_name, "init") == 0) && (!is_constructor)) {
    const char* rec_val = Codegen_gen_expr(self, receiver_idx);
    const char* rec_inferred = Codegen_get_expr_type(self, receiver_idx);
    if (((rec_inferred)[0] == ((char)(42))) || ((rec_inferred)[0] == ((char)(38)))) {
    return /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "*(";
  const char* const _tmp_r = rec_val;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ") = ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = func_name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "(";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = args_str;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ")";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    return /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = rec_val;
  const char* const _tmp_r = " = ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = func_name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "(";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = args_str;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ")";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    return /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = func_name;
  const char* const _tmp_r = "(";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = args_str;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ")";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    if (expr.kind == ExprKind_ek_catch) {
    const char* inner = Codegen_gen_expr(self, expr.catch_expr);
    const char* inner_ty = Codegen_get_expr_type(self, expr.catch_expr);
    int64_t excl_pos = Codegen_str_find(self, inner_ty, ((char)(33)));
    if (excl_pos < 0) {
    return inner;
}
    const char* val_type = substring(inner_ty, 0, excl_pos);
    const char* result_ctype = Codegen_map_type(self, inner_ty);
    const char* val_ctype = Codegen_map_type(self, val_type);
    const char* fallback_code = Codegen_gen_stmt(self, expr.catch_fallback);
    const char* catch_code = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "({ ";
  const char* const _tmp_r = result_ctype;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = " _kai_cr = (";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = inner;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "); ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    if (strcmp(val_type, "Void") == 0) {
    catch_code = /* Str concat */ ({
  const char* const _tmp_l = catch_code;
  const char* const _tmp_r = "if (_kai_cr.tag != 0) { ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    if (strlen(expr.catch_var) > 0) {
    catch_code = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = catch_code;
  const char* const _tmp_r = "int64_t ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = expr.catch_var;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = " = _kai_cr.tag; ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    catch_code = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = catch_code;
  const char* const _tmp_r = fallback_code;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = " } 0; })";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
} else {
    catch_code = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = catch_code;
  const char* const _tmp_r = val_ctype;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = " _kai_cv; ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    catch_code = /* Str concat */ ({
  const char* const _tmp_l = catch_code;
  const char* const _tmp_r = "if (_kai_cr.tag != 0) { ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    if (strlen(expr.catch_var) > 0) {
    catch_code = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = catch_code;
  const char* const _tmp_r = "int64_t ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = expr.catch_var;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = " = _kai_cr.tag; ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    catch_code = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = catch_code;
  const char* const _tmp_r = "_kai_cv = (";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = fallback_code;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "); ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    catch_code = /* Str concat */ ({
  const char* const _tmp_l = catch_code;
  const char* const _tmp_r = "} else { _kai_cv = _kai_cr.value; } _kai_cv; })";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    return catch_code;
}
    return "0";
}
bool Codegen_str_contains(Codegen* self, const char* s, char target) {
    int64_t i = 0;
    while (i < strlen(s)) {
    if ((s)[i] == target) {
    return true;
}
    i = (i + 1);
}
    return false;
}
int64_t Codegen_str_find(Codegen* self, const char* s, char target) {
    int64_t i = 0;
    while (i < strlen(s)) {
    if ((s)[i] == target) {
    return i;
}
    i = (i + 1);
}
    return (-1);
}
bool Codegen_is_standard_c_func(Codegen* self, const char* name) {
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
    if (strcmp(name, "mmap") == 0) {
    return true;
}
    if (strcmp(name, "munmap") == 0) {
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
    if (strcmp(name, "print_int") == 0) {
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
    if (stmt_idx < 0) {
    return "";
}
    StmtNode stmt = ArrayList_StmtNode_get(self->stmt_pool, stmt_idx);
    if (stmt.kind == StmtKind_sk_block) {
    ArrayList_Int_push(&(self->block_stack), stmt_idx);
    const char* block_str = "{\n";
    int64_t i = 0;
    while (i < ArrayList_Int_length(&(stmt.block_stmts))) {
    const char* s = Codegen_gen_stmt(self, ArrayList_Int_get(&(stmt.block_stmts), i));
    if (strlen(s) > 0) {
    block_str = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = block_str;
  const char* const _tmp_r = "    ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = s;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    i = (i + 1);
}
    int64_t di = 0;
    while (di < ArrayList_DropVarEntry_length(&(stmt.block_drop_vars))) {
    DropVarEntry entry = ArrayList_DropVarEntry_get(&(stmt.block_drop_vars), di);
    block_str = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = block_str;
  const char* const _tmp_r = "    ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = entry.base_type;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "_drop(&";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = entry.name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ");\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    di = (di + 1);
}
    block_str = /* Str concat */ ({
  const char* const _tmp_l = block_str;
  const char* const _tmp_r = "}";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    (void)(ArrayList_Int_pop(&(self->block_stack)));
    return block_str;
}
    if (stmt.kind == StmtKind_sk_var_decl) {
    const char* name = stmt.vardecl_name;
    const char* init_val = Codegen_gen_expr(self, stmt.vardecl_value);
    if (strcmp(name, "_") == 0) {
    return /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "(void)(";
  const char* const _tmp_r = init_val;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ");";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    const char* var_type_name = stmt.vardecl_type;
    if (strlen(var_type_name) == 0) {
    var_type_name = Codegen_get_expr_type(self, stmt.vardecl_value);
}
    const char* var_type = Codegen_map_type(self, var_type_name);
    type_map_put(&(self->var_types), name, var_type_name);
    return /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = var_type;
  const char* const _tmp_r = " ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = " = ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = init_val;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ";";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    if (stmt.kind == StmtKind_sk_assignment) {
    const char* lhs = Codegen_gen_expr(self, stmt.assign_target);
    const char* rhs = Codegen_gen_expr(self, stmt.assign_value);
    return /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = lhs;
  const char* const _tmp_r = " = ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = rhs;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ";";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    if (stmt.kind == StmtKind_sk_func_decl) {
    if (ArrayList_Str_length(&(stmt.func_type_params)) > 0) {
    type_map_put(&(self->generic_func_decls), stmt.func_name, int_to_str(stmt_idx));
    return "";
}
    const char* name = stmt.func_name;
    const char* ret_type = Codegen_map_type(self, stmt.func_return_type);
    const char* params_str = "";
    int64_t i = 0;
    while (i < ArrayList_Param_length(&(stmt.func_params))) {
    Param p = ArrayList_Param_get(&(stmt.func_params), i);
    if (i > 0) {
    params_str = /* Str concat */ ({
  const char* const _tmp_l = params_str;
  const char* const _tmp_r = ", ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    params_str = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = params_str;
  const char* const _tmp_r = Codegen_map_type(self, p.ptype);
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = " ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = p.name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    i = (i + 1);
}
    if (strlen(params_str) == 0) {
    params_str = "void";
}
    const char* old_fn = self->cur_func_name;
    const char* old_ret = self->cur_return_type;
    bool old_init = self->cur_method_is_init;
    self->cur_func_name = name;
    self->cur_return_type = stmt.func_return_type;
    self->cur_method_is_init = false;
    int64_t old_var_len2 = ArrayList_StrMapEntry_length(&(self->var_types));
    int64_t p_reg2 = 0;
    while (p_reg2 < ArrayList_Param_length(&(stmt.func_params))) {
    Param p = ArrayList_Param_get(&(stmt.func_params), p_reg2);
    type_map_put(&(self->var_types), p.name, p.ptype);
    p_reg2 = (p_reg2 + 1);
}
    const char* body_str = Codegen_gen_stmt(self, stmt.func_body);
    while (ArrayList_StrMapEntry_length(&(self->var_types)) > old_var_len2) {
    (void)(ArrayList_StrMapEntry_pop(&(self->var_types)));
}
    const char* proto = "";
    const char* impl_str = "";
    if (strcmp(name, "main") == 0) {
    impl_str = /* Str concat */ ({
  const char* const _tmp_l = "int main(int argc, char** argv) ";
  const char* const _tmp_r = body_str;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
} else {
    proto = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = ret_type;
  const char* const _tmp_r = " ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "(";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = params_str;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ");\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    impl_str = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = ret_type;
  const char* const _tmp_r = " ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "(";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = params_str;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ") ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = body_str;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    if (strlen(proto) > 0) {
    (void)(StringBuilder_append(&(self->func_decls), proto));
}
    (void)(StringBuilder_append(&(self->output), impl_str));
    self->cur_func_name = old_fn;
    self->cur_return_type = old_ret;
    self->cur_method_is_init = old_init;
    return "";
}
    if (stmt.kind == StmtKind_sk_struct_decl) {
    if (ArrayList_Str_length(&(stmt.struct_type_params)) > 0) {
    type_map_put(&(self->generic_struct_decls), stmt.struct_name, int_to_str(stmt_idx));
    return "";
}
    const char* name = Codegen_map_type(self, stmt.struct_name);
    const char* struct_str = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "typedef struct ";
  const char* const _tmp_r = name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = " ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ";\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    struct_str = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = struct_str;
  const char* const _tmp_r = "struct ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = " {\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    int64_t i = 0;
    while (i < ArrayList_StructField_length(&(stmt.struct_fields))) {
    StructField f = ArrayList_StructField_get(&(stmt.struct_fields), i);
    struct_str = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = struct_str;
  const char* const _tmp_r = "    ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = Codegen_map_type(self, f.ftype);
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = " ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = f.name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ";\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    i = (i + 1);
}
    struct_str = /* Str concat */ ({
  const char* const _tmp_l = struct_str;
  const char* const _tmp_r = "};\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    (void)(StringBuilder_append(&(self->struct_decls), struct_str));
    return "";
}
    if (stmt.kind == StmtKind_sk_error_decl) {
    type_map_put(&(self->enum_decls), stmt.error_name, int_to_str(stmt_idx));
    const char* name = Codegen_map_type(self, stmt.error_name);
    const char* enum_str = "typedef enum {\n";
    int64_t j = 0;
    while (j < ArrayList_Str_length(&(stmt.error_variants))) {
    const char* vname = ArrayList_Str_get(&(stmt.error_variants), j);
    enum_str = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = enum_str;
  const char* const _tmp_r = "    ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "_";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = vname;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = " = ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = int_to_str((j + 1));
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ",\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    j = (j + 1);
}
    enum_str = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = enum_str;
  const char* const _tmp_r = "} ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ";\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    (void)(StringBuilder_append(&(self->struct_decls), enum_str));
    return "";
}
    if (stmt.kind == StmtKind_sk_enum_decl) {
    type_map_put(&(self->enum_decls), stmt.enum_name, int_to_str(stmt_idx));
    if (ArrayList_Str_length(&(stmt.enum_type_params)) > 0) {
    type_map_put(&(self->generic_enum_decls), stmt.enum_name, int_to_str(stmt_idx));
    return "";
}
    const char* name = Codegen_map_type(self, stmt.enum_name);
    bool has_payload = false;
    int64_t i = 0;
    while (i < ArrayList_Variant_length(&(stmt.enum_variants))) {
    Variant v = ArrayList_Variant_get(&(stmt.enum_variants), i);
    if (ArrayList_Param_length(&(v.params)) > 0) {
    has_payload = true;
}
    i = (i + 1);
}
    const char* enum_str = "";
    if (!has_payload) {
    enum_str = "typedef enum {\n";
    int64_t j = 0;
    while (j < ArrayList_Variant_length(&(stmt.enum_variants))) {
    Variant v = ArrayList_Variant_get(&(stmt.enum_variants), j);
    enum_str = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = enum_str;
  const char* const _tmp_r = "    ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "_";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = v.vname;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ",\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    j = (j + 1);
}
    enum_str = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = enum_str;
  const char* const _tmp_r = "} ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ";\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
} else {
    const char* tags_name = /* Str concat */ ({
  const char* const _tmp_l = name;
  const char* const _tmp_r = "_tags";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    enum_str = "typedef enum {\n";
    int64_t j = 0;
    while (j < ArrayList_Variant_length(&(stmt.enum_variants))) {
    Variant v = ArrayList_Variant_get(&(stmt.enum_variants), j);
    enum_str = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = enum_str;
  const char* const _tmp_r = "    ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "_";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = v.vname;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "_TAG,\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    j = (j + 1);
}
    enum_str = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = enum_str;
  const char* const _tmp_r = "} ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = tags_name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ";\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    enum_str = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = enum_str;
  const char* const _tmp_r = "typedef struct ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = " ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ";\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    enum_str = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = enum_str;
  const char* const _tmp_r = "struct ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = " {\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    enum_str = /* Str concat */ ({
  const char* const _tmp_l = enum_str;
  const char* const _tmp_r = "    uint8_t tag;\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    enum_str = /* Str concat */ ({
  const char* const _tmp_l = enum_str;
  const char* const _tmp_r = "    union {\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    int64_t k = 0;
    while (k < ArrayList_Variant_length(&(stmt.enum_variants))) {
    Variant v = ArrayList_Variant_get(&(stmt.enum_variants), k);
    if (ArrayList_Param_length(&(v.params)) > 0) {
    enum_str = /* Str concat */ ({
  const char* const _tmp_l = enum_str;
  const char* const _tmp_r = "        struct {\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    int64_t p_idx = 0;
    while (p_idx < ArrayList_Param_length(&(v.params))) {
    Param p = ArrayList_Param_get(&(v.params), p_idx);
    enum_str = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = enum_str;
  const char* const _tmp_r = "            ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = Codegen_map_type(self, p.ptype);
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = " ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = p.name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ";\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    p_idx = (p_idx + 1);
}
    enum_str = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = enum_str;
  const char* const _tmp_r = "        } ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = v.vname;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ";\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    k = (k + 1);
}
    enum_str = /* Str concat */ ({
  const char* const _tmp_l = enum_str;
  const char* const _tmp_r = "    } payload;\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    enum_str = /* Str concat */ ({
  const char* const _tmp_l = enum_str;
  const char* const _tmp_r = "};\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    (void)(StringBuilder_append(&(self->struct_decls), enum_str));
    return "";
}
    if (stmt.kind == StmtKind_sk_impl_block) {
    const char* struct_name = stmt.impl_struct_name;
    bool has_generic_struct = ((strlen(type_map_get(&(self->generic_struct_decls), struct_name)) > 0) || (strlen(type_map_get(&(self->generic_enum_decls), struct_name)) > 0));
    if (has_generic_struct || Codegen_str_contains(self, struct_name, ((char)(60)))) {
    type_map_put(&(self->generic_impl_blocks), struct_name, int_to_str(stmt_idx));
    return "";
}
    const char* mapped_struct_name = Codegen_map_type(self, struct_name);
    int64_t idx = 0;
    while (idx < ArrayList_Int_length(&(stmt.impl_methods))) {
    int64_t method_stmt_idx = ArrayList_Int_get(&(stmt.impl_methods), idx);
    StmtNode method_node = ArrayList_StmtNode_get(self->stmt_pool, method_stmt_idx);
    const char* method_name = method_node.func_name;
    bool is_init = ((((strcmp(method_name, "init") == 0) || (strcmp(method_node.func_return_type, struct_name) == 0)) || (strcmp(method_node.func_return_type, /* Str concat */ ({
  const char* const _tmp_l = "*";
  const char* const _tmp_r = struct_name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
})) == 0)) || (strcmp(method_node.func_return_type, /* Str concat */ ({
  const char* const _tmp_l = "&";
  const char* const _tmp_r = struct_name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
})) == 0));
    const char* ret_type = "";
    if (is_init) {
    ret_type = mapped_struct_name;
} else {
    ret_type = Codegen_map_type(self, method_node.func_return_type);
}
    const char* params_str = "";
    if (!is_init) {
    params_str = /* Str concat */ ({
  const char* const _tmp_l = mapped_struct_name;
  const char* const _tmp_r = "* self";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    int64_t p_idx = 0;
    while (p_idx < ArrayList_Param_length(&(method_node.func_params))) {
    Param p = ArrayList_Param_get(&(method_node.func_params), p_idx);
    if (strcmp(p.name, "self") != 0) {
    if (strlen(params_str) > 0) {
    params_str = /* Str concat */ ({
  const char* const _tmp_l = params_str;
  const char* const _tmp_r = ", ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    params_str = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = params_str;
  const char* const _tmp_r = Codegen_map_type(self, p.ptype);
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = " ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = p.name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    p_idx = (p_idx + 1);
}
    if (strlen(params_str) == 0) {
    params_str = "void";
}
    const char* mangled_fn_name = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = mapped_struct_name;
  const char* const _tmp_r = "_";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = method_name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
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
    type_map_put(&(self->var_types), "self", /* Str concat */ ({
  const char* const _tmp_l = "*";
  const char* const _tmp_r = struct_name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
}));
}
    int64_t p_reg = 0;
    while (p_reg < ArrayList_Param_length(&(method_node.func_params))) {
    Param p = ArrayList_Param_get(&(method_node.func_params), p_reg);
    if (strcmp(p.name, "self") != 0) {
    type_map_put(&(self->var_types), p.name, p.ptype);
}
    p_reg = (p_reg + 1);
}
    const char* body_str = Codegen_gen_stmt(self, method_node.func_body);
    while (ArrayList_StrMapEntry_length(&(self->var_types)) > old_var_len) {
    (void)(ArrayList_StrMapEntry_pop(&(self->var_types)));
}
    if (is_init) {
    const char* self_decl = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "    ";
  const char* const _tmp_r = mapped_struct_name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = " self = (";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = mapped_struct_name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "){0};\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    const char* self_ret = "    return self;\n}";
    int64_t body_len = strlen(body_str);
    body_str = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "{\n";
  const char* const _tmp_r = self_decl;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = substring(body_str, 2, (body_len - 1));
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = self_ret;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    const char* proto = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = ret_type;
  const char* const _tmp_r = " ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = mangled_fn_name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "(";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = params_str;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ");\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    const char* impl_str = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = ret_type;
  const char* const _tmp_r = " ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = mangled_fn_name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "(";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = params_str;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ") ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = body_str;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    (void)(StringBuilder_append(&(self->func_decls), proto));
    (void)(StringBuilder_append(&(self->output), impl_str));
    self->cur_func_name = old_fn;
    self->cur_return_type = old_ret;
    self->cur_method_is_init = old_init;
    idx = (idx + 1);
}
    return "";
}
    if (stmt.kind == StmtKind_sk_if) {
    const char* cond_val = Codegen_gen_expr(self, stmt.if_cond);
    const char* cond_str = "";
    if (((strlen(cond_val) > 1) && ((cond_val)[0] == ((char)(40)))) && ((cond_val)[(strlen(cond_val) - 1)] == ((char)(41)))) {
    cond_str = cond_val;
} else {
    cond_str = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "(";
  const char* const _tmp_r = cond_val;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ")";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    const char* if_str = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "if ";
  const char* const _tmp_r = cond_str;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = " ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = Codegen_gen_stmt(self, stmt.if_then);
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    if (stmt.if_else >= 0) {
    StmtNode else_node = ArrayList_StmtNode_get(self->stmt_pool, stmt.if_else);
    if ((else_node.kind == StmtKind_sk_block) && (ArrayList_Int_length(&(else_node.block_stmts)) == 1)) {
    int64_t single_stmt_idx = ArrayList_Int_get(&(else_node.block_stmts), 0);
    StmtNode single_stmt = ArrayList_StmtNode_get(self->stmt_pool, single_stmt_idx);
    if (single_stmt.kind == StmtKind_sk_if) {
    if_str = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = if_str;
  const char* const _tmp_r = " else ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = Codegen_gen_stmt(self, single_stmt_idx);
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
} else {
    if_str = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = if_str;
  const char* const _tmp_r = " else ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = Codegen_gen_stmt(self, stmt.if_else);
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
} else {
    if_str = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = if_str;
  const char* const _tmp_r = " else ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = Codegen_gen_stmt(self, stmt.if_else);
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
}
    return if_str;
}
    if (stmt.kind == StmtKind_sk_while) {
    const char* cond_val = Codegen_gen_expr(self, stmt.while_cond);
    const char* cond_str = "";
    if (((strlen(cond_val) > 1) && ((cond_val)[0] == ((char)(40)))) && ((cond_val)[(strlen(cond_val) - 1)] == ((char)(41)))) {
    cond_str = cond_val;
} else {
    cond_str = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "(";
  const char* const _tmp_r = cond_val;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ")";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    if (stmt.while_body >= 0) {
    StmtNode body_stmt = ArrayList_StmtNode_get(self->stmt_pool, stmt.while_body);
    body_stmt.block_is_loop_body = true;
    ArrayList_StmtNode_set(self->stmt_pool, stmt.while_body, body_stmt);
}
    return /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "while ";
  const char* const _tmp_r = cond_str;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = " ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = Codegen_gen_stmt(self, stmt.while_body);
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    if (stmt.kind == StmtKind_sk_for) {
    const char* iter_var = stmt.for_var;
    const char* start = Codegen_gen_expr(self, stmt.for_start);
    const char* end = Codegen_gen_expr(self, stmt.for_end);
    const char* op = "<";
    if (stmt.for_inclusive) {
    op = "<=";
}
    if (stmt.for_body >= 0) {
    StmtNode body_stmt = ArrayList_StmtNode_get(self->stmt_pool, stmt.for_body);
    body_stmt.block_is_loop_body = true;
    ArrayList_StmtNode_set(self->stmt_pool, stmt.for_body, body_stmt);
}
    const char* body = Codegen_gen_stmt(self, stmt.for_body);
    return /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "for (int64_t ";
  const char* const _tmp_r = iter_var;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = " = ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = start;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "; ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = iter_var;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = " ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = op;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = " ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = end;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "; ++";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = iter_var;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ") ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = body;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    if (stmt.kind == StmtKind_sk_return) {
    ArrayList_Str drop_calls = ArrayList_Str_init(self->allocator);
    int64_t bi = (ArrayList_Int_length(&(self->block_stack)) - 1);
    while (bi >= 0) {
    int64_t b_idx = ArrayList_Int_get(&(self->block_stack), bi);
    StmtNode b_node = ArrayList_StmtNode_get(self->stmt_pool, b_idx);
    int64_t di = 0;
    while (di < ArrayList_DropVarEntry_length(&(b_node.block_drop_vars))) {
    DropVarEntry entry = ArrayList_DropVarEntry_get(&(b_node.block_drop_vars), di);
    ArrayList_Str_push(&(drop_calls), /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = entry.base_type;
  const char* const _tmp_r = "_drop(&";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = entry.name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ");";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
}));
    di = (di + 1);
}
    bi = (bi - 1);
}
    if (ArrayList_Str_length(&(drop_calls)) == 0) {
    if (stmt.return_value >= 0) {
    int64_t ret_excl_pos = Codegen_str_find(self, self->cur_return_type, ((char)(33)));
    if (ret_excl_pos >= 0) {
    const char* result_ctype = Codegen_map_type(self, self->cur_return_type);
    const char* val_payload_type = substring(self->cur_return_type, 0, ret_excl_pos);
    const char* err_type = substring(self->cur_return_type, (ret_excl_pos + 1), strlen(self->cur_return_type));
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
    int64_t expr_excl_pos = Codegen_str_find(self, expr_ty, ((char)(33)));
    if (expr_excl_pos >= 0) {
    return /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "return ";
  const char* const _tmp_r = val_str;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ";";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    if (is_error_variant) {
    return /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "return (";
  const char* const _tmp_r = result_ctype;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "){ .tag = ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = val_str;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = " };";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    if (strcmp(val_payload_type, "Void") == 0) {
    return /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "return (";
  const char* const _tmp_r = result_ctype;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "){ .tag = 0 };";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    return /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "return (";
  const char* const _tmp_r = result_ctype;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "){ .tag = 0, .value = ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = val_str;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = " };";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    return /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "return ";
  const char* const _tmp_r = Codegen_gen_expr(self, stmt.return_value);
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ";";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    return "return;";
}
    if (stmt.return_value >= 0) {
    const char* val_str = Codegen_gen_expr(self, stmt.return_value);
    const char* val_type = Codegen_get_expr_type(self, stmt.return_value);
    if ((strcmp(val_type, "Void") == 0) || (strcmp(val_type, "NoneType") == 0)) {
    const char* res = /* Str concat */ ({
  const char* const _tmp_l = val_str;
  const char* const _tmp_r = "; ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    int64_t ci = 0;
    while (ci < ArrayList_Str_length(&(drop_calls))) {
    res = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = res;
  const char* const _tmp_r = ArrayList_Str_get(&(drop_calls), ci);
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = " ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    ci = (ci + 1);
}
    return /* Str concat */ ({
  const char* const _tmp_l = res;
  const char* const _tmp_r = "return;";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    const char* mapped_type = Codegen_map_type(self, val_type);
    const char* res_str = "{\n";
    res_str = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = res_str;
  const char* const _tmp_r = "    ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = mapped_type;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = " __ret_val = ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = val_str;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ";\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    int64_t ci = 0;
    while (ci < ArrayList_Str_length(&(drop_calls))) {
    res_str = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = res_str;
  const char* const _tmp_r = "    ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ArrayList_Str_get(&(drop_calls), ci);
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    ci = (ci + 1);
}
    res_str = /* Str concat */ ({
  const char* const _tmp_l = res_str;
  const char* const _tmp_r = "    return __ret_val;\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    res_str = /* Str concat */ ({
  const char* const _tmp_l = res_str;
  const char* const _tmp_r = "}";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    return res_str;
} else {
    const char* res_str = "{\n";
    int64_t ci = 0;
    while (ci < ArrayList_Str_length(&(drop_calls))) {
    res_str = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = res_str;
  const char* const _tmp_r = "    ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ArrayList_Str_get(&(drop_calls), ci);
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    ci = (ci + 1);
}
    res_str = /* Str concat */ ({
  const char* const _tmp_l = res_str;
  const char* const _tmp_r = "    return;\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    res_str = /* Str concat */ ({
  const char* const _tmp_l = res_str;
  const char* const _tmp_r = "}";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    return res_str;
}
}
    if (stmt.kind == StmtKind_sk_expr) {
    return /* Str concat */ ({
  const char* const _tmp_l = Codegen_gen_expr(self, stmt.expr_stmt);
  const char* const _tmp_r = ";";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
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
    int64_t i = 0;
    while (i < ArrayList_Param_length(&(stmt.extern_params))) {
    Param p = ArrayList_Param_get(&(stmt.extern_params), i);
    if (i > 0) {
    params_str = /* Str concat */ ({
  const char* const _tmp_l = params_str;
  const char* const _tmp_r = ", ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    params_str = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = params_str;
  const char* const _tmp_r = Codegen_map_type(self, p.ptype);
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = " ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = p.name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    i = (i + 1);
}
    if (strlen(params_str) == 0) {
    params_str = "void";
}
    const char* proto = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "extern ";
  const char* const _tmp_r = ret_type;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = " ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "(";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = params_str;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ");\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    (void)(StringBuilder_append(&(self->func_decls), proto));
    return "";
}
    if (stmt.kind == StmtKind_sk_cimport) {
    const char* hdr = stmt.cimport_header;
    if (strlist_find(&(self->cimport_headers), hdr) < 0) {
    ArrayList_Str_push(&(self->cimport_headers), hdr);
}
    return "";
}
    if (stmt.kind == StmtKind_sk_import) {
    ArrayList_Str path = stmt.import_path;
    const char* module_key = "";
    int64_t pi = 0;
    while (pi < ArrayList_Str_length(&(path))) {
    if (pi > 0) {
    module_key = /* Str concat */ ({
  const char* const _tmp_l = module_key;
  const char* const _tmp_r = ".";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    module_key = /* Str concat */ ({
  const char* const _tmp_l = module_key;
  const char* const _tmp_r = ArrayList_Str_get(&(path), pi);
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    pi = (pi + 1);
}
    if (strcmp(module_key, "") == 0) {
    return "";
}
    if (strlist_find(&(self->loaded_modules), module_key) >= 0) {
    return "";
}
    ArrayList_Str_push(&(self->loaded_modules), module_key);
    const char* file_path = "";
    if ((ArrayList_Str_length(&(path)) > 0) && (strcmp(ArrayList_Str_get(&(path), 0), "std") == 0)) {
    const char* path_str = "";
    int64_t i = 0;
    while (i < ArrayList_Str_length(&(path))) {
    if (i > 0) {
    path_str = /* Str concat */ ({
  const char* const _tmp_l = path_str;
  const char* const _tmp_r = "/";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    path_str = /* Str concat */ ({
  const char* const _tmp_l = path_str;
  const char* const _tmp_r = ArrayList_Str_get(&(path), i);
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    i = (i + 1);
}
    file_path = /* Str concat */ ({
  const char* const _tmp_l = path_str;
  const char* const _tmp_r = ".kai";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
} else if (ArrayList_Str_length(&(path)) > 0) {
    file_path = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "src/";
  const char* const _tmp_r = module_key;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ".kai";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    if (strcmp(file_path, "") != 0) {
    Result_Str_Int source_res = read_to_string(self->allocator, file_path);
    if (source_res.tag == Result_Str_Int_ok_TAG) {
    const char* source = source_res.payload.ok.value;

    Lexer lexer = Lexer_init(self->allocator, source);
    Lexer_lex(&(lexer));
    if (lexer.has_error) {
    return "";
}
    Parser parser = Parser_init_with_pools(self->allocator, lexer.tokens, self->expr_pool, self->stmt_pool, self->pattern_pool);
    int64_t program_idx = Parser_parse_program(&(parser));
    if (program_idx >= 0) {
    Codegen_build_func_types(self);
    (void)(Codegen_gen_stmt(self, program_idx));
}
} else if (source_res.tag == Result_Str_Int_err_TAG) {
    int64_t err_code = source_res.payload.err.value;

    return "";
} 
}
    return "";
}
    if (stmt.kind == StmtKind_sk_break) {
    ArrayList_Str drop_calls = Codegen__collect_loop_drops(self);
    if (ArrayList_Str_length(&(drop_calls)) == 0) {
    return "break;";
}
    const char* res_str = "{\n";
    int64_t ci = 0;
    while (ci < ArrayList_Str_length(&(drop_calls))) {
    res_str = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = res_str;
  const char* const _tmp_r = "    ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ArrayList_Str_get(&(drop_calls), ci);
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    ci = (ci + 1);
}
    res_str = /* Str concat */ ({
  const char* const _tmp_l = res_str;
  const char* const _tmp_r = "    break;\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    res_str = /* Str concat */ ({
  const char* const _tmp_l = res_str;
  const char* const _tmp_r = "}";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    return res_str;
}
    if (stmt.kind == StmtKind_sk_continue) {
    ArrayList_Str drop_calls = Codegen__collect_loop_drops(self);
    if (ArrayList_Str_length(&(drop_calls)) == 0) {
    return "continue;";
}
    const char* res_str = "{\n";
    int64_t ci = 0;
    while (ci < ArrayList_Str_length(&(drop_calls))) {
    res_str = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = res_str;
  const char* const _tmp_r = "    ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ArrayList_Str_get(&(drop_calls), ci);
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    ci = (ci + 1);
}
    res_str = /* Str concat */ ({
  const char* const _tmp_l = res_str;
  const char* const _tmp_r = "    continue;\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    res_str = /* Str concat */ ({
  const char* const _tmp_l = res_str;
  const char* const _tmp_r = "}";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
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
    if ((((expr_type)[0] == ((char)(42))) || ((expr_type)[0] == ((char)(38)))) || is_self_ptr) {
    is_ptr = true;
}
    const char* op = ".";
    if (is_ptr) {
    op = "->";
}
    const char* match_str = "";
    int64_t case_idx = 0;
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
    const char* v = pat_node.lit_value.payload.tv_str.v;

    lit_str = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "\"";
  const char* const _tmp_r = Codegen_escape_string(self, v);
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "\"";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
} else if (pat_node.lit_value.tag == TokenValue_tv_bool_TAG) {
    bool v = pat_node.lit_value.payload.tv_bool.v;

    if (v) {
    lit_str = "true";
} else {
    lit_str = "false";
}
} else if (pat_node.lit_value.tag == TokenValue_tv_char_TAG) {
    char v = pat_node.lit_value.payload.tv_char.v;

    if (v == ((char)(10))) {
    lit_str = "'\\n'";
} else if (v == ((char)(13))) {
    lit_str = "'\\r'";
} else if (v == ((char)(9))) {
    lit_str = "'\\t'";
} else if (v == ((char)(92))) {
    lit_str = "'\\\\'";
} else if (v == ((char)(39))) {
    lit_str = "'\\''";
} else {
    lit_str = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "'";
  const char* const _tmp_r = char_to_str(v);
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "'";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
} else {
    lit_str = "0";
} 
    cond = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = expr_val;
  const char* const _tmp_r = " == ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = lit_str;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
} else if (pat_node.kind == PatternKind_pk_variant) {
    const char* var_name = pat_node.variant_name;
    const char* base_type = mapped_expr_type;
    if ((strlen(base_type) > 0) && (((base_type)[(strlen(base_type) - 1)] == ((char)(42))) || ((base_type)[(strlen(base_type) - 1)] == ((char)(38))))) {
    base_type = substring(base_type, 0, (strlen(base_type) - 1));
}
    if ((strlen(base_type) > 0) && ((base_type)[0] == ((char)(42)))) {
    base_type = substring(base_type, 1, strlen(base_type));
}
    if (Codegen_enum_has_payload(self, expr_type)) {
    cond = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = expr_val;
  const char* const _tmp_r = op;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "tag == ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = base_type;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "_";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = var_name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "_TAG";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
} else {
    cond = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = expr_val;
  const char* const _tmp_r = " == ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = base_type;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "_";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = var_name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    if (ArrayList_Str_length(&(pat_node.bindings)) > 0) {
    const char* bind_name = ArrayList_Str_get(&(pat_node.bindings), 0);
    if (strcmp(bind_name, "_") != 0) {
    const char* bind_type = "";
    const char* field_name = "";
    if (strcmp(var_name, "ok") == 0) {
    const char* t_type = type_map_get(&(self->current_type_map), "T");
    if (strlen(t_type) == 0) {
    t_type = Codegen_extract_first_type_arg(self, expr_type);
}
    bind_type = t_type;
    field_name = "value";
} else if (strcmp(var_name, "err") == 0) {
    const char* e_type = type_map_get(&(self->current_type_map), "E");
    if (strlen(e_type) == 0) {
    e_type = "Int";
}
    bind_type = e_type;
    field_name = "value";
} else if (strcmp(var_name, "tv_int") == 0) {
    bind_type = "Int";
    field_name = "v";
} else if (strcmp(var_name, "tv_float") == 0) {
    bind_type = "Float";
    field_name = "v";
} else if (strcmp(var_name, "tv_bool") == 0) {
    bind_type = "Bool";
    field_name = "v";
} else if (strcmp(var_name, "tv_char") == 0) {
    bind_type = "Char";
    field_name = "v";
} else if (strcmp(var_name, "tv_str") == 0) {
    bind_type = "Str";
    field_name = "v";
}
    const char* mapped_bind_type = Codegen_map_type(self, bind_type);
    bindings_str = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "    ";
  const char* const _tmp_r = mapped_bind_type;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = " ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = bind_name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = " = ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = expr_val;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = op;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "payload.";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = var_name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ".";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = field_name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ";\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
}
} else if (pat_node.kind == PatternKind_pk_else) {
    cond = "true";
}
    const char* prefix = "";
    if (case_idx == 0) {
    prefix = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "if (";
  const char* const _tmp_r = cond;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ")";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
} else if (strcmp(cond, "true") == 0) {
    prefix = "else";
} else {
    prefix = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "else if (";
  const char* const _tmp_r = cond;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ")";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    const char* full_block = block_str;
    if (strlen(bindings_str) > 0) {
    int64_t body_len = strlen(block_str);
    full_block = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "{\n";
  const char* const _tmp_r = bindings_str;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = substring(block_str, 1, body_len);
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    match_str = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = match_str;
  const char* const _tmp_r = prefix;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = " ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = full_block;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = " ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    case_idx = (case_idx + 1);
}
    return match_str;
}
    return "";
}
const char* Codegen_clean_enum_name(Codegen* self, const char* type_name) {
    const char* base_name = type_name;
    if (Codegen_str_contains(self, type_name, ((char)(60)))) {
    int64_t lt_pos = Codegen_str_find(self, type_name, ((char)(60)));
    base_name = substring(type_name, 0, lt_pos);
}
    if (strcmp(substring(base_name, 0, 4), "mut ") == 0) {
    base_name = substring(base_name, 4, strlen(base_name));
}
    bool done = false;
    while (!done) {
    if ((strlen(base_name) > 0) && (((base_name)[0] == ((char)(42))) || ((base_name)[0] == ((char)(38))))) {
    base_name = substring(base_name, 1, strlen(base_name));
} else {
    done = true;
}
}
    done = false;
    while (!done) {
    int64_t l = strlen(base_name);
    if ((l > 0) && (((base_name)[(l - 1)] == ((char)(42))) || ((base_name)[(l - 1)] == ((char)(38))))) {
    base_name = substring(base_name, 0, (l - 1));
} else {
    done = true;
}
}
    if (strlen(type_map_get(&(self->enum_decls), base_name)) == 0) {
    if (Codegen_str_contains(self, base_name, ((char)(95)))) {
    int64_t underscore_pos = Codegen_str_find(self, base_name, ((char)(95)));
    const char* fallback_name = substring(base_name, 0, underscore_pos);
    if (strlen(type_map_get(&(self->enum_decls), fallback_name)) > 0) {
    return fallback_name;
}
}
}
    return base_name;
}
bool Codegen_is_enum_type(Codegen* self, const char* type_name) {
    const char* clean_name = Codegen_clean_enum_name(self, type_name);
    return (strlen(type_map_get(&(self->enum_decls), clean_name)) > 0);
}
bool Codegen_enum_has_payload(Codegen* self, const char* enum_name) {
    const char* clean_name = Codegen_clean_enum_name(self, enum_name);
    const char* idx_str = type_map_get(&(self->enum_decls), clean_name);
    if (strlen(idx_str) == 0) {
    return false;
}
    StmtNode enum_stmt = ArrayList_StmtNode_get(self->stmt_pool, Codegen_str_to_int(self, idx_str));
    if (enum_stmt.kind == StmtKind_sk_error_decl) {
    return false;
}
    bool has_payload = false;
    int64_t vi = 0;
    while (vi < ArrayList_Variant_length(&(enum_stmt.enum_variants))) {
    Variant v = ArrayList_Variant_get(&(enum_stmt.enum_variants), vi);
    if (ArrayList_Param_length(&(v.params)) > 0) {
    has_payload = true;
}
    vi = (vi + 1);
}
    return has_payload;
}
const char* Codegen_escape_string(Codegen* self, const char* s) {
    const char* res = "";
    int64_t i = 0;
    while (i < strlen(s)) {
    char c = (s)[i];
    if (c == ((char)(10))) {
    res = /* Str concat */ ({
  const char* const _tmp_l = res;
  const char* const _tmp_r = "\\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
} else if (c == ((char)(13))) {
    res = /* Str concat */ ({
  const char* const _tmp_l = res;
  const char* const _tmp_r = "\\r";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
} else if (c == ((char)(9))) {
    res = /* Str concat */ ({
  const char* const _tmp_l = res;
  const char* const _tmp_r = "\\t";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
} else if (c == ((char)(92))) {
    res = /* Str concat */ ({
  const char* const _tmp_l = res;
  const char* const _tmp_r = "\\\\";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
} else if (c == ((char)(34))) {
    res = /* Str concat */ ({
  const char* const _tmp_l = res;
  const char* const _tmp_r = "\\\"";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
} else {
    res = /* Str concat */ ({
  const char* const _tmp_l = res;
  const char* const _tmp_r = char_to_str(c);
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
    i = (i + 1);
}
    return res;
}
ArrayList_Str Codegen__collect_loop_drops(Codegen* self) {
    ArrayList_Str drop_calls = ArrayList_Str_init(self->allocator);
    int64_t bi = (ArrayList_Int_length(&(self->block_stack)) - 1);
    bool done = false;
    while ((bi >= 0) && (!done)) {
    int64_t b_idx = ArrayList_Int_get(&(self->block_stack), bi);
    StmtNode b_node = ArrayList_StmtNode_get(self->stmt_pool, b_idx);
    int64_t di = 0;
    while (di < ArrayList_DropVarEntry_length(&(b_node.block_drop_vars))) {
    DropVarEntry entry = ArrayList_DropVarEntry_get(&(b_node.block_drop_vars), di);
    ArrayList_Str_push(&(drop_calls), /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = entry.base_type;
  const char* const _tmp_r = "_drop(&";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = entry.name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ");";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
}));
    di = (di + 1);
}
    if (b_node.block_is_loop_body) {
    done = true;
}
    bi = (bi - 1);
}
    return drop_calls;
}
const char* Codegen_generate(Codegen* self, int64_t top_stmt_idx) {
    Codegen_build_func_types(self);
    const char* body = Codegen_gen_stmt(self, top_stmt_idx);
    const char* final_code = "";
    final_code = /* Str concat */ ({
  const char* const _tmp_l = final_code;
  const char* const _tmp_r = "#include <stdint.h>\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    final_code = /* Str concat */ ({
  const char* const _tmp_l = final_code;
  const char* const _tmp_r = "#include <stdbool.h>\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    final_code = /* Str concat */ ({
  const char* const _tmp_l = final_code;
  const char* const _tmp_r = "#include <stdio.h>\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    final_code = /* Str concat */ ({
  const char* const _tmp_l = final_code;
  const char* const _tmp_r = "#include <stdlib.h>\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    final_code = /* Str concat */ ({
  const char* const _tmp_l = final_code;
  const char* const _tmp_r = "#include <string.h>\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    final_code = /* Str concat */ ({
  const char* const _tmp_l = final_code;
  const char* const _tmp_r = "#include <sys/mman.h>\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    final_code = /* Str concat */ ({
  const char* const _tmp_l = final_code;
  const char* const _tmp_r = "#include <ctype.h>\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    int64_t ci = 0;
    bool has_cimports = false;
    while (ci < ArrayList_Str_length(&(self->cimport_headers))) {
    const char* hdr = ArrayList_Str_get(&(self->cimport_headers), ci);
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
    final_code = /* Str concat */ ({
  const char* const _tmp_l = final_code;
  const char* const _tmp_r = "/* C FFI Imports */\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    has_cimports = true;
}
    bool has_slash = false;
    bool dot_start = false;
    if (strlen(hdr) > 0) {
    int64_t hi = 0;
    while (hi < strlen(hdr)) {
    if ((hdr)[hi] == ((char)(47))) {
    has_slash = true;
}
    hi = (hi + 1);
}
    if ((hdr)[0] == ((char)(46))) {
    dot_start = true;
}
}
    if ((!has_slash) && (!dot_start)) {
    final_code = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = final_code;
  const char* const _tmp_r = "#include <";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = hdr;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = ">\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
} else {
    final_code = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = final_code;
  const char* const _tmp_r = "#include \"";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = hdr;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "\"\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
}
}
    ci = (ci + 1);
}
    final_code = /* Str concat */ ({
  const char* const _tmp_l = final_code;
  const char* const _tmp_r = "\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    final_code = /* Str concat */ ({
  const char* const _tmp_l = final_code;
  const char* const _tmp_r = "static inline void print_int(int64_t i) { printf(\"%lld\\n\", (long long)i); }\n\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    final_code = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = final_code;
  const char* const _tmp_r = StringBuilder_to_str(&(self->struct_decls));
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    final_code = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = final_code;
  const char* const _tmp_r = StringBuilder_to_str(&(self->func_decls));
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = "\n";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    final_code = /* Str concat */ ({
  const char* const _tmp_l = final_code;
  const char* const _tmp_r = StringBuilder_to_str(&(self->output));
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    return final_code;
}
const char* get_base_name(KaiAllocator* allocator, const char* path) {
    int64_t last_slash = (-1);
    int64_t dot_pos = (-1);
    int64_t i = 0;
    int64_t l = strlen(path);
    while (i < l) {
    char c = (path)[i];
    if (c == ((char)(47))) {
    last_slash = i;
} else if (c == ((char)(46))) {
    dot_pos = i;
}
    i = (i + 1);
}
    int64_t start = 0;
    if (last_slash >= 0) {
    start = (last_slash + 1);
}
    int64_t end = l;
    if (dot_pos > last_slash) {
    end = dot_pos;
}
    return substring(path, start, end);
}
int main(int argc, char** argv) {
    if (argc < 2) {
    printf("%s\n", "Usage: compiler <input.kai> [-o <output_bin>] [-c]");
    return 1;
}
    const char* input_file = "";
    const char* output_bin = "";
    bool emit_c_only = false;
    int64_t i = 1;
    while (i < argc) {
    const char* arg = (const char*)((argv)[i]);
    bool is_c = false;
    bool is_o = false;
    {
    if (strcmp(arg, "-c") == 0) {
    is_c = true;
} else if (strcmp(arg, "-o") == 0) {
    is_o = true;
}
}
    if (is_c) {
    emit_c_only = true;
} else if (is_o) {
    if ((i + 1) < argc) {
    i = (i + 1);
    output_bin = (const char*)((argv)[i]);
} else {
    printf("%s\n", "Error: -o requires an argument");
    return 1;
}
} else {
    input_file = arg;
}
    i = (i + 1);
}
    if (strlen(input_file) == 0) {
    printf("%s\n", "Error: No input file specified");
    return 1;
}
    KaiAllocator allocator = (KaiAllocator){ .heads = (char*)(0), .used = 0 };
    allocator = KaiAllocator_init();
    const char* base = get_base_name(&(allocator), input_file);
    const char* bin_name = base;
    if (strlen(output_bin) > 0) {
    bin_name = output_bin;
}
    const char* c_file = /* Str concat */ ({
  const char* const _tmp_l = base;
  const char* const _tmp_r = ".c";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    Result_Str_Int source_res = read_to_string(&(allocator), input_file);
    if (source_res.tag == Result_Str_Int_ok_TAG) {
    const char* source = source_res.payload.ok.value;

    Lexer lexer = Lexer_init(&(allocator), source);
    Lexer_lex(&(lexer));
    if (lexer.has_error) {
    return 2;
}
    Parser parser = Parser_init(&(allocator), lexer.tokens);
    int64_t program_idx = Parser_parse_program(&(parser));
    if (program_idx < 0) {
    return 3;
}
    TypeChecker checker = TypeChecker_init(&(allocator), parser.stmt_pool, parser.expr_pool, parser.pattern_pool);
    bool success = TypeChecker_check_program(&(checker), program_idx);
    if (!success) {
    return 4;
}
    Codegen gen = Codegen_init(&(allocator), parser.stmt_pool, parser.expr_pool, parser.pattern_pool);
    const char* output = Codegen_generate(&(gen), program_idx);
    Result_Bool_Int write_res = write_string(c_file, output);
    if (write_res.tag == Result_Bool_Int_ok_TAG) {
    if (emit_c_only) {
    return 0;
}
    const char* cmd = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = /* Str concat */ ({
  const char* const _tmp_l = "clang -O1 ";
  const char* const _tmp_r = c_file;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = " -o ";
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
  const char* const _tmp_r = bin_name;
  size_t l1 = strlen(_tmp_l);
  size_t l2 = strlen(_tmp_r);
  char* buf = malloc(l1 + l2 + 1);
  strcpy(buf, _tmp_l);
  strcat(buf, _tmp_r);
  buf;
});
    {
    return system((char*)(cmd));
}
} else if (write_res.tag == Result_Bool_Int_err_TAG) {
    return 5;
} 
} else if (source_res.tag == Result_Str_Int_err_TAG) {
    int64_t err_code = source_res.payload.err.value;

    return 4;
} 
    return 0;
}