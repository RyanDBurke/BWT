/* auxiliary.h:  contains all aux-functions needed to build index and align reads */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int *buildSuffixArray(char *seq, int length);
void printSA(int *sa, int length);

/* suffix array struct */
typedef struct suffixArray {
    int offset;
    char *suffix;
} SA;

/* comparison sort function */
int cmp(const void *a, const void *b) {
    const SA *da = (const SA *) a;
    const SA *db = (const SA *) b;
    
    return strcmp(da->suffix, db->suffix);
}

/* builds suffix array */
int *buildSuffixArray(char *seq, int length) {

    /* store suffixes and their offset */
    SA suffixes[length];

    /* starting adding SA objects to array */
    for (int i = 0; i < length; i++) {
        suffixes[i].suffix = malloc(strlen(seq + i) + 1);
        strcpy(suffixes[i].suffix, (seq + i));
        suffixes[i].offset = i;
    }

    /* sort suffixes */
    qsort(suffixes, length, sizeof(SA), &cmp);

    /* build suffix array */
    int *sa = malloc(sizeof(int) * length);
    for (int i = 0; i < length; i++) {
        sa[i] = suffixes[i].offset;
        free(suffixes[i].suffix);
    }

    return sa;
}

/* prints suffix array */
void printSA(int *sa, int length) {
    for (int i = 0; i < length; i++) {
        printf("%d\n", sa[i]);
    }
}

