#include <stdio.h>
#include <stdlib.h>

void reverseString(char *str, int length) {
    int start = 0;
    int end = length - 1;
    while (start < end) {
        /* Swap the characters */
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        /* Move towards the middle */
        start++;
        end--;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s fileIn fileOut\n", argv[0]);
        return 1;
    }

    FILE *fileIn = fopen(argv[1], "r");
    if (fileIn == NULL) {
        perror("Error opening input file");
        return 2;
    }

    /* Seek to the end to find the file size */
    fseek(fileIn, 0, SEEK_END);
    long fileSize = ftell(fileIn);
    rewind(fileIn); /* Go back to the beginning of the file */

    /* Allocate memory for the content plus a null terminator */
    char *content = (char *)malloc(fileSize + 1);
    if (content == NULL) {
        perror("Memory allocation failed");
        fclose(fileIn);
        return 3;
    }

    /* Read the content and add a null terminator */
    fread(content, 1, fileSize, fileIn);
    content[fileSize] = '\0';

    /* Close the input file as we no longer need it */
    fclose(fileIn);

    /* Reverse the content */
    reverseString(content, fileSize);

    FILE *fileOut = fopen(argv[2], "w");
    if (fileOut == NULL) {
        perror("Error opening output file");
        free(content);
        return 4;
    }

    /* Write the reversed content and close the file */
    fwrite(content, 1, fileSize, fileOut);
    fclose(fileOut);

    /* Free the allocated memory */
    free(content);

    return 0;
}
