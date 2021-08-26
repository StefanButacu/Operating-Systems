// Write a C program that receives any number of strings as command line arguments. The program creates two child processes, which inherit the parent's command line arguments (ie. no need to send the arguments via pipe/fifo to the children for this problem). Each child process creates a thread for each of the command line arguments. Each thread created by the first child will extract the vowels from its argument and will append them to a string shared among the threads. Each thread created by the second child process will extract the digits from its argument and will add them to a sum shared among the threads. Both child processes wait for their respective threads to finish and send the result to the parent via pipe. The parent displays the results.
// Scrieti un program C care primeste oricate argumente la linia de comanda. Programul creeaza doua procese fiu care mostenesc argumentele de la linia de comanda primite de parinte (pentru aceasta problema nu e necesar sa se trimita argumentele prin pipe). Fiecare proces fiu creeaza cate un thread pentru fiecare argument de la linia de comanda. Fiecare thread creat de primul proces fiu extrage vocalele din argumentul sau si le concateneaza la un string accesibil de catre toate thread-urile primului proces fiu. Fiecare thread creat de al doilea proces fiu extrage cifrele din argumentul sau si le aduna la o variabila suma accesibila de catre toate thread-urile celui de-al doilea proces fiu. Ambele procese fiu asteapta ca thread-urile proprii sa se incheie, apoi trimit rezultatul catre procesul parinte prin pipe.
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <pthread.h>
#include <string.h>


typedef struct{
	char s[100];
	pthread_mutex_t* mtx;
	int* len;
	char* rez;
} myData1;
void* proc1(void * arg){

	myData1 d = *((myData1*) arg);
	int i = 0;
	char vocale[] = "aeiouAEIOU";
	while(d.s[i]){
		if(strchr(vocale,d.s[i])){
			pthread_mutex_lock(d.mtx);
			d.rez[(*(d.len))] = d.s[i];
			(*(d.len))++;
	         	pthread_mutex_unlock(d.mtx);
		}
	
		i++;
	}
	
	return NULL;
}
pthread_mutex_t mtx2;
int sum;
typedef struct{
	char s[100];
	pthread_mutex_t *mtx;
	int* sum;

}myData2;
void* proc2(void * arg){
	myData2 d = *((myData2*) arg);
	int i = 0;
	while(d.s[i]){
		if('0' <= d.s[i] && d.s[i] <= '9'){
			pthread_mutex_lock(d.mtx);
			*(d.sum) += d.s[i] - '0';
			pthread_mutex_unlock(d.mtx);
		
		}
	
		i++;
	}
	return NULL;

}
int main(int argc, char** argv){
	int c1p[2];int c2p[2];
	pipe(c1p); pipe(c2p);
	int pid1 = fork();
	if(0 > pid1){
		perror("Error at creating 1st process");
		exit(1);
	
	}
	if(0 == pid1){
	// child only code
	close(c1p[0]); // inchid capatul de read in procesul fiu
	close(c2p[0]); close(c2p[1]);
	pthread_t* thr1 = malloc(sizeof(pthread_t) *argc);
	int maxLen = 0;
	for(int i = 1; i < argc; i++)
		maxLen += strlen(argv[i]);

	char* rez1 = malloc(sizeof(char) * maxLen);
	pthread_mutex_t* mtx1 = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(mtx1, NULL);	
	int* len1 = malloc(sizeof(int)); *(len1) = 0;
	myData1* args = malloc(sizeof(myData1) * argc);

	for(int i = 1; i < argc; i++){
		strcpy(args[i].s, argv[i]);
		args[i].mtx = mtx1;
		args[i].len = len1;
		args[i].rez = rez1;
	}


	for(int i = 1; i < argc; i++){
		pthread_create(&thr1[i], NULL, proc1, &args[i]);
	
	}
	for(int i = 1; i < argc; i++)
		pthread_join(thr1[i], NULL);
	 	

	if( 0 > write(c1p[1], len1, sizeof(int))){
		perror("Error at sending lenght1 to parent");
		exit(1);
	
	}
	if( 0 > write(c1p[1], rez1, sizeof(char) * (*len1))){
		perror("Error at sending rez1 to parent");
		exit(1);
			
	}
	pthread_mutex_destroy(mtx1);
	close(c1p[1]);
	free(args);
	free(len1);
	free(mtx1);
	free(rez1);
	free(thr1);
	exit(0);
	
	}else{
	// parent only code
	int pid2 = fork();
	if( 0 > pid2){
		perror("Error at creating 2nd process");
		exit(1);
	
	}
	if( 0 == pid2){
	// child2 only code		
		close(c1p[0]);close(c1p[1]);
		close(c2p[0]);
		pthread_t* thr2 = malloc(sizeof(pthread_t) * argc);
		pthread_mutex_t* mtx = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(mtx, NULL);
		int* sum = malloc(sizeof(sum)); (*(sum)) = 0;
		myData2* args = malloc(sizeof(myData2) * argc);
		for(int i = 1; i < argc; i++){
			strcpy(args[i].s, argv[i]);
			args[i].sum = sum;
			args[i].mtx = mtx;
		
		}
		for(int i = 1; i < argc; i++){
			pthread_create(&thr2[i], NULL, proc2, &args[i]);
		
		}
		for(int i = 1; i < argc; i++)
			pthread_join(thr2[i], NULL);
		pthread_mutex_destroy(mtx);

		if( 0 > write( c2p[1], sum, sizeof(int))){
			perror("Error sending sum to parent");
			exit(1);		
				
		}
		close(c2p[1]);
		free(args);
		free(sum);
		free(mtx);
		free(thr2);
		exit(0);
		
	}
	else{
	// parent only sure  
	//
	close(c1p[1]);
	close(c2p[1]);
	int len1;
	if( 0 > read(c1p[0], &len1, sizeof(int))){
		perror("Error at reading len1");
		exit(1);
	}
	char* rez1 = malloc(sizeof(char) * len1);
	if( 0 > read(c1p[0], rez1, len1)){
		perror("Error at reading rez1");
		exit(1);		
	}
	close(c1p[0]);
	printf("%s -> %s\n", "Rezultatul procesului 1", rez1);
	free(rez1);	
	int mySum;
	if( 0 > read(c2p[0],&mySum, sizeof(int))){
		perror("Error at reading the sum");
		exit(1);

	} 
	close(c2p[0]);
	printf("%s -> %d\n", "Rezultatul procesului 2", mySum);
	wait(0);wait(0);
	}
	
	
	}



	return 0;
}
