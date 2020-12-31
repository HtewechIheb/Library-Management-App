#include "general_structs.h"

#ifndef BOOKS_H
#define BOOKS_H

// Utility function to free a book linked list
void free_book_list(BOOK_NODE** head);

// Function to print a book structure
void print_book(BOOK);

// Function to print a book linked list
void print_book_list(BOOK_NODE*);

// Function to read a book structure
void scan_book(BOOK*);

// Function to read books of linked list
void scan_book_list(BOOK_NODE*);

// Function to append a book to the linked list
void add_book(BOOK_NODE**, BOOK);

// Function to edit a book in the linked list
int edit_book(BOOK_NODE*, BOOK);

// Function to remove all the copies of a book
void remove_book_copies(RESERVATION_NODE**, COPY_NODE**, int);

// Function to remove the book with the specified id from the linked list
void remove_book(RESERVATION_NODE**, COPY_NODE**, BOOK_NODE**, int);

// Function to search a book by id
BOOK* search_book(BOOK_NODE*, int);

// Function to get a list of books that correspond to the searching criteria: title, subject, author and language
BOOK_NODE* search_books(BOOK_NODE*, char*, char*, char*, char*, int);

// Function to get the new id increment for the latest book
int get_new_book_id();

//******************DO NOT PASS UNINITIALISED POINTER, SET TO NULL******************
// Function to store all in memory data to file
void read_library_data_from_file(BOOK_NODE**);

//******************DO NOT PASS UNINITIALISED POINTER, SET TO NULL******************
// Function to read all file data into memory
void write_library_data_to_file(BOOK_NODE*);

#endif //BOOKS_H
