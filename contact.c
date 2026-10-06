#include <stdio.h>                       
#include <stdlib.h>
#include <string.h>
#include <stdio_ext.h>
#include "contact.h"
#include "contact.h"                  //addressbook structure of function declaration
#include "file.h"                     //function releted to save/load contact to file

//Display all contacts
void listContacts(AddressBook *addressBook)                              
{
    Contact temp;                                   //Temporary variable used for swapping contacts

    //Bubble sort based on naming
    for(int i=0; i < addressBook->contactCount-1; i++)
    {
        //compare adjecent contacts
        for(int j=0; j<addressBook->contactCount-i-1; j++)
        {
            if(strcmp(addressBook->contacts[j].name , addressBook->contacts[j+1].name)>0)
            {
                //swap if the current name comes after the next name
                temp=addressBook->contacts[j];
                addressBook->contacts[j]=addressBook->contacts[j+1];
                addressBook->contacts[j+1]=temp;
            }
        }
    }
    //shows the list to user
    printf("\n===============================================================\n");
    printf("------CONTACT LIST------\n");
    printf("=================================================================\n");
    printf("%-8s %-20s %-15s %-30s\n","Sr.No","|NAME","|PHONE","|EMAIL");
    printf("-----------------------------------------------------------------\n");

    for(int i=0; i<addressBook->contactCount; i++)
    {
        printf("%-8d|%-20s|%-15s|%-30s\n",i+1,addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }

    printf("==================================================================\n");
}

void initialize(AddressBook *addressBook) 
{ 
    addressBook->contactCount = 0;                            //initialize contact count
    
    
    loadContactsFromFile(addressBook);                        //load previously saved contacts from file
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook);                          // Save contacts to file
    exit(EXIT_SUCCESS);                                       // Exit the program
}


int validate_name(char *str1)                                 //validation function for name
{
    int i=0;
    int valid=1;
    
    while(str1[i])                                             //validate 
    {
        if(!((str1[i]>='A' && str1[i]<='Z')  || (str1[i]>='a' && str1[i]<='z') ||
            (str1[i]=='.') || (str1[i]==' ')))
            {
                valid=0;
                break;
            }
            i++;
    }
    return valid;                                               //returnns result valid or not
}


int validate_phone(char *str2, AddressBook* addressBook)         //validation for phone number
{
    int i=0;
    int valid=1;
    int len=strlen(str2);                                        //calculating length of str is it 10
    while(str2[i])
    {
        if(!((str2[i]>='0' && str2[i]<='9') && len==10))         //validating user number contains only digits
        {
            valid=0;
            break;
        }
        i++;
    }
    if(valid==1)
    {
        for(int k=0; k<addressBook->contactCount; k++)           //cheack is this no. already present or not         
        {
            if(strcmp(addressBook->contacts[k].phone, str2)==0)
            {
                valid=-1;
                break;
            }
        }
    }
    return valid;                                                 //returns the result
}
    
    
int validate_email(char *str3, AddressBook* addressBook)          //validate mail
{
    int len=strlen(str3);
    int i=0;
    int at=0;

    if(!(str3[0]>='a' && str3[0]<='z'))                          //1st char is either than small
    {
        return 0;
    }
    while(str3[i])
    {
        if(!((str3[i]>='a' && str3[i]<='z') ||                   //either than this chars then invalid
          (str3[i]>='0' && str3[i]<='9') || (str3[i]=='@')|| (str3[i]=='.')))
        {
            return 0;
        }
        if(str3[i]=='@')                                        //count @ in string
        {
            at++;
        }
        i++;
    }

    if(at!=1) return 0;                                         //more than 1 or 0 @ are present return 0

    if(str3[0]=='@' || str3[len-1]=='@')                        //if @ and 0th idx or last idx 
    {
        return 0;
    }

    if(strcmp(&str3[len-4], ".com")!=0)                         //compare at last '.com' present
    {
        return 0;
    }
    
    for(int k=0; k<addressBook->contactCount; k++)               //compare is email already exists or not
    {
        if(strcmp(addressBook->contacts[k].email , str3)==0)
        {
            
            return -1;
        }
    }
    return 1;                                                      //if all okay return 1
}

