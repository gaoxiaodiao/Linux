/**************************************
*文件说明:Compress.h
*作者:高小调
*创建时间:2017年07月13日 星期四 16时21分44秒
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
#pragma once
#include<cstdio>
#include<string>
using std::string;
struct CharInfo{
	unsigned char ch;
	int count;
	string code;
	CharInfo(unsigned char c)
		:ch(c)
		,count(0)
		,code(){}
	CharInfo operator+(const CharInfo r){
		r.count += count;
		return r;
	}
};
class Compress{
public:
	Compress(const char* filename){
		_in = fopen(filename,"r");
		if(_in==NULL){
			perror("fopen");
		}
		memset(_hash,sizeof(_hash),0);
	}
	~Compress(){
		if(_in!=NULL){
			fclose(_in);
		}
	}

private:
	FILE* _in;
	FILE* _out;
	char _hash[256];
};
