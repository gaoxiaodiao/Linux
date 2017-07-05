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
	if(sendto(sd,&request,sizeof(request),0,&sa,sizeof(sa)) < 0){
		perror("sendto");
		exit(-2);
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

void request_test(const char* intfc,const char* src,const char* dst){
	struct ethernet_packet ep;
	char sip[18] = {0};
	unsigned char mac[6] = {0};
	get_local_info(intfc,sip,mac);
	printf("id:%s\n",sip);
	printf("mac:");
	for(int i=0; i<5;  ++i){
		printf("%2x:",mac[i]);
	}
	printf("%2x\n",mac[5]);
	init_ethernet_packet(&ep,sip,mac,dst,0,0);
	//创建套接字
	int sock = socket(AF_INET,SOCK_PACKET,htons(0x0806));
	if(sock < 0){
		perror("socket");
		exit(1);
	}	
	struct sockaddr sa;
	strcpy(sa.sa_data,intfc);
	ssize_t s = sendto(sock,&ep,sizeof(ep),0,&sa,sizeof(sa));
	if(s ==-1){
		perror("sendto");
		exit(2);
	}
	printf("发送成功,共%dB,等待回应...\n",s);
	struct in_addr ip;
	struct ethernet_packet rev;

	if(recv(sock,&rev,sizeof(rev),0)>0){
		ip.s_addr = *((int*)rev.ap.dest_ip);
		printf("dst_mac:%02x %02x %02x %02x %02x %02x\n",rev.dest_mac[0],rev.dest_mac[1],rev.dest_mac[2],rev.dest_mac[3],rev.dest_mac[4],rev.dest_mac[5]);
		printf("dst_ip:%s\n",inet_ntoa(ip));
		printf("src:%02x %02x %02x %02x %02x %02x\n",rev.src_mac[0],rev.src_mac[1],rev.src_mac[2],rev.src_mac[3],rev.src_mac[4],rev.src_mac[5]);
		printf("op:0x%02x%02x\n",rev.ap.op[0],rev.ap.op[1]);
	}
}
void print_mac(const unsigned char* mac){
	for(int i=0; i<5; ++i)
		printf("%2x:",mac[i]);
	printf("%2x\n",mac[5]);
}

void arpspoof(const char *dev,const char* host,const char* target){
	unsigned char local_ip[18] = {0};
	unsigned char local_mac[6] = {0};
	unsigned char host_mac[6] = {0};
	unsigned char target_mac[6] = {0};
	get_local_info(dev,local_ip,local_mac);
	printf("local ip is:%s\n",local_ip);
	printf("local mac is:");
	print_mac(local_mac);
	get_other_mac(dev,local_ip,local_mac,host,host_mac);
	printf("host mac is:");
	print_mac(host_mac);
	get_other_mac(dev,local_ip,local_mac,target,target_mac);
	printf("target mac is:");
	print_mac(target_mac);
}	

int main(int argc,const char* argv[]){
	if(argc!=4){
		printf("Useage:%s [interface] [source_ip] [dest_ip]\n",argv[0]);
		return 0;
	}
	//request_test(argv[1],argv[2],argv[3]);
	arpspoof(argv[1],argv[2],argv[3]);
	return 0;
}
