/**************************************
*文件说明:Test.cpp
*作者:高小调
*创建时间:2017年05月09日 星期二 09时30分42秒
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
#include"2017-05-09.h"
#include<iostream>
using namespace std;
void TestQueue(){
	Queue<int> q;
	for(int i=0; i<10; ++i){
		q.Push(i);
	}
	cout<<q.Front()<<endl;
	q.Pop();
		
	cout<<q.Front()<<endl;
	q.Pop();

	cout<<q.Front()<<endl;
	q.Pop();

	cout<<q.Front()<<endl;
	q.Pop();

	cout<<q.Front()<<endl;
	q.Pop();

	cout<<q.Front()<<endl;
	q.Pop();

	cout<<q.Front()<<endl;
	q.Pop();

	q.Push(10);	
	cout<<q.Front()<<endl;
	q.Pop();

	q.Push(11);	
	cout<<q.Front()<<endl;
	q.Pop();
	
	cout<<q.Front()<<endl;
	q.Pop();

	cout<<q.Front()<<endl;
	q.Pop();
}
int main(){
	TestQueue();
	return 0;
}
