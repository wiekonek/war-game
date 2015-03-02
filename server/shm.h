#ifndef SHM_H
#define	SHM_H

#define SHMEM_KEY 10

typedef struct {
    int resources[2];
    int workers[2];
    int light_soldiers[2];
    int heavy_soldiers[2];
    int cavalry[2];
} Data;

#endif	/* SHM_H */

