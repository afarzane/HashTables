// Implement HashTable methods.
#include "HashTable.h"
using namespace std;

bool HashTable::insert(string key, int value) {
	// Try to insert key,value pair at pval, increment by probe function.
	int hval = hash(key);
	int pval = hval;

	for (int iter=0; iter<tsize; iter++) {
		if (sentinels[pval] != curr_used) {
			// Found an empty spot, insert the (key,value) pair here.
			sentinels[pval] = curr_used;
			keys[pval] = key;
			values[pval] = value;
			nstored++;
			return true;
		}
		pval = probeFunction(hval,iter);
	}
	return false;
}


bool HashTable::remove(string key, int value) {
	int hval = hash(key);
	int pval = hval;

	for (int iter = 0; iter < tsize; iter++) {
		if (sentinels[pval] == curr_used && values[pval] == value) {
			sentinels[pval] = prev_used;
			keys[pval] = " ";
			values[pval] = 0;
			nstored--;
			return true;
		}
		pval = probeFunction(hval, iter);
	}

	return false;
}


bool HashTable::lookup(string key, int& value) {
	
	int hval = hash(key);
	int pval = hval;

	for (int iter = 0; iter < tsize; iter++) {
		if (sentinels[pval] == curr_used && values[pval] == value) {
			return true;
		}
		pval = probeFunction(hval, iter);
	}

	return false;
}


bool HashTable::modify(string key, int value) {
	int hval = hash(key);
	int pval = hval;

	for (int iter = 0; iter < tsize; iter++) {
		if (sentinels[pval] == curr_used && keys[pval] == key) {
			values[pval] = value;
			return true;
		}
		pval = probeFunction(hval, iter);
	}

	return false;
}


void HashTable::getKeys(string*& all_keys, int& nkeys) {
	// Allocate an array to hold all the keys in the table.
	all_keys = new string[nstored];
	nkeys = nstored;


	// Walk the table's array.
	int key_i=0;
	for (int i=0; i<tsize; i++) {
		if (sentinels[i]==curr_used) {
			// Debug check: there shouldn't be more sentinels at curr_used than nstored thinks.
			if (key_i > nkeys) {
				cerr << "Error: more keys in table than nstored reports." << endl;
			}

			all_keys[key_i] = keys[i];
			key_i++;
		}
	}
}

int HashTable::numStored() {
	return nstored;
}


int HashTable::hash(string key) {
	return smarterHash(key);
}


int HashTable::probeFunction(int val, int iter) {
	// Linear probing.
	return (val + iter) % tsize;
}


int HashTable::sillyHash(string key) {
	return tsize/2;
}

int HashTable::smarterHash(string key) {
	// TO DO:: Write this.
	return 0;
}


HashTable::HashTable() {
	init(default_size);
}


HashTable::HashTable(int nkeys) {
	init(4*nkeys);
}


void HashTable::init(int tsizei) {
	tsize = tsizei;
	nstored = 0;

	keys = new string[tsize];
	values = new int[tsize];
	sentinels = new int[tsize];

	// Initialize all sentinels to 0.
	for (int i=0; i<tsize; i++)
		sentinels[i]=0;
}



HashTable::~HashTable() {
	delete[] keys;
	delete[] values;
	delete[] sentinels;
}


void HashTable::printTable() {
	// Print the current state of the hashtable.
	// Note, prints actual data structure contents, entry might not be "in" the table if sentinel not curr_used.
	// left, setw() are part of <iomanip>

	// Find longest string.
	const int indw = 5;
	int long_string = 3; // Length of "Key", nice magic number.
	const int intw = 10;
	const int sentw = 8;
	for (int i=0; i<tsize; i++) {
		if (keys[i].length() > long_string)
			long_string = keys[i].length();
	}

	// Print title
	cout << setw(indw) << left << "Index" << " | " << setw(long_string) << left << "Key" << " | " << setw(intw) << "Value" << " | " << "Sentinel" << endl;

	// Print a separator.
	for (int i=0; i < indw+long_string+intw+sentw+9; i++) {
		cout << "-";
	}
	cout << endl;

	// Print each table row.
	for (int i=0; i<tsize; i++) {
		cout << setw(indw) << left << i << " | " << setw(long_string) << left << keys[i] << " | " << setw(intw) << values[i] << " | " << sentinels[i] << endl;
	}

	// Print a separator.
	for (int i=0; i < indw+long_string+intw+sentw+9; i++) {
		cout << "-";
	}
	cout << endl;

}
