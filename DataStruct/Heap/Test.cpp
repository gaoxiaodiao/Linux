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
	cout<<h1.CheckIsHeap()<<endl;
	h1.Print(); 
	h1.Pop();
	cout<<h1.CheckIsHeap()<<endl;
	h1.Print();
	h1.Push(5);
	cout<<h1.CheckIsHeap()<<endl;
	h1.Print();

	//大堆
	Heap<int,std::greater<int>> h2(arr,size);
	cout<<h1.CheckIsHeap()<<endl;
	h2.Print();	
	h2.Pop();
	cout<<h1.CheckIsHeap()<<endl;
	h2.Print();	
	h2.Push(20);
	cout<<h1.CheckIsHeap()<<endl;
	h2.Print();	
}
int main(){
	TestHeap();
	return 0;
}
