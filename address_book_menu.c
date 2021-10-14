#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "address_book_fops.h"
#include "address_book_menu.h"
#include "address_book.h"

int get_option(int type, const char *msg)
{
	/*
	 * Mutilfuction user intractions like
	 * Just an enter key detection
	 * Read an number
	 * Read a charcter
	 */ 

	/* Fill the code to add above functionality */
}

Status save_prompt(AddressBook *address_book)
{
	char option;

	do
	{
		main_menu();

		option = get_option(CHAR, "\rEnter 'N' to Ignore and 'Y' to Save: ");

		if (option == 'Y')
		{
			save_file(address_book);
			printf("Exiting. Data saved in %s\n", DEFAULT_FILE);

			break;
		}
	} while (option != 'N');

	free(address_book->list);

	return e_success;
}

Status list_contacts(AddressBook *address_book, const char *title, int *index, const char *msg, Modes mode)
{
	/* 
	 * Add code to list all the contacts availabe in address_book.csv file
	 * Should be menu based
	 * The menu provide navigation option if the entries increase the page size
	 */ 

	return e_success;
}

void menu_header(const char *str)
{
	fflush(stdout);

	printf("#######  Address Book  #######\n");
	if (*str != '\0')
	{
		printf("#######  %s\n", str);
	}
}

void main_menu(void)
{
	menu_header("Features:\n");

	printf("0. Exit\n");
	printf("1. Add Contact\n");
	printf("2. Search Contact\n");
	printf("3. Edit Contact\n");
	printf("4. Delete Contact\n");
	printf("5. List Contacts\n");
	printf("6. Save\n");
	printf("\n");
	printf("Please select an option: ");
}

Status menu(AddressBook *address_book)
{
	ContactInfo backup;
	Status ret;
	int option;
	char exitOpt;
	do
	{
		main_menu();

		option = get_option(NUM, "");

		if ((address_book-> count == 0) && (option != e_add_contact))
		{
			get_option(NONE, "No entries found!!. Would you like to add? Use Add Contacts");

			continue;
		}

		printf("Enter your option: ");
		int option;
		scanf("%d", &option);
		

		switch (option)
		{
			case e_add_contact:
				/* Add your implementation to call add_contacts function here */
				add_contacts(address_book);
				break;
			case e_search_contact:
				search_contact(address_book);
				break;
			case e_edit_contact:
				edit_contact(address_book);
				break;
			case e_delete_contact:
				delete_contact(address_book);
				break;
			case e_list_contacts:
				list_All_Contacts(address_book);
				break;
				/* Add your implementation to call list_contacts function here */
			case e_save:
				save_file(address_book);
				break;
			case e_exit:
				option = e_exit;
				break;
		}
		getchar();
		printf("Would you like to exit the program? y/n: ");
		scanf("%c", &exitOpt);
	} while ( exitOpt != 'y');

	return e_success;
}

Status add_contacts(AddressBook *address_book)
{
	/* Add the functionality for adding contacts here */
	ContactInfo info;
	FILE *fp;
	if((fp = fopen(DEFAULT_FILE, "a")) == NULL)
	{	
		printf("File cannot be opened \n");
		return e_fail;
	}
	printf("Enter username : ");
	scanf("\n%s", info.name);
	printf("Enter phone no : ");
	scanf("%s", info.phone_numbers[0]);
	getchar();
	printf("Enter phone no#2: ");
	scanf("%s", info.phone_numbers[1]);
	getchar();
	printf("Enter email id : ");
	scanf("%s", info.email_addresses);
	fwrite(&info, sizeof(info), 1, fp);
	fclose(fp);

	return e_success;
}

Status search(const char *str, AddressBook *address_book, int loop_count, int field, const char *msg, Modes mode)
{
	/* Add the functionality for adding contacts here */
	; // Do nothing
}

Status search_contact(AddressBook *address_book)
{
	/* Add the functionality for search contacts here */
}

