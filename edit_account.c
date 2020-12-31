#include <ctype.h>
#include "edit_account.h"
#include "books.h"
#include "accounts.h"
#include "copies.h"
#include "reservations.h"
#include "general.h"
#include "gui.h"

void on_btn_edit_account_clicked(GtkButton *button, GLOBAL_DATA *g_data)
{
    // Show edit account window
    gtk_widget_show(g_data->app_wdgts->admin_main_wdgts->edit_account_wdgts->window_edit_account);
}

void on_btn_edit_account_confirm_clicked(GtkButton* button, GLOBAL_DATA *g_data)
{
    GtkTreeIter iter; // Iterator to read from list store
    GtkTreeModel *model; // Model for list store
    GtkTreeSelection *selection; // Account treeview selection to get selected row
    ACCOUNT account; // Variable to hold new account data
    int id; // Variable to hold account ID
    GtkWidget *toplevel = gtk_widget_get_toplevel (GTK_WIDGET(button)); // Get top level window
    gboolean valid = TRUE; // Variable to test validity of the entries

    // If entry is empty, show error message and set validity to false
    if(!strlen(gtk_entry_get_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->edit_account_wdgts->entry_edit_account_email))))
    {
        gtk_widget_set_visible(g_data->app_wdgts->admin_main_wdgts->edit_account_wdgts->error_edit_account_email_required, TRUE);
        valid = FALSE;
    }
    if(!strlen(gtk_entry_get_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->edit_account_wdgts->entry_edit_account_password))))
    {
        gtk_widget_set_visible(g_data->app_wdgts->admin_main_wdgts->edit_account_wdgts->error_edit_account_password_required, TRUE);
        valid = FALSE;
    }
    if(!strlen(gtk_entry_get_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->edit_account_wdgts->entry_edit_account_name))))
    {
        gtk_widget_set_visible(g_data->app_wdgts->admin_main_wdgts->edit_account_wdgts->error_edit_account_name_required, TRUE);
        valid = FALSE;
    }
    if(!strlen(gtk_entry_get_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->edit_account_wdgts->entry_edit_account_address))))
    {
        gtk_widget_set_visible(g_data->app_wdgts->admin_main_wdgts->edit_account_wdgts->error_edit_account_address_required, TRUE);
        valid = FALSE;
    }
    if(!strlen(gtk_entry_get_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->edit_account_wdgts->entry_edit_account_phone))))
    {
        gtk_widget_set_visible(g_data->app_wdgts->admin_main_wdgts->edit_account_wdgts->error_edit_account_phone_required, TRUE);
        valid = FALSE;
    }

    // If phone is less than 8 digits, show error message and set validity to false
    if(strlen(gtk_entry_get_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->edit_account_wdgts->entry_edit_account_phone))) < 8)
    {
        gtk_widget_set_visible(g_data->app_wdgts->admin_main_wdgts->edit_account_wdgts->error_edit_account_phone_invalid, TRUE);
        valid = FALSE;
    }


    if(valid)
    {
        // Read selected account ID
        selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(g_data->app_wdgts->admin_main_wdgts->treeview_account_list));
        if (gtk_tree_selection_get_selected (selection, &model, &iter))
        {
                gtk_tree_model_get (model, &iter, ACCOUNT_LIST_COL_ID, &id, -1);
        }

        // Edit account and add it to file
        account = new_account(
            gtk_entry_get_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->edit_account_wdgts->entry_edit_account_email)),
            gtk_entry_get_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->edit_account_wdgts->entry_edit_account_password)),
            gtk_entry_get_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->edit_account_wdgts->entry_edit_account_name)),
            gtk_entry_get_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->edit_account_wdgts->entry_edit_account_address)),
            atoi(gtk_entry_get_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->edit_account_wdgts->entry_edit_account_phone))),
            (ACCOUNT_TYPE)gtk_combo_box_get_active(GTK_COMBO_BOX(g_data->app_wdgts->admin_main_wdgts->edit_account_wdgts->entry_edit_account_type))
        );
        account.id = id;
        edit_account_in_file(account);

        // Render updated account treeview
        render_account_list(g_data, NULL, 0);

        // Confirm edition and hide add account window
        if (gtk_dialog_run(GTK_DIALOG(g_data->app_wdgts->admin_main_wdgts->edit_account_wdgts->dialog_confirm_edit_account)) == GTK_RESPONSE_OK)
        {
            gtk_widget_hide(g_data->app_wdgts->admin_main_wdgts->edit_account_wdgts->dialog_confirm_edit_account);
            if (GTK_IS_WINDOW (toplevel))
            {
                gtk_window_close(GTK_WINDOW(toplevel));
            }
        }
    }
}

void on_btn_edit_account_cancel_clicked(GtkButton* button, GLOBAL_DATA *g_data)
{
    GtkWidget *toplevel = gtk_widget_get_toplevel (GTK_WIDGET(button)); // Get top level window

    // Hide current window
    if (GTK_IS_WINDOW (toplevel))
    {
        gtk_window_close(GTK_WINDOW(toplevel));
    }
}

