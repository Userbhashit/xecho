#ifndef PRINT_H
#define PRINT_H

#include <stdio.h>
#include "types.h"

// Print all arguments according to the specified flags.
// - Handles all xecho flags like -n (no newline), -e (escape sequences), etc.
// - argc: total number of command-line arguments
// - argv: array of command-line arguments
// - flag: bitmask of all flags detected
// - first_argv: index of the first argument that is not a flag
void echo(int argc, const char* argv[], argv_flag flag);

// Print arguments without interpreting escape sequences (\n, \t, etc.).
// Used when the -E or ignore-escape flag is active.
void escape_ignored_echo(int argc, const char* argv[]);

// Print arguments while interpreting escape sequences (\n, \t, etc.).
// Used when the -e or escape flag is active.
void escaped_echo(int argc, const char* argv[]);

#endif
