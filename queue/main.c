/* 
 * File:   main.c
 * Author: wiekonek
 *
 * Created on March 5, 2015, 2:33 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/types.h>
/*
 * 
 */
int main(int argc, char** argv) {
    
    int msgid;
    
    if( -1 == (msgid = msgget ( 666, 0666 )) ){
        perror("Main queue");
        exit(1);
    }
    
    msgctl(msgid, IPC_RMID, NULL);
    printf("Queue deleted.\n");
    return (EXIT_SUCCESS);
}

