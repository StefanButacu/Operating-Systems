#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h> 
int main( int argc, char ** argv){


	int a2b = open("a2b", O_RDONLY);
	if( 0 > a2b) {
	perror("Error at open fifo");
	exit(1);
	}
	while(1){
	int len;
	if( 0 > read( a2b, &len, sizeof(int))){
	perror("Error at reading len");
	exit(1);
	}
	char *s = malloc((len+1) * sizeof(char));
	int k = 0; 
	while(k < len){
	int buf = read( a2b, s + k, (len - k) * sizeof(char));
	if(0 > buf){
		perror("Error at reading chars");
		exit(1);
	}
	k += buf;
	} 
	s[len] = 0;
	printf("B received %s\n", s);
	}
	return 0;
}
