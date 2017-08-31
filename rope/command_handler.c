#include <stdio.h>
#include <string.h>

#include "command_handler.h"

#define EXIT 0
#define RETRY 1
#define MAX_COMMAND_LENGTH 10

#define INSERT_OPCODE 1
#define DELETE_OPCODE 2
#define SPACE_OPCODE 3
#define NEWLINE_OPCODE 4
#define PRINT_OPCODE 5

static void _printCustomError(char *message) {
    printf("Error: %s.\n", message);
}

static void _printGenericError() {
    _printCustomError("Invalid command");
}

static int _lengthExceptForSpaces(char *input) {
    int length = 0;
    for (int i = 0; i < strlen(input); i++) {
        if (input[i] != ' ') {
            length++;
        }
    }
    return length;
}

static int _getInput(CommandHandler *self) {
    char *could_read;

    if (self->command_file) {
        could_read = fgets(self->input, MAX_INPUT_LENGTH, self->command_file);
    } else {
        could_read = fgets(self->input, MAX_INPUT_LENGTH, stdin);
    }

    if (!could_read) {
        self->input[0] = 0;
        return EXIT;
    }

    size_t input_length = strlen(self->input);
    char last_character = self->input[input_length - 1];
    bool commandIsEmpty = _lengthExceptForSpaces(self->input) <= strlen("\n\0");

    if (last_character != '\n') {
        _printCustomError("Command length greater than expected");
        return RETRY;
    }
    if (commandIsEmpty) {
        return RETRY;
    }

    self->input[input_length - 1] = 0;
    return EXIT;
}

static void _getValidInput(CommandHandler *self) {
    int status;
    do {
        status = _getInput(self);
    } while (status == RETRY);
}

static void _processInsert(CommandHandler *self, char *options) {
    int position;
    char content[MAX_INPUT_LENGTH];
    if (sscanf(options, "%d %s", &position, content) != 2) {
        _printGenericError();
    }
    int content_length = (int) strlen(content);
    sendInteger(self->connection_handler, INSERT_OPCODE, 4);
    sendInteger(self->connection_handler, position, 4);
    sendInteger(self->connection_handler, content_length, 2);
    sendString(self->connection_handler, content, content_length);
}

static void _processDelete(CommandHandler *self, char *options) {
    int from, to;
    if (sscanf(options, "%d %d", &from, &to) != 2) {
        _printGenericError();
    }
    sendInteger(self->connection_handler, DELETE_OPCODE, 4);
    sendInteger(self->connection_handler, to, 4);
    sendInteger(self->connection_handler, from, 4);
}

static void
_processInsertCharacter(CommandHandler *self, char *character,
                        char *position_as_string) {
    int position;
    if (sscanf(position_as_string, "%d", &position) != 1) {
        _printGenericError();
    }

    if (strcmp(character, " ") == 0) {
        sendInteger(self->connection_handler, SPACE_OPCODE, 4);
    } else if (strcmp(character, "\n") == 0) {
        sendInteger(self->connection_handler, NEWLINE_OPCODE, 4);
    } else {
        return;
    }
    sendInteger(self->connection_handler, position, 4);
}

static void _processPrint(CommandHandler *self) {
    char buffer[MAX_INPUT_LENGTH];
    sendInteger(self->connection_handler, PRINT_OPCODE, 4);
    int length = receiveInteger(self->connection_handler, 4);
    receiveString(self->connection_handler, buffer, length);
    printf("%s", buffer);
}

static int _processInput(CommandHandler *self) {
    char command[MAX_COMMAND_LENGTH];
    char options[MAX_INPUT_LENGTH];

    if (sscanf(self->input, " %s %[^\t\n] ", command, options) > 0) {
        if (strcmp(command, "insert") == 0) {
            _processInsert(self, options);
        } else if (strcmp(command, "delete") == 0) {
            _processDelete(self, options);
        } else if (strcmp(command, "space") == 0) {
            _processInsertCharacter(self, " ", options);
        } else if (strcmp(command, "newline") == 0) {
            _processInsertCharacter(self, "\n", options);
        } else if (strcmp(command, "print") == 0) {
            _processPrint(self);
        } else {
            _printGenericError();
        }
        return RETRY;
    } else {
        return EXIT;
    }
}

void run(CommandHandler *self,
         ConnectionHandler *connection_handler,
         FILE *command_file) {
    self->connection_handler = connection_handler;
    self->command_file = command_file;
    int status;
    do {
        _getValidInput(self);
        status = _processInput(self);
    } while (status == RETRY);
}
