#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <wait.h>

using namespace std;

int main() {
    int k = 1000000;
    int shmid = shmget(IPC_PRIVATE, 1, 0777);
    int semid = semget(IPC_PRIVATE, 1, 0777);

    int *array = (int *) shmat(shmid, nullptr, 0);
    array[0] = 0;
    semctl(semid, 0, SETVAL, 1);

    int id1 = fork();
    if (id1) {
        int id2 = fork();
        if(!id2){
            execl("p1", to_string(shmid).c_str(), to_string(semid).c_str(), to_string(k).c_str(), NULL);
        }
        waitpid(id1, nullptr, 0);
        waitpid(id2, nullptr, 0);
        cout << array[0] << endl;
    } else {
        execl("p2", to_string(shmid).c_str(), to_string(semid).c_str(), to_string(k).c_str(), NULL);

    }
   shmdt(array);
    array[0]++; 
    return 0;
}
