/**
  ******************************************************************************
  * @file    tftpserver.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    31-October-2011   
  * @brief   basic tftp server implementation for IAP (only Write Req supported)
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************  
  */

/* Includes ------------------------------------------------------------------*/
#include "tftpserver.h"
#include "flash_if.h"
#include <string.h>
#include <stdio.h>
#include <24c04-iic.h>
#include "w25qxx.h" 
#include "modbus.h"

Ipv4Addr ipaddr;
int dest_port,src_port;

int write_w25q128_addr=0;
u8 *save_tftp_data ;
u8 *Ex_board_data;
//u8 save_tftp_data[8256] __attribute__((at(0X64000000)));   //__attribute__((at()))  �����ⲿоƬ;
u8 tftp_rec_num[4]={0,0,0,0};

#ifdef USE_IAP_TFTP

/**
  * @brief Returns the TFTP opcode 
  * @param buf: pointer on the TFTP packet 
  * @retval none
  */
static uint32_t Flash_Write_Address;
static __IO uint32_t total_count=0;
	
void tftp_recevice_callback(NetInterface *interface, const IpPseudoHeader *pseudoHeader,
   const UdpHeader *header, const NetBuffer *buffer, size_t offset, void *params);

static tftp_opcode IAP_tftp_decode_op(char *buf)
{
  return (tftp_opcode)(buf[1]);
}

/**
  * @brief Sets the TFTP opcode 
  * @param  buffer: pointer on the TFTP packet
  * @param  opcode: TFTP opcode
  * @retval none
  */
static void IAP_tftp_set_opcode(char *buffer, tftp_opcode opcode)
{
  buffer[0] = 0;
  buffer[1] = (u8)opcode;
}
/**
  * @brief Sets the TFTP block number 
  * @param packet: pointer on the TFTP packet 
  * @param  block: block number
  * @retval none
  */
static void IAP_tftp_set_block(char* packet, u16 block)
{
  u16 *p = (u16 *)packet;
  p[1] = htons(block);
}

/**
  * @brief  Extracts the block number
  * @param  buf: pointer on the TFTP packet 
  * @retval block number
  */
static u16 IAP_tftp_extract_block(char *buf)
{
  u16 *b = (u16*)buf;
  return ntohs(b[1]);
}

void IAP_tftp_send_ack_packet(NetInterface *interface, const IpPseudoHeader *pseudoHeader,const UdpHeader *header, int block)
{
	error_t error;	
	NetBuffer *pkt_buf;
	size_t set_offset;
	IpAddr *sendaddr;
	IpPseudoHeader *addest = (IpPseudoHeader *)pseudoHeader;
	char packet[TFTP_ACK_PKT_LEN];
	
	sendaddr = (IpAddr *)pvPortMalloc(sizeof(IpAddr));         //����ռ�
	
	sendaddr->ipv4Addr = addest->ipv4Data.srcAddr;
	sendaddr->length = sizeof(Ipv4Addr);	
	
   //Allocate a memory buffer to hold the UDP datagram
   pkt_buf = udpAllocBuffer(0, &set_offset);	
	
  /* define the first two bytes of the packet */
  IAP_tftp_set_opcode(packet, TFTP_ACK);

  /* Specify the block number being ACK'd.
   * If we are ACK'ing a DATA pkt then the block number echoes that of the DATA pkt being ACK'd (duh)
   * If we are ACK'ing a WRQ pkt then the block number is always 0
   * RRQ packets are never sent ACK pkts by the server, instead the server sends DATA pkts to the
   * host which are, obviously, used as the "acknowledgement".  This saves from having to sEndTransferboth
   * an ACK packet and a DATA packet for RRQs - see RFC1350 for more info.  */
  IAP_tftp_set_block(packet, block);

//  /* Copy the original data buffer over to the packet buffer's payload */
//  memcpy((uint8_t*)pkt_buf->chunk->address, packet, TFTP_ACK_PKT_LEN);

  //Copy data payload
   error = netBufferAppend(pkt_buf, packet, TFTP_ACK_PKT_LEN);	
   if(error)
   {
     return ;
   }
      //Send UDP datagram
   error = udpSendDatagramEx(interface, src_port , sendaddr, dest_port, pkt_buf, set_offset, 0);		//UDP���ͺ���
	 if(error)
	 {
			return;
	 }	 
	 vPortFree(sendaddr);
	 netBufferFree(pkt_buf);

}

