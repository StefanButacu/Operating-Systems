#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>


int main(){

	int a2b = open("a2b", O_RDONLY);
	int l3;
	if( 0 > read(a2b, &l3, sizeof(int))){
	perror("Error at reading 3rd lenght");
	exit(1);
	}
	char* sir = malloc((l3+1) * sizeof(char));
	int read_bytes = 0;
	int max = l3;
	while(read_bytes < max){
	int k;
	if(( k = read(a2b, sir + read_bytes, (max-read_bytes) * sizeof(char))) > 0)
		read_bytes +=k;
	}
	sir[l3] = 0;	
	printf("Sirul concatenat este %s", sir);
	free(sir);
	return 0;
}
