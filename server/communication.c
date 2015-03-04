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
void client(int num, Data *data, int smgid) {
    printf("Player: %d Workers from communication 1: %d\n", num, data->workers[num]);
    int i;
    Player_msg rcv;
    while(666) {
        msgrcv(smgid, &rcv, 6, num, 0);
        for(i = 2; i < 6; i++)
            if(rcv.data[i])
                switch(i){
                    case 2:     add_worker(data, num);      break;
                    case 3:     add_ls(data, num);          break;
                    case 4:     add_hs(data, num);          break;
                    case 5:     add_cavalry(data, num);
                }
    }
    printf("Player: %d Workers from communication 2: %d\n", num, data->workers[num]);
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
