#include <csignal>
#include <unistd.h>
#include <iostream>

using namespace std;

void handler(int signal) {
    if (signal == SIGALRM) {
        cout << "hello" << endl;
    }
    exit(0);
}

int main() {
    alarm(3);
    signal(SIGPIPE, SIG_IGN);
    signal(SIGALRM, handler);
    while (true) {
        sleep(1);
    }
}
