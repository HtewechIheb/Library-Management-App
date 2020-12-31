#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include "general.h"
#include "books.h"
#include "accounts.h"
#include "copies.h"
#include "reservations.h"
#include "gui.h"
#include "add_book.h"
#include "edit_book.h"
#include "delete_book.h"
#include "search_book.h"
#include "add_copy.h"
#include "delete_copy.h"
#include "search_copy.h"
#include "manage_copies.h"
#include "add_account.h"
#include "edit_account.h"
#include "delete_account.h"
#include "search_account.h"
#include "delete_reservation.h"
#include "search_reservation.h"
#include "authentication.h"
#include "reserve_book.h"
#include "search_reservation_book.h"
#include "return_book.h"
#include "search_reserved_book.h"

int main(int argc, char *argv[])
{
    GtkBuilder      *builder;

    // Instantiate structure, allocating memory for it
    GLOBAL_DATA     *g_data = g_slice_new(GLOBAL_DATA);
    g_data->app_wdgts = g_slice_new(APP_WIDGETS);
    g_data->app_wdgts->admin_main_wdgts = g_slice_new(ADMIN_MAIN_WIDGETS);
    g_data->app_wdgts->admin_main_wdgts->add_book_wdgts = g_slice_new(ADD_BOOK_WIDGETS);
    g_data->app_wdgts->admin_main_wdgts->edit_book_wdgts = g_slice_new(EDIT_BOOK_WIDGETS);
    g_data->app_wdgts->admin_main_wdgts->delete_book_wdgts = g_slice_new(DELETE_BOOK_WIDGETS);
    g_data->app_wdgts->admin_main_wdgts->manage_copies_wdgts = g_slice_new(MANAGE_COPIES_WIDGETS);
    g_data->app_wdgts->admin_main_wdgts->manage_copies_wdgts->add_copy_wdgts = g_slice_new(ADD_COPY_WIDGETS);
    g_data->app_wdgts->admin_main_wdgts->manage_copies_wdgts->delete_copy_wdgts = g_slice_new(DELETE_COPY_WIDGETS);
    g_data->app_wdgts->admin_main_wdgts->manage_copies_wdgts->search_copy_wdgts = g_slice_new(SEARCH_COPY_WIDGETS);
    g_data->app_wdgts->admin_main_wdgts->search_book_wdgts = g_slice_new(SEARCH_BOOK_WIDGETS);
    g_data->app_wdgts->admin_main_wdgts->add_account_wdgts = g_slice_new(ADD_ACCOUNT_WIDGETS);
    g_data->app_wdgts->admin_main_wdgts->edit_account_wdgts = g_slice_new(EDIT_ACCOUNT_WIDGETS);
    g_data->app_wdgts->admin_main_wdgts->delete_account_wdgts = g_slice_new(DELETE_ACCOUNT_WIDGETS);
    g_data->app_wdgts->admin_main_wdgts->search_account_wdgts = g_slice_new(SEARCH_ACCOUNT_WIDGETS);
    g_data->app_wdgts->admin_main_wdgts->delete_reservation_wdgts = g_slice_new(DELETE_RESERVATION_WIDGETS);
    g_data->app_wdgts->admin_main_wdgts->search_reservation_wdgts = g_slice_new(SEARCH_RESERVATION_WIDGETS);

    g_data->app_wdgts->auth_wdgts = g_slice_new(AUTHENTICATION_WIDGETS);

    g_data->app_wdgts->user_main_wdgts = g_slice_new(USER_MAIN_WIDGETS);
    g_data->app_wdgts->user_main_wdgts->reserve_book_wdgts = g_slice_new(RESERVE_BOOK_WIDGETS);
    g_data->app_wdgts->user_main_wdgts->search_reservation_book_wdgts = g_slice_new(SEARCH_RESERVATION_BOOK_WIDGETS);
    g_data->app_wdgts->user_main_wdgts->return_book_wdgts = g_slice_new(RETURN_BOOK_WIDGETS);
    g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts = g_slice_new(SEARCH_RESERVED_BOOK_WIDGETS);

    g_data->book_list = NULL;
    g_data->copy_list = NULL;
    g_data->reservation_list = NULL;
    g_data->current_user = NULL;

    gtk_init(&argc, &argv);

    builder = gtk_builder_new_from_file("glade/window_main.glade");

    // Get pointers to widgets
    g_data->app_wdgts->admin_main_wdgts->treeview_book_list = GTK_WIDGET(gtk_builder_get_object(builder, "treeview_book_list"));
    g_data->app_wdgts->admin_main_wdgts->treeview_account_list = GTK_WIDGET(gtk_builder_get_object(builder, "treeview_account_list"));
    g_data->app_wdgts->admin_main_wdgts->treeview_reservation_list = GTK_WIDGET(gtk_builder_get_object(builder, "treeview_reservation_list"));

    g_data->app_wdgts->admin_main_wdgts->list_store_books = GTK_LIST_STORE(gtk_builder_get_object(builder, "list_store_books"));
    g_data->app_wdgts->admin_main_wdgts->list_store_accounts = GTK_LIST_STORE(gtk_builder_get_object(builder, "list_store_accounts"));
    g_data->app_wdgts->admin_main_wdgts->list_store_reservations = GTK_LIST_STORE(gtk_builder_get_object(builder, "list_store_reservations"));

    g_data->app_wdgts->admin_main_wdgts->window_admin_main = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    g_data->app_wdgts->admin_main_wdgts->btn_edit_book = GTK_WIDGET(gtk_builder_get_object(builder, "btn_edit_book"));
    g_data->app_wdgts->admin_main_wdgts->btn_delete_book = GTK_WIDGET(gtk_builder_get_object(builder, "btn_delete_book"));
    g_data->app_wdgts->admin_main_wdgts->btn_edit_account = GTK_WIDGET(gtk_builder_get_object(builder, "btn_edit_account"));
    g_data->app_wdgts->admin_main_wdgts->btn_delete_account = GTK_WIDGET(gtk_builder_get_object(builder, "btn_delete_account"));
    g_data->app_wdgts->admin_main_wdgts->btn_delete_reservation = GTK_WIDGET(gtk_builder_get_object(builder, "btn_delete_reservation"));
    g_data->app_wdgts->admin_main_wdgts->btn_manage_copies = GTK_WIDGET(gtk_builder_get_object(builder, "btn_manage_copies"));
    g_data->app_wdgts->admin_main_wdgts->btn_search_book = GTK_WIDGET(gtk_builder_get_object(builder, "btn_search_book"));

    g_data->app_wdgts->admin_main_wdgts->add_book_wdgts->window_add_book = GTK_WIDGET(gtk_builder_get_object(builder, "window_add_book"));
    g_data->app_wdgts->admin_main_wdgts->add_book_wdgts->dialog_confirm_add_book = GTK_WIDGET(gtk_builder_get_object(builder, "dialog_confirm_add_book"));
    g_data->app_wdgts->admin_main_wdgts->add_book_wdgts->entry_add_book_title = GTK_WIDGET(gtk_builder_get_object(builder, "entry_add_book_title"));
    g_data->app_wdgts->admin_main_wdgts->add_book_wdgts->entry_add_book_subject = GTK_WIDGET(gtk_builder_get_object(builder, "entry_add_book_subject"));
    g_data->app_wdgts->admin_main_wdgts->add_book_wdgts->entry_add_book_author = GTK_WIDGET(gtk_builder_get_object(builder, "entry_add_book_author"));
    g_data->app_wdgts->admin_main_wdgts->add_book_wdgts->entry_add_book_language = GTK_WIDGET(gtk_builder_get_object(builder, "entry_add_book_language"));
    g_data->app_wdgts->admin_main_wdgts->add_book_wdgts->entry_add_book_number_of_pages = GTK_WIDGET(gtk_builder_get_object(builder, "entry_add_book_number_of_pages"));
    g_data->app_wdgts->admin_main_wdgts->add_book_wdgts->error_add_book_title_required = GTK_WIDGET(gtk_builder_get_object(builder, "error_add_book_title_required"));
    g_data->app_wdgts->admin_main_wdgts->add_book_wdgts->error_add_book_subject_required = GTK_WIDGET(gtk_builder_get_object(builder, "error_add_book_subject_required"));
    g_data->app_wdgts->admin_main_wdgts->add_book_wdgts->error_add_book_author_required = GTK_WIDGET(gtk_builder_get_object(builder, "error_add_book_author_required"));
    g_data->app_wdgts->admin_main_wdgts->add_book_wdgts->error_add_book_language_required = GTK_WIDGET(gtk_builder_get_object(builder, "error_add_book_language_required"));

    g_data->app_wdgts->admin_main_wdgts->edit_book_wdgts->window_edit_book = GTK_WIDGET(gtk_builder_get_object(builder, "window_edit_book"));
    g_data->app_wdgts->admin_main_wdgts->edit_book_wdgts->dialog_confirm_edit_book = GTK_WIDGET(gtk_builder_get_object(builder, "dialog_confirm_edit_book"));
    g_data->app_wdgts->admin_main_wdgts->edit_book_wdgts->entry_edit_book_title = GTK_WIDGET(gtk_builder_get_object(builder, "entry_edit_book_title"));
    g_data->app_wdgts->admin_main_wdgts->edit_book_wdgts->entry_edit_book_subject = GTK_WIDGET(gtk_builder_get_object(builder, "entry_edit_book_subject"));
    g_data->app_wdgts->admin_main_wdgts->edit_book_wdgts->entry_edit_book_author = GTK_WIDGET(gtk_builder_get_object(builder, "entry_edit_book_author"));
    g_data->app_wdgts->admin_main_wdgts->edit_book_wdgts->entry_edit_book_language = GTK_WIDGET(gtk_builder_get_object(builder, "entry_edit_book_language"));
    g_data->app_wdgts->admin_main_wdgts->edit_book_wdgts->entry_edit_book_number_of_pages = GTK_WIDGET(gtk_builder_get_object(builder, "entry_edit_book_number_of_pages"));
    g_data->app_wdgts->admin_main_wdgts->edit_book_wdgts->error_edit_book_title_required = GTK_WIDGET(gtk_builder_get_object(builder, "error_edit_book_title_required"));
    g_data->app_wdgts->admin_main_wdgts->edit_book_wdgts->error_edit_book_subject_required = GTK_WIDGET(gtk_builder_get_object(builder, "error_edit_book_subject_required"));
    g_data->app_wdgts->admin_main_wdgts->edit_book_wdgts->error_edit_book_author_required = GTK_WIDGET(gtk_builder_get_object(builder, "error_edit_book_author_required"));
    g_data->app_wdgts->admin_main_wdgts->edit_book_wdgts->error_edit_book_language_required = GTK_WIDGET(gtk_builder_get_object(builder, "error_edit_book_language_required"));

    g_data->app_wdgts->admin_main_wdgts->delete_book_wdgts->dialog_verify_delete_book = GTK_WIDGET(gtk_builder_get_object(builder, "dialog_verify_delete_book"));
    g_data->app_wdgts->admin_main_wdgts->delete_book_wdgts->dialog_confirm_delete_book = GTK_WIDGET(gtk_builder_get_object(builder, "dialog_confirm_delete_book"));

    g_data->app_wdgts->admin_main_wdgts->manage_copies_wdgts->window_manage_copies = GTK_WIDGET(gtk_builder_get_object(builder, "window_manage_copies"));
    g_data->app_wdgts->admin_main_wdgts->manage_copies_wdgts->btn_add_copy = GTK_WIDGET(gtk_builder_get_object(builder, "btn_add_copy"));
    g_data->app_wdgts->admin_main_wdgts->manage_copies_wdgts->btn_delete_copy = GTK_WIDGET(gtk_builder_get_object(builder, "btn_delete_copy"));
    g_data->app_wdgts->admin_main_wdgts->manage_copies_wdgts->btn_search_copy = GTK_WIDGET(gtk_builder_get_object(builder, "btn_search_copy"));
    g_data->app_wdgts->admin_main_wdgts->manage_copies_wdgts->list_store_copies = GTK_LIST_STORE(gtk_builder_get_object(builder, "list_store_copies"));
    g_data->app_wdgts->admin_main_wdgts->manage_copies_wdgts->treeview_copy_list = GTK_WIDGET(gtk_builder_get_object(builder, "treeview_copy_list"));

    g_data->app_wdgts->admin_main_wdgts->manage_copies_wdgts->add_copy_wdgts->window_add_copy = GTK_WIDGET(gtk_builder_get_object(builder, "window_add_copy"));
    g_data->app_wdgts->admin_main_wdgts->manage_copies_wdgts->add_copy_wdgts->dialog_confirm_add_copy = GTK_WIDGET(gtk_builder_get_object(builder, "dialog_confirm_add_copy"));
    g_data->app_wdgts->admin_main_wdgts->manage_copies_wdgts->add_copy_wdgts->entry_add_copy_barcode = GTK_WIDGET(gtk_builder_get_object(builder, "entry_add_copy_barcode"));
    g_data->app_wdgts->admin_main_wdgts->manage_copies_wdgts->add_copy_wdgts->btn_add_copy_confirm = GTK_WIDGET(gtk_builder_get_object(builder, "btn_add_copy_confirm"));
    g_data->app_wdgts->admin_main_wdgts->manage_copies_wdgts->add_copy_wdgts->btn_add_copy_cancel = GTK_WIDGET(gtk_builder_get_object(builder, "btn_add_copy_cancel"));

    g_data->app_wdgts->admin_main_wdgts->manage_copies_wdgts->delete_copy_wdgts->dialog_verify_delete_copy = GTK_WIDGET(gtk_builder_get_object(builder, "dialog_verify_delete_copy"));
    g_data->app_wdgts->admin_main_wdgts->manage_copies_wdgts->delete_copy_wdgts->dialog_confirm_delete_copy = GTK_WIDGET(gtk_builder_get_object(builder, "dialog_confirm_delete_copy"));

    g_data->app_wdgts->admin_main_wdgts->manage_copies_wdgts->search_copy_wdgts->window_search_copy = GTK_WIDGET(gtk_builder_get_object(builder, "window_search_copy"));
    g_data->app_wdgts->admin_main_wdgts->manage_copies_wdgts->search_copy_wdgts->entry_search_copy_barcode = GTK_WIDGET(gtk_builder_get_object(builder, "entry_search_copy_barcode"));
    g_data->app_wdgts->admin_main_wdgts->manage_copies_wdgts->search_copy_wdgts->entry_search_copy_status = GTK_WIDGET(gtk_builder_get_object(builder, "entry_search_copy_status"));

    g_data->app_wdgts->admin_main_wdgts->search_book_wdgts->window_search_book = GTK_WIDGET(gtk_builder_get_object(builder, "window_search_book"));
    g_data->app_wdgts->admin_main_wdgts->search_book_wdgts->entry_search_book_title = GTK_WIDGET(gtk_builder_get_object(builder, "entry_search_book_title"));
    g_data->app_wdgts->admin_main_wdgts->search_book_wdgts->entry_search_book_subject = GTK_WIDGET(gtk_builder_get_object(builder, "entry_search_book_subject"));
    g_data->app_wdgts->admin_main_wdgts->search_book_wdgts->entry_search_book_author = GTK_WIDGET(gtk_builder_get_object(builder, "entry_search_book_author"));
    g_data->app_wdgts->admin_main_wdgts->search_book_wdgts->entry_search_book_language = GTK_WIDGET(gtk_builder_get_object(builder, "entry_search_book_language"));
    g_data->app_wdgts->admin_main_wdgts->search_book_wdgts->entry_search_book_number_of_pages = GTK_WIDGET(gtk_builder_get_object(builder, "entry_search_book_number_of_pages"));

    g_data->app_wdgts->admin_main_wdgts->add_account_wdgts->window_add_account = GTK_WIDGET(gtk_builder_get_object(builder, "window_add_account"));
    g_data->app_wdgts->admin_main_wdgts->add_account_wdgts->dialog_confirm_add_account = GTK_WIDGET(gtk_builder_get_object(builder, "dialog_confirm_add_account"));
    g_data->app_wdgts->admin_main_wdgts->add_account_wdgts->entry_add_account_email = GTK_WIDGET(gtk_builder_get_object(builder, "entry_add_account_email"));
    g_data->app_wdgts->admin_main_wdgts->add_account_wdgts->entry_add_account_password = GTK_WIDGET(gtk_builder_get_object(builder, "entry_add_account_password"));
    g_data->app_wdgts->admin_main_wdgts->add_account_wdgts->entry_add_account_name = GTK_WIDGET(gtk_builder_get_object(builder, "entry_add_account_name"));
    g_data->app_wdgts->admin_main_wdgts->add_account_wdgts->entry_add_account_address = GTK_WIDGET(gtk_builder_get_object(builder, "entry_add_account_address"));
    g_data->app_wdgts->admin_main_wdgts->add_account_wdgts->entry_add_account_phone = GTK_WIDGET(gtk_builder_get_object(builder, "entry_add_account_phone"));
    g_data->app_wdgts->admin_main_wdgts->add_account_wdgts->entry_add_account_type = GTK_WIDGET(gtk_builder_get_object(builder, "entry_add_account_type"));
    g_data->app_wdgts->admin_main_wdgts->add_account_wdgts->error_add_account_email_required = GTK_WIDGET(gtk_builder_get_object(builder, "error_add_account_email_required"));
    g_data->app_wdgts->admin_main_wdgts->add_account_wdgts->error_add_account_password_required = GTK_WIDGET(gtk_builder_get_object(builder, "error_add_account_password_required"));
    g_data->app_wdgts->admin_main_wdgts->add_account_wdgts->error_add_account_name_required = GTK_WIDGET(gtk_builder_get_object(builder, "error_add_account_name_required"));
    g_data->app_wdgts->admin_main_wdgts->add_account_wdgts->error_add_account_address_required = GTK_WIDGET(gtk_builder_get_object(builder, "error_add_account_address_required"));
    g_data->app_wdgts->admin_main_wdgts->add_account_wdgts->error_add_account_phone_required = GTK_WIDGET(gtk_builder_get_object(builder, "error_add_account_phone_required"));
    g_data->app_wdgts->admin_main_wdgts->add_account_wdgts->error_add_account_phone_invalid = GTK_WIDGET(gtk_builder_get_object(builder, "error_add_account_phone_invalid"));

    g_data->app_wdgts->admin_main_wdgts->edit_account_wdgts->window_edit_account = GTK_WIDGET(gtk_builder_get_object(builder, "window_edit_account"));
    g_data->app_wdgts->admin_main_wdgts->edit_account_wdgts->dialog_confirm_edit_account = GTK_WIDGET(gtk_builder_get_object(builder, "dialog_confirm_edit_account"));
    g_data->app_wdgts->admin_main_wdgts->edit_account_wdgts->entry_edit_account_email = GTK_WIDGET(gtk_builder_get_object(builder, "entry_edit_account_email"));
    g_data->app_wdgts->admin_main_wdgts->edit_account_wdgts->entry_edit_account_password = GTK_WIDGET(gtk_builder_get_object(builder, "entry_edit_account_password"));
    g_data->app_wdgts->admin_main_wdgts->edit_account_wdgts->entry_edit_account_name = GTK_WIDGET(gtk_builder_get_object(builder, "entry_edit_account_name"));
    g_data->app_wdgts->admin_main_wdgts->edit_account_wdgts->entry_edit_account_address = GTK_WIDGET(gtk_builder_get_object(builder, "entry_edit_account_address"));
    g_data->app_wdgts->admin_main_wdgts->edit_account_wdgts->entry_edit_account_phone = GTK_WIDGET(gtk_builder_get_object(builder, "entry_edit_account_phone"));
    g_data->app_wdgts->admin_main_wdgts->edit_account_wdgts->entry_edit_account_type = GTK_WIDGET(gtk_builder_get_object(builder, "entry_edit_account_type"));
    g_data->app_wdgts->admin_main_wdgts->edit_account_wdgts->error_edit_account_email_required = GTK_WIDGET(gtk_builder_get_object(builder, "error_edit_account_email_required"));
    g_data->app_wdgts->admin_main_wdgts->edit_account_wdgts->error_edit_account_password_required = GTK_WIDGET(gtk_builder_get_object(builder, "error_edit_account_password_required"));
    g_data->app_wdgts->admin_main_wdgts->edit_account_wdgts->error_edit_account_name_required = GTK_WIDGET(gtk_builder_get_object(builder, "error_edit_account_name_required"));
    g_data->app_wdgts->admin_main_wdgts->edit_account_wdgts->error_edit_account_address_required = GTK_WIDGET(gtk_builder_get_object(builder, "error_edit_account_address_required"));
    g_data->app_wdgts->admin_main_wdgts->edit_account_wdgts->error_edit_account_phone_required = GTK_WIDGET(gtk_builder_get_object(builder, "error_edit_account_phone_required"));
    g_data->app_wdgts->admin_main_wdgts->edit_account_wdgts->error_edit_account_phone_invalid = GTK_WIDGET(gtk_builder_get_object(builder, "error_edit_account_phone_invalid"));

    g_data->app_wdgts->admin_main_wdgts->delete_account_wdgts->dialog_verify_delete_account = GTK_WIDGET(gtk_builder_get_object(builder, "dialog_verify_delete_account"));
    g_data->app_wdgts->admin_main_wdgts->delete_account_wdgts->dialog_confirm_delete_account = GTK_WIDGET(gtk_builder_get_object(builder, "dialog_confirm_delete_account"));

    g_data->app_wdgts->admin_main_wdgts->search_account_wdgts->window_search_account = GTK_WIDGET(gtk_builder_get_object(builder, "window_search_account"));
    g_data->app_wdgts->admin_main_wdgts->search_account_wdgts->dialog_confirm_search_account = GTK_WIDGET(gtk_builder_get_object(builder, "dialog_confirm_search_account"));
    g_data->app_wdgts->admin_main_wdgts->search_account_wdgts->entry_search_account_email = GTK_WIDGET(gtk_builder_get_object(builder, "entry_search_account_email"));
    g_data->app_wdgts->admin_main_wdgts->search_account_wdgts->entry_search_account_name = GTK_WIDGET(gtk_builder_get_object(builder, "entry_search_account_name"));
    g_data->app_wdgts->admin_main_wdgts->search_account_wdgts->entry_search_account_address = GTK_WIDGET(gtk_builder_get_object(builder, "entry_search_account_address"));
    g_data->app_wdgts->admin_main_wdgts->search_account_wdgts->entry_search_account_phone = GTK_WIDGET(gtk_builder_get_object(builder, "entry_search_account_phone"));
    g_data->app_wdgts->admin_main_wdgts->search_account_wdgts->entry_search_account_type = GTK_WIDGET(gtk_builder_get_object(builder, "entry_search_account_type"));

    g_data->app_wdgts->admin_main_wdgts->delete_reservation_wdgts->dialog_verify_delete_reservation = GTK_WIDGET(gtk_builder_get_object(builder, "dialog_verify_delete_reservation"));
    g_data->app_wdgts->admin_main_wdgts->delete_reservation_wdgts->dialog_confirm_delete_reservation  = GTK_WIDGET(gtk_builder_get_object(builder, "dialog_confirm_delete_reservation"));

    g_data->app_wdgts->admin_main_wdgts->search_reservation_wdgts->window_search_reservation = GTK_WIDGET(gtk_builder_get_object(builder, "window_search_reservation"));
    g_data->app_wdgts->admin_main_wdgts->search_reservation_wdgts->entry_search_reservation_title = GTK_WIDGET(gtk_builder_get_object(builder, "entry_search_reservation_title"));
    g_data->app_wdgts->admin_main_wdgts->search_reservation_wdgts->entry_search_reservation_author = GTK_WIDGET(gtk_builder_get_object(builder, "entry_search_reservation_author"));
    g_data->app_wdgts->admin_main_wdgts->search_reservation_wdgts->entry_search_reservation_reservation_day = GTK_WIDGET(gtk_builder_get_object(builder, "entry_search_reservation_reservation_day"));
    g_data->app_wdgts->admin_main_wdgts->search_reservation_wdgts->entry_search_reservation_reservation_month = GTK_WIDGET(gtk_builder_get_object(builder, "entry_search_reservation_reservation_month"));
    g_data->app_wdgts->admin_main_wdgts->search_reservation_wdgts->entry_search_reservation_reservation_year = GTK_WIDGET(gtk_builder_get_object(builder, "entry_search_reservation_reservation_year"));
    g_data->app_wdgts->admin_main_wdgts->search_reservation_wdgts->checkbox_search_reservation_reservation_date = GTK_WIDGET(gtk_builder_get_object(builder, "checkbox_search_reservation_reservation_date"));
    g_data->app_wdgts->admin_main_wdgts->search_reservation_wdgts->entry_search_reservation_due_day = GTK_WIDGET(gtk_builder_get_object(builder, "entry_search_reservation_due_day"));
    g_data->app_wdgts->admin_main_wdgts->search_reservation_wdgts->entry_search_reservation_due_month = GTK_WIDGET(gtk_builder_get_object(builder, "entry_search_reservation_due_month"));
    g_data->app_wdgts->admin_main_wdgts->search_reservation_wdgts->entry_search_reservation_due_year = GTK_WIDGET(gtk_builder_get_object(builder, "entry_search_reservation_due_year"));
    g_data->app_wdgts->admin_main_wdgts->search_reservation_wdgts->checkbox_search_reservation_due_date = GTK_WIDGET(gtk_builder_get_object(builder, "checkbox_search_reservation_due_date"));
    g_data->app_wdgts->admin_main_wdgts->search_reservation_wdgts->entry_search_reservation_copy_barcode = GTK_WIDGET(gtk_builder_get_object(builder, "entry_search_reservation_copy_barcode"));

    g_data->app_wdgts->admin_main_wdgts->box_book_details = GTK_WIDGET(gtk_builder_get_object(builder, "box_book_details"));
    g_data->app_wdgts->admin_main_wdgts->lbl_book_details_title = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_book_details_title"));
    g_data->app_wdgts->admin_main_wdgts->lbl_book_details_subject = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_book_details_subject"));
    g_data->app_wdgts->admin_main_wdgts->lbl_book_details_author = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_book_details_author"));
    g_data->app_wdgts->admin_main_wdgts->lbl_book_details_language = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_book_details_language"));
    g_data->app_wdgts->admin_main_wdgts->lbl_book_details_number_of_pages = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_book_details_number_of_pages"));

    g_data->app_wdgts->admin_main_wdgts->box_account_details = GTK_WIDGET(gtk_builder_get_object(builder, "box_account_details"));
    g_data->app_wdgts->admin_main_wdgts->lbl_account_details_email = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_account_details_email"));
    g_data->app_wdgts->admin_main_wdgts->lbl_account_details_name = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_account_details_name"));
    g_data->app_wdgts->admin_main_wdgts->lbl_account_details_address = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_account_details_address"));
    g_data->app_wdgts->admin_main_wdgts->lbl_account_details_phone = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_account_details_phone"));
    g_data->app_wdgts->admin_main_wdgts->lbl_account_details_type = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_account_details_type"));

    g_data->app_wdgts->admin_main_wdgts->box_admin_reservation_details = GTK_WIDGET(gtk_builder_get_object(builder, "box_admin_reservation_details"));
    g_data->app_wdgts->admin_main_wdgts->lbl_admin_reservation_details_book = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_admin_reservation_details_book"));
    g_data->app_wdgts->admin_main_wdgts->lbl_admin_reservation_details_reservation_date = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_admin_reservation_details_reservation_date"));
    g_data->app_wdgts->admin_main_wdgts->lbl_admin_reservation_details_due_date = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_admin_reservation_details_due_date"));
    g_data->app_wdgts->admin_main_wdgts->lbl_admin_reservation_details_copy_barcode = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_admin_reservation_details_copy_barcode"));
    g_data->app_wdgts->admin_main_wdgts->lbl_admin_reservation_details_user = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_admin_reservation_details_user"));

    g_data->app_wdgts->auth_wdgts->window_authentication = GTK_WIDGET(gtk_builder_get_object(builder, "window_authentication"));
    g_data->app_wdgts->auth_wdgts->dialog_failed_authentication = GTK_WIDGET(gtk_builder_get_object(builder, "dialog_failed_authentication"));
    g_data->app_wdgts->auth_wdgts->btn_authentication_login = GTK_WIDGET(gtk_builder_get_object(builder, "btn_authentication_login"));
    g_data->app_wdgts->auth_wdgts->btn_authentication_exit = GTK_WIDGET(gtk_builder_get_object(builder, "btn_authentication_exit"));
    g_data->app_wdgts->auth_wdgts->entry_authentication_email = GTK_WIDGET(gtk_builder_get_object(builder, "entry_authentication_email"));
    g_data->app_wdgts->auth_wdgts->entry_authentication_password = GTK_WIDGET(gtk_builder_get_object(builder, "entry_authentication_password"));
    g_data->app_wdgts->auth_wdgts->error_authentication_email_required = GTK_WIDGET(gtk_builder_get_object(builder, "error_authentication_email_required"));
    g_data->app_wdgts->auth_wdgts->error_authentication_password_required = GTK_WIDGET(gtk_builder_get_object(builder, "error_authentication_password_required"));

    g_data->app_wdgts->user_main_wdgts->treeview_reservation_book_list = GTK_WIDGET(gtk_builder_get_object(builder, "treeview_reservation_book_list"));
    g_data->app_wdgts->user_main_wdgts->treeview_reserved_book_list = GTK_WIDGET(gtk_builder_get_object(builder, "treeview_reserved_book_list"));

    g_data->app_wdgts->user_main_wdgts->list_store_reservation_books = GTK_LIST_STORE(gtk_builder_get_object(builder, "list_store_reservation_books"));
    g_data->app_wdgts->user_main_wdgts->list_store_reserved_books = GTK_LIST_STORE(gtk_builder_get_object(builder, "list_store_reserved_books"));

    g_data->app_wdgts->user_main_wdgts->window_user_main = GTK_WIDGET(gtk_builder_get_object(builder, "window_user_main"));
    g_data->app_wdgts->user_main_wdgts->btn_reserve_book = GTK_WIDGET(gtk_builder_get_object(builder, "btn_reserve_book"));
    g_data->app_wdgts->user_main_wdgts->btn_return_book = GTK_WIDGET(gtk_builder_get_object(builder, "btn_return_book"));

    g_data->app_wdgts->user_main_wdgts->reserve_book_wdgts->window_reserve_book = GTK_WIDGET(gtk_builder_get_object(builder, "window_reserve_book"));
    g_data->app_wdgts->user_main_wdgts->reserve_book_wdgts->dialog_confirm_reserve_book = GTK_WIDGET(gtk_builder_get_object(builder, "dialog_confirm_reserve_book"));
    g_data->app_wdgts->user_main_wdgts->reserve_book_wdgts->dialog_error_max_reservations = GTK_WIDGET(gtk_builder_get_object(builder, "dialog_error_max_reservations"));
    g_data->app_wdgts->user_main_wdgts->reserve_book_wdgts->entry_reserve_book_duration = GTK_WIDGET(gtk_builder_get_object(builder, "entry_reserve_book_duration"));
    g_data->app_wdgts->user_main_wdgts->reserve_book_wdgts->btn_reserve_book_confirm = GTK_WIDGET(gtk_builder_get_object(builder, "btn_reserve_book_confirm"));
    g_data->app_wdgts->user_main_wdgts->reserve_book_wdgts->btn_reserve_book_cancel = GTK_WIDGET(gtk_builder_get_object(builder, "btn_reserve_book_cancel"));

    g_data->app_wdgts->user_main_wdgts->search_reservation_book_wdgts->window_search_reservation_book = GTK_WIDGET(gtk_builder_get_object(builder, "window_search_reservation_book"));
    g_data->app_wdgts->user_main_wdgts->search_reservation_book_wdgts->entry_search_reservation_book_title = GTK_WIDGET(gtk_builder_get_object(builder, "entry_search_reservation_book_title"));
    g_data->app_wdgts->user_main_wdgts->search_reservation_book_wdgts->entry_search_reservation_book_subject = GTK_WIDGET(gtk_builder_get_object(builder, "entry_search_reservation_book_subject"));
    g_data->app_wdgts->user_main_wdgts->search_reservation_book_wdgts->entry_search_reservation_book_author = GTK_WIDGET(gtk_builder_get_object(builder, "entry_search_reservation_book_author"));
    g_data->app_wdgts->user_main_wdgts->search_reservation_book_wdgts->entry_search_reservation_book_language = GTK_WIDGET(gtk_builder_get_object(builder, "entry_search_reservation_book_language"));
    g_data->app_wdgts->user_main_wdgts->search_reservation_book_wdgts->entry_search_reservation_book_number_of_pages = GTK_WIDGET(gtk_builder_get_object(builder, "entry_search_reservation_book_number_of_pages"));

    g_data->app_wdgts->user_main_wdgts->return_book_wdgts->dialog_verify_return_book = GTK_WIDGET(gtk_builder_get_object(builder, "dialog_verify_return_book"));
    g_data->app_wdgts->user_main_wdgts->return_book_wdgts->dialog_confirm_return_book = GTK_WIDGET(gtk_builder_get_object(builder, "dialog_confirm_return_book"));

    g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts->window_search_reserved_book = GTK_WIDGET(gtk_builder_get_object(builder, "window_search_reserved_book"));
    g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts->entry_search_reserved_book_title = GTK_WIDGET(gtk_builder_get_object(builder, "entry_search_reserved_book_title"));
    g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts->entry_search_reserved_book_author = GTK_WIDGET(gtk_builder_get_object(builder, "entry_search_reserved_book_author"));
    g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts->entry_search_reserved_book_reservation_day = GTK_WIDGET(gtk_builder_get_object(builder, "entry_search_reserved_book_reservation_day"));
    g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts->entry_search_reserved_book_reservation_month = GTK_WIDGET(gtk_builder_get_object(builder, "entry_search_reserved_book_reservation_month"));
    g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts->entry_search_reserved_book_reservation_year = GTK_WIDGET(gtk_builder_get_object(builder, "entry_search_reserved_book_reservation_year"));
    g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts->checkbox_search_reserved_book_reservation_date = GTK_WIDGET(gtk_builder_get_object(builder, "checkbox_search_reserved_book_reservation_date"));
    g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts->entry_search_reserved_book_due_day = GTK_WIDGET(gtk_builder_get_object(builder, "entry_search_reserved_book_due_day"));
    g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts->entry_search_reserved_book_due_month = GTK_WIDGET(gtk_builder_get_object(builder, "entry_search_reserved_book_due_month"));
    g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts->entry_search_reserved_book_due_year = GTK_WIDGET(gtk_builder_get_object(builder, "entry_search_reserved_book_due_year"));
    g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts->checkbox_search_reserved_book_due_date = GTK_WIDGET(gtk_builder_get_object(builder, "checkbox_search_reserved_book_due_date"));
    g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts->entry_search_reserved_book_copy_barcode = GTK_WIDGET(gtk_builder_get_object(builder, "entry_search_reserved_book_copy_barcode"));

    g_data->app_wdgts->user_main_wdgts->box_reservation_book_details = GTK_WIDGET(gtk_builder_get_object(builder, "box_reservation_book_details"));
    g_data->app_wdgts->user_main_wdgts->lbl_reservation_book_details_title = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_reservation_book_details_title"));
    g_data->app_wdgts->user_main_wdgts->lbl_reservation_book_details_subject = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_reservation_book_details_subject"));
    g_data->app_wdgts->user_main_wdgts->lbl_reservation_book_details_author = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_reservation_book_details_author"));
    g_data->app_wdgts->user_main_wdgts->lbl_reservation_book_details_language = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_reservation_book_details_language"));
    g_data->app_wdgts->user_main_wdgts->lbl_reservation_book_details_number_of_pages = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_reservation_book_details_number_of_pages"));

    g_data->app_wdgts->user_main_wdgts->box_reservation_details = GTK_WIDGET(gtk_builder_get_object(builder, "box_reservation_details"));
    g_data->app_wdgts->user_main_wdgts->lbl_reservation_details_book = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_reservation_details_book"));
    g_data->app_wdgts->user_main_wdgts->lbl_reservation_details_reservation_date = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_reservation_details_reservation_date"));
    g_data->app_wdgts->user_main_wdgts->lbl_reservation_details_due_date = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_reservation_details_due_date"));
    g_data->app_wdgts->user_main_wdgts->lbl_reservation_details_copy_barcode = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_reservation_details_copy_barcode"));

    // Read data from files
    read_library_data_from_file(&g_data->book_list);
    read_copies_data_from_file(&g_data->copy_list);
    read_reservations_data_from_file(&g_data->reservation_list);

    //Widgets pointer are passed to all widget handler functions as the user_data parameter
    gtk_builder_connect_signals(builder, g_data);

    g_object_unref(builder);

    gtk_widget_show(g_data->app_wdgts->auth_wdgts->window_authentication);
    gtk_main();

    // Free up widget structure memory
    free_reservation_list(&g_data->reservation_list);
    free_copy_list(&g_data->copy_list);
    free_book_list(&g_data->book_list);
    g_free(g_data->current_user);

    g_slice_free(SEARCH_RESERVED_BOOK_WIDGETS, g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts);
    g_slice_free(RETURN_BOOK_WIDGETS, g_data->app_wdgts->user_main_wdgts->return_book_wdgts);
    g_slice_free(SEARCH_RESERVATION_BOOK_WIDGETS, g_data->app_wdgts->user_main_wdgts->search_reservation_book_wdgts);
    g_slice_free(RESERVE_BOOK_WIDGETS, g_data->app_wdgts->user_main_wdgts->reserve_book_wdgts);
    g_slice_free(SEARCH_RESERVATION_WIDGETS, g_data->app_wdgts->admin_main_wdgts->search_reservation_wdgts);
    g_slice_free(DELETE_RESERVATION_WIDGETS, g_data->app_wdgts->admin_main_wdgts->delete_reservation_wdgts);
    g_slice_free(SEARCH_ACCOUNT_WIDGETS, g_data->app_wdgts->admin_main_wdgts->search_account_wdgts);
    g_slice_free(DELETE_ACCOUNT_WIDGETS, g_data->app_wdgts->admin_main_wdgts->delete_account_wdgts);
    g_slice_free(EDIT_ACCOUNT_WIDGETS, g_data->app_wdgts->admin_main_wdgts->edit_account_wdgts);
    g_slice_free(ADD_ACCOUNT_WIDGETS, g_data->app_wdgts->admin_main_wdgts->add_account_wdgts);
    g_slice_free(SEARCH_BOOK_WIDGETS, g_data->app_wdgts->admin_main_wdgts->search_book_wdgts);
    g_slice_free(SEARCH_COPY_WIDGETS, g_data->app_wdgts->admin_main_wdgts->manage_copies_wdgts->search_copy_wdgts);
    g_slice_free(DELETE_COPY_WIDGETS, g_data->app_wdgts->admin_main_wdgts->manage_copies_wdgts->delete_copy_wdgts);
    g_slice_free(ADD_COPY_WIDGETS, g_data->app_wdgts->admin_main_wdgts->manage_copies_wdgts->add_copy_wdgts);
    g_slice_free(MANAGE_COPIES_WIDGETS, g_data->app_wdgts->admin_main_wdgts->manage_copies_wdgts);
    g_slice_free(DELETE_BOOK_WIDGETS, g_data->app_wdgts->admin_main_wdgts->delete_book_wdgts);
    g_slice_free(EDIT_BOOK_WIDGETS, g_data->app_wdgts->admin_main_wdgts->edit_book_wdgts);
    g_slice_free(ADD_BOOK_WIDGETS, g_data->app_wdgts->admin_main_wdgts->add_book_wdgts);
    g_slice_free(USER_MAIN_WIDGETS, g_data->app_wdgts->user_main_wdgts);
    g_slice_free(AUTHENTICATION_WIDGETS, g_data->app_wdgts->auth_wdgts);
    g_slice_free(ADMIN_MAIN_WIDGETS, g_data->app_wdgts->admin_main_wdgts);
    g_slice_free(APP_WIDGETS, g_data->app_wdgts);
    g_slice_free(GLOBAL_DATA, g_data);

    return 0;
}

