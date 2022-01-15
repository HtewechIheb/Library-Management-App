#include <time.h>
#include "search_reserved_book.h"
#include "books.h"
#include "accounts.h"
#include "copies.h"
#include "reservations.h"
#include "general.h"
#include "gui.h"

void on_btn_search_reserved_book_clicked(GtkButton *button, GLOBAL_DATA *g_data)
{
    time_t current_time = time(NULL);                   //
    struct tm current_date = *gmtime(&current_time);    // Variables to hold current date

    // Reset search reserved book entries and set dates to current date
    gtk_entry_set_text(GTK_ENTRY(g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts->entry_search_reserved_book_title), "");
    gtk_entry_set_text(GTK_ENTRY(g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts->entry_search_reserved_book_author), "");
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts->entry_search_reserved_book_reservation_day), current_date.tm_mday);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts->entry_search_reserved_book_reservation_year), 1900 + current_date.tm_year);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts->entry_search_reserved_book_due_day), current_date.tm_mday);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts->entry_search_reserved_book_due_year), 1900 + current_date.tm_year);
    gtk_combo_box_set_active(GTK_COMBO_BOX(g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts->entry_search_reserved_book_reservation_month), current_date.tm_mon);
    gtk_combo_box_set_active(GTK_COMBO_BOX(g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts->entry_search_reserved_book_due_month), current_date.tm_mon);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts->entry_search_reserved_book_copy_barcode), 0);

    // Show search reserved book window
    gtk_widget_show(g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts->window_search_reserved_book);
}

void on_btn_search_reserved_book_confirm_clicked(GtkButton* button, GLOBAL_DATA *g_data)
{
    GtkWidget *toplevel = gtk_widget_get_toplevel (GTK_WIDGET(button)); // Get top level window
    RESERVATION_NODE* buffer = NULL, *search_result = NULL; // buffer: reserved book search result (without considering entries related to book information), search_result: final search result after searching with book information
    COPY* copy = NULL; // Variable to hold copy associated with reservation

    time_t reservation_date, due_date;      //
    struct tm reservation_date_struct = {}; // Variables to handle dates
    struct tm due_date_struct = {};         //

    // If reservation date search is enabled, convert reservation date entries data to date
    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts->checkbox_search_reserved_book_reservation_date)))
    {
        reservation_date_struct.tm_mday = (int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts->entry_search_reserved_book_reservation_day));
        reservation_date_struct.tm_mon = gtk_combo_box_get_active(GTK_COMBO_BOX(g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts->entry_search_reserved_book_reservation_month));
        reservation_date_struct.tm_year = (int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts->entry_search_reserved_book_reservation_year)) - 1900;
        reservation_date = mktime(&reservation_date_struct);
    }
    else
    {
        reservation_date = -1;
    }

    // If due date search is enabled, convert due date entries data to date
    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts->checkbox_search_reserved_book_due_date)))
    {
        due_date_struct.tm_mday = (int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts->entry_search_reserved_book_due_day));
        due_date_struct.tm_mon = gtk_combo_box_get_active(GTK_COMBO_BOX(g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts->entry_search_reserved_book_due_month));
        due_date_struct.tm_year = (int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts->entry_search_reserved_book_due_year)) - 1900;
        due_date = mktime(&due_date_struct);
    }
    else
    {
        due_date = -1;
    }

    // If barcode value is different to 0, use it in the search
    if((int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts->entry_search_reserved_book_copy_barcode)) != 0)
    {
        copy = search_copy_by_barcode(g_data->copy_list, (int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts->entry_search_reserved_book_copy_barcode)));
    }

    // Search resered books using reservation information
    buffer = search_reservations(g_data->reservation_list, copy ? copy->id : -1, -1, reservation_date, due_date);

    // Search reserved books using book information
    search_result = search_reservations_by_book(
        buffer,
        g_data->copy_list,
        g_data->book_list,
        gtk_entry_get_text(GTK_ENTRY(g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts->entry_search_reserved_book_title)),
        NULL,
        gtk_entry_get_text(GTK_ENTRY(g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts->entry_search_reserved_book_author)),
        NULL,
        0
    );

    // Render search result in treeview
    render_reserved_book_list(g_data, search_result, 1);
    if (GTK_IS_WINDOW (toplevel))
    {
        gtk_window_close(GTK_WINDOW(toplevel));
    }

    // Free memory
    free_reservation_list(&buffer);
    free_reservation_list(&search_result);
}

void on_btn_search_reserved_book_cancel_clicked(GtkButton* button, GLOBAL_DATA *g_data)
{
    GtkWidget *toplevel = gtk_widget_get_toplevel (GTK_WIDGET(button)); // Get top level window

    // Hide current window
    if (GTK_IS_WINDOW (toplevel))
    {
        gtk_window_close(GTK_WINDOW(toplevel));
    }
}

