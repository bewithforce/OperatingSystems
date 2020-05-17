#include <string>
#include <vector>
#include <thread>
#include <mutex>

#include <sys/ipc.h>
#include <sys/msg.h>

#include <cstring>
#include <iostream>

#define MAXLEN 81

using namespace std;

vector<pair<thread, pair<int, int>>> threads;//thread, mtype for thread, message index in chat
vector<pair<string, int>> chat;

int msgid;

mutex writeLock;

void chatMonitor() {
    for (auto &th : threads) {
        for (int i = th.second.second; i < chat.size(); i++) {
            if (chat[i].second == th.second.first) {
                continue;
            }
            struct msgbuf {
                long mtype;
                char mtext[100];
            } buf{th.second.first + 1};
            char prot[10] = "0        ";
            char msg[90];
            strcpy(msg, chat[i].first.c_str());
            if (chat[i].first == "hi chat") {
                strcpy(prot, to_string(chat[i].second).c_str());
                for (int j = strlen(prot); j < 9; j++) {
                    prot[j] = ' ';
                }
            }
            strcpy(buf.mtext, (string(prot) + ' ' + string(msg)).c_str());
            // printf("from chat through server to %d: %s\n", th.second.first, buf.mtext);
            if (msgsnd(msgid, &buf, strlen(buf.mtext) + 1, 0) < 0) {
                return;
            }
        }
        th.second.second = chat.size();
    }
}

void run(int k) {
    struct msgbuf {
        long mtype;
        char mtext[100];
    } buf{k + 1};

    strcpy(buf.mtext, "greetings");
    msgsnd(msgid, &buf, strlen(buf.mtext) + 1, 0);

    while (true) {
        if (msgrcv(msgid, &buf, 100, k, 0) < 0) {
            return;
        }
        writeLock.lock();
        //  printf("from %d to server: %s\n", k, buf.mtext);
        chat.emplace_back(pair(buf.mtext, k));
        chatMonitor();

        writeLock.unlock();
    }
}


int main() {
    cout << "start server" << endl;
    struct msgbuf {
        long mtype;
        char mtext[100];
    } buf{};


    msgid = msgget(16, 0666 | IPC_CREAT);
    int k = 4;

    int l = 10;

    while (l++ < 123) {
        int res = msgrcv(msgid, &buf, MAXLEN, 1, 0);
        cout << "\"" << buf.mtext << "\" from " << k << endl;
        writeLock.lock();

        chat.emplace_back(buf.mtext, k);
        chatMonitor();

        writeLock.unlock();

        buf.mtype = 2;
        strcpy(buf.mtext, to_string(k).c_str());
        msgsnd(msgid, &buf, strlen(buf.mtext) + 1, 0);

        threads.emplace_back(pair(thread(run, k), pair(k, chat.size())));

        l++;
        k += 2;
    }
    for (auto &th : threads) {
        th.first.join();
    }
    msgctl(msgid, IPC_RMID, nullptr);
    cout << "stop server" << endl;
    return 0;
}

