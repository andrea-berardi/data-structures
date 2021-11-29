// Header guards:
// patterns of preprocessor directives that protect a header from being included multiple times
#ifndef TREES_UTILS_H
#define TREES_UTILS_H

#include <stdlib.h> // in order to get the `size_t` type
#include <stdbool.h> // imports the boolean type for more idiomatic code

#include "linked_lists.h"
#include "binary_search_trees.h"

// Generate a new, uninitialized, array of integers, given its length
int *new_array(size_t length);

// Generate a new random array, given its length
int *gen_rnd_array(size_t length);

// Check if a given array is sorted (ascending order)
bool is_sorted(const int array[], size_t length);

// Prints to stdout a given array
void print_array(const int array[], size_t length);

// Populates an array passed as argument while walking a Linked List
void LLListWalkToArray(LLHead *L, int array[]);

// Populates an array passed as argument while walking a BST (InOrderTreeWalk)
void BSTInOrderTreeWalkToArray(BSTNode *x, int array[], size_t *index);

#endif //TREES_UTILS_H

// #pragma once
// an alternative to header guards
