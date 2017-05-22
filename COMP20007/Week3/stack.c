#include <stdlib.h>
#include <assert.h>

#include "list.h"
#include "stack.h"

Stack *new_stack(void) {
	Stack *newstack = malloc(sizeof(*newstack));
	assert(newstack != NULL);

	newstack->stack = new_list();
	assert(newstack->stack != NULL);

	return newstack;
}

void free_stack(Stack *S) {
	free_list(S->stack);
}

void stack_push(Stack *S, int data) {
	list_add_start(S->stack, data);
}

void stack_pop(Stack *S) {
	list_remove_start(S->stack);
}

int stack_size(Stack *S) {
	return list_size(S->stack);
}