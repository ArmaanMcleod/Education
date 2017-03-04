#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

#define ARRAYSIZE(x) (sizeof x / sizeof x[0])
#define NAMESTRLEN 100
#define MONTHLEN 10
#define MONTHS 12
#define NUMBASE 10

static void remove_newline(char *buffer) {
	size_t slen;

	slen = strlen(buffer);
	if (slen > 0 && buffer[slen-1] == '\n') {
		buffer[slen-1] = '\0';
	} 
}

int main(void) {
	list_t *listarray[MONTHS];
	char *name = NULL, *month = NULL, *endptr = NULL;
	size_t len = 0;
	ssize_t read;
	unsigned count = 1;
	int monthnum;

	for (size_t i = 0; i < ARRAYSIZE(listarray); i++) {
		listarray[i] = new_list();
	}

	while (1) {
		printf("Please enter classmate %d name(enter newline to stop): ", count);
		if ((read = getline(&name, &len, stdin)) != -1) {
			remove_newline(name);
		} 

		if (*name == '\0') {
			free(name);
			break;
		}

		printf("Please enter classmate %d birthday month: ", count);
		if ((read = getline(&month, &len, stdin)) != -1) {
			remove_newline(month);
		}

		monthnum = strtol(month, &endptr, NUMBASE);
		if (endptr == month || *endptr != '\0' || monthnum >= MONTHS) {
			fprintf(stderr, "Invalid birthday\n");
		} else {
			listarray[monthnum] = list_add_end(listarray[monthnum], name, monthnum);

			count++;
		}

		free(month);
		free(name);
	}

	for (size_t i = 0; i < ARRAYSIZE(listarray); i++) {
		listarray[i]->n = list_size(listarray[i]);

		if (listarray[i]->n > 0) {
			listarray[i] = list_remove_start(listarray[i]);

			if (listarray[i]->n == 0) {
				printf("\nlistarray[%zu] is empty\n", i);
			} else {
				listarray[i] = list_remove_end(listarray[i]);
				printf("\nlistarray[%zu]:\n", i);
				print_list(listarray[i]);
				free(listarray[i]);
			}
		} else {
			printf("\nlistarray[%zu] is empty\n", i);
		}
	}

	return 0;
}
