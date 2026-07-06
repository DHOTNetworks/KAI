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

#endif
