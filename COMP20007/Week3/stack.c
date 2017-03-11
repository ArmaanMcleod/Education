#include "list.h"
#include "stack.h"

List *new_stack(void) {
	return new_list();
}

void free_stack(List *Stack) {
	free_list(Stack);
}

void stack_push(List *Stack, int data) {
	list_add_start(Stack, data);
}

void stack_pop(List *Stack) {
	list_remove_start(Stack);
}

int stack_size(List *Stack) {
	return list_size(Stack);
}