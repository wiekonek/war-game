#include "client.h"

void on_window_game_destroy (GtkWidget *object, gpointer user_data) {
    gtk_main_quit();
    gtk_widget_destroy(user_data);
}

int client_run(GtkBuilder *builder) {

    GtkWidget *game;
    ClientWindow wind;
    
    game = GTK_WIDGET (gtk_builder_get_object (builder, "window_game"));
    if(game == NULL) {
        fprintf(stderr, "Error getting object from file.");
        return -1;
    }
    
//    wind.button_start = GTK_BUTTON (gtk_builder_get_object (builder, "window_button_start"));
//    wind.button_exit = GTK_BUTTON (gtk_builder_get_object (builder, "window_button_exit"));

    gtk_builder_connect_signals( builder, &wind );
    g_signal_connect (game, "destroy", G_CALLBACK (on_window_game_destroy), game);

    gtk_widget_show (game);       
    gtk_main ();

    return 0;
}
