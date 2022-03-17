cmake_minimum_required(VERSION 3.20)
project(data_structures C)

set(CMAKE_C_STANDARD 11)

add_executable(data_structures src/main.c src/modules/data_structures/binary_search_trees.c src/headers/data_structures/binary_search_trees.h src/headers/utils/experiments.h src/modules/experiments/lab_1A.c src/modules/utils/utils.c src/headers/utils/utils.h src/modules/data_structures/linked_lists.c src/headers/data_structures/linked_lists.h src/modules/experiments/lab_1B.c src/modules/data_structures/red_black_trees.c src/headers/data_structures/red_black_trees.h src/modules/experiments/lab_2.c src/modules/utils/colors.c src/headers/utils/colors.h src/modules/data_structures/b_trees.c src/headers/data_structures/b_trees.h src/modules/experiments/lab_3.c src/modules/experiments/lab_final.c src/modules/utils/tests.c src/headers/utils/tests.h)

# This enables extra compiler warnings, and more "pedantic" checks
# set(CMAKE_C_FLAGS "-Wall -Werror -Wextra -pedantic")
set(CMAKE_C_FLAGS "-Wall -Wextra -pedantic")

# This enables runtime sanity checks (this will slow down the executable by a lot!)
# Currently it is enabled only for debug builds.
# Why? It is mandatory to ensure that the executables are free from bugs and Undefined Behaviors
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} -fsanitize=address -fsanitize=undefined -fsanitize=leak -g")

# Release builda flags
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS} -O3")
