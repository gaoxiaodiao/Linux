/**************************************
*文件说明:测试文件
*作者:高小调
*创建时间:2017年05月02日 星期二 07时59分57秒
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
#include"HuffmanTree.hpp"
void TestHuffmanTree(){
	int arr[]={1,2,3,4,5};
	HuffmanTree<int> tree(arr,sizeof(arr)/sizeof(*arr));
	tree.PrevOrderNonR();
	tree.InOrderNonR();
	tree.PostOrderNonR();
}
int main(){
	TestHuffmanTree();
	return 0;
}
