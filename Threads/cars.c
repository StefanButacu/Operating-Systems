/*
 
   Car bridge under reparation. There is a bridge over a river, that is under reparation. Use locks and condition variables to synchronize, in a C program, the threads simulating cars, such that the following conditions hold simultaneously: 

   1.	Cars can pass the bridge in only one direction at one moment. The crossing direction is changed periodically (for instance, every 5 seconds) by another thread traffic_controller.

   2.	The maximum number of cars on the bridge is limited to MAX.

   3.	When the crossing direction is changed, the cars that are just given the permission to enter the bridge must wait until all the cars from the opposite direction exit the bridge.

   4.	NOTE 1. The threads playing roles of cars execute the following function:

   struct car_args {

   int car_id;

   int car_direction;

   }



   void* car(struct car_args *arg)

   {

      enter_bridge(arg->car_id, arg->car_direction);

         pass_bridge(arg->car_id, arg->car_direction);

	    exit_bridge(arg->car_id, arg->car_direction);



	       return NULL;

	       }

	       5.	NOTE 2. The thread controlling the passing direction executes the following function:

	       int passing_direction = 0;

	       void* trafic_controller(void* arg)

	       {

	          while (1) {

		       sleep(5);

		            change_passing_direction();

			       }

			       }

 */


#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#define N 10
#define MAX 5

pthread_mutext_t mtx;
pthread_cond_t cnd;
sem_t sem;
typedef struct carArg{
	int carId;
	int carDir;
}

void* car(void* arg){
	carArg myCar = *((carArg*)arg);
	pthread_mutex_lock(&mtx); 
	sem_wait(&sem);  // masina intra pe pod 




}
int main(){
	carArg args[N];
	for(int i = 0 ; i < N; i++){
		args[i].carId = i;
		args[i].carDir = 1;
	}
	pthread_mutex_init(&mtx, NULL);
	pthread_cond_init(&cnd,NULL);
	sem_init(&sem, 0, MAX);
	pthread_t thr[N];
	for(int i = 0 ; i< N; i++){
		pthread_create(&thr[i], NULL, car, &args[i]);
	
	}
	return 0;

}






























