/********************************************/
/* Author: Razvan Dinu                      */
/* Project: Projet C IG3                    */
/* Date: 13.04.2010                         */
/********************************************/

#ifndef FBFRIENDS_H_INCLUDED
#define FBFRIENDS_H_INCLUDED

// Information about a facebook account.
// We are only interested in the id and the name.
struct facebook_account{
	char id[20];
	char name[50];
};

// Define a shortcut
typedef struct facebook_account fb_account;

int identify_accounts(char* file_name, fb_account* accounts);
int get_friends_list(char* email, char* password, char* id, fb_account** friends);

#endif // FBFRIENDS_H_INCLUDED
