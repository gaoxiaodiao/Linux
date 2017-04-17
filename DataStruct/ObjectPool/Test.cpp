/**************************************
*文件说明:测试内存池
*作者:高小调
*创建时间:2017年04月17日 星期一 21时07分31秒
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
#include<iostream>
#include"ObjectPool.hpp"
void TestObjectPool(){
	ObjectPool<int> op(3);
	int *arr[10] ={0};
	for(int i=0; i<6; ++i){
		arr[i] = op.New();
		std::cout<<arr[i]<<std::endl;
	}
	//析构
	for(int i=5; i>=0; --i){
		op.Delete(arr[i]);
	}
	std::cout<<std::endl;
	//再次从链表中获取	
	for(int i=0; i<6; ++i){
		arr[i] = op.New();
		std::cout<<arr[i]<<std::endl;
	}
	std::cout<<std::endl;
	for(int i=6; i<10; ++i){
		arr[i] = op.New();
		std::cout<<arr[i]<<std::endl;
	}

}
int main(){
	TestObjectPool();
	return 0;
}
