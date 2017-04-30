/**************************************
*文件说明:测试堆
*作者:高小调
*创建时间:2017年04月24日 星期一 13时45分41秒
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
#include<iostream>
#include"Heap.hpp"
using namespace std;
void TestHeap(){
	int arr[] = {10,16,18,12,11,13,15,17,14,19};
	int size = sizeof(arr)/sizeof(*arr);
	//小堆
	Heap<int> h1(arr,size);
	h1.Print(); 
	cout<<h1.CheckIsHeap()<<endl;
	h1.Pop();
	h1.Print();
	cout<<h1.CheckIsHeap()<<endl;
	h1.Push(5);
	h1.Print();
	cout<<h1.CheckIsHeap()<<endl;

	//大堆
	Heap<int,std::greater<int>> h2(arr,size);
	h2.Print();	
	cout<<h2.CheckIsHeap()<<endl;
	h2.Pop();
	h2.Print();	
	cout<<h2.CheckIsHeap()<<endl;
	h2.Push(20);
	h2.Print();	
	cout<<h2.CheckIsHeap()<<endl;
}
int main(){
	TestHeap();
	return 0;
}
