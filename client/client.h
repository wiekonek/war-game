#ifndef CLIENT_H
#define	CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "msg.h"

typedef struct {
    GtkButton *button_start;
    GtkButton *button_exit;
} ClientWindow;

int client_run(GtkBuilder *builder, int id);


#endif	/* CLIENT_H */

