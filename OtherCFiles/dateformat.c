#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMDATES 3

int main(void) { 
    char s[] = "12/02/1997";
    const char *delim = "/";
    char *date[NUMDATES];
    char *newformat, *word, *copy;
    size_t strcnt = 0, i;

    copy = malloc(strlen(s)+1);
    strcpy(copy, s);

    word = strtok(s, delim);
    while (word != NULL) {
        date[strcnt] = malloc(strlen(word)+1);
        strcpy(date[strcnt], word);
        strcnt++;
        word = strtok(NULL, delim);
    }

    newformat = malloc(strlen(s)+1);
    *newformat = '\0';

    for (i = strcnt-1; i > 0; i--) {
        strcat(newformat, date[i]);
        free(date[i]);
        date[i] = NULL;

        strcat(newformat, delim);
    }
    strcat(newformat, date[i]);

    printf("Previous format: %s\n", copy);
    printf("New format: %s\n", newformat);

    free(newformat);
    newformat = NULL;

    return 0;
}