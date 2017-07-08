/**************************************
*文件说明:tcp_server.c
*作者:高小调
*创建时间:2017年07月06日 星期四 16时06分51秒
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
#include<stdio.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/select.h>

int fds[sizeof(fd_set)*8];
#define SIZE sizeof(fds)/sizeof(*fds)

//创建tcp套接字并返回
int start_up(const char* ip,const char* port){
	int sd = socket(AF_INET,SOCK_STREAM,0);
	if(sd < 0){
		perror("socket");
		exit(-1);
	}
	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(atoi(port));
	local.sin_addr.s_addr = inet_addr(ip);
	if(bind(sd,(struct sockaddr*)&local,sizeof(local) ) < 0){
		perror("bind");
		exit(-2);
	}
	
	if(listen(sd,10) < 0){
		perror("listen");
		exit(-3);
	}
	return sd;
}
//初始化文件描述符表fds
void init_fds(int* arr,int n){
	for(int i=1; i<n; ++i){
		arr[i] = -1;
	}
}
//初始化rdfds
void init_rdfds(int *fds,int size,fd_set* rdfds,int *max_fd){
	FD_ZERO(rdfds);
	for(int i=0; i<size; ++i){
		if(fds[i] != -1){
			if(fds[i] > *max_fd){
				*max_fd = fds[i];
			}
			FD_SET(fds[i],rdfds);
		}
	}
}
//将新文件描述符放入文件描述符表中
//成功返回index,失败返回-1
int put_fd_in_fds(int *fds,int size,int fd){
	int i = 0;
	for(; i<size; ++i){
		if(fds[i] == -1){
			break;
		}
	}
	if(i == size){
		return -1;
		close(fd);
	}
	fds[i] = fd;
	return i;
}
int main(int argc,const char* argv[]){
	if(argc!=3){
		printf("usage:%s [ip] [port]\n",argv[0]);
		return 0;
	}
	int listen_sock = start_up(argv[1],argv[2]);
	fds[0] = listen_sock;
	init_fds(fds,SIZE);	
	while(1){
		int max_fd = -1;
		fd_set rdfds;
		init_rdfds(fds,SIZE,&rdfds,&max_fd);
		switch(select(max_fd+1,&rdfds,NULL,NULL,NULL)){
			case 0:
				printf("time out!\n");
				break;
			case -1:
				perror("select");
				break;
			default:{
				//遍历文件描述符表,找已就绪的文件描述符
				for(int i=0; i<SIZE; ++i){
					if(i==0 && FD_ISSET(fds[i],&rdfds)){
						//监听套接字已就绪
						struct sockaddr_in client;
						socklen_t size = sizeof(client);
						int client_sock = accept(fds[0],(struct sockaddr *)&client,&size);
						if(client_sock < 0){
							perror("accept");
							break;
						}
						int index = put_fd_in_fds(fds,SIZE,client_sock);
						printf("%s:%d connected, fd in %d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port),index);
					}else if(i!=0 && FD_ISSET(fds[i],&rdfds)){
						//其它读事件已就绪(假设数据量小于1024)
						char buff[1024] = {0};
						ssize_t s = read(fds[i],buff,sizeof(buff)-1);
						if(s == 0){
							printf("someone is disconneced!\n");
							fds[i] = -1;
							close(fds[i]);
							break;
						}else if(s < 0){
							perror("read");
							break;
						}
						printf("client#%s",buff);
					}
				}
			}
		}
	}	
	return 0;
}
