/**************************************
*文件说明:Test.cpp
*作者:高小调
*创建时间:2017年04月19日 星期三 19时55分52秒
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
#include<iostream>
using namespace std;
#define __STRING_DEBUG__
#include"2017-04-19.h"
void TestString(){
	String s1(NULL);
	String s2;
	String s3("Hello World!");
	cout<<"s1:"<<static_cast<const void *>(s1.c_str())<<endl;
	cout<<"s2:"<<static_cast<const void *>(s2.c_str())<<endl;
	cout<<"s3:"<<static_cast<const void *>(s3.c_str())<<endl;
	String s4(s3);
	cout<<"s4:"<<static_cast<const void *>(s4.c_str())<<endl;
	s4 = s2;
	cout<<"s4 = s2 赋值完后:"<<endl;
	cout<<"s2:"<<static_cast<const void *>(s2.c_str())<<endl;
	cout<<"s4:"<<static_cast<const void *>(s4.c_str())<<endl;
}
int main(){
	TestString();
	return 0;
}
