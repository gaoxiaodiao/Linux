////////////////////////////////////
//文件说明:signal.c
//作者:高小调
//创建时间:2017年06月25日 星期日 09时17分48秒
//开发环境:Kali Linux/g++ v6.3.0
////////////////////////////////////
#include<stdio.h>
#include<signal.h>
#include<unistd.h>
void blockSIGINT(){
	sigset_t set,oset;
	sigemptyset(&set);
	sigaddset(&set,SIGINT);
	sigprocmask(SIG_BLOCK,&set,&oset);
	int count = 5;
	while(1){
		printf("i had blocked the SIGINT,%ds recover later!\n",count);
		sleep(1);
		if(count==0){
			break;
		}
		count--;
	}
	sigprocmask(SIG_SETMASK,&oset,NULL);
	while(1){
		printf("SIGINT has recovered!\n");
		sleep(1);
	}
}
void printSet
int main(){
	blockSIGINT();
	return 0;
}
