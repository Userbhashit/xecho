#include "global.h"
#include <stdio.h>

/*
 * This file provides the actual definitions of the global variables
 * declared in global.h. 
 *
 * Defining them here ensures there is exactly one storage location
 * for each variable, avoiding multiple-definition linker errors.
 */

int first_argv = 0;   // default: start argument index = 0
int last_argv = 0;    // default: last argument index = 0
FILE* output = NULL;  // default: no output file (set later, usually stdout)
