////////////////////////////////////
//文件说明:ArrayImpTwoStack.hpp
//作者:高小调
//创建时间:2017年06月18日 星期日 08时40分41秒
//开发环境:Kali Linux/g++ v6.3.0
////////////////////////////////////
#pragma once
enum CLS{
	STACK1,
	STACK2,
};
template<typename T>
class TwoStack{
public:
	TwoStack()
		:stack(NULL)
		,s1(0)
		,s2(-1)
		,size(0){}
	~TwoStack(){
		if(stack!=NULL){
			delete []stack;
		}
	}
public:
	void Push(CLS cls,const T& e){
		_CheckCapacity();
		if(cls==STACK1){
			stack[s1] = e;
			s1++;
		}else{
			stack[s2] = e;
			s2--;
		}
	}

	void Pop(CLS cls){
		if(cls==STACK1){
			if(!Empty(cls)){
				s1--;
			}
		}else{
			if(!Empty(cls)){
				s2++;
			}
		}
	}

	bool Empty(CLS cls){
		if(cls == STACK1){
			return s1==0;
		}else{
			return s2==size-1;
		}
	}

	const T& Top(CLS cls){
		if(cls == STACK1){
			if(!Empty(cls))
				return stack[s1-1];
		}else{
			if(!Empty(cls))
				return stack[s2+1];
		}
		return T();
	}
	void Print(){
		for(int i=0; i<size; ++i){
			cout<<stack[i]<<" ";
		}
		cout<<endl;
	}
private:
	void _CheckCapacity(){
		if(stack==NULL){
			stack = new T[10];
			size = 10;
			s1 = 0;
			s2 = size-1;
		}else if(s1==s2){
			int newSize = size*2+3;
			int *newStack = new T[newSize];
			for(int i = 0; i<s1; ++i){
				newStack[i] = stack[i];
			}
			
			int sub = size-s2;
			int oldS2Index = s2-sub;
			int newS2Index = newSize-sub;
			for(int i=1; i<=sub; i++){
				newStack[newS2Index+i] = stack[s2+i]; 
			}

			delete stack;

			stack = newStack;
			size = newSize;
			s1 = s1;
			s2 = newSize-sub;
		}
	}
private:
	T *stack;
	int s1;
	int s2;
	int size;
};
