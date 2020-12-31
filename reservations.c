#include <string.h>
#include "books.h"
#include "accounts.h"
#include "copies.h"
#include "reservations.h"
#include "general.h"

void free_reservation_list(RESERVATION_NODE** head)
{
    RESERVATION_NODE *node_to_delete; // Variable to hold the node to delete in order to free it

    // If the linked list is empty, return
    if(!*head)
    {
        printf("\nThere is no list!");
        return;
    }

    // Set head to next node and then free the node that it previously occupied
    // Repeat untill head is NULL
    while(*head)
    {
        node_to_delete = *head;
        *head = node_to_delete->next;
        free(node_to_delete);
        node_to_delete = NULL;
    }
}

int get_account_reservations_nb(RESERVATION_NODE* head, int id_user)
{
    RESERVATION_NODE* current;
    int result = 0; // Variable to store number of account reservations

    if(!head)
    {
        printf("\nThere are no book reservations!");
        return -1;
    }

    for(current = head; current; current = current->next)
    {
        if(current->data.id_user == id_user)
        {
            result++;
        }
    }
    return result;
}

void print_reservation(RESERVATION reservation)
{
    char reservation_date_string[30];   //
    char due_date_string[30];           //
    struct tm reservation_date_struct;  // Variables to handle dates
    struct tm due_date_struct;          //

    // Get strings of dates
    reservation_date_struct = *gmtime(&reservation.reservation_date);
    due_date_struct = *gmtime(&reservation.due_date);
    strftime(reservation_date_string, sizeof(reservation_date_string), "%A, %d %B %Y", &reservation_date_struct);
    strftime(due_date_string, sizeof(due_date_string), "%A, %d %B %Y", &due_date_struct);

    printf("\nThe reservation id: %d", reservation.id);
    printf("\nThe reservation copy: %d", reservation.id_copy);
    printf("\nThe reservation user: %d", reservation.id_user);
    printf("\nThe reservation date: %s", reservation_date_string);
    printf("\nThe reservation due date: %s", due_date_string);
    putchar('\n');
}

void print_reservation_list(RESERVATION_NODE* head)
{
    RESERVATION_NODE* current; // Temporary reservation node to loop through the linked list

    if(!head)
    {
        printf("\nThere are no book reservations!");
        return;
    }

    for(current = head; current; current = current->next)
    {
        print_reservation(current->data);
    }
}

void scan_reservation(RESERVATION* reservation)
{
    struct tm buffer; // Variable to handle dates
    int reservation_days;

    printf("\nType the reservation id: ");
    scanf("%d", &reservation->id);
    printf("\nType the reservation copy: ");
    scanf("%d", &reservation->id_copy);
    printf("\nType the reservation user: ");
    scanf("%d", &reservation->id_user);
    printf("\nType the reservation days: ");
    scanf("%d", &reservation_days);
    // Add reservation_days to reservation date and store it in due date
    reservation->reservation_date = time(NULL);
    buffer = *gmtime(&reservation->reservation_date);
    buffer.tm_mday += reservation_days;
    reservation->due_date = mktime(&buffer);
    putchar('\n');
    //DO NOT FREE STATIC STORED VARIABLES (buffer);
}

void scan_reservation_list(RESERVATION_NODE* head)
{
    RESERVATION_NODE* current;

    if(!head)
    {
        printf("\nThere is no list!");
        return;
    }

    for(current = head; current; current = current->next)
    {
        scan_reservation(&current->data);
    }
}

void add_reservation_to_list(RESERVATION_NODE** head_res, COPY_NODE* head_copy, RESERVATION reservation)
{
    RESERVATION_NODE* current;
    RESERVATION_NODE* node = (RESERVATION_NODE*)malloc(sizeof(RESERVATION_NODE)); // Reservation node to append to the linked list

    if(!node)
    {
        printf("\nError! Could not allocate memory!");
        return;
    }
    node->data = reservation;
    node->next = NULL;

    // Update the reserved copy status
    set_copy_status(head_copy, node->data.id_copy, RESERVED);

    // Append new node to linked list, set it as the head if the linked list in empty
    if(!*head_res)
    {
        *head_res = node;
    }
    else
    {
        current = *head_res;
        while(current->next != NULL)
        {
            current = current->next;
        }
        current->next = node;
    }

    write_reservations_data_to_file(*head_res);
}

int edit_reservation(RESERVATION_NODE* head, int id, RESERVATION reservation)
{
    RESERVATION_NODE* current;
    int edited = 0; // Variable indicating wether or not the edition succeeded

    if(!head)
    {
        printf("\nThere are no book reservations!");
        return -1;
    }

    for(current = head; current; current = current->next)
    {
        if(current->data.id == id)
        {
            current->data = reservation;
            write_reservations_data_to_file(head);
            edited = 1;
            break;
        }
    }
    return edited;
}

