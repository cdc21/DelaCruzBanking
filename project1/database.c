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
//  FILE:        database.c
//
//  DESCRIPTION:
//   Database for a bank that is able to create & add, find, delete, 
//   print bank records; able to write and read bank records to & 
//   from a file, and free memory. 
//
****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"

extern int debug;

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

int addRecord (struct record ** start, int accountNum, char uaddress[ ],char uname[ ])
{
    struct record* current;
    struct record* newRecord;
    struct record* prev;
    int boolean;

    if(debug == 1)
    {
        printf("\n========== This is the addRecord function ==========\n");
        printf("Parameters:\nstruct record:%p\nint: %d\naddress[]:%s\nname[]: %s\n", (void *) *start, accountNum, uaddress, uname);
        printf("====================================================\n"); 
    }

    boolean = 0;
    current = *start;
    prev = NULL;

    while (current != NULL && accountNum < current->accountno) 
    {
        prev = current;
        current = current->next;
    }

    if (current != NULL && current->accountno == accountNum) 
    {
        boolean = -1;
    } 

    if (boolean != -1)
    {
        newRecord = (struct record*)malloc(sizeof(struct record));
        newRecord->accountno = accountNum;
        strcpy(newRecord->name, uname);
        strcpy(newRecord->address, uaddress);
        newRecord->next = NULL;

        if (prev == NULL) 
        {
            newRecord->next = *start;
            *start = newRecord;
        } 
        else 
        {
            newRecord->next = prev->next;
            prev->next = newRecord;
        }
    }

    return boolean; 
}

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

void printAllRecords(struct record* info)
{
    struct record* current = info;

    if(debug == 1)
    {
        printf("\n========== This is the printAllRecords function ==========\n");
        printf("Parameters:\nstruct record:%p\n", (void *) info);
        printf("==========================================================\n");
    }

    while (current != NULL) {
        printf("\nAccount Number: %d\n", current->accountno);
        printf("Name: %s\n", current->name);
        printf("Address: %s\n", current->address); 
        printf("\n");       
        
        current = current->next;
    }

    if(info == NULL)
    {
        printf("\nNO RECORDS TO BE PRINTED\n");
    }

}

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

int findRecord (struct record * start, int accountNum)
{
    int boolean = -1;

    struct record* current = start;

    if(debug == 1)
    {
        printf("\n========== This is the findRecord function ==========\n");
        printf("Parameters:\nstruct record:%p\nint: %d\n", (void*) start, accountNum);
        printf("=====================================================\n");
    }

    while (current != NULL && boolean == -1) 
    {
        if (current->accountno == accountNum) 
        {
            printf("\nAccount Number: %d\n", current->accountno);
            printf("Name: %s\n", current->name);
            printf("Address: %s\n", current->address); 
            printf("\n");  

            boolean = 0;
        }

        current = current->next;
    }

    return boolean;
}

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

int deleteRecord(struct record ** start, int accountNum)
{
    int boolean = 1;

    struct record* current = *start;
    struct record* prev = NULL;


    if(debug == 1)
    {
        printf("\n========== This is the deleteRecord function ==========\n");
        printf("Parameters:\nstruct record:%p\nint: %d\n", (void*) *start, accountNum);
        printf("=======================================================\n");
    }


    if (*start == NULL) {
        boolean = -1; ; 
    }

    while (current != NULL && boolean == 1) {
        if (current->accountno == accountNum) 
        {
            if (prev == NULL) 
            {
                *start = current->next;
            } 
            else 
            {
                prev->next = current->next;
            }

            free(current);
            boolean = 0;
        }
        else
        {
            prev = current;
            current = current->next;
        }
    }

    return boolean; 
}

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

int writeFile(struct record * file, char filename[])
{
    int boolean = 0;
    FILE *outfile = fopen(filename, "w");

    if(debug == 1)
    {
        printf("\n========== This is the writeFile function ==========\n");
        printf("Parameters:\nstruct record*: %p\nchar[] filename: %s\n", (void*) file, filename);
        printf("====================================================\n");
    }

    if(outfile == NULL)
    {
        boolean = -1;
    }

    if(boolean != -1)
    {
        while(file != NULL)  
        {
            fprintf(outfile, "%d\n", file->accountno);
            fprintf(outfile, "%s\n", file->name);
            fprintf(outfile, "%s$\n", file->address);

            file = file->next;    
        }

    }

    fclose(outfile);
    
    return boolean;
}

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

int readFile(struct record ** start, char filename[])
{
    int boolean = 0;
    int accountno;
    int length;
    int index = 0;
    int readSuccessful = 1;
    int addressLoop = 1;
    int counter;

    char character;

    char name[30];
    char address[50];

    FILE* infile = fopen(filename, "r");


    if(debug == 1)
    {
        printf("\n========== This is the readFile function ==========\n");
        printf("Parameters:\nstruct record*: %p\nchar[] filename: %s\n", (void *) *start, filename);
        printf("===================================================\n");
    }

    if(infile == NULL)
    {
        boolean = -1;
    }

    if( boolean != -1 )
    {
        while (readSuccessful)
        {
            counter = fscanf(infile, "%d", &accountno);

            if(counter != 1 || counter == EOF)
            {
                readSuccessful = 0;
            }
            else
            {
                fgetc(infile);
                fgets(name, 30, infile);
                length = strlen(name);

                if(name[length - 1] == '\n' )
                {
                    name[length - 1] = '\0';
                }
            }

            index = 0;
            character = ' ';
            addressLoop = 1;

            while(addressLoop && readSuccessful)
            {
                if (fscanf(infile, "%c", &character) != 1) 
                {
                    readSuccessful = 0;
                    addressLoop = 0;
                }

                address[index] = character;
                index++;

                if(character == '$')
                {
                     address[index-1] = '\0';

                     addressLoop = 0;
                }
            }

            if(readSuccessful)
            {
                addRecord(start, accountno, address, name);
            }
        }

        fclose(infile);

    }

    return boolean;
} 

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

void cleanUp(struct record ** start) 
{
    struct record *current = *start;
    struct record *next;

   if(debug == 1)
    {
        printf("\n========== This is the cleanup function ==========\n");
        printf("Parameters:\nstruct record**: %p\n", (void *) *start);
        printf("===================================================\n");
    }

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    *start = NULL;
}


