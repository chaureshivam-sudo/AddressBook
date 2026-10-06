#include <stdio.h>
#include<string.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) 
{
    FILE *fp;
    fp=fopen("contacts.txt","w");

    if(fp==NULL)
    {
        printf("Unable to open File.!!!\n");
        return;
    }
     fprintf(fp, "# %d\n",addressBook->contactCount);
    for(int i=0; i<addressBook->contactCount; i++)
    {
        fprintf(fp ,"%s  %s  %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fp);

    printf(GREEN"Contacts Saved Successfully.!!\n"RESET);
}

void loadContactsFromFile(AddressBook *addressBook) 
{
    FILE *fp;
    fp=fopen("contacts.txt" , "r");
    if(fp==NULL)
    {
        // printf("File not Found.!!\n");
        return ;
    }   
    char name[60];
    char phone[20];
    char email[60];

    int count=0;
    fscanf(fp,"# %d\n",&count);


    while(fscanf(fp, "%s %s %s", name,phone,email)==3 && addressBook->contactCount<MAX_CONTACTS)
    {
        strcpy(addressBook->contacts[addressBook->contactCount].name,name);
        strcpy(addressBook->contacts[addressBook->contactCount].phone,phone);
        strcpy(addressBook->contacts[addressBook->contactCount].email,email);

        addressBook->contactCount++;
    }
    fclose(fp);
}




