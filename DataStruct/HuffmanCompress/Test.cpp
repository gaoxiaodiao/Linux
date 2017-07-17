/**************************************
*文件说明:Test.cpp
*作者:高小调
*创建时间:2017年07月13日 星期四 16时12分25秒
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
#include"HuffmanTree.hpp"
void Test(){
	int arr[] = {1,2,3,4};
	int size = sizeof(arr)/sizeof(*arr);
	HuffmanTree<int> tree(arr,size);
	tree.PrevOrderNonR();
	tree.InOrderNonR();
}
int main(){
	Test();
	return 0;
}
