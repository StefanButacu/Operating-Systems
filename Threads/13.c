
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

typedef struct{
	int N;
	int * arr;
} data;

pthread_cond_t cond1, cond2;
pthread_mutex_t mutex1, mutex2;

void* f1(void *arg){
	// pare
	data d = *((data * arg));
	int i=0;
	while(i < d.N){
		int num = (random() % 51 ) * 2;
		d.arr[i]= num;
		i+=2;
		pthread_cond_signal(&cond2);
		 pthread_mutex_lock(&mutex2);
		  pthread_cond_wait(&cond2, &mutex2);   
	}
	return NULL;
}
void* f2(void *arg){
	// impare
	data d = *((data * arg));
	int i=1;
	while(i < d.N){
		int num = (random() % 51 ) * 2; 
		d.arr[i]= num;
		i+=2;
		pthread_cond_signal(&cond1);
		pthread_mutex_lock(&mutex2);
		pthread_cond_wait(&cond2, &mutex2);
	}


	return NULL;
}
void init_args(data* arg, int* arr, int N){
	arg->N = N;
	arg->arr = arr;

}
int main(int argc, char** argv[]){

	if(argc != 2){
		printf("Dati argmunet\n");
		exit(1);
	}
	int N = atoi(argv[1]);
	int *arr = malloc(sizeof(int) * N);
	srandom(time(NULL));

	pthread_mutex_init(&mutex1,NULL);
	pthread_mutex_init(&mutex2,NULL);
	pthread_cond_init(&cond1, NULL);
	pthread_cond_init(&cond2, NULL);

	pthread_t T[2];
	data args[2];

	init_args(&args[0], arr, N);
	init_args(&args[1], arr, N);

	pthread_create(&T[0], NULL, f1, (void*) &args[0]);
	pthread_create(&T[1], NULL, f2, (void*) &args[1]);
	pthread_join(T[0], NULL);
	pthread_join(T[1], NULL);
	int i;
	for(i = 0; i < N ; i++)
		printf("%d ", arr[i]);
	free(arr);
	pthread_mutex_destroy(&mutex1);
	pthread_mutex_destroy(&mutex2);

	return 0;
}
