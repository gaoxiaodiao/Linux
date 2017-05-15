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
#include<string.h>
int main(){
	int fd = open("./myfifo",O_WRONLY);
	if(fd==-1){
		perror("open");
		return 2;
	}
	char buff[1024]={0};
	while(1){
		ssize_t s = read(0,buff,sizeof(buff));
		buff[s] = 0;
		write(fd,buff,strlen(buff));
	}
	return 0;
}
