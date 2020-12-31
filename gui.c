#include "books.h"
#include "accounts.h"
#include "copies.h"
#include "reservations.h"
#include "general.h"
#include "gui.h"

void render_book_list(GLOBAL_DATA *g_data, BOOK_NODE* head, int from_arg_list)
{
    GtkTreeIter iter; // Iterator to read from list store
    BOOK_NODE   *current, *list; // current: Iterator for linked list, list: book list

    // If book list is provided in arguments, use it else use global data book list
    if(from_arg_list)
    {
        list = head;
    }
    else
    {
        list = g_data->book_list;
    }

    // Clear book list store
    gtk_list_store_clear(g_data->app_wdgts->admin_main_wdgts->list_store_books);

    if(list)
    {
        // Fill book list store if book list is not empty
        for(current = list; current; current = current->next)
        {
            gtk_list_store_append(g_data->app_wdgts->admin_main_wdgts->list_store_books, &iter);
            gtk_list_store_set(g_data->app_wdgts->admin_main_wdgts->list_store_books, &iter, BOOK_LIST_COL_ID, current->data.id, BOOK_LIST_COL_TITLE, current->data.title, BOOK_LIST_COL_SUBJECT, current->data.subject, BOOK_LIST_COL_AUTHOR, current->data.author, BOOK_LIST_COL_LANGUAGE, current->data.language, BOOK_LIST_COL_NB_PAGES, current->data.number_of_pages, -1);
        }
    }
    else
    {
        // Fill book list store with placeholders if book list is empty
        gtk_list_store_append(g_data->app_wdgts->admin_main_wdgts->list_store_books, &iter);
        gtk_list_store_set(g_data->app_wdgts->admin_main_wdgts->list_store_books, &iter, BOOK_LIST_COL_ID, 0, BOOK_LIST_COL_TITLE, "None", BOOK_LIST_COL_SUBJECT, "None", BOOK_LIST_COL_AUTHOR, "None", BOOK_LIST_COL_LANGUAGE, "None", BOOK_LIST_COL_NB_PAGES, 0, -1);
    }
}

void render_reservation_book_list(GLOBAL_DATA *g_data, BOOK_NODE *head, int from_arg_list)
{
    GtkTreeIter iter; // Iterator to read from list store
    BOOK_NODE   *current, *list; // current: Iterator for linked list, list: reservation book list

    // If reservation book list is provided in arguments, use it else use global data reservation book list
    if(from_arg_list)
    {
        list = head;
    }
    else
    {
        list = g_data->book_list;
    }

    // Clear reservation book list store
    gtk_list_store_clear(g_data->app_wdgts->user_main_wdgts->list_store_reservation_books);
    if(list)
    {
        // Fill reservation book list store if reservation book list is not empty
        for(current = list; current; current = current->next)
        {
            gtk_list_store_append(g_data->app_wdgts->user_main_wdgts->list_store_reservation_books, &iter);
            gtk_list_store_set(g_data->app_wdgts->user_main_wdgts->list_store_reservation_books, &iter, RESERVATION_BOOK_LIST_COL_ID, current->data.id, RESERVATION_BOOK_LIST_COL_TITLE, current->data.title, RESERVATION_BOOK_LIST_COL_SUBJECT, current->data.subject, RESERVATION_BOOK_LIST_COL_AUTHOR, current->data.author, RESERVATION_BOOK_LIST_COL_LANGUAGE, current->data.language, RESERVATION_BOOK_LIST_COL_NB_PAGES, current->data.number_of_pages, 6, get_book_copies_nb_with_status(g_data->copy_list, current->data.id, FREE), -1);
        }
    }
    else
    {
        // Fill reservation book list store with placeholders if reservation book list is empty
        gtk_list_store_append(g_data->app_wdgts->user_main_wdgts->list_store_reservation_books, &iter);
        gtk_list_store_set(g_data->app_wdgts->user_main_wdgts->list_store_reservation_books, &iter, RESERVATION_BOOK_LIST_COL_ID, 0, RESERVATION_BOOK_LIST_COL_TITLE, "None", RESERVATION_BOOK_LIST_COL_AUTHOR, "None", RESERVATION_BOOK_LIST_COL_SUBJECT, "None", RESERVATION_BOOK_LIST_COL_LANGUAGE, "None", RESERVATION_BOOK_LIST_COL_NB_PAGES, 0, RESERVATION_BOOK_LIST_COL_NB_AVAILABLE_COPIES, 0, -1);
    }
}

