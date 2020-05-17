#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstdio>

#define LAST_MESSAGES 255

int main() {
    int msgid;

    struct mymsgbuf {
        long mtype;
        char mtext[81];
    } mybuf{};

    msgid = msgget(16, 0666 | IPC_CREAT);

    while (true) {
        int maxlen = 81;
        msgrcv(msgid, &mybuf, maxlen, 0, 0);

        if (mybuf.mtype == LAST_MESSAGES) {
            msgctl(msgid, IPC_RMID, nullptr);
            return 0;
        }
        printf("%s\n", mybuf.mtext);
    }
}

