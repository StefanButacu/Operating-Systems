#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <stdio.h>


int bigL;
int sum;

pthread_mutex_t mtx;

void* work(void* arg){
	char* s = (char*) arg;
	FILE* f = fopen(s, "r");
	char buf[100];
	int k;
	while( (k = fread(buf, 1 , 100, f)) > 0){
		for(int i = 0 ; i < k ; i++){
			if('A' <= buf[i] && buf[i] <= 'Z')
			{
				pthread_mutex_lock(&mtx);
				bigL++;
				pthread_mutex_unlock(&mtx);
			}
			if('0' <= buf[i] && buf[i] <= '9')
			{
				pthread_mutex_lock(&mtx);
				sum += buf[i] - '0';
				pthread_mutex_unlock(&mtx);  

			}

		
		} 
	
	}
	fclose(f);
	return NULL;


}
int main(int argc, char** argv){
	
	int N = argc - 1;
	pthread_t* thr = malloc(sizeof(pthread_t) * N);
	pthread_mutex_init(&mtx,NULL);
	for(int i = 1; i < argc; i++)
		pthread_create(&thr[i], NULL, work, argv[i]);
	for(int i = 1; i < argc; i++)
		pthread_join(thr[i], NULL);
	printf("bigL = %d\nsum = %d\n", bigL, sum);
	pthread_mutex_destroy(&mtx);
	return 0;



}
