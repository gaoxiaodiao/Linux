/**************************************
*文件说明:二叉树相关声明及实现
*作者:高小调
*创建时间:2017年04月09日 星期日 18时31分33秒
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
#ifndef __BINARYTREE_H__
#define __BINARYTREE_H__
#define __DEBUG__
#include<iostream>
#include<stack>
#include<queue>
//二叉树节点声明
template<typename T>
struct BinaryTreeNode{
	BinaryTreeNode *_left;
	BinaryTreeNode *_right;
	T _value;
	//构造函数
	BinaryTreeNode(const T &value)
		:_left(NULL)
		,_right(NULL)
		,_value(value){}
};

//二叉树结构声明
template<typename T>
class BinaryTree{
	typedef BinaryTreeNode<T> Node;
public:
	BinaryTree(T*,size_t sz,const T&invalid);		//构造函数
	~BinaryTree();									//析构函数
	void PrevOrder();			//前序遍历
	void PrevOrderNonR();		//前序遍历非递归
	void InOrder();				//中序遍历
	void InOrderNonR();			//中序遍历非递归
	void PostOrder();			//后序遍历
	void PostOrderNonR();		//后序遍历非递归
	void LevelOrder();			//层序遍历
	
	size_t Depth();								//二叉树深度/高度
	size_t GetLeafNodeNum();					//叶子节点个数
	size_t GetKNodeNum();						//第K层叶子节点个数
	Node* Find(const T &);								//查节点是否在树中
	Node* GetCommonAncestralNode(Node*,Node*);	//两个节点最近的公共祖先节点
	//Node* IsBalanceTree();					//判断是否为平衡树
	size_t GetMaxDistance();					//二叉树中最远两节点间的距离
	void ReBuiltTree(int*,int*,size_t);			//根据前序、中序重建二叉树
	bool IsCompleteTree();						//判断是否为完全二叉树
	void GetMirrorTree();						//求二叉树的镜像
	//Node* BecomeList();							//将二叉搜索树转换为双向链表
protected:
	Node *_CreateTree(T*,size_t,const T&,size_t&);	//创建树
	void _Destroy(Node*);							//销毁树
	void _PrevOrder(Node*);							//前序遍历
	void _InOrder(Node *);							//中序遍历
	void _PostOrder(Node*);							//后序遍历
	size_t _Depth(Node*);							//求深度
	void _GetLeafNodeNum(Node*,size_t&);			//求叶子结点个数
	Node* _Find(Node *,const T &);
	bool _FindPath(Node*,Node*,std::stack<Node*>&); 
private:
	BinaryTree &operator=(const BinaryTree&);	//禁止拷贝
	BinaryTree(const BinaryTree&);				//禁止赋值
private:
	Node *_root;
};

//二叉树相关实现

//构造函数
template<typename T>
BinaryTree<T>::BinaryTree(T *arr,size_t sz,const T &invalid){
	size_t index = 0;
	_root = _CreateTree(arr,sz,invalid,index);
}
//创建二叉树
template<typename T>
typename BinaryTree<T>::Node *BinaryTree<T>::_CreateTree(T *arr,size_t sz,const T& invalid,size_t &index){
	if(index<sz && arr[index]!=invalid){
		Node *root = new Node(arr[index]);
		root->_left = _CreateTree(arr,sz,invalid,++index);
		root->_right = _CreateTree(arr,sz,invalid,++index);
		return root;
	}
	return NULL;
}
//析构函数
template<typename T>
BinaryTree<T>::~BinaryTree(){
#ifdef __DEBUG__
	std::cout<<"DEBUG:检查析构:";
#endif
	_Destroy(_root);
#ifdef __DEBUG__
	std::cout<<std::endl;
#endif
}
//销毁二叉树
template<typename T>
void BinaryTree<T>::_Destroy(Node *root){
	if(root==NULL){
		return ;
	}
	_Destroy(root->_left);
	_Destroy(root->_right);
#ifdef __DEBUG__
	std::cout<<root->_value<<" ";
#endif
	delete root;
}

//前序遍历
//时间复杂度O(N)
//平均空间复杂度O(logN) 最坏空间复杂度O(N)
template<typename T>
void BinaryTree<T>::PrevOrder(){
	_PrevOrder(_root);
	std::cout<<std::endl;
}
template<typename T>
void BinaryTree<T>::_PrevOrder(Node *root){
	if(root==NULL){
		return ;
	}
	std::cout<<root->_value<<" ";
	_PrevOrder(root->_left);
	_PrevOrder(root->_right);
}
template<typename T>
void BinaryTree<T>::PrevOrderNonR(){
	std::stack<Node*> s;
	Node *cur = _root;
	while(cur!=NULL || !s.empty()){
		
		while(cur!=NULL){
			s.push(cur);
			std::cout<<cur->_value<<" ";
			cur = cur->_left;
		}
		
		Node *top = s.top();
		s.pop();
		
		cur = top->_right;
	}
	std::cout<<std::endl;
}
//中序遍历
template<typename T>
void BinaryTree<T>::InOrder(){
	_InOrder(_root);
	std::cout<<std::endl;
}
template<typename T>
void BinaryTree<T>::_InOrder(Node *root){
	if(root==NULL){
		return ;
	}
	_InOrder(root->_left);
	std::cout<<root->_value<<" ";
	_InOrder(root->_right);
}
template<typename T>
void BinaryTree<T>::InOrderNonR(){
	std::stack<Node*> s;
	Node *cur = _root;
	
	while(cur!=NULL || !s.empty()){
		
		while(cur!=NULL){
			s.push(cur);
			cur = cur->_left;
		}

		Node *top = s.top();
		s.pop();
		std::cout<<top->_value<<" ";

		cur = top->_right;
	}
	std::cout<<std::endl;
}

//后序遍历
template<typename T>
void BinaryTree<T>::PostOrder(){
	_PostOrder(_root);
	std::cout<<std::endl;
}
template<typename T>
void BinaryTree<T>::_PostOrder(Node *root){
	if(root==NULL){
		return ;
	}
	_PostOrder(root->_left);
	_PostOrder(root->_right);
	std::cout<<root->_value<<" ";
}
template<typename T>
void BinaryTree<T>::PostOrderNonR(){
	std::stack<Node*> s;
	Node* cur = _root;
	Node *prev = NULL;
	while(cur!=NULL || !s.empty()){
		
		while(cur!=NULL){
			s.push(cur);
			cur = cur->_left;
		}

		Node *top = s.top();
		if(top->_right==NULL || top->_right == prev){
			prev = top;
			std::cout<<top->_value<<" ";
			s.pop();
		}else{
			cur = top->_right;
		}

	}
	std::cout<<std::endl;
}

//层序遍历
//时间复杂度O(N)
//空间复杂度O(2^logN)
template<typename T>
void BinaryTree<T>::LevelOrder(){
	std::queue<Node*> q;
	q.push(_root);
	while(!q.empty()){
		Node *front = q.front();
		q.pop();
		if(front!=NULL){
			std::cout<<front->_value<<" ";
			q.push(front->_left);
			q.push(front->_right);
		}
	}
	std::cout<<std::endl;	
}

//求二叉树的高度/深度
//时间复杂度O(N)
//平均空间复杂度O(logN)  最差O(N)
template<typename T>
size_t BinaryTree<T>::Depth(){
	return _Depth(_root);
}
template<typename T>
size_t BinaryTree<T>::_Depth(Node *root){
	if(root==NULL){
		return 0;
	}
	size_t leftD = _Depth(root->_left);
	size_t rightD = _Depth(root->_right);
	return leftD>rightD?leftD+1:rightD+1;
}

//求二叉树的叶子个数
//时间复杂度O(N)
template<typename T>
size_t BinaryTree<T>::GetLeafNodeNum(){
	size_t count = 0;
	_GetLeafNodeNum(_root,count);
	return count;
}
template<typename T>
void BinaryTree<T>::_GetLeafNodeNum(Node *root,size_t &count){
	if(root==NULL){
		return ;
	}
	if(root->_left==NULL&&root->_right==NULL){
		++count;
		return ;
	}
	_GetLeafNodeNum(root->_left,count);
	_GetLeafNodeNum(root->_right,count);
}

//查找某个节点是否在树中
//时间复杂度O(N)
template<typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::Find(const T &value){
	return _Find(_root,value);
}
template<typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::_Find(Node *root,const T &value){
	if(root==NULL){
		return NULL;
	}
	if(root->_value == value){
		return root;
	}
	Node *ret = _Find(root->_left,value);
	if(ret==NULL){
		ret = _Find(root->_right,value);
	}
	return ret;
}

/*
//找两节点公共祖先
//时间复杂度O(N*N)
//空间复杂度O(1)
template<typename T>
typename BinaryTree<T>::Node *BinaryTree<T>::_GetCommonAncestralNode(Node*root,Node *n1,Node *n2){
	if(n1==NULL || n2 == NULL){
		return NULL;
	}

	bool n1InLeft,n1InRight,n2InLeft,n2InRight;
	n1InLeft = _Find(root->_left,n1->_value)==NULL?false:true;
	n1InRight = n1InLeft?false:true;
	n2InLeft = _Find(root->_left,n2->_value)!=NULL?true:false;
	n2InRight = n2InLeft?false:true;

	if((n1InLeft && n2InRight) || (n1InRight && n2InLeft)){
		return root;
	}else if(n1InLeft && n2InLeft){
		return _GetCommonAncestralNode(root->_left,n1,n2);
	}else{
		return _GetCommonAncestralNode(root->_right,n1,n2);
	}

	return NULL;
}
*/

//找两节点公共祖先(优化版)
//时间复杂度O(N)
//平均空间复杂度O(logN)  最差O(N)与树的形态有关(深度)
template<typename T>
typename BinaryTree<T>::Node *BinaryTree<T>::GetCommonAncestralNodeOP(Node *n1,Node *n2){
	std::stack<Node*> s1;
	std::stack<Node*> s2;
	
	//找n1、n2路径分别存放在s1、s2里
	_FindPath(_root,n1,s1);
	_FindPath(_root,n2,s2);

	//删除多余的路径
	while(s1.size() > s2.size()){
		s1.pop();
	}
	while(s2.size() > s1.size()){
		s2.pop();
	}
	
	//找最近公共祖先
	while(s1.top()!=s2.top()){
		s1.pop();
		s2.pop();
	}

	return s1.top();
}

template<typename T>
bool BinaryTree<T>::_FindPath(Node*root,Node *n,std::stack<Node*> &path){
	if(root==NULL || n == NULL){
		return false;
	}
	
	path.push(root);

	if(root == n){
		return true;
	}

	if(_FindPath(root->_left,n,path)){
		return true;
	}

	if(_FindPath(root->_right,n,path)){
		return true;
	}

	path.pop();
	return false;
}



#endif
