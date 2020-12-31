#include <string.h>
#include "books.h"
#include "accounts.h"
#include "copies.h"
#include "reservations.h"
#include "general.h"

void free_copy_list(COPY_NODE** head)
{
    COPY_NODE *node_to_delete; // Variable to hold the node to delete in order to free it

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

char* get_copy_status(COPY_STATUS status)
{
    switch(status)
    {
        case FREE: return "Free";
        case RESERVED: return "Reserved";
    }
}

int set_copy_status(COPY_NODE *head, int id, COPY_STATUS status)
{
    COPY_NODE* current; // Temporary book node to loop through the linked list
    int edited = 0; // Variable indicating wether or not the edition succeeded

    if(!head)
    {
        printf("\nThere are no book copies!");
        return 0;
    }

    for(current = head; current; current = current->next)
    {
        if(current->data.id == id)
        {
            current->data.status = status;
            write_copies_data_to_file(head);
            edited = 1;
            break;
        }
    }
    return edited;
}

int get_book_copies_nb(COPY_NODE* head, int id_book)
{
    COPY_NODE* current;
    int result = 0; // Variable to store number of book copies

    if(!head)
    {
        printf("\nThere are no book copies!");
        return -1;
    }

    for(current = head; current; current = current->next)
    {
        if(current->data.id_book == id_book)
        {
            result++;
        }
    }
    return result;
}

int get_book_copies_nb_with_status(COPY_NODE* head, int id_book, COPY_STATUS status)
{
    COPY_NODE* current;
    int result = 0; // Variable to store number of book copies who have the specified status

    if(!head)
    {
        printf("\nThere are no book copies!");
        return -1;
    }

    for(current = head; current; current = current->next)
    {
        if(((current->data.id_book) == id_book) && ((COPY_STATUS)current->data.status == status))
        {
            result++;
        }
    }
    return result;
}

COPY* get_book_copy(COPY_NODE* head, int id_book)
{
    COPY_NODE* current;
    COPY* result = NULL; // Variable to store the free copy

    if(!head)
    {
        printf("\nThere are no book copies!");
        return NULL;
    }

    for(current = head; current; current = current->next)
    {
        if((current->data.id_book == id_book) && (current->data.status == FREE))
        {
            result = (COPY*)malloc(sizeof(COPY));
            if(!result)
            {
                printf("\nError, could not allocate memory!");
                return NULL;
            }
            *result = current->data;
            break;
        }
    }
    return result;
}

void print_copy(COPY copy)
{
    printf("\nThe copy id: %d", copy.id);
    printf("\nThe copy barcode: %d", copy.barcode);
    printf("\nThe copy book reference: %d", copy.id_book);
    printf("\nThe copy status: %d", copy.status);
    putchar('\n');
}

void print_copy_list(COPY_NODE* head)
{
    COPY_NODE* current;

    if(!head)
    {
        printf("\nThere are no book copies!");
        return;
    }

    for(current = head; current; current = current->next)
    {
        print_copy(current->data);
    }
}

void scan_copy(COPY* copy)
{
    printf("\nType the copy id: ");
    scanf("%d", &copy->id);
    printf("\nType the copy barcode: ");
    scanf("%d", &copy->barcode);
    printf("\nType the copy book reference: ");
    scanf("%d", &copy->id_book);
    printf("\nType the copy status: ");
    scanf("%d", &copy->status);
    putchar('\n');
}

void scan_copy_list(COPY_NODE* head)
{
    COPY_NODE* current;

    if(!head)
    {
        printf("\nThere is no list!");
        return;
    }

    for(current = head; current; current = current->next)
    {
        scan_copy(&current->data);
    }
}

void add_copy_to_list(COPY_NODE** head, COPY copy)
{
    COPY_NODE* current;
    COPY_NODE* node = (COPY_NODE*)malloc(sizeof(COPY_NODE)); // Copy node to append to the linked list

    if(!node)
    {
        printf("\nError! Could not allocate memory!");
        return;
    }
    node->data = copy;
    node->next = NULL;

    // Append new node to linked list, set it as the head if the linked list in empty
    if(!*head)
    {
        *head = node;
    }
    else
    {
        current = *head;
        while(current->next != NULL)
        {
            current = current->next;
        }
        current->next = node;
    }

    write_copies_data_to_file(*head);
}

int edit_copy(COPY_NODE* head, int id, COPY copy)
{
    COPY_NODE* current;
    int edited = 0; // Variable indicating wether or not the edition succeeded

    if(!head)
    {
        printf("\nThere are no book copies!");
        return 0;
    }

    for(current = head; current; current = current->next)
    {
        if(current->data.id == id)
        {
            current->data = copy;
            write_copies_data_to_file(head);
            edited = 1;
            break;
        }
    }
    return edited;
}

void remove_copy_reservation(RESERVATION_NODE** head, int id)
{
    RESERVATION_NODE* current;
    RESERVATION_NODE* node_to_delete;

    if(!*head)
    {
        printf("\nThere are no book reservations!");
        return;
    }

    // Check if head has the copy id, if it does, delete the reservation, set head to next node and then free the node that it previously occupied
    // Repeat until head no longer has the copy id or head is NULL
    while(*head && ((*head)->data.id_copy == id))
    {
        node_to_delete = *head;
        *head = node_to_delete->next;
        free(node_to_delete);
        node_to_delete = NULL;
    }

    // Check if next node has the copy id, if it does delete it
    // Only pass to the the next node if it doesn't have the copy id
    for(current = *head; current && current->next; )
    {
        if(current->next->data.id_copy == id)
        {
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

    write_reservations_data_to_file(*head);
}

void remove_copy_from_list(RESERVATION_NODE** head_res, COPY_NODE** head_copy, int id)
{
    COPY_NODE* current;
    COPY_NODE* node_to_delete;

    if(!*head_copy)
    {
        printf("\nThere are no book copies!");
        return;
    }

    // Check if head has the id, if it does, delete the copy reservation, set head to next node and then free the node that it previously occupied
    // Repeat until head no longer has the id or head is NULL
    while(*head_copy && ((*head_copy)->data.id == id))
    {
        remove_copy_reservation(head_res, id);
        node_to_delete = *head_copy;
        *head_copy = node_to_delete->next;
        free(node_to_delete);
        node_to_delete = NULL;
    }

    // Check if next node has the id, if it does delete it
    // Only pass to the the next node if it doesn't have the id
    for(current = *head_copy; current && current->next; )
    {
        if(current->next->data.id == id)
        {
            remove_copy_reservation(head_res, id);
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

    write_copies_data_to_file(*head_copy);
}

COPY* search_copy(COPY_NODE* head, int id)
{
    COPY_NODE* current;
    COPY* result = NULL; // Variable to hold search result

    if(!head)
    {
        printf("\nThere are no book copies!");
        return NULL;
    }

    for(current = head; current; current = current->next)
    {
        if(current->data.id == id)
        {
            result = (COPY*)malloc(sizeof(COPY));
            if(!result)
            {
                printf("\nError! Could not allocate memory!");
                return NULL;
            }
            *result = current->data;
            break;
        }
    }

    return result;
}

COPY* search_copy_by_barcode(COPY_NODE* head, int barcode)
{
    COPY_NODE* current;
    COPY* result = NULL; // Variable to hold search result

    if(!head)
    {
        printf("\nThere are no book copies!");
        return NULL;
    }

    for(current = head; current; current = current->next)
    {
        if(current->data.barcode == barcode)
        {
            result = (COPY*)malloc(sizeof(COPY));
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

COPY_NODE* search_copies(COPY_NODE* head, int barcode, int id_book, COPY_STATUS status)
{
    COPY_NODE* current;
    COPY_NODE* current_result; // Temporary node used to construct search result linked list
    COPY_NODE* result = NULL; // Linked list to hold the search result
    COPY_NODE* node = NULL; // Temporary node used to append to search result linked list

    if(!head)
    {
        printf("\nThere are no book copies!");
        return NULL;
    }

    for(current = head; current; current = current->next)
    {
        if(((barcode == 0) || (current->data.barcode == barcode)) && ((id_book == -1) || (current->data.id_book == id_book)) && (((int)status == -1) || (current->data.status == status)))
        {
            // If the node passes the search, copy its data to a newly constructed node
            node = (COPY_NODE*)malloc(sizeof(COPY_NODE));
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

int get_new_copy_id()
{
    int max_id = 0; // Integer to hold newest id increment
    FILE* fptr;
    COPY* buffer = (COPY*)malloc(sizeof(COPY)); // Temporary copy pointer used as a buffer to read from file

    fptr = fopen("copies", "rb");
    if(!fptr)
    {
        printf("Error! Could not open file.");
        return 0;
    }

    while(fread(buffer, sizeof(COPY), 1, fptr) == 1)
    {
        // Get the largest id of the stored copies
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

void read_copies_data_from_file(COPY_NODE** head){
    FILE* fptr;
    COPY_NODE* current;
    COPY* buffer = (COPY*)malloc(sizeof(COPY)); //Temporary copy pointer used as a buffer to read from file
    COPY_NODE* node = NULL; // Temporary node used to construct copy linked list

    fptr = fopen("copies", "rb");
    if(!fptr)
    {
        printf("Error! Could not open file.");
        return;
    }

    while(fread(buffer, sizeof(COPY), 1, fptr) == 1)
    {
        node = (COPY_NODE*)malloc(sizeof(COPY_NODE));
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

void write_copies_data_to_file(COPY_NODE* head)
{
    FILE* fptr;
    COPY_NODE* current; //Temporary copy node to loop through the linked list

    fptr = fopen("copies", "wb");
    if(!fptr)
    {
        printf("Error! Could not open file.");
        return;
    }

    for(current = head; current; current = current->next)
    {
        fwrite(&current->data, sizeof(COPY), 1, fptr);
    }

    fclose(fptr);
}

