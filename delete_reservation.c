#include "delete_reservation.h"
#include "books.h"
#include "accounts.h"
#include "copies.h"
#include "reservations.h"
#include "general.h"
#include "gui.h"

void on_btn_delete_reservation_clicked(GtkToolButton *toolbutton, GLOBAL_DATA* g_data)
{
    GtkTreeIter iter; // Iterator to read from list store
    GtkTreeModel *model; // Model for list store
    GtkTreeSelection *selection; // Reservation treeview selection to get selected row
    int id; // Variable to hold reservation ID

    // Get currently selected reservation
    selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(g_data->app_wdgts->admin_main_wdgts->treeview_reservation_list));
    if (gtk_tree_selection_get_selected (selection, &model, &iter))
    {
            // If a reservation is selected, read reservation data then delete it
            gtk_tree_model_get (model, &iter, RESERVATION_BOOK_LIST_COL_ID, &id, -1);

            // Run verification dialog before deletion
            if(gtk_dialog_run(GTK_DIALOG(g_data->app_wdgts->admin_main_wdgts->delete_reservation_wdgts->dialog_verify_delete_reservation)) == GTK_RESPONSE_ACCEPT)
            {
                remove_reservation_from_list(&g_data->reservation_list, g_data->copy_list, id);

                // Render updated reservation treeview
                render_reservation_list(g_data, NULL, 0);

                // Confirm deletion and hide verification dialog
                if(gtk_dialog_run(GTK_DIALOG(g_data->app_wdgts->admin_main_wdgts->delete_reservation_wdgts->dialog_confirm_delete_reservation)) == GTK_RESPONSE_OK)
                {
                    gtk_widget_hide(g_data->app_wdgts->admin_main_wdgts->delete_reservation_wdgts->dialog_confirm_delete_reservation);
                };
            };
            gtk_widget_hide(g_data->app_wdgts->admin_main_wdgts->delete_reservation_wdgts->dialog_verify_delete_reservation);
    }
}

gboolean on_dialog_verify_delete_reservation_delete_event(GtkWidget *window, GdkEvent *event, GLOBAL_DATA *g_data)
{
    // Hide verification dialog
    return gtk_widget_hide_on_delete(window);
}

