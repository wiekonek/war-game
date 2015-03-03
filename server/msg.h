#ifndef MSG_H
#define	MSG_H

#define KEY_MSG 666


typedef struct msginitbuf {
long mtype;     // player number
int id;         // 1 - war, 2 - exit
} ID_msg;

typedef struct msgplayerbuf {
    long mtype; // 0 - player 1, 1 - player 2;
    int data[6];
//    0 - number of players; (3 - war) 
//    1 - resources;
//    2 - workers;
//    3 - light_soldiers;
//    4 - heavy_soldiers;
//    5 - cavalry;
} Player_msg;

#endif	/* MSG_H */

