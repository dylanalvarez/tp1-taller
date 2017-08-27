#ifndef TP1_TALLER_COMMAND_H
#define TP1_TALLER_COMMAND_H

#include "rope.h"

#define MAX_INPUT_LENGTH 500

typedef struct {
    Rope *rope;
    char input[MAX_INPUT_LENGTH];
} CommandHandler;

void run(CommandHandler *command, Rope *rope);

#endif //TP1_TALLER_COMMAND_H
