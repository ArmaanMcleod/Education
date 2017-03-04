#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

list_t *new_list(void) {
	list_t *newlist;

	newlist = malloc(sizeof(*newlist));
	if (newlist == NULL) {
		fprintf(stderr, "Cannot create empty list\n");
		exit(EXIT_FAILURE);
	}

	newlist->head = NULL;
	newlist->foot = NULL;
	newlist->n = 0;

	return newlist;
}

list_t *list_add_start(list_t *list, char *name, int month) {
	node_t *newnode;

	newnode = malloc(sizeof(*newnode));
	if (newnode == NULL) {
		fprintf(stderr, "Cannot create new node\n");
		exit(EXIT_FAILURE);
	}

	newnode->data = malloc(sizeof(data_t));
	if (newnode->data == NULL) {
		fprintf(stderr, "Cannot allocate pointer to data\n");
		exit(EXIT_FAILURE);
	}

	newnode->data->name = malloc(strlen(name)+1);
	if (newnode->data->name == NULL) {
		fprintf(stderr, "Cannot allocate string\n");
		exit(EXIT_FAILURE);
	}

	strcpy(newnode->data->name, name);

	newnode->data->month = month;

	newnode->next = list->head;
	list->head = newnode;

	if (list->foot ==NULL) {
		list->foot = newnode;
	}

	return list;
}

list_t *list_add_end(list_t *list, char *name, int month) {
	node_t *newnode;

	newnode = malloc(sizeof(*newnode));
	if (newnode == NULL) {
		fprintf(stderr, "Cannot create new node\n");
		exit(EXIT_FAILURE);
	}

	newnode->data = malloc(sizeof(data_t));
	if (newnode->data == NULL) {
		fprintf(stderr, "Cannot allocate pointer to data\n");
		exit(EXIT_FAILURE);
	}

	newnode->data->name = malloc(strlen(name)+1);
	if (newnode->data->name == NULL) {
		fprintf(stderr, "Cannot allocate string\n");
		exit(EXIT_FAILURE);
	}

	strcpy(newnode->data->name, name);

	newnode->data->month = month;
	newnode->next = NULL;

	if (list->foot == NULL) {
		list->head = newnode;
		list->foot = newnode;
	} else {
		list->foot->next = newnode;
		list->foot = newnode;
	}

	return list;
}

list_t *list_remove_start(list_t *list) {
	node_t *oldhead;

	oldhead = list->head;
	list->head = list->head->next;
	if (list->head == NULL) {
		list->foot = NULL;
	}

	free(oldhead);

	list->n--;

	return list;
}

list_t *list_remove_end(list_t *list) {
	node_t *curr, *prev;

	curr = list->head;
	if (list->head->next == NULL) {
		free(list->head);
		list->head = NULL;
	} else {
		while (curr != NULL && curr->next != NULL) {
			prev = curr;
			curr = curr->next;
		}

		free(prev->next);
		prev->next = NULL;
	}

	list->n--;

	return list;
}

size_t list_size(list_t *list) {
	node_t *curr;
	size_t currsize = 0;

	curr = list->head;
	while (curr != NULL) {
		currsize++;
		curr = curr->next;
	}

	return currsize;
}

void free_list(list_t *list) {
	node_t *curr, *prev;

	curr = list->head;
	while (curr != NULL) {
		prev = curr;
		curr = curr->next;
		free(prev->data->name);
		free(prev->data);
		free(prev);
	}

	free(list);
}

void print_list(list_t *list) {
	node_t *curr;

	curr = list->head;
	while (curr != NULL) {
		printf("Classmate: %s Birthday Month: %d\n", curr->data->name, curr->data->month);
		curr = curr->next;
	}
}