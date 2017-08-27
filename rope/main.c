#include "command_handler.h"
#include "rope_tests.h"

void runCommandLineApp() {
    CommandHandler command_handler;

    Rope rope;
    createEmptyRope(&rope);

    run(&command_handler, &rope);

    destroyRope(&rope);
}

int main(int argc, char **argv) {
    runCommandLineApp();
//    runRopeTests();
    return 0;
}
