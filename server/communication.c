#include "communication.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <time.h>
#include "mechanics.h"

void add_worker(Data *data, int num) {
    sleep(2);
    (data->workers[num])++;
}

void add_ls(Data *data, int num) {
    sleep(3);
    (data->light_soldiers[num])++;
}

void add_hs(Data *data, int num) {
    sleep(3);
    (data->heavy_soldiers[num])++;
}

void add_cavalry(Data *data, int num) {
    sleep(5);
    (data->cavalry[num])++;
}

void rec(Player_msg msg, Data *data, int num) {
    int i;
    for(i = 2; i < 6; i++)
        if(msg.data[i])
            switch(i){
                case 2:     add_worker(data, num);      break;
                case 3:     add_ls(data, num);          break;
                case 4:     add_hs(data, num);          break;
                case 5:     add_cavalry(data, num);
            }
}

void end_game(Data *data, int msgid, int num) {
    printf("End game.\n");
    Player_msg snd;
    if(num == 1) 
        snd.mtype = 4;
    else
        snd.mtype = 3;
    snd.data[0] = -1;
    if ( msgsnd(msgid, &snd, 6, 0) == -1 ) {
        perror("msgsnd(): end game");
    }
    data->game = 0;
}

void battle(Player_msg msg, Data *data, int num) {
}

void client(int num, Data *data, int msgid) {
    Player_msg rcv;
    while(data->game) {
        if ( msgrcv(msgid, &rcv, 6, num, IPC_NOWAIT) != -1 ) {
            switch(rcv.data[0]) {
                case -1:    end_game(data, msgid, num);     break;
                case 2:     rec(rcv, data, num);          break;
                case 3:     battle(rcv, data, num);
            }
        }
    }
}

void communication(Data *data, int msgid) {
    
    printf("Komunikacja z klientami.\n");
    pid_t pid = fork();
    if( pid ) {
        client(0, data, msgid);
        wait(NULL);
        printf("Koniec komunikacji.\n");
    } else { // proces potomny
        client(1, data, msgid);
    }
}
