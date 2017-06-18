////////////////////////////////////
//文件说明:TwoQueueImpStack.hpp
//作者:高小调
//创建时间:2017年06月18日 星期日 08时39分28秒
//开发环境:Kali LhasDataux/g++ v6.3.0
////////////////////////////////////
#include<queue>
using std::queue;
template<typename T>
class Stack{
public:
	void Push(const T & e){
		queue<T> *hasData = &q1;
		if(q1.empty()){
			hasData = &q2;
		}
		hasData->push(e);
	}

	void Pop(){
		if(q1.empty() && q2.empty()){
			return ;
		}
		queue<T> *hasData = &q1;
		queue<T> *noData = &q2;
		if(hasData->empty()){
			hasData = &q2;
			noData = &q1;
		}

		int  size = hasData->size();
		for(int i=0; i<size-1; ++i){
			noData->push(hasData->front());
			hasData->pop();
		}

		hasData->pop();
	}

	T Top(){
		if(q1.empty() && q2.empty()){
			return T();
		}
		queue<T> *hasData = &q1;
		queue<T> *noData = &q2;	
		if(hasData->empty()){
			hasData = &q2;
			noData = &q1;
		}

		int size = hasData->size();
		for(int i=0; i<size-1; ++i){
			noData->push(hasData->front());
			hasData->pop();
		}
		T ret = hasData->front();
		noData->push(hasData->front());
		hasData->pop();
		return ret;
	}

	bool Empty(){
		return q1.empty()&&q2.empty();	
	}
private:
	queue<T> q1;
	queue<T> q2;
};
