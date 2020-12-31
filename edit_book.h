#include <gtk/gtk.h>
#include "gui_structs.h"

#ifndef EDIT_BOOK_H
#define EDIT_BOOK_H

void on_btn_edit_book_clicked(GtkButton*, GLOBAL_DATA*);

void on_btn_edit_book_confirm_clicked(GtkButton*, GLOBAL_DATA*);

void on_btn_edit_book_cancel_clicked(GtkButton*, GLOBAL_DATA*);

void on_edit_book_entry_changed(GtkEditable*, GLOBAL_DATA*);

gboolean on_window_edit_book_delete_event(GtkWidget*, GdkEvent*, GLOBAL_DATA*);

#endif //EDIT_BOOK_H
