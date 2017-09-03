#include "server_handler.h"
#include "constants.h"

static void _processInsert(ServerHandler *self) {
    int position = 0;
    if (receiveInteger(self->connection_handler, &position, LONG_INT) ==
        ERROR) { return; }
    int length;
    if (receiveInteger(self->connection_handler, &length, SHORT_INT) ==
        ERROR) { return; }
    char buffer[MAX_INPUT_LENGTH];
    if (receiveString(self->connection_handler, buffer, length) ==
        ERROR) { return; }
    insert(self->rope, buffer, position);
}

static void _processDelete(ServerHandler *self) {
    int from, to;
    if (receiveInteger(self->connection_handler, &to, LONG_INT) == ERROR) {
        return;
    }
    if (receiveInteger(self->connection_handler, &from, LONG_INT) == ERROR) {
        return;
    }
    delete(self->rope, from, to);
}

static void
_processInsertCharacter(ServerHandler *self, char *character) {
    int position = 0;
    if (receiveInteger(self->connection_handler, &position, LONG_INT) ==
        ERROR) { return; }
    insert(self->rope, character, position);
}

static void _processPrint(ServerHandler *self) {
    char buffer[MAX_INPUT_LENGTH];
    getRopeContent(self->rope, buffer);
    int buffer_length = (int) getRopeContentLength(self->rope);
    sendInteger(self->connection_handler, buffer_length, LONG_INT);
    sendString(self->connection_handler, buffer, buffer_length);
}

static int _processInput(ServerHandler *self) {
    int opcode;
    if (receiveInteger(self->connection_handler, &opcode, LONG_INT) == ERROR) {
        return EXIT;
    }
    if (opcode == INSERT_OPCODE) {
        _processInsert(self);
    } else if (opcode == DELETE_OPCODE) {
        _processDelete(self);
    } else if (opcode == SPACE_OPCODE) {
        _processInsertCharacter(self, " ");
    } else if (opcode == NEWLINE_OPCODE) {
        _processInsertCharacter(self, "\n");
    } else if (opcode == PRINT_OPCODE) {
        _processPrint(self);
    } else {
        return EXIT;
    }
    return RETRY;
}

void runServerHandler(ServerHandler *server_handler,
                      ConnectionHandler *connection_handler,
                      Rope *rope) {
    server_handler->connection_handler = connection_handler;
    server_handler->rope = rope;
    int exit_code;
    do {
        exit_code = _processInput(server_handler);
    } while (exit_code == RETRY);
}
