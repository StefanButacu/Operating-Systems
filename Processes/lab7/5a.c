#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
int main(int argc, char** argv){
	if( 0 > mkfifo("a2b", 0600)){
	perror("Error at creating fifo");
	exit(1);
	}
	int a2b = open("a2b", O_WRONLY);
	char input[150];
	while(1)
	{
		scanf("%s", input);
		if(strcmp(input, "stop")) break;
		int k = 0;
		int len = strlen(input);
		if( 0 > write(a2b, &len, sizeof(int))){
		perror("Error at sending the lenght");
		exit(1);	
		}
		while(k < len){
		int buf = write(a2b, input, (len - k) * sizeof(char));
			if( 0 > buf) {
			perror("Error at sending the input string");
			exit(1);
			}
		k += buf;	
		}
	}
	close(a2b);
	unlink("a2b");
	return 0;

}
