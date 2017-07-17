///////////////////////////
//文件说明:epoll_server.c
//作者:高小调
//创建时间:2017年07月11日 星期二 12时42分15秒
//开发环境:Kali Linux/g++ v6.3.0
////////////////////////////////////
#include<stdio.h>
#include<sys/epoll.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
//创建监听套接字
int start_up(const char*ip,const char* port){
	//创建套接字
	int sd = socket(AF_INET,SOCK_STREAM,0);
	if(sd < 0){
		perror("socket");
		exit(2);
	}
	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(atoi(port));
	local.sin_addr.s_addr = inet_addr(ip);
	//绑定ip与端口
	if(bind(sd,(struct sockaddr*)&local,sizeof(local)) < 0){
		perror("bind");
		exit(3);
	}
	//设置监听队列
	if(listen(sd,10) < 0){
		perror("listen");
		exit(4);
	}
	return sd;
}

typedef struct epoll_fd{
	int fd;
	char buff[1024];	
}epoll_fd_t,*epoll_fd_p;

//可优化为内存池
epoll_fd_p alloc_new_node(int _fd){
	epoll_fd_p ret = (epoll_fd_p)malloc(sizeof(epoll_fd_t));
	ret.fd = _fd;
	ret.buff = 0;
	return ret;
}

void set_noblock(int fd){
	int fl = fcntl(fd,F_GETFL);
	if(fl < 0){
		perror("fcntl");
		exit(10);
	}
	if(fcntl(fd,F_SETFL,fl|NONBLOCK) < 0){
		perror("fcntl");
		exit(11);
	}
}

int main(int argc,const char*argv[]){
	if(argc!=3){
		printf("usage:%s [ip] [port]\n",argv[0]);
		return 1;
	}
	//创建监听套接字
	int listen_sock = start_up(argv[1],argv[2]);
	set_noblock(listen_sock);		//设置listen_sock为非阻塞.                                        
	//创建epoll模型
	int epfd = epoll_create(256);
	if(epfd < 0){
		perror("epoll_create");
		return 5;
	}
	//将listen_sock加入epoll模型中
	struct epoll_event ev;
	ev.events = EPOLLIN;
	ev.data.fd = listen_sock;
	if(epoll_ctl(epfd,EPOLL_CTL_ADD,listen_sock,&ev) < 0){
		perror("epoll_ctl");
		return 6;
	}
	//服务器主要逻辑
	while(1){
		struct epoll_event evs[255];
		//获取当前就绪事件
		int ready_num = epoll_wait(epfd,evs,255,-1);
		switch(ready_num){
			case 0:
				//time out
				break;
			case -1:
				perror("epoll_wait");
				return 7;
			default:
				//处理就绪事件
				for(int i=0; i<ready_num; ++i){
					int fd = evs[i].data.fd;
					int event = evs[i].events;
					if(fd == listen_sock && (event&EPOLLIN)){
						//listen_sock就绪
						struct sockaddr_in client;
						socklen_t len = sizeof(client);
						int new_sock = accept(fd,(struct sockaddr*)&client,&len);
						if(new_sock < 0){
							perror("accept");
							return 8;
						}
						printf("get a new client [%s:%d]\n",\
								inet_ntoa(client.sin_addr),\
								ntohs(client.sin_port));
						//将新套接字加入epoll模型,关注其读事件
						ev.events = EPOLLIN;
						ev.data.fd = new_sock;
						epoll_ctl(epfd,EPOLL_CTL_ADD,new_sock,&ev);
					}else if(fd!=listen_sock && (event&EPOLLIN)){
						//其它读事件就绪（假设其数据小于1024）
						char buff[1024];
						ssize_t s = read(fd,buff,sizeof(buff)-1);
						if(s > 0){
							//接受到客户端的数据,打印
							buff[s] = 0;
							printf("%s",buff);
							//关注其写事件
							ev.events = EPOLLOUT;
							ev.data.fd = fd;
							epoll_ctl(epfd,EPOLL_CTL_MOD,fd,&ev);
						}else if(s == 0){
							//客户端断开链接
							close(fd);
							epoll_ctl(epfd,EPOLL_CTL_DEL,fd,NULL);
						}else{
							perror("read");
							return 9;
						}
					}else if(fd!=listen_sock && (event & EPOLLOUT)){
						//其它写事件就绪
						const char* data = "HTTP/1.1 200 OK\r\n<html><p>Hello!<p><html>";
						write(fd,data,strlen(data));
						close(fd);
						epoll_ctl(epfd,EPOLL_CTL_DEL,fd,NULL);
					}else{
						//其它事件就绪
					}
				}
				break;
		}
	}
	return 0;
}
