#include "loading.h"
int ID = 0;
GtkWidget *window;
LoadingWindow wind;

void on_window_loading_destroy (GtkWidget *object, gpointer user_data) {
    gtk_main_quit();
}

int end(GtkWidget* window) {
    int msgid;
    Player_msg msg;
    
    msgid = msgget( KEY_MSG, 0666);
    if( msgid == -1 ) {
        perror("Setting up init queue");
        exit(1);
    }

    if ( msgrcv(msgid, &msg, sizeof(Player_msg)-sizeof(long), ID+2, IPC_NOWAIT) == -1 ) {
        return 1;
    } else {
        g_print("Zaczynamy!\n");
        gtk_widget_destroy(window);
        return 0;
    }
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
       
    if ( msgrcv(msgid, &msg, sizeof(Player_msg)-sizeof(long), 5, 0) == -1 ) {
        perror("msgrcv: first msg rcv");
        exit(1);
    }
    
    
    g_print("ID: %d\n", msg.data[0]);
    ID = msg.data[0];
    
    msg.mtype=ID;
    int i;
    for(i = 0; i < 6; i++) {
        msg.data[i];
    }
    
    if ( msgsnd(msgid, &msg, sizeof(Player_msg)-sizeof(long), 0)) {
        
    }
    
    if(ID == 1)
        gtk_label_set_text(label, "Twoje ID to: 1\n Oczekiwanie na drugiego gracza.");
    else
        gtk_label_set_text(label, "Twoje ID to: 2\n Oczekiwanie na drugiego gracza.");
    
    g_timeout_add ( 10, G_CALLBACK (end), window);
}

int loading_run(GtkBuilder *builder) {

    

   
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
    g_timeout_add ( 1, G_CALLBACK (start), wind.label);
    //funkcja musi zwrócić jedynkę by zostałą wykonana kolejny raz
    
    
    gtk_main ();

    return ID;
}
