////////////////////////////////////
//文件说明:LinkList.h
//作者:高小调
//创建时间:2017年06月14日 星期三 08时10分45秒
//开发环境:Kali Linux/g++ v6.3.0
////////////////////////////////////
#ifndef __LINKLIST_H__
#define __LINKLIST_H__
#include<iostream>
#include<cassert>
using std::cout;
using std::endl;
using std::exit;
using std::swap;
//链表节点
typedef struct LinkListNode{
	int val;
	LinkListNode* sibling;
	LinkListNode* next;

	LinkListNode(int value)
		:val(value)
		,sibling(NULL)
		,next(NULL){}

}Node_t,*Node_p,**Node_pp;

void PrintLinkList(Node_p head){
	Node_p cur = head;
	int count = 30;
	while(cur!=NULL&&count--){
		cout<<cur->val<<" ";
		cur = cur->next;
	}
	cout<<endl;
}

Node_p FindNode(Node_p head,int value){
	assert(head);

	Node_p cur = head;
	while(cur!=NULL){
		if(cur->val == value){
			return cur;
		}
		cur = cur->next;
	}
	return NULL;
}

Node_p CreateMutiLinkList(){
	Node_p head = new Node_t(0);
	Node_p cur = head;
	for(int i=1; i<10; i++){
		cur->next = new Node_t(i);
		cur = cur->next;
	}

	for(int i=1; i<10; i+=2){
		FindNode(head,i)->sibling = FindNode(head,i+2);
	}
	return head;
}

void PrintMutiLinkList(Node_p head){
	Node_p cur = head;
	while(cur!=NULL){
		if(cur->sibling==NULL){
			cout<<cur->val<<":"<<"NULL"<<endl;
		}else{
			cout<<cur->val<<":"<<cur->sibling->val<<"("<<(void*)cur->sibling<<")"<<endl;
		}
		cur = cur->next;
	}
}
//复制复杂链表
Node_p CopyMutiLinkList(Node_p head){
	if(head==NULL){
		return NULL;
	}
	
	//拷贝next
	Node_p copyNextCur = head;
	while( copyNextCur!=NULL ){
		Node_p copyNode = new Node_t(copyNextCur->val);

		copyNode->next = copyNextCur->next;
		copyNextCur->next = copyNode;

		copyNextCur = copyNode->next;
	}
	
	//拷贝sibling
	Node_p oriSiblingCur = head;
	Node_p copySiblingCur = head->next;
	while(oriSiblingCur!=NULL&&copySiblingCur!=NULL){
		copySiblingCur->sibling = oriSiblingCur->sibling==NULL?NULL:oriSiblingCur->sibling->next;
		
		oriSiblingCur = copySiblingCur->next;
		if(oriSiblingCur!=NULL)
			copySiblingCur = oriSiblingCur->next;
	}
	
	//分离原链表与复杂链表
	// oriCur   retHead/retCur   cur 
	//    1           1           3  3 5 5 7 7 9 9
	Node_p oriCur = head;
	Node_p retHead = head->next;
	Node_p retCur = retHead;
	Node_p cur = retCur->next;
	for(int i=1; cur!=NULL; ++i){
		if(i%2!=0){
			oriCur->next = cur;
			oriCur = cur;
		}else{
			retCur->next = cur;
			retCur = cur;
		}
		cur = cur->next;
	}
	return retHead;






/*
	Node_p cur = head;
	//拷贝next,放在后面
	while(cur!=NULL){
		Node_p tmp = new Node_t(cur->val);
		tmp->next = cur->next;
		cur->next = tmp;
		cur = tmp->next;
	}
	//拷贝sibling
	Node_p prev = head;			//旧的复杂链表
	cur = head->next;	//新的复杂链表
	while(cur!=NULL&&prev!=NULL){
		cur->sibling = prev->sibling==NULL?NULL:prev->sibling->next;
		prev = prev->next;
		if(prev==NULL){
			break;
		}
		prev = prev->next;

		cur = cur->next;
		if(cur==NULL){
			break;
		}
		cur = cur->next;
	}

	//分离原复杂链表与拷贝复杂链表
	// 1 1 2 2 3 3 4 4 5 5 6 6 7 7 8 8 9 9 
	Node_p retHead = head->next;
	Node_p retCur = retHead;
	Node_p oriCur = head;
	cur = head;
	for(int i=1;cur!=NULL;++i){
		if(i%2==0){
			retCur->next = cur;
			retCur = retCur->next;
		}else{
			oriCur->next = cur->next;
			oriCur = oriCur->next;
		}
		cur = cur->next;
	}
	return retCur;
*/
	return NULL;
}