gboolean on_window_search_reserved_book_delete_event(GtkWidget *window, GdkEvent *event, GLOBAL_DATA *g_data)
{
    time_t curr_time = time(NULL);                  //
    struct tm current_date = *gmtime(&curr_time);   // Variables to hold current date

    // Reset search reserved book entries and set dates to current date
    gtk_entry_set_text(GTK_ENTRY(g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts->entry_search_reserved_book_title), "");
    gtk_entry_set_text(GTK_ENTRY(g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts->entry_search_reserved_book_author), "");
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts->entry_search_reserved_book_reservation_day), current_date.tm_mday);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts->entry_search_reserved_book_reservation_year), current_date.tm_year);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts->entry_search_reserved_book_due_day), current_date.tm_mday);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts->entry_search_reserved_book_due_year), current_date.tm_year);
    gtk_combo_box_set_active(GTK_COMBO_BOX(g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts->entry_search_reserved_book_reservation_month), current_date.tm_mon);
    gtk_combo_box_set_active(GTK_COMBO_BOX(g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts->entry_search_reserved_book_due_month), current_date.tm_mon);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts->entry_search_reserved_book_copy_barcode), 0);

    // Show search reserved window
    return gtk_widget_hide_on_delete(window);
}

void on_entry_search_reserved_book_reservation_month_changed(GtkComboBox *combobox, GLOBAL_DATA *g_data)
{
    int active_item = gtk_combo_box_get_active(GTK_COMBO_BOX(g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts->entry_search_reserved_book_reservation_month)); // Get selected month index
    int max_days; // Variable to hold the max days of a month

    // Set max days according to selected month
    if(active_item == 0 || active_item == 2 || active_item == 4 || active_item == 6 || active_item == 7 || active_item == 9 || active_item == 11)
    {
        max_days = 31;
    }
    else if(active_item == 3 || active_item == 5 || active_item == 8 || active_item == 10)
    {
        max_days = 30;
    }
    else
    {
        max_days = 28;
    }

    // Set days entry adjustement max value to max_days
    gtk_adjustment_set_upper(gtk_spin_button_get_adjustment(GTK_SPIN_BUTTON(g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts->entry_search_reserved_book_reservation_day)), max_days);

    // Set days entry value to max_days if previous value exceeded it
    if((int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts->entry_search_reserved_book_reservation_day)) > max_days)
    {
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts->entry_search_reserved_book_reservation_day), max_days);
    }
}

void on_entry_search_reserved_book_due_month_changed(GtkComboBox *combobox, GLOBAL_DATA *g_data)
{
    int active_item = gtk_combo_box_get_active(GTK_COMBO_BOX(g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts->entry_search_reserved_book_due_month)); // Get selected month index
    int max_days; // Variable to hold the max days of a month

    // Set max days according to selected month
    if(active_item == 0 || active_item == 2 || active_item == 4 || active_item == 6 || active_item == 7 || active_item == 9 || active_item == 11)
    {
        max_days = 31;
    }
    else if(active_item == 3 || active_item == 5 || active_item == 8 || active_item == 10)
    {
        max_days = 30;
    }
    else
    {
        max_days = 28;
    }

    // Set days entry adjustement max value to max_days
    gtk_adjustment_set_upper(gtk_spin_button_get_adjustment(GTK_SPIN_BUTTON(g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts->entry_search_reserved_book_due_day)), max_days);

    // Set days entry value to max_days if previous value exceeded it
    if((int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts->entry_search_reserved_book_due_day)) > max_days)
    {
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts->entry_search_reserved_book_due_day), max_days);
    }
}

void on_checkbox_search_reserved_book_reservation_date_toggled(GtkToggleButton *togglebutton, GLOBAL_DATA *g_data)
{
    // If reservation date search is enabled, enable reservation date entries
    if(gtk_toggle_button_get_active(togglebutton))
    {
        gtk_widget_set_sensitive(g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts->entry_search_reserved_book_reservation_day, TRUE);
        gtk_widget_set_sensitive(g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts->entry_search_reserved_book_reservation_month, TRUE);
        gtk_widget_set_sensitive(g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts->entry_search_reserved_book_reservation_year, TRUE);
    }
    // Otherwise, disable them
    else
    {
        gtk_widget_set_sensitive(g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts->entry_search_reserved_book_reservation_day, FALSE);
        gtk_widget_set_sensitive(g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts->entry_search_reserved_book_reservation_month, FALSE);
        gtk_widget_set_sensitive(g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts->entry_search_reserved_book_reservation_year, FALSE);
    }
}

void on_checkbox_search_reserved_book_due_date_toggled(GtkToggleButton *togglebutton, GLOBAL_DATA *g_data)
{
    // If due date search is enabled, enable due date entries
    if(gtk_toggle_button_get_active(togglebutton))
    {
        gtk_widget_set_sensitive(g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts->entry_search_reserved_book_due_day, TRUE);
        gtk_widget_set_sensitive(g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts->entry_search_reserved_book_due_month, TRUE);
        gtk_widget_set_sensitive(g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts->entry_search_reserved_book_due_year, TRUE);
    }
    // Otherwise, disable them
    else
    {
        gtk_widget_set_sensitive(g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts->entry_search_reserved_book_due_day, FALSE);
        gtk_widget_set_sensitive(g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts->entry_search_reserved_book_due_month, FALSE);
        gtk_widget_set_sensitive(g_data->app_wdgts->user_main_wdgts->search_reserved_book_wdgts->entry_search_reserved_book_due_year, FALSE);
    }
}



