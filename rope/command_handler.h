#ifndef TP1_TALLER_COMMAND_H
#define TP1_TALLER_COMMAND_H

#include "rope.h"

#define MAX_INPUT_LENGTH 500

typedef struct {
    Rope *rope;
    char input[MAX_INPUT_LENGTH];
} CommandHandler;


// Pre:  rope is a created Rope.
// Post: rope will be modified according to received instruction until a print
//       instruction is received.
void run(CommandHandler *command, Rope *rope);

#endif //TP1_TALLER_COMMAND_H
