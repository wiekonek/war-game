#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#include "msg.h"
#include "shm.h"
#include "mechanics.h"
#include "communication.h"

int main(int argc, char** argv) {
    int i = 0;
    int id_queue = 0;
    ID_msg rcv, snd;
    
    
    printf("Serwer działa.\n");
    id_queue = msgget( KEY_ID, IPC_CREAT | 0666 );
    
    snd.mtype = 1;
    for(i = 1; i < 3; i++) {
        snd.id = i;
        if( msgsnd(id_queue, &snd, 1, 0) == -1 ) {
            perror("Snd");
        }  
    }
    
    printf("ID kolejki: %d.\nOczekiwanie na graczy.\n", id_queue);
    
/*
    for(i = 1; i < 3; i++) {
        if( msgrcv(id_queue, &rcv, 1, 2, 0) == -1 ) {
            perror("Rcv");
        }  
    }
*/
    printf("Zaczynamy grę.");
    msgctl(id_queue, IPC_RMID, NULL);
    
    
    int shmid = 0;
    shmid = shmget ( SHMEM_KEY, sizeof(Data), IPC_CREAT | 0666);
    pid_t pID;
    
    pID = fork();
    if ( pID ) {    //mechanika
        mechanics(shmid);
    } else {        //komunikacja z klientami
        communication(shmid);
    }

    
    return (0);
}

