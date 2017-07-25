#include "function.h"




int wq_addr=0;

void functon_delay(int temp)
{
	while(temp--);
}

char xor(char *buf,char len)             //异或校验
{
	char i;
	char rec;
	rec=0;
	for(i=0;i<len;i++)
	{
	   rec	^= buf[i];
	}
	return rec;
}

//u16 my_strlen(u8 *p)
//{
//	u16 len=0;
//	while(*p!='\0')
//	{
//		len++;
//		p++;
//	}
//	return len;
//}

char mytok(char *src,int counter)
{
		char rec[32];
		char next;
		char i,j;
		char *p;
		p=src;
		i=0;j=0;
		next=0;
		memset(rec,0,sizeof(char)*32);
		while((char)(*p)!='\0' || next<20)
		{
				if(i==counter)
				{
						rec[j]=(char)(*p);
						j++;
				}
				if((char)(*p)=='.')
				{
						if(i>counter)
						{
								break;
						}
						i++;
				}
				p++;
				next++;
		}
		return atoi(rec);
}


error_t snmpAgentRandCallback(uint8_t *data, size_t length)
{
   size_t i;
   uint32_t value;

   //Generate some random data
   for(i = 0; i < length; i++)
   {
      //Check whether a new 32-bit random integer must be generated
      if((i % 4) == 0)
      {
         //Wait for the RNG to contain a valid data
         while(RNG_GetFlagStatus(RNG_FLAG_DRDY) == RESET);

         //Get 32-bit random value
         value = RNG_GetRandomNumber();
      }

      //Copy random data
      data[i] = value & 0xFF;
      //Shift the value to the right
      value >>= 8;
   }

   //No error to report
   return NO_ERROR;
}


void reqorder(char *request,char *orderline,int counter)
{
	char i,j;
	char *p;
	char *buf;
	p=request;
	i=0;j=0;
	while((char)(*p)!='\0')
	{
		if((char)(*p)=='=')
		{
			if(i==counter)
			{
				buf=p+1;
				while((char)(*buf)!='\0' && (char)(*buf)!='&')
				{
					if(j>=120)
					{
						break;
					}
					j++;
					buf++;
				}
				strncpy(orderline,p+1,j);
				return;
			}
			i++;
		}
		p++;
	}
}

///**
// * @brief HTTP authentication callback
// * @param[in] connection Handle referencing a client connection
// * @param[in] user NULL-terminated string specifying the user name
// * @param[in] uri NULL-terminated string containing the path to the requested resource
// * @return Access status (HTTP_ACCESS_ALLOWED, HTTP_ACCESS_DENIED,
// *   HTTP_BASIC_AUTH_REQUIRED or HTTP_DIGEST_AUTH_REQUIRED)
// **/
//error_t httpServerCgiCallback(HttpConnection *connection,
//   const char_t *param)
//{
//	
//}
///**
// * @brief HTTP authentication callback
// * @param[in] connection Handle referencing a client connection
// * @param[in] user NULL-terminated string specifying the user name
// * @param[in] uri NULL-terminated string containing the path to the requested resource
// * @return Access status (HTTP_ACCESS_ALLOWED, HTTP_ACCESS_DENIED,
// *   HTTP_BASIC_AUTH_REQUIRED or HTTP_DIGEST_AUTH_REQUIRED)
// **/

/**
 * @brief HTTP authentication callback
 * @param[in] connection Handle referencing a client connection
 * @param[in] user NULL-terminated string specifying the user name
 * @param[in] uri NULL-terminated string containing the path to the requested resource
 * @return Access status (HTTP_ACCESS_ALLOWED, HTTP_ACCESS_DENIED,
 *   HTTP_BASIC_AUTH_REQUIRED or HTTP_DIGEST_AUTH_REQUIRED)
 **/

//HttpAccessStatus httpServerAuthCallback(HttpConnection *connection,
//   const char_t *user, const char_t *uri)
//{
//   HttpAccessStatus status;

