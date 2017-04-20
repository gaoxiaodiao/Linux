/**************************************
*文件说明:面试题04:替换空格
*作者:高小调
*创建时间:Thu 20 Apr 2017 02:21:50 PM CST
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
#include<iostream>
#include"2017-04-20.h"
void TestReplaceBlank(){
	char str1[30] = "we are happy";		//空格在中间
	char str2[30] = " we are happy";	//空格在开始
	char str3[30] = "we are happy ";	//空格在最后
	char str4[30] = "             ";	//连续空格
	char str5[30] = "Hello";			//没有空格
	char *str6 = NULL;					//空指针
	std::cout<<ReplaceBlank(str1)<<std::endl;
	std::cout<<ReplaceBlank(str2)<<std::endl;
	std::cout<<ReplaceBlank(str3)<<std::endl;
	std::cout<<ReplaceBlank(str4)<<std::endl;
	std::cout<<ReplaceBlank(str5)<<std::endl;
	std::cout<<ReplaceBlank(str6)<<std::endl;	//引发断言错误
}
int main(){
	TestReplaceBlank();
	return 0;
}
