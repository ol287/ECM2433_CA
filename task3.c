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
long int msLength(const msString *ms);
int msCompare(const msString *ms1, const msString *ms2);
int msCompareString(const msString *ms, const char *s);
void msFree(msString *ms);
void msError(const char *s);

// Function definitions
void msError(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
    exit(1);
}

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

long int msLength(const msString *ms) {
    if (!ms) return 0;
    return ms->length;
}

int msCompare(const msString *ms1, const msString *ms2) {
    if (!ms1 || !ms2) return 1; // Consider unequal if either is NULL.
    return strcmp(ms1->str, ms2->str) == 0 ? 0 : 1;
}

int msCompareString(const msString *ms, const char *s) {
    if (!ms || !s) return 1; // Consider unequal if either is NULL.
    return strcmp(ms->str, s) == 0 ? 0 : 1;
}


void msCopy(msString **dest, const msString *src) {
    if (!dest || !src) return;

    if (!*dest) {
        *dest = (msString *)malloc(sizeof(msString));
        if (!*dest) {
            msError("Memory allocation for destination failed");
            return;
        }
    } else {
        free((*dest)->str);
    }

    (*dest)->str = (char *)malloc(src->length + 1);
    if (!(*dest)->str) {
        msError("Memory allocation for string copy failed");
        free(*dest);
        *dest = NULL;
        return;
    }

    strcpy((*dest)->str, src->str);
    (*dest)->length = src->length;
}

void msConcatenate(msString **dest, const msString *src) {
    if (!dest || !src || !*dest) return;

    char *new_str = (char *)realloc((*dest)->str, (*dest)->length + src->length + 1);
    if (!new_str) {
        msError("Memory reallocation failed");
        return;
    }

    (*dest)->str = new_str;
    strcat((*dest)->str, src->str);
    (*dest)->length += src->length;
}

void msFree(msString *ms) {
    if (!ms) return;
    free(ms->str);
    free(ms);
}

int main() {
    msString *ms = msSetString("Hello");
    msString *ms2 = msSetString("World!");
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
    printf("Concatenated string |%s| is %ld characters long\n", msGetString(mscopy), msLength(mscopy));

    msFree(ms);
    msFree(ms2);
    msFree(mscopy);
    return 0;
}
