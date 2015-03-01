#ifndef LOADING_H
#define	LOADING_H

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

typedef struct {
    GtkButton *button_ready;
    GtkButton *button_exit;
} LoadingWindow;

int loading_run(GtkBuilder *builder);

#endif	/* LOADING_H */

