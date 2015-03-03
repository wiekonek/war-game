#ifndef MSG_H
#define	MSG_H

#define KEY_ID1 66
#define KEY_ID2 67

typedef struct msginitbuf {
long mtype;     // player number
int id;         // 1 - war, 2 - exit
} ID_msg;

typedef struct msgplayerbufbuf {
    long mtype;
    int players;
    int resources;
    int workers;
    int light_soldiers;
    int heavy_soldiers;
    int cavalry;
} Player_msg;

#endif	/* MSG_H */

