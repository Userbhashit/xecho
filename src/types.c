#include "types.h"

/*
 * An array `colors[]` is defined for lookup purposes.
 * This allows mapping between command-line arguments and ANSI codes.
 */
struct ColorInfo colors[] = {
    {black,   "--black",   BLACK},
    {red,     "--red",     RED},
    {green,   "--green",   GREEN},
    {yellow,  "--yellow",  YELLOW},
    {blue,    "--blue",    BLUE},
    {magenta, "--magenta", MAGENTA},
    {cyan,    "--cyan",    CYAN}
};

// Colors count
size_t colors_count = sizeof(colors) / sizeof(colors[0]);