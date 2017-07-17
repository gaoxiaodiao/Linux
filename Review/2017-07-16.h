/**************************************
*文件说明:2017-07-16.h
*作者:高小调
*创建时间:2017年07月16日 星期日 20时21分35秒
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
#include"LinkList.h"
#include"2017-07-15.h"
Node_p IsIntersect(Node_p head1,Node_p head2){
	if(head1==NULL || head2==NULL){
		return NULL;
	}
	Node_p 
	Node_p cur1 = head1;
	Node_p cur2 = head2;
	Node_p tail1 = NULL;
	Node_p tail2 = NULL;
	int len1 = 0;
	int len2 = 0;
	while(cur1!=NULL&&cur2!=NULL){
		len1++;
		len2++;
		tail1 = cur1;
		tail2 = cur2;
		cur1 = cur1->next;
		cur2 = cur2->next;
	}
	while(cur1!=NULL){
		len1++;
		tail1 = cur1;
		cur1 = cur1->next;
	}
	while(cur2!=NULL){
		len2++;
		tail2 = cur2;
		cur2 = cur2->next;
	}
	if(tail1!=tail2){
		//两个链表没有相交
		return NULL;
	}
	cur1 = head1;
	cur2 = head2;
	if(len1 > len2){
		int sub = len1-len2;
		while(sub--){
			cur1 = cur1->next;
		}
	}else{
		int sub = len2-len1;
		while(sub--){
			cur2 = cur2->next;
		}
	}
	while(cur1!=cur2){
		cur1 = cur1->next;
		cur2 = cur2->next;
	}
	return cur1;
}
void Test4(){
	Node_p head1 = CreateLinkList(1,10,2);
	Node_p head2 = CreateLinkList(10,18,2);
	PrintLinkList(head1);
	PrintLinkList(head2);
	Node_p point = Find(head1,9);
	point->next = Find(head2,14);
	cout<<"交点为:"<<IsIntersect(head1,head2)->val<<endl;

}
