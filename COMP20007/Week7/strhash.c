/* * * * * * *
 * Module providing several hash functions for strings
 *
 * created for COMP20007 Design of Algorithms 2017
 * by Matt Farrugia <matt.farrugia@unimelb.edu.au>
 * 
 * additional hash function implementations by ...
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#include "strhash.h"

#define MAX_KEY_LEN 128

// hash everything to a random value (mod size)
unsigned int random_hash(const char *key, unsigned int size) {
	return rand() % size;
}

// hash everything to zero
unsigned int zero_hash(const char *key, unsigned int size) {
	return 0;
}

unsigned int ascii_hash(const char *key, unsigned int size) {
	return (key[0] - '0') % size;
}

unsigned int len_hash(const char *key, unsigned int size) {
	return strlen(key) % size;
}

unsigned int xorhash(const char *key, int seed, int size) {
	int i, c, h;

	h = seed;
	for (i = 0; (c = key[i]) != '\0'; i++) {
		h = h ^ ( (h << 5) + c + (h >> 2));
	}
	return((unsigned int)(h % size));
}

unsigned int universal_hash(const char *key, int size) {
	static int *random_ints;
	size_t i, rlen = MAX_KEY_LEN;
	unsigned int h = 0;

	random_ints = malloc(rlen * sizeof(*random_ints));
	if (random_ints == NULL) {
		fprintf(stderr, "Cannot create static array\n");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < rlen; i++) {
		random_ints[i] = rand();
	}

	for (i = 0; key[i] != '\0'; i++) {
		h += random_ints[i] * (key[i] - '0');
	}

	return (unsigned int)(h % size);
}


/* * *
 * ADD YOUR OWN HASH FUNCTIONS HERE
 */


// generate a hash value for key (a string) to a hash table of size entries,
// using hash method 'method'
// guarantees a return value between 0 (inclusive) and size (non inclusive)
unsigned int hash(const char *key, unsigned int size, char method) {
	switch(method) {
		// really bad hash functions:
		case '0':
			return zero_hash(key, size);
		case 'r':
			return random_hash(key, size);
		case 'a':
			return ascii_hash(key, size);
		case 'l':
			return len_hash(key, size);
		case 'x':
			return xorhash(key, 78302, size);	
		case 'u':
			return universal_hash(key, size);	
		// once you have implemented your own hash functions,
		// add cases to this function to access them from main.c

		default:
			fprintf(stderr, "unknown hashing method '%c'\n", method);
			exit(1);
	}
}

// return the string name of a hash function specified by method
char *name(char method) {
	switch(method) {
		case '0':
			return "zero hash";
		case 'r':
			return "random hash";
		
		// once you have implemented your own hash functions,
		// add cases to this function to access their names from main.c

		default:
			return "unknown";
	}
}