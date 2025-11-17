#include "parse.h"
#include "print.h"
#include "types.h"

int main(const int argc, const char* argv[])
{
    // Parse command-line arguments to determine which flags are set
    const argv_flag flags = get_flag(argc, argv);

    // // Print the arguments according to the flags (handles -n, -e, etc.)
    echo(argv, flags);

    // // Reset to default color
    reset_color();

    return 0;
}
