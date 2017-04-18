/**************************************
*文件说明:测试哈希表
*作者:高小调
*创建时间:2017年04月18日 星期二 11时29分59秒
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
#include<iostream>
#include<string>
#include"HashTable.hpp"
void TestHashTable(){
	//测试基本的插入、扩容、查找
	HashTable<int,const char*> ht1(0);
	ht1.Insert(1,"Hello");	//第一次开辟7个空间
	ht1.Insert(2,"World");
	ht1.Insert(3,"My");
	ht1.Insert(4,"Name");
	ht1.Insert(5,"Is");
	ht1.Insert(6,"Gao");//在此负载因子大于0.7,为提高效率,需要进行扩容处理
	ht1.Insert(7,"Xiao");
	ht1.Insert(8,"Diao");	
	for(int i=1; i<=8; ++i){
		std::pair<typename HashTable<int,const char*>::Node*,bool> ret;
		ret = ht1.Find(i);
		if(ret.second){
			std::cout<<i<<":"<<ret.first->_value<<std::endl;
		}else{
			std::cout<<i<<":未找到"<<std::endl;
		}
	}

}
int main(){
	TestHashTable();
	return 0;
}
