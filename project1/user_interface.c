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
//  FILE:        user_interface.c
//
//  DESCRIPTION:
//   Takes user input from the banker to let them choose 
//   to add a bank record, find a bank record, delete a
//   bank record, print all bank records, and quit the program.
//
****************************************************************/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "database.h"

int debug = 0;

void getaddress(char [], int);
int addRecord (struct record **, int, char [],char []);
void printAllRecords(struct record *);
int findRecord (struct record *, int);
int deleteRecord(struct record **, int);
int writeFile(struct record *, char[]);
int readFile(struct record**, char[]);
void cleanUp(struct record**);
int tolower(int c);

/*****************************************************************
//
//  Function name: main
//
//  DESCRIPTION:   Prints menu options for the banker and allows
//                 them to choose from which one, then takes
//                 account number and name, and calls function
//                 from database.c based on selected user input.
//
//  Parameters:    argc (int) : The number of elements in argv
//                 argv (char*[]) : An array of arguments passed
//                                  to the program.
//
//  Return values:  0 : success
//
****************************************************************/

int main(int argc, char* argv[])
{
    struct record* start = NULL;
    
    char add[] = "add";
    char printall[] = "printall";
    char find[] = "find";
    char delete[] = "delete";
    char quit[] = "quit";

    char name[30];
    char address[50]; 
    char user[100];
    char input[100];

    int accountNumber;
    int i;
    int scanner;
    int clear;
    int index;
    int boolean = 1;
    int menu = 1;
    int lowerCase = 0;

    if(argv[1] != NULL)
    {
        if(argc == 2 && strcmp(argv[1], "debug") == 0)
        {
            debug = 1;
        }
        else if(argc > 2 || strcmp(argv[1], "debug") != 0)
        {
            printf("ERROR: INCORRECT COMMAND LINE ARGUMENTS\n");
            boolean = 0;
        }    
    }

    readFile(&start, "records");

    while(boolean)
    {
        if (menu == 1) 
        {
            printf("\n*******************************************\n");
            printf("  Welcome to Bank of Dela Cruz Financial\n");
            printf("*******************************************\n");
            printf("MENU:\n");
            printf("-------------------------------------------------\n");
            printf("Add: Adds a new bank record.\n");
            printf("Printall: Prints all existing bank records.\n");
            printf("Find: Finds existing bank record.\n");
            printf("Delete: Deletes one existing bank record.\n");
            printf("Quit: Quits the program.\n");
            printf("-------------------------------------------------\n\n");
            printf("Please choose a menu option to continue: ");
        }

        scanf("%s", user);

        while (user[lowerCase]) 
        {
            user[lowerCase] = tolower(user[lowerCase]);
            lowerCase++;
        }

        i = 0;
        index = 0;
        lowerCase = 0;

        while(i < strlen(user))
        {
            if (strstr("add printall find delete quit", user) != NULL) {
                if(strncmp(user, add, i + 1) == 0 && strlen(user) <= 3)
                {
                    printf("\n*******************************************\n");
                    printf("              Add: Option Selected              \n");
                    printf("*******************************************\n\n");
                    printf("Please enter your account number: ");

                    scanner = scanf("%d" , &accountNumber);

                    while(scanner == 0 || accountNumber <= 0)
                    { 
                        if(scanner != 1)
                        { 
                            printf("ERROR: enter an integer for your account number: "); 
                        }
                        else if(accountNumber <= 0)
                        {
                            printf("ERROR: enter a positive account number: ");
                        }

                        fgets(input, 100, stdin);
                        scanner = scanf("%d", &accountNumber);
                    } 
            
                    while((clear = fgetc(stdin)) != '\n')
                    { 
  
                    }

                    printf("Please enter your name: ");

                    fgets(name, 30, stdin);
               
                    while(index >= 0)
                    {
                        if (index >= 30) 
                        {
                            printf("\nName is too long. Please enter a shorter name.\n");

                            while ((clear = fgetc(stdin)) != '\n') 
                            {
 
                            }

                            index = 0;

                            fgets(name, 30, stdin);

                        }

                        if(name[index] != '\n')
                        {
                            index++;
                        }
                        else
                        {
                            name[index] = '\0';
                            index = -1;
                        }
                    }

                    getaddress(address, 50);

                    if(addRecord(&start, accountNumber, address, name) == -1)
                    {
                        printf("\n=========== ACCOUNT NUMBER ALREADY EXISTS! ==========\n");
                        printf("=                                                   =\n");
                        printf("=                 RECORD NOT ADDED                  =\n");
                        printf("=                                                   =\n");
                        printf("=====================================================\n");

                    }
                    else
                    {
                        printf("\n==================================================\n");
                        printf("=           RECORD SUCCESSFULLY ADDED            =\n");
                        printf("==================================================\n");
                    }


                    fgets(input, 100, stdin);
                    i = strlen(user);
                    menu = 1;
                } 
                else if(strncmp(user, printall, i + 1) == 0 && strlen(user) <= 8)
                {
                    printf("\n*******************************************\n");
                    printf("           Print All: Option Selected           \n");
                    printf("*******************************************\n");
  
                    printAllRecords(start);

                    i = strlen(user);
                    menu = 1;
                }
                else if(strncmp(user, find, i + 1) == 0 && strlen(user) <= 4)
                {
                    printf("\n*******************************************\n");
                    printf("             Find: Option Selected             \n");
                    printf("*******************************************\n\n");
                    printf("Please enter your account number: ");
 
                    scanner = scanf("%d" , &accountNumber);

                    while(scanner == 0 || accountNumber <= 0)
                    {
                        if(scanner != 1)
                        {
                            printf("ERROR: enter an integer for your account number: ");
                        }
                        else if(accountNumber <= 0)
                        {
                            printf("ERROR: enter a positive account number: ");
                        }

                        fgets(input, 100, stdin);
                        scanner = scanf("%d", &accountNumber);
                    }
                
                    while((clear = fgetc(stdin)) != '\n')
                    {

                    }

                    if(findRecord(start, accountNumber))
                    {
                        printf("\n========== ACCOUNT NUMBER DOES NOT EXIST! ==========\n");
                        printf("=                                                  =\n");
                        printf("=               COULDN'T FIND RECORD               =\n");
                        printf("=                                                  =\n");
                        printf("====================================================\n");
                    }
  
                    i = strlen(user);
                    menu = 1;
                }
                else if(strncmp(user, delete, i + 1) == 0 && strlen(user) <= 6)
                {
                    printf("\n*******************************************\n");
                    printf("            Delete: Option Selected            \n");
                    printf("*******************************************\n\n");
                    printf("Please enter your account number: ");

                    scanner = scanf("%d" , &accountNumber);
  
                    while(scanner != 1 || accountNumber <= 0)
                    { 
                        if(scanner != 1)
                        {
                            printf("ERROR: enter an integer for your account number: ");
                        }
                        else if(accountNumber <= 0)
                        {
                            printf("ERROR: enter a positive account number: ");
                        }

                        fgets(input, 100, stdin);
                        scanner = scanf("%d", &accountNumber);
                    }
                
                    while((clear = fgetc(stdin)) != '\n')
                    {

                    }
                
                    if(deleteRecord(&start, accountNumber))
                    {
                        printf("\n========== ACCOUNT NUMBER DOES NOT EXIST! ==========\n");
                        printf("=                                                  =\n");
                        printf("=               RECORD NOT DELETED                =\n");
                        printf("=                                                  =\n");
                        printf("====================================================\n");

                    }
                    else
                    {
                        printf("\n====================================================\n");
                        printf("=           RECORD SUCCESSFULLY DELETED            =\n");
                        printf("====================================================\n");
                    }

                    i = strlen(user);
                    menu = 1;
                }
                else if(strncmp(user, quit, i + 1) == 0 && strlen(user) <= 4)
                {
                    if(writeFile(start, "records"))
                    {
                        printf("Records Could Not Be Saved.");
                    }

                    boolean = 0; 

                    if(boolean == 0 && i == 0)
                    {
                        printf("\n###########################################\n");
                        printf("     Thank You for Banking with Us!        \n");
                        printf("      Have a Great Day and Goodbye!          \n");
                        printf("###########################################\n\n");
                    }
                }
                else
                {
                    printf("\nINVALID CHOICE.\n");
                    printf("---------------------------------------\n");
                    printf("add: Adds a new bank record.\n");
                    printf("printall: Prints all existing bank records.\n");
                    printf("find: Finds exisitng bank record.\n");
                    printf("delete: Deletes one existing bank record.\n");
                    printf("quit: Quits the program\n");
                    printf("----------------------------------------\n\n");
                    printf("PLEASE SELECT A VALID OPTION: ");

                    menu = 0;

                    i = strlen(user);
                }
            }
            else
            {
                printf("\nINVALID CHOICE.\n");
                printf("---------------------------------------\n");
                printf("add: Adds a new bank record.\n");
                printf("printall: Prints all existing bank records.\n");
                printf("find: Finds exisitng bank record.\n");
                printf("delete: Deletes one existing bank record.\n");
                printf("quit: Quits the program\n");
                printf("----------------------------------------\n\n");
                printf("PLEASE SELECT A VALID OPTION: ");

                menu = 0;

                i = strlen(user);
            }

            i++;

        }

    }

    cleanUp(&start);

    return boolean;
}

