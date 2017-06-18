/**************************************
*文件说明:Push、Pop、Min操作均为O(1)的栈
*作者:高小调
*创建时间:2017年04月17日 星期一 18时48分35秒
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
#include<stack>
#include<cassert>
template<typename T>
class MinStack{
public:
	//构造、拷贝构造、赋值运算符重载、析构略
public:
	void Push(const T &e);	//入栈
	void Pop();				//出栈
	const T& Min();			//获取最小值
	bool Empty();			//判断是否为空(测试使用)
private:
	std::stack<T> _s;		//栈
	std::stack<T> _min;		//最小值栈
};

//入栈
template<typename T>
void MinStack<T>::Push(const T &e){
	if(_min.empty() || _min.top() >= e){
		_min.push(e);
	}
	_s.push(e);

}

//出栈
template<typename T>
void MinStack<T>::Pop(){
	if(_s.empty()){
		assert(false);
	}
	if(_s.top() == _min.top()){
		_min.pop();
	}
	_s.pop();
}

//获取当前栈中元素的最小值
template<typename T>
const T &MinStack<T>::Min(){
	if(_min.empty()){
		assert(false);
	}
	return _min.top();
}

template<typename T>
bool MinStack<T>::Empty(){
	return _s.empty();
}
