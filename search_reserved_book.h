#include <gtk/gtk.h>
#include "gui_structs.h"

#ifndef SEARCH_RESERVED_BOOK_H
#define SEARCH_RESERVED_BOOK_H

void on_btn_search_reserved_book_clicked(GtkButton*, GLOBAL_DATA*);

void on_btn_search_reserved_book_confirm_clicked(GtkButton*, GLOBAL_DATA*);

void on_btn_search_reserved_book_cancel_clicked(GtkButton*, GLOBAL_DATA*);

gboolean on_window_search_reserved_book_delete_event(GtkWidget*, GdkEvent*, GLOBAL_DATA*);

void on_checkbox_search_reserved_book_reservation_date_toggled(GtkToggleButton*, GLOBAL_DATA*);

void on_checkbox_search_reserved_book_due_date_toggled(GtkToggleButton*, GLOBAL_DATA*);

#endif //SEARCH_RESERVED_BOOK_H



