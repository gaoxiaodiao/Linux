/**************************************
*文件说明:测试函数
*作者:高小调
*创建时间:2017年05月04日 星期四 14时55分37秒
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
#include"UnionSet.h"
#include<iostream>
using namespace std;

void TestUnionSet(){
	UnionSet us(10);
	us.Union(0,6);
	us.Union(0,7);
	us.Union(0,8);

	us.Union(1,4);
	us.Union(1,9);

	us.Union(2,3);
	us.Union(2,5);

	us.Print();

	us.Union(0,1);

	us.Print();

}
int Friends(int n,int m,int arr[][2]){
	UnionSet us(n+1);
	for(int i=0; i<m; ++i){
		us.Union(arr[i][0],arr[i][1]);
	}
	return us.GetUnionNum()-1;
}

void TestFriends(){
	int n = 5;
	int m = 3;
	int arr[][2]={{1,2},{2,3},{4,5}};
	cout<<Friends(n,m,arr)<<endl;;
}
int main(){
	TestFriends();
	//TestUnionSet();
	return 0;
}
