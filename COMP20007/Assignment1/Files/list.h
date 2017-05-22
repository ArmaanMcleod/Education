/* * * * * * *
 * Module for creating and manipulating singly-linked lists of pointers to vertexes
 *
 * created for Assignment 1 COMP20007 Design of Algorithms 2017
 * by Armaan Dhaliwal-Mcleod 837674 <dhaliwala@student.unimelb.edu.au>
 * Main idea taken from Head tutor Matt Farrugia's sample list.h from Workshop Week 03
 */

#ifndef LIST_H
#define LIST_H

// libraries and header files included for this module
// included graph module to allow list module to insert vertices from graph
#include <stdbool.h>

#include "graph.h"


// a list node that points to the next element in the list, with some vertex data 
typedef struct node {
	Vertex *data;
	struct node *next;
} Node;


// a list points to its first and last nodes, and stores its size
typedef struct {
	Node *head;
	Node *tail;
	int size;
} List;


// function prototypes

// create a new list and return its pointer
List *new_list(void);

// destroy a list and free its memory
void free_list(List *list);

// add an element to the front of a list
void list_add_start(List *list, Vertex *data);

// add an element to the back of a list
void list_add_end(List *list, Vertex *data);

// remove and return the front data element from a list
Vertex *list_remove_start(List *list);

// remove and return the final data element in a list
Vertex *list_remove_end(List *list);


// return the number of elements contained in a list
int list_size(List *list);

// returns whether the list contains no elements (true) or some elements (false)
bool list_is_empty(List *list);

#endif





