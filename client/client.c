#include "client.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int ID;
int msgid;
int wins;
Player_msg snd, rcv;
ClientWindow wind;
GtkWidget *game;
GtkBuilder *build;
    
void on_window_game_destroy (GtkWidget *object, gpointer user_data) {
    snd.data[0] = -1;
    if( msgsnd(msgid, &snd, sizeof(Player_msg)-sizeof(long), 0) == -1) {
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
            case 3:  gtk_label_set_text(wind.ls, c); gtk_adjustment_set_upper (wind.ad_ls, rcv.data[3]);       break;
            case 4:  gtk_label_set_text(wind.hs, c); gtk_adjustment_set_upper (wind.ad_hs, rcv.data[4]);       break;
            case 5:  gtk_label_set_text(wind.cavalry, c); gtk_adjustment_set_upper (wind.ad_cavalry, rcv.data[5]);  break;
        }     
    }
}

void end_game() {
    gtk_widget_destroy(game);
}

void win() {
    GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;
    GtkWidget *dialog = gtk_message_dialog_new (GTK_WINDOW(game), flags, GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE, "Wygrałeś.");
    gtk_dialog_run (GTK_DIALOG (dialog));
    gtk_widget_destroy (dialog);
    end_game();
}

void loose() {
    GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;
    GtkWidget *dialog = gtk_message_dialog_new (GTK_WINDOW(game), flags, GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE, "Przegrałeś.");
    gtk_dialog_run (GTK_DIALOG (dialog));
    gtk_widget_destroy (dialog);
    end_game();
}

void win_battle() {
    wins++;
    char c[1];
    sprintf(c, "%d", wins);
    gtk_label_set_text(wind.wins, c);
    g_print("wygrales bitwe.\n");
}

void loose_battle() {
    g_print("Przegrales bitwe.\n");
}

int update (gpointer nie_wiem) {
    if ( msgrcv(msgid, &rcv, sizeof(Player_msg)-sizeof(long), ID+2, IPC_NOWAIT) != -1 ) {
        switch(rcv.data[0]) {
            case -1: end_game();        break;
            case 2: refresh_labels();   break;
            case 3: win_battle();       break;
            case 4: loose_battle();     break;
            case 5: win();              break;
            case 6: loose();
        }
    }
    
    return 1;
}

void send_msg(int what) {
    snd.data[0] = what;
    if ( msgsnd(msgid, &snd, sizeof(Player_msg)-sizeof(long), 0) ) {
        perror("msgsnd(): rec");
    }
}


void on_button_rec1_clicked(GtkWidget *object, gpointer user_data) {
    int i;
    for(i = 2; i < 6; i++)
        snd.data[i] = 0;
    snd.data[2] = 1;
    send_msg(2);
}

void on_button_rec2_clicked(GtkWidget *object, gpointer user_data) {
    int i;
    for(i = 2; i < 6; i++)
        snd.data[i] = 0;
    snd.data[3] = 1;
    send_msg(2);
}

void on_button_rec3_clicked(GtkWidget *object, gpointer user_data) {
    int i;
    for(i = 2; i < 6; i++)
        snd.data[i] = 0;
    snd.data[4] = 1;
    send_msg(2);
}

void on_button_rec4_clicked(GtkWidget *object, gpointer user_data) {
    int i;
    for(i = 2; i < 6; i++)
        snd.data[i] = 0;
    snd.data[5] = 1;
    send_msg(2);
}

void on_button_attack_clicked(GtkWidget *object, gpointer user_data) {
    int ls, hs, cavalry, i;
    
    ls = gtk_range_get_value ( GTK_RANGE(wind.scale_ls) );
    hs = gtk_range_get_value ( GTK_RANGE(wind.scale_hs) );
    cavalry = gtk_range_get_value ( GTK_RANGE(wind.scale_cavalry) );
    g_print("Zaatakuj\n");
    snd.data[1] = 0;
    snd.data[2] = 0;
    snd.data[3] = ls;
    snd.data[4] = hs;
    snd.data[5] = cavalry;
    send_msg(3);
}

void on_button_exit_clicked(GtkWidget *object, gpointer user_data) {
    end_game();
}

int client_run(GtkBuilder *builder, int id) {
    wins = 0;
    build = builder;
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
    wind.wins = GTK_LABEL (gtk_builder_get_object(builder, "label_wins"));
    wind.scale_ls = GTK_SCALE (gtk_builder_get_object(builder, "scale_ls"));
    wind.scale_hs = GTK_SCALE (gtk_builder_get_object(builder, "scale_hs"));
    wind.scale_cavalry = GTK_SCALE (gtk_builder_get_object(builder, "scale_cavalry"));
    wind.ad_ls = GTK_ADJUSTMENT (gtk_builder_get_object(builder, "adjustment_ls"));
    wind.ad_hs = GTK_ADJUSTMENT (gtk_builder_get_object(builder, "adjustment_hs"));
    wind.ad_cavalry = GTK_ADJUSTMENT (gtk_builder_get_object(builder, "adjustment_cavalry"));
    
    
    char c[1];
    sprintf(c, "%d", id);
    gtk_label_set_text(wind.id, c);

    g_timeout_add( 10, G_CALLBACK (update), NULL);
    
    gtk_builder_connect_signals( builder, &wind );
    g_signal_connect (game, "destroy", G_CALLBACK (on_window_game_destroy), game);

    gtk_widget_show (game);       
    gtk_main ();

    return 0;
}
