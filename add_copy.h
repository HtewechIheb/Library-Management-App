#include <gtk/gtk.h>
#include "gui_structs.h"

#ifndef ADD_COPY_H
#define ADD_COPY_H

void on_btn_add_copy_clicked(GtkButton*, GLOBAL_DATA*);

void on_btn_add_copy_confirm_clicked(GtkButton*, GLOBAL_DATA*);

void on_btn_add_copy_cancel_clicked(GtkButton*, GLOBAL_DATA*);

gboolean on_window_add_copy_delete_event(GtkWidget*, GdkEvent*, GLOBAL_DATA*);

#endif //ADD_COPY_H
