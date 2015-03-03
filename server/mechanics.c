#include "mechanics.h"
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>
#include "shm.h"

void init_players(Data *data) {
    int i = 0;
    for(i = 0; i < 2; i++) {
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

void loop(Data *data) {
    printf("Loop\n");
    init_players(data);
    int i = 0;
    
    while(666) {
        i++;
        sleep(1);
        itteration(data);
        printf("Gracz 1: %d, gracz 2: %d\n", data->resources[0], data->resources[1]);
        
        
        
        
        
        if(i>=10) {
            break;
        }
    }
}


void mechanics(Data *data) {
    printf("Mechanika gry : )\n");
    loop(data);
}
