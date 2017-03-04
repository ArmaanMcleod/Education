#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFSIZE 128

void exit_if_null(void *ptr, const char *msg);

int
main(int argc, char const *argv[]) {
	FILE *filename;
	char buffer[BUFFSIZE];
	char *sequence;
	char **ipinfo;
	int str_size = 10, str_count = 0, i;
	
	filename = fopen("ips.txt", "r");

	if (filename == NULL) {
		fprintf(stderr, "%s\n", "Error Reading File!");
		exit(EXIT_FAILURE);
	}

	ipinfo = malloc(str_size * sizeof(*ipinfo));
	exit_if_null(ipinfo, "Initial Allocation");

	while (fgets(buffer, BUFFSIZE, filename) != NULL) {
		sequence = strtok(buffer, "-\n");

		while (sequence != NULL) {
			if (str_size == str_count) {
				str_size *= 2;
				ipinfo = realloc(ipinfo, str_size * sizeof(*ipinfo));
				exit_if_null(ipinfo, "Reallocation");
			}

			ipinfo[str_count] = malloc(strlen(sequence)+1);
			exit_if_null(ipinfo[str_count], "Initial Allocation");

			strcpy(ipinfo[str_count], sequence);

			str_count++;
		
			sequence = strtok(NULL, "-\n");
		}
	}

	for (i = 0; i < str_count; i++) {
		printf("%s\n", ipinfo[i]);
		free(ipinfo[i]);
		ipinfo[i] = NULL;
	}

	free(ipinfo);
	ipinfo = NULL;

	fclose(filename);

	return 0;
}

void
exit_if_null(void *ptr, const char *msg) {
    if (!ptr) {
        printf("Unexpected null pointer: %s\n", msg);
        exit(EXIT_FAILURE);
    }
}