#include <gtk/gtk.h>
#include "gui_structs.h"

#ifndef RETURN_BOOK_H
#define RETURN_BOOK_H

void on_toolbar_btn_return_book_clicked(GtkToolButton*, GLOBAL_DATA*);

gboolean on_dialog_verify_return_book_delete_event(GtkWidget*, GdkEvent*, GLOBAL_DATA*);

#endif //RETURN_BOOK_H
