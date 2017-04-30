/**************************************
*文件说明:Test.cpp
*作者:高小调
*创建时间:2017年04月30日 星期日 12时51分28秒
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
#include<iostream>
#include"AVLTree.hpp"
using namespace std;
void TestAVLTree(){
	int arr1[] = {16,3,7,11,9,26,18,14,15};
	AVLTree<int,int> Tree1;
	for(int i=0; i<sizeof(arr1)/sizeof(*arr1); ++i){
		Tree1.Insert(arr1[i],i);
		cout<<Tree1.CheckIsBalance()<<endl;
	}
	Tree1.InOrderNonR();
	
	int arr2[] = {4,2,6,1,3,5,15,7,16,14}; 
	AVLTree<int,int> Tree2;
	for(int i=0; i<sizeof(arr2)/sizeof(*arr2); ++i){
		Tree2.Insert(arr2[i],i);
		cout<<Tree2.CheckIsBalance()<<endl;
	}
	Tree2.InOrderNonR();
}
int main(){
	TestAVLTree();
	return 0;
}
