#include <csignal>
#include <unistd.h>
#include <iostream>

using namespace std;

int pid1, pid2;

void handler1(int signal) {
    if (signal == SIGUSR1) {
        cout << "a" << endl;
        kill(pid2, SIGUSR2);
    }
}

void handler2(int signal) {
    if (signal == SIGUSR2) {
        cout << "b" << endl;
        kill(pid1, SIGUSR1);
    }
}

int main() {
    signal(SIGUSR1, handler1);
    signal(SIGUSR2, handler2);

    if (fork()) {
        pid1 = getpid();
        while (1) {
            sleep(2);
        }
    } else {
        pid2 = getpid();
        kill(pid1, SIGUSR1);
        while (1) {
            sleep(2);
        }
    }
}