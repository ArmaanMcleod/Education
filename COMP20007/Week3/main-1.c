#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main(void) {
	List *list = new_list();
	int num;

	printf("Enter some numbers into list:\n");
	while (scanf("%d", &num) == 1) {
		list_add_start(list, num);
		list_add_end(list, num);
	}

	list_remove_end(list);
	list_remove_start(list);

	return 0;
}