Node_p HasCircle(Node_p head){
	if(head==NULL){
		return NULL;
	}

	//一个指针走一步,一个指针走两步
	Node_p cur1 = head;
	Node_p cur2 = head;
	do{
		cur1 = cur1->next;
		cur2 = cur2->next;
		if(cur2==NULL){
			break;
		}
		cur2 = cur2->next;
	}while(cur1!=NULL&&cur2!=NULL&&cur1!=cur2);
	
	//环?不存在的!
	if(cur1==NULL || cur2==NULL){
		return NULL;
	}
	
	//找环入口点
	Node_p cur3 = head;
	while(cur1!=cur3){
		cur1 = cur1->next;
		cur3 = cur3->next;
	}

	return cur3;
}

Node_p Intersect(Node_p head1,Node_p head2){
	Node_p entry = HasCircle(head1);
	int length1 = 0;
	int length2 = 0;
	//环什么的,不存在的!
	if(entry==NULL){
		Node_p cur1 = head1;
		Node_p cur2 = head2;
		//求公共长度
		while(cur1!=NULL&&cur2!=NULL){
			cur1 = cur1->next;
			cur2 = cur2->next;
			length1++;
			length2++;
		}
		//求多余长度
		while(cur1!=NULL){
			cur1 = cur1->next;
			length1++;
		}
		while(cur2!=NULL){
			cur2 = cur2->next;
			length2++;
		}
		//根据长度差,求相交点
		int sub = length1-length2;
		if(sub > 0){
			//head1长度 > head2长度,让head1先走sub步
			cur1 = head1;
			while(cur1!=NULL&&sub!=0){
				cur1 = cur1->next;
				sub--;
			}
			//走完多余部分,两个同时走
			cur2 = head2;
			while(cur1!=NULL&&cur2!=NULL&&cur1!=cur2){
				cur1 = cur1->next;
				cur2 = cur2->next;
			}
			//有交点返回交点,无交点返回NULL
			return cur1;
		}
		//head2长度 > head1长度,让head2先走sub步
		cur2 = head2;
		while(cur2!=NULL&&sub!=0){
			cur2 = cur2->next;
			sub++;
		}
		//两者同时走,遇到交点结束
		cur1 = head1;
		while(cur1!=NULL&&cur2!=NULL&&cur1!=cur2){
			cur1 = cur1->next;
			cur2 = cur2->next;
		}
		//存在交点返回位置,不存在返回NULL
		return cur1;
	}

	//有环?很皮!用巧妙的办法解决 
	Node_p next = entry->next;	//保存原有环结构
	entry->next = NULL;			//破坏当前环
	Node_p ret = Intersect(head1,head2);	//递归执行无环找交点
	entry->next = next;			//恢复原有环结构
	return ret==NULL?entry:ret;	//返回结果
}
struct CircleInfo{
	int length;
	Node_p entry;
};

int HasCircle(Node_p head,CircleInfo *in){
	if(head==NULL){
		return 0;
	}

	Node_p cur1 = head;
	Node_p cur2 = head;
	do{
		cur1 = cur1->next;
		cur2 = cur2->next;
		if(cur2==NULL){
			break;
		}
		cur2 = cur2->next;
	}while(cur1!=NULL&&cur2!=NULL&&cur1!=cur2);

	//不存在环
	if(cur1==NULL || cur2==NULL){
		return 0;
	}
	
	int length = 1;
	
	cur2 = cur2->next;
	while(cur1!=cur2){
		cur2 = cur2->next;
		++length;
	}
	
	Node_p entry = head;
	while(entry!=cur1){
		entry = entry->next;
		cur1 = cur1->next;
	}
	struct CircleInfo ret;
	ret.length = length;
	ret.entry = entry;
	*in = ret;
	return 1;
}

Node_p FindLastKNode(Node_p head,int k){
	if(head==NULL){
		return NULL;
	}
	if(k<0){
		Node_p cur = head;
		k = 0-k;
		while(cur!=NULL&&k!=0){
			cur = cur->next;
			--k;
		}
		return cur;
	}
	Node_p cur = head;
	
	while(cur!=NULL&&k!=0){
		cur = cur->next;
		--k;
	}

	if(cur==NULL){
		return NULL;
	}

	while(cur!=NULL){
		head = head->next;
		cur = cur->next;
	}
	return head;
}
Node_p FindMidNode(Node_p head){
	if(head==NULL){
		return NULL;
	}
	Node_p singleNode = head;
	Node_p doubleNode = head;
	while(doubleNode!=NULL&&doubleNode->next!=NULL){
		singleNode = singleNode->next;
		doubleNode = doubleNode->next;
		doubleNode = doubleNode->next;
	}
	return singleNode;
}
//两个都是升序< 1 3 5 7 9  2 4 6 8 10
//两个都是降序> 8 7 6 5 4  5 4 3 2 1
Node_p MergeLinkList(Node_p head1,Node_p head2){
	if(head1 == NULL){
		return head2;
	}
	if(head2 == NULL){
		return head1;
	}
	
	Node_p retHead = head1->val>head2->val?head1:head2;
	Node_p cur1 = retHead==head1?head1->next:head1;
	Node_p cur2 = retHead==head2?head2->next:head2;
	Node_p cur = retHead;
	
	while(cur1!=NULL && cur2!=NULL){
		if(cur1->val > cur2->val){
			cur->next = cur1;
			cur1 = cur1->next;
		}else{
			cur->next = cur2;
			cur2 = cur2->next;
		}
		cur = cur->next;
	}

	cur->next=cur1==NULL?cur2:cur1;
	return retHead;
}

