#include "manage_copies.h"
#include "books.h"
#include "accounts.h"
#include "copies.h"
#include "reservations.h"
#include "general.h"
#include "gui.h"

void on_btn_manage_copies_clicked(GtkButton *button, GLOBAL_DATA *g_data)
{
    // Show manage copies window
    gtk_widget_show(g_data->app_wdgts->admin_main_wdgts->manage_copies_wdgts->window_manage_copies);
}

gboolean on_window_manage_copies_delete_event(GtkWidget *window, GdkEvent *event, GLOBAL_DATA *g_data)
{
    // Show manage copies window
    return gtk_widget_hide_on_delete(window);
}



