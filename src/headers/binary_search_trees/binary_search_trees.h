// Header guards:
// patterns of preprocessor directives that protect a header from being included multiple times
#ifndef BINARY_TREES_BINARY_SEARCH_TREES_H
#define BINARY_TREES_BINARY_SEARCH_TREES_H

#include <stdlib.h>

typedef struct bst_node {
    int key;
    struct bst_node* parent;
    struct bst_node* left_child;
    struct bst_node* right_child;
} BSTNode;

typedef struct bst_tree {
    size_t cardinality; // practical usage: it'll define the dimension of the arrays we'll use for "TreeWalks"
    struct bst_node* root;
} BSTTree;

BSTNode *BSTTreeSearch(BSTNode *x, int k); // `x` is the "root" of the tree, `k` is the key we're looking for

BSTNode *BSTIterativeTreeSearch(BSTNode *x, int k); // `x` is the "root" of the tree, `k` is the key we're looking for

BSTNode *BSTTreeMinimum(BSTNode *x);

BSTNode *BSTTreeMaximum(BSTNode *x);

BSTNode *BSTTreeSuccessor(BSTNode *x);

BSTNode *BSTTreePredecessor(BSTNode *x);

void BSTTreeInsert(BSTTree T, int k);

BSTTree *BSTNewTree(BSTNode *x); // `x` can be NULL, but if it isn't then a new BSTNode gets instantiated

void BSTTreeDelete(BSTTree T, BSTNode z);

#endif //BINARY_TREES_BINARY_SEARCH_TREES_H

// #pragma once
// an alternative to header guards
