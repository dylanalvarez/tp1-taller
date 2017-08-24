#include <stdio.h>
#include <stdbool.h>
#include "rope.h"

// GENERIC FUNCTIONS

void assert(bool condition) {
    condition ? printf("OK\n") : printf("FAILED!\n");
}

// ROPE TESTS

void testNewEmptyRopeHasNoLength() {
    Rope rope;
    createRope(&rope, NULL);

    assert(getRopeContentLength(&rope) == 0);

    destroyRope(&rope);
}

void testNewRopeHasLengthOfPassedInString() {
    Rope rope;
    createRope(&rope, "example");

    assert(getRopeContentLength(&rope) == strlen("example"));

    destroyRope(&rope);
}

void testConcatenationOfEmptyRopesHasNoLength() {
    Rope rope1;
    createRope(&rope1, NULL);
    Rope rope2;
    createRope(&rope2, NULL);
    Rope rope3;

    concatRopes(&rope1, &rope2, &rope3);
    assert(getRopeContentLength(&rope3) == 0);

    destroyRope(&rope3);
}

void testNewEmptyRopeKeepsAnEmptyString() {
    Rope rope;
    createRope(&rope, NULL);
    char buffer[getRopeContentLength(&rope) + 1];
    getRopeContent(&rope, buffer);

    assert(strlen(buffer) == 0);

    destroyRope(&rope);
}

void testConcatenationOfEmptyRopesKeepsAnEmptyString() {
    Rope rope1;
    createRope(&rope1, NULL);
    Rope rope2;
    createRope(&rope2, NULL);
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
    testNewEmptyRopeHasNoLength();
    testConcatenationOfEmptyRopesHasNoLength();
    testNewEmptyRopeKeepsAnEmptyString();
    testConcatenationOfEmptyRopesKeepsAnEmptyString();
    testNewRopeHasLengthOfPassedInString();
    return 0;
}
