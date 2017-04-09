/**************************************
*文件说明:test.cpp
*作者:高小调
*创建时间:2017年04月08日 星期六 20时50分15秒
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
#include"RBTree.hpp"
int main(){
	RBTree<int,int> rbt;
	int arr[][10] = {{2,4,5,3,6,9,1,0,7,8},
					{4,2,6,1,3,5,15,7,16,14}};
	for(int i=0; i<sizeof(arr)/sizeof(*arr); ++i){
		for(int j=0; j<sizeof(*arr)/sizeof(**arr); ++j){
			rbt.Insert(arr[i][j],i);
			std::cout<<arr[i][j]<<":"<<rbt.CheckIsBalance()<<std::endl;
		}
		rbt.InOrderNonR();
		std::cout<<std::endl;
	}
	return 0;
}
