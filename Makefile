

all: myShell

myShell: myShell.o
	g++ -g  myShell.o -o myShell

myShell.o: myShell.cpp
	g++  -g -c myShell.cpp

clean: 
	rm -rf *o myShell
