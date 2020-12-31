#include <gtk/gtk.h>
#include "gui_structs.h"

#ifndef DELETE_BOOK_H
#define DELETE_BOOK_H

void on_btn_delete_book_clicked(GtkButton*, GLOBAL_DATA*);

gboolean on_dialog_verify_delete_book_delete_event(GtkWidget*, GdkEvent*, GLOBAL_DATA*);

#endif //DELETE_BOOK_H
