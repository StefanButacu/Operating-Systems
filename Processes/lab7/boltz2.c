#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int **myPipe;
int N;
int boltz(int n){
	if(n % 7 == 0)
		return 1;
	while(n){
	if(n % 10 == 7)
		return 1;
	n = n/10;
	}
}
void playBoltz(int NrProcese, int index){
	if(index + 1 < NrProcese){
		int f = fork();
		if( 0 > f)
		{
			perror("Erroare la creearea unui nou proces");
			exit(1);
		}
		else if(f == 0){
			playBoltz(NrProcese, index + 1);
			return
		}
	}
	else{
	// start playing 
	int nr;
	int readIndex = index%N;
	int writeIndex = (index + 1 ) %N;
	while(1){
		if() {
		// daca sunt la primul proces 
		
		}
	
	
	}
	
	
	}


}
int main(int argc, char** argv){
	if(argc < 2) {
	 	perror("Dati 1 argument");
		exit(1);
	}
	N = atoi(argv[1]);
	myPipe = malloc(N*sizeof(int*));
	for(int i = 0 ; i < N ; i++){
		myPipe[i]=malloc(2*sizeof(int));
		if(0 > pipe(myPipe))
		{
			perror("Error at creating pipe");
			exit(1);
		}
	}
	playBoltz(N, 0);
	return 0;
}	
