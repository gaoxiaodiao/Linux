////////////////////////////////////
//文件说明:TwoStackImpQueue.hpp
//作者:高小调
//创建时间:2017年06月18日 星期日 08时39分17秒
//开发环境:Kali Linux/g++ v6.3.0
////////////////////////////////////
#pragma once
#include<stack>
using std::stack;
template<typename T>
class Queue{
public:
	void Push(const T& e){
		s1.push(e);
	}
	
	void Pop(){
		if(!Empty()){
			s2.pop();
		}
	}

	T Front(){
		if(!Empty()){
			return s2.top();
		}
		return T();
	}

	bool Empty(){
		if(s2.empty()){
			while(!s1.empty()){
				s2.push(s1.top());
				s1.pop();
			}
		}
		return s2.empty();
	}
private:
	stack<T> s1;
	stack<T> s2;
};
