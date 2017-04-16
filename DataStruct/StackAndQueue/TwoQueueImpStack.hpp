/**************************************
*文件说明:两个队列实现一个栈
*作者:高小调
*创建时间:2017年04月16日 星期日 18时37分32秒
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
#include<iostream>
#include<queue>
#include<cassert>
template<typename T>
class Stack{
public:
	//构造、拷贝构造、赋值运算符重载、析构函数省略.
public:
	void Push(const T &e);		//入栈
	void Pop();					//出栈
	const T &Top();				//获取栈顶元素
protected:
	void _QinToQout();
	void _QoutToQin();
private:
	std::queue<T> qin;		//入栈队列
	std::queue<T> qout;		//出栈队列
};

template<typename T>
void Stack<T>::_QinToQout(){
	int size = qin.size();
	while(size>1){
		qout.push(qin.front());
		qin.pop();
		--size;
	}
}

template<typename T>
void Stack<T>::_QoutToQin(){
	while(!qout.empty()){
		qin.push(qout.front());
		qout.pop();
	}
}

//入栈
template<typename T>
void Stack<T>::Push(const T &e){
	qin.push(e);
#ifdef __DEBUG__
	std::cout<<"\033[31m"<<e<<"入栈!"<<"\033[0m"<<std::endl;
#endif
}

//出栈
template<typename T>
void Stack<T>::Pop(){
	std::queue<T>* pIn = &qin;
	std::queue<T>* pOut = &qout;
	if(qout.empty()){
		pIn = &qout;
		pOut = &qin;
	}
	size_t size = pOut->size();
	while(size>1){
		pIn->push(pOut->front());
		pOut->pop();
		--size;
	}
#ifdef __DEBUG__
	std::cout<<"\033[32m"<<pOut->front()<<"出栈!"<<"\033[0m"<<std::endl;
#endif
	pOut->pop();
}
