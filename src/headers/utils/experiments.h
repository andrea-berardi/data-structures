// Header guards:
// patterns of preprocessor directives that protect a header from being included multiple times
#ifndef DS_EXPERIMENTS_H
#define DS_EXPERIMENTS_H

#include <stdlib.h>

/**
 ** @file experiments.h
 ** @brief Utils functions
 ** @author Andrea Berardi
 ** @date 20/02/2022
 **/

// Configuration
typedef struct {
    size_t min_keys; // minimum number of keys
    size_t max_keys; // maximum number of keys
    size_t max_instances; // maximum number of instances (how many times the experiment is run)
    size_t step; // step between min and max keys
    size_t search_delete_ratio; // percentage of searches (60 = 60% searches / 40% deletions)
    unsigned int seed; // seed for random number generator
    ssize_t t; // `t` of B-Trees
} Configuration;

// Enumeration of the available data structures
typedef enum data_structures {
    LL = 0, // Linked List
    BST = 1, // Binary Search Tree
    // RBT = 2, // Red-Black Tree
    // BT = 3, // B-Tree
} DataStructure;

// Lab. 1A - Binary Search Trees
void lab_1A(char file[], Configuration conf);

// Lab. 1B - Linked Lists, Binary Search Trees
void lab_1B(char file[], Configuration conf);

// Lab. 2 - Binary Search Trees, Red-Black Trees
void lab_2(char file[], Configuration conf);

// Lab. 3 - B-Trees, Binary Search Trees, Red-Black Trees
void lab_3(char file[], Configuration conf);

// Final experiment - B-Trees
void lab_final(char file[], Configuration conf);

#endif //DS_EXPERIMENTS_H

// #pragma once
// an alternative to header guards
