/* * * * * * * * *
 * Dynamic hash table using multi-key cuckoo extendible hashing with multiple keys per bucket,
 * resolving collisions by incrementally growing the hash table
 *
 * created for COMP20007 Design of Algorithms - Assignment 2, 2017
 * by Armaan Dhaliwal-McLeod
 */

// necessary libraries for this module
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "xuckoon.h"

// macro to calculate the rightmost n bits of a number x
#define rightmostnbits(n, x) (x) & ((1 << (n)) - 1)

// some helpeful table flags
#define TABLE1 1
#define TABLE2 2

// a bucket stores an array of keys
// it also knows how many bits are shared between possible keys, and the first 
// table address that references it
typedef struct {
	int id;			// a unique id for this bucket, equal to the first address
					// in the table which points to it
	int depth;		// how many hash value bits are being used by this bucket
	int nkeys;		// number of keys currently contained in this bucket
	int64 *keys;	// the keys stored in this bucket
} Bucket;

// a hash table is an array of slots pointing to buckets holding up to 
// bucketsize keys, along with some information about the number of hash value 
// bits to use for addressing
typedef struct {
	Bucket **buckets;	// array of pointers to buckets
	int size;			// how many entries in the table of pointers (2^depth)
	int depth;			// how many bits of the hash value to use (log2(size))
	int bucketsize;  	// maximum number of keys per bucket
	int nkeys;          // number of keys being stored in table
	int nbuckets;       // how many buckets are being stored in table
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
static Bucket *new_bucket(int first_address, int depth, int bucketsize) {
	Bucket *bucket = malloc(sizeof(*bucket));
	assert(bucket != NULL);

	bucket->id = first_address;
	bucket->nkeys = 0;
	bucket->depth = depth;

	bucket->keys = malloc(bucketsize * sizeof(*(bucket->keys)));
	assert(bucket->keys);

	return bucket;
}

// set up the internals of a xuckoon hash table
static void initialise_each_table(InnerTable *table, int bucketsize) {
	table->bucketsize = bucketsize;
	table->size = 1;

	table->buckets = malloc(table->size * sizeof(*(table->buckets)));
	assert(table->buckets != NULL);

	table->buckets[0] = new_bucket(0, 0, bucketsize);
	table->depth = 0;
	table->nkeys = 0;
	table->nbuckets = 1;
}

// initialise whole xuckoon hash table
static void initialise_table(XuckoonHashTable *table, int bucketsize) {
	initialise_each_table(table->table1, bucketsize);
	table->table1->tablenum = TABLE1;

	initialise_each_table(table->table2, bucketsize);
	table->table2->tablenum = TABLE2;

	table->time = 0;
}

// initialise a multi-key extendible cuckoo hash table
XuckoonHashTable *new_xuckoon_hash_table(int bucketsize) {
	XuckoonHashTable *table = malloc(sizeof(*table));
	assert(table != NULL);

	table->table1 = malloc(sizeof(*(table->table1)));
	assert(table->table1 != NULL);

	table->table2 = malloc(sizeof(*(table->table2)));
	assert(table->table2 != NULL);

	initialise_table(table, bucketsize);

	return table;
}

// free internals of xuckoon hash table	
static void free_each_table(InnerTable *table) {
	assert(table != NULL);

	int i;

	// loop backwards through the array of pointers, freeing buckets only as we
	// reach their first reference
	// (if we loop through forwards, we wouldn't know which reference was last)
	for (i = table->size-1; i >= 0; i--) {
		if (table->buckets[i]->id == i) {

			// free bucket keys
			free(table->buckets[i]->keys);

			// free bucket
			free(table->buckets[i]);
		}
	}

	// free array of bucket pointers
	free(table->buckets);

	// free table itself
	free(table);
}

// free all memory associated with 'table'
void free_xuckoon_hash_table(XuckoonHashTable *table) {
	assert(table != NULL);

	// free internals of xuckoon table
	free_each_table(table->table1);
	free_each_table(table->table2);

	free(table);
}

// helper function to lookup key in an inner table
// returns true if the key was found, false if not
bool xuckoon_lookup_each_table(InnerTable *table, int64 key, int address) {
	assert(table != NULL);

	int i;

	for (i = 0; i < table->buckets[address]->nkeys; i++) {
		if (table->buckets[address]->keys[i] == key) {
			return true;
		}
	}

	return false;
}

// lookup whether 'key' is inside 'table'
// returns true if found, false if not
bool xuckoon_hash_table_lookup(XuckoonHashTable *table, int64 key) {
	assert(table != NULL);
	int start_time = clock(); // start timer

	// calculate both addresses
	int address1 = rightmostnbits(table->table1->depth, h1(key));
	int address2 = rightmostnbits(table->table2->depth, h2(key));

	if (xuckoon_lookup_each_table(table->table1, key, address1) ||
		xuckoon_lookup_each_table(table->table2, key, address2)) {
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
	table->buckets = realloc(table->buckets, (sizeof *table->buckets) * size);
	assert(table->buckets != NULL);

	// copy the pointers over safely
	for (i = 0; i < table->size; i ++) {
		table->buckets[table->size + i] = table->buckets[i];
	}

	// update the table size
	table->size = size;
	table->depth++;
}

// reinsert a key into the hash table after splitting a bucket --- we can assume
// that there will definitely be space for this key because it was already
// inside the hash table previously
// use 'xuckoon_hash_table_insert()' instead for inserting new keys
static void reinsert_keys(InnerTable *table, int64 *keys, int nkeys) {
	int i, address;

	for (i = 0; i < nkeys; i++) {

		// checks which table it being passed
		if (table->tablenum == TABLE1) {
			address = rightmostnbits(table->depth, h1(keys[i]));
		} else {
			address = rightmostnbits(table->depth, h2(keys[i]));
		}

		// is their enough space?
		if (table->buckets[address]->nkeys < table->bucketsize) {
			table->buckets[address]->keys[table->buckets[address]->nkeys] = keys[i];
			table->buckets[address]->nkeys++;
		}
	}
}


static void split_bucket(InnerTable *table, int address) {
	int i, prefix;

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

	bucket->nkeys = 0;

	// safely copy over bucket pointers
	for (i = 0; i < numkeys; i++) {
		keys[i] = bucket->keys[i];
	}

	// remove and reinsert the keys
	reinsert_keys(table, keys, numkeys);

	// done with array
	free(keys);
}

// helper function to swap two keys
static void key_swap(int64 *key1, int64 *key2) {
	int64 temp = *key1;
	*key1 = *key2;
	*key2 = temp;
}

// helper function to insert key, and do necessary updates
static void insert_key(InnerTable *table, int64 key, int address) {
	int key_index = table->buckets[address]->nkeys;
	table->buckets[address]->keys[key_index] = key;
	table->buckets[address]->nkeys++;
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
bool xuckoon_hash_table_insert(XuckoonHashTable *table, int64 key) {
	assert(table != NULL);
	int start_time = clock(); // start timer

	int count = 0, address, rand_index;

	srand(time(NULL)); // set random seeds

	// is they key already in table?
	if (xuckoon_hash_table_lookup(table, key)) {
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
			if (table->table1->buckets[address]->nkeys < table->table1->bucketsize) {
				insert_key(table->table1, key, address);

				// add time elapsed to total CPU time before returning
				table->time += clock() - start_time;
				return true;
			}

			// obtain legal random index from key array
			rand_index = rand() % table->table1->buckets[address]->nkeys;

			// collision has occured, kick out key and
			// update current key
			key_swap(&table->table1->buckets[address]->keys[rand_index], &key);

			count++;

			// calculate second table address
			address = update_table_hash_address(table->table2, key);

			if (table->table2->buckets[address]->nkeys < table->table2->bucketsize) {
				insert_key(table->table2, key, address);

				// add time elapsed to total CPU time before returning
				table->time += clock() - start_time;
				return true;
			}

			rand_index = rand() % table->table2->buckets[address]->nkeys;
			key_swap(&table->table2->buckets[address]->keys[rand_index], &key);

			count++;

		}

		// updates address
		// splits bucket and rehashes values
		address = rightmostnbits(table->table1->depth, h1(key));
		split_bucket(table->table1, address);

		// add time elapsed to total CPU time before returning
		// return back to function to attempt to reinsert key again
		table->time += clock() - start_time;
		return xuckoon_hash_table_insert(table, key);

	// attempts to insert into second table first
	// same procudure as above, except different order of tables
	} else if (table->table1->nkeys > table->table2->nkeys) {
		while (count < table->table2->size * 2) {
			address = update_table_hash_address(table->table2, key);

			if (table->table2->buckets[address]->nkeys < table->table2->bucketsize) {
				insert_key(table->table2, key, address);

				// add time elapsed to total CPU time before returning
				table->time += clock() - start_time;
				return true;
			}

			rand_index = rand() % table->table2->buckets[address]->nkeys;
			key_swap(&table->table2->buckets[address]->keys[rand_index], &key);

			count++;

			address = update_table_hash_address(table->table1, key);

			if (table->table1->buckets[address]->nkeys < table->table1->bucketsize) {
				insert_key(table->table1, key, address);

				// add time elapsed to total CPU time before returning
				table->time += clock() - start_time;
				return true;
			}

			rand_index = rand() % table->table1->buckets[address]->nkeys;
			key_swap(&table->table1->buckets[address]->keys[rand_index], &key);

			count++;
		}

		address = rightmostnbits(table->table2->depth, h2(key));
		split_bucket(table->table2, address);

		// add time elapsed to total CPU time before returning
		table->time += clock() - start_time;
		return xuckoon_hash_table_insert(table, key);
	}

	// will never reach here
	// but just incase if it does, then it was
	// impossible to insert key
	return false;
}

// print the contents of 'table' to stdout
void xuckoon_hash_table_print(XuckoonHashTable *table)  {
	assert(table != NULL);

	int tbl, bucket, key;

	printf("--- table ---\n");

	// loop through the two tables, printing them
	InnerTable *innertables[2] = {table->table1, table->table2};
	for (tbl = 0; tbl < 2; tbl++) {
		printf("table %d\n", tbl+1);

		printf("  table:               buckets:\n");
		printf("  address | bucketid   bucketid [key]\n");

		// print table and buckets
		for (bucket = 0; bucket < innertables[tbl]->size; bucket++) {
			// table entry
			printf("%9d | %-9d ", bucket, innertables[tbl]->buckets[bucket]->id);

			// if this is the first address at which a bucket occurs, print it
			if (innertables[tbl]->buckets[bucket]->id == bucket) {
				printf("%9d ", innertables[tbl]->buckets[bucket]->id);

				// print the bucket's contents
				printf("[");
				for (key = 0; key < innertables[tbl]->bucketsize; key++) {
					if (key < innertables[tbl]->buckets[bucket]->nkeys) {  
						printf(" %llu", innertables[tbl]->buckets[bucket]->keys[key]);
					} else {
						printf(" -");
					}
				}
				printf("]");
			}
			printf("\n");
		}
	}
	printf("--- end table ---\n");
}

// print some statistics about 'table' to stdout
void xuckoon_hash_table_stats(XuckoonHashTable *table) {
	assert(table != NULL);

	printf("--- table stats ---\n");

	// print out some stats of table
	printf("Table 1 size: %d\nTable 2 size: %d\n",
			table->table1->size, table->table2->size);

	printf("Table 1 number of keys: %d\nTable 2 number of keys: %d\n",
	        table->table1->nkeys, table->table2->nkeys);

	printf("Table 1 number of buckets: %d\nTable 2 number of buckets: %d\n",
	        table->table1->nbuckets, table->table2->nbuckets);

	// load factors
	printf("Table 1 load factor: %.3f%%\nTable 2 load factor: %.3f%%\n", 
		    table->table1->nkeys * 100.0 / table->table1->size,
		    table->table2->nkeys * 100.0 / table->table2->size);

	// also calculate CPU usage in seconds and print this
	float seconds = table->time * 1.0 / CLOCKS_PER_SEC;
	printf("    CPU time spent: %.6f sec\n", seconds);

	printf("--- end stats ---\n");
}

