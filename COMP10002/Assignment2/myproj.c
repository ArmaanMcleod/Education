/* Solution to COMP10002 Assignment 1, October 2016
   Armaan Dhaliwal-Mcleod, a.dhaliwalmcleod@student.unimelb.edu.au
   Student ID: 837674
*/

/*All necessary libraries imported */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <math.h>

/*hash defines for important aspects of program */

/* max input chars */
#define MAXCHAR 999

/* max printing pairs */
#define MAXPAIR 10

/* max queries allowed per line */
#define MAXQUERY 20

/* some extra printing */
#define FOURSPC "    "
#define CREDITS "\nTa da-da-daaah...\n"

/* flat for nothing found in binary search */
#define NOT_FOUND (-1)

#define TOP_3 3

/* double comparison checkers */
#define EPSILON 1e-8
#define DOUBLE_ZERO ((double) 0)

/*lower level typedef for input buffer */
typedef char input_t[MAXCHAR+1];

/*hierachial structs passed throughout program */
typedef struct {
	int docid;
	int freq;
} pairs_t;

/*lower level struct for each member of index */
typedef struct {
	char *word;
	pairs_t *pairs;
	int npairs;
	int numlines;
	int index_loc;
} data_t;

/*low level struct needed for stage 3 */
typedef struct {
	double accumulate;
	int document;
	int length;
} doclen_t;

/*main struct which holds index */
typedef struct {
	data_t *data;
	int N;
	int numwords;
	doclen_t *doclens;
} index_t;

/*function prototypes */
void print_array(index_t *index);
void print_stage1(index_t *index);
void print_stage2(index_t *index, char *words[], int word_count);
void print_stage3(index_t *index);
int total_pairs(index_t *index);
index_t *initialize_index(void);
void print_pairs(index_t *index, int term);
void read_index(index_t*index, FILE *filename);
void read_queries(index_t *index);
void insert_data(index_t *index, char *word, int *scores, int size, int count);
int binary_search(index_t *index, char *string, int high, int low);
int find_max_docid(index_t *index);
void calc_documentlens(index_t *index);
void calc_accumulate(index_t *index, int index_found);
void initialize_accumulate(index_t *index);
double get_average_mean(index_t *index);
void free_index(index_t *index);
void set_doclens(index_t *index);
int double_equal(double a, double b);
int mygetchar(void);
int mygetc(FILE *filename);
double my_log(double x, int base);
int sortcmp(const void *a, const void *b);
int compare_int( const int a , const int b);
void print_stage(int stage);

/* main program which controls all action */
int
main(int argc, const char *argv[]) {
	FILE *filename;

	/* pointer to main struct */
	index_t *index;

	index = initialize_index();

	/* file handling needed for program */
	filename = fopen(argv[1], "r");

	if (filename == NULL) {
		fprintf(stderr, "Error Reading File!\n");
		exit(EXIT_FAILURE);
	}
	
	/* Sequential function calls for displaying outputs */
	read_index(index, filename);

	print_stage1(index);

	read_queries(index);

	printf(CREDITS);

	/* freeing function call for freeing whole index */
	free_index(index);

	fclose(filename);

	return 0;
}

/* function which reads entire index file, and stores in main struct */
void
read_index(index_t*index, FILE *filename) {
	int ch;
	input_t word;
	int *scores, num_size = 1, num_count = 0;
	char *buffer = NULL;
	int str_size = 1, str_count = 0;
	int word_len = 0, space = 0;
	int count = 0;

	/* Declaring dynamic arrays, ready for processing */
	scores = malloc(num_size * sizeof(int));

	buffer = malloc(str_size * sizeof(char));

	index->data = malloc((count + 1) * sizeof(data_t));

	while ((ch = mygetc(filename)) != EOF) {

		/* Checking for alpha characters */
		/*process through buffer */
		if (isalpha(ch)) {
			word[word_len++] = ch;
			word[word_len] = '\0';
		}

		/*Checking for integers */
		/*process through second buffer */
		if (isdigit(ch)) {

			/* check for space */
			space = 1;

			/*But is there space available? */
			if (str_size == str_count) {
				str_size++;

				/*realocate memory for more space */
				buffer = realloc(buffer, (2*str_size)*sizeof(*buffer)) ;
			}
			buffer[str_count++] = ch;
		}

		/* Check for spaces after first number */
		if (isspace(ch) && space == 1) {
			buffer[str_count] = '\0';

			/* is there space? */
			if (num_size == num_count) {
				num_size++;
				scores = realloc(scores, (2*num_size) *sizeof(*scores));
			}
			scores[num_count++] = atoi(buffer);

			str_size = 1;
			str_count = 0;
		}

		/* newline found, process whole line just read */
		if (ch == '\n') {
			index->data = realloc(index->data, (count+2) * sizeof(data_t));

			/*insert data one at a time */
			insert_data(index, word, scores, num_size, count);

			count++;

			/*reset used counters, to be safe */
			num_count = 0;
			num_size = 1;
			word_len = 0;
			str_count = 0;
			str_size = 1;
			space = 0;
		}
	}

	/* information to add to struct */
	index->numwords = count;
	index->N = find_max_docid(index);

	/* free the buffers when done */
	free(scores);
	free(buffer);
}

