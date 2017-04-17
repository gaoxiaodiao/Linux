/**************************************
*文件说明:测试文件
*作者:高小调
*创建时间:2017年04月16日 星期日 18时22分29秒
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
#include"TwoStackImpQueue.hpp"
#include"TwoQueueImpStack.hpp"
#include"CheckStackArrayIsLegal.hpp"
#include"ArrayImpTwoStack.hpp"
#include"MinStack.hpp"
void TestQueue(){
	Queue<int> q;
	q.Push(0);
	q.Push(1);
	q.Push(2);
	q.Push(3);
	q.Pop();
	q.Pop();
	q.Pop();	
	q.Push(4);
	q.Push(5);
	q.Push(6);
	q.Pop();	
	q.Pop();	
	q.Pop();	
	q.Pop();	
}
void TestStack(){
	Stack<int> s;
	s.Push(0);
	s.Push(4);
	s.Push(5);
	s.Pop();
	s.Pop();
	s.Push(1);
	s.Push(2);
	s.Push(3);
	s.Pop();
	s.Pop();
	s.Pop();
	s.Pop();
}
void TestArray(){
	int in[] = {1,2,3,4,5};
	int out1[] = {4,5,3,2,1};
	int out2[] = {5,3,1,2,4};
	int out3[] = {3,2,1,5,4};
	int out4[] = {3,5,4,1,2};
	std::cout<<CheckStackArrayIsLegal(in,out1,sizeof(in)/sizeof(*in))<<std::endl;
	std::cout<<CheckStackArrayIsLegal(in,out2,sizeof(in)/sizeof(*in))<<std::endl;
	std::cout<<CheckStackArrayIsLegal(in,out3,sizeof(in)/sizeof(*in))<<std::endl;
	std::cout<<CheckStackArrayIsLegal(in,out4,sizeof(in)/sizeof(*in))<<std::endl;
}

void TestTwoStack(){
	TwoStack<int> ts;
	ts.Push(STACK1,0);	//第一次扩容
	ts.Push(STACK1,1);
	ts.Push(STACK1,2);
	ts.Push(STACK1,3);
	ts.Push(STACK1,4);

	ts.Push(STACK2,5);
	ts.Push(STACK2,6);
	ts.Push(STACK2,7);
	ts.Push(STACK2,8);
	ts.Push(STACK2,9);	//第二次扩容

	ts.Push(STACK1,10);	
	ts.Push(STACK2,11);

	//STACK1:10 4 3 2 1 0
	ts.Pop(STACK1);
	ts.Pop(STACK1);
	ts.Pop(STACK1);
	ts.Pop(STACK1);
	ts.Pop(STACK1);
	ts.Pop(STACK1);
	//STACK2:11 9 8 7 6 5			
	ts.Pop(STACK2);
	ts.Pop(STACK2);
	ts.Pop(STACK2);
	ts.Pop(STACK2);
	ts.Pop(STACK2);
	ts.Pop(STACK2);

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
	//TestArray();
	//TestTwoStack();
	TestMinStack();
	return 0;
}
