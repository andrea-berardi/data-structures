// Header guards:
// patterns of preprocessor directives that protect a header from being included multiple times
#ifndef BINARY_TREES_EXPERIMENTS_H
#define BINARY_TREES_EXPERIMENTS_H

#include <stdlib.h>

// Configuration
typedef struct {
    ssize_t min_keys;
    ssize_t max_keys;
    size_t max_instances;
    ssize_t step;
    ssize_t search_delete_ratio; // percentage of searches (60 = 60% searches / 40% deletions)
    unsigned int seed;
} Configuration;

#endif //BINARY_TREES_EXPERIMENTS_H

// #pragma once
// an alternative to header guards
