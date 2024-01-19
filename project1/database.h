/*****************************************************************
//
//  NAME:        Christian Dela Cruz
//
//  HOMEWORK:    Project 1
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        October 27, 2023
//
//  FILE:        database.h
//
//  DESCRIPTION:
//   Database for a bank that is able to create & add, find, delete, 
//   print bank records; able to write and read bank records to & 
//   from a file, and free memory. 
//
****************************************************************/

#include "record.h"

/*****************************************************************
//
//  Function name: addRecord
//
//  DESCRIPTION:   Adds a new bank record.
//
//  Parameters:    struct record** : address of the records in 
//                                   the HEAP that is being
//                                   held in start.
//                  int accountNum : the account number that
//                                   corresponds to the 
//                                   record.
//                 char[] uaddress: address of banker
//                 char[] uname: name of banker
//
//  Return values:  0 : successfully added bank record.
//                 -1 : did not successfully add bank record.
//
****************************************************************/

int addRecord (struct record ** start, int accountNum, char uaddress[ ],char uname[ ]);

/*****************************************************************
//
//  Function name: printAllRecords
//
//  DESCRIPTION:   Prints all existing records.
//
//  Parameters:    struct record** : address of the beginning
//                                  of the linkedlist.
//
//  Return values:  No Return Values.
//
****************************************************************/

void printAllRecords(struct record * file);

/*****************************************************************
//
//  Function name: findRecord
//
//  DESCRIPTION:   Finds an existing record in the bank's
//                 database.
//
//  Parameters:    struct record* : address of the beginning
//                                  of the linkedlist.
//                 int accountNum : the account number that
//                                   corresponds to the 
//                                   record.
//
//  Return values:  0 : successfully found record and prints
//                      it out.
//                 -1 : did not find record.
//
****************************************************************/

int findRecord (struct record * start, int accountNum);

/*****************************************************************
//
//  Function name: deleteRecord
//
//  DESCRIPTION:   Removes an existing record from the bank's 
//                 database.
//
///  Parameters:    struct record** : address of the records in 
//                                   the HEAP that is being
//                                   held in start.
//                  int accountNum : the account number that
//                                   corresponds to the 
//                                   record.
//
//  Return values:  0 : successfully found record and deletes it.
//                 -1 : does not delete the record.
//
****************************************************************/

int deleteRecord(struct record ** start, int accountNum);

/*****************************************************************
//
//  Function name: writeFile
//
//  DESCRIPTION:   Writes all bank records from the linkedlist
//                 into the file, and saves the file with the 
//                 bank records.
//
//  Parameters:    struct record* : address of the beginning
//                                  of the linkedlist.
//                 filename : the file name containing the
//                            bank records. 
//
//  Return values:  0 : successfully opened and wrote to 
//                      the file.
//                 -1 : did not open the file and did not
//                      write to the file.
//
****************************************************************/

int writeFile(struct record * file, char filename[]);

/*****************************************************************
// 
//  Function name: readFile
//
//  DESCRIPTION:   Reads the bank records from the file.
//
//  Parameters:    struct record** : address of the records in 
//                                   the HEAP that is being
//                                   held in start.
//                 filename : the file name containing the
//                            bank records. 
//
//  Return values:  0 : successfully read the file and added
//                      to the linkedlist. 
//                 -1 : file could not be opened, did not 
//                      successfully read the file, and 
//                      did not add to linkedlist.
//
****************************************************************/

int readFile(struct record ** start, char filename[]);

/*****************************************************************
// 
//  Function name: cleanUp
//
//  DESCRIPTION:   frees the allocated space on the HEAP
//                 and sets the start of the linkedlist 
//                 to NULL.
//
//  Parameters:    struct record** : address of the records in 
//                                   the HEAP that is being
//                                   held in start.
//  Return values:  0 : successful.
//
****************************************************************/

void cleanUp(struct record ** start);

