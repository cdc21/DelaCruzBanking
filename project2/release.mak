#Christian Dela Cruz - Project 2 \
This is a Release Makefile for user_interface.cpp \
and llist.cpp. 

project: user_interface.o llist.o
	g++ -o project user_interface.o llist.o

user_interface.o: user_interface.cpp
	g++ -ansi -pedantic-errors -Wall -c user_interface.cpp

llist.o: llist.cpp llist.h record.h
	g++ -ansi -pedantic-errors -Wall -c llist.cpp



