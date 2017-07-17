////////////////////////////////////
//文件说明:2017-07-14.h
//作者:高小调
//创建时间:2017年07月14日 星期五 10时14分23秒
//开发环境:Kali Linux/g++ v6.3.0
////////////////////////////////////
#include"LinkList.h"
#include<cassert>
Node_p Reverse(Node_p head){
	if(head==NULL || head->next==NULL){
		return head;
	}
//	p c n
//	                  p c n
	//1 2 3 4 5 6 7 8 9 10
	Node_p prev = NULL;
	Node_p cur = head;
	Node_p next = NULL;
	while(next=cur->next){
		cur->next = prev;
		prev = cur;
		cur = next;
	}
	cur->next = prev;
	return cur;
}

Node_p FindLastKNode(Node_p head,int k){
	assert(head && k>0);
	//              k
	//0 1 2 3 4 5 6 7 8 9
	Node_p fast = head;
	Node_p slow = head;
	while(--k){
		fast = fast->next;
	}

	while(fast->next!=NULL){
		fast = fast->next;
		slow = slow->next;
	}
	return slow;
}

void Test2(){
	Node_p head1 = CreateLinkList(1,10,1);
	PrintLinkList(head1);
	head1 = Reverse(head1);
	PrintLinkList(head1);
	Node_p Node3 = FindLastKNode(head1,3);
	cout<<Node3->val<<endl;
}
