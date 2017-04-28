/**************************************
*文件说明:位图相关实现
*作者:高小调
*创建时间:2017年04月28日 星期五 13时46分46秒
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
#include"BitMap.h"
BitMap::BitMap(size_t size){
	//一个char8位,因此只需要size/8+1个char
	_array.resize((size>>3)+1,0);
}

void BitMap::Set(size_t pos){
	assert(pos<_array.size()<<3);
	size_t index = pos>>3;	//pos/8
	size_t num = pos%8;
	_array[index] |= 1<<num;
}

void BitMap::Reset(size_t pos){
	assert(pos<_array.size()<<3);
	size_t index = pos>>3;
	size_t num = pos%8;
	_array[index] &= ~(1<<num);
}

bool BitMap::Get(size_t pos){
	//assert(pos<_array.size()<<3);
	size_t index = pos>>3;
	size_t num = pos%8;
	return _array[index]&(1<<num);
}
