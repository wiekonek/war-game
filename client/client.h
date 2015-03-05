#ifndef CLIENT_H
#define	CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "msg.h"

typedef struct {
    GtkButton *button_attack;
    GtkButton *button_exit;
    GtkButton *button_rec1;
    GtkButton *button_rec2;
    GtkButton *button_rec3;
    GtkButton *button_rec4;
} ClientWindow;

int client_run(GtkBuilder *builder, int id);


#endif	/* CLIENT_H */

