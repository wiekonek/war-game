#include "mechanics.h"
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>
#include "shm.h"

void loop() {
    clock_t trigger = 1000;
    while(666) {
        int msec = 0;
        clock_t start = clock();
        while ( msec < trigger ) {
          clock_t difference = clock() - start;
          msec = difference * 1000 / CLOCKS_PER_SEC;
        }
        
        
        
        
    }
}


void mechanics(int shmid) {
    printf("Mechanika gry : )\n");
    char* shmem;
/*
    int shmget ( key_t key, size_t size, int shmflags );
    int shmctl ( int shmid, int cmd, struct shmid_ds *buf );
    char* shmat ( int shmid, char* shmaddr, int shmflg );
    char* shmdt ( char* shmaddr );
*/  
    shmem = shmat( shmid, 0, 0);
    
    shmdt(shmem);
}
