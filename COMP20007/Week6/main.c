#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "heap.h"

#define INITIAL_KEY 20.123456

int main(void) {
	Heap *h;
	int maxsize, i, number;

	printf("Enter max size of heap: ");
	if (scanf("%d", &maxsize) != 1) {
		fprintf(stderr, "Invalid size entered.\n");
		exit(EXIT_FAILURE);
	}

	h = new_heap(maxsize);

	srand((unsigned int)time(NULL));

	printf("Enter numbers into heap:\n");
	for (i = 0; i < maxsize; i++) {
		if (scanf("%d", &number) == 1) {
			heap_insert(h, INITIAL_KEYgcc, number);
		}
	}

	for (i = 0; i < h->currsize; i++) {
		printf("%d: %f\n", h->heap[i].data, h->heap[i].key);
	}
	
	
	return 0;
}