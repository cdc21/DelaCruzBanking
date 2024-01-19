/*****************************************************************
//
//  NAME:        Christian Dela Cruz
//
//  HOMEWORK:    3b
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        September 22,2023
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

struct record
{
    int                accountno;
    char               name[30];
    char               address[50];
    struct record*     next;
};
