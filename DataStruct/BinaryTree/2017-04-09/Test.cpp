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
//	int arr[] = {1,2,4,'#','#',7,'#','#',3,5,'#','#',6,'#',8};
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
	int arr1[] = {1,2,3,4,0,0,5,0,0,6,7,0,8,0,0,9};
	//情况2:最长路径在根节点所在的子树中
	int arr2[] = {1,2,3,4,0,0,5,0,6};
	
	BinaryTree<int> tree1(arr1,sizeof(arr1)/sizeof(*arr1),0);
	BinaryTree<int> tree2(arr2,sizeof(arr2)/sizeof(*arr2),0);
	
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
//测试二叉树映像
void Test5(){	
	int arr[] = {1,2,4,'#','#',7,'#','#',3,5,'#','#',6,'#',8};
	BinaryTree<int> tree(arr,sizeof(arr)/sizeof(*arr),'#');
	tree.PrevOrderNonR();
	tree.GetMirrorTree();
	tree.PrevOrderNonR();
}
//测试判断是否为完全二叉树
void Test6(){	
	int arr1[] = {1,2,4,'#','#',7,'#','#',3,5,'#','#',6,'#',8};	//非完全二叉树
	int arr2[] = {1,2,4,0,0,5,0,0,3,0,0};	//完全二叉树
	int arr3[] = {1,2,4,0,0,5,0,0,3,0,6};	//非完全二叉树
	
	BinaryTree<int> tree1(arr1,sizeof(arr1)/sizeof(*arr1),'#');
	BinaryTree<int> tree2(arr2,sizeof(arr2)/sizeof(*arr2),0);
	BinaryTree<int> tree3(arr3,sizeof(arr3)/sizeof(*arr3),0);
	std::cout<<tree1.IsCompleteTree()<<std::endl;	
	std::cout<<tree2.IsCompleteTree()<<std::endl;	
	std::cout<<tree3.IsCompleteTree()<<std::endl;	
}
//测试第K层节点个数
void Test7(){
	int arr1[] = {1,2,4,'#','#',7,'#','#',3,5,'#','#',6,'#',8};	//非完全二叉树
	int arr2[] = {1,2,4,0,0,5,0,0,3,0,0};	//完全二叉树
	int arr3[] = {1,2,4,0,0,5,0,0,3,0,6};	//非完全二叉树
	BinaryTree<int> tree1(arr1,sizeof(arr1)/sizeof(*arr1),'#');
	BinaryTree<int> tree2(arr2,sizeof(arr2)/sizeof(*arr2),0);
	BinaryTree<int> tree3(arr3,sizeof(arr3)/sizeof(*arr3),0);
	std::cout<<tree1.GetKNodeNum(1)<<std::endl;	//1
	std::cout<<tree1.GetKNodeNum(2)<<std::endl;	//2
	std::cout<<tree1.GetKNodeNum(3)<<std::endl;	//4
	std::cout<<tree1.GetKNodeNum(4)<<std::endl;	//1
	std::cout<<tree1.GetKNodeNum(5)<<std::endl;	//0

	std::cout<<tree2.GetKNodeNum(1)<<std::endl;	//1
	std::cout<<tree2.GetKNodeNum(2)<<std::endl;	//2
	std::cout<<tree2.GetKNodeNum(3)<<std::endl;	//2
	std::cout<<tree2.GetKNodeNum(4)<<std::endl;	//0

	std::cout<<tree3.GetKNodeNum(1)<<std::endl;	//1
	std::cout<<tree3.GetKNodeNum(2)<<std::endl;	//2
	std::cout<<tree3.GetKNodeNum(3)<<std::endl;	//3
	std::cout<<tree3.GetKNodeNum(4)<<std::endl;	//0
}
//测试将二叉树转换为双向链表
void Test8(){
	int arr[] = {5,3,2,1,0,0,0,4,0,0,10,7,6,0,0,8,0,9};
	BinaryTree<int> searchTree(arr,sizeof(arr)/sizeof(*arr),0);
	std::cout<<"这是一颗二叉搜索树,不信我中序给你看:";
	searchTree.InOrderNonR();
	std::cout<<std::endl;
	typename BinaryTree<int>::Node *head = searchTree.BecomeList();
	std::cout<<"我已经变身为双向链表,我先正序打印:"<<std::endl;
	typename BinaryTree<int>::Node *cur = head;
	while(cur!=NULL&&cur->_right!=NULL){
		std::cout<<cur->_value<<"->";
		cur = cur->_right;
	}
	std::cout<<cur->_value<<"->NULL"<<std::endl;
	std::cout<<"我再逆序输出给你看:"<<std::endl;
	while(cur!=NULL&&cur->_left!=NULL){
		std::cout<<cur->_value<<"->";
		cur = cur->_left;	
	}
	//因为,把树的结构改成了双向链表,所以,运行到这里,析构时就会出现问题
	//出现段错误
}
int main(){
	//Test1();
	//Test2();
	Test3();
	//Test4();
	//Test5();
	//Test6();
	//Test7();
	//Test8();
	return 0;
}
