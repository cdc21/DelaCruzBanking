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
//  DATE:        November 21,2023
//
//  FILE:        record.h
//
//  DESCRIPTION:
//   Header file containing a structure for a bank database.
//
****************************************************************/

/*****************************************************************
//
//  Function name: record
//
//  DESCRIPTION:   Contains information such as name, account
//                 number, and address for a bank database.
//
//  Parameters:    No Parameters.
//
//  Return values:  No Return Values.
//
****************************************************************/

#ifndef RECORD_H
#define RECORD_H

struct record {
    int accountno;
    char name[30];
    char address[50];
    struct record* next;
};

#endif 

