#include <stdio.h>
#include "rope.h"

void createRope(Rope *self, const char *content) {
    self->root = malloc(sizeof(RopeNode));
    createRopeNode(self->root, content);
}

static void
_concatRopesFromRoots(RopeNode *left, RopeNode *right, RopeNode *new_root) {
    createEmptyRopeNode(new_root);
    appendLeftChild(new_root, left);
    appendRightChild(new_root, right);
}

void concatRopes(Rope *left, Rope *right, Rope *new_rope) {
    createRope(new_rope, NULL);
    _concatRopesFromRoots(left->root, right->root, new_rope->root);
}

static void _appendToLeft(RopeNode *node_to_append, RopeNode **left_root) {
    if (!node_to_append) {
        return;
    }
    if (!*left_root) {
        *left_root = node_to_append;
        return;
    }
    RopeNode *new_left_root = malloc(sizeof(RopeNode));
    _concatRopesFromRoots(node_to_append, *left_root, new_left_root);
    *left_root = new_left_root;
}

static RopeNode *
_moveFirstCharactersToLeftRoot(RopeNode *node,
                               size_t characters_to_left,
                               RopeNode **left_root) {
    if (isLeaf(node)) {
        if (!node->content) { return NULL; }

        RopeNode *left = malloc(sizeof(RopeNode));
        RopeNode *right = malloc(sizeof(RopeNode));
        splitRopeNode(node, characters_to_left, left, right);

        RopeNode *to_left = _moveFirstCharactersToLeftRoot(node,
                                                           characters_to_left,
                                                           left_root);
        _appendToLeft(to_left, left_root);
    } else if (node->weight < characters_to_left) {
        _moveFirstCharactersToLeftRoot(node->right,
                                       characters_to_left - node->weight,
                                       left_root);
        _appendToLeft(node->left, left_root);

        appendLeftChild(node, NULL);
    } else if (node->weight > characters_to_left) {
        RopeNode *to_left = _moveFirstCharactersToLeftRoot(node->left,
                                                           characters_to_left,
                                                           left_root);
        _appendToLeft(to_left, left_root);

        node->weight = getSubRopeContentLength(node->left);
    } else { // node->weight == characters_to_left
        RopeNode *left = node->left;
        appendLeftChild(node, NULL);
        return left;
    }
    return NULL;
}

void splitRope(Rope *source, size_t characters_to_left,
               Rope *left, Rope *right) {
    RopeNode *left_root = NULL;
    _moveFirstCharactersToLeftRoot(source->root,
                                   characters_to_left,
                                   &left_root);
    if (!left_root) {
        left_root = malloc(sizeof(RopeNode));
        createEmptyRopeNode(left_root);
    }
    left->root = left_root;
    right->root = source->root;
}

void insert(Rope *self, const char *content, size_t index) {
    Rope left;
    Rope right;
    splitRope(self, index, &left, &right);

    Rope center;
    createRope(&center, content);

    Rope left_plus_center;
    Rope new_self;

    concatRopes(&left, &center, &left_plus_center);
    concatRopes(&left_plus_center, &right, &new_self);
    self->root = new_self.root;
}

void delete(Rope *self, size_t from, size_t to) {
    Rope left;
    Rope center;
    Rope right;

    Rope temp;
    splitRope(self, from, &left, &temp);
    splitRope(&temp, to - from, &center, &right);

    Rope new_self;
    concatRopes(&left, &right, &new_self);
    self->root = new_self.root;

    destroyRope(&center);
}

size_t getRopeContentLength(Rope *self) {
    return getSubRopeContentLength(self->root);
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
    buffer[0] = 0;
    _fillBuffer(self->root, buffer, &position);
}

static char _getRopeContentAtIndex(RopeNode *node, size_t index) {
    if (node->weight <= index) {
        return _getRopeContentAtIndex(node->right, index - node->weight);
    }
    if (node->left) {
        return _getRopeContentAtIndex(node->left, index);
    }
    return node->content[index];
}

char getRopeContentAtIndex(Rope *self, size_t index) {
    return _getRopeContentAtIndex(self->root, index);
}

static void _destroyNode(RopeNode *node) {
    if (!node) { return; }
    _destroyNode(node->left);
    _destroyNode(node->right);
    destroyRopeNode(node);
    free(node);
}

void destroyRope(Rope *self) {
    _destroyNode(self->root);
}
