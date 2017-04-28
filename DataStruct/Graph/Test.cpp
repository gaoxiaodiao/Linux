/**************************************
*文件说明:测试图的相关实现
*作者:高小调
*创建时间:2017年04月28日 星期五 13时15分56秒
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
#include<iostream>
#include<string>
#define __GRAPHMATRIX_DEBUG__
#include"GraphMatrix.hpp"
using namespace std;
void TestGraphMatrix(){
	const char* arr[]={"北京","西安","咸阳","兰州","上海","武汉"};
	GraphMatrix<const char*,int> map(arr,sizeof(arr)/sizeof(*arr),0,true);
	map.AddEdge("北京","西安",500);
	map.AddEdge("北京","咸阳",300);
	map.AddEdge("兰州","北京",150);
	map.AddEdge("上海","武汉",8000);
	map.AddEdge("西安","武汉",10000);
	for(int i=0; i<sizeof(arr)/sizeof(*arr); ++i){
		for(int j=0; j<sizeof(arr)/sizeof(*arr); ++j){
			if(map._matrix[i][j]!=0){
				cout<<map._vertex[i]<<"->"<<map._vertex[j]<<"="<<map._matrix[i][j]<<endl;
			}
		}
	}

}
int main(){
	TestGraphMatrix();
	return 0;
}