void createContact(AddressBook *addressBook)                       //function for create contact
{

    char str1[60];
    int res;

    do
    {
        printf("Enter the Name : ");                                //reading input from user
        scanf(" %[^\n]", str1);

        res = validate_name(str1);                                //call validate function for validation
        if(res==0)
        {
            printf(RED"Invalid Name!!!\nEnter Again..\n"RESET);            //not valid
        }
    }while(res == 0);

    char str2[11];                                                  //string initallization for mobile no.
    
    do
    {
        printf("Enter The Phone Number : ");                        //reading phone number from user
        scanf("%s",str2);

        res=validate_phone(str2, addressBook);                      //call validate phone function for validate phone no.
        if(res==0)
        {
            printf(RED"Invalid phone Number\nEnter Again..\n"RESET);
        }
        if(res==-1)                                                 //if contact already present return -1
        {
            printf(YELLOW"Contact Already Existss.!!!\nEnter Valid Number\n"RESET);
        }
    }while(res==0 || res==-1);                                      //runing loop until invalid and duplicate


    char str3[60];                                                  //declaration of str for email

    do
    {
        printf("Enter The Email-ID : ");                            //reading input email-ID from user
        scanf("%s",str3);

        res=validate_email(str3,addressBook);                       //validate email id by calling validate email function
        if(res==0)                                                  //if it returns 0 means it is inavlid 
        {
            printf(RED"Invalid EMAIL-ID\nEnter Valid ID   ..\n"RESET);
        }
        if(res==-1)                                                  //if it returns -1 means duplicate email occuring
        {
            printf(YELLOW"Email Already Existt.!!!\nEnter Valid Email\n"RESET);
        }
    }while(res==0 || res==-1);                                      //run loop until right input


    //stores the Validated contact details

    strcpy(addressBook->contacts[addressBook->contactCount].name, str1);
    strcpy(addressBook->contacts[addressBook->contactCount].phone, str2);
    strcpy(addressBook->contacts[addressBook->contactCount].email, str3);

    addressBook->contactCount++;                                   //increse contact count after adding the contact
    
    
}
//search by name function for searching contact using name
int search_by_name(AddressBook* addressBook)
{
    char str[60];
    int choice;
    int found=0;

    printf("Enter the Name: ");                                      //reading input name from user to search contact
    scanf(" %[^\n]",str);

    for(int k=0; k<addressBook->contactCount; k++)                   //calculates how many contacts matched
    {
        if(strcmp(addressBook->contacts[k].name, str)==0)
        {
            found++;
        }
    }
    if(found==0)                                                      //if not found returns -1
    {
        return -1;
    }
    if(found==1)                                                      //if single contact found returns index
    {
       for(int k=0; k<addressBook->contactCount; k++)
       {
            if(strcmp(addressBook->contacts[k].name, str)==0)
            {
                return k;
            }
        } 
    }
    //shows to user that more than 1 contacts matched

    printf("-----------------------------------------------------------\n");
    printf(YELLOW"\n=====.Multiple Contacts Found.!!!=====\n\n"RESET);
    printf("Contacts found at \n\n");
    printf("%-8s %-20s %-15s %-30s\n","Sr.No","NAME","PHONE","EMAIL");
    printf("------------------------------------------------------------\n");

    for(int k=0; k<addressBook->contactCount; k++)                     //shows all contacts with same name
    {
        if(strcmp(addressBook->contacts[k].name, str)==0)
        {
            printf("%-8d %-20s %-15s %-30s\n",k+1,addressBook->contacts[k].name,addressBook->contacts[k].phone,addressBook->contacts[k].email);
        }
    }
    printf("--------------------------------------------------------------\n");
    do
    {
        printf(MAGENTA"Enter Sr.No to select contact: "RESET);                      //ask user for select sr no which user want contact  
        scanf("%d",&choice);
        
        if(choice < 1 || choice > addressBook->contactCount)            //if user gives invalid contact
        {
            printf(RED"Invalid Sr.No.!! Enter again.\n"RESET);
            continue;
        }
        if(strcmp(addressBook->contacts[choice-1].name,str)!=0)          //user gives wrong sr no from list
        {
            printf(MAGENTA"This Sr.No. does not belongs to %s!\n"RESET,str);
            continue;
        }  

        return choice-1;                                                  //returns index which user selected

    }while(1);                                                            //create infinte loop for send correct 
}
//search by phone number function

