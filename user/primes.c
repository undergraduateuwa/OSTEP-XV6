#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void prime_sieve(int fd){
    int num = 0;
    int n = read(fd,&num,sizeof(int));
    if(n == 0){
        close(fd);
        exit(0);
    }
    printf("prime %d\n",num);

    int pd[2];
    pipe(pd);


    if(fork() == 0){
        close(pd[1]);
        prime_sieve(pd[0]);
    }
    else{
        int left = 0;
        while(read(fd,&left,sizeof(int))==sizeof(left)){
            if(left % num == 0){
                continue;
            }
            else{
                write(pd[1],&left,sizeof(left));
            }
        }

        close(pd[0]);
        close(pd[1]);
        wait(0);
    }
}


int main(int argc, char** args){
    if(argc < 1){
        printf("insufficient args");
        exit(0);
    }
    int num = atoi(args[1]);

    if(num > 36){
        printf("too large\n");
        exit(0);
    }
    int p[2];
    pipe(p);

    if(fork() == 0){
        close(p[1]);
        prime_sieve(p[0]);
    }
    else{
        close(p[0]);
        for(int i=2;i<= num;i++){
            write(p[1],&i,sizeof(i));
        }
        close(p[1]);
        wait(0);
    }
}