#ifndef MSG_H
#define	MSG_H

#define KEY_ID 66

typedef struct msginitbuf {
long mtype;//przydzielenie IP - 1, nowi gracze - 2
int id;
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

