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
#include "fifo.h"
#include "textindex.h"

#define logging
#define LogFile "/tmp/natshort-REFlookupserver.log"
#include "logfile.h"
	  
using namespace std;

string receive_pipe = "REFrequest";
string send_pipe = "REFreply";

main (int argc, char **argv) {
	#ifdef logging
	logFile.open(LogFile, ios::out); 
	#endif
	// Create Bible object to process the raw text file
	Bible webBible("/home/class/csc3004/Bibles/web-complete");
	
	Fifo recfifo(receive_pipe);
	Fifo sendfifo(send_pipe);
	
	string messageBack;
		
	Verse verse;
	int b, c, v = 0;
	int r = 1;
	LookupResult result;
	
	recfifo.openread();
	log("Opened Request pipe");
	while(true){
		//webBible.display();
		// Prompt for input: get reference to lookup
		// This is good for testing your classes quickly for the first milestone.
		// TODO: your final program should get input from command line arguments instead.
		//cout << "Enter 3 integers for book, chapter, and verse to find: " << flush;
		
		string reference = recfifo.recv();
		Ref refToFind(reference);
		log("Reference string: "+reference);
		
		b = refToFind.getBook();
		c = refToFind.getChap();
		v = refToFind.getVerse();
		
		log("$Variable B: "+b);	
		log("$Variable C: "+c);
		log("$$Variable V: "+v);
		log(b+c+v);
		
		if (b < 1 || b > 66){
			result = NO_BOOK;
			messageBack = result + "$This book does not exist.";
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
					result = NO_VERSE;
					messageBack = result + "$Result status: No Verse ";
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
				messageBack = result + "$" + verse.getVerse();
			}
			
			
			else if(result == NO_CHAPTER){
				if( x==0){
					result = NO_CHAPTER;
					messageBack = result + "$Result status: No Chapter.";
					break;
				}
				b++;
				c = 1;
				v = 1;
				result = OTHER;
				Ref newRef (b, c, v);
				verse = webBible.lookup(ref, result);
				
				messageBack = result + "$" + verse.getVerse();
			}
			
			v++;
			verse.display();
			cout << endl;
			messageBack = result + "$" + verse.getVerse();
		}
		sendfifo.openwrite();
		log("Opened Reply pipe");
		log("..."+messageBack);
		sendfifo.send(messageBack);
		sendfifo.fifoclose();
		log("Closed Reply pipe");
	}
	//recfifo.fifoclose();
}