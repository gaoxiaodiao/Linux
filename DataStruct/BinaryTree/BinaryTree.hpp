////////////////////////////////////
//文件说明:BinaryTree.hpp
//作者:高小调
//创建时间:2017年06月19日 星期一 08时31分02秒
//开发环境:Kali Linux/g++ v6.3.0
////////////////////////////////////
#pragma once
#include<iostream>
#include<stack>
#include<queue>
#include<stdlib.h>
using std::queue;
using std::stack;
using std::cout;
using std::endl;
//二叉树节点定义
typedef struct BinaryTreeNode{
	int val;
	BinaryTreeNode *left;
	BinaryTreeNode *right;
	BinaryTreeNode(int value)
		:val(value)
		,left(NULL)
		,right(NULL){}
}Node_t,*Node_p,**Node_pp;


void _BecomeLinkList(Node_p root,Node_p &prev){
	if(root==NULL){
		return ;
	}
		
	_BecomeLinkList(root->left,prev);
	
	root->left = prev;
	if(prev!=NULL){
		prev->right = root;
	}
	prev = root;
	_BecomeLinkList(root->right,prev);

}

Node_p BecomeLinkList(Node_p root){
	Node_p prev = NULL;
	Node_p cur = root;
	while(cur->left!=NULL){
		cur = cur->left;
	}
	_BecomeLinkList(root,prev);
	return cur;
}

void GetTreeMirror(Node_p root){
	if(root==NULL){
		return ;
	}
	GetTreeMirror(root->left);
	GetTreeMirror(root->right);
	std::swap(root->left,root->right);
}

int _GetMaxDistance(Node_p root,int &max){
	if(root==NULL){
		return 0;
	}
	int left = _GetMaxDistance(root->left,max);
	int right = _GetMaxDistance(root->right,max);
	int tmp = left+right;
	if(max < tmp){
		max = tmp;
	}
	return left>right?left+1:right+1;
}

int GetMaxDistance(Node_p root){
	int max = 0;
	_GetMaxDistance(root,max);
	return max;
}

bool IsCompletlyTree(Node_p root){
	queue<Node_p> q;
	if(root!=NULL){
		q.push(root);
	}
	bool flag = true;
	while(!q.empty()){
		Node_p top = q.front();
		
		if(top->left == NULL){
			flag = false;
		}else{
			if(flag == false){
				return false;
			}
			q.push(top->left);
		}

		if(top->right == NULL){
			flag = false;
		}else{
			if(flag == false){
				return false;
			}
			q.push(top->right);
		}

		q.pop();
	}
	return true;
}

Node_p rebuildBinaryTree(int *prevStart,int *prevEnd,int *inStart,int *inEnd){
	Node_p root = NULL;
	if( *prevStart==*prevEnd && *inStart==*inEnd && *prevStart==*inEnd ){
		root = new Node_t(*prevStart);
		return root;
	}

	int *rootIn = inStart;
	while(rootIn!=inEnd && *rootIn!=*prevStart){
		rootIn++;
	}
	if(rootIn == inEnd && *rootIn!=*prevStart){
		cout<<"参数错误!"<<endl;
		abort();
	}

	root = new Node_t(*prevStart);
	int leftLength = rootIn - inStart;
	
	if(leftLength > 0){
		root->left = rebuildBinaryTree(prevStart+1,prevStart+leftLength,inStart,inStart+leftLength-1);
	}

	if(inEnd - rootIn > 0){
		root->right = rebuildBinaryTree(prevStart+leftLength+1,prevEnd,rootIn+1,inEnd);
	}

	return root;
}


//查找节点是否在树中,找到返回true,否则返回false
bool FindNode(Node_p root,Node_p pos){
	if(root==NULL){
		return false;
	}
	if(root == pos){
		return true;
	}
	if(FindNode(root->left,pos)){
		return true;
	}
	if(FindNode(root->right,pos)){
		return true;
	}
	return false;
}
Node_p GetCommonAncestor(Node_p root,Node_p node1,Node_p node2,float flag){
	if(root==NULL){
		return NULL;
	}
}
Node_p GetCommonAncestor(Node_p root,Node_p node1,Node_p node2,int flag){
	if(root==NULL){
		return NULL;
	}

	bool node1InLeft = FindNode(root->left,node1);
	bool node1InRight = !node1InLeft;
	bool node2InLeft = FindNode(root->left,node2);
	bool node2InRight = !node2InLeft;
	if((node1InLeft && node2InRight) || (node2InLeft&&node1InRight)){
		return root;
	}else if(node1InLeft && node2InLeft){
		return GetCommonAncestor(root->left,node1,node2,flag);
	}else{
		return GetCommonAncestor(root->right,node1,node2,flag);
	}
	return NULL;
}


Node_p FindNode(Node_p root,int value){
	if(root==NULL){
		return NULL;
	}
	if(root->val==value){
		return root;
	}
	Node_p ret = FindNode(root->left,value);
	if(ret!=NULL){
		return ret;
	}
	ret = FindNode(root->right,value);
	if(ret!=NULL){
		return ret;
	}
	return NULL;
}


