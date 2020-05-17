#include <dirent.h>
#include <iostream>
#include <set>

using namespace std;

int main() {
    DIR *d;
    struct dirent *dir;
    set<string> files;

    string pathname = ".";
    d = opendir(pathname.c_str());
    while (d) {
        while ((dir = readdir(d)) != nullptr) {
            if (dir->d_type != DT_LNK && dir->d_type != DT_DIR) {
                cout << dir->d_name << endl;
            }
        }
        closedir(d);
        pathname.insert(0, "../");
        d = opendir(pathname.c_str());
    }
    for (auto &item : files) {
        cout << item << endl;
    }
    return 0;
}