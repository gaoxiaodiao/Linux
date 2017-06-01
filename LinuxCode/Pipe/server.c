/**************************************
*文件说明:server.c
*作者:高小调
*创建时间:2017年05月15日 星期一 21时46分09秒
*开发环境:Kali Linux/g++ v6.3.0
***************************************/
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
int main(){
	if(mkfifo("./myfifo",S_IFIFO|0666)==-1){
		perror("mkfifo");
		//return 1;
	}
	int fd = open("./myfifo",O_RDONLY);
	if(fd==-1){
		perror("open");
		return 2;
	}
	char buff[1024]={0};
	while(1){
		ssize_t s = read(fd,buff,sizeof(buff)-1);
		buff[s] = 0;
		printf("%s\n",buff);
	}
	return 0;
}