void on_book_list_selection_changed(GtkTreeSelection *selection, GLOBAL_DATA *g_data)
{
    GtkTreeIter iter; // Iterator to read from list store
    GtkTreeModel *model; // Model for list store
    char *title, *subject, *author, *language;  //
    char number_of_pages_string[6];             // Variables to hold data read from list store
    int id, number_of_pages;                    //

    // Check if a row is selected in the treeview
    if (gtk_tree_selection_get_selected (selection, &model, &iter))
    {
            // Enable book operations
            gtk_widget_set_sensitive(g_data->app_wdgts->admin_main_wdgts->btn_edit_book, TRUE);
            gtk_widget_set_sensitive(g_data->app_wdgts->admin_main_wdgts->btn_delete_book, TRUE);
            gtk_widget_set_sensitive(g_data->app_wdgts->admin_main_wdgts->btn_manage_copies, TRUE);

            // Read data from list store
            gtk_tree_model_get (model, &iter, BOOK_LIST_COL_ID, &id, BOOK_LIST_COL_TITLE, &title, BOOK_LIST_COL_SUBJECT, &subject, BOOK_LIST_COL_AUTHOR, &author, BOOK_LIST_COL_LANGUAGE, &language, BOOK_LIST_COL_NB_PAGES, &number_of_pages, -1);

            // Print book data to the details area
            sprintf(number_of_pages_string, "%d", number_of_pages);
            gtk_label_set_text(GTK_LABEL(g_data->app_wdgts->admin_main_wdgts->lbl_book_details_title), title);
            gtk_label_set_text(GTK_LABEL(g_data->app_wdgts->admin_main_wdgts->lbl_book_details_subject), subject);
            gtk_label_set_text(GTK_LABEL(g_data->app_wdgts->admin_main_wdgts->lbl_book_details_author), author);
            gtk_label_set_text(GTK_LABEL(g_data->app_wdgts->admin_main_wdgts->lbl_book_details_language), language);
            gtk_label_set_text(GTK_LABEL(g_data->app_wdgts->admin_main_wdgts->lbl_book_details_number_of_pages), number_of_pages_string);

            // Inject book data to edit book view
            gtk_entry_set_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->edit_book_wdgts->entry_edit_book_title), title);
            gtk_entry_set_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->edit_book_wdgts->entry_edit_book_subject), subject);
            gtk_entry_set_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->edit_book_wdgts->entry_edit_book_author), author);
            gtk_entry_set_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->edit_book_wdgts->entry_edit_book_language), language);
            gtk_spin_button_set_value(GTK_SPIN_BUTTON(g_data->app_wdgts->admin_main_wdgts->edit_book_wdgts->entry_edit_book_number_of_pages), number_of_pages);

            // Free memory
            g_free (title);
            g_free (subject);
            g_free (author);
            g_free (language);

            // Update the copy treeview according to selected book
            render_copy_list(g_data, NULL, id, 0);
    }
    else
    {
        // Reset details area
        gtk_label_set_text(GTK_LABEL(g_data->app_wdgts->admin_main_wdgts->lbl_book_details_title), "None");
        gtk_label_set_text(GTK_LABEL(g_data->app_wdgts->admin_main_wdgts->lbl_book_details_subject), "None");
        gtk_label_set_text(GTK_LABEL(g_data->app_wdgts->admin_main_wdgts->lbl_book_details_author), "None");
        gtk_label_set_text(GTK_LABEL(g_data->app_wdgts->admin_main_wdgts->lbl_book_details_language), "None");
        gtk_label_set_text(GTK_LABEL(g_data->app_wdgts->admin_main_wdgts->lbl_book_details_number_of_pages), "None");

        // Disable book operations
        gtk_widget_set_sensitive(g_data->app_wdgts->admin_main_wdgts->btn_edit_book, FALSE);
        gtk_widget_set_sensitive(g_data->app_wdgts->admin_main_wdgts->btn_delete_book, FALSE);
        gtk_widget_set_sensitive(g_data->app_wdgts->admin_main_wdgts->btn_manage_copies, FALSE);

        // Reset copies treeview
        render_copy_list(g_data, NULL, -1, 1);
    }
}

