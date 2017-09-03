#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#include "client_handler.h"


static int _lengthExceptForSpaces(char *input) {
    int length = 0;
    for (int i = 0; i < strlen(input); i++) {
        if (input[i] != ' ') {
            length++;
        }
    }
    return length;
}

static int _getInput(ClientHandler *self) {
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
    bool commandIsEmpty = _lengthExceptForSpaces(self->input) <= strlen("\n\0");

    if (self->input[input_length - 1] == '\n') {
        self->input[input_length - 1] = 0;
    }
    if (commandIsEmpty) {
        return RETRY;
    }
    return EXIT;
}

static void _getValidInput(ClientHandler *self) {
    int exit_code;
    do {
        exit_code = _getInput(self);
    } while (exit_code == RETRY);
}

static void _processInsert(ClientHandler *self, char *options) {
    int position;
    char content[MAX_INPUT_LENGTH];
    if (sscanf(options, "%d %s", &position, content) != 2) {
        fprintf(stderr, "Invalid command");
    }
    int content_length = (int) strlen(content);
    sendInteger(self->connection_handler, INSERT_OPCODE, LONG_INT);
    sendInteger(self->connection_handler, position, LONG_INT);
    sendInteger(self->connection_handler, content_length, SHORT_INT);
    sendString(self->connection_handler, content, content_length);
}

static void _processDelete(ClientHandler *self, char *options) {
    int from, to;
    if (sscanf(options, "%d %d", &from, &to) != 2) {
        fprintf(stderr, "Invalid command");
    }
    sendInteger(self->connection_handler, DELETE_OPCODE, LONG_INT);
    sendInteger(self->connection_handler, to, LONG_INT);
    sendInteger(self->connection_handler, from, LONG_INT);
}

static void _processInsertCharacter(ClientHandler *self, char *character,
                                    char *position_as_string) {
    int position;
    if (sscanf(position_as_string, "%d", &position) != 1) {
        fprintf(stderr, "Invalid command");
    }

    if (strcmp(character, " ") == 0) {
        sendInteger(self->connection_handler, SPACE_OPCODE, LONG_INT);
    } else if (strcmp(character, "\n") == 0) {
        sendInteger(self->connection_handler, NEWLINE_OPCODE, LONG_INT);
    } else {
        return;
    }
    sendInteger(self->connection_handler, position, LONG_INT);
}

static void _processPrint(ClientHandler *self) {
    sendInteger(self->connection_handler, PRINT_OPCODE, LONG_INT);
    int length;
    if (receiveInteger(self->connection_handler, &length, LONG_INT) == ERROR) {
        return;
    }
    char buffer[MAX_INPUT_LENGTH];
    if (receiveString(self->connection_handler, buffer, length) ==
        ERROR) { return; }
    printf("%s", buffer);
}

static int _processInput(ClientHandler *self) {
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
            fprintf(stderr, "Invalid command");
        }
        return RETRY;
    } else {
        return EXIT;
    }
}

void runClientHandler(ClientHandler *client_handler,
                      ConnectionHandler *connection_handler,
                      FILE *command_file) {
    client_handler->connection_handler = connection_handler;
    client_handler->command_file = command_file;
    int status;
    do {
        _getValidInput(client_handler);
        status = _processInput(client_handler);
    } while (status == RETRY);
}
