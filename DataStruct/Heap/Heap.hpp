/**************************************
*文件说明:堆的相关声明及实现
*作者:高小调
*创建时间:2017年04月24日 星期一 11时31分30秒
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
#ifndef __HEAP_H__
#define __HEAP_H__
#include<iostream>
#include<functional>
#include<vector>
template<typename T,typename Com = std::less<T> >
class Heap{
	public:
		Heap(T arr[],int size);	//构造函数
	public:
		void Push(const T&);	//入数据
		void Pop();				//出数据
		void Print();			//打印堆(测试使用)
		bool CheckIsHeap();		//判断是否为堆
	protected:
		void _AdjustUp(int);		//向上调整
		void _AdjustDown(int);	//向下调整
		bool _CheckIsHeap(int);	//递归判断是否为堆
	private:
		Heap(const Heap& );
		Heap& operator=(const Heap&);
	private:
		std::vector<T> _heap;
};

template<typename T,typename Com>
void Heap<T,Com>::Print(){
	for(int i=0; i<_heap.size(); ++i){
		std::cout<<_heap[i]<<" ";
	}
	std::cout<<std::endl;
}

//构造函数:建堆
//时间复杂度O(N*lgN)
template<typename T,typename Com> 
Heap<T,Com>::Heap(T arr[],int size)
	:_heap(arr,arr+size){
	//从最后一个非叶子节点开始,不断的向下调整
	for(int i=(size-2)/2; i>=0; --i){
		_AdjustDown(i);
	}
}

//向下调整
//时间复杂度O(logN)
template<typename T,typename Com>
void Heap<T,Com>::_AdjustDown(int index){
	int parent = index;
	int child = parent*2+1;
	while(child<_heap.size()){
		//找出大/小孩子
		if(child+1<_heap.size() &&
				Com()(_heap[child+1],_heap[child])){
			child++;
		}
		//找出根节点
		if(Com()(_heap[child],_heap[parent])){
			//当前根节点不满足条件,进行交换
			//交换后,继续向下调整
			std::swap(_heap[parent],_heap[child]);
			parent = child;
			child = parent*2;
		}else{
			//当前已满足最大/小堆,结束调整
			break;
		}
	}
}

//向上调整
//时间复杂度O(lgN)
template<typename T,typename Com>
void Heap<T,Com>::_AdjustUp(int index){
	int parent = index;
	int child = parent*2+1;
	while(parent>=0){
		//两个孩子中找较大/小的,进行交换
		if(child+1<_heap.size() &&
				Com()(_heap[child+1],_heap[child])){
			child++;
		}
		//孩子与父亲间找出较大/小的,进行交换
		if(Com()(_heap[child],_heap[parent])){
			//交换后,继续向上调整
			std::swap(_heap[parent],_heap[child]);
			child = parent;
			parent = (child-1)/2;
		}else{
			//不需要交换,已经成为堆
			break;
		}
	}
}

//插入
template<typename T,typename Com>
void Heap<T,Com>::Push(const T& e){
	_heap.push_back(e);
	_AdjustUp((_heap.size()-2)/2);
}

//删除
template<typename T,typename Com>
void Heap<T,Com>::Pop(){
	std::swap(_heap[0],_heap[_heap.size()-1]);
	_AdjustDown(0);
	_heap.pop_back();
}

//判断是是否为堆
template<typename T,typename Com>
bool Heap<T,Com>::CheckIsHeap(){
	return _CheckIsHeap(0);
}

template<typename T,typename Com>
bool Heap<T,Com>::_CheckIsHeap(int index){
	if(index>_heap.size()){
		return true;
	}
	int parent = index;
	int child = parent*2+1;
	Com compare;
	if(compare(_heap[parent],_heap[child])&&
	(child+1>_heap.size() ||
	 compare(_heap[parent],_heap[child+1])))
		return _CheckIsHeap(child)&&_CheckIsHeap(child+1);
	}
	return false;
}
#endif
