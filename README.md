# Kai Compiler (Self-Hosted Version)

Welcome to the clean, self-hosted version of the **Kai** systems programming language compiler! 

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

---

## 4. Next Action Plans / Roadmap

For the next agent working on this codebase, the priorities are:
1. **Error Unions implementation (Phase 3)**:
   - Implement status-integer error unions (`T!E`), restoring the `try` / `catch` propagation check logic natively inside the self-hosted type checker and C code generator.
2. **Standard Library Expansion**:
   - Add native networking, threading wrappers, and standard formatting routines directly into the `std/` directory.
3. **Compiler Speed Optimizations**:
   - Modifier compiler structures (e.g., AST pooling, string allocation) to increase the self-compilation throughput.
