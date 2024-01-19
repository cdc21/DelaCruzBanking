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
//  FILE:        llist.cpp
//
//  DESCRIPTION:
//   Database for a bank that is able to create & add, find, delete, 
//   print bank records; able to write and read bank records to & 
//   from a file, and free memory. 
//
****************************************************************/

#include "llist.h"
#include <fstream>
#include <cstring>
#include <limits>

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

llist::llist()
{
    #ifdef DEBUG_MODE
        std::cout << "\n---------- This is the default llist() constructor ----------\n"
                  << "Parameters:\nNO PARAMETERS\n"
                  << "-------------------------------------------------------------\n";
    #endif

    start = NULL;
    strcpy(filename, "records");
    readfile();
}

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

llist::llist(char file[])
{
    #ifdef DEBUG_MODE
        std::cout << "\n---------- This is the llist(char file[]) constructor ----------\n"
                  << "Parameters:\nchar[]: \n" << file
                  << "\n------------------------------------------------------------------\n";
    #endif

    start = NULL;
    strcpy(filename, file);
    readfile(); 
}

/*****************************************************************
//
//  Function name: ~llist()
//
//  DESCRIPTION:    Default deconstructor that writes the linked
//                  list to file with given filename and cleans
//                  up the memory in the HEAP.
//
//  Parameters:     NO PARAMETERS.
//
//  Return values:  No Return Value.
//
****************************************************************/

llist::~llist() 
{
    #ifdef DEBUG_MODE
        std::cout << "\n---------- This is the ~llist() deconstructor ----------\n"
                  << "Parameters:\nNO PARAMETERS\n"
                  << "\nstart: " << (void *) start << "\n"
                  << "--------------------------------------------------------\n";
    #endif

    writefile();
    cleanup(); 
}

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

llist::llist(const llist& other) 
{
    #ifdef DEBUG_MODE
        std::cout << "\n---------- This is the llist(const llist& other) copy constructor ----------\n"
                  << "Parameters:\nconst llist&: \n" << other
                  << "----------------------------------------------------------------------------\n";
    #endif

    start = NULL;

    filename[0] = '\0'; 

    strncpy(filename, other.filename, 19);
    filename[19] = '\0';

    record* currentOther = other.start;
    record* prevThis = NULL;

    while (currentOther != NULL) 
    {
        record* newRecord = new record;

        newRecord->accountno = currentOther->accountno;
        strncpy(newRecord->name, currentOther->name, 29); 

        newRecord->name[29] = '\0'; 
        strncpy(newRecord->address, currentOther->address, 49); 

        newRecord->address[49] = '\0'; 
        newRecord->next = NULL;

        if (prevThis == NULL) 
        {
            start = newRecord;
        } 
        else 
        {
            prevThis->next = newRecord;
        }

        prevThis = newRecord;
        currentOther = currentOther->next;
    }
}

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

llist& llist::operator=(const llist& other) 
{
    #ifdef DEBUG_MODE
        std::cout << "\n---------- This is the operator=(const llist& other) overload assignment operator ----------\n"
                  << "Parameters:\nconst llist&: \n" << other
                  << "----------------------------------------------------------------------------------------------\n";
    #endif

    if (this != &other) 
    {
        cleanup(); 

        strncpy(filename, other.filename, 19);
        filename[19] = '\0';

        record* currentOther = other.start;
        record* prevThis = NULL;

        while (currentOther != NULL) 
        {
            record* newRecord = new record;

            newRecord->accountno = currentOther->accountno;

            strncpy(newRecord->name, currentOther->name, 29);
            newRecord->name[29] = '\0'; 

            strncpy(newRecord->address, currentOther->address, 49); 
            newRecord->address[49] = '\0'; 

            newRecord->next = NULL;

            if (prevThis == NULL) 
            {
                start = newRecord;
            } 
            else 
            {
                prevThis->next = newRecord;
            }

                prevThis = newRecord;
                currentOther = currentOther->next;
            }
        }

        return *this;
    }

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

std::ostream& operator<<(std::ostream& os, const llist& list) 
{
    #ifdef DEBUG_MODE
        std::cout << "\n========== This is the operator<<(std::ostream& os, const llist& list) ==========\n"
                  << "                                  overloaded operator                                "
                  << "\n==================================================================================\n";
    #endif

    record* current = list.start;

    while (current != NULL) 
    {
        os << "\nAccount Number: " << current->accountno << "\n";
        os << "Name: " << current->name << "\n";
        os << "Address: " << current->address << "\n";
        current = current->next;
    }

    if (list.start == NULL) 
    {
        os << "\n~ NO RECORDS TO BE PRINTED ~\n";
    }

    return os;
}

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

