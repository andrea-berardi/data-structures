# Data Structures (:construction: Work in Progress)

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
- [Credits](#credits)

## About

Things to say about this project... preamble and things like that.

## Data Structures implemented

- [x] Linked Lists (personal test, **not** required by the lab.)
- [x] Binary Search Trees
- [ ] RB-Trees (_Red-Black Trees_)
- [ ] B-Trees

## Project Structure

Folders and files of this project.

```
TODO
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

### Lab. 1A

Binary Search Trees

![Binary Search Trees](https://github.com/andrea-berardi/trees/blob/main/results/lab_1/1A/lab_1A.png?raw=true)

### Lab. 1B

Linked Lists, Binary Search Trees

![Linked Lists, Binary Search Trees](https://github.com/andrea-berardi/trees/blob/main/results/lab_1/1B/lab_1B.png?raw=true)

### Lab. 2

Red-Black Trees

![Red-Black Trees](https://github.com/andrea-berardi/trees/blob/main/results/lab_2/lab_2.png?raw=true)

### Lab. 3

B-Trees

![B-Trees](https://github.com/andrea-berardi/trees/blob/main/results/lab_3/lab_3.png?raw=true)

### Final experiment

Linked Lists, Binary Search Trees, Red-Black Trees, B-Trees

![Linked Lists, Binary Search Trees, Red-Black Trees, B-Trees](https://github.com/andrea-berardi/trees/blob/main/results/total/total.png?raw=true)

## Credits

Special thanks to [...]
