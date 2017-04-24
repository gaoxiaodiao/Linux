/**************************************
*文件说明:堆的相关声明及实现
*作者:高小调
*创建时间:2017年04月24日 星期一 11时31分30秒
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
#ifndef __HEAP_H__
#define __HEAP_H__
#include<vector>
template<typename T,typename Com = std::Less<T>>
class Heap{
	public:
		Heap(T arr[],int size);	//构造函数
	public:
		void Push(const T&);	//入数据
		void Pop();				//出数据
	protected:
		void AdjustUp(int);		//向上调整
		void AdjustDown(int);	//向下调整
	private:
		Heap(const Heap& );
		Heap& operator=(const Heap&);
	private:
		std::vector<T> _heap;
};
#endif
