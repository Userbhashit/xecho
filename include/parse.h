#ifndef PARSE_H
#define PARSE_H

#include "types.h"

/*
 * Parse command-line arguments to detect flags and determine the first non-flag argument.
 *
* Notes:
 *   - Only recognized flags that are set in the bitmask.
 *   - Unrecognized flags will be printed as an error.
 */
argv_flag get_flag(int argc, const char* argv[], int* first_argv);

/*
* Functions to: 
* - Verify the color
* - Set the color
* - Fucntion to rest the terminal default color called at end of main()
*/
enum color verify_color (const char* color);
void set_color(enum color c);
void reset_color (void);

#endif
