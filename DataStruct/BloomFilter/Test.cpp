/**************************************
*文件说明:测试文件
*作者:高小调
*创建时间:2017年04月28日 星期五 13时56分29秒
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
#include"BitMap.h"
#include<iostream>
#include"BloomFilter.hpp"
using std::cout;
using std::endl;
void TestBloomFilter(){
	BloomFilter<string> bf(10);
	const char *url1 = "https://github.com/gaoxiaodiao";
	const char *url2 = "https://github.com/gaoxiaodiao/Linux";
    const char *url3 = "http://blog.gaoxiaodiao.com";
	const char *url4 = "https://github.com/gaoxiaodiao/CodePractice";
	const char *url5 = "https://github.com/gaoxiaodiao/Paddle";	
	bf.Set(url1);
	bf.Set(url2);
	bf.Set(url3);
	bf.Set(url4);
	bf.Set(url5);
	cout<<bf.Get(url1)<<endl;
	cout<<bf.Get(url2)<<endl;
	cout<<bf.Get(url3)<<endl;
	cout<<bf.Get(url4)<<endl;
	cout<<bf.Get(url5)<<endl;
	cout<<bf.Get("http://baidu.com")<<endl;
}
void TestBitMap(){
	BitMap bm(30);
	//输出
	for(int i=0; i<30; ++i){
		std::cout<<bm.Get(i);
		if((i+1)%5==0)
			std::cout<<std::endl;
	}
	std::cout<<std::endl<<std::endl;;
	
	//奇数置1
	cout<<"奇数置1"<<endl;
	for(int i=0; i<30; ++i){
		if(!(i%2)){
			bm.Set(i);
		}
	}
	//输出
	for(int i=0; i<30; ++i){
		std::cout<<bm.Get(i);
		if((i+1)%5==0)
			std::cout<<std::endl;
	}
	std::cout<<std::endl<<std::endl;
	
	//奇数置0
	cout<<"奇数置0"<<endl;
	for(int i=0; i<30; ++i){
		if(!(i%2)){
			bm.Reset(i);
		}
	}
	//输出
	for(int i=0; i<30; ++i){
		std::cout<<bm.Get(i);
		if((i+1)%5==0)
			std::cout<<std::endl;
	}
	cout<<endl;
	
	//偶数置1
	cout<<"偶数置1"<<endl;
	for(int i=0; i<30; ++i){
		if(i%2){
			bm.Set(i);
		}
	}
	//输出
	for(int i=0; i<30; ++i){
		std::cout<<bm.Get(i);
		if((i+1)%5==0)
			std::cout<<std::endl;
	}
	std::cout<<std::endl<<std::endl;
	
	//偶数置0
	cout<<"偶数置0"<<endl;
	for(int i=0; i<30; ++i){
		if(i%2){
			bm.Reset(i);
		}
	}
	//输出
	for(int i=0; i<30; ++i){
		std::cout<<bm.Get(i);
		if((i+1)%5==0)
			std::cout<<std::endl;
	}
	cout<<endl;

	//全部置1
	cout<<"全部置1"<<endl;
	for(int i=0; i<30; ++i){
		bm.Set(i);
	}
	//输出
	for(int i=0; i<30; ++i){
		std::cout<<bm.Get(i);
		if((i+1)%5==0)
			std::cout<<std::endl;
	}
	std::cout<<std::endl<<std::endl;
	
	//全部置0
	cout<<"全部清0"<<endl;
	for(int i=0; i<30; ++i){
		bm.Reset(i);
	}
	//输出
	for(int i=0; i<30; ++i){
		std::cout<<bm.Get(i);
		if((i+1)%5==0)
			std::cout<<std::endl;
	}
}

int main(){
	//TestBitMap();
	TestBloomFilter();
	return 0;
}
