#include <stdio.h>
#include <stdlib.h>

#define MAXROWS 4

void permute(int array[], int start, int end, int **permutations, int maxrows);
void print_free_perms(int **permutations, int n, int rows);
int factorial(int n);
int num_perms(int n);
void int_swap(int *a, int *b);

int main(void) {
	int n, i, **permutations, maxrows = MAXROWS;

	printf("Enter number digits to permute: ");
	if (scanf("%d", &n) != 1) {
		printf("Invalid number.\n");
		exit(EXIT_FAILURE);
	}

	int numbers[n];
    
    printf("Enter numbers: ");
	for (i = 0; i < n; i++) {
		if (scanf("%d", &numbers[i]) != 1) {
			printf("Invalid number.\n");
			exit(EXIT_FAILURE);
		}
	}

	permutations = malloc(maxrows * sizeof(*permutations));
	if (!permutations) {
		printf("Cannot allocate space for %d perms.\n", maxrows);
		exit(EXIT_FAILURE);
	}

	permute(numbers, 0, n, permutations, maxrows);

	print_free_perms(permutations, n, maxrows);

	return 0;
}

void print_free_perms(int **permutations, int n, int rows) {
	int row, col;

	printf("\nPermutations:\n");
	for (row = 0; row < rows; row++) {
		for (col = 0; col < n; col++) {
			printf("%d ", permutations[row][col]);
		}
		//free(permutations[row]);
		//permutations[row] = NULL;
		printf("\n");
	}
	free(permutations);
	permutations = NULL;
}

void permute(int array[], int start, int end, int **permutations, int maxrows) {
	int i, count = 0;

	if (start == end && count < maxrows) {

		permutations[count] = malloc(end * sizeof(int));
		if (!permutations[count]) {
			printf("Cannot allocate space for %d numbers.\n", end);
			exit(EXIT_FAILURE);
		}

		for (i = 0; i < end; i++) {
			permutations[count][i] = array[i];
		}
		count++;

	} else {
		for (i = start; i < end; i++) {
			int_swap(&array[start], &array[i]);
			permute(array, start+1, end, permutations, maxrows);
			int_swap(&array[start], &array[i]);
		}
	}
}

void int_swap(int *a, int *b) {
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}