#include "add_book.h"
#include "books.h"
#include "accounts.h"
#include "copies.h"
#include "reservations.h"
#include "general.h"
#include "gui.h"

void on_btn_add_book_clicked(GtkButton *button, GLOBAL_DATA *g_data)
{
    // Show add book window
    gtk_widget_show(g_data->app_wdgts->admin_main_wdgts->add_book_wdgts->window_add_book);
}

void on_btn_add_book_confirm_clicked(GtkButton* button, GLOBAL_DATA *g_data)
{
    GtkWidget *toplevel = gtk_widget_get_toplevel (GTK_WIDGET(button)); // Get top level window
    BOOK book; // Variable to hold new book data
    gboolean valid = TRUE; // Variable to test validity of entries

    // If entry is empty, show error message and set validity to false
    if(!strlen(gtk_entry_get_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->add_book_wdgts->entry_add_book_title))))
    {
        gtk_widget_set_visible(g_data->app_wdgts->admin_main_wdgts->add_book_wdgts->error_add_book_title_required, TRUE);
        valid = FALSE;
    }
    if(!strlen(gtk_entry_get_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->add_book_wdgts->entry_add_book_subject))))
    {
        gtk_widget_set_visible(g_data->app_wdgts->admin_main_wdgts->add_book_wdgts->error_add_book_subject_required, TRUE);
        valid = FALSE;
    }
    if(!strlen(gtk_entry_get_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->add_book_wdgts->entry_add_book_author))))
    {
        gtk_widget_set_visible(g_data->app_wdgts->admin_main_wdgts->add_book_wdgts->error_add_book_author_required, TRUE);
        valid = FALSE;
    }
    if(!strlen(gtk_entry_get_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->add_book_wdgts->entry_add_book_language))))
    {
        gtk_widget_set_visible(g_data->app_wdgts->admin_main_wdgts->add_book_wdgts->error_add_book_language_required, TRUE);
        valid = FALSE;
    }

    if(valid)
    {
        // Create book and add it to file
        book.id = get_new_book_id();
        strcpy(book.title, gtk_entry_get_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->add_book_wdgts->entry_add_book_title)));
        strcpy(book.subject, gtk_entry_get_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->add_book_wdgts->entry_add_book_subject)));
        strcpy(book.author, gtk_entry_get_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->add_book_wdgts->entry_add_book_author)));
        strcpy(book.language, gtk_entry_get_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->add_book_wdgts->entry_add_book_language)));
        book.number_of_pages = gtk_spin_button_get_value(GTK_SPIN_BUTTON(g_data->app_wdgts->admin_main_wdgts->add_book_wdgts->entry_add_book_number_of_pages));
        add_book(&g_data->book_list, book);

        // Render updated book treeview
        render_book_list(g_data, NULL, 0);

        // Confirm addition and hide add account window
        if (gtk_dialog_run(GTK_DIALOG(g_data->app_wdgts->admin_main_wdgts->add_book_wdgts->dialog_confirm_add_book)) == GTK_RESPONSE_OK)
        {
            gtk_widget_hide(g_data->app_wdgts->admin_main_wdgts->add_book_wdgts->dialog_confirm_add_book);
            if (GTK_IS_WINDOW (toplevel))
            {
                gtk_window_close(GTK_WINDOW(toplevel));
            }
        }
    }
}

void on_btn_add_book_cancel_clicked(GtkButton* button, GLOBAL_DATA *g_data)
{
    GtkWidget *toplevel = gtk_widget_get_toplevel (GTK_WIDGET(button)); // Get top level window

    // Hide current window
    if (GTK_IS_WINDOW (toplevel))
    {
        gtk_window_close(GTK_WINDOW(toplevel));
    }
}

