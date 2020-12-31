#include <gtk/gtk.h>
#include "gui_structs.h"

#ifndef GUI_H
#define GUI_H

void render_book_list(GLOBAL_DATA*, BOOK_NODE*, int);

void render_reservation_book_list(GLOBAL_DATA*, BOOK_NODE*, int);

void render_reserved_book_list(GLOBAL_DATA*, RESERVATION_NODE*, int);

void render_account_list(GLOBAL_DATA*, ACCOUNT_NODE*, int);

void render_reservation_list(GLOBAL_DATA*, RESERVATION_NODE*, int);

void render_copy_list(GLOBAL_DATA*, COPY_NODE*, int, int);

#endif //GUI_H
