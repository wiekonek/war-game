#include "communication.h"
#include <stdio.h>
#include <time.h>
#include "msg.h"
#include "shm.h"

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
    Player_msg rcv;
    //msgrcv(smgid, &rcv, 6, num, 0);
    rcv.data[2] = 1;
    rcv.data[3] = 0;
    rcv.data[4] = 0;
    rcv.data[5] = 0;
    int i;
    for(i = 2; i < 6; i++)
        if(rcv.data[i])
            switch(i){
                case 2:     add_worker(data, num);      break;
                case 3:     add_ls(data, num);          break;
                case 4:     add_hs(data, num);          break;
                case 5:     add_cavalry(data, num);     break;
                    
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
        sleep(2);
        client(1, data, msgid);
    }
}
