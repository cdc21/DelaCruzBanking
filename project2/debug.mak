#Christian Dela Cruz - Project 2 \
This is a DEBUG_MODE Makefile for user_interface.cpp \
and llist.cpp. 

project_debug: user_interface.o llist.o
	g++ -o project_debug user_interface.o llist.o

user_interface.o: user_interface.cpp
	g++ -ansi -pedantic-errors -Wall -DDEBUG_MODE -c user_interface.cpp

llist.o: llist.cpp llist.h record.h
	g++ -ansi -pedantic-errors -Wall -DDEBUG_MODE -c llist.cpp


