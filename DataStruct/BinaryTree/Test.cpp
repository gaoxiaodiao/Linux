/**************************************
*文件说明:测试文件
*作者:高小调
*创建时间:2017年04月09日 星期日 19时18分50秒
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
#include"BinaryTree.hpp"
//测试构造/析构/遍历
void Test1(){
	//构造
	int arr[] = {1,2,4,'#','#',7,'#','#',3,5,'#','#',6,'#',8};
	BinaryTree<int> tree(arr,sizeof(arr)/sizeof(*arr),'#');
	
	//前序遍历
	std::cout<<"前序遍历:"<<std::endl;
	tree.PrevOrder();
	tree.PrevOrderNonR();
	std::cout<<std::endl;

	//中序遍历
	std::cout<<"中序遍历:"<<std::endl;
	tree.InOrder();
	tree.InOrderNonR();
	std::cout<<std::endl;
	
	//后序遍历
	std::cout<<"后序遍历:"<<std::endl;
	tree.PostOrder();
	tree.PostOrderNonR();
	std::cout<<std::endl;
	
	//层序遍历
	std::cout<<"层序遍历:"<<std::endl;
	tree.LevelOrder();
	std::cout<<std::endl;

}//析构(DEBUG::后序遍历)
//测试高度/叶子节点个数/公共祖先
void Test2(){	
	int arr[] = {1,2,4,'#','#',7,'#','#',3,5,'#','#',6,'#',8};
	BinaryTree<int> tree(arr,sizeof(arr)/sizeof(*arr),'#');
	std::cout<<"二叉树的高度为:"<<tree.Depth()<<std::endl;
	std::cout<<"二叉树的叶子结点个数为:"<<tree.GetLeafNodeNum()<<std::endl;
	for(int i=0; i<sizeof(arr)/sizeof(*arr); ++i){
		if(arr[i]!='#'){
			std::cout<<arr[i]<<":"<<tree.Find(arr[i])<<std::endl;
		}
	}
	int n1 = 4;
	int n2 = 8;
	std::cout<<n1<<"与"<<n2<<"之间的公共祖先为:"<<tree.GetCommonAncestralNode(tree.Find(n1),tree.Find(n2))->_value<<std::endl;
}
//测试树中最长路径
void Test3(){
	//情况1:最长路径就在根节点所在的树中
	int arr1[] = {1,2,4,'#','#',7,'#','#',3,5,'#','#',6,'#',8};
	//情况2:最长路径在根节点所在的子树中
	int arr2[] = {1,2,'#','#',3,4,5,6,7,'#','#',8,9,10,11,12,13,14,15};
	
	BinaryTree<int> tree1(arr1,sizeof(arr1)/sizeof(*arr1),'#');
	BinaryTree<int> tree2(arr2,sizeof(arr2)/sizeof(*arr2),'#');
	
	std::cout<<"情况1的最长路径为:"<<tree1.GetMaxDistance()<<std::endl;
	std::cout<<"情况2的最长路径为:"<<tree2.GetMaxDistance()<<std::endl;
}
//测试重建二叉树
void Test4(){
	int arr[] = {1,2,4,'#','#',7,'#','#',3,5,'#','#',6,'#',8};
	int prevorder[] = {1,2,4,7,3,5,6,8};
	int inorder[] = {4,2,7,1,5,3,6,8};

	BinaryTree<int> tree1(arr,sizeof(arr)/sizeof(*arr),'#');
	std::cout<<"tree1:"<<std::endl;
	tree1.PrevOrderNonR();
	tree1.InOrderNonR();
	tree1.PostOrderNonR();

	//测试重建二叉树
	try{
		std::cout<<"tree2"<<std::endl;
		BinaryTree<int> tree2(prevorder,inorder,sizeof(prevorder)/sizeof(*prevorder));
		tree2.PrevOrderNonR();
		tree2.InOrderNonR();
		tree2.PostOrderNonR();
	}catch(std::exception &e){
		std::cout<<e.what()<<std::endl;
	}
}
int main(){
	//Test1();
	//Test2();
	//Test3();
	Test4();
	return 0;
}
