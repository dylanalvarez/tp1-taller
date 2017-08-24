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

void destroyRopeNode(RopeNode *self);

#endif //TP1_TALLER_NODE_H
