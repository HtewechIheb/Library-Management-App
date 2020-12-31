#include <stdlib.h>
#include "search_account.h"
#include "books.h"
#include "accounts.h"
#include "copies.h"
#include "reservations.h"
#include "general.h"
#include "gui.h"

void on_btn_search_account_clicked(GtkButton *button, GLOBAL_DATA *g_data)
{
    // Show search account window
    gtk_widget_show(g_data->app_wdgts->admin_main_wdgts->search_account_wdgts->window_search_account);
}

void on_btn_search_account_confirm_clicked(GtkButton* button, GLOBAL_DATA *g_data)
{
    GtkWidget *toplevel = gtk_widget_get_toplevel (GTK_WIDGET(button)); // Get top level window
    ACCOUNT_NODE* search_result; // Linked list to hold search result

    // Search accounts using entries data
    search_result = search_accounts_in_file(
        gtk_entry_get_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->search_account_wdgts->entry_search_account_email)),
        gtk_entry_get_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->search_account_wdgts->entry_search_account_name)),
        gtk_entry_get_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->search_account_wdgts->entry_search_account_address)),
        !strcmp(gtk_entry_get_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->search_account_wdgts->entry_search_account_phone)), "") ? -1 : atoi(gtk_entry_get_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->search_account_wdgts->entry_search_account_phone))),
        (gtk_combo_box_get_active(GTK_COMBO_BOX(g_data->app_wdgts->admin_main_wdgts->search_account_wdgts->entry_search_account_type))) == 2 ? -1 : (ACCOUNT_TYPE)gtk_combo_box_get_active(GTK_COMBO_BOX(g_data->app_wdgts->admin_main_wdgts->search_account_wdgts->entry_search_account_type))
    );

    // Render search result in treeview
    render_account_list(g_data, search_result, 1);

    // Hide current window
    if (GTK_IS_WINDOW (toplevel))
    {
        gtk_window_close(GTK_WINDOW(toplevel));
    }

    // Free memory
    free_account_list(&search_result);
}

void on_btn_search_account_cancel_clicked(GtkButton* button, GLOBAL_DATA *g_data)
{
    GtkWidget *toplevel = gtk_widget_get_toplevel (GTK_WIDGET(button)); // Get top level window

    // Hide current window
    if (GTK_IS_WINDOW (toplevel))
    {
        gtk_window_close(GTK_WINDOW(toplevel));
    }
}

gboolean on_window_search_account_delete_event(GtkWidget *window, GdkEvent *event, GLOBAL_DATA *g_data)
{
    // Reset search entries
    gtk_entry_set_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->search_account_wdgts->entry_search_account_email), "");
    gtk_entry_set_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->search_account_wdgts->entry_search_account_name), "");
    gtk_entry_set_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->search_account_wdgts->entry_search_account_address), "");
    gtk_entry_set_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->search_account_wdgts->entry_search_account_phone), "");

    // Hide search window
    return gtk_widget_hide_on_delete(window);
}



