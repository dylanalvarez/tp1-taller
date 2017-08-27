#include "rope_tests.h"
#include "rope.h"
#include <stdio.h>

int failures = 0;
char buffer[50];
char buffer2[50];
char buffer3[50];
char leftBuffer[50];
char rightBuffer[50];

void assert(bool condition) {
    condition ? printf("OK\n") : printf("FAILED!\n");
    if (!condition) {
        failures++;
    }
}

void testNewEmptyRopeHasNoLength() {
    Rope rope;
    createEmptyRope(&rope);

    getRopeContent(&rope, buffer);

    assert(strcmp(buffer, "") == 0);
    assert(getRopeContentLength(&rope) == 0);

    destroyRope(&rope);
}

void testNewRopeHasLengthOfPassedInString() {
    Rope rope;
    createRope(&rope, "example");
    getRopeContent(&rope, buffer);

    assert(strcmp(buffer, "example") == 0);
    assert(getRopeContentLength(&rope) == strlen("example"));

    destroyRope(&rope);
}

void testConcatenationOfEmptyRopesHasNoLength() {
    Rope rope1;
    createEmptyRope(&rope1);
    Rope rope2;
    createEmptyRope(&rope2);
    Rope rope3;

    concatRopes(&rope1, &rope2, &rope3);

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

    getRopeContent(&rope7, buffer);

    assert(strcmp(buffer, "1224567") == 0);
    assert(getRopeContentLength(&rope7) == 7);

    destroyRope(&rope7);
}

void testNewEmptyRopeKeepsAnEmptyString() {
    Rope rope;
    createEmptyRope(&rope);
    getRopeContent(&rope, buffer);

    assert(strcmp(buffer, "") == 0);
    assert(strlen(buffer) == 0);

    destroyRope(&rope);
}

void testConcatenationOfEmptyRopesKeepsAnEmptyString() {
    Rope rope1;
    createEmptyRope(&rope1);
    Rope rope2;
    createEmptyRope(&rope2);
    Rope rope3;

    concatRopes(&rope1, &rope2, &rope3);
    getRopeContent(&rope3, buffer);

    assert(strcmp(buffer, "") == 0);
    assert(getRopeContentLength(&rope3) == 0);

    destroyRope(&rope3);
}

void testSplittingAnEmptyRopeReturnsTwoEmptyLengths() {
    Rope rope1;
    createEmptyRope(&rope1);
    Rope rope2;
    Rope rope3;

    splitRope(&rope1, 0, &rope2, &rope3);

    getRopeContent(&rope2, buffer2);
    assert(strcmp(buffer2, "") == 0);
    assert(getRopeContentLength(&rope2) == 0);

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

    getRopeContent(&rope2, buffer2);
    assert(strcmp(buffer2, "qw") == 0);
    assert(getRopeContentLength(&rope2) == 2);

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

    getRopeContent(&rope2, buffer2);
    assert(strcmp(buffer2, "") == 0);
    assert(getRopeContentLength(&rope2) == 0);

    getRopeContent(&rope3, buffer3);
    assert(strcmp(buffer3, "qwerty") == 0);
    assert(getRopeContentLength(&rope3) == 6);

    destroyRope(&rope2);
    destroyRope(&rope3);
}

void
testSplittingACreatedRopeWithMaxIndexReturnsOriginalContentAndEmptyString() {
    Rope rope1;
    createRope(&rope1, "qwerty");
    Rope rope2;
    Rope rope3;

    splitRope(&rope1, 6, &rope2, &rope3);

    getRopeContent(&rope2, buffer2);
    assert(strcmp(buffer2, "qwerty") == 0);
    assert(getRopeContentLength(&rope2) == 6);

    getRopeContent(&rope3, buffer3);
    assert(strcmp(buffer3, "") == 0);
    assert(getRopeContentLength(&rope3) == 0);

    destroyRope(&rope2);
    destroyRope(&rope3);
}

