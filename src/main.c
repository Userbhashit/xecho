#include <stdio.h>
#include "parse.h"
#include "print.h"

int main(int argc, const char *argv[])
{
    // Parse command-line arguments to determine which flags are set
    argv_flag flag = get_flag(argc, argv);

    // Print the arguments according to the flags (handles -n, -e, etc.)
    echo(argc, argv, flag);

    // Reset to default color
    reset_color();

    return 0;
}

