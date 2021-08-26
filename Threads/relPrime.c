//4. A C program receives command line args pairs of numbers, and creates for each pair a thread that checks is the two numbers are relatively prime (gcd=1), incrementing a global variable. The program prints at the end how many relatively prime pairs have been found and the respective pairs.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
int v;

int gcd(int a, int b){
	int r = a % b;
	while(r){
		a = b;
		b = r;
		r = a % b;
	}
	return b;
}
pthread_mutex_t mtx;

typedef struct {
	int a,b;
}pair;

pair ans[150];

void* work( void * arg){
 	pair data = *((pair*) arg);
	if(gcd(data.a,data.b) == 1){
		pthread_mutex_lock(&mtx);
		ans[v].a = data.a;
		ans[v].b = data.b;
		v++;
		pthread_mutex_unlock(&mtx);
	
	}
	return NULL;

}
int main(int argc, char** argv){
	pair* pairs = malloc(sizeof(pair) * ((argc / 2) + 1));
	int len=0;
	// 0 -> 1 si 2
	// 1 -> 3 si 4 
	// 2 -> 5 si 6 
	  for(int i = 0;  2*(i+1) < argc; i++){
		printf("%s,%s\n", argv[2*i+1], argv[2*(i+1)]);
		pairs[i].a = atoi(argv[2*i+1]);
		pairs[i].b = atoi(argv[2*(i+1)]);
		len++;
	}	
	pthread_t* thr = malloc(sizeof(pthread_t) * len);
	pthread_mutex_init(&mtx, NULL);
	for(int i = 0 ; i < len; i++){
		pthread_create(&thr[i], NULL, work, &pairs[i]);
	
	}
	for(int i = 0; i < len; i++)
		pthread_join(thr[i], NULL);
	//pthread_mutex_destory(&mtx);
	pthread_mutex_destroy(&mtx);
	printf("%d pairs\n", v);
	for(int i = 0 ; i < v ; i++){
		printf("a=%d, b=%d\n", ans[i].a, ans[i].b);
	
	}
	free(pairs);
	free(thr);
	return 0;


}
