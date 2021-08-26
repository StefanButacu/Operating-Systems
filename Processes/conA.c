#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
int main(){
/* Screoto 2 programe C, A si B. A va crea 2 procese P1 si P2, P2 va citi de la tastatura 2 siruri de carctere
 * si le va trimite prin pipe lui P1. P1 va trimite prin fifo lui B cele doua siruri concatenate. Dupa care
 * B le va afisa pe ecran 
 * 
 */

	int pid1,pid2;
	int myPipe[2];
	pipe(myPipe);
	pid1 = fork();
/*	if( 0 > mkfifo("a2b", 0600)){
	perror("Error at creating fifo");
	exit(1);
	}
*/	
	int a2b = open("a2b", O_WRONLY);
	if( 0 > a2b) {
	perror("Error open fifo");
	exit(1);
	}
	if( 0 > pid1){
	perror("Error at 1st fork");
	exit(1);
	}
	if( pid1 == 0){
	// child1
	close(myPipe[1]);
	int l1;
	if(0 > read(myPipe[0], &l1, sizeof(int))){
	perror("Error at reading the first lenght");
	exit(1);
	}
	char* sir1 = malloc((l1+1) * sizeof(char));
	if(0 > read(myPipe[0], sir1, l1 * sizeof(char))){
	perror("Error at reading the 1st string");
	exit(1);
	}
	sir1[l1] = 0;
	//printf("%s", sir1);
	int l2 ;
	if( 0 > read(myPipe[0], &l2, sizeof(int))){
	perror("Error at reading the second lenght");
	exit(1);
	}
	char* sir2 = malloc((l2 +1 ) * sizeof(char));
	if( 0 > read(myPipe[0], sir2, sizeof(int))){
	perror("Error at reading the second string");
	exit(1);
	}
	sir2[l2] = 0;
	//printf("\n%s", sir2);
	int l3 = l1 + l2;
	char* sir3 = malloc((l3+1) * sizeof(char));
	strcpy(sir3, sir1);
	strcat(sir3,sir2);
	printf("%d-%s\n", l3,sir3);
	if( 0 > write(a2b, &l3, sizeof(int))){
	perror("Error at sending 3rd lenght");
	exit(1);
	}
	if( 0 > write(a2b, sir3, l3 * sizeof(char))){
	perror("Error at sending 3rd string");
	exit(1);
	}
// concatenare si trimite prin fifo lui B;
	free(sir1);
	free(sir2);
	free(sir3);
	//unlink("a2b");
	close(myPipe[0]);
	exit(0);
	}
	// parent	
	pid2 = fork();
	if(0 > pid2){
	perror("Error at 2nd fork");
	exit(1);
	}
	if(0 == pid2){
	// chil2 
		
	close(myPipe[0]);
 	char sir1[100];
	printf("Dati primul sir=");
	if( 0 > scanf("%s", sir1)){
	perror("Error at reading sir1");
	exit(1);
	}
	
	int l1 = strlen(sir1);
	if( 0 > write(myPipe[1], &l1, sizeof(int))){
	perror("Error at sending the 1st lenght");
	exit(1);
	}
	if( 0 > write(myPipe[1], sir1, l1 * sizeof(char))){
	perror("Error at sending 1st string");
	exit(1);	
	}	
	char sir2[100];
	printf("Dati al doilea sir=");
	scanf("%s", sir2);
	int l2 = strlen(sir2);
	if( 0 > write(myPipe[1], &l2, sizeof(int))){
	perror("Error at sending the 2nd lenght");
	exit(1);
	}
	if(0 > write(myPipe[1], sir2, l2* sizeof(char))){
	perror("Error at sending the 2nd string");
	exit(1);
	}

	close(myPipe[1]);
	exit(0);
	}
	//parent
	wait(0);
	wait(0);
	return 0;
	
}
