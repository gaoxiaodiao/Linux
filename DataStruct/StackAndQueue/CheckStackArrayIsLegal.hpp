////////////////////////////////////
//文件说明:CheckStackArrayIsLeal.hpp
//作者:高小调
//创建时间:2017年06月18日 星期日 08时40分06秒
//开发环境:Kali Linux/g++ v6.3.0
////////////////////////////////////
#include<stack>
using std::stack;
bool CheckStackArrayIsLegal(int in[],int out[],int size){
	stack<int> s;
	int inIndex = 0;
	int outIndex = 0;
	while(inIndex<size && outIndex<size){

		while(inIndex<size&&in[inIndex]!=out[outIndex]){
			s.push(in[inIndex]);
			inIndex++;
		}
		
		
		while(inIndex<size&&outIndex<size&&in[inIndex]==out[outIndex]){
			inIndex++;
			outIndex++;
		}

		while(!s.empty() && outIndex<size && s.top() == out[outIndex]){
			outIndex++;
			s.pop();
		}
	}
	return s.empty();
}
