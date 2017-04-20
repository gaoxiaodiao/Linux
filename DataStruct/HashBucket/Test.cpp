/**************************************
*文件说明:Test.cpp
*作者:高小调
*创建时间:2017年04月19日 星期三 09时23分26秒
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
#include<iostream>
#define __HASHBUCKET_DEBUG__
#include"HashBucket.hpp"
void TestHashBucket(){
	/*
	//测试构造、析构、查找、插入、扩容、
	//排查出错误:在插入删除时,没有进行_size的++--
	HashBucket<int,const char*> hb(0);
	hb.Insert(0,"春种一粒粟,");		//第一次扩容7
	hb.Insert(1,"秋成万颗子.");	
	hb.Insert(2,"四海无闲田,");
	hb.Insert(3,"农夫犹饿死.");
	hb.Insert(4,"锄禾日当午,");
	hb.Insert(5,"汗滴禾下土.");
	hb.Insert(6,"谁知盘中餐,");		//第二次扩容,素数表
	hb.Insert(7,"粒粒皆辛苦.");
	for(int i=0; i<8; ++i){
		typename HashBucket<int,const char*>::Node* ret = hb.Find(i);
		if(ret!=NULL){
			std::cout<<i<<":"<<ret->_kv.second<<std::endl;
		}else{
			std::cout<<i<<":"<<"NULL"<<std::endl;
		}
	}
	//在测试析构的时候遇到两个问题:
	//1.为什么析构了两次?
	//2.为什么第二次析构的时候,诗经的顺序是乱的?
	//问题1:经过我的一阵头脑风暴后,开启gdb单步调试了进去,发现原来第一次析构是在扩容的时候.第二次析构,很明显是hb变量出了函数作用域,不得已调用析构函数.
	//问题2:再次开启gdb调试进去后发现,因为第二次扩容是容量变成了53,所以0到7的模53时,位置肯定不会在是0-7了,因此,就出现了乱序的问题.
	//
	*/
	//测试删除、迭代器
	//测试迭代器时,又遇到两个问题:
	//1.编译不通过,折腾了将近一个多小时.
	//2.编译通过了,但是输出的次序有问题.
	//问题1:在敲迭代器时,忘了给_hb加星号,构造函数中也忘了加*号,
	//写的时候,心里明明想的传指针比传整个哈希表效率更好,但写的时候还是忘了.
	//问题2:还是昨天的问题2,很明显昨天问题2的答案是错的,虽然与扩容有,但程序输出
	//错误并不是因为扩容,而是因为我把哈希表内部哈希函数写错了!!!!!
	//写%的时候,敲成了&,肯定就错了!!!!!
	//唉..这些低级错误让我倍受打击,什么时候我的代码能力变得这么差了??????
	//淡淡的忧伤!
	HashBucket<int,const char*> hb2(10);
	hb2.Insert(0,"离离原上草,");
	hb2.Insert(1,"一岁一枯荣.");
	hb2.Insert(2,"野火烧不尽,");
	hb2.Insert(3,"春风吹又生.");
	hb2.Insert(4,"远芳侵古道,");
	hb2.Insert(5,"晴翠接荒城.");
	hb2.Insert(6,"又送王孙去,");
	hb2.Insert(7,"萋萋满别情.");
	HashBucket<int,const char*>::Iterator it = hb2.Begin();
	while(it!=hb2.End()){
		std::cout<<it->first<<":"<<it->second<<std::endl;
		++it;
	}
	hb2.Remove(0);
	hb2.Remove(1);
	hb2.Remove(2);
	hb2.Remove(3);
	hb2.Remove(4);
	hb2.Remove(5);
	hb2.Remove(6);
	hb2.Remove(7);
}
int main(){
	TestHashBucket();
	return 0;
}
