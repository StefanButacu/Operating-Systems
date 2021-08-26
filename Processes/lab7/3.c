#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>
int main(int argc, char ** argv){
	if(0 > mkfifo("a2b", 0600))
	{
		perror("Error at creating a2b fifo");
		exit(1);
	}
	if(0 > mkfifo("b2a", 0600)){
		perror("Error at creating b2a fifo");
		exit(1);
	}
	srandom(time(NULL));
	int a2b, b2a;
	int pid1 = fork();
	if(0 > pid1){
		perror("Error at 1st fork");
		exit(1);
	}
	else if(pid1 == 0) // A 
	{
		a2b = open("a2b", O_WRONLY);
		b2a = open("b2a", O_RDONLY);
		int n;
		while(1){
		// presupun ca procesul b scrie prima oara 
		if(0 > read(b2a, &n, sizeof(int))){
			perror("Error at receiving nr from B");
			exit(1);
		}
		if( n == 10){
			printf("A received 10, bye bye\n");
			break;
		}
		printf("A received %d\n", n);
		srandom(getpid());
		n = random() % 10 + 1;
		printf("A sends %d\n", n);
		if(0 > write(a2b, &n, sizeof(int))){
			perror("Error at sending nr to B");
			exit(1);
		}
		if ( n == 10) break;		
		}
		close(a2b);
		close(b2a);
		exit(0);
	}
	int pid2 = fork();
	if(0 > pid2) {
		perror("Error at 2nd fork");
		exit(1);
	}	
	else if(pid2 == 0) // b 
	{
		a2b= open("a2b", O_RDONLY);
		b2a= open("b2a", O_WRONLY);
		int n;
		srandom(getpid());
		n = random()%10+1;
		printf("B sends %d\n", n);
		if(0 > write(b2a, &n, sizeof(int))){
			perror("Error at sending the first number to A");
			exit(1);
		} 
		while(1 && n != 10){
			if(0 > read(a2b, &n, sizeof(int))){
			perror("Error at receiving from A");
			exit(1);
			}
			if(n == 10){
			printf("B received 10, bye bye\n");
			break;
			}
			printf("B received %d\n", n);
			n = random() % 10 + 1;
			printf("B sends %d\n", n);
			if(0 > write(b2a, &n, sizeof(int))){
			perror("Errot at sending to A");
			exit(1);
			}
			if(n == 10) break;	
		
		}
		close(a2b);
		close(b2a);
		exit(0);

	}
	wait(0);wait(0);
	unlink("a2b");
	unlink("b2a");
	return 0;


}