void on_selection_reservation_book_list_changed(GtkTreeSelection *selection, GLOBAL_DATA *g_data)
{
    GtkTreeIter iter; // Iterator to read from list store
    GtkTreeModel *model; // Model for list store
    char *title, *subject, *author, *language;  //
    char number_of_pages_string[6];             // Variables to hold data read from list store
    int id_book, number_of_pages;               //

    // Check if a row is selected in the treeview
    if (gtk_tree_selection_get_selected (selection, &model, &iter))
    {
        // Read data from list store
        gtk_tree_model_get (model, &iter, RESERVATION_BOOK_LIST_COL_ID, &id_book, RESERVATION_BOOK_LIST_COL_TITLE, &title, RESERVATION_BOOK_LIST_COL_SUBJECT, &subject, RESERVATION_BOOK_LIST_COL_AUTHOR, &author, RESERVATION_BOOK_LIST_COL_LANGUAGE, &language, RESERVATION_BOOK_LIST_COL_NB_PAGES, &number_of_pages, -1);

        // Print book data to details area
        sprintf(number_of_pages_string, "%d", number_of_pages);
        gtk_label_set_text(GTK_LABEL(g_data->app_wdgts->user_main_wdgts->lbl_reservation_book_details_title), title);
        gtk_label_set_text(GTK_LABEL(g_data->app_wdgts->user_main_wdgts->lbl_reservation_book_details_subject), subject);
        gtk_label_set_text(GTK_LABEL(g_data->app_wdgts->user_main_wdgts->lbl_reservation_book_details_author), author);
        gtk_label_set_text(GTK_LABEL(g_data->app_wdgts->user_main_wdgts->lbl_reservation_book_details_language), language);
        gtk_label_set_text(GTK_LABEL(g_data->app_wdgts->user_main_wdgts->lbl_reservation_book_details_number_of_pages), number_of_pages_string);

        // Check if there are any free copies of the book
        if(get_book_copies_nb_with_status(g_data->copy_list, id_book, FREE))
        {
            // If so, enable reserve book operation
            gtk_widget_set_sensitive(g_data->app_wdgts->user_main_wdgts->btn_reserve_book, TRUE);
        }
        else
        {
            // If not, disable reserve book operation
            gtk_widget_set_sensitive(g_data->app_wdgts->user_main_wdgts->btn_reserve_book, FALSE);
        }

        // Free memory
        g_free (title);
        g_free (subject);
        g_free (author);
        g_free (language);
    }
    else
    {
        // Reset details area
        gtk_label_set_text(GTK_LABEL(g_data->app_wdgts->user_main_wdgts->lbl_reservation_book_details_title), "None");
        gtk_label_set_text(GTK_LABEL(g_data->app_wdgts->user_main_wdgts->lbl_reservation_book_details_subject), "None");
        gtk_label_set_text(GTK_LABEL(g_data->app_wdgts->user_main_wdgts->lbl_reservation_book_details_author), "None");
        gtk_label_set_text(GTK_LABEL(g_data->app_wdgts->user_main_wdgts->lbl_reservation_book_details_language), "None");
        gtk_label_set_text(GTK_LABEL(g_data->app_wdgts->user_main_wdgts->lbl_reservation_book_details_number_of_pages), "None");

        // Disable reserve book operation
        gtk_widget_set_sensitive(g_data->app_wdgts->user_main_wdgts->btn_reserve_book, FALSE);
    }
}

