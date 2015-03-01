#include "loading.h"
int retl = 0;

void on_window_loading_destroy (GtkWidget *object, gpointer user_data) {
    gtk_main_quit();
    gtk_widget_destroy(user_data);
}

void on_button_loading_ready_clicked(GtkWidget *object, gpointer user_data) {
    g_print("Ready!\n");
    gtk_main_quit();
    gtk_widget_destroy(user_data);
    retl = 1;
}

void on_button_loading_exit_clicked(GtkWidget *object, gpointer user_data) {
    g_print("Exit!\n");
    gtk_main_quit();
    gtk_widget_destroy(user_data);
    retl = 0;
}

int loading_run(GtkBuilder *builder) {

    GtkWidget *window;
    LoadingWindow wind;
    
    window = GTK_WIDGET (gtk_builder_get_object (builder, "window_loading"));
    if(window == NULL) {
        fprintf(stderr, "Error getting object from file.");
        return -1;
    }

    gtk_builder_connect_signals( builder, &wind );
    g_signal_connect (window, "destroy", G_CALLBACK (on_window_loading_destroy), window);

    gtk_widget_show (window);
    gtk_main ();

    return retl;
}
