#ifndef __ARP_H__
#define __ARP_H__

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

#define U16SWAP(n) (((n&0xff)<<8)|((n>>8)&0xff))

typedef struct eth_hdr
{
	u8 dst_mac[6];
	u8 src_mac[6];
	u16 frame_type;
}ETH_HDR;

typedef struct arp_hdr
{
	ETH_HDR ehdr;
	u16 hw_type;
	u16 protocal;
	u8 mac_len;
	u8 ip_len;
	u16 op_code;
	u8 src_mac[6];
	u8 src_ip[4];
	u8 dst_mac[6];
	u8 dst_ip[4];
}ARP_HDR;


void Arp_Process(u8 *rcv_buf);

#endif



