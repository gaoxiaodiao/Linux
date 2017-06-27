////////////////////////////////////
//文件说明:Test.cpp
//作者:高小调
//创建时间:2017年06月19日 星期一 09时01分30秒
//开发环境:Kali Linux/g++ v6.3.0
////////////////////////////////////
#include"BinaryTree.hpp"
#include"Heap.hpp"
void Test1(){
	int arr[] = {1,2,4,'#','#',7,'#','#',3,5,'#','#',6,'#',8};	
	Node_p root = CreateBinaryTree(arr,sizeof(arr)/sizeof(*arr),'#');
	cout<<"前序遍历:"<<endl;
	PrevOrder(root);
	PrevOrderNonR(root);
	cout<<endl;

	cout<<"中序遍历:"<<endl;
	InOrder(root);
	InOrderNonR(root);
	cout<<endl;
	
	cout<<"后序遍历:"<<endl;
	PostOrder(root);
	PostOrderNonR(root);
	cout<<endl;

	cout<<"层序遍历:"<<endl;
	LevelOrder(root);
	cout<<endl;
	int depth = Depth(root);
	cout<<"该树的高度为:"<<depth<<endl;
	cout<<"该树共有"<<LeafNum(root)<<"个叶子节点"<<endl;
	for(int i=1; i<=depth; ++i){
		cout<<"该树第"<<i<<"层有"<<GetKNode(root,i)<<"个节点"<<endl;
	}
	Node_p node1 = FindNode(root,4);
	Node_p node2 = FindNode(root,7);
	Node_p ancestor = GetCommonAncestor(root,node1,node2,1);
	cout<<node1->val<<"和"<<node2->val<<"的公共祖先为:"<<ancestor->val<<endl;
	node1 = FindNode(root,4);
	node2 = FindNode(root,5);
	ancestor = GetCommonAncestor(root,node1,node2,1);
	cout<<node1->val<<"和"<<node2->val<<"的公共祖先为:"<<ancestor->val<<endl;
	node1 = FindNode(root,5);
	node2 = FindNode(root,8);
	ancestor = GetCommonAncestor(root,node1,node2,1);
	cout<<node1->val<<"和"<<node2->val<<"的公共祖先为:"<<ancestor->val<<endl;
	
}
void Test2(){
	int prevorder[] = {1,2,4,7,3,5,6,8};
	int inorder[] = {4,2,7,1,5,3,6,8};
	int size = sizeof(prevorder)/sizeof(*prevorder);
	Node_p root = rebuildBinaryTree(prevorder,prevorder+size-1,inorder,inorder+size-1);
	PrevOrder(root);
	InOrder(root);
	PostOrder(root);
}
void Test3(){
	int arr1[] = {1,2,4,'#','#',7,'#','#',3,5,'#','#',6,'#',8};	//非完全二叉树
	int arr2[] = {1,2,4,0,0,5,0,0,3,0,0};	//完全二叉树
	int arr3[] = {1,2,4,0,0,5,0,0,3,0,6};	//非完全二叉树
	Node_p root1 = CreateBinaryTree(arr1,sizeof(arr1)/sizeof(*arr1),'#');	
	Node_p root2 = CreateBinaryTree(arr2,sizeof(arr2)/sizeof(*arr2),0);	
	Node_p root3 = CreateBinaryTree(arr3,sizeof(arr3)/sizeof(*arr3),0);	
	cout<<IsCompletlyTree(root1)<<endl;
	cout<<IsCompletlyTree(root2)<<endl;
	cout<<IsCompletlyTree(root3)<<endl;
}
void Test4(){
	//情况1:最长路径就在根节点所在的树中
	int arr1[] = {1,2,3,4,0,0,0,5,0,0,6,7,0,8,0,0,9};
	//情况2:最长路径在根节点所在的子树中
	int arr2[] = {1,2,3,4,0,0,5,0,6};
	Node_p root1 = CreateBinaryTree(arr1,sizeof(arr1)/sizeof(*arr1),0);
	
	Node_p root2 = CreateBinaryTree(arr2,sizeof(arr2)/sizeof(*arr2),0);
	cout<<GetMaxDistance(root1)<<endl;	//6
	cout<<GetMaxDistance(root2)<<endl;	//4
	
	PrevOrder(root1);
	InOrder(root1);
	PostOrder(root1);
	GetTreeMirror(root1);
	cout<<endl;
	PrevOrder(root1);
	InOrder(root1);
	PostOrder(root1);
	cout<<endl;
	PrevOrder(root2);
	InOrder(root2);
	PostOrder(root2);
	GetTreeMirror(root2);
	cout<<endl;
	PrevOrder(root2);
	InOrder(root2);
	PostOrder(root2);
}
void Test5(){
	int arr[]={5,3,2,1,0,0,0,4,0,0,7,6,0,0,8};
	Node_p root = CreateBinaryTree(arr,sizeof(arr)/sizeof(*arr),0);
	PrevOrder(root);
	InOrder(root);
	PostOrder(root);
	Node_p head = BecomeLinkList(root);
	
	Node_p cur = head;
	while(cur->right!=NULL){
		cout<<cur->val<<" ";
		cur = cur->right;
	}
	cout<<cur->val<<endl;
	
	while(cur->left!=NULL){
		cout<<cur->val<<" ";
		cur = cur->left;
	}
	cout<<cur->val<<endl;
	

}
void TestHeap(){
	int arr[]={1,2,3,4,5,6,7,8,9};
	Heap<int,greater<int>> heap(arr,sizeof(arr)/sizeof(*arr));
	heap.Print();
	heap.Pop();
	heap.Print();
	heap.Push(8);
	heap.Print();
	Heap<int> minHeap(arr,sizeof(arr)/sizeof(*arr));
	minHeap.Print();
	minHeap.Pop();
	minHeap.Print();
	minHeap.Push(1);
	minHeap.Print();
}
int main(){
	TestHeap();
	//Test5();
	//Test4();
	//Test3();
	//Test2();
	//Test1();
	return 0;
}
