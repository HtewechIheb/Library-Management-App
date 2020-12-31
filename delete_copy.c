#include "delete_copy.h"
#include "books.h"
#include "accounts.h"
#include "copies.h"
#include "reservations.h"
#include "general.h"
#include "gui.h"

void on_btn_delete_copy_clicked(GtkButton *button, GLOBAL_DATA *g_data)
{
    GtkTreeIter iter; // Iterator to read from list store
    GtkTreeModel *model; // Model for list store
    GtkTreeSelection *selection; // Copy treeview selection to get selected row
    int id, barcode, id_book;   //
    COPY_STATUS status;         // Variables to hold copy data

    // Get currently selected copy
    selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(g_data->app_wdgts->admin_main_wdgts->manage_copies_wdgts->treeview_copy_list));
    if (gtk_tree_selection_get_selected (selection, &model, &iter))
    {
            // If a copy is selected, read copy data then delete it
            gtk_tree_model_get (model, &iter, COPY_LIST_COL_ID, &id, COPY_LIST_COL_BARCODE, &barcode, COPY_LIST_COL_STATUS, &status, COPY_LIST_COL_ID_BOOK, &id_book, -1);

            // Run verification dialog before deletion
            if(gtk_dialog_run(GTK_DIALOG(g_data->app_wdgts->admin_main_wdgts->manage_copies_wdgts->delete_copy_wdgts->dialog_verify_delete_copy)) == GTK_RESPONSE_ACCEPT)
            {
                remove_copy_from_list(&g_data->reservation_list, &g_data->copy_list, id);

                // Render updated copy treeview
                render_copy_list(g_data, NULL, id_book, 0);

                // Render updated reservation treeview
                render_reservation_list(g_data, NULL, 0);

                // Confirm deletion and hide verification dialog
                if(gtk_dialog_run(GTK_DIALOG(g_data->app_wdgts->admin_main_wdgts->manage_copies_wdgts->delete_copy_wdgts->dialog_confirm_delete_copy)) == GTK_RESPONSE_OK)
                {
                    gtk_widget_hide(g_data->app_wdgts->admin_main_wdgts->manage_copies_wdgts->delete_copy_wdgts->dialog_confirm_delete_copy);
                };
            };
            gtk_widget_hide(g_data->app_wdgts->admin_main_wdgts->manage_copies_wdgts->delete_copy_wdgts->dialog_verify_delete_copy);
    }
}

gboolean on_dialog_verify_delete_copy_delete_event(GtkWidget *window, GdkEvent *event, GLOBAL_DATA *g_data)
{
    // Hide verification dialog
    return gtk_widget_hide_on_delete(window);
}

