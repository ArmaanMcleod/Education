#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define INPUTSIZE 108

int main(void) {
	char str_input[INPUTSIZE], characters[INPUTSIZE];
	size_t slen, char_count = 0;

	printf("Enter input:\n");
	if (fgets(str_input, INPUTSIZE, stdin) != NULL) {

		slen = strlen(str_input);
		if (slen > 0 && str_input[slen-1] == '\n') {
			str_input[slen-1] = '\0';
		} else {
			fprintf(stderr, "Number of characters entered exceeds buffer size\n");
			exit(EXIT_FAILURE);
		}

		if (*str_input == '\0') {
			fprintf(stderr, "No input found\n");
			exit(EXIT_FAILURE);
		}

		printf("Buffer: %s\n", str_input);

		for (size_t i = 0; str_input[i] != '\0'; i++) {
			if (!isdigit(str_input[i])) {
				characters[char_count++] = str_input[i];
			}
		}

		characters[char_count] = '\0';

		printf("New buffer without numbers: %s\n", characters);
	} 

    /*char str_input[INPUTSIZE],
	int ch;
	size_t char_count = 0;

	while ((ch = getchar()) != EOF && ch != '\n') {
		if (!isdigit(ch)) {
			if (char_count < sizeof(str_input)) {
				str_input[char_count++] = ch;
			}
		}
	} 

	str_input[char_count] = '\0';

	printf("Non-number buffer: %s\n", str_input);*/

	return 0;
}