/* COMP10002 Assignment 1 */

/*Al necessary imported libraries for this task */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* hash-defines for internal structure */
#define ROWS 1000
#define COLS 30
#define MAX_CHAR 50

/* command-line arguement states */
#define MIN_ARGV 1
#define ARGV_TWO 2

/*max amount of space reserved for output count */
#define COUNTSPC 6

/* four spaces counter constant */
#define FOURSPC 4

/* Important state variables of internal structure */
#define NEWLINE '\n'
#define TAB '\t'

/* Some necessary printing strings needed, just for clarity */
#define BORDER "----"
#define DASH "-"
#define SINGLE_SPACE " "
#define FOUR_SPACE "    "

/* lowerlevel typedef for each string */
typedef char string_t[MAX_CHAR+1];

/* high level struct for storing internal structure, tsv data */
typedef struct {
	string_t str[ROWS][COLS];
	int numrows, numcols;
} tsv_t;

/* function prototypes */
int mygetchar(void);
void read_tsv(tsv_t *data);
void print_stage1(tsv_t *data);
void print_stage2(tsv_t *data);
void print_stage3(tsv_t *data, int columns[], int nheaders);
void print_stage3_headers(tsv_t *data, int columns[], int nheaders);
void initial_sort(tsv_t *data, int column);
void secondary_sort(tsv_t *data, int col, int second);
int find_longest_wordlen(tsv_t *data, int columns[], int nheaders);
int find_last_header(tsv_t *data, int columns[], int nheaders);
void print_dashes(tsv_t *data, int columns[], int nheaders);
void row_swap(char *str1, char *str2);
void print_stage(int stage);

/* main program which controls all action */
int
main(int argc, char *argv[]) {
	tsv_t T;
	int columns[COLS], i, argv_start, argv_count;
	
	read_tsv(&T);

	/* Command-line arguement handling */
	if (argc == MIN_ARGV) {
		print_stage1(&T);

	} else if (argc >= ARGV_TWO) {
		print_stage1(&T);

		/* Applies initial sort */
		initial_sort(&T, atoi(argv[1])-1);

		/* Compares initial sort if secondary keys are available */
		for (i = 1; i < argc-1; i++) {
			secondary_sort(&T, atoi(argv[i])-1, atoi(argv[i+1])-1);
		}
		print_stage2(&T);
		
		/* Stores command-line args in integer array */
		argv_start = 1;
		argv_count = 0;
		for (i = 0; i < argc-1; i++) {
			columns[i] = atoi(argv[argv_start]);
			argv_count++;
			argv_start++;
		}
        
		print_stage3(&T, columns, argv_count);
	}

	return 0;
}

/* function which reads input from stdin. Reads one character at a time from
   the tsv data, and stores each string into internal structure, ready for 
   processing
*/
void 
read_tsv(tsv_t *data) {
	int len, row, col, ch;
	char curr_string[MAX_CHAR+1] = {'\0'};

	len = 0;
	row = 0;
	col = 0;
	while ((ch = mygetchar()) != EOF) {
		if (ch == TAB) {

			/* Copies into string array */
			strcpy(data->str[row][col], curr_string);
			len = 0;
			col++;
			continue;
		}
		else if (ch == NEWLINE) {
			strcpy(data->str[row][col], curr_string);
			col = 0;
			len = 0;
			row++;
			continue;
		}
		
		/* Continues assigning none-tab and non-newline
		   characters to current string */
		curr_string[len] = ch;
		len++;
		curr_string[len] = '\0';

		/* Stories last recorded columns and rows into
		   struct */
		data->numrows = row+1;
		data->numcols = col+1;
	}
}

/* Stage 1
   Prints out recorded data stored in high level struct from
   stdin. Prints out column and row data of structure, and
   prints final row in the end of processing 
*/
void
print_stage1(tsv_t *data) {
	int col, num = 1;

	print_stage(1);

	printf("Input tsv data has %d rows and %d columns\n",
		data->numrows-1, data->numcols);

	/* final row information */
	printf("row %d is:\n", data->numrows-1);
	for (col = 0; col < data->numcols; col++) {
		printf("  %d: %s\t%s\n", num, data->str[0][col], 
		       data->str[data->numrows-1][col]);
		num++;
	}
}

