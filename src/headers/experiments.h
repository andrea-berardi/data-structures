// Header guards:
// patterns of preprocessor directives that protect a header from being included multiple times
#ifndef DS_EXPERIMENTS_H
#define DS_EXPERIMENTS_H

#include <stdlib.h>

// Configuration
typedef struct {
    size_t min_keys;
    size_t max_keys;
    size_t max_instances;
    size_t step;
    size_t search_delete_ratio; // percentage of searches (60 = 60% searches / 40% deletions)
    unsigned int seed;
    ssize_t t; // `t` of B-Trees
} Configuration;

// Enumeration of the available data structures
typedef enum data_structures {
    LL = 0, // Linked List
    BST = 1, // Binary Search Tree
    RBT = 2, // Red-Black Tree
    BT = 3, // B-Tree
} DataStructure;

// Lab. 1A - Binary Search Trees
void lab_1A(char file[], Configuration conf, bool DEBUG);

// Lab. 1B - Linked Lists, Binary Search Trees
void lab_1B(char file[], Configuration conf, bool DEBUG);

// Lab. 2 - Binary Search Trees, Red-Black Trees
void lab_2(char file[], Configuration conf, bool DEBUG);

// Lab. 3 - B-Trees
void lab_3(char file[], Configuration conf, bool DEBUG);

#endif //DS_EXPERIMENTS_H

// #pragma once
// an alternative to header guards
