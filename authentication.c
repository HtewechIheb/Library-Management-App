#include "authentication.h"
#include "books.h"
#include "accounts.h"
#include "copies.h"
#include "reservations.h"
#include "general.h"
#include "gui.h"

void on_authentication_entry_changed(GtkEditable* editable, GLOBAL_DATA *g_data)
{
    GtkWidget *toplevel = gtk_widget_get_toplevel (GTK_WIDGET(editable)); // Get top level window
    const char* editable_name = gtk_widget_get_name(GTK_WIDGET(editable)); // Get changed entry

    if(!strcmp(editable_name, "n_entry_authentication_email"))
    {
        // If entry is not empty, hide error message
        if(strlen(gtk_entry_get_text(GTK_ENTRY(g_data->app_wdgts->auth_wdgts->entry_authentication_email))))
        {
            gtk_widget_set_visible(g_data->app_wdgts->auth_wdgts->error_authentication_email_required, FALSE);

            // Resize window to adapt to error message displays
            if (GTK_IS_WINDOW (toplevel))
            {
                gtk_window_resize(GTK_WINDOW(toplevel), 1, 1);
            }
        }
        else
        {
            gtk_widget_set_visible(g_data->app_wdgts->auth_wdgts->error_authentication_email_required, TRUE);
        }

    }
    else if(!strcmp(editable_name, "n_entry_authentication_password"))
    {
        if(strlen(gtk_entry_get_text(GTK_ENTRY(g_data->app_wdgts->auth_wdgts->entry_authentication_password))))
        {
            gtk_widget_set_visible(g_data->app_wdgts->auth_wdgts->error_authentication_password_required, FALSE);
            if (GTK_IS_WINDOW (toplevel))
            {
                gtk_window_resize(GTK_WINDOW(toplevel), 1, 1);
            }
        }
        else
        {
            gtk_widget_set_visible(g_data->app_wdgts->auth_wdgts->error_authentication_password_required, TRUE);
        }
    }
}

void on_btn_authentication_login_clicked(GtkButton *button, GLOBAL_DATA *g_data)
{
    GtkWidget *toplevel = gtk_widget_get_toplevel (GTK_WIDGET(button)); // Get to level window
    char *email = gtk_entry_get_text(GTK_ENTRY(g_data->app_wdgts->auth_wdgts->entry_authentication_email)); // Typed email
    char *password = gtk_entry_get_text(GTK_ENTRY(g_data->app_wdgts->auth_wdgts->entry_authentication_password)); // Typed password
    gboolean valid = TRUE; // Variable to test validity of entries

    // If entry is empty, show error message and set validity to false
    if(!strlen(gtk_entry_get_text(GTK_ENTRY(g_data->app_wdgts->auth_wdgts->entry_authentication_email))))
    {
        gtk_widget_set_visible(g_data->app_wdgts->auth_wdgts->error_authentication_email_required, TRUE);
        valid = FALSE;
    }
    if(!strlen(gtk_entry_get_text(GTK_ENTRY(g_data->app_wdgts->auth_wdgts->entry_authentication_password))))
    {
        gtk_widget_set_visible(g_data->app_wdgts->auth_wdgts->error_authentication_password_required, TRUE);
        valid = FALSE;
    }


    if(valid)
    {
        // Attempt to authenticate user with typed coordinates
        g_data->current_user = authenticate_from_file(email, password);

        // If authentication succeeded
        if(g_data->current_user)
        {
            // Hide current window
            if (GTK_IS_WINDOW (toplevel))
            {
                gtk_widget_hide(toplevel);
            }

            // Show main window and render treeviews according to user type
            if(g_data->current_user->type == USER)
            {

                render_reservation_book_list(g_data, NULL, 0);
                render_reserved_book_list(g_data, NULL, 0);

                gtk_widget_show(g_data->app_wdgts->user_main_wdgts->window_user_main);
            }
            else if(g_data->current_user->type == ADMIN)
            {
                render_book_list(g_data, NULL, 0);
                render_account_list(g_data, NULL, 0);
                render_reservation_list(g_data, NULL, 0);

                gtk_widget_show(g_data->app_wdgts->admin_main_wdgts->window_admin_main);
            }

            // Reset authentication entries
            gtk_entry_set_text(GTK_ENTRY(g_data->app_wdgts->auth_wdgts->entry_authentication_email), "");
            gtk_entry_set_text(GTK_ENTRY(g_data->app_wdgts->auth_wdgts->entry_authentication_password), "");

            // Hide error messages
            gtk_widget_set_visible(g_data->app_wdgts->auth_wdgts->error_authentication_email_required, FALSE);
            gtk_widget_set_visible(g_data->app_wdgts->auth_wdgts->error_authentication_password_required, FALSE);
        }
        else
        {
            // Reset authentication entries
            gtk_entry_set_text(GTK_ENTRY(g_data->app_wdgts->auth_wdgts->entry_authentication_email), "");
            gtk_entry_set_text(GTK_ENTRY(g_data->app_wdgts->auth_wdgts->entry_authentication_password), "");

            // Hide error messages
            gtk_widget_set_visible(g_data->app_wdgts->auth_wdgts->error_authentication_email_required, FALSE);
            gtk_widget_set_visible(g_data->app_wdgts->auth_wdgts->error_authentication_password_required, FALSE);

            // Show failed authentication dialog
            if(gtk_dialog_run(GTK_DIALOG(g_data->app_wdgts->auth_wdgts->dialog_failed_authentication)) == GTK_RESPONSE_OK)
            {
                gtk_widget_hide(g_data->app_wdgts->auth_wdgts->dialog_failed_authentication);
            }
        }
    }
}


void on_btn_authentication_exit_clicked()
{
    gtk_main_quit();
}

void on_window_authentication_destroy()
{
    gtk_main_quit();
}
