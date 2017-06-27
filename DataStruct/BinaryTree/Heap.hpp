////////////////////////////////////
//文件说明:Heap.hpp
//作者:高小调
//创建时间:2017年06月20日 星期二 11时32分00秒
//开发环境:Kali Linux/g++ v6.3.0
////////////////////////////////////
#ifndef __HEAP_H__
#define __HEAP_H__
#include<vector>
#include<functional>
using std::vector;
using std::less;
using std::swap;
using std::greater;
template<typename T,typename Com=less<T>>
class Heap{
public:
	Heap(T *arr,int size)
		:_heap(arr,arr+size-1){
			for(int i=(size-2)/2; i>=0; --i){
				AdjustDown(i);
			}
		}
	void Push(const T &e){
		_heap.push_back(e);
		AdjustUp((_heap.size()-2)/2);
	}
	void Pop(){
		swap(_heap[0],_heap[_heap.size()-1]);
		_heap.pop_back();
		AdjustDown(0);
	}
	void Print(){
		for(int i=0; i<_heap.size(); ++i){
			cout<<_heap[i]<<" ";
		}
		cout<<endl;
	}
protected:
	void AdjustDown(int index){
		int parent = index;
		int child = parent*2+1;
		Com compare;
		while( child<_heap.size() ){
			if(child+1<_heap.size() && 
					compare(_heap[child+1],_heap[child])){
				child++;
			}
			if(compare(_heap[child],_heap[parent])){
				swap(_heap[parent],_heap[child]);
				parent = child;
				child = parent*2+1;
			}else{
				break;
			}
		}
	}
	void AdjustUp(int index){
		int parent = index;
		int child = parent*2+1;
		Com compare;
		while(parent>=0){
			if(child+1<_heap.size() 
					&&compare(_heap[child+1],_heap[child])){
				child++;
			}
			if(compare(_heap[child],_heap[parent]) ){
				swap(_heap[parent],_heap[child]);
				child = parent;
				parent = (child-1)/2;
			}else{
				break;
			}
		}
	}

private:
	vector<T> _heap;
};
#endif
