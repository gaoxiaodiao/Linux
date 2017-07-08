////////////////////////////////////
//文件说明:tcp_client.c
//作者:高小调
//创建时间:2017年07月08日 星期六 10时16分24秒
//开发环境:Kali Linux/g++ v6.3.0
////////////////////////////////////
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>
int main(int argc,const char* argv[]){
	if(argc!=3){
		printf("useage:%s [ip] [port]\n",argv[0]);
		return 0;
	}
	int sd = socket(AF_INET,SOCK_STREAM,0);
	if(sd < 0){
		perror("socket");
		return 1;	
	}
	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(atoi(argv[2]));
	local.sin_addr.s_addr = inet_addr(argv[1]);
	if(connect(sd,(struct sockaddr*)&local,sizeof(local)) < 0){
		perror("connect");
		return 2;
	}
	dup2(sd,1);
	while(1){
		char buff[1024] = {0};
		ssize_t s = read(0,buff,sizeof(buff)-1);
		printf("%s",buff);
		fflush(stdout);
		//write(sd,buff,strlen(buff));
	}
	return 0;
}
