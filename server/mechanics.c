#include "mechanics.h"
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>
#include "shm.h"

void init_players(Data *data) {
    int i = 0;
    for(i = 0; i < 2; i++) {
        printf("przed dostępem\n");
        data->resources[i] = 300;
        printf("po_dostpeie\n");
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

void loop(Data *data) {
    printf("loop\n");
    init_players(data);
    printf("init\n");
    int i = 0;
    clock_t trigger = 1000;
    while(666) {
        i++;
        int msec = 0;
        clock_t start = clock();
        while ( msec < trigger ) {
          clock_t difference = clock() - start;
          msec = difference * 1000 / CLOCKS_PER_SEC;
        }
        printf("in_loop\n");
        itteration(data);
        printf("Gracz 1: %d, gracz 2: %d\n", data->resources[0], data->resources[1]);
        
        
        
        
        
        if(i>=30) {
            break;
        }
    }
}


void mechanics(Data *data) {
    printf("Mechanika gry : )\n");
    //Data *data;
    
    //data = shmat( shmid, 0, 0);
    loop(data);
   
    //shmdt(data);
}
