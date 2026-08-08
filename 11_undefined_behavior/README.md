# 11 — Undefined Behavior

## What this shows
Four separate, deliberately broken programs, each isolated in its own
file so one bug doesn't stop you from reaching the others:

1. `01_signed_overflow.c` — signed integer overflow.
2. `02_uninitialized_variable.c` — reading a variable before it's set.
3. `03_out_of_bounds_write.c` — writing past the end of an array.
4. `04_dangling_pointer.c` — returning the address of a local variable.

## How to reproduce and catch each one

Compile EACH file individually with sanitizers enabled:

    gcc -fsanitize=address,undefined -g 01_signed_overflow.c -o ub1 && ./ub1
    gcc -fsanitize=address,undefined -g 02_uninitialized_variable.c -o ub2 && ./ub2
    gcc -fsanitize=address,undefined -g 03_out_of_bounds_write.c -o ub3 && ./ub3
    gcc -fsanitize=address,undefined -g 04_dangling_pointer.c -o ub4 && ./ub4

Example real sanitizer output (signed overflow):

    01_signed_overflow.c:11:22: runtime error: signed integer overflow:
    2147483647 + 1 cannot be represented in type 'int'

Example real sanitizer output (out-of-bounds write):

    ERROR: AddressSanitizer: stack-buffer-overflow on address ...
    WRITE of size 4 at ... thread T0
        #0 in main 03_out_of_bounds_write.c:11

Example real sanitizer output (dangling pointer):

    ERROR: AddressSanitizer: stack-use-after-return on address ...
    READ of size 4 at ... thread T0
        #0 in main 04_dangling_pointer.c:16

*(Paste your actual terminal output here once you run these locally —
real output from your machine is more convincing in a portfolio than
retyped text.)*

## Key takeaways
- "Undefined behavior" does not mean "the program crashes." It means
  the C standard makes NO guarantee about what happens — the code
  might crash, might silently produce wrong results, might appear to
  work fine today and break on a different compiler, optimization
  level, or hardware target. That unpredictability is exactly what
  makes UB dangerous.
- Signed overflow (`INT_MAX + 1`) is UB, but unsigned overflow wraps
  around predictably — this is a deliberate, well-defined difference
  in the C standard, not an inconsistency.
- Reading an uninitialized variable can produce a different "garbage"
  value every run, every recompilation, or every optimization level —
  it is never safe to assume it will "probably be zero."
- Out-of-bounds array access has no automatic bounds checking in C
  (unlike languages such as Python or Java) — writing past the end of
  an array silently corrupts whatever memory happens to be adjacent,
  which can stay invisible for a long time before it causes a crash
  somewhere completely unrelated.
- Returning the address of a local variable is one of the most common
  beginner bugs: the local variable's storage is reclaimed the moment
  the function returns, so the returned pointer refers to memory that
  no longer belongs to anything.

## Embedded relevance
- Embedded/automotive code very often runs WITHOUT an OS or memory
  protection to catch these bugs at runtime — an out-of-bounds write
  or dangling pointer can silently corrupt a register, a peripheral
  buffer, or another task's stack, with no crash message at all.
- This is exactly why safety-critical coding standards (MISRA C) ban
  or restrict entire categories of these patterns outright (e.g., no
  returning pointers to locals, mandatory initialization of all
  variables) — not as style preferences, but because these bugs are
  extremely hard to catch after the fact on real hardware.
- Running your code through sanitizers on your PC, BEFORE it ever
  touches a microcontroller, is a habit worth demonstrating —
  showing you actively hunt for this class of bug (rather than
  hoping you never write one) is a strong signal for a safety-focused
  automotive role.
