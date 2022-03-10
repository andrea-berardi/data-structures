# Data Structures

[![LICENSE](https://badgen.net/badge/Support/Ukraine/?color=0057B8&labelColor=FFD700)](https://www.icrc.org/en/donate/ukraine)
[![LICENSE](https://img.shields.io/badge/license-AGPLv3-blue)](https://github.com/andrea-berardi/trees/blob/main/LICENSE)
[![CMake Build Status](https://github.com/andrea-berardi/data-structures/actions/workflows/cmake.yml/badge.svg)](https://github.com/andrea-berardi/data-structures/actions)

This repository implements many data structures and their associated algorithms, and provides a ready to use environment to easily test them.

## Table of Contents

Here's what you'll find on this document:

- [About](#about)
- [Data Structures implemented](#data-structures-implemented)
- [Project Structure](#project-structure)
- [Notes](#notes)
- [Laboratories](#laboratories)
  - [Lab. 1A](#lab-1a)
  - [Lab. 1B](#lab-1b)
  - [Lab. 2](#lab-2)
  - [Lab. 3](#lab-3)
  - [Final experiment](#final-experiment)
- [Bibliography](#bibliography)

## About

This repository contains a simple implementation of some (cool) data structures.
This is the second part of an assignment of a course on algorithms and data structures, the first half regarding sorting algorithms, can be found [here](https://github.com/andrea-berardi/sorting-algorithms).
The thought behind the project is to create an enviroment that allows for easy performance testing.

## Data Structures implemented

- [x] Linked Lists (personal test, **not** required by the lab.)
- [x] Binary Search Trees
- [x] RB-Trees (_Red-Black Trees_)
- [x] B-Trees

## Project Structure

Folders and files of this project.

```mono
data-structures
├── CMakeLists.txt
├── docs
│  ├── Laboratorio (1) - BST.pdf
│  ├── Laboratorio (2) - RBT.pdf
│  └── Laboratorio (3) - BT.pdf
├── LICENSE
├── README.md
├── results
│  ├── final
│  │  ├── final.csv
│  │  └── final.png
│  ├── lab_1
│  │  ├── 1A
│  │  │  ├── lab_1A.csv
│  │  │  └── lab_1A.png
│  │  └── 1B
│  │     ├── lab_1B.csv
│  │     └── lab_1B.png
│  ├── lab_2
│  │  ├── lab_2.csv
│  │  └── lab_2.png
│  └── lab_3
│     ├── lab_3.csv
│     └── lab_3.png
├── SECURITY.md
└── src
   ├── headers
   │  ├── data_structures
   │  │  ├── b_trees.h
   │  │  ├── binary_search_trees.h
   │  │  ├── linked_lists.h
   │  │  └── red_black_trees.h
   │  └── utils
   │     ├── colors.h
   │     ├── experiments.h
   │     ├── tests.h
   │     └── utils.h
   ├── main.c
   └── modules
      ├── data_structures
      │  ├── b_trees.c
      │  ├── binary_search_trees.c
      │  ├── linked_lists.c
      │  └── red_black_trees.c
      ├── experiments
      │  ├── lab_1A.c
      │  ├── lab_1B.c
      │  ├── lab_2.c
      │  ├── lab_3.c
      │  └── lab_final.c
      └── utils
         ├── colors.c
         ├── plotter.py
         ├── tests.c
         └── utils.c
```

## Notes

Unless I'm missing something, the project should be 100% free from:

- :cyclone: Undefined Behaviors (checked with Clang's sanitizers)
- :bug: Bugs (_hopefully_)
- :sweat_drops: Memory Leaks (checks made with Clang and Valgrind)

The `CMakeLists.txt` (build file) ensures that debug builds have runtime sanity checks (provided by Clang) and the absence of warnings*°^ hints that there aren't weird things going on. In addition, Cppcheck (a static C/C++ code analyzer) and Valgrind confirmed that everything is compliant and safe. The `DEBUG` flag on the code even allows performing additional correctness checks (it ensures the data structures work correctly by using many antagonist functions). I'm keeping it as a `const` flag to allow the compiler to better optimize the code when it is set to `false` (hopefully it recognizes that its value never changes and removes the `if` branch of the checks completely from the binary).

I'm planning to add more specific directions on how to run the project, but afaik it should be already out-of-the-box.

I use CLion as my IDE and Clang as my compiler. The project manager is CMake.

I tried to keep the algorithms as close as possible to those shown on the book _Introduction to Algorithms_, but it wasn't always possible. Nevertheless, I have **not** used any additional resources apart my professor's PDFs and my tutor's laboratory documentations.

_\*: Unfortunately there's a tiny warning due to my use of `rand()` in the `gen_rand_array()` function. Basically, the IDE is saying that it has limited randomness, which is fine and totally expected. Please ignore._

_°: The warnings about recursive calls can be ignored too, they're necessary to make some algorithms work properly._

_^: I have not yet decided how to deal with unused functions._

## Laboratories

The following pictures show the performance of the data structures.

The `X` axis represents the amount of keys that will be stored on the data structures.

The `Y` axis represents the time it took to run some operations on them (insertion, search and deletion of keys). It is calculated using C's `clock()` function, provided by the `time.h` library.

Yes, the pictures have watermarks, because why not.

### Lab. 1A

Binary Search Trees

![Binary Search Trees](https://github.com/andrea-berardi/data-structures/blob/main/results/lab_1/1A/lab_1A.png?raw=true)

### Lab. 1B

Linked Lists, Binary Search Trees

![Linked Lists, Binary Search Trees](https://github.com/andrea-berardi/data-structures/blob/main/results/lab_1/1B/lab_1B.png?raw=true)

### Lab. 2

Red-Black Trees, Binary Search Trees

![Red-Black Trees](https://github.com/andrea-berardi/data-structures/blob/main/results/lab_2/lab_2.png?raw=true)

### Lab. 3

B-Trees, Red-Black Trees, Binary Search Trees

![B-Trees](https://github.com/andrea-berardi/data-structures/blob/main/results/lab_3/lab_3.png?raw=true)

### Final experiment

B-Trees, with variable degree `t`.

![B-Trees with variable t](https://github.com/andrea-berardi/data-structures/blob/main/results/final/final.png?raw=true)

## Bibliography

Resources used for my studies and the implementation:

- _Introduction to Algorithms_, Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein (2009)
- _Misc laboratory PDFs_, Eduard I. Stan (2021)
- _Misc course slides_, Guido Sciavicco (2021)
- _The Art of Computer Programming_, Donald E. Knuth (1998)
- _B-tree_, Wikipedia (as of 2022)
- _Open Data Structures_, Pat Morin (2013)
- _B-Trees_, CIS - Saint Vincent College (2016)
- _The Ubiquitous B-Tree_, Sally E. Fischbeck (1987)
- _The Ubiquitous B-Tree_, Douglas Comer (1979)
- _Modern C_, Jens Gustedt (2019)
- _Linux's GitHub repository_, Linus Torvalds (as of 2022)
