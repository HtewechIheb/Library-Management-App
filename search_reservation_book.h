#include <gtk/gtk.h>
#include "gui_structs.h"

#ifndef SEARCH_RESERVATION_BOOK_H
#define SEARCH_RESERVATION_BOOK_H

void on_btn_search_reservation_book_clicked(GtkButton*, GLOBAL_DATA*);

void on_btn_search_reservation_book_confirm_clicked(GtkButton*, GLOBAL_DATA*);

void on_btn_search_reservation_book_cancel_clicked(GtkButton*, GLOBAL_DATA*);

gboolean on_window_search_reservation_book_delete_event(GtkWidget*, GdkEvent*, GLOBAL_DATA*);

#endif //SEARCH_RESERVATION_BOOK_H


