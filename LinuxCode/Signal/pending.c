////////////////////////////////////
//文件说明:pending.c
//作者:高小调
//创建时间:2017年06月28日 星期三 15时15分45秒
//开发环境:Kali Linux/g++ v6.3.0
////////////////////////////////////
#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>
//屏蔽SIGINT
void blockSIGINT(){
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set,SIGINT);
	sigprocmask(SIG_BLOCK,&set,NULL);
}
//恢复SIGINT
void recoverSIGINT(){
	sigset_t set;
	sigemptyset(&set);
	sigprocmask(SIG_SETMASK,&set,NULL);
}
//打印未决表
void printPending(sigset_t *set){
	for(int i=1; i<=31; ++i){
		if(sigismember(set,i)){
			putchar('1');
		}else{
			putchar('0');
		}
	}
	putchar('\n');
}
void handler(int sig){
	printf("the No.%d signal is deliver!\n",sig);
}
int main(){
	signal(SIGINT,handler);
	int count = 5;
	printf("block the SIGINT %ds later!\n",count);
	sigset_t set;
	sigemptyset(&set);
	//先将SIGINT屏蔽掉
	while(1){
		if(count==0){
			blockSIGINT();
			printf("SIGINT has benn blocked!\n");
			break;
		}
		sigpending(&set);
		printPending(&set);
		sleep(1);
		--count;
	}
	//再把它恢复过来
	printf("recover the SIGINT %ds later!\n",10-count);
	while(1){
		if(count==10){
			recoverSIGINT();
			printf("SIGINT has been recovered!\n");
			break;
		}
		//恢复之前,信号被阻塞,因此如果产生SIGINT信号,将会处于未决状态
		sigpending(&set);
		printPending(&set);
		count++;
		sleep(1);
	}
	while(1);
	return 0;
}
