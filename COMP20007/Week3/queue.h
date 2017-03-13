#include "list.h"

List *new_queue(void);

void free_queue(List *Queue);

void queue_enqueue(List *Queue, int data);

void queue_deque(List *Queue);

int queue_size(List *Queue);

