/**************************************
*文件说明:哈夫曼树相关声明及实现
*作者:高小调
*创建时间:2017年05月02日 星期二 07时35分33秒
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
#include<queue>
#include<vector>
#include<stack>
#include<iostream>
using std::cout;
using std::endl;
using std::stack;
using std::vector;
using std::priority_queue;
//哈夫曼树节点定义
template<typename W>
struct HuffmanTreeNode{
	W _weight;
	HuffmanTreeNode *_left;
	HuffmanTreeNode *_right;
	HuffmanTreeNode(const W& weight)
		:_weight(weight)
		 ,_left(0)
		 ,_right(0){}
};
//哈夫曼树
template<typename W>
class HuffmanTree{
typedef HuffmanTreeNode<W> Node;
	public:
		HuffmanTree(W arr[],int size,W invalid=W());
		~HuffmanTree();
		void InOrderNonR();
		void PrevOrderNonR();
		void PostOrderNonR();
	protected:
		static void _Destroy(Node*);
	private:
		Node* _root;
};

template<typename W>
HuffmanTree<W>::HuffmanTree(W arr[],int size,W invalid){
	//仿函数
	struct More{
		bool operator()(Node* left ,Node *right){
			return left->_weight>right->_weight;
		}
	};
	//把所有数据以Node*的形式入堆
	priority_queue<Node*,vector<Node*>,More> heap;
	for(int i=0; i<size; ++i){
		if(arr[i]!=invalid){
			Node *tmp = new Node(arr[i]);
			heap.push(tmp);
		}
	}
	//构建HuffmanTree
	while(heap.size() != 1){
		//取出堆中两个最小的元素
		Node *left = heap.top();
		heap.pop();
		Node *right = heap.top();
		heap.pop();

		//构建其父节点
		Node *parent = new Node(left->_weight+right->_weight);
		parent->_left = left;
		parent->_right = right;
		
		//将父节点入堆
		heap.push(parent);
	}
	//剩下的最后一个节点为根节点
	_root = heap.top();
}

template<typename W>
HuffmanTree<W>::~HuffmanTree(){
	_Destroy(_root);
}

template<typename W>
void HuffmanTree<W>::_Destroy(Node *root){
	if(root==0){
		return ;
	}
	_Destroy(root->_left);
	_Destroy(root->_right);
	delete root;
}

template<typename W>
void HuffmanTree<W>::PrevOrderNonR(){
	stack<Node*> s;
	Node* cur = _root;
	while(cur!=0 || !s.empty()){

		while(cur!=0){
			s.push(cur);
			cout<<cur->_weight<<" ";
			cur = cur->_left;
		}
		
		Node* top = s.top();
		s.pop();

		cur = top->_right;
	}
	cout<<endl;
}

template<typename W>
void HuffmanTree<W>::InOrderNonR(){
	stack<Node*> s;
	Node *cur = _root;
	
	while(cur!=0 || !s.empty()){
		
		while(cur!=0){
			s.push(cur);
			cur = cur->_left;	
		}
	
		Node* top = s.top();
		s.pop();
		cout<<top->_weight<<" ";
	
		cur = top->_right;

	}
	cout<<endl;
}

template<typename W>
void HuffmanTree<W>::PostOrderNonR(){
	stack<Node*> s;
	Node *cur = _root;
	Node *prev = 0;

	while(cur!=0 || !s.empty()){
		
		while(cur!=0){
			s.push(cur);
			cur = cur->_left;
		}

		Node *top = s.top();

		if(top->_right==0 || top->_right==prev){
			prev = top;
			cout<<top->_weight<<" ";
			s.pop();
		}else{
			cur = top->_right;
		}

	}
	cout<<endl;
}
