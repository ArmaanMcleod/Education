/* * * * * * * * *
 * Dynamic hash table using extendible hashing with multiple keys per bucket,
 * resolving collisions by incrementally growing the hash table
 *
 * created for COMP20007 Design of Algorithms - Assignment 2, 2017
 * by Armaan Dhaliwal-McLeod
 * inspired from Matt Farrigia's xtndbl1 implementation
 */

// necessary libraries for this module
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "xtndbln.h"

// macro to calculate the rightmost n bits of a number x
#define rightmostnbits(n, x) (x) & ((1 << (n)) - 1)

// a bucket stores an array of keys
// it also knows how many bits are shared between possible keys, and the first 
// table address that references it
typedef struct xtndbln_bucket {
	int id;			// a unique id for this bucket, equal to the first address
					// in the table which points to it
	int depth;		// how many hash value bits are being used by this bucket
	int nkeys;		// number of keys currently contained in this bucket
	int64 *keys;	// the keys stored in this bucket
} Bucket;

// a hash table is an array of slots pointing to buckets holding up to 
// bucketsize keys, along with some information about the number of hash value 
// bits to use for addressing
struct xtndbln_table {
	Bucket **buckets;	// array of pointers to buckets
	int size;			// how many entries in the table of pointers (2^depth)
	int depth;			// how many bits of the hash value to use (log2(size))
	int bucketsize;		// maximum number of keys per bucket
	int load;           // how many keys are being stored in the table
	int nbuckets;       // number of buckets in table
	int time;           // how much CPU time has been used for insert/lookup keys
};

// create a new bucket first referenced from 'first_address', based on 'depth'
// bits of its keys' hash values
static Bucket *new_bucket(int first_address, int depth, int bucketsize) {
	Bucket *bucket = malloc(sizeof(*bucket));
	assert(bucket != NULL);

	bucket->id = first_address;
	bucket->nkeys = 0;
	bucket->depth = depth;

	// create space for bucketsize keys
	bucket->keys = malloc(bucketsize * sizeof(*(bucket->keys)));
	assert(bucket->keys);

	return bucket;
}

// initialise an extendible hash table with 'bucketsize' keys per bucket
XtndblNHashTable *new_xtndbln_hash_table(int bucketsize) {
	XtndblNHashTable *table = malloc(sizeof(*table));
	assert(table != NULL);

	table->bucketsize = bucketsize;
	table->size = 1;

	table->buckets = malloc(table->size * sizeof(*(table->buckets)));
	assert(table->buckets != NULL);

	table->buckets[0] = new_bucket(0, 0, bucketsize);

	table->depth = 0;
	table->time = 0;
	table->nbuckets = 1;
	table->load = 0;

	return table;
}


// free all memory associated with 'table'
void free_xtndbln_hash_table(XtndblNHashTable *table) {
	assert(table != NULL);

	int i;

	// loop backwards through the array of pointers, freeing buckets only as we
	// reach their first reference
	// (if we loop through forwards, we wouldn't know which reference was last)
	for (i = table->size-1; i >= 0; i--) {
		if (table->buckets[i]->id == i) {
			free(table->buckets[i]->keys);
			free(table->buckets[i]);
		}
	}

	// free array of bucket pointers
	free(table->buckets);

	// free the table itself
	free(table);
}

// lookup whether 'key' is inside 'table'
// returns true if found, false if not
bool xtndbln_hash_table_lookup(XtndblNHashTable *table, int64 key) {
	assert(table != NULL);
	int start_time = clock(); // start timing

	// calculate table address for this key
	int address = rightmostnbits(table->depth, h1(key));
	int i;

	// look for the key in that bucket (unless it's empty)
	bool found = false;
	for (i = 0; i < table->buckets[address]->nkeys; i++) {
		if (table->buckets[address]->keys[i] == key) {
			found = true;
		}
	}

	// add time elapsed to total CPU time before returning result
	table->time += clock() - start_time;
	return found;
}

// double the table of bucket pointers, duplicating the bucket pointers in the
// first half into the new second half of the table	
static void double_table(XtndblNHashTable *table) {
	int size = table->size * 2, i;

	// verify that size hasnt exceed maximum table size
	assert(size < MAX_TABLE_SIZE && "error: table has grown too large!");

	// creates more more space on the heap, this time for twice as many 
	// bucket pointers
	table->buckets = realloc(table->buckets, (sizeof *table->buckets) * size);
	assert(table->buckets);

	// copy the pointers over safely
	for (i = 0; i < table->size; i++) {
		table->buckets[table->size + i] = table->buckets[i];
	}

	// update the table size
	table->size = size;
	table->depth++;
}

// reinsert a key into the hash table after splitting a bucket --- we can assume
// that there will definitely be space for this key because it was already
// inside the hash table previously
// use 'xtndbln_hash_table_insert()' instead for inserting new keys
static void reinsert_keys(XtndblNHashTable *table, int64 *keys, int nkeys) {
	int i, address;

	for (i = 0; i < nkeys; i++) {

		// update address from current key
		address = rightmostnbits(table->depth, h1(keys[i]));

		// Are we legally allowed to place more keys in this bucket?
		if (table->buckets[address]->nkeys < table->bucketsize) {
			table->buckets[address]->keys[table->buckets[address]->nkeys] = keys[i];
			table->buckets[address]->nkeys++;
		}
	}
}

