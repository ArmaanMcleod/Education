#include "list.h"
#include "queue.h"

List *new_queue(void) {
	return new_list();
}

void free_queue(List *Queue) {
	free_list(Queue);
}

void queue_enqueue(List *Queue, int data) {
	list_add_end(Queue, data);
}

void queue_dequeue(List *Queue) {
	list_remove_start(Queue);
}

int queue_size(List *Queue) {
	return list_size(Queue);
}

