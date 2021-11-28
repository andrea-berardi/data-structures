#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../../headers/utils.h"
#include "../../headers/experiments.h"
#include "../../headers/binary_search_trees/binary_search_trees.h"

long double experiment(size_t max_keys, size_t max_search, size_t max_delete, size_t max_instances, const bool DEBUG) {
    clock_t t_tot = 0;

    for (size_t instance = 1; instance <= max_instances; ++instance) {
        clock_t t_start, t_end;

        // I'm creating these arrays of random integer values for many reasons:
        // - I can keep track of what I'm generating
        // - I won't be adding any overheads by using the modulus operator (%) during the experiments
        // - By using "good" values I'll be able to tell if weird things are happening to my arrays
        // - I'll be able to compare the generated arrays and the generated BSTs
        // Also, I'm using different arrays in order not to create outliers.
        int *rand_insert_values_pool = gen_rnd_array(max_keys);
        int *rand_search_values_pool = gen_rnd_array(max_search);
        int *rand_delete_values_pool = gen_rnd_array(max_delete);

        // I'll use these indexes to scan the arrays. They'll be incremented at each run.
        size_t insert_index = 0;
        size_t search_index = 0;
        size_t delete_index = 0;

        BSTTree *T = BSTNewTree(NULL);

        t_start = clock();
        for (size_t key = 0; key < max_keys; ++key) {
            BSTTreeInsertKey(T, rand_insert_values_pool[insert_index++]); // it's important to use `i++` instead of `++i` here
        }

        for (size_t key = 0; key < max_search; ++key) {
            BSTTreeSearch(T->root, rand_search_values_pool[search_index++]); // it's important to use `i++` instead of `++i` here
        }

        for (size_t key = 0; key < max_delete; ++key) {
            BSTTreeDeleteKey(T, rand_delete_values_pool[delete_index++]); // it's important to use `i++` instead of `++i` here
        }
        t_end = clock();

        t_tot += t_end - t_start;

        if (DEBUG) {
            //printf("%zu = %zu - %zu\n", t_end - t_start, t_end, t_start);
            //printf("%zu / %zu = %Lf\n", t_tot, max_instances, (long double) t_tot / (long double) max_instances);

            /*if (is_sorted(array, length))
                printf("Array sorted successfully (length: %ld)\n", length);
            else
                fprintf(stderr, "The array was not sorted correctly.\n"), print_array(array, length);*/
        }

        BSTTreeDestroyTree(T); // destroying the tree and all its leaves (nodes)
        T = NULL;

        free(rand_insert_values_pool);
        rand_insert_values_pool = NULL;
        free(rand_search_values_pool);
        rand_search_values_pool = NULL;
        free(rand_delete_values_pool);
        rand_delete_values_pool = NULL;
    }

    return (long double) t_tot / (long double) max_instances;
}

void lab_1(char file[], Configuration conf, const bool DEBUG) {
    FILE *fp = fopen(file, "w+");
    if (fp == NULL) {
        fprintf(stderr, "Failed to open file `%s`\n", file);
        exit(EXIT_FAILURE);
    }

    fprintf(fp, "Keys (n),Binary Search Trees\n");
    for (size_t keys = conf.min_keys; keys <= conf.max_keys; keys += conf.step) {
        srand(conf.seed);

        size_t max_search = keys * conf.search_delete_ratio / 100;
        size_t max_delete = keys - max_search;

        long double time_BST = experiment(keys, max_search, max_delete, conf.max_instances, DEBUG);

        fprintf(fp, "%zu,%Lf\n", keys, time_BST);

        ++conf.seed;
    }

    if (fclose(fp) == EOF)
        fprintf(stderr, "Failed to flush buffered data on `%s`\n", file);
}