// split the bucket in 'table' at address 'address', growing table if necessary
static void split_bucket(XtndblNHashTable *table, int address) {
	int i, prefix;

	// do we need to grow the table?
	if (table->buckets[address]->depth == table->depth) {
		double_table(table);
	}

	// create a new bucket
	Bucket *bucket = table->buckets[address];
	int depth = bucket->depth;
	int first_address = bucket->id;

	int new_depth = depth+1;
	bucket->depth = new_depth;

	// new bucket's first address ill be a 1 but plus the old first address
	int new_first_address = 1 << depth | first_address;
	Bucket *newbucket = new_bucket(new_first_address, new_depth, table->bucketsize);
	table->nbuckets++;

	// redirect every second address pointing to this bucket to the new bucket
	// construct addresses by joining a bit 'prefix' and a bit 'suffix'
	// suffix: a 1 bit followed by the previous bucket bit address
	int bit_address = rightmostnbits(depth, first_address);
	int suffix = (1 << depth) | bit_address;

	// prefix: all bitstrings of length equal to the difference between the new
	// bucket depth and the table depth
	// use a for loop to enumerate all possible prefixes less than maxprefix:
	int maxprefix = 1 << (table->depth - new_depth);

	for (prefix = 0; prefix < maxprefix; prefix++) {

		// construct address by joining this prefix and the suffix
		int a = (prefix << new_depth) | suffix;

		// redirect this table entry to point at the new bucket
		table->buckets[a] = newbucket;
	}

	int numkeys = bucket->nkeys;

	// filter the key from the old bucket into its rightful place in the new 
	// table (which may be the old bucket, or may be the new bucket)

	// create temporary array, ready to copy keys over
	int64 *keys = malloc(numkeys * sizeof(*keys));
	assert(keys != NULL);

	// set old buckets size to 0, to avoid overflow
	bucket->nkeys = 0;

	// safely copy over bucket pointers
	for (i = 0; i < numkeys; i++) {
		keys[i] = bucket->keys[i];
	}

	// remove and reinsert the key
	reinsert_keys(table, keys, numkeys);

	// done with array
	free(keys);
}

// insert 'key' into 'table', if it's not in there already
// returns true if insertion succeeds, false if it was already in there
bool xtndbln_hash_table_insert(XtndblNHashTable *table, int64 key) {
	assert(table != NULL);
	int start_time = clock(); // start timing

	// calculate table address
	int hash = h1(key);
	int address = rightmostnbits(table->depth, hash);

	// is the key already there?
	if (xtndbln_hash_table_lookup(table, key)) {
		return false;
	}

	// if not, make space in the table until our target bucket has space
	while (table->buckets[address]->nkeys == table->bucketsize) {
		split_bucket(table, address);

		// and recalculate address because we might now need more bits
		address = rightmostnbits(table->depth, hash);
	}

	// space now available, insert key
	int key_index = table->buckets[address]->nkeys;
	table->buckets[address]->keys[key_index] = key;
	table->buckets[address]->nkeys++;
	table->load++;

    // add time elapsed to total CPU time before returning
	table->time += clock() - start_time;
	return true;
}


// print the contents of 'table' to stdout
void xtndbln_hash_table_print(XtndblNHashTable *table) {
	assert(table);
	printf("--- table size: %d\n", table->size);

	// print header
	printf("  table:               buckets:\n");
	printf("  address | bucketid   bucketid [key]\n");
	
	// print table and buckets
	int i;
	for (i = 0; i < table->size; i++) {
		// table entry
		printf("%9d | %-9d ", i, table->buckets[i]->id);

		// if this is the first address at which a bucket occurs, print it now
		if (table->buckets[i]->id == i) {
			printf("%9d ", table->buckets[i]->id);

			// print the bucket's contents
			printf("[");
			for(int j = 0; j < table->bucketsize; j++) {
				if (j < table->buckets[i]->nkeys) {
					printf(" %llu", table->buckets[i]->keys[j]);
				} else {
					printf(" -");
				}
			}
			printf(" ]");
		}
		// end the line
		printf("\n");
	}

	printf("--- end table ---\n");
}


// print some statistics about 'table' to stdout
void xtndbln_hash_table_stats(XtndblNHashTable *table) {
	assert(table != NULL);

	printf("--- table stats ---\n");

	// print some stats about table state
	printf("Table size: %d\n", table->size);
	printf("Table number of keys: %d\n", table->load);
	printf("Table number of buckets: %d\n", table->nbuckets);
	printf("Number of keys allowed per bucket: %d\n", table->bucketsize);

	// print out the load factor for the table
	printf("load factor: %.3f%%\n", table->load * 100.0 / table->size);

	// also calculate CPU usage in seconds and print this
	float seconds = table->time * 1.0 / CLOCKS_PER_SEC;
	printf("    CPU time spent: %.6f sec\n", seconds);

	printf("--- end stats ---\n");
}
