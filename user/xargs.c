#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

int fgets(char* buf, int max){
    int n,i;
    char c;
    for(i = 0; i< max - 1 ;i++){
        n = read(0,&c,1);
        if(n == 0){
            break;
        }
        if(c == '\n'){
            break;
        }
        if(c == '\0'){
            break;
        }
        buf[i] = c;
    }
    buf[i] = '\0';
    return i;
}

void xargs(char ** args,int argc){
    char buf[128];
    char* exe_args[32];
    int len,i;

    if (argc < 2) {
        fprintf(2, "usage: xargs cmd [args...]\n");
        return;
   }

    if(argc > 32){
        fprintf(2, "xargs: too many args\n");
        exit(1);
    }

    for(i=1;i<argc;i++){
        exe_args[i-1] = args[i];
    }
    i-- ;
    while(1){
    
        len = fgets(buf,sizeof(buf));

        if(len <= 0){
            break;
        }

        exe_args[i] = (char*)malloc(len+1);

        strcpy(exe_args[i],buf);
        i++;
    }

    exe_args[i] = 0;
    int pid = fork();

    if(pid < 0){
         fprintf(2, "exec %s failed\n", exe_args[0]);
    }

    if(pid > 0){
        wait(0);
    }

    if (pid == 0) {
    exec(exe_args[0], exe_args); 
    fprintf(2, "exec %s failed\n", exe_args[0]);
    exit(1);
}
}

int main(int argc, char ** args){
    if(argc < 2){
        printf("none sufficient args\n");
        exit(1);
    }

    xargs(args,argc);

    return 0;
}