////////////////////////////////////
//文件说明:Server.c
//作者:高小调
//创建时间:2017年06月10日 星期六 11时10分38秒
//开发环境:Kali Linux/g++ v6.3.0
////////////////////////////////////
#include"Common.h"
#include<stdio.h>
#include<pthread.h>
int msgid = 0;
void* Receive(void* arg){
	char buff[1024] = {0};
	ReceiveMessage(msgid,buff,_CLIENT_);
	printf("Client#%s\n",buff);
}

void* Send(void* arg){
	char buff[1024] = {0};
	printf("Server#");
	fflush(stdout);
	ssize_t s = read(1,buff,sizeof(buff));
	buff[s-1] = 0;
	SendMessage(msgid,buff,_SERVER_);
}

int main(){
	key_t key = ftok(PATHNAME,PROJNAME);
	if(key < 0){
		perror("ftok");
		return 1;
	}
	msgid = CreateMessage(key);
	pthread_t c1,c2;
	for(int i=0; i<10; ++i){
		pthread_create(&c1,NULL,Send,NULL);
		pthread_create(&c2,NULL,Receive,NULL);
		pthread_join(c1,NULL);
		pthread_join(c2,NULL);
	}
	DestoryMessage(msgid);
	return 0;
}
