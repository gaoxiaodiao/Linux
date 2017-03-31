#include<stdio.h>
#include<unistd.h>
int main(){
	int i = 0;
	char str[22] = {0};
	for(i=0; i<=20; ++i){	
		str[i] = '*';	
		str[i+1] = 0;
		printf("[%-20s][%d%%]\r",str,i);
		fflush(stdout);
		sleep(1);
	}

}
