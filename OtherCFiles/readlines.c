#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMWORDS 20
#define WORDLEN 20
#define LINESIZE 100

#define SIZEONE(x) (sizeof x[0])
#define SIZETWO(x) (sizeof x / sizeof x[0])

int main(void) {
	char array[NUMWORDS][WORDLEN];
	char line[LINESIZE];
	char *word = NULL, *currline = NULL;
	const char *delim = " \n";
	size_t numwords = 0;

	printf("%zu %zu\n", SIZEONE(array), SIZETWO(array));

	while (fgets(line, LINESIZE, stdin) != NULL) {
		currline = line;

		word = strtok(currline, delim);
		while (word != NULL) {
			if (numwords < SIZETWO(array) && strlen(word) < SIZEONE(array)) {
				strcpy(array[numwords], word);
				numwords++;
			}
			word = strtok(NULL, delim);
		}
	}

	for (size_t i = 0; i < numwords; i++) {
		printf("array[%zu] = %s\n", i, array[i]);
	}

	return 0;
}