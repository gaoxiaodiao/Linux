////////////////////////////////////
//文件说明:链表相关声明及实现
//作者:高小调
//创建时间:2017年06月01日 星期四 18时57分47秒
//开发环境:Kali Linux/g++ v6.3.0
////////////////////////////////////
#ifndef __LINKLIST_H__
#define __LINKLIST_H__
#include<stdlib.h>
#include<stdio.h>
typedef struct Node{
	int value;
	struct Node* next;
}Node_t,*Node_p,**Node_pp;

void InitList(Node_pp head){
	*head = BuyNode(0);
}

static Node_p BuyNode(int data){
	Node_p ret = (Node_p)malloc(sizeof(Node_t));
	if(ret==NULL){
		perror("malloc");
		exit(-1);
	}
	ret->value = data;
	ret->next = NULL;
	return ret;
}

void PushFront(Node_p head,int data){
	Node_p Node = BuyNode(data);
	Node->next = head->next;
	head->next = Node;
}

int IsEmpty(Node_p head){
	return head->next==NULL?0:1;
}

void PopFront(Node_p head,int *data){
	if(!IsEmpty(head)){
		Node_p del = head->next;
		head->next = del->next;
		*data = del->value;
		free(del);
	}
}

void Destroy(Node_pp head){
	int data = 0;
	while(!IsEmpty(*head)){
		PopFront(head,data);
	}
	free(*head);
	*head = NULL;
}

void ShowList(Node_p head){
	Node_p cur = head;
	while(cur!=NULL){
		printf("%d->",cur->value);
		cur = cur->next;
	}
	printf("\n");
}

#endif
