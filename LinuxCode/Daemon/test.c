////////////////////////////////////
//文件说明:守护进程相关代码
//作者:高小调
//创建时间:2017年06月27日 星期二 20时08分29秒
//开发环境:Kali Linux/g++ v6.3.0
////////////////////////////////////

#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
void myDaemon(){
	umask(0);			//1.将umask设置为0,方便解决守护进程创建文件的权限问题
	chdir("/");			//2.改变进程主工作目录
	if(fork() > 0){		//3.fork子进程,父进程退出(进程组组长不能运行setid函数)
		exit(0);
	}
	setsid();			//4.在子进程中新建会话!
	close(0);			//5.关闭不必要的文件描述符
	close(1);
	close(2);
}
int main(){
	myDaemon();
	//打开其他终端的设备文件
	int fd = open("/dev/pts/2",O_WRONLY);
	if(fd == -1){
		return -1;
	}
	char str[]="Hello World!\n";
	while(1){
		//不断向其他终端发送Hello World!
		write(fd,str,sizeof(str));
		sleep(1);
	}
	return 0;
}
