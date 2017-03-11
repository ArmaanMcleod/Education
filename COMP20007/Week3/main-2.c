#include <stdio.h>

#include "queue.h"
#include "stack.h"

int main(void) {
	List *Queue = new_queue();
	List *Stack = new_stack();

	stack_push(Stack, 1);
	queue_enqueue(Queue, 1);
	
	return 0;
}

