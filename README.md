# C Fundamentals Lab

A collection of small, deliberately isolated C programs, each focused
on exactly one core language concept — the foundation every Embedded
C project (STM32 register access, drivers, RTOS, CAN) builds on top
of. This repo exists to answer one question directly: **do I actually
understand C at a systems level, or did I only ever copy embedded
tutorials?**

Every folder follows the same structure:
- `code.c` (or multiple `.c` files where the concept requires it)
- `README.md` explaining what the code demonstrates, a memory/behavior
  trace, key takeaways, and — specifically — why the concept matters
  in embedded/automotive firmware.

## How to build any example

    gcc -Wall -Wextra <folder>/code.c -o demo && ./demo

For the undefined-behavior folder, use sanitizers instead:

    gcc -fsanitize=address,undefined -g <folder>/<file>.c -o demo && ./demo

## Index

| Folder | Concept | Demonstrates |
|---|---|---|
| [`01_pointers`](./01_pointers) | Pointers | Pass-by-pointer, pointer arithmetic (string reversal), pointer-to-pointer, NULL checks |
| [`02_arrays_vs_pointers`](./02_arrays_vs_pointers) | Arrays vs pointers | Array decay, `sizeof` inside vs outside a function, `arr[i]` == `*(arr+i)` |
| [`03_structs_unions_enums`](./03_structs_unions_enums) | Structs / unions / enums | Struct layout, union type-punning, enums as named constants, composite config objects |
| [`06_static`](./06_static) | `static` vs global scope | File-scope linkage rules, function-local static persistence, multi-file compilation |
| [`07_const_correctness`](./07_const_correctness) | `const` correctness | `const int*` vs `int *const` vs `const int *const`, compile-time safety |
| [`08_function_pointers`](./08_function_pointers) | Function pointers | Dispatch tables, callbacks, runtime-selectable comparators (`qsort`-style) |
| [`09_preprocessor_macros`](./09_preprocessor_macros) | Preprocessor / macros | Object-like vs function-like macros, the classic `MIN(x++, y++)` bug, conditional compilation |
| [`10_dynamic_memory`](./10_dynamic_memory) | Dynamic memory | `malloc`/`realloc`/`free`, use-after-free (sanitizer-verified), why embedded avoids it after init |
| [`11_undefined_behavior`](./11_undefined_behavior) | Undefined behavior | Signed overflow, uninitialized reads, out-of-bounds writes, dangling pointers — all sanitizer-verified |
| [`12_memory`](./12_memory) | Memory layout | Stack vs heap vs `.data` vs `.bss`, stack growth, why RAM layout matters on constrained targets |

> Note: folders `04` and `05` are intentionally reserved for two
> upcoming concepts and will be filled in shortly — numbering reflects
> the eventual full sequence, not the order things were finished in.

## Why this repo exists

Most embedded portfolios jump straight to STM32 blink/UART projects
and skip proving the C fundamentals underneath them. This repo does
the opposite on purpose: each folder isolates ONE concept so it can be
verified in under a minute, with an explicit "why this matters in
embedded/automotive firmware" section — so the connection to real
hardware work isn't left implicit.

This is the first step of a larger roadmap:

    C fundamentals (this repo)
        -> Embedded C (STM32 register-level projects)
        -> Professional Embedded C (RTOS, CAN, state machines, linker/boot)
        -> Automotive Embedded (ECU-style capstone)

See my other repositories for the STM32 and automotive-focused stages
of this roadmap.
