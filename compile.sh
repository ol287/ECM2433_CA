#!/bin/bash

# Define the source files
SRC_FILES="task1.c task2.c task3.c" # Specify your C source files here

# Include directory for the header file if needed
# For example, if msString.h is in the current directory, no need to specify
# If it's in a 'include' directory, you can add: -I./include

# Compile and link the program
gcc -std=c99 -o coursework $SRC_FILES -I.

# Check if the compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful."
else
    echo "Compilation failed."
    exit 1
fi
