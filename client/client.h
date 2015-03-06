#ifndef CLIENT_H
#define	CLIENT_H

#include "msg.h"
#include <gtk/gtk.h>

typedef struct {
    GtkButton *button_attack;
    GtkButton *button_exit;
    GtkButton *button_rec1;
    GtkButton *button_rec2;
    GtkButton *button_rec3;
    GtkButton *button_rec4;
    GtkLabel *resources;
    GtkLabel *workers;
    GtkLabel *ls;
    GtkLabel *hs;
    GtkLabel *cavalry;
    GtkLabel *id;
} ClientWindow;

int client_run(GtkBuilder *builder, int id);


#endif	/* CLIENT_H */

