#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "msString.h"

/* Define a structure to hold a string along with its length, hidden behind the msString type */
typedef struct {
    int length;  /* Length of the string */
    char *str;   /* Pointer to the string data */
} msStringInternal;




/* Error handling function */
static void msError(char *s) {
    fprintf(stderr, "Error: %s\n", s);
    exit(1);
}

/* Create a new msString */
msString msSetString(char *s) {
    msStringInternal *ms = (msStringInternal *)malloc(sizeof(msStringInternal));
    if (!ms) {
        msError("Memory allocation failed");
    }
    ms->length = strlen(s);
    ms->str = (char *)malloc(ms->length + 1);
    if (!ms->str) {
        msError("Memory allocation failed");
        free(ms);
    }
    strcpy(ms->str, s);
    return (msString)ms; /* Cast to msString type */
}

/* Retrieve the string data */
char *msGetString(msString ms) {
    msStringInternal *internal = (msStringInternal *)ms;
    if (!internal) return NULL;
    char *copy = (char *)malloc(internal->length + 1);
    if (!copy) {
        msError("Memory allocation failed");
    }
    strcpy(copy, internal->str);
    return copy;
}

/* Copy an msString */
void msCopy(msString *dest, msString src) {
    if (!dest || !src) return;
    msStringInternal *source = (msStringInternal *)src;
    *dest = msSetString(source->str);
}

/* Concatenate two msStrings */
void msConcatenate(msString *dest, msString src) {
    if (!dest || !src) return;
    msStringInternal *destination = (msStringInternal *)*dest;
    msStringInternal *source = (msStringInternal *)src;
    char *newStr = (char *)realloc(destination->str, destination->length + source->length + 1);
    if (!newStr) {
        msError("Memory reallocation failed");
    }
    strcat(newStr, source->str);
    destination->str = newStr;
    destination->length += source->length;
}

/* Get the length of an msString */
long int msLength(msString ms) {
    msStringInternal *internal = (msStringInternal *)ms;
    if (!internal) return 0;
    return internal->length;
}

/* Compare two msStrings */
int msCompare(msString ms1, msString ms2) {
    msStringInternal *first = (msStringInternal *)ms1;
    msStringInternal *second = (msStringInternal *)ms2;
    if (!first || !second) return 1; /* Consider them unequal if either is NULL*/
    return strcmp(first->str, second->str) == 0 ? 0 : 1;
}

/* Compare an msString with a char* */
int msCompareString(msString ms, char *s) {
    msStringInternal *internal = (msStringInternal *)ms;
    if (!internal || !s) return 1; /* Consider them unequal if either is NULL */
    return strcmp(internal->str, s) == 0 ? 0 : 1;
}
void msFree(msString ms) {
    if (ms) {
        msStringInternal *internal = (msStringInternal *)ms;
        free(internal->str); /* Free the string data */
        free(internal); /* Free the structure itself */
    }
}


/* Main function adapted for the new type definitions and function prototypes */
int main() {
    msString ms = msSetString("Hello");
    msString ms2 = msSetString(" World!");
    msString mscopy = NULL;

    /* Displaying the original string and its length*/
    char *str = msGetString(ms);
    printf("String | %s | is %ld characters long.\n", str, msLength(ms));
    free(str); /* Remember to free memory allocated by msGetString*/

    /* Copying ms to mscopy and displaying*/
    msCopy(&mscopy, ms);
    str = msGetString(mscopy);
    printf("Copied string | %s | is %ld characters long.\n", str, msLength(mscopy));
    free(str); /* Free the string obtained from msGetString*/

    /*Comparisons*/
    printf("Compare ms with mscopy: %d\n", msCompare(ms, mscopy));
    printf("Compare ms with ms2: %d\n", msCompare(ms, ms2));
    printf("Compare ms with Hello: %d\n", msCompareString(ms, "Hello"));
    printf("Compare ms with HelloX: %d\n", msCompareString(ms, "HelloX"));
    printf("Compare ms with Hella: %d\n", msCompareString(ms, "Hella"));

    /* Concatenation and displaying the result */
    msConcatenate(&mscopy, ms2);
    str = msGetString(mscopy);
    printf("Concatenated string | %s | is %ld characters long.\n", str, msLength(mscopy));
    free(str); /* Free the concatenated string */

    /* Freeing all msString instances */
    msFree(ms);
    msFree(ms2);
    msFree(mscopy);

    return 0;
}
