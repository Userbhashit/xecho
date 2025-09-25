#include <ctype.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "parse.h"
#include "types.h"
#include "global.h"

/*
 * get_flag
 * --------
 * Parse command-line arguments to detect flags and determine the index of
 * the first non-flag argument.
 *
 * Behavior:
 *   - Iterates over argv[], starting from argv[1].
 *   - Recognizes the following flags:
 *       -n    → FLAG_NO_NEWLINE
 *       -E    → FLAG_IGNORE_ESCAPE
 *       --time → INCLUDE_TIME
 *   - Stops parsing flags once a non-flag argument is found.
 *   - Allows setting a color if the argument matches a valid color.
 *   - Allows redirecting output to a file via "-o filename".
 *
 * Side effects:
 *   - Updates global variables first_argv, last_argv, and output.
 *   - Prints an error (in red) to stderr for unrecognized flags.
 *
 * Parameters:
 *   argc : number of arguments
 *   argv : array of argument strings
 *
 * Returns:
 *   argv_flag bitmask with recognized flags set.
 */
argv_flag get_flag(int argc, const char* argv[])
{
    argv_flag final_flag = FLAG_NONE;  // Start with no flags
    int color_set = 0;                 // Ensure only the first valid color is applied
    first_argv = 1;                    // Default: first argument after program name
    output = stdout;                   // Default output: stdout
    last_argv = argc;                  // Default: process all arguments

    // Loop through all arguments
    for (int i = 1; i < argc; i++)
    {
        // Stop flag parsing if the argument doesn’t start with '-'
        if (argv[i][0] != '-')
        {
            first_argv = i;
            break;
        }

        // Handle recognized flags
        switch (argv[i][1]) 
        {
            case 'n':
                final_flag |= FLAG_NO_NEWLINE;
                break;

            case 'E':
                final_flag |= FLAG_IGNORE_ESCAPE;
                break;

            case '-':
                if (strcmp(argv[i], "--time") == 0)
                {
                    final_flag |= INCLUDE_TIME;
                }

                // Try applying a color only once
                if (!color_set) 
                {
                    enum color argv_color = verify_color(argv[i]);
                    if (argv_color != error) 
                    {
                        set_color(argv_color);
                        color_set = 1;
                    } 
                }
                break;

            default:
                // Print unrecognized flag to stderr in red
                fprintf(stderr, "\033[31mError: %s is not a valid flag.\033[0m\n", argv[i]);
                break;
        }

        // Move first_argv to the argument after the last parsed flag
        first_argv = i + 1;
    }

    // Handle "-o filename" → redirect output
    if (argc >= 4 && strcmp(argv[argc-2], "-o") == 0)
    {
        output = fopen(argv[argc-1], "a");  // Append mode
        last_argv = argc - 2;              // Exclude "-o" and filename
    }

    return final_flag;
}

/*
 * verify_color
 * ------------
 * Check if the given string matches a valid color name.
 */
enum color verify_color(const char *color) 
{
    for (size_t i = 0; i < colors_count; i++) 
    {
        if (strcasecmp(color, colors[i].name) == 0) 
        {
            return colors[i].value;
        }
    }
    return error;
}

/*
 * set_color
 * ---------
 * Print the ANSI escape code for the given color to the output stream,
 * but only if the output is a terminal (not a file).
 */
void set_color(enum color c) 
{
    if (isatty(fileno(output)))
    {
        for (size_t i = 0; i < colors_count; i++) 
        {
            if (c == colors[i].value) 
            {
                fprintf(output, "%s", colors[i].ansi_code);
                return;
            }
        }
    }
}

/*
 * reset_color
 * -----------
 * Reset the terminal color back to default by printing the ANSI reset code,
 * but only if the output is a terminal.
 */
void reset_color(void)
{
    if (isatty(fileno(output)))
    {
        fprintf(output, "\033[0m");
    }
}
