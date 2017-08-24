#include <stdio.h>
#include <stdbool.h>
#include "rope.h"

// GENERIC FUNCTIONS

void assert(bool condition) {
    condition ? printf("OK\n") : printf("FAILED!\n");
}

// ROPE TESTS


// NODE TESTS

void testNewRopeNodeHasWeightOfString() {
    RopeNode rope_node;
    createRopeNode(&rope_node, "Hola");

    assert(rope_node.weight == 4);

    destroyRopeNode(&rope_node);
}

void testNewRopeIsLeaf() {
    RopeNode rope_node;
    createRopeNode(&rope_node, "Hola");

    assert(isLeaf(&rope_node));

    destroyRopeNode(&rope_node);
}

// MAIN

int main(int argc, char **argv) {
    testNewRopeNodeHasWeightOfString();
    testNewRopeIsLeaf();
    return 0;
}
