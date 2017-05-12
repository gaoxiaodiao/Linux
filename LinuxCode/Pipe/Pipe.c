/**************************************
*文件说明:计算匿名管道与命名管道的容量
*作者:高小调
*创建时间:2017年05月12日 星期五 16时26分04秒
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

#include<sys/types.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<fcntl.h>
//匿名管道容量为65536
void Pipe1(){
	int fds[2] = {0};
	if(pipe(fds)<0){
		perror("pipe");
		exit(1);
	}
	//printf("%d,%d\n",fds[0],fds[1]);	
	pid_t pid = fork();
	if(pid==0){			//子进程
		close(fds[0]);	//关闭读
		int i = 0;
		const char* str = "1";
		while(1){
			ssize_t ret = write(fds[1],str,strlen(str));
			i+=1;
			printf("匿名管道已存入%d个字节,ret = %d\n",i,ret);
		}
		//为什么管道容量满了之后其ret仍然为1?
		printf("%d\n",i);
	}else if(pid>0){	//父进程
		printf("父进程:等待子进程!\n");
		//回收子进程
		int status = 0;
		pid_t ret = waitpid(pid,&status,0);
		if(ret>0){
						//成功回收!
		}else{
			perror("wait");
			exit(3);
		}
	}else{
		perror("fork");
		exit(2);
	}
}

void Pipe2(){
	umask(0);
	int ret = mkfifo("./myPipe",S_IFIFO|0666);
	if(ret==-1){
		perror("mkpipe");
		exit(1);
	}
	printf("父进程:创建管道文件完毕!ret=%d\n",ret);
	pid_t pid = fork();
	printf("父进程:创建子进程完毕!pid为:%d\n",pid);
	
	if(pid==0){	//child
		printf("子进程:进入子进程!\n");
		int fd = open("./myPipe",O_WRONLY);
		printf("子进程:打开管道文件!\n");
		if(fd==-1){
			perror("fd");
			exit(4);
		}
		printf("子进程:管道文件打开完毕!\n");
		int i = 0;
		const char* msg = "1";
		while(1){
			ssize_t ret = write(fd,msg,strlen(msg));
			++i;
			printf("已写入%d个字节ret = %d\n",i,ret);
		}
	}else if(pid>0){
		printf("父进程:等待回收子进程!\n");
		pid_t ret = waitpid(pid,NULL,0);
		if(ret<=0){
			perror("waitpid");
			exit(3);
		}
	}else{
		perror("fork");
	}
}
//打开管道文件并写入数据
void Pipe3(){
	int fd = open("./myPipe",O_WRONLY);
	printf("")
	printf("子进程:打开管道文件!\n");
	if(fd==-1){
		perror("fd");
		exit(4);
	}
	printf("子进程:管道文件打开完毕!\n");
	int i = 0;
	const char* msg = "1";
	while(1){
		ssize_t ret = write(fd,msg,strlen(msg));
		++i;
		printf("已写入%d个字节ret = %d\n",i,ret);
	}
}

int main(){
	//Pipe1();	
	//Pipe2();
	Pipe3();
	return 0;
}