int search_by_phone(AddressBook* addressBook)
{
    char str[11];
    printf("Enter the Phone Number: ");                                    //reading input phone number to search
    scanf("%s",str);
    for(int k=0; k<addressBook->contactCount; k++)
    {
        if(strcmp(addressBook->contacts[k].phone, str)==0)
        {
            return k;                                                     //actual array index
        }
    }
    return -1;                                                           //-1 coz array idx starts from 0              
}
//search by email function

int search_by_email(AddressBook* addressBook)
{
    char str[60];
    printf("Enter the EMAIL-ID: ");                                        //reading input email from user to search
    scanf("%s",str);
    for(int k=0; k<addressBook->contactCount; k++)                         //finds that mail from database
    {
        if(strcmp(addressBook->contacts[k].email, str)==0)
        {
            return k;                                                     //actual array index
        }
    }
    return -1;                                                            //if not found
}

void searchContact(AddressBook *addressBook) 
{
    int valid=0;
    int choice;
    do
    {
        printf("Search By:-\n1.Name\n2.Phone No.\n3.Email\n4.EXIT\n");     //menu for user to select choice to search
        if(scanf("%d",&choice)!=1)
        {
            __fpurge(stdin);
            printf(RED"Invalid Choice. Please try again..\n"RESET);
            continue;
        }

        int index;
        switch(choice)                                                     //using switch for menu driven system
        {
            case 1:
            index=search_by_name(addressBook);                              //calling search by name function
            if(index==-1)                                                   //not found in database
            {
                printf(RED"Contact Not Found.!!\n"RESET);
            }
            else
            {
                //printing found contact to screen
                printf("Contacts Found At...\n");
                printf("-------------------------------------------------------------------------------------\n");
                printf("%-8s %-20s %-15s %-30s\n","Sr.No","NAME","PHONE","EMAIL");
                printf("-------------------------------------------------------------------------------------\n");
                printf("%-8d %-20s %-15s %-30s\n\n",index+1,addressBook->contacts[index].name,addressBook->contacts[index].phone,addressBook->contacts[index].email);
            }
            valid=1;                                                       //makes valid=1 for to exit from loop
            break;                                                //using break to avoid fall through condition

            case 2:
            index=search_by_phone(addressBook);                            //search contact by phone
            if(index==-1)                                                  //returns if contact not found
            {
                printf(RED"Contact Not Found.!!\n"RESET);
            }
            else
            {
                //list contact to user 
                printf("Contacts Found At...\n");
                printf("----------------------------------------------------------------------------------\n");
                printf("%-8s %-20s %-15s %-30s\n","Sr.No","NAME","PHONE","EMAIL");
                printf("-----------------------------------------------------------------------------------\n");
                printf("%-8d %-20s %-15s %-30s\n",index+1,addressBook->contacts[index].name,addressBook->contacts[index].phone,addressBook->contacts[index].email);
            }
            valid=1;
            break;

            case 3: 
            index=search_by_email(addressBook);                              //call search by email function to find using mail
            if(index==-1)                                                    //-1 if not found
            {
                printf("Contact Not Found.!!\n");
            }
            else
            {
                //shows list to user
                printf(RED"Contacts Found At...\n"RESET);
                printf("-----------------------------------------------------------------------------------------------\n");
                printf("%-8s %-20s %-15s %-30s\n","Sr.No","NAME","PHONE","EMAIL");
                printf("------------------------------------------------------------------------------------------------\n");
                printf("%-8d %-20s %-15s %-30s\n\n",index+1,addressBook->contacts[index].name,addressBook->contacts[index].phone,addressBook->contacts[index].email);
            }
            valid=1;
            break;

            case 4:
            printf("Exiting...\n");                                           //if user select exit it returns to main menu
            return ;

            default:
            printf(RED"INVALID CHOICE.!!\nEnter Correct Choice..\n"RESET);          
        }

    }while(valid==0);
}

