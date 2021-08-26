#include <unistd.h>
#include <stdlib.h> 
#include <stdio.h> 
#include <sys/wait.h>

int main(){
	int p2c[2], c2p[2];
	// p2c - parintele scrie copilului, copilul citeste
	// c2p - copilul scire parintelui, parintele citeste 
	if( 0 > pipe(p2c)){
		perror("Error on pipe p2c: ");
	}
	if( 0 > pipe(c2p)){
		perror("Error on pipe c2p: ");
	}
	int pid = fork();
	int N;
	printf("Dati N");
	srandom(getpid());
	if(pid == -1){
		perror("Error on fork: "); // 
		exit(1);
	}
	else if ( pid == 0){
		//child
		// read n 
		// for i = 0 ; i < n ; i++
	 	close(c2p[0]);
		close(p2c[1]);
		int i,sum=0 ;
		if(read(p2c[0], &n, sizeof(int)) > 0){
			
			for(i = 0; i < n; i++){
			int nr;
			if(read(p2c[0], &nr, sizeof(int)) > 0) sum +=nr;
			}
		}




	}else{
		scanf("%d", &N);
	
	
	}
	// 
	close(p2c[1]); // parintelenu mai scrie copilului
	

}