void on_entry_edit_account_phone_insert_text(GtkEntry *entry, const gchar *text, gint length, gint *position, GLOBAL_DATA *g_data)
{
    GtkEditable *editable = GTK_EDITABLE (entry); // Get phone entry
    int i;

    for (i=0; i < length; i++)
    {
        // Loop through the inserted text and if it contains ahything other than digits, stop the insertion
        if (!isdigit(text[i])){
            g_signal_stop_emission_by_name(G_OBJECT (editable), "insert_text");
            return;
        }
    }
}

void on_edit_account_entry_changed(GtkEditable* editable, GLOBAL_DATA *g_data)
{
    GtkWidget *toplevel = gtk_widget_get_toplevel (GTK_WIDGET(editable)); // Get top level window
    const char* editable_name = gtk_widget_get_name(GTK_WIDGET(editable)); // Get changed entry
    if(!strcmp(editable_name, "n_entry_edit_account_email"))
    {
        // If entry is not empty, hide error message
        if(strlen(gtk_entry_get_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->edit_account_wdgts->entry_edit_account_email))))
        {
            gtk_widget_set_visible(g_data->app_wdgts->admin_main_wdgts->edit_account_wdgts->error_edit_account_email_required, FALSE);
            // Resize window to adapt to error message displays
            if (GTK_IS_WINDOW (toplevel))
            {
                gtk_window_resize(GTK_WINDOW(toplevel), 1, 1);
            }
        }
        else{
            gtk_widget_set_visible(g_data->app_wdgts->admin_main_wdgts->edit_account_wdgts->error_edit_account_email_required, TRUE);
        }

    }
    else if(!strcmp(editable_name, "n_entry_edit_account_password")){
        if(strlen(gtk_entry_get_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->edit_account_wdgts->entry_edit_account_password))))
        {
            gtk_widget_set_visible(g_data->app_wdgts->admin_main_wdgts->edit_account_wdgts->error_edit_account_password_required, FALSE);
            if (GTK_IS_WINDOW (toplevel))
            {
                gtk_window_resize(GTK_WINDOW(toplevel), 1, 1);
            }
        }
        else{
            gtk_widget_set_visible(g_data->app_wdgts->admin_main_wdgts->edit_account_wdgts->error_edit_account_password_required, TRUE);
        }
    }
    else if(!strcmp(editable_name, "n_entry_edit_account_name")){
        if(strlen(gtk_entry_get_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->edit_account_wdgts->entry_edit_account_name))))
        {
            gtk_widget_set_visible(g_data->app_wdgts->admin_main_wdgts->edit_account_wdgts->error_edit_account_name_required, FALSE);
            if (GTK_IS_WINDOW (toplevel))
            {
                gtk_window_resize(GTK_WINDOW(toplevel), 1, 1);
            }
        }
        else{
            gtk_widget_set_visible(g_data->app_wdgts->admin_main_wdgts->edit_account_wdgts->error_edit_account_name_required, TRUE);
        }
    }
    else if(!strcmp(editable_name, "n_entry_edit_account_address")){
        if(strlen(gtk_entry_get_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->edit_account_wdgts->entry_edit_account_address))))
        {
            gtk_widget_set_visible(g_data->app_wdgts->admin_main_wdgts->edit_account_wdgts->error_edit_account_address_required, FALSE);
            if (GTK_IS_WINDOW (toplevel))
            {
                gtk_window_resize(GTK_WINDOW(toplevel), 1, 1);
            }
        }
        else{
            gtk_widget_set_visible(g_data->app_wdgts->admin_main_wdgts->edit_account_wdgts->error_edit_account_address_required, TRUE);
        }
    }
    else if(!strcmp(editable_name, "n_entry_edit_account_phone")){
        if(strlen(gtk_entry_get_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->edit_account_wdgts->entry_edit_account_phone))))
        {
            gtk_widget_set_visible(g_data->app_wdgts->admin_main_wdgts->edit_account_wdgts->error_edit_account_phone_required, FALSE);
            // If phone is less than 8 digits, show error message
            if(strlen(gtk_entry_get_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->edit_account_wdgts->entry_edit_account_phone))) < 8)
            {
                gtk_widget_set_visible(g_data->app_wdgts->admin_main_wdgts->edit_account_wdgts->error_edit_account_phone_invalid, TRUE);
            }
            else{
                gtk_widget_set_visible(g_data->app_wdgts->admin_main_wdgts->edit_account_wdgts->error_edit_account_phone_invalid, FALSE);
            }
            if (GTK_IS_WINDOW (toplevel))
            {
                gtk_window_resize(GTK_WINDOW(toplevel), 1, 1);
            }
        }
        else{
            gtk_widget_set_visible(g_data->app_wdgts->admin_main_wdgts->edit_account_wdgts->error_edit_account_phone_required, TRUE);
        }
    }
}

gboolean on_window_edit_account_delete_event(GtkWidget *window, GdkEvent *event, GLOBAL_DATA *g_data)
{
    // Hide edit account window
    return gtk_widget_hide_on_delete(window);
}