bool FindPath(Node_p root,Node_p node,stack<Node_p> & s){
	if(root==NULL || node == NULL){
		return false;
	}
	s.push(root);
	if(root==node){
		return true;
	}
	if(FindPath(root->left,node,s)){
		return true;
	}
	if(FindPath(root->right,node,s)){
		return true;
	}
	s.pop();
	return false;
}

Node_p GetCommonAncestor(Node_p root,Node_p node1,Node_p node2){
	if(root==NULL || node1==NULL || node2==NULL){
		return NULL;
	}
	stack<Node_p> path1,path2;
	bool path1IsFind = FindPath(root,node1,path1); 
	bool path2IsFind =FindPath(root,node2,path2);
	cout<<"path1:"<<path1IsFind<<endl;
	cout<<"path2:"<<path2IsFind<<endl;
	if( path1IsFind && path2IsFind){ 
		int size1 = path1.size();
		int size2 = path2.size();
		while(!path1.empty()&&size1>size2){
			cout<<path1.top()->val<<" ";
			path1.pop();
			size1--;
		}
		while(!path2.empty()&&size2>size1){
			cout<<path2.top()->val<<" ";
			path2.pop();
			size2--;
		}
		while(!path1.empty()&&!path2.empty()&&path1.top()!=path2.top()){
			path1.pop();
			path2.pop();
		}
		if(path1.empty() || path2.empty()){
			return NULL;
		}
		return path1.top();
	}
	return NULL;
}

void _GetKNode(Node_p root,int k,int &num){
	if(root==NULL){
		return ;
	}
	if(k==1){
		++num;
		return ;
	}
	_GetKNode(root->left,k-1,num);
	_GetKNode(root->right,k-1,num);
}

int GetKNode(Node_p root,int k){
	int num = 0;
	_GetKNode(root,k,num);
	return num;
}

void _LeafNum(Node_p root,int &num){
	if(root==NULL){
		return ;
	}
	if(root->left==NULL && root->right==NULL){
		num++;
		return ;
	}
	_LeafNum(root->left,num);
	_LeafNum(root->right,num);
}


int LeafNum(Node_p root){
	int ret = 0;
	_LeafNum(root,ret);
	return ret;
}
int Depth(Node_p root){
	if(root==NULL){
		return 0;
	}
	int left = Depth(root->left);
	int right = Depth(root->right);
	return left>right?left+1:right+1;
}

void LevelOrder(Node_p root){
	if(root==NULL){
		return ;
	}
	queue<Node_p> q;
	q.push(root);
	while(!q.empty()){
		Node_p top = q.front();
		cout<<top->val<<" ";
		if(top->left!=NULL)
			q.push(top->left);
		if(top->right!=NULL)
			q.push(top->right);
		q.pop();
	}
	cout<<endl;
}



Node_p _CreateBinaryTree(int arr[],int size,int invalid,int &index){
	if(index>=size || arr[index]==invalid){
		return NULL;
	}
	Node_p root = new Node_t(arr[index]);
	root->left = _CreateBinaryTree(arr,size,invalid,++index);
	root->right = _CreateBinaryTree(arr,size,invalid,++index);
	return root;
}
Node_p CreateBinaryTree(int arr[],int size,int invalid){
	int index = 0;
	return _CreateBinaryTree(arr,size,invalid,index);
}

void _PrevOrder(Node_p root){
	if(root==NULL){
		return ;
	}
	cout<<root->val<<" ";
	_PrevOrder(root->left);
	_PrevOrder(root->right);
}
void PrevOrder(Node_p root){
	_PrevOrder(root);
	cout<<endl;
}

void PrevOrderNonR(Node_p root){
	Node_p cur = root;
	stack<Node_p> s;
	while(!s.empty() || cur!=NULL){
		while(cur!=NULL){
			s.push(cur);
			cout<<cur->val<<" ";
			cur = cur->left;
		}

		Node_p top = s.top();
		s.pop();

		cur = top->right;
	}
	cout<<endl;
}

void _InOrder(Node_p root){
	if(root==NULL){
		return ;
	}
	_InOrder(root->left);
	cout<<root->val<<" ";
	_InOrder(root->right);
}
void InOrder(Node_p root){
	_InOrder(root);
	cout<<endl;
}
void InOrderNonR(Node_p root){
	Node_p cur = root;
	stack<Node_p> s;
	while(!s.empty() || cur!=NULL){
		while(cur!=NULL){
			s.push(cur);
			cur = cur->left;
		}

		Node_p top = s.top();
		cout<<top->val<<" ";
		s.pop();

		cur = top->right;
	}
	cout<<endl;
}

void _PostOrder(Node_p root){
	if(root==NULL){
		return ;
	}
	_PostOrder(root->left);
	_PostOrder(root->right);
	cout<<root->val<<" ";
}
void PostOrder(Node_p root){
	_PostOrder(root);
	cout<<endl;
}
void PostOrderNonR(Node_p root){
	Node_p cur = root;
	stack<Node_p> s;
	Node_p prev = NULL;
	while(!s.empty() || cur!=NULL){
		while(cur!=NULL){
			s.push(cur);
			cur = cur->left;
		}	
		Node_p top = s.top();
		if(top->right == NULL || top->right == prev){
			s.pop();
			cout<<top->val<<" ";
			prev = top;
		}else{
			cur = top->right;
		}
	
	}
	cout<<endl;
}
