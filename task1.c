#include <stdio.h>

void printBytes(void *ptr, int numBytes);

int main() {
    int num = 0x12345678;
    float fnum = 123.456f;
    char str[] = "Hello, World!";

    // Test with an integer
    printf("Bytes of an integer:\n");
    printBytes(&num, sizeof(num));

    // Test with a float
    printf("\nBytes of a float:\n");
    printBytes(&fnum, sizeof(fnum));

    // Test with a string
    printf("\nBytes of a string:\n");
    printBytes(str, sizeof(str) - 1); // -1 to not include the null terminator

    return 0;
}

void printBytes(void *ptr, int numBytes) {
    // We use a char pointer to be able to access each byte of the memory.
    unsigned char *p = (unsigned char *)ptr;

    printf("Starting at memory address %p:\n", ptr);
    for (int i = 0; i < numBytes; i++) {
        printf("%03d: %d\n", i + 1, p[i]);
    }
}


