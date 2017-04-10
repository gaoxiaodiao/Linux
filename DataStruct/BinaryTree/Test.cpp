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
//测试高度
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

int main(){
	Test1();
	Test2();
	return 0;
}
