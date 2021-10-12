#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "address_book_fops.h"
#include "address_book_menu.h"
#include "address_book.h"

int get_option(int type, const char *msg)
{
	printf("%s", msg);
   	switch (type)
   	{
		case NONE:
         	return e_no_opt;
      	case NUM:
         	int option;
         	scanf("%d", &option);
         	return option;
      	case CHAR:
         	char option;
         	scanf("%c", &option);
         	return option;
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
	 * Add code to list all the contacts availabe in address_book.csv file
	 * Should be menu based
	 * The menu provide navigation option if the entries increase the page size
	 */ 

	return e_success;
}

void menu_header(const char *str)
{
	fflush(stdout);

	system("clear");

	printf("#######  Address Book  #######\n");
	if (str != '\0')
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

	do
	{
		main_menu();

		option = get_option(NUM, "");

		if ((address_book-> count == 0) && (option != e_add_contact))
		{
			get_option(NONE, "No entries found!!. Would you like to add? Use Add Contacts");

			continue;
		}

		switch (option)
		{
			case e_add_contact:
				/* Add your implementation to call add_contacts function here */
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
				break;
				/* Add your implementation to call list_contacts function here */
			case e_save:
				save_file(address_book);
				break;
			case e_exit:
				break;
		}
	} while (option != e_exit);

	return e_success;
}

Status add_contacts(AddressBook *address_book)
{
	/* Add the functionality for adding contacts here */
}

Status search(const char *str, AddressBook *address_book, int loop_count, int field, const char *msg, Modes mode)
{
	menu_header("Search Result: \n"); // Adds header saying address book

    printf("=============================================================================================================="); // Top border
    printf("\n: S.No : Name                            : Phone No                        : Email ID                        :"); // Headers
    printf("\n=============================================================================================================="); // Middle border

	ContactInfo *ptr = address_book->list; // Get starting pointer
   	ContactInfo *endPtr = ptr + address_book->count; // Get ending pointer
   	unsigned int matchFound = 0;
	int match = 0;

   	for (ptr; ptr < endPtr; ptr++) {
		ContactInfo contact;

		switch (field) {
      		case 1:
     			match = strcmp(str, ptr->name[0]); // Check if the user's search matches any names
				break;
			case 2:
         		for (int phone = 0; phone < PHONE_NUMBER_COUNT; phone++) {
        	 		if (strcmp(str, ptr->phone_numbers[phone]) == 0) // Check if the user's search matches any phone numbers
           				match = 0;
     			}
         		match = 1;
				break;
    		case 3:
     			for (int email = 0; email < EMAIL_ID_COUNT; email++) {
					if (strcmp(str, ptr->email_addresses[email]) == 0) // Check if the user's search matches any email addresses
               		match = 0;
         		}
         		match = 1;
				break;
      		case 4:
         		match = atoi(str) != ptr->si_no; // Check if the user's search matches any serial numbers
				break;
   		}

      	if (match == 0) {
         	matchFound++;
         	printf("\n: %d", contact.si_no); // Prints serial number

         	printf(": %-32s", contact.name); // Prints name
         
         	printf(": %-32s", contact.phone_numbers[0]); // Prints a phone number

         	printf(": %-32s:\n", contact.email_addresses[0]); // Prints an email address

         	for (int info = 1; info < PHONE_NUMBER_COUNT; info++) {
            	printf(":      :                                 : %-32s", contact.phone_numbers[info]); // Print other phone numbers

            	printf(": %-32s:\n", contact.email_addresses[info]); // Print other email addresses
         	}
         	printf("\n=============================================================================================================="); // Bottom border
      	}
    }

    printf("%s", msg);

    if (matchFound > 0)
       return e_success; // Successful if a match was found
    else if (matchFound < 0)
       return e_fail; // Unsuccessful if no matches were found

    return e_no_match;
}

Status search_contact(AddressBook *address_book)
{
	char *name, *phoneNo, *emailId, *serialNo; 
	char *qToCancel = "Press: [q] | Cancel: ";
   	Status status;

	menu_header("Search contact by: \n"); // Adds header saying address book
   	printf("0. Back\n1. Name\n2. Phone No\n3. Email ID\n4. Serial No\n\n"); //Lists search options

   	int searchOption = get_option(NUM, "Please select an option: "); // Asks for user input

	switch (searchOption) {
   		case 0: // If user selects to go back
      		return e_back;
			break;
   		case 1: // If user selects to search by name
      		printf("Enter the Name: ");
      		scanf("%s", &name);
      		status = search(name, address_book, 0, 1, qToCancel, e_search); // Search address book based on target name
			break;
		case 2: // If user selects to search by phone number
      		printf("Enter the Phone Number: ");
      		scanf("%s", phoneNo);
      		status = search(phoneNo, address_book, 0, 2, qToCancel, e_search); // Search address book based on target phone number
			break;
		case 3: // If user selects to search by email ID
      		printf("Enter the Email ID: ");
      		scanf("%s", emailId);
      		status = search(emailId, address_book, 0, 3, qToCancel, e_search); // Search address book based on target email address
			break;
		case 4: // If user selects to search by serial number
      		printf("Enter the Serial Number: ");
      		scanf("%s", &serialNo);
      		status = search(serialNo, address_book, 0, 4, qToCancel, e_search); // Search address book based on target serial number
			break;
		default: // If user selects an invalid number
      		status = e_fail;
			break;
	}
	
   	char option = get_option(CHAR, ""); // Allow user to press q to cancel

   	if (option == 'q')
      	return status; // Leaves same status from last search because user canceled
}

Status edit_contact(AddressBook *address_book)
{
	/* Add the functionality for edit contacts here */
}

Status delete_contact(AddressBook *address_book)
{
	/* Add the functionality for delete contacts here */
}
