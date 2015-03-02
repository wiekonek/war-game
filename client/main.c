#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

#include "start.h"
#include "client.h"
#include "loading.h"

int main (int argc, char** argv) {
    GtkBuilder *builder;
    gtk_init (&argc, &argv);

    builder = gtk_builder_new ();

    if(0 == gtk_builder_add_from_file (builder, "war.glade", NULL)) {
        fprintf(stderr, "Error adding build from file.");
        return -1;
    }
    
    int ret;
    ret = start_run(builder);
    if (ret == 1) {
        ret = loading_run(builder);
        if(ret > 0)
            client_run(builder, ret);
    }
    
    g_object_unref(G_OBJECT(builder));
        
    return 0;
}