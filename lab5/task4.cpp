#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
#include <cstdio>
#include <unistd.h>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <vector>

using namespace std;

#define LAST_MESSAGES 255

struct mymsgbuf {
    long mtype;
    char mtext[1024];
};

int main() {
    int msgid;
    msgid = msgget(16, 0666 | IPC_CREAT);

    int forkResult = fork();
    if (forkResult > 0) {
        vector<mymsgbuf> first;
        vector<mymsgbuf> second;
        mymsgbuf buf{};
        bool flg = 0;
        while (true) {
            if (msgrcv(msgid, &buf, 1024, 0, 0) == 0) {
                flg = flg != 1;
                if (!flg) break;
                continue;
            }
            if (buf.mtype == 1) first.push_back(buf);
            else second.push_back(buf);
        }
        for (int i = 0; i < first.size(); i++)
            printf("%s\n%s\n", first[i].mtext, second[i].mtext);
    } else {
        if (fork() == 0) {
            mymsgbuf buf{1};
            for (int i = 0; i < 20; i += 2) {
                usleep(rand() % 100000 + 50000);
                char *str = new char[1024];
                sprintf(str, "%d", i);
                strcpy(buf.mtext, str);
                msgsnd(msgid, &buf, strlen(buf.mtext) + 1, 0);
            }
            msgsnd(msgid, &buf, 0, 0);
        } else {
            mymsgbuf buf{2};
            for (int i = 1; i < 20; i += 2) {
                usleep(rand() % 100000 + 50000);
                char *str = new char[1024];
                sprintf(str, "%d", i);
                strcpy(buf.mtext, str);
                msgsnd(msgid, &buf, strlen(buf.mtext) + 1, 0);
            }
            msgsnd(msgid, &buf, 0, 0);
        }
    }
}