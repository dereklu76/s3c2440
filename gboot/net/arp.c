#include "arp.h"
#include "dm9000.h"
#include "printf.h"
#include <string.h>

const u8 BROADCAST_MAC[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
const u8 board_ip_addr[4] = {192, 168, 1, 23};
const u8 pc_ip_addr[4] = {192, 168, 1, 100};

void Arp_Request(void)
{
	ARP_HDR arp_buf;

	memcpy(arp_buf.ehdr.dst_mac, BROADCAST_MAC, 6);
	memcpy(arp_buf.ehdr.src_mac, board_mac_addr, 6);
	arp_buf.ehdr.frame_type = U16SWAP(0x0806);
	arp_buf.hw_type = U16SWAP(1);
	arp_buf.protocal = U16SWAP(0x0800);
	arp_buf.mac_len = 6;
	arp_buf.ip_len = 4;
	arp_buf.op_code = U16SWAP(1);
	memcpy(arp_buf.src_mac, board_mac_addr, 6);
	memcpy(arp_buf.src_ip, board_ip_addr, 4);
	memcpy(arp_buf.dst_ip, pc_ip_addr, 4);

	dm9000_tx((u8*)(&arp_buf), sizeof(ARP_HDR));
}

void Arp_Process(u8 *rcv_buf)
{
	u8 i;
	ARP_HDR *arp_buf = (ARP_HDR*)rcv_buf;

	printf("mac address is ");
	
	for(i = 0; i < 5; i++)
	{
		printf("%02x:", arp_buf->src_mac[i]);
	}
	
	printf("%02x\r\n", arp_buf->src_mac[5]);
}


