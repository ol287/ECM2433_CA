#compile the coursework.c code
gcc -ansi -c  coursework.c -o coursework

# Check if compilation was successful
if [ $? -eq 0 ]; then
    # Add execution permissions to the executable
    chmod +x coursework
    echo "Compilation successful. Executable 'coursework' created."
else
    echo "Compilation failed."
fi
