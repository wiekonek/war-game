#include "shm.h"

Data convertToData(char* shmem) {
    
}

int add(char* ch, int where, char what[5]) {
    int i;
    for(i = 0 ; i< 5; i++) {
        ch[i] = what[i];
    }
    ch[++i] = what [i];
    return i;
}

char* convertToShMem(Data data) {
    char mem[61];
    char c[5];
    int i, j, k = 0;
    for(i = 0; i < 2; i++) {
        sprintf(c, "%d", data.workers[i]);
        k = add(mem, k, c);
    }
}