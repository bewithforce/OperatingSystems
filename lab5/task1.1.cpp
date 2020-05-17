#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
#include <cstdio>

#define LAST_MESSAGES 255

int main() {
    int msgid;

    struct mymsgbuf {
        long mtype;
        char mtext[81];
    } mybuf{};

    msgid = msgget(16, 0666 | IPC_CREAT);

    for (int i = 1; i < 5; i++) {
        mybuf.mtype = 1;
        strcpy(mybuf.mtext, "this text");
        int len = strlen(mybuf.mtext) + 1;
        if (msgsnd(msgid, &mybuf, len, 0) < 0) {
            printf("bad send");
            msgctl(msgid, IPC_RMID, nullptr);
            return 0;
        }
    }

    mybuf.mtype = LAST_MESSAGES;
    int len = 0;
    if (msgsnd(msgid, &mybuf, len, 0) < 0) {
        printf("bad send");
        msgctl(msgid, IPC_RMID, nullptr);
        return 0;
    }


}

