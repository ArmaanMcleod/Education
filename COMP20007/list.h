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

extern list_t *new_list(void);

extern list_t *list_add_start(list_t *list, char *name, int month);

extern list_t *list_add_end(list_t *list, char *name, int month);

extern list_t *list_remove_start(list_t *list);

extern list_t *list_remove_end(list_t *list);

extern size_t list_size(list_t *list);

extern void print_list(list_t *list);

extern void free_list(list_t *list);