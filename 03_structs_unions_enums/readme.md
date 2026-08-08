# 03 — Structs, Unions, Enums

## What this shows
- `struct Point`: grouping related data into a single object.
- `enum Color`: naming constant values instead of using raw magic
  numbers (`0`, `1`, `2`).
- `union RawValue`: reading the exact same 4 bytes in memory as either
  a `float` or as 4 raw bytes — type punning.
- `struct Led`: a struct that embeds an enum and another struct, the
  kind of composite object used constantly in embedded configuration
  code (similar to `UART_Config_t` in earlier notes).

## Memory trace

sizeof(struct Point)       = 8 bytes    (two ints, 4 bytes each)
sizeof(union RawValue)     = 4 bytes    (union size = size of LARGEST member, not the sum)

rv.f     = 3.14
rv.bytes = 4 individual bytes that make up that same float in memory
           (exact hex values depend on your system's endianness)

## Key takeaways
- A `struct` allocates space for ALL its members, one after another
  (plus possible padding for alignment) — `sizeof` grows with each
  member you add.
- A `union` allocates space for only its LARGEST member — all members
  share the same memory address. Writing to one member and reading
  another is exactly how you "reinterpret" the same bytes differently.
- An `enum` is really just an `int` under the hood with named values,
  starting at 0 by default. Using enums instead of raw numbers makes
  code self-documenting and prevents invalid states in a `switch`.
- Combining struct + enum (`struct Led`) is the standard pattern for
  representing a peripheral or device's full configuration in one
  object, instead of passing 3-4 separate loose variables around.

## Embedded relevance
- `union` is exactly how raw sensor/ADC/UART byte data gets
  reinterpreted as an actual number (e.g., reading 2 raw bytes over
  I2C and reinterpreting them as a signed 16-bit temperature).
- `struct` groups peripheral registers (as in `GPIOA->MODER`,
  `GPIOA->ODR`) or a driver's configuration into one object, which is
  exactly the pattern used later in the UART/SPI driver projects.
- `enum` replaces magic numbers for peripheral states (e.g., a UART
  state enum: `UART_IDLE`, `UART_BUSY`, `UART_ERROR`) — this becomes
  central in the state-machine projects (Level 3).
