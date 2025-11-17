#ifndef TYPES_H
#define TYPES_H

#include <stdio.h>

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
 *
 * INCLUDE_TIME       - (bit 2) Option: --time
 */
#define FLAG_NONE 0
#define FLAG_NO_NEWLINE (1 << 0)
#define FLAG_IGNORE_ESCAPE (1 << 1)
#define INCLUDE_TIME (1 << 2)

#define BLACK "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"

enum color {
    black,
    red,
    green,
    yellow,
    blue,
    magenta,
    cyan,
    error
};

struct ColorInfo {
    enum color value;
    const char* name;
    const char* ansi_code;
};

extern struct ColorInfo colors[];
extern size_t colors_count;

#endif
