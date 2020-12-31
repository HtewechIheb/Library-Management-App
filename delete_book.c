#include "delete_book.h"
#include "books.h"
#include "accounts.h"
#include "copies.h"
#include "reservations.h"
#include "general.h"
#include "gui.h"

void on_btn_delete_book_clicked(GtkButton *button, GLOBAL_DATA *g_data)
{
    GtkTreeIter iter; // Iterator to read from list store
    GtkTreeModel *model; // Model for list store
    GtkTreeSelection *selection; // Book treeview selection to get selected row
    int id; // Variable to hold book ID

    // Get currently selected book
    selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(g_data->app_wdgts->admin_main_wdgts->treeview_book_list));
    if (gtk_tree_selection_get_selected (selection, &model, &iter))
    {
            // If a book is selected, read book data then delete it
            gtk_tree_model_get (model, &iter, BOOK_LIST_COL_ID, &id, -1);

            // Run verification dialog before deletion
            if(gtk_dialog_run(GTK_DIALOG(g_data->app_wdgts->admin_main_wdgts->delete_book_wdgts->dialog_verify_delete_book)) == GTK_RESPONSE_ACCEPT)
            {
                remove_book(&g_data->reservation_list, &g_data->copy_list, &g_data->book_list, id);

                // Render updated book treeview
                render_book_list(g_data, NULL, 0);

                // Render updated copy treeview
                render_copy_list(g_data, NULL, -1, 1);

                // Render updated reservation treeview
                render_reservation_list(g_data, NULL, 0);

                // Confirm deletion and hide verification dialog
                if(gtk_dialog_run(GTK_DIALOG(g_data->app_wdgts->admin_main_wdgts->delete_book_wdgts->dialog_confirm_delete_book)) == GTK_RESPONSE_OK)
                {
                    gtk_widget_hide(g_data->app_wdgts->admin_main_wdgts->delete_book_wdgts->dialog_confirm_delete_book);
                };
            };
            gtk_widget_hide(g_data->app_wdgts->admin_main_wdgts->delete_book_wdgts->dialog_verify_delete_book);
    }
}

gboolean on_dialog_verify_delete_book_delete_event(GtkWidget *window, GdkEvent *event, GLOBAL_DATA *g_data)
{
    // Hide verification dialog
    return gtk_widget_hide_on_delete(window);
}
