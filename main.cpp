#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fstream>

using namespace std;

void task_1_1() {
    for (int i = 0; i < rand() % 25 + 1; i++)
        cout << ftok("/home/dzianis/Projects/C++/OperatingSystems/main.cpp", rand() % 121234) << endl;
}

void task_1_2() {
    cout << ftok("/home/dzianis/Projects/C++/OperatingSystems/main.cpp", 63) << endl;
    system("touch main.cpp");
    cout << ftok("main.cpp", 63) << endl;
    system("touch main.cpp1");
    cout << ftok("main.cpp1", 63) << endl;
    system("rm -rf main.cpp");
    system("rm -rf main.cpp1");
}

/*
void task_2_1() {

}


void task_2_2() {

}
*/

void task_2_3() {

}

void task_2_4() {
    int key = ftok("../main.cpp", 63);
    if(errno)
        cout << "errno 1: " << errno << endl;

    int t = shmget(key, INT64_MAX, IPC_CREAT);
    if(errno)
        cout << "errno 2: " << errno << endl;

    struct shmid_ds shmid_ds, *buf;
    buf = & shmid_ds;
    int r = shmctl(t, IPC_STAT, buf);
    if(errno)
        cout << "errno 3: " << errno << endl;

    cout << r << endl;
}

void task_2_5() {

}

void task_2_6() {

}

void task_2_7() {

}

void task_2_8() {

}

int main() {
//    cout << "task 1.1:" << endl; task_1_1();

//    cout << "\n\ntask 1.2:" << endl; task_1_2();

//    cout << "\n\ntask 2.1:" << endl; task_2_1();

//   cout << "\n\ntask 2.2:" << endl; task_2_2();

    //   cout << "\n\ntask 2.3:" << endl; task_2_3();

    cout << "\n\ntask 2.4:" << endl;
    task_2_4();

    //   cout << "\n\ntask 2.5:" << endl; task_2_5();

    //   cout << "\n\ntask 2.6:" << endl; task_2_6();

    //   cout << "\n\ntask 2.7:" << endl; task_2_7();

    //   cout << "\n\ntask 2.8:" << endl; task_2_8();
}