void on_selection_reserved_book_list_changed(GtkTreeSelection *selection, GLOBAL_DATA *g_data)
{
    GtkTreeIter iter; // Iterator to read from list store
    GtkTreeModel *model; // Model for list store
    COPY* copy; // Variable to hold the reserved copy
    char *title, *author, *reservation_date, *due_date; //
    int id_book, id_copy;                               // Variables to hold data read from list store
    char barcode_string[10]; // Variable to hold copy barcode string

    // Check if a row is selected in the treeview
    if (gtk_tree_selection_get_selected (selection, &model, &iter))
    {
        // Read data from list store
        gtk_tree_model_get (model, &iter, RESERVED_BOOK_LIST_COL_ID, &id_book, RESERVED_BOOK_LIST_COL_TITLE, &title, RESERVED_BOOK_LIST_COL_AUTHOR, &author, RESERVED_BOOK_LIST_COL_RESERVATION_DATE, &reservation_date, RESERVED_BOOK_LIST_COL_DUE_DATE, &due_date, RESERVED_BOOK_LIST_COL_ID_COPY, &id_copy, -1);

        // Get reserved copy
        copy = search_copy(g_data->copy_list, id_copy);

        // Print reservation data to details area
        sprintf(barcode_string, "%d", copy->barcode);
        gtk_label_set_text(GTK_LABEL(g_data->app_wdgts->user_main_wdgts->lbl_reservation_details_book), title);
        gtk_label_set_text(GTK_LABEL(g_data->app_wdgts->user_main_wdgts->lbl_reservation_details_reservation_date), reservation_date);
        gtk_label_set_text(GTK_LABEL(g_data->app_wdgts->user_main_wdgts->lbl_reservation_details_due_date), due_date);
        gtk_label_set_text(GTK_LABEL(g_data->app_wdgts->user_main_wdgts->lbl_reservation_details_copy_barcode), barcode_string);

        // Enable return book operation
        gtk_widget_set_sensitive(g_data->app_wdgts->user_main_wdgts->btn_return_book, TRUE);

        // Free memory
        free(copy);
        g_free (title);
        g_free (author);
        g_free (reservation_date);
        g_free (due_date);
    }
    else
    {
        // Reset details area
        gtk_label_set_text(GTK_LABEL(g_data->app_wdgts->user_main_wdgts->lbl_reservation_details_book), "None");
        gtk_label_set_text(GTK_LABEL(g_data->app_wdgts->user_main_wdgts->lbl_reservation_details_reservation_date), "None");
        gtk_label_set_text(GTK_LABEL(g_data->app_wdgts->user_main_wdgts->lbl_reservation_details_due_date), "None");
        gtk_label_set_text(GTK_LABEL(g_data->app_wdgts->user_main_wdgts->lbl_reservation_details_copy_barcode), "None");

        // Disable return book operation
        gtk_widget_set_sensitive(g_data->app_wdgts->user_main_wdgts->btn_return_book, FALSE);
    }
}

