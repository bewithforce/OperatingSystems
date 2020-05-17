#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
#include <cstdio>
#include <unistd.h>
#include <string>

#define MAXLEN 81

using namespace std;

int main() {

    struct mymsgbuf {
        long mtype;
        char mtext[100];
    } mybuf{};

    int msgid = msgget(16, 0666 | IPC_CREAT);

    mybuf.mtype = 1;
    strcpy(mybuf.mtext, to_string(getpid()).c_str());
    auto len = strlen(mybuf.mtext) + 1;
    msgsnd(msgid, &mybuf, len, 0);

    msgrcv(msgid, &mybuf, MAXLEN, 255, 0);
    printf("%s\n", mybuf.mtext);

    msgctl(msgid, IPC_RMID, nullptr);
    return 0;
}

