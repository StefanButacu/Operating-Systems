/*
 *
 *calculate the sum of all the elements of the matrix using as many threads as there are rows, each thread adds to the total the numbers on a row
 *
 * */ 
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct{

	int index;
	int M;
	int linie[105];
	int* sum;
} data;

pthread_mutex_t mtx;

void* work(void* arg){
	data d = *((data*) arg);
	int s = 0;
	for(int i = 0 ; i < d.M; i++)
		s+= d.linie[i];
	pthread_mutex_lock(&mtx);
	*(d.sum) += s;
	pthread_mutex_unlock(&mtx);

	return NULL;
}
int main(int argc, char** argv){
	if(argc != 2){
		perror("Invalid nr of params");
		exit(1);
	}
	FILE*f = fopen(argv[1], "r");
	int N, M;
	data matrix[10005];
	fscanf(f,"%d", &N);
	fscanf(f,"%d", &M);
	int* mySum = malloc(sizeof(int));
	*mySum = 0;
	for(int i = 0; i < N; i++)
	{	
		matrix[i].index = i;
		matrix[i].M = M;
		matrix[i].sum = mySum;
		for(int j = 0 ; j < M; j++)
			fscanf(f,"%d", &matrix[i].linie[j]);
	
	}
	pthread_t thr[10005];
	pthread_mutex_init(&mtx, NULL);
	for(int i = 0 ; i < N; i++){
	pthread_create(&thr[i], NULL, work, &matrix[i]);
	
	}
	for(int i = 0 ; i < N; i++)
		pthread_join(thr[i], NULL);
	pthread_mutex_destroy(&mtx);
	printf("Suma din matrice este %d", *mySum);
	free(mySum);
	fclose(f);
	return 0;
}
