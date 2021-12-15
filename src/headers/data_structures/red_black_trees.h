// Header guards:
// patterns of preprocessor directives that protect a header from being included multiple times
#ifndef DS_RED_BLACK_TREES_H
#define DS_RED_BLACK_TREES_H

#include <stdlib.h>

// the nodes will either be "red" or "black"
typedef enum color {
    RED = 0,
    BLACK = 1,
} Color;

typedef struct rbt_node {
    int key;
    Color color;
    struct rbt_node *parent;
    struct rbt_node *left;
    struct rbt_node *right;
} RBTNode;

typedef struct rbt_tree {
    size_t cardinality; // practical usage: it'll define the dimension of the arrays we'll use for "TreeWalks"
    struct rbt_node *nil;  // sentinel node `T.nil`
    struct rbt_node *root;
} RBTTree;

RBTTree *RBTNewTree(RBTNode *x);

RBTNode *RBTSearch(RBTTree *T, RBTNode *x, int k);

void RBTInsertKey(RBTTree *T, int key);

RBTNode *RBTIterativeSearch(RBTTree *T, RBTNode *x, int k);

// Returns true on success, false on failure (if you try to delete a non-existing key)
bool RBTDeleteKey(RBTTree *T, int k);

void RBTDestroyTree(RBTTree *T);

#endif //DS_RED_BLACK_TREES_H

// #pragma once
// an alternative to header guards
