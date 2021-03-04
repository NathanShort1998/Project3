// Bible class function definitions
// Computer Science, MVNU

#include "Ref.h"
#include "Verse.h"
#include "Bible.h" 
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

Bible::Bible() { // Default constructor
	infile = "/home/class/csc3004/Bibles/web-complete";
	buildTextIndex(infile);
}

// Constructor – pass bible filename
Bible::Bible(const string s) { 
	infile = s;
	buildTextIndex(infile);
}

// REQUIRED: lookup finds a given verse in this Bible
const Verse Bible::lookup(Ref ref, LookupResult& status) { 
    // TODO: scan the file to retrieve the line with ref ...
	map<Ref, int>::iterator iter;
	iter = refs.find(ref);
	Verse blank;
	
    if (!instream) {
	cerr << "Error - can't open input file: " << infile << endl;
	return blank;  /* false, indicates error */
	}
	
	int positionInFile;
	string line;
	
	if (iter == refs.end()) {
		//status = OTHER;
		//return blank;
	
		int newB = ref.getBook();
		int newC = ref.getChap();
		Ref verseCheckRef (newB,newC,1);
		
		lookup(verseCheckRef,status);
		
		if (status == SUCCESS){
			cout << "Status: No Verse" << endl << endl ;
			status = NO_VERSE;
			return blank;
		}
		else {
			cout<< "Status: No Chapter" << endl << endl;
			status = NO_CHAPTER;
			return blank;
		}
		
		
	} 
	else {
		instream.open(infile,ios::in);
		positionInFile = refs[ref];
		instream.seekg(positionInFile);
		getline(instream,line);
		Verse foundVerse(line);
		instream.close();
		status = SUCCESS;
		return foundVerse;
	}
    /*
		
	int requestedBook = ref.getBook();
	int requestedChap = ref.getChap();
	int requestedVerse = ref.getVerse();
	
	string finalString = "";
	
    string buffer, verseText;
    int book, chap, verse;

    // read in every verse 
    do {
        // get the next verse 
        getline(instream, buffer);
		
		//cout<< buffer << endl;  
		
		if(instream.fail()==true){
			status = OTHER;
			Verse verse;
			return verse;
		}
		
		Ref ref2 (buffer);
		book = ref2.getBook();
		
        // See if it is the right book, chapter, and verse
        if (ref == ref2) {
					
			/* create and return the verse object 
			Verse theVerse(buffer);
			status = SUCCESS;
			return (theVerse);			
        }
		
		//Add else statements for if the chapter or verse do not exist.
		
		//If the verse does not exist:
		
		else if ((ref2.getBook() == requestedBook)&&(requestedChap < ref2.getChap())){
			status = NO_VERSE;
			#ifdef DEBUG
				cout<< endl << endl << "Issue: no verse. Moving to next chapter." << endl <<endl;
			#endif
			cout << endl;
			Verse v;
			return (v);
		}
		
		
		//If the chapter does not exist:
		
		else if (requestedBook < ref2.getBook()){
			status = NO_CHAPTER;
			cout<< endl << endl << "Issue: no chapter. Moving to next book." << endl;
			cout << endl;
			Verse v;
			return (v);
		}
		
		
    } while (requestedBook >= book && !instream.fail());
	
    // update the status variable
	status = NO_BOOK; // placeholder until retrieval is attempted
	Verse v;
    return(v);
	*/
}

// REQUIRED: Return the reference after the given ref
const Ref next(const Ref ref, LookupResult& status) {
	/*use lookup function, and based on that status, adjust.
	string buffer;
	getline(instream, buffer);
	
	if(status == NO_VERSE){
		status == SUCCESS;
	}
	
	else if(status == NO_CHAPTER){
		
	}
	return next;*/	
};

// OPTIONAL: Return the reference before the given ref
const Ref prev(const Ref ref, LookupResult& status) {
	/*
	int prevVerse = ref.getVerse()--;
	int sameBook = ref.getBook();
	int sameChap = ref.getChap();
	
	Ref prev(sameBook,sameChap,prevVerse);
	return prev;
	*/
};

// Return an error message string to describe status
const string Bible::error(LookupResult status) {
	cout << "Error finding Verse. Status: " << status << "/n";
};

void Bible::display() {
	cout << endl << "Bible file: " << infile << endl << endl;
}

int Bible::buildTextIndex (string filename) {
  ifstream  instream;     /* input file descriptor */
  int tryPosition;
  int position;         /* location of line in the file */
  string text, line, word;

  /* open text file */
  instream.open(filename.c_str(), ios::in);
  if (!instream) {
	cerr << "Error - can't open input file: " << filename << endl;
	return 0;  /* false, indicates error */
  }

  /* process text file */
  while (!instream.fail()) {
    /* Get the file position at beginning of line */
    tryPosition = instream.tellg();
    /* get the next line */
    getline(instream,line);
	if(instream.fail()){
		break;
	}
	position = tryPosition;
	Ref newRef(line); //Cretaed a new Ref object for the line before we analize it.
	refs[newRef] = position;
  } // end while loop for lines of file
  cout << endl << endl << "Refs: " << refs.size() << " Offset: " << position << endl;
  instream.close();
  return 1;  /* true, indicates success */
}

string getNextWord(string& line) {
  string word="";
  int pos;

  if (line.length() > 1)
	{
	  pos = line.find_first_of(".,; :?!""''()");
	  /* get next word */
	  if (pos != 0) {
		word = line.substr(0,pos);
        }
	  /* trim the line */
	  if (pos == string::npos) {
		pos = line.length()-1;
	  }
	  line = line.substr(pos+1, 2000);
	}
  return word;
}