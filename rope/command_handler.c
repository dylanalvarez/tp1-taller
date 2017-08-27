#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

static int _processInsert(CommandHandler *self, char *strtok_context) {
    char *position_as_string = strtok_r(NULL, SEPARATOR, &strtok_context);
    char *content = strtok_r(NULL, SEPARATOR, &strtok_context);
    if (!(position_as_string && content)) {
        return _printGenericErrorAndRetry();
    }

    int position;
    if (sscanf(position_as_string, "%d", &position) != 1) {
        return _printGenericErrorAndRetry();
    }

    insert(self->rope, content, position);

    return RETRY;
}

static int _processDelete(CommandHandler *self, char *strtok_context) {
    char *from_as_string = strtok_r(NULL, SEPARATOR, &strtok_context);
    char *to_as_string = strtok_r(NULL, SEPARATOR, &strtok_context);
    if (!(to_as_string && from_as_string)) {
        return _printGenericErrorAndRetry();
    }

    int from, to;
    if (sscanf(from_as_string, "%d", &from) != 1 ||
        sscanf(to_as_string, "%d", &to) != 1) {
        return _printGenericErrorAndRetry();
    }

    delete(self->rope, from, to);

    return RETRY;
}

static int
_processInsertCharacter(CommandHandler *self, char *character,
                        char *strtok_context) {
    char *position_as_string = strtok_r(NULL, SEPARATOR, &strtok_context);
    if (!position_as_string) {
        return _printGenericErrorAndRetry();
    }

    int position;
    if (sscanf(position_as_string, "%d", &position) != 1) {
        return _printGenericErrorAndRetry();
    }

    insert(self->rope, character, position);

    return RETRY;
}

static int _processPrint(CommandHandler *self) {
    char *buffer = malloc(sizeof(char) * getRopeContentLength(self->rope) + 1);
    getRopeContent(self->rope, buffer);
    printf("%s", buffer);
    free(buffer);

    return EXIT;
}

static int _processInput(CommandHandler *self) {
    char *strtok_context = NULL;
    char *command = strtok_r(self->input, SEPARATOR, &strtok_context);

    if (strcmp(command, "insert") == 0) {
        return _processInsert(self, strtok_context);
    } else if (strcmp(command, "delete") == 0) {
        return _processDelete(self, strtok_context);
    } else if (strcmp(command, "space") == 0) {
        return _processInsertCharacter(self, " ", strtok_context);
    } else if (strcmp(command, "newline") == 0) {
        return _processInsertCharacter(self, "\n", strtok_context);
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
