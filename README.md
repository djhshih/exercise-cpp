# Programming Exercises

## Debugging Problem ##
 
The code in `pearson_problem.cpp` compiles successfully with
 
    g++ -o pearson pearson_problem.cpp
 
However, the unit tests fail during runtime:
 
    ./pearson

    Assertion failed: (std::abs(numeric::correlation(x, n, z, n)) - (-1.0)
    < tolerance), function main, file pearson_problem.cpp, line 106.
 
Find and correct 7 logical errors in `pearson_problem.cpp`.


## Code Comprehension ##

Review the code in `numeric.hpp` and answer the following questions.

1. What is the worse-case time and space complexities of the following function?

    ```c++
    template <typename T> inline double mad(T* xs, size_t n)
    ```

2. What is the average-case time complexity of the following function?

    ```c++
    template <typename T> inline double median(T* xs, size_t n)
    ```


## Problem Solving ##

Write a program (in any language) that finds the fourth most frequent value 
in an integer array. In the case of ties in frequency among multiple values, 
return the smallest of such values.

For example, given the values (as command-line argument inputs)

    4 4 1 2 2 2 2 3 3 3 5 5 5 6 1 5 9

the program should print

    1

