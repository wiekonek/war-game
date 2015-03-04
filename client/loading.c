#include "loading.h"
int retl = 0;
int id_queue = 0;
int ID = 0;
LoadingWindow wind;

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
    int msgid;
    Player_msg msg;


    msgid = msgget( KEY_MSG, 0666);
    if( msgid == -1 ) {
        perror("Setting up init queue");
        g_print("Server isn't available.");
        exit(1);
    }
    g_print("Queue ID: %d\n", msgid);
       
    if ( msgrcv(msgid, &msg, 6, 5, 0) == -1 ) {
        perror("first msg rcv");
        exit(1);
    }
    
    
    g_print("ID: %d\n", msg.data[0]);
    ID = msg.data[0];
    
    msg.mtype=ID;
    int i;
    for(i = 0; i < 6; i++) {
        msg.data[i];
    }
    
    if ( msgsnd(msgid, &msg, 6, 0)) {
        
    }
    
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
    //funkcja musi zwrócić jedynkę by zostałą wykonana kolejny raz
    
    
    gtk_main ();

    return ID;
}
