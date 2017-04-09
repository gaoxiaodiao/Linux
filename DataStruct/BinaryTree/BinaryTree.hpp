/**************************************
*文件说明:二叉树相关声明及实现
*作者:高小调
*创建时间:2017年04月09日 星期日 18时31分33秒
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
#ifndef __BINARYTREE_H__
#define __BINARYTREE_H__
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
	BinaryTree(T*,size_t sz,T &invalid);			//构造函数
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

#endif
