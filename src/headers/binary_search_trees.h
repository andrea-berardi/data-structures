// Header guards:
// patterns of preprocessor directives that protect a header from being included multiple times
#ifndef BINARY_TREES_BINARY_SEARCH_TREES_H
#define BINARY_TREES_BINARY_SEARCH_TREES_H

typedef struct bst_node {
    int key;
    struct bst_node* parent;
    struct bst_node* left_child;
    struct bst_node* right_child;
} BSTNode;

typedef struct bst_tree {
    // size_t cardinality; // Do we need this field? Is the overhead of keeping this field updated justified?
    struct bst_node* root;
} BSTTree;

void BSTTreeInOrderTreeWalk(BSTTree x); // `x` is the "root" of the tree we want to walk

void BSTTreePreOrderTreeWalk(BSTTree x); // `x` is the "root" of the tree we want to walk

void BSTTreePostOrderTreeWalk(BSTTree x); // `x` is the "root" of the tree we want to walk

void BSTTreesSearch(BSTNode x, int k); // `x` is the "root" of the tree, `k` is the key we're looking for

#endif //BINARY_TREES_BINARY_SEARCH_TREES_H

// #pragma once
// an alternative to header guards
