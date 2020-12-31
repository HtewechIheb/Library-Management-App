#include <gtk/gtk.h>
#include "gui_structs.h"

#ifndef RESERVE_BOOK_H
#define RESERVE_BOOK_H

void on_toolbar_btn_reserve_book_clicked(GtkToolButton*, GLOBAL_DATA*);

void on_btn_reserve_book_confirm_clicked(GtkButton*, GLOBAL_DATA*);

void on_btn_reserve_book_cancel_clicked(GtkButton*, GLOBAL_DATA*);

gboolean on_window_reserve_book_delete_event(GtkWidget*, GdkEvent*, GLOBAL_DATA*);

#endif //RESERVE_BOOK_H

