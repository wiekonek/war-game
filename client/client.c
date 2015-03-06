#include "client.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int ID;
int msgid;
Player_msg snd, rcv;
ClientWindow wind;
GtkWidget *game;
    
void on_window_game_destroy (GtkWidget *object, gpointer user_data) {
    snd.data[0] = -1;
    if( msgsnd(msgid, &snd, 6, 0) == -1) {
        perror("msgsnd(): Deleting msg");
    }           
    gtk_main_quit();
    gtk_widget_destroy(user_data);
}

void refresh_labels () {
    char c[10];
    int i;
    for(i = 1; i < 6; i++) {
        sprintf(c, "%d", rcv.data[i]);
        switch(i) {
            case 1:  gtk_label_set_text(wind.resources, c); break;
            case 2:  gtk_label_set_text(wind.workers, c); break;
            case 3:  gtk_label_set_text(wind.ls, c); break;
            case 4:  gtk_label_set_text(wind.hs, c); break;
            case 5:  gtk_label_set_text(wind.cavalry, c); break;
        }     
    }
}

void win() {
    
}

void loose() {
    
}

void win_battle() {
    
}

void loose_battle() {
    
}

void end_game() {
    gtk_widget_destroy(game);
}

int update (gpointer nie_wiem) {
    if ( msgrcv(msgid, &rcv, 6, ID+2, IPC_NOWAIT) != -1 ) {
        switch(rcv.data[0]) {
            case -1: end_game();        break;
            case 2: refresh_labels();   break;
            case 3: win_battle();       break;
            case 4: loose_battle();     break;
            case 5: win();              break;
            case 6: loose();
        }
    } else {
        //perror("update: msgrcv");
    }
    return 1;


}

int client_run(GtkBuilder *builder, int id) {
    ID = id;
    snd.mtype = ID;

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
    wind.button_attack =  GTK_BUTTON (gtk_builder_get_object(builder, "button_attack"));
    wind.button_exit =  GTK_BUTTON (gtk_builder_get_object(builder, "button_exit"));
    wind.button_rec1 =  GTK_BUTTON (gtk_builder_get_object(builder, "button_rec1"));
    wind.button_rec2 =  GTK_BUTTON (gtk_builder_get_object(builder, "button_rec2"));
    wind.button_rec3 =  GTK_BUTTON (gtk_builder_get_object(builder, "button_rec3"));
    wind.button_rec4 =  GTK_BUTTON (gtk_builder_get_object(builder, "button_rec4"));
    wind.resources =  GTK_LABEL (gtk_builder_get_object(builder, "label_resource"));
    wind.workers =  GTK_LABEL (gtk_builder_get_object(builder, "label_workers"));
    wind.ls =  GTK_LABEL (gtk_builder_get_object(builder, "label_ls"));
    wind.hs =  GTK_LABEL (gtk_builder_get_object(builder, "label_hs"));
    wind.cavalry =  GTK_LABEL (gtk_builder_get_object(builder, "label_cavalry"));
    wind.id = GTK_LABEL (gtk_builder_get_object(builder, "label_id"));
    
    char c[1];
    sprintf(c, "%d", id);
    gtk_label_set_text(wind.id, c);

    g_timeout_add ( 10, G_CALLBACK (update), NULL);
    
    gtk_builder_connect_signals( builder, &wind );
    g_signal_connect (game, "destroy", G_CALLBACK (on_window_game_destroy), game);

    gtk_widget_show (game);       
    gtk_main ();

    return 0;
}
