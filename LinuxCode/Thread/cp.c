////////////////////////////////////
//文件说明:生产者-消费者模型
//作者:高小调
//创建时间:2017年06月01日 星期四 18时54分34秒
//开发环境:Kali Linux/g++ v6.3.0
////////////////////////////////////
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include"LinkList.h"
Node_p head = NULL;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond =  PTHREAD_COND_INITIALIZER;

void *Consumer(void* s){
	int data = 0;
	while(1){
		pthread_mutex_lock(&lock);
		if(IsEmpty(head)){
			printf("consumer is waiting...\n");
			pthread_cond_wait(&cond,&lock);
		}else{
			PopFront(head,&data);
			printf("consumer get >>> %d\n",data);
		}
		pthread_mutex_unlock(&lock);
	}
}

void* Producer(void* s){
	while(1){		
		pthread_mutex_lock(&lock);
		int data = rand()%123;
		PushFront(head,data);
		printf("producer put >>> %d\n",data);
		pthread_cond_signal(&cond);
		sleep(1);
		pthread_mutex_unlock(&lock);
	}
}
void TestList(){
	int data = 0;
	InitList(&head);
	for(int i=0; i<10; ++i){
		PushFront(head,i);
		ShowList(head);
	}
	for(int i=0; i<10; ++i){
		PopFront(head,&data);
		ShowList(head);
	}
	Destroy(&head);

}
int main(){
	pthread_mutex_init(&lock,NULL);
	pthread_t c1,c2;	
	InitList(&head);
	pthread_create(&c2,NULL,Producer,NULL);
	pthread_create(&c1,NULL,Consumer,NULL);
	pthread_join(c1,NULL);
	pthread_join(c2,NULL);
	Destroy(&head);
	pthread_mutex_destroy(&lock);
	return 0;
}
