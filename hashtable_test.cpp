//============================================================================
// Name        : hashtable_test.cpp
//============================================================================

// A driver program to perform basic tests of hashtable functionality.

#include "HashTable.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>

string int2letter(int i);




// This program takes command-line arguments
// The two arguments are:
//    test case to run, an integer
//    output filename (optional)
int main(int argc, char *argv[]) {

	// ostream for writing result.
	// Default to cout.
	// This code is to allow us to use either cout (an ostream) or an output file (ofstream)
	ostream *outputp = &cout;
	ofstream outputfile;

	// Parse command-line arguments.
	int tcase=0;
	if (argc < 2 || argc > 3) {
		// Print error message, need a test case number.
		cerr << "Error: incorrect number of arguments" << endl;
		cerr << "  Usage:" << endl;
		cerr << "    " << argv[0] << " case_no [outfilename]" << endl;

		return 1;
	} else {
		// Turn the argument into an integer.
		tcase = atoi(argv[1]);

		if (argc > 2) {
			// Open the filename specified for output.
			outputfile.open (argv[2]);
			outputp = &outputfile;
		}
	}
	// This is a reference, which seems strange.  However, one can't directly assign the *outputp to output because there is no copy constructor to use.
	ostream& output = *outputp;

	// cout << "Running case " << tcase << endl;
		

	/*
	  Test cases.
	  1: Insert a (key,value), get the (key,value).
	  2: Insert a (key,value), modify the (key, value), lookup the (key,value).
	  3: Insert a (key,value), delete (key,value), try to lookup the (key,value).
	  4: Insert a (key,value), insert (key,value2) to cause collision, delete (key,value), lookup the (key,value2).
	  5: Many entries.  Insert until table is 75% full.  lookup (last key, value)
	  6: Many entries, test reuse.  Insert 200% of table size, with deletions so table is never more than 50% full.  lookup (last key, value).
	 */

	// This will make a hashtable with 100 spaces.
	HashTable ht(25);
	string key = "a";
	int val = 0;

	// Select test case.
	switch (tcase) {
	case 1: {
		ht.insert(key,20);
		ht.lookup(key,val);

		output << val << endl;
		break;
	} case 2: 
		ht.insert(key,20);
		ht.modify(key,18);
		ht.lookup(key,val);

		output << val << endl;
		break;
	case 3: 
		ht.insert(key,20);
		ht.remove(key,20);

		output << ht.lookup(key,val) << endl;
		break;
	case 4: 
		ht.insert(key,20);
		ht.insert(key,18);
		ht.remove(key,20);
		ht.lookup(key,val);

		output << val << endl;
		break;
	case 5: 
		for (int i=30; i<105; i++) {
			ht.insert(int2letter(i),i);
		}

		key = "a";
		ht.insert(key,400);
		ht.lookup(key,val);

		output << val << endl;
		break;
	case 6: 
		// Insert 50 to get started
		for (int i=0; i<50; i++) {
			ht.insert(int2letter(i),i);
		}

		for (int j=0; j<6; j++) {
			// Remove 25
			for (int i=25*j; i < 25*j + 25; i++) {
				ht.remove(int2letter(i),i);
			}
			// Add another 25
			for (int i=25*(j+1) ; i < 25*(j+2); i++) {
				ht.insert(int2letter(i),i);
			}
		}



		key = "a";
		ht.insert(key,400);
		ht.lookup(key,val);

		output << val << endl;
		output << "Number of pairs stored in the table: " << ht.numStored() << endl;
		break;
	default:
		cerr << "Invalid test case number" << endl;
		return 2;
	}
	

	// Close up the output file, if we had one.
	if (argc > 2) {
		outputfile.close();
	}

	return 0;
}


// Take an integer and convert it into a letter in A-Z.
// Does ASCII of 65 + (i % 26).
string int2letter(int i) {
	char the_char = (char) (65 + i % 26);

	// Put it in a string to return.
	string rtn_string(1,the_char);
	return rtn_string;
}
