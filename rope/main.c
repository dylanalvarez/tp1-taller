#include "command_handler.h"
#include <string.h>
#include "connection_handler.h"
#include "rope_tests.h"

#define localhost "127.0.0.1"

#define SUCCESS 0
#define ERROR -1

void runCommandLineApp(FILE *command_file) {
    Rope rope;
    createEmptyRope(&rope);
    CommandHandler command_handler;
    run(&command_handler, &rope, command_file);
    destroyRope(&rope);
}

int _handleClient(char **argv, FILE *command_file) {
    ConnectionHandler connection_handler;
    char* ip = argv[2];
    char* port = argv[3];
    createConnectionHandler(&connection_handler, ip, port);
    runCommandLineApp(command_file);
    destroyConnectionHandler(&connection_handler);
    return SUCCESS;
}

int _handleServer(char **argv) {
    ConnectionHandler connection_handler;
    createConnectionHandler(&connection_handler, localhost, argv[2]);
    destroyConnectionHandler(&connection_handler);
    return SUCCESS;
}

int main(int argc, char **argv) {
    int number_of_arguments = argc - 1;
    if (number_of_arguments < 2) {
        return ERROR;
    }

    if (strcmp(argv[1], "client") == 0) { // client 127.0.0.1 9898 input.txt

        if (number_of_arguments < 3) {
            return ERROR;
        }
        FILE *command_file = NULL;
        if (number_of_arguments == 4) {
            command_file = fopen(argv[4], "r");
        }
        int exit_code = _handleClient(argv, command_file);
        if (command_file) {
            fclose(command_file);
        }
        return exit_code;

    } else if (strcmp(argv[1], "server") == 0) { // server 9898

        return _handleServer(argv);

    } else if (strcmp(argv[1], "test") == 0) { // test

        runRopeTests();
        return SUCCESS;

    }
    return ERROR;
}
