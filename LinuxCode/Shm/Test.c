////////////////////////////////////
//文件说明:Test.c
//作者:高小调
//创建时间:2017年06月13日 星期二 14时25分31秒
//开发环境:Kali Linux/g++ v6.3.0
////////////////////////////////////
#include<stdio.h>
#include<sys/wait.h>
#include<string.h>
#include"Common.h"
int main(){
	int iShmId = CreateShm(1024);
	pid_t pid = fork();
	char *buff = AtShm(iShmId);
	if(pid<0){
		perror("fork");
		return 1;
	}else if(pid>0){
		strcpy(buff,"hello child!");
		wait(NULL);
		printf("%s\n",buff);
		DtShm(buff);
		DestoryShm(iShmId);
	}else{
		printf("%s\n",buff);
		strcpy(buff,"hello parent!");
	}
	return 0;
}
