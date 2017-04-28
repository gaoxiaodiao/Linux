/**************************************
*文件说明:布隆过滤器相关声明及实现
*作者:高小调
*创建时间:2017年04月28日 星期五 14时15分52秒
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
#ifndef __BLOOMFILTER_HPP__
#define __BLOOMFILTER_HPP__
#include<string>
#include"BitMap.h"
#include"HashFunc.h"
using std::string;

struct _HashFunc1{
	size_t operator()(const string &s){
		return SDBMHash(s.c_str());
	}
};


struct _HashFunc2{
	size_t operator()(const string &s){
		return RSHash(s.c_str());
	}
};


struct _HashFunc3{
	size_t operator()(const string &s){
		return APHash(s.c_str());
	}
};


struct _HashFunc4{
	size_t operator()(const string &s){
		return JSHash(s.c_str());
	}
};


struct _HashFunc5{
	size_t operator()(const string &s){
		return BKDRHash(s.c_str());
	}
};

template<typename K=string,
	typename HashFunc1 = _HashFunc1,
	typename HashFunc2 = _HashFunc2,
	typename HashFunc3 = _HashFunc3,
	typename HashFunc4 = _HashFunc4,
	typename HashFunc5 = _HashFunc5>
class BloomFilter{
	public:
		BloomFilter(size_t size)
			:_bm(size*5*2)
			,_size(size*5*2){}
	public:
		void Set(const K& key){
			size_t hash1 = HashFunc1()(key);
			size_t hash2 = HashFunc2()(key);
			size_t hash3 = HashFunc3()(key);
			size_t hash4 = HashFunc4()(key);
			size_t hash5 = HashFunc5()(key);
			
			_bm.Set(hash1%_size);
			_bm.Set(hash2%_size);
			_bm.Set(hash3%_size);
			_bm.Set(hash4%_size);
			_bm.Set(hash5%_size);
		}
		bool Get(const K& key){
			size_t hash1 = HashFunc1()(key)%_size;
			if(!_bm.Get(hash1)){
				return false;
			}
			size_t hash2 = HashFunc2()(key)%_size;
			if(!_bm.Get(hash2)){
				return false;
			}
			size_t hash3 = HashFunc3()(key)%_size;
			if(!_bm.Get(hash3)){
				return false;
			}
			size_t hash4 = HashFunc4()(key)%_size;
			if(!_bm.Get(hash4)){
				return false;
			}
			size_t hash5 = HashFunc5()(key)%_size;
			if(!_bm.Get(hash5)){
				return false;
			}
			return true;
		}
	private:
		BitMap _bm;
		size_t _size;
};
#endif
