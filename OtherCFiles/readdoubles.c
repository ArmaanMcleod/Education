#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINESIZE 1000
#define ROWS 12
#define COLS 12

int main(void) {
	double data[ROWS][COLS];
	char line[LINESIZE];
	char *lineptr = NULL;
	int offset, row = 0, col;
	FILE *fptr;

	fptr = fopen("Monthly_Rainfall_Himachal.txt","r");
	if (!fptr) {
		fprintf(stderr, "Cannot open file!\n");
		exit(EXIT_FAILURE);
	}

	while (fgets(line, sizeof line, fptr) != NULL && row < ROWS) {
		lineptr = line;
		col = 0;
		while (sscanf(lineptr, " %lf%n", &data[row][col], &offset) == 1 && col < COLS) {
			lineptr += offset;
			col++;
		}
		row++;
	}

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			printf("%.2f ", data[i][j]);
		}
		printf("\n");
	}

	fclose(fptr);

	return 0;
}