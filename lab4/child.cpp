#include <unistd.h>

int main(){
	alarm(3);
	while(true){
		pause();
	}
}
