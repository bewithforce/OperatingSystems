#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/shm.h>

using namespace std;

int shmid = shmget(IPC_PRIVATE, 1, 0777);
int *array = (int *) shmat(shmid, nullptr, 0);

void *run(void *args) {
    (*array)++;
    string out = to_string(*array) + "\n";
    write(3, out.c_str(), out.length());
    return nullptr;
}

int main() {
    pthread_t thread_id1, thread_id2, thread_id3;
    open("out.txt", O_RDWR);

    *array = 0;

    pthread_create(&thread_id1, (pthread_attr_t *) nullptr, run, nullptr);
    pthread_create(&thread_id2, (pthread_attr_t *) nullptr, run, nullptr);
    pthread_create(&thread_id3, (pthread_attr_t *) nullptr, run, nullptr);

    pthread_join(thread_id1, (void **) nullptr);
    pthread_join(thread_id2, (void **) nullptr);
    pthread_join(thread_id3, (void **) nullptr);

    return 0;
}
