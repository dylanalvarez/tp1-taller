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
// Post: left and right are created, the first n characters
//       being n = left_length go to left and the rest, to right.
//       SOURCE NEEDS TO BE DESTROYED
void splitRopeNode(
        RopeNode *source, size_t left_length,
        RopeNode *left_destination,
        RopeNode *right_destination
);

void destroyRopeNode(RopeNode *self);

#endif //TP1_TALLER_NODE_H
