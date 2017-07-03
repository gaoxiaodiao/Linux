////////////////////////////////////
//文件说明:tcp_server.c
//作者:高小调
//创建时间:2017年07月03日 星期一 15时02分31秒
//开发环境:Kali Linux/g++ v6.3.0
////////////////////////////////////
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/wait.h>
#include<pthread.h>
struct info{
	int sock;
	char * ip;
	int port;
};
int start_up(char *_ip,char* _port){
	int sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock < 0){
		perror("socket");
		exit(2);
	}
	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(atoi(_port));
	local.sin_addr.s_addr = inet_addr(_ip);
	if(bind(sock,(struct sockaddr*)&local,sizeof(local)) < 0){
		perror("bind:");
		exit(3);
	}
	if(listen(sock,10) < 0){
		perror("listen:");
		exit(4);
	}
	return sock;
}
//单用户模式
void single_user(int new_sock,char* ip,int port){
	while(1){
		char buff[1024] = {0};
		ssize_t s = read(new_sock,buff,sizeof(buff)-1);
		if(s > 0){
			buff[s-1] = 0;
			printf("%s:%d#%s\n",ip,port,buff);
		}else if(s == 0){	
			printf("%s:%d exited!\n",ip,port);
			close(new_sock);
			break;
		}else{
			perror("read");
			exit(5);
		}
	}
}
//多进程模式
//优点:稳定
//缺点:连接数很大时,需要很多进程,占用系统资源;
//很多进程间进行不必要的切换,造成服务性能差
void mutiprogress(int new_sock,char* ip,int port){
	int pid = fork();
	if(pid==0){
		if(fork()>0){
			exit(0);
		}
		while(1){
			char buff[1024] = {0};
			ssize_t s = read(new_sock,buff,sizeof(buff)-1);
			if(s > 0){
				buff[s-1] = 0;
				printf("%s:%d#%s\n",ip,port,buff);
			}else if(s == 0){
				printf("%s:%d exited!\n",ip,port);
				close(new_sock);
				exit(0);
			}else{
				perror("read");
				exit(5);
			}
		}
	}else{
		wait(NULL);	
	}
}
void* handler(void *arg){
	char * ip = ((struct info*)arg)->ip;
	int sock = ((struct info*) arg)->sock;
   	int port = ((struct info*)arg)->port;
	single_user(sock,ip,port);
	return (void*)0;
}
//多线程模式
//优点:轻量级进程,性能高
//缺点:稳定性不好
void mutipthread(int new_sock,char *ip,int port){
	pthread_t cid;
	struct info a = {new_sock,ip,port};
	pthread_create(&cid,NULL,handler,(void*)&a);
	pthread_detach(cid);
}
int main(int argc,char* argv[]){
	if(argc!=3){
		printf("Usage:./tcp_server [local_ip] [local_port]\n");
		return 0;
	}
	int listen_sock = start_up(argv[1],argv[2]);
	while(1){
		struct sockaddr_in client;
		socklen_t size = sizeof(client);
		int new_sock = accept(listen_sock,(struct sockaddr*)&client,&size);
		int port = ntohs(client.sin_port);
		char* ip = inet_ntoa(client.sin_addr);
		printf("%s:%d connected!\n",ip,port);

		//single_user(new_sock,ip,port);
		//mutiprogress(new_sock,ip,port);
		mutipthread(new_sock,ip,port);

	}
	return 0;
}
