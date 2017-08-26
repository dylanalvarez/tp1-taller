#ifndef TP1_TALLER_NODE_H
#define TP1_TALLER_NODE_H

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct RopeNode {
    char *content;
    size_t weight;
    struct RopeNode *left;
    struct RopeNode *right;
} RopeNode;

// Post: self is a rope node containing a copy of the passed in string
void createRopeNode(RopeNode *self, const char *content);

// Pre:  self is a created rope
bool isLeaf(RopeNode *self);

// Pre:  source is a created rope node, it isLeaf(), left_length is a number
//       between 0 and strlen(source->content), it has content.
// Post: left and right are created, the first n characters being
//       n = left_length go to left and the rest, to right.
//       SOURCE, LEFT AND RIGHT WILL NEED TO BE DESTROYED
void splitRopeNode(
        RopeNode *self,
        size_t left_length,
        RopeNode *left,
        RopeNode *right
);

// Post: gets sum of string lengths contained inside self
//       and its (direct and indirect) children.
size_t getSubRopeContentLength(RopeNode *self);

// Pre:  left_child can be NULL.
// Post: self->left == left_child, self's weight is updated.
void appendLeftChild(RopeNode *self, RopeNode *left_child);

// Pre:  right_child can be NULL.
// Post: self->right == right_child, self's weight is updated
void appendRightChild(RopeNode *self, RopeNode *right_child);

void destroyRopeNode(RopeNode *self);

#endif //TP1_TALLER_NODE_H
