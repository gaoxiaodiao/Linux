////////////////////////////////////
//文件说明:HuffmanTree.hpp
//作者:高小调
//创建时间:2017年07月13日 星期四 15时29分16秒
//开发环境:Kali Linux/g++ v6.3.0
////////////////////////////////////
#pragma once
#include<queue>
#include<vector>
#include<stack>
#include<iostream>
using std::stack;
using std::vector;
using std::priority_queue;
using std::cout;
using std::endl;
template<typename W>
struct HuffmanTreeNode{
	W weight;
	HuffmanTreeNode* left;
	HuffmanTreeNode* right;

	HuffmanTreeNode(const W& w)
		:weight(w)
		 ,left(0)
		 ,right(0){}
};

template<typename W>
class HuffmanTree{
typedef HuffmanTreeNode<W> Node;
public:
	HuffmanTree(W *arr,int size,const W& invalid=W() ){
		struct Less{
			bool operator()(Node* l,Node* r){
				return l->weight > r->weight;
			}
		};
	
		priority_queue<Node*,vector<Node*>,Less> heap;
		//将有效元素放入堆中
		for(int i=0; i<size; ++i){
			if(arr[i] != invalid){
				heap.push(new Node(arr[i]));
			}
		}

		//构建哈夫曼树
		while(heap.size()!=1){
			//选出左孩子
			Node* left = heap.top();
			heap.pop();
			//选出右孩子
			Node* right = heap.top();
			heap.pop();
			//创建父亲
			cout<<left->weight<<" "<<right->weight<<endl;
			Node* parent = new Node(left->weight + right->weight);
			parent->left = left;
			parent->right = right;
			//把父亲放入堆内
			heap.push(parent);
		}
		//哈夫曼树构建完成
		_root = heap.top();
	}
	Node* GetRoot(){
		return _root;
	}
	~HuffmanTree(){
		_Destory(_root);
		_root = NULL;
	}
public:
	void PrevOrderNonR(){
		stack<Node*> s;
		Node*cur = _root;
		while( cur!=NULL || !s.empty() ){
			while(cur!=NULL){
				s.push(cur);
				cout<<cur->weight<<" ";
				cur = cur->left;
			}
			Node*top = s.top();
			s.pop();
			cur = top->right;
		}
		cout<<endl;
	}
	void InOrderNonR(){
		stack<Node*> s;
		Node*cur = _root;
		while( cur!=NULL || !s.empty() ){
			while(cur!=NULL){
				s.push(cur);
				cur = cur->left;
			}
			Node*top = s.top();
			cout<<top->weight<<" ";
			s.pop();
			cur = top->right;
		}
		cout<<endl;
	}
protected:
	static void _Destory(Node* root){
		if(root==NULL){
			return ;
		}
		_Destory(root->left);
		_Destory(root->right);
		delete root;
	}
private:
	Node *_root;
};
