#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAYSIZE(x) (sizeof x / sizeof x[0])
#define NAMESTRLEN 100
#define MONTHLEN 10
#define MONTHS 12
#define NUMBASE 10

typedef struct {
	char *name;
	int month;
} data_t;

typedef struct node {
	data_t *data;
	struct node *next;
} node_t;

typedef struct {
	node_t *head;
	node_t *foot;
	size_t n;
} list_t;

list_t *new_list(void);
list_t *list_add_start(list_t *list, char *name, int month);
list_t *list_add_end(list_t *list, char *name, int month);
list_t *list_remove_start(list_t *list);
list_t *list_remove_end(list_t *list);
size_t list_size(list_t *list);
void remove_newline(char *buffer);
void print_list(list_t *list);
void free_list(list_t *list);

int main(void) {
	list_t *listarray[MONTHS];
	char *name = NULL, *month = NULL, *endptr = NULL;
	size_t len = 0;
	ssize_t read;
	unsigned count = 1;
	int monthnum;

	for (size_t i = 0; i < ARRAYSIZE(listarray); i++) {
		listarray[i] = new_list();
	}

	while (1) {
		printf("Please enter classmate %d name(enter newline to stop): ", count);
		if ((read = getline(&name, &len, stdin)) != -1) {
			remove_newline(name);
		} 

		if (*name == '\0') {
			free(name);
			break;
		}

		printf("Please enter classmate %d birthday month: ", count);
		if ((read = getline(&month, &len, stdin)) != -1) {
			remove_newline(month);
		}

		monthnum = strtol(month, &endptr, NUMBASE);
		if (endptr == month || *endptr != '\0' || monthnum >= MONTHS) {
			fprintf(stderr, "Invalid birthday\n");
		} else {
			listarray[monthnum] = list_add_end(listarray[monthnum], name, monthnum);

			count++;
		}

		free(month);
		free(name);
	}

	for (size_t i = 0; i < ARRAYSIZE(listarray); i++) {
		listarray[i]->n = list_size(listarray[i]);

		if (listarray[i]->n > 0) {
			listarray[i] = list_remove_start(listarray[i]);

			if (listarray[i]->n == 0) {
				printf("\nlistarray[%zu] is empty\n", i);
			} else {
				listarray[i] = list_remove_end(listarray[i]);
				printf("\nlistarray[%zu]:\n", i);
				print_list(listarray[i]);
				free(listarray[i]);
			}
		} else {
			printf("\nlistarray[%zu] is empty\n", i);
		}
	}

	return 0;
}

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

void remove_newline(char *buffer) {
	size_t slen;

	slen = strlen(buffer);
	if (slen > 0 && buffer[slen-1] == '\n') {
		buffer[slen-1] = '\0';
	} 
}

