#include <gtk/gtk.h>
#include "gui_structs.h"

#ifndef DELETE_ACCOUNT_H
#define DELETE_ACCOUNT_H

void on_btn_delete_account_clicked(GtkButton*, GLOBAL_DATA*);

gboolean on_dialog_verify_delete_account_delete_event(GtkWidget*, GdkEvent*, GLOBAL_DATA*);

#endif //DELETE_ACCOUNT_H


