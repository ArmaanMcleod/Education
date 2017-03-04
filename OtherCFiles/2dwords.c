#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMWORDS 400
#define WORDLEN 40
#define BUFFSIZE 100

int
main(void) {
	char text[NUMWORDS][WORDLEN];
	char line[BUFFSIZE], *word;
	size_t slen, count = 0;
	int i;

	printf("Enter some words: ");
	if (fgets(line, BUFFSIZE, stdin) == NULL) {
		printf("Error reading into buffer.\n");
		exit(EXIT_FAILURE);
	}

	slen = strlen(line);
	if (slen > 0) {
		if (line[slen-1] == '\n') {
			line[slen-1] = '\0';
		} else {
			printf("Exceeded buffer length of %d.\n", BUFFSIZE);
			exit(EXIT_FAILURE);
		}
	}

	if (!*line) {
		printf("No words entered.\n");
		exit(EXIT_FAILURE);
	} 

	word = strtok(line, " ");
	while (word != NULL) {
		if (strlen(word) >= WORDLEN) {
			printf("\nYour word \"%s\" is longer than word size limit: %d\n", 
				    word,  WORDLEN);
			exit(EXIT_FAILURE);
		}
		strcpy(text[count], word);
		count++;
		word = strtok(NULL, " \n");
	}

	if (count > NUMWORDS) {
		printf("Too many words entered.\n");
		exit(EXIT_FAILURE);
	}

	printf("\nYour array of strings:\n");
	for (i = 0; i < count; i++) {
		printf("text[%d] = %s\n", i, text[i]);
	}

	return 0;
}
