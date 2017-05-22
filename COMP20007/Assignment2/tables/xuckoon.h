/* * * * * * * * *
 * Dynamic hash table using multi-key cuckoo extendible hashing to resolve collisions by
 * incrementally growing the hash table
 *
 * created for COMP20007 Design of Algorithms - Assignment 2, 2017
 * by Armaan Dhaliwal-Mcleod 837674
 */

#ifndef XUCKOON_H
#define XUCKOON_H

#include <stdbool.h>
#include "../inthash.h"

typedef struct xuckoo_table XuckoonHashTable;

// initialise an extendible xuckoon hash table
XuckoonHashTable *new_xuckoon_hash_table(int bucketsize);

// free all memory associated with 'table'
void free_xuckoon_hash_table(XuckoonHashTable *table);

// insert 'key' into 'table', if it's not in there already
// returns true if insertion succeeds, false if it was already in there
bool xuckoon_hash_table_insert(XuckoonHashTable *table, int64 key);

// lookup whether 'key' is inside 'table'
// returns true if found, false if not
bool xuckoon_hash_table_lookup(XuckoonHashTable *table, int64 key);

// print the contents of 'table' to stdout
void xuckoon_hash_table_print(XuckoonHashTable *table);

// print some statistics about 'table' to stdout
void xuckoon_hash_table_stats(XuckoonHashTable *table);

#endif