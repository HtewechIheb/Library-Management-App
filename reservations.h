#include "general_structs.h"

#ifndef RESERVATIONS_H
#define RESERVATIONS_H

// Utility function to free a reservation linked list
void free_reservation_list(RESERVATION_NODE** head);

// Function to get the number of reservations of the account with the specified id
int get_account_reservations_nb(RESERVATION_NODE*, int);

// Function to print a reservation structure
void print_reservation(RESERVATION reservation);

// Function to print a reservation linked list
void print_reservation_list(RESERVATION_NODE* head);

// Function to read a reservation structure
void scan_reservation(RESERVATION* reservation);

// Function to read reservations of linked list
void scan_reservation_list(RESERVATION_NODE* head);

// Function to append a reservation to the linked list
void add_reservation_to_list(RESERVATION_NODE** head, COPY_NODE*, RESERVATION reservation);

// Function to edit a reservation in the linked list
int edit_reservation(RESERVATION_NODE* head, int id, RESERVATION reservation);

// Function to remove the reservation with the specified id from the linked list
void remove_reservation_from_list(RESERVATION_NODE** head, COPY_NODE*, int id);

// Function to search a reservation by id
RESERVATION* search_reservation(RESERVATION_NODE* head, int id);

// Function to search a reservation by the book associated to its copy
RESERVATION_NODE* search_reservations_by_book(RESERVATION_NODE*, COPY_NODE*, BOOK_NODE*, char*, char*, char*, char*, int);

// Function to get a list of books that correspond to the searching criteria: copy id, user id, reservation date, due date
RESERVATION_NODE* search_reservations(RESERVATION_NODE*, int, int, time_t, time_t);

// Function to get the new id increment for the latest reservation
int get_new_reservation_id();

// Function to reserve a copy to a user for a certain duration
int reserve_copy(RESERVATION_NODE** head_res, COPY_NODE* head_copy, int id_copy, int id_user, int nb_days);

//******************DO NOT PASS UNINITIALISED POINTER, SET TO NULL******************
// Function to store all in memory data to file
void read_reservations_data_from_file(RESERVATION_NODE** head);

//******************DO NOT PASS UNINITIALISED POINTER, SET TO NULL******************
// Function to read all file data into memory
void write_reservations_data_to_file(RESERVATION_NODE* head);

#endif //RESERVATIONS_H