// https://en.wikipedia.org/wiki/Rope_(data_structure)
//                        #/media/File:Vector_Rope_split.svg
void testSplitWikipediaExample() {
    Rope ropeE;
    createRope(&ropeE, "Hello_");
    Rope ropeF;
    createRope(&ropeF, "my_");
    Rope ropeJ;
    createRope(&ropeJ, "na");
    Rope ropeK;
    createRope(&ropeK, "me_i");
    Rope ropeM;
    createRope(&ropeM, "s");
    Rope ropeN;
    createRope(&ropeN, "_Simon");
    Rope rope_;
    createRope(&rope_, "");
    Rope ropeA;
    Rope ropeB;
    Rope ropeC;
    Rope ropeD;
    Rope ropeG;
    Rope ropeH;

    concatRopes(&ropeE, &ropeF, &ropeC);
    concatRopes(&ropeJ, &ropeK, &ropeG);
    concatRopes(&ropeM, &ropeN, &ropeH);
    concatRopes(&ropeG, &ropeH, &ropeD);
    concatRopes(&ropeC, &ropeD, &ropeB);
    concatRopes(&ropeB, &rope_, &ropeA);

    Rope leftDestination;
    Rope rightDestination;

    splitRope(&ropeA, 11, &leftDestination, &rightDestination);

    getRopeContent(&leftDestination, leftBuffer);
    assert(strcmp(leftBuffer, "Hello_my_na") == 0);
    assert(getRopeContentLength(&leftDestination) == 11);

    getRopeContent(&rightDestination, rightBuffer);
    assert(strcmp(rightBuffer, "me_is_Simon") == 0);
    assert(getRopeContentLength(&rightDestination) == 11);

    destroyRope(&leftDestination);
    destroyRope(&rightDestination);
}

void testSplitWikipediaExampleThisTimeNeedingToSplitANode() {
    Rope ropeE;
    createRope(&ropeE, "Hello_");
    Rope ropeF;
    createRope(&ropeF, "my_");
    Rope ropeJ;
    createRope(&ropeJ, "na");
    Rope ropeK;
    createRope(&ropeK, "me_i");
    Rope ropeM;
    createRope(&ropeM, "s");
    Rope ropeN;
    createRope(&ropeN, "_Simon");
    Rope rope_;
    createRope(&rope_, "");
    Rope ropeA;
    Rope ropeB;
    Rope ropeC;
    Rope ropeD;
    Rope ropeG;
    Rope ropeH;

    concatRopes(&ropeE, &ropeF, &ropeC);
    concatRopes(&ropeJ, &ropeK, &ropeG);
    concatRopes(&ropeM, &ropeN, &ropeH);
    concatRopes(&ropeG, &ropeH, &ropeD);
    concatRopes(&ropeC, &ropeD, &ropeB);
    concatRopes(&ropeB, &rope_, &ropeA);

    Rope leftDestination;
    Rope rightDestination;

    splitRope(&ropeA, 10, &leftDestination, &rightDestination);

    getRopeContent(&leftDestination, leftBuffer);
    assert(strcmp(leftBuffer, "Hello_my_n") == 0);
    assert(getRopeContentLength(&leftDestination) == 10);

    getRopeContent(&rightDestination, rightBuffer);
    assert(strcmp(rightBuffer, "ame_is_Simon") == 0);
    assert(getRopeContentLength(&rightDestination) == 12);

    destroyRope(&leftDestination);
    destroyRope(&rightDestination);
}

void testSplitWikipediaExampleThisTimeCheckingEveryCharacter() {
    Rope ropeE;
    createRope(&ropeE, "Hello_");
    Rope ropeF;
    createRope(&ropeF, "my_");
    Rope ropeJ;
    createRope(&ropeJ, "na");
    Rope ropeK;
    createRope(&ropeK, "me_i");
    Rope ropeM;
    createRope(&ropeM, "s");
    Rope ropeN;
    createRope(&ropeN, "_Simon");
    Rope rope_;
    createRope(&rope_, "");
    Rope ropeA;
    Rope ropeB;
    Rope ropeC;
    Rope ropeD;
    Rope ropeG;
    Rope ropeH;

    concatRopes(&ropeE, &ropeF, &ropeC);
    concatRopes(&ropeJ, &ropeK, &ropeG);
    concatRopes(&ropeM, &ropeN, &ropeH);
    concatRopes(&ropeG, &ropeH, &ropeD);
    concatRopes(&ropeC, &ropeD, &ropeB);
    concatRopes(&ropeB, &rope_, &ropeA);

    char *content = "Hello_my_name_is_Simon";
    bool correct = true;
    for (size_t i = 0; i < getRopeContentLength(&ropeA); i++) {
        if (content[i] != getRopeContentAtIndex(&ropeA, i)) {
            correct = false;
        }
    }
    assert(correct);

    destroyRope(&ropeA);
}

