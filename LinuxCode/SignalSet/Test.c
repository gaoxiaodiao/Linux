////////////////////////////////////
//文件说明:Test.c
//作者:高小调
//创建时间:2017年06月12日 星期一 11时01分24秒
//开发环境:Kali Linux/g++ v6.3.0
////////////////////////////////////
#include"Common.h"
#include<unistd.h>

int main(){
	key_t key = ftok(PATHNAME,PROJ_ID);
	int semid = CreateSem(key,1);
	
	InitSem(semid,0);
	pid_t pid = fork();
	if(pid<0){
		perror("fork");
		return 1;
	}else if(pid==0){
		//child
		while(1){
			P(semid);
			printf("A");
			fflush(stdout);
			sleep(rand()%3);
			V(semid);
		}
	}else{
		//parent
		while(1){
			P(semid);
			printf("B");
			fflush(stdout);
			sleep(rand()%3);
			V(semid);
		}
	}
	return 0;
}
