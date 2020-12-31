#include <string.h>
#include "books.h"
#include "accounts.h"
#include "copies.h"
#include "reservations.h"
#include "general.h"

void free_book_list(BOOK_NODE** head)
{
    BOOK_NODE *node_to_delete; // Variable to hold the node to delete in order to free it

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

void print_book(BOOK book)
{
    printf("\nThe book reference: %d", book.id);
    printf("\nThe book title: %s", book.title);
    printf("\nThe book subject: %s", book.subject);
    printf("\nThe book author: %s", book.author);
    printf("\nThe book language: %s", book.language);
    printf("\nThe number of pages: %d", book.number_of_pages);
    putchar('\n');
}

void print_book_list(BOOK_NODE* head)
{
    BOOK_NODE* current; // Temporary book node to loop through the linked list

    if(!head)
    {
        printf("\nThere are no books!");
        return;
    }

    for(current = head; current; current = current->next)
    {
        print_book(current->data);
    }
}

void scan_book(BOOK* book)
{
    printf("\nType the book reference: ");
    scanf("%d", &book->id);
    printf("\nType the book title: ");
    scanf("%s", book->title);
    printf("\nType the book subject: ");
    scanf("%s", book->subject);
    printf("\nType the book author: ");
    scanf("%s", book->author);
    printf("\nType the book language: ");
    scanf("%s", book->language);
    printf("\nType the number of pages: ");
    scanf("%d", &book->number_of_pages);
    putchar('\n');
}

void scan_book_list(BOOK_NODE* head)
{
    BOOK_NODE* current;

    if(!head)
    {
        printf("\nThere is no list!");
        return;
    }

    for(current = head; current; current = current->next)
    {
        scan_book(&current->data);
    }
}

void add_book(BOOK_NODE** head, BOOK book)
{
    BOOK_NODE* current;
    BOOK_NODE* node = (BOOK_NODE*)malloc(sizeof(BOOK_NODE)); // Book node to append to the linked list

    if(!node)
    {
        printf("\nError! Could not allocate memory!");
        return;
    }
    node->data = book;
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

    write_library_data_to_file(*head);
}

int edit_book(BOOK_NODE* head, BOOK book)
{
    BOOK_NODE* current;
    int edited = 0; // Variable indicating wether or not the edition succeeded

    if(!head)
    {
        printf("\nThere are no books!");
        return 0;
    }

    for(current = head; current; current = current->next)
    {
        if(current->data.id == book.id)
        {
            current->data = book;
            write_library_data_to_file(head);
            edited = 1;
            break;
        }
    }
    return edited;
}

void remove_book_copies(RESERVATION_NODE** head_res, COPY_NODE** head_copy, int id)
{
    COPY_NODE* current;
    COPY_NODE* node_to_delete;

    if(!*head_copy)
    {
        printf("\nThere are no book copies!");
        return;
    }

    // Check if head has the book id, if it does, delete the copy reservations, set head to next node and then free the node that it previously occupied
    // Repeat until head no longer has the book id or head is NULL
    while(*head_copy && ((*head_copy)->data.id_book == id))
    {
        remove_copy_reservation(head_res, (*head_copy)->data.id);
        node_to_delete = *head_copy;
        *head_copy = node_to_delete->next;
        free(node_to_delete);
        node_to_delete = NULL;
    }

    // Check if next node has the book id, if it does delete it
    // Only pass to the the next node if it doesn't have the book id
    for(current = *head_copy; current && current->next; )
    {
        if(current->next->data.id_book == id)
        {
            remove_copy_reservation(head_res, current->next->data.id);
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

void remove_book(RESERVATION_NODE** head_res, COPY_NODE** head_copy, BOOK_NODE** head_book, int id)
{
    BOOK_NODE *current, *node_to_delete;

    if(!*head_book)
    {
        printf("\nThere are no books!");
        return;
    }

    // Check if head has the id, if it does, delete the book copies, set head to next node and then free the node that it previously occupied
    // Repeat until head no longer has the id or head is NULL
    while(*head_book && ((*head_book)->data.id == id))
    {
        remove_book_copies(head_res, head_copy, id);
        node_to_delete = *head_book;
        *head_book = node_to_delete->next;
        free(node_to_delete);
        node_to_delete = NULL;
    }

    // Check if next node has the id, if it does delete it
    // Only pass to the the next node if it doesn't have the id
    for(current = *head_book; current && current->next; )
    {
        if(current->next->data.id == id)
        {
            remove_book_copies(head_res, head_copy, id);
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

    write_library_data_to_file(*head_book);
}

BOOK* search_book(BOOK_NODE* head, int id)
{
    BOOK_NODE* current;
    BOOK* result = NULL; // Variable to hold search result

    if(!head)
    {
        printf("\nThere are no books!");
        return NULL;
    }

    for(current = head; current; current = current->next)
    {
        if(current->data.id == id)
        {
            result = (BOOK*)malloc(sizeof(BOOK));
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

BOOK_NODE* search_books(BOOK_NODE* head, char* title, char* subject, char* author, char* language, int number_of_pages)
{
    BOOK_NODE* current;
    BOOK_NODE* current_result; // Temporary node used to construct search result linked list
    BOOK_NODE* result = NULL; // Linked list to hold the search result
    BOOK_NODE* node = NULL; // Temporary node used to append to search result linked list
    char* title_lower, *subject_lower, *author_lower, *language_lower, *node_title_lower, *node_subject_lower, *node_author_lower, *node_language_lower; // Variables to hold search strings

    if(!head)
    {
        printf("\nThere are no books!");
        return NULL;
    }

    // Transform search entries to lowercase
    title_lower = str_tolower(title);
    subject_lower = str_tolower(subject);
    author_lower = str_tolower(author);
    language_lower = str_tolower(language);

    for(current = head; current; current = current->next)
    {
        // Transform node data to lowercase
        node_title_lower = str_tolower(current->data.title);
        node_subject_lower = str_tolower(current->data.subject);
        node_author_lower = str_tolower(current->data.author);
        node_language_lower = str_tolower(current->data.language);

        if((!title || strstr(node_title_lower, title_lower)) && (!subject || strstr(node_subject_lower, subject_lower))
        && (!author || strstr(node_author_lower, author_lower)) && (!language || strstr(node_language_lower, language_lower)) && ((number_of_pages == 0) || current->data.number_of_pages == number_of_pages))
        {
            // If the node passes the search, copy its data to a newly constructed node
            node = (BOOK_NODE*)malloc(sizeof(BOOK_NODE));
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

int get_new_book_id()
{
    int max_id = 0; // Integer to hold newest id increment
    FILE* fptr;
    BOOK* buffer = (BOOK*)malloc(sizeof(BOOK)); // Temporary book pointer used as a buffer to read from file

    fptr = fopen("library", "rb");
    if(!fptr)
    {
        printf("Error! Could not open file.");
        return -1;
    }

    while(fread(buffer, sizeof(BOOK), 1, fptr) == 1)
    {
        // Get the largest id of the stored books
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

void read_library_data_from_file(BOOK_NODE** head)
{
    FILE* fptr;
    BOOK_NODE* current;
    BOOK* buffer = (BOOK*)malloc(sizeof(BOOK)); // Temporary book pointer used as a buffer to read from file
    BOOK_NODE* node = NULL; // Temporary node used to construct book linked list

    fptr = fopen("library", "rb");
    if(!fptr)
    {
        printf("Error! Could not open file.");
        return;
    }

    while(fread(buffer, sizeof(BOOK), 1, fptr) == 1)
    {
        node = (BOOK_NODE*)malloc(sizeof(BOOK_NODE));
        if(!node)
        {
            printf("\nError! Could not allocate memory!");
            return;
        }
        node->data = *buffer;
        node->next = NULL;
        if(!*head)
        {
            // If the linked list head is null, assign it to newly constructed node
            current = *head = node;
        }
        else
        {
            // Link newly constructed node to previous one and step into it
            current = current->next = node;
        }
    }

    free(buffer);
    fclose(fptr);
}

void write_library_data_to_file(BOOK_NODE* head)
{
    FILE* fptr;
    BOOK_NODE* current; //Temporary book node to loop through the linked list

    fptr = fopen("library", "wb");
    if(!fptr)
    {
        printf("Error! Could not open file.");
        return;
    }

    for(current = head; current; current = current->next)
    {
        fwrite(&current->data, sizeof(BOOK), 1, fptr);
    }

    fclose(fptr);
}


