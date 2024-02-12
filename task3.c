#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "msString.h"

// Define a structure for a custom string type
typedef struct {
    int length;  // Length of the string
    char *str;   // Pointer to the character array representing the string
} msString;

// Function to set a string in the custom string type
msString *msSetString(const char *s) {
    // Allocate memory for the custom string structure
    msString *ms = (msString *)malloc(sizeof(msString));
    // Check if memory allocation failed
    if (!ms) {
        msError("Memory allocation failed");
        return NULL;
    }
    // Calculate the length of the input string
    ms->length = strlen(s);
    // Allocate memory for the character array to store the string
    ms->str = (char *)malloc(ms->length + 1);
    // Check if memory allocation failed
    if (!ms->str) {
        msError("Memory allocation failed");
        free(ms);
        return NULL;
    }
    // Copy the input string to the custom string structure
    strcpy(ms->str, s);
    return ms;
}

// Function to get the string from the custom string type
char *msGetString(const msString *ms) {
    if (!ms) return NULL;
    // Allocate memory for a character array to hold the string
    char *s = (char *)malloc(ms->length + 1);
    // Check if memory allocation failed
    if (!s) {
        msError("Memory allocation failed");
        return NULL;
    }
    // Copy the string from the custom string structure to the allocated character array
    strcpy(s, ms->str);
    return s;
}

// Function to copy one custom string to another
void msCopy(msString **dest, const msString *src) {
    if (!dest || !src) return;
    if (!*dest) {
        // Allocate memory for the destination custom string structure if it's NULL
        *dest = (msString *)malloc(sizeof(msString));
        if (!*dest) {
            msError("Memory allocation for destination failed");
            return;
        }
    } else {
        // Free the old string if it exists
        free((*dest)->str);
    }
    // Allocate memory for the new string in the destination custom string
    (*dest)->str = (char *)malloc(src->length + 1);
    if (!(*dest)->str) {
        msError("Memory allocation for string copy failed");
        free(*dest);
        *dest = NULL;
        return;
    }
    // Copy the string and update the length
    strcpy((*dest)->str, src->str);
    (*dest)->length = src->length;
}

// Function to concatenate a string to another
void msConcatenate(msString **dest, const msString *src) {
    if (!dest || !src) return;
    // Reallocate memory for the destination string to accommodate the concatenated string
    (*dest)->str = (char *)realloc((*dest)->str, (*dest)->length + src->length + 1);
    if (!(*dest)->str) {
        msError("Memory allocation failed");
        return;
    }
    // Concatenate the source string to the destination string and update the length
    strcat((*dest)->str, src->str);
    (*dest)->length += src->length;
}

// Function to get the length of a custom string
long int msLength(const msString *ms) {
    if (!ms) return -1;
    return (long int)ms->length; 
}

// Function to compare two custom strings
int msCompare(const msString *ms1, const msString *ms2) {
    if (!ms1 || !ms2) return -1;
    if (ms1->length != ms2->length) return 0;
    return strcmp(ms1->str, ms2->str) == 0;
}

// Function to compare a custom string with a regular C string
int msCompareString(const msString *ms, const char *s) {
    if (!ms || !s) return -1;
    if (ms->length != (int)strlen(s)) return 0;
    return strcmp(ms->str, s) == 0;
}

// Function to handle errors
void msError(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
    exit(EXIT_FAILURE);
}

// Function to free memory allocated for a custom string
void msFree(msString *ms) {
    if (ms) {
        free(ms->str);
        free(ms);
    }
}

int main() {
    msString *ms = msSetString(" Hello ");
    msString *ms2 = msSetString(" World!");
    msString *mscopy = NULL;

    printf("String |%s| is %ld characters long (%p).\n", msGetString(ms), msLength(ms), (void*)ms);
    msCopy(&mscopy, ms);
    printf("Copied string |%s| is %ld characters long (%p).\n", msGetString(mscopy), msLength(mscopy), (void*)mscopy);

    printf("Compare ms with mscopy: %d\n", msCompare(ms, mscopy));
    printf("Compare ms with ms2: %d\n", msCompare(ms, ms2));
    printf("Compare ms with Hello: %d\n", msCompareString(ms, "Hello"));
    printf("Compare ms with HelloX: %d\n", msCompareString(ms, "HelloX"));
    printf("Compare ms with Hella: %d\n", msCompareString(ms, "Hella"));

    msConcatenate(&mscopy, ms2);
    printf("Concatenated string |%s| is %ld characters long", msGetString(mscopy), msLength(mscopy));
    
    msFree(ms);
    msFree(ms2);
    msFree(mscopy);

    return 0;
}
