#include <iostream>
#include <vector>
#include <ctime>

#include <thread>
#include <mutex>

#include <sys/shm.h>
#include <sys/types.h>

using namespace std;

const int t = 20;
const int m = 10;

vector<thread> threads;
vector<mutex *> mutexes;
vector<int *> shared_memory;

void run() {
    int k = rand() % 10 + 1;
    for (int i = 0; i < k; i++) {
        mutexes[i]->lock();
        (*(shared_memory[i]))++;
    }
    for (int i = 0; i < k; i++) {
        mutexes[i]->unlock();
    }
}

int main() {
    srand(time(nullptr));

    for (int i = 0; i < m; i++) {
        key_t shmid = shmget(IPC_PRIVATE, 1, 0777);
        shared_memory.emplace_back((int *) shmat(shmid, nullptr, 0));
        mutexes.emplace_back(new mutex);
    }

    for (int i = 0; i < t; i++) {
        threads.emplace_back(thread(run));
    }

    for (auto &th : threads) {
        th.join();
    }

    for (auto &mx : mutexes) {
        delete mx;
    }

    for (auto number : shared_memory) {
        cout << *number << endl;
    }
    return 0;
}
