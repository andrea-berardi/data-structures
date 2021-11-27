cmake_minimum_required(VERSION 3.20)
project(binary_trees C)

set(CMAKE_C_STANDARD 11)

add_executable(binary_trees src/main.c src/modules/binary_search_trees/binary_search_trees.c src/headers/binary_search_trees/binary_search_trees.h src/modules/binary_search_trees/bst_utils.c src/headers/binary_search_trees/bst_utils.h)

# This enables extra compiler warnings, and more "pedantic" checks
set(CMAKE_C_FLAGS "-Wall -Wextra -pedantic")

# This enables runtime sanity checks (this will slow down the executable by a lot!)
# Currently it is enabled only for debug builds.
# Why? It is mandatory to ensure that the executables are free from bugs and Undefined Behaviors
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} -fsanitize=address -fsanitize=undefined -fsanitize=leak -g")

set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS} -O3")

# set(CMAKE_VERBOSE_MAKEFILE ON)