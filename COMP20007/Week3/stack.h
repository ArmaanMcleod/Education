#include "list.h"

List *new_stack(void);

void free_stack(List *Stack);

void stack_push(List *Stack, int data);

void stack_pop(List *Stack);

int stack_size(List *Stack);