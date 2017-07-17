////////////////////////////////////
//文件说明:MyString.cpp
//作者:高小调
//创建时间:2017年07月13日 星期四 18时10分31秒
//开发环境:Kali Linux/g++ v6.3.0
////////////////////////////////////
#pragma once
#include<cstring>
#include<iostream>
using std::swap;
using std::cout;
using std::endl;
class String{
public:
	//构造函数
	String(const char* str = ""){
		if(str==NULL){
			_str = new char[1];
			*_str = '\0';
		}else{
			_str = new char[strlen(str)+1];
			strcpy(_str,str);
		}
	}
	//拷贝构造
	String(const String& s)
		:_str(NULL){
		String tmp(s._str);
		swap(tmp._str,_str);
	}
	//赋值运算符重载
	String &operator=(const String &s){
		if(_str!=s._str){
			String tmp(s);
			swap(_str,tmp._str);
		}
		return *this;
	}
	//析构
	~String(){
		if(_str != NULL){
			delete []_str;
		}
	}
	const char* CStr(){
		return _str;
	}
private:
	char *_str;
};

int main(){
	String str1;
	String str2("i am str2");
	String str3("i am str3");
	String str4("i am str4");
	String str5("i am str5");
	str3 = str5;
	str4 = str2;
	String str6(str5);
	cout<<str1.CStr()<<endl;
	cout<<str2.CStr()<<endl;
	cout<<str3.CStr()<<endl;
	cout<<str4.CStr()<<endl;
	cout<<str5.CStr()<<endl;
	cout<<str6.CStr()<<endl;
	return 0;
}