void edit_field(AddressBook* addressBook, int index)                         ///for edit name or phone or mail
{
    int choice;
    do
    {
        //to edit particular field 
        printf("Which Field do you Want to EDIT: \n1.Name\n2.Phone No.\n3.Email\n4.Exit\n\n");
        if(scanf("%d",&choice)!=1)
        {
            __fpurge(stdin);
            printf(RED"Invalid Choice. Please try again..\n"RESET);
            continue;
        }
        __fpurge(stdin);

        switch(choice)                                                        //using switch for taking user cg]hoice
        {
            case 1:
            {
                char str[60];
                int res;

                do
                {
                    printf("Enter New Name: ");                               //read new name to read from user
                    scanf(" %[^\n]",str);

                    res=validate_name(str);                                   //calling validate name function to check new name is valid

                    if(res==0)
                    {
                        printf(RED"Invalid Name.!!\nEnter Again.\n"RESET);             //if user gives invalid name
                    }
                }while(res==0);

                strcpy(addressBook->contacts[index].name, str);                //coping to contacts from local string
                printf(GREEN"\nName Updated Successfully...!!!\n"RESET);
                printf(GREEN"Editing Completed.\n"RESET);    
                return ;                                                        //returns to main menu after completing
            }
            case 2:
            {
                char str[11];                                                   //creating tempor string to store phone number
                int res;

                do
                {
                    printf("Enter NEW Phone Number: \n");                            //reading string from user
                    scanf("%s",str);

                    if(strcmp(addressBook->contacts[index].phone, str)==0)        //allow current no without treating duplicate
                    {
                        res=1;
                    }
                    else
                    {
                        res=validate_phone(str,addressBook);                      //calling validate function to check is this no valid
                    }

                    if(res==0)
                    {
                        printf(RED"Invalid phone Number.!!!\nEnter Again.\n"RESET);        //if validate fun returns  means it invalid
                    }
                    else if(res==-1)                                                //-1 means no already allowed to another
                    {
                        printf(YELLOW"Phone Number Already Exists!!!\nEnter Again.\n"RESET);
                        res=0;
                    }
                }while(res==0);                                                      

                strcpy(addressBook->contacts[index].phone, str);                      //undating phone number from temp str
                printf(GREEN"Phone No. Updated Successfully!\n"RESET);
                printf(GREEN"Editing Completed.\n"RESET);
                return ;
            }
            case 3:
            {
                char str[60];                                                  // temp string
                int res;

                do
                {
                    printf("Enter New Email-ID : ");                           //reading new emailid from user
                    scanf("%s",str);

                    if(strcmp(addressBook->contacts[index].email, str)==0)     //comparing to current mail
                    {
                        res=1;
                    }
                    else
                    {
                        res=validate_email(str,addressBook);                    //calling validate email to check valid or not
                    }

                    if(res==0)
                    {
                        printf(RED"Invalid Email.!!\nEnter Again.\n\n"RESET);
                    }
                    else if(res==-1)
                    {
                        printf(YELLOW"Email Already Exists.!!Enter Again.\n"RESET);         //if mail already allocated to another
                        res=0;
                    }
                }while(res==0);

                strcpy(addressBook->contacts[index].email, str);                  //updating to addressbook
                printf(GREEN"Email Updated Successfully!!\n"RESET);
                printf(GREEN"Editing Completed.\n"RESET);
                return ;
            }

            case 4:
            printf("Back to Main MENU.\n\n");                                     //it returns to main menu
            return ;

            default:
            printf(RED"Invalid Choice.!!\n"RESET);                                        //user gives invalid choice
        }

    } while (1);
}
//function to edit the contact
void editContact(AddressBook *addressBook)
{     
    int choice;
    int index;
    int valid=0;
    do
    {
        //menu to user edit contact by..
        printf("\nEdit Contact:\nSearch By..\n1.Name\n2.Phone No.\n3.Email\n  4.Exit\n\n");
        printf("Enter Choice: ");                                   //read choice from user
        if(scanf("%d",&choice)!=1)
        {
            __fpurge(stdin);
            printf(RED"Invalid Choice. Please try again..\n"RESET);
            continue;
        }
        __fpurge(stdin);

        switch(choice)                                               //use switch case to call the function based of user choice 
        {
            case 1:
            index=search_by_name(addressBook);                       //search contact by name
            valid=1;
            break;

            case 2:
            index=search_by_phone(addressBook);                        //search contact by phone
            valid=1; 
            break;

            case 3:
            index=search_by_email(addressBook);                         //search contact by email
            valid=1;

            case 4:
            printf("EXITING...\n");                                      //back to main menu
            break;

            default:
            printf(RED"INVALID Choice..!!!\n"RESET);                             //other than 1-4 choices
        }
    }while(valid==0);
    
    if(index==-1)
    {
        printf("Contact Not Found..!!\n");                              //contact not found returns -1
        return ;
    }
    //printing the selected contact to edit
    printf("\nSelected Contact:\n");
    printf("----------------------------------------------------------------------------------------------------\n");
    printf("%-8s %-20s %-15s %-30s\n","Sr.No","NAME","PHONE","EMAIL");
    printf("-----------------------------------------------------------------------------------------------------\n");
    printf("%-8d %-20s %-15s %-30s\n",index+1,addressBook->contacts[index].name,addressBook->contacts[index].phone,addressBook->contacts[index].email);

    edit_field(addressBook,index);                     //call function edit_field to edit specific contact
    
}
//function to shift contact that we want to dlt
void shift_contact(AddressBook* addressBook, int index)
{
    for(int i=index; i<addressBook->contactCount-1; i++)             //loop start from contact that to dlt to last count
    {
        addressBook->contacts[i]=addressBook->contacts[i+1];         //coping the next contact to current position
    }

    addressBook->contactCount--;                                     //decreses contact count by 1
}

