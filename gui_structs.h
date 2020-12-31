#include "general_structs.h"

#ifndef GUI_STRUCTS_H
#define GUI_STRUCTS_H

typedef enum {
    BOOK_LIST_COL_ID = 0,
    BOOK_LIST_COL_TITLE,
    BOOK_LIST_COL_SUBJECT,
    BOOK_LIST_COL_AUTHOR,
    BOOK_LIST_COL_LANGUAGE,
    BOOK_LIST_COL_NB_PAGES
} BOOK_LIST_COLUMNS;

typedef enum {
    ACCOUNT_LIST_COL_ID = 0,
    ACCOUNT_LIST_COL_EMAIL,
    ACCOUNT_LIST_COL_NAME,
    ACCOUNT_LIST_COL_ADDRESS,
    ACCOUNT_LIST_COL_PHONE,
    ACCOUNT_LIST_COL_TYPE
} ACCOUNT_LIST_COLUMNS;

typedef enum {
    RESERVATION_BOOK_LIST_COL_ID = 0,
    RESERVATION_BOOK_LIST_COL_TITLE,
    RESERVATION_BOOK_LIST_COL_SUBJECT,
    RESERVATION_BOOK_LIST_COL_AUTHOR,
    RESERVATION_BOOK_LIST_COL_LANGUAGE,
    RESERVATION_BOOK_LIST_COL_NB_PAGES,
    RESERVATION_BOOK_LIST_COL_NB_AVAILABLE_COPIES
} RESERVATION_BOOK_LIST_COLUMNS;

typedef enum {
    RESERVED_BOOK_LIST_COL_ID = 0,
    RESERVED_BOOK_LIST_COL_TITLE,
    RESERVED_BOOK_LIST_COL_AUTHOR,
    RESERVED_BOOK_LIST_COL_RESERVATION_DATE,
    RESERVED_BOOK_LIST_COL_DUE_DATE,
    RESERVED_BOOK_LIST_COL_ID_COPY,
    RESERVED_BOOK_LIST_COL_RESERVATION_DATE_VALUE,
    RESERVED_BOOK_LIST_COL_DUE_DATE_VALUE
} RESERVED_BOOK_LIST_COLUMNS;

typedef enum {
    RESERVATION_LIST_COL_ID = 0,
    RESERVATION_LIST_COL_TITLE,
    RESERVATION_LIST_COL_AUTHOR,
    RESERVATION_LIST_COL_RESERVATION_DATE,
    RESERVATION_LIST_COL_DUE_DATE,
    RESERVATION_LIST_COL_ID_COPY,
    RESERVATION_LIST_COL_ID_USER,
    RESERVATION_LIST_COL_RESERVATION_DATE_VALUE,
    RESERVATION_LIST_COL_DUE_DATE_VALUE,
} RESERVATION_LIST_COLUMNS;

typedef enum {
    COPY_LIST_COL_ID = 0,
    COPY_LIST_COL_BARCODE,
    COPY_LIST_COL_STATUS,
    COPY_LIST_COL_ID_BOOK
} COPY_LIST_COLUMNS;

typedef struct {
    GtkWidget       *window_add_book;
    GtkWidget       *dialog_confirm_add_book;
    GtkWidget       *entry_add_book_title;
    GtkWidget       *entry_add_book_subject;
    GtkWidget       *entry_add_book_author;
    GtkWidget       *entry_add_book_language;
    GtkWidget       *entry_add_book_number_of_pages;
    GtkWidget       *error_add_book_title_required;
    GtkWidget       *error_add_book_subject_required;
    GtkWidget       *error_add_book_author_required;
    GtkWidget       *error_add_book_language_required;
} ADD_BOOK_WIDGETS;

typedef struct {
    GtkWidget       *window_edit_book;
    GtkWidget       *dialog_confirm_edit_book;
    GtkWidget       *entry_edit_book_title;
    GtkWidget       *entry_edit_book_subject;
    GtkWidget       *entry_edit_book_author;
    GtkWidget       *entry_edit_book_language;
    GtkWidget       *entry_edit_book_number_of_pages;
    GtkWidget       *error_edit_book_title_required;
    GtkWidget       *error_edit_book_subject_required;
    GtkWidget       *error_edit_book_author_required;
    GtkWidget       *error_edit_book_language_required;
} EDIT_BOOK_WIDGETS;

