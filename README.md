# Kai Compiler (Self-Hosted Version)

Welcome to the clean, self-hosted version of the **Kai** systems programming language compiler! 

<div align="center">

[![Zig](https://img.shields.io/badge/Zig-0.15.2-F7A41D?style=flat-square&logo=zig&logoColor=white)](https://ziglang.org/)
![KAI](https://img.shields.io/badge/KAI-black?style=for-the-badge&logo=data:image/svg%2bxml;base64,PHN2ZyB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHZpZXdCb3g9IjAgMCAxMTAgMTAwIj4KICA8ZGVmcz4KICAgIDwhLS0gQSB2aWJyYW50LCBoaWdoLWVuZXJneSBncmFkaWVudCBpbnNwaXJlZCBieSBaaWcncyBzdHJpa2luZyBjb2xvciBwcm9maWxlIC0tPgogICAgPGxpbmVhckdyYWRpZW50IGlkPSJ6aWdTdHlsZUdyYWQiIHgxPSIwJSIgeTE9IjAlIiB4Mj0iMTAwJSIgeTI9IjEwMCUiPgogICAgICA8c3RvcCBvZmZzZXQ9IjAlIiBzdG9wLWNvbG9yPSIjRkY3QTAwIiAvPgogICAgICA8c3RvcCBvZmZzZXQ9IjEwMCUiIHN0b3AtY29sb3I9IiNGRkIzMDAiIC8+CiAgICA8L2xpbmVhckdyYWRpZW50PgogIDwvZGVmcz4KCiAgPCEtLSBMZWZ0IFN0ZW06IEEgdGhpY2ssIGphZ2dlZCBwaWxsYXIgbGVhbmluZyBmb3J3YXJkLCB3aXRoIGFuIGlubmVyIHN0ZXAgY3V0IG91dCAtLT4KICA8cGF0aCBkPSJNIDMyIDEwIEwgNjIgMTAgTCA1MiA0NSBMIDQyIDQ1IEwgMzIgOTAgTCAyIDkwIFoiIGZpbGw9InVybCgjemlnU3R5bGVHcmFkKSIgLz4KICAKICA8IS0tIFVwcGVyIFJpZ2h0IEFybTogQSBzaGFycCBzaGFyZCBwZXJmZWN0bHkgc2xvdHRlZCBhYm92ZSB0aGUgc3RlbSdzIHN0ZXAgLS0+CiAgPHBhdGggZD0iTSA2NiAxMCBMIDEwNyAxMCBMIDc2IDQxIEwgNTcgNDEgWiIgZmlsbD0idXJsKCN6aWdTdHlsZUdyYWQpIiAvPgogIAogIDwhLS0gTG93ZXIgUmlnaHQgQXJtOiBBIHdpZGUsIGdyb3VuZGluZyBzaGFyZCBzbG90dGVkIGJlbG93IHRoZSBzdGVwIC0tPgogICAgPHBhdGggZD0iTSA0NSA0OSBMIDY1IDQ5IEwgODcgOTAgTCAzNiA5MCBaIiBmaWxsPSJ1cmwoI3ppZ1N0eWxlR3JhZCkiIC8+Cjwvc3ZnPg==)
[![C](https://img.shields.io/badge/C-00599C?logo=c&logoColor=white)](#)
[![Open Source](https://img.shields.io/badge/Open%20Source-Yes-brightgreen?style=flat-square)](#)

</div>

---

This repository has been fully transitioned from the original Python bootstrap compiler. All compiler development, standard library modules, and feature enhancements are now written entirely in Kai and compiled by Kai itself.

---

## 1. Project Structure

The project has been restructured into clean subdirectories under `src/`:

- **`src/`**: The self-hosted compiler source code:
  - [`compiler.kai`](file:///Users/karan/kai-c/src/compiler.kai): Main compiler driver and command-line entrypoint.
  - **`compiler/`**: The frontend compilation phases:
    - [`lexer.kai`](file:///Users/karan/kai-c/src/compiler/lexer.kai): Converts source to token streams.
    - [`parser.kai`](file:///Users/karan/kai-c/src/compiler/parser.kai): Parses tokens into expression and statement AST nodes.
    - [`ast_nodes.kai`](file:///Users/karan/kai-c/src/compiler/ast_nodes.kai): Nodes defining the structure of AST.
    - [`token_defs.kai`](file:///Users/karan/kai-c/src/compiler/token_defs.kai): Lexer token kinds and value structures.
    - [`types.kai`](file:///Users/karan/kai-c/src/compiler/types.kai): Language types and target type representation.
    - [`type_checker.kai`](file:///Users/karan/kai-c/src/compiler/type_checker.kai): Resolves types, tracks mutability/moves, checks imports.
    - [`symbol_table.kai`](file:///Users/karan/kai-c/src/compiler/symbol_table.kai): Manages nested scopes and variable declarations.
    - [`imports.kai`](file:///Users/karan/kai-c/src/compiler/imports.kai): Resolves imported modules from the local and std paths.
    - [`error_registry.kai`](file:///Users/karan/kai-c/src/compiler/error_registry.kai): Error definitions and descriptive auto-fixes.
  - **`codegen/`**: The backend code emitters:
    - [`c_legacy.kai`](file:///Users/karan/kai-c/src/codegen/c_legacy.kai): Direct-emit transpiler mapping AST directly to raw C text (`-c`).
    - [`c_builder.kai`](file:///Users/karan/kai-c/src/codegen/c_builder.kai): High-fidelity C-AST compiler tree builder (`-CC`).
    - [`c_printer.kai`](file:///Users/karan/kai-c/src/codegen/c_printer.kai): Translates structured C-AST to pretty-printed C text.
    - [`llvm.kai`](file:///Users/karan/kai-c/src/codegen/llvm.kai): Native LLVM backend generating LLVM IR directly (`-llvm`).
  - **`tools/`**: Subcommand modules (`init`, `build`, `fix`, `explain`, etc.).
- **`std/`**: The standard library:
  - `std/core/allocator.kai`: Allocation routines (`KaiAllocator`, `CAlloc`).
  - `std/collections/`: Core collections (`ArrayList`, `HashMap`, `StringBuilder`).
  - `std/io/`: Output and file interaction.
- **`compiler_bootstrap.c`**: A verified C output of the compiler, used as the zero-dependency bootstrapper.

---

## 2. CLI Usage & Commands

Run `./CCkai` (or the bootstrapped binary) to see all options:

```bash
Usage: kai <command> [options]

Commands:
  init [path]     Create a new Kai project
  build [args]    Build the project using build.kai
  check <file>    Type-check only (no code generation)
  run <file>      Compile and run a .kai file
  <file>          Compile and run (shorthand)
  patch <file>    Apply an operation-based edit
  explain <code>  Explain an error code (e.g., E0031)
  skills          List available agent skills
  fix <file>      Auto-fix diagnostics (--plan|--patch|--apply)
  graph <file>    Export or query the AST graph

Flags:
  --json          Output diagnostics in JSON format
  -o <file>       Specify output binary name
  -c              Emit C code only (no linking)
  -CC             Use builder-based C-AST codegen (experimental)
  -llvm           Use LLVM backend (experimental)
  -O0|-O1|-O2|-O3|-Os  Optimization level (default: -O2)
```

---

## 3. Language & Compiler Features

- **Double-pass Import Resolution**: Modules parse into a unified shared pool. Selective symbols are typechecked and validated without index integrity issues.
- **Robust Memory Rules**: Static validation of mutability, explicit allocators, compilation warnings for use-after-free and double-free scenarios.
- **C-AST Builder Codegen (`-CC`)**: Rewrites complex patterns (nested `try`/`catch`, options, match, loops, slices, string interpolations) into structured, correct C-AST nodes, printing clean, robust C output.
- **Direct LLVM IR Gen (`-llvm`)**: Targets native binary generation without a C compiler, handling numeric, string, array, struct, flow control, and inline assembly.

---

## 4. Bootstrapping & Building

### Step 1: Compile the Bootstrap Binary
Build from `compiler_bootstrap.c`:
```bash
gcc -O2 compiler_bootstrap.c -o CCkai-bootstrap
```

### Step 2: Compile compiler from source
Compile the compiler source using the bootstrap binary:
```bash
./CCkai-bootstrap -c -CC src/compiler.kai && gcc -O2 -o CCkai CCcompiler.c
```

### Step 3: Self-Host Verification
Re-compile the compiler with the newly built compiler to verify complete identity:
```bash
./CCkai -c -CC src/compiler.kai && gcc -O2 -o CCkai-self CCcompiler.c
shasum CCcompiler.c
```
*(C outputs of successive self-hosted stages match perfectly)*

---

## 5. Cross-Compilation via Zig

To cross-compile the transpiled C compiler code for Windows or other platforms:

1. **Translate C output to Zig (skipping C platform-specific helpers)**:
   ```bash
   zig translate-c -DNO_GET_EXE_DIR compiler.c > compiler.zig
   ```
2. **Append the Windows compatibility imports**:
   ```bash
   echo 'comptime { _ = @import("windows_compat.zig"); }' >> compiler.zig
   ```
3. **Cross-compile**:
   ```bash
   zig build-exe compiler.zig -target aarch64-windows-gnu -lc -femit-bin=compiler.exe
   zig build-exe compiler.zig -target x86_64-windows-gnu -lc -femit-bin=compiler.exe
   ```