//void IAP_wrq_recv_callback(NetInterface *interface, const IpPseudoHeader *pseudoHeader,
//   const UdpHeader *header, const NetBuffer *buffer, size_t offset, void *params)
//{
//  tftp_connection_args *args = (tftp_connection_args *)params;      //����tftp_connection_args�ṹ��args
//	UdpHeader *udphead = (UdpHeader *)header;
//	NetBuffer *udp_buf = (NetBuffer *)buffer;
//  uint32_t lent;                              //data_buffer[128],
//	u8 data_buffer[516];
//	char payload[516];
//  u16 count=0,i;
//	u16 leng=0;
//	u8 datatemp[516];	
//	
//	lent= (uint32_t)buffer->chunk->length - offset;                //TFTP������(516)ȷ�� 
//	
//	netBufferRead(payload,udp_buf,offset,lent);                   //TFTP�����ݰ�payload��������(2)+���(2)+������(512)
//	
//	  /* Does this packet have any valid data to write? */
//  if ((lent > TFTP_DATA_PKT_HDR_LEN) &&
//      (IAP_tftp_extract_block(payload) == (args->block + 1)))     //���
//	{	
//		
//			tftp_rec_num[2]=1;   //��ֹ����ж�
//		  tftp_rec_num[3]=10;   //��ֹ����Ͽ�������
//		
//							//Copy the payload	
//			memcpy(&data_buffer[2],&payload[TFTP_DATA_PKT_HDR_LEN],lent-TFTP_DATA_PKT_HDR_LEN);    //������data_buffer��512��
//						 
//			leng = lent - TFTP_DATA_PKT_HDR_LEN;            //һ��������ĳ��� 512				
//						
//			data_buffer[0] = leng/256%256;   //���ȸ��ֽ�
//			data_buffer[1] = leng%256;     //���ȵ��ֽ�
//			data_buffer[leng+2] = CRC16_2(data_buffer,leng+2)%256;      // CRC L  
//			data_buffer[leng+3] = CRC16_2(data_buffer,leng+2)/256%256;  // CRC H	
//					
//			//			  W25QXX_Write(data_buffer,write_w25q128_addr+4096*512 ,leng+4);                                       //д��W25Q128     4096*512                   write_w25q128_addr	
//			//				write_w25q128_addr += (leng+4);		
//							
//		  				
//					memcpy(&save_tftp_data[total_count],data_buffer,leng+4); 
//									
//					total_count += leng+4;		
//				
//					if(total_count==49536)
//					{
//							tftp_rec_num[0]=1;
//							W25QXX_Write(save_tftp_data,write_w25q128_addr+4096*512 ,total_count); 
//							write_w25q128_addr += total_count;
//							total_count=0;
//							
//					}
//					else
//					{
//						if (lent < TFTP_DATA_PKT_LEN_MAX)
//						{
//								tftp_rec_num[1]=1;
//								W25QXX_Write(save_tftp_data,write_w25q128_addr+4096*512 ,total_count); 
//								write_w25q128_addr += total_count;						
//								total_count=0;	
//								
//						}						
//					}				
//		
//							
//			/* update our block number to match the block number just received */
//			args->block++;	
//			
//			    /* update total bytes  */
//		  (args->tot_bytes) += (lent- TFTP_DATA_PKT_HDR_LEN);
//	}
//  else if (IAP_tftp_extract_block(payload) == (args->block + 1))
//  {
//    /* update our block number to match the block number just received  */
//    args->block++;
//  }
//	
//	IAP_tftp_send_ack_packet(interface, pseudoHeader, header, args->block);	  //����Ӧ��

//  if (lent < TFTP_DATA_PKT_LEN_MAX)           //tftp�������һ�β���512�ֽ�
//  {//�ϴ����
//		 	


//				  if(tftp_rec_num[0]&&tftp_rec_num[1])  //������
//					{
//							tftp_rec_num[0]=0;
//							tftp_rec_num[1]=0;
//							vPortFree(save_tftp_data);						
//							I2cWrite(36,26);
//							devicedown();							
//					}
//					else                   //�жϰ�
//					{
//							tftp_rec_num[0]=0;
//							tftp_rec_num[1]=0;						
//					}

//			

//  }
//  else
//  {
//    return;
//  }	
//}


void IAP_wrq_recv_callback(NetInterface *interface, const IpPseudoHeader *pseudoHeader,
   const UdpHeader *header, const NetBuffer *buffer, size_t offset, void *params)
{
  tftp_connection_args *args = (tftp_connection_args *)params;      //����tftp_connection_args�ṹ��args
	UdpHeader *udphead = (UdpHeader *)header;
	NetBuffer *udp_buf = (NetBuffer *)buffer;
  uint32_t data_buffer[128],lent;
	char payload[516];
  u16 count=0;
	u16 a,b;
	
	lent= (uint32_t)buffer->chunk->length - offset;                //TFTP������(516)ȷ�� 
	
	netBufferRead(payload,udp_buf,offset,lent);                   //TFTP�����ݰ�payload��������(2)+���(2)+������(512)
	
//	a = IAP_tftp_extract_block(payload);
//	b =  args->block + 1;
	
	
	  /* Does this packet have any valid data to write? */
  if ((lent > TFTP_DATA_PKT_HDR_LEN) &&
      (IAP_tftp_extract_block(payload) == (args->block + 1)))     //���
	{
		
			tftp_rec_num[2]=1;   //��ֹ����ж�
		  tftp_rec_num[3]=10;   //��ֹ����Ͽ�������		
		
			//Copy the payload	
		  memcpy(data_buffer,&payload[TFTP_DATA_PKT_HDR_LEN],lent-TFTP_DATA_PKT_HDR_LEN);    //������data_buffer��512��
		
			total_count += lent - TFTP_DATA_PKT_HDR_LEN;     //512 ������

			count = (lent - TFTP_DATA_PKT_HDR_LEN)/4;
			if (((lent - TFTP_DATA_PKT_HDR_LEN)%4)!=0) 
			count++;
                    
			    /* Write received data in Flash */                      
		  FLASH_If_Write(&Flash_Write_Address, data_buffer ,count);            //������д��flash      
			
			/* update our block number to match the block number just received */
			args->block++;	

//			b =  args->block;
			
			    /* update total bytes  */
		  (args->tot_bytes) += (lent- TFTP_DATA_PKT_HDR_LEN);
	}
  else if (IAP_tftp_extract_block(payload) == (args->block + 1))
  {
    /* update our block number to match the block number just received  */
    args->block++;
  }
	
	IAP_tftp_send_ack_packet(interface, pseudoHeader, header, args->block);	  //����Ӧ��

  if (lent < TFTP_DATA_PKT_LEN_MAX)           //tftp�������һ�β���512�ֽ�
  {//�ϴ����
			I2cWrite(33,26);
			devicedown();
  }
  else
  {
    return;
  }	
}

