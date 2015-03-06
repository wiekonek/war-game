#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

#include "msg.h"
#include "shm.h"
#include "mechanics.h"
#include "communication.h"

#define KEY_SEM 16

int main(int argc, char** argv) {
    
    int shmid = 0, msgid = 0, semid = 0;
    int i;
    Player_msg msg;
    
    printf("Serwer działa.\nInicializowanie: kolejka.\n");    
    
    if( -1 == (msgid = msgget ( KEY_MSG, IPC_CREAT | 0666 )) ){
        perror("Main queue");
        exit(1);
    }
    
    msg.mtype = 5;
    for(i = 1; i < 3; i++) {
        msg.data[0] = i;
        if( msgsnd(msgid, &msg, 6, 0) == -1 ) {
            perror("msgsnd: init players");
        } 
    }
    
    for(i = 1; i < 3; i++) {
        if( msgrcv(msgid, &msg, 6, i, 0) == -1 ) {
            perror("msgrcv: info from clients");
        } 
        printf("Player ID=%d ready.\n", i);
    }
    
    printf("Zaczynamy grę. Inicjalizowanie: pamięć, semafory.\n");
    for(i = 1; i < 3; i++) {
        msg.mtype = i + 2;
        msg.data[0] = 2;
        if( msgsnd(msgid, &msg, 6, 0) == -1 ) {
            perror("msgsnd: start game");
        } 
    }
    

    if( -1 == (shmid = shmget ( SHMEM_KEY, sizeof(Data), IPC_CREAT | 0666)) ){
        perror("Shared memory");
        msgctl(msgid, IPC_RMID, NULL);
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
        mechanics(data, msgid);
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

