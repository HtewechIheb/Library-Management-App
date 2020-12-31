#include "general_structs.h"

#ifndef ACCOUNTS_H
#define ACCOUNTS_H

// Utility function to free an account linked list
void free_account_list(ACCOUNT_NODE** head);

// Utility function to hash passwords using OpenSSL SHA-256
void hash_password(char*, unsigned char*, unsigned int*);

// Utility function to get the string of an ACCOUNT_TYPE
char* get_account_type(ACCOUNT_TYPE);

// Function to create a new account and return it
ACCOUNT new_account(char* email, char* password, char* name, char* address, int phone, ACCOUNT_TYPE type);

// Function to print an account structure
void print_account(ACCOUNT);

// Function to print an account linked list
void print_account_list(ACCOUNT_NODE*);

// Function to read an account structure
void scan_account(ACCOUNT*);

// Function to read accounts of linked list
void scan_account_list(ACCOUNT_NODE*);

/********************************LIST FUNCTIONS ARE ONLY USED FOR TEST PURPOSES*****************************/
/*****************ACCOUNTS ARE MANIPULATED DIRECTLY IN ENCRYPTED FILES FOR SECURITY PURPOSES****************/
/*********************THE CODE IN LIST FUNCTIONS AND FILE FUNCTIONS IS PRETTY MUCH THE SAME*****************/
/*********************************THEREFORE ONLY FILE FUNCTIONS ARE DOCUMENTED******************************/

// Function to append an account to the linked list
void add_account_to_list(ACCOUNT_NODE**, ACCOUNT);

// Function to append an account to the accounts file
void add_account_to_file(ACCOUNT);

// Function to edit an account in the linked list
int edit_account_in_list(ACCOUNT_NODE*, ACCOUNT);

// Function to edit an account in the accounts file
int edit_account_in_file(ACCOUNT);

// Function to remove all account reservations
void remove_account_reservations(RESERVATION_NODE**, COPY_NODE*, int);

// Function to remove the account with the specified id from the linked list
void remove_account_from_list(ACCOUNT_NODE**, RESERVATION_NODE**, COPY_NODE*, int);

// Function to remove the account with the specified id from the accounts file
void remove_account_from_file(RESERVATION_NODE**, COPY_NODE*, int);

// Function to search an account by id in linked list
ACCOUNT* search_account_in_list(ACCOUNT_NODE*, int);

// Function to search an account by id in file
ACCOUNT* search_account_in_file(int);

// Function to get a list of accounts that correspond to the searching criteria: email, name, address, phone and type in linked list
ACCOUNT_NODE* search_accounts_in_list(ACCOUNT_NODE*, char*, char*, char*, int, ACCOUNT_TYPE type);

// Function to get a list of accounts that correspond to the searching criteria: email, name, address, phone and type in file
ACCOUNT_NODE* search_accounts_in_file(char*, char*, char*, int, ACCOUNT_TYPE type);

// Function to attempt authentication from linked list
ACCOUNT* authenticate_from_list(ACCOUNT_NODE*, char*, char*);

// Function to attempt authentication from file
ACCOUNT* authenticate_from_file(char*, char*);

// Function to get the new id increment for the latest account
int get_new_account_id();

//******************DO NOT PASS UNINITIALISED POINTER, SET TO NULL******************
// Function to store all in memory accounts data to file
void read_account_data_from_file(ACCOUNT_NODE**);

//******************DO NOT PASS UNINITIALISED POINTER, SET TO NULL******************
// Function to read all accounts file data into memory
void write_account_data_to_file(ACCOUNT_NODE*);

#endif //ACCOUNTS_H
