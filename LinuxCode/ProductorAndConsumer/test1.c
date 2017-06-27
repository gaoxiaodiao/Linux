////////////////////////////////////
//文件说明:test.c
//作者:高小调
//创建时间:2017年06月27日 星期二 14时56分13秒
//开发环境:Kali Linux/g++ v6.3.0
////////////////////////////////////
#include<stdio.h>
#include<pthread.h>
#include"LinkList.h"
//互斥锁
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
//条件变量
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
//测试链表
void TestLinkList(){
	pNode head;
	InitLinkList(&head);
	int tmp;
	for(int i=0; i<10; ++i){
		PushFront(&head,i);
		PrintLinkList(head);
	}
	for(int i=0; i<10; ++i){
		PopFront(&head,&tmp);
		PrintLinkList(head);
	}
}
pNode head;
//生产者:每次向头节点插入数据
void *Productor(void*arg){
	int val = 0;
	while(1){
		//互斥锁加锁:确保生产时不会消费,消费时不会生产
		pthread_mutex_lock(&lock);
		val = rand()%100;
		PushFront(&head,val);
		printf("Productor push %d\n",val);
		//互斥锁解锁
		pthread_mutex_unlock(&lock);
		//条件变量,生产完成之后向消费者发出信号消费
		pthread_cond_signal(&cond);
		sleep(1);
	}
}
//消费者:每次将头节点数据取出
void *Consumer(void*arg){
	int val = 0;
	while(1){
		//互斥锁
		pthread_mutex_lock(&lock);
		while(head==NULL){
			//链表中没数据,阻塞等待生产者发消费信号
			printf("wait for data\n");
			pthread_cond_wait(&cond,&lock);
		}
		PopFront(&head,&val);
		printf("Consumer pop %d\n",val);
		pthread_mutex_unlock(&lock);
		sleep(1);
	}
}
int main(){
	InitLinkList(&head);
	pthread_t cid1,cid2;
	pthread_create(&cid1,NULL,Productor,NULL);
	pthread_create(&cid2,NULL,Consumer,NULL);
	pthread_join(&cid1,NULL);
	pthread_join(&cid2,NULL);
	
	return 0;
}
