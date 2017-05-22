#include <stdlib.h>
#include <assert.h>

#include "list.h"
#include "queue.h"

Queue *new_queue(void) {
	Queue *newqueue = malloc(sizeof(*newqueue));
	assert(newqueue != NULL);

	newqueue->queue = new_list();

	return newqueue;
}

void free_queue(Queue *Q) {
	assert(Q != NULL);

	free_list(Q->queue);
	free(Q);
}

void queue_enqueue(Queue *Q, Vertex *data) {
	assert(Q != NULL);
	list_add_end(Q->queue, data);
}

Vertex *queue_dequeue(Queue *Q) {
	assert(Q != NULL);
	assert(queue_size(Q) > 0);

	return list_remove_start(Q->queue);
}

int queue_size(Queue *Q) {
	assert(Q != NULL);
	return list_size(Q->queue);
}

bool is_queue_empty(Queue *Q) {
	assert(Q != NULL);
	return list_is_empty(Q->queue);
}