//   //Manage access rights
//   if(pathMatch(uri, "/passwords.txt"))
//   {
//      //This file is not visible
//      status = HTTP_ACCESS_DENIED;
//   }
//   else if(pathMatch(uri, "/config/*"))
//   {
//      //This directory is not visible
//      status = HTTP_ACCESS_DENIED;
//   }
//   else if(pathMatch(uri, "/admin/*"))
//   {
//      //Only the administrator can access this directory
//      if(!strcmp(user, "administrator"))
//      {
//         //Check the administrator password
//         if(httpCheckPassword(connection, "password", HTTP_AUTH_MODE_BASIC))
//            status = HTTP_ACCESS_ALLOWED;
//         else
//            status = HTTP_ACCESS_BASIC_AUTH_REQUIRED;
//      }
//      else
//      {
//         //Users other than administrator cannot access this directory
//         status = HTTP_ACCESS_BASIC_AUTH_REQUIRED;
//      }
//   }
//   else
//   {
//      //No restriction for other directories
//      status = HTTP_ACCESS_ALLOWED;
//   }

//   //Return access status
//   return status;
//}

///**
// * @brief SMTP client test routine
// * @return Error code
// **/
error_t smtpClientTest(void)
{
   error_t error;

   //Authentication information
   static SmtpAuthInfo authInfo =
   {
       NULL,             //Network interface
       "mail.china-clever.com", //SMTP server name
       25,               //SMTP server port
       "yangjq@china-clever.com",       //User name
       "Clever#$123",       //Password
       FALSE,            //Use STARTTLS rather than implicit TLS
       YARROW_PRNG_ALGO, //PRNG algorithm
       &yarrowContext    //PRNG context
   };

   //Recipients
   static SmtpMailAddr recipients[2] =
   {
       {"Alice", "745009246@qq.com", SMTP_RCPT_TYPE_TO}, //First recipient
       {"Bob", "wuzhiwei@china-clever.com", SMTP_RCPT_TYPE_CC}      //Second recipient
   };

   //Mail contents
   static SmtpMail mail =
   {
      {"Charlie", "yangjq@china-clever.com"},  //From
      recipients,                        //Recipients
      2,                                 //Recipient count
      "",                                //Date
      "SMTP Client Demo",                //Subject
      "Hello World!"                     //Body
   };

   //Send mail
   error = smtpSendMail(&authInfo, &mail);

   //Return status code
   return error;
}

/**
 * @brief SNTP client test routine
 * @return Error code
 **/

//error_t sntpClientTest(void)
//{
//   error_t error;
//   time_t unixTime;
//   IpAddr ip_sntp_Addr;
//   NtpTimestamp timestamp;
//   

//	    //Point to the network interface
//	
////   //Resolve SNTP server name 解析SNTP服务器名称
//   error = getHostByName(NULL, "0.fr.pool.ntp.org", &ip_sntp_Addr, 0);


//	
//   //Any error to report?  
//   if(error)
//   {
//      //Exit immediately   Failed to resolve server name
//      return error;
//   }

//   //Retrieve current time from NTP server using SNTP protocol  从NTP服务器获取当前时间用在SNTP协议 Requesting time from SNTP server
//   error = sntpClientGetTimestamp(NULL, &ip_sntp_Addr, &timestamp);

//   //Any error to report?
//   if(error)
//   {
//      //Failed to retrieve NTP timestamp!获取NTP时间失败
//   }
//   else
//   {
//      //Unix time starts on January 1st, 1970
//      unixTime = timestamp.seconds - 2208988800;
//      //Convert Unix timestamp to date  时间戳转为日期
//      convertUnixTimeToDate(unixTime, &date);
//		  

//      //"Current date/time: %s\r\n", formatDate(&date, NULL)


//      //Refresh LCD display LCD显示年月日时分秒
////      printf("%04u/%02u/%02u %02u:%02u:%02u", date.year, date.month,
////         date.day, date.hours, date.minutes, date.seconds);
//   }

//   //Return status code
//   return error;
//}


//u8 RecUartCmd(void)
//{
//	static volatile u8 s_ucUart1_Byte_Cnt = 0;
//	static volatile u8 s_ucCheck_Sum_Byte = 0;
//	static volatile u8 s_ucUart1_Rxd_Current_P = 0;
//	static volatile u8 s_ucOrder_Byte_Num = 0;
// 	u8 Rec_Byte;
// 	u8 Crc_L;
// 	u8 Crc_H;
//	u8 i;

//	while (s_ucUart1_Rxd_Current_P != RSART6_RX_CNT)   //和串口接收长度
//	{
//			Rec_Byte = USART6_RX_BUF[s_ucUart1_Rxd_Current_P];
//			s_ucUart1_Rxd_Current_P ++;	

