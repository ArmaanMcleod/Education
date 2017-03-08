#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BASE 10

long fib1(int n);
int *fib_ptr(int n);

int main(int argc, char *argv[]) {
	int fib;
	char *str, *endptr;
	int *fibarr;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s str [base]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	str = argv[1];

	fib = strtol(str, &endptr, BASE);
	if (endptr == str || *endptr != '\0' || fib < 0) {
		fprintf(stderr, "Invalid number entered\n");
		exit(EXIT_FAILURE);
	}

	printf("First approach: %dth fibonacci number: %ld\n", fib, fib1(fib));

	fibarr = fib_ptr(fib);
	if (fibarr != NULL) {
		printf("Second approach: %dth fibonacci number: %d\n", fib, fibarr[fib]);
	} else {
		printf("Second approach: %dth fibonacci number: %d\n", fib, 0);
	}

	return 0;
}

long fib1(int n) {
	if (n == 0) {
		return 0;
	} else if (n == 1) {
		return 1;
	}

	return fib1(n-1) + fib1(n-2);
}

int *fib_ptr(int n) {
	int *arr, i;

	if (n == 0) {
		return NULL;
	}

	arr = malloc(n * sizeof(*arr));
	if (arr == NULL) {
		fprintf(stderr, "Cannot allocate pointer\n");
		exit(EXIT_FAILURE);
	}

	arr[0] = 0;
	arr[1] = 1;

	for (i = 2; i <= n; i++) {
		arr[i] = arr[i-1] + arr[i-2];
	}

	return arr;
}
