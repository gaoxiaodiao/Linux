////////////////////////////////////
//文件说明:Test.cpp
//作者:高小调
//创建时间:2017年06月14日 星期三 08时23分46秒
//开发环境:Kali Linux/g++ v6.3.0
////////////////////////////////////
#include"LinkList.h"
//逆序打印单链表
void Test1(){
	Node_p head = NULL;
	InitLinkList(&head);
	PrintLinkList(head);
	ReversePrint(head);
}
//删除无头链表非尾节点,时间复杂度为O(1)
void Test2(){
	Node_p head = NULL;
	InitLinkList(&head);
	PrintLinkList(head);
	for(int i=1; i<=8; ++i){
		EraseNotTail(&head,FindNode(head,i));
		PrintLinkList(head);
	}
	EraseNotTail(&head,FindNode(head,0));
	PrintLinkList(head);
	EraseNotTail(&head,FindNode(head,9));
	PrintLinkList(head);
}
//无头单链表的非头节点前插入一个节点
void Test3(){
	Node_p head = NULL;
	InitLinkList(&head);
	PrintLinkList(head);
	for(int i=9; i>=0; --i){
		InsertNotHead(&head,head,i);
		PrintLinkList(head);
	}
}
//约瑟夫环
void Test4(){
	Node_p head = NULL;
	InitLinkList(&head,1,8);
	PrintLinkList(head);
	JosephCircle(&head,4);
}
void TestCommon(Node_pp head){
	InitLinkList(head,0,5);
	PrintLinkList(*head);
}
//反转单链表
void Test5(){
	Node_p head = NULL;
	TestCommon(&head);
	ReverseLinkList(&head);
	PrintLinkList(head);
}
//冒泡排序
void Test6(){
	Node_p head = NULL;
	TestCommon(&head);
	BubbleSort(head);
	PrintLinkList(head);
}
/*
//快速排序
void Test7(){
	Node_p head = NULL;
	const int tail = 3;
	InitLinkList(&head,0,tail);
	PrintLinkList(head);
	QuickSort(head,FindNode(head,tail));
	PrintLinkList(head);
}
*/
//合并链表
void Test8(){
	Node_p head1,head2,newHead;
	InitLinkList(&head1,19,0,2);
	InitLinkList(&head2,21,0,3);
	PrintLinkList(head1);
	PrintLinkList(head2);
	newHead = MergeLinkList(head1,head2);
	PrintLinkList(newHead);
}
//获取链表中间元素
void Test9(){
	Node_p head1,head2,head3,head4;
	InitLinkList(&head1,0,3);
	InitLinkList(&head2,3,5);
	InitLinkList(&head3,5,6);
	InitLinkList(&head4,7,15);

	PrintLinkList(head1);	
	Node_p mid = FindMidNode(head1);
	if(mid!=NULL){
		cout<<"mid="<<mid->val<<endl;
	}else{
		cout<<"mid=NULL"<<endl;
	}

	PrintLinkList(head2);
	mid = FindMidNode(head2);
	if(mid!=NULL){
		cout<<"mid="<<mid->val<<endl;
	}else{
		cout<<"mid=NULL"<<endl;
	}

	PrintLinkList(head3);
	mid = FindMidNode(head3);
	if(mid!=NULL){
		cout<<"mid="<<mid->val<<endl;
	}else{
		cout<<"mid=NULL"<<endl;
	}

	PrintLinkList(head4);
	mid = FindMidNode(head4);
	if(mid!=NULL){
		cout<<"mid="<<mid->val<<endl;
	}else{
		cout<<"mid=NULL"<<endl;
	}

}
//寻找倒数第k个结点
void Test10(){
	Node_p head = NULL;
	InitLinkList(&head,0,10,2);
	Node_p lastK = FindLastKNode(head,10);
	PrintLinkList(head);
	cout<<"lastK="<<lastK->val<<endl;
}
//判断单链表是否带环
void Test11(){
	Node_p head = NULL;
	InitLinkList(&head,0,36,3);
	PrintLinkList(head);
	Node_p tail = FindNode(head,36);
	tail->next = FindNode(head,18);
	struct CircleInfo ret;
	if(HasCircle(head,&ret)==1){
		cout<<"该链表带环,环长度为:"<<ret.length<<",环的入口点为:"<<ret.entry->val<<endl;
	}
}
//两链表相交,求交点
void Test12(){
	Node_p head1,head2;
	//0 3 6 9 12 15 18
	InitLinkList(&head1,0,18,3);
	//21 24 27 30 33 36
	InitLinkList(&head2,21,36,3);

	PrintLinkList(head1);
	PrintLinkList(head2);
	Node_p point = Intersect(head1,head2);
	if(point==NULL){
		cout<<"两者无交点"<<endl;
	}else{
		cout<<"两者交点为:"<<point->val<<endl;
	}
	//带环,相交点在环内
	
	Node_p tmp12 = FindNode(head1,12);
	Node_p tmp36 = FindNode(head2,36);
	Node_p tmp18 = FindNode(head1,18);
	Node_p tmp9 = FindNode(head1,9);
	tmp36->next = tmp12;	//相交点为12
	tmp18->next = tmp9;		//环入口为9
	
	point = Intersect(head1,head2);
	if(point==NULL){
		cout<<"两者无交点"<<endl;
	}else{
		cout<<"两者交点为:"<<point->val<<endl;
	}
	Node_p entry1 = HasCircle(head1);	//9
	Node_p entry2 = HasCircle(head2);	//12

	cout<<"entry1="<<entry1->val<<endl;
	cout<<"entry2="<<entry2->val<<endl;


/*
	//带环,相交点在环外
	Node_p tmp6 = FindNode(head1,6);
	Node_p tmp36 = FindNode(head2,36);
	Node_p tmp18 = FindNode(head1,18);
	Node_p tmp9 = FindNode(head1,9);
	tmp36->next = tmp6;	//相交点为6
	tmp18->next = tmp9;	//环入口为9
	
	point = Intersect(head1,head2);
	if(point==NULL){
		cout<<"两者无交点"<<endl;
	}else{
		cout<<"两者交点为:"<<point->val<<endl;
	}
*/
/*	不带环
	FindNode(head1,18)->next = FindNode(head2,21);
	PrintLinkList(head1);
	PrintLinkList(head2);
	point = Intersect(head1,head2);
	if(point==NULL){
		cout<<"两者无交点"<<endl;
	}else{
		cout<<"两者交点为:"<<point->val<<endl;
	}
*/	

}
//复杂链表复制
void Test13(){
	Node_p head = CreateMutiLinkList();
	PrintMutiLinkList(head);
	Node_p copyHead = CopyMutiLinkList(head);
	cout<<endl;
	PrintMutiLinkList(head);
	cout<<endl;
	PrintMutiLinkList(copyHead);
}
int main(){
	Test13();
	//Test12();
	//Test11();
	//Test10();
	//Test9();
	//Test8();
	//Test7();
	//Test6();
	//Test5();
	//Test4();
	//Test3();
	//Test2();
	//Test1();
	return 0;
}
