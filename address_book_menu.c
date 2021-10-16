#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "address_book_fops.h"
#include "address_book_menu.h"
#include "address_book.h"

int count = 1;
Status getCount(){
	FILE *file;
    ContactInfo information;
	file = fopen (DEFAULT_FILE, "r");
	count = 1;
    if (file == NULL)
    {
        return e_exit;
    }
	while(fread(&information, sizeof(ContactInfo), 1, file))
	{
		count++;
	}
	//printf("The count is %d .\n", count);
    // close file
    fclose (file);
	return e_success;
}

int get_option(int type, const char *msg)
{
	/*
	 * Mutilfuction user intractions like
	 * Just an enter key detection
	 * Read an number
	 * Read a charcter
	 */ 

	/* Fill the code to add above functionality */
	int intOption;
	char charOption;
	printf("%s", msg);
   	switch (type)
   	{
		case NONE:
         	return e_no_opt;
      	case NUM:
         	scanf("%d", &intOption);
         	return intOption;
      	case CHAR:
         	scanf("%c", &charOption);
         	return charOption;
   	}
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
	 * list_All_Contacts function
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

		
		getCount();
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
	for(int i = 0; i < PHONE_NUMBER_COUNT; i++){
		strcpy(info.phone_numbers[i],"");
	}
	for(int i = 0; i < EMAIL_ID_COUNT; i++){
		strcpy(info.email_addresses[i],"");
	}
	FILE *fp;
	if((fp = fopen(DEFAULT_FILE, "a")) == NULL)
	{	
		printf("File cannot be opened \n");
		return e_fail;
	}
	info.si_no = count;
	do{
	printf("Enter username : ");
	scanf("\n%s", info.name);
	} while (strlen(*info.name) > 32);
	// Add Phone numbers
	char addMultiplePhone;
	for(int i = 0; i<PHONE_NUMBER_COUNT; i++){
		printf("Would you like to add a phone number? y/n : ");
		getchar();
		scanf("%c", &addMultiplePhone);
		if(addMultiplePhone == 'y'){
			do{
				printf("Enter phone no. ID #%d: ", i+1);
				scanf("%s", info.phone_numbers[i]);
			}while (strlen(info.phone_numbers[i]) > 32);
		} else {
			break;
		}
	}
	// Add Emails
	char addMultipleEmails;
	for(int i = 0; i<EMAIL_ID_COUNT; i++){
		printf("Would you like to add a email ID? y/n : ");
		getchar();
		scanf("%c", &addMultipleEmails);
		if(addMultipleEmails == 'y'){
			do{
				printf("Enter email ID #%d : ", i+1);
				scanf("%s", info.email_addresses[i]);
			}while (strlen(info.email_addresses[i]) > 32);
		} else {
			break;
		}
	}
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

	int counter = 0;
	int saveCounter = 0;
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
				}
			}
			break;
		case 2:
			printf("Enter the Phone No: ");
			scanf("%s", phoneNum);

			while (fread(&editInfo, sizeof(editInfo), 1, fp) == 1) {
				if (strcmp(phoneNum, *editInfo.phone_numbers)) {
					fwrite(&editInfo, sizeof(editInfo), 1, rewriteFile);
					counter = 0;
				}
				else {
					printf("Enter the phone number you would like to change to: ");
					scanf("\n%s", editInfo.phone_numbers);
					fwrite(&editInfo, sizeof(editInfo), 1, rewriteFile);
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
					fwrite(&editInfo, sizeof(editInfo), 1, rewriteFile);
					counter = 0;
				}
				else {
					printf("Enter the email ID you would like to change to: ");
					scanf("\n%s", editInfo.email_addresses);
					fwrite(&editInfo, sizeof(editInfo), 1, rewriteFile);
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
	printf("\nPlease select an option: ");
	int selection;

	scanf("%d", &selection);

	int counter = 0;
	int saveCounter = 0;
	int entry = 0;
	int boolAlreadyDeleted = 0;
	switch(selection) {
		case 0:
			return e_back;
		case 1:
			printf("Enter the Name: ");
			scanf("\n%s", name);

			while (fread(&delInfo, sizeof(delInfo), 1, fp) == 1) {
				entry++;
				if (strcmp(name, *delInfo.name) || boolAlreadyDeleted) {
					if (boolAlreadyDeleted) {
						delInfo.si_no = entry - 1;
					}
					fwrite(&delInfo, sizeof(delInfo), 1, rewriteFile);
					counter = 0;
				}
				else {
					boolAlreadyDeleted = 1;
					counter++;
					saveCounter = counter;
				}
			}
			break;
		case 2:
			printf("Enter the Phone No: ");
			scanf("%s", phoneNum);

			while (fread(&delInfo, sizeof(delInfo), 1, fp) == 1) {
				entry++;
				for (int i = 0; i < PHONE_NUMBER_COUNT; i++) {
					if (strcmp(phoneNum, delInfo.phone_numbers[i]) || boolAlreadyDeleted) {
						if (boolAlreadyDeleted) {
							delInfo.si_no = entry - 1;
						}
						if (i == 4) {
							fwrite(&delInfo, sizeof(delInfo), 1, rewriteFile);
							counter = 0;
						}
					}
					else {
						boolAlreadyDeleted = 1;
						counter++;
						saveCounter = counter;
						break;
					}
				}
			}
			break;
		case 3:
			printf("Enter the Email ID: ");
			scanf("%s", email);

			while (fread(&delInfo, sizeof(delInfo), 1, fp) == 1) {
				entry++;
				for (int i = 0; i < EMAIL_ID_COUNT; i++) {
					if (strcmp(email, delInfo.email_addresses[i]) || boolAlreadyDeleted) {
						if (boolAlreadyDeleted) {
							delInfo.si_no = entry - 1;
						}
						if (i == 4) {
							fwrite(&delInfo, sizeof(delInfo), 1, rewriteFile);
							counter = 0;
						}
					}
					else {
						boolAlreadyDeleted = 1;
						counter++;
						saveCounter = counter;
						break;
					}
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
     
    menu_header("All Contacts: \n"); // Adds header saying address book

    printf("\n=============================================================================================================="); // Top border
    printf("\n: S.No : Name                            : Phone No                        : Email ID                        :"); // Headers
    printf("\n=============================================================================================================="); // Middle border

    // read file contents till end of file
    while(fread(&information, sizeof(ContactInfo), 1, infile))
	{
        printf ("\n: %-5d: %-32s: %-32s: %-32s:",information.si_no, information.name, information.phone_numbers[0], information.email_addresses[0]);
		for(int i = 1; i < EMAIL_ID_COUNT; i++){
			printf("\n:      :                                 : %-32s: %-32s:", information.phone_numbers[i], information.email_addresses[i]);
		}
		
		printf("\n=============================================================================================================="); // Bottom border

	}
	printf("\n");
	
    // close file
    fclose (infile);
}

/*
int main(){
	AddressBook address_book;
	menu(&address_book);
} */