int llist::addRecord(int accountNum, char uaddress[], char uname[]) 
{
    #ifdef DEBUG_MODE 
        std::cout << "\n========== This is the addRecord function ==========\n"
                  << "Parameters:\nint: " << accountNum
                  << "\naddress[]: " << uaddress
                  << "\nname[]: " << uname
                  << "\n---------------------------"
                  << "\nstart: " << (void *) start 
                  << "\n====================================================\n";
    #endif

    int boolean;

    record* current;
    record* prev;

    boolean = 0;
    current = start;
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

    if(boolean != -1)
    {
        record* newRecord = new record;
        newRecord->accountno = accountNum;
        strncpy(newRecord->name, uname, 29); 
        strncpy(newRecord->address, uaddress, 49); 
        newRecord->next = NULL;
    
        if (prev == NULL) 
        {
            newRecord->next = start;
            start = newRecord;
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
//  Parameters:    NO PARAMETERS
//
//  Return values:  No Return Values.
//
****************************************************************/

void llist::printAllRecords() 
{

    #ifdef DEBUG_MODE
        std::cout << "\n========== This is the printAllRecords function ==========\n"
                  << "Parameters:\nNO PARAMETERS\n"
                  << "---------------------------"
                  << "\nstart: " << (void *) start << "\n"
                  << "==========================================================\n";
    #endif

    record* current = start;

    while (current != NULL) 
    {
        std::cout << "\nAccount Number: " << current->accountno << "\n";
        std::cout << "Name: " << current->name << "\n";
        std::cout << "Address: " << current->address << "\n";

        current = current->next;
    }

    if (start == NULL) 
    {
        std::cout << "\nNO RECORDS TO BE PRINTED\n";
    }  
}

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

int llist::findRecord(int accountNum) 
{
    #ifdef DEBUG_MODE
        std::cout << "\n========== This is the findRecord function ==========\n"
                  << "Parameters:\nint:" << accountNum << "\n"
                  << "---------------------------"
                  << "\nstart: " << (void *) start << "\n"
                  << "=====================================================\n";
    #endif
    
    int found = -1;

    record* current = start;

    while (current != NULL) 
    {
        if (current->accountno == accountNum) 
        {
            std::cout << "\nAccount Number: " << current->accountno << "\n";
            std::cout << "Name: " << current->name << "\n";
            std::cout << "Address: " << current->address << "\n";

            found = 0; 
        }
        current = current->next;
    }

    return found;
}

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

int llist::deleteRecord(int accountNum) 
{
    #ifdef DEBUG_MODE
        std::cout << "\n========== This is the deleteRecord function ==========\n"
                  << "Parameters:\nint:" << accountNum << "\n"
                  << "---------------------------"
                  << "\nstart: " << (void *) start << "\n"
                  << "=======================================================\n";
    #endif

    int remove = -1;

    record* current = start;
    record* prev = NULL;

    if (start == NULL) 
    {
        remove = -1; 
    }
    else
    {
        while (current != NULL)
        {
            if (current->accountno == accountNum) 
            {
                if (prev == NULL) 
                {
                    start = current->next;
                } 
                else
                {
                    prev->next = current->next;
                }

                delete current;

                remove = 0;
            } 
            else 
            {
                prev = current;
                current = current->next;
            }
        }
    }

    return remove;
}

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

int llist::writefile() 
{
    #ifdef DEBUG_MODE
        std::cout << "\n========== This is the writeFile function ==========\n"
                  << "Parameters:\nNO PARAMETERS\n"
                  << "---------------------------"
                  << "\nstart: " << (void *) start << "\n"
                  << "=====================================================\n";
    #endif

    int file = 0;

    std::ofstream outfile(filename);

    if (!outfile.is_open()) 
    {
        file = -1; 
    }
    else
    {
        record* current = start;

        while (current != NULL) 
        {
            outfile << current->accountno << "\n";
            outfile << current->name << "\n";
            outfile << current->address << "$\n";
            current = current->next;
        }

        outfile.close();

    }

    return file; 
}

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

int llist::readfile() 
{
    #ifdef DEBUG_MODE
        std::cout << "\n========== This is the readFile function ==========\n"
                  << "Parameters:\nNO PARAMETERS\n"
                  << "---------------------------"
                  << "\nstart: " << (void *) start << "\n"
                  << "====================================================\n";
    #endif

    int file = 0;

    int accountno;
    char name[30];
    char address[50];

    std::ifstream infile(filename);

    if (!infile.is_open()) 
    {
        file = -1; 
    }
    else
    {
        while (infile >> accountno) 
        {
            infile.ignore(); 
            infile.getline(name, 30);
            infile.getline(address, 50, '$');

            addRecord(accountno, address, name);
        }

        infile.close();

    }

    return file; 
}

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

void llist::cleanup() 
{
    #ifdef DEBUG_MODE
        std::cout << "\n========== This is the cleanUp function ==========\n"
                  << "Parameters:\nNO PARAMETERS\n"
                  << "---------------------------"
                  << "\nstart: " << (void *) start << "\n"
                  << "==================================================\n";
    #endif

    record* current = start;
    record* next;

    while (current != NULL) 
    {
        next = current->next;
        delete current;
        current = next;
    }

    start = NULL; 
}

