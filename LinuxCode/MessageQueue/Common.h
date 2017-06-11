////////////////////////////////////
//文件说明:Common.h
//作者:高小调
//创建时间:2017年06月10日 星期六 10时46分11秒
//开发环境:Kali Linux/g++ v6.3.0
////////////////////////////////////
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>
#include<unistd.h>
#define _SERVER_ 1
#define _CLIENT_ 2
#define PATHNAME "/"
#define PROJNAME 0
typedef struct msgbuf{
	long mtype;
	char mtext[1024];
}msgbuf;

int MessageCommon(key_t key,int flag){
	int ret = 0;
	if((ret=msgget(key,flag))==-1){
		perror("msgget:");
		exit(-1);
	}
	return ret;
}

int CreateMessage(key_t qid){
	return MessageCommon(qid,IPC_CREAT|IPC_EXCL|0666);
}

int GetMessage(key_t qid){
	return MessageCommon(qid,IPC_CREAT);
}

void DestoryMessage(int msgid){
	if(msgctl(msgid,IPC_RMID,NULL) == -1){
		perror("msgctl");
		exit(-4);
	}
}
void SendMessage(int msgid,const char* msg,int who){
	msgbuf buf;
	buf.mtype = who;
	strcpy(buf.mtext,msg);
	if(msgsnd(msgid,&buf,sizeof(buf),0) == -1){
		perror("msgsnd");
		DestoryMessage(msgid);
		exit(-2);
	}
}

void ReceiveMessage(int msgid,char* msg,int who){
	msgbuf buf;
	if(msgrcv(msgid,&buf,sizeof(buf),who,0)==-1){
		perror("msgrcv");
		DestoryMessage(msgid);
		exit(-3);
	}
	strcpy(msg,buf.mtext);
}