/* function used to insert data into array of structures */
/* inserts one row every time called */
void
insert_data(index_t *index, char *word, int *scores, int size, int count) {
    int posfreq = 0, posdoc = 0, i;

    /*Dynamic arrays, needed for arrays declared in structs */
	index->data[count].word = malloc(strlen(word)+1);
	index->data[count].pairs = malloc((2*size) * sizeof(pairs_t));

	/* copy over relevant information for structs */
	index->data[count].numlines = scores[0];
	index->data[count].npairs = (size-1)/2;

	strcpy(index->data[count].word, word);

	for (i = 1; i < size; i++) {

		if (i % 2 == 0) {
			/* for fdt values */
			index->data[count].pairs[posfreq++].freq = scores[i];

			/* for document numbers */
		} else {
			index->data[count].pairs[posdoc++].docid = scores[i];
		}
	}

	/* index location in whole index structure */
	index->data[count].index_loc = count+1;
}

/* function which frees all the dynamic arrays */
/* All of which are contained in structure */
void
free_index(index_t *index) {
	int word;

	/*one by one, free the words and pairs */
	for (word = 0; word < index->numwords; word++) {
		free(index->data[word].word);
		free(index->data[word].pairs);
	}

	/*free more */
	free(index->data);
	free(index->doclens);

	/*free whole index */
	free(index);

}

/* function which initializes index structure */
index_t
*initialize_index(void) {
	index_t *index;
	index = malloc(sizeof(index_t));

	/*definetly not needed */
	/*but just to be safe */
	index->data = NULL;
	index->numwords = 0;
	index->N = 0;
	index->doclens = NULL;

	return index;
}

/* function used to print stage one of the program */
/* prints out pair information concerning top two
   and bottom two words located in index */
void
print_stage1(index_t *index) {
	int totalpairs, i, first = 0, second = 1;

	print_stage(1);

	/* get the total pairs from helper function */
	totalpairs = total_pairs(index);

	printf("index has %d terms and %d (d,fdt) pairs\n",
		   index->numwords, totalpairs);

	/* loop through, get as you come across them */
	for (i = 0; i < index->numwords; i++) {
		if ((i == first) || (i == second) || (i == index->numwords-1) ||
		   (i == index->numwords-2)) {
			printf("term %d is \"%s\":\n", i+1, index->data[i].word);
			printf(FOURSPC);
			print_pairs(index, i);
		} 
	}
}

/* function used to print pairs for stage 1 output */
void
print_pairs(index_t *index, int term) {
	int i;

	/* only goes up to ten pairs */
	for (i = 0; i < index->data[term].npairs && i < MAXPAIR; i++) {
		if (i > 0) {
			printf("; ");
		} 
		if (i == MAXPAIR-1) {
			printf("...");
		} else {
			printf("%d,%d", index->data[term].pairs[i].docid,
				          index->data[term].pairs[i].freq);
		}
	}
	printf("\n");
}

