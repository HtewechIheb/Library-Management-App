#include <string.h>
#include "books.h"
#include "accounts.h"
#include "copies.h"
#include "reservations.h"
#include "general.h"

void free_account_list(ACCOUNT_NODE** head)
{
    ACCOUNT_NODE *node_to_delete; // Variable to hold the node to delete in order to free it

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

void hash_password(char* password_buffer, unsigned char* password, unsigned int* password_len)
{
    EVP_MD_CTX *hash_ctx; // Digest context
    const EVP_MD *hash_ptr = EVP_get_digestbyname("SHA256"); // Hashing algorithm

    OpenSSL_add_all_digests();

    hash_ctx = EVP_MD_CTX_create();

    // Initialize digest context
    EVP_DigestInit_ex(hash_ctx, hash_ptr, NULL);
    // Hash the password into the digest context
    EVP_DigestUpdate(hash_ctx, password_buffer, strlen(password_buffer));
    // Retrieve the digest value from the context and store it in password
    EVP_DigestFinal_ex(hash_ctx, password, password_len);


    EVP_MD_CTX_destroy(hash_ctx);
    EVP_cleanup();
}

char* get_account_type(ACCOUNT_TYPE type)
{
    switch(type)
    {
        case USER: return "User";
        case ADMIN: return "Admin";
    }
}

ACCOUNT new_account(char* email, char* password, char* name, char* address, int phone, ACCOUNT_TYPE type)
{
    ACCOUNT account;

    account.id = get_new_account_id();
    strcpy(account.email, email);
    strcpy(account.name, name);
    strcpy(account.address, address);
    hash_password(password, account.password, &account.password_len);
    account.phone = phone;
    account.type = type;

    return account;
}

void print_account(ACCOUNT account)
{
    int i; // Counter variable

    printf("\nThe account ID: %d", account.id);
    printf("\nThe account email: %s", account.email);
    printf("\nThe account password is: ");

    // Hashed password in not null terminated
    // Print it as an array of unsigned chars
    for (i = 0; i < account.password_len; i++)
    {
        printf("%02x", account.password[i]);
    }

    printf("\nThe account name: %s", account.name);
    printf("\nThe account address: %s", account.address);
    printf("\nThe account phone: %d", account.phone);
    printf("\nThe account type: %s", get_account_type(account.type));
    putchar('\n');

}

void print_account_list(ACCOUNT_NODE* head)
{
    ACCOUNT_NODE* current; //Temporary account node to loop through the linked list

    if(!head)
    {
        printf("\nThere are no accounts!");
        return;
    }

    for(current = head; current; current = current->next)
    {
        print_account(current->data);
    }
}

void scan_account(ACCOUNT* account)
{
    char password_buffer[128]; // Buffer to hold the password input

    printf("\nType the account ID: ");
    scanf("%d", &account->id);
    printf("\nType the account email: ");
    scanf("%s", account->email);
    printf("\nType the account password: ");
    scanf("%s", password_buffer);
    hash_password(password_buffer, account->password, &account->password_len);
    printf("\nType the account name: ");
    scanf("%s", account->name);
    printf("\nType the account address: ");
    scanf("%s", account->address);
    printf("\nType the account phone: ");
    scanf("%d", &account->phone);
    printf("\nType the account type: ");
    scanf("%d", &account->type);
    putchar('\n');
}

void scan_account_list(ACCOUNT_NODE* head)
{
    ACCOUNT_NODE* current;

    if(!head)
    {
        printf("\nThere is no list!");
        return;
    }

    for(current = head; current; current = current->next)
    {
        scan_account(&current->data);
    }
}

void add_account_to_list(ACCOUNT_NODE** head, ACCOUNT account)
{
    ACCOUNT_NODE* current;
    ACCOUNT_NODE* node = (ACCOUNT_NODE*)malloc(sizeof(ACCOUNT_NODE));

    if(!node)
    {
        printf("\nError! Could not allocate memory!");
        return;
    }
    node->data = account;
    node->next = NULL;

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

    write_account_data_to_file(*head);
}

void add_account_to_file(ACCOUNT account)
{
    ACCOUNT_NODE* head = NULL; // Linked list to hold accounts
    ACCOUNT_NODE* current;
    ACCOUNT_NODE* node = (ACCOUNT_NODE*)malloc(sizeof(ACCOUNT_NODE)); // Account node to append to the linked list

    // Store accounts read from file to head linked list
    read_account_data_from_file(&head);

    if(!node)
    {
        printf("\nError! Could not allocate memory!");
        return;
    }
    node->data = account;
    node->next = NULL;

    // Append new node to linked list, set it as the head if the linked list in empty
    if(!head)
    {
        head = node;
    }
    else
    {
        current = head;
        while(current->next != NULL)
        {
            current = current->next;
        }
        current->next = node;
    }

    write_account_data_to_file(head);

    // Free memory
    free_account_list(&head);
}

int edit_account_in_list(ACCOUNT_NODE* head, ACCOUNT account)
{
    ACCOUNT_NODE* current;
    int edited = 0;

    if(!head)
    {
        printf("\nThere are no accounts!");
        return 0;
    }

    for(current = head; current; current = current->next)
    {
        if(current->data.id == account.id)
        {
            current->data = account;
            write_account_data_to_file(head);
            edited = 1;
            break;
        }
    }

    return edited;
}

int edit_account_in_file(ACCOUNT account)
{
    ACCOUNT_NODE* head = NULL;
    ACCOUNT_NODE* current;
    int edited = 0; // Variable indicating wether or not the edition succeeded

    read_account_data_from_file(&head);

    if(!head)
    {
        printf("\nThere are no accounts!");
        return 0;
    }

    for(current = head; current; current = current->next)
    {
        if(current->data.id == account.id)
        {
            current->data = account;
            edited = 1;
            break;
        }
    }

    write_account_data_to_file(head);
    free_account_list(&head);
    return edited;
}

void remove_account_reservations(RESERVATION_NODE** head_res, COPY_NODE* head_copy, int id)
{
    RESERVATION_NODE* current;
    RESERVATION_NODE* node_to_delete;

    if(!*head_res)
    {
        printf("\nThere are no book reservations!");
        return;
    }

    // Check if head has the account id, if it does, delete the account reservations, set head to next node and then free the node that it previously occupied
    // Repeat until head no longer has the account id or head is NULL
    while(*head_res && ((*head_res)->data.id_user == id))
    {
        set_copy_status(head_copy, (*head_res)->data.id_copy, FREE);
        node_to_delete = *head_res;
        *head_res = node_to_delete->next;
        free(node_to_delete);
        node_to_delete = NULL;
    }

    // Check if next node has the account id, if it does delete it
    // Only pass to the the next node if it doesn't have the account id
    for(current = *head_res; current && current->next; )
    {
        if(current->next->data.id_user == id)
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

void remove_account_from_list(ACCOUNT_NODE** head_acc, RESERVATION_NODE** head_res, COPY_NODE* head_copy, int id)
{
    ACCOUNT_NODE* current;
    ACCOUNT_NODE* node_to_delete;

    if(!*head_acc)
    {
        printf("\nThere are no accounts!");
        return;
    }

    while(*head_acc && ((*head_acc)->data.id == id))
    {
        remove_account_reservations(head_res, head_copy, id);
        node_to_delete = *head_acc;
        *head_acc = node_to_delete->next;
        free(node_to_delete);
        node_to_delete = NULL;
    }

    for(current = *head_acc; current && current->next; )
    {
        if(current->next->data.id == id)
        {
            remove_account_reservations(head_res, head_copy, id);
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

    write_account_data_to_file(*head_acc);
}

void remove_account_from_file(RESERVATION_NODE** head_res, COPY_NODE* head_copy, int id)
{
    ACCOUNT_NODE* head = NULL;
    ACCOUNT_NODE* current;
    ACCOUNT_NODE* node_to_delete;

    read_account_data_from_file(&head);

    if(!head)
    {
        printf("\nThere are no accounts!");
        return;
    }

    // Check if head has the id, if it does, delete the account reservations, set head to next node and then free the node that it previously occupied
    // Repeat until head no longer has the id or head is NULL
    while(head && (head->data.id == id))
    {
        remove_account_reservations(head_res, head_copy, id);
        node_to_delete = head;
        head = node_to_delete->next;
        free(node_to_delete);
        node_to_delete = NULL;
    }

    // Check if next node has the id, if it does delete it
    // Only pass to the the next node if it doesn't have the id
    for(current = head; current && current->next; )
    {
        if(current->next->data.id == id)
        {
            remove_account_reservations(head_res, head_copy, id);
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

    write_account_data_to_file(head);
    free_account_list(&head);
}

ACCOUNT* search_account_in_list(ACCOUNT_NODE* head, int id)
{
    ACCOUNT_NODE* current;
    ACCOUNT* result = NULL;

    if(!head)
    {
        printf("\nThere are no accounts!");
        return NULL;
    }

    for(current = head; current; current = current->next)
    {
        if(current->data.id == id)
        {
            result = (ACCOUNT*)malloc(sizeof(ACCOUNT));
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

ACCOUNT* search_account_in_file(int id)
{
    ACCOUNT_NODE* head = NULL;
    ACCOUNT_NODE* current;
    ACCOUNT* result = NULL; // Variable to hold search result

    read_account_data_from_file(&head);

    if(!head)
    {
        printf("\nThere are no accounts!");
        return NULL;
    }

    for(current = head; current; current = current->next)
    {
        if(current->data.id == id)
        {
            result = (ACCOUNT*)malloc(sizeof(ACCOUNT));
            if(!result)
            {
                printf("\nError! Could not allocate memory!");
                return NULL;
            }
            *result = current->data;
            break;
        }
    }

    write_account_data_to_file(head);
    free_account_list(&head);
    return result;
}

ACCOUNT_NODE* search_accounts_in_list(ACCOUNT_NODE* head, char* email, char* name, char* address, int phone, ACCOUNT_TYPE type)
{
    ACCOUNT_NODE* current;
    ACCOUNT_NODE* current_result;
    ACCOUNT_NODE* result = NULL;
    ACCOUNT_NODE* node = NULL;
    char* email_lower, *name_lower, *address_lower, *node_email_lower, *node_name_lower, *node_address_lower; // Variables to hold search strings

    if(!head)
    {
        printf("\nThere are no accounts!");
        return NULL;
    }

    email_lower = str_tolower(email);
    name_lower = str_tolower(name);
    address_lower = str_tolower(address);

    for(current = head; current; current = current->next)
    {
        node_email_lower = str_tolower(current->data.email);
        node_name_lower = str_tolower(current->data.name);
        node_address_lower = str_tolower(current->data.address);

        if((!email || strstr(node_email_lower, email_lower)) && (!name || strstr(node_name_lower, name_lower))
        && (!address || strstr(node_address_lower, address_lower)) && ((phone == -1) || (current->data.phone == phone)) && (((int)type == -1) || (current->data.type == type)))
        {
            node = (ACCOUNT_NODE*)malloc(sizeof(ACCOUNT_NODE));
            if(!node)
            {
                printf("\nError! Could not allocate memory!");
                return NULL;
            }
            node->data = current->data;
            node->next = NULL;

            if(!result)
            {
                current_result = result = node;
            }
            else
            {
                current_result->next = node;
                current_result = current_result->next;
            }
        }

        free(node_email_lower);
        free(node_name_lower);
        free(node_address_lower);
    }

    free(email_lower);
    free(name_lower);
    free(address_lower);
    return result;
}

ACCOUNT_NODE* search_accounts_in_file(char* email, char* name, char* address, int phone, ACCOUNT_TYPE type)
{
    ACCOUNT_NODE* head = NULL;
    ACCOUNT_NODE* current;
    ACCOUNT_NODE* current_result; // Temporary node used to construct search result linked list
    ACCOUNT_NODE* result = NULL; // Linked list to hold the search result
    ACCOUNT_NODE* node = NULL; // Temporary node used to append to search result linked list
    char* email_lower, *name_lower, *address_lower, *node_email_lower, *node_name_lower, *node_address_lower; // Variables to hold search strings

    read_account_data_from_file(&head);

    if(!head)
    {
        printf("\nThere are no accounts!");
        return NULL;
    }

    // Transform search entries to lowercase
    email_lower = str_tolower(email);
    name_lower = str_tolower(name);
    address_lower = str_tolower(address);

    for(current = head; current; current = current->next)
    {
        // Transform node data to lowercase
        node_email_lower = str_tolower(current->data.email);
        node_name_lower = str_tolower(current->data.name);
        node_address_lower = str_tolower(current->data.address);

        if((!email || strstr(node_email_lower, email_lower)) && (!name || strstr(node_name_lower, name_lower))
        && (!address || strstr(node_address_lower, address_lower)) && ((phone == -1) || (current->data.phone == phone)) && (((int)type == -1) || (current->data.type == type)))
        {
            // If the node passes the search, copy its data to a newly constructed node
            node = (ACCOUNT_NODE*)malloc(sizeof(ACCOUNT_NODE));
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
        free(node_email_lower);
        free(node_name_lower);
        free(node_address_lower);
    }

    write_account_data_to_file(head);

    // Free memory
    free(email_lower);
    free(name_lower);
    free(address_lower);
    free_account_list(&head);
    return result;
}

ACCOUNT* authenticate_from_list(ACCOUNT_NODE* head, char* email, char* password)
{
    ACCOUNT_NODE* current;
    ACCOUNT* result = NULL;
    char *email_lower, *node_email_lower;
    unsigned char hashed_password[EVP_MAX_MD_SIZE];
    unsigned int hashed_password_len;

    if(!head)
    {
        printf("\nThere are no accounts!");
        return NULL;
    }

    email_lower = str_tolower(email);
    hash_password(password, hashed_password, &hashed_password_len);

    for(current = head; current; current = current->next)
    {
        node_email_lower = str_tolower(current->data.email);

        if((!email || !strcmp(email_lower, node_email_lower)) && !memcmp(current->data.password, hashed_password, hashed_password_len))
        {
            result = (ACCOUNT*)malloc(sizeof(ACCOUNT));
            if(!result)
            {
                printf("\nError! Could not allocate memory!");
                return NULL;
            }
            *result = current->data;
            free(node_email_lower);
            break;
        }
        free(node_email_lower);
    }

    free(email_lower);
    return result;
}

ACCOUNT* authenticate_from_file(char* email, char* password)
{
    ACCOUNT_NODE* head = NULL;
    ACCOUNT_NODE* current;
    ACCOUNT* result = NULL; // Variable to hold authenticated user data
    char *email_lower, *node_email_lower; // Variables to hold email strings
    unsigned char hashed_password[EVP_MAX_MD_SIZE]; // Variable to hold hashed version of typed password
    unsigned int hashed_password_len;   // Variable to hold hashed password length

    read_account_data_from_file(&head);

    if(!head)
    {
        printf("\nThere are no accounts!");
        return NULL;
    }

    // Transform typed email to lowercase
    email_lower = str_tolower(email);

    // Hash typed password
    hash_password(password, hashed_password, &hashed_password_len);

    for(current = head; current; current = current->next)
    {
        // Transform node email to lowercase
        node_email_lower = str_tolower(current->data.email);

        if((!email || !strcmp(email_lower, node_email_lower)) && !memcmp(current->data.password, hashed_password, hashed_password_len))
        {
            // If authentication succeeds, set result as the authenticated user
            result = (ACCOUNT*)malloc(sizeof(ACCOUNT));
            if(!result)
            {
                printf("\nError! Could not allocate memory!");
                return NULL;
            }
            *result = current->data;
            free(node_email_lower);
            break;
        }

        free(node_email_lower);
    }

    free(email_lower);
    free_account_list(&head);
    return result;
}

int get_new_account_id()
{
    int max_id = 0; // Integer to hold newest id increment
    FILE *ifp, *ofp; // ifp: input file, ofp: output file
    ACCOUNT_NODE* current; // Temporary account node to loop through the linked list
    ACCOUNT* buffer = (ACCOUNT*)malloc(sizeof(ACCOUNT)); // Temporary account pointer used as a buffer to read from file
    ACCOUNT_NODE* node = NULL; // Temporary node used to construct account linked list
    EVP_CIPHER_CTX* ctx; // Cipher context
    int plain_len = 0; // Length of plain text
    long cipher_len; // Length of cipher text
    unsigned char *plain_data; // Plain text
    unsigned char *cipher_data; // Cipher text
    unsigned char key[] = "4u7w!z%C*F-JaNdRgUkXp2s5v8y/A?D("; // AES-256 key
    unsigned char iv[] = "Zr4u7x!A%D*G-KaP"; // AES-256 initialization vector

    // accounts holds encrypted accounts data
    ifp = fopen("accounts", "rb");
    // accounts_tmp is used to store plain accounts data after decrypting it
    // It is deleted after decryption is done and list is constructed
    ofp = fopen("accounts_tmp", "wb");

    ctx = EVP_CIPHER_CTX_new();

    // Get length of encrypted file content
    fseek(ifp, 0L, SEEK_END);
    cipher_len = ftell(ifp);
    fseek(ifp, 0L, SEEK_SET);

    plain_len = 0;
    cipher_data = (unsigned char*)malloc(cipher_len);
    if(!cipher_data)
    {
        printf("\nError while allocating memory!");
        return;
    }

    plain_data = (unsigned char*)malloc(cipher_len);
    if(!plain_data)
    {
        printf("\nError while allocating memory!");
        return;
    }

    // Read encrypted file content into cipher_data
    fread(cipher_data, 1, cipher_len, ifp);

    // Initialize decryption context
    EVP_DecryptInit(ctx, EVP_aes_256_cbc(), key, iv);
    // Decrypt cipher_data and store it in plain_data
    EVP_DecryptUpdate(ctx, plain_data, &plain_len, cipher_data, (int)cipher_len);
    // Write plain_data to temporary file
    fwrite(plain_data, 1, plain_len, ofp);
    // Decrypt final block and store it in plain_data
    EVP_DecryptFinal(ctx, plain_data, &plain_len);
    // Write plain_data to temporary file
    fwrite(plain_data, 1, plain_len, ofp);

    free(cipher_data);
    free(plain_data);

    fclose(ifp);
    fclose(ofp);

    // Read accounts data from decrypted file and construct linked list
    ofp = fopen("accounts_tmp", "rb");
    if(!ofp)
    {
        printf("Error! Could not open file.");
        return;
    }
    while(fread(buffer, sizeof(ACCOUNT), 1, ofp) == 1)
    {
        // Get the largest id of the stored accounts
        if(buffer->id > max_id)
        {
            max_id = buffer->id;
        }
    }

    free(buffer);

    // Delete temporary file
    remove("accounts_tmp");
    fclose(ofp);

    // Increment largest id by 1 and return it
    return max_id + 1;
}

void read_account_data_from_file(ACCOUNT_NODE** head)
{
    FILE *ifp, *ofp; // ifp: input file, ofp: output file
    ACCOUNT_NODE* current; // Temporary account node to loop through the linked list
    ACCOUNT* buffer = (ACCOUNT*)malloc(sizeof(ACCOUNT)); // Temporary account pointer used as a buffer to read from file
    ACCOUNT_NODE* node = NULL; // Temporary node used to construct account linked list
    EVP_CIPHER_CTX* ctx; // Cipher context
    int plain_len = 0; // Length of plain text
    long cipher_len; // Length of cipher text
    unsigned char *plain_data; // Plain text
    unsigned char *cipher_data; // Cipher text
    unsigned char key[] = "4u7w!z%C*F-JaNdRgUkXp2s5v8y/A?D("; // AES-256 key
    unsigned char iv[] = "Zr4u7x!A%D*G-KaP"; // AES-256 initialization vector

    // accounts holds encrypted accounts data
    ifp = fopen("accounts", "rb");
    // accounts_tmp is used to store plain accounts data after decrypting it
    // It is deleted after decryption is done and list is constructed
    ofp = fopen("accounts_tmp", "wb");

    ctx = EVP_CIPHER_CTX_new();

    // Get length of encrypted file content
    fseek(ifp, 0L, SEEK_END);
    cipher_len = ftell(ifp);
    fseek(ifp, 0L, SEEK_SET);

    plain_len = 0;
    cipher_data = (unsigned char*)malloc(cipher_len);
    if(!cipher_data)
    {
        printf("\nError while allocating memory!");
        return;
    }

    plain_data = (unsigned char*)malloc(cipher_len);
    if(!plain_data)
    {
        printf("\nError while allocating memory!");
        return;
    }

    // Read encrypted file content into cipher_data
    fread(cipher_data, 1, cipher_len, ifp);

    // Initialize decryption context
    EVP_DecryptInit(ctx, EVP_aes_256_cbc(), key, iv);
    // Decrypt cipher_data and store it in plain_data
    EVP_DecryptUpdate(ctx, plain_data, &plain_len, cipher_data, (int)cipher_len);
    // Write plain_data to temporary file
    fwrite(plain_data, 1, plain_len, ofp);
    // Decrypt final block and store it in plain_data
    EVP_DecryptFinal(ctx, plain_data, &plain_len);
    // Write plain_data to temporary file
    fwrite(plain_data, 1, plain_len, ofp);

    free(cipher_data);
    free(plain_data);

    fclose(ifp);
    fclose(ofp);

    // Read accounts data from decrypted file and construct linked list
    ofp = fopen("accounts_tmp", "rb");
    if(!ofp)
    {
        printf("Error! Could not open file.");
        return;
    }
    while(fread(buffer, sizeof(ACCOUNT), 1, ofp) == 1)
    {
        //Create a new node after reading an entry
        node = (ACCOUNT_NODE*)malloc(sizeof(ACCOUNT_NODE));
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

    // Delete temporary file
    remove("accounts_tmp");
    fclose(ofp);
}

void write_account_data_to_file(ACCOUNT_NODE* head){
    FILE *ifp, *ofp; // ifp: input file, ofp: output file
    ACCOUNT_NODE* current; // Temporary account node to loop through the linked list
    EVP_CIPHER_CTX* ctx; // Cipher context
    int cipher_len = 0; // Length of cipher text
    long plain_len; // Length of plain text
    unsigned char *plain_data; // Plain text
    unsigned char *cipher_data; // Cipher text
    unsigned char key[] = "4u7w!z%C*F-JaNdRgUkXp2s5v8y/A?D("; // AES-256 key
    unsigned char iv[] = "Zr4u7x!A%D*G-KaP"; // AES-256 initialization vector
    unsigned blocksize; // block size of encryption algorithm


    // Write accounts data to temporary file
    ifp = fopen("accounts_tmp", "wb");
    for(current = head; current; current = current->next)
    {
        fwrite(&current->data, sizeof(ACCOUNT), 1, ifp);
    }
    fclose(ifp);

    // accounts_tmp is used to store plain accounts data before encrypting it
    // It is deleted after encryption is done and list is constructed
    ifp = fopen("accounts_tmp", "rb");
    // accounts holds encrypted accounts data
    ofp = fopen("accounts", "wb");

    ctx = EVP_CIPHER_CTX_new();

    // Get length of temporary file content
    fseek(ifp, 0L, SEEK_END);
    plain_len = ftell(ifp);
    fseek(ifp, 0L, SEEK_SET);

    plain_data = (unsigned char*)malloc(plain_len);
    if(!plain_data)
    {
        printf("\nError while allocating memory!");
        return;
    }

    // Read temporary file content into plain_data
    fread(plain_data, sizeof(unsigned char), plain_len, ifp);

    // Initialize encryption context
    EVP_EncryptInit(ctx, EVP_aes_256_cbc(), key, iv);
    // Round up to nearest block size, this will add a complete
    // block of additional padding if the input size is perfectly
    // a factor of the block size
    blocksize = EVP_CIPHER_CTX_block_size(ctx);
    cipher_data = (unsigned char*)malloc(((plain_len + blocksize)/blocksize) * blocksize);

    // Encrypt plain_data and store it in cipher_data
    EVP_EncryptUpdate(ctx, cipher_data, &cipher_len, plain_data, (int)plain_len);
    // Write cipher_data to encrypted file
    fwrite(cipher_data, 1, cipher_len,  ofp);
    // Encrypt final block and store it in cipher_data
    EVP_EncryptFinal(ctx, cipher_data, &cipher_len);
    // Write cipher_data to encrypted file
    fwrite(cipher_data, 1, cipher_len, ofp);

    free(plain_data);
    free(cipher_data);

    fclose(ofp);
    // Delete temporary file
    remove("accounts_tmp");
    fclose(ifp);
}


