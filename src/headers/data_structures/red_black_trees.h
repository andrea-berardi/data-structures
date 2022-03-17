// Header guards:
// patterns of preprocessor directives that protect a header from being included multiple times
#ifndef DS_RED_BLACK_TREES_H
#define DS_RED_BLACK_TREES_H

#include <stdlib.h>

/**
 ** @file red_black_trees.h
 ** @brief Red-Black Trees implementation (header)
 ** @author Andrea Berardi
 ** @date 20/02/2022
 **/

/**
 ** @brief Red-Black Tree node's color (either red or black)
 **/
typedef enum color {
    RED = 0,
    BLACK = 1,
} Color;

/**
 ** @brief Red-Black Tree node
 **/
typedef struct rbt_node {
    int key; // key of the node
    Color color; // color of the node
    struct rbt_node *parent; // parent of the node
    struct rbt_node *left; // left child of the node
    struct rbt_node *right; // right child of the node
} RBTNode;

/**
 ** @brief Red-Black Tree
 **/
typedef struct rbt_tree {
    size_t cardinality; // practical usage: it'll define the dimension of the arrays we'll use for "TreeWalks"
    struct rbt_node *nil;  // sentinel node `T.nil`
    struct rbt_node *root; // root node of the tree
} RBTTree;

RBTTree *RBTNewTree(RBTNode *x);

void RBTInsertKey(RBTTree *T, int key);

RBTNode *RBTIterativeSearch(RBTTree *T, RBTNode *x, int k);

// Returns true on success, false on failure (if you try to delete a non-existing key)
bool RBTDeleteKey(RBTTree *T, int k);

void RBTDestroyTree(RBTTree *T);

#endif //DS_RED_BLACK_TREES_H

// #pragma once
// an alternative to header guards
