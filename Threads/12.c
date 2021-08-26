//  Write a C program that receives integers as command line argument. The program will keep a frequency vector for all digits. The program will create a thread for each argument that counts the number of occurences of each digit and adds the result to the frequency vector. Use efficient synchronization.

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct{
	int *myFrecv;
	int nr;
	pthread_mutex_t* mtxs;

}data; 

void* work(void* arg){
	data d = *((data*) arg);
	int nr = d.nr;
	int fr[10] = {0,0,0,0,0,0,0,0,0,0};
	while(nr > 0){
		fr[nr%10]++;
		nr /= 10;
	}
	for(int i = 0 ; i < 10; i++){
		if(fr[i] > 0){
			pthread_mutex_lock(&d.mtxs[i]);
			d.myFrecv[i] +=fr[i];
			pthread_mutex_unlock(&d.mtxs[i]);
		}		
	}

	return NULL;
}
int main(int argc, char** argv){
	if( argc <= 1){
		perror("Please give at least 1 number");
		exit(1);
	}
	int *frecv = malloc(sizeof(int)* 10);
	pthread_mutex_t* mtx = malloc(sizeof(pthread_mutex_t) * 10);
	for(int i = 0 ; i < 10; i++)
	{
		frecv[i] = 0;
		pthread_mutex_init(&mtx[i], NULL);
	}
	data* args = malloc(sizeof(data) * argc);
	for(int i = 1; i < argc; i++){
		args[i].nr = atoi(argv[i]);
		args[i].myFrecv = frecv;
		args[i].mtxs = mtx;
	
	}	
	pthread_t* thr = malloc(sizeof(pthread_t) * argc);
	for(int i = 1; i < argc; i++){
		pthread_create(&thr[i], NULL, work, &args[i]);
	
	}
	for(int i = 1; i < argc; i++)
		pthread_join(thr[i],NULL);
	
	for(int i = 0; i < 10; i++)
	{	
		pthread_mutex_destroy(&mtx[i]);
		printf("%d -> %d times\n", i, frecv[i]);	
	}
	free(frecv);
	free(mtx);
	free(args);
	free(thr);
	return 0;


}
