#include <stdlib.h>
#include <assert.h>

#include "list.h"
#include "queue.h"

Queue *new_queue(void) {
	Queue *newqueue = malloc(sizeof(*newqueue));
	assert(newqueue != NULL);

	newqueue->queue = new_list();
	assert(newqueue->queue != NULL);

	return newqueue;
}

void free_queue(Queue *Q) {
	free_list(Q->queue);
}

void queue_enqueue(Queue *Q, int data) {
	list_add_end(Q->queue, data);
}

void queue_dequeue(Queue *Q) {
	list_remove_start(Q->queue);
}

int queue_size(Queue *Q) {
	return list_size(Q->queue);
}

