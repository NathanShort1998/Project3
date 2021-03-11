# Project 3
# Simple build for the AjaxDemoclientserver to lookup Shakespeare

USER= natshort

# Use GNU C++ compiler with C++11 standard
CC= g++
CFLAGS= -g -std=c++11

#all:	indexdemo sslookupclient sslookupserver  PutCGI PutHTML testclient
all: testreader REFlookupserver REFclient PutInCGI PutInHTML

testreader: Ref.o Verse.o Bible.o testreader.o
	$(CC) $(CFLAGS) -o testreader Ref.o Verse.o Bible.o testreader.o

textindex.o:	textindex.cpp textindex.h english_stem.h narrow_wide_string.h string_util.h utilities.h meta.h stemming.h	
		g++ -c textindex.cpp

indexdemo.o:    indexdemo.cpp textindex.h
		g++ -c indexdemo.cpp 

indexdemo:	textindex.o indexdemo.o
		g++ -o indexdemo indexdemo.o textindex.o

testclient.o: 	testclient.cpp fifo.h
		g++ -c testclient.cpp

testclient:	testclient.o fifo.o
		g++ -o 	testclient testclient.o fifo.o
		
fifo.o:	fifo.cpp fifo.h
		$(CC) $(CFLAGS) -c fifo.cpp
		
testreader.o: testreader.cpp Bible.o Ref.o Verse.o 
		$(CC) $(CFLAGS) -c testreader.cpp 

sslookupclient.o: 	sslookupclient.cpp fifo.h
		g++ -c sslookupclient.cpp

sslookupclient:	sslookupclient.o fifo.o
		g++ -o 	sslookupclient sslookupclient.o fifo.o -L/usr/local/lib -lcgicc

sslookupserver: sslookupserver.o textindex.o fifo.o
		g++ -o sslookupserver sslookupserver.o textindex.o fifo.o	
		
sslookupserver.o:	sslookupserver.cpp fifo.h textindex.h
		g++ -c sslookupserver.cpp
		
REFlookupserver: REFlookupserver.o  fifo.o Ref.o Bible.o Verse.o
		$(CC) $(CFLAGS) -o REFlookupserver REFlookupserver.o fifo.o Ref.o Bible.o Verse.o
		
REFlookupserver.o: REFlookupserver.cpp fifo.h
		$(CC) $(CFLAGS) -c REFlookupserver.cpp
		
REFclient.o: REFclient.cpp fifo.h
		$(CC) $(CFLAGS) -c REFclient.cpp

REFclient:	REFclient.o fifo.o
		$(CC) $(CFLAGS) -o 	REFclient REFclient.o fifo.o -L/usr/local/lib -lcgicc
	
# Ref Object
Ref.o : Ref.h Ref.cpp
	$(CC) $(CFLAGS) -c Ref.cpp

# Verse Object
Verse.o : Ref.h Verse.h Verse.cpp
	$(CC) $(CFLAGS) -c Verse.cpp

# Bible Object
Bible.o : Ref.h Verse.h Bible.h Bible.cpp
	$(CC) $(CFLAGS) -c Bible.cpp

PutInCGI: REFclient
	chmod 757 REFclient
	cp REFclient /var/www/html/class/csc3004/$(USER)/cgi-bin
	
	echo "Current contents of the cgi-bin directory: "
	ls -l /var/www/html/class/csc3004/$(USER)/cgi-bin

PutInHTML: REFclient.html
	cp REFclient.html /var/www/html/class/csc3004/$(USER)
	cp layout.css /var/www/html/class/csc3004/$(USER)
	
	echo "Current contents of your HTML directory: "
	ls -l  /var/www/html/class/csc3004/$(USER)
		
PutCGI: sslookupclient
		chmod 757 sslookupclient
		cp sslookupclient /var/www/html/class/csc3004/$(USER)/cgi-bin
		echo "Current contents of your cgi-bin directory: "
		ls -l /var/www/html/class/csc3004/$(USER)/cgi-bin/

PutHTML: sslookup.html
		cp sslookup.html  /var/www/html/class/csc3004/$(USER)
		cp layout.css /var/www/html/class/csc3004/$(USER)
		echo "Current contents of your HTML directory: "
		ls -l  /var/www/html/class/csc3004/$(USER)
		
clean:
	rm *.o *# *~ sslookupclient sslookupserver testclient indexdemo


