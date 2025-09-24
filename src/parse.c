#include <string.h>
#include <stdio.h>
#include "parse.h"
#include "types.h"

/*
 * Parse command-line arguments to detect flags and determine the first non-flag argument.
 *
 * This function loops through argv starting from index 1 (skipping program name)
 * and sets bits in a bitmask for each recognized flag:
 *   - FLAG_NO_NEWLINE    (-n)
 *   - FLAG_IGNORE_ESCAPE (-E)
 *
 * Unrecognized flags are printed as errors to stderr in red.
 */
argv_flag get_flag(int argc, const char* argv[], int* first_argv)
{
    argv_flag final_flag = FLAG_NONE;  // Initialize flags to none
    *first_argv = 1;                   // Default first argument index
    int color_set = 0;                 // Bool flag for color only first color will be applied

    // Loop through command-line arguments starting from argv[1]
    for (int i = 1; i < argc; i++)
    {
        // Stop parsing flags at the first argument that does not start with '-'
        if (argv[i][0] != '-')
        {
            *first_argv = i;
            break;
        }

        // Detect which flag is set and update the bitmask
        switch (argv[i][1]) 
        {
            case 'n':
                final_flag |= FLAG_NO_NEWLINE;   // Set -n flag
                break;
            case 'E':
                final_flag |= FLAG_IGNORE_ESCAPE; // Set -E flag
                break;
            case '-':
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
                // Print unrecognized flag as red error message to stderr
                fprintf(stderr, "\033[31mError: %s is not a valid flag.\033[0m\n", argv[i]);
                break;
        }

        // Update first_argv to point past the last flag
        *first_argv = i + 1;
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
    for (size_t i = 0; i < colors_count; i++) 
    {
        if (c == colors[i].value) 
        {
            printf(colors[i].ansi_code);
            return;
        }
    }
}

void reset_color (void)
{
    printf("\033[0m");
}