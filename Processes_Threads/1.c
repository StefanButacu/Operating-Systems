/*Program C care creeaza 10 threaduri si primeste ca arg la linia de comanda un N intreg
 * Fiecare intreg primeste un index I ca arg (0 <=i <=9)
 * fiecare thread va genera N nr aleatoare int 100 si 999
 * Fiecare thread va calcula frecventa cifrelor din baza 10 din numerele generate si le va aduna la un vector de frecventa global
 * Fiecare thread va astepta pana cand toate threadurile au generat N nr si au adunat vectorul de frecventa local la cel global
 * apoi fiecare thread va afisa frecventa globala a cifrei i (index ul threadului
 * Fiecare thread va afisa numerele pe care le genereaza alaturi de indexul sau 
 *
 * */
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#define T 10
#define M 10

typedef struct{
	int index;
	int N;
	pthread_mutex_t* mtxs;
	pthread_barrier_t* bar;
}myData;

int frGlobal[10];
void* work(void * arg){
	myData d = *((myData*) arg);
	int frLocal[10];
	for(int i = 0 ; i < 10; i++)
		frLocal[i] = 0;
	for(int i = 0 ; i < d.N; i++){
		int x = random() % 900 + 100;
		printf("Threadul %d a generat %d\n", d.index, x);
		while(x) {
			frLocal[x%10]++;
			x = x/10;
		}

	}

	for(int j = 0 ; j < 10; j++){
		if(frLocal[j] > 0){
		pthread_mutex_lock(&d.mtxs[j]);
		frGlobal[j] += frLocal[j]; 
		pthread_mutex_unlock(&d.mtxs[j]);
		
		}
	
	}
	pthread_barrier_wait(d.bar);
	printf("Frecventa globala a cifrei %i = %i\n", d.index, frGlobal[d.index]);
	return NULL;
}
int main(int argc, char** argv){
	if(argc != 2){
		perror("Nr invalid de params");
		exit(1);
	}
	pthread_t thr[T];
	myData args[T];
	int N = atoi(argv[1]);
	srandom(time(NULL));
	pthread_mutex_t* mtxs = malloc(sizeof(pthread_mutex_t) * M);
	pthread_barrier_t* bar = malloc(sizeof(pthread_barrier_t));
	if( 0 > pthread_barrier_init(bar, NULL, 10)){
		perror("Error at init bar");
	}
	for(int i = 0; i < T; i++){
		args[i].index = i;
		args[i].N = N;
		args[i].mtxs = mtxs;
		args[i].bar = bar;
	} 
	for(int i = 0; i < M; i++)
		pthread_mutex_init(&mtxs[i], NULL);
	for(int i = 0; i < T; i++){
		if( 0 > pthread_create(&thr[i], NULL, work,(void*) &args[i])){
			perror("Error at creating thread");
		}
	
	}
	for(int i = 0 ; i < T; i++)
		pthread_join(thr[i], NULL);
	for(int i = 0; i < M; i++)
		pthread_mutex_destroy(&mtxs[i]);
	free(mtxs);
	pthread_barrier_destroy(bar);
	free(bar);
	return 0;

}
