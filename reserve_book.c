#include "reserve_book.h"
#include "books.h"
#include "accounts.h"
#include "copies.h"
#include "reservations.h"
#include "general.h"
#include "gui.h"

void on_btn_reserve_book_clicked(GtkToolButton *toolbutton, GLOBAL_DATA* g_data)
{
    // If current user's reservations number exceeds 5, display error dialog
    if(get_account_reservations_nb(g_data->reservation_list, g_data->current_user->id) == 5)
    {
        if (gtk_dialog_run(GTK_DIALOG(g_data->app_wdgts->user_main_wdgts->reserve_book_wdgts->dialog_error_max_reservations)) == GTK_RESPONSE_OK)
        {
            gtk_widget_hide(g_data->app_wdgts->user_main_wdgts->reserve_book_wdgts->dialog_error_max_reservations);
        }
    }
    // Else show reserve book window
    else
    {
        gtk_widget_show(g_data->app_wdgts->user_main_wdgts->reserve_book_wdgts->window_reserve_book);
    }
}

void on_btn_reserve_book_confirm_clicked(GtkButton* button, GLOBAL_DATA *g_data)
{
    GtkTreeIter iter; // Iterator to read from list store
    GtkTreeModel *model; // Model for list store
    GtkTreeSelection *selection; // Reservation book treeview selection to get selected row
    GtkWidget *toplevel = gtk_widget_get_toplevel (GTK_WIDGET(button)); // Get top level window
    COPY* copy; // Variable to hold copy data
    int id_book; // Variable to hold book ID

    // Get currently selected book
    selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(g_data->app_wdgts->user_main_wdgts->treeview_reservation_book_list));
    if (gtk_tree_selection_get_selected (selection, &model, &iter))
    {
        // If a book is selected, get one of it's free copies
        gtk_tree_model_get (model, &iter, RESERVATION_BOOK_LIST_COL_ID, &id_book, -1);
        copy = get_book_copy(g_data->copy_list, id_book);

        // If there are no free copies of the book, abort the operation
        if(!copy)
        {
            if (GTK_IS_WINDOW (toplevel))
            {
                gtk_window_close(GTK_WINDOW(toplevel));
            }
            return;
        }

        // Else reserve the free copy to the current user
        reserve_copy(&g_data->reservation_list, g_data->copy_list, copy->id, g_data->current_user->id, gtk_spin_button_get_value(GTK_SPIN_BUTTON(g_data->app_wdgts->user_main_wdgts->reserve_book_wdgts->entry_reserve_book_duration)));

        // Render updated reservation book treeview
        render_reservation_book_list(g_data, NULL, 0);

        // Render updated reserved book treeview
        render_reserved_book_list(g_data, NULL, 0);

        // Confirm reservation and hide add account window
        if (gtk_dialog_run(GTK_DIALOG(g_data->app_wdgts->user_main_wdgts->reserve_book_wdgts->dialog_confirm_reserve_book)) == GTK_RESPONSE_OK)
        {
            gtk_widget_hide(g_data->app_wdgts->user_main_wdgts->reserve_book_wdgts->dialog_confirm_reserve_book);
            if (GTK_IS_WINDOW (toplevel))
            {
                gtk_window_close(GTK_WINDOW(toplevel));
            }
        }
    }

    // Free memory
    free(copy);
}

void on_btn_reserve_book_cancel_clicked(GtkButton* button, GLOBAL_DATA *g_data)
{
    GtkWidget *toplevel = gtk_widget_get_toplevel (GTK_WIDGET(button)); // Get top level window

    // Hide current window
    if (GTK_IS_WINDOW (toplevel))
    {
        gtk_window_close(GTK_WINDOW(toplevel));
    }
}

gboolean on_window_reserve_book_delete_event(GtkWidget *window, GdkEvent *event, GLOBAL_DATA *g_data)
{
    // Reset reserve book entries
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(g_data->app_wdgts->user_main_wdgts->reserve_book_wdgts->entry_reserve_book_duration), 1);

    // Hide reserve book window
    return gtk_widget_hide_on_delete(window);
}
