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
    if( data->resources[num] >= 150 ) {
        data->resources[num] = data->resources[num]-150;
        sleep(2);
        (data->workers[num])++;
    }
}

void add_ls(Data *data, int num) {
    if( data->resources[num] >= 100 ) {
        data->resources[num] = data->resources[num]-100;
        sleep(2);
        (data->light_soldiers[num])++;
    }
}

void add_hs(Data *data, int num) {
    if( data->resources[num] >= 250 ) {
        data->resources[num] = data->resources[num]-250;
        sleep(3);
        (data->heavy_soldiers[num])++;
    }
}

void add_cavalry(Data *data, int num) {
    if( data->resources[num] >= 550 ) {
        data->resources[num] = data->resources[num]-550;
        sleep(5);
        (data->cavalry[num])++;
    }
}

void rec(Player_msg msg, Data *data, int num) {
    int i, j;
    num--;
    for(i = 2; i < 6; i++)
        if(msg.data[i] == 1)
            switch(i){
                case 2:     for(j = 0; j < msg.data[2]; j++) add_worker(data, num);      break;
                case 3:     for(j = 0; j < msg.data[3]; j++) add_ls(data, num);          break;
                case 4:     for(j = 0; j < msg.data[4]; j++) add_hs(data, num);          break;
                case 5:     for(j = 0; j < msg.data[5]; j++) add_cavalry(data, num);
            }
}

void end_game(Data *data, int msgid, int num) {
    printf("Zakoncz rozgrywke.\n");
    Player_msg snd;
    if(num == 1) 
        snd.mtype = 4;
    else
        snd.mtype = 3;
    snd.data[0] = -1;
    if ( msgsnd(msgid, &snd, sizeof(Player_msg)-sizeof(long), 0) == -1 ) {
        perror("msgsnd(): end game");
    }
    data->game = 0;
}

int power(int tab[3]) {
    return tab[0] + tab[1]*1.5 + tab[2]*3.5;
}

int defence(int tab[3]) {
    return tab[0]*1.2 + tab[1]*3 + tab[2]*1.2;
}

void battle(Player_msg rcv, Data *data, int my_id, int msgid) {
    Player_msg snd;
    int i, op_id = 1, my_power, my_defence, op_power, op_defence, lost;
    if( my_id == 1 )
        op_id = 2;
    snd.mtype = my_id+2;
    for(i = 0; i < 6; i++)
        snd.data[i] = 0;
    
    int my_soldiers[3] = {rcv.data[3], rcv.data[4], rcv.data[5]};
    data->light_soldiers[my_id-1] -= my_soldiers[0];
    data->heavy_soldiers[my_id-1] -= my_soldiers[1];
    data->cavalry[my_id-1] -= my_soldiers[2];
    int op_soldiers[3] = {data->light_soldiers[op_id-1], data->heavy_soldiers[op_id-1], data->cavalry[op_id-1]};
    
    my_power = power(my_soldiers);
    my_defence = defence(my_soldiers);
    op_power = power(op_soldiers);
    op_defence = defence(op_soldiers);
   
    sleep(5);
   
    if(my_power > op_defence) {
        
        if(++data->wins[my_id-1] < 5) {
            snd.data[0] = 3;
            msgsnd(msgid, &snd, sizeof(Player_msg)-sizeof(long), 0);
            printf("Wygrales bitwe. Iość Twoich wygranych: %d\n", data->wins[my_id-1]);
        } else {
            printf("Wygrales.\n");
            snd.data[0] = 5;
            msgsnd(msgid, &snd, sizeof(Player_msg)-sizeof(long), 0);
            snd.mtype = op_id+2;
            snd.data[0] = 6;
            msgsnd(msgid, &snd, sizeof(Player_msg)-sizeof(long), 0);
            data->game = 0;
        }
        
    } else {
        printf("Dupa.\n");
        snd.data[0] = 4;
        msgsnd(msgid, &snd, sizeof(Player_msg)-sizeof(long), 0);
    }
    
    if(my_power  < op_defence) {
        lost = my_power/op_defence;
        data->light_soldiers[op_id-1] -= op_soldiers[0]*lost;
        data->heavy_soldiers[op_id-1] -= op_soldiers[1]*lost;
        data->cavalry[op_id-1] -= op_soldiers[2]*lost;
    } else {
        data->light_soldiers[op_id-1] = 0;
        data->heavy_soldiers[op_id-1] = 0;
        data->cavalry[op_id-1] = 0;
    }
    
    if(op_power < my_defence) {
        lost = op_power/my_defence;
        data->light_soldiers[my_id-1] += my_soldiers[0] - my_soldiers[0]*lost;
        data->heavy_soldiers[my_id-1] += my_soldiers[1] - my_soldiers[1]*lost;
        data->cavalry[my_id-1] += my_soldiers[2] - my_soldiers[2]*lost;
    }
        
    
}

void client(int num, Data *data, int msgid) {
    Player_msg rcv;
    while(data->game) {
        if ( msgrcv(msgid, &rcv, sizeof(Player_msg)-sizeof(long), num, IPC_NOWAIT) != -1 ) {
            switch(rcv.data[0]) {
                case -1:    end_game(data, msgid, num);     break;
                case 2:     rec(rcv, data, num);          break;
                case 3:     battle(rcv, data, num, msgid);
            }
        }
    }
}

void communication(Data *data, int msgid) {
    
    printf("Komunikacja z klientami.\n");
    pid_t pid = fork();
    if( pid ) {
        client(1, data, msgid);
        wait(NULL);
        printf("Koniec komunikacji.\n");
    } else { // proces potomny
        client(2, data, msgid);
    }
}
