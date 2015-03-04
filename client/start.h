#ifndef START_H
#define	START_H

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "msg.h"

typedef struct {
    GtkButton *button_start;
    GtkButton *button_exit;
} StartWindow;

int start_run(GtkBuilder *builder);


#endif	/* START_H */

