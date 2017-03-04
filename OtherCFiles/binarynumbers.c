#include <stdio.h>
#include <stdlib.h>

#define EXIT 0

typedef int data_t;

typedef struct node node_t;

struct node {
	void *data;
	node_t *right;
	node_t *left;
};

typedef struct {
	node_t *root;
	int (*cmp)(void*, void*);
} tree_t;


void exit_if_null(void *ptr, const char *msg);
tree_t *make_empty_tree(int func(void*, void*));
int int_cmp(void *a, void *b);
int is_empty_tree(tree_t *tree);
tree_t *insert_in_order(tree_t *tree, void *value);
void traverse_tree(tree_t *tree, void action(void*));
void free_tree(tree_t *tree);
void *search_tree(tree_t *tree, void *key);
void print_tree(void *x);
int tree_size(tree_t *tree);
int depth(tree_t *tree);
double avg_depth(tree_t *tree);
void *get_tree_head(tree_t *tree);


int
main(int argc, char const *argv[]) {
	tree_t *tree, *locn;
	node_t *new;
	int values;
	int size;
	int average_depth, depths;
	int *smallest;

	tree = make_empty_tree(int_cmp);
	printf("Enter numbers(0 to stop):\n");
	while (scanf("%d", &values) == 1 && values != EXIT) {
		new = malloc(sizeof(*new));
		exit_if_null(new, "Initial Allocation");
		new->data = (int*)values;
		locn = search_tree(tree, new);
		if (!locn) {
			tree = insert_in_order(tree, new);
		} else {
			free(new);
		}
	}

	size = tree_size(tree);
	printf("tree size = %d\n", size);

	depths = depth(tree);
	printf("depth = %d\n", depths);

	smallest = get_tree_head(tree);
	printf("smallest = %d\n", *smallest);

	average_depth = avg_depth(tree);
	printf("Average Depth = %d\n", average_depth);

	traverse_tree(tree, print_tree);

	free_tree(tree);

	tree = NULL;

	return 0;
}

static int
tree_count(node_t *root) {
	int count;

	if (root != NULL) {
		count = 1;
	}

	if (root->right != NULL) {
		count += tree_count(root->right);
	}

	if (root->left != NULL) {
		count += tree_count(root->left);
	}

	return count;
}

int
tree_size(tree_t *tree) {
	int size = tree_count(tree->root);
	return size;
}

tree_t
*make_empty_tree(int func(void*, void*)) {
	tree_t *tree;

	tree = malloc(sizeof(*tree));
	exit_if_null(tree, "Initial Allocation");

	tree->root = NULL;
	tree->cmp = func;

	return tree;
}

static
int tree_depth(node_t *root) {
	int rdepth, ldepth;
	if (root == NULL) {
		return 0;
	} else {
		ldepth = tree_depth(root->left);
		rdepth = tree_depth(root->right);

		if (ldepth > rdepth) {
			return ldepth + 1;
		} else {
			return rdepth + 1;
		}
	}
}

int
depth(tree_t *tree) {
	int depths = tree_depth(tree->root);
	return depths;
}

double
avg_depth(tree_t *tree) {
	int d, size;
	double average;

	if (tree->root != NULL) {
		d = depth(tree);
		size = tree_size(tree);
	}

	if (d && size) {
		average = (1.0 * d) / size;
		return average;
	}

	return 0;
}

static void
*get_head(node_t *root) {
	if (root->left != NULL) {
		return get_head(root->left)
	} else {
		return root->data;
	}
}

void
*get_tree_head(tree_t *tree) {
	return get_head(tree->root);
}

static node_t
*insert_node(node_t *root, node_t *new, int cmp(void*, void*)) {
	if (root == NULL) {
		return new;
	} else if (cmp(new->data, root->data)) {
		root->left = insert_node(root->left, new, cmp);
	} else {
		root->right = insert_node(root->right, new, cmp);
	}
	return root;
}

tree_t
*insert_in_order(tree_t *tree, void *value) {
	node_t *new;

	new = malloc(sizeof(*new));
	exit_if_null(new, "Initial Allocation");

	new->data = value;
	new->right = NULL;
	new->left = NULL;

	tree->root = insert_node(tree->root, new, tree->cmp);

	return tree;
}

static void
traverse_rec(node_t *root, void action(void*)) {
	if (root) {
		traverse_rec(root->left, action);
		action(root->data);
		traverse_rec(root->right, action);
	}
}

void
traverse_tree(tree_t *tree, void action(void*)) {
	traverse_rec(tree->root, action);
}

static void
*rec_search_tree(node_t *root, void *key, int cmp(void*, void*)) {
	int outcome;
	if (!root) {
		return NULL;
	}

	if ((outcome = cmp(key, root->data)) != 0) {
		return rec_search_tree(root->left, key, cmp);
		return rec_search_tree(root->right, key, cmp);
	} else {
		return root->data;
	}
}

void 
*search_tree(tree_t *tree, void *key) {
	return rec_search_tree(tree->root, key, tree->cmp);
}

static void
rec_free_tree(node_t *root) {
	if (root) {
		rec_free_tree(root->left);
		rec_free_tree(root->right);
		free(root);
	}
}

void
free_tree(tree_t *tree) {
	rec_free_tree(tree->root);
	free(tree);
}

int
is_empty_tree(tree_t *tree) {
	return (tree->root == NULL);
}

void
print_tree(void *x) {
	node_t *p1 = x;
	printf("%d ", (int)p1->data);
	free(p1);
}

int
int_cmp(void *a, void *b) {
	data_t *num1 = a, *num2 = b;
	if (*num1 < *num2) {
		return -1;
	} else if (*num1 > *num2) {
		return +1;
	}
	return 0;
}

void
exit_if_null(void *ptr, const char *msg) {
    if (!ptr) {
        printf("Unexpected null pointer: %s\n", msg);
        exit(EXIT_FAILURE);
    }
}



