////////////////////////////////////
//文件说明:LinkList.h
//作者:高小调
//创建时间:2017年07月13日 星期四 17时47分56秒
//开发环境:Kali Linux/g++ v6.3.0
////////////////////////////////////
#pragma once
#include<iostream>
using std::cout;
using std::endl;
typedef struct LinkListNode{
	int val;
	LinkListNode* next;
	LinkListNode(int v)
		:val(v)
		,next(NULL){}
}Node_t,*Node_p;
Node_p Find(Node_p head,int val){
	Node_p cur = head;
	while(cur!=NULL){
		if(cur->val == val){
			return cur;
		}
		cur = cur->next;
	}
	return NULL;
}
Node_p CreateLinkList(int left,int right,int gap){
	if(left>right){
		gap = 0-gap;
		int tmp = left;
		left = right;
		right = tmp;
	}
	Node_p head = new Node_t(left);
	Node_p cur = head;
	for(int i=left+gap; i<=right; i+=gap){
		cur->next = new Node_t(i);
		cur = cur->next;
	}
	return head;
}

void PrintLinkList(Node_p head){
	while(head!=NULL){
		cout<<head->val<<" ";
		head = head->next;
	}
	cout<<endl;
}

