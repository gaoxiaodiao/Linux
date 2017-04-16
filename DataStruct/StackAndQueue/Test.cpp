/**************************************
*文件说明:测试文件
*作者:高小调
*创建时间:2017年04月16日 星期日 18时22分29秒
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
#include"TwoStackImpQueue.hpp"
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
int main(){
	TestQueue();
	return 0;
}
