#include "start.h"
int ret = 0;

void on_window_start_destroy (GtkWidget *object, gpointer user_data) {
    gtk_main_quit();
    gtk_widget_destroy(user_data);
}

void on_button_start_connect_clicked(GtkWidget *object, gpointer user_data) {
    g_print("Connect me to server!\n");
    gtk_main_quit();
    gtk_widget_destroy(user_data);
    ret = 1;
}

void on_button_start_exit_clicked(GtkWidget *object, gpointer user_data) {
    g_print("Exit!\n");
    gtk_main_quit();
    gtk_widget_destroy(user_data);
    ret = 0;
}

int start_run(GtkBuilder *builder) {

    GtkWidget *window;
    StartWindow wind;
    
    window = GTK_WIDGET (gtk_builder_get_object (builder, "window_start"));
    if(window == NULL) {
        fprintf(stderr, "Error getting object from file.");
        return -1;
    }
    wind.button_start = GTK_BUTTON (gtk_builder_get_object (builder, "window_button_start"));
    wind.button_exit = GTK_BUTTON (gtk_builder_get_object (builder, "window_button_exit"));

    gtk_builder_connect_signals( builder, &wind );
    g_signal_connect (window, "destroy", G_CALLBACK (on_window_start_destroy), window);

    gtk_widget_show (window);
    
    gtk_main ();

    return ret;
}