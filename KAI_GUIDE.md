# The Kai Programming Language: Reference & Guide

Welcome to the definitive developer guide for the **Kai programming language**. Kai is a high-performance, statically-typed, compile-to-C systems programming language designed for zero runtime overhead, memory safety through explicit allocation policies, and clean code generation. 

This document provides a comprehensive guide to Kai's syntax, design patterns, standard library, and a comparison with C and Zig to help new learners master it.

---

## Table of Contents
1. [Design Philosophy](#design-philosophy)
2. [Language Basics](#language-basics)
3. [Functions and FFI](#functions-and-ffi)
4. [Structs and Object-Oriented Patterns](#structs-and-object-oriented-patterns)
5. [Enums and Pattern Matching](#enums-and-pattern-matching)
6. [Generics and Comptime Duck-Typing](#generics-and-comptime-duck-typing)
7. [Standard Library Showcase](#standard-library-showcase)
8. [Do's and Don'ts (Best Practices)](#dos-and-donts-best-practices)
9. [Side-by-Side Comparison: Kai vs. C vs. Zig](#side-by-side-comparison-kai-vs-c-vs-zig)

---

## Design Philosophy
* **Zero Runtime Overhead:** No garbage collector, no hidden runtime, and no vtables. Everything compiles directly to clean, predictable C code.
* **Explicit Allocations:** Kai mandates explicit allocator propagation. There is no implicit global allocator.
* **Monomorphization-Based Generics:** Generics compile down to concrete monomorphized functions per type, offering compile-time safety and maximum performance.
* **Direct FFI:** Importing C libraries requires zero glue code using first-class `cimport` directives.

---

## Language Basics

### Variables & Mutability
Kai distinguishes between constant variables (`let`) and mutable variables (`var`).

```kai
// Constant, immutable binding
let count = 42

// Mutable variable binding
var temperature = 36.5
temperature = 37.2
```

### Standard Data Types
* `Int`: 64-bit signed integer (maps to `int64_t` in C).
* `Float`: 64-bit double-precision floating point (maps to `double` in C).
* `Bool`: Boolean value (`true` or `false`).
* `Char`: Character value.
* `Str`: Constant character array (maps to `const char*` in C).

```kai
let age: Int = 30
let ratio: Float = 3.14159
let active: Bool = true
let symbol: Char = Char(65) // 'A' in ASCII
let message: Str = "Hello, Kai!"
```

### Control Flow
Kai supports `if`/`else` branches, standard `while` loops, and Go/Zig-style `defer` blocks.

```kai
// If-Else
if ratio > 3.0 {
    print("Greater than 3")
} else {
    print("Less or equal")
}

// While Loop (No 'for' loop exist in Kai, use 'while')
var i = 0
while i < 10 {
    print(int_to_str(i))
    i = i + 1
}

// Defer Block (Runs automatically at the end of the surrounding block scope)
unsafe {
    let buf = malloc(1024)
    defer free(buf) // Guaranteed to execute on exit, preventing leaks
    // Do work with buf...
}
```

### Type Casting & Unsafe Blocks
Safe type casting uses the `as` operator. Unsafe operations (like calling `extern` C functions or dereferencing pointers) must reside inside `unsafe` blocks.

```kai
let int_val = 100
let float_val = int_val as Float // Safe numeric cast

unsafe {
    let raw_ptr = 0x12345 as *Void  // Cast address to void pointer
    let char_ptr = raw_ptr as *Char // Cast void pointer to char pointer
}
```

---

## Functions and FFI

### Declaring Functions
Functions are declared using the `fn` keyword. Parameters and return types are explicitly typed. If a function returns nothing, the return type is omitted.

```kai
fn add(a: Int, b: Int) -> Int {
    return a + b
}

fn print_message(msg: Str) {
    print(msg)
}
```

### FFI & Direct C Importing
Kai features first-class interoperability with C. Standard headers can be directly imported using `cimport` and their functions declared using `extern fn`.

```kai
// Imports header declarations directly
cimport "stdio.h"

// Exposes standard printf function to Kai
extern fn printf(format: Str, value: Int) -> Int

fn main() -> Int {
    unsafe {
        let _ = printf("Hello from C FFI! Val: %d\n", 42)
    }
    return 0
}
```

---

## Structs and Object-Oriented Patterns

### Structs and Implementation Blocks
Structs define state, while `impl` blocks attach methods to those structs. The first parameter of an `impl` method should be named `self` to receive the instance pointer.

```kai
struct Vector {
    x: Float
    y: Float
}

impl Vector {
    // 'self' is implicitly passed as a pointer (Vector*) under the hood
    fn scale(self, factor: Float) {
        self.x = self.x * factor
        self.y = self.y * factor
    }

    fn magnitude(self) -> Float {
        import fast_sqrt from std.math.fast
        return fast_sqrt(self.x * self.x + self.y * self.y)
    }
}

fn main() -> Int {
    var v = Vector(x: 3.0, y: 4.0)
    v.scale(2.0)
    let mag = v.magnitude() // Returns 10.0
    return 0
}
```

---

## Enums and Pattern Matching

### Algebraic Data Types
Kai supports enums with optional payloads (Algebraic Data Types) and handles them via pattern matching.

```kai
enum Option<T> {
    case some(value: T)
    case empty
}

impl Option {
    fn unwrap(self) -> T {
        match self {
            case .some(val) => return val
            case else => unsafe {
                extern fn exit(code: Int)
                exit(1)
            }
        }
    }
}
```

---

## Generics and Comptime Duck-Typing

### Monomorphization & Bound Traits
Kai uses compile-time generics. Traits are optional interface contracts. When compiling generics, Kai compiles a concrete copy of the function for each substituted type (static monomorphization, zero runtime overhead).

```kai
trait Show {
    fn show(self) -> Str
}

struct Point {
    x: Int
    y: Int
}

impl Show for Point {
    fn show(self) -> Str {
        return "Point"
    }
}

// Bounded generic function
fn print_item<T: Show>(item: T) {
    print(item.show())
}
```

---

## Standard Library Showcase

The standard library under `std/` provides high-performance routines with zero external dependencies:

| Module | Purpose | Key API Methods |
| --- | --- | --- |
| `std.core.allocator` | Memory Management | `KaiAllocator` (slab allocator), `CAlloc` (malloc/free wrapper) |
| `std.core.array` | Dynamic Arrays | `ArrayList<T>` (`init`, `push`, `get`, `set`, `pop`, `deinit`) |
| `std.core.string` | String Manipulations | `StringBuilder` (`append_char`, `append_str`), `length`, `substring`, `int_to_str` |
| `std.math.fast` | Optimized Math | `fast_sqrt`, `fast_abs`, `fast_sin`, `fast_cos`, `fast_pow` |
| `std.sync.thread` | Concurrency | `spawn(fn_ptr, arg_ptr)`, `join(thread)`, `Mutex` |
| `std.sync.atomic` | Hardware Locks | `atomic_add(ptr, val)`, `atomic_cas(ptr, old, new)` |
| `std.net.socket` | Berkeley Sockets | `tcp_listen(port)`, `tcp_accept(socket)`, `tcp_connect(ip, port)`, `socket_close(socket)` |
| `std.net.http` | HTTP Web Server | `HttpServer(port, handler)`, `HttpRequest` (`get_header`, `method`, `path`, `body`) |
| `std.os.os` | System Interactivity | `os_sleep_ms(ms)`, `os_getpid()`, `os_getenv(name)`, `os_setenv(name, val)` |
| `std.fs.fs` | Directory Traversals | `fs_exists(path)`, `fs_mkdir(path)`, `fs_opendir(path)`, `fs_readdir(dir)` |
| `std.fs.path` | Path Parsing | `basename(path)`, `dirname(path)`, `extension(path)` |

---

## Do's and Don'ts (Best Practices)

### 1. Function Parameter Naming
* **DON'T** use the parameter name `func` in declarations (e.g., `fn process(func: *Void)`).
* **DO** use alternative names like `f` or `callback`. `func` is a reserved keyword in the lexer and will cause syntactic errors.

### 2. Namespace Collision Prevention in C Targets
* **DON'T** name public standard/global functions exactly after C library symbols (e.g., declaring `fn getenv` or `fn mkdir` at file scope).
* **DO** prefix public symbols with your module namespaces, e.g. `os_getenv` or `fs_mkdir`. The Kai compiler transpiles declarations to global C namespace symbols, so raw naming will cause C compilation duplicate symbol errors.

### 3. Dynamic Allocator Lifecycles
* **DON'T** instantiate local slab allocators (`KaiAllocator`) in loop stack frames and pass their pointers to concurrent threads.
* **DO** initialize the `KaiAllocator` inside the thread's worker body or allocate the state heap structure using the stateless system allocator `CAlloc`.

---

## Side-by-Side Comparison: Kai vs. C vs. Zig

### 1. Simple Variables and Loops

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

### 2. Structures and Methods

#### Kai
```kai
struct Rect {
    w: Int
    h: Int
}
impl Rect {
    fn area(self) -> Int {
        return self.w * self.h
    }
}
```

#### C
```c
struct Rect {
    int64_t w;
    int64_t h;
};
int64_t Rect_area(struct Rect* self) {
    return self->w * self->h;
}
```

#### Zig
```zig
const Rect = struct {
    w: i64,
    h: i64,
    pub fn area(self: Rect) i64 {
        return self.w * self.h;
    }
};
```

---

### 3. FFI Declaration

#### Kai
```kai
cimport "unistd.h"
extern fn getpid() -> Int
```

#### C
```c
#include <unistd.h>
// Standard declaration
pid_t getpid(void);
```

#### Zig
```zig
const c = @cImport({
    @cInclude("unistd.h");
});
// Access via c.getpid()
```

---

### 4. Memory Allocator Usage

#### Kai
```kai
unsafe {
    var allocator = KaiAllocator(heads: 0 as *Char, used: 0)
    allocator.init()
    defer allocator.deinit()

    let buf = allocator.alloc(1024, 1)
    // Use buffer...
    allocator.free(buf)
}
```

#### C
```c
#include <stdlib.h>
void process() {
    char* buf = malloc(1024);
    if (!buf) return;
    // Use buffer...
    free(buf);
}
```

#### Zig
```zig
pub fn process(allocator: std.mem.Allocator) !void {
    const buf = try allocator.alloc(u8, 1024);
    defer allocator.free(buf);
    // Use buffer...
}
```
