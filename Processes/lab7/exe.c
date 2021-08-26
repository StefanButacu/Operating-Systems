#include <unistd.h>
#include <stdlib.h>
#include <stdio.h> 
#include <sys/time.h> 
#include <sys/wait.h>
// primeste ca argument la linia de comanda o comanda bash si afiseaza timpul de executie
// fork 
// execvp
// gettimeofdayu

int main(int argc, char** argv){
	struct timeval start, end;
	gettimeofday(&start,NULL);
	if( fork() == 0){
		// sunt in procesul copil 
		execvp(argv[1], argv+1);
		exit(0);		
	
	}
	wait(0);
	 gettimeofday(&end,NULL);
	 double duration = ((end.tv_sec - start.tv_sec)*1000.0 + (end.tv_usec - start.tv_usec)/1000.0)/1000.0;
	 printf("Duration: %lf seconds\n", duration);

}
