#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
	int p2c[2], c2p[2];
	if( 0 > pipe(p2c)) {
			
	perror("Error on pipe 1");		
	}

	pipe(c2p);
	int f= fork();

	if(0 > f){
		perror("Eroor on fork");
		exit(1);

	}
	else if (f == 0){
		// child
		int n;
		close(p2c[1]);
		close(c2p[0]);
		while(1) {
		if( 0 > read(p2c[0], &n, sizeof(int))){
			perror("Error on child read");		
		}

		printf("Copilul a primit: %d\n", n);  
		n = n /2 ;
		
		if( 0 > write(c2p[1], &n, sizeof(int)))
			perror("Error on child read");
		
		printf("Copilul a trimis %d\n", n);  
		
		if(n < 5) 
			break;
		}
		close(p2c[0]);
		close(c2p[1]);
	exit(1);
		}

	else{
	// parent 
	close(p2c[0]);
	close(c2p[1]);
	srandom(time(NULL));
	int Y = 50, X = 151;
	int n = random() % X + Y ; // Y si X + Y - 1 
	printf("Parintele a generat: %d\n", n);
	while(n >= 5) {
		if(n % 2 == 1) 
			n++;
		if( 0 > write(p2c[1], &n, sizeof(int))){
			perror("Error on paren write");
		};

		if( 0 > read(c2p[0], &n , sizeof(int))){
			perror("Error on parent read");
		}
		printf("Parintele a primit: %d\n", n);
		
	}
	close(p2c[1]);
	close(c2p[0]);
	wait(0);
	}
	
	return 0;
}
