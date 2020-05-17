#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstdio>
#include <cstring>
#include <string>
#include <unistd.h>

#define MAXLEN 81

using namespace std;

int main() {
    int msgid;

    struct mymsgbuf {
        long mtype;
        char mtext[100];
    } mybuf{};

    msgid = msgget(16, 0666 | IPC_CREAT);

    msgrcv(msgid, &mybuf, MAXLEN, 1, 0);
    printf("%s\n", mybuf.mtext);

    mybuf.mtype = 255;
    strcpy(mybuf.mtext, to_string(getpid()).c_str());
    auto len = strlen(mybuf.mtext) + 1;
    msgsnd(msgid, &mybuf, len, 0);

    return 0;
}

