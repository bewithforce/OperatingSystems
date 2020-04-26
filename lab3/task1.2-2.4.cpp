#include <pthread.h>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <semaphore.h>
#include <fcntl.h>

using namespace std;

struct thread_arguments {
    int inc;
    sem_t *mutex;
    thread_arguments(int inc, sem_t &mutex) : mutex(&mutex), inc(inc) {}
};

int a = 0;

void *run(void *args) {
    int inc = ((thread_arguments *) args)->inc;
    sem_t *mutex = ((thread_arguments *) args)->mutex;
    //  pthread_t mythid =  pthread_self();
    for (int i = 0; i < 100000; i++) {
        sem_wait(mutex);
        a += inc;
        sem_post(mutex);
    }
   // write(3, "hi\n", 3);
    //   printf("thread: %lu, a = %d\n", mythid, a);
    return nullptr;
}

int main() {
    pthread_t thread_id1, thread_id2;
    auto *mutex = new sem_t;
    sem_init(mutex, 0, 1);
  //  int fd = open("out.txt", O_RDWR);

    auto *param1 = new thread_arguments(1, *mutex);

    auto *param2 = new thread_arguments(1, *mutex);

    pthread_create(&thread_id1, (pthread_attr_t *) nullptr, run, param1);
    pthread_create(&thread_id2, (pthread_attr_t *) nullptr, run, param2);

    //system(("ps -T --ppid " + to_string(getppid())).c_str());

    pthread_join(thread_id1, (void **) nullptr);
    pthread_join(thread_id2, (void **) nullptr);
    sem_destroy(mutex);
    printf("result %d\n", a);
    //close(3);
    return 0;

}