void render_reserved_book_list(GLOBAL_DATA *g_data, RESERVATION_NODE *head, int from_arg_list)
{
    GtkTreeIter iter; // Iterator to read from list store
    char reservation_date_string[30];   //
    char due_date_string[30];           //
    struct tm reservation_date_struct;  // Variables to handle dates
    struct tm due_date_struct;          //
    BOOK* book; // Variable to hold book to which the reserved copy is associated
    COPY* copy; // Variable to hold reserved copy
    RESERVATION_NODE   *current, *list; // current: Iterator for linked list, list: reservation list
    RESERVATION_NODE   *reserved_books = NULL; // Variable to hold user reservations

    // If reservation list is provided in arguments, use it else use global data reservation list
    if(from_arg_list)
    {
        list = head;
    }
    else
    {
        list = g_data->reservation_list;
    }

    // Search current user's reservations
    reserved_books = search_reservations(list, -1, g_data->current_user->id, -1, -1);

    // Clear reservation list store
    gtk_list_store_clear(g_data->app_wdgts->user_main_wdgts->list_store_reserved_books);
    if(reserved_books)
    {
        // Fill reservation list store if reservation list is not empty
        for(current = reserved_books; current; current = current->next)
        {
            copy = search_copy(g_data->copy_list, current->data.id_copy);
            book = search_book(g_data->book_list, copy->id_book);

            // Format dates to strings
            reservation_date_struct = *gmtime(&current->data.reservation_date);
            strftime(reservation_date_string, sizeof(reservation_date_string), "%A, %d %B %Y", &reservation_date_struct);
            due_date_struct = *gmtime(&current->data.due_date);
            strftime(due_date_string, sizeof(due_date_string), "%A, %d %B %Y", &due_date_struct);

            gtk_list_store_append(g_data->app_wdgts->user_main_wdgts->list_store_reserved_books, &iter);
            gtk_list_store_set(g_data->app_wdgts->user_main_wdgts->list_store_reserved_books, &iter, RESERVED_BOOK_LIST_COL_ID, current->data.id, RESERVED_BOOK_LIST_COL_TITLE, book->title, RESERVED_BOOK_LIST_COL_AUTHOR, book->author, RESERVED_BOOK_LIST_COL_RESERVATION_DATE, reservation_date_string, RESERVED_BOOK_LIST_COL_DUE_DATE, due_date_string, RESERVED_BOOK_LIST_COL_ID_COPY, current->data.id_copy, RESERVED_BOOK_LIST_COL_RESERVATION_DATE_VALUE, current->data.reservation_date, RESERVED_BOOK_LIST_COL_DUE_DATE_VALUE, current->data.due_date, -1);

            // Free memory
            free(book);
            free(copy);
        }
    }
    else
    {
        // Fill reservation list store with placeholders if reservation list is empty
        gtk_list_store_append(g_data->app_wdgts->user_main_wdgts->list_store_reserved_books, &iter);
        gtk_list_store_set(g_data->app_wdgts->user_main_wdgts->list_store_reserved_books, &iter, RESERVED_BOOK_LIST_COL_ID, 0, RESERVED_BOOK_LIST_COL_TITLE, "None", RESERVED_BOOK_LIST_COL_AUTHOR, "None", RESERVED_BOOK_LIST_COL_RESERVATION_DATE, "None", RESERVED_BOOK_LIST_COL_DUE_DATE, "None", RESERVED_BOOK_LIST_COL_ID_COPY, 0, RESERVED_BOOK_LIST_COL_RESERVATION_DATE_VALUE, 0, RESERVED_BOOK_LIST_COL_DUE_DATE_VALUE, 0, -1);
    }

    // Free memory
    free_reservation_list(&reserved_books);
}

