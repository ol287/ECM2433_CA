#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Define a structure to hold a string along with its length */
typedef struct {
    int length;  /* Length of the string */
    char *str;   /* Pointer to the string data */
} msString;

/* Function prototypes */
msString *msSetString(const char *s);
char *msGetString(const msString *ms);
void msCopy(msString **dest, const msString *src);
void msConcatenate(msString **dest, const msString *src);
long int msLength(const msString *ms);
int msCompare(const msString *ms1, const msString *ms2);
int msCompareString(const msString *ms, const char *s);
void msFree(msString *ms);
void msError(const char *s);

/* Function to handle errors */
void msError(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
    exit(1);
}

/* Function to create a new msString from a given C string */
msString *msSetString(const char *s) {
    msString *ms = (msString *)malloc(sizeof(msString)); /* Allocate memory for the msString structure */
    if (ms == NULL) { /* Check if memory allocation was successful */
        msError("Memory allocation failed");
        return NULL;
    }
    ms->length = (int)strlen(s); /* Determine the length of the input string */
    ms->str = (char *)malloc(ms->length + 1); /* Allocate memory for the string data (+1 for null terminator) */
    if (ms->str == NULL) { /* Check if memory allocation was successful */
        msError("Memory allocation failed");
        free(ms); /* Free previously allocated memory for msString structure */
        return NULL;
    }
    strcpy(ms->str, s); /* Copy the input string into the msString data */
    return ms; /* Return the created msString */
}

/* Function to get a copy of the string data from an msString */
char *msGetString(const msString *ms) {
    if (ms == NULL) return NULL; /* Return NULL if the input is NULL */
    char *s = (char *)malloc(ms->length + 1); /* Allocate memory for the copy of the string data */
    if (s == NULL) { /* Check if memory allocation was successful */
        msError("Memory allocation failed");
        return NULL;
    }
    strcpy(s, ms->str); /* Copy the string data */
    return s; /* Return the copied string */
}

/* Function to get the length of an msString */
long int msLength(const msString *ms) {
    if (ms == NULL) return 0; /* Return 0 if the input is NULL */
    return ms->length; /* Return the length of the msString */
}

/* Function to compare two msStrings */
int msCompare(const msString *ms1, const msString *ms2) {
    if (ms1 == NULL || ms2 == NULL) return 1; /* Consider unequal if either is NULL */
    return strcmp(ms1->str, ms2->str) == 0 ? 0 : 1; /* Compare the string data */
}

/* Function to compare an msString with a C string */
int msCompareString(const msString *ms, const char *s) {
    if (ms == NULL || s == NULL) return 1; /* Consider unequal if either is NULL */
    return strcmp(ms->str, s) == 0 ? 0 : 1; /* Compare the string data */
}

/* Function to copy an msString */
void msCopy(msString **dest, const msString *src) {
    if (dest == NULL || src == NULL) return; /* Return if any input is NULL */

    if (*dest == NULL) { /* If the destination is NULL, allocate memory for it */
        *dest = (msString *)malloc(sizeof(msString));
        if (*dest == NULL) { /* Check if memory allocation was successful */
            msError("Memory allocation for destination failed");
            return;
        }
    } else { /* If the destination already exists, free its string data */
        free((*dest)->str);
    }

    (*dest)->str = (char *)malloc(src->length + 1); /* Allocate memory for the string data */
    if ((*dest)->str == NULL) { /* Check if memory allocation was successful */
        msError("Memory allocation for string copy failed");
        free(*dest); /* Free previously allocated memory for msString structure */
        *dest = NULL;
        return;
    }

    strcpy((*dest)->str, src->str); /* Copy the string data */
    (*dest)->length = src->length; /* Update the length */
}

/* Function to concatenate an msString to another msString */
void msConcatenate(msString **dest, const msString *src) {
    if (dest == NULL || src == NULL || *dest == NULL) return; /* Return if any input is NULL */

    char *new_str = (char *)realloc((*dest)->str, (*dest)->length + src->length + 1); /* Reallocate memory for concatenated string */
    if (new_str == NULL) { /* Check if memory reallocation was successful */
        msError("Memory reallocation failed");
        return;
    }

    (*dest)->str = new_str; /* Update the string data pointer */
    strcat((*dest)->str, src->str); /* Concatenate the strings */
    (*dest)->length += src->length; /* Update the length */
}

/* Function to free memory occupied by an msString */
void msFree(msString *ms) {
    if (ms == NULL) return; /* Return if the input is NULL */
    free(ms->str); /* Free the string data */
    free(ms); /* Free the msString structure */
}

/* Main function */
/* Main function */
int main() {
    /* Create msString instances */
    msString *ms = msSetString("Hello");
    msString *ms2 = msSetString(" World!");
    msString *mscopy = NULL;

    if (!ms || !ms2) {
        /* Handle error if any msString wasn't created */
        msFree(ms);
        msFree(ms2);
        return 1;
    }

    /* Get and print the msString details, then free the temporary string */
    char *temp_str = msGetString(ms);
    if (temp_str) {
        printf("String |%s| is %ld characters long.\n", temp_str, msLength(ms));
        free(temp_str);
    }

    /* Copy msString */
    msCopy(&mscopy, ms);
    if (mscopy) {
        temp_str = msGetString(mscopy); /* Reuse temp_str for the new string */
        if (temp_str) {
            printf("Copied string |%s| is %ld characters long.\n", temp_str, msLength(mscopy));
            free(temp_str);
        }
    }

    /* Perform string comparisons */
    printf("Compare ms with mscopy: %d\n", msCompare(ms, mscopy));
    printf("Compare ms with ms2: %d\n", msCompare(ms, ms2));
    printf("Compare ms with 'Hello': %d\n", msCompareString(ms, "Hello"));
    printf("Compare ms with 'HelloX': %d\n", msCompareString(ms, "HelloX"));
    printf("Compare ms with 'Hella': %d\n", msCompareString(ms, "Hella"));

    /* Concatenate msString instances */
    msConcatenate(&mscopy, ms2);
    if (mscopy) {
        temp_str = msGetString(mscopy); /* Reuse temp_str for the new string */
        if (temp_str) {
            printf("Concatenated string |%s| is %ld characters long\n", temp_str, msLength(mscopy));
            free(temp_str);
        }
    }

    /* Free memory for all msString instances */
    msFree(ms);
    msFree(ms2);
    msFree(mscopy);

    return 0; /* Return from main */
}

