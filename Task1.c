#include <stdio.h>

void printBytes(void *ptr, int numBytes) {
    // We use a char pointer to be able to access each byte of the memory.
    unsigned char *p = (unsigned char *)ptr;

    printf("Starting at memory address %p:\n", ptr);
    for (int i = 0; i < numBytes; i++) {
        printf("%03d: %d\n", i + 1, p[i]);
    }
}

// Example usage of printBytes
//int main() {
    //unsigned char someData[] = {10, 20, 30, 145};
    //printBytes(someData, 4);

    //return 0;
//}


