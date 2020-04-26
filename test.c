#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char const *argv[]) {
    int semid;
    int rtrn;
    char temp[255];
    struct sembuf mybuf;

    int i;
    int j;
    for(i = 1;i < 10000 ;i++) {
        for( j = 1; j < 128; j++) {
            if((semid = semget(IPC_PRIVATE, 1, 0666|IPC_CREAT)) < 0) {
                printf("Can\'t get semid\n");
                printf("num: %d\n", i*j);
                exit(-1);
            }
        }
    }
    return 0;
}