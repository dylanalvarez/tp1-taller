#include <stdio.h>
#include "rope.h"

void createRope(Rope *self) {
    self->root = malloc(sizeof(RopeNode));
    createRopeNode(self->root, NULL);
}

void concatRopes(Rope *left, Rope *right, Rope *new_rope) {
    createRope(new_rope);
    new_rope->root->left = left->root;
    new_rope->root->right = right->root;
    destroyRope(left);
    destroyRope(right);
}

void splitRopes(Rope *source, int index, Rope *left, Rope *right) {}

int getRopeContentLength(Rope *self) {
    int total = 0;
    RopeNode *node = self->root;
    while (node) {
        total += node->weight;
        node = node->right;
    }
    return total;
}

void fillBuffer(RopeNode *node, char *buffer, int *position) {
    if (!node) { return; }
    fillBuffer(node->left, buffer, position);

    if (node->content) {
        size_t length = strlen(node->content);
        for (int i = *position; i < length + *position; i++) {
            buffer[i] = node->content[i - *position];
        }
        *position += length;
        buffer[*position] = (char) 0;
    }

    fillBuffer(node->right, buffer, position);
}

void getRopeContent(Rope *self, char *buffer) {
    int position = 0;
    buffer[0] = (char) 0;
    fillBuffer(self->root, buffer, &position);
}

void destroyRope(Rope *self) {
    destroyRopeNode(self->root);
}
