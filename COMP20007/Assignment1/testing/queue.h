/* * * * * * *
 * Module for creating and manipulating queues of vertices
 *
 * created for Assignment 1 COMP20007 Design of Algorithms 2017
 * by Armaan Dhaliwal-Mcleod 837674 <dhaliwala@student.unimelb.edu.au>
 * Main idea taken from Head tutor Matt Farrugia's solution to queue.h from Workshop Week 03
 */

#ifndef QUEUE_H
#define QUEUE_H

// necessary header included for this module 
#include "list.h"

// wrapper struct to hold a queue, which is just a list
typedef struct {
	List *queue;
} Queue;

// function prototypes

// create a new queue and return its pointer
Queue *new_queue(void);

// destroy a queue and its associated memory
void free_queue(Queue *Q);

// insert a new item of data at the back of a queue.
void queue_enqueue(Queue *Q, Vertex *data);

// remove and return the item of data at the front of a queue.
Vertex *queue_dequeue(Queue *Q);

// return the number of items currently in a queue
int queue_size(Queue *Q);

// returns whether the queue contains no elements (true) or some elements (false)
bool is_queue_empty(Queue *S);

#endif