#include <gtk/gtk.h>
#include "gui_structs.h"

#ifndef DELETE_COPY_H
#define DELETE_COPY_H

void on_btn_delete_copy_clicked(GtkButton*, GLOBAL_DATA*);

gboolean on_dialog_verify_delete_copy_delete_event(GtkWidget*, GdkEvent*, GLOBAL_DATA*);

#endif //DELETE_COPY_H

