/**************************************
*文件说明:测试BitMap
*作者:高小调
*创建时间:Thu 20 Apr 2017 03:01:57 PM CST
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
#include<iostream>
#include"BitMap.hpp"
void TestBitMap(){
	BitMap bm(30);
	//输出
	for(int i=0; i<30; ++i){
		std::cout<<bm.Get(i);
		if((i+1)%5==0)
			std::cout<<std::endl;
	}
	std::cout<<std::endl<<std::endl;;
	/*
	//奇数置1
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
	*/
	/*
	//偶数置1
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
	*/
		
	//全部置1
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
	TestBitMap();
	return 0;
}

