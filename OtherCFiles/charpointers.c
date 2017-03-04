#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STEPSIZE 100
#define BUFFSIZE 1000

char **loadfile(char const *filename, size_t *len);
void check_ptr(void *ptr, const char *msg);

int 
main(int argc, char const *argv[]) {
	int i;
	size_t len;
	char **words;

	if (argc == 1) {
		fprintf(stderr, "Must supply a file name to read.\n");
        exit(EXIT_FAILURE);
	}

	words = loadfile(argv[1], &len);

	for (i = 0; i < len; i++) {
		printf("%s\n", words[i]);
		free(words[i]);
		words[i] = NULL;
	}

	free(words);
	words = NULL;

	return (EXIT_SUCCESS);
}

char 
**loadfile(char const *filename, size_t *len) {
	FILE *fp;
	size_t arrlen, blen;
	char **lines;
	char buffer[BUFFSIZE];
	char *str;
	int i = 0;

	fp = fopen(filename, "r");
	if (!fp) {
		fprintf(stderr, "Can't open %s for reading.\n", filename);
        return NULL;
	}

	arrlen = STEPSIZE;

	lines = malloc(arrlen * sizeof(*lines));
	check_ptr(lines, "Allocation");

	while (fgets(buffer, BUFFSIZE, fp) != NULL) {
		if (i == arrlen) {
			arrlen += STEPSIZE;
			lines = realloc(lines, arrlen * sizeof(*lines));
			check_ptr(lines, "Reallocation");
		}
		buffer[strlen(buffer)-1] = '\0';
		blen = strlen(buffer);

		str = malloc((blen+1) * sizeof(*str));
		strcpy(str, buffer);

		lines[i] = str;
		i++;

	}
	*len = i;
	return lines;
}

void
check_ptr(void *ptr, const char *msg) {
    if (!ptr) {
        printf("Unexpected null pointer: %s\n", msg);
        exit(EXIT_FAILURE);
    }
}
