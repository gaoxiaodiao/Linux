/**************************************
*文件说明:test.c
*作者:高小调
*创建时间:2017年07月16日 星期日 20时52分09秒
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
#include<unistd.h>
#include<stdio.h>
int main(){
	int i;
	for(i=0;i<2;i++){
		fork();
		printf("-");
	}
	return 0;
}