void remove_reservation_from_list(RESERVATION_NODE** head_res, COPY_NODE* head_copy, int id)
{
    RESERVATION_NODE* current;
    RESERVATION_NODE* node_to_delete;

    if(!*head_res)
    {
        printf("\nThere are no book reservations!");
        return;
    }

    // Check if head has the id, if it does, set the associated copy status to FREE, set head to next node and then free the node that it previously occupied
    // Repeat until head no longer has the id or head is NULL
    while(*head_res && ((*head_res)->data.id == id))
    {
        set_copy_status(head_copy, (*head_res)->data.id_copy, FREE);
        node_to_delete = *head_res;
        *head_res = node_to_delete->next;
        free(node_to_delete);
        node_to_delete = NULL;
    }

    // Check if next node has the id, if it does delete it
    // Only pass to the the next node if it doesn't have the id
    for(current = *head_res; current && current->next; )
    {
        if(current->next->data.id == id)
        {
            set_copy_status(head_copy, current->next->data.id_copy, FREE);
            node_to_delete = current->next;
            current->next = node_to_delete->next;
            free(node_to_delete);
            node_to_delete = NULL;
        }
        else
        {
            current = current->next;
        }
    }

    write_reservations_data_to_file(*head_res);
}

RESERVATION* search_reservation(RESERVATION_NODE* head, int id)
{
    RESERVATION_NODE* current;
    RESERVATION* result = NULL; // Variable to hold search result

    if(!head)
    {
        printf("\nThere are no book reservations!");
        return NULL;
    }

    for(current = head; current; current = current->next)
    {
        if(current->data.id == id)
        {
            result = (RESERVATION*)malloc(sizeof(RESERVATION));
            if(!result)
            {
                printf("\nError! Could not allocate memory!");
                return NULL;
            }
            *result = current->data;
            return result;
        }
    }
    return NULL;
}

RESERVATION_NODE* search_reservations_by_book(RESERVATION_NODE* head_res, COPY_NODE* head_copy, BOOK_NODE* head_book, char* title, char* subject, char* author, char* language, int number_of_pages)
{
    RESERVATION_NODE* current;
    RESERVATION_NODE* current_result; // Temporary node used to construct search result linked list
    RESERVATION_NODE* node = NULL; // Linked list to hold the search result
    RESERVATION_NODE* result = NULL; // Temporary node used to append to search result linked list
    char* title_lower, *subject_lower, *author_lower, *language_lower, *node_title_lower, *node_subject_lower, *node_author_lower, *node_language_lower; // Variables to hold search strings
    COPY* copy; // Variable to hold the reserved copy
    BOOK* book; // Variable to hold the book to which the reserved copy is associated

    if(!head_res)
    {
        printf("\nThere are no book reservations!");
        return NULL;
    }

    if(!head_copy)
    {
        printf("\nThere are no book copies!");
        return NULL;
    }

    if(!head_book)
    {
        printf("\nThere are no books!");
        return NULL;
    }

    // Transform search entries to lowercase
    title_lower = str_tolower(title);
    subject_lower = str_tolower(subject);
    author_lower = str_tolower(author);
    language_lower = str_tolower(language);

    for(current = head_res; current; current = current->next)
    {
        // Get reserved copy
        copy = search_copy(head_copy, current->data.id_copy);
        // Get book to which reserved copy is associated
        book = search_book(head_book, copy->id_book);

        // Transform node data to lowercase
        node_title_lower = str_tolower(book->title);
        node_subject_lower = str_tolower(book->subject);
        node_author_lower = str_tolower(book->author);
        node_language_lower = str_tolower(book->language);

        if((!title || strstr(node_title_lower, title_lower)) && (!subject || strstr(node_subject_lower, subject_lower))
        && (!author || strstr(node_author_lower, author_lower)) && (!language || strstr(node_language_lower, language_lower)) && ((number_of_pages == 0) || book->number_of_pages == number_of_pages))
        {
            // If the node passes the search, copy its data to a newly constructed node
            node = (RESERVATION_NODE*)malloc(sizeof(RESERVATION_NODE));
            if(!node)
            {
                printf("\nError! Could not allocate memory!");
                return NULL;
            }
            node->data = current->data;
            node->next = NULL;

            // Append newly constructed node to search result linked list
            if(!result)
            {
                // If the linked list head is null, assign it to newly constructed node
                current_result = result = node;
            }
            else
            {
                // Link newly constructed node to previous one and step into it
                current_result->next = node;
                current_result = current_result->next;
            }
        }

        // Free memory
        free(copy);
        free(book);
        free(node_title_lower);
        free(node_subject_lower);
        free(node_author_lower);
        free(node_language_lower);
    }

    // Free memory
    free(title_lower);
    free(subject_lower);
    free(author_lower);
    free(language_lower);

    return result;
}

