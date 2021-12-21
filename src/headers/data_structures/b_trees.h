// Header guards:
// patterns of preprocessor directives that protect a header from being included multiple times
#ifndef DATA_STRUCTURES_B_TREES_H
#define DATA_STRUCTURES_B_TREES_H

#include <stdlib.h>
#include <stdbool.h>

#define t 1000 // maximum numbers of keys that a node can have - it has to be >= 2

typedef struct bt_node {
    size_t n; // cardinality of the node
    int keys[2 * t]; // keys actually stored in the node (NOT in descending order)
    bool leaf; // `true` if the node is a leaf, `false` if it's an internal node
    struct bt_node *parent; // pointer to the parent node
    struct bt_node *children[2 * t + 1]; // pointers to the children
} BTNode;

typedef struct bt_tree {
    size_t cardinality; // total number of keys in the data structure
    struct bt_node *root; // regular node, stored in the main memory
} BTTree;

void DiskRead(BTNode x[]);
void DiskWrite(BTNode *x);

#endif //DATA_STRUCTURES_B_TREES_H

// #pragma once
// an alternative to header guards
