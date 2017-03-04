#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROWS 5

#define MALLOC_MSG "Memory Allocation"
#define REALLOC_MSG "Memory Reallocation"

typedef struct {
	char **line;
	int numcols;
} array_t;

typedef struct {
	array_t *A;
	int numrows;
} arrays_t;

void read_string(arrays_t *Array, const char *array[], const size_t size);
arrays_t *initialize_array(void);
void print_and_free(arrays_t *Array);
void check_malloc(void *ptr, const char *msg);

int
main(int argc, char *argv[]) {
	const char *array1[] = {
    	"echo", "hi", "|", "sed", "s/i/ey/g", "|", "sed", "s/y/ll/g", "|", "sed", "s/$/o/g", "|", "cat"};

    const size_t size = sizeof(array1)/sizeof(*array1);

    arrays_t *Array = initialize_array();
    
    read_string(Array, array1, size);

    print_and_free(Array);

	return 0;
}

void
read_string(arrays_t *Array, const char *array[], const size_t size) {
	int i, cols = 0, rows = 0;
    const char *split = "|";
    size_t arrsize = ROWS, currsize;

    Array->A = malloc(arrsize * sizeof(*(Array->A)));
    check_malloc(Array->A, MALLOC_MSG);

    for (i = 0; i < size; i++) {
    	if (arrsize == rows) {
    		arrsize *= 2;
    		Array->A = realloc(Array->A, arrsize * sizeof(*(Array->A)));
    		check_malloc(Array->A, REALLOC_MSG);
    	}

    	if (strcmp(array[i], split) != 0) {
    		currsize = cols+1;
    		Array->A[rows].line = realloc(Array->A[rows].line, currsize * sizeof(*(Array->A[rows].line)));
    		check_malloc(Array->A[rows].line, REALLOC_MSG);

    		Array->A[rows].line[cols] = malloc(strlen(array[i])+1);
    		check_malloc(Array->A[rows].line[cols], MALLOC_MSG);
    		strcpy(Array->A[rows].line[cols], array[i]);
    		cols++;
    		Array->A[rows].numcols = cols;
    	} else {
    		rows++;
    		cols = 0;
    	}
    	Array->numrows = rows+1;
    }
}

void
print_and_free(arrays_t *Array) {
	int row, col;

	for (row = 0; row < Array->numrows; row++) {
		printf("{");
    	for (col = 0; col < Array->A[row].numcols; col++) {
    		printf("%s", Array->A[row].line[col]);
    		free(Array->A[row].line[col]);
    		if (col != Array->A[row].numcols-1) {
    			printf(", ");
    		}
    	}
    	free(Array->A[row].line);
    	printf("}\n");
    }
    free(Array->A);
    free(Array);
}

void
check_malloc(void *ptr, const char *msg) {
	if (!ptr) {
		printf("unexpected null pointer: %s\n", msg);
		exit(EXIT_FAILURE);
	}
}


arrays_t
*initialize_array(void) {
	arrays_t *Array = malloc(sizeof(*Array));
	check_malloc(Array, MALLOC_MSG);
	Array->numrows = 0;
	return Array;
}
