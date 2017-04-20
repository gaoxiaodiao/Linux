/**************************************
*文件说明:面试题04:替换空格
*作者:高小调
*创建时间:Thu 20 Apr 2017 02:24:21 PM CST
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
#include<cassert>
char* ReplaceBlank(char *str){
	assert(str);
	char *front = str;
	//1.计算空格数目
	int count = 0;
	while(*front){
		if(*front ==' '){
			++count;
		}
		++front;
	}
	//2.计算新字符串尾部
	char *back = front + count*2;
	//3.开始复制
	while(front!=back){
		//当前位置为空格
		if(*front==' '){
			*back-- = '0';
			*back-- = '2';
			*back-- = '%';
			front--;
		}else{
			*back-- = *front--;
		}
	}
	return str;
}
