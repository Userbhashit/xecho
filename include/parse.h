#ifndef PARSE_H
#define PARSE_H

#include <stdio.h>

/*
 * Type representing a set of flags using a bitmask.
 * Each bit corresponds to a specific command-line option.
 */
typedef unsigned int argv_flag;

/*
 * Bitmask flags for command-line options:
 *   FLAG_NONE         - No flags set
 *   FLAG_NO_NEWLINE   - -n : Do not print the trailing newline
 *   FLAG_IGNORE_ESCAPE- -E : Do not interpret escape sequences (\n, \t, etc.)
 */
#define FLAG_NONE          0
#define FLAG_NO_NEWLINE    (1 << 0)
#define FLAG_IGNORE_ESCAPE (1 << 1)

/*
 * Parse command-line arguments to detect flags and determine the first non-flag argument.
 *
* Notes:
 *   - Only recognized flags that are set in the bitmask.
 *   - Unrecognized flags should be handled separately by the caller (or print an error).
 */
argv_flag get_flag(int argc, char* argv[], int* first_argv);

#endif
