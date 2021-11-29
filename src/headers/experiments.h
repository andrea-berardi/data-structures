// Header guards:
// patterns of preprocessor directives that protect a header from being included multiple times
#ifndef TREES_EXPERIMENTS_H
#define TREES_EXPERIMENTS_H

#include <stdlib.h>

// Configuration
typedef struct {
    size_t min_keys;
    size_t max_keys;
    size_t max_instances;
    size_t step;
    size_t search_delete_ratio; // percentage of searches (60 = 60% searches / 40% deletions)
    unsigned int seed;
} Configuration;

// Enumeration of the available data structures
typedef enum data_structures {
    LL = 0, // Linked List
    BST = 1, // Binary Search Tree
    RBT = 2, // Red-Black Tree
    BT = 3, // B-Tree
} DataStructure;

// Lab. 1 - Binary Search Trees
void lab_1A(char file[], Configuration conf, bool DEBUG);

// Lab. 1A - Linked Lists, Binary Search Trees
void lab_1B(char file[], Configuration conf, bool DEBUG);

#endif //TREES_EXPERIMENTS_H

// #pragma once
// an alternative to header guards
