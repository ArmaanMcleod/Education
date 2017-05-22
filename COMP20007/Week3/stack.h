#include "list.h"

typedef struct {
	List *stack;
} Stack;

Stack *new_stack(void);

void free_stack(Stack *S);

void stack_push(Stack *S, int data);

void stack_pop(Stack *S);

int stack_size(Stack *S);