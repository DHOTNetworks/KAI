# The Kai Programming Language: Reference & Guide

Welcome to the definitive developer guide for the **Kai programming language**. Kai is a high-performance, statically-typed, compile-to-C and compile-to-LLVM-IR systems programming language. It is designed for zero runtime overhead, memory safety through explicit allocation policies, and clean code generation.

This document provides a comprehensive guide to Kai's syntax, type system, control flow, standard library, best practices, and side-by-side comparisons with C and Zig.

---

## Table of Contents
1. [Design Philosophy](#1-design-philosophy)
2. [Data Types](#2-data-types)
3. [Variables & Mutability](#3-variables--mutability)
4. [Pointer System](#4-pointer-system)
5. [Arrays, Slices, and Ranges](#5-arrays-slices-and-ranges)
6. [Tuples](#6-tuples)
7. [Control Flow](#7-control-flow)
8. [Functions & Direct C FFI](#8-functions--direct-c-ffi)
9. [Structs & Method Implementation Blocks](#9-structs--method-implementation-blocks)
10. [Enums & Pattern Matching (ADTs)](#10-enums--pattern-matching-adts)
11. [Error Unions & Optionals](#11-error-unions--optionals)
12. [Traits & Bounded Generics](#12-traits--bounded-generics)
13. [GCC Inline Assembly](#13-gcc-inline-assembly)
14. [Standard Library Showcase](#14-standard-library-showcase)
15. [Memory Management & Safety](#15-memory-management--safety)
16. [Do's and Don'ts (Best Practices)](#16-dos-and-donts-best-practices)
17. [Side-by-Side Comparison: Kai vs. C vs. Zig](#17-side-by-side-comparison-kai-vs-c-vs-zig)
18. [Compiler Command-Line Reference](#18-compiler-command-line-reference)

---

## 1. Design Philosophy
* **Zero Runtime Overhead:** No garbage collector, no hidden runtime, and no vtables. Everything compiles directly to clean, predictable C code or LLVM IR.
* **Explicit Allocations:** Kai mandates explicit allocator propagation. There is no implicit global allocator.
* **Monomorphization-Based Generics:** Generics compile down to concrete monomorphized functions per type, offering compile-time safety and maximum performance.
* **Direct FFI:** Importing C libraries requires zero glue code using first-class `cimport` directives.

---

## 2. Data Types

Kai supports a full range of native and sized systems types:

### Sized Integer Types
| Signed Type | Unsigned Type | C Equivalent |
|---|---|---|
| `i8` | `u8` | `int8_t` / `uint8_t` |
| `i16` | `u16` | `int16_t` / `uint16_t` |
| `i32` | `u32` | `int32_t` / `uint32_t` |
| `i64` | `u64` | `int64_t` / `uint64_t` |
| `isize` | `usize` | `intptr_t` / `uintptr_t` (or `ptrdiff_t` / `size_t`) |

* `Int` is the default integer type (alias for `i64`).

### Floating-Point & Other Primitives
* `Float` (alias for `f64` / C `double`)
* `f32` (C `float`)
* `f64` (C `double`)
* `Bool` (`true` or `false`)
* `Char` (ASCII character value)
* `Str` (immutable string pointer, C `const char*`)
* `Void` (C `void`)

---

## 3. Variables & Mutability

Kai distinguishes between constant variables (`let`) and mutable variables (`var`).

```kai
// Constant, immutable binding
let count = 42

// Mutable variable binding
var temperature = 36.5
temperature = 37.2

// Explicit type annotations
let age: i32 = 30
var flag: Bool = true
```

---

## 4. Pointer System

Kai implements a simplified, type-safe pointer system:

- `*T`: Constant/immutable pointer.
- `*mut T`: Mutable pointer.
- `&x`: Address-of operator. Automatically infers mutability (`*mut T` if the target is a `var`, `*T` if the target is a `let`).
- `*ptr`: Dereferences a pointer safely. No `unsafe` block is required for safe dereferences, but operations on raw generic pointers may require `unsafe` contexts.

```kai
var val: Int = 100
let ptr: *mut Int = &val
*ptr = 200 // val is now 200

let const_val: Int = 50
let const_ptr: *Int = &const_val
// *const_ptr = 60 // Error: cannot modify through immutable pointer
```

---

## 5. Arrays, Slices, and Ranges

### Arrays
Declare fixed-size stack arrays:
```kai
let arr = [1, 2, 3, 4, 5]
let val = arr[2] // 3
```

### Slices
Create a fat-pointer representation of a sub-array or sub-string using start and end indices:
```kai
let message: Str = "hello world"
let slice: Str = message[0..5] // "hello"
```

### Ranges
Used for loop boundaries and slice limits:
- `0..10`: Exclusive range (0 through 9).
- `0..=10`: Inclusive range (0 through 10).

---

## 6. Tuples

Tuples are anonymous collections of values that compile to flat, named struct representations behind the scenes:

```kai
let point = (10, 20)
let x = point.0
let y = point.1
```

---

## 7. Control Flow

### If/Else Conditionals
Conditionals must evaluate to a boolean expression. Curly braces are required.
```kai
if x > 10 {
    print("Greater")
} else {
    print("Less or equal")
}
```

### Loops
Loops can use `while` or `for ... in` range operators:
```kai
// While Loop
var i = 0
while i < 10 {
    i = i + 1
}

// For Loop (requires range)
for idx in 0..10 {
    // idx goes from 0 to 9
}

for idx in 0..=5 {
    // idx goes from 0 to 5
}
```

### Break & Continue
```kai
var j = 0
while true {
    j = j + 1
    if j == 5 { continue }
    if j > 10 { break }
}
```

### Defer & Errdefer
- `defer` executes block operations at the end of the surrounding scope.
- `errdefer` executes only if the function returns an error (within an error union type).

```kai
unsafe {
    let buf = malloc(1024)
    defer free(buf) // Cleans up block exit
    // do work...
}
```

---

## 8. Functions & Direct C FFI

### Declaring Functions
```kai
fn add(a: Int, b: Int) -> Int {
    return a + b
}

// Void return type is implicit if omitted
fn log_message(msg: Str) {
    print(msg)
}
```

### Direct C Interoperability (FFI)
Use `cimport` to bring in C declarations directly. Declare C symbols using `extern fn`:

```kai
cimport "stdio.h"
cimport "stdlib.h"

extern fn printf(format: Str, value: Int) -> Int
extern fn exit(code: Int)

fn main() -> Int {
    unsafe {
        let _ = printf("FFI value: %d\n", 99)
    }
    return 0
}
```

---

## 9. Structs & Method Implementation Blocks

Structs represent structured state. Methods are attached using separate `impl` blocks. The first argument to an `impl` method should be `self` (constant pointer `*T`) or `mut self` (mutable pointer `*mut T`):

```kai
struct Point {
    x: Int
    y: Int
}

impl Point {
    // Read-only method
    fn magnitude_squared(self) -> Int {
        return self.x * self.x + self.y * self.y
    }

    // Mutating method
    fn scale(mut self, factor: Int) {
        self.x = self.x * factor
        self.y = self.y * factor
    }
}
```

---

## 10. Enums & Pattern Matching (ADTs)

Enums can have payloads per variant, forming Algebraic Data Types. Retrieve payload contents via pattern-matching `match` blocks:

```kai
enum Shape {
    case circle(radius: Int)
    case rectangle(width: Int, height: Int)
}

fn get_area(s: Shape) -> Int {
    match s {
        case .circle(r) => {
            return r * r * 3
        }
        case .rectangle(w, h) => {
            return w * h
        }
    }
}
```

---

## 11. Error Unions & Optionals

### Error Unions (`T!E`)
Error unions indicate a function can either return a value or an error code declared in an `error` set:

```kai
error FileError {
    case not_found
    case permission_denied
}

fn open_file(path: Str) -> Int!FileError {
    if file_exists(path) {
        return 42 // returns success value
    }
    return FileError.not_found // returns error enum variant
}
```

#### Try Propagation & Catch Fallback
- `try expr`: If the expression returns an error, bubble it up from the current function.
- `expr catch fallback`: If `expr` errors, evaluate to the fallback value.
- `expr catch |err| fallback`: Inspect the specific error in the fallback expression.

```kai
fn process() -> Int!FileError {
    let fd = try open_file("data.txt")
    return fd
}

fn main() {
    let val = open_file("config.json") catch 0 // Defaults to 0 on failure
    let specific = open_file("config.json") catch |err| {
        // handle err...
        return 1
    }
}
```

### Optionals (`?T`)
An optional type indicates a value might be present (`some`) or absent (`none`).

```kai
let optional_val: ?Int = none
let active_val: ?Int = 42

// Unwrap with catch:
let unwrapped = active_val catch 0
```

---

## 12. Traits & Bounded Generics

### Bounded Generics & Traits
Define generic protocols using `trait`, implement them in `impl TraitName for StructName`, and bound generic type parameters:

```kai
trait Printable {
    fn print_val(self)
}

struct Logger {}

impl Printable for Logger {
    fn print_val(self) {
        print("Logger active")
    }
}

// Bounded generic function declaration
fn run_print<T: Printable>(obj: T) {
    obj.print_val()
}
```

---

## 13. GCC Inline Assembly

Inject optimized inline assembly directly into C output:

```kai
fn get_cpuid() -> Int {
    var out: Int = 0
    unsafe {
        asm volatile (
            "cpuid"
            : [result] "=r" (out)
            :
            : "eax", "ebx", "ecx", "edx"
        )
    }
    return out
}
```

---

## 14. Standard Library Showcase

The standard library under `std/` provides modules for system programming:

| Module | Purpose | APIs |
|---|---|---|
| `std.core.allocator` | Heap allocations | `KaiAllocator`, `CAlloc`, `Allocator` |
| `std.core.array` | Dynamic arrays | `ArrayList<T>` |
| `std.core.string` | Core strings, converters | `StringBuilder`, `length`, `int_to_str` |
| `std.io.file` | Filesystem IO | `read_to_string`, `write_string` |
| `std.io.print` | Output printing | `print`, `printf` |
| `std.os` | Operating system services | Command line args, env variables |

---

## 15. Memory Management & Safety

Kai prevents common bugs via:
1. **Explicit Propagation**: Memory allocators are passed down; there is no hidden implicit global heap allocator.
2. **Compile-Time Warnings**: The compiler checks for use-after-free (E0031) and double-free (E0032) conditions at compile-time.

---

## 16. Do's and Don'ts (Best Practices)

1. **Avoid Parameter Name `func`**:
   * **DON'T** use parameter name `func` (e.g. `fn process(func: *Void)`).
   * **DO** use alternative names like `f` or `callback`. `func` is a lexer token category.
2. **Prevent Namespace Collision**:
   * **DON'T** name public standard/global functions exactly after C library symbols (e.g., declaring `fn getenv` or `fn mkdir` at file scope).
   * **DO** prefix public symbols with your module namespaces, e.g. `os_getenv` or `fs_mkdir`.
3. **Allocator Lifetime**:
   * **DON'T** initialize local slab allocators (`KaiAllocator`) in loop stack frames and pass them to concurrent threads.
   * **DO** allocate dynamic heap data using `CAlloc` or initialize the allocator inside the thread's scope.

---

## 17. Side-by-Side Comparison: Kai vs. C vs. Zig

### Variables and Loops
#### Kai
```kai
var i = 0
while i < 5 {
    print(int_to_str(i))
    i = i + 1
}
```
#### C
```c
int i = 0;
while (i < 5) {
    printf("%d\n", i);
    i++;
}
```
#### Zig
```zig
var i: usize = 0;
while (i < 5) : (i += 1) {
    std.debug.print("{d}\n", .{i});
}
```

---

## 18. Compiler Command-Line Reference

Build programs, run diagnostics, or query the compiler state:

```bash
# Type-check a file only
kai check main.kai

# Transpile to C and compile with GCC/Clang (default optimization: -O2)
kai run main.kai

# Specify custom output binary
kai main.kai -o my_app

# Emit transpiled C code to disk without linking
kai -c main.kai

# Compile using builder-based transpilation
kai -c -CC main.kai

# Compile directly to LLVM IR
kai -llvm main.kai
```
