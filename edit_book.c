#include "edit_book.h"
#include "books.h"
#include "accounts.h"
#include "copies.h"
#include "reservations.h"
#include "general.h"
#include "gui.h"

void on_btn_edit_book_clicked(GtkButton *button, GLOBAL_DATA *g_data)
{
    // Show edit book window
    gtk_widget_show(g_data->app_wdgts->admin_main_wdgts->edit_book_wdgts->window_edit_book);
}

void on_btn_edit_book_confirm_clicked(GtkButton* button, GLOBAL_DATA *g_data)
{
    GtkTreeIter iter; // Iterator to read from list store
    GtkTreeModel *model; // Model for list store
    GtkTreeSelection *selection; // Book treeview selection to get selected row
    BOOK book; // Variable to hold new book data
    GtkWidget *toplevel = gtk_widget_get_toplevel (GTK_WIDGET(button)); // Get top level window
    gboolean valid = TRUE; // Variable to test validity of the entries

    // If entry is empty, show error message and set validity to false
    if(!strlen(gtk_entry_get_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->edit_book_wdgts->entry_edit_book_title))))
    {
        gtk_widget_set_visible(g_data->app_wdgts->admin_main_wdgts->edit_book_wdgts->error_edit_book_title_required, TRUE);
        valid = FALSE;
    }
    if(!strlen(gtk_entry_get_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->edit_book_wdgts->entry_edit_book_subject))))
    {
        gtk_widget_set_visible(g_data->app_wdgts->admin_main_wdgts->edit_book_wdgts->error_edit_book_subject_required, TRUE);
        valid = FALSE;
    }
    if(!strlen(gtk_entry_get_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->edit_book_wdgts->entry_edit_book_author))))
    {
        gtk_widget_set_visible(g_data->app_wdgts->admin_main_wdgts->edit_book_wdgts->error_edit_book_author_required, TRUE);
        valid = FALSE;
    }
    if(!strlen(gtk_entry_get_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->edit_book_wdgts->entry_edit_book_language))))
    {
        gtk_widget_set_visible(g_data->app_wdgts->admin_main_wdgts->edit_book_wdgts->error_edit_book_language_required, TRUE);
        valid = FALSE;
    }
    if(strlen(gtk_entry_get_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->edit_account_wdgts->entry_edit_account_phone))) < 8)
    {
        gtk_widget_set_visible(g_data->app_wdgts->admin_main_wdgts->edit_account_wdgts->error_edit_account_phone_invalid, TRUE);
        valid = FALSE;
    }

    if(valid)
    {

        // Read selected book ID
        selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(g_data->app_wdgts->admin_main_wdgts->treeview_book_list));
        if (gtk_tree_selection_get_selected (selection, &model, &iter))
        {
                gtk_tree_model_get (model, &iter, BOOK_LIST_COL_ID, &book.id, -1);
        }

        // Edit book and add it to file
        strcpy(book.title, gtk_entry_get_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->edit_book_wdgts->entry_edit_book_title)));
        strcpy(book.subject, gtk_entry_get_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->edit_book_wdgts->entry_edit_book_subject)));
        strcpy(book.author, gtk_entry_get_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->edit_book_wdgts->entry_edit_book_author)));
        strcpy(book.language, gtk_entry_get_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->edit_book_wdgts->entry_edit_book_language)));
        book.number_of_pages = gtk_spin_button_get_value(GTK_SPIN_BUTTON(g_data->app_wdgts->admin_main_wdgts->edit_book_wdgts->entry_edit_book_number_of_pages));
        edit_book(g_data->book_list, book);

        // Render updated book treeview
        render_book_list(g_data, NULL, 0);

        // Confirm edition and hide add account window
        if (gtk_dialog_run(GTK_DIALOG(g_data->app_wdgts->admin_main_wdgts->edit_book_wdgts->dialog_confirm_edit_book)) == GTK_RESPONSE_OK)
        {
            gtk_widget_hide(g_data->app_wdgts->admin_main_wdgts->edit_book_wdgts->dialog_confirm_edit_book);
            if (GTK_IS_WINDOW (toplevel))
            {
                gtk_window_close(GTK_WINDOW(toplevel));
            }
        }
    }
}

