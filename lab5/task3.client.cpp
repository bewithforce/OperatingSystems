#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
#include <cstdio>
#include <string>

#define MAXLEN 81

using namespace std;

int main() {
    struct msgbuf {
        long mtype;
        char mtext[100];
    } buf{};

    int msgid = msgget(16, 0666 | IPC_CREAT);

    buf.mtype = 1;
    strcpy(buf.mtext, "hi chat");
    msgsnd(msgid, &buf, strlen(buf.mtext) + 1, 0);
    printf("me: %s\n", buf.mtext);

    msgrcv(msgid, &buf, MAXLEN, 2, 0);
    int n = stoi(buf.mtext);
    buf.mtype = n;
    msgrcv(msgid, &buf, MAXLEN, buf.mtype + 1, 0);
    buf.mtype = n;
    printf("server: %s\n", buf.mtext);

    while (true) {
        int res = msgrcv(msgid, &buf, MAXLEN, buf.mtype + 1, 0);
        buf.mtype = n;
        if (res <= 0) {
            return 0;
        }
        printf("someone other: %s\n", &buf.mtext[10]);
        try {
            int n = stoi(buf.mtext);
            if (n) {
                strcpy(buf.mtext, ("hi, " + to_string(n)).c_str());
                msgsnd(msgid, &buf, strlen(buf.mtext) + 1, 0);
                printf("me: %s\n", buf.mtext);
            }
        } catch (...) {}
    }
}



