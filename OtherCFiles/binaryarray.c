#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define INITSIZE 3

typedef struct {
	const uint8_t *p_arr;
	uint8_t currsize;
	uint8_t max;
	uint8_t min;
} array_t;

typedef struct {
	array_t *A;
	uint8_t numarrays;
} data_t;

data_t *initialize_meta_data(void);
int check_arrays(const uint8_t arr[], const size_t n, uint8_t *key);
void set_arrays(data_t *data, const uint8_t arr[], const size_t n, int index);
void search_arrays(data_t *data, uint8_t key);
int cmpfunc(const void *a, const void *b);

int
main(int argc, char *argv[]) {
	const uint8_t arr_1[] = {1, 4, 53 , 209};
	const uint8_t arr_2[] = {54, 56, 90, 100};
	const uint8_t arr_3[] = {6, 7, 8, 9, 10};

	const size_t size1 = sizeof(arr_1)/sizeof(*arr_1);
	const size_t size2 = sizeof(arr_2)/sizeof(*arr_2);
	const size_t size3 = sizeof(arr_3)/sizeof(*arr_3);

	data_t *data = initialize_meta_data();

	data->A = malloc(data->numarrays * sizeof(*(data->A)));

	set_arrays(data, arr_1, size1, 0);
	set_arrays(data, arr_2, size2, 1);
	set_arrays(data, arr_3, size3, 2);

	uint8_t key = 209;

	search_arrays(data, key);

	free(data->A);
	free(data);

	return 0;
}

void
search_arrays(data_t *data, uint8_t key) {
	int i;

	for (i = 0; i < data->numarrays; i++) {
		if ((key <= data->A[i].max) && (key >= data->A[i].min)) {
			if (check_arrays(data->A[i].p_arr, data->A[i].currsize, &key)) {
				printf("%d found in array number: %d\n", key, i+1);
			}
		} else {
			printf("array number: %d skipped\n", i+1);
		}
	}
}

void
set_arrays(data_t *data, const uint8_t arr[], const size_t n, int index) {
	data->A[index].p_arr = arr;
	data->A[index].currsize = n;
	data->A[index].max = data->A[index].p_arr[data->A[index].currsize-1];
	data->A[index].min = data->A[index].p_arr[0];
}

data_t
*initialize_meta_data(void) {
	data_t *data = malloc(sizeof(*data));
	data->A = NULL;
	data->numarrays = INITSIZE;
	return data;
}

int
check_arrays(const uint8_t arr[], const size_t n, uint8_t *key) {
	uint8_t *item;

	item = bsearch(key, arr, n, sizeof(*arr), cmpfunc);

	if (item != NULL) {
		return 1;
	}

	return 0;
}

int
cmpfunc(const void *a, const void *b) {
	return (*(uint8_t*)a > *(uint8_t*)b) - (*(uint8_t*)a < *(uint8_t*)b);
}
