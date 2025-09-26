#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int main(int argc,char** args){
    struct sysinfo * sif = malloc(sizeof(struct sysinfo*));
    info(sif);
    printf("nproc: %d, freemem: %d\n", sif->nproc, sif->freemem);
    exit(0);
}