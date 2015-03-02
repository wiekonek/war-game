#include "communication.h"
#include <stdio.h>
#include "msg.h"
#include "shm.h"


void client(int num, int shmid) {
    Data *data;
    data = shmat( shmid, 0, 0);
    
    
    
    shmdt(data);
}

void communication(int shmid) {
    
    printf("Komunikacja z klientami.\n");
    
    if(fork()) {
        client(1, shmid);
    } else {
        client(2, shmid);
    }
    
   
    
    
    
}
