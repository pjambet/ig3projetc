/********************************************/
/* Author: Razvan Dinu                      */
/* Project: Projet C IG3                    */
/* Date: 13.04.2010                         */
/********************************************/

#ifndef __FBFRIENDS_H__
#define __FBFRIENDS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#include "../headers/os_dependent.h"

// Information about a facebook account.
// We are only interested in the id and the name.
struct facebook_account{
	char id[20];
	char name[50];
};

// Define a shortcut
typedef struct facebook_account fb_account;

// Extracts all the accounts from the given file.
// Accounts are placed in the given array (enough space is assumed).
// Returns the number of found accounts.
int identify_accounts(char* file_name, fb_account* accounts);

int get_friends_list(char* email, char* password, char* id, fb_account** friends);

#endif
