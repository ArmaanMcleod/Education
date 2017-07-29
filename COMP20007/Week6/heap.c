#include <stdlib.h>
#include <assert.h>

#include "heap.h"

#define NOT_IN_HEAP -1

Heap *new_heap(int max_size) {
	int i;

	Heap *h = malloc(sizeof(*h));
	assert (h != NULL);

	h->heap = malloc(max_size * sizeof(*(h->heap)));
	assert(h->heap != NULL);

	h->map = malloc(max_size * sizeof(*(h->map)));
	assert(h->map != NULL);

	for (i = 0; i < max_size; i++) {
		h->map[i] = NOT_IN_HEAP;
	}
	h->maxsize = max_size;
	h->currsize = 0;

	return h;
}

static void swap (Heap *h, int a, int b) {
	int i = h->map[h->heap[a].data];					HeapItem t = h->heap[a];
	h->map[h->heap[a].data] = h->map[h->heap[b].data];	h->heap[a] = h->heap[b];
	h->map[h->heap[b].data] = i;						h->heap[b] = t;
}

void siftup(Heap *h, int i) {
	int me = i;
	int parent = (me - 1) / 2;
	while ((me > 0) && (h->heap[parent].key > h->heap[me].key)) {
		swap(h, parent, me);
		me = parent;
		parent = (me - 1) / 2;
	}
}

void heap_insert(Heap *h, float key, int data) {
	assert(h != NULL);
	assert(h->currsize < h->maxsize);

	h->heap[h->currsize].key = key;
	h->heap[h->currsize].data = data;
	h->map[data] = h->currsize;
	h->currsize++;

	siftup(h, h->currsize-1);
}
