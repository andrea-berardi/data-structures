// Header guards:
// patterns of preprocessor directives that protect a header from being included multiple times
#ifndef DS_BINARY_SEARCH_TREES_H
#define DS_BINARY_SEARCH_TREES_H

#include <stdlib.h>

typedef struct bst_node {
    int key;
    struct bst_node *parent;
    struct bst_node *left;
    struct bst_node *right;
} BSTNode;

typedef struct bst_tree {
    size_t cardinality; // practical usage: it'll define the dimension of the arrays we'll use for "TreeWalks"
    struct bst_node *root;
} BSTTree;

BSTNode *BSTSearch(BSTNode *x, int k); // `x` is the "root" of the tree, `k` is the key we're looking for

BSTNode *BSTIterativeSearch(BSTNode *x, int k); // `x` is the "root" of the tree, `k` is the key we're looking for

BSTNode *BSTMinimum(BSTNode *x);

BSTNode *BSTMaximum(BSTNode *x);

// BSTNode *BSTSuccessor(BSTNode *x); // unused

// BSTNode *BSTPredecessor(BSTNode *x); // unused

void BSTInsertKey(BSTTree *T, int k);

BSTTree *BSTNewTree(BSTNode *x); // `x` can be NULL, but if it isn't then a new BSTNode gets instantiated

void BSTDeleteKey(BSTTree *T, int k);

// this procedure destroys every node of a tree (faster than `BSTEmptyTreePreserveStructure()`)
void BSTDestroyTree(BSTTree *T);

// this procedure destroys every node of a tree BUT preserves the structure of the BST while running
// void BSTEmptyTreePreserveStructure(BSTTree *T, BSTNode *x); // unused

#endif //DS_BINARY_SEARCH_TREES_H

// #pragma once
// an alternative to header guards
