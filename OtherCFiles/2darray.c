#include <stdio.h>

#define ROWS 49
#define COLS 49

void fillMap(char (*map)[COLS], size_t rows, size_t cols);
void printMap(char (*map)[COLS], size_t rows, size_t cols);

int main(void) {
    char map[ROWS][COLS];
    size_t rows = ROWS, cols = COLS;
    
    fillMap(map, rows, cols);

    printMap(map, rows, cols);

    return 0;
}

void fillMap(char (*map)[COLS], size_t rows, size_t cols) {
    size_t i, j;

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            map[i][j] = 'x';
        }
        map[i][j] = '\0';
    }
}
    


void printMap(char (*map)[COLS], size_t rows, size_t cols) {
    size_t i, j;

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
}
