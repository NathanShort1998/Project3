// Ref class function definitions
// Computer Science, MVNU

#include "Ref.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// GetNextToken - general routine for getting next token from a string
// Parameters
//    str - string to search. search is destructive, i.e., token is removed.
//    delimiters - string, a list of characters to use a delimiters between tokens
// Returns: string token (removed from str)

string GetNextToken(string& str, const string& delimiters = " ") {
  // Skip delimiters at beginning                                          
  string::size_type startPos = str.find_first_not_of(delimiters, 0);
  // Find position of delimiter at end of token                                           
  string::size_type endPos = str.find_first_of(delimiters, startPos);

  // Found a token, remove it from string, and return it                       
  string next = str.substr(startPos, endPos - startPos);
  string rest = str.substr(endPos - startPos + 1, string::npos);
  str = rest;
  return(next);
}

// Ref member functions

Ref::Ref() {book = 0; chap = 0; verse = 0;}  	// Default constructor

Ref::Ref(const string s) { // Parse constructor - receives a line "34:5:7 text"
    string rtext = s; // make local copy of string to avoid modifying parameter
    // parse the reference - notice, currently there is no error checking!
    // Get book number
    string strbook = GetNextToken(rtext,":");
    book = atoi(strbook.c_str());
    // Get the chapter number
    string strchap = GetNextToken(rtext,":");
    chap = atoi(strchap.c_str());
    // Get the verse number
    string strverse = GetNextToken(rtext," ");
    verse = atoi(strverse.c_str());
}

Ref::Ref(const int b, const int c, const int v) { 	// Construct Ref from three integers
	book = b;
	chap = c;
	verse = v;									
}

// Accessors
int Ref::getBook() {return book;}	 // Access book number
int Ref::getChap() {return chap;}	 // Access chapter number
int Ref::getVerse() {return verse;} // Access verse number

// TO DO: implement comparison functions
// REQUIRED: == comparison

/*
The '==' operator has a default for variables like ints or floats
but we needed to make one for Ref objects. This function declares 
how the == operator should compare two Ref objects. 
*/

bool Ref::operator==(const Ref r) { 
	//Checks if the verse we are looking at is the verse requested.
	return (book == r.book && chap == r.chap && verse == r.verse);
}

//This function will return true if the Ref object using the function is less than the Ref r
// OPTIONAL: define < and > comparisons
bool Ref::operator<(const Ref r) const { 
	if(book < r.book){
		return true;
	}	
	else {
		if((book == r.book)&&(chap < r.chap)){
			return true;
		}
		else{
			if((book == r.book) && (chap == r.chap) && (verse < r.verse)){
				return true;
			}
			else{
				return false;
			}
		}
	}
}

// TO DO: modify display function to show book name instead of book number
void Ref::display() { 	// Display Reference
	string name = "Unknown book for now";
	ifstream infile ("books.txt");	
	int bookNum = book;
	int count = 1;
	
	while((count <= book)&& (getline(infile,name))){
		count++;
	}
	
    cout << name << " chapter: " << getChap() <<" verse: " << getVerse();
}

void Ref::displayName() {
	string name = "Unknown book for now";
	ifstream infile ("books.txt");	
	int bookNum = book;
	int count = 1;
	
	while((count <= book)&& (getline(infile,name))){
		count++;
	}
    cout << name;
}