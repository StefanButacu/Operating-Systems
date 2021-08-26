//(Partea 4 - pregatire pentru examen)
//
//        Sa se scrie un program care genereaza pe 5 thread-uri distincte 1000 de numere intregi pe care le introduce intr-un vector global. 
//
//                Fiecare numar generat va fi introdus de thread-ul care l-a generat pe pozitia corecta in vector, astfel incat la orice moment vectorul sa fie sortat.
//
//                        Threadul principal va afisa la fiecare 10 numere generate intreg continutul vectorului.

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define T 5
#define N 100

int v[T*N + 5]; // vectorul in care se vor pune numerele 
int len;
pthread_t thr[T];
pthread_mutex_t mtx;
pthread_cond_t cnd;
pthread_barrier_t bar;
pthread_cond_t goThr;
int flag = 0;
void* work(void * arg){
	pthread_barrier_wait(&bar);
	for(int i = 0; i < N; i++){
		 pthread_mutex_lock(&mtx);   
		int nr = random() % (T*N) + 1;
	//	pthread_mutex_lock(&mtx);
		// inserez in v
		if(len == 0)
		{      // v e gol 
			v[len] = nr;
			len++;
		}
		else
		{
			if( v[len - 1] <= nr){
				// nr generat e mai mare decat ultimul 
				v[len] = nr;
				len++;

			} 
			else{ // trebuie inserat undeva in interior
				int j = 0;
				while(nr > v[j])
					j++;
				for(int k = len; k > j; k--)
					v[k] = v[k-1];
				v[j] = nr;
				len++;

			}
// daca lungimea e diferita de cea veche 
			if( len % 10 == 0){	
				flag = 1;   
				pthread_cond_signal(&cnd); // trimit semnal la main 
				while(flag == 1){
					pthread_cond_wait(&goThr, &mtx); // astept sa mi zica main ca a terminat afisarea
				}
			}
				
		}
		pthread_mutex_unlock(&mtx);

	}
	return NULL;


}

int main(int argc, char** argv){

	srandom(time(NULL));
	pthread_mutex_init(&mtx,NULL);
	pthread_cond_init(&cnd, NULL);
	pthread_cond_init(&goThr, NULL);
	pthread_barrier_init(&bar, NULL, T);
	for(int i = 0 ; i < T; i++)
	{
		pthread_create(&thr[i], NULL, work, NULL);
	}


	pthread_mutex_lock(&mtx);  
	while(len < T * N){
// Ulitma lungime afisata
		while(flag == 0)
			pthread_cond_wait(&cnd, &mtx);
		while(flag == 1){
			sleep(1);
			printf("Len = %d\n", len);
			for(int k = 0; k < len; k++)
				printf("%d ", v[k]);
			printf("\n");
			flag = 0;
					
		}
		pthread_cond_broadcast(&goThr);
//	pthread_mutex_unlock(&mtx);

	}	
	pthread_mutex_unlock(&mtx);

	for(int i = 0 ; i< T; i++)
		pthread_join(thr[i], NULL);
	printf("\n");
	for(int i = 0 ; i < len; i++)
		printf("%d ", v[i]);
pthread_mutex_destroy(&mtx);
pthread_cond_destroy(&cnd);
pthread_cond_destroy(&goThr);
pthread_barrier_destroy(&bar);
return 0;


}
