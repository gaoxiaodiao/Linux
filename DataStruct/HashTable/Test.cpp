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
	/*
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
	*/
	//测试冲突、二次扩容后冲突处理、删除
	HashTable<int,int> ht2(10);
	ht2.Insert(0,15465123);		//0
	ht2.Insert(1,14565123);		//1
	ht2.Insert(2,15112123);		//2
	ht2.Insert(7,15465123);		//0冲突 探测为3
	ht2.Insert(8,15415623);		//1冲突	探测为4
	ht2.Insert(9,15456823);		//2冲突 探测为5
	for(int i=0; i<3; ++i){
		std::pair<typename HashTable<int,int>::Node*,bool> ret1;	
		std::pair<typename HashTable<int,int>::Node*,bool> ret2;
		ret1 = ht2.Find(i);
		ret2 = ht2.Find(i+7);
		if(ret1.second){
			std::cout<<i<<":"<<ret1.first->_value<<std::endl;
		}else{
			std::cout<<i<<":没找到"<<std::endl;
		}
		if(ret2.second){
			std::cout<<i+7<<":"<<ret2.first->_value<<std::endl;
		}else{
			std::cout<<i+7<<":没找到"<<std::endl;
		}
	}
	std::cout<<std::endl;
	ht2.Insert(3,4564561);	//扩容为53
	ht2.Insert(4,4564561);
	ht2.Insert(5,4564561);
	ht2.Insert(6,4564561);
	//扩容后,再次打印
	for(int i=0; i<10; ++i){
		std::pair<typename HashTable<int,int>::Node*,bool> ret;	
		ret = ht2.Find(i);
		if(ret.second){
			std::cout<<i<<":"<<ret.first->_value<<std::endl;
		}else{
			std::cout<<i<<":没找到"<<std::endl;
		}
	}
	std::cout<<std::endl;
	ht2.Remove(1);
	ht2.Remove(3);
	ht2.Remove(5);
	ht2.Remove(7);
	ht2.Remove(9);
	//删除后,再次打印	
	for(int i=0; i<10; ++i){
		std::pair<typename HashTable<int,int>::Node*,bool> ret;	
		ret = ht2.Find(i);
		if(ret.second){
			std::cout<<i<<":"<<ret.first->_value<<std::endl;
		}else{
			std::cout<<i<<":没找到"<<std::endl;
		}
	}
}
int main(){
	TestHashTable();
	return 0;
}
