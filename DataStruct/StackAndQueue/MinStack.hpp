////////////////////////////////////
//文件说明:MinStack.hpp
//作者:高小调
//创建时间:2017年06月18日 星期日 08时38分55秒
//开发环境:Kali Linux/g++ v6.3.0
////////////////////////////////////
#pragma once
#include<stack>
using std::stack;
template<typename T>
class MinStack{
public:
	void Push(const T& e){
		if(minStack.empty() || minStack.top() >= e){
			minStack.push(e);
		}
		dataStack.push(e);
	}
	void Pop(){
		if(!dataStack.empty()){
			if(!minStack.empty() && dataStack.top()==minStack.top()){
				minStack.pop();
			}
			dataStack.pop();
		}
	}
	int Min(){
		if(!minStack.empty()){
			return minStack.top();
		}
		return -9999999;
	}
	bool Empty(){
		return dataStack.empty();
	}
private:
	stack<T> dataStack;
	stack<T> minStack;
};
