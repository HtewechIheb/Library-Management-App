#include "search_book.h"
#include "books.h"
#include "accounts.h"
#include "copies.h"
#include "reservations.h"
#include "general.h"
#include "gui.h"

void on_btn_search_book_clicked(GtkButton *button, GLOBAL_DATA *g_data)
{
    // Show search book window
    gtk_widget_show(g_data->app_wdgts->admin_main_wdgts->search_book_wdgts->window_search_book);
}

void on_btn_search_book_confirm_clicked(GtkButton* button, GLOBAL_DATA *g_data)
{
    GtkWidget *toplevel = gtk_widget_get_toplevel (GTK_WIDGET(button)); // Get top level window
    BOOK_NODE* search_result; // Linked list to hold search result

    // Search books using entries data
    search_result = search_books(
        g_data->book_list,
        gtk_entry_get_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->search_book_wdgts->entry_search_book_title)),
        gtk_entry_get_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->search_book_wdgts->entry_search_book_subject)),
        gtk_entry_get_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->search_book_wdgts->entry_search_book_author)),
        gtk_entry_get_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->search_book_wdgts->entry_search_book_language)),
        gtk_spin_button_get_value(GTK_SPIN_BUTTON(g_data->app_wdgts->admin_main_wdgts->search_book_wdgts->entry_search_book_number_of_pages))
    );

    // Render search result in treeview
    render_book_list(g_data, search_result, 1);

    // Hide current window
    if (GTK_IS_WINDOW (toplevel))
    {
        gtk_window_close(GTK_WINDOW(toplevel));
    }

    // Free memory
    free_book_list(&search_result);
}

void on_btn_search_book_cancel_clicked(GtkButton* button, GLOBAL_DATA *g_data)
{
    GtkWidget *toplevel = gtk_widget_get_toplevel (GTK_WIDGET(button)); // Get top level window

    // Hide current window
    if (GTK_IS_WINDOW (toplevel))
    {
        gtk_window_close(GTK_WINDOW(toplevel));
    }
}

gboolean on_window_search_book_delete_event(GtkWidget *window, GdkEvent *event, GLOBAL_DATA *g_data)
{
    // Reset search entries
    gtk_entry_set_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->search_book_wdgts->entry_search_book_title), "");
    gtk_entry_set_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->search_book_wdgts->entry_search_book_subject), "");
    gtk_entry_set_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->search_book_wdgts->entry_search_book_author), "");
    gtk_entry_set_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->search_book_wdgts->entry_search_book_language), "");
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(g_data->app_wdgts->admin_main_wdgts->search_book_wdgts->entry_search_book_number_of_pages), 0);

    // Hide search window
    return gtk_widget_hide_on_delete(window);
}

