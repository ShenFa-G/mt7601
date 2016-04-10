/*ar: This file to call the driver functions and transmit custom beacon frames*/

#include "swarm.h"

int swarmMethodCount = 0;

int createSwarmPacket(PNDIS_PACKET ** ppPacket, char *pHeader, int HeaderLen, char *pData, int DataLen){
	printk(KERN_ALERT"in createSwarmPacket \n");
	struct sk_buff *swarm_packet;
	swarm_packet = dev_alloc_skb(HeaderLen + DataLen + RTMP_PKT_TAIL_PADDING);
	// fail safe condition to be added

	MEM_DBG_PKT_ALLOC_INC(swarm_packet);

	/* Clone the frame content and update the length of packet */
	if (HeaderLen > 0)
		NdisMoveMemory(swarm_packet->data, pHeader, HeaderLen);
	if (DataLen > 0)
		NdisMoveMemory(swarm_packet->data + HeaderLen, pData, DataLen);
	skb_put(swarm_packet, HeaderLen + DataLen);
	/* printk(KERN_ERR "%s : swarm_packet = %p, len = %d\n", __FUNCTION__, swarm_packet, GET_OS_PKT_LEN(swarm_packet));*/

	RTMP_SET_PACKET_SOURCE(swarm_packet, PKTSRC_NDIS);
	*ppPacket = (PNDIS_PACKET)swarm_packet;

	return NDIS_STATUS_SUCCESS;
}

int swarmInit(){
	printk(KERN_ALERT"in Swarm Init \n");
	PNDIS_PACKET *pPacket_swarm;
	VOID *pad = NULL;
	char *swarmHeader = kmalloc(BUF_SIZE/2,NULL);
	swarmHeader = "swarmHeader\n";
	char *sendString = kmalloc(BUF_SIZE,NULL);
	sendString = "Hello I am Swarm \n";
	int retval;

	retval = createSwarmPacket(&pPacket_swarm,swarmHeader,BUF_SIZE,sendString,BUF_SIZE);
	struct net_device *net_dev = ((struct sk_buff*)pPacket_swarm)->dev;
	GET_PAD_FROM_NET_DEV(pad,net_dev);
	

	if (retval){
		printk(KERN_ALERT"SwarmPacket create success \n");
		while(1){
			printk(KERN_ALERT"swarm transmit thread woken up\n");
			swarmTxPackets(pad,1);
			STASendPackets((NDIS_HANDLE) pad , (PPNDIS_PACKET)&pPacket_swarm,1);
			printk(KERN_ALERT"swarm transmit thread sleeping \n");
			msleep(3);
		}
	}
	else{
		printk(KERN_ALERT" create Swarm Packet failed\n");
		return -1;
	}
	return 1;
}


void swarmTxPackets(void * pAd, int type){

	swarmMethodCount++;
	printk(KERN_ALERT"swarmTxPackets call no. %d \n",swarmMethodCount);
	
	char *sendString = kmalloc(BUF_SIZE,NULL);
	sendString = "This is swarm\n";
	if (type){
		int len = sizeof(sendString);
		char Nulldata[48];
		mlmeHelper(pAd,Nulldata,len);
	}
	else{
		mlmeHelper(pAd,sendString,sizeof(sendString));
	}
	
}
