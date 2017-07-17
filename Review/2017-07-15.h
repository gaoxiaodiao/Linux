/**************************************
*文件说明:2017-07-15.h
*作者:高小调
*创建时间:2017年07月15日 星期六 14时34分05秒
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
#include"LinkList.h"
//不带环:实际上走了N/2步,时间复杂度为O(N)
//带环:大于N/2 小于N步,时间复杂度为O(N)
//综上所述,不管带不带环,时间复杂度均为O(N)
Node_p HasCircle(Node_p head){
	if(head==NULL){
		return NULL;
	}
	// head one  two
	//  1    3    5   7  9 12 15 18 21 23 25
	//oneStep先走一步
	Node_p oneStep = head->next;
	if(oneStep==NULL){
		//当前链表只有一个节点
		return NULL;
	}
	//twoStep在oneStep的后面
	Node_p twoStep = oneStep->next;
	//oneStep每次走一步
	//twoStep每次走两步
	while(twoStep!=NULL&&oneStep!=twoStep){
		oneStep = oneStep->next;
		twoStep = twoStep->next;
		if(twoStep!=NULL)
			twoStep = twoStep->next;
	}
	//最终返回twoStep(为NULL或者两节点相遇)
	return twoStep;
}
//求环的入口点,时间复杂度O(N)
Node_p GetEnterance(Node_p head){
	if(head==NULL){
		//空表
		return NULL;
	}
	//获取相交点O(N)
	Node_p point = HasCircle(head);
	if(point == NULL){
		return NULL;
	}
	//从起点开始,与相交点相遇O(N)
	Node_p cur = head;
	while(cur!=point){
		cur = cur->next;
		point = point->next;
	}
	return cur;
}

//求环长度O(N)
int GetCircleLen(Node_p head){
	if(head==NULL){
		return 0;
	}
	Node_p enter = GetEnterance(head);
	if(enter==NULL){
		return 0;
	}
	int length = 1;
	Node_p cur = enter->next;
	while(cur!=enter){
		cur = cur->next;
		length++;
	}
	return length;
}
void Test3(){
	Node_p head = CreateLinkList(1,26,2);	
	//PrintLinkList(head);
	Node_p Node15 = Find(head,15);
	cout<<"Find15"<<endl;
	Node_p Node25 = Find(head,25);
	cout<<"Find25"<<endl;
	Node25->next = Node15;
	if(HasCircle(head)){
		cout<<"有环"<<endl;
	}else{
		cout<<"无环"<<endl;
	}
	cout<<"入口点为:"<<GetEnterance(head)->val<<endl;
	cout<<"环的长度为:"<<GetCircleLen(head)<<endl;
	Node_p head2 = CreateLinkList(1,10,3);
	if(HasCircle(head2)){
		cout<<"有环"<<endl;
	}else{
		cout<<"无环"<<endl;
	}
}
