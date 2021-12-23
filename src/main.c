#include <stdio.h>
#include <stdlib.h>
#include <string.h> // required for strcmp()
#include <stdbool.h> // required to use idiomatically the boolean type

#include "headers/utils.h"
#include "headers/colors.h"
#include "headers/experiments.h"

const bool DEBUG = false; // this flag toggles debug checks (e.g. it checks if the data structures work correctly)

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Wrong number of arguments supplied.\n");
        error_menu(argv);

        exit(EXIT_FAILURE);
    }

    /* Lab. 1A configurations */
    Configuration lab1A_conf;
    lab1A_conf.min_keys = 0; // minimum number of keys in the tree
    lab1A_conf.max_keys = 100000; // maximum number of keys in the tree
    lab1A_conf.max_instances = 100; // how many times to repeat the same test
    lab1A_conf.step = 1000; // the amount of keys will grow this much at each test
    lab1A_conf.search_delete_ratio = 60; // ratio of insertions/deletions
    lab1A_conf.seed = 10; // srand()'s starting seed

    /* Lab. 1B configurations */
    Configuration lab1B_conf;
    lab1B_conf.min_keys = 0; // minimum number of keys in the tree
    lab1B_conf.max_keys = 10000; // maximum number of keys in the tree
    lab1B_conf.max_instances = 100; // how many times to repeat the same test
    lab1B_conf.step = 250; // the amount of keys will grow this much at each test
    lab1B_conf.search_delete_ratio = 60; // ratio of insertions/deletions
    lab1B_conf.seed = 10; // srand()'s starting seed

    /* Lab. 2 configurations */
    Configuration lab2_conf;
    lab2_conf.min_keys = 0; // minimum number of keys in the tree
    lab2_conf.max_keys = 1000000; // maximum number of keys in the tree
    lab2_conf.max_instances = 50; // how many times to repeat the same test
    lab2_conf.step = 10000; // the amount of keys will grow this much at each test
    lab2_conf.search_delete_ratio = 60; // ratio of insertions/deletions
    lab2_conf.seed = 10; // srand()'s starting seed

    if (strcmp(argv[1], "1A") == 0) {
        bold_yellow(), printf("Running Lab. 1A (Binary Search Trees)... ");
        reset_color(), fflush(stdout);

        /* Lab. 1A - (BSTs) Binary Search Trees */
        lab_1A("../results/lab_1/1A/lab_1A.csv", lab1A_conf, DEBUG);
    } else if (strcmp(argv[1], "1B") == 0) {
        bold_yellow(), printf("Running Lab. 1B (Linked Lists, Binary Search Trees)... ");
        reset_color(), fflush(stdout);

        /* Lab. 1B - (LLs) Linked Lists, (BSTs) Binary Search Trees */
        lab_1B("../results/lab_1/1B/lab_1B.csv", lab1B_conf, DEBUG);
    } else if (strcmp(argv[1], "2") == 0) {
        bold_yellow(), printf("Running Lab. 2 (Red-Black Trees, Binary Search Trees)... ");
        reset_color(), fflush(stdout);

        /* Lab. 2 - (RBTs) Red-Black Trees, (BSTs) Binary Search Trees */
        lab_2("../results/lab_2/lab_2.csv", lab2_conf, DEBUG);
    } else if (strcmp(argv[1], "3") == 0) {
        bold_yellow(), printf("Running Lab. 3 (B-Trees, Red-Black Trees, Binary Search Trees)... ");
        reset_color(), fflush(stdout);

        /* Lab. 3 - (BTs) B-Trees */
    } else if (strcmp(argv[1], "4") == 0) {
        bold_yellow(), printf("Running everything (LLs, BSTs, RBTs, BTs)... ");
        reset_color(), fflush(stdout);

        /* Everything */
    } else {
        fprintf(stderr, "Invalid argument supplied: `%s`\n", argv[1]);
        error_menu(argv);

        exit(EXIT_FAILURE);
    }

    bold_green(), printf("Done!\n"), reset_color(); // if we arrive here, the experiment were successful

    /* Automatic plotter (Python script) */
    plotter(); // the function handles potential errors

    return EXIT_SUCCESS;
}
