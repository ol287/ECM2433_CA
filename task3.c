#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "msString.h"

typedef struct {
    int length;
    char *str;
} msString;

// Function definitions
msString *msSetString(const char *s) {
    msString *ms = (msString *)malloc(sizeof(msString));
    if (!ms) {
        msError("Memory allocation failed");
        return NULL;
    }
    ms->length = strlen(s);
    ms->str = (char *)malloc(ms->length + 1);
    if (!ms->str) {
        msError("Memory allocation failed");
        free(ms);
        return NULL;
    }
    strcpy(ms->str, s);
    return ms;
}

char *msGetString(const msString *ms) {
    if (!ms) return NULL;
    char *s = (char *)malloc(ms->length + 1);
    if (!s) {
        msError("Memory allocation failed");
        return NULL;
    }
    strcpy(s, ms->str);
    return s;
}

void msCopy(msString **dest, const msString *src) {
    if (!dest || !src) return; // Check if either dest or src is NULL.

    // If *dest is NULL, allocate memory for it.
    if (!*dest) {
        *dest = (msString *)malloc(sizeof(msString));
        if (!*dest) {
            msError("Memory allocation for destination failed");
            return;
        }
    } else {
        // Free the old string if it exists.
        free((*dest)->str);
    }

    // Allocate memory for the new string.
    (*dest)->str = (char *)malloc(src->length + 1);
    if (!(*dest)->str) {
        msError("Memory allocation for string copy failed");
        // If allocation failed, free the allocated msString before returning.
        free(*dest);
        *dest = NULL;
        return;
    }

    // Copy the string and the length.
    strcpy((*dest)->str, src->str);
    (*dest)->length = src->length;
}


void msConcatenate(msString **dest, const msString *src) {
    if (!dest || !src) return;
    (*dest)->str = (char *)realloc((*dest)->str, (*dest)->length + src->length + 1);
    if (!(*dest)->str) {
        msError("Memory allocation failed");
        return;
    }
    strcat((*dest)->str, src->str);
    (*dest)->length += src->length;
}

long int msLength(const msString *ms) {
    if (!ms) return -1;
    return (long int)ms->length; 
}

int msCompare(const msString *ms1, const msString *ms2) {
    if (!ms1 || !ms2) return -1;
    if (ms1->length != ms2->length) return 0;
    return strcmp(ms1->str, ms2->str) == 0;
}

int msCompareString(const msString *ms, const char *s) {
    if (!ms || !s) return -1;
    if (ms->length != (int)strlen(s)) return 0;
    return strcmp(ms->str, s) == 0;
}

void msError(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
    exit(EXIT_FAILURE);
}

// Memory management
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


    // Free the memory allocated for msStrings
    msFree(ms);
    msFree(ms2);
    msFree(mscopy);

    return 0;
}
