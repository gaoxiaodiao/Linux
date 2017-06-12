////////////////////////////////////
//文件说明:Common.h
//作者:高小调
//创建时间:2017年06月12日 星期一 10时40分12秒
//开发环境:Kali Linux/g++ v6.3.0
////////////////////////////////////
#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#define PATHNAME "."
#define PROJ_ID 1
typedef union semun{
	int val;
	struct semid_ds *buf;
	unsigned short  *array;
	struct seminfo *__buf;
}semun_t;
/*
typedef struct sembuf{
	unsigned short sem_num;
	short sem_op;
	short sem_flg;
}sembuf_t;
*/
int CommonSem(key_t key,int num,int flag){
	return semget(key,num,flag);
}

int CreateSem(key_t key,int num){
	return CommonSem(key,num, IPC_CREAT | IPC_EXCL |0666);
}

int GetSem(key_t key,int num){
	return CommonSem(key,num,IPC_CREAT);
}

void InitSem(int id,int which){
	semun_t semum;
	semum.val = 1;
	int ret = semctl(id,which,SETVAL,semum);
	if(ret==-1){
		perror("semctl");
		exit(0);
	}
}


void CommonOP(int id,int flg){
	struct sembuf sembuf;
	sembuf.sem_num = 0;
	sembuf.sem_op = flg;
	sembuf.sem_flg = SEM_UNDO;
	if( semop(id,&sembuf,1) == -1 ){
		perror("semop:");
		exit(0);
	}
}

void P(int id){
	CommonOP(id,-1);
}

void V(int id){
	CommonOP(id,1);
}

