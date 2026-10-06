#include <stdio.h>
#include <stdio_ext.h>
#include "contact.h"

int main() 
{
    int choice;
    AddressBook addressBook;
    initialize(&addressBook);                                    // Initialize the address book

    do 
    {
        //shows main menu to user
        
        printf("\n:::--------AddressBook Menu--------:::\n\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
    	printf("6. Save and Exit\n\n");		

        printf("Enter your choice: ");                           //reading the choice from user 
        if(scanf("%d", &choice)!=1)
        {
            __fpurge(stdin);
            printf("Invalid choice, please try again..\n");
            continue;
        }
        __fpurge(stdin);
        
        switch (choice)                                          //use switch case to function call choice wise
        {
            case 1:
                createContact(&addressBook);                     //function to create contact 
                break;
            case 2:
                searchContact(&addressBook);                     //function to search contact
                break;
            case 3:
                editContact(&addressBook);                       //function to edit contact
                break;
            case 4:
                deleteContact(&addressBook);                     //function to delete contact
                break;
            case 5:          
                listContacts(&addressBook);                      //function to display contact list
                break;
            case 6:
                printf("Saving and Exiting...\n");                
                saveContactsToFile(&addressBook);                //it terminate program and save contact to database
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);
    
    return 0;
}