void on_selection_account_list_changed(GtkTreeSelection *selection, GLOBAL_DATA *g_data)
{
    GtkTreeIter iter; //Iterator to read from list store
    GtkTreeModel *model; //Model for list store
    char *email, *name, *address;   //
    char phone_string[10];          // Variables to hold data read from list store
    int id, phone, type;            //

    // Check if a row is selected in the treeview
    if (gtk_tree_selection_get_selected (selection, &model, &iter))
    {
        // Read data from list store
        gtk_tree_model_get (model, &iter, ACCOUNT_LIST_COL_ID, &id, ACCOUNT_LIST_COL_EMAIL, &email, ACCOUNT_LIST_COL_NAME, &name, ACCOUNT_LIST_COL_ADDRESS, &address, ACCOUNT_LIST_COL_PHONE, &phone, ACCOUNT_LIST_COL_TYPE, &type, -1);

        // Print account data to details area
        sprintf(phone_string, "%d", phone);
        gtk_label_set_text(GTK_LABEL(g_data->app_wdgts->admin_main_wdgts->lbl_account_details_email), email);
        gtk_label_set_text(GTK_LABEL(g_data->app_wdgts->admin_main_wdgts->lbl_account_details_name), name);
        gtk_label_set_text(GTK_LABEL(g_data->app_wdgts->admin_main_wdgts->lbl_account_details_address), address);
        gtk_label_set_text(GTK_LABEL(g_data->app_wdgts->admin_main_wdgts->lbl_account_details_phone), phone_string);
        gtk_label_set_text(GTK_LABEL(g_data->app_wdgts->admin_main_wdgts->lbl_account_details_type), get_account_type(type));

        if(!(g_data->current_user->id == id))
        {
            // If current user selects any account that's not his own, enable account operations
            gtk_widget_set_sensitive(g_data->app_wdgts->admin_main_wdgts->btn_edit_account, TRUE);
            gtk_widget_set_sensitive(g_data->app_wdgts->admin_main_wdgts->btn_delete_account, TRUE);

            // Inject account data to edit account view
            gtk_entry_set_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->edit_account_wdgts->entry_edit_account_email), email);
            gtk_entry_set_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->edit_account_wdgts->entry_edit_account_name), name);
            gtk_entry_set_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->edit_account_wdgts->entry_edit_account_address), address);
            gtk_entry_set_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->edit_account_wdgts->entry_edit_account_phone), phone_string);
            gtk_combo_box_set_active(GTK_COMBO_BOX(g_data->app_wdgts->admin_main_wdgts->edit_account_wdgts->entry_edit_account_type), type);
        }
        else
        {
            // If user selects his account, disable account operations
            gtk_widget_set_sensitive(g_data->app_wdgts->admin_main_wdgts->btn_edit_account, FALSE);
            gtk_widget_set_sensitive(g_data->app_wdgts->admin_main_wdgts->btn_delete_account, FALSE);
        }

        // Free memory
        g_free (email);
        g_free (name);
        g_free (address);
    }
    else
    {
        // Reset details area
        gtk_label_set_text(GTK_LABEL(g_data->app_wdgts->admin_main_wdgts->lbl_account_details_email), "None");
        gtk_label_set_text(GTK_LABEL(g_data->app_wdgts->admin_main_wdgts->lbl_account_details_name), "None");
        gtk_label_set_text(GTK_LABEL(g_data->app_wdgts->admin_main_wdgts->lbl_account_details_address), "None");
        gtk_label_set_text(GTK_LABEL(g_data->app_wdgts->admin_main_wdgts->lbl_account_details_phone), "None");
        gtk_label_set_text(GTK_LABEL(g_data->app_wdgts->admin_main_wdgts->lbl_account_details_type), "None");

        // Disable account operations
        gtk_widget_set_sensitive(g_data->app_wdgts->admin_main_wdgts->btn_edit_account, FALSE);
        gtk_widget_set_sensitive(g_data->app_wdgts->admin_main_wdgts->btn_delete_account, FALSE);
    }
}

