#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
#include <cstdio>
#include <unistd.h>
#include <string>
#include <set>

using namespace std;

#define LAST_MESSAGES 255

struct mymsgbuf {
    long mtype;
    char mtext[1024];
};


void sendToAll(const set<int> &clients, int msgid, char msg[1024], int from) {
    for (auto client : clients) {
        mymsgbuf buf{};
        char prot[7];
        sprintf(prot, "%.7d\0", from);
        string newstring = "asd__" + string(prot) + string(msg) + "__asd\n";
        //  write(1, newstring.c_str(), newstring.length());
        strcpy(buf.mtext, (string(prot) + string(msg)).c_str());
        buf.mtype = client + 1000000;
        msgsnd(msgid, &buf, strlen(buf.mtext) + 1, 0);
    }
}

//из сервера в клиент -- pid + 1000000
//из клиента в сервер -- pid

int main() {
    int msgid;
    msgid = msgget(16, 0666 | IPC_CREAT);

    int forkResult = fork();
    if (forkResult > 0) {
        set<int> clients;
        mymsgbuf to_send{};
        mymsgbuf to_recieve{};

        while (true) {
            msgrcv(msgid, &to_recieve, 1024, -1000000, 0);
            if (clients.find(to_recieve.mtype) == clients.end()) {
                to_send.mtype = to_recieve.mtype + 1000000;
                char *str = new char[1024];
                sprintf(str, "hi Client%ld", to_send.mtype);
                strcpy(to_send.mtext, str);
                msgsnd(msgid, &to_send, strlen(to_send.mtext) + 1, 0);
                string tmp = "new client " + to_string(to_recieve.mtype) + "\n";
                printf("server: %s\n", tmp.c_str());
                clients.insert(to_recieve.mtype);
            } else {
                sendToAll(clients, msgid, to_recieve.mtext, to_recieve.mtype);
            }
        }
    } else {
        for (int i = 0; i < 3; i++) {
            if (fork() == 0) {

                int pid = getpid();

                mymsgbuf to_send{pid};
                mymsgbuf to_recieve{};
                msgsnd(msgid, &to_send, 0, 0);
                msgrcv(msgid, &to_recieve, 1024, pid + 1000000, 0);

                printf("client: %s\n", to_recieve.mtext);

                to_send.mtype = pid;
                string hello = "privet vsem v etom chatike";
                strcpy(to_send.mtext, hello.c_str());

                msgsnd(msgid, &to_send, strlen(to_send.mtext) + 1, 0);

                while (true) {
                    msgrcv(msgid, &to_recieve, 1024, pid + 1000000, 0);

                    string msg(to_recieve.mtext);
                    try {
                        int tmp = stoi(msg.substr(0, 7));
                        if (pid == tmp)
                            continue;
                    } catch (...) {
                        write(1, ("test_" + msg.substr(0, 7) + "_test\n").c_str(), ("test_" + msg.substr(0, 7) + "_test\n").length());
                        break;
                    }
                    string out = "client: " + msg.substr(7) + "\n";
                    write(1, out.c_str(), out.length());
                    if (msg.substr(7) == hello) {
                        to_send.mtype = pid;
                        strcpy(to_send.mtext, ("Hello " + to_string(pid)).c_str());
                        msgsnd(msgid, &to_send, strlen(to_send.mtext) + 1, 0);
                    }
                }
            }
        }
    }
}