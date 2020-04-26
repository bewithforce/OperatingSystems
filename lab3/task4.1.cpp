#include <unistd.h>
#include <pthread.h>
#include <sys/sem.h>

int semid = semget(IPC_PRIVATE, 2, 0777);

sembuf incF{0, 1, 0};
sembuf decF{0, -1, 0};
sembuf waitF{0, 0, 0};

sembuf incS{1, 1, 0};
sembuf decS{1, -1, 0};
sembuf waitS{1, 0, 0};

void *runF(void *args) {
    for(int i = 1; i < 100; i++){
        semop(semid, &waitF, 1);
        semop(semid, &incF, 1);
        semop(semid, &waitS, 1);

        semop(semid, &decF, 1);
    }
    return nullptr;
}

void *runS(void *args) {
    for(int i = 1; i < 100; i++){
        semop(semid, &waitS, 1);
        semop(semid, &incS, 1);
        semop(semid, &waitF, 1);

        semop(semid, &decS, 1);
    }
    return nullptr;
}

int main(){
    pthread_t thread_id1, thread_id2;

    pthread_create(&thread_id1, (pthread_attr_t *) nullptr, runF, nullptr);
    pthread_create(&thread_id2, (pthread_attr_t *) nullptr, runS, nullptr);

    pthread_join(thread_id1, (void **) nullptr);
    pthread_join(thread_id2, (void **) nullptr);
    return 0;
}
