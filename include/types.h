#ifndef TYPES_H  
#define TYPES_H

#include <stdio.h>
/*
 * Type representing a set of flags using a bitmask.
 * Each bit in the integer corresponds to a different command-line option.
 */
typedef unsigned int argv_flag;

/*
 * Bitmask flags for command-line options:
 *
 * FLAG_NONE          - No flags set (all bits = 0)
 * FLAG_NO_NEWLINE    - (bit 0) Option: -n
 *                      Prevents printing the trailing newline in output
 *
 * FLAG_IGNORE_ESCAPE - (bit 1) Option: -E
 *                      Prevents interpreting escape sequences like \n, \t
 */
#define FLAG_NONE          0
#define FLAG_NO_NEWLINE    (1 << 0)   // binary: 0001
#define FLAG_IGNORE_ESCAPE (1 << 1)   // binary: 0010

// ---------- Color definitions ----------

// ANSI escape codes for text colors in the terminal
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"

// Enum listing supported colors.
// `error` is used when no valid color is matched keeping everything default.
enum color 
{
    black,
    red,
    green,
    yellow,
    blue,
    magenta,
    cyan,
    error
};

/*
 * Struct that combines:
 *   - enum color value  : internal identifier for the color
 *   - const char *name  : command-line option (e.g., "--red")
 *   - const char *ansi_code : ANSI escape sequence for that color
 *
 */
struct ColorInfo {
    enum color value;
    const char *name;
    const char *ansi_code;
};

// Array and its size for all colors
extern struct ColorInfo colors[];  
extern size_t colors_count;

#endif  // End of header guard
