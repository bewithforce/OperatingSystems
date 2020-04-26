#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>

int reader(int semids[3], struct sembuf *decr, struct sembuf *incr, sembuf *zero, int *array) {
    if (fork() == 0) {
        while (semop(semids[1], zero, 1) < 0);
        semop(semids[0], incr, 1);
        printf("%d\n", array[0]);
        semop(semids[0], decr, 1);
        exit(0);
    }
}

int writer(int semids[3], struct sembuf *decr, struct sembuf *incr, sembuf *zero, int *array) {
    if (fork() == 0) {
        while (semop(semids[1], zero, 1) < 0);
        semop(semids[1], incr, 1);
        while (semop(semids[0], zero, 1) < 0);
        array[0]++;
        semop(semids[1], decr, 1);
        exit(0);
    }
}

int main() {
    int *array;
    int shmid = shmget(IPC_PRIVATE, sizeof(int), 0666 | IPC_CREAT);
    array = (int *) shmat(shmid, NULL, 0);

    int semids[3];
    semids[0] = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);
    semids[1] = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);
    sembuf incr{0, 1, IPC_NOWAIT};
    sembuf decr{0, -1, IPC_NOWAIT};
    sembuf zero{0, 0, IPC_NOWAIT};
    for (int i = 0; i < 5; i++)
        writer(semids, &decr, &incr, &zero, array);
    for (int i = 0; i < 5; i++)
        reader(semids, &decr, &incr, &zero, array);
    return 0;
}