/*
void QuickSort(Node_p head,Node_p tail){
	if(head==NULL|| tail==NULL||head==tail){
		return ;
	}
	Node_p prev = NULL;
	Node_p cur = head;
	Node_p key = tail;
	while(cur!=tail){
		Node_p prev_next = (prev==NULL?head:prev->next);

		if(cur->val > key->val && (prev=prev_next)!=cur){
			swap(cur->val,prev->val);
		}

		cur = cur->next;
	}
	Node_p prev_next = (prev==NULL?head:prev->next);
	swap(prev_next->val,cur->val);

	QuickSort(head,prev);
	QuickSort(prev->next,tail);

}
*/
void BubbleSort(Node_p head){
	bool flag = true;
	Node_p i= head;
	Node_p tail = NULL;	

	while(flag&&i!=NULL){
		flag = false;
		Node_p prev = head;
		Node_p j = head->next;
		while(j!=tail){
			if(prev->val < j->val){
				swap(prev->val,j->val);
				flag = true;
			}
			prev = j;
			j = j->next;
		}
		tail = prev;

		i = i->next;
	}
}

void ReverseLinkList(Node_pp head){
	assert(head);
	if(*head == NULL || (*head)->next == NULL){
		//空链表 或 只有一个节点
		return ;	
	}
	Node_p prev = NULL;
	Node_p cur = *head;
	Node_p next = cur->next;
	while(next=cur->next){
		cur->next = prev;
		prev = cur;
		cur = next;
	}
	cur->next = prev;
	*head = cur;
}

void JosephCircle(Node_pp head,int n){
	Node_p cur = *head;
	//1.构成一个环
	while(cur->next!=NULL){
		cur = cur->next;
	}
	cur->next = *head;

	//2.约瑟夫选择
	while(cur->next!=cur){
		Node_p del = cur;
		for(int i=0; i<n; ++i){
			cur = del;
			del = del->next;
		}
		cur->next = del->next;
		cout<<del->val<<" ";
		delete del;
	}
	cur->next = NULL;
	cout<<cur->val<<endl;

}


void InsertNotHead(Node_pp head,Node_p pos,int value){
	assert(head);
	if(pos == NULL){
		return ;
	}
	Node_p NewNode = new Node_t(value);
	NewNode->next = pos->next;
	pos->next = NewNode;
	swap(pos->val,NewNode->val);
}


void EraseNotTail(Node_pp head,Node_p pos){
	assert(head);
	if(*head==NULL || pos==NULL){
		return ;
	}
	Node_p del = pos->next;
	if(del!=NULL){
		pos->val = del->val;
		pos->next = del->next;
	}else{
		//最后一个节点,无法删除
		cout<<"该算法,不能删除尾节点!"<<endl;
		exit(-1);
	}
	//删除第一个元素,修改head
	if((*head)->next==del){
		*head = pos;
	}
	delete del;
}

void InitLinkList(Node_pp head,int start,int end,int flag=1){
	assert(head);
	if(start < end){
		*head = new Node_t(start);
		Node_p cur = *head;
		for(int i=start+flag; i<=end; i+=flag){
			cur->next = new Node_t(i);
			cur = cur->next;
		}
	}else{
		*head = new Node_t(start);
		Node_p cur = *head;
		for(int i=start-1; i>=end; i-=flag){
			cur->next = new Node_t(i);
			cur = cur->next;
		}
	}
}
/*
void InitLinkList(Node_pp head,int start,int end){
	assert(head);
	*head = new Node_t(start);
	Node_p cur = *head;
	for(int i=start+1; i<=end; ++i){
		cur->next = new Node_t(i);
		cur = cur->next;
	}
}
*/

void InitLinkList(Node_pp head){
	assert(head);
	*head = new Node_t(0);
	Node_p cur = *head;
	for(int i=1; i<10; ++i){
		cur->next = new Node_t(i);
		cur = cur->next;
	}
}
void _ReversePrint(Node_p head){
	if(head==NULL){
		return ;
	}
	_ReversePrint(head->next);
	cout<<head->val<<" ";
}

void ReversePrint(Node_p head){
	_ReversePrint(head);
	cout<<endl;
}

#endif
