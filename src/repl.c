#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#include "repl.h"

void start_repl(void)
{
    struct termios oldt, newt;

    // Save old terminal settings
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    // Turn off canonical and echo mode and apply new settings
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // Start with empty history
    history* current = NULL;

    char c;
    
    // Index for the command and command buffer
    int index = 0;
    char commands[max_char];

    printf("\r");
    while (1) {
        printf("Xecho > ");
        fflush(stdout);


        if (current == NULL) {
            current = malloc(sizeof(history));

            if (!current) {
                perror("malloc failed");
                tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
                exit(1);
            }

            current->previous = NULL;
            current->next = NULL;
        } else {
            history* temp = malloc(sizeof(history));

            if (!temp) {
                perror("malloc failed");
                tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
                exit(1);
            }
            temp->previous = current;
            temp->next = NULL;

            current->next = temp;
            current = temp;
        }

        memset(commands, '\0', sizeof(commands));
        index = 0;

        history* ptr = current;

        while (1) {
            c = getchar();

            if (c == '\n') {
                commands[index] = '\0';
                break;
            }
            
            if (c == '\x1b') {
                char c1 = getchar();
                char c2 = getchar();

                if (c1 == '[') {
                    

                    switch (c2) {
                    case 'A':
                        if (!ptr || !ptr->previous) continue;

                        ptr = ptr->previous;
                        snprintf(commands, sizeof(commands), "%s", ptr->command);
                        index = ptr->size;

                        printf("\r\033[KXecho > %s", ptr->command);
                        fflush(stdout);

                        break;
                    case 'B':
                        if (!ptr || !ptr->next) continue;

                        ptr = ptr->next;
                        snprintf(commands, sizeof(commands), "%s", ptr->command);
                        index = ptr->size;

                        printf("\r\033[KXecho > %s", ptr->command);
                        fflush(stdout);

                        break;
                    }
                }

                continue;
            }

            printf("%c", c);

            if (index < max_char - 1) {
                commands[index++] = c;
                commands[index] = '\0';
            }

        }

        if (strcmp(commands, "q") == 0 || strcmp(commands, "quit") == 0)
            break;

        strcpy(current->command, commands);
        current->size = index;
        printf("\n%s\n", commands);
        fflush(stdout);
    }

    printf("\n");
    delete_history(current);

    // Apply old settings back to terminal when proggram ends
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    exit(0);
}

void delete_history (history* last_command)
{
    while (last_command) {
        history* prev = last_command->previous;
        free(last_command); 
        last_command = prev;
    }
}