Status edit_contact(AddressBook *address_book)
{
	/* Add the functionality for edit contacts here */
	/* Add the functionality for edit contacts here */
	ContactInfo editInfo;

	FILE *fp;
	FILE *rewriteFile;

	if ((fp = fopen(DEFAULT_FILE, "r")) == NULL) {
		printf("File can't be opened\n");
		return e_fail;
	}
	else {
		rewriteFile = fopen("temporaryFile.csv", "w");
		if (rewriteFile == NULL) {
			printf("File can't be opened\n");
			return e_fail;
		}
	}

	char name[NAME_LEN];
	char phoneNum[NUMBER_LEN];
	char email[EMAIL_ID_LEN];

	menu_header("Search Contact by field you would like to edit:\n");
	printf("0. Back\n");
	printf("1. Name\n");
	printf("2. Phone No\n");
	printf("3. Email ID\n");
	printf("4. Serial No\n");
	printf("\nPlease select an option: ");
	int selection;

	scanf("%d", &selection);

	int counter;
	int saveCounter;
	switch(selection) {
		case 0:
			return e_back;
		case 1:
			printf("Enter the Name: ");
			scanf("\n%s", name);

			while (fread(&editInfo, sizeof(editInfo), 1, fp) == 1) {
				if (strcmp(name, *editInfo.name)) { //finding the contact to edit
					fwrite(&editInfo, sizeof(editInfo), 1, rewriteFile);
					counter = 0;
				}
				else {
					printf("Enter the name you would like to change to: ");
					scanf("\n%s", editInfo.name);
					fwrite(&editInfo, sizeof(editInfo), 1, rewriteFile);
					counter++;
					saveCounter = counter;
					printf("Edited Successfully\n");
				}
			}
			break;
		case 2:
			printf("Enter the Phone No: ");
			scanf("%s", phoneNum);

			while (fread(&editInfo, sizeof(editInfo), 1, fp) == 1) {
				if (strcmp(phoneNum, *editInfo.phone_numbers)) {
					printf("Enter the phone number you would like to change to: ");
					scanf("\n%s", editInfo.phone_numbers); //mult phone numbers??
					fwrite(&editInfo, sizeof(editInfo), 1, rewriteFile);
					counter = 0;
				}
				else {
					counter++;
					saveCounter = counter;
				}
			}
			break;
		case 3:
			printf("Enter the Email ID: ");
			scanf("%s", email);

			while (fread(&editInfo, sizeof(editInfo), 1, fp) == 1) {
				if (strcmp(email, *editInfo.email_addresses)) {
					printf("Enter the email ID you would like to change to: ");
					scanf("\n%s", editInfo.email_addresses);
					fwrite(&editInfo, sizeof(editInfo), 1, rewriteFile);
					counter = 0;
				}
				else {
					counter++;
					saveCounter = counter;
				}
			}
			break;
		default:
			printf("Invalid option.\n");
			return e_no_match;
	}

	fclose(fp);
	// fclose(fp);
	fclose(rewriteFile);
	// fclose(rewriteFile);

	remove(DEFAULT_FILE);
	rename("temporaryFile.csv", DEFAULT_FILE);

	if (!saveCounter) {
		printf("Could not find that contact detail.\n");
		return e_fail;
	}
	else {
		printf("That contact details has been edited successfully.\n");
	}
	return e_success;
}

Status delete_contact(AddressBook *address_book)
{
	/* Add the functionality for delete contacts here */
	ContactInfo delInfo;

	FILE *fp;
	FILE *rewriteFile;

	if ((fp = fopen(DEFAULT_FILE, "r")) == NULL) {
		printf("File can't be opened\n");
		return e_fail;
	}
	else {
		rewriteFile = fopen("temporaryFile.csv", "w");
		if (rewriteFile == NULL) {
			printf("File can't be opened\n");
			return e_fail;
		}
	}

	char name[NAME_LEN];
	char phoneNum[NUMBER_LEN];
	char email[EMAIL_ID_LEN];

	menu_header("Search Contact to Delete By:\n");
	printf("0. Back \n");
	printf("1. Name\n");
	printf("2. Phone No\n");
	printf("3. Email ID\n");
	printf("4. Serial No\n");
	printf("\nPlease select an option: ");
	int selection;

	scanf("%d", &selection);

	int counter;
	int saveCounter;
	switch(selection) {
		case 0:
			return e_back;
		case 1:
			printf("Enter the Name: ");
			scanf("\n%s", name);

			while (fread(&delInfo, sizeof(delInfo), 1, fp) == 1) {
				if (strcmp(name, *delInfo.name)) {
					fwrite(&delInfo, sizeof(delInfo), 1, rewriteFile);
					counter = 0;
				}
				else {
					counter++;
					saveCounter = counter;
					printf("Deleted Successfully\n");
				}
			}
			break;
		case 2:
			printf("Enter the Phone No: ");
			scanf("%s", phoneNum);

			while (fread(&delInfo, sizeof(delInfo), 1, fp) == 1) {
				if (strcmp(phoneNum, *delInfo.phone_numbers)) {
					fwrite(&delInfo, sizeof(delInfo), 1, rewriteFile);
					counter = 0;
				}
				else {
					counter++;
					saveCounter = counter;
				}
			}
			break;
		case 3:
			printf("Enter the Email ID: ");
			scanf("%s", email);

			while (fread(&delInfo, sizeof(delInfo), 1, fp) == 1) {
				if (strcmp(email, *delInfo.email_addresses)) {
					fwrite(&delInfo, sizeof(delInfo), 1, rewriteFile);
					counter = 0;
				}
				else {
					counter++;
					saveCounter = counter;
				}
			}
			break;
		default:
			printf("Invalid option.\n");
			return e_no_match;
	}

	fclose(fp);
	fclose(rewriteFile);

	remove(DEFAULT_FILE);
	rename("temporaryFile.csv", DEFAULT_FILE);

	if (!saveCounter) {
		printf("Could not find that contact detail.\n");
		return e_fail;
	}
	else {
		printf("That contact details has been deleted successfully.\n");
	}
	return e_success;
}

Status list_All_Contacts(AddressBook *addressbook){
	FILE *infile;
    ContactInfo information;
     
    infile = fopen (DEFAULT_FILE, "r");
    if (infile == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        exit (1);
    }
     
    // read file contents till end of file
    while(fread(&information, sizeof(ContactInfo), 1, infile))
	{
        printf ("Name = %s  \n", information.name);
		for(int i = 0; i < 5; i++){
			printf("Phone number %d: %s \n", i, information.phone_numbers[i]);
		}
		printf ("Email = %s  \n", information.email_addresses);
	}
 
    // close file
    fclose (infile);
}

/*
int main(){
	AddressBook address_book;
	add_contacts(&address_book);
	list_All_Contacts(&address_book);
	menu(&address_book);
}
*/