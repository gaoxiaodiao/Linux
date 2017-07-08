/**************************************
*文件说明:udp_server.c
*作者:高小调
*创建时间:2017年07月06日 星期四 09时34分13秒
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
int main(int argc,const char* argv[]){
	if(argc!=3){
		return 0;
	}
	int sd = socket(AF_INET,SOCK_DGRAM,0);
	if(sd<0){
		perror("socket");
		return 1;
	}
	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(atoi(argv[2]));
	local.sin_addr.s_addr = inet_addr(argv[1]);
	if(bind(sd,(struct sockaddr*)&local,sizeof(local)) < 0){
		perror("bind");
		return 2;
	}
	char buff[1024] = {0};
	while(1){
		struct sockaddr_in client;
		int size = sizeof(client);
		ssize_t s = recvfrom(sd,buff,sizeof(buff)-1,0,(struct sockaddr*)&client,&size);
		if(s < 0){
			perror("recvfrom");
			return 3;
		}
		buff[s] = 0;
		printf("%s:%d#%s\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port),buff);
	}
	return 0;
}
