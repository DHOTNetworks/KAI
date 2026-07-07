# Kai Compiler (Self-Hosted Version)

Welcome to the clean, self-hosted version of the **Kai** systems programming language compiler! 

<div align="center">

[![Zig](https://img.shields.io/badge/Zig-0.15.2-F7A41D?style=flat-square&logo=zig&logoColor=white)](https://ziglang.org/)
![KAI](https://img.shields.io/badge/KAI-black?style=for-the-badge&logo=data:image/svg%2bxml;base64,PHN2ZyB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHZpZXdCb3g9IjAgMCAxMTAgMTAwIj4KICA8ZGVmcz4KICAgIDwhLS0gQSB2aWJyYW50LCBoaWdoLWVuZXJneSBncmFkaWVudCBpbnNwaXJlZCBieSBaaWcncyBzdHJpa2luZyBjb2xvciBwcm9maWxlIC0tPgogICAgPGxpbmVhckdyYWRpZW50IGlkPSJ6aWdTdHlsZUdyYWQiIHgxPSIwJSIgeTE9IjAlIiB4Mj0iMTAwJSIgeTI9IjEwMCUiPgogICAgICA8c3RvcCBvZmZzZXQ9IjAlIiBzdG9wLWNvbG9yPSIjRkY3QTAwIiAvPgogICAgICA8c3RvcCBvZmZzZXQ9IjEwMCUiIHN0b3AtY29sb3I9IiNGRkIzMDAiIC8+CiAgICA8L2xpbmVhckdyYWRpZW50PgogIDwvZGVmcz4KCiAgPCEtLSBMZWZ0IFN0ZW06IEEgdGhpY2ssIGphZ2dlZCBwaWxsYXIgbGVhbmluZyBmb3J3YXJkLCB3aXRoIGFuIGlubmVyIHN0ZXAgY3V0IG91dCAtLT4KICA8cGF0aCBkPSJNIDMyIDEwIEwgNjIgMTAgTCA1MiA0NSBMIDQyIDQ1IEwgMzIgOTAgTCAyIDkwIFoiIGZpbGw9InVybCgjemlnU3R5bGVHcmFkKSIgLz4KICAKICA8IS0tIFVwcGVyIFJpZ2h0IEFybTogQSBzaGFycCBzaGFyZCBwZXJmZWN0bHkgc2xvdHRlZCBhYm92ZSB0aGUgc3RlbSdzIHN0ZXAgLS0+CiAgPHBhdGggZD0iTSA2NiAxMCBMIDEwNyAxMCBMIDc2IDQxIEwgNTcgNDEgWiIgZmlsbD0idXJsKCN6aWdTdHlsZUdyYWQpIiAvPgogIAogIDwhLS0gTG93ZXIgUmlnaHQgQXJtOiBBIHdpZGUsIGdyb3VuZGluZyBzaGFyZCBzbG90dGVkIGJlbG93IHRoZSBzdGVwIC0tPgogIDxwYXRoIGQ9Ik0gNDUgNDkgTCA2NSA0OSBMIDg3IDkwIEwgMzYgOTAgWiIgZmlsbD0idXJsKCN6aWdTdHlsZUdyYWQpIiAvPgo8L3N2Zz4K)
[![C](https://img.shields.io/badge/C-00599C?logo=c&logoColor=white)](#)
[![Open Source](https://img.shields.io/badge/Open%20Source-Yes-brightgreen?style=flat-square)](#)

</div>

---

This repository has been fully transitioned from the original Python bootstrap compiler. All compiler development, standard library modules, and feature enhancements are now written entirely in Kai and compiled by Kai itself.

---

## 1. Project Structure

- **`src/`**: The self-hosted compiler source code:
  - [`compiler.kai`](file:///Users/karan/kai-c/src/compiler.kai): Main compiler driver and command-line entrypoint.
  - [`lexer.kai`](file:///Users/karan/kai-c/src/lexer.kai): Lexical analyzer converting source code to tokens.
  - [`parser.kai`](file:///Users/karan/kai-c/src/parser.kai): Parser converting tokens to AST nodes. Supports parsing traits, generics, error unions, block curly braces, and inline assembly.
  - [`type_checker.kai`](file:///Users/karan/kai-c/src/type_checker.kai): Resolves types, tracks mutability/move semantics, and validates symbol scopes.
  - [`codegen.kai`](file:///Users/karan/kai-c/src/codegen.kai): Transpiles the AST to highly portable C code.
  - [`ast_nodes.kai`](file:///Users/karan/kai-c/src/ast_nodes.kai) & [`token_defs.kai`](file:///Users/karan/kai-c/src/token_defs.kai): AST node structure and token type definitions.
  - [`symbol_table.kai`](file:///Users/karan/kai-c/src/symbol_table.kai): Manages scopes and variable descriptors.
- **`std/`**: The standard library:
  - `std/core/allocator.kai`: Allocators and memory management.
  - `std/collections/`: Core collections (`ArrayList`, `HashMap`, `StringBuilder`).
  - `std/io/`: Basic I/O and file handling.
- **`compiler_bootstrap.c`**: The verified C transpilation output of the compiler, used as the zero-dependency bootstrapper.

---

## 2. Current Implementation Status

### A. Unified Pointer System (Option A)
- **Types**: We only have `*T` (const/immutable pointer) and `*mut T` (mutable pointer). Legacy references (`&T` / `&mut T`) are mapped to pointers in the parser.
- **Address-Of**: `&x` automatically infers pointer mutability (`*mut T` if the target is a `var`, `*T` if the target is a `let`).
- **Dereference**: `*ptr` is safe by default and does not require an `unsafe` block.
- **Type Checking**: Strict type checking prevents assigning `*T` to `*mut T` (const correctness).

### B. Transpiler Feature Alignment
The self-hosted compiler supports all core language features 1:1 with the Python reference backend, including:
- Struct/Enum factory constructors (e.g., `ArrayList<Int>(&allocator)`).
- Semicolons and curly brace delimiters.
- C-style `sizeof(Type)` parsing and codegen.
- Slices, ranges, array literals, and tuple initialization expressions.
- GCC Inline Assembly (`asm`) blocks with volatile prefixes, inputs, outputs, and clobbers.

---

## 3. How to Bootstrap & Compile

To build the compiler from scratch without any pre-existing binaries or Python dependencies:

### Step 1: Build the Bootstrap Compiler
Compile the C bootstrap file directly using `clang` or `gcc`:
```bash
clang -O3 compiler_bootstrap.c -o ./kai_bootstrap
```

### Step 2: Recompile the Compiler from Source (Self-Hosting)
Compile the Kai source files using the bootstrapped compiler binary:
```bash
./kai_bootstrap src/compiler.kai -o ./kai
```

### Step 3: Verify the Compiler (Stage 2)
Verify that the new compiler binary is functional by compiling a target program or recompiling itself:
```bash
./kai src/compiler.kai -o ./kai_self_compiled
```
## Cross Compilation via Zig

### 1. Translate C output to Zig, skipping the inline C get_exe_dir implementation
```
zig translate-c -DNO_GET_EXE_DIR compiler.c > compiler.zig
```

### 2. Append the Windows compatibility imports
```
echo 'comptime { _ = @import("windows_compat.zig"); }' >> compiler.zig
```

### 3. Cross-compile
```
zig build-exe compiler.zig -target aarch64-windows-gnu -lc -femit-bin=compiler

zig build-exe compiler.zig -target x86_64-windows-gnu -lc -femit-bin=compiler

```

---

## 4. Next Action Plans / Roadmap

For the next agent working on this codebase, the priorities are:
1. **Error Unions implementation (Phase 3)**:
   [DONE]- Implement status-integer error unions (`T!E`), restoring the `try` / `catch` propagation check logic natively inside the self-hosted type checker and C code generator.
2. **Standard Library Expansion**:
   [DONE]- Add native networking, threading wrappers, and standard formatting routines directly into the `std/` directory.
3. **Compiler Speed Optimizations**:
   - Modifier compiler structures (e.g., AST pooling, string allocation) to increase the self-compilation throughput.