typedef struct {
    GtkWidget       *dialog_verify_delete_book;
    GtkWidget       *dialog_confirm_delete_book;
} DELETE_BOOK_WIDGETS;

typedef struct {
    GtkWidget   *window_add_copy;
    GtkWidget   *dialog_confirm_add_copy;
    GtkWidget   *entry_add_copy_barcode;
    GtkWidget   *btn_add_copy_confirm;
    GtkWidget   *btn_add_copy_cancel;
} ADD_COPY_WIDGETS;

typedef struct {
    GtkWidget       *dialog_verify_delete_copy;
    GtkWidget       *dialog_confirm_delete_copy;
} DELETE_COPY_WIDGETS;

typedef struct {
    GtkWidget       *window_search_copy;
    GtkWidget       *entry_search_copy_barcode;
    GtkWidget       *entry_search_copy_status;
} SEARCH_COPY_WIDGETS;

typedef struct {
    GtkListStore        *list_store_copies;

    GtkWidget           *treeview_copy_list;

    ADD_COPY_WIDGETS    *add_copy_wdgts;
    DELETE_COPY_WIDGETS *delete_copy_wdgts;
    SEARCH_COPY_WIDGETS *search_copy_wdgts;

    GtkWidget           *window_manage_copies;
    GtkWidget           *btn_add_copy;
    GtkWidget           *btn_delete_copy;
    GtkWidget           *btn_search_copy;
} MANAGE_COPIES_WIDGETS;

typedef struct {
    GtkWidget       *window_search_book;
    GtkWidget       *entry_search_book_title;
    GtkWidget       *entry_search_book_subject;
    GtkWidget       *entry_search_book_author;
    GtkWidget       *entry_search_book_language;
    GtkWidget       *entry_search_book_number_of_pages;
} SEARCH_BOOK_WIDGETS;

typedef struct {
    GtkWidget       *window_add_account;
    GtkWidget       *dialog_confirm_add_account;
    GtkWidget       *entry_add_account_email;
    GtkWidget       *entry_add_account_password;
    GtkWidget       *entry_add_account_name;
    GtkWidget       *entry_add_account_address;
    GtkWidget       *entry_add_account_phone;
    GtkWidget       *entry_add_account_type;
    GtkWidget       *error_add_account_email_required;
    GtkWidget       *error_add_account_password_required;
    GtkWidget       *error_add_account_name_required;
    GtkWidget       *error_add_account_address_required;
    GtkWidget       *error_add_account_phone_required;
    GtkWidget       *error_add_account_phone_invalid;
} ADD_ACCOUNT_WIDGETS;

typedef struct {
    GtkWidget       *window_edit_account;
    GtkWidget       *dialog_confirm_edit_account;
    GtkWidget       *entry_edit_account_email;
    GtkWidget       *entry_edit_account_password;
    GtkWidget       *entry_edit_account_name;
    GtkWidget       *entry_edit_account_address;
    GtkWidget       *entry_edit_account_phone;
    GtkWidget       *entry_edit_account_type;
    GtkWidget       *error_edit_account_email_required;
    GtkWidget       *error_edit_account_password_required;
    GtkWidget       *error_edit_account_name_required;
    GtkWidget       *error_edit_account_address_required;
    GtkWidget       *error_edit_account_phone_required;
    GtkWidget       *error_edit_account_phone_invalid;
} EDIT_ACCOUNT_WIDGETS;

typedef struct {
    GtkWidget       *dialog_verify_delete_account;
    GtkWidget       *dialog_confirm_delete_account;
} DELETE_ACCOUNT_WIDGETS;

typedef struct {
    GtkWidget       *window_search_account;
    GtkWidget       *dialog_confirm_search_account;
    GtkWidget       *entry_search_account_email;
    GtkWidget       *entry_search_account_name;
    GtkWidget       *entry_search_account_address;
    GtkWidget       *entry_search_account_phone;
    GtkWidget       *entry_search_account_type;
} SEARCH_ACCOUNT_WIDGETS;

