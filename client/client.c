#include "client.h"
int ID;
int msgid;

void on_window_game_destroy (GtkWidget *object, gpointer user_data) {
    gtk_main_quit();
    gtk_widget_destroy(user_data);
}

int update (gpointer nie_wiem) {
   if ( msg ) {
       
   } else {
       
   }
}

int client_run(GtkBuilder *builder, int id) {
    ID = id;
    GtkWidget *game;
    ClientWindow wind;
    
    msgid = msgget(KEY_MSG, 0666);
    if( msgid == -1 ) {
        perror("Setting up init queue");
        exit(1);
    }
    
    game = GTK_WIDGET (gtk_builder_get_object (builder, "window_game"));
    if(game == NULL) {
        fprintf(stderr, "Error getting object from file.");
        return -1;
    }
    
//    wind.button_start = GTK_BUTTON (gtk_builder_get_object (builder, "window_button_start"));
//    wind.button_exit = GTK_BUTTON (gtk_builder_get_object (builder, "window_button_exit"));
    
    g_timeout_add ( 10, G_CALLBACK (update), NULL);
    
    gtk_builder_connect_signals( builder, &wind );
    g_signal_connect (game, "destroy", G_CALLBACK (on_window_game_destroy), game);

    gtk_widget_show (game);       
    gtk_main ();

    return 0;
}
