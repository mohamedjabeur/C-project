# 10 — Dynamic Memory

## What this shows
- A growable dynamic array (`DynamicArray`) built with `malloc` and
  `realloc`, doubling capacity whenever it fills up.
- Correct cleanup with `free`, including setting the pointer to
  `NULL` afterward to avoid leaving a dangling pointer.
- A deliberately commented-out use-after-free bug, with the exact
  sanitizer command needed to catch it.

## How to reproduce the bug on purpose

    gcc -fsanitize=address,undefined code.c -o demo
    ./demo

Then uncomment the `da_push(&da, 999);` line after `da_free(&da);`
and rebuild. AddressSanitizer will report a `heap-use-after-free`
error, pointing to the exact line — pasted output would look like:

    ERROR: AddressSanitizer: heap-use-after-free on address ...
    READ of size 4 at ... thread T0
        #0 in da_push code.c:XX

## Key takeaways
- `malloc` requests memory from the heap at runtime; `realloc` tries
  to grow (or shrink) an existing allocation, possibly moving it to a
  new address — which is why you must always reassign the pointer
  from `realloc`'s return value, never assume the old pointer is
  still valid.
- `realloc` can fail and return `NULL` while leaving the original
  allocation untouched — overwriting your only pointer with that
  `NULL` return value directly (`da->data = realloc(...)`) would leak
  the original block. The safe pattern is to store the result in a
  temporary pointer first and check it, exactly as done above.
- `free()` releases memory back to the system but does NOT set your
  pointer to `NULL` automatically — using it afterward (a
  "use-after-free") is undefined behavior: it might work, crash, or
  silently corrupt unrelated memory, which is what makes it dangerous
  and hard to debug without a sanitizer.
- Every `malloc`/`realloc` must be paired with exactly one `free` —
  more automotive/embedded static-analysis tools exist specifically
  to catch mismatched allocation/free pairs, because in C the
  compiler will not catch this for you.

## Why embedded/automotive code usually avoids malloc after init
- **Fragmentation**: repeated malloc/free over a long-running system
  (weeks/months of uptime) can fragment the heap until a new
  allocation fails even if "enough" total memory is technically free.
- **Non-determinism**: `malloc`'s execution time isn't guaranteed —
  it can vary depending on heap state, which is unacceptable in
  hard real-time systems (e.g., an ECU control loop with a strict
  timing deadline).
- **Safety standards**: MISRA C and most automotive coding guidelines
  either forbid or heavily restrict dynamic memory after
  initialization, specifically because a failed allocation
  (`malloc` returning `NULL`) in a safety-critical path is a failure
  mode you must never allow.
- In practice: embedded systems allocate everything they need ONCE at
  startup (often as static/global buffers or fixed-size arrays, like
  the ring buffer from the C fundamentals folder) and never call
  `malloc` again during normal operation.
