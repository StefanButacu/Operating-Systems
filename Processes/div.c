#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){
	int p2c[2], c2p[2];
	int pid;
	pipe(p2c);
	pipe(c2p);
	pid = fork();
	if ( 0 > pid) {
		perror("Error at fork");
		exit(1);
	}
	if( 0 == pid){
		int n;
		close(p2c[1]);
		close(c2p[0]);
		while(1){
			if( 0 > read(p2c[0], &n, sizeof(int))){
				perror("Error at reading N");
				exit(1);
			}
			if( n == 0) break;
			int i;
			int cnt = 0;
			for(i = 1; i <= n ; i++)
				if(n % i == 0)
				       cnt++;
			if( 0 > write(c2p[1], &cnt, sizeof(int))){
				perror("Error at write nr");
				exit(1);
			}
			for(i = 1; i <=n ; i++){
				if(n % i == 0){
					if( 0 > write(c2p[1], &i, sizeof(int))){
					perror("Error at writeing divizor");
					exit(1);
					}
				
				}
			
			}
		
		}
		close(p2c[0]);
		close(c2p[1]);
		exit(1);
	}
	else if(0 < pid){
		int n;
		close(p2c[0]);
		close(c2p[1]);
		while(1){
			printf("n="); 
			scanf("%d", &n);
			if( n == 0) 
				break;
			if( 0 > write(p2c[1], &n, sizeof(int))){
				perror("error at writing N");
				exit(1);
			}
			int cnt;
			if( 0 > read(c2p[0], &cnt, sizeof(int))){
				perror("Error at reading from child");
				exit(1);
			}
			int i;
			int x;
			for(i = 1; i <= cnt; i++)
			{
				if( 0 > read(c2p[0], &x, sizeof(int))){
					perror("Error at reading divizor");
					exit(1);
				}
				printf("%d ", x);
			}

			printf("\n");
		}

		close(p2c[1]);
		close(c2p[0]);
		wait(0);
	}



	return 0;
}
