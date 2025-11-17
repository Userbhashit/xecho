#ifndef REPL_H
#define REPL_H

#include <stdio.h>

#define max_char 1024

typedef struct history {
    int size;
    char command[max_char];
    struct history* previous;
    struct history* next;
} history;

void start_repl(void);
void delete_history(history* last_command);

#endif
