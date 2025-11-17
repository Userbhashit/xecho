#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdio.h>

/*
 * - first_argv : index of the first argument (for parsing)
 * - last_argv  : index of the last argument
 * - output     : file stream where output will be written
 *                (can be stdout, stderr, or an opened file)
 */

extern int first_argv;
extern int last_argv;
extern FILE* output;

#endif
