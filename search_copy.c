#include "search_copy.h"
#include "books.h"
#include "accounts.h"
#include "copies.h"
#include "reservations.h"
#include "general.h"
#include "gui.h"

void on_btn_search_copy_clicked(GtkButton *button, GLOBAL_DATA *g_data)
{
    // Show search book window
    gtk_widget_show(g_data->app_wdgts->admin_main_wdgts->manage_copies_wdgts->search_copy_wdgts->window_search_copy);
}

void on_btn_search_copy_confirm_clicked(GtkButton* button, GLOBAL_DATA *g_data)
{
    GtkWidget *toplevel = gtk_widget_get_toplevel (GTK_WIDGET(button)); // Get top level window
    COPY_NODE* search_result; // Linked list to hold search result
    GtkTreeIter iter; // Iterator to read from list store
    GtkTreeModel *model; // Model for list store
    GtkTreeSelection *selection; // Copy treeview selection to get selected row
    int id; // Variable to hold copy ID

    // Get currently selected book
    selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(g_data->app_wdgts->admin_main_wdgts->treeview_book_list));
    // If a book is selected, read its ID
    if (gtk_tree_selection_get_selected (selection, &model, &iter))
    {
            gtk_tree_model_get (model, &iter, BOOK_LIST_COL_ID, &id, -1);
    }

    // Search copies using entries data
    search_result = search_copies(
        g_data->copy_list,
        (int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(g_data->app_wdgts->admin_main_wdgts->manage_copies_wdgts->search_copy_wdgts->entry_search_copy_barcode)),
        id,
        (gtk_combo_box_get_active(GTK_COMBO_BOX(g_data->app_wdgts->admin_main_wdgts->manage_copies_wdgts->search_copy_wdgts->entry_search_copy_status)) == 2) ? -1 : (COPY_STATUS)gtk_combo_box_get_active(GTK_COMBO_BOX(g_data->app_wdgts->admin_main_wdgts->manage_copies_wdgts->search_copy_wdgts->entry_search_copy_status))
    );

    // Render search result in treeview
    render_copy_list(g_data, search_result, id,1);

    // Hide current window
    if (GTK_IS_WINDOW (toplevel))
    {
        gtk_window_close(GTK_WINDOW(toplevel));
    }

    // Free memory
    free_copy_list(&search_result);
}

void on_btn_search_copy_cancel_clicked(GtkButton* button, GLOBAL_DATA *g_data)
{
    GtkWidget *toplevel = gtk_widget_get_toplevel (GTK_WIDGET(button)); // Get top level window

    // Hide current window
    if (GTK_IS_WINDOW (toplevel))
    {
        gtk_window_close(GTK_WINDOW(toplevel));
    }
}

gboolean on_window_search_copy_delete_event(GtkWidget *window, GdkEvent *event, GLOBAL_DATA *g_data)
{
    // Reset search entries
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(g_data->app_wdgts->admin_main_wdgts->manage_copies_wdgts->search_copy_wdgts->entry_search_copy_barcode), 0);

    // Hide search window
    return gtk_widget_hide_on_delete(window);
}


