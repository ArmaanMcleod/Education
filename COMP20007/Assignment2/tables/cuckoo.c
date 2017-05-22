/* * * * * * * * *
 * Dynamic hash table using cuckoo hashing, resolving collisions by switching
 * keys between two tables with two separate hash functions
 *
 * created for COMP20007 Design of Algorithms - Assignment 2, 2017
 * by Armaan Dhaliwal-McLeod
 * inspired from Matt Farrugia's linear.c implementation
 */

// necessary libraries for this module
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "cuckoo.h"

// an inner table represents one of the two internal tables for a cuckoo
// hash table. it stores two parallel arrays: 'slots' for storing keys and
// 'inuse' for marking which entries are occupied
typedef struct inner_table {
	int64 *slots;	// array of slots holding keys
	bool  *inuse;	// is this slot in use or not?
} InnerTable;

// a cuckoo hash table stores its keys in two inner tables
struct cuckoo_table {
	InnerTable *table1; // first table
	InnerTable *table2; // second table
	int size;			// size of each table
	int time;           // how much CPU time has been used for insert/lookup keys
	int load;           // number of keys in table now
};


// set up the internals of a cuckoo hash table struct with new
// arrays of size 'size'
static void initialise_each_table(InnerTable *table, int size) {
	int i;

	table->slots = malloc(size * sizeof(*(table->slots)));
	assert(table->slots);

	table->inuse = malloc(size * sizeof(*(table->inuse)));
	assert(table->inuse);

	for (i = 0; i < size; i++) {
		table->inuse[i] = false;
	}
}

// initialise whole cuckoo hash table
static void initialise_table(CuckooHashTable *table, int size) {
	assert(size < MAX_TABLE_SIZE && "error: table has grown too large!");

	initialise_each_table(table->table1, size);
	initialise_each_table(table->table2, size);

	table->time = 0;
	table->load = 0;

	table->size = size;
}

// initialise a cuckoo hash table with 'size' slots in each table
CuckooHashTable *new_cuckoo_hash_table(int size) {
	CuckooHashTable *table;

	table = malloc(sizeof(*table));
	assert(table != NULL);

	table->table1 = malloc(sizeof(*(table->table1)));
	assert(table->table1);

	table->table2 = malloc(sizeof(*(table->table2)));
	assert(table->table2);

	// set up the internals of the table struct with arrays of size 'size'
	initialise_table(table, size);

	return table;
}

// free internals of cuckoo hash table
static void free_each_table(InnerTable *table) {
	assert(table != NULL);

	// free the table arrays
	free(table->slots);
	free(table->inuse);

	free(table);
}


// free all memory associated with 'table'
void free_cuckoo_hash_table(CuckooHashTable *table) {
	assert(table != NULL);

	free_each_table(table->table1);
	free_each_table(table->table2);

	// free the table itself
	free(table);
}

// double the size of the internal table arrays and re-hash all
// keys in the old tables
static void double_table(CuckooHashTable *table) {

	// keep track of old values
	// not the nicest way to do this
	int64 *oldslots1 = table->table1->slots;
	int64 *oldslots2 = table->table2->slots;
	bool *oldinuse1 = table->table1->inuse;
	bool *oldinuse2 = table->table2->inuse;
	int oldsize = table->size, i;

	// double size of table
	initialise_table(table, table->size * 2);

	// rehash all pre-existing keys back into table
	for (i = 0; i < oldsize; i++) {
		if (oldinuse1[i] == true) {
			cuckoo_hash_table_insert(table, oldslots1[i]);
		}
		if (oldinuse2[i] == true) {
			cuckoo_hash_table_insert(table, oldslots2[i]);
		}
	}

	// free these pointers
	free(oldslots1);
	free(oldslots2);
	free(oldinuse1);
	free(oldinuse2);
}

