#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc,char** args){
    int c2p[2];
    int p2c[2];

    pipe(c2p);
    pipe(p2c);

    if(fork() == 0){
        close(p2c[1]);
        close(c2p[0]);
        char buf;
        read(p2c[0],&buf,1);
        fprintf(1,"<%d>:revieved ping,(%c)\n",getpid(),buf);
        close(p2c[1]);

        write(c2p[1],&buf,1);
        close(c2p[1]);
        exit(0);
    }
    else {
        close(p2c[0]);
        close(c2p[1]);

        char buf = 'A';

        write(p2c[1],&buf,1);
        
        close(p2c[1]);

        read(c2p[0],&buf,1);

        fprintf(1,"<%d>:revieved pong,(%c)\n",getpid(),buf);

        close(c2p[0]);
        exit(0);
    }
}