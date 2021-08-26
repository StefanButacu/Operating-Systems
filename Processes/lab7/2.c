#include <unistd.h>
#include <stdlib.h> 
#include <stdio.h> 
#include <sys/wait.h>

int main(int argc, char** argv){
	int p2c[2], c2p[2];
	// p2c - parintele scrie copilului, copilul citeste
	// c2p - copilul scire parintelui, parintele citeste 
	if( 0 > pipe(p2c)){
		perror("Error on pipe p2c: ");
	}
	if( 0 > pipe(c2p)){
		perror("Error on pipe c2p: ");
	}
	if(argc < 2 ) {
		perror("Not enough arguments");
		exit(1);
	}
	int N = atoi(argv[1]);
	srandom(getpid());
	int pid = fork();
	if(pid == -1){
		perror("Error on fork: "); // 
		exit(1);
	}
	else if ( pid == 0){
		//child
		// read n 
		// for i = 0 ; i < n ; i++
		// copilul ia de la printe N ul 
		// copilul trimite la parinte media 
		close(c2p[0]); 
		close(p2c[1]);	
		int n;
		if(0 > read(p2c[0], &n, sizeof(int))){
			perror("Error at receiving N");
			exit(1);
		}
		int i;
	        float sum;	
		for(i = 0; i < n; i++){
			int nr;
			if(read(p2c[0], &nr, sizeof(int)) > 0) sum +=nr;
			else
			{
			perror("Error at receving the random numbers");
			exit(1);
			}
		}
		float avg = sum / n;
		if( 0 > write(c2p[1], &avg, sizeof(float))) 
		{
			perror("Error at seding the average");
			exit(1);
		}
		close(p2c[0]);
		close(c2p[1]);
		exit(1);

	}else{
		close(c2p[1]);
		close(p2c[0]);
	        // ii scriu copilului cate numere are de citit
		if(0 > write(p2c[1], &N, sizeof(int))) {
			perror("Error at sending the N");
			exit(1);
		}
		int i;	
		for(i=0 ; i < N; i++)
		{
			int nrGen = random() % 100 + 1;
			printf("Random = %d\n", nrGen);
			if(0 > write(p2c[1], &nrGen, sizeof(int))){
			perror("Error at sending nrGen");
			exit(1);
			}
		}
		float avg;
		if(0 > read(c2p[0], &avg, sizeof(float))){
			perror("Error at reading the avg");
			exit(1);
		}
		close(p2c[1]);
		close(c2p[0]);
		printf("Avg= %f\n", avg);
		wait(0);
	}
	// 
	
	return 0;
}
