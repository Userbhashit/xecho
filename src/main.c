#include "parse.h"
#include "print.h"

int main(int argc, const char *argv[])
{
    // Index of the first argument that is not a flag
    int first_argv = 1;

    // Parse command-line arguments to determine which flags are set
    argv_flag flag = get_flag(argc, argv, &first_argv);

    // Print the arguments according to the flags (handles -n, -e, etc.)
    echo(argc, argv, flag, first_argv);

    // reset to default color
    reset_color();

    return 0;
}