void testInsertInFirstIndex() {
    Rope rope;
    createRope(&rope, "example");
    insert(&rope, "qwe", 0);
    getRopeContent(&rope, buffer);

    assert(strcmp(buffer, "qweexample") == 0);

    destroyRope(&rope);
}

void testInsertInLastIndex() {
    Rope rope;
    createRope(&rope, "example");
    insert(&rope, "qwe", 7);
    getRopeContent(&rope, buffer);

    assert(strcmp(buffer, "exampleqwe") == 0);

    destroyRope(&rope);
}

void testInsertInTheMiddle() {
    Rope rope;
    createRope(&rope, "example");
    insert(&rope, "qwe", 3);
    getRopeContent(&rope, buffer);

    assert(strcmp(buffer, "exaqwemple") == 0);

    destroyRope(&rope);
}

void testDeleteAllCharacters() {
    Rope rope;
    createRope(&rope, "example");
    delete(&rope, 0, 7);
    getRopeContent(&rope, buffer);

    assert(getRopeContentLength(&rope) == 0);
    assert(strcmp(buffer, "") == 0);

    destroyRope(&rope);
}

void testDeleteLastCharacters() {
    Rope rope;
    createRope(&rope, "example");
    delete(&rope, 2, 7);
    getRopeContent(&rope, buffer);

    assert(getRopeContentLength(&rope) == 2);
    assert(strcmp(buffer, "ex") == 0);

    destroyRope(&rope);
}

void testDeleteFirstCharacters() {
    Rope rope;
    createRope(&rope, "example");
    delete(&rope, 0, 3);
    getRopeContent(&rope, buffer);

    assert(getRopeContentLength(&rope) == 4);
    assert(strcmp(buffer, "mple") == 0);

    destroyRope(&rope);
}

void testInsertInEmptyRope() {
    Rope rope;
    createEmptyRope(&rope);
    insert(&rope, "asd", 0);
    getRopeContent(&rope, buffer);

    assert(getRopeContentLength(&rope) == 3);
    assert(strcmp(buffer, "asd") == 0);

    destroyRope(&rope);
}

void testInsertInNegativeIndex() {
    Rope rope;

    createEmptyRope(&rope); // ""
    insert(&rope, "foo", -1); // "foo"
    insert(&rope, "u", -2); // "fouo"
    insert(&rope, "a", -5); // "afouo"

    getRopeContent(&rope, buffer);
    assert(getRopeContentLength(&rope) == 5);
    assert(strcmp(buffer, "afouo") == 0);

    destroyRope(&rope);
}

void testDeleteInNegativeIndex() {
    Rope rope;

    createRope(&rope, "1234567890"); // "1234567890"
    delete(&rope, -2, -1); // "12345678"
    delete(&rope, -8, -7); // "345678"
    delete(&rope, 0, -5); // "5678"
    delete(&rope, 1, -3); // "578"
    delete(&rope, -3, 1); // "78"

    getRopeContent(&rope, buffer);
    assert(getRopeContentLength(&rope) == 2);
    assert(strcmp(buffer, "78") == 0);

    destroyRope(&rope);
}

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

void runRopeTests() {
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
    testSplittingACreatedRopeWithMaxIndexReturnsOriginalContentAndEmptyString();
    testSplitWikipediaExample();
    testSplitWikipediaExampleThisTimeNeedingToSplitANode();
    testSplitWikipediaExampleThisTimeCheckingEveryCharacter();
    testInsertInFirstIndex();
    testInsertInLastIndex();
    testInsertInTheMiddle();
    testDeleteAllCharacters();
    testDeleteLastCharacters();
    testDeleteFirstCharacters();
    testInsertInEmptyRope();
    testInsertInNegativeIndex();
    testDeleteInNegativeIndex();

    printf("\nRope tests: \n%d failures.\n", failures);
}
