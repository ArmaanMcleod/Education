#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFSIZE 1024
#define INITSIZE 10

typedef struct {
	char **words;
	size_t nwords;
} wordlist_t;

typedef struct {
	wordlist_t *wlist;
	size_t nlines;
	size_t currsize;
} permute_t;

void print_lists(permute_t *wordlists);
permute_t *create_word_lists(void);

int main(void) {
	permute_t *wordlists;
	char buffer[BUFFSIZE], *word;
	const char *delim = " \n";
	size_t words_size = INITSIZE, curr, count = 1;

	wordlists = create_word_lists();

	printf("Words #%zu: ", count);
	count++;
	while (fgets(buffer, BUFFSIZE, stdin) != NULL && strlen(buffer) > 1) {
		printf("Words #%zu: ", count);
		if (wordlists->currsize == wordlists->nlines) {
			wordlists->currsize *= 2;
			wordlists->wlist = realloc(wordlists->wlist, wordlists->currsize * sizeof(wordlist_t));
		}
		words_size = INITSIZE;
		curr = 0;
		wordlists->wlist[wordlists->nlines].words = malloc(words_size * sizeof(char *));

		word = strtok(buffer, delim);
		while (word != NULL) {
			if (words_size == curr) {
				words_size *= 2;
				wordlists->wlist[wordlists->nlines].words = realloc(wordlists->wlist[wordlists->nlines].words, 
					                                                words_size * sizeof(char *));
			}
			wordlists->wlist[wordlists->nlines].words[curr] = malloc(strlen(word)+1);
			strcpy(wordlists->wlist[wordlists->nlines].words[curr], word);
			curr++;
			
			word = strtok(NULL, delim);
		}
		wordlists->wlist[wordlists->nlines].nwords = curr;
		wordlists->nlines++;
		count++;
	}

	print_lists(wordlists);
	
	return 0;
}

void print_lists(permute_t *wordlists) {
	size_t i, j;

	for (i = 0; i < wordlists->nlines; i++) {
		for (j = 0; j < wordlists->wlist[i].nwords; j++) {
			printf("%s ", wordlists->wlist[i].words[j]);
		}
		printf("\n");
	}
}

permute_t *create_word_lists(void) {
	permute_t *wordlists = malloc(sizeof(*wordlists));
	wordlists->nlines = 0;
	wordlists->currsize = INITSIZE;
	wordlists->wlist = malloc(wordlists->currsize * sizeof(wordlist_t));
	return wordlists;
}
