// Header guards:
// patterns of preprocessor directives that protect a header from being included multiple times
#ifndef DATA_STRUCTURES_B_TREES_H
#define DATA_STRUCTURES_B_TREES_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct bt_node {
    size_t t; // capacity of the node (number of keys that can be stored)
    size_t n; // cardinality of keys in the node (number of keys actually stored)
    int *keys; // keys actually stored in the node (NOT in descending order)
    bool leaf; // `true` if the node is a leaf, `false` if it's an internal node
    struct bt_node *parent; // pointer to the parent node
    struct bt_node **children; // array of pointers to the children
} BTNode;

typedef struct bt_tree {
    size_t t; // total number of keys in the data structure
    struct bt_node *root; // regular node, stored in the main memory
} BTTree;

// this is necessary because you cannot return two items from a function, unless they're in a struct
typedef struct node_and_index {
    BTNode *node;
    size_t index;
} NodeAndIndex;

BTTree *BTNewTree(size_t t);
NodeAndIndex BTSearch(BTNode *x, int k);


#endif //DATA_STRUCTURES_B_TREES_H

// #pragma once
// an alternative to header guards
