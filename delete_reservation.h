#include <gtk/gtk.h>
#include "gui_structs.h"

#ifndef DELETE_RESERVATION_H
#define DELETE_RESERVATION_H

void on_toolbar_btn_delete_reservation_clicked(GtkToolButton*, GLOBAL_DATA*);

gboolean on_dialog_verify_delete_reservation_delete_event(GtkWidget*, GdkEvent*, GLOBAL_DATA*);

#endif //DELETE_RESERVATION_H

