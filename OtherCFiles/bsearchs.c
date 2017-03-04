#include <stdio.h>
#include <stdlib.h>

#define BSFOUND 1
#define BS_NOT_FOUND 0

int cmpfunc(const void * a, const void * b);
int binary_search(int A[], int lo, int hi, int *key, int *locn);

int
main(void) {
	int array[] = {1, 2, 3, 4, 5, 6};
   size_t n = sizeof(array)/sizeof(*array);
	//int *item;
	int key = 6, locn;

	/*item = bsearch(&key, array, n, sizeof(*array), cmpfunc);

	if (item != NULL) {
		printf("Found item  = %d\n", *item);
	} else {
		printf("Item = %d could not be found\n", key);
	}*/

   if ((binary_search(array, 0, n, &key, &locn)) == BSFOUND) {
      printf("Found item = %d\n", array[locn]);
   } else {
      
      printf("Item = %d cound not be found\n", key);
   }

	return 0;
}

int
binary_search(int A[], int lo, int hi, int *key, int *locn) {
   int mid, outcome;

   if (lo >= hi) {
      return BS_NOT_FOUND;
   }

   mid = lo + (hi - lo) / 2;
   if ((outcome = cmpfunc(key, A+mid)) < 0) {
      return binary_search(A, lo, mid, key, locn);
   } else if(outcome > 0) {
      return binary_search(A, mid+1, hi, key, locn);
   } else {
      *locn = mid;
      return BSFOUND;
   }
}

int 
cmpfunc(const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}