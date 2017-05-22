#ifndef LIST_H
#define LIST_H

#include <stdbool.h>

#include "graph.h"

typedef struct node {
	Vertex *data;
	struct node *next;
} Node;

typedef struct {
	Node *head;
	Node *tail;
	int size;
} List;

List *new_list(void);

void free_list(List *list);

void list_add_start(List *list, Vertex *data);

void list_add_end(List *list, Vertex *data);

Vertex *list_remove_start(List *list);

Vertex *list_remove_end(List *list);

int list_size(List *list);

bool list_is_empty(List *list);

#endif





