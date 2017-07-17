////////////////////////////////////
//文件说明:Test.cpp
//作者:高小调
//创建时间:2017年07月13日 星期四 18时02分35秒
//开发环境:Kali Linux/g++ v6.3.0
////////////////////////////////////
#include"LinkList.h"
#include"MergeLinkList.h"
#include"2017-07-14.h"
#include"2017-07-15.h"
#include"2017-07-16.h"
void Test1(){
	Node_p head1 = CreateLinkList(1,12,2);
	Node_p head2 = CreateLinkList(2,10,2);
	PrintLinkList(head1);
	PrintLinkList(head2);
	Node_p newHead = MergeLinkList(head1,head2);
	PrintLinkList(newHead);

}
int main(){
	Test4();
	return 0;
}
