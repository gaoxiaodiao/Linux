/**************************************
*文件说明:MyShell
*作者:高小调
*创建时间:2017年05月08日 星期一 19时07分39秒
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<pwd.h>
void MyShell(){
	//输出用户相关信息
	char hostname[32] = {0};
	if(gethostname(hostname,sizeof(hostname)-1)){
		perror("gethostname:");
		exit(1);
	}
	printf("%s@%s:%s$",getenv("LOGNAME"),hostname,getenv("PWD"));
	fflush(stdout);
	
	//获取命令及参数
	char buff[1024] = {0};
	ssize_t s = read(0,buff,sizeof(buff)-1);
	if(s<0){
		perror("read:");
		exit(2);
	}
	buff[s-1] = 0;
	//解析
	char *start = buff;
	char *_argv[32]={0};
	_argv[0] = buff;
	int i = 1;
	int flag = 0;
	char *filename = 0;
	while(*start!=0){
		if(*start==' '){
			*start = 0;
			start++;
			if(*start=='>'){
				flag = 1;
				start++;
				while(*start!=0&&*start==' '){
					++start;
				}
				filename = start;
				break;
			}
			_argv[i++] = start;
		}else{
			start++;
		}
	}
	if(flag == 1){
		for(int i=0; _argv[i]!=0; ++i){
			printf("%s ",_argv[i]);
		}
		printf("\n");
		printf("%s\n",filename);
	}
	//创建子进程,执行命令
	pid_t pid = fork();
	if(pid==0){//child 程序替换
		if(flag == 1){
			close(1);
			int fd = open(filename,O_WRONLY|O_CREAT,777);
			if(fd<0){
				perror("open:");
			}
		}
		execvp(_argv[0],_argv);
		exit(4);
	}else{//father 回收子进程
		pid_t ret = waitpid(pid,NULL,0);
		if(ret<0){
			perror("wait:");
		}
	}
}
int main(){
	while(1){
		MyShell();
	}
	return 0;
}
