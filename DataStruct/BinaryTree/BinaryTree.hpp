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
	Node* Find();								//查节点
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
#endif
