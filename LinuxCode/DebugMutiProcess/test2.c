////////////////////////////////////
//文件说明:test2.c
//作者:高小调
//创建时间:2017年06月07日 星期三 09时22分43秒
//开发环境:Kali Linux/g++ v6.3.0
////////////////////////////////////
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
void *prog1(void *s){
	while(1){
		printf("i am prog1 \n");
		sleep(5);
	}
}
void* prog2(void*s){
	while(1){
		printf("i am prog2 \n");
		sleep(5);
	}
}
int main(){
	pthread_t id1,id2;
	pthread_create(&id1,NULL,prog1,NULL);
	pthread_create(&id2,NULL,prog2,NULL);
	while(1){
		printf("i am main thread\n");
		sleep(5);
	}
	pthread_join(id1,NULL);
	pthread_join(id2,NULL);
	return 0;
}
