#include <gtk/gtk.h>
#include "gui_structs.h"

#ifndef SEARCH_COPY_H
#define SEARCH_COPY_H

void on_btn_search_copy_clicked(GtkButton*, GLOBAL_DATA*);

void on_btn_search_copy_confirm_clicked(GtkButton*, GLOBAL_DATA*);

void on_btn_search_copy_cancel_clicked(GtkButton*, GLOBAL_DATA*);

gboolean on_window_search_copy_delete_event(GtkWidget*, GdkEvent*, GLOBAL_DATA*);

#endif //SEARCH_COPY_H