void on_selection_reservation_list_changed(GtkTreeSelection *selection, GLOBAL_DATA *g_data)
{
    GtkTreeIter iter; //Iterator to read from list store
    GtkTreeModel *model; //Model for list store
    COPY* copy; // Variable to hold the reserved copy
    ACCOUNT* user; // Variable to hold the reserving user
    char *title, *author, *reservation_date, *due_date; //
    int id_book, id_copy, id_user;                      // Variables to hold data read from list store
    char barcode_string[10]; // Variable to hold copy barcode string

    // Check if a row is selected in the treeview
    if (gtk_tree_selection_get_selected (selection, &model, &iter))
    {
        // Read data from list store
        gtk_tree_model_get (model, &iter, RESERVATION_LIST_COL_ID, &id_book, RESERVATION_LIST_COL_TITLE, &title, RESERVATION_LIST_COL_AUTHOR, &author, RESERVATION_LIST_COL_RESERVATION_DATE, &reservation_date, RESERVATION_LIST_COL_DUE_DATE, &due_date, RESERVATION_LIST_COL_ID_COPY, &id_copy, RESERVATION_LIST_COL_ID_USER, &id_user, -1);

        // Get reserved copy
        copy = search_copy(g_data->copy_list, id_copy);

        // Get reserving user
        user = search_account_in_file(id_user);

        // Print reservation data to details area
        sprintf(barcode_string, "%d", copy->barcode);
        gtk_label_set_text(GTK_LABEL(g_data->app_wdgts->admin_main_wdgts->lbl_admin_reservation_details_book), title);
        gtk_label_set_text(GTK_LABEL(g_data->app_wdgts->admin_main_wdgts->lbl_admin_reservation_details_reservation_date), reservation_date);
        gtk_label_set_text(GTK_LABEL(g_data->app_wdgts->admin_main_wdgts->lbl_admin_reservation_details_due_date), due_date);
        gtk_label_set_text(GTK_LABEL(g_data->app_wdgts->admin_main_wdgts->lbl_admin_reservation_details_copy_barcode), barcode_string);
        gtk_label_set_text(GTK_LABEL(g_data->app_wdgts->admin_main_wdgts->lbl_admin_reservation_details_user), user->name);

        // Enable delete reservation operation
        gtk_widget_set_sensitive(g_data->app_wdgts->admin_main_wdgts->btn_delete_reservation, TRUE);

        free(user);
        free(copy);
    }
    else
    {
        // Reset details area
        gtk_label_set_text(GTK_LABEL(g_data->app_wdgts->admin_main_wdgts->lbl_admin_reservation_details_book), "None");
        gtk_label_set_text(GTK_LABEL(g_data->app_wdgts->admin_main_wdgts->lbl_admin_reservation_details_reservation_date), "None");
        gtk_label_set_text(GTK_LABEL(g_data->app_wdgts->admin_main_wdgts->lbl_admin_reservation_details_due_date), "None");
        gtk_label_set_text(GTK_LABEL(g_data->app_wdgts->admin_main_wdgts->lbl_admin_reservation_details_copy_barcode), "None");
        gtk_label_set_text(GTK_LABEL(g_data->app_wdgts->admin_main_wdgts->lbl_admin_reservation_details_user), "None");

        // Disable delete reservation operation
        gtk_widget_set_sensitive(g_data->app_wdgts->admin_main_wdgts->btn_delete_reservation, FALSE);
    }
}