/* function which handles reading the queries */
void
read_queries(index_t *index) {
	char *word = NULL;
	char *words[MAXQUERY];
	int word_size = 1, word_len = 0, word_count = 0;
	int found = 0; 
	int i, ch, char_count = 0;

	/* make space for word to be processed */
	word = malloc(word_size *sizeof(char));

	/* helpful document calculator */
	calc_documentlens(index);

	while ((ch = mygetchar()) != EOF) {

		/* looking for lowercase letters */
		if (isalpha(ch) && tolower(ch)) {
			char_count++;

			/* found one, but is there space? */
			if (word_size == word_len) {
				word_size++;
				word = realloc(word, (2*word_size) * sizeof(char));
			}
			word[word_len++] = ch;
			word[word_len] = '\0';
		}

		/*checking for space and whether a word exists */
		if (isspace(ch) && word_size > 1) {
			char_count++;
			found = 0;

			/* basic linear search to check previous words */
			for (i = 0; i < word_count && !found; i++) {
				found = (strcmp(word, words[i]) == 0);
			}

			/* exact guard to enable correct words to be inserted */
			if ((!found) && (word_count < MAXQUERY) &&
			    (char_count <= MAXCHAR)) {

				/* make space for word */
				words[word_count] = malloc(strlen(word)+1);
				strcpy(words[word_count], word);
				word_count++;
			}
			word_len = 0;
			word_size = 1;
		}

		/* newline found */
		/* process queries found on line inputted */
		if (ch == '\n' && word_count > 0) {

			/* initialize accumulator */
			initialize_accumulate(index);

			/*stage printing functions */
			print_stage2(index, words, word_count);

			print_stage3(index);
		 	
		 	/* resetting  inportant information */
			word_len = 0;
			word_size = 1;
			word_count = 0;
			char_count = 0;
		}
	}

	/* free buffer when done */
	free(word);
}

/* function responsible for printing stage 2 */
void
print_stage2(index_t *index, char *words[], int word_count) {
	int i, index_found, first, last;

	first = 0;
	last = index->numwords-1;

	print_stage(2);

	/* checks words against binary search */
	/* Specifically for the index */
	for (i = 0; i < word_count; i++) {
		printf(FOURSPC);

		/*calling binary search to perform the search */
		index_found = binary_search(index, words[i], last, first);
		if (index_found != NOT_FOUND) {
			printf("\"%s\" is term %d\n", words[i], index_found);

			/*calculating the accumulated score for each word */
			calc_accumulate(index, index_found);
		} else {
			printf("\"%s\" is not indexed\n", words[i]);
		}
	}
}

/* Stage three printing function */
void
print_stage3(index_t *index) {
	int i;

	print_stage(3);

	/* quick sort call which sorts all of the accumulators at once */
	/* please have mercy */
	qsort(index->doclens, index->N, sizeof(doclen_t), sortcmp);

	/* prints out valid scores */
	for (i = 0; i < TOP_3; i++) {
		if (index->doclens[i].accumulate > DOUBLE_ZERO) {
			printf("    document   %d: score  %.3f\n", 
			       index->doclens[i].document, index->doclens[i].accumulate);
		}
	}

}

/* function used to gather average mean of documents */
double
get_average_mean(index_t *index) {
	int average_count = 0, i;
	double average_mean = 0.0;

	average_count = 0;
	average_mean = 0.0;

	/* loops over all document lengths */
	/*adds to total sum */
	for (i = 0; i < index->N; i++) {
		average_count += index->doclens[i].length;
	}

	average_mean = ((1.0)* average_count)/(index->N);

	return average_mean;
}

/* helper function */
/* initialize accumulators for summing */
void
initialize_accumulate(index_t *index) {
	int i;

	for (i = 0; i < index->N; i++) {
		index->doclens[i].accumulate = 0.0;
	}
}


/* helper function used to sum accumulators */
/* is called everytime index is checked */
void
calc_accumulate(index_t *index, int index_found) {
	int pair, doc, word;
	double score = 0.0, ld = 0.0;
	double logs, average_mean;

	word = index_found-1;

	/* retrieving the average mean */
	average_mean = get_average_mean(index);

	for (pair = 0; pair < index->data[word].npairs; pair++) {
	
		for (doc = 0; doc < index->N; doc++) {
			
			/* thorough check if the document being searched matches */
			if (index->data[word].pairs[pair].docid == 
				index->doclens[doc].document) {

				/* calculations as per BMDS equation */
				ld = (1.2) * ((1 - 0.75) + ((0.75)*
					 (index->doclens[doc].length) / average_mean));
	
				logs = (index->N + 0.5) / (index->data[word].numlines);
	
				score = ((2.2 * index->data[word].pairs[pair].freq) / 
					     (ld+index->data[word].pairs[pair].freq)
						* (my_log(logs, 2)));
	
		        /* accumulate score */
				index->doclens[doc].accumulate += score;
			}
		}
	}
}

