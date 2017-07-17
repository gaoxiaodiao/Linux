////////////////////////////////////
//文件说明:MergeLinkList.cpp
//作者:高小调
//创建时间:2017年07月13日 星期四 17时47分36秒
//开发环境:Kali Linux/g++ v6.3.0
////////////////////////////////////
#include"LinkList.h"
Node_p MergeLinkList(Node_p head1,Node_p head2){
	if(head1==NULL){
		return head2;
	}
	if(head2==NULL){
		return head1;
	}
	Node_p cur1 = head1;
	Node_p cur2 = head2;
	
	//找出两个链表中较小值作为新链表的头节点
	Node_p newHead = NULL;
	if(cur1->val < cur2->val){
		newHead = cur1;
		cur1 = cur1->next;
	}else{
		newHead = cur2;
		cur2 = cur2->next;
	}
	//将两个链表数据交错插入新链表
	Node_p cur = newHead;
	while(cur1!=NULL && cur2!=NULL){
		if(cur1->val < cur2->val){
			cur->next = cur1;
			cur1 = cur1->next;
		}else{
			cur->next = cur2;
			cur2 = cur2->next;
		}
		cur = cur->next;
	}
	//此时,将剩下的链表挂在新链表后面
	if(cur1!=NULL){
		cur->next = cur1;
	}
	if(cur2!=NULL){
		cur->next = cur2;
	}
	return newHead;
}
