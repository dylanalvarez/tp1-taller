#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "command_handler.h"

#define EXIT 0
#define RETRY 1
#define MAX_COMMAND_LENGTH 10

static void _printCustomError(char *message) {
    printf("Error: %s.\n", message);
}

static void _printGenericError() {
    _printCustomError("Invalid command");
}

static int _lengthExceptForSpaces(char* input){
    int length = 0;
    for (int i = 0; i < strlen(input); i++) {
        if (input[i] != ' '){
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
    insert(self->rope, content, position);
}

static void _processDelete(CommandHandler *self, char *options) {
    int from, to;
    if (sscanf(options, "%d %d", &from, &to) != 2) {
        _printGenericError();
    }
    delete(self->rope, from, to);
}

static void
_processInsertCharacter(CommandHandler *self, char *character,
                        char *position_as_string) {
    int position;
    if (sscanf(position_as_string, "%d", &position) != 1) {
        _printGenericError();
    }
    insert(self->rope, character, position);
}

static void _processPrint(CommandHandler *self) {
    char *buffer = malloc(sizeof(char) * getRopeContentLength(self->rope) + 1);
    getRopeContent(self->rope, buffer);
    printf("%s", buffer);
    free(buffer);
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

void run(CommandHandler *self, Rope *rope, FILE *command_file) {
    self->rope = rope;
    self->command_file = command_file;
    int status;
    do {
        _getValidInput(self);
        status = _processInput(self);
    } while (status == RETRY);
}
