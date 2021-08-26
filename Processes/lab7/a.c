/*
 * Scrieti 2 programe C,A,B. Procesul A primeste  oricate argumente la linia de comanda si le trimite procesului B.
 * B transf orice litera mica din argumentele primite in litera mare si apoi le trimite procesului A. Procesul A citeste rezultatele le concateneaza
 * intr un string si il afiseaza 
 *
 *
*/
#include "common.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h> 
#include <string.h>

void make_fifo_if_not_exists(char * fifo_name){

	if(0 > mkfifo(fifo_name, 0600)){
		if(EEXIST == errno){
			printf("FIFO %s already exitst \n", fifo_name);
			if(0 > unlink(fifo_name)){
				perror("Error at deleting FIFO");
				exit(1);
			}
		
		}
		perror("Error at creating fifo");
		exit(1);
	}
}
void write_fo_file(int fd, char * str){
	int len = strlen(str);
	if( 0 > write(fd, &len, sizeof(int))){
		perror("Error on write lenght");
	}
	if( 0 > write(fd, str, len*sizeof(char))){
		perror("error on write string");
	}

}
int main(int argc, char* argv[]) {

	make_fifo_if_not_exists("./a2b");
	make_fifo_if_not_exists("./b2a");	
	int fda2b = open(a2b, O_WRONLY);
	int fdb2a = open(b2a, O_RDONLY);
	if( 0 > fda2b || 0 > fdb2a) {
		perror("Error opening fifo");
		exit(1);
	}
	int i;
	for( i = 1; i < argc; ++i){
		write_to_fifo(fda2b, argv[1]);	
	
	}
	int stop = -1;
	write(fda2b, &stop, sizeof(int));


	return 0;
}
