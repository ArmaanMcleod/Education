#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct record {
    int accountno;
    char name[25];
    char address[80];
    struct record *next;
} record_t;

int main() {
    record_t *head = NULL;
    record_t *record1;

    record1 = malloc(sizeof(*record1));
    if (record_1 == NULL) {
        printf("\nrecord_1 is NULL\n");
        exit(EXIT_FAILURE);
    }



    // Assign record_1.accountno
    // Assign record_1.name
    // Assign record_1.address
    // ...

    return 0;
}