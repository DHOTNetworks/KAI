#ifndef KAI_LLVM_CORE_H
#define KAI_LLVM_CORE_H

#include <llvm-c/Core.h>
#include <llvm-c/Target.h>
#include <llvm-c/TargetMachine.h>
#include <llvm-c/Analysis.h>
#include <llvm-c/BitWriter.h>
#include <stdint.h>
#include <stdbool.h>

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

// --- Compatibility wrapper for renamed ABI alignment function ---
static inline unsigned LLVMGetABITypeAlignment(LLVMTargetDataRef TD, LLVMTypeRef Ty) {
    return LLVMABIAlignmentOfType(TD, Ty);
}

#endif
