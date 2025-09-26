#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void trace(int argc, char **args) {

    char **exe_args = malloc(sizeof(char*) * argc);

    for (int i = 2; i < argc; i++) {
        exe_args[i-2] = malloc(128);
        strcpy(exe_args[i-2],args[i]);
    }
    exe_args[argc-2] = 0; 

    int pid = fork();
    if (pid == 0) {

        calltrace(atoi(args[1]));
        exec(exe_args[0], exe_args);

        printf("trace: exec %s failed\n", exe_args[0]);
        exit(1);
    } else if (pid < 0) {
        printf("trace: fork failed\n");
        exit(1);
    } else {
        wait(0);
    }
}

int main(int argc, char **args) {
    if (argc < 3) {
        printf("trace: usage: trace mask command [args...]\n");
        exit(1);
    }
    trace(argc, args);
    exit(0);
}
