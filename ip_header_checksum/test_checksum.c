#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
/****************************************************************************
 *IP头的格式:
 *|4 bits version |4 bits header len|8 bits TOS|16 bits packet len|
 *|16 bits Identify|3 bits flags|13 bits offset|
 *|8 bits TTL|8 bits ptoro|16 bits checksum|
 *|32 bits source ip addr|
 *|32 bits destinate ip addr|
 *|...opts...|
 *完整的ip数据包应该包含data部分
 *checksum字段在ip头部中，以unsigned short的数组来看，位于第6个数字
 *即addr[5]是checksum字段对应的两个字节
 *unsigned short 占两个字节。因此len/2==addr数组的数字个数
 ****************************************************************************/
/*发出的数据包的校验和计算,len代表所有的头部字节数*/
void send_checksum(unsigned short* addr,int len){
	//首先把校验和字段全置为0
	unsigned short* head=addr;
	head[5]=0x0000;
	int temp=0;
	while(len>1){
		temp+=*addr++;
		len-=2;
	}
	if(len==1)
		temp+=*addr;
	printf("send checksum,now get all sum:%x\n",temp);
	/*temp中可能有进位,右移将进位位放到最低位,
	 *例如00012222,应该计算为:0001+2222=2223*/
	temp=(temp>>16)+(temp & 0x0000ffff);
	temp= ~temp & (0x0000ffff);//取反,并将高16位置为0
	head[5]=(unsigned short)temp;
	printf("get checksum:%x\n",head[5]);
return ;
}

void receive_checksum(unsigned short* addr,int len){
	int temp=0;
	while(len>1){
		temp+=*addr++;
		len-=2;
	}
	if(len==1)
		temp+=*addr;
	printf("receive checksum,now get all sum:%x\n",temp);
	/*temp中可能有进位,右移将进位位放到最低位,
	 *例如00012222,应该计算为:0001+2222=2223*/
	temp=(temp>>16)+(temp & 0x0000ffff);
	if(temp == 0xffff){
		printf("checksum is OK,%x\n",temp);
	}else{
		printf("checksum is WRONG,%x,packet dropped\n",temp);
	}
return ;
}


int main(){
	unsigned short head[]={0x4500,0x0031,0x89f5,0x1001,0x6e06,0x1010,0xdeb7,0x455d,0xc0a8,0x00dc};
	int len=sizeof(head);
	printf("len is %d\n",len);
	send_checksum(head,len);
	receive_checksum(head,len);
return 0;
}
