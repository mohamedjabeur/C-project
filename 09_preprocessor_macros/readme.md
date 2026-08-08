# 09 — Preprocessor & Macros

## What this shows
- An object-like macro (`MAX_BUFFER_SIZE`) — a named constant, purely
  text substitution before compilation even starts.
- A function-like macro (`MIN`/`MAX`) — and the classic bug that
  happens when you pass an expression with side effects (`x++`) into
  one, because macros substitute TEXT, they don't evaluate arguments
  like real functions.
- A register-address-style macro, exactly matching the pattern used
  to define peripheral register addresses in embedded code
  (`GPIOA_ODR`).
- Conditional compilation (`#if DEBUG ... #endif`) — code that either
  exists or doesn't exist in the final binary, decided at compile
  time, not at runtime.

## The MIN(x++, y++) bug, expanded by hand

    MIN(x++, y++)

expands literally to:

    ((x++) < (y++) ? (x++) : (y++))

Notice `x++` and `y++` each appear TWICE in the expanded text. Since
one of them is inside the condition AND inside the branch that gets
returned, that variable gets incremented twice instead of once — a
bug that's invisible just by reading the macro call, and only obvious
once you mentally expand it.

## Key takeaways
- Macros are handled by the PREPROCESSOR, a separate pass that runs
  BEFORE the compiler even sees real C syntax. It performs pure
  text substitution — it has no concept of types, evaluation order,
  or "evaluate once."
- A real function evaluates its arguments once, then passes the
  result. A macro copy-pastes the argument text everywhere it appears
  in the macro body — this is the root cause of the `x++`/`y++` bug.
- Always wrap macro parameters (and the whole macro body) in
  parentheses — `((a) < (b) ? (a) : (b))` not `a < b ? a : b` —
  otherwise operator precedence can silently break the macro when
  called with an expression instead of a plain variable.
- `#if DEBUG` / `#endif` code doesn't even exist in the compiled
  binary when the condition is false — unlike an `if (DEBUG)` at
  runtime, which still compiles both branches and costs a runtime
  check.

## Embedded relevance
- Every register-level embedded project defines peripheral addresses
  exactly like `GPIOA_ODR` above — this is precisely how vendor
  header files (`stm32f4xx.h` etc.) define hardware addresses.
- `#ifdef DEBUG` / `#ifdef BOARD_REV_A` style conditional compilation
  is the standard way to build the SAME source code differently for
  different hardware revisions, or to strip out debug logging
  entirely from a production/release binary to save flash space.
- Because embedded code often uses macros instead of inline functions
  for tiny operations (to guarantee zero function-call overhead), you
  need to know exactly when a macro's text-substitution behavior can
  bite you — this is a real bug class, not just a trivia question.
