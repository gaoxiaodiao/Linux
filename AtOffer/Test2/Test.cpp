/**************************************
*文件说明:Test.cpp
*作者:高小调
*创建时间:Thu 20 Apr 2017 01:33:46 PM CST
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
#include<iostream>
#include"2017-04-20.h"
void TestYangMatrixFind(){
	int arr1[4][4]={{1,2,8,9}
					,{2,4,9,12}
					,{4,7,10,13}
					,{6,8,11,15}};
	int arr2[4][3] = {{1,2,8}
					,{2,4,9}
					,{4,7,10}
					,{6,8,11}};
	int arr3[3][4] = {{1,2,8,9}
					,{2,4,9,12}
					,{4,7,10,13}};
	std::cout<<YangMatrixFind((int*)arr1,4,4,1)<<std::endl;				//找最小值
	std::cout<<YangMatrixFind((int*)arr1,4,4,15)<<std::endl;			//找最大值
	std::cout<<YangMatrixFind((int*)arr1,4,4,9)<<std::endl;				//找介于最小值与最大值之间
	std::cout<<YangMatrixFind((int*)arr1,4,4,-1)<<std::endl;			//不存在的最小值
	std::cout<<YangMatrixFind((int*)arr1,4,4,5)<<std::endl;				//不存在介于最小值与最大值之间
	std::cout<<YangMatrixFind((int*)arr1,4,4,16)<<std::endl<<std::endl; //不存在的最大值

	std::cout<<YangMatrixFind((int*)arr2,4,3,1)<<std::endl;				 //找最小值
	std::cout<<YangMatrixFind((int*)arr2,4,3,11)<<std::endl;			 //找最大值
	std::cout<<YangMatrixFind((int*)arr2,4,3,7)<<std::endl;				 //找介于最小值与最大值之间
	std::cout<<YangMatrixFind((int*)arr2,4,3,-1)<<std::endl;			 //不存在的最小值
	std::cout<<YangMatrixFind((int*)arr1,4,4,5)<<std::endl;				//不存在介于最小值与最大值之间
	std::cout<<YangMatrixFind((int*)arr2,4,3,16)<<std::endl<<std::endl;	//不存在的最大值

	std::cout<<YangMatrixFind((int*)arr3,3,4,1)<<std::endl;				//找最小值
	std::cout<<YangMatrixFind((int*)arr3,3,4,13)<<std::endl;			//找最大值
	std::cout<<YangMatrixFind((int*)arr3,3,4,9)<<std::endl;				//找介于最小值与最大值之间
	std::cout<<YangMatrixFind((int*)arr3,3,4,-1)<<std::endl;			//不存在的最小值
	std::cout<<YangMatrixFind((int*)arr1,4,4,5)<<std::endl;				//不存在介于最小值与最大值之间
	std::cout<<YangMatrixFind((int*)arr3,3,4,16)<<std::endl<<std::endl; //不存在的最大值
}
int main(){
	TestYangMatrixFind();
	return 0;
}
