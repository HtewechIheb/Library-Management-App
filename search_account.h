#include <gtk/gtk.h>
#include "gui_structs.h"

#ifndef SEARCH_ACCOUNT_H
#define SEARCH_ACCOUNT_H

void on_btn_search_account_clicked(GtkButton*, GLOBAL_DATA*);

void on_btn_search_account_confirm_clicked(GtkButton*, GLOBAL_DATA*);

void on_btn_search_account_cancel_clicked(GtkButton*, GLOBAL_DATA*);

gboolean on_window_search_account_delete_event(GtkWidget*, GdkEvent*, GLOBAL_DATA*);

#endif //SEARCH_ACCOUNT_H
