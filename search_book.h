#include <gtk/gtk.h>
#include "gui_structs.h"

#ifndef SEARCH_BOOK_H
#define SEARCH_BOOK_H

void on_btn_search_book_clicked(GtkButton*, GLOBAL_DATA*);

void on_btn_search_book_confirm_clicked(GtkButton*, GLOBAL_DATA*);

void on_btn_search_book_cancel_clicked(GtkButton*, GLOBAL_DATA*);

gboolean on_window_search_book_delete_event(GtkWidget*, GdkEvent*, GLOBAL_DATA*);

#endif //SEARCH_BOOK_H

