#include "add_copy.h"
#include "books.h"
#include "accounts.h"
#include "copies.h"
#include "reservations.h"
#include "general.h"
#include "gui.h"

void on_btn_add_copy_clicked(GtkButton *button, GLOBAL_DATA *g_data){
    // Show add copy window
    gtk_widget_show(g_data->app_wdgts->admin_main_wdgts->manage_copies_wdgts->add_copy_wdgts->window_add_copy);
}

void on_btn_add_copy_confirm_clicked(GtkButton *button, GLOBAL_DATA *g_data){
    GtkWidget *toplevel = gtk_widget_get_toplevel (GTK_WIDGET(button)); // Get top level window
    GtkTreeIter iter; // Iterator to read from list store
    GtkTreeModel *model; // Model for list store
    GtkTreeSelection *selection; // Book treeview selection to get selected row
    COPY copy; // Variable to hold new copy data
    int id_book; // ID of the book to which the copy is associated

    // Get currently selected book
    selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(g_data->app_wdgts->admin_main_wdgts->treeview_book_list));
    if (gtk_tree_selection_get_selected (selection, &model, &iter))
    {
        // If a book is selected, read book data then create the copy and add it to file
        gtk_tree_model_get (model, &iter, BOOK_LIST_COL_ID, &id_book, -1);
        copy.barcode = gtk_spin_button_get_value(GTK_SPIN_BUTTON(g_data->app_wdgts->admin_main_wdgts->manage_copies_wdgts->add_copy_wdgts->entry_add_copy_barcode));
        copy.id = get_new_copy_id();
        copy.id_book = id_book;
        copy.status = FREE;
        add_copy_to_list(&g_data->copy_list, copy);

        // Render updated copy list
        render_copy_list(g_data, NULL, copy.id_book, 0);

        // Confirm addition and hide add account window
        if (gtk_dialog_run(GTK_DIALOG(g_data->app_wdgts->admin_main_wdgts->manage_copies_wdgts->add_copy_wdgts->dialog_confirm_add_copy)) == GTK_RESPONSE_OK) {
            gtk_widget_hide(g_data->app_wdgts->admin_main_wdgts->manage_copies_wdgts->add_copy_wdgts->dialog_confirm_add_copy);
            if (GTK_IS_WINDOW (toplevel))
            {
                gtk_window_close(GTK_WINDOW(toplevel));
            }
        }
    }
}

void on_btn_add_copy_cancel_clicked(GtkButton* button, GLOBAL_DATA *g_data){

    GtkWidget *toplevel = gtk_widget_get_toplevel (GTK_WIDGET(button)); // Get top level window

    // Hide current window
    if (GTK_IS_WINDOW (toplevel))
    {
        gtk_window_close(GTK_WINDOW(toplevel));
    }
}

gboolean on_window_add_copy_delete_event(GtkWidget *window, GdkEvent *event, GLOBAL_DATA *g_data){
    // Reset add copy entries
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(g_data->app_wdgts->admin_main_wdgts->manage_copies_wdgts->add_copy_wdgts->entry_add_copy_barcode), 1);

    // Hide add copy window
    return gtk_widget_hide_on_delete(window);
}
