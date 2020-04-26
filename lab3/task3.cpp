#include <iostream>
#include <chrono>
#include <unistd.h>
#include <wait.h>

using namespace std;
using namespace chrono;

void *run(void *args) {
    return nullptr;
}

int main() {
    steady_clock::time_point begin = steady_clock::now();
    for (int i = 0; i < 10000; i++) {
        int id = fork();
        if (!id) {
            return 0;
        }
        waitpid(id, nullptr, 0);
    }
    steady_clock::time_point end = steady_clock::now();
    cout << "forks worktime: " << duration_cast<milliseconds>(end - begin).count() << " ms" << endl;

    begin = steady_clock::now();
    for (int i = 0; i < 10000; i++) {
        pthread_t thread_id;
        pthread_create(&thread_id, (pthread_attr_t *) nullptr, run, nullptr);
        pthread_join(thread_id, (void **) nullptr);
    }
    end = steady_clock::now();
    cout << "threads worktime: " << duration_cast<milliseconds>(end - begin).count() << " ms" << endl;
}
