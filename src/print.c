#include "global.h"
#include "print.h"
#include "types.h"
#include <stdio.h>
#include <time.h>

void echo(const char* argv[], argv_flag flag)
{
    if ((flag & INCLUDE_TIME) == INCLUDE_TIME) {
        const time_t current_time = time(NULL);
        const struct tm* lt = localtime(&current_time);

        fprintf(output, "[%d-%d-%d %d:%d:%d] ",
            lt->tm_year + 1900, lt->tm_mon + 1, lt->tm_mday,
            lt->tm_hour, lt->tm_min, lt->tm_sec);
    }

    if ((flag & FLAG_IGNORE_ESCAPE) == FLAG_IGNORE_ESCAPE) {
        escape_ignored_echo(argv);
    } else {
        escaped_echo(argv);
    }

    if ((flag & FLAG_NO_NEWLINE) != FLAG_NO_NEWLINE) {
        fputc('\n', output);
    }
}

void escape_ignored_echo(const char* argv[])
{
    for (int i = first_argv; i < last_argv; i++) {
        fputs(argv[i], output);

        // Add space between arguments except after the last one
        if (i != last_argv)
            putc(' ', output);
    }
}

void escaped_echo(const char* argv[])
{
    for (int i = first_argv; i < last_argv; i++) {
        for (int j = 0; argv[i][j] != '\0'; j++) {
            if (argv[i][j] == '\\' && argv[i][j + 1] != '\0') {
                switch (argv[i][j + 1]) {
                case 'n':
                    putc('\n', output);
                    j++;
                    break;
                case 't':
                    putc('\t', output);
                    j++;
                    break;
                case 'v':
                    putc('\v', output);
                    j++;
                    break;
                case 'b':
                    putc('\b', output);
                    j++;
                    break;
                case 'r':
                    putc('\r', output);
                    j++;
                    break;
                default:
                    putc('\\', output); // print the backslash
                    putc(argv[i][j + 1], output); // print the next character
                    j++;
                    break;
                }
            } else {
                putc(argv[i][j], output);
            }
        }

        // Add space between arguments except after the last one
        if (i < last_argv)
            putc(' ', output);
    }
}
