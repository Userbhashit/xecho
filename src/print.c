#include <stdio.h>
#include "print.h"
#include "parse.h"

/*
 * Main echo function that prints arguments based on the provided flags.
 * - If FLAG_IGNORE_ESCAPE is set, prints arguments without interpreting escape sequences.
 * - Otherwise, interprets escape sequences like \n, \t, etc.
 * - Adds a newline at the end unless FLAG_NO_NEWLINE is set.
 */
void echo(int argc, const char* argv[], argv_flag flag, int first_argv)
{
    if ((flag & FLAG_IGNORE_ESCAPE) == FLAG_IGNORE_ESCAPE)
    {
        escape_ignored_echo(argc, argv, first_argv);
    } 
    else 
    {
        escaped_echo(argc, argv, first_argv);
    }

    // Print newline unless FLAG_NO_NEWLINE is set
    if ((flag & FLAG_NO_NEWLINE) != FLAG_NO_NEWLINE)
    {
        printf("\n");
    }
}

/*
 * Print all arguments exactly as they are, without interpreting any escape sequences.
 *
 * Parameters:
 *  argc       - Total number of command-line arguments
 *  argv       - Array of command-line argument strings
 *  first_argv - Index of the first argument that is not a flag
 */
void escape_ignored_echo(int argc, const char* argv[], int first_argv)
{
    for (int i = first_argv; i < argc; i++)
    {
        for (int j = 0; argv[i][j] != '\0'; j++)
        {
            putchar(argv[i][j]);
        }
    }
}

/*
 * Print all arguments while interpreting common escape sequences:
 *  - \n : newline
 *  - \t : horizontal tab
 *  - \v : vertical tab
 *  - \b : backspace
 *  - \r : carriage return
 * Any unrecognized escape sequence is printed as-is (\<char>).
 * Spaces are added between arguments.
 *
 * Parameters:
 *  argc       - Total number of command-line arguments
 *  argv       - Array of command-line argument strings
 *  first_argv - Index of the first argument that is not a flag
 */
void escaped_echo(int argc, const char* argv[], int first_argv)
{
    for (int i = first_argv; i < argc; i++) 
    {
        for (int j = 0; argv[i][j] != '\0'; j++)
        {
            if (argv[i][j] == '\\' && argv[i][j+1] != '\0')
            {
                switch (argv[i][j+1]) 
                {
                    case 'n': putchar('\n'); j++; break;
                    case 't': putchar('\t'); j++; break;
                    case 'v': putchar('\v'); j++; break;
                    case 'b': putchar('\b'); j++; break;
                    case 'r': putchar('\r'); j++; break;
                    default:
                        putchar('\\');             // print the backslash
                        putchar(argv[i][j+1]);    // print the next character
                        j++;
                        break;
                }
            }
            else 
            {
                putchar(argv[i][j]);
            }
        }

        // Add space between arguments except after the last one
        if (i < argc - 1)
            putchar(' ');
    }
}
