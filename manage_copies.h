#include <gtk/gtk.h>
#include "gui_structs.h"

#ifndef MANAGE_COPIES_H
#define MANAGE_COPIES_H

void on_btn_manage_copies_clicked(GtkButton*, GLOBAL_DATA*);

gboolean on_window_manage_copies_delete_event(GtkWidget*, GdkEvent*, GLOBAL_DATA*);

#endif //MANAGE_COPIES_H


