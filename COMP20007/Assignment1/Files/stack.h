/* * * * * * *
 * Module for creating and manipulating stacks of vertices
 *
 * created for Assignment 1 COMP20007 Design of Algorithms 2017
 * by Armaan Dhaliwal-Mcleod 837674 <dhaliwala@student.unimelb.edu.au>
 * Main idea taken from Head tutor Matt Farrugia's solution to stack.h from Workshop Week 03
 */


#ifndef STACK_H
#define STACK_H

// necessary header included for this module 
#include "list.h"


// wrapper struct to hold a stack, which is just a list
typedef struct {
	List *stack;
} Stack;


// function prototypes

// create a new stack and return its pointer
Stack *new_stack(void);

// destroy a stack and its associated memory
void free_stack(Stack *S);

// push a new item of data onto the top of a stack.
void stack_push(Stack *S, Vertex *data);

// remove and return the top item of data from a stack.
Vertex *stack_pop(Stack *S);

// return the number of items currently in a stack
int stack_size(Stack *S);

// returns whether the stack contains no elements (true) or some elements (false)
bool is_stack_empty(Stack *S);

#endif