#include <stdio.h>
#include <string.h>

#define SIZE 100

int main(void) {
	char array[SIZE] = {'\0'};

	memset(array, 'A', sizeof(array)-1);

	printf("array = %s\n", array);
	printf("length of array = %zu\n", strlen(array));

	return 0;
}