# 12 — Memory Layout (Stack / Heap / Data / BSS)

## What this shows
- Where different kinds of variables actually live in memory:
  initialized globals (`.data`), uninitialized globals (`.bss`),
  function-local `static` variables (also `.data`/`.bss`, NOT the
  stack), regular locals (stack), and `malloc`'d memory (heap).
- That `.bss` variables are automatically zero-initialized by the
  runtime before `main()` even starts — you get a guaranteed `0`
  without writing any initialization code yourself.
- Stack growth/shrink across recursive function calls, visible by
  printing each local variable's address at increasing recursion
  depth.

## Typical memory layout (low to high address, conceptually)

    +-------------------+  low addresses
    |   .text (code)    |   the compiled instructions themselves
    +-------------------+
    |   .data            |  initialized globals/statics (global_initialized, static_local)
    +-------------------+
    |   .bss              | uninitialized globals/statics (global_uninitialized), zeroed at startup
    +-------------------+
    |   heap              | grows UPWARD as you malloc more (heap_var's target)
    |        ...          |
    |   (free space)      |
    |        ...          |
    |   stack             | grows DOWNWARD with each function call (stack_var, local_var)
    +-------------------+  high addresses

(exact layout/direction is platform-dependent, but this is the common
mental model on most desktop and microcontroller architectures)

## Key takeaways
- **Stack**: automatic, fast, limited size. Every function call pushes
  a new frame; every return pops it. Local variables are only valid
  for the lifetime of the function call — this is exactly why
  returning `&local_var` from a function (see `11_undefined_behavior`)
  is a dangling pointer bug.
- **Heap**: manual, flexible, much larger (but not infinite), managed
  explicitly with `malloc`/`free`. Slower to allocate than the stack,
  and — as covered in `10_dynamic_memory` — riskier (leaks,
  fragmentation, use-after-free).
- **.data vs .bss**: both hold global/static variables, but `.data`
  stores ones you gave an explicit non-zero initial value, while
  `.bss` stores ones left uninitialized (or explicitly set to 0) —
  `.bss` doesn't even take up space in the compiled binary file itself,
  since it's just "reserve this much zeroed memory at startup."
- A function-local `static` variable is NOT on the stack — it behaves
  like a global in terms of WHERE it lives and HOW LONG it lives, but
  its NAME is only visible inside that function (this connects
  directly back to `06_static`).

## Embedded relevance
- On a microcontroller, RAM is extremely limited (often kilobytes,
  not gigabytes) — knowing exactly which segment a variable lives in
  is not academic trivia, it directly determines whether your
  firmware fits in available memory.
- The linker script (a later Level 3 project) is literally the file
  that defines where `.text`, `.data`, `.bss`, the heap, and the
  stack are placed in the microcontroller's actual memory map — this
  module is the conceptual foundation for understanding that file
  later.
- Stack overflow (running out of stack space, often from deep
  recursion or large local arrays) is a real and common embedded
  failure mode, and unlike on a PC, there's often no OS to catch it
  gracefully — it can silently corrupt adjacent memory instead of
  crashing with an error.
- `.bss` being auto-zeroed matters in practice: many embedded bugs
  come from ASSUMING a global is zero-initialized when it actually
  isn't (e.g., in code paths that skip normal startup), so knowing
  this guarantee — and its limits — is directly useful.
