#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int mypipe[2];
int N;
int boltz(int n){
	if(n % 7 == 0)
		return 1;
	while(n){
	if(n % 10 == 7)
		return 1;
	n = n/10;
	}
	return 0;
}

void playBoltz(int nrProces){
while(1){ // am scris un while aici din cauza ca: 1. Dupa ce se executa ne nrProcese ori if-ul sa se mearga pe ramura else si sa se continue
	// se creeaza cu ajutorul if ului recursiv cele N procese 
	// ca mai apoi in ramura else sa se continue citirea si scrierea in pipe 
	// problema e ca se creeaza prea multe procese(decat N ul citit), de fapt se creeaza atatea procese cat permite sistemul si de asemenea cand Dupe ce se afiseaza mesajul "A iesit prin random" procgramul nu isi finaliezaza executia 
	//  ramane suspendat (cel mai probabil din cauza ca sistemul nu permite crearea altor procese, fie din cauza waiturilor, fie a pipe ului ) :) cam multe path-uri de facut debug
	///////////////////////////////////////////////////////////////
	if(nrProces > 0){
		int pid = fork();
		if( 0 > pid ) {
			perror("Error at fork call");
			exit(1);	
		}
		if(pid == 0) {
		// do stuff with this child 
		// send through pipe the number 
		int n;
		read(mypipe[0], &n, sizeof(int)); // il citesc in procesul copil 
		if(boltz(n) == 1){
			//	genreaza nr intre 1 si 3  si vezi daca pica 
			srandom(time(NULL));
			int nrRand = random() % 3 + 1;
		 	printf("\n(nrRandom=%d)\n", nrRand);
			if(nrRand == 1) 

			{ 	
				int i; 
				for(i = 1; i <= N - nrProces; i++) 
					wait(0);
				printf("A iesit prin random\n");
				exit(0);
			}
			else 
				printf("boltz\n");	
		}
		else{
			printf("%d\n", n);
		}
		n++;
		write(mypipe[1], &n, sizeof(int));
		playBoltz(nrProces-1);

		}	
//	wait(0);
		 
	}
	// inainte sa introduc acest if in structura while(1)  programul "parea ca merge ok" doar ca se generau 
	// 
	/////////////////////////////////////////
	else{
		int n;
		read(mypipe[0], &n, sizeof(int));
		if(boltz(n) == 1){	
			srandom(time(NULL));
			int nrRand = random() % 3 + 1;	
			printf("\n(nrRandom = %d)\n", nrRand);
			if(nrRand == 1) 
			{
			int i;
			for(i = 1; i <= N ;i++)
				wait(0);
			printf("A iesit prin random\n"); 
			exit(0); // break ?
			}
			else printf("boltz\n");
			}
		else printf("%d\n", n);
		n++;
		write(mypipe[1], &n, sizeof(int));

		}
	}
}

int main(){
	printf("N=");
	scanf("%d", &N);

	int i;
	pipe(mypipe);
	i = 1;
	write(mypipe[1], &i, sizeof(int)); // scriu primul nr prin pipe
	playBoltz(N);
	return 0;
}	
