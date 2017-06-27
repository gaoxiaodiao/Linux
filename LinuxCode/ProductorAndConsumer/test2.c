////////////////////////////////////
//文件说明:test2.c
//作者:高小调
//创建时间:2017年06月27日 星期二 16时29分30秒
//开发环境:Kali Linux/g++ v6.3.0
////////////////////////////////////
#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>
#define SIZE 1024
//环形队列
int arr[SIZE] = {0};
sem_t sem_pro;		//描述环形队列中的空位置
sem_t sem_con;		//描述唤醒队列中的数据
//生产者，只要环形队列有空位,便不断生产
void*productor(void*arg){
	int data = 0;
	int proIndex = 0;
	while(1){
		//有空位便生产,没空位便阻塞等消费者消费
		sem_wait(&sem_pro);
		data = rand()%1234;
		arr[proIndex] = data;
		printf("product done %d\n",data);
		proIndex = (proIndex+1)%SIZE;
		//供消费者消费的数据加1
		sem_post(&sem_con);
	}
}
//消费者,只要环形队列中有数据,就不断消费
void*consumer(void*arg){
	int data = 0;
	int conIndex = 0;
	while(1){
		//环形队列中存在数据则消费,不存在数据则阻塞,直到有数据为止
		sem_wait(&sem_con);
		data = arr[conIndex];
		printf("consume done %d\n",data);
		conIndex = (conIndex+1)%SIZE;
		//最后,消费了一个数据,空位加1
		sem_post(&sem_pro);
	}
} 

int main(){
	pthread_t pro,con;
	sem_init(&sem_pro,0,SIZE-1);		//一开始有很多空位置
	sem_init(&sem_con,0,0);			//但并没有数据

	pthread_create(&pro,NULL,productor,NULL);
	pthread_create(&con,NULL,consumer,NULL);
	pthread_join(pro,NULL);
	pthread_join(con,NULL);

	sem_destroy(&sem_pro);
	sem_destroy(&sem_con);
	return 0;
}
