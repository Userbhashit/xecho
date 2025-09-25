#include <time.h>
#include <stdio.h>
#include "print.h"
#include "types.h"
#include "global.h"

/*
 * echo
 * ----
 * Main echo function that prints command-line arguments according to
 * the specified flags.
 *
 * Behavior:
 *   - If INCLUDE_TIME flag is set, prints the current timestamp before arguments.
 *   - If FLAG_IGNORE_ESCAPE is set, prints arguments literally without interpreting escape sequences.
 *   - Otherwise, interprets common escape sequences (\n, \t, \v, \b, \r).
 *   - Adds a newline at the end unless FLAG_NO_NEWLINE is set.
 *
 * Parameters:
 *   argc : total number of command-line arguments
 *   argv : array of argument strings
 *   flag : bitmask of argv_flag flags set by get_flag()
 */
void echo(int argc, const char* argv[], argv_flag flag)
{
    if ((flag & INCLUDE_TIME) == INCLUDE_TIME)
    {
        time_t current_time = time(NULL);
        struct tm *lt = localtime(&current_time);

        fprintf(output, "[%d-%d-%d %d:%d:%d] ",
                lt->tm_year + 1900, lt->tm_mon + 1, lt->tm_mday,
                lt->tm_hour, lt->tm_min, lt->tm_sec);
    }

    if ((flag & FLAG_IGNORE_ESCAPE) == FLAG_IGNORE_ESCAPE)
    {
        escape_ignored_echo(argc, argv);
    } 
    else 
    {
        escaped_echo(argc, argv);
    }

    // Print newline unless FLAG_NO_NEWLINE is set
    if ((flag & FLAG_NO_NEWLINE) != FLAG_NO_NEWLINE)
    {
        fputc('\n', output);
    }
}

/*
 * escape_ignored_echo
 * ------------------
 * Prints all arguments exactly as they are, without interpreting escape sequences.
 *
 * Parameters:
 *   argc       - total number of command-line arguments
 *   argv       - array of argument strings
 *
 * Side effects:
 *   Uses global variables first_argv and last_argv to determine which
 *   arguments to print.
 */
void escape_ignored_echo(int argc, const char* argv[])
{
    for (int i = first_argv; i < last_argv; i++)
    {
        fputs(argv[i], output);

        // Add space between arguments except after the last one
        if (i != argc - 1) 
            putc(' ', output);
    }
}

/*
 * escaped_echo
 * ------------
 * Prints arguments while interpreting common escape sequences:
 *   - \n : newline
 *   - \t : horizontal tab
 *   - \v : vertical tab
 *   - \b : backspace
 *   - \r : carriage return
 * Any unrecognized escape sequence is printed as-is (\<char>).
 * Spaces are added between arguments.
 *
 * Parameters:
 *   argc       - total number of command-line arguments
 *   argv       - array of argument strings
 *
 * Side effects:
 *   Uses global variables first_argv and last_argv to determine which
 *   arguments to print.
 */
void escaped_echo(int argc, const char* argv[])
{
    for (int i = first_argv; i < last_argv; i++) 
    {
        for (int j = 0; argv[i][j] != '\0'; j++)
        {
            if (argv[i][j] == '\\' && argv[i][j+1] != '\0')
            {
                switch (argv[i][j+1]) 
                {
                    case 'n': putc('\n', output); j++; break;
                    case 't': putc('\t', output); j++; break;
                    case 'v': putc('\v', output); j++; break;
                    case 'b': putc('\b', output); j++; break;
                    case 'r': putc('\r', output); j++; break;
                    default:
                        putc('\\', output);             // print the backslash
                        putc(argv[i][j+1], output);    // print the next character
                        j++;
                        break;
                }
            }
            else 
            {
                putc(argv[i][j], output);
            }
        }

        // Add space between arguments except after the last one
        if (i < argc - 1)
            putc(' ', output);
    }
}