/*****************************************************************
//
//  Function name: getaddress
//
//  DESCRIPTION:   Asks banker to input address name using
//                 any format with delimiter '$'.
//
//  Parameters:    char address[] : single char array 
//                                  that holds the bankers
//                                  address
//                 int size : the size of the address array
//
//  Return values:  No Return Value.
//
****************************************************************/

void getaddress(char address[], int size)
{
    char character;
    int loop = 1;
    int index = 0;

    if(debug == 1)
    {
        printf("\n\n========== This is the getaddress function ==========\n");
        printf("Paramters:\nchar address[]: %s\nint size: %d\n", address, size);
        printf("=======================================================\n");
    }

    printf("Please enter your address below and type '$' when finished:\n");

    while(loop)
    {
        if (index >= size) 
        {
            printf("\n+-------------------------------------------------------------+\n");
            printf("+    Address is too long. Please enter a shorter address.     +\n");
            printf("+ Please enter your address below and type '$' when finished: +\n");
            printf("+-------------------------------------------------------------+\n");

            while ((character = fgetc(stdin)) != '\n') 
            {

            }

            index = 0;

        }

        character = fgetc(stdin);
        address[index] = character;
        index++;

       if(character == '$')
       {
            address[index-1]='\0';
            loop = 0;
       }
    }
}



