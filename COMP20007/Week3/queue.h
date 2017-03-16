#include "list.h"

typedef struct {
	List *queue;
} Queue;

Queue *new_queue(void);

void free_queue(Queue *Q);

void queue_enqueue(Queue *Q, int data);

void queue_deque(Queue *Q);

int queue_size(Queue *Q);

