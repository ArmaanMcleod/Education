
static void initialise_table(CuckooHashTable *table, int size) {
	
	assert(size < MAX_TABLE_SIZE && "error: table has grown too large!");
	
	table->slots = malloc((sizeof *table->slots) * size);
	assert(table->slots);
	table->inuse = malloc((sizeof *table->inuse) * size);
	assert(table->inuse);
}

// initialise a cuckoo hash table with 'size' slots in each table
CuckooHashTable *new_cuckoo_hash_table(int size) {

	assert(size < MAX_TABLE_SIZE && "error: table has grown too large!");
	CuckooHashTable *newtable = malloc(sizeof(newtable));
	assert(newtable);
	initialise_table(newtable, size);
	
    return newtable;
}
