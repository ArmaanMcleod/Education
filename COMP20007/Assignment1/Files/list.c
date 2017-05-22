/* * * * * * *
 * Module for creating and manipulating singly-linked lists of pointers to vertexes
 *
 * created for COMP20007 Design of Algorithms 2017
 * by Armaan Dhaliwal-Mcleod 837674 <dhaliwala@student.unimelb.edu.au>
 * functions taken from Head tutor Matt Farrugia's sample list.c from Workshop Week 03
 */

// libraries and header files included for this module
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "list.h"

// create new list and return pointer to it
List *new_list(void) {
	List *list = malloc(sizeof(*list));
	assert(list != NULL);

	list->head = NULL;
	list->tail = NULL;
	list->size = 0;

	return list;
}

// destroy a list and free its memory
void free_list(List *list) {
	assert(list != NULL);

	Node *curr = list->head;
	Node *prev = NULL;

	while (curr != NULL) {
		prev = curr;
		free(prev->data);
		free(prev);
		curr = curr->next;
	}

	free(list);
}

// helper function to create a new node and return its address
static Node *new_node(void) {
	Node *newnode = malloc(sizeof(*newnode));
	assert(newnode != NULL);

	return newnode;
}

// add an element to the front of a list
void list_add_start(List *list, Vertex *data) {
	assert(list != NULL && data != NULL);

	// create and initialise a new list node
	Node *newnode = new_node();

	// allocate size for data to be stored in node
	newnode->data = malloc(sizeof(*data));
	assert(newnode->data != NULL);

    // using memcpy() to allow safe copying
	memcpy(newnode->data, data, sizeof(*data));

	// next will be old first node
	newnode->next = list->head;

	// place it at the start of the list
	list->head = newnode;

	// if list was empty, this new node is also the last node now
	if (list->size == 0) {
		list->tail = newnode;
	}

	// keep size updated
	list->size++;
}

// add an element to the back of a list
void list_add_end(List *list, Vertex *data) {
	assert(list != NULL && data != NULL);

	// create and initialise a new list node
	Node *newnode = new_node();

	// allocate size for data to be stored in node
	newnode->data = malloc(sizeof(*data));
	assert(newnode->data != NULL);

	// using memcpy() to allow safe copying
	memcpy(newnode->data, data, sizeof(*data));

	// as the last node, there's no next node
	newnode->next = NULL;

	if (list->size == 0) {
		// if the list was empty, new node is now the first node
		list->head = newnode;
	} else {
		// otherwise, it goes after the current last node
		list->tail->next = newnode;
	}

	// place this new node at the end of the list
	list->tail = newnode;

	// keep size updated
	list->size++;
}

// remove and return the front data element from a list
Vertex *list_remove_start(List *list) {
	assert(list != NULL);
	assert(list->size > 0);

	// save the data to return it
	Node *oldhead = list->head;
	Vertex *vertex = oldhead->data;

	// replace the head with its next node
	list->head = list->head->next;

	// if this was the last node in the list, the last also needs to be cleared
	if (list->size == 1) {
		list->tail = NULL;
	}

	// decrement list size
	list->size--;

	// finished with this node
	free(oldhead);

	// return data
	return vertex;
}

// remove and return the final data element in a list
Vertex *list_remove_end(List *list) {
	assert(list != NULL);
	assert(list->size > 0);

	// save the data to return it
	Node *oldtail = list->tail;
	Vertex *vertex = oldtail->data;

	// replace the last with the second-last node
	Node *curr = list->head;
	Node *prev = NULL;

	// walk down list to do replacement
	while (curr != NULL && curr->next != NULL) {
		prev = curr;
		curr = curr->next;
	}
	list->tail = prev;

	if (list->size == 1) {
		// since removing the last node, the head also needs clearing
		list->head = NULL;
	} else {
		// otherwise, the second-last node needs to drop the removed last node
		prev->next = NULL;
	}

	// decrement list size
	list->size--;

	// finished with this node
	free(oldtail);

	// return data
	return vertex;
}

// return the number of elements contained in a list
int list_size(List *list) {
	assert(list != NULL);
	return list->size;
}

// returns whether the list contains no elements (true) or some elements (false)
bool list_is_empty(List *list) {
	assert(list != NULL);
	return (list->size == 0);
}












