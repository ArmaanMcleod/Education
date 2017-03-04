#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINESIZE 256
#define STARTSIZE 10

int main(void) {
	char line[LINESIZE];
	char **words;
	char *curr, *next;
	const char comma = ',';
	void *temp;
	size_t slen, word_cnt = 0, currsize = STARTSIZE, i;

	words = malloc(currsize  * sizeof(*words));
	if (words == NULL) {
		fprintf(stderr, "Cannot allocate %zu pointers\n", currsize);
		exit(EXIT_FAILURE);
	}

	printf("Enter the string:\n");
	if (fgets(line, LINESIZE, stdin) != NULL) {
		slen = strlen(line);
		if (slen > 0 && line[slen-1] == '\n') {
			line[slen-1] = '\0';
		}

		if (*line == '\0') {
			fprintf(stderr, "No string entered\n");
			exit(EXIT_FAILURE);
		}

		curr = line;
		while ((next = strchr(curr, comma)) != NULL) {
			if (currsize == word_cnt) {
				currsize *= 2;
				temp = realloc(words, currsize * sizeof(*words));
				if (temp == NULL) {
					free(temp);
					temp = NULL;

					for (i = 0; i < word_cnt; i++) {
						free(words[i]);
						words[i] = NULL;
					}

					free(words);
					words = NULL;

					fprintf(stderr, "Cannot reallocate to fit %zu pointers", currsize);
					exit(EXIT_FAILURE);
				}
				words = temp;
			}
			*next++ = '\0';

			words[word_cnt] = strdup(curr);
			if (words[word_cnt] == NULL) {
				fprintf(stderr, "Cannot duplicate string\n");
				exit(EXIT_FAILURE);
			}

			word_cnt++;
			curr = next;
		}

		words[word_cnt] = strdup(curr);
		if (words[word_cnt] == NULL) {
			fprintf(stderr, "Cannot duplicate string\n");
			exit(EXIT_FAILURE);
		}

		word_cnt++;
	}

	for (i = 0; i < word_cnt; i++) {
		printf("%s\n", words[i]);
		free(words[i]);
		words[i] = NULL;
	}

	free(words);
	words = NULL;

	exit(EXIT_SUCCESS);
}