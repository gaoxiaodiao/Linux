/**************************************
*文件说明:ZombieProcess.c
*作者:高小调
*创建时间:2017年04月16日 星期日 16时09分12秒
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
//僵尸进程说明:当子进程结束,而父进程没有对子进程进行处理,那么子进程将会处于僵尸状态.
//此刻的僵尸进程,已经将进程地址空间归还给了操作系统,但仍然保留了自己的PCB信息,等待父进程处理.
#include<stdio.h>
#include<unistd.h>
int main(){
	pid_t pid = fork();
	if(pid<=0){
		//child
		printf("child:%d,parent:%d\n",getpid(),getppid());
	}else{
		//parent
		while(1){
			printf("parent:%d,pparent:%d\n",getpid(),getppid());
			sleep(3);
		}
	}
	return 0;
}