void on_add_book_entry_changed(GtkEditable* editable, GLOBAL_DATA *g_data)
{
    GtkWidget *toplevel = gtk_widget_get_toplevel (GTK_WIDGET(editable)); // Get top level window
    const char* editable_name = gtk_widget_get_name(GTK_WIDGET(editable)); // Get changed entry

    if(!strcmp(editable_name, "n_entry_add_book_title"))
    {
        // If entry is not empty, hide error message
        if(strlen(gtk_entry_get_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->add_book_wdgts->entry_add_book_title))))
        {
            gtk_widget_set_visible(g_data->app_wdgts->admin_main_wdgts->add_book_wdgts->error_add_book_title_required, FALSE);

            // Resize window to adapt to error message displays
            if (GTK_IS_WINDOW (toplevel))
            {
                gtk_window_resize(GTK_WINDOW(toplevel), 1, 1);
            }
        }
        else
        {
            // If entry is empty, show error message
            gtk_widget_set_visible(g_data->app_wdgts->admin_main_wdgts->add_book_wdgts->error_add_book_title_required, TRUE);
        }

    }
    else if(!strcmp(editable_name, "n_entry_add_book_subject"))
    {
        if(strlen(gtk_entry_get_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->add_book_wdgts->entry_add_book_subject))))
        {
            gtk_widget_set_visible(g_data->app_wdgts->admin_main_wdgts->add_book_wdgts->error_add_book_subject_required, FALSE);
            if (GTK_IS_WINDOW (toplevel))
            {
                gtk_window_resize(GTK_WINDOW(toplevel), 1, 1);
            }
        }
        else
        {
            gtk_widget_set_visible(g_data->app_wdgts->admin_main_wdgts->add_book_wdgts->error_add_book_subject_required, TRUE);
        }
    }
    else if(!strcmp(editable_name, "n_entry_add_book_author"))
    {
        if(strlen(gtk_entry_get_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->add_book_wdgts->entry_add_book_author))))
        {
            gtk_widget_set_visible(g_data->app_wdgts->admin_main_wdgts->add_book_wdgts->error_add_book_author_required, FALSE);
            if (GTK_IS_WINDOW (toplevel))
            {
                gtk_window_resize(GTK_WINDOW(toplevel), 1, 1);
            }
        }
        else
        {
            gtk_widget_set_visible(g_data->app_wdgts->admin_main_wdgts->add_book_wdgts->error_add_book_author_required, TRUE);
        }
    }
    else if(!strcmp(editable_name, "n_entry_add_book_language"))
    {
        if(strlen(gtk_entry_get_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->add_book_wdgts->entry_add_book_language))))
        {
            gtk_widget_set_visible(g_data->app_wdgts->admin_main_wdgts->add_book_wdgts->error_add_book_language_required, FALSE);
            if (GTK_IS_WINDOW (toplevel))
            {
                gtk_window_resize(GTK_WINDOW(toplevel), 1, 1);
            }
        }
        else
        {
            gtk_widget_set_visible(g_data->app_wdgts->admin_main_wdgts->add_book_wdgts->error_add_book_language_required, TRUE);
        }
    }
}

gboolean on_window_add_book_delete_event(GtkWidget *window, GdkEvent *event, GLOBAL_DATA *g_data)
{
    // Reset add book entries
    gtk_entry_set_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->add_book_wdgts->entry_add_book_title), "");
    gtk_entry_set_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->add_book_wdgts->entry_add_book_subject), "");
    gtk_entry_set_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->add_book_wdgts->entry_add_book_author), "");
    gtk_entry_set_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->add_book_wdgts->entry_add_book_language), "");

    // Hide error messages
    gtk_widget_set_visible(g_data->app_wdgts->admin_main_wdgts->add_book_wdgts->error_add_book_title_required, FALSE);
    gtk_widget_set_visible(g_data->app_wdgts->admin_main_wdgts->add_book_wdgts->error_add_book_subject_required, FALSE);
    gtk_widget_set_visible(g_data->app_wdgts->admin_main_wdgts->add_book_wdgts->error_add_book_author_required, FALSE);
    gtk_widget_set_visible(g_data->app_wdgts->admin_main_wdgts->add_book_wdgts->error_add_book_language_required, FALSE);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(g_data->app_wdgts->admin_main_wdgts->add_book_wdgts->entry_add_book_number_of_pages), 1);

    // Hide add book window
    return gtk_widget_hide_on_delete(window);
}
