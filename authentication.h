#include <gtk/gtk.h>
#include "gui_structs.h"

#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

void on_authentication_entry_changed(GtkEditable* editable, GLOBAL_DATA *g_data);

void on_btn_authentication_login_clicked(GtkButton *button, GLOBAL_DATA *g_data);

void on_btn_authentication_exit_clicked();

void on_window_authentication_destroy();

#endif //AUTHENTICATION_H
