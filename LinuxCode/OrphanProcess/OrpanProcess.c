/**************************************
*文件说明:OrpanProcess.c
*作者:高小调
*创建时间:2017年04月16日 星期日 16时29分03秒
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main(){
	pid_t pid = fork();
	if(pid>0){
		//parent
		printf("current process is parent\n");
		printf("parent:%d,pparent:%d\n",getpid(),getppid());
		sleep(1);
		printf("parent process is dead\n");
	}else{
		//child
		printf("current process is child\n");
		printf("child:%d,parent:%d\n",getpid(),getppid());
		sleep(5);
		printf("child:%d,parent:%d\n",getpid(),getppid());
	}
	return 0;
}
