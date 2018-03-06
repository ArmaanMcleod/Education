#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(char *a, char *b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

char *revstr(char *str) {
    size_t start, end, slen;
    char *reversed = NULL;

    slen = strlen(str);

    reversed = malloc(slen+1);
    if (reversed == NULL) {
        printf("Cannot allocate %zu bytes for string.\n", slen+1);
        exit(EXIT_FAILURE);
    }

    strcpy(reversed, str);

    for (start = 0, end = slen-1; start <= end; start++, end--) {
        swap(&reversed[start], &reversed[end]);
    }

    return reversed;
}

int main(void) {
    printf("%s\n", revstr("StackOverFlow"));
}
