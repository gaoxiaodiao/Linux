////////////////////////////////////
//文件说明:ArpSpoof.c
//作者:高小调
//创建时间:2017年07月05日 星期三 08时48分14秒
//开发环境:Kali Linux/g++ v6.3.0
////////////////////////////////////
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<ifaddrs.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<net/if.h>
#include<sys/ioctl.h>
//获取本地ip与mac地址
void get_local_info(const char* device,char ip[],char *mac){
	int sd = socket(AF_INET,SOCK_DGRAM,0);
	if(sd == -1){
		perror("socket");
		exit(1);
	}
	struct sockaddr_in addr;
	struct ifreq ifr;
	strcpy(ifr.ifr_name,device);
	if(ioctl(sd,SIOCGIFADDR,&ifr) < 0){
		//No such device
		perror("ioctl");
		exit(2);
	}
	memcpy(&addr,&ifr.ifr_addr,sizeof(addr));
	char * tmp = inet_ntoa(addr.sin_addr);
	strcpy(ip,tmp);
	if(ioctl(sd,SIOCGIFHWADDR,&ifr) < 0){
		perror("ioctl");
		exit(2);
	}
	//memcpy(mac,ifr.ifr_hwaddr.sa_data,sizeof(ifr.ifr_hwaddr.sa_data)); bug!
	printf("%d\n",sizeof(ifr.ifr_hwaddr.sa_data));
	memcpy(mac,ifr.ifr_hwaddr.sa_data,6);
	close(sd);
}

void test_get_local_info(){
	char ip[33] = {'H','E','L','L','O'};
	unsigned char mac[6] = {0};
	get_local_info("wlan0",ip,mac);
	for(int i=0; i<5; ++i){
		printf("%02x:",mac[i]);
	}
	printf("%02x\n",mac[5]);
}
int main(){
	test_get_local_info();
	return 0;
}
