#include "list.h"

List *new_queue(void);

void free_queue(List *queue);

void queue_enqueue(List *queue, int data);

void queue_deque(List *queue);

int queue_size(List *queue);

