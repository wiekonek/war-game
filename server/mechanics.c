#include "mechanics.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <time.h>

void init_players(Data *data) {
    data->game = 1;
    int i = 0;
    for(i = 0; i < 2; i++) {
        data->wins[i] = 0;
        data->resources[i] = 300;
        data->workers[i] = 0;
        data->light_soldiers[i] = 0;
        data->heavy_soldiers[i] = 0;
        data->cavalry[i] = 0;
    }
}

void player(Data *data, int p_num) {
    
    int resources = data->resources[p_num];
    int workers = data->workers[p_num];

    resources = resources + 50 + workers*5;
    
    data->resources[p_num] = resources;
}

void itteration(Data *data) {
    int i = 0;
    for(i = 0; i < 2; i++) {
        player(data, i);
    }
}

void update_client(Data *data, int msgid, int player) {
    Player_msg msg;
    msg.mtype = player+3;
    msg.data[0] = 2;
    msg.data[1] = data->resources[player];
    msg.data[2] = data->workers[player];
    msg.data[3] = data->light_soldiers[player];
    msg.data[4] = data->heavy_soldiers[player];
    msg.data[5] = data->cavalry[player];
    msgsnd(msgid, &msg, sizeof(Player_msg)-sizeof(long), 0);
}

void update_clients(Data *data, int msgid) {
    int i;
    for( i = 0; i < 2; i++)
        update_client(data, msgid, i);
}

void loop(Data *data, int msgid) {
    init_players(data);
    update_clients(data, msgid);
    while(data->game) {
        sleep(1);
        itteration(data);
        update_clients(data, msgid);
    }
}

void mechanics(Data *data, int msgid) {
    printf("Mechanika gry.\n");
    loop(data, msgid);
}