//			if (s_ucUart1_Rxd_Current_P >= 64)
//		  {
//		    	s_ucUart1_Rxd_Current_P = 0;
//		  }			
//			
//			if (s_ucUart1_Byte_Cnt==0)
//			{
//					if ( Rec_Byte == 0XC1)
//					{
//								rs485buf[s_ucUart1_Byte_Cnt] = Rec_Byte;
//								s_ucCheck_Sum_Byte ^= Rec_Byte;
//								s_ucUart1_Byte_Cnt = 1;					
//					}
//					else
//					{
//								s_ucCheck_Sum_Byte = 0;
//								s_ucUart1_Byte_Cnt = 0;
//								s_ucOrder_Byte_Num = 0;
//								return 0;					
//					}
//			}
//			else if (s_ucUart1_Byte_Cnt==1)
//			{
//					if ((Rec_Byte == 0X01) || (Rec_Byte == 0X02) || (Rec_Byte == 0X03))		
//					{
//		  				rs485buf[s_ucUart1_Byte_Cnt] = Rec_Byte;
//		  				s_ucCheck_Sum_Byte ^= Rec_Byte;
//		  				s_ucUart1_Byte_Cnt = 2; 
//		  				s_ucOrder_Byte_Num = 29;						 
//					}
//					else
//		  		{
//		  				s_ucCheck_Sum_Byte = 0;
//		  				s_ucUart1_Byte_Cnt = 0;
//		  				s_ucOrder_Byte_Num = 0;
//		  				return 0;
//		  		}					
//			}
//			else if (s_ucUart1_Byte_Cnt < (s_ucOrder_Byte_Num -1)) 
//			{
//					rs485buf[s_ucUart1_Byte_Cnt] = Rec_Byte;
//					s_ucCheck_Sum_Byte ^= Rec_Byte;
//					s_ucUart1_Byte_Cnt++;					
//			}
//			else
//			{
//					if (rs485buf[0]==0xc1)     //首部
//					{
//							if (rs485buf[2]==0x1D)     //长度
//							{
//									if (s_ucCheck_Sum_Byte == Rec_Byte)   //检验
//										{
//											rs485buf[s_ucUart1_Byte_Cnt] = Rec_Byte;
//											s_ucCheck_Sum_Byte = 0;
//											s_ucUart1_Byte_Cnt = 0;
//											usart6_flag=0;
//											return 1;
//										}								 
//							}
//					}	
//					s_ucCheck_Sum_Byte = 0;
//					s_ucUart1_Byte_Cnt = 0;
//					s_ucOrder_Byte_Num = 0;
//					usart6_flag=0;
//					return 0;					
//			}
//	}
//	return 0;
//	
//}

//void RSART6_Receive_Data(u8 *buf,u8 *len)
//{
//	u8 rxlen=RSART6_RX_CNT;
//	u8 i=0;
//	*len=0;				//默认为0
//	osDelayTask(100);		//等待10ms,连续超过10ms没有接收到一个数据,则认为接收结束
//	if(rxlen==RSART6_RX_CNT&&rxlen)//接收到了数据,且接收完成了
//	{
//		for(i=0;i<rxlen;i++)
//		{
//			buf[i]=USART6_RX_BUF[i];	
//		}		
//		*len=RSART6_RX_CNT;	//记录本次数据长度
//		RSART6_RX_CNT=0;		//清零
//		usart6_flag=0;
//	}	
//}

//u8 RSART1_Receive_Data(u8 *buf,u8 *len)
//{
//	u8 rxlen=RSART1_RX_CNT;
//	u8 i=0;
//	*len=0;				//默认为0
//	osDelayTask(20);		//等待10ms,连续超过10ms没有接收到一个数据,则认为接收结束
//	if(rxlen==RSART1_RX_CNT&&rxlen)//接收到了数据,且接收完成了
//	{
//		for(i=0;i<rxlen;i++)
//		{
//			buf[i]=USART1_RX_BUF[i];	
//		}		
//		*len=RSART1_RX_CNT;	//记录本次数据长度
//		RSART1_RX_CNT=0;		//清零
//		return 1;
//	}
//	else return 0;
//}









