#include <unistd.h>

int main(){
    if(fork()){
        while(true){
            pause();
        }
    } else {
        while(true);
    }

}