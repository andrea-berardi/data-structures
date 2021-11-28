// Header guards:
// patterns of preprocessor directives that protect a header from being included multiple times
#ifndef BINARY_TREES_BST_UTILS_H
#define BINARY_TREES_BST_UTILS_H

#include <stdlib.h>

void BSTInOrderTreeWalkToArray(BSTNode *x, int array[], size_t* index); // `x` is the "root" of the tree we want to walk

void BSTPreOrderTreeWalk(BSTTree *x, int array[], size_t index); // `x` is the "root" of the tree we want to walk

void BSTPostOrderTreeWalk(BSTTree *x, int array[], size_t index); // `x` is the "root" of the tree we want to walk

#endif //BINARY_TREES_BST_UTILS_H

// #pragma once
// an alternative to header guards
