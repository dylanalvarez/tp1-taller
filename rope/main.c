#include <stdio.h>
#include <stdbool.h>
#include "rope.h"

// GENERIC FUNCTIONS

void assert(bool condition) {
    condition ? printf("OK\n") : printf("FAILED!\n");
}

// ROPE TESTS

void testNewRopeHasNoLength() {
    Rope rope;
    createRope(&rope);

    assert(getRopeContentLength(&rope) == 0);

    destroyRope(&rope);
}

void concatenationOfEmptyRopesHasNoLength() {
    Rope rope1;
    createRope(&rope1);
    Rope rope2;
    createRope(&rope2);
    Rope rope3;

    concatRopes(&rope1, &rope2, &rope3);
    assert(getRopeContentLength(&rope3) == 0);

    destroyRope(&rope3);
}

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
    testNewRopeHasNoLength();
    concatenationOfEmptyRopesHasNoLength();
    return 0;
}
