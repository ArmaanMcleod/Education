/* * * * * * *
 * Module for creating and manipulating queues of vertices
 *
 * created for Assignment 1 COMP20007 Design of Algorithms 2017
 * by Armaan Dhaliwal-Mcleod 837674 <dhaliwala@student.unimelb.edu.au>
 * functions taken from Head tutor Matt Farrugia's solution to queue.c from Workshop Week 03
 */

// libraries and header files included for this module 
#include <stdlib.h>
#include <assert.h>

#include "list.h"
#include "queue.h"

// create a new queue and return its pointer
Queue *new_queue(void) {
	Queue *newqueue = malloc(sizeof(*newqueue));
	assert(newqueue != NULL);

	newqueue->queue = new_list();

	return newqueue;
}

// destroy a queue and its associated memory
void free_queue(Queue *Q) {
	assert(Q != NULL);

	free_list(Q->queue);
	free(Q);
}

// remove and return the item at the front of a queue.
void queue_enqueue(Queue *Q, Vertex *data) {
	assert(Q != NULL);
	list_add_end(Q->queue, data);
}


// insert a new item at the back of a queue.
Vertex *queue_dequeue(Queue *Q) {
	assert(Q != NULL);
	assert(queue_size(Q) > 0);

	return list_remove_start(Q->queue);
}

// return the number of items currently in a queue
int queue_size(Queue *Q) {
	assert(Q != NULL);
	return list_size(Q->queue);
}

// returns whether the queue contains no elements (true) or some elements (false)
// optional function, can simply use stack_size() to check for empty queues
bool is_queue_empty(Queue *Q) {
	assert(Q != NULL);
	return list_is_empty(Q->queue);
}