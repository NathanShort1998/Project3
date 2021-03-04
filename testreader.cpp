// biblereader.cpp
// main function for Project 1

#include "Ref.h"
#include "Verse.h"
#include "Bible.h"
#include <iostream>
#include <fstream>
#include <string> 
#include <stdio.h>
#include <stdlib.h>
using namespace std;

main (int argc, char **argv) {
	// Create Bible object to process the raw text file
	Bible webBible("/home/class/csc3004/Bibles/web-complete");
		
	Verse verse;
	int b, c, v, r;
	LookupResult result;
	//cout << "Using Bible from: ";
	webBible.display();
	// Prompt for input: get reference to lookup
	// This is good for testing your classes quickly for the first milestone.
	// TODO: your final program should get input from command line arguments instead.
	//cout << "Enter 3 integers for book, chapter, and verse to find: " << flush;

	/*if (argc != 2){
		cerr << "Usage: " << argv[0] << "Enter bible book number (1-66)" << endl ; 
		exit(1);
	}*/

	/*if(arc == 1){
		cout << "Usage: enter three numbers indicating book, chapter, and verse to look up.";
	}*/
	
	if(argc == 4){
		b = atoi(argv[1]);
		c = atoi(argv[2]);
		v = atoi(argv[3]);
		r = 1;
	}
	
	else if(argc == 5){
		b = atoi(argv[1]);
		c = atoi(argv[2]);
		v = atoi(argv[3]);
		r = atoi(argv[4]);
	}
	
	if (b < 1 || b > 66){
		cout << "This book does not exist." << endl;
	}
	for(int x = 0; x < r; x++){
		Ref ref(b, c, v);
		
		//cout << webBible.refs[ref];
		// Create a reference from the numbers
		
		// Use the Bible object to retrieve the verse by reference
		cout << "Looking up reference: ";
		ref.display();
		cout << endl;

		verse = webBible.lookup(ref, result);

		if(result == NO_VERSE){
			if( x == 0){
					cout << "Result status: No Verse" << result << endl;
					break;
				}
			c++;
			v = 1;
			result = OTHER;
			Ref newRef (b, c, v);
			
			cout<< "Looking up reference: ";
			newRef.display();
			cout<< endl;
			
			verse = webBible.lookup(newRef, result);
		}
		
		
		else if(result == NO_CHAPTER){
			if( x==0){
				cout << "Result status: No Chapter." << endl;
				break;
			}
			b++;
			c = 1;
			v = 1;
			result = OTHER;
			Ref newRef (b, c, v);
			verse = webBible.lookup(ref, result);
		}
		
		v++;
		verse.display();
		cout << endl;
	}
}