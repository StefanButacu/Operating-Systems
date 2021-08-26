/*
 *Citeste o matrice de intregi dintr un fisier
 Creeaza un nr de thread uri egal cu nr de randuri din matrice
 Fiecare thread Calculeaza suma nuemerlor de pe un rand
 Procesul principal asteapta ca threadurile sa isi incheie executia si apoi afiseaza sumele
 *
 * */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h> 
int N,M;
int **matrix;

typedef struct {
	int linie;
	int suma;
	pthread_mutex_t m;
}data;
void* suma(void *arg){
	int i;
	data a = *((data*) arg);
	for(i = 0 ; i < M ; i++){
		pthread_mutex_lock(&a.m);
		a.suma += matrix[a.linie][i];
		pthread_mutex_unlock(&a.m);
	}
	printf("Thread %d -> sum %d\n", a.linie, a.suma);
	return NULL;
}
int main(int argc, char** argv){
	if(argc != 2) {
		perror("Please provide the fileName");
		exit(1);
	}
	char s[100];
	strcpy(s, argv[1]);
	FILE* f = fopen(s, "r");
	fscanf(f, "%d", &N);
	fscanf(f, "%d", &M);
	matrix = malloc(N * sizeof(int *));
	int i = 0;
	for(i = 0; i < N ; i++)
		matrix[i] = malloc(M * sizeof(int));
	int j;
	for( i = 0 ; i < N ; i++)
		for(j = 0 ; j < M ; j++)
			fscanf(f, "%d", &matrix[i][j]);

	pthread_t* T;
	T = malloc(sizeof(pthread_t) * N);
	data* dt = malloc(sizeof(data) * N);
	for(i = 0 ; i < N; i++) 
		pthread_mutex_init(&dt[i].m, NULL);
	for(i = 0 ; i < N; i++)
	{
		dt[i].linie = i;
		dt[i].suma = 0;
		pthread_create(&T[i], NULL, suma, (void*)&dt[i]);

	}
	for(i = 0 ; i < N ; i++)
	{
		pthread_join(T[i], NULL);
		// printf("Rand %d -> sum %d\n", dt[i].linie, dt[i].suma);         	
		pthread_mutex_destroy(&dt[i].m);
	}
	free(T);
	free(dt);
	for(i= 0; i < N ; i++)
		free(matrix[i]);
	free(matrix);
	fclose(f);
	return 0;
}
