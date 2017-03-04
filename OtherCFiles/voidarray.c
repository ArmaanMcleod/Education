#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>

int main(void){
    void** data;
    data = malloc(sizeof(int)*2);
    (int*)data[0] = 5;
    (int*)data[1] = 10;
    printf("%d\n", (int*)data[0]);
    printf("%d\n", (int*)data[1]);
    free(data);
    return 0;
}