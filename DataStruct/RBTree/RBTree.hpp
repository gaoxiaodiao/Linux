/**************************************
*文件说明:红黑树相关声明
*作者:高小调
*创建时间:2017年04月08日 星期六 20时31分19秒
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
#ifndef __RBTREE_H__
#define __RBTREE_H__
#include<iostream>
#include<cassert>
//颜色定义
enum COLOR{
	RED,
	BLACK
};
//节点的定义
template<typename K,typename V>
struct RBTreeNode{
	RBTreeNode *_parent;	
	RBTreeNode *_left;
	RBTreeNode *_right;
	K _key;
	V _value;
	COLOR _color;
	RBTreeNode(const K&,const V&);
};
//红黑树定义
template<typename K,typename V>
class RBTree{
	typedef RBTreeNode<K,V> Node;
public:
	RBTree();								//构造函数
	RBTree(const RBTree & rbt);				//拷贝构造
	RBTree &operator=(const RBTree &rbt);	//赋值运算符重载
	~RBTree();								//析构函数
public:
	std::pair<Node*,bool> Insert(const K& k,const V &v);
	//void Insert(const K& k,const V &v);
	bool CheckIsBalance();
protected:
	void _Destory(Node *root);
	void RotateL(Node *parent);
	void RotateR(Node *parent);
private:
	Node *_root;
};

//红黑树节点构造函数
template<typename K,typename V>
RBTreeNode<K,V>::RBTreeNode(const K& key,const V& value)
	:_parent(0)
	,_left(0)
	,_right(0)
	,_key(key)
	,_value(value)
	,_color(RED){}

//红黑树构造函数
template<typename K,typename V>
RBTree<K,V>::RBTree()
	:_root(0){}

//红黑树析构函数
template<typename K,typename V>
RBTree<K,V>::~RBTree(){
	_Destory(_root);
}

//释放整个树
template<typename K,typename V>
void RBTree<K,V>::_Destory(RBTree::Node *root){
	if(root==0){
		return ;
	}
	_Destory(root->_left);
	_Destory(root->_right);
	delete root;
}

//插入
template<typename K,typename V>
std::pair<typename RBTree<K,V>::Node*,bool> RBTree<K,V>::Insert(const K&key,const V &value){
	if(_root==NULL){
		_root = new Node(key,value);
		_root->_color = BLACK;
		return std::make_pair(_root,true);
	}
	//找插入位置
	Node *parent = NULL;
	Node *cur = _root;
	while(cur!=NULL){
		if(cur->_key > key){
			parent = cur;
			cur = cur->_left;
		}else if(cur->_key < key){
			parent = cur;
			cur = cur->_right;
		}else{
			return std::make_pair(parent,false);
		}
	}
	//插入数据
	cur = new Node(key,value);
	if(parent->_key > key){
		parent->_left = cur;
	}else{
		parent->_right = cur;
	}
	cur->_parent = parent;
	Node *ret = cur;
	//变色处理
	while(parent!=NULL && parent->_color == RED){
		Node *grandfather = parent->_parent;
		if(grandfather->_left == parent){
			Node *uncle = grandfather->_right;
			if(uncle!=NULL && uncle->_color == RED){
				//第一种情况,变色处理后,继续向上调整
				uncle->_color = parent->_color = BLACK;
				grandfather->_color = RED;
				//继续向上调整
				cur = grandfather;
				parent = cur->_parent;
			}else{
				if(cur!=parent->_left){
					//第三种情况,左旋,变成第二种情况
					RotateL(parent);
					//cur与parent交换(重要!!!)
					std::swap(cur,parent);
				}else{
					//第二钟情况,右旋，处理完成后结束变色
					RotateR(grandfather);
					parent->_color = BLACK;
					grandfather->_color = RED;
					break;	//重要!!!
				}
			}
		}else{
			Node *uncle = grandfather->_left;
			if(uncle!=NULL && uncle->_color == RED){
				//第一种情况,变色处理后,继续向上调整
				parent->_color = uncle->_color = BLACK;
				grandfather->_color = RED;
				cur = grandfather;
				parent = cur->_parent;
			}else{
				//第三种情况,右旋,变成第二种情况
				if(cur!=parent->_right){
					RotateR(parent);
					std::swap(cur,parent);	//重要!!!
				}else{
					//第二种情况,左旋,结束变色
					RotateL(grandfather);
					parent->_color = BLACK;
					grandfather->_color = RED;
					break;	//重要!!!
				}
			}
		}
	}
	_root->_color = BLACK;
	return std::make_pair(ret,true);
}
template<typename K,typename V>
void RBTree<K,V>::RotateL(Node *parent){
	Node *subR = parent->_right;
	Node *subRL = subR->_left;

	parent->_right = subRL;
	if(subRL!=NULL){
		subRL->_parent = parent;
	}

	Node *pparent = parent->_parent;
	if(pparent==NULL){
		_root = subR;
		subR->_parent = NULL;
	}else{
		if(pparent->_left == parent){
			pparent->_left = subR;
		}else{
			pparent->_right = subR;
		}
		subR->_parent = pparent;
	}

	subR->_left = parent;
	parent->_parent = subR;
}

template<typename K,typename V>
void RBTree<K,V>::RotateR(Node *parent){
	Node *subL = parent->_left;
	Node *subLR = subL->_right;

	parent->_left = subLR;
	if(subLR!=NULL){
		subLR->_parent = parent;
	}

	Node *pparent = parent->_parent;
	if(pparent==NULL){
		_root = subL;
		_root->_parent = NULL;
	}else{
		if(pparent->_left==parent){
			pparent->_left = subL;
		}else{
			pparent->_right = subL;
		}
		subL->_parent = pparent;
	}

	subL->_right = parent;
	parent->_parent = subL;
}
#endif
