#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMSIZE 1000
#define INITIALSIZE 10

typedef struct {
    char whole[NUMSIZE+1];
    char decimal[NUMSIZE+1];
    double number;
} record_t;

typedef struct {
	record_t *rec;
	size_t nrec;
	size_t currsize;
} records_t;

char *create_number(records_t *R, size_t numbytes);
int cmp_func(const void *a, const void *b);
void read_records(FILE *filestream, records_t *R);
void print_records(records_t *R);
records_t *create_records(void);

int main(void) {
	records_t *R;
	FILE *fp;

	fp = fopen("doublec.txt", "r");
	if (fp == NULL) {
		fprintf(stderr, "%s\n", "Error reading file");
		return 1;
	}

	R = create_records();

	read_records(fp, R);

	printf("\nOriginal Records:\n");
	print_records(R);

	qsort(R->rec, R->nrec, sizeof(record_t), cmp_func);

	printf("\nSorted Records:\n");
	print_records(R);

	free(R->rec);
	R->rec = NULL;

	free(R);
	R = NULL;

	return 0;
}

void read_records(FILE *filestream, records_t *R) {
	char *number;
	size_t w_size, d_size, numbytes;

	while (fscanf(filestream, "%1000s %1000s", R->rec[R->nrec].whole, R->rec[R->nrec].decimal) == 2) {
		w_size = strlen(R->rec[R->nrec].whole);
		d_size = strlen(R->rec[R->nrec].decimal);

		numbytes = w_size + d_size + 2;

		number = create_number(R, numbytes);

		R->rec[R->nrec].number = atof(number);

		if (R->currsize == R->nrec) {
			R->currsize *= 2;
			R->rec = realloc(R->rec, R->currsize * sizeof(record_t));
			if (R->rec == NULL) {
				printf("Cannot reallocate %zu members.\n", R->currsize);
				exit(EXIT_FAILURE);
			}
		}

		free(number);
		number = NULL;

		R->nrec++;
	}
}

char *create_number(records_t *R, size_t numbytes) {
	char *result;
	const char *decimal = ".";

	result = malloc(numbytes);
	if (result == NULL) {
		printf("Cannot allocate %zu bytes for number.\n", numbytes);
		exit(EXIT_FAILURE);
	}

	*result = '\0';

	strcat(result, R->rec[R->nrec].whole);
	strcat(result, decimal);
	strcat(result, R->rec[R->nrec].decimal);

	return result;
}

void print_records(records_t *R) {
	size_t i;

	for (i = 0; i < R->nrec; i++) {
		printf("Whole Number: %-5s Decimal: %-8s Number: %-7f\n", R->rec[i].whole, 
			                                                      R->rec[i].decimal, 
			                                                      R->rec[i].number);
	}
}

int cmp_func(const void *a, const void *b) {
	const record_t *num1 = (const record_t *)a;
	const record_t *num2 = (const record_t *)b;

	if (num1->number > num2->number) {
		return +1;
	} else if (num1->number < num2->number) {
		return -1;
	}
	return 0;
}

records_t *create_records(void) {
	records_t *R = malloc(sizeof(*R));
	if (R == NULL) {
		printf("Cannot allocate struct.\n");
		exit(EXIT_FAILURE);
	}

	R->nrec = 0;

	R->currsize = INITIALSIZE;

	R->rec = malloc(R->currsize * sizeof(record_t));
	if (R->rec == NULL) {
		printf("Cannot allocate initial %zu members.\n", R->currsize);
		exit(EXIT_FAILURE);
	}

	return R;
}