/* helper function for performing log base 2 */
double 
my_log(double x, int base) { 
	return log(x) / log(base); 
} 

/* helper function for calculatinf N */
/* is inserted into struct in read_index function */
int
find_max_docid(index_t *index) {
	int word, pair, max;

	/*performing normal max search for highest document numbers */
	max = index->data[0].pairs[0].docid;

	for (word = 0; word < index->numwords; word++) {

		for (pair = 0; pair < index->data[word].npairs; pair++) {

			if ((index->data[word].pairs[pair].docid) > max) {
					max = index->data[word].pairs[pair].docid;
			}
		}
	}
	return max;
}

/* set document lengths for calculations */
void
set_doclens(index_t *index) {
	int doc, startdoc = 1;

	/* make sure there is enough space for both freq and id */
	index->doclens = (doclen_t*)malloc((2*index->N) * sizeof(doclen_t));

	/* initializing time */
	for (doc = 0; doc < index->N; doc++) {
		index->doclens[doc].length = 0;
		index->doclens[doc].document = startdoc;
		startdoc++;
	}
}

/* function which calculates over all document lengths */
void
calc_documentlens(index_t *index) {
	int word, pair, doc;

	/* set the initial values */
	set_doclens(index);

	/* just normal loop checking */
	for (doc = 0; doc < index->N; doc++) {

		for (word = 0; word < index->numwords; word++) {

			for (pair = 0; pair < index->data[word].npairs; pair++) {	

				/* checking if document matches required docid */
				if (index->data[word].pairs[pair].docid == 
					index->doclens[doc].document) {
					index->doclens[doc].length += 
				    index->data[word].pairs[pair].freq;
				}
			}
		}
	}
}

/* binary search function
   Based of Binary Search Function, obtained from
   "Programming, Problem Soving and Abstraction with C"
   From auther Allistair Moffat, 2003 Pearson Australia.
   Modifcations were added to thing program, to return
   the index found, rather than the word */
int
binary_search(index_t *index, char *string, int high, int low) {
	int mid, outcome;

	/*base case, not wanted case */
	if (low >= high) {
		return NOT_FOUND;
	}

	/*middle of array */
	mid = (low+high)/2;

	/* out come we want. Keep recursively searching until found */
	if ((outcome = strcmp(index->data[mid].word, string)) == 0) {
		return index->data[mid].index_loc;
	} else if (outcome < 0) {
		return binary_search(index, string, high, low+1);
	} else {
		return binary_search(index, string, high-1, low);
	}
}

/* helper function used to calculate total pairs in index */
int
total_pairs(index_t *index) {
	int totalpairs = 0, word;

	for (word = 0; word < index->numwords; word++) {
		totalpairs += index->data[word].numlines;
	}
	return totalpairs;
}

/* qsort comparison function */
/* first checks for differing scores 
   Then sorts by document number */
int
sortcmp(const void *a , const void *b ) {
    const doclen_t* const num1 = a;
    const doclen_t* const num2 = b;

    /* safe equal double comparison checking */
    if(double_equal(num1->accumulate, num2->accumulate)) {

    	/* if equal return a return integer */
    	/* to determine which one is bigger */
    	return compare_int(num1->document, num2->document);
	}else if( num1->accumulate > num2->accumulate) {
    	return -1;
	}else {
    	return 1;
	}
}

/* function to check double comparison */
int
double_equal(double a, double b) {
	return fabs(a-b) < EPSILON;
}

/* function which compares two ints */
/* and returns if there is a difference found */
int
compare_int(const int a , const int b) {
    if( a < b ) {
        return -1;
    }else if( a > b ) {
        return 1;
    }
    return 0;
}

/* Allistairs function to skip carriage return */
int
mygetchar(void) {
	int c;
	while ((c = getchar()) == '\r') {
	}
	return c;
}

/* A safe function to have */
int
mygetc(FILE *filename) {
	int c;
	while ((c = getc(filename)) == '\r') {
	}
	return c;
}

/* helpful function for printing stages */
void
print_stage(int stage) {
	if (stage == 1) {
		printf("Stage %d Output\n", stage);
	} else {
		printf("\nStage %d Output\n", stage);
	}
}

/*Algorithms are fun! */