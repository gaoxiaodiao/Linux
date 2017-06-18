/**************************************
*文件说明:一个数组实现两个栈
*作者:高小调
*创建时间:2017年04月17日 星期一 16时17分52秒
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
#include<iostream>
#define __ARRAYIMPTWOSTACK_DEBUG__
#define S1_PUSH "\033[31m"
#define S1_POP	"\033[32m"
#define S1_ERROR "\033[33m"
#define S2_PUSH "\033[34m"
#define S2_POP	"\033[35m"
#define S2_ERROR "\033[36m"
#define COLOR_END "\033[0m"
enum STACK{
	STACK1,
	STACK2
};
template<typename T>
class TwoStack{
public:
	//构造函数
	TwoStack()
		:_arr(NULL)
		 ,_s1(0)
		 ,_s2(0)
		 ,_capacity(0){}
	//析构函数
	~TwoStack(){
		if(_arr!=NULL){
			delete []_arr;
			_arr = NULL;
			_s1 = 0;
			_s2 = 0;
			_capacity = 0;
		}
	}
public:
	//入栈
	void Push(STACK s,const T &e);
	//出栈
	void Pop(STACK s);
private:
	//禁止拷贝、赋值(懒人做法)
	TwoStack(const TwoStack & ts);
	TwoStack &operator=(const TwoStack &ts);
protected:
	void _CheckCapacity();
private:
	T *_arr;			//数组
	size_t _s1;			//数组的起始位置
	size_t _s2;			//数组的结束位置
	size_t _capacity;	//数组的大小
};

template<typename T>
void TwoStack<T>::_CheckCapacity(){
	if(_arr==NULL){
		//第一次开辟空间
		size_t capacity = 10;
		_arr = new T[capacity];
		_s1 = 0;
		_s2 = capacity-1;
		_capacity = capacity;
	}else if(_s1==_s2){
		//扩容处理
#ifdef __ARRAYIMPTWOSTACK_DEBUG__
		std::cout<<"s1在"<<_s1<<std::endl;
		std::cout<<"s2在"<<_s2<<std::endl;
		std::cout<<"旧空间大小为:"<<_capacity<<std::endl;
		std::cout<<"s1中有"<<_s1<<"个元素"<<std::endl;
		std::cout<<"s2中有"<<_capacity-_s2<<"个元素"<<std::endl;
#endif
		size_t capacity = _capacity*2;
		T *tmp = new T[capacity];
		//s1从前向后拷贝数据
		for(int i =0; i<_s1; ++i){
			tmp[i] = _arr[i];
		}
		/*
		//s2从后向前拷贝数据
		int s2length = capacity - _s2; 
		for(int i = 0; i<s2length; ++i){
			tmp[capacity-i] = _arr[capacity-i];
		}
		*/
		int i = 0;
		for( ;i<_s2;++i){
			tmp[capacity-i-1] = _arr[_capacity-i];
		}

		//更新指针
		_arr = tmp;
		_s2 = capacity-i-1;
		_capacity = capacity;
#ifdef __ARRAYIMPTWOSTACK_DEBUG__
		std::cout<<"s1在"<<_s1<<std::endl;
		std::cout<<"s2在"<<_s2<<std::endl;
		std::cout<<"新空间大小为:"<<_capacity<<std::endl;
		std::cout<<"s1中有"<<_s1<<"个元素"<<std::endl;
		std::cout<<"s2中有"<<_capacity-_s2<<"个元素"<<std::endl;
#endif
	}
}

//入栈
template<typename T>
void TwoStack<T>::Push(STACK s,const T &e){
	_CheckCapacity();
	if(s==STACK1){
		_arr[_s1++] = e;		
#ifdef __ARRAYIMPTWOSTACK_DEBUG__
			std::cout<<S1_PUSH<<"s1:"<<e<<"入栈!"<<COLOR_END<<std::endl;
#endif
	}else{
		_arr[_s2--] = e;
#ifdef __ARRAYIMPTWOSTACK_DEBUG__
			std::cout<<S2_PUSH<<"s2:"<<e<<"入栈!"<<COLOR_END<<std::endl;
#endif
	}
}

//出栈
template<typename T>
void TwoStack<T>::Pop(STACK s){
	if(s==STACK1){
		if(_s1 >= 0){
			--_s1;
#ifdef __ARRAYIMPTWOSTACK_DEBUG__
			std::cout<<S1_POP<<"s1:"<<_arr[_s1]<<"出栈!"<<COLOR_END<<std::endl;
#endif
		}else{
#ifdef __ARRAYIMPTWOSTACK_DEBUG__
			std::cout<<S1_ERROR<<"Pop失败:s1空了!"<<COLOR_END<<std::endl;
#endif
		}
	}else{
		if(_s2 < _capacity-1){
			++_s2;
#ifdef __ARRAYIMPTWOSTACK_DEBUG__
			std::cout<<S2_POP<<"s2:"<<_arr[_s2]<<"出栈!"<<COLOR_END<<std::endl;
#endif
		}else{		
#ifdef __ARRAYIMPTWOSTACK_DEBUG__
			std::cout<<S2_ERROR<<"Pop失败:s2空了!"<<COLOR_END<<std::endl;
#endif
		}
	}
}
