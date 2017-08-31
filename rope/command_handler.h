#ifndef TP1_TALLER_COMMAND_H
#define TP1_TALLER_COMMAND_H

#include <stdio.h>
#include "rope.h"
#include "connection_handler.h"

#define MAX_INPUT_LENGTH 500

typedef struct {
    ConnectionHandler *connection_handler;
    char input[MAX_INPUT_LENGTH];
    FILE *command_file;
} CommandHandler;


// Pre:  rope is a created Rope.
// Post: rope will be modified according to instructions received from a file,
//       or stdin if command_file is NULL, until end of file (ctrl + D).
void run(CommandHandler *command,
         ConnectionHandler *connection_handler,
         FILE *command_file);

#endif //TP1_TALLER_COMMAND_H
