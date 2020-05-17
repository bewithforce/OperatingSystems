#include <iostream>
#include <cstring>

using namespace std;

int main() {
   /* char prot[10] = "0        ";
    char msg[90];
    char buf[100];
    string chat = "hi chat";
    strcpy(msg, chat.c_str());
    if (chat == "hi chat") {
        strcpy(prot, to_string(4).c_str());
        for (int j = strlen(prot); j < 9; j++) {
            prot[j] = ' ';
        }
    }
    cout << "asd_" << string(prot) << "_asd" << endl;
    strcpy(buf, (string(prot) + ' ' + string(msg)).c_str());
    cout << "asd_" << string(prot) + string(msg) << "_asd" << endl;
    cout << "asd_" << string(msg) << "_asd" << endl;
    cout << "asd_" << string(prot) << "_asd" << endl;
    cout << "asd_" << buf << "_asd" << endl;
    cout << "asd_" << &buf[10] << "_asd" << endl;*/
    char *temp = new char[123];
    sprintf(temp, "asdasd %d", 13);
    return 0;
}