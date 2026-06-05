# sorting algorithms

Various soring algorithms that can be used to sort strings



## compiling

make



## requirements

* GCC with C23 support
* Nim compiler
* Make



## using the program

sorting\_algorithms \[algorithm\_selection] \[list\_1] \[list-2] ...



## algorithm index

1 - bubble (string)

2 - bubble (number, double)



## example

sorting\_algorithms 1 f e d c b a



## output

* selected algorithm
* sorted list



## notes and things I've ran into while making this

* makefiles are odd
* This setup allows for the change and addition of algorithms without needing to recompile everything
* The idea of the layout is such that I can call my sorting algorithms written in C by using the Nim program



## potential future updates

* more sorting algorithms (merge, heap, etc)
* multithreading for algorithms that can benefit from it (said algorithms needed first)
* add support for sorting lists in files, and to possibly also export sorted list to a file
* add ability to sort doubles

