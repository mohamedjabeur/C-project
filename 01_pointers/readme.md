# 01 — Pointers

## What this shows
- Passing a pointer to a function so it can modify the caller's variable
  (`change_value`).
- Pointer arithmetic / traversal: reversing a string in-place using two
  pointers walking toward each other (`reverse_string`).
- Pointer-to-pointer (`int **`) and defensive NULL checking before
  dereferencing (`safe_increment`).

## Memory trace (Example 1)

Initial state:
  x   = 10
  &x  = 0x7fffcad31c4     (address of x)
  p   = 0x7fffcad31c4     (pointer stores address of x)
  *p  = 10                (value pointed to by p)

Passing &x to change_value():
  Inside change_value():
    parameter 'value' (the address passed) = 0x7fffcad31c4
    dereferencing *value before change      = 10
    dereferencing *value after change       = 100

Final state in main():
  x = 100

## Key takeaways
- `&x` gives the memory address of `x`.
- A pointer stores that address; `*p` reaches through the pointer to
  read/write `x` directly.
- Passing `&x` to a function lets that function permanently change `x`
  in the caller — this is how embedded drivers modify caller-owned
  buffers/structs without returning a copy.
- A pointer-to-pointer (`int **pp`) is how you pass a pointer by
  reference (e.g., so a function can reallocate or reassign what the
  caller's pointer points to).
- Always check for `NULL` before dereferencing — this is not optional
  in embedded/automotive code, where a bad pointer can crash the whole
  system instead of just one process.

## Embedded relevance
Memory-mapped registers, driver APIs, buffers, DMA descriptors, and
the fundamental fact that hardware is accessed through addresses, not
values — everything above is the foundation for register-level GPIO,
UART ring buffers, and driver interfaces used later in this portfolio.
