#ifndef PARSE_H
#define PARSE_H

#include "types.h"

argv_flag get_flag(int argc, const char* argv[]);
enum color verify_color(const char* color);
void set_color(enum color c);
void reset_color(void);

#endif
