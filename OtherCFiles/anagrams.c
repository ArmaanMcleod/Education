#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLINE 1000
#define MAXLETTER 256

int is_anagram(char *word1, char *word2);
void check_lines(FILE *filename);
int cmpfunc(const void *a, const void *b);
void convert_to_lowercase(char *word);

int
main(int argc, char const *argv[]) {
	FILE *filename;

	if ((filename = fopen("anagram.txt", "r")) == NULL) {
		fprintf(stderr, "Error opening file\n");
		exit(EXIT_FAILURE);
	}

	check_lines(filename);

	fclose(filename);

	return 0;
}

void
check_lines(FILE *filename) {
	char line[MAXLINE];
	char *word1, *word2, *copy1, *copy2;

	while (fgets(line, MAXLINE, filename) != NULL) {
		word1 = strtok(line, "#");
		word2 = strtok(NULL, "\n");

		copy1 = strdup(word1);
		copy2 = strdup(word2);

		convert_to_lowercase(copy1);
		convert_to_lowercase(copy2);

		if (is_anagram(copy1, copy2)) {
			printf("%s#%s - Anagrams!\n", word1, word2);
		} else {
			printf("%s#%s - Not Anagrams!\n", word1, word2);
		}
	}
}

void
convert_to_lowercase(char *word) {
	int i;

	for (i = 0; word[i] != '\0'; i++) {
		word[i] = tolower(word[i]);
	}
}

int
is_anagram(char *word1, char *word2) {

	qsort(word1, strlen(word1), sizeof(*word1), cmpfunc);
	qsort(word2, strlen(word2), sizeof(*word2), cmpfunc);

	if (strcmp(word1, word2) == 0) {
		return 1;
	} 
	return 0;
}

int
cmpfunc(const void *a, const void *b) {
	if ((*(char*)a) < (*(char*)b)) {
		return -1;
	}

	if ((*(char*)a) > (*(char*)b)) {
		return +1;
	}

	return 0;
} 