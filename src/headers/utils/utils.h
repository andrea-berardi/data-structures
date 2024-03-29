// Header guards:
// patterns of preprocessor directives that protect a header from being included multiple times
#ifndef DS_UTILS_H
#define DS_UTILS_H

#include <stdlib.h> // in order to get the `size_t` type
#include <stdbool.h> // imports the boolean type for more idiomatic code

#include "../data_structures/linked_lists.h"
#include "../data_structures/red_black_trees.h"
#include "../data_structures/binary_search_trees.h"
#include "../data_structures/b_trees.h"

/**
 ** @file utils.h
 ** @brief Utils functions
 ** @author Andrea Berardi
 ** @date 20/02/2022
 **/

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

// Populates an array passed as argument while walking a RBT (InOrderTreeWalk)
void RBTInOrderTreeWalkToArray(RBTTree *T, RBTNode *x, int array[], size_t *index);

// Error messages to print in case of bad input
void error_menu(char *argv[]);

// Python Plotter
void plotter(char s[]);

#endif //DS_UTILS_H

// #pragma once
// an alternative to header guards