void IAP_tftp_process_write(NetInterface *interface, const IpPseudoHeader *pseudoHeader,const UdpHeader *header)
{
	error_t err;
	int j;
	tftp_connection_args *args = NULL; 
	args = (tftp_connection_args *)pvPortMalloc(sizeof(tftp_connection_args));
	

//			save_tftp_data = (char *)pvPortMalloc(49536);         //���붯̬�ڴ�       49536   8256


//	memset(args,0,sizeof(tftp_connection_args));
  args->op = TFTP_WRQ;            //TFTPд����
  args->to_ip = pseudoHeader->ipv4Data.srcAddr;   //PC��IP��ַ            
  args->to_port = (int)header->srcPort;       //�յ��Ķ˿ں�
  /* the block # used as a positive response to a WRQ is _always_ 0!!! (see RFC1350)  */
  args->block = 0;           //��һ��Ӧ��ʱ�����Ϊ0
  args->tot_bytes = 0;	
	
  total_count =0;
	write_w25q128_addr=0;	

	if(tftp_rec_num[2])
	{
		tftp_rec_num[2]=0;
		devicedown();	
	}		


  /* init flash */
  FLASH_If_Init();           //��ʼ��flash
   
  /* erase user flash area */
  FLASH_If_Erase(USER_FLASH_FIRST_PAGE_ADDRESS);           // �ӵ�ַ USER_FLASH_FIRST_PAGE_ADDRESS 0x8090000  ����flash
 
  Flash_Write_Address = USER_FLASH_FIRST_PAGE_ADDRESS;     //��Ҫд��ĵ�ַ  USER_FLASH_FIRST_PAGE_ADDRESS 0x8090000  ��������Flash_Write_Address
  /* initiate the write transaction by sending the first ack  ������һ��ȷ�� ���Ϊ0������ACK��ͻ��˿�ʼ�����ļ��������ص�����IAP_wrq_recv_callback*/
  IAP_tftp_send_ack_packet(interface, pseudoHeader, header, args->block);	
	
	udpAttachRxCallback(interface,src_port,IAP_wrq_recv_callback,args);	
	 
}

void tftp_recevice_callback(NetInterface *interface, const IpPseudoHeader *pseudoHeader,
   const UdpHeader *header, const NetBuffer *buffer, size_t offset, void *params)
{
	error_t error;
	tftp_opcode op;
	UdpHeader * heed = (UdpHeader *)header;

	dest_port = heed->srcPort;
	
	dest_port = (dest_port<<8 | dest_port>>8) & 0x0000ffff ;   // PC���Ķ˿�

  src_port = heed->destPort;                       
	
	op = IAP_tftp_decode_op((char*)header->data);    //�õ�TFTP������   2Ϊд����
	
	if (op != TFTP_WRQ)
	{
//		
	}
	else
	{
		write_w25q128_addr=0;
		/* Start the TFTP write mode*/
		IAP_tftp_process_write(interface, pseudoHeader, header);      //����TFTPдģʽ			  
	}	
	
}


void TftpTask(void *param)
{
	error_t error;
	unsigned port = 69;

			 //Point to the network interface
	NetInterface *tftp_interface = &netInterface[0];
	error = udpAttachRxCallback(tftp_interface,port,tftp_recevice_callback,NULL);
	
	
   while(1)
   {		
		  
		  if(tftp_rec_num[3]!=0)
			{
					tftp_rec_num[3]--;
					if(tftp_rec_num[3]<=0)
					{	
							tftp_rec_num[3]=0;
						  devicedown();													
					}
			}		
			
		  osDelayTask(300);

   }
}
void IAP_tftpd_init(void)
{
	
	osCreateTask("Tftp Server", TftpTask, NULL, 1000, 1);
		
}






#endif /* USE_IAP_TFTP */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
