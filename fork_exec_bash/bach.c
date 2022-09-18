#include "stdio.h"
#include "sys/types.h"
#include "unistd.h"

int main(){
    if(fork() == 0){
        printf("Hello from Child!\n");

        char *args[2] = {"/bin/ksh", NULL};
        execve(args[0], args, NULL);
        printf("\n");
        return 0;
    }

    else
        printf("Hello from Parent!\n");
    
    return 0;
}