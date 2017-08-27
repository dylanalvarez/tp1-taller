#ifndef TP1_TALLER_ROPE_H
#define TP1_TALLER_ROPE_H

#include "node.h"

typedef struct {
    RopeNode *root;
} Rope;

void createEmptyRope(Rope *self);

// Post: self is a rope containing the passed in string.
void createRope(Rope *self, const char *content);

// Pre:  left and right are both distinct created ropes.
// Post: left and right are both destroyed,
//       destination is created with their contents.
void concatRopes(
        Rope *left_source,
        Rope *right_source,
        Rope *destination
);

// Pre:  source is a created rope, left_length is a number between 0 and
//       getRopeContentLength(&source)
// Post: source is destroyed, left and right are created, the first n characters
//       being n = left_length go to left and the rest, to right.
void splitRope(
        Rope *source, size_t characters_to_left,
        Rope *left_destination,
        Rope *right_destination
);

// Pre:  index is a number between 0 and getRopeContentLength(&self)
//       index can be negative: it is -1 for inserting in
//       getRopeContentLength(&self) and -n for inserting in
//       getRopeContentLength(&self) - n + 1.
//       in that case, it has to be between - getRopeContentLength(&self) - 1
//       and -1.
// Post: the passed in string is inserted beginning in (and including)
//       position "index"
void insert(Rope *self, const char *content, int index);

// Pre:  from < to, both "from" and "to" are numbers between 0 and
//       getRopeContentLength(&self)
//       index can be negative: it has to be between
//       - getRopeContentLength(&self) - 1 and -1.
// Post: the rope's characters in positions between "from" (including if the
//       index is positive, not including if it's negative) and (not including
//       if the index is positive, including if it's negative)
//       "to" are removed.
void delete(Rope *self, int from, int to);

// Post: returns length of the string contained within self
//       it's faster than calling strlen on getRopeContent
size_t getRopeContentLength(Rope *self);

// Pre:  buffer's length is at least getRopeContentLength(&self) + 1 bytes
// Post: buffer contains the string contained within self
void getRopeContent(Rope *self, char *buffer);

//Pre:  index is a number between 0 and getRopeContentLength(&self)
char getRopeContentAtIndex(Rope *self, size_t index);

void destroyRope(Rope *self);

#endif //TP1_TALLER_ROPE_H
