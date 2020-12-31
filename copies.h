#include "general_structs.h"

#ifndef COPIES_H
#define COPIES_H

// Utility function to free a copy linked list
void free_copy_list(COPY_NODE** head);

// Utility function to get string of a COPY_STATUS
char* get_copy_status(COPY_STATUS);

// Function to set status of the copy with the specified id
int set_copy_status(COPY_NODE *head, int id, COPY_STATUS status);

// Function to get the number of copies of the book with the specified id
int get_book_copies_nb(COPY_NODE* head, int id_book);

// Function to get the number of copies with the specified status of the book with the specified id
int get_book_copies_nb_with_status(COPY_NODE* head, int id_book, COPY_STATUS status);

// Function to get a free copy of the book with the specified id
COPY* get_book_copy(COPY_NODE*, int);

// Function to print a copy structure
void print_copy(COPY copy);

// Function to print a copy linked list
void print_copy_list(COPY_NODE* head);

// Function to read a copy structure
void scan_copy(COPY* copy);

// Function to read copies of linked list
void scan_copy_list(COPY_NODE* head);

// Function to append a copy to the linked list
void add_copy_to_list(COPY_NODE** head, COPY copy);

// Function to edit a copy in the linked list
int edit_copy(COPY_NODE* head, int id, COPY copy);

// Function to remove the reservation of a copy
void remove_copy_reservation(RESERVATION_NODE**, int);

// Function to remove the copy with the specified id from the linked list
void remove_copy_from_list(RESERVATION_NODE**, COPY_NODE**, int);

// Function to search a copy by id
COPY* search_copy(COPY_NODE*, int);

// Function to search a copy by barcode
COPY* search_copy_by_barcode(COPY_NODE*, int);

// Function to get a list of copies that correspond to the searching criteria: barcode, associated book id, status
COPY_NODE* search_copies(COPY_NODE*, int, int, COPY_STATUS);

// Function to get the new id increment for the latest copy
int get_new_copy_id();

//******************DO NOT PASS UNINITIALISED POINTER, SET TO NULL******************
// Function to store all in memory data to file
void read_copies_data_from_file(COPY_NODE**);

//******************DO NOT PASS UNINITIALISED POINTER, SET TO NULL******************
// Function to read all file data into memory
void write_copies_data_to_file(COPY_NODE*);

#endif //COPIES_H
