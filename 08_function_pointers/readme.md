# 08 — Function Pointers

## What this shows
- A basic function pointer type (`MathFunc`) and an array of function
  pointers selected by an `enum` index — a lightweight "dispatch
  table" instead of an if/else or switch chain.
- Passing a function pointer as a callback into `for_each()`, so the
  SAME loop can perform different actions depending on what's passed
  in — behavior injected at call time, not hardcoded.
- A custom `bubble_sort()` that takes a comparator function pointer,
  so sort direction (ascending/descending) is chosen at runtime — the
  same pattern the standard library's `qsort()` uses internally.

## What's happening under the hood

    typedef int (*MathFunc)(int, int);

`MathFunc` is a variable TYPE that can hold the ADDRESS of any
function matching that exact signature: takes `(int, int)`, returns
`int`. Assigning `operations[0] = add;` doesn't call `add` — it
stores add's address. Calling `operations[0](6, 3)` is what actually
jumps to that address and executes it.

## Key takeaways
- A function pointer stores the ADDRESS of a function, the same way a
  normal pointer stores the address of a variable — you can pass it
  around, store it in arrays/structs, and call through it.
- Using an array of function pointers indexed by an enum
  (`operations[OP_ADD]`) replaces a `switch` statement with a single
  array lookup — this scales much better when the number of cases
  grows (e.g., 20 command types instead of 3).
- Passing a function pointer as an argument (`for_each(..., callback)`)
  is how C achieves what other languages call "callbacks" or "higher
  order functions" — the loop logic and the action performed inside
  the loop are fully decoupled.
- This is the exact mechanism behind `qsort()` in the standard
  library: you provide the data and a comparator function pointer,
  the library provides the sorting algorithm.

## Embedded relevance
- Interrupt handlers are frequently registered as function pointers:
  a peripheral driver lets you assign a callback function that gets
  called automatically when data arrives (e.g., `UART_SetRxCallback
  (my_handler)`), instead of the driver needing to know your
  application code in advance.
- A "driver interface" pattern uses a struct of function pointers to
  represent a generic device (e.g. `Sensor_t` with `.init`, `.read`
  as function pointers) — this is exactly how you'd unify an I2C
  sensor and an SPI sensor behind one common API in a later project.
- State machines (Level 3 project) use an array of function pointers
  indexed by state, so transitioning state is just "call
  state_handlers[current_state]()" instead of a giant switch.
