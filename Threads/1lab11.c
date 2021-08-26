#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
int N,M;

pthread_t thr[1000];
pthread_mutex_t mtx[1000];

void *work(void *arg){
	int nr = (int) arg;
	int i;
	printf("Alive %d\n", nr);
	for(i = 0; i < M; i++){
		pthread_mutex_lock(&mtx[i]);

		srandom(time(NULL));
		int s = random() % 100001 + 100000;
		usleep(s);
		printf("Thread %d a trecut prin %d punct de control\n", nr, i);
		pthread_mutex_unlock(&mtx[i]);
	}
	return NULL;

}
int main(int argc, char** argv){
	if(argc != 3){
		perror("NR invalid de params");
		exit(1);
	}
	N = atoi(argv[1]);
	M = atoi(argv[2]);
	//printf("%d,%d", N, M);
	int i;
	for(i = 0; i < M ; i++)
		pthread_mutex_init(&mtx[i], NULL);
	for(i = 0; i < N; i++){
		pthread_create(&thr[i], NULL, work, (void*) i);
	
	}
	for(i = 0; i < N ; i++)
		pthread_join(thr[i], NULL);
	for(i = 0 ; i < M ; i++)
		pthread_mutex_destroy(&mtx[i]);
	return 0;
	
}
