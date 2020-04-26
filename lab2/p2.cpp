#include <iostream>
#include <sys/shm.h>
#include <sys/sem.h>

using namespace std;

int main(int argc, char *argv[]) {
    int shmid = atoi(argv[0]);
    int semid = atoi(argv[1]);
    int k = atoi(argv[2]);
    int *array = (int *) shmat(shmid, nullptr, 0);
    sembuf incOp{0, 1, 0};
    sembuf decOp{0, -1, 0};

    for (int i = 0; i < k; i++) {
        semop(semid, &decOp, 1);
        array[0]--;
        semop(semid, &incOp, 1);
    }
    shmdt(array);

    return 0;
}
