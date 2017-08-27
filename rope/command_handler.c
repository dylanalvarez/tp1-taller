#include <stdio.h>
#include <string.h>
#include "command_handler.h"

#define SEPARATOR " "
#define EXIT 0
#define RETRY 1


static int _printCustomErrorAndRetry(char *message) {
    printf("Error: %s. Enter 'print' to quit.\n", message);
    return RETRY;
}

static int _printGenericErrorAndRetry() {
    return _printCustomErrorAndRetry("Invalid command");
}

static int _getInput(CommandHandler *self) {
    char *ok = fgets(self->input, MAX_INPUT_LENGTH, stdin);
    if (!ok) {
        return _printGenericErrorAndRetry();
    }

    size_t input_length = strlen(self->input);
    char last_character = self->input[input_length - 1];

    if (last_character != '\n') {
        return _printCustomErrorAndRetry(
                "Command length greater than expected");
    }
    if (input_length <= strlen("\n\0")) {
        return _printCustomErrorAndRetry("Empty command");
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

static int _processInsert(CommandHandler *self) {
    char *position_as_string = strtok(NULL, SEPARATOR);
    char *text = strtok(NULL, SEPARATOR);
    int position;
    if (!(position_as_string && text)) {
        return _printGenericErrorAndRetry();
    }
    int successful_if_1 = sscanf(position_as_string, "%d", &position);
    if (successful_if_1 != 1){
        return _printGenericErrorAndRetry();
    }
    printf("insert %s in position %d", text, position);
    return RETRY;
}

static int _processDelete(CommandHandler *self) {
    char *from = strtok(NULL, SEPARATOR);
    char *to = strtok(NULL, SEPARATOR);
    if (!(to && from)) {
        return _printGenericErrorAndRetry();
    }
    printf("delete from position %s to position %s", from, to);
    return RETRY;
}

static int _processSpace(CommandHandler *self) {
    char *position = strtok(NULL, SEPARATOR);
    if (!position) {
        return _printGenericErrorAndRetry();
    }
    printf("insert space in position %s", position);
    return RETRY;
}

static int _processNewline(CommandHandler *self) {
    char *position = strtok(NULL, SEPARATOR);
    if (!position) {
        return _printGenericErrorAndRetry();
    }
    printf("insert new line in position %s", position);
    return RETRY;
}

static int _processPrint(CommandHandler *self) {
    printf("print the whole thing");
    return EXIT;
}

static int _processInput(CommandHandler *self) {
    char *command = strtok(self->input, SEPARATOR);

    if (strcmp(command, "insert") == 0) {
        return _processInsert(self);
    } else if (strcmp(command, "delete") == 0) {
        return _processDelete(self);
    } else if (strcmp(command, "space") == 0) {
        return _processSpace(self);
    } else if (strcmp(command, "newline") == 0) {
        return _processNewline(self);
    } else if (strcmp(command, "print") == 0) {
        return _processPrint(self);
    } else {
        return _printGenericErrorAndRetry();
    }
}

void run(CommandHandler *self, Rope *rope) {
    self->rope = rope;

    int status;
    do {
        _getValidInput(self);
        status = _processInput(self);
    } while (status == RETRY);
}
