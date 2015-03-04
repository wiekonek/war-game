#include "attack.h"

int attack_run(GtkBuilder *builder, int id) {

    GtkWidget *window;
    ClientWindow wind;
    
    window = GTK_WIDGET (gtk_builder_get_object (builder, "window_game"));
    if(window == NULL) {
        fprintf(stderr, "Error getting object from file.");
        return -1;
    }
    
    gtk_builder_connect_signals( builder, &wind );
    g_signal_connect (window, "destroy", G_CALLBACK (on_window_game_destroy), window);

    gtk_widget_show (window);       
    gtk_main ();

    return 0;
}
