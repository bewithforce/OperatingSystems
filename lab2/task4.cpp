#include <sys/ipc.h>
#include <sys/shm.h>
#include <cstdio>
#include <sys/sem.h>
#include <unistd.h>
#include <fstream>

using namespace std;

short dataLength = 1;
short numberOfReadersInQueue = 5;
int shmid = shmget(IPC_PRIVATE, dataLength * sizeof(short), 0777), semid = semget(IPC_PRIVATE, 3, 0777);
int *buffer = (int *) shmat(shmid, nullptr, 0);
bool *flag = (bool *) buffer + 10;

sembuf incF{0, 1, 0},
        incS{1, 1, 0},
        incT{2, 1, 0},
        decF{0, -1, 0},
        decS{1, -1, 0},
        decT{2, -1, 0},
        decTest{2, (short) -numberOfReadersInQueue, 0},
        incTest{2, numberOfReadersInQueue, 0},
        testF{0, 0, 0},
        testS{1, 0, 0};//IPC_NOWAIT

void reader() {
    while (*flag) {
        semop(semid, &incT, 1);
        semop(semid, &testS, 1);
        semop(semid, &decT, 1);
        semop(semid, &incF, 1);
        printf("%d\n", *buffer);
        semop(semid, &decF, 1);
     //   usleep(rand()%100);
    }
}

void writer() {
    while (*flag) {
        semop(semid, &testS, 1);

        semop(semid, &decTest, 1);
        semop(semid, &incTest, 1);

        semop(semid, &incS, 1);
        semop(semid, &testF, 1);
        (*buffer)++;
        semop(semid, &decS, 1);
    //    usleep(rand()%100);
    }
}

int main() {
    buffer[0] = 0;
    *flag = true;
    int counter = 0;

    if (fork()) {
        if (fork()) {
            while (*flag) {

                if (counter > 3) {
                    *flag = false;
                }
                counter++;
                sleep(1);
            }
        } else {
            fork();
            writer();
        }
    } else {
        if (fork()) {
            fork();
            fork();
        }
        reader();
    }
    sleep(2);
    return 0;
}