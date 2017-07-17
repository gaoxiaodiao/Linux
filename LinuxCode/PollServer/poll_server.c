////////////////////////////////////
//文件说明:poll_server.c
//作者:高小调
//创建时间:2017年07月10日 星期一 10时26分41秒
//开发环境:Kali Linux/g++ v6.3.0
////////////////////////////////////
#include<stdio.h>
#include<poll.h>
int start_up(const char* ip,const char* port){
	int sd = socket(AF_INET,SOCK_STREAM,0);
	if( sd < 0 ){
		perror("socket");
		exit(1);
	}
	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(atoi(port));
	local.sin_addr.s_addr = innet_addr(ip);
	if(bind(sd,(struct sockaddr*)&local,sizeof(local)) < 0){
		perror("bind");
		exit(2);
	}
	if(listen(sd,10) < 0){
		perror("listen");
		exit(3);
	}
	return sd;
}	
int main(int argc,const char*argv[]){
	if(argc!=3){
		printf("usage:%s [ip] [port]\n");
		return 4;
	}
	int listen_sock = start_up()
	return 0;
}
