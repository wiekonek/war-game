#include "loading.h"
int retl = 0;
int id_queue = 0;
int ID = 0;
LoadingWindow wind;

void clening() {
    exit(1);
}

void on_window_loading_destroy (GtkWidget *object, gpointer user_data) {
    gtk_main_quit();
    if( msgctl(id_queue, IPC_RMID, NULL) == -1 ) {
        perror("Deleting queue: ");
    }
}

void on_button_loading_ready_clicked(GtkWidget *object, gpointer user_data) {
    g_print("Ready!\n");
    gtk_widget_destroy(user_data);
    retl = 1;
}

void on_button_loading_exit_clicked(GtkWidget *object, gpointer user_data) {
    g_print("Exit!\n");
    gtk_widget_destroy(user_data);
    retl = 0;
}

void start(gpointer label) {
    int retty;
    ID_msg snd, rcv;
    snd.mtype = 1;
    snd.id = 0;
    rcv.mtype = 2;
    rcv.id = 0;

    id_queue = msgget( KEY_ID, 0777);
    if( id_queue < 1 ) {
        perror("Setting up queue");
        g_print("Server isn't available.");
        exit(1);
    }
    g_print("Queue ID: %d\n", id_queue);
    
    if( msgsnd(id_queue, &snd, 1, 0) == -1 ) {
        perror("Sending");
        exit(1);
    }    
    g_print("Message send.\n");
    
    msgrcv(id_queue, &rcv, 1, 2, 0);
    g_print("ID: %d\n", rcv.id);
    ID = rcv.id;
    
    if(ID == 1)
        gtk_label_set_text(label, "Twoje ID to: 1\n Oczekiwanie na drugiego gracza.");
    else
        gtk_label_set_text(label, "Twoje ID to: 2\n Oczekiwanie na drugiego gracza.");
    //gtk_spinner_stop(wind.spinner);
}


int loading_run(GtkBuilder *builder) {

    GtkWidget *window;

   
    window = GTK_WIDGET (gtk_builder_get_object (builder, "window_loading"));
    if(window == NULL) {
        fprintf(stderr, "Error getting object from file.");
        return -1;
    }

    gtk_builder_connect_signals( builder, &wind );
    g_signal_connect (window, "destroy", G_CALLBACK (on_window_loading_destroy), window);
    
    wind.label = GTK_LABEL (gtk_builder_get_object (builder, "label_loading"));
    wind.spinner = GTK_SPINNER (gtk_builder_get_object (builder, "spinner_loading"));
    
    gtk_widget_show (window);
    g_timeout_add ( 1000, G_CALLBACK (start), wind.label);
    
    
    gtk_main ();

    return ID;
}
