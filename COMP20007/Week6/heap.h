#ifndef HEAP_H
#define HEAP_H

typedef struct {
	float key;
	int data;
} HeapItem;

typedef struct {
	HeapItem *heap;
	int *map;
	int currsize;
	int maxsize;
} Heap;

Heap *new_heap(int max_size);

void heap_insert(Heap *h, float key, int data);

int heap_remove_min(Heap *h);

void siftup(Heap *h, int i);

void siftdown(Heap *h, int i);

int min_child(Heap *h, int i);

int heap_peek_min(Heap *h);

float heap_peak_key(Heap *h);

void free_heap(Heap *h);

#endif