void on_selection_copy_list_changed(GtkTreeSelection *selection, GLOBAL_DATA *g_data)
{
    GtkTreeIter iter; // Iterator to read from list store
    GtkTreeModel *model; // Model for list store

    // Check if a row is selected in the treeview
    if (gtk_tree_selection_get_selected (selection, &model, &iter))
    {
        // Enable delete copy operation
        gtk_widget_set_sensitive(g_data->app_wdgts->admin_main_wdgts->manage_copies_wdgts->btn_delete_copy, TRUE);
    }
    else
    {
        // Disable delete copy operation
        gtk_widget_set_sensitive(g_data->app_wdgts->admin_main_wdgts->manage_copies_wdgts->btn_delete_copy, FALSE);
    }
}

void on_notebook_main_switch_page(GtkNotebook *notebook, GtkWidget *page, guint page_num, GLOBAL_DATA *g_data)
{
   if(page_num == 0)
   {
        // If Books tab is selected, show book details area and hide others
        gtk_widget_set_visible(g_data->app_wdgts->admin_main_wdgts->box_account_details, FALSE);
        gtk_widget_set_visible(g_data->app_wdgts->admin_main_wdgts->box_admin_reservation_details, FALSE);
        gtk_widget_set_visible(g_data->app_wdgts->admin_main_wdgts->box_book_details, TRUE);
    }
    else if(page_num == 1)
    {
        // If Accounts tab is selected, show account details area and hide others
        gtk_widget_set_visible(g_data->app_wdgts->admin_main_wdgts->box_book_details, FALSE);
        gtk_widget_set_visible(g_data->app_wdgts->admin_main_wdgts->box_admin_reservation_details, FALSE);
        gtk_widget_set_visible(g_data->app_wdgts->admin_main_wdgts->box_account_details, TRUE);
    }
    else if(page_num == 2)
    {
        // If Reservations tab is selected, show reservation details area and hide others
        gtk_widget_set_visible(g_data->app_wdgts->admin_main_wdgts->box_book_details, FALSE);
        gtk_widget_set_visible(g_data->app_wdgts->admin_main_wdgts->box_account_details, FALSE);
        gtk_widget_set_visible(g_data->app_wdgts->admin_main_wdgts->box_admin_reservation_details, TRUE);
    }
}

