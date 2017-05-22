/* * * * * * * * *
* Dynamic hash table using a combination of extendible hashing and cuckoo
* hashing with a single keys per bucket, resolving collisions by switching keys 
* between two tables with two separate hash functions and growing the tables 
* incrementally in response to cycles
*
* created for COMP20007 Design of Algorithms - Assignment 2, 2017
* by Armaan Dhaliwal-McLeod
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "xuckoo.h"

// macro to calculate the rightmost n bits of a number x
#define rightmostnbits(n, x) (x) & ((1 << (n)) - 1)

// some helpeful table flags
#define TABLE1 1
#define TABLE2 2

// a bucket stores a single key (full=true) or is empty (full=false)
// it also knows how many bits are shared between possible keys, and the first 
// table address that references it
typedef struct bucket {
	int id;		// a unique id for this bucket, equal to the first address
				// in the table which points to it
	int depth;	// how many hash value bits are being used by this bucket
	bool full;	// does this bucket contain a key
	int64 key;	// the key stored in this bucket
} Bucket;

// an inner table is an extendible hash table with an array of slots pointing 
// to buckets holding up to 1 key, along with some information about the number 
// of hash value bits to use for addressing
typedef struct inner_table {
	Bucket **buckets;	// array of pointers to buckets
	int size;			// how many entries in the table of pointers (2^depth)
	int depth;			// how many bits of the hash value to use (log2(size))
	int nkeys;			// how many keys are being stored in the table
	int nbuckets;       // how many buckets are being stored in the table
	int tablenum;       // number which determines table number
} InnerTable;

// a xuckoo hash table is just two inner tables for storing inserted keys
struct xuckoo_table {
	InnerTable *table1;
	InnerTable *table2;
	int time;
};

// create a new bucket first referenced from 'first_address', based on 'depth'
// bits of its keys' hash values
static Bucket *new_bucket(int first_address, int depth) {
	Bucket *bucket = malloc(sizeof(*bucket));
	assert(bucket != NULL);

	bucket->id = first_address;
	bucket->depth = depth;
	bucket->full = false;

	return bucket;
}

// set up the internals of a xuckoo hash table
static void initialise_each_table(InnerTable *table) {
	table->size = 1;
	table->buckets = malloc(table->size * sizeof(*(table->buckets)));
	assert(table->buckets != NULL);

	table->buckets[0] = new_bucket(0, 0);
	table->depth = 0;
	table->nkeys = 0;
	table->nbuckets = 1;
}

// initialise whole xuckoo hash table
static void initialise_table(XuckooHashTable *table) {
	initialise_each_table(table->table1);
	table->table1->tablenum = TABLE1;

	initialise_each_table(table->table2);
	table->table2->tablenum = TABLE2;

	table->time = 0;
}

// initialise a single-key extendible cuckoo hash table
XuckooHashTable *new_xuckoo_hash_table() {
	XuckooHashTable *table;

	table = malloc(sizeof(*table));
	assert(table != NULL);

	table->table1 = malloc(sizeof(*(table->table1)));
	assert(table->table1 != NULL);

	table->table2 = malloc(sizeof(*(table->table2)));
	assert(table->table2 != NULL);

	initialise_table(table);

	return table;
}

// free internals of xuckoo hash table
static void free_each_table(InnerTable *table) {
	assert(table != NULL);

	int i;

	// loop backwards through the array of pointers, freeing buckets only as we
	// reach their first reference
	// (if we loop through forwards, we wouldn't know which reference was last)
	for (i = table->size-1; i >= 0; i--) {
		if (table->buckets[i]->id == i) {
			free(table->buckets[i]);
		}
	}

	// free array of bucket pointers
	free(table->buckets);

	// free the table itself
	free(table);
}

// free all memory associated with 'table'
void free_xuckoo_hash_table(XuckooHashTable *table) {
	assert(table != NULL);

	// free internal tables
	free_each_table(table->table1);
	free_each_table(table->table2);

	free(table);
}


// helper function to lookup key in an inner table
// returns true if the key was found, false if not
static bool xuckoo_lookup_each_table(InnerTable *table, int64 key, int address) {
	if (table->buckets[address]->full) {
		if (table->buckets[address]->key == key) {
			return true;
		}
	}
	return false;
}

// lookup whether 'key' is inside 'table'
// returns true if found, false if not
bool xuckoo_hash_table_lookup(XuckooHashTable *table, int64 key) {
	assert(table != NULL);
	int start_time = clock(); // start timer 

	// calculate both addresses
	int address1 = rightmostnbits(table->table1->depth, h1(key));
	int address2 = rightmostnbits(table->table2->depth, h2(key));

	if (xuckoo_lookup_each_table(table->table1, key, address1) ||
		xuckoo_lookup_each_table(table->table2, key, address2)) {
		return true;
	}

	// add time elapsed to total CPU time before returning
	table->time += clock() - start_time;
	return false;
}

// double the table of bucket pointers, duplicating the bucket pointers in the
// first half into the new second half of the table	
// Code inspired from xtndbln.c, by Matt Farrigia, the legendary tutor
static void double_table(InnerTable *table) {
	int size = table->size * 2, i;

	// verify that size hasnt exceed maximum table size
	assert(size < MAX_TABLE_SIZE && "error: table has grown too large!");

	// creates more more space on the heap, this time for twice as many 
	// bucket pointers
	table->buckets = realloc(table->buckets, size * sizeof(*(table->buckets)));
	assert(table->buckets != NULL);

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
// use 'xuckoo_hash_table_insert()' instead for inserting new keys
// Code inspired from xtndbln.c, by Matt Farrigia, the legendary tutor
static void reinsert_key(InnerTable *table, int64 key, int address) {
	table->buckets[address]->key = key;
	table->buckets[address]->full = true;
}

// split the bucket in 'table' at address 'address', growing table if necessary
static void split_bucket(InnerTable *table, int address) {
	int prefix;

	// do we need to grow the table?
	if (table->buckets[address]->depth == table->depth) {
		double_table(table);
	}

	// create a new bucket
	Bucket *bucket = table->buckets[address];
	int depth = bucket->depth;
	int first_address = bucket->id;

	int new_depth = depth + 1;
	bucket->depth = new_depth;

	// new bucket's first address ill be a 1 but plus the old first address
	int new_first_address = 1 << depth | first_address;
	Bucket *newbucket = new_bucket(new_first_address, new_depth);
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

	// filter the key from the old bucket into its rightful place in the new 
	// table (which may be the old bucket, or may be the new bucket)

	// remove and reinsert the key
	int64 key = bucket->key;
	bucket->full = false;
	reinsert_key(table, key, address);
}

// helper function to swap two keys
static void key_swap(int64 *key1, int64 *key2) {
	int64 temp = *key1;
	*key1 = *key2;
	*key2 = temp;
}

// helper function to insert key, and do necessary updates
static void insert_key(InnerTable *table, int64 key, int address) {
	table->buckets[address]->key = key;
	table->buckets[address]->full = true;
	table->nkeys++;
}

// helper function to update address of table to insert into
static int update_table_hash_address(InnerTable *table, int64 key) {
	int hash;

	// checkes which table is being passed
	if (table->tablenum == TABLE1) {
		hash = h1(key);
	} else {
		hash = h2(key);
	}

	// returns address
	return rightmostnbits(table->depth, hash);
}

// insert 'key' into 'table', if it's not in there already
// returns true if insertion succeeds, false if it was already in there
bool xuckoo_hash_table_insert(XuckooHashTable *table, int64 key) {
	assert(table != NULL);
	int start_time = clock(); // start timer

	int address, count = 0;

	// is they key already in table?
	if (xuckoo_hash_table_lookup(table, key)) {
		return false;
	}

	// checks whether to insert into first table
	if (table->table1->nkeys < table->table2->nkeys || 
		table->table1->nkeys == table->table2->nkeys) {

		// main loop for zigzagging between both tables until a free
		// space is found, or a cycle occurs, which happens when
		// count == table->size * 2
		while (count < table->table1->size * 2) {

			// calculate first table address 
			address = update_table_hash_address(table->table1, key);

			// is this slot empty
			if (table->table1->buckets[address]->full == false) {
				insert_key(table->table1, key, address);

				// add time elapsed to total CPU time before returning
				table->time += clock() - start_time;
				return true;
			}

			// collision has occured, kick out key and
			// update current key
			key_swap(&table->table1->buckets[address]->key, &key);

			count++;

			// calculate second table address
			address = update_table_hash_address(table->table2, key);

			if (table->table2->buckets[address]->full == false) {
				insert_key(table->table2, key, address);

				// add time elapsed to total CPU time before returning
				table->time += clock() - start_time;
				return true;
			}

			key_swap(&table->table2->buckets[address]->key, &key);

			count++;
		}

		// updates address
		// splits bucket and rehashes values
		address = rightmostnbits(table->table1->depth, h1(key));
		split_bucket(table->table1, address);

		// add time elapsed to total CPU time before returning
		// return back to function to attempt to reinsert key again
		table->time += clock() - start_time;
		return xuckoo_hash_table_insert(table, key);

	// attempts to insert into second table first
	// same procudure as above
	} else if (table->table1->nkeys > table->table2->nkeys) {
		while (count < table->table2->size * 2) {
			address = update_table_hash_address(table->table2, key);

			if (table->table2->buckets[address]->full == false) {
				insert_key(table->table2, key, address);

				// add time elapsed to total CPU time before returning
				table->time += clock() - start_time;
				return true;
			}

			key_swap(&table->table2->buckets[address]->key, &key);

			count++;

			address = update_table_hash_address(table->table1, key);

			if (table->table1->buckets[address]->full == false) {
				insert_key(table->table1, key, address);
				
				// add time elapsed to total CPU time before returning
				table->time += clock() - start_time;
				return true;
			}

			key_swap(&table->table1->buckets[address]->key, &key);

			count++;
		}

		address = rightmostnbits(table->table2->depth, h2(key));
		split_bucket(table->table2, address);

		// add time elapsed to total CPU time before returning
		table->time += clock() - start_time;
		return xuckoo_hash_table_insert(table, key);
	}

	// will never reach here
	// but just incase if it does, then it was
	// impossible to insert key
	return false;
}


// print the contents of 'table' to stdout
void xuckoo_hash_table_print(XuckooHashTable *table) {
	assert(table != NULL);

	printf("--- table ---\n");

	// loop through the two tables, printing them
	InnerTable *innertables[2] = {table->table1, table->table2};
	int t;
	for (t = 0; t < 2; t++) {
		// print header
		printf("table %d\n", t+1);

		printf("  table:               buckets:\n");
		printf("  address | bucketid   bucketid [key]\n");
		
		// print table and buckets
		int i;
		for (i = 0; i < innertables[t]->size; i++) {
			// table entry
			printf("%9d | %-9d ", i, innertables[t]->buckets[i]->id);

			// if this is the first address at which a bucket occurs, print it
			if (innertables[t]->buckets[i]->id == i) {
				printf("%9d ", innertables[t]->buckets[i]->id);
				if (innertables[t]->buckets[i]->full) {
					printf("[%llu]", innertables[t]->buckets[i]->key);
				} else {
					printf("[ ]");
				}
			}

			// end the line
			printf("\n");
		}
	}
	printf("--- end table ---\n");
}


// print some statistics about 'table' to stdout
void xuckoo_hash_table_stats(XuckooHashTable *table) {
	assert(table != NULL);

	printf("--- table stats ---\n");

	// print out some table stats
	printf("Table 1 size: %d\nTable 2 size: %d\n",
			table->table1->size, table->table2->size);

	printf("Table 1 number of keys: %d\nTable 2 number of keys: %d\n",
	        table->table1->nkeys, table->table2->nkeys);

	printf("Table 1 number of buckets: %d\nTable 2 number of buckets: %d\n",
	        table->table1->nbuckets, table->table2->nbuckets);

	// table load factors
	printf("Table 1 load factor: %.3f%%\nTable 2 load factor: %.3f%%\n", 
		    table->table1->nkeys * 100.0 / table->table1->size,
		    table->table2->nkeys * 100.0 / table->table2->size);

	// also calculate CPU usage in seconds and print this
	float seconds = table->time * 1.0 / CLOCKS_PER_SEC;
	printf("    CPU time spent: %.6f sec\n", seconds);

	printf("--- end stats ---\n");
}
