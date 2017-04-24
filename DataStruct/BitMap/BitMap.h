/**************************************
*文件说明:BitMap.cpp
*作者:高小调
*创建时间:Thu 20 Apr 2017 02:41:01 PM CST
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
#include<vector>
typedef unsigned long size_t;
class BitMap{
public:
	BitMap(size_t size = 1024);	//构造函数
public:
	void Set(size_t value);		//设置某个位为1
	void Reset(size_t value);	//设置某个位为0
	bool Get(size_t value);		//获取某个位置的值
private:
	std::vector<char> _array;
};
/*
//构造函数的实现
BitMap::BitMap(size_t size){
	//每个char占8位,因此要除以8
	_array.resize((size>>3)+1);
}
//将 某个位 置1
void BitMap::Set(size_t value){
	size_t index = value>>3;	//计算char数组的下标 value/8
	size_t num = value%8;		//计算第num个位
	_array[index] |= (1<<num);
}
//将 某个位 置0
void BitMap::Reset(size_t value){
	size_t index = value>>3;
	size_t num = value%8;
	_array[index] &= ~(1<<num);
}
//获取某个位置的值
bool BitMap::Get(size_t value){
	size_t index = value>>3;
	size_t num = value%8;
	return _array[index]&(1<<num);
}*/
