/* Scrieti un program C care primeste ca arg la linia de comanda un nr intreg N
 * Procesul va crea 2 procese fiu
 * Fiecare Proces fiu va avea un sir de frecvente pentru cifrele din baza 10
 * si va genera N numere intregi aleatoare in 100 si 999
 * Firecare proces fiu va actualiza sirul de frecventa al cifrelor in functei de cifrele continute de numerele generate. DUpa ce a generat N numere aleatoare fiecare proces fiu isi trimite sirul de frecventa catre procesul parinte. Procesul parinte va afisa un mesaj pentru fiecare cifra indicard care proces fiu a obtinut frecventa mai mare. Firecare proces fiu va afisa fiecare numar generat 
 *
 *
 * */
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
void init(int* fr){
	for(int i = 0 ; i < 10; i++)
		fr[i] = 0;
}
int main(int argc, char** argv){
	if(argc != 2){
		perror("Invalid nr of params");
		return 0;
	}
	int N = atoi(argv[1]);
	int a2p = mkfifo("a2p", 0600);
	if( 0  > a2p){
		perror("Error at creating 1st fifo");
		exit(1);

	}
	int b2p = mkfifo("b2p", 0600);
	if( 0 > b2p){
		perror("Error at creating 2nd fifo");
		exit(1);
	}
	int pid1 = fork();
	if( 0 > pid1)
		perror("Error at creating 1st process");
	if( 0 == pid1){
		// child only code
		int fr1[10];
		init(fr1);
		srandom(getpid());
		printf("Child 1 generates: ");
		for(int i = 0; i < N; i++){
			int x = random() % 900 + 100;
			printf(" %d, ",x);
			while(x){
				fr1[x%10]++;
				x /= 10;
			}

		}
		printf("\nFrecv array for child 1:\n");
		for(int i = 0; i < 10; i++){
			printf("%d ", fr1[i]);
		}
		printf("\n");
		int fd = open("a2p", O_WRONLY);
		for(int i = 0 ; i < 10; i++){
			if( 0 > write(fd, &fr1[i], sizeof(int))){
				perror("Error at child 1 writing"); 
			}
		
		}
		exit(0);
	}
	int pid2 = fork();
	if( 0 > pid2)
		perror("Error at creating 2nd process");
	if( 0 == pid2){
		// child2
		int fr2[10];
		init(fr2);
		srandom(getpid());
		printf("Child 2 generates: ");
		for(int i = 0; i  < N ;i++){
			int x = random()%900 + 100;
			printf(" %d, ", x);
			while(x){
				fr2[x%10]++;
				x/=10;
			}
		}
		printf("\nFrecv array for child2: \n");
		for(int i = 0; i < 10; i++)
			printf("%d ", fr2[i]);
		int fd = open("b2p", O_WRONLY);
		for(int i = 0; i < 10; i++){
			if( 0 > write(fd, &fr2[i], sizeof(int)))
				perror("Error at child 2 writing");
		}
		printf("\n");
		exit(0);

	}
	// cod parinte
	int fr1[10], fr2[10];
	int fd1 = open("a2p", O_RDONLY);
	for(int i = 0 ; i < 10; i++){
		if( 0 > read(fd1, &fr1[i], sizeof(int))){
			perror("Error at read from child1");
		}
	}
	int fd2 = open("b2p", O_RDONLY);
	for(int i = 0; i < 10; i++){
		if(0 > read(fd2, &fr2[i], sizeof(int)))
			perror("Error at read from child2");
	
	}
	
	for(int i = 0; i < 10; i++){
		printf("%d -", i);
		if( fr1[i] > fr2[i])
			printf(" Child 1\n");
		else
			if(fr1[i] < fr2[i])
				printf(" Child 2\n");
			else 
				if(fr1[i] == fr2[i])
					printf(" Equal\n");
	
	}
	wait(0);
	wait(0);
	
	
	if( 0 > unlink("a2p"))
		perror("Error at rmv 1st fifo");
	if( 0 > unlink("b2p"))
		perror("Error at rmv 2nd fifo");
	return 0;
}
