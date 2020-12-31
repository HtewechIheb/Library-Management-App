#include <gtk/gtk.h>
#include "gui_structs.h"

#ifndef ADD_BOOK_H
#define ADD_BOOK_H

void on_btn_add_book_clicked(GtkButton*, GLOBAL_DATA*);

void on_btn_add_book_confirm_clicked(GtkButton*, GLOBAL_DATA*);

void on_btn_add_book_cancel_clicked(GtkButton*, GLOBAL_DATA*);

void on_add_book_entry_changed(GtkEditable*, GLOBAL_DATA*);

gboolean on_window_add_book_delete_event(GtkWidget*, GdkEvent*, GLOBAL_DATA*);

#endif //ADD_BOOK_H
