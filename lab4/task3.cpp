#include <unistd.h>
#include <iostream>
#include <sys/wait.h>

using namespace std;

int res;

void handler(int signal) {
    if (signal == SIGALRM) {
        cout << "hello" << endl;
    }
    if(res){
        waitpid(0, NULL, 0);
    }
    exit(0);
}

int main() {
    signal(SIGALRM, handler);
    res = fork();
    if(!res){
        execl("../child", "", nullptr);
    }
    alarm(3);
    while (true) {
        sleep(1);
    }
}

