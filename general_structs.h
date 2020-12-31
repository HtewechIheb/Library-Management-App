#include <openssl/evp.h>

#ifndef GENERAL_STRUCTS_H
#define GENERAL_STRUCTS_H

typedef enum {
    FREE = 0,
    RESERVED
} COPY_STATUS;

typedef enum {
    USER = 0,
    ADMIN
} ACCOUNT_TYPE;

//Book structure
typedef struct {
    int id;
    char title[128];
    char subject[256];
    char author[128];
    char language[32];
    int number_of_pages;
} BOOK;

//Node structure for book linked list
typedef struct book_node {
    BOOK data;
    struct book_node* next;
} BOOK_NODE;

//Account structure
typedef struct {
    int id;
    char email[128];
    unsigned char password[EVP_MAX_MD_SIZE];
    unsigned int password_len;
    char name[128];
    char address[256];
    int phone;
    ACCOUNT_TYPE type;
} ACCOUNT;

//Node structure for account linked list
typedef struct account_node {
    ACCOUNT data;
    struct account_node* next;
} ACCOUNT_NODE;

typedef struct {
    int id;
    int barcode;
    COPY_STATUS status;
    int id_book;
} COPY;

//Node structure for book linked list
typedef struct copy_node {
    COPY data;
    struct copy_node* next;
} COPY_NODE;

typedef struct {
    int id;
    int id_copy;
    int id_user;
    time_t reservation_date;
    time_t due_date;
} RESERVATION;

//Node structure for book linked list
typedef struct reservation_node {
    RESERVATION data;
    struct reservation_node* next;
} RESERVATION_NODE;

#endif // GENERAL_STRUCTS_H

