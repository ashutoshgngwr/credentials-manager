#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <stdarg.h>
#include "base64.h"


/*All the constants are to be defined here (in Utils.h). */

#define WELCOME_MESSAGE "Credential Manager\n"
#define ABOUT_SOFTWARE "Credential Manager is an utility tool to keep all your username/password\nfor different websites/services at one place, secured using a master password.\n"
#define ABOUT_AUTHOR "Presented By\n1. Ashutosh Gangwar\n2. Ashwini Maurya\n3. Ashvik Sirohi\n"
#define INIT_SOFT_MESSAGE "A few things before we get started...\n"
#define CREATE_PASSWORD_MESSAGE "Create a password : "
#define CONFIRM_PASSWORD_MESSAGE "Confirm password : "
#define ENTER_PASSWORD_MESSAGE "Enter your password : "
#define PASSWORD_MISMATCH_MESSAGE "Passwords do not match. Try again!\n"
#define INVALID_PASSWORD_MESSAGE "Invalid Password! Try again!\n"
#define MENU_OPTIONS_MESSAGE "Press\n1. Add an entry\n2. Search an entry\n3. About\n4. Exit\n"
#define ADD_ENTRY_MESSAGE "Add an entry\n"
#define ENTER_WEBSITE_MESSAGE "Website/Service : "
#define ENTER_USERNAME_MESSAGE "Username for %s : "
#define ENTER_PASS_MESSAGE "Password for %s : "
#define INVALID_INPUT "Invalid input provided! Try again!\n"
#define CONFIRM_ADD_ENTRY_MESSAGE "Adding entry for website: %s with\nusername: %s and password: %s\n\nPress Enter to confirm or any other key to retry!\n"
#define ENTRY_ADDED_MESSAGE "Entry added!\n"
#define CONTINUE_MESSAGE "Press any key to continue...\n"
#define SEARCH_ENTRY_MESSAGE "Search Entry\n"
#define WEBSITE_SEARCH_MESSAGE "Enter website/service to be searched : "
#define NO_RESULTS_FOUND_MESSAGE "No results found!\nPress ENTER to try again or any other key to go to menu!"
#define EDIT_REMOVE_ENTRY_MESSAGE "Press E to edit, R to remove entry or any other key\nto go back to menu!\n"
#define REMOVE_ENTRY_MESSAGE "Enter SN. of entry to be removed : "
#define REMOVE_ENTRY_CONFIRM_MESSAGE "Press ENTER to confirm deletion of url: %s\nor press any other key to abort!\n"
#define EDIT_ENTRY_MESSAGE "Enter SN. of entry to be edited : "
#define ENTRY_DELETED_SUCCESSFULLY "Entry deleted successfully!\n"
#define EMPTY_UNCHANGED_MESSAGE "Leave fields empty to keep them unchanged!\n"
#define ENTRY_EDITED_SUCCESSFULLY "Entry edited successfully!\n"
#define ENTRY_EDIT_CONFIRM_MESSAGE "Press ENTER to confirm changes from url: %s\nusername: %s password: %s to\nurl: %s username: %s password: %s\nor any other key to abort!\n"
#define GOODBYE_MESSAGE "Goodbye!\n"

void clear_screen();
void pause_process();
char *process_buffer();
char *input_text();
char *input_password();
char getch();
char *str_copy(char*);
char *base64_encode(unsigned char*);
unsigned char *base64_decode(char*);
size_t hash(const char*);
void strrev(char*);
void encrypt(char*, char*);
void decrypt(char*, char*);
void dump(char*, ...);

#endif