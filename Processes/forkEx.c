#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
int main(){
	if(fork() == 0){
		printf("Child only code\n");
		exit(0);
	}
	wait(0);
	printf("Parent only Code\n");
	return 0;
}
