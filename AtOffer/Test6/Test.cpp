/**************************************
*文件说明:Test.c
*作者:高小调
*创建时间:2017年05月09日 星期二 08时42分08秒
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
#include<iostream>
#include"2017-05-09.h"
void TestRebuiltBinaryTree(){
	int prevOrder[]={1,2,4,7,3,5,6,8};
	int inOrder[]={4,7,2,1,5,3,8,6};
	int size = sizeof(prevOrder)/sizeof(*prevOrder);
	Node *root = RebuiltBinaryTree(prevOrder,inOrder,size);
	if(root == NULL){
		std::cout<<"root = NULL"<<std::endl;		
	}
	PrevOrderNonR(root);
	InOrderNonR(root);
	PostOrderNonR(root);
}
int main(){
	TestRebuiltBinaryTree();
	return 0;
}
