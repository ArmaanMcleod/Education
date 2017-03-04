#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <assert.h>

#define MAXCHAR 100
#define INITSIZE 10

#define INSERT 'i'
#define PRINTOUT 'p'
#define TABULATE 't'
#define ROTATE 'r'
#define SNAZZY 's'
#define FREE 'f'
#define QUIT 'q'

typedef struct node {
	char *word;
	struct node *right;
	struct node *left;
} node_t;

typedef struct {
	node_t *root;
} tree_t;

void read_insert_BST(tree_t *tree);
tree_t *create_empty_tree(void);
node_t *generate_node(void);
node_t *search_tree(node_t *root, char *word);
node_t *insert_node(node_t *root, node_t *newnode);
tree_t *insert_in_order(tree_t *tree, node_t *newnode);
int find_tree_depth(node_t *root);
void print_tree(node_t *root);
void padding(char *str, int n);
void print_BST(node_t *root, int level);
int tree_depth(tree_t *tree);
int find_tree_size(node_t *root);
int tree_size(tree_t *tree);
int total_depth(node_t *root, int accum);
int total_depth_tree(tree_t *tree);
void free_nodes(node_t *root);
void free_tree(tree_t *tree);

int
main(int argc, char const *argv[]) {
	tree_t *tree;

	tree = create_empty_tree();

	read_insert_BST(tree);
	
	return 0;
}

void
read_insert_BST(tree_t *tree) {
	node_t *newnode, *locn;
	int ch, buff_len, space_found;
	char *buffer;
	char command;
	size_t buffsize;

	while (true) {
		printf("> ");
		space_found = 0;
		buffsize = INITSIZE;
		buff_len = 0;
		buffer = malloc(buffsize * sizeof(*buffer));

		while ((ch = getchar()) != '\n') {
			if (!isspace(ch) && !space_found) {
				command = ch;
			} else {
				space_found = 1;
			}

			if (space_found && isalpha(ch)) {
				if (buffsize == buff_len) {
					buffsize *= 2;
					buffer = realloc(buffer, buffsize * sizeof(*buffer));
				}
				buffer[buff_len++] = ch;
				buffer[buff_len] = '\0';
			}
 		}
 		if (command == INSERT) {
			newnode = generate_node();
			newnode->word = buffer;
			locn = search_tree(tree->root, buffer);
			if (!locn) {
				newnode->word = malloc(strlen(buffer)+1);
				strcpy(newnode->word, buffer);
				tree = insert_in_order(tree, newnode);
			} else {
				free(newnode);
			}
		} else if (command == PRINTOUT) {
			print_BST(tree->root, 0);
		} else if (command == TABULATE) {
			if (tree->root != NULL) {
				printf("size     :     %d\n", tree_size(tree));
				printf("avg depth:  %.2f\n", (1.0)*total_depth_tree(tree) /
			                                   tree_size(tree));
				printf("max depth:     %d\n", tree_depth(tree));
			} else {
				printf("size     :     %d\n", 0);
			}
		} else if (command == FREE) {
			free_tree(tree);
			tree = create_empty_tree();
		} else if (command == QUIT) {
			printf("Program Exited\n");
			break;
		}
		free(buffer);
	}
}

node_t
*insert_node(node_t *root, node_t *newnode) {
	if (root == NULL) {
		return newnode;
	} else {
		if (strcmp(newnode->word, root->word) < 0) {
			if (root->left != NULL) {
				root->left = insert_node(root->left, newnode);
			} else {
				root->left = newnode;
			}
		} else {
			if (root->right != NULL) {
				root->right = insert_node(root->right, newnode);
			} else {
				root->right = newnode;
			}
		}
		return root;
	}
}

tree_t
*insert_in_order(tree_t *tree, node_t *newnode) {
	tree->root = insert_node(tree->root, newnode);
	return tree;
}

node_t
*search_tree(node_t *root, char *word) {
	if (root != NULL) {
		if (strcmp(root->word, word) == 0) {
			return root;
		} else if (strcmp(root->word, word) < 0) {
			return search_tree(root->left, word);
		} else {
			return search_tree(root->right, word);
		}
	} else {
		return NULL;
	}
}

int
find_tree_depth(node_t *root) {
	int ldepth, rdepth;
	if (root == NULL) {
		return 0;
	} else {
		ldepth = find_tree_depth(root->left);
		rdepth = find_tree_depth(root->right);

		if (ldepth > rdepth) {
			return ldepth + 1;
		} else {
			return rdepth + 1;
		}
	}
}

int
tree_depth(tree_t *tree) {
	int depth = find_tree_depth(tree->root);
	return depth;
}

int
find_tree_size(node_t *root) {
	int count = 1;
	if (root == NULL) {
		return 0;
	} else {
		if (root->left != NULL) {
			count += find_tree_size(root->left);
		}
		if (root->right != NULL) {
			count += find_tree_size(root->right);
		}
		return count;
	}
}

int
tree_size(tree_t *tree) {
	int size = find_tree_size(tree->root);
	return size;
}

int
total_depth(node_t *root, int accum) {
	if (root == NULL) {
		return 0;
	} else {
		return accum +
        total_depth(root->left, accum + 1) +
        total_depth(root->right, accum + 1);
	}
}

int 
total_depth_tree(tree_t *tree) {
	int depth = total_depth(tree->root, 1);
	return depth;
}

tree_t
*create_empty_tree(void) {
	tree_t *tree = malloc(sizeof(*tree));
	tree->root = NULL;
	return tree;
}

node_t
*generate_node(void) {
	node_t *newnode = malloc(sizeof(*newnode));
	newnode->word = NULL;
	newnode->right = NULL;
	newnode->left = NULL;
	return newnode;
}

void
free_nodes(node_t *root) {
	if (root) {
		free_nodes(root->right);
		free_nodes(root->left);
		free(root);
	}
}

void
free_tree(tree_t *tree) {
	free_nodes(tree->root);
	free(tree);
}

void
padding(char *str, int n) {
	int i;
	for (i = 0; i < n; i++) {
		printf("%s", str);
	}
}

void
print_BST(node_t *root, int level) {
	if (root != NULL) {
		print_BST(root->right, level+1);
		padding("     ", level);
		printf("%s\n", root->word);
		print_BST(root->left, level+1);
	} 
}

void
print_tree(node_t *root) {
	if (root != NULL) {
		print_tree(root->left);
		printf("%s\n", root->word);
		print_tree(root->right);
	}
}



