/**************************************
*文件说明:面试题07:两个栈实现一个队列
*作者:高小调
*创建时间:2017年05月09日 星期二 09时22分21秒
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
#include<stack>
#include<cassert>
using std::stack;
template<typename T>
class Queue{
	public:
		void Push(const T & e);
		void Pop();
		T & Front();
	private:
		stack<T> _s1;
		stack<T> _s2;
};

template<typename T>
void Queue<T>::Push(const T &e){
	_s1.push(e);
}

template<typename T>
void Queue<T>::Pop(){
	if(_s2.empty()){
		while(_s1.empty()){
			_s2.push(_s1.top());
			_s1.pop();
		}
	}
	if(!_s2.empty())
		_s2.pop();
}

template<typename T>
T& Queue<T>::Front(){
	if(_s2.empty()){
		while(!_s1.empty()){
			_s2.push(_s1.top());
			_s1.pop();
		}
	}
	if(_s2.empty()){
		assert(false);
	}
	return _s2.top();
}
