#include "delete_account.h"
#include "books.h"
#include "accounts.h"
#include "copies.h"
#include "reservations.h"
#include "general.h"
#include "gui.h"

void on_btn_delete_account_clicked(GtkButton *button, GLOBAL_DATA *g_data)
{
    GtkTreeIter iter; // Iterator to read from list store
    GtkTreeModel *model; // Model for list store
    GtkTreeSelection *selection; // Account treeview selection to get selected row
    int id; // Variable to hold account ID

    // Get currently selected account
    selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(g_data->app_wdgts->admin_main_wdgts->treeview_account_list));
    if (gtk_tree_selection_get_selected (selection, &model, &iter))
    {
            // If an account is selected, read account data then delete it
            gtk_tree_model_get (model, &iter, 0, &id, -1);

            // Run verification dialog before deletion
            if(gtk_dialog_run(GTK_DIALOG(g_data->app_wdgts->admin_main_wdgts->delete_account_wdgts->dialog_verify_delete_account)) == GTK_RESPONSE_ACCEPT)
            {
                remove_account_from_file(&g_data->reservation_list, g_data->copy_list, id);

                // Render updated account treeview
                render_account_list(g_data, NULL, 0);

                // Confirm deletion and hide verification dialog
                if(gtk_dialog_run(GTK_DIALOG(g_data->app_wdgts->admin_main_wdgts->delete_account_wdgts->dialog_confirm_delete_account)) == GTK_RESPONSE_OK)
                {
                    gtk_widget_hide(g_data->app_wdgts->admin_main_wdgts->delete_account_wdgts->dialog_confirm_delete_account);
                };
            };
            gtk_widget_hide(g_data->app_wdgts->admin_main_wdgts->delete_account_wdgts->dialog_verify_delete_account);
    }
}

gboolean on_dialog_verify_delete_account_delete_event(GtkWidget *window, GdkEvent *event, GLOBAL_DATA *g_data)
{
    // Hide verification dialog
    return gtk_widget_hide_on_delete(window);
}