typedef struct {
    GtkWidget   *dialog_verify_delete_reservation;
    GtkWidget   *dialog_confirm_delete_reservation;
} DELETE_RESERVATION_WIDGETS;

typedef struct {
    GtkWidget       *window_search_reservation;
    GtkWidget       *entry_search_reservation_title;
    GtkWidget       *entry_search_reservation_author;
    GtkWidget       *entry_search_reservation_reservation_day;
    GtkWidget       *entry_search_reservation_reservation_month;
    GtkWidget       *entry_search_reservation_reservation_year;
    GtkWidget       *checkbox_search_reservation_reservation_date;
    GtkWidget       *entry_search_reservation_due_day;
    GtkWidget       *entry_search_reservation_due_month;
    GtkWidget       *entry_search_reservation_due_year;
    GtkWidget       *checkbox_search_reservation_due_date;
    GtkWidget       *entry_search_reservation_copy_barcode;
} SEARCH_RESERVATION_WIDGETS;

typedef struct {
    GtkWidget   *window_authentication;
    GtkWidget   *dialog_failed_authentication;
    GtkWidget   *btn_authentication_login;
    GtkWidget   *btn_authentication_exit;
    GtkWidget   *entry_authentication_email;
    GtkWidget   *entry_authentication_password;
    GtkWidget   *error_authentication_email_required;
    GtkWidget   *error_authentication_password_required;
} AUTHENTICATION_WIDGETS;

typedef struct {
    GtkWidget   *window_reserve_book;
    GtkWidget   *dialog_confirm_reserve_book;
    GtkWidget   *dialog_error_max_reservations;
    GtkWidget   *entry_reserve_book_duration;
    GtkWidget   *btn_reserve_book_confirm;
    GtkWidget   *btn_reserve_book_cancel;
} RESERVE_BOOK_WIDGETS;

typedef struct {
    GtkWidget       *window_search_reservation_book;
    GtkWidget       *dialog_confirm_search_reservation_book;
    GtkWidget       *entry_search_reservation_book_title;
    GtkWidget       *entry_search_reservation_book_subject;
    GtkWidget       *entry_search_reservation_book_author;
    GtkWidget       *entry_search_reservation_book_language;
    GtkWidget       *entry_search_reservation_book_number_of_pages;
} SEARCH_RESERVATION_BOOK_WIDGETS;

typedef struct {
    GtkWidget   *dialog_verify_return_book;
    GtkWidget   *dialog_confirm_return_book;
} RETURN_BOOK_WIDGETS;

typedef struct {
    GtkWidget       *window_search_reserved_book;
    GtkWidget       *entry_search_reserved_book_title;
    GtkWidget       *entry_search_reserved_book_author;
    GtkWidget       *entry_search_reserved_book_reservation_day;
    GtkWidget       *entry_search_reserved_book_reservation_month;
    GtkWidget       *entry_search_reserved_book_reservation_year;
    GtkWidget       *checkbox_search_reserved_book_reservation_date;
    GtkWidget       *entry_search_reserved_book_due_day;
    GtkWidget       *entry_search_reserved_book_due_month;
    GtkWidget       *entry_search_reserved_book_due_year;
    GtkWidget       *checkbox_search_reserved_book_due_date;
    GtkWidget       *entry_search_reserved_book_copy_barcode;
} SEARCH_RESERVED_BOOK_WIDGETS;