// insert 'key' into 'table', if it's not in there already
// returns true if insertion succeeds, false if it was already in there
bool cuckoo_hash_table_insert(CuckooHashTable *table, int64 key) {
	assert(table != NULL);
	int start_time = clock(); // start timer

	int count = 0, h;
	int64 temp;

	// is the key already there?
	if (cuckoo_hash_table_lookup(table, key)) {
		return false;
	}

	// main loop for zigzagging between both tables until a free
	// space is found, or a cycle occurs, which happens when
	// count == table->size * 2
	while (count < table->size * 2) {

		// calculate first table address 
		h = h1(key) % table->size;

		// is this slot empty
		if (table->table1->inuse[h] == false) {

			// insert key
			table->table1->slots[h] = key;
			table->table1->inuse[h] = true;
			table->load++;

			// add time elapsed to total CPU time before returning
			table->time += clock() - start_time;
			return true;
		} 

		// collision has occured, kick out key and
		// update current key
		temp = table->table1->slots[h];
		table->table1->slots[h] = key;
		key = temp;

		count++;

		// calculate second table address
		// repeate process above
		h = h2(key) % table->size;

		if (table->table2->inuse[h] == false) {
			table->table2->slots[h] = key;
			table->table2->inuse[h] = true;
			table->load++;
			table->time += clock() - start_time;
			return true;
		}
		temp = table->table2->slots[h];
		table->table2->slots[h] = key;
		key = temp;

		count++;
	}

	// cycle has been found, time to double the table size
	// and rehash all the values in newly sized table
	double_table(table);

	// add time elapsed to total CPU time before returning
	table->time += clock() - start_time;
	return cuckoo_hash_table_insert(table, key);
}

// helper function to lookup key in an inner table
// returns true if the key was found, false if not
static bool cuckoo_lookup_each_table(InnerTable *table, int64 key, int hashfunc) {
	if (table->inuse[hashfunc] == true) {
		if (table->slots[hashfunc] == key) {
			return true;
		}
	}
	return false;
}

// lookup whether 'key' is inside 'table'
// returns true if found, false if not
bool cuckoo_hash_table_lookup(CuckooHashTable *table, int64 key) {
	assert(table != NULL);
	int start_time = clock(); // start timer

	// calculate both hash functions
	int hash_func_1 = h1(key) % table->size;
	int hash_func_2 = h2(key) % table->size;

	if (cuckoo_lookup_each_table(table->table1, key, hash_func_1) || 
		cuckoo_lookup_each_table(table->table2, key, hash_func_2)) {
		return true;
	}

	// add time elapsed to total CPU time before returning
	table->time += clock() - start_time;
	return false;
}


// print the contents of 'table' to stdout
void cuckoo_hash_table_print(CuckooHashTable *table) {
	assert(table);
	printf("--- table size: %d\n", table->size);

	// print header
	printf("                    table one         table two\n");
	printf("                  key | address     address | key\n");
	
	// print rows of each table
	int i;
	for (i = 0; i < table->size; i++) {

		// table 1 key
		if (table->table1->inuse[i]) {
			printf(" %20llu ", table->table1->slots[i]);
		} else {
			printf(" %20s ", "-");
		}

		// addresses
		printf("| %-9d %9d |", i, i);

		// table 2 key
		if (table->table2->inuse[i]) {
			printf(" %llu\n", table->table2->slots[i]);
		} else {
			printf(" %s\n",  "-");
		}
	}

	// done!
	printf("--- end table ---\n");
}


// print some statistics about 'table' to stdout
void cuckoo_hash_table_stats(CuckooHashTable *table) {
	assert(table != NULL);

	printf("--- table stats ---\n");

	// print out some table stats
	printf("Table size: %d\n", table->size);
	printf("Table load: %d\n", table->load);

	// table load factors
	printf("load factor: %.3f%%\n", table->load * 100.0 / table->size);

	// also calculate CPU usage in seconds and print this
	float seconds = table->time * 1.0 / CLOCKS_PER_SEC;
	printf("    CPU time spent: %.6f sec\n", seconds);

	printf("--- end stats ---\n");
}
