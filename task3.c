#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int length;
    char *str;
} msString;

// Function prototypes
msString *msSetString(const char *s);
char *msGetString(const msString *ms);
void msCopy(msString **dest, const msString *src);
void msConcatenate(msString **dest, const msString *src);
int msLength(const msString *ms);
int msCompare(const msString *ms1, const msString *ms2);
int msCompareString(const msString *ms, const char *s);
void msError(const char *s);

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
    if (!dest || !src) return;
    free((*dest)->str);
    (*dest)->str = (char *)malloc(src->length + 1);
    if (!(*dest)->str) {
        msError("Memory allocation failed");
        return;
    }
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

int msLength(const msString *ms) {
    if (!ms) return -1;
    return ms->length;
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
    // Create msStrings using the given C strings
    msString *ms = msSetString("Hello");
    msString *ms2 = msSetString(" World!");
    msString *mscopy;

    // Print initial strings, lengths, and memory addresses
    printf("String |%s| is %d characters long (0x%p).\n", msGetString(ms), msLength(ms), ms);
    printf("String |%s| is %d characters long (0x%p).\n", msGetString(ms2), msLength(ms2), ms2);

    // Copy ms to mscopy
    mscopy = msSetString(""); // Initialize mscopy with an empty string
    msCopy(&mscopy, ms);

    // Print the copied string, length, and memory address
    printf("Copied string |%s| is %d characters long (0x%p).\n", msGetString(mscopy), msLength(mscopy), mscopy);

    // Compare strings (no change needed here)
    printf("Compare ms with mscopy: %d\n", msCompare(ms, mscopy));
    printf("Compare ms with ms2 : %d\n", msCompare(ms, ms2));
    printf("Compare ms with Hello : %d\n", msCompareString(ms, "Hello"));
    printf("Compare ms with HelloX: %d\n", msCompareString(ms, "Hellox"));
    printf("Compare ms with Hella : %d\n", msCompareString(ms, "Helloa"));

    // Concatenate ms2 to mscopy
    msConcatenate(&mscopy, ms2);

    // Print the concatenated string, length, and memory address
    printf("Concatenated string |%s| is %d characters long (0x%p).\n", msGetString(mscopy), msLength(mscopy), mscopy);

    // Free the memory allocated for msStrings
    msFree(ms);
    msFree(ms2);
    msFree(mscopy);

    return 0;
}