typedef struct {
    GtkListStore                    *list_store_reservation_books;
    GtkListStore                    *list_store_reserved_books;

    GtkWidget                       *treeview_reservation_book_list;
    GtkWidget                       *treeview_reserved_book_list;

    RESERVE_BOOK_WIDGETS            *reserve_book_wdgts;
    SEARCH_RESERVATION_BOOK_WIDGETS *search_reservation_book_wdgts;
    RETURN_BOOK_WIDGETS             *return_book_wdgts;
    SEARCH_RESERVED_BOOK_WIDGETS    *search_reserved_book_wdgts;

    GtkWidget                       *window_user_main;
    GtkWidget                       *btn_reserve_book;
    GtkWidget                       *btn_return_book;

    GtkWidget                       *box_reservation_book_details;
    GtkWidget                       *lbl_reservation_book_details_title;
    GtkWidget                       *lbl_reservation_book_details_subject;
    GtkWidget                       *lbl_reservation_book_details_author;
    GtkWidget                       *lbl_reservation_book_details_language;
    GtkWidget                       *lbl_reservation_book_details_number_of_pages;

    GtkWidget                       *box_reservation_details;
    GtkWidget                       *lbl_reservation_details_book;
    GtkWidget                       *lbl_reservation_details_reservation_date;
    GtkWidget                       *lbl_reservation_details_due_date;
    GtkWidget                       *lbl_reservation_details_copy_barcode;
} USER_MAIN_WIDGETS;

typedef struct {
    GtkListStore                    *list_store_books;
    GtkListStore                    *list_store_accounts;
    GtkListStore                    *list_store_reservations;

    GtkWidget                       *treeview_book_list;
    GtkWidget                       *treeview_account_list;
    GtkWidget                       *treeview_reservation_list;

    ADD_BOOK_WIDGETS                *add_book_wdgts;
    EDIT_BOOK_WIDGETS               *edit_book_wdgts;
    DELETE_BOOK_WIDGETS             *delete_book_wdgts;
    MANAGE_COPIES_WIDGETS           *manage_copies_wdgts;
    SEARCH_BOOK_WIDGETS             *search_book_wdgts;
    ADD_ACCOUNT_WIDGETS             *add_account_wdgts;
    EDIT_ACCOUNT_WIDGETS            *edit_account_wdgts;
    DELETE_ACCOUNT_WIDGETS          *delete_account_wdgts;
    SEARCH_ACCOUNT_WIDGETS          *search_account_wdgts;
    DELETE_RESERVATION_WIDGETS      *delete_reservation_wdgts;
    SEARCH_RESERVATION_WIDGETS      *search_reservation_wdgts;

    GtkWidget                       *window_admin_main;
    GtkWidget                       *btn_edit_book;
    GtkWidget                       *btn_delete_book;
    GtkWidget                       *btn_search_book;
    GtkWidget                       *btn_manage_copies;
    GtkWidget                       *btn_edit_account;
    GtkWidget                       *btn_delete_account;
    GtkWidget                       *btn_delete_reservation;

    GtkWidget                       *box_book_details;
    GtkWidget                       *lbl_book_details_title;
    GtkWidget                       *lbl_book_details_subject;
    GtkWidget                       *lbl_book_details_author;
    GtkWidget                       *lbl_book_details_language;
    GtkWidget                       *lbl_book_details_number_of_pages;

    GtkWidget                       *box_account_details;
    GtkWidget                       *lbl_account_details_email;
    GtkWidget                       *lbl_account_details_name;
    GtkWidget                       *lbl_account_details_address;
    GtkWidget                       *lbl_account_details_phone;
    GtkWidget                       *lbl_account_details_type;

    GtkWidget                       *box_admin_reservation_details;
    GtkWidget                       *lbl_admin_reservation_details_book;
    GtkWidget                       *lbl_admin_reservation_details_reservation_date;
    GtkWidget                       *lbl_admin_reservation_details_due_date;
    GtkWidget                       *lbl_admin_reservation_details_copy_barcode;
    GtkWidget                       *lbl_admin_reservation_details_user;
} ADMIN_MAIN_WIDGETS;

// Custom structure that holds pointers to widgets and user variables
typedef struct {
    // Add pointers to widgets below
    AUTHENTICATION_WIDGETS          *auth_wdgts;
    ADMIN_MAIN_WIDGETS              *admin_main_wdgts;
    USER_MAIN_WIDGETS               *user_main_wdgts;
} APP_WIDGETS;

typedef struct {
    APP_WIDGETS         *app_wdgts;
    BOOK_NODE           *book_list;
    COPY_NODE           *copy_list;
    RESERVATION_NODE    *reservation_list;
    ACCOUNT             *current_user;
} GLOBAL_DATA;

#endif // GUI_STRUCTS_H

