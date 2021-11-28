// Header guards:
// patterns of preprocessor directives that protect a header from being included multiple times
#ifndef BINARY_TREES_EXPERIMENTS_H
#define BINARY_TREES_EXPERIMENTS_H

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

// Lab. 1 - Binary Search Trees
void lab_1(char file[], Configuration conf, bool DEBUG);

#endif //BINARY_TREES_EXPERIMENTS_H

// #pragma once
// an alternative to header guards
