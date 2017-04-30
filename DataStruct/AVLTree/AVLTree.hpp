/**************************************
*文件说明:AVL树相关声明及实现
*作者:高小调
*创建时间:2017年04月30日 星期日 11时15分36秒
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
#ifndef __AVLTREE_H__
#define __AVLTREE_H__
#include<stack>
#include<iostream>
using std::cout;
using std::endl;
using std::stack;
//节点定义
template<typename K,typename V>
struct AVLTreeNode{
	AVLTreeNode *_parent;	
	AVLTreeNode *_left;	
	AVLTreeNode *_right;
	K _key;
	V _value;
	int _bf;	//平衡因子balance factor

	AVLTreeNode(const K& key,const V& value)
		:_parent(0)
		 ,_left(0)
		 ,_right(0)
		 ,_key(key)
		 ,_value(value)
		 ,_bf(0){}
};
template<typename K,typename V>
class AVLTree{
typedef AVLTreeNode<K,V> Node;
	public:
		AVLTree();
		~AVLTree();
	public:
		bool Insert(const K&,const V&);
		bool CheckIsBalance();
		void InOrderNonR();
	protected:
		void RotateL(Node*);
		void RotateR(Node*);
		void RotateRL(Node*);
		void RotateLR(Node*);
		static void _Destory(Node*);
		static bool _CheckIsBalance(Node*,int&);
	private:
		Node *_root;
};
//构造函数
template<typename K,typename V>
AVLTree<K,V>::AVLTree()
	:_root(NULL){}

//销毁树
template<typename K,typename V>
void AVLTree<K,V>::_Destory(Node* root){
	if(root==0){
		return ;
	}
	_Destory(root->_left);
	_Destory(root->_right);
	delete root;
}

//析构函数
template<typename K,typename V>
AVLTree<K,V>::~AVLTree(){
	_Destory(_root);
}

//左旋
template<typename K,typename V>
void AVLTree<K,V>::RotateL(Node *parent){
	Node *subR = parent->_right;
	Node *subRL = subR->_left;

	parent->_right = subRL;
	if(subRL!=0){
		subRL->_parent = parent;
	}

	Node *gf = parent->_parent;
	if(gf==0){
		_root = subR;
		_root->_parent = 0;
	}else{
		if(gf->_left == parent){
			gf->_left = subR;
		}else{
			gf->_right = subR;
		}
		subR->_parent = gf;
	}

	subR->_left = parent;
	parent->_parent = subR;

	parent->_bf = subR->_bf = 0;
}

//右旋
template<typename K,typename V>
void AVLTree<K,V>::RotateR(Node *parent){
	Node *subL = parent->_left;
	Node *subLR = subL->_right;

	parent->_left = subLR;
	if(subLR!=0){
		subLR->_parent = parent;
	}

	Node *gf = parent->_parent;
	if(gf==0){
		_root = subL;
		_root->_parent = 0;
	}else{
		if(gf->_left == parent){
			gf->_left = subL;
		}else{
			gf->_right = subL;
		}
		subL->_parent = gf;
	}

	subL->_right = parent;
	parent->_parent = subL;

	parent->_bf = subL->_bf = 0;
}

//左右双旋
//  *
// *
//  * 
template<typename K,typename V>
void AVLTree<K,V>::RotateLR(Node *parent){
	Node *subL = parent->_left;
	Node *subLR = subL->_right;
	int bf = subLR->_bf;

	RotateL(subL);
	RotateR(parent);

	if(bf == 0){
		parent->_bf = subL->_bf = 0;
	}else if(bf == 1){
		subL->_bf = -1;
		parent->_bf = 0;
	}else{	//bf == -1
		subL->_bf = 0;
		parent->_bf = 1;
	}
}

//右左双旋
// *
//  *
// *
template<typename K,typename V>
void AVLTree<K,V>::RotateRL(Node *parent){
	Node *subR = parent->_right;
	Node *subRL = subR->_left;
	int bf = subRL->_bf;

	RotateR(subR);
	RotateL(parent);

	if(bf == 0){
		subR->_bf = parent->_bf = 0;
	}else if(bf == -1){
		parent->_bf = 0;
		subR->_bf = 1;
	}else{
		parent->_bf = -1;
		subR->_bf = 0;
	}

}

//中序遍历非递归
template<typename K,typename V>
void AVLTree<K,V>::InOrderNonR(){
	stack<Node*> s;
	Node *cur = _root;
	while(cur!=0 || !s.empty()){
		while(cur!=0){
			s.push(cur);
			cur = cur->_left;
		}

		Node *top = s.top();
		s.pop();
		cout<<top->_key<<" ";
		
		cur = top->_right;
	}
	cout<<endl;
}

//插入
template<typename K,typename V>
bool AVLTree<K,V>::Insert(const K &key,const V &value){
	if(_root==0){
		_root = new Node(key,value);
		return true;
	}
	//找插入位置
	Node *parent = 0;
	Node *cur = _root;
	while(cur!=0){
		if(cur->_key > key){
			parent = cur;
			cur = cur->_left;
		}else if(cur->_key < key){
			parent = cur;
			cur = cur->_right;
		}else{
			return false;
		}
	}
	//插入新数据
	cur = new Node(key,value);
	if(parent->_key > key){
		parent->_left = cur;
	}else{
		parent->_right = cur;
	}
	cur->_parent = parent;

	//调节平衡因子
	while(parent!=0){
		//更新父亲的平衡因子	
		if(parent->_left == cur){
			parent->_bf -= 1;
		}else{
			parent->_bf += 1;
		}
		//判断情况
		if(parent->_bf == 1||
				parent->_bf == -1){
			cur = parent;
			parent = cur->_parent;
		}else if(parent->_bf == 0){
			break;	//已经平衡
		}else if(parent->_bf == -2||
				parent->_bf == 2){
			//四种旋转情况
			if(parent->_bf == -2&&
					cur->_bf == -1){
				//    *
				//  *
				//*
				RotateR(parent);
			}else if(parent->_bf == -2&&
					cur->_bf == 1){
				//  *
				//*
				//  *
				RotateLR(parent);
			}else if(parent->_bf == 2&&
					cur->_bf == -1){
				//*
				//  *
				//*
				RotateRL(parent);
			}else{
				//*
				//  *
				//    *
				RotateL(parent);
			}
			break;	//旋转完成后,结束循环!
		}else{
			cout<<"平衡因子出错!"<<endl;
		}
	}
	return true;
}

//判断是否平衡
template<typename K,typename V>
bool AVLTree<K,V>::CheckIsBalance(){
	int depth = 0;
	return _CheckIsBalance(_root,depth);
}

template<typename K,typename V>
bool AVLTree<K,V>::_CheckIsBalance(Node *root,int& depth){
	if(root==NULL){
		depth = 0;
		return true;
	}
	int leftd = 0;
	bool left = _CheckIsBalance(root->_left,leftd);
	int rightd = 0;
	bool right = _CheckIsBalance(root->_right,rightd);
	if(left && right){
		int diff = rightd - leftd;
		if(diff!=root->_bf){
			cout<<"平衡因子异常!key="<<root->_key<<endl;
		}
		if(diff >= -1 &&  diff <= 1){
			depth = leftd>rightd?leftd+1:rightd+1;
			return true;
		}
	}
	return false;
}

/*
template<typename K,typename V>
AVLTree<K,V>::


template<typename K,typename V>
AVLTree<K,V>::


template<typename K,typename V>
AVLTree<K,V>::


template<typename K,typename V>
AVLTree<K,V>::


template<typename K,typename V>
AVLTree<K,V>::
*/

#endif
