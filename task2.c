#include <stdio.h>
#include <stdlib.h>

// Function to reverse the contents of a file
int reverseFileContents(const char *inputFileName, const char *outputFileName) {
    // Try to open the input file
    FILE *fileIn = fopen(inputFileName, "r");
    if (fileIn == NULL) {
        perror("Error opening input file");
        return EXIT_FAILURE; 
    }

    // Try to open the input file
    FILE *fileOut = fopen(outputFileName, "w");
    if (fileOut == NULL) {
        perror("Error opening output file");
        // close input file
        fclose(fileIn); 
        return EXIT_FAILURE; 
    }

    // Move to the end of the input file so we can start reading from the back.
    if (fseek(fileIn, 0, SEEK_END) != 0) {
        perror("Error seeking in input file");
        fclose(fileIn);
        fclose(fileOut);
        return EXIT_FAILURE;
    }

    // Find out how big the file is, which tells us where the last character is.
    long fileSize = ftell(fileIn);
    if (fileSize == -1) {
        perror("Error telling position in input file");
        fclose(fileIn);
        fclose(fileOut);
        return EXIT_FAILURE;
    }

    // read each character in the file starting from the last one
    for (long pos = fileSize - 1; pos >= 0; --pos) {
        if (fseek(fileIn, pos, SEEK_SET) != 0) {
            perror("Error seeking in input file");
            break;
        }

        // Read a single character from the file.
        int ch = fgetc(fileIn);
        if (ch == EOF) { 
            perror("Error reading character");
            break;
        }

        // Write that character into the output file.
        if (fputc(ch, fileOut) == EOF) {
            perror("Error writing character");
            break;
        }
    }

    // close both files
    fclose(fileIn);
    fclose(fileOut);

    return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
    // Check if the user ran the program with the right number of arguments: the program name, input file name, and output file name.
    if (argc != 3) {
        fprintf(stderr, "Usage: %s fileIn fileOut\n", argv[0]); 
        return EXIT_FAILURE; 
    }
    return reverseFileContents(argv[1], argv[2]);
}
