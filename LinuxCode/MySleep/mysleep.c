////////////////////////////////////
//文件说明:mysleep.c
//作者:高小调
//创建时间:2017年06月26日 星期一 15时02分06秒
//开发环境:Kali Linux/g++ v6.3.0
////////////////////////////////////
#include<stdio.h>
#include<signal.h>
#include<unistd.h>
void handler(int sig){
}
int mysleep3(unsigned int scds){
	//捕捉信号
	struct sigaction act,oact;
	act.sa_handler = handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGALRM,&act,&oact);
	
	//屏蔽信号
	sigset_t sem,osem,sussem;
	sigemptyset(&sem);					//初始化
	sigaddset(&sem,SIGALRM);		
	sigprocmask(SIG_BLOCK,&sem,&osem);	//设置阻塞信号

	alarm(scds);
	sussem = osem;
	sigdelset(&sussem,SIGALRM);			//确保SIGALRM信号不会被阻塞
	sigsuspend(&sussem);
	int ret = alarm(0);
	//恢复信号屏蔽字
	sigprocmask(SIG_BLOCK,&osem,NULL);
	//恢复捕捉信号
	sigaction(SIGALRM,&oact,NULL);
	return ret;
}

int mysleep2(unsigned int scds){
	struct sigaction set,oset;
	set.sa_handler = handler;
	sigemptyset(&set.sa_mask);
	set.sa_flags = 0;
	sigaction(SIGALRM,&set,&oset);
	
	int ret = alarm(scds);	//bug
	pause();
	
	sigaction(SIGALRM,&oset,NULL);
	return ret;
}
int mysleep1(unsigned int scds){
	signal(SIGALRM,handler);
	int ret = alarm(scds);
	pause();
	return ret;
}
int main(){
	while(1){
		printf("i came to test mysleep function!\n");
		mysleep3(1);
	}
	return 0;
}
