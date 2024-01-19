/*****************************************************************
//
//  NAME:        Christian Dela Cruz
//
//  HOMEWORK:    Project 2
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        November 21, 2023
//
//  FILE:        llist.h
//
//  DESCRIPTION:
//   Database for a bank that is able to create & add, find, delete, 
//   print bank records; able to write and read bank records to & 
//   from a file, and free memory. 
//
****************************************************************/

#ifndef LLIST_H
#define LLIST_H

#include "record.h"
#include <iostream>

class llist 
{
private:
    /*****************************************************************
    // 
    //  Variable name: start
    //
    //  DESCRIPTION:   Record pointer that points the the start
    //                 of the linked list. 
    //
    ****************************************************************/

    record* start;

    /*****************************************************************
    // 
    //  Function name: filename
    //
    //  DESCRIPTION:   char array that holds the name of the file
    //                 that all the records are being read and written.
    //
    ****************************************************************/

    char filename[20];

    /*****************************************************************
    // 
    //  Function name: readFile
    //
    //  DESCRIPTION:   Reads the bank records from the file.
    //
    //  Parameters:    NO PARAMETERS
    //
    //  Return values:  0 : successfully read the file and added
    //                      to the linkedlist. 
    //                 -1 : file could not be opened, did not 
    //                      successfully read the file, and 
    //                      did not add to linkedlist.
    //
    ****************************************************************/

    int readfile();

    /*****************************************************************
    //
    //  Function name: writeFile
    //
    //  DESCRIPTION:   Writes all bank records from the linkedlist
    //                 into the file, and saves the file with the 
    //                 bank records.
    //
    //  Parameters:    NO PARAMETERS 
    //
    //  Return values:  0 : successfully opened and wrote to 
    //                      the file.
    //                 -1 : did not open the file and did not
    //                      write to the file.
    //
    ****************************************************************/

    int writefile();

    /*****************************************************************
    // 
    //  Function name: cleanUp
    //
    //  DESCRIPTION:   frees the allocated space on the HEAP
    //                 and sets the start of the linkedlist 
    //                 to NULL.
    //
    //  Parameters:    NO PARAMETERS.
    //
    //  Return values:  No Return Value.
    //
    ****************************************************************/

    void cleanup();

public:
    /*****************************************************************
    //
    //  Function name: llist()
    //
    //  DESCRIPTION:    Default constructor that initializes 
    //                  record start* to null, initalizes the file
    //                  name, and reads a file to add any pre-
    //                  existing records.
    //
    //  Parameters:     NO PARAMETERS.
    //
    //  Return values:  No Return Value.
    //
    ****************************************************************/

    llist();

    /*****************************************************************
    //
    //  Function name: llist(char file[])
    //
    //  DESCRIPTION:    Overloaded constructor that initializes
    //                  record start* to null, initalizes the file
    //                  name with given fie, and reads a file to add 
    //                  any pre-existing records.
    //
    //  Parameters:     char file[] : file name. 
    //
    //  Return values:  No Return Value.
    //
    ****************************************************************/

    llist(char[]);

    /*****************************************************************
    //
    //  Function name: ~llist()
    //
    //  DESCRIPTION:    Default deconstructor that writes the linked
    //                  list to file with given filename and cleans
    /                  up the memory in the HEAP.
    //
    //  Parameters:     NO PARAMETERS.
    //
    //  Return values:  No Return Value.
    //
    ****************************************************************/

    ~llist();

    /*****************************************************************
    //
    //  Function name: llist::llist(const llist& other)
    //
    //  DESCRIPTION:    Copy constructor of the llist class that 
    //                  duplicates the content of another llist object.
    //
    //  Parameters:     const llist& : Reference to another llist object to copy.
    //
    //  Return values:  No Return Values.
    //
    ******************************************************************/

    llist(const llist& other);

    /*****************************************************************
    //
    //  Function name: llist& llist::operator=(const llist& other)
    //
    //  DESCRIPTION:    Overloaded assignment operator that assigns 
    //                  the content of another llist object to this 
    //                  llist object.
    //
    //  Parameters:     const llist& : Reference to another llist object to copy.
    //
    //  Return values:  Reference to the current llist object.
    //
    ******************************************************************/

    llist& operator=(const llist& other);

    /*****************************************************************
    //
    //  Function name: operator<<(std::ostream& os, const llist& list)
    //
    //  DESCRIPTION:    Overloaded stream insertion operator that 
    //                  allows printing llist object contents to the 
    //                  output stream.
    //
    //  Parameters:     std::ostream& : Reference to the output stream.
    //                  const llist&  : Reference to the llist object to print.
    //
    //  Return values:  Reference to the output stream.
    //
    ******************************************************************/

    friend std::ostream& operator<<(std::ostream& os, const llist& list);

    /*****************************************************************
    //
    //  Function name: addRecord
    //
    //  DESCRIPTION:   Adds a new bank record.
    //
    //  Parameters:    int accountNum : the account number that
    //                                  corresponds to the 
    //                                  record.
    //                 char[] uaddress: address of banker
    //                 char[] uname: name of banker
    //
    //  Return values:  0 : successfully added bank record.
    //                 -1 : did not successfully add bank record.
    //
    ****************************************************************/

    int addRecord(int, char[], char[]);

    /*****************************************************************
    //
    //  Function name: findRecord
    //
    //  DESCRIPTION:   Finds an existing record in the bank's
    //                 database.
    //
    //  Parameters:     int accountNum : the account number that
    //                                   corresponds to the 
    //                                   record.
    //
    //  Return values:  0 : successfully found record and prints
    //                      it out.
    //                 -1 : did not find record.
    //
    ****************************************************************/

    int findRecord(int);

    /*****************************************************************
    //
    //  Function name: printAllRecords
    //
    //  DESCRIPTION:   Prints all existing records.
    //
    //  Parameters:    NO PARAMETERS
    //
    //  Return values:  No Return Values.
    //
    ****************************************************************/

    void printAllRecords();

    /*****************************************************************
    //
    //  Function name: deleteRecord
    //
    //  DESCRIPTION:   Removes an existing record from the bank's 
    //                 database.
    //
    //  Parameters:     int accountNum : the account number that
    //                                   corresponds to the 
    //                                   record.
    //
    //  Return values:  0 : successfully found record and deletes it.
    //                 -1 : does not delete the record.
    //
    ****************************************************************/

    int deleteRecord(int);
};

#endif 
