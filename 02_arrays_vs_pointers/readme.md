# 02 — Arrays vs Pointers

## What this shows
- The same sum computed two ways: array indexing (`arr[i]`) vs pointer
  arithmetic (`*(arr + i)`), proving they compile to the same access
  pattern.
- The "array decay" problem: `sizeof` gives a different, wrong answer
  once an array is passed into a function.
- Explicit proof that `numbers[i]` and `*(numbers + i)` point to the
  exact same address.

## Memory trace

sizeof(numbers) inside main()      = 20 bytes  (5 ints x 4 bytes — the WHOLE array)
sizeof(arr) inside a function      = 8 bytes   (just a pointer, on a 64-bit system)

numbers[0] = 10 | *(numbers + 0) = 10 | same address
numbers[1] = 20 | *(numbers + 1) = 20 | same address
...

## Key takeaways
- An array name, when passed to a function, "decays" into a pointer to
  its first element. The function never receives the array itself or
  its true size — only an address.
- This is why you must ALWAYS pass the length explicitly alongside an
  array parameter in C (`sum_with_indexing(arr, len)`) — the function
  has no way to know where the array ends otherwise.
- `arr[i]` is literally syntactic sugar for `*(arr + i)`. The compiler
  generates identical code for both — indexing is not "safer" or
  "slower," it's the same operation written differently.
- Forgetting the decay rule is a classic embedded bug source: e.g.
  calling `sizeof(buffer) / sizeof(buffer[0])` to count array elements
  works fine in the file where the array is defined, but silently
  breaks (returns 1 or 2 instead of the real count) if you move that
  calculation inside a function that only received a pointer.

## Embedded relevance
Peripheral buffers, DMA transfer arrays, and UART/SPI ring buffers are
almost always passed around as `pointer + length` pairs for exactly
this reason. Understanding decay now prevents a very common class of
"my buffer size calculation is wrong" bugs later, when the compiler
won't warn you and the mistake only shows up as corrupted data at
runtime.
