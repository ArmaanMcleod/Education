static bool insert_first_second(XuckooHashTable *table, int64 key) {
	int hash, address, count = 0;
	int64 temp;

	while (count < table->table1->size * 2) {
		hash = h1(key);
		address = rightmostnbits(table->table1->depth, hash);

		if (table->table1->buckets[address]->full == false) {
			table->table1->buckets[address]->key = key;
			table->table1->buckets[address]->full = true;
			table->table1->nkeys++;
			return true;
		}

		temp = table->table1->buckets[address]->key;
		table->table1->buckets[address]->key = key;
		key = temp;

		count++;

		hash = h2(key);
		address = rightmostnbits(table->table2->depth, hash);

		if (table->table2->buckets[address]->full == false) {
			table->table2->buckets[address]->key = key;
			table->table2->buckets[address]->full = true;
			table->table2->nkeys++;
			return true;
		}

		temp = table->table2->buckets[address]->key;
		table->table2->buckets[address]->key = key;
		key = temp;

		count++;
	}

	address = rightmostnbits(table->table1->depth, h1(key));
	split_bucket(table->table1, address);

	return false;
}