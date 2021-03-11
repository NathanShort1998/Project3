/* sslookupclient.cpp
 * Shakespeare full-text search client:
 * receives an Ajax request from web client
 * extracts search string, and sends request to sslookupserver
 */
#include <iostream>
#include <fstream>
#include <string>

// Stuff for Ajax
#include "/home/class/csc3004/cgicc/Cgicc.h"
#include "/home/class/csc3004/cgicc/HTTPHTMLHeader.h"
#include "/home/class/csc3004/cgicc/HTMLClasses.h"
using namespace cgicc;

//Stuff for pipes                                                               
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include "fifo.h"
using namespace std;

#include "textindex.h"

#define logging // enable log file
#define LogFile "/tmp/natshort-REFlookupclient.log"
#include "logfile.h"

// Pipes for communication                                                      
string receive_pipe = "REFreply";
string send_pipe = "REFrequest";

string convertInt(int number)
{
  stringstream ss;//create a stringstream
  ss << number;//add number to the stream
  return ss.str();//return a string with the contents of the stream
}

int main(int argc, char **argv) { 
  #ifdef logging
	logFile.open(LogFile, ios::out); 
  #endif 
 
  Cgicc cgi; // used to access CGI request data
  
  form_iterator sstring = cgi.getElement("string");
  string searchString = **sstring;
  
  form_iterator st = cgi.getElement("search_type");
  form_iterator book = cgi.getElement("book");
  form_iterator chapter = cgi.getElement("chapter");
  form_iterator verse = cgi.getElement("verse");
  //form_iterator nv = cgi.getElement("num_verse");
  //We'll use this for multi-verse search
  
  /*
  int b, c, v, r;
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
  */
  
  //Establish the pipes
  Fifo recfifo(receive_pipe);
  Fifo sendfifo(send_pipe);

  //open the pipe to send data
  log("1");
  sendfifo.openwrite();
  log("Open Request Pipe");
  
  // create reference string
  int bookNum = book->getIntegerValue();
  int chapterNum = chapter->getIntegerValue();
  int verseNum = verse->getIntegerValue();
  
  string referenceToFind = "";
  referenceToFind += convertInt(bookNum);
  referenceToFind += ":";
  referenceToFind += convertInt(chapterNum);
  referenceToFind += ":";
  referenceToFind += convertInt(verseNum);
  
  // Call server to get results  
  string x = "Before";
  log(x+referenceToFind);
  
  sendfifo.send(referenceToFind);
  
  x="After";
  log(x+referenceToFind);

  //Open access to the read pipe
  recfifo.openread();
  log("Open Reply pipe");

  // output the response to the web page
  string results = "";
  int times = 0; // Counter for header lines
  while (results != "$end") {
    results = recfifo.recv();
    log("Reply: "+results);
    if (results != "$end") {
      cout << results << endl;
      if (times++ > 2) {
	cout << "<br>";
      }
    }
  }
  cout << endl; // flush output when done
  recfifo.fifoclose();
  log("close reply fifo");
  sendfifo.fifoclose();
  log("close request fifo");
  return 0;
}
