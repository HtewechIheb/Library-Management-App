#include <gtk/gtk.h>
#include "gui_structs.h"

#ifndef SEARCH_RESERVATION_H
#define SEARCH_RESERVATION_H

void on_btn_search_reservation_clicked(GtkButton*, GLOBAL_DATA*);

void on_btn_search_reservation_confirm_clicked(GtkButton*, GLOBAL_DATA*);

void on_btn_search_reservation_cancel_clicked(GtkButton*, GLOBAL_DATA*);

gboolean on_window_search_reservation_delete_event(GtkWidget*, GdkEvent*, GLOBAL_DATA*);

void on_checkbox_search_reservation_reservation_date_toggled(GtkToggleButton*, GLOBAL_DATA*);

void on_checkbox_search_reservation_due_date_toggled(GtkToggleButton*, GLOBAL_DATA*);

#endif //SEARCH_RESERVATION_H




