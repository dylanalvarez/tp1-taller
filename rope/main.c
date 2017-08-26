#include <stdio.h>
#include <stdbool.h>
#include "rope.h"

// GENERIC FUNCTIONS

int failures = 0;

void assert(bool condition) {
    condition ? printf("OK\n") : printf("FAILED!\n");
    if (!condition) {
        failures++;
    }
}

// ROPE TESTS

void testNewEmptyRopeHasNoLength() {
    Rope rope;
    createRope(&rope, NULL);

    char buffer[getRopeContentLength(&rope) + 1];
    getRopeContent(&rope, buffer);

    assert(strcmp(buffer, "") == 0);
    assert(getRopeContentLength(&rope) == 0);

    destroyRope(&rope);
}

void testNewRopeHasLengthOfPassedInString() {
    Rope rope;
    createRope(&rope, "example");
    char buffer[getRopeContentLength(&rope) + 1];
    getRopeContent(&rope, buffer);

    assert(strcmp(buffer, "example") == 0);
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

    char buffer[getRopeContentLength(&rope3) + 1];
    getRopeContent(&rope3, buffer);

    assert(strcmp(buffer, "") == 0);
    assert(getRopeContentLength(&rope3) == 0);

    destroyRope(&rope3);
}

void testConcatenationOfRopesHasSumOfLengths() {
    Rope rope1;
    createRope(&rope1, "123");
    Rope rope2;
    createRope(&rope2, "456");
    Rope rope3;

    concatRopes(&rope1, &rope2, &rope3);

    char buffer[getRopeContentLength(&rope3) + 1];
    getRopeContent(&rope3, buffer);

    assert(strcmp(buffer, "123456") == 0);
    assert(getRopeContentLength(&rope3) == 6);

    destroyRope(&rope3);
}

void testMultipleConcatenationOfRopesHasSumOfLengths() {
    Rope rope1;
    createRope(&rope1, "1");
    Rope rope2;
    createRope(&rope2, "23");
    Rope rope3;
    createRope(&rope3, "456");
    Rope rope4;
    createRope(&rope4, "7890");
    Rope rope5;
    Rope rope6;
    Rope rope7;

    concatRopes(&rope1, &rope2, &rope5);
    concatRopes(&rope3, &rope4, &rope6);
    concatRopes(&rope5, &rope6, &rope7);

    char buffer[getRopeContentLength(&rope7) + 1];
    getRopeContent(&rope7, buffer);

    assert(strcmp(buffer, "1234567890") == 0);

    assert(getRopeContentLength(&rope7) == 10);

    destroyRope(&rope7);
}

void testMultipleConcatenationOfRopesHasSumOfLengthsAgain() {
    Rope rope1;
    createRope(&rope1, "12");
    Rope rope2;
    createRope(&rope2, "2");
    Rope rope3;
    createRope(&rope3, "4567");
    Rope rope4;
    createRope(&rope4, "");
    Rope rope5;
    Rope rope6;
    Rope rope7;

    concatRopes(&rope1, &rope2, &rope5);
    concatRopes(&rope3, &rope4, &rope6);
    concatRopes(&rope5, &rope6, &rope7);

    char buffer[getRopeContentLength(&rope7) + 1];
    getRopeContent(&rope7, buffer);

    assert(strcmp(buffer, "1224567") == 0);
    assert(getRopeContentLength(&rope7) == 7);

    destroyRope(&rope7);
}

void testNewEmptyRopeKeepsAnEmptyString() {
    Rope rope;
    createRope(&rope, NULL);
    char buffer[getRopeContentLength(&rope) + 1];
    getRopeContent(&rope, buffer);

    assert(strcmp(buffer, "") == 0);
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
    char buffer[getRopeContentLength(&rope3) + 1];
    getRopeContent(&rope3, buffer);

    assert(strcmp(buffer, "") == 0);
    assert(getRopeContentLength(&rope3) == 0);

    destroyRope(&rope3);
}

void testSplittingAnEmptyRopeReturnsTwoEmptyLengths() {
    Rope rope1;
    createRope(&rope1, NULL);
    Rope rope2;
    Rope rope3;

    splitRope(&rope1, 0, &rope2, &rope3);

    char buffer2[getRopeContentLength(&rope2) + 1];
    getRopeContent(&rope2, buffer2);
    assert(strcmp(buffer2, "") == 0);
    assert(getRopeContentLength(&rope2) == 0);

    char buffer3[getRopeContentLength(&rope2) + 1];
    getRopeContent(&rope3, buffer3);
    assert(strcmp(buffer3, "") == 0);
    assert(getRopeContentLength(&rope3) == 0);

    destroyRope(&rope2);
    destroyRope(&rope3);
}

void testSplittingACreatedRopeDividesThePassedInString() {
    Rope rope1;
    createRope(&rope1, "qwerty");
    Rope rope2;
    Rope rope3;

    splitRope(&rope1, 2, &rope2, &rope3);

    char buffer2[getRopeContentLength(&rope2) + 1];
    getRopeContent(&rope2, buffer2);
    assert(strcmp(buffer2, "qw") == 0);
    assert(getRopeContentLength(&rope2) == 2);

    char buffer3[getRopeContentLength(&rope2) + 1];
    getRopeContent(&rope3, buffer3);
    assert(strcmp(buffer3, "erty") == 0);
    assert(getRopeContentLength(&rope3) == 4);

    destroyRope(&rope2);
    destroyRope(&rope3);
}

void testSplittingACreatedRopeWithIndex0ReturnsEmptyStringAndOriginalContent() {
    Rope rope1;
    createRope(&rope1, "qwerty");
    Rope rope2;
    Rope rope3;

    splitRope(&rope1, 0, &rope2, &rope3);

    char buffer2[getRopeContentLength(&rope2) + 1];
    getRopeContent(&rope2, buffer2);
    assert(strcmp(buffer2, "") == 0);
    assert(getRopeContentLength(&rope2) == 0);

    char buffer3[getRopeContentLength(&rope2) + 1];
    getRopeContent(&rope3, buffer3);
    assert(strcmp(buffer3, "qwerty") == 0);
    assert(getRopeContentLength(&rope3) == 6);

    destroyRope(&rope2);
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
    testConcatenationOfRopesHasSumOfLengths();
    testMultipleConcatenationOfRopesHasSumOfLengths();
    testMultipleConcatenationOfRopesHasSumOfLengthsAgain();
    testSplittingAnEmptyRopeReturnsTwoEmptyLengths();
    testSplittingACreatedRopeDividesThePassedInString();
    testSplittingACreatedRopeWithIndex0ReturnsEmptyStringAndOriginalContent();

    printf("\n%d failures", failures);
    return 0;
}
