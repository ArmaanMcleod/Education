#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int arr[] = {1, 2, 3, 4};
	int *ptr = &arr[0];

	for (size_t i = 0; i < sizeof *ptr; i++) {
		printf("%d\n", ptr[i]);
	}

	return 0;
}