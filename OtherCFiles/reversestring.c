#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *allocate_chars(int *len);
void number_of_words(int *num);
void read_strings(char *str, int len);
char *reversed_words(char *str, int len, int num);
char *reverse_word(char *word);

int main(void) {
	int len, num;
	char *str, *result;

	str = allocate_chars(&len);

	read_strings(str, len);

	number_of_words(&num);

	result = reversed_words(str, len, num);
	printf("Reversed string = %s\n", result);

	free(result);
	free(str);

	return 0;
}

char *allocate_chars(int *len) {
	char *str;

	printf("Enter how many chars to allocate: ");
	if (scanf("%d", len) != 1 || *len < 1) {
		printf("Invalid length.\n");
		exit(EXIT_FAILURE);
	}
	getchar();

	str = malloc(*len+1);
	if (!str) {
		printf("Cannot allocate %d bytes for string.\n", *len+1);
		exit(EXIT_FAILURE);
	}

	printf("Allocated %d chars.\n", *len+1);

	return str;
}

void number_of_words(int *num) {
	printf("Please enter how many words to reverse: ");
	if (scanf("%d", num) != 1 || *num < 0) {
		printf("Invalid number.\n");
		exit(EXIT_FAILURE);
	}
}

void read_strings(char *str, int len) {
	int slen;

	printf("Please enter your string: ");
	if (fgets(str, len, stdin) == NULL) {
		printf("Cannot create buffer.\n");
		exit(EXIT_FAILURE);
	}

	slen = strlen(str);
	if (slen > 0) {
		if (str[slen-1] == '\n') {
			str[slen-1] = '\0';
		} else {
			printf("Entered string bigger than buffer size of %d bytes.\n", len);
			exit(EXIT_FAILURE);
		}
	}

	if (!*str) {
		printf("No string entered.\n");
		exit(EXIT_FAILURE);
	}
}

char *reversed_words(char *str, int len, int num) {
	char *reversed, *word, *reversed_word;
	const char *delim = " ";
	int count = 1;

	reversed = malloc(len+1);
	if (!reversed) {
		printf("Cannot allocate %d bytes for string.\n", len+1);
		exit(EXIT_FAILURE);
	}

	*reversed = '\0';

	word = strtok(str, delim);
	while (word != NULL) {
		if (count <= num) {
			reversed_word = reverse_word(word);
			strcat(reversed, reversed_word);
			free(reversed_word);
			count++;
		} else {
			strcat(reversed, word);
		}
		word = strtok(NULL, delim);
		if (word != NULL) {
			strcat(reversed, delim);
		}
	}

	return reversed;
}

char *reverse_word(char *word) {
	char *reverse;
	int slen, str_count = 0, i;

	slen = strlen(word);

	reverse = malloc(slen+1);
	if (!reverse) {
		printf("Cannot allocate %d bytes for string.\n", slen+1);
		exit(EXIT_FAILURE);
	}

	for (i = slen-1; i >= 0; i--) {
		reverse[str_count++] = word[i];
	}
	reverse[str_count] = '\0';

	return reverse;
}
