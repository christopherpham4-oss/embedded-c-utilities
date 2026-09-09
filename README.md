# Embedded C Memory and Data Conversion Utilities

Bare-metal C implementations of memory manipulation and integer/ASCII conversion
routines, written without the C standard library. Builds for both a host machine
(GCC) and the TI MSP432P401R (arm-none-eabi-gcc) from the same source tree.

Originally written for the University of Colorado Boulder *Introduction to
Embedded Systems Software and Development Environments* course.

**Attribution.** `src/memory.c` (the `my_*` functions), `src/data.c`,
`src/stats.c`, `src/main.c`, and `include/common/stats.h` are mine, along with
the `PLATFORM` handling in the `Makefile` and `sources.mk`. The test harness
(`src/course1.c`, `include/common/course1.h`), `include/common/memory.h`, the
MSP432 board support files, linker script, and CMSIS headers are course material
by Alex Fosdick / University of Colorado and retain their original copyright.

## What's here

### `src/memory.c` — memory manipulation

| Function | Description |
|---|---|
| `my_memmove(src, dst, length)` | Byte move that stays correct when source and destination overlap |
| `my_memcopy(src, dst, length)` | Byte copy, no overlap handling |
| `my_memset(src, length, value)` | Fill a region with a given byte |
| `my_memzero(src, length)` | Zero a region |
| `my_reverse(src, length)` | Reverse a byte sequence in place |
| `reserve_words(length)` | Dynamically allocate a block of 32-bit words |
| `free_words(src)` | Release a block from `reserve_words` |

`my_memmove` is the interesting one. When the destination overlaps the source
from above, a forward byte-by-byte copy overwrites bytes it hasn't read yet, so
the copy direction is chosen from the pointer comparison before any bytes move.

### `src/data.c` — integer and ASCII conversion

| Function | Description |
|---|---|
| `my_itoa(data, ptr, base)` | Signed integer to ASCII string, bases 2-16, returns length |
| `my_atoi(ptr, digits, base)` | ASCII string to signed 32-bit integer, bases 2-16 |

Both handle negative values and operate on caller-supplied buffers. No
`stdio.h`, no `stdlib.h` conversion helpers.

### `src/stats.c` — statistics library

Minimum, maximum, mean, and median over an array of unsigned bytes, plus a
descending sort. Printing is wrapped in compile-time `PRINTF` / `VERBOSE`
macros so debug output compiles out of release builds entirely rather than
sitting behind a runtime flag.

## Building

Host build and run:

```
make build PLATFORM=HOST
./c1final.out
```

MSP432 cross-compile:

```
make build PLATFORM=MSP432
```

Both produce `c1final.out` plus a `c1final.map` linker map. The `Makefile` and
`sources.mk` select the compiler, architecture flags, and linker script from the
`PLATFORM` variable, so the same sources produce a native executable or an ARM
Cortex-M4 image with no source changes.

Compiled with `-Wall -Werror -std=c99`, so the build fails on any warning.
Debug output is gated behind the `VERBOSE` define: without it the `PRINTF`
statements are removed by the preprocessor rather than skipped at runtime, so
release builds carry no printing code at all.

Useful targets:

```
make compile-all PLATFORM=HOST    # compile without linking
make <file>.i                     # preprocessed output
make <file>.asm                   # generated assembly
make clean
```

## Verification

The host build runs a test suite covering `my_memmove` (non-overlapping, source
end overlapping destination start, and destination end overlapping source
start), `my_memcopy`, `my_memset`, `my_memzero`, `my_reverse`, and round-trip
`my_itoa` / `my_atoi` conversion on both negative and positive values. All 8
tests pass on the host, and the MSP432 target cross-compiles and links cleanly
against the device linker script.

On the MSP432 build, `.text` is placed in flash from low addresses while `.data`
and `.bss` land at 0x20000000 in SRAM, which the section sizes in the build
output show directly.

## Toolchain

- GCC (host) — developed on Ubuntu 22.04 under WSL2
- `arm-none-eabi-gcc` (MSP432)
- GNU Make

## Notes

Build output was analyzed against the MSP432 linker script to classify symbols
by memory segment, access permission, and lifetime — where each variable lands
in flash versus RAM, and why.
