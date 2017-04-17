/**************************************
*文件说明:判断出栈序列是否合法
*作者:高小调
*创建时间:2017年04月16日 星期日 19时45分43秒
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
#include<stack>
template<typename T>
bool CheckStackArrayIsLegal(T *in,T *out,size_t size){
	std::stack<T> s;
	size_t indexIn = 0;
	size_t indexOut = 0;
	
	while(!s.empty() || indexOut<size){
		//如果入栈序列不等于出栈序列,则入栈序列入栈
		while(indexIn<size && in[indexIn]!=out[indexOut]){
			s.push(in[indexIn++]);
		}
		if(indexIn <size){
			//此时压入的入栈序列等于出栈序列
			s.push(in[indexIn]);
			++indexIn;
		}
		if(indexIn>=size && s.top()!=out[indexOut]){
			//如果入栈序列已经结束、并且栈顶元素不等于出栈序列
			//则说明当前序列不匹配
			return false;
		}
		while(!s.empty() && s.top()==out[indexOut]){
			//此时,栈顶元素与出栈序列相等,则出栈,出栈序列后移
			s.pop();
			++indexOut;
		}

	}
	return true;
}
