#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTRLEN 100

typedef struct node {
	void *data;
	struct node *next;
} node_t;

typedef struct {
	node_t *head;
	node_t *foot;
} list_t;

list_t *create_list(void);
node_t *generate_node(void);
list_t *insert_node(list_t *list, char *data);
void print_list(list_t *list);
void free_list(list_t *list);

int
main(int argc, char *argv[]) {
	list_t *list;
	char data[MAXSTRLEN];
	int user_choice;

	list = create_list();

	while (1) {
		printf("Enter the data: ");
		scanf("%s", data);

		printf("\nType '1' to continue, '0' to exit:\n");
        if (scanf("%d",&user_choice) != 1) {
        	printf("Invalid input\n");
        	exit(EXIT_FAILURE);
        }

        if (user_choice == 1) {
        	list = insert_node(list, data);
        } else {
        	list = insert_node(list, data);
        	break;
        }
	}

	print_list(list);

	free_list(list);
	list = NULL;

	return 0;
}

list_t
*insert_node(list_t *list, char *data) {
	node_t *newnode = generate_node();

	newnode->data = malloc(strlen(data)+1);
	strcpy(newnode->data, data);

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

node_t
*generate_node(void) {
	node_t *new = malloc(sizeof(*new));
	new->data = NULL;
	return new;
}

void
print_list(list_t *list) {
	node_t *curr = list->head;

	printf("\nlinked list data:\n");
	while(curr != NULL) {
		printf("%s\n", (char*)curr->data);
		curr = curr->next;
	}
}

list_t
*create_list(void) {
	list_t *list = malloc(sizeof(*list));
	if (list == NULL) {
		fprintf(stderr, "%s\n", "Error allocating memory");
		exit(EXIT_FAILURE);
	}
	list->head = NULL;
	list->foot = NULL;
	return list;
}

void
free_list(list_t *list) {
	node_t *curr, *prev;
	curr = list->head;
	while (curr) {
		prev = curr;
		curr = curr->next;
		free(prev);
	}
	free(list);
}