RESERVATION_NODE* search_reservations(RESERVATION_NODE* head, int id_copy, int id_user, time_t reservation_date, time_t due_date)
{
    RESERVATION_NODE* current;
    RESERVATION_NODE* current_result; // Temporary node used to construct search result linked list
    RESERVATION_NODE* node = NULL; // Linked list to hold the search result
    RESERVATION_NODE* result = NULL; // Temporary node used to append to search result linked list

    time_t current_reservation_date;                //
    time_t current_due_date;                        //
                                                    //
    struct tm current_reservation_date_struct = {}; // Variables to handle dates
    struct tm current_due_date_struct = {};         //
                                                    //
    struct tm buffer;                               //

    if(!head)
    {
        printf("\nThere are no book reservations!");
        return NULL;
    }

    for(current = head; current; current = current->next)
    {

        // Take into consideration only the day, month and year of reservation date for searching
        buffer = *gmtime(&current->data.reservation_date);

        current_reservation_date_struct.tm_mday = buffer.tm_mday;
        current_reservation_date_struct.tm_mon = buffer.tm_mon;
        current_reservation_date_struct.tm_year = buffer.tm_year;

        // Take into consideration only the day, month and year of due date for searching
        buffer = *gmtime(&current->data.due_date);

        current_due_date_struct.tm_mday = buffer.tm_mday;
        current_due_date_struct.tm_mon = buffer.tm_mon;
        current_due_date_struct.tm_year = buffer.tm_year;

        // Transform dates into time_t for comparison
        current_reservation_date = mktime(&current_reservation_date_struct);
        current_due_date = mktime(&current_due_date_struct);

        if(((id_copy == -1) || (current->data.id_copy == id_copy)) && ((id_user == -1) || (current->data.id_user == id_user))
            && (((int)reservation_date == -1) || (current_reservation_date == reservation_date)) && (((int)due_date == -1) || (current_due_date == due_date)))
            {
            // If the node passes the search, copy its data to a newly constructed node
            node = (RESERVATION_NODE*)malloc(sizeof(RESERVATION_NODE));
            if(!node)
            {
                printf("\nError! Could not allocate memory!");
                return NULL;
            }
            node->data = current->data;
            node->next = NULL;

            // Append newly constructed node to search result linked list
            if(!result)
            {
                // If the linked list head is null, assign it to newly constructed node
                current_result = result = node;
            }
            else
            {
                // Link newly constructed node to previous one and step into it
                current_result->next = node;
                current_result = current_result->next;
            }
        }
    }

    return result;
}

int get_new_reservation_id()
{
    int max_id = 0; // Integer to hold newest id increment
    FILE* fptr;
    RESERVATION* buffer = (RESERVATION*)malloc(sizeof(RESERVATION)); // Temporary reservation pointer used as a buffer to read from file

    fptr = fopen("reservations", "rb");
    if(!fptr)
    {
        printf("Error! Could not open file.");
        return 0;
    }

    while(fread(buffer, sizeof(RESERVATION), 1, fptr) == 1)
    {
        // Get the largest id of the stored reservations
        if(buffer->id > max_id)
        {
            max_id = buffer->id;
        }
    }

    free(buffer);
    fclose(fptr);

    // Increment largest id by 1 and return it
    return max_id + 1;
}

int reserve_copy(RESERVATION_NODE** head_res, COPY_NODE* head_copy, int id_copy, int id_user, int nb_days)
{
    RESERVATION reservation; // Variable to hold newly created reservation
    struct tm buffer; // Variable to handle dates
    int reserved = 0; // Variable indicating wether or not the reservation succeeded

    reservation.id = get_new_reservation_id();
    reservation.id_copy = id_copy;
    reservation.id_user = id_user;
    reservation.reservation_date = time(NULL);
    reservation.due_date = time(NULL);
    // Add reservation days to reservation date and set it to due date
    buffer = *gmtime(&reservation.reservation_date);
    buffer.tm_mday += nb_days;
    reservation.due_date = mktime(&buffer);

    // Add reservation to file
    add_reservation_to_list(head_res, head_copy, reservation);

    return reserved;
}

void read_reservations_data_from_file(RESERVATION_NODE** head)
{
    FILE* fptr;
    RESERVATION_NODE* current;
    RESERVATION* buffer = (RESERVATION*)malloc(sizeof(RESERVATION)); //Temporary copy pointer used as a buffer to read from file
    RESERVATION_NODE* node = NULL; // Temporary node used to construct reservation linked list

    fptr = fopen("reservations", "rb");
    if(!fptr)
    {
        printf("Error! Could not open file.");
        return;
    }

    while(fread(buffer, sizeof(RESERVATION), 1, fptr) == 1)
    {
        node = (RESERVATION_NODE*)malloc(sizeof(RESERVATION_NODE));
        if(!node)
        {
            printf("\nError! Could not allocate memory!");
            return;
        }
        node->data = *buffer;
        node->next = NULL;
        if(!*head)
        {
            //If the linked list head is null, assign it to new node
            current = *head = node;
        }
        else
        {
            //Link new node to previous one and step into it
            current = current->next = node;
        }
    }

    free(buffer);
    fclose(fptr);
}

void write_reservations_data_to_file(RESERVATION_NODE* head)
{
    FILE* fptr;
    RESERVATION_NODE* current; //Temporary reservation node to loop through the linked list

    fptr = fopen("reservations", "wb");
    if(!fptr)
    {
        printf("Error! Could not open file.");
        return;
    }

    for(current = head; current; current = current->next)
    {
        fwrite(&current->data, sizeof(RESERVATION), 1, fptr);
    }

    fclose(fptr);
}



