# 06 — static vs global scope

## What this shows
- A `static` global variable (`counter` in file1.c): only visible
  inside file1.c, invisible to every other file — even with `extern`.
- A plain global variable (`total`): visible across files using
  `extern`, demonstrated by modifying it from file2.c and reading the
  change back in main.c.
- A `static` variable INSIDE a function (`call_count` in
  `call_tracker`): initialized once, then keeps its value between
  calls — unlike a normal local variable, which resets every call.

## Memory trace

counter (file-scope static in file1.c) = 1, 2, 3   (only file1.c can touch it)
total   (global, external linkage)     = 100 -> 150 (modified from file2.c, seen in main.c)

call_tracker() call 1 -> call_count = 1
call_tracker() call 2 -> call_count = 2
call_tracker() call 3 -> call_count = 3
(a normal local `int call_count = 0;` would print 1, 1, 1 every time)

## Key takeaways
- `static` at file scope = "private to this .c file." It restricts
  LINKAGE, not lifetime — the variable still exists for the whole
  program's life, but no other file can reference it, even with a
  matching `extern` declaration (that would be a linker error).
- A plain global (no `static`) has external linkage by default — any
  other file can access it via `extern`, which is powerful but risky:
  it's very easy to lose track of who modifies a global from where.
- `static` INSIDE a function changes LIFETIME, not linkage: the
  variable is created once (before `main` even runs) and keeps its
  value across every call to that function, instead of being
  destroyed and recreated each time like a normal local variable.
- These are two different meanings of the same keyword depending on
  where it's used — a very common interview question.

## Embedded relevance
- File-scope `static` is exactly how driver internal state is hidden,
  e.g. `static UART_Config_t uart_config;` inside `uart_driver.c` —
  other files can only touch it through the driver's public functions
  (`UART_Init()`, `UART_Send()`), never directly. This is the C
  equivalent of "private" data in encapsulation.
- Function-local `static` is the standard way to implement a counter,
  a state-tracking flag, or a ring-buffer index that must persist
  between interrupt calls without using a global variable that the
  rest of the program could accidentally overwrite.
