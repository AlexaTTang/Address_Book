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
	if((fp = fopen(DEFAULT_FILE, "a+")) == NULL)
	{	
		printf("File cannot be opened \n");
		return e_fail;
	}
	fp = fopen(DEFAULT_FILE, "a");
	printf("Enter username : ");
	scanf("\n%s", info.name);
	printf("Enter phone no : ");
	scanf("%s", info.phone_numbers);
	printf("Enter email id : ");
	scanf("%s", info.email_addresses);
	fwrite(&info, sizeof(info), 1, fp);
	fclose(fp);

	return e_success;
}

Status search(const char *str, AddressBook *address_book, int loop_count, int field, const char *msg, Modes mode)
{
	/* Add the functionality for adding contacts here */

}

Status search_contact(AddressBook *address_book)
{
	/* Add the functionality for search contacts here */
}

Status edit_contact(AddressBook *address_book)
{
	/* Add the functionality for edit contacts here */
}

Status delete_contact(AddressBook *address_book)
{
	/* Add the functionality for delete contacts here */
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
        printf ("Name = %s  Phone Number = %s  Email address %s\n", information.name, information.phone_numbers, information.email_addresses);
 
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