#ifndef PRINT_H
#define PRINT_H

#include "types.h"

void echo(const char* argv[], argv_flag flag);
void escape_ignored_echo(const char* argv[]);
void escaped_echo(const char* argv[]);

#endif
