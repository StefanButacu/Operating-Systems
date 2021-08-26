#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void* nrCif(void* str){
	int n = strlen((char *) str);
	int i;
	int cnt;
	for(i = 0 ; i < n ; i++){
		if(str[i] >='0' && str[i] <= '9')
			cnt++;
	}
	return &cnt;

}
void* nrLit(void* str){
	int n = strlen((char*) str);
	int i; 
	int cnt;
	for( i = 0 ; i < n; i++){
		if( (str[i] >= 'a' && str[i] <= 'z') || (str[i] >'A' && str[i] <= 'Z')
				cnt++;
	}
	return &cnt;
}

void* nrSpec(void * str){


}
int main(int argc, char ** argv){
	int i;
	pthread_t t1,t2,t3;

	for(i = 0 ; i < argc; i++){
	// do smth argv[i]
	pthread_create(t1, NULL, nrCif, (void*) argv[i]);	
	}


}
