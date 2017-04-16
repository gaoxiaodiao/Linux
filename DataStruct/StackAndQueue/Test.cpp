/**************************************
*文件说明:测试文件
*作者:高小调
*创建时间:2017年04月16日 星期日 18时22分29秒
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
#include"TwoStackImpQueue.hpp"
#include"TwoQueueImpStack.hpp"
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
int main(){
	//TestQueue();
	TestStack();
	return 0;
}
