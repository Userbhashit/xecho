#include <ctype.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "parse.h"
#include "types.h"
#include "global.h"

/*
 * Side effects:
 *   - Updates global variables first_argv, last_argv, and output.
 *   - Prints an error (in red) to stderr for unrecognized flags.
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

    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] != '-')
        {
            first_argv = i;
            break;
        }

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
                fprintf(stderr, "\033[31mError: %s is not a valid flag.\033[0m\n", argv[i]);
                break;
        }

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

void reset_color()
{
    if (isatty(fileno(output)))
    {
        fprintf(output, "\033[0m");
    }
}
