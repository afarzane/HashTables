// A program to calculate word frequencies in a single document.
#include <iostream>
#include <fstream>
#include "HashTable.h"

using namespace std;

#define MAX_STRING_LEN 256
#define DICT_SIZE 20000

// This program takes command-line arguments.
// By convention, these parameters are called argc (argument count) and argv (argument vector).
// This program wants only a single argument, the filename of the document to be processed.
int main (int argc, char* argv[]) {

	// Local variables.
	ifstream inputfile;  // ifstream for reading from input file.
	HashTable dict(DICT_SIZE);  // Dictionary for storing words and their counts.

	// Parse command-line arguments.
	if (argc != 2) {
		// Note that the program name is the first argument, so argc==1 if there are no additional arguments.
		cerr << "Expected one argument." << endl;
		cerr << "  Usage: " << argv[0] << " input_filename" << endl;
		return 1;
	} else {
		// Open the filename specified for input.
		inputfile.open (argv[1]);
	}



	// Tokenize the input.
	// Read one character at a time.
	// If the character is not in a-z or A-Z, terminate current string.
	char c;
	char curr_str[MAX_STRING_LEN];
	int str_i = 0;  // Index into curr_str.
	bool flush_it = false;  // Whether we have a complete string to flush.
	
	while (inputfile.good()) {
		// Read one character, convert it to lowercase.
		inputfile.get(c);
		c = tolower(c);

		if (c >= 'a' && c <= 'z') {
			// c is a letter.
			curr_str[str_i] = c;
			str_i++;
			
			// Check over-length string.
			if (str_i >= MAX_STRING_LEN) {
				flush_it = true;
			}
		} else {
			// c is not a letter.
			// Create a new string if curr_str is non-empty.
			if (str_i>0) {
				flush_it = true;
			}
		}

		if (flush_it) {
			// Create the new string from curr_str.
			string the_str(curr_str,str_i);
			// cout << the_str << endl;


			// Handle the string, insert/increment count in dictionary.
			int count;
			if (dict.lookup(the_str,count)) {
				dict.modify(the_str,count+1);
			} else {
				dict.insert(the_str,1);
			}
			

			// Reset state variables.
			str_i = 0;
			flush_it = false;
		}
	}
	

	// Get the hash table as a vector, print it.
	string *keys;
	int nkeys;
	dict.getKeys(keys,nkeys);
	for (int i=0; i<nkeys; i++) {
		int count;
		// Lookup key in table, store value in count.
		if (!dict.lookup(keys[i],count)) {
			// Return with an error if not in table.
			cerr << "Key not in table" << endl;
			return 2;
		}
		cout << keys[i] << ": " << count << endl;
	}

	
	// Close input file.
	inputfile.close();
	return 0;
}
