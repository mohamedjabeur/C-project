# 07 — const correctness

## What this shows
- `const int *arr` as a function parameter: a promise that the
  function will only read, never modify, the caller's data.
- `const int *p1` — pointer to a const value: the VALUE is protected,
  the pointer can be reassigned.
- `int *const p2` — const pointer to a value: the POINTER is fixed,
  the value it points to can be modified.
- `const int *const p3` — both the pointer and the value are locked.

## Read-right-to-left rule (how to parse any const declaration)

    const int *p1;        ->  p1 is a "pointer to (const int)"
                               = the INT is const, pointer is not

    int *const p2;        ->  p2 is a "const pointer to (int)"
                               = the POINTER is const, int is not

    const int *const p3;  ->  p3 is a "const pointer to (const int)"
                               = BOTH are const

## Key takeaways
- `const` on a function parameter is a contract: it tells the caller
  (and the compiler enforces it) that the function will not modify
  their data through that pointer — critical when passing large
  buffers/structs by pointer for performance, without giving up
  safety.
- The position of `const` relative to `*` changes what's actually
  protected — this is one of the most commonly misunderstood/misused
  parts of C, and a frequent interview question.
- `const int *const` is the safest possible pointer parameter: it
  guarantees the function can only read one specific piece of data
  and nothing else.
- These are all COMPILE-time checks, not runtime — the compiler
  rejects violations before the program ever runs, which is exactly
  why const-correctness is "free" safety with zero runtime cost.

## Embedded relevance
- Peripheral register definitions are often declared as
  `volatile const uint32_t *` for read-only status registers — const
  documents "this register is read-only by contract," volatile
  documents "hardware can change it outside program flow" (see the
  future `volatile` module for that distinction).
- Passing large config structs or lookup tables into driver functions
  as `const struct Foo *` avoids copying the whole struct while
  guaranteeing the driver won't accidentally corrupt the caller's
  data — used constantly in HAL/driver-style APIs.
- Compilers can place `const` data (like lookup tables) into flash
  memory instead of RAM on embedded targets, which matters a lot when
  RAM is extremely limited — const isn't just a safety habit, it can
  directly affect memory placement.
