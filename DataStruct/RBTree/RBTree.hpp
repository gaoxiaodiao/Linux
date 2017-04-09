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
#include<stack>
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
	~RBTree();								//析构函数
private:
	//懒得写这些
	RBTree(const RBTree & rbt);				//禁止拷贝构造
	RBTree &operator=(const RBTree &rbt);	//禁止赋值运算符重载
public:
	std::pair<Node*,bool> Insert(const K& k,const V &v);	//插入元素
	bool CheckIsBalance();									//判断是否平衡
	void InOrderNonR();										//中序遍历非递归
protected:
	void _Destory(Node *root);
	bool _CheckIsBalance(Node *,int,const int);
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
//左旋
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

//右旋
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
//检测该树是否为红黑树
//1.所有路径黑色节点数目相同
//2.不能有连续的红节点
//(以上条件满足,则满足最短路径不超过最长路径的两倍)
template<typename K,typename V>
bool RBTree<K,V>::CheckIsBalance(){
	int leftBlackNum = 0;
	int curBlackNum = 0;
	//记录最左侧黑色节点的数量
	Node *cur = _root;
	while(cur!=NULL){
		if(cur->_color == BLACK){
			++leftBlackNum;
		}
		cur = cur->_left;
	}
	//递归对颜色、黑色节点数目进行判断
	return _CheckIsBalance(_root,curBlackNum,leftBlackNum);
}

template<typename K,typename V>
bool RBTree<K,V>::_CheckIsBalance(Node *root,int curBlackNum,const int leftBlackNum){
	if(root == NULL){
		return true;
	}
	if(root->_color == BLACK){
		++curBlackNum;
	}
	//该路径黑色节点数目与最左侧黑色节点数目不同
	if(root->_left==NULL &&
		root->_right==NULL &&
		curBlackNum!=leftBlackNum){
		return false;
	}
	//存在连续的红节点
	if(root->_color==RED && root->_parent->_color == RED){
		return false;
	}
	return _CheckIsBalance(root->_left,curBlackNum,leftBlackNum)&&
			_CheckIsBalance(root->_right,curBlackNum,leftBlackNum);
}

template<typename K,typename V>
void RBTree<K,V>::InOrderNonR(){
	std::stack<Node*> s;
	Node *cur = _root;
	while(cur!=NULL || !s.empty()){
		//走到最左路径
		while(cur!=NULL){
			s.push(cur);
			cur = cur->_left;
		}

		//无路可走,拿出Stack中的节点访问
		Node *top = s.top();
		s.pop();
		std::cout<<top->_key<<" ";

		//访问右子树
		cur = top->_right;
	}
	std::cout<<std::endl;
}

#endif
