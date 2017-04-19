/**************************************
*文件说明:面试题01:赋值运算符函数(扩展实现简单的String类)
*作者:高小调
*创建时间:2017年04月19日 星期三 19时45分50秒
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
#ifndef __STRING_H__
#define __STRING_H__
#include<cstring>
class String{
public:
	String(const char *str='\0');		//构造函数
	String(const String &);				//拷贝构造
	String& operator=(const String&);	//赋值运算符重载
	~String();							//析构函数
	char *c_str();						//返回_str指针(测试使用)
private:
	char *_str;
};

//构造函数
String::String(const char *str)
	:_str(NULL){
		if(str==NULL){
			//多开辟一个字节,方便调用delete[]
			_str = new char[1];
			*_str = '\0';
		}else{
			//多开辟一个字节,用于存放'\0'
			_str = new char[std::strlen(str)+1];
			std::strcpy(_str,str);
		}
	}

//拷贝构造
String::String(const String &s)
	:_str(NULL){		//此处必须初始化为NULL,否则tmp析构会出错
	String tmp(s._str);
#ifdef __STRING_DEBUG__
	std::cout<<"\033[33m"<<static_cast<const void*>(_str)<<"变成了"<<static_cast<const void*>(tmp._str)<<"\033[0m"<<std::endl;
#endif
	std::swap(_str,tmp._str);
}

//赋值运算符重载
String &String::operator=(const String &s){
	if(_str!=s._str){
		String tmp(s);
		std::swap(_str,tmp._str);
	}
	return *this;
}

//析构函数
String::~String(){
	if(_str!=NULL){
#ifdef __STRING_DEBUG__
		std::cout<<"\033[32m"<<static_cast<void *>(_str)<<"被释放"<<"\033[0m"<<std::endl;
#endif
		delete[] _str;
		_str = NULL;
	}
}

char *String::c_str(){
	return _str;
}
#endif
