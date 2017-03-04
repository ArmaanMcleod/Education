#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEXTSIZE 1000

typedef struct {
	char *dictionary[TEXTSIZE];
	size_t numwords;
} dictionary_t;

void read_text(char *text);
void read_words(char *text, dictionary_t *dict);
int search_word(dictionary_t *dict, char *word);
void print_words(dictionary_t *dict);
int str_cmp(const void *a, const void *b);

int main(void) {
	dictionary_t dict;
	char text[TEXTSIZE];

	read_text(text);

	read_words(text, &dict);

	print_words(&dict);

	return 0;
}

void read_text(char *text) {
	size_t slen;

	printf("Please enter text: \n");
	if (fgets(text, TEXTSIZE, stdin) == NULL) {
		fprintf(stderr, "Error reading text\n");
		exit(EXIT_FAILURE);
	}

	slen = strlen(text);
	if (slen > 0) {
		if (text[slen-1] == '\n') {
			text[slen-1] = '\0';
		} else {
			printf("Buffer overflow detected.\n");
			exit(EXIT_FAILURE);
		}
	}

	if (!*text) {
		printf("No text entered.\n");
		exit(EXIT_FAILURE);
	}
}

void read_words(char *text, dictionary_t *dict) {
	char *word;
	const char *delim = " ,.!?;:";
	dict->numwords = 0;

	word = strtok(text, delim);
	while (word != NULL) {
		if (search_word(dict, word)) {
			dict->dictionary[dict->numwords] = malloc(strlen(word)+1);
			if (!dict->dictionary[dict->numwords]) {
				printf("Cannot allocate word.\n");
				exit(EXIT_FAILURE);
			}
			strcpy(dict->dictionary[dict->numwords], word);
			dict->numwords++;
		}
		word = strtok(NULL, delim);
	}
}

int search_word(dictionary_t *dict, char *word) {
	size_t i;

	for (i = 0; i < dict->numwords; i++) {
		if (strcmp(dict->dictionary[i], word) == 0) {
			return 0;
		}
	}
	return 1;
}

int str_cmp(const void *a, const void *b) {
	const char **str1 = (const char **)a;
	const char **str2 = (const char **)b;

	return strcmp(*str1, *str2);
}

void print_words(dictionary_t *dict) {
	size_t i;

	qsort(dict->dictionary, dict->numwords, sizeof(*(dict->dictionary)), str_cmp);

	printf("\nDictionary:\n");
	for (i = 0; i < dict->numwords; i++) {
		printf("%s\n", dict->dictionary[i]);
		free(dict->dictionary[i]);
		dict->dictionary[i] = NULL;
	}
}

/*void *key;

	key = bsearch(&word, dict->dictionary, dict->numwords, sizeof(*(dict->dictionary)), str_cmp);
	if (!key) {
		return 0;
	}*/



