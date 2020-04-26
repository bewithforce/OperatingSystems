#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>

using namespace std;

int main() {
    int k = 1000000;

    int shmid = shmget(IPC_PRIVATE, 1, 0777);

    int semid = semget(IPC_PRIVATE, 1, 0777);

    int *array = (int *) shmat(shmid, nullptr, 0);
    array[0] = 0;

    sembuf incOp{0, 1, 0};
    sembuf decOp{0, -1, 0};

    semop(semid, &incOp, 1);

    if (fork()) {
        for (int i = 0; i < k; i++) {
            semop(semid, &decOp, 1);
            array[0]++;
            semop(semid, &incOp, 1);
        }
        cout << *array << endl;
    } else {
        for (int i = 0; i < k; i++) {
            semop(semid, &decOp, 1);
            array[0]--;
            semop(semid, &incOp, 1);
        }
        cout << array[0] << endl;
        return 0;
    }
    return 0;
}
