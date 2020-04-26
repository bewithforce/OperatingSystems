#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fstream>
#include <signal.h>
#include <unistd.h>

using namespace std;

void task_1_1() {
    for (int i = 0; i < rand() % 25 + 1; i++)
        printf("%x\n", ftok("/home/Varvara/Projects/C++/OperatingSystems/main.cpp", rand() % 121234));
    key_t k = ftok("/home/dzianis/Projects/C++/OperatingSystems/main.cpp", 1);
    int i = 2;
    while (k != ftok("/home/dzianis/Projects/C++/OperatingSystems/main.cpp", i++)) {}
    printf("%d", i - 1);
}

void task_1_2() {
    cout << ftok("/home/Varvara/Projects/C++/OperatingSystems/main.cpp", 63) << endl;
    cout << ftok("../main.cpp", 63) << endl;
    system("touch main.cpp");
    cout << ftok("main.cpp", 63) << endl;
    system("touch main.cpp1");
    cout << ftok("main.cpp1", 63) << endl;
    system("rm -rf main.cpp");
    system("rm -rf main.cpp1");
}


void task_2_1() {

}


void task_2_2() {

}


void task_2_3() {

}

void task_2_4() {
    int key = ftok("../main.cpp", 456);
    if (errno)
        cout << "errno 1: " << errno << endl;

    long long k = INT32_MAX - 2;
    while (!errno) {
        shmget(key, k++, IPC_CREAT | 0777);
        if (errno)
            cout << "max = " << k - 1 << endl;
    }
}

int spec_k = 128 * 4;

void ouch(int sig) {
    cout << spec_k << endl;
    exit(spec_k);
}

void task_2_5() {
    char *array;
    int key = ftok("../source", 123);
    int shmid = shmget(key, 128, IPC_CREAT | 0777);
    array = (char *) shmat(shmid, NULL, 0);
    struct sigaction act;
    act.sa_handler = ouch;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGSEGV, &act, 0);
    while (true) {
        char i = *(array + spec_k++);
    }
}

void task_2_6() {
    int *array;
    int key = ftok("../source", 123);
    int shmid = shmget(key, 128, IPC_CREAT | 0777);


    if (!fork()) {
        array = (int *) shmat(shmid, NULL, 0);
        for (int i = 0; i < 128; i++) {
            cout << array[i] << " ";
        }
        exit(-1);
    } else {
        array = (int *) shmat(shmid, NULL, 0);
        for (int i = 0; i < 128; i++) {
            array[i] = i + 1;
        }
        sleep(1);
    }
}

void task_2_7() {
    int k = 124500;
    int *array;
    int key = ftok("../source", 127);
    int shmid = shmget(key, 1, IPC_CREAT | 0777);

    if (fork()) {
        array = (int *) shmat(shmid, NULL, 0);
        array[0] = 0;
        for (int i = 0; i < k; i++) {
            array[0]++;
        }
        cout << array[0] << endl;

    } else {
        array = (int *) shmat(shmid, NULL, 0);
        for (int i = 0; i < k; i++) {
            array[0]--;
        }
        cout << array[0] << endl;
        exit(0);
    }
}

void task_2_8() {
    int k = 100000;
    int *array;
    bool *flag1, *flag2;

    int key = ftok("../source", 64);

    int shmid = shmget(key, 4, IPC_CREAT | 0777);

    array = (int *) shmat(shmid, NULL, 0);

    array[0] = 0;
    flag1 = (bool *) (&array + 8);
    flag2 = (bool *) (&array + 12);
    *flag1 = false;
    *flag2 = false;
    array[1] = 0;

    if (fork()) {
        *flag1 = true;
        for (int i = 0; i < k; i++) {
            *flag1 = true;
            while (*flag2) {
                if (array[1] == 1) {
                    *flag1 = false;
                    while (array[1] == 1) {}
                    *flag1 = true;
                }
            }
            array[0]++;
            array[1] = 1;
            *flag1 = false;
        }
        cout << array[0] << endl;
    } else {
        for (int i = 0; i < k; i++) {
            *flag2 = true;
            while (*flag1) {
                if (array[1] == 0) {
                    *flag2 = false;
                    while (array[1] == 0) {}
                    *flag2 = true;
                }
            }
            array[0]--;
            array[1] = 0;
            *flag2 = false;
        }
        cout << array[0] << endl;
        exit(0);
    }
}

int main() {
    cout << "task 1.1:" << endl;
    task_1_1();

    cout << "\n\ntask 1.2:" << endl;
    task_1_2();

    cout << "\n\ntask 2.1:" << endl;
    task_2_1();

    cout << "\n\ntask 2.2:" << endl;
    task_2_2();

    cout << "\n\ntask 2.3:" << endl;
    task_2_3();

    cout << "\n\ntask 2.4:" << endl;
    task_2_4();

    cout << "\n\ntask 2.5:" << endl;
    task_2_5();

    cout << "\n\ntask 2.6:" << endl;
    task_2_6();

    cout << "\n\ntask 2.7:" << endl;
    task_2_7();

    sleep(1);
    cout << "\n\ntask 2.8:" << endl;
    task_2_8();

}
