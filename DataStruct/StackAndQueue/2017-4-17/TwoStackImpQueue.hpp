/**************************************
*文件说明:两个栈实现一个队列
*作者:高小调
*创建时间:2017年04月16日 星期日 18时00分26秒
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
#include<iostream>
#include<stack>
#include<cassert>
#define __QUEUE__DEBUG__
template<typename T>
class Queue{
public:
	//构造、拷贝构造、赋值运算符重载、析构省略.
public:
	void Push(const T& e);		//入队
	void Pop();				//出队
	const T& Front();				//获取队首元素
protected:
	void _SinToSout();			//将入队栈中的数据全部放入出队栈中
private:
	std::stack<T> sin;		//入队栈
	std::stack<T> sout;		//出队栈
};

//内部函数:将sin的全部数据压入sout中
template<typename T>
void Queue<T>::_SinToSout(){
	while(!sin.empty()){
		sout.push(sin.top());
		sin.pop();
	}
}

//入队
template<typename T>
void Queue<T>::Push(const T& e){
	sin.push(e);
#ifdef __QUEUE__DEBUG__
	std::cout<<"\033[31m"<<e<<"入队!"<<"\033[0m"<<std::endl;
#endif	
}

//出队
template<typename T>
void Queue<T>::Pop(){
	//出队栈为空,则把入队栈全部元素压入出队栈
	if(sout.empty()){
		assert(!sin.empty());	//空队列断言
		_SinToSout();	
	}
#ifdef __QUEUE__DEBUG__
	std::cout<<"\033[32m"<<sout.top()<<"出队!"<<"\033[0m"<<std::endl;
#endif
	sout.pop();
}

//获取队首元素
template<typename T>
const T& Queue<T>::Front(){
	if(sout.empty()){
		assert(!sin.empty());	//空队列
		_SinToSout();
	}
	return sout.top();
}
