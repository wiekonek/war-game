#include "communication.h"
#include <stdio.h>
#include <time.h>
#include "msg.h"
#include "shm.h"

void wait(int i) {
    clock_t trigger = i * 1000;
    int msec = 0;
    clock_t start = clock();
    while ( msec < trigger ) {
        clock_t difference = clock() - start;
        msec = difference * 1000 / CLOCKS_PER_SEC;
    }
}

void add_worker(Data *data, int num) {
    wait(2);
    (data->workers[num])++;
}

void add_ls(Data *data, int num) {
    wait(3);
    (data->light_soldiers[num])++;
}

void add_hs(Data *data, int num) {
    wait(3);
    (data->heavy_soldiers[num])++;
}

void add_cavalry(Data *data, int num) {
    wait(5);
    (data->cavalry[num])++;
}
void client(int num, Data *data, int smgid) {
    printf("Dupa\n");
    //Data *data;
    //data = shmat( shmid, 0, 0);
    //perror("Shm attach");
    printf("Workers: %d\n", data->workers[num]);
    printf("Dupa2\n");
    Player_msg rcv;
    //msgrcv(smgid, &rcv, 6, num, 0);
    rcv.workers = 1;
    rcv.light_soldiers = 0;
    rcv.heavy_soldiers = 0;
    rcv.cavalry = 0;
    
    if(rcv.workers)
        add_worker(data, num);
    if(rcv.light_soldiers)
        add_ls(data, num);
    if(rcv.heavy_soldiers)
        add_hs(data, num);
    if(rcv.cavalry)
        add_cavalry(data, num);
    printf("Workers: %d\n", data->workers[num]);
    //shmdt(data);
}

void communication(Data *data, int msgid) {
    
    printf("Komunikacja z klientami.\n");
    
    if(fork()) {
        client(1, data, msgid);
    } else {
        client(2, data, msgid);
    }
        
}
