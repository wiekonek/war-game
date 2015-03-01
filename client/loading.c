#include "loading.h"
int retl = 0;

void on_window_loading_destroy (GtkWidget *object, gpointer user_data) {
    gtk_main_quit();
}

void on_button_loading_ready_clicked(GtkWidget *object, gpointer user_data) {
    g_print("Ready!\n");
    gtk_widget_destroy(user_data);
    gtk_main_quit();
    retl = 1;
}

void on_button_loading_exit_clicked(GtkWidget *object, gpointer user_data) {
    g_print("Exit!\n");
    gtk_main_quit();
    retl = 0;
}

int loading_run(GtkBuilder *builder) {

    GtkWidget *game;
    LoadingWindow wind;
    
    game = GTK_WIDGET (gtk_builder_get_object (builder, "window_loading"));
    if(game == NULL) {
        fprintf(stderr, "Error getting object from file.");
        return -1;
    }

    gtk_builder_connect_signals( builder, &wind );
    g_signal_connect (game, "destroy", G_CALLBACK (on_window_loading_destroy), NULL);

    gtk_widget_show (game);
    gtk_main ();

    return retl;
}
