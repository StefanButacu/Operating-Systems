#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct{
	int a;
	int b;
	int* v;
	int s;
	pthread_mutex_t m;
}myData;

void* f(void *arg){

	int b = (*((myData*) arg)).b;
	int a = (*((myData*) arg)).a;
	(*((myData*) arg)).a++;
	printf("This is %d %d",a,b);
	pthread_mutex_lock(&((*((myData*) arg)).m));
	for(int i = 0 ; i < 3 ; i++)
		(*((myData*) arg)).s += (*((myData*) arg)).v[i];
	pthread_mutex_unlock(&(((*((myData*) arg)).m)));  
	return NULL;
}
int main(){
	myData* p = malloc(sizeof(myData));
	(*p).a = 5;
	(*p).b = 10;
	(*p).v = malloc(3 * sizeof(int));
	(*p).s = 0;
	pthread_mutex_init(&((*p).m), NULL);
	for(int i = 0 ; i < 3 ; i++)
		(*p).v[i] = i+1;
	pthread_t t;
	pthread_create(&t, NULL, f, p);
	
	pthread_join(t,NULL);
	printf("%d", p->s);
	return 0;



}
