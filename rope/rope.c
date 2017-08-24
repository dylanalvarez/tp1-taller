#include <stdio.h>
#include "rope.h"

void createRope(Rope *self, const char *content) {
    self->root = malloc(sizeof(RopeNode));
    createRopeNode(self->root, content);
}

void concatRopes(Rope *left, Rope *right, Rope *new_rope) {
    createRope(new_rope, NULL);
    new_rope->root->left = left->root;
    new_rope->root->right = right->root;
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

static void _fillBuffer(RopeNode *node, char *buffer, int *position) {
    if (!node) { return; }
    _fillBuffer(node->left, buffer, position);

    if (node->content) {
        size_t length = strlen(node->content);
        for (int i = *position; i < length + *position; i++) {
            buffer[i] = node->content[i - *position];
        }
        *position += length;
        buffer[*position] = (char) 0;
    }

    _fillBuffer(node->right, buffer, position);
}

void getRopeContent(Rope *self, char *buffer) {
    int position = 0;
    buffer[0] = (char) 0;
    _fillBuffer(self->root, buffer, &position);
}

void _destroyNode(RopeNode *node) {
    if (!node) { return; }
    _destroyNode(node->left);
    _destroyNode(node->right);
    destroyRopeNode(node);
    free(node);
}

void destroyRope(Rope *self) {
    _destroyNode(self->root);
}
