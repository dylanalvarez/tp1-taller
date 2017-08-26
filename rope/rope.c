#include <stdio.h>
#include "rope.h"

void createRope(Rope *self, const char *content) {
    self->root = malloc(sizeof(RopeNode));
    createRopeNode(self->root, content);
}

size_t _getContentLengthFromRoot(RopeNode *node) {
    size_t total = 0;
    while (node) {
        total += node->weight;
        node = node->right;
    }
    return total;
}

void
_concatRopesFromRoots(RopeNode *left, RopeNode *right, RopeNode *new_root) {
    new_root->left = left;
    new_root->right = right;
    new_root->content = NULL;
    new_root->weight = _getContentLengthFromRoot(new_root->left);
}

void concatRopes(Rope *left, Rope *right, Rope *new_rope) {
    createRope(new_rope, NULL);
    _concatRopesFromRoots(left->root, right->root, new_rope->root);
}

void _updateTemp(RopeNode *node_to_append, RopeNode **temp) {
    if (!node_to_append) {
        return;
    }
    if (!*temp) {
        *temp = node_to_append;
        return;
    }
    RopeNode *new_temp = malloc(sizeof(RopeNode));
    _concatRopesFromRoots(node_to_append, *temp, new_temp);
    *temp = new_temp;
}


RopeNode *_splitRopeFromRoot(RopeNode *node, size_t index, RopeNode **temp) {
    if (isLeaf(node)) {
        if (!node->content) { return NULL; }
        RopeNode *left = malloc(sizeof(RopeNode));
        RopeNode *right = malloc(sizeof(RopeNode));
        splitRopeNode(node, index, left, right);
        _updateTemp(_splitRopeFromRoot(node, index, temp), temp);
        return NULL;
    }
    if (node->weight < index) {
        _splitRopeFromRoot(node->right, index - node->weight, temp);
        _updateTemp(node->left, temp);
        node->left = NULL;
        node->weight = 0;
    }
    if (node->weight == index) {
        RopeNode *left = node->left;
        node->left = NULL;
        node->weight = 0;
        return left;
    }
    if (node->weight > index) {
        _updateTemp(_splitRopeFromRoot(node->left, index, temp), temp);
        node->weight = _getContentLengthFromRoot(node->left);
    }
    return NULL;
}

void splitRope(Rope *source, size_t index, Rope *left, Rope *right) {
    RopeNode *temp = NULL;
    _splitRopeFromRoot(source->root, index, &temp);
    if (!temp) {
        temp = malloc(sizeof(RopeNode));
        createRopeNode(temp, NULL);
    }
    left->root = temp;
    right->root = source->root;
}

size_t getRopeContentLength(Rope *self) {
    return _getContentLengthFromRoot(self->root);
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