void render_account_list(GLOBAL_DATA *g_data, ACCOUNT_NODE* head, int from_arg_list)
{
    GtkTreeIter iter; // Iterator to read from list store
    ACCOUNT_NODE   *current, *list = NULL; // current: Iterator for linked list, list: account list

    // If account list is provided in arguments, use it else use global data account list
    if(from_arg_list)
    {
        list = head;
    }
    else
    {
        read_account_data_from_file(&list);
    }

    // Clear account list store
    gtk_list_store_clear(g_data->app_wdgts->admin_main_wdgts->list_store_accounts);
    if(list)
    {
        // Fill account list store if account list is not empty
        for(current = list; current; current = current->next)
        {
            gtk_list_store_append(g_data->app_wdgts->admin_main_wdgts->list_store_accounts, &iter);
            gtk_list_store_set(g_data->app_wdgts->admin_main_wdgts->list_store_accounts, &iter, ACCOUNT_LIST_COL_ID, current->data.id, ACCOUNT_LIST_COL_EMAIL, current->data.email, ACCOUNT_LIST_COL_NAME, current->data.name, ACCOUNT_LIST_COL_ADDRESS, current->data.address, ACCOUNT_LIST_COL_PHONE, current->data.phone, ACCOUNT_LIST_COL_TYPE, current->data.type, -1);
        }
    }
    else
    {
        // Fill account list store with placeholders if account list is empty
        gtk_list_store_append(g_data->app_wdgts->admin_main_wdgts->list_store_accounts, &iter);
        gtk_list_store_set(g_data->app_wdgts->admin_main_wdgts->list_store_accounts, &iter, ACCOUNT_LIST_COL_ID, 0, ACCOUNT_LIST_COL_EMAIL, "None", ACCOUNT_LIST_COL_NAME, "None", ACCOUNT_LIST_COL_ADDRESS, "None", ACCOUNT_LIST_COL_PHONE, 0, ACCOUNT_LIST_COL_TYPE, 0 -1);
    }
}

