#ifndef KAI_LLVM_CORE_H
#define KAI_LLVM_CORE_H

#include "../core/platform.h"

#include <llvm-c/Core.h>
#include <llvm-c/Target.h>
#include <llvm-c/TargetMachine.h>
#include <llvm-c/Analysis.h>
#include <llvm-c/BitWriter.h>

// --- Target Initialization wrappers (avoid link issues with inline macros) ---

static inline void kai_LLVMInitializeAllTargetInfos(void) {
    LLVMInitializeAllTargetInfos();
}

static inline void kai_LLVMInitializeAllTargets(void) {
    LLVMInitializeAllTargets();
}

static inline void kai_LLVMInitializeAllTargetMCs(void) {
    LLVMInitializeAllTargetMCs();
}

static inline void kai_LLVMInitializeAllAsmPrinters(void) {
    LLVMInitializeAllAsmPrinters();
}

static inline void kai_LLVMInitializeAllAsmParsers(void) {
    LLVMInitializeAllAsmParsers();
}

static inline int64_t kai_LLVMInitializeNativeTarget(void) {
    return (int64_t)LLVMInitializeNativeTarget();
}

static inline int64_t kai_LLVMInitializeNativeAsmPrinter(void) {
    return (int64_t)LLVMInitializeNativeAsmPrinter();
}

static inline int64_t kai_LLVMInitializeNativeAsmParser(void) {
    return (int64_t)LLVMInitializeNativeAsmParser();
}

static inline void* kai_LLVMContextCreate(void) {
    return (void*)LLVMContextCreate();
}

static inline void kai_LLVMContextDispose(void* ctx) {
    LLVMContextDispose((LLVMContextRef)ctx);
}

static inline void* kai_LLVMModuleCreateWithNameInContext(const char* name, void* ctx) {
    return (void*)LLVMModuleCreateWithNameInContext(name, (LLVMContextRef)ctx);
}

static inline void kai_LLVMDisposeModule(void* m) {
    LLVMDisposeModule((LLVMModuleRef)m);
}

static inline char* kai_LLVMPrintModuleToString(void* m) {
    return LLVMPrintModuleToString((LLVMModuleRef)m);
}

static inline int64_t kai_LLVMWriteBitcodeToFile(void* m, const char* path) {
    return (int64_t)LLVMWriteBitcodeToFile((LLVMModuleRef)m, path);
}

// ---------------------------------------------------------------------------
// Convenience wrappers for call/type construction (avoid C-array-in-Kai issue)
// ---------------------------------------------------------------------------

static inline void* kai_func_type_0(void* ret) {
    return (void*)LLVMFunctionType((LLVMTypeRef)ret, NULL, 0, 0);
}
static inline void* kai_func_type_1(void* ret, void* p0, int is_vararg) {
    LLVMTypeRef params[1] = {(LLVMTypeRef)p0};
    return (void*)LLVMFunctionType((LLVMTypeRef)ret, params, 1, is_vararg);
}
static inline void* kai_func_type_2(void* ret, void* p0, void* p1, int is_vararg) {
    LLVMTypeRef params[2] = {(LLVMTypeRef)p0, (LLVMTypeRef)p1};
    return (void*)LLVMFunctionType((LLVMTypeRef)ret, params, 2, is_vararg);
}

static inline void* kai_build_call_1(void* b, void* fn_ty, void* fn_val, void* arg0, const char* name) {
    LLVMValueRef args[1] = {(LLVMValueRef)arg0};
    return (void*)LLVMBuildCall2((LLVMBuilderRef)b, (LLVMTypeRef)fn_ty, (LLVMValueRef)fn_val, args, 1, name);
}
static inline void* kai_build_call_2(void* b, void* fn_ty, void* fn_val, void* arg0, void* arg1, const char* name) {
    LLVMValueRef args[2] = {(LLVMValueRef)arg0, (LLVMValueRef)arg1};
    return (void*)LLVMBuildCall2((LLVMBuilderRef)b, (LLVMTypeRef)fn_ty, (LLVMValueRef)fn_val, args, 2, name);
}
static inline void* kai_build_call_3(void* b, void* fn_ty, void* fn_val, void* arg0, void* arg1, void* arg2, const char* name) {
    LLVMValueRef args[3] = {(LLVMValueRef)arg0, (LLVMValueRef)arg1, (LLVMValueRef)arg2};
    return (void*)LLVMBuildCall2((LLVMBuilderRef)b, (LLVMTypeRef)fn_ty, (LLVMValueRef)fn_val, args, 3, name);
}
static inline void* kai_build_call_4(void* b, void* fn_ty, void* fn_val, void* arg0, void* arg1, void* arg2, void* arg3, const char* name) {
    LLVMValueRef args[4] = {(LLVMValueRef)arg0, (LLVMValueRef)arg1, (LLVMValueRef)arg2, (LLVMValueRef)arg3};
    return (void*)LLVMBuildCall2((LLVMBuilderRef)b, (LLVMTypeRef)fn_ty, (LLVMValueRef)fn_val, args, 4, name);
}

// Inline assembly
static inline void* kai_LLVMGetInlineAsm(void* ft, const char* asm_str, int64_t asm_len, const char* constraints, int64_t constraints_len, int has_side_effects, int is_align_stack, int dialect, int can_throw) {
    return (void*)LLVMGetInlineAsm((LLVMTypeRef)ft, asm_str, (size_t)asm_len, constraints, (size_t)constraints_len, (LLVMBool)has_side_effects, (LLVMBool)is_align_stack, (LLVMInlineAsmDialect)dialect, (LLVMBool)can_throw);
}

// Aggregate value construction (safe int64_t→unsigned wrappers)
static inline void* kai_LLVMConstNamedStruct(void* struct_ty, void* constant_vals, int64_t count) {
    return (void*)LLVMConstNamedStruct((LLVMTypeRef)struct_ty, (LLVMValueRef*)constant_vals, (unsigned)count);
}
static inline void* kai_LLVMBuildExtractValue(void* b, void* agg_val, int64_t index, const char* name) {
    return (void*)LLVMBuildExtractValue((LLVMBuilderRef)b, (LLVMValueRef)agg_val, (unsigned)index, name);
}
static inline void* kai_LLVMBuildInsertValue(void* b, void* agg_val, void* elt_val, int64_t index, const char* name) {
    return (void*)LLVMBuildInsertValue((LLVMBuilderRef)b, (LLVMValueRef)agg_val, (LLVMValueRef)elt_val, (unsigned)index, name);
}

#endif // KAI_LLVM_CORE_H
