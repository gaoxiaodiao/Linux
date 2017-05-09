/**************************************
*文件说明:面试题06:重建二叉树
*作者:高小调
*创建时间:2017年05月09日 星期二 07时59分32秒
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
#include<cassert>
#include<stack>
#include<iostream>
using std::cout;
using std::endl;
using std::stack;

typedef struct BinaryTreeNode{
	int _value;
	BinaryTreeNode *_left;
	BinaryTreeNode *_right;

	BinaryTreeNode(int value)
		:_value(value)
		,_left(0)
		,_right(0){}
}Node;

Node *_RebuiltBinaryTree(int *prevOrderStart,int *prevOrderEnd,int *inOrderStart,int *inOrderEnd){
	
	Node *root = NULL;
	if(*prevOrderStart == *prevOrderEnd &&
			*inOrderStart == *inOrderEnd &&
			*prevOrderStart == *inOrderStart){
		root = new Node(*prevOrderStart);
		return root;
	}

	//找根
	int *rootInOrder = inOrderStart;
	while(*prevOrderStart != *rootInOrder &&
			*rootInOrder!=*inOrderEnd){
		++rootInOrder;
	}
	if(*rootInOrder == *inOrderEnd &&
			*rootInOrder!=*prevOrderStart){
		//数据错误
		assert(false);
	}
	root = new Node(*rootInOrder);
	int leftLength = rootInOrder-inOrderStart;
	int rightLength = inOrderEnd - rootInOrder;
	if(leftLength>0){
		//cout<<*(prevOrderStart+1)<<","<<*(prevOrderStart+leftLength)<<" "<<*(inOrderStart)<<","<<*(rootInOrder-1)<<endl;
		root->_left = _RebuiltBinaryTree(prevOrderStart+1,prevOrderStart+leftLength,inOrderStart,rootInOrder-1);
	}
	if(leftLength < prevOrderEnd-prevOrderStart){
		//cout<<*(prevOrderStart+leftLength+1)<<","<<*(prevOrderEnd)<<" "<<*(rootInOrder+1)<<" "<<*(inOrderEnd)<<endl;
		root->_right = _RebuiltBinaryTree(prevOrderStart+leftLength+1,prevOrderEnd,rootInOrder+1,inOrderEnd);
	}
	return root;
}


Node* RebuiltBinaryTree(int*prevorder,int*inorder,size_t size){
	return _RebuiltBinaryTree(prevorder,prevorder+size-1,inorder,inorder+size-1);
}
void PrevOrderNonR(Node *root){
	stack<Node*> s;
	Node *cur = root;
	while(!s.empty() || cur!=NULL){
		while(cur!=NULL){
			s.push(cur);
			cout<<cur->_value<<" ";
			cur = cur->_left;
		}

		Node *top = s.top();
		s.pop();

		cur = top->_right;
	}
	cout<<endl;
}

void PostOrderNonR(Node *root){
	stack<Node*> s;
	Node *cur = root;
	Node *prev = NULL;
	while(!s.empty() || cur!=NULL){
		while(cur!=NULL){
			s.push(cur);
			cur = cur->_left;
		}
		Node *top = s.top();
		if(top->_right==NULL || top->_right == prev){
			prev = top;
			cout<<top->_value<<" ";
			s.pop();
		}else{
			cur = top->_right;
		}
	}
	cout<<endl;
}


void InOrderNonR(Node *root){
	stack<Node*> s;
	Node *cur = root;
	while(!s.empty() || cur!=NULL){
		while(cur!=NULL){
			s.push(cur);
			cur = cur->_left;
		}

		Node *top = s.top();
		cout<<top->_value<<" ";
		s.pop();

		cur = top->_right;
	}
	cout<<endl;
}


