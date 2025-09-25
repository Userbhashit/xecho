#ifndef PARSE_H
#define PARSE_H

#include "types.h"

/*
 * Parse command-line arguments to detect flags and determine
 * the index of the first non-flag argument.
 *
 * Parameters:
 *   - argc : argument count from main()
 *   - argv : argument vector from main()
 *
 * Returns:
 *   - an argv_flag bitmask indicating which flags are active
 */
argv_flag get_flag(int argc, const char* argv[]);

// Verify whether a given string corresponds to a valid color.
enum color verify_color(const char* color);

/*
 * Apply a color to the output stream by printing the corresponding
 * ANSI escape sequence.
 *
 * Parameters:
 *   - c : a value from enum color
 */
void set_color(enum color c);

/*
 * Reset the output stream to the terminal's default color.
 * This should usually be called at the end of main() to avoid
 * leaving the terminal in a colored state.
 */
void reset_color(void);

#endif