/* Stage 2
   Prints out sorted state of array, based on the command-line
   arguements recorded in main. Prints the first row, middle row[r/2],
   and last row, all of which have been sorted beforehand.
*/
void
print_stage2(tsv_t *data) {
	int col, colnum = 1, row = 1, halfway;

	print_stage(2);
	
	/* first row information*/
	printf("row %d is:\n", row);
	for (col = 0; col < data->numcols; col++) {
		printf("  %d: %s\t%s\n",
			   colnum, data->str[0][col], data->str[row][col]);
		colnum++;
	}

	/* using math.h ceil() method to get the middle data row */
	halfway = ceil((data->numrows)/2);

	/* middle row information*/
	colnum = 1;
	printf("row %d is:\n", halfway);
	for (col = 0; col < data->numcols; col++) {
		printf("  %d: %s\t%s\n",
			   colnum, data->str[0][col], data->str[halfway][col]);
		colnum++;
	}

	/* final row information*/
	colnum = 1;
	printf("row %d is:\n", data->numrows-1);
	for (col = 0; col < data->numcols; col++) {
		printf("  %d: %s\t%s\n", 
			  colnum, data->str[0][col], 
			  data->str[data->numrows-1][col]);
		colnum++;
	}
}

/* function used to find the longest string length in the 
   string array, specifically in last column key specified
   with respect to the column numbers */
int
find_longest_wordlen(tsv_t *data, int columns[], int nheaders) {
	int longest, row;

	longest = 0;
	for (row = 0; row < data->numrows; row++) {
		if (strlen(data->str[row][columns[nheaders-1]-1]) > longest) {
			longest=strlen(data->str[row][columns[nheaders-1]-1]);
		}
	}
	return longest;
}

/* function used to return the length of the last header for
   printing in Stage 3 */
int
find_last_header(tsv_t *data, int columns[], int nheaders) {
	return strlen(data->str[0][columns[nheaders-1]-1]);
}

/* Stage 3
   function which prints out the data headers, along with count
   header which accompanies the final output for Stage 3.
*/
void
print_stage3_headers(tsv_t *data, int columns[], int nheaders) {
	int i, j, spaces = 0, longest_word, last_header;

	/* longest word length obtained from helper function */
	longest_word = find_longest_wordlen(data, columns, nheaders);

	/* last header length obtained from helper function */
	last_header = find_last_header(data, columns, nheaders);

	/* determining the 4 spaces found in every header except last */
	for (i = 1; i < nheaders; i++) {
		spaces+=FOURSPC;
	}
	
	/* the printing of the headers */
	for (i = 1; i <= nheaders; i++) {

		for (j = 1; j < i; j++) {
			printf(FOUR_SPACE);
		}
		printf("%s", data->str[0][columns[i-1]-1]);
		if (i == nheaders) {

			/* printing of single spaces needed until word 
			   "Count" is reached */
			for (i=spaces+last_header; i<spaces+longest_word+1;i++){
				printf(SINGLE_SPACE);
			}
			printf("Count\n");

		} else {
			printf("\n");
		}
	}
}

/* Stage 3
   Core function of printing hierachiel data for this stage. Purpose is
   to generate a report of the counts and rows that match the selected
   column combinations. Relies on the sorted order of data from Stage 2.
*/
void
print_stage3(tsv_t * data, int columns[], int nheaders) {
	int row, col, found = 0,  flagged, count , space, longest_word;
	    
	print_stage(3);

	longest_word = find_longest_wordlen(data, columns, nheaders);

	/* helper function to print necessary dashes in output */
	print_dashes(data, columns, nheaders);
	
	/* helper function to print the headers above hierachial report */
	print_stage3_headers(data, columns, nheaders);

	print_dashes(data, columns, nheaders);

	/* The core logic of printing hierachial data */
	count = 1;
	for (row = 1; row < data->numrows; row++) {
		found = 0;

		/* flag variable, to determine whether count should be printed */
		flagged = 1;

		for (col = 0; col < nheaders; col++) {

			/* Compares the cureent row with previous rows */
			if (strcmp(data->str[row][columns[col]-1], 
				       data->str[row-1][columns[col]-1]) != 0) {
				found = 1;

				if (row > 1 && flagged) {
					printf("%6d\n", count);
					count = 1;
					flagged = 0;
				}
			}

			/* the printing of the first sorting key */
			if (found == 1 && col == 0) {

				/* printing depending on amount of sorting keys used */
				if (nheaders > 1) {
					printf ("%s\n", data->str[row][columns[col]-1]);
				} else {
					printf ("%-*s", longest_word, 
						    data->str[row][columns[col]-1]);
				}

			/* used for differences not involving first sorting key */
			} else if (found == 1 && col != 0) {

				/* printing of spaces */
				for (space = 0; space < col; space++) {
					printf(FOUR_SPACE);
				}

				/* left justify printing */
				printf("%-*s", longest_word, 
				       data->str[row][columns[col]-1]);

				if (col < nheaders-1) {	
					printf("\n");
				}
			}
		}
		/* keep incrementing count if not differences found */
		if (found == 0) {
			count++;
		}
	}
	/* printing last recorded count */
	printf("%6d\n", count);

	print_dashes(data, columns, nheaders);
}