void render_reservation_list(GLOBAL_DATA *g_data, RESERVATION_NODE *head, int from_arg_list)
{
    GtkTreeIter iter; // Iterator to read from list store
    char reservation_date_string[30];   //
    char due_date_string[30];           //
    struct tm reservation_date_struct;  // Variables to handle dates
    struct tm due_date_struct;          //
    BOOK* book; // Variable to hold book to which the reserved copy is associated
    COPY* copy; // Variable to hold reserved copy
    RESERVATION_NODE   *current, *list; // current: Iterator for linked list, list: reservation list

    print_reservation_list(head);
    // If reservation list is provided in arguments, use it else use global data reservation list
    if(from_arg_list)
    {
        list = head;
    }
    else
    {
        list = g_data->reservation_list;
    }

    g_print("%p", g_data->app_wdgts->admin_main_wdgts->list_store_reservations);
    // Clear reservation list store
    gtk_list_store_clear(g_data->app_wdgts->admin_main_wdgts->list_store_reservations);
    if(list)
    {
        // Fill reservation list store if reservation list is not empty
        for(current = list; current; current = current->next)
        {
            copy = search_copy(g_data->copy_list, current->data.id_copy);
            book = search_book(g_data->book_list, copy->id_book);

            // Format dates to strings
            reservation_date_struct = *gmtime(&current->data.reservation_date);
            strftime(reservation_date_string, sizeof(reservation_date_string), "%A, %d %B %Y", &reservation_date_struct);
            due_date_struct = *gmtime(&current->data.due_date);
            strftime(due_date_string, sizeof(due_date_string), "%A, %d %B %Y", &due_date_struct);

            gtk_list_store_append(g_data->app_wdgts->admin_main_wdgts->list_store_reservations, &iter);
            gtk_list_store_set(g_data->app_wdgts->admin_main_wdgts->list_store_reservations, &iter, RESERVATION_LIST_COL_ID, current->data.id, RESERVATION_LIST_COL_TITLE, book->title, RESERVATION_LIST_COL_AUTHOR, book->author, RESERVATION_LIST_COL_RESERVATION_DATE, reservation_date_string, RESERVATION_LIST_COL_DUE_DATE, due_date_string, RESERVATION_LIST_COL_ID_COPY, current->data.id_copy, RESERVATION_LIST_COL_ID_USER, current->data.id_user, RESERVATION_LIST_COL_RESERVATION_DATE_VALUE, current->data.reservation_date, RESERVATION_LIST_COL_DUE_DATE_VALUE, current->data.due_date, -1);

            // Free memory
            free(book);
            free(copy);
        }
    }
    else
    {
        // Fill reservation list store with placeholders if reservation list is empty
        gtk_list_store_append(g_data->app_wdgts->admin_main_wdgts->list_store_reservations, &iter);
        gtk_list_store_set(g_data->app_wdgts->admin_main_wdgts->list_store_reservations, &iter, RESERVATION_LIST_COL_ID, 0, RESERVATION_LIST_COL_TITLE, "None", RESERVATION_LIST_COL_AUTHOR, "None", RESERVATION_LIST_COL_RESERVATION_DATE, "None", RESERVATION_LIST_COL_DUE_DATE, "None", RESERVATION_LIST_COL_ID_COPY, 0, RESERVATION_LIST_COL_ID_USER, 0, RESERVATION_LIST_COL_RESERVATION_DATE_VALUE, 0, RESERVATION_LIST_COL_DUE_DATE_VALUE, 0, -1);
    }
}

void render_copy_list(GLOBAL_DATA *g_data, COPY_NODE *head, int id_book, int from_arg_list)
{
    GtkTreeIter iter; // Iterator to read from list store
    COPY_NODE   *current, *list; // current: Iterator for linked list, list: copy list

    // If copy list is provided in arguments, use it else use global data copy list
    if(from_arg_list)
    {
        list = head;
    }
    else
    {
        list = search_copies(g_data->copy_list, 0, id_book, -1);
    }

    // Clear copy list store
    gtk_list_store_clear(g_data->app_wdgts->admin_main_wdgts->manage_copies_wdgts->list_store_copies);
    if(list)
    {
        // Fill copy list store if copy list is not empty
        for(current = list; current; current = current->next)
        {
            gtk_list_store_append(g_data->app_wdgts->admin_main_wdgts->manage_copies_wdgts->list_store_copies, &iter);
            gtk_list_store_set(g_data->app_wdgts->admin_main_wdgts->manage_copies_wdgts->list_store_copies, &iter, COPY_LIST_COL_ID, current->data.id, COPY_LIST_COL_BARCODE, current->data.barcode, COPY_LIST_COL_STATUS, get_copy_status(current->data.status), COPY_LIST_COL_ID_BOOK, current->data.id_book, -1);
        }
    }
    else
    {
        // Fill copy list store with placeholders if copy list is empty
        gtk_list_store_append(g_data->app_wdgts->admin_main_wdgts->manage_copies_wdgts->list_store_copies, &iter);
        gtk_list_store_set(g_data->app_wdgts->admin_main_wdgts->manage_copies_wdgts->list_store_copies, &iter, COPY_LIST_COL_ID, 0, COPY_LIST_COL_BARCODE, 0, COPY_LIST_COL_STATUS, "None", COPY_LIST_COL_ID_BOOK, 0, -1);
    }
}
