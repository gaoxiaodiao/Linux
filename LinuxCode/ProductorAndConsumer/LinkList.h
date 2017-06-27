////////////////////////////////////
//文件说明:LinkList.h
//作者:高小调
//创建时间:2017年06月27日 星期二 14时57分27秒
//开发环境:Kali Linux/g++ v6.3.0
////////////////////////////////////
#include<assert.h>
#include<stdlib.h>
#include<stdio.h>
//链表节点
typedef struct LinkListNode{
	int val;
	struct inkListNode *next;
}Node,*pNode,**ppNode;

//初始化链表
void InitLinkList(ppNode head){
	assert(head);
	*head = NULL;
}
//判断链表是否为空
int IsEmpty(pNode head){
	return head==NULL;
}
//申请新节点
pNode BuyNewNode(int val){
	pNode ret = (pNode)malloc(sizeof(Node));
	ret->val = val;
	ret->next = NULL;
	return ret;
}
//头插
void PushFront(ppNode head,int val){
	assert(head);
	if(*head==NULL){
		*head = BuyNewNode(val);
		return ;
	}
	pNode newNode = BuyNewNode(val);
	newNode->next = *head;
	*head = newNode;
}
//头删
void PopFront(ppNode head,int *val){
	assert(head);
	if((*head) == NULL){
		return ;
	}
	if((*head)->next == NULL){
		*val = (*head)->val;
		free(*head);
		*head = NULL;
		return ;
	}
	pNode del = *head;
	*head = del->next;
	*val = del->val;
	free(del);
}
//销毁链表
void Destory(ppNode head){
	assert(head);
	pNode cur = *head;
	pNode del = NULL;
	while(cur!=NULL){
		del = cur;
		cur = cur->next;
		free(del);
	}
	*head = NULL;
}
//打印链表
void PrintLinkList(pNode head){
	pNode cur = head;
	while(cur!=NULL){
		printf("%d ",cur->val);
		cur = cur->next;
	}
	printf("\n");
}
