#include <dirent.h>
#include <iostream>
#include <set>

using namespace std;

int main() {
    DIR *d;
    struct dirent *dir;
    set<string> files;
    d = opendir("../");
    if (d) {
        while ((dir = readdir(d)) != nullptr) {
            if(dir->d_type != DT_LNK && dir->d_type != DT_DIR){
                files.insert(dir->d_name);
            }
        }
        closedir(d);
    }
    for(auto& item : files){
        cout << item << endl;
    }
    return 0;
}