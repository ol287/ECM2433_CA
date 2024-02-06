#include <stdio.h>
#include <stdlib.h>

int reverseFileContents(const char *inputFileName, const char *outputFileName) {
    // Open the input file for reading
    FILE *fileIn = fopen(inputFileName, "r");
    if (fileIn == NULL) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }

    // Open the output file for writing
    FILE *fileOut = fopen(outputFileName, "w");
    if (fileOut == NULL) {
        perror("Error opening output file");
        fclose(fileIn); // Close the input file before exiting
        return EXIT_FAILURE;
    }

    // Go to the end of the fileIn
    if (fseek(fileIn, 0, SEEK_END) != 0) {
        perror("Error seeking in input file");
        fclose(fileIn);
        fclose(fileOut);
        return EXIT_FAILURE;
    }

    // Get the position of the last character (size of the file)
    long fileSize = ftell(fileIn);
    if (fileSize == -1) {
        perror("Error telling position in input file");
        fclose(fileIn);
        fclose(fileOut);
        return EXIT_FAILURE;
    }

    // Read from the end of fileIn and write to fileOut in reverse
    for (long pos = fileSize - 1; pos >= 0; --pos) {
        // Seek to the next character from the end
        if (fseek(fileIn, pos, SEEK_SET) != 0) {
            perror("Error seeking in input file");
            break;
        }

        // Read a character
        int ch = fgetc(fileIn);
        if (ch == EOF) {
            perror("Error reading character");
            break;
        }

        // Write the character
        if (fputc(ch, fileOut) == EOF) {
            perror("Error writing character");
            break;
        }
    }

    // Close the files
    fclose(fileIn);
    fclose(fileOut);

    return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
    // Check if the number of arguments is correct
    if (argc != 3) {
        fprintf(stderr, "Usage: %s fileIn fileOut\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Call the function to reverse the contents of the file
    return reverseFileContents(argv[1], argv[2]);
}
