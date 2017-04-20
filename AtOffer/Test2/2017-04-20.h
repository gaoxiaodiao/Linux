/**************************************
*文件说明:面试题2:二维数组的查找(第一遍)
*作者:高小调
*创建时间:Thu 20 Apr 2017 11:36:54 AM CST
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
// 1 2 3 4
// 2 3 4 5
// 3 4 5 6
// 5 6 7 8
#include<cassert>
bool YangMatrixFind(int *arr,int row,int col,int key){
	assert(arr&&row>0&&col>0);
	int x = 0;
	int y = col-1;
	while( x<row&& y>=0 ){
		if(arr[x*col+y] > key){
			--y;				
		}else if(arr[x*col+y] < key){
			++x;
		}else{
			return true;
		}
	}
	return false;
}
