/* Convertese literele mici din arg in litere mari si afiseaza rezultatele
 *
 *
 *
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

typedef struct{

	char str[10];
}data;
void* f(void* arg){

	data* myDt = (data*) arg;
	int l = strlen(myDt->str);
	for(int i = 0 ; i < l ; i++)
		if('a' <= myDt->str[i] && myDt->str[i] <= 'z')
			myDt->str[i] -= 'a' - 'A';
	return NULL;
}

int main(int argc, char** argv){
	if(argc < 2) {
	printf("Give at least 1 paremter");
	exit(1);
	}
	pthread_t* T = malloc(sizeof(pthread_t) * argc);
	data* args = malloc(sizeof(data) * argc);
	for(int i = 0 ; i < argc; i++){
		strcpy(args[i].str, argv[i]);
		pthread_create(&T[i], NULL, f, (void*) &args[i]);
	}
	for(int i = 0 ; i < argc; i++)
		pthread_join(T[i], NULL);
	for(int i = 0 ; i < argc; i++)
		printf("%s\n", args[i].str);
	free(T);
	free(args);
	return 0;



} 
