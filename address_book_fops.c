#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>

#include "address_book.h"

Status load_file(AddressBook *address_book)
{
	int ret;

	/* 
	 * Check for file existance
	 */
	// ret = 0 if the file exists and 1 if not
	// ret = access(DEFAULT_FILE, F_OK);

	if (ret == 0)
	{
		/* 
		 * Do the neccessary step to open the file
		 * Do error handling
		 */ 
		// address_book->fp = fopen(DEFAULT_FILE, "a+");
		
		// If file does not exist
		if (address_book->fp == NULL)
		{
			return e_fail;
		}
	}
	else
	{
		/* Create a file for adding entries */
		// address_book->fp = fopen(DEFAULT_FILE, "w+");
	}

	return e_success;
}

Status save_file(AddressBook *address_book)
{
	/*
	 * Write contacts back to file.
	 * Re write the complete file currently
	 */ 
	// address_book->fp = fopen(DEFAULT_FILE, "w");

	if (address_book->fp == NULL)
	{
		return e_fail;
	}

	/* 
	 * Add the logic to save the file
	 * Make sure to do error handling
	 */ 

	// fclose(address_book->fp);

	return e_success;
}