//function to delete contact from addressbook
void deleteContact(AddressBook *addressBook)
{
    int choice;
    int index;
    int valid=0;
    
    do
    {
        //to delete contact by...
        printf("---Delete Contact---\nSearch By :\n1.Name\n2.Phone\n3.Email\n4.Exit\n\n");
        printf("Enter Choice : ");
        if(scanf("%d",&choice)!=1)
        {
            __fpurge(stdin);
            printf(RED"Invalid Choice. Please try again..\n"RESET);
            continue;
        }
        __fpurge(stdin);                           //reading ip from user

        switch(choice)                                 //use switch case to call function based on user choice
        {
            case 1:
            index=search_by_name(addressBook);          //search contact by name  
            valid=1;
            break;

            case 2:
            index=search_by_phone(addressBook);         //search contact by phone
            valid=1;
            break;

            case 3:
            index=search_by_email(addressBook);           //search contact by email id
            valid=1;
            break;

            case 4:
            printf("Closingg..\n");                       //back to main menu
            return ;

            default: 
            printf(RED"Invalid Choice.!!!\nEnter the Valid choice>\n"RESET);        //invalid 
        }
    } while (valid==0);
    
    if(index==-1)                                             //if contact not found returns -1
    {
        printf(RED"Contact Not Found.!!!\n"RESET);
        return ;
    }
    //print the selected contact to delete
    printf("\nSelected Contact : \n");
    printf("---------------------------------------------------------------------------------------------\n");
    printf("%-8s %-20s %-15s %-30s\n","Sr.No","NAME","PHONE","EMAIL");
    printf("----------------------------------------------------------------------------------------------\n");
    printf("%-8d %-20s %-15s %-30s\n",index+1,addressBook->contacts[index].name,addressBook->contacts[index].phone,addressBook->contacts[index].email);

    shift_contact(addressBook,index);                          //calling shif_contact function to shift contact that we want to dlt

    printf(GREEN"\nContact Deleted Successfully!!!\n"RESET);             //successful deleting done
}
