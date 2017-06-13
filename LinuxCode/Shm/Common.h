////////////////////////////////////
//文件说明:Common.h
//作者:高小调
//创建时间:2017年06月13日 星期二 14时16分39秒
//开发环境:Kali Linux/g++ v6.3.0
////////////////////////////////////
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/unistd.h>

static const char *PATHNAME = ".";
static const int PROJ_ID = 1;

int CreateShm(int size){
	key_t key = ftok(PATHNAME,PROJ_ID);
	int ret = shmget(key,size,IPC_CREAT|0666);
	if(ret==-1){
		perror("shmget");
		exit(-1);
	}
	return ret;
}

char *AtShm(int id){
	return (char*)shmat(id,NULL,0);
}

int DtShm(char* addr){
	return shmdt(addr);
}

int DestoryShm(int id){
	return shmctl(id,IPC_RMID,NULL);
}