void on_btn_edit_book_cancel_clicked(GtkButton* button, GLOBAL_DATA *g_data)
{
    GtkWidget *toplevel = gtk_widget_get_toplevel (GTK_WIDGET(button)); // Get top level window

    // Hide current window
    if (GTK_IS_WINDOW (toplevel))
    {
        gtk_window_close(GTK_WINDOW(toplevel));
    }
}

void on_edit_book_entry_changed(GtkEditable* editable, GLOBAL_DATA *g_data)
{
    GtkWidget *toplevel = gtk_widget_get_toplevel (GTK_WIDGET(editable)); // Get top level window
    const char* editable_name = gtk_widget_get_name(GTK_WIDGET(editable)); // Get changed entry
    if(!strcmp(editable_name, "n_entry_edit_book_title"))
    {
        // If entry is not empty, hide error message
        if(strlen(gtk_entry_get_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->edit_book_wdgts->entry_edit_book_title))))
        {
            gtk_widget_set_visible(g_data->app_wdgts->admin_main_wdgts->edit_book_wdgts->error_edit_book_title_required, FALSE);
            // Resize window to adapt to error message displays
            if (GTK_IS_WINDOW (toplevel))
            {
                gtk_window_resize(GTK_WINDOW(toplevel), 1, 1);
            }
        }
        else
        {
            gtk_widget_set_visible(g_data->app_wdgts->admin_main_wdgts->edit_book_wdgts->error_edit_book_title_required, TRUE);
        }

    }
    else if(!strcmp(editable_name, "n_entry_edit_book_subject"))
    {
        if(strlen(gtk_entry_get_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->edit_book_wdgts->entry_edit_book_subject))))
        {
            gtk_widget_set_visible(g_data->app_wdgts->admin_main_wdgts->edit_book_wdgts->error_edit_book_subject_required, FALSE);
            if (GTK_IS_WINDOW (toplevel))
            {
                gtk_window_resize(GTK_WINDOW(toplevel), 1, 1);
            }
        }
        else
        {
            gtk_widget_set_visible(g_data->app_wdgts->admin_main_wdgts->edit_book_wdgts->error_edit_book_subject_required, TRUE);
        }
    }
    else if(!strcmp(editable_name, "n_entry_edit_book_author"))
    {
        if(strlen(gtk_entry_get_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->edit_book_wdgts->entry_edit_book_author))))
        {
            gtk_widget_set_visible(g_data->app_wdgts->admin_main_wdgts->edit_book_wdgts->error_edit_book_author_required, FALSE);
            if (GTK_IS_WINDOW (toplevel))
            {
                gtk_window_resize(GTK_WINDOW(toplevel), 1, 1);
            }
        }
        else
        {
            gtk_widget_set_visible(g_data->app_wdgts->admin_main_wdgts->edit_book_wdgts->error_edit_book_author_required, TRUE);
        }
    }
    else if(!strcmp(editable_name, "n_entry_edit_book_language"))
    {
        if(strlen(gtk_entry_get_text(GTK_ENTRY(g_data->app_wdgts->admin_main_wdgts->edit_book_wdgts->entry_edit_book_language))))
        {
            gtk_widget_set_visible(g_data->app_wdgts->admin_main_wdgts->edit_book_wdgts->error_edit_book_language_required, FALSE);
            if (GTK_IS_WINDOW (toplevel))
            {
                gtk_window_resize(GTK_WINDOW(toplevel), 1, 1);
            }
        }
        else
        {
            gtk_widget_set_visible(g_data->app_wdgts->admin_main_wdgts->edit_book_wdgts->error_edit_book_language_required, TRUE);
        }
    }
}

gboolean on_window_edit_book_delete_event(GtkWidget *window, GdkEvent *event, GLOBAL_DATA *g_data)
{
    // Hide edit account window
    return gtk_widget_hide_on_delete(window);
}

