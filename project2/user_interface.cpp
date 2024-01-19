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
//  DATE:        Novemeber 25, 2023
//
//  FILE:        user_interface.cpp
//
//  DESCRIPTION:
//   Takes user input from the banker to let them choose 
//   to add a bank record, find a bank record, delete a
//   bank record, print all bank records, and quit the program.
//
****************************************************************/

#include <iostream>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <string>
#include <limits>
#include "llist.h"

void getaddress(char [], int);
int system(const char *command);

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
    system("clear");

    llist start; 
    
    char add[] = "add";
    char printall[] = "printall";
    char find[] = "find";
    char del[] = "delete";
    char quit[] = "quit";

    char name[30];
    char address[50]; 
    char user[100];
    char input[100];

    int accountNumber;
    int index;
    int boolean = 1;
    int menu = 1;
    int lowerCase = 0;

    size_t userIndex;

    while (boolean)
    {
        if (menu == 1) 
        {
            std::cout << "\n*******************************************\n";
            std::cout << "  Welcome to Bank of Dela Cruz Financial\n";
            std::cout << "*******************************************\n";
            std::cout << "MENU:\n";
            std::cout << "-------------------------------------------------\n";
            std::cout << "Add: Adds a new bank record.\n";
            std::cout << "Printall: Prints all existing bank records.\n";
            std::cout << "Find: Finds existing bank record.\n";
            std::cout << "Delete: Deletes one existing bank record.\n";
            std::cout << "Quit: Quits the program.\n";
            std::cout << "-------------------------------------------------\n\n";
            std::cout << "Please choose a menu option to continue: ";
        }

        std::cin.getline(user, 100);

        while (user[lowerCase]) 
        {
            user[lowerCase] = std::tolower(user[lowerCase]);
            lowerCase++;
        }

        userIndex = 0;
        index = 0;
        lowerCase = 0;

        while (userIndex < std::strlen(user))
        {            
            if (strstr("add printall find delete quit", user) != NULL) 
            {
                if (std::strncmp(user, add, userIndex + 1) == 0 && std::strlen(user) <= 3)
                {
                    std::cout << "\n*******************************************\n";
                    std::cout << "              Add: Option Selected              \n";
                    std::cout << "*******************************************\n\n";
                    std::cout << "Please enter your account number: ";

                    while (!(std::cin >> accountNumber) || accountNumber <= 0)
                    {
                        if (!std::cin)
                        {
                            std::cout << "ERROR: enter an integer for your account number: ";
                            std::cin.clear();
                        }
                        else if (accountNumber <= 0)
                        {
                            std::cout << "ERROR: enter a positive account number: ";
                        }

                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }

                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    std::cout << "Please enter your name: ";
                    std::cin.getline(name, 30);

                    while (index >= 0)
                    {
                        if (index >= 30)
                        {
                            std::cout << "\nName is too long. Please enter a shorter name.\n";

                            std::cin.clear();

                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                            index = 0;

                            std::cin.getline(name, 30);
                        }

                        if (name[index] == '\0')
                        {
                            index = -1;
                        }
                        else
                        {
                            index++;
                        }
                    }

                    getaddress(address, 50); 

                    if (start.addRecord(accountNumber, address, name) == -1)
                    {
                        std::cout << "\n=========== ACCOUNT NUMBER ALREADY EXISTS! ==========\n";
                        std::cout << "=                                                   =\n";
                        std::cout << "=                 RECORD NOT ADDED                  =\n";
                        std::cout << "=                                                   =\n";
                        std::cout << "=====================================================\n";
                    }
                    else
                    {
                        std::cout << "\n==================================================\n";
                        std::cout << "=           RECORD SUCCESSFULLY ADDED            =\n";
                        std::cout << "==================================================\n";
                    }

                    std::cin.getline(input, 100);
                    userIndex = std::strlen(user); 
                    menu = 1;                 
                } 
                else if (std::strncmp(user, printall, userIndex + 1) == 0 && std::strlen(user) <= 8)
                {
                    std::cout << "\n*******************************************\n";
                    std::cout << "           Print All: Option Selected           \n";
                    std::cout << "*******************************************\n";

                    /* start.printAllRecords(); */

                    std::cout << start;

                    userIndex = strlen(user);
                    menu = 1;
                }
                else if (std::strncmp(user, find, userIndex + 1) == 0 && std::strlen(user) <= 4)
                {
                    std::cout << "\n*******************************************\n";
                    std::cout << "             Find: Option Selected             \n";
                    std::cout << "*******************************************\n\n";
                    std::cout << "Please enter your account number: ";

                    while (!(std::cin >> accountNumber) || accountNumber <= 0)
                    {
                        if (!std::cin)
                        {
                            std::cout << "ERROR: enter an integer for your account number: ";
                            std::cin.clear();
                        }
                        else if (accountNumber <= 0)
                        {
                            std::cout << "ERROR: enter a positive account number: ";
                        }

                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }

                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    if (start.findRecord(accountNumber)) 
                    {
                        std::cout << "\n========== ACCOUNT NUMBER DOES NOT EXIST! ==========\n";
                        std::cout << "=                                                  =\n";
                        std::cout << "=               COULDN'T FIND RECORD               =\n";
                        std::cout << "=                                                  =\n";
                        std::cout << "====================================================\n";
                    }

                    userIndex = strlen(user);
                    menu = 1;
                }
                else if (std::strncmp(user, del, userIndex + 1) == 0 && std::strlen(user) <= 6)
                {
                    std::cout << "\n*******************************************\n";
                    std::cout << "            Delete: Option Selected            \n";
                    std::cout << "*******************************************\n\n";
                    std::cout << "Please enter your account number: ";

                    while (!(std::cin >> accountNumber) || accountNumber <= 0)
                    {
                        if (!std::cin)
                        {
                            std::cout << "ERROR: enter an integer for your account number: ";
                            std::cin.clear();
                        }
                        else if (accountNumber <= 0)
                        {
                            std::cout << "ERROR: enter a positive account number: ";
                        }

                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }

                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
               
                    if(start.deleteRecord(accountNumber))
                    {
                        std::cout << "\n========== ACCOUNT NUMBER DOES NOT EXIST! ==========\n";
                        std::cout << "=                                                  =\n";
                        std::cout << "=               RECORD NOT DELETED                 =\n";
                        std::cout << "=                                                  =\n";
                        std::cout << "====================================================\n";

                    }
                    else
                    {
                        std::cout << "\n====================================================\n";
                        std::cout << "=           RECORD SUCCESSFULLY DELETED            =\n";
                        std::cout << "====================================================\n";
                    }

                    userIndex = strlen(user);
                    menu = 1;

                }
                else if (std::strncmp(user, quit, userIndex + 1) == 0 && std::strlen(user) <= 4)
                {
                    boolean = 0;
                    
                    if(boolean == 0)
                    {
                        std::cout << "\n###########################################\n";
                        std::cout << "     Thank You for Banking with Us!        \n";
                        std::cout << "      Have a Great Day and Goodbye!          \n";
                        std::cout << "###########################################\n\n";
                    }

                    userIndex = std::strlen(user);
                }
                else 
                {
                    std::cout << "\nINVALID CHOICE.\n";
                    std::cout << "---------------------------------------\n";
                    std::cout << "add: Adds a new bank record.\n";
                    std::cout << "printall: Prints all existing bank records.\n";
                    std::cout << "find: Finds existing bank record.\n";
                    std::cout << "delete: Deletes one existing bank record.\n";
                    std::cout << "quit: Quits the program\n";
                    std::cout << "----------------------------------------\n\n";
                    std::cout << "PLEASE SELECT A VALID OPTION: ";

                    menu = 0;

                    userIndex = std::strlen(user);               
                } 
            }
            else 
            {
                std::cout << "\nINVALID CHOICE.\n";
                std::cout << "---------------------------------------\n";
                std::cout << "add: Adds a new bank record.\n";
                std::cout << "printall: Prints all existing bank records.\n";
                std::cout << "find: Finds existing bank record.\n";
                std::cout << "delete: Deletes one existing bank record.\n";
                std::cout << "quit: Quits the program\n";
                std::cout << "----------------------------------------\n\n";
                std::cout << "PLEASE SELECT A VALID OPTION: ";

                menu = 0;

                userIndex = std::strlen(user);   
            }

            userIndex++;
        }
    }

    /* EXTRA CREDIT 
    
    llist copy = start;

    llist twin;

    twin = copy;

    std::cout << "\nThis is the START list\n" << start;

    std::cout << "\nThis is the COPY list\n" << copy;

    std::cout << "\nThis is the TWIN list\n" << twin; 
    
    */

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
    #ifdef DEBUG_MODE 
        std::cout << "\n========== This is the getaddress function ==========\n"
                  << "Parameters:\naddress[]: " << address
                  << "\nint: " << size
                  << "\n====================================================\n";
    #endif

    char character;
    int loop = 1;
    int index = 0;

    std::cout << "Please enter your address below and type '$' when finished:\n";

    while (loop)
    {
        if (index >= size) 
        {
            std::cout << "\n+-------------------------------------------------------------+\n";
            std::cout << "+    Address is too long. Please enter a shorter address.     +\n";
            std::cout << "+ Please enter your address below and type '$' when finished: +\n";
            std::cout << "+-------------------------------------------------------------+\n";

            while ((character = std::cin.get()) != '\n') 
            {

            }

            index = 0;
        }

        character = std::cin.get();
        address[index] = character;
        index++;

       if (character == '$')
       {
            address[index-1] = '\0';
            loop = 0;
       }
    }
}