void on_notebook_user_main_switch_page(GtkNotebook *notebook, GtkWidget *page, guint page_num, GLOBAL_DATA *g_data)
{
   if(page_num == 0)
   {
        // If Books tab is selected, show book details area and hide others
        gtk_widget_set_visible(g_data->app_wdgts->user_main_wdgts->box_reservation_details, FALSE);
        gtk_widget_set_visible(g_data->app_wdgts->user_main_wdgts->box_reservation_book_details, TRUE);
    }
    else if(page_num == 1)
    {
        // If Reservations tab is selected, show reservation details area and hide others
        gtk_widget_set_visible(g_data->app_wdgts->user_main_wdgts->box_reservation_book_details, FALSE);
        gtk_widget_set_visible(g_data->app_wdgts->user_main_wdgts->box_reservation_details, TRUE);
    }
}

void on_menu_item_logout_activate(GtkMenuItem *menuitem, GLOBAL_DATA* g_data)
{
    GtkWidget *toplevel = gtk_widget_get_toplevel (GTK_WIDGET(menuitem)); // Get top level window

    // Logout current user
    g_data->current_user = NULL;

    // Hide current window
    if (GTK_IS_WINDOW (toplevel))
    {
        gtk_widget_hide(toplevel);
    }

    // Show authentication window
    gtk_widget_show(g_data->app_wdgts->auth_wdgts->window_authentication);
}

void on_menu_item_exit_activate()
{
    gtk_main_quit();
}

void on_window_user_main_destroy_event()
{
    gtk_main_quit();
}

void on_window_main_destroy()
{
    gtk_main_quit();
}


