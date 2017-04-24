/**************************************
*文件说明:位图相关实现
*作者:高小调
*创建时间:2017年04月24日 星期一 10时46分55秒
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
#include"BitMap.h"
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
}
