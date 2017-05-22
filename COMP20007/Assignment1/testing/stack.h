#ifndef STACK_H
#define STACK_H

#include "list.h"

typedef struct {
	List *stack;
} Stack;

Stack *new_stack(void);

void free_stack(Stack *S);

void stack_push(Stack *S, Vertex *data);

Vertex *stack_pop(Stack *S);

int stack_size(Stack *S);

bool is_stack_empty(Stack *S);

#endif