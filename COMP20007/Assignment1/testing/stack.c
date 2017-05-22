#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "list.h"
#include "stack.h"

Stack *new_stack(void) {
	Stack *newstack = malloc(sizeof(*newstack));
	assert(newstack != NULL);

	newstack->stack = new_list();

	return newstack;
}

void free_stack(Stack *S) {
	assert(S != NULL);

	free_list(S->stack);
	free(S);
}

void stack_push(Stack *S, Vertex *data) {
	assert(S != NULL);

	list_add_start(S->stack, data);
}

Vertex *stack_pop(Stack *S) {
	assert(S != NULL);
	assert(stack_size(S) > 0);

	return list_remove_start(S->stack);
}

int stack_size(Stack *S) {
	assert(S != NULL);
	return list_size(S->stack);
}

bool is_stack_empty(Stack *S) {
	assert(S != NULL);
	return list_is_empty(S->stack);
}