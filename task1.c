#include <stdio.h>

/* Function prototype */
void printBytes(void *ptr, int numBytes);

int main() {
    int integerVar = 0x12345678;
    float floatVar = 123.456f;
    char stringVar[] = "Hello, World!";

    /* Test with an integer */
    printf("Bytes of an integer:\n");
    printBytes(&integerVar, sizeof(integerVar));

    /* Test with a float */
    printf("\nBytes of a float:\n");
    printBytes(&floatVar, sizeof(floatVar));

    /* Test with a string */
    printf("\nBytes of a string:\n");
    printBytes(stringVar, sizeof(stringVar) - 1); /* -1 to exclude the null terminator */

    return 0;
}

/* Function that takes a void pointer and an integer as parameters */
void printBytes(void *ptr, int numBytes) {
    /* Use unsigned char pointer to access each byte of memory */
    unsigned char *bytePtr = (unsigned char *)ptr;
    printf("Starting at memory address %p:\n", ptr);

    /* Declare loop variable outside the loop due to ANSI C limitations */
    int i;
    /* Loop through each byte of memory */
    for (i = 0; i < numBytes; i++) {
        printf("%03d: %d\n", i + 1, bytePtr[i]);
    }
}
