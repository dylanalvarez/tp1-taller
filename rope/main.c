#include "command_handler.h"

int main(int argc, char **argv) {
    CommandHandler command_handler;

    Rope rope;
    createEmptyRope(&rope);

    run(&command_handler, &rope);

    return 0;
}
