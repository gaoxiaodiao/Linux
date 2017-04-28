/**************************************
*文件说明:位图相关声明及实现
*作者:高小调
*创建时间:2017年04月28日 星期五 13时42分39秒
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
#ifndef __BITMAP_H__
#define __BITMAP_H__
#include<vector>
#include<cassert>
using std::vector;
typedef unsigned long size_t;
class BitMap{
	public:
		BitMap(size_t size=1024);		//位图的大小
	public:
		void Set(size_t pos);			//将指定位置1
		void Reset(size_t pos);			//将指定位清0
		bool Get(size_t pos);			//获取某个位的值
	private:
		vector<char> _array;
};
#endif
