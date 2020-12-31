#include <gtk/gtk.h>
#include "gui_structs.h"

#ifndef EDIT_ACCOUNT_H
#define EDIT_ACCOUNT_H

void on_btn_edit_account_clicked(GtkButton*, GLOBAL_DATA*);

void on_btn_edit_account_confirm_clicked(GtkButton*, GLOBAL_DATA*);

void on_btn_edit_account_cancel_clicked(GtkButton*, GLOBAL_DATA*);

void on_entry_edit_account_phone_insert_text(GtkEntry*, const gchar*, gint, gint*, GLOBAL_DATA*);

void on_edit_book_account_changed(GtkEditable*, GLOBAL_DATA*);

gboolean on_window_edit_account_delete_event(GtkWidget*, GdkEvent*, GLOBAL_DATA*);

#endif //EDIT_ACCOUNT_H
