#include <stdio.h>

//function prototype
void printBytes(void *ptr, int numBytes);

int main() {
    int num = 0x12345678;
    float fnum = 123.456f;
    char str[] = "Hello, World!";

    //test with an integer
    printf("Bytes of an integer:\n");
    printBytes(&num, sizeof(num));

    //test with a float
    printf("\nBytes of a float:\n");
    printBytes(&fnum, sizeof(fnum));

    //test with a string
    printf("\nBytes of a string:\n");
    printBytes(str, sizeof(str) - 1); // -1 to not include the null terminator

    return 0;
}

//function that takes a void pointer and interger as parameters
void printBytes(void *ptr, int numBytes) {
    //use char pointer to be able to access each byte of the memory
    unsigned char *p = (unsigned char *)ptr;
    printf("Starting at memory address %p:\n", ptr);
    //loop through each byte of mmeory
    for (int i = 0; i < numBytes; i++) {
        printf("%03d: %d\n", i + 1, p[i]);
    }
}




