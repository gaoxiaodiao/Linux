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

}//析构(DEBUG::后序遍历)
int main(){
	Test1();
	return 0;
}
