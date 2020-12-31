#include <gtk/gtk.h>
#include "gui_structs.h"

#ifndef ADD_ACCOUNT_H
#define ADD_ACCOUNT_H

void on_btn_add_account_clicked(GtkButton*, GLOBAL_DATA*);

void on_btn_add_account_confirm_clicked(GtkButton*, GLOBAL_DATA*);

void on_btn_add_account_cancel_clicked(GtkButton*, GLOBAL_DATA*);

void on_entry_add_account_phone_insert_text(GtkEntry*, const gchar*, gint, gint*, GLOBAL_DATA*);

void on_add_account_entry_changed(GtkEditable*, GLOBAL_DATA*);

gboolean on_window_add_account_delete_event(GtkWidget*, GdkEvent*, GLOBAL_DATA*);

#endif //ADD_ACCOUNT_H

