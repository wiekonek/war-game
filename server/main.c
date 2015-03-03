#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <unistd.h>

#include "msg.h"
#include "shm.h"
#include "mechanics.h"
#include "communication.h"

#define KEY_SEM 16

int main(int argc, char** argv) {

    
    
    printf("Serwer działa.\n");
    /*
    id_queue = msgget( KEY_ID1, IPC_CREAT | 0666 );
    
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


    msgctl(id_queue, IPC_RMID, NULL);
    
    */
    
    printf("Zaczynamy grę. Inicjalizowanie: kolejka, pamięć, semafory.\n");  
    
    int shmid = 0, msgid = 0, semid = 0;
    
    if( -1 == (shmid = shmget ( SHMEM_KEY, sizeof(Data), IPC_CREAT | 0666)) ){
        perror("Shared memory");
        exit(1);
    }
    
    if( -1 == (msgid = msgget ( KEY_MSG, IPC_CREAT | 0666 )) ){
        perror("Main queue");
        shmctl(shmid, IPC_RMID, NULL);
        exit(1);
    }
    
    if( -1 == (semid = semget ( KEY_SEM, 1, IPC_CREAT )) ){
        perror("Main queue");
        shmctl(shmid, IPC_RMID, NULL);
        msgctl(msgid, IPC_RMID, NULL);
        exit(1);
    }

    Data *data;
    data = (Data*)shmat(shmid, 0, 0);
    data->cavalry[1]=0;
    
    if ( fork() ) {    //mechanika
        mechanics(data);
        wait(NULL);
        printf("Cleaning.");
        shmctl(shmid, IPC_RMID, NULL);
        msgctl(msgid, IPC_RMID, NULL);
        semctl(semid, 0, IPC_RMID, NULL);
    } else {        //komunikacja z klientami, proces potomny
        communication(data, msgid);
    }
    
    

    return (0);
}

