/* * * * * * *
 * Module for creating and manipulating stacks of vertices
 *
 * created for Assignment 1 COMP20007 Design of Algorithms 2017
 * by Armaan Dhaliwal-Mcleod 837674 <dhaliwala@student.unimelb.edu.au>
 * functions taken from Head tutor Matt Farrugia's solution to stack.c from Workshop Week 03
 */

// libraries and header files included for this module 
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "list.h"
#include "stack.h"

// create a new stack and return its pointer
Stack *new_stack(void) {
	Stack *newstack = malloc(sizeof(*newstack));
	assert(newstack != NULL);

	// free the list of items, and the stack itself
	newstack->stack = new_list();

	return newstack;
}

// destroy a stack and its associated memory
void free_stack(Stack *S) {
	assert(S != NULL);

	free_list(S->stack);
	free(S);
}

// push a new item of data onto the top of a stack.
void stack_push(Stack *S, Vertex *data) {
	assert(S != NULL);

	list_add_start(S->stack, data);
}

// remove and return the top item of data from a stack.
Vertex *stack_pop(Stack *S) {
	assert(S != NULL);
	assert(stack_size(S) > 0);

	return list_remove_start(S->stack);
}

// return the number of items currently in a stack
int stack_size(Stack *S) {
	assert(S != NULL);
	return list_size(S->stack);
}

// returns whether the stack contains no elements (true) or some elements (false)
// Option function, can simply use stack_size() to check for empty stacks
bool is_stack_empty(Stack *S) {
	assert(S != NULL);
	return list_is_empty(S->stack);
}