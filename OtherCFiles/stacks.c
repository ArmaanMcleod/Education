#include <stdio.h>
#include <stdlib.h>

#define INITLEN 3

typedef int data_t;

typedef struct {
	data_t *data;
	int curr_size;
	int top;
} stack_t;

stack_t *make_empty_stack(void);
void push(stack_t *stack, data_t data);
data_t pop(stack_t *stack);
void print_stack(stack_t *stack);

int
main(int argc, char const *argv[]) {
	stack_t *stack;

	stack = make_empty_stack();

	push(stack, 10);
	push(stack, 12);
	pop(stack);
	push(stack, 11);
	push(stack, 13);

	print_stack(stack);

	return 0;
}

stack_t
*make_empty_stack(void) {
	stack_t *stack;

	stack = malloc(sizeof(*stack));

	stack->top = 0;
	stack->curr_size = INITLEN;

	stack->data = malloc(stack->curr_size *sizeof(data_t));

	return stack;
}

void
push(stack_t *stack, data_t data) {
	if (stack->top == stack->curr_size) {
		(stack->curr_size) *= 2;
		stack->data = realloc(stack->data, stack->curr_size *sizeof(data_t));
	}
	stack->data[stack->top] = data;
	(stack->top)++;
}

data_t
pop(stack_t *stack) {
	if (stack->top > 0) {
		(stack->top)--;
		return stack->data[stack->top];
	}
	return -1;
}

void
print_stack(stack_t *stack) {
	int i;

	printf("Stacked numbers:\n");
	for (i = 0; i < stack->top; i++) {
		printf("%d\n", stack->data[i]);
	}
}

list_t
insert_node(list_t *list, data_t value) {
	node_t *new = malloc(sizeof(*new));
	new->data = value;
	new->next = list->head;
	list->head = new;

}







