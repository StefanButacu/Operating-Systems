int main(int argc, char* argv[]) {
	int fda2b = open(a2b, O_RDONLY); 
        int fdb2a = open(b2a, O_WRONLY);  



	while(1){
		int len;
		if( 0 > read(fda2b, &len, sizeof(int)))
			perror("Error on read lenght");
		if(len == -1)
			break;
		char *buf = malloc(sizeof(char) * len);
		int read_bytes = 0;
		while( read_bytes < len) {
			int k;
			if(0 > (k=read (fda2b, buf, sizeof(char)* len)))
			{
				perror("Error on read");
			
			}
			read_bytes += k;
				
		
		}
		int  i;
		for(i = 0 ; i < len; i++)
		{
			if(buf[i] >= 'a' && buf[i] <= 'z') {
				buf[i] += 'A' - 'a';
			
			}
		
		}


	
	}
