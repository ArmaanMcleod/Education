#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int blah;
} A;

typedef A b;

typedef struct b X;

typedef union {
	typedef struct {
		int blah;
	} A;

	typedef struct {
		int blah;
	} b;

	typedef struct {
		int blah;
	} X;
} all_structs;

int main(void) {
	X *x = malloc(sizeof(*x));
	x->blah = 1234;
	printf("%d\n", x->blah);

	return 0;
}
