# Data Structures: Trees

This repository implements many data structures and algorithms, and provides a ready to use environment to easily test them.

## Table of Contents

Here's what you'll find on this document:

- [Data Structures currently implemented](#algorithms-currently-implemented)
- [Project Structure](#project-structure)
- [Notes](#notes)
- [Laboratories](#laboratories)
    - [Lab. 1](#lab-1)
    - [Lab. 1A](#lab-1a)
    - [Lab. 2](#lab-2)
    - [Lab. 3](#lab-3)
    - [Final experiment](#final-experiment)

## Data Structures currently implemented

- Linked Lists
- Binary Search Trees
- RB-Trees (_Red-Black Trees_)
- B-Trees

## Project Structure

```
TODO
```

## Notes

At the moment, as far as I can tell, the project is 100% bug-free and undefined behavior-free.

The `CMakeLists.txt` (build file) ensures that debug builds have runtime sanity checks (provided by Clang) and the absence of warnings\*° hints that there aren't weird things going on. I have also run several checks with Cppcheck (a static analyzer) and everything seems to be compliant. The `DEBUG_MODE` flag on the code even allows performing additional correctness checks (it ensures the algorithms sort correctly by using an antagonist function). I have decided to keep it as a `const` flag to allow the compiler to better optimize the code when it is set to `false`.

I'm planning to add more specific directions on how to run the project, but afaik it should be already out-of-the-box.

I use CLion as my IDE and Clang as my compiler. The project manager is CMake.

I tried to keep the algorithms as close as possible to those shown on the book _Introduction to Algorithms_, but it wasn't always possible. Nevertheless, I have **not** used any additional resources apart my professor's PDFs and my tutor's laboratory documentations.

_\*: Unfortunately there's a tiny warning due to my use of `rand()` in the `gen_rand_array()` function. Basically, the IDE is saying that it has limited randomness, which is fine and totally expected. Please ignore._

_°: The warnings about recursive calls can be ignored too, they're necessary to make some algorithms work properly._

## Laboratories

The following pictures show the performance of the algorithms.

The `X` axis represents the amount of keys that will be stored on the Data Structures.

The `Y` axis represents the time it took to run some operations on them (insertion, search and deletion of keys). It is calculated using C's `clock()` function, provided by the `time.h` library.

### Lab. 1

Binary Search Trees

![Binary Search Trees](https://github.com/andrea-berardi/trees/blob/main/results/lab_1/lab_1A.png?raw=true)

### Lab. 1A

Linked Lists, Binary Search Trees

![Linked Lists, Binary Search Trees](https://github.com/andrea-berardi/sorting-algorithms/blob/main/results/lab_2/2A/lab_2A.png?raw=true)

### Lab. 2B

Insertion Sort, Merge Sort, Hybrid Sort

![Insertion Sort, Merge Sort, Hybrid Sort](https://github.com/andrea-berardi/trees/blob/main/results/lab_2/2B/lab_2B.png?raw=true)

### Lab. 3

Quick Sort, Median of Three Quick Sort

![Quick Sort, Median of Three Quick Sort](https://github.com/andrea-berardi/trees/blob/main/results/lab_3/lab_3.png?raw=true)

### Final experiment

(Insertion Sort), Merge Sort, Hybrid Sort, Quick Sort, Median of Three Quick Sort, Tail Recursive Quick Sort, Heap Sort, Median of Three Tail Quick Sort, Hybrid Tail Recursive Median of Three Quick Sort

![Insertion Sort, Merge Sort, Hybrid Sort, Quick Sort, Median of Three Quick Sort, Tail Recursive Quick Sort, Heap Sort, Median of Three Tail Quick Sort, Hybrid Tail Recursive Median of Three Quick Sort](https://github.com/andrea-berardi/sorting-algorithms/blob/main/results/total/total.png?raw=true)
