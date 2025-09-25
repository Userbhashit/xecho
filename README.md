# xecho

xecho is a small, modern reimplementation of the Unix `echo` command with a few niceties:

- Extended flags: `-n`, `-E`, `--time`
- Simple ANSI color support via long options like `--red`, `--green`, ...
- Optional file output with `-o <file>` (appends)

The codebase is C99, built with CMake.

## Build

Requirements:

- CMake ≥ 3.15
- A C compiler (clang or gcc) with C99 support

Steps:

```bash
cmake -S . -B build
cmake --build build --config Release
```

The binary will be placed in `build/xecho`.

## Usage

Basic usage mirrors `echo`:

```bash
./build/xecho hello world
```

Flags:

- `-n`: Do not output the trailing newline
- `-E`: Print arguments literally (do not interpret escapes like `\n`, `\t`)
- `--time`: Prefix output with a local timestamp `[YYYY-M-D H:M:S]`
- Colors: `--black | --red | --green | --yellow | --blue | --magenta | --cyan`
- Output file: `-o <filename>` (appends to file; excluded from printed args)

Notes:

- Color codes are only emitted when the output is a terminal (TTY). If redirected to a file, color codes are suppressed.
- Escapes interpreted when `-E` is NOT set: `\n`, `\t`, `\v`, `\b`, `\r`. Others are passed through as `\\<char>`.
- Color (if provided) is applied once to the whole output and reset at the end when writing to a terminal.

### Examples

```bash
# Plain output
./build/xecho hello world

# No trailing newline
./build/xecho -n "no newline"

# Ignore escapes
./build/xecho -E "line1\nline2"

# Interpret common escapes
./build/xecho "line1\nline2"

# Add timestamp
./build/xecho --time "timed message"

# Add color (to terminal only)
./build/xecho --green "success"

# Append output to a file (no color codes are written)
./build/xecho --time "logged" -o out.log
```

## Development

- Source lives in `src/`, public headers in `include/`.
- Global argument/output state is shared via `include/global.h`.
- Flags are parsed in `src/parse.c`; printing logic is in `src/print.c`.
- Color metadata resides in `src/types.c` / `include/types.h`.

Re-configure after adding new source files (CMake auto-discovers `src/*.c` on re-run):

```bash
cmake -S . -B build && cmake --build build
```