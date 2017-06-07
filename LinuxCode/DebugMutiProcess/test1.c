////////////////////////////////////
//文件说明:test.c
//作者:高小调
//创建时间:2017年06月06日 星期二 18时06分53秒
//开发环境:Kali Linux/g++ v6.3.0
////////////////////////////////////
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
int main(){
	pid_t pid = fork();
	if(pid<0){
		perror("fork");
		return 1;
	}else if(pid>0){
		printf("i am father!pid=%d\n",getpid());
		printf("i am father!pid=%d\n",getpid());
		printf("i am father!pid=%d\n",getpid());
		printf("i am father!pid=%d\n",getpid());
		printf("i am father!pid=%d\n",getpid());
		printf("i am father!pid=%d\n",getpid());
		printf("i am father!pid=%d\n",getpid());
		printf("i am father!pid=%d\n",getpid());
		printf("i am father!pid=%d\n",getpid());
		printf("i am father!pid=%d\n",getpid());
		wait(NULL);
	}else{
		printf("i am child,pid=%d\n",getpid());
		printf("i am child,pid=%d\n",getpid());
		printf("i am child,pid=%d\n",getpid());
		printf("i am child,pid=%d\n",getpid());
		printf("i am child,pid=%d\n",getpid());
		printf("i am child,pid=%d\n",getpid());
		printf("i am child,pid=%d\n",getpid());
		printf("i am child,pid=%d\n",getpid());
		printf("i am child,pid=%d\n",getpid());
		printf("i am child,pid=%d\n",getpid());
	}
	return 0;
}
