#include <sys/ipc.h>
#include <sys/sem.h>
#include <iostream>
#include <cstring>

using namespace std;

int main() {
    int semid;
    int result;
    for (result = 30000; !errno; result++) {
        semid = semget(IPC_PRIVATE, result, 0);
        if (semid > 0)
            system(("ipcrm -s " + to_string(semid)).c_str());
    }
    cout << "errno code: " << errno << endl;
    cout << strerror(errno) << endl;
    cout << "nsems: " << result - 2 << endl;
    return 0;
}