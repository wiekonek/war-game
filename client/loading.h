#ifndef LOADING_H
#define	LOADING_H

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define KEY_ID 66

typedef struct msgbuf {
long mtype;//zgłosznie 1, przydział ID 2
int id;
} ID_msg;

typedef struct {
    GtkLabel *label;
    GtkSpinner *spinner;
} LoadingWindow;

int loading_run(GtkBuilder *builder);

#endif	/* LOADING_H */

