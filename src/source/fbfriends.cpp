/********************************************/
/* Author: Razvan Dinu                      */
/* Project: Projet C IG3                    */
/* Date: 13.04.2010                         */
/********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include "../headers/fbfriends.h"
#include "../headers/os_dependent.h"

// Extracts all the accounts from the given file.
// Accounts are placed in the given array (enough space is assumed).
// Returns the number of found accounts.
int identify_accounts(char* file_name, fb_account* accounts)
{
	FILE* f;					// file used for reading
	char* buf;					// buffer used for reading
	long size;					// file size
	long bytes_read;			// number of bytes read

	int count;					// number of found accounts

	// We try to open the given file
	f = fopen(file_name, "r");

	// In case of error we quit
	if (f == NULL)
	{
		perror("There was a error opening the file");
		return 0;
	}

	// Find out the size of the file
	fseek (f, 0 , SEEK_END);
	size = ftell (f);
	rewind (f);

	// Since our file is always around 200k we allocate memory for the whole file at once
	buf = (char*) malloc (sizeof(char) * (size + 1));
	if (buf == NULL)
	{
		perror("Cound not allocate memory for the buffer");
		return 0;
	}
	buf[size] = 0;

	// Copy the file into the buffer
	bytes_read = fread (buf, 1, size, f);
	if (bytes_read != size)
	{
		perror ("File read error");
		return 0;
	}

	// Create the two regular expressions used for account id and account name
	regex_t rId;
	regex_t rName;

	regcomp(&rId, "<div class=.\"ffriend clearfix.\" id=.\"f([0123456789]+).\"", REG_EXTENDED);
	regcomp(&rName, "class=.\"fname.\">([a-zA-Z \\0-9]+)<", REG_EXTENDED);

	// We need two matches: one for the whole expression, one for the expression between paranthesis
	regmatch_t matches[2];

	// Reset counters
	count = 0;
	int start = 0;

	// We start search alternatively for an id, using the regular expression for ids, and for
	// a name, using the regular expression for names. We stop when we find nothing.

	int result;
	do {
		// We continue our search starting at position 'start'
		result = regexec(&rId, buf + start, 2, matches, 0);

		if (result == 0)
		{
			// Extract the length of the id
			int len = matches[1].rm_eo - matches[1].rm_so;

			// Copy id into the current account
			strncpy(accounts[count].id, buf + start + matches[1].rm_so, len);
			accounts[count].id[len] = 0;

			// Advance and search for the name
			start += matches[1].rm_eo;
			result = regexec(&rName, buf + start, 2, matches, 0);

			if (result == 0)
			{
				// Extract the length of the name
				int len = matches[1].rm_eo - matches[1].rm_so;

				// Copy name into the current account
				strncpy(accounts[count].name, buf + start + matches[1].rm_so, len);
				accounts[count].name[len] = 0;

				// Advance our position
				start += matches[1].rm_eo;
			}

			count++;
		}

	} while (result == 0);

	// Free the regular expressions used
	regfree(&rId);
	regfree(&rName);

	// In the end we close our file
	fclose(f);

	return count;
}

// Tries to get the list of friends for a given id.
// We rely on the 'curl' tool being properly installed and accessible.
int get_friends_list(char* email, char* password, char* id, fb_account** friends)
{
	// We connect to facebook main page because we are interested in the cookies the server will send us.
	// The cookies are written in the 'cookies' file.
	if (exec_and_wait("curl -D cookies --user-agent \"Mozilla/4.0\" http://www.facebook.com/ -o facebook.html"))
		return 0;

	// We send the user and the password and save the new set of cookies in 'cookies_auth'.
	char cmd[1024];
	sprintf(cmd, "curl -D cookies_auth -b cookies -d \"email=%s&pass=%s\" --insecure --user-agent \"Mozilla/4.0\" https://login.facebook.com/login.php?login_attempt=1 -o facebook.html", email, password);
	if (exec_and_wait(cmd))
		return 0;

	// Prepare the final request: the list of friends.
	sprintf(cmd, "curl -b cookies_auth --user-agent \"Mozilla/4.0\" http://www.facebook.com/friends/?id=%s -o friendslist.html", id);

	// Make the request.
	if (exec_and_wait(cmd))
		return 0;

	// We don't know how many friends there are so we allocate memory for a maximum of 2000 friends
	fb_account *accounts = (fb_account*) malloc(sizeof(fb_account) * 2000);
	int n_accounts = identify_accounts("friendslist.html", accounts);

	// Free unnecessary memory
	accounts = (fb_account*)realloc(accounts, sizeof(fb_account) * n_accounts);

	// Set the return value for the accounts and return the number
	*friends = accounts;
	return n_accounts;
}

/*
// Start here
int main(int argc, char** argv)
{
	fb_account* accounts;	// accounts array after retrival
	int n_accounts;			// number of found accounts

	// Check proper usage
	if (argc != 4)
	{
		printf("Usage: %s email password facebook_id\n", argv[0]);
		return 1;
	}

	// Get the list of friends for the given account
	n_accounts = get_friends_list(argv[1], argv[2], argv[3], &accounts);

	// Show the list of friends
	if (n_accounts > 0)
	{
		printf("Found %d accounts.\n", n_accounts);

		for (int i = 0; i < n_accounts; i++)
			printf("%s: %s\n", accounts[i].id, accounts[i].name);
	}

	return 0;
}
*/
