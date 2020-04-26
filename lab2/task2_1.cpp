#include <sys/ipc.h>
#include <sys/sem.h>
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int main() {
    vector<int> semids;
    while (!errno)
        semids.push_back(semget(IPC_PRIVATE, 1, 0));
    semids.pop_back();
    cout << "errno code: " << errno << endl;
    cout << strerror(errno) << endl;
    cout << "ids count: " << semids.size() << endl;
    for (int i : semids)
        system(("ipcrm -s " + to_string(i)).c_str());
    return 0;
}