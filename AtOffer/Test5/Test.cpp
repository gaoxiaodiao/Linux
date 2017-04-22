/**************************************
*文件说明:Test.cpp
*作者:高小调
*创建时间:Sat 22 Apr 2017 03:48:34 PM CST
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
#include<iostream>
#include"2017-04-22.h"
using namespace std;
//创建一个数值连续的链表
Node* CreateList(int start,int end){
	Node *head = new Node(start);
	Node *cur = head;
	for(int i=start+1; i<=end; ++i){
		cur->_next = new Node(i);
		cur = cur->_next;
	}
	return head;
}
//销毁链表
void Destroy(Node** head){
	assert(head);
	Node*prev = NULL;
	Node*cur = *head;
	while(cur!=NULL){
		prev = cur;
		cur = cur->_next;
		delete prev;
	}
	*head = NULL;
}
//打印链表
void Print(Node* head){
	Node* cur = head;
	while(cur!=NULL){
		cout<<cur->_value<<" ";
		cur = cur->_next;
	}
	cout<<endl;
}
void TestPrintR(){
	Node *head = CreateList(1,20);
	Print(head);
	PrintR(head);
	cout<<endl;
	Print(head);
	Destroy(&head);
}
int main(){
	TestPrintR();
	return 0;
}
