#include <stdio.h>

#include "queue.h"
#include "stack.h"

int main(void) {
	Queue *q = new_queue();
	Stack *s = new_stack();

	stack_push(s, 1);
	queue_enqueue(q, 1);
	
	return 0;
}

