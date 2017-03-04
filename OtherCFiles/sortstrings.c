#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINESIZE 100

int main(void) {
	char input[LINESIZE];
	size_t numstr, prev_numstr, slen;
	void *temp = NULL;

	printf("Enter number of strings for set 1:\n");
	if (scanf("%zu ", &numstr) != 1) {
		fprintf(stderr, "Invalid value\n");
		exit(EXIT_FAILURE);
	}

	char **strings = malloc(numstr * sizeof(*strings));
	if (strings == NULL) {
		fprintf(stderr, "Cannot allocate %zu strings\n", numstr);
		exit(EXIT_FAILURE);
	}

	for (size_t i = 0; i < numstr; i++) {
		if (fgets(input, LINESIZE, stdin) != NULL) {
			slen = strlen(input);
			if (slen > 0 && input[slen-1] == '\n') {
				input[slen-1] = '\0';
			}

			strings[i] = malloc(strlen(input)+1);
			if (strings[i] == NULL) {
				fprintf(stderr, "Cannot allocate %zu bytes for string\n", strlen(input)+1);
				exit(EXIT_FAILURE);
			}

			strcpy(strings[i], input);
		}		
	}
	
	prev_numstr = numstr;

	printf("Enter number of strings for set 2:\n");
	if (scanf("%zu ", &numstr) != 1) {
		fprintf(stderr, "Invalid value\n");
		exit(EXIT_FAILURE);
	}

	if (numstr != prev_numstr) {
		temp = realloc(strings, numstr * sizeof(*strings));
		if (temp == NULL) {
			fprintf(stderr, "Cannot reallocate %zu spaces\n", numstr);
			exit(EXIT_FAILURE);
		}
		strings = temp;
	} 

	for (size_t i = 0; i < numstr; i++) {
		if (fgets(input, LINESIZE, stdin) != NULL) {
			slen = strlen(input);
			if (slen > 0 && input[slen-1] == '\n') {
				input[slen-1] = '\0';
			}

			strings[i] = malloc(strlen(input)+1);
			if (strings[i] == NULL) {
				fprintf(stderr, "Cannot allocate %zu bytes for string\n", strlen(input)+1);
				exit(EXIT_FAILURE);
			}

			strcpy(strings[i], input);
		}		
	}

	for (size_t i = 0; i < numstr; i++) {
		printf("%s\n", strings[i]);
		free(strings[i]);
		strings[i] = NULL;
	}

	free(strings);
	strings = NULL;

}