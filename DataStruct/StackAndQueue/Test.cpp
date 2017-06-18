/**************************************
*文件说明:测试文件
*作者:高小调
*创建时间:2017年04月16日 星期日 18时22分29秒
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
#include<iostream>
using namespace std;
#include"TwoStackImpQueue.hpp"
#include"TwoQueueImpStack.hpp"
#include"CheckStackArrayIsLegal.hpp"
#include"ArrayImpTwoStack.hpp"
#include"MinStack.hpp"
void TestQueue(){
	Queue<int> q;
	q.Push(0);
	cout<<q.Front()<<endl;
	q.Push(1);
	cout<<q.Front()<<endl;
	q.Push(2);
	cout<<q.Front()<<endl;
	q.Push(3);
	cout<<q.Front()<<endl;
	q.Pop();
	cout<<q.Front()<<endl;
	q.Pop();
	cout<<q.Front()<<endl;
	q.Pop();	
	cout<<q.Front()<<endl;
	q.Push(4);
	cout<<q.Front()<<endl;
	q.Push(5);
	cout<<q.Front()<<endl;
	q.Push(6);
	cout<<q.Front()<<endl;
	q.Pop();	
	cout<<q.Front()<<endl;
	q.Pop();	
	cout<<q.Front()<<endl;
	q.Pop();	
	cout<<q.Front()<<endl;
	q.Pop();	
	cout<<q.Front()<<endl;
}

void TestStack(){
	Stack<int> s;
	s.Push(0);
	cout<<s.Top()<<endl;
	s.Push(4);
	cout<<s.Top()<<endl;
	s.Push(5);
	cout<<s.Top()<<endl;
	s.Pop();
	cout<<s.Top()<<endl;
	s.Pop();
	cout<<s.Top()<<endl;
	s.Push(1);
	cout<<s.Top()<<endl;
	s.Push(2);
	cout<<s.Top()<<endl;
	s.Push(3);
	cout<<s.Top()<<endl;
	s.Pop();
	s.Pop();
	cout<<s.Top()<<endl;
	s.Pop();
	cout<<s.Top()<<endl;
	s.Pop();
	cout<<s.Top()<<endl;
}

void TestArray(){
	int in[] = {1,2,3,4,5};
	int out1[] = {4,5,3,2,1};
	int out2[] = {5,3,1,2,4};
	int out3[] = {3,2,1,5,4};
	int out4[] = {3,5,4,1,2};
	//1 0 1 0
	std::cout<<CheckStackArrayIsLegal(in,out1,sizeof(in)/sizeof(*in))<<std::endl;
	std::cout<<CheckStackArrayIsLegal(in,out2,sizeof(in)/sizeof(*in))<<std::endl;
	std::cout<<CheckStackArrayIsLegal(in,out3,sizeof(in)/sizeof(*in))<<std::endl;
	std::cout<<CheckStackArrayIsLegal(in,out4,sizeof(in)/sizeof(*in))<<std::endl;
}

void TestTwoStack(){
	TwoStack<int> ts;
	ts.Push(STACK1,0);	//第一次扩容
	std::cout<<ts.Top(STACK1)<<std::endl;
	ts.Push(STACK1,1);
	std::cout<<ts.Top(STACK1)<<std::endl;
	ts.Push(STACK1,2);
	std::cout<<ts.Top(STACK1)<<std::endl;
	ts.Push(STACK1,3);
	std::cout<<ts.Top(STACK1)<<std::endl;
	ts.Push(STACK1,4);
	std::cout<<ts.Top(STACK1)<<std::endl;
	//0 1 2 3 4
	ts.Push(STACK2,5);
	std::cout<<ts.Top(STACK2)<<std::endl;
	ts.Push(STACK2,6);
	std::cout<<ts.Top(STACK2)<<std::endl;
	ts.Push(STACK2,7);
	std::cout<<ts.Top(STACK2)<<std::endl;
	ts.Push(STACK2,8);
	std::cout<<ts.Top(STACK2)<<std::endl;

	ts.Push(STACK2,9);	//第二次扩容
	std::cout<<ts.Top(STACK2)<<std::endl;

	ts.Push(STACK1,10);	
	std::cout<<ts.Top(STACK1)<<std::endl;
	ts.Push(STACK2,11);
	std::cout<<ts.Top(STACK2)<<std::endl;

	//STACK1:10 4 3 2 1 0
	while(!ts.Empty(STACK1)){
		std::cout<<ts.Top(STACK1)<<" ";
		ts.Pop(STACK1);
	}
	std::cout<<std::endl;
	//STACK2:11 9 8 7 6 5			
	while(!ts.Empty(STACK2)){
		std::cout<<ts.Top(STACK2)<<" ";
		ts.Pop(STACK2);
	}
	std::cout<<std::endl;
	ts.Print();
}

void TestMinStack(){
	MinStack<int> ms;
	ms.Push(6);
	ms.Push(5);
	ms.Push(4);
	ms.Push(3);
	ms.Push(2);
	ms.Push(1);
	ms.Push(0);
	ms.Push(0);
	ms.Push(0);
	ms.Push(0);
	//0000123456
	while(!ms.Empty()){
		std::cout<<ms.Min()<<std::endl;
		ms.Pop();
	}
}

int main(){
	//TestQueue();
	//TestStack();
	//TestArray();	//1010
	TestTwoStack();
	//TestMinStack();
	return 0;
}
