#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(){
    printf("We have: %d bytes available.\n",memoleft());
    exit(0);
}