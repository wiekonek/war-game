#ifndef SHM_H
#define	SHM_H

#define SHMEM_KEY 11

typedef struct {
    int game;
    int wins[2];
    int resources[2];
    int workers[2];
    int light_soldiers[2];
    int heavy_soldiers[2];
    int cavalry[2];
} Data;

#endif	/* SHM_H */

