#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdio.h>

/*
 * This header declares global variables that are shared across
 * multiple source files in the project. 
 *
 * - first_argv : index of the first argument (for parsing)
 * - last_argv  : index of the last argument
 * - output     : file stream where output will be written 
 *                (can be stdout, stderr, or an opened file)
 *
 * The variables are declared with 'extern' so that:
 *   - Every .c file that includes this header can access them.
 *   - The actual storage is defined only once in global.c.
 */

extern int first_argv;
extern int last_argv;
extern FILE* output;

#endif
