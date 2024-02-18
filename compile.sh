#!/bin/bash

# Compile task1.c, task2.c, and task3.c with ANSI C standard compliance
gcc -ansi -c task1.c -o task1.o
gcc -ansi -c task2.c -o task2.o
gcc -ansi -c task3.c -o task3.o

# Link the object files into a single executable named coursework
gcc task1.o task2.o task3.o -o coursework

# Check if the compilation and linking were successful
if [ $? -eq 0 ]; then
    echo "Compilation and linking successful. Executable named 'coursework' created."
else
    echo "An error occurred during compilation or linking."
fi
