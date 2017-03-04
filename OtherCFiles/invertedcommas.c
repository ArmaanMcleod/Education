#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
	const char string[] = "ret=\"y\"  err=\"000\"";
	const char *key = "ret";
	const char equals = '=', space = ' ', quote = '"';
	char *start, *copy, *next, *value;
	size_t i;

	start = strstr(string, key);
	if (start != NULL) {
		copy = strdup(start);
		if (copy == NULL) {
			fprintf(stderr, "Failed to copy contents of string\n");
			exit(EXIT_FAILURE);
		}
		for (i = 0; start[i] != space && start[i] != '\0'; i++) {
			copy[i] = start[i];
		}
		copy[i] = '\0';
		next = strchr(copy, equals);
		if (next != NULL) {
			next++;
			if (*next == quote) {
				next++;
				next[strlen(next)-1] = '\0';
				value = next;
			}
		}

		printf("%s = %s\n", key, value);

		free(copy);
	}

	return 0;
}