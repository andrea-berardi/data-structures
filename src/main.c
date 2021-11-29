#include <stdio.h>
#include <stdlib.h>
#include <string.h> // required for strcmp()
#include <stdbool.h> // required to use idiomatically the boolean type

#include "headers/experiments.h"

const bool DEBUG = false; // this flag toggles debug checks (e.g. it checks if the algorithms sort correctly)

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Wrong number of arguments supplied.\n");
        fprintf(stderr, "Usage: `.%s <1-4>`.\n", argv[0]);
        fprintf(stderr, "Please specify which test you want to run:\n");
        fprintf(stderr, "1) Lab. 1\n2) Lab. 2\n3) Lab. 3\n5) Everything\n");

        exit(EXIT_FAILURE);
    }

    /* Lab. 1 configurations */
    Configuration lab1_conf;
    lab1_conf.min_keys = 0; // minimum number of keys in the tree
    lab1_conf.max_keys = 10000; // maximum number of keys in the tree
    lab1_conf.max_instances = 100; // how many times to repeat the same test
    lab1_conf.step = 250; // the amount of keys will grow this much at each test
    lab1_conf.search_delete_ratio = 60; // ratio of insertions/deletions
    lab1_conf.seed = 10; // srand()'s starting seed

    /* Lab. 1A configurations */
    Configuration lab1A_conf;
    lab1_conf.min_keys = 0; // minimum number of keys in the tree
    lab1_conf.max_keys = 10000; // maximum number of keys in the tree
    lab1_conf.max_instances = 100; // how many times to repeat the same test
    lab1_conf.step = 250; // the amount of keys will grow this much at each test
    lab1_conf.search_delete_ratio = 60; // ratio of insertions/deletions
    lab1_conf.seed = 10; // srand()'s starting seed

    if (strcmp(argv[1], "1") == 0) {
        /* Lab. 1 - (BSTs) Binary Search Trees */
        lab_1("../results/lab_1/lab_1.csv", lab1_conf, DEBUG);
    } else if (strcmp(argv[1], "1A") == 0) {
        /* Lab. 1 - (LLs) Linked Lists, (BSTs) Binary Search Trees */
        lab_1A("../results/lab_1A/lab_1A.csv", lab1A_conf, DEBUG);
    } else if (strcmp(argv[1], "2") == 0) {
        /* Lab. 2 - (RBTs) Red-Black Trees */
    } else {
        fprintf(stderr, "Invalid argument supplied: `%s`\n", argv[1]);
        fprintf(stderr, "Usage: `.%s <1-4>`.\n", argv[0]);
        fprintf(stderr, "Please specify which test you want to run:\n");
        fprintf(stderr, "1) Lab. 1\n2) Lab. 2\n3) Lab. 3\n5) Everything\n");

        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
