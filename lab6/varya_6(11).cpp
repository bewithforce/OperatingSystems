#include <dirent.h>
#include <iostream>
#include <cstring>

using namespace std;

int main() {
    DIR *d;
    struct dirent *dir;

    string pathname = ".";
    d = opendir(pathname.c_str());
    while (d) {
        while ((dir = readdir(d)) != nullptr) {
            if (dir->d_type != DT_DIR && dir->d_type != DT_LNK) {
                cout << dir->d_name << endl;
            }
        }
        rewinddir(d);

        pathname.insert(0, "../");
        char bufTmp[PATH_MAX];
        char buf[PATH_MAX];
        DIR *tmp = opendir(pathname.c_str());

        readdir(tmp);
        readdir(tmp);
        readdir(d);
        readdir(d);

        realpath(readdir(tmp)->d_name, bufTmp);
        realpath(readdir(d)->d_name, buf);

        if(strcmp(bufTmp, buf) == 0){
            closedir(d);
            closedir(tmp);
            break;
        }
        rewinddir(tmp);
        closedir(d);
        d = tmp;
    }
    return 0;
}