#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "list.h"

List *new_list(void) {
	List *list = malloc(sizeof(*list));
	assert(list != NULL);

	list->head = NULL;
	list->tail = NULL;
	list->size = 0;

	return list;
}

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

static Node *new_node(void) {
	Node *newnode = malloc(sizeof(*newnode));
	assert(newnode != NULL);

	return newnode;
}

void list_add_start(List *list, Vertex *data) {
	assert(list != NULL && data != NULL);

	Node *newnode = new_node();

	newnode->data = malloc(sizeof(*data));
	assert(newnode->data != NULL);

	memcpy(newnode->data, data, sizeof(*data));

	newnode->next = list->head;
	list->head = newnode;

	if (list->size == 0) {
		list->tail = newnode;
	}

	list->size++;
}

void list_add_end(List *list, Vertex *data) {
	assert(list != NULL && data != NULL);

	Node *newnode = new_node();

	newnode->data = malloc(sizeof(*data));
	assert(newnode->data != NULL);

	memcpy(newnode->data, data, sizeof(*data));

	newnode->next = NULL;

	if (list->size == 0) {
		list->head = newnode;
	} else {
		list->tail->next = newnode;
	}

	list->tail = newnode;

	list->size++;
}

Vertex *list_remove_start(List *list) {
	assert(list != NULL);
	assert(list->size > 0);

	Node *oldhead = list->head;
	Vertex *vertex = oldhead->data;

	list->head = list->head->next;

	if (list->size == 1) {
		list->tail = NULL;
	}

	list->size--;

	free(oldhead);

	return vertex;
}

Vertex *list_remove_end(List *list) {
	assert(list != NULL);
	assert(list->size > 0);

	Node *oldtail = list->tail;
	Vertex *vertex = oldtail->data;

	Node *curr = list->head;
	Node *prev = NULL;

	while (curr != NULL && curr->next != NULL) {
		prev = curr;
		curr = curr->next;
	}
	list->tail = prev;

	if (list->size == 1) {
		list->head = NULL;
	} else {
		prev->next = NULL;
	}

	list->size--;

	free(oldtail);

	return vertex;
}

int list_size(List *list) {
	assert(list != NULL);
	return list->size;
}

bool list_is_empty(List *list) {
	assert(list != NULL);
	return (list->size == 0);
}