/* helper function used to print dashes in Stage 3. Relies on some
   mathematical reasoning to print correct amount of dashes */
void
print_dashes(tsv_t *data, int columns[], int nheaders) {
	int i, longest;

	longest = find_longest_wordlen(data, columns, nheaders);

	/* 4 space differences for non last headers */
	for (i = 1; i < nheaders; i++) {
		printf(BORDER);
	}

	/* printing depending on longest word length */
	for (i = 0; i < longest; i++) {
		printf(DASH);
	}

	/* allocated spaces required for "Count" */
	for (i = 0; i < COUNTSPC; i++) {
		printf(DASH);
	}

	printf("\n");
}

/* Main sorting function used for sorting rows in Stage 2. 
   Based of Bubble sort algorithm, obtained from 
   "Programming, Problem Solving and Abstraction with C, First Edition"
	From author Allistair Moffat, 2003 Pearson Education Australia.
	Modifications were added to this algorithm for this program, in
	order to basically sort a 2 dimensional array of strings, whereas
	the original algorithm was based on a one dimensional array of integers.
*/
void
initial_sort(tsv_t *data, int column) {
	int row, col, didswaps;

	didswaps = 1;
	while(didswaps) {
		didswaps = 0;

		/* skipping first row of headers */
		for (row = 1; row < data->numrows-1; row++) {

			/* guard for checking differences between rows */
			if ((strcmp(data->str[row][column], data->str[row+1][column])>0)){

				/* added for loop to the algorithm, to make suitable for
				   2D array. also uses helper function to swap rows */
				for (col = 0; col < data->numcols; col++) {
					row_swap(data->str[row][col], 
						     data->str[row+1][col]);

					didswaps = 1;
				}
			}
		}
	}
}

/* Secondary sorting function used for sorting rows in Stage 2. 
   Based of Bubble sort algorithm, obtained from 
   "Programming, Problem Solving and Abstraction with C, First Edition"
	From author Allistair Moffat, 2003 Pearson Education Australia.
	Modifications were added to this algorithm for this program, in
	order to basically sort a 2 dimensional array of strings, whereas
	the original algorithm was based on a one dimensional array of integers.
	This sorting function's primary focus is for secondary sorting keys used
	in the program.
*/
void
secondary_sort(tsv_t *data, int column, int second) {
	int row, col, didswaps;

	didswaps = 1;
	while(didswaps) {
		didswaps = 0;

		for (row = 1; row < data->numrows-1; row++) {

			/* Assumes that row checking of the first key are identical,
			   and comparisions using secondary key must be used */
			if ((strcmp(data->str[row][column], data->str[row+1][column])==0) 
				 && (strcmp(data->str[row][second], 
				 	        data->str[row+1][second]) > 0)) {

				for (col = 0; col < data->numcols; col++) {
					row_swap(data->str[row][col], 
						     data->str[row+1][col]);     

					didswaps = 1;
				}
			}
		}
	}
}

/* helper functopn used to swar rows in program. Based of int_swap function
   taken from "Programming, Problem Solving and Abstraction with C" by
   Allistair Moffat 2003 Pearson Eduction Australia.
*/
void
row_swap(char *str1, char *str2) {
	char temp[MAX_CHAR+1];
	strcpy(temp, str1);
	strcpy(str1, str2);
	strcpy(str2, temp);
}

/* Allistairs modified getchar() function, used to stop distruptions of
   program when reading characters one by one. Prevents program from
   crashing on Unix servers */
int
mygetchar(void) {
	int c;
	while ((c = getchar()) == '\r') {
	}
	return c;
}

/* Nice helper function to print stage headers in program */
void
print_stage(int stage) {
	if (stage == 1) {
		printf("Stage %d Output\n", stage);
	} else {
		printf("\nStage %d Output\n", stage);
	}
}



