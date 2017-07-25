#include "ip_info.h"
#include "debugudp.h"

static uint8_t gSentBuf_2[UDP_BUF_SIZE]={0};
static uint8_t data_buf[256];
short  UDP_Port=28720;
static char logo;
static char udp_status=0;
static char device_status[75]={0};

Socket *clientSocketa=NULL;
IpAddr clientIpAddrr;
static char login=0,lock=0;

///==========================
static Socket *gSocket=NULL;
static IpAddr gServerIpAddr;
static int udpLock=0;
///////////////===========


int data_packet_sent(dev_data_packet *msg);
void device_control(char *cdata);

/**
 * 发送工作状态
 */
void sent_devStatus(uint8_t id, uint8_t status)
{
//	static dev_data_packet msg;           //  msg：数据域
//	msg.addr = id; 
//	msg.len = 1;
//	msg.data = &status;

//	msg.fn[0] = 0;
//	msg.fn[1] = 0;
//	data_packet_sent(&msg);
}

/**
 * 功  能：短整形变成字符串型数据
 * 入口参数：from-> 数据来源，len-> 数据长度
 * 出口参数：to->数据缓冲区
 * 返  回：数据长度
 */
int shortToChar(uint16_t *form, int len, uint8_t *to)
{
//	int i, offset=0;
//	if(form)
//	{
//		memset(to,0, DATA_MSG_SIZE);
//		for(i=0; i<len; ++i)
//		{
//			to[offset++] = form[i] >> 8; // 高位
//			to[offset++] = form[i] & 0xFF; // 低8位
//		}
//	}

//	return offset;
}
/**
 * 功  能：整形变成字符串型数据
 * 入口参数：from-> 数据来源，len-> 数据长度
 * 出口参数：to->数据缓冲区
 * 返  回：数据长度
 */
int intToChar(uint32_t *form, int len, uint8_t *to)
{
//	int i, offset=0;

//	if(form)
//	{
//		memset(to,0, DATA_MSG_SIZE);
//		for(i=0; i<len; ++i)
//		{
//			to[offset++] = form[i] >> 24; // 高位
//			to[offset++] = (form[i] >> 16) ;
//			to[offset++] = (form[i] >> 8) ;
//			to[offset++] = form[i] & 0xFF; // 低8位
//		}
//	}

//	return offset;
}

void data_dev_code(data_code *code)
{
//	int i=0;
//	for(i=0; i<DEV_CODE_SIZE; ++i)
//	{
//		if(i==1)
//		{
//		  code->devCode[i] = 2; /*设备代号*/
//		}
//		else
//		{
//		  code->devCode[i] = 1;
//		}
//	}
//	code->type = TRA_TYPR_UDP; /*通讯类型*/
//	code->version = DATA_DEV_VERSION; /*版本号*/
//	code->trans = DATA_MSG_CLIENT; /*服务端发送标志：10H 客户端应答标志：03H */
//	code->reserve = 0;
}

/**
 * 功能：数据域打包
 * 入口参数：pkt->包结构休
 * 出口参数：buf->数据包首地址
 * 返回值：数据域长度
 * 说明：当要发送数据时就会调用此函数把数据打包
 */
int msg_packet(dev_data_packet *pkt, uint8_t *buf)
{
//    uint16_t i,rtn=0,leng=0;
//    uint8_t *ptr = buf;

//    *(ptr++) = pkt->addr; 	/*设备号*/

//    *(ptr++) = pkt->fn[0]; /*功能码*/
//    *(ptr++) = pkt->fn[1];

//    /*数据长度*/
//    *(ptr++) = (pkt->len >> 8); /*高八位*/
//    *(ptr++) = (pkt->len) & 0xFF; /*低八位*/

//    for(i=0; i<pkt->len; ++i)
//    	 *(ptr++) = pkt->data[i];
//		leng = pkt->len;
//    rtn = 1 + 2 + 2 + leng;

//    return rtn; /*数据包长度*/
}



/**
 * 功能：数据发送
 * 入口参数：data_code -> 代号段构体 	buf->数据首地址 len ->数据长度
 * 返回值：数据包长度
 * 说明：当要发送数据时就会调用此函数发送数据
 */
int data_msg_packetSent(data_code *code,uint8_t *buf, uint16_t len)
{
//	error_t error;
//	size_t set_offset;
//	
//	NetBuffer *pkt_buf;
//	data_packet *msg;	
//	uint8_t i,XOR=0;
//	uint16_t lent;
//	int j, port;

//	pkt_buf = udpAllocBuffer(0, &set_offset);	
//	msg = (data_packet *)malloc(sizeof(data_packet));
//		
//	msg->code = *code;        //代号段
//	msg->len = len;          //数据长度
//	msg->data = buf;         //数据域

//	for(i=0;i<len;i++)
//	{
//		gSentBuf_2[13+i] = data_buf[i];
//		XOR += data_buf[i];
//	}

//	
//	gSentBuf_2[13+len] = XOR;	/*生成校验码*/		

//	gSentBuf_2[0] = DATA_MSG_HDR;  /*信息头*/
//	gSentBuf_2[1] = DATA_MSG_STX; /*标识字*/	
//	
//    /*填入代号段*/
//  for(i=0; i<DEV_CODE_SIZE; ++i)
//  gSentBuf_2[2+i] = msg->code.devCode[i];	/*设备号*/	
//	gSentBuf_2[6] = msg->code.type;     /*通讯类型*/
//	gSentBuf_2[7] = msg->code.version; /*版本号*/
//	gSentBuf_2[8] = msg->code.trans; /*传输方向*/
//	msg->code.reserve = 0;
//	gSentBuf_2[9] = (msg->code.reserve)/256; /*预留号*/	
//	gSentBuf_2[10] = (msg->code.reserve)%256; /*预留号*/
//	
//	gSentBuf_2[11] = (msg->len)/256; /*数据长度*/	
//	gSentBuf_2[12] = (msg->len)%256; /*数据长度*/	
//	

//		
//	gSentBuf_2[13+len+1] = DATA_MSG_ED;    //结束符
//	
//	lent = 13 + len + 2 ;
//		
//		
//		
//		if(udpLock)
//		{
//			UDP_Port = 28720 + rand()%20;  
//			error = socketSendTo(gSocket, &gServerIpAddr, UDP_Port,gSentBuf_2, lent, NULL, 0);
//			if(error) {return;}
//			osDelayTask(1);
//		}
//		
//		
//		if(login>0) 
//		{
//			error = socketSendTo(clientSocketa, &clientIpAddrr, 11283,gSentBuf_2, lent, NULL, 0);		 
//			 if(error)
//			 {
//				socketClose(clientSocketa);		 
//				clientSocketa = NULL;
//				login = 0;
//			 } 
//		}
//		
//		osDelayTask(18);
//		free(msg);
//		netBufferFree(pkt_buf);	 
//		return len;		
}

/**
 *  发送数据域函数
 */
int data_packet_sent(dev_data_packet *msg)
{
//	uint16_t rtn=0;
//	uint8_t i;
//	data_code devCode; /*代号段*/
//	data_dev_code(&devCode);                // 代号段

//	memset(gSentBuf_2,0,sizeof(gSentBuf_2));
//	rtn = msg_packet(msg,gSentBuf_2);                      // * 功能：设备数据域打包    dev_data_packet赋值给缓冲区gSentBuf  rtn：数据长度

//	for(i=0;i<rtn;i++)
//	{
//		data_buf[i] = gSentBuf_2[i];
//	}

//	rtn = data_msg_packetSent(&devCode, gSentBuf_2, rtn);   // * 功能：数据发送

//	return rtn;
}


/**
 * 发送数据包
 *  发送数据的条件：数据长度大于0 缓冲区地址有效
 */
void sent_packet(dev_data_packet *msg)
{
//	if(msg->len > 0) // 必需有数据
//	{
//		if(msg->data) // 数据指针有效
//			data_packet_sent(msg);             // *  发送数据域函数
//	}
}

/**
 * 功  能：发送数据单元数据
 * 参  数：unit->数据单元结构体
 * 		  buf->发送数据缓冲区
 * 		  len-> 数据长度
 */
void sent_unit(_devDataUnit *unit, int len, uint8_t *buf, dev_data_packet *msg)
{
//	int fn=1, fc = msg->fn[1];
////	int j;
//	logo = msg->fn[0];

//	/* 发送当前值 */
//	msg->fn[1] = fc + fn++;              //功能码
//	msg->data = buf;                //数据	
//	msg->len = shortToChar(unit->value,len,buf);    //数据长度		
//	sent_packet(msg);                       // 发送数据包

//	/*发送最小值*/
//	msg->fn[0]=logo;
//	msg->fn[1] = fc + fn++;
//	msg->data = buf;                //数据	
//	msg->len = shortToChar(unit->min,len,buf);	
//	sent_packet(msg);

//	/*发送最大值*/
//	msg->fn[0]=logo;
//	msg->fn[1] = fc + fn++;
//	msg->data = buf;                //数据	
//	msg->len = shortToChar(unit->max,len,buf);	
//	sent_packet(msg);

//	/*发送报警*/
//	msg->fn[0]=logo;
//	msg->fn[1] = fc + fn++;
//	msg->len = len;
//	msg->data = unit->alrm;
//	sent_packet(msg);

//	/*发送临界最小值*/
//	msg->addr=0;
//	msg->fn[0]=logo;
//	msg->fn[1] = fc + fn++;
//	msg->data = buf;		
//	msg->len = shortToChar(unit->crMin,len,buf);
//	sent_packet(msg);

//	/*发送临界最大值*/
//	msg->fn[0]=logo;
//	msg->fn[1] = fc + fn++;
//	msg->data = buf;		
//	msg->len = shortToChar(unit->crMax,len,buf);
//	sent_packet(msg);

//	/*发送临界报警*/
//	msg->fn[0]=logo;
//	msg->fn[1] = fc + fn++;
//	msg->data = unit->crAlrm;
//	msg->len = len;	
//	sent_packet(msg);
//	
//	/*回路*/
//	msg->fn[0]=logo;
//	msg->fn[1] = fc + fn++;
//	msg->data = (uint8_t*)(&HARDWARE);
//	msg->len = 1;
//	sent_packet(msg);		
}


/**
 * 功 能：发送数据对象 包括电流、电压、功率、电能、功率因素等
 */
void sent_object(_devDataObj *obj, uint8_t *buf, dev_data_packet *msg)
{
////	u8_t lent=0;
//	int fn=0, len = obj->len;    //数据长度
//	
//	/*电流*/
//	fn += 1;
//	msg->fn[1] = fn << 4;
//	sent_unit(&(obj->cur), len, buf, msg);             //功  能：发送数据单元数据

//	/*电压*/
//	fn += 1;
//	msg->fn[1] = fn << 4;
//	sent_unit(&(obj->vol), len, buf, msg);             //功  能：发送数据单元数据
//	
//	/*功率*/
//	fn += 1;
//	msg->fn[1] = fn << 4;		
//	msg->len = intToChar(obj->pow,len,buf); // 功率
//	msg->data = buf;	
//	sent_packet(msg);

//	/*电能*/
//	fn += 1;
//	msg->fn[1] = fn << 4;
//	msg->len = intToChar(obj->ele,len,buf); // 电能	
//	msg->data = buf;
//	sent_packet(msg);

//	/*功率因素*/
//	fn += 1;
//	msg->fn[1] = fn << 4;
//	msg->data = buf;
//	msg->len = shortToChar(obj->pf,len,buf);
//	sent_packet(msg);

//	/*开关控制*/
//	msg->fn[0]=logo;
//	fn += 1;
//	msg->fn[1] = fn << 4;
//	msg->data = obj->sw;
//	msg->len = len;
//	sent_packet(msg);

//	/*排C量*/
//	fn += 1;
//	msg->fn[1] = fn << 4;
//	msg->data = buf;
//	msg->len = shortToChar(obj->carbon,len,buf);
//	sent_packet(msg);

//	/*电压频率*/
//	fn += 1;
//	msg->fn[1] = fn << 4;
//	msg->data = buf;
//	msg->len = shortToChar(obj->rate,len,buf); // 功率
//	sent_packet(msg);

}


/**
 * 功  能：发送温度、湿度、门禁、水浸等相关数据
 */
void sent_envObject(_envDataObjct *obj, uint8_t *buf, dev_data_packet *msg)
{
//	int fn=0, len = obj->len;

//	/*湿度*/
//	
//	fn += 1;
//	msg->fn[1] = fn << 4;
//	sent_unit(&(obj->tem), len, buf, msg);

//	/*湿度*/
//	fn += 1;
//	msg->fn[1] = fn << 4;
//	sent_unit(&(obj->hum), len, buf, msg);

//	/*门禁*/
//	fn += 1;
//	msg->fn[1] = fn << 4;
//	msg->data = obj->door;
//	msg->len = 2;
//	sent_packet(msg);

//	/*水禁*/
//	fn += 1;
//	msg->fn[1] = fn << 4;
//	msg->data = obj->water;
//	msg->len = 1;
//	sent_packet(msg);

//	/*烟雾*/
//	fn += 1;
//	msg->fn[1] = fn << 4;
//	msg->data = obj->smoke;
//	msg->len = 1;
//	sent_packet(msg);
}


/**
 * 功  能：发送温度、湿度、门禁、水浸等相关数据
 */
void sent_devObject(_dataObjct *obj, uint8_t *buf, dev_data_packet *msg)
{
//	//int len = obj->len;

//	/*设备名称*/

//	msg->fn[1] = 0x11;
//	msg->data = obj->devname;
//	msg->len = strlen((const char *)obj->devname);
//	sent_packet(msg);

}

void sent_userObject(_userObjct *obj, uint8_t *buf, dev_data_packet *msg)
{
//	//int len = obj->len;

//	/*用户和密码*/

//	msg->fn[1] = 0x11;
//	msg->data = obj->userpsd;
//	msg->len = strlen((const char *)obj->userpsd);
//	sent_packet(msg);

}


void sent_netObject(_netObjct *obj, uint8_t *buf, dev_data_packet *msg)
{
////	int len = obj->len;

//	/*IP地址*/
//	msg->fn[1] = 0x11;
//	msg->data = obj->ipaddr;
//	msg->len = strlen((const char *)obj->ipaddr);
//	sent_packet(msg);
//	
//	/*网关*/
//	msg->fn[1] = 0x12;
//	msg->data = obj->gateway;
//	msg->len = strlen((const char *)obj->gateway);
//	sent_packet(msg);

//	/*掩码*/
//	msg->fn[1] = 0x13;
//	msg->data = obj->mask;
//	msg->len = strlen((const char *)obj->mask);
//	sent_packet(msg);	
//	
//		/*DNS*/
//	msg->fn[1] = 0x14;
//	msg->data = obj->udns;
//	msg->len = strlen((const char *)obj->udns);
//	sent_packet(msg);	

//		/*get共同体*/
//	msg->fn[1] = 0x82;
//	msg->data = obj->gcommunity;
//	msg->len = strlen((const char *)obj->gcommunity);
//	sent_packet(msg);	

//		/*set共同体*/
//	msg->fn[1] = 0x83;
//	msg->data = obj->scommunity;
//	msg->len = strlen((const char *)obj->scommunity);
//	sent_packet(msg);	
//	
//		/*trap1*/
//	msg->fn[1] = 0x84;
//	msg->data = obj->trapa;
//	msg->len = strlen((const char *)obj->trapa);
//	sent_packet(msg);	

//		/*trap2*/
//	msg->fn[1] = 0x85;
//	msg->data = obj->trapb;
//	msg->len = strlen((const char *)obj->trapb);
//	sent_packet(msg);	

//   /*smtp用户*/
//	msg->addr=0;
//	msg->fn[0]=logo;
//	msg->fn[1] = 0xA1;	
//	msg->data = obj->smtpuse;
//	msg->len = strlen((const char *)obj->smtpuse);
//	sent_packet(msg);	
//	
//   /*smtp密码*/
//	msg->addr=0;
//	msg->fn[0]=logo;
//	msg->fn[1] = 0xA2;
//	msg->data = obj->smtppass;
//	msg->len = strlen((const char *)obj->smtppass);
//	sent_packet(msg);		
//	
//   /*smtp服务器*/
//	msg->addr=0;
//	msg->fn[0]=logo;
//	msg->fn[1] = 0xA3;
//	msg->data = obj->smtpserve;
//	msg->len = strlen((const char *)obj->smtpserve);
//	sent_packet(msg);		
//	
//   /*smtp接收帐号*/
//	msg->fn[1] = 0xA6;
//	msg->data = obj->smtpmail;
//	msg->len = strlen((const char *)obj->smtpmail);
//	sent_packet(msg);			
}

void sent_devData(uint8_t id, pduDevData *devData)
{
//	 dev_data_packet msg;           //  msg：数据域   ////========
//	 uint8_t buf[DATA_MSG_SIZE] = {0};
//	int fn=1;

//	msg.addr = id;                     // addr

//	msg.fn[0] = fn++;                 //功能码	
//	sent_object(&(devData->group), buf, &msg);          //* 功 能：发送路数据对象 包括电流、电压、功率、电能、功率因素等	
//	
//	msg.fn[0] = fn++;                 //功能码	
//	sent_object(&(devData->line), buf, &msg);          //* 功 能：发送相数据对象 包括电流、电压、功率、电能、功率因素等

//	msg.fn[0] = fn++;
//	sent_object(&(devData->output), buf, &msg);         //* 功 能：发送输出位数据对象 包括电流、电压、功率、电能、功率因素等

//	msg.fn[0] = fn++;
//	sent_envObject(&(devData->env), buf,&msg);
//	
//	msg.fn[0] = fn++;
//	sent_devObject(&(devData->dev), buf,&msg);
//	
//	msg.fn[0] = fn++;
//	sent_userObject(&(devData->userp), buf,&msg);	
//	
//	msg.fn[0] = fn++;
//	sent_netObject(&(devData->network), buf,&msg);		
}



/**
 * 组初始化数据  测试用，
 */
void init_unit_cur(_devDataUnit *unit)
{
//	static uint16_t cur_buf[6],cur_min[6],cur_max[6],cur_crmin[6],cur_crmax[6];
//	static uint8_t critical[6];

//	char i;
//	for(i=0; i<6; i++)
//	{
//		cur_buf[i] = Group_Cur[i][0] ;
//		cur_min[i] = Group_Cur[i][1] ;
//		cur_crmin[i] = Group_Cur[i][3] ;	
//    cur_max[i] = Group_Cur[i][2] ;
//		cur_crmax[i] = Group_Cur[i][4] ;	
//	}			
//		
//		for(i=0;i<6;i++)
//		{
//			if(cur_crmin[i]>cur_buf[i] || cur_buf[i]>cur_crmax[i])
//			{
//				critical[i]=1;		
//			}
//			else
//			{
//				critical[i]=0;
//			}
//			device_status[i]=Group_alarm[i];				
//			device_status[i+6]=critical[i];		
//		}	
//	
//	unit->value = cur_buf;
//	unit->max = cur_max;
//	unit->min = cur_min;
//	unit->alrm = (uint8_t*)Group_alarm;			
//	unit->crMin = cur_crmin;
//	unit->crMax = cur_crmax;	
//  unit->crAlrm= critical;
}

void group_data(_devDataObj *ptr)
{
//	ptr->len = 6;            
//	init_unit_cur(&(ptr->cur));     //初始化数据

}

/**
 * 相初始化数据  测试用，
 */
void line_unit_cur(_devDataUnit *unit)
{
//	static uint16_t cur_buf[3],cur_min[3],cur_max[3],cur_crmin[3],cur_crmax[3];
//	static uint8_t line_critical[3];
//	char i;

//	for(i=0; i<LINE_NUM; i++)
//	{
//	   cur_buf[i] = Total_Cur[i][0] ;
//		 cur_min[i] = Total_Cur[i][1] ;	
//		 cur_crmin[i] = Total_Cur[i][3] ;	
//		 cur_max[i] = Total_Cur[i][2] ;	
//		 cur_crmax[i] = Total_Cur[i][4] ;		
//	}
//		
//	for(i=0;i<LINE_NUM;i++)
//	{
//		 if(cur_crmin[i]>cur_buf[i] || cur_buf[i]>cur_crmax[i])
//		 {
//			 line_critical[i]=1;
//		 }
//		 else
//		 {
//			 line_critical[i]=0;
//		 }	
//		device_status[i+12]=Total_cur_alarm[i];			 
//		device_status[i+15]=line_critical[i];			 
//	}	

//	unit->value = cur_buf;
//	unit->max = cur_max;
//	unit->min = cur_min;
//	unit->alrm = (uint8_t*)Total_cur_alarm;	
//	unit->crMin = cur_crmin;
//	unit->crMax = cur_crmax;
//	unit->crAlrm= line_critical;	
}

void line_unit_vol(_devDataUnit *unit)
{
//	static uint16_t vol_buf[3],vol_min[3],vol_max[3];
//	char i;
//	
//	for(i=0; i<3; i++)
//	{
//  	vol_buf[i] = Tvol[i][0]*10 ;
//	  vol_min[i] = Tvol[i][1]*10 ;		
//	  vol_max[i] = Tvol[i][2]*10 ;		
//	}

//	for(i=0;i<3;i++)
//	{
//		 device_status[i+18]=Total_vol_alarm[i];	
//	}	
//	
//	unit->value = vol_buf;
//	unit->max = vol_max;
//	unit->min = vol_min;
//	unit->alrm = (uint8_t*)Total_vol_alarm;		

}

void line_data(_devDataObj *ptrline)
{
//	ptrline->len = LINE_NUM;     
//	line_unit_cur(&(ptrline->cur));     //初始化数据
//	line_unit_vol(&(ptrline->vol));    //初始化 电压值	
		
}

/**
 * 输出位初始化数据  测试用，
 */
void output_unit_cur(_devDataUnit *unit)
{
//	static uint16_t cur_buf[24],cur_min[24],cur_max[24],cur_crmin[24],cur_crmax[24];
//  static uint8_t out_critical[24];
//	char i;
////	if(corlogo==1)
////	{
//	for(i=0; i<outputnum; i++)
//	{
//	   cur_buf[i] = unit_cur[i][0] ;
//		 cur_min[i] = unit_cur[i][1] ;	
//		 cur_crmin[i] = unit_cur[i][3] ;	
//		 cur_max[i] = unit_cur[i][2] ;	
//		 cur_crmax[i] = unit_cur[i][4] ;		
//	}
//	
////  }	
//		
//		for(i=0;i<outputnum;i++)
//		{
//       if(cur_crmin[i]>cur_buf[i] || cur_buf[i]>cur_crmax[i])
//			 {
//			   out_critical[i]=1;
//			 }
//			 else
//			 {
//				 out_critical[i]=0;
//			 }	
//				 device_status[i+21]=unit_alarm[i];			 
//				 device_status[i+45]=out_critical[i];			 
//		}	

//	unit->value = cur_buf;
//	unit->min = cur_min;
//	unit->max = cur_max;	
//	unit->alrm = (uint8_t*)unit_alarm;		
//	unit->crMin = cur_crmin;
//	unit->crMax = cur_crmax;
//	unit->crAlrm= out_critical;			
		
}

void output_data(_devDataObj *ptrout)
{
//	ptrout->len = outputnum;     
//	output_unit_cur(&(ptrout->cur));     //初始化数据
		
}

/**
 * 温度初始化数据  测试用，
 */
void init_unit_tem(_devDataUnit *unit)
{
//	static uint16_t tem_buf[3],tem_min[3],tem_max[3];
//	uint16_t i ;

//	tem_buf[0] = tem[0][0]*10 ;
//	tem_min[0] = tem[0][1]*10 ;
//	tem_max[0] = tem[0][2]*10 ;

//	tem_buf[1] = tem[1][0]*10 ;
//	tem_min[1] = tem[1][1]*10 ;
//	tem_max[1] = tem[1][2]*10 ;	

//  for(i=0; i<2; i++)
//	{
//	  device_status[i+69]=tem_alarm[i];
//	}
//	unit->value = tem_buf;
//	unit->max = tem_max;
//	unit->min = tem_min;
//	unit->alrm= (uint8_t*)tem_alarm;

}

/**
 * 湿度初始化数据  测试用，
 */
void init_unit_hum(_devDataUnit *unit)
{
//	static uint16_t hum_buf[3],hum_min[3],hum_max[3];
//	uint16_t i ;

//	hum_buf[0] = hum[0][0]*10 ;
//	hum_min[0] = hum[0][1]*10 ;
//	hum_max[0] = hum[0][2]*10 ;
//	hum_buf[1] = hum[1][0]*10 ;
//	hum_min[1] = hum[1][1]*10 ;
//	hum_max[1] = hum[1][2]*10 ;	
//  for(i=0; i<2; i++)
//	{
//	  device_status[i+71]=hum_alarm[i];
//	}
//	unit->value = hum_buf;
//	unit->max = hum_max;
//	unit->min = hum_min;
//	unit->alrm= (uint8_t*)hum_alarm;

}

void init_alarm(void)
{
//    	char  alarm_t;
//	    char i=0;

//			for(alarm_t=0;alarm_t<73;alarm_t++)
//			{
//			   if(device_status[alarm_t]==1)
//			   {
//				    udp_status = 1;
//				 }
//				 else if(device_status[alarm_t]==0)
//			   {
//				    i+= 1;
//				 }		
//			}
//      if(i==73)
//			{
//		    	udp_status = 0;	
//			}
//      if(udp_status == 1)
//			{
//			  sent_devStatus(0, udp_status);	
//			}
//	    else if(udp_status==0)
//			{
//			  sent_devStatus(0, udp_status);
//			}
   
}

void sent_test()
{
//	uint8_t id = 0;
//	_devDataObj *ptr;
//	_devDataObj *ptrline;
//	_devDataObj *ptrout;	
//	_dataObjct *devic;	
//	_userObjct *userpa;	
//	_netObjct *netip;	
//	uint32_t power_buf[3] ;
//	uint32_t Energy_buf[3] ;
//	uint16_t power_pf[3] ;
//	uint32_t g_power[6] ;
//	uint32_t g_Energy[6] ;
//	uint32_t o_power[24] ;
//	uint32_t o_Energy[24] ;	
//	char i,j,k;
//	char userpp[20];
//	char ipadd[20];
//	char gway[20];	
//	char mak[20];	
//	char traa[20]; 
//	char trab[20];		
//	
//	pduDevData *devData = (pduDevData*)malloc(sizeof(pduDevData));
//	
//		memset(userpp,0,sizeof(char)*50);
//		strcat(userpp,user[0]);
//		strcat(userpp,"; ");
//		strcat(userpp,psd[0]);	
//	
//		sprintf(ipadd,"%d.%d.%d.%d",ip1,ip2,ip3,ip4);
//		sprintf(gway,"%d.%d.%d.%d",gw1,gw2,gw3,gw4);	
//		sprintf(mak,"%d.%d.%d.%d",ms1,ms2,ms3,ms4);	

//    sprintf(traa,"%d.%d.%d.%d",trapip1[0],trapip1[1],trapip1[2],trapip1[3]);	
//    sprintf(trab,"%d.%d.%d.%d",trapip2[0],trapip2[1],trapip2[2],trapip2[3]);	
//	
//	  for(i=0; i<3;i++)
//		{
//		  power_buf[i] = Total_Applied_Power[i]/10000;
//      Energy_buf[i] = Total_Energy[i] ;		
//	  	power_pf[i] = Total_PF[i]/100 ;			
//		}
//	
//    for(j=0; j<6; j++)
//    {
//		  g_power[j] = Group_Applied_Power[j]/1000;
//			g_Energy[j] = Group_Energy[j]/10;
//		}		
//		
//    for(k=0; k<24; k++)
//    {
//		  o_power[k] = unit_applied_power[k]/1000;
//			o_Energy[k] = unit_energy[k]/10;
//		}	
//		
//	memset(devData, 0, sizeof(pduDevData));
//	
//	ptr = &(devData->group);
//	ptrline = &(devData->line);
//	ptrout = &(devData->output);
//	devic=&(devData->dev);	
//	userpa=&(devData->userp);		
//	netip=&(devData->network);	
//	
//	devic->devname=(uint8_t*)devicename;    //设备名
//	
//	group_data(ptr);             //组数据初始化	
//	line_data(ptrline);             //相数据初始化
//	output_data(ptrout);             //输出位数据初始化	
//	
//	ptrline->pow = power_buf;          //功率
//	ptrline->ele = Energy_buf;        //电能	
//	ptrline->pf = power_pf;        //电能	
//	
//	ptr->pow = g_power;          //功率
//	ptr->ele = g_Energy;        //电能	
//	ptr->sw = (uint8_t*)breaker;//回路空开状态
////	unit->roge = (uint8_t*)(&HARDWARE);//回路个数

//	ptrout->pow = o_power;          //功率
//	ptrout->ele = o_Energy;        //电能	
//	ptrout->sw = (uint8_t*)unit_switchs;  //开关状态
//	
//	netip->ipaddr=(uint8_t*)ipadd;          //Ip地址
//	netip->gateway=(uint8_t*)gway;          //网关
//	netip->mask=(uint8_t*)mak;          //掩码
//	netip->udns=(uint8_t*)dnsinfo;          //DNS	

//	netip->gcommunity="public";          //get共同体
//	netip->scommunity="private";          //get共同体	
//	netip->trapa=(uint8_t*)traa;          //trap1
//	netip->trapb=(uint8_t*)trab;          //trap2		

//	netip->smtpuse=(uint8_t*)smtpuser;          //smtp用户	
//	netip->smtppass=(uint8_t*)smtppsd;          //smtp密码
//	netip->smtpserve=(uint8_t*)smtpserver;          //smtp服务器	
//	netip->smtpmail=(uint8_t*)To_Email[0];           //smtp收件箱	

//  userpa->userpsd=(uint8_t*)userpp;       //用户名和密码	
//	
//	devData->env.len = 2;
//	init_unit_tem(&(devData->env.tem));
//	init_unit_hum(&(devData->env.hum));	
// 
//  init_alarm();
//	sent_devData(id,devData); 
//	free(devData);
}





//////////////////////////==============================

void udp_recv_headPacket()
{
	error_t error;
	size_t length;
	uint8_t buffer[84];
	Socket *socket;
	IpAddr clientIpAddr;
	uint16_t clientPort;	
	
	socket = socketOpen(SOCKET_TYPE_DGRAM, SOCKET_IP_PROTO_UDP);
	if(!socket) {return;}	
	
	error = socketBind(socket, &IP_ADDR_ANY, 18725);
	if(error) {return;}
	gSocket = socket;
	
	while(1)
	{
		memset(buffer, 0, sizeof(buffer));
		error = socketReceiveFrom(socket, &gServerIpAddr,&clientPort, buffer, sizeof(buffer), &length, 0);
		if(!error)
		{
			if(strncmp((char*)buffer,"Clever-Manager",13)==0)	 
			{			
				udpLock = 1;
				if(lock==0) 
				{
					lock = 1;
					sent_test();
					lock = 0;
				}
				
				udpLock = 0;
			}					
			osDelayTask(800);		
		}
	}
}

void udp_recv_control()
{	
	error_t error;
	size_t length;
	uint8_t buffer[45];
	Socket *socket;
	IpAddr clientIpAddr;
	uint16_t clientPort;	
	
	socket = socketOpen(SOCKET_TYPE_DGRAM, SOCKET_IP_PROTO_UDP);
	if(!socket) {return;}	
	
	error = socketBind(socket, &IP_ADDR_ANY, 18750);
	if(error) {return;}
	gSocket = socket;
	
	while(1)
	{
		memset(buffer, 0, sizeof(buffer));
		error = socketReceiveFrom(socket, &clientIpAddr,&clientPort, buffer, sizeof(buffer), &length, 0);
		if(!error)
		{
			device_control((char*)buffer);	
		}
	}
}

//////////////////////////==============================






 char* mytokk(char *src,int counter)
{
	char rec[20];
	char next;
	char i,j;
	char *p;
	p=src;
	i=0;j=0;
	next=0;
	memset(rec,0,sizeof(char)*20);
	while((char)(*p)!='\0' || next<20)
	{
		if((char)(*p)==';')
		{
			if(i>counter)
			{
				break;
			}
			i++;
		}		
		if(i==counter)
		{
			rec[j]=(char)(*p);
			j++;
		}	
		p++;
		next++;
	}
	return rec;
}

char myto(char *src,int counter)
{
	char rec[20];
	char next;
	char i,j;
	char *p;
	p=src;
	i=0;j=0;
	next=0;
	memset(rec,0,sizeof(char)*20);
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

 
void device_control(char *cdata)
{
//		char i,j;
//		char datad[45];

//		memset(datad,0,sizeof(char)*45);					
//		for(i=0;i<45;i++)
//		{
//			datad[i]=*cdata++;
//		}	
//		if(datad[14]==0x05&&datad[15]==0x11)
//		{	
//				for(i=0;i<10;i++)
//				{
//					I2cWrite(37+i,0);
//					devicename[i]=0;
//				}
//				for(i=0;i<datad[17];i++)
//				{
//					I2cWrite(37+i,datad[18+i]);
//					devicename[i]=datad[18+i];	
//				}	
//		}	
//		if(datad[14]==0x06&&datad[15]==0x11)
//		{	
//				char udpuserp[25];
//				char *uuser;
//				char *upsd;	
//				char udpuser[10];
//				char udppsd[10];					
//				for(i=0;i<10;i++)
//				{
//					I2cWrite(47+i,0);
//					I2cWrite(57+i,0);							
//					user[0][i]=0;
//					psd[0][i]=0;							
//				}		
//				memset(udpuserp,0,sizeof(char)*25);						
//				for(i=0;i<datad[17];i++)
//				{
//					udpuserp[i]=datad[18+i];
//				}	
//		
//				uuser =mytokk(udpuserp,0);
//				for(i=0;i<10;i++)
//				{
//					udpuser[i]=*uuser++;
//				}
//				upsd =mytokk(udpuserp,1);	
//				for(i=0;i<10;i++)
//				{
//					udppsd[i]=*upsd++;

//				}		
//				for(i=0;i<10;i++)
//				{
//					I2cWrite(47+i,udpuser[i]);
//					I2cWrite(57+i,udppsd[i+2]);	
//					user[0][i]=udpuser[i];
//					psd[0][i]=udppsd[i+2];
//				}							
//			
//				
//		}
//		if(datad[14]==0x07&&datad[15]==0xA1)
//		{	
//				memset(smtpuser,0,sizeof(char)*25);
//				strcpy(smtpuser,"");	
//				W25QXX_Write((u8*)smtpuser,0,25);
//				for(i=0;i<datad[17];i++)
//				{
//					smtpuser[i]=datad[18+i];							
//				}	
//				W25QXX_Write((u8*)smtpuser,0,25);	
//				
//		}	
//		if(datad[14]==0x07&&datad[15]==0xA2)
//		{	
//				memset(smtppsd,0,sizeof(char)*25);
//				strcpy(smtppsd,"");	
//				W25QXX_Write((u8*)smtppsd,25,25);
//				for(i=0;i<datad[17];i++)
//				{
//					smtppsd[i]=datad[18+i];							
//				}	
//				W25QXX_Write((u8*)smtppsd,25,25);		
//				
//		}	
//		if(datad[14]==0x07&&datad[15]==0xA3)
//		{	
//				memset(smtpserver,0,sizeof(char)*25);
//				strcpy(smtpserver,"");	
//				W25QXX_Write((u8*)smtpserver,50,25);
//				for(i=0;i<datad[17];i++)
//				{
//					smtpserver[i]=datad[18+i];							
//				}	
//				W25QXX_Write((u8*)smtpserver,50,25);		
//				
//		}			
//		if(datad[14]==0x07&&datad[15]==0xA6)  //clevermanage邮件设置
//		{	
//				memset(&To_Email[0][0],0,sizeof(char)*25);
//				strcpy(&To_Email[0][0],"");	
//				W25QXX_Write((u8*)&To_Email[0][0],75,25);
//				for(i=0;i<datad[17];i++)
//				{
//					To_Email[0][i]=datad[18+i];							
//				}	
//				W25QXX_Write((u8*)&To_Email[0][0],75,25);
//		}			
//		if(datad[14]==13)
//		{	      
//				USART6_TX_STA=0XA1;
//				SW_Flag = 1;
//				sw_value[0] = datad[15];          //第几位
//				sw_value[1] = datad[18];           //开或关
////				unit_switchs[datad[15]-1] = datad[18] + 1;
//		}
//		if(datad[14]==0x72)
//		{	      
//				USART6_TX_STA=0XA1;
//				SW_Flag = 3;				
//				sw_value[1] = datad[18];           //开或关	
//			 if(LINE_NUM==1)
//			 {
//				 if(HARDWARE==2)
//				 {
//					 if(datad[15]==1)sw_value[0] = 1;          //第几回路	
//					 else if(datad[15]==2)sw_value[0] = 4;          //第几回路	
//					 else USART6_TX_STA=0;
//				 }
//				 else
//				 {
//					 if(datad[15]==1)sw_value[0] = 1;          //第几回路	
//					 else if(datad[15]==2)sw_value[0] = 3;          //第几回路		
//					 else if(datad[15]==3)sw_value[0] = 4;          //第几回路	
//					 else if(datad[15]==4)sw_value[0] = 6;          //第几回路	
//					 else USART6_TX_STA=0;	
//				 }
//			 }
//			 else
//			 {
//				 if(HARDWARE==3)
//				 {
//					 if(datad[15]==1)sw_value[0] = 1;          //第几回路	
//					 else if(datad[15]==2)sw_value[0] = 3;          //第几回路		
//					 else if(datad[15]==3)sw_value[0] = 5;          //第几回路	
//					 else USART6_TX_STA=0;	
//				 }
//				 else sw_value[0] = datad[15];          //第几回路		 
//			 }
//			
//			
//		}					
//		if(datad[14]==18&&datad[15]== 0x00 || datad[14]==0x13&&datad[15]== 0x00 || datad[14]==0x72&&datad[15]== 0x00)
//		{	      
//			USART6_TX_STA=0XA1;
//			SW_Flag = 2;
//			sw_value[1] = datad[18];           //总开关
//		}		
//   	for(j=13;j<37;j++)	
//		{
//			if(datad[14]==0x00&&datad[15]== j-12)
//			{	
//					unit_cur[j-13][1] = datad[18]*256+datad[19];
//					unit_cur[j-13][2] = datad[20]*256+datad[21];
//					unit_cur[j-13][3] = datad[22]*256+datad[23];
//					unit_cur[j-13][4] = datad[24]*256+datad[25];					
//					
//					I2cWrite_2(74+(j-13),datad[19]);
//					I2cWrite_2(98+(j-13),datad[21]);		
//					I2cWrite_2(122+(j-13),datad[23]);
//					I2cWrite_2(146+(j-13),datad[25]);				
//			}			
//	  }
//		if(datad[14]==0x00&&datad[15]== 0x00)
//		{	
//			 for(i=0; i<24; i++)
//			 {
//					unit_cur[i][1] = datad[18]*256+datad[19];
//					unit_cur[i][2] = datad[20]*256+datad[21];
//					unit_cur[i][3] = datad[22]*256+datad[23];
//					unit_cur[i][4] = datad[24]*256+datad[25];					
//					
//					I2cWrite_2(74+i,datad[19]);
//					I2cWrite_2(98+i,datad[21]);		
//					I2cWrite_2(122+i,datad[23]);
//					I2cWrite_2(146+i,datad[25]);				 
//			 }			
//		}				
//		for(j=7; j<13; j++)
//		{
//			if(datad[14]==0x71&&datad[15]== j-6)
//			{				
//					Group_Cur[j-7][1] = datad[18]*256+datad[19];
//					Group_Cur[j-7][2] = datad[20]*256+datad[21];
//					Group_Cur[j-7][3] = datad[22]*256+datad[23];
//					Group_Cur[j-7][4] = datad[24]*256+datad[25];					
//					
//					I2cWrite_2(18+(j-7)*2,datad[18]);
//					I2cWrite_2(19+(j-7)*2,datad[19]);		
//					I2cWrite_2(30+(j-7)*2,datad[20]);
//					I2cWrite_2(31+(j-7)*2,datad[21]);
//					I2cWrite_2(42+(j-7)*2,datad[22]);
//					I2cWrite_2(43+(j-7)*2,datad[23]);		
//					I2cWrite_2(54+(j-7)*2,datad[24]);
//					I2cWrite_2(55+(j-7)*2,datad[25]);	
//			}
//		}
//		if(datad[14]==0x71&&datad[15]== 0x00)
//		{		
//			 for(i=0; i<6; i++)
//			 {
//					Group_Cur[i][1] = datad[18]*256+datad[19];
//					Group_Cur[i][2] = datad[20]*256+datad[21];
//					Group_Cur[i][3] = datad[22]*256+datad[23];
//					Group_Cur[i][4] = datad[24]*256+datad[25];					
//					
//					I2cWrite_2(18+i*2,datad[18]);
//					I2cWrite_2(19+i*2,datad[19]);		
//					I2cWrite_2(30+i*2,datad[20]);
//					I2cWrite_2(31+i*2,datad[21]);
//					I2cWrite_2(42+i*2,datad[22]);
//					I2cWrite_2(43+i*2,datad[23]);		
//					I2cWrite_2(54+i*2,datad[24]);
//					I2cWrite_2(55+i*2,datad[25]);	
//			 }
//		}		
//		for(j=4;j<7;j++)
//		{				
//			if(datad[14]==0x02&&datad[15]==j-3)
//			{							
//					Total_Cur[j-4][1]=datad[18]*256+datad[19]; 
//					Total_Cur[j-4][2]=datad[20]*256+datad[21];	
//					Total_Cur[j-4][3]=datad[22]*256+datad[23]; 
//					Total_Cur[j-4][4]=datad[24]*256+datad[25];					
//					
//					I2cWrite(248+(j-4)*2,datad[18]);
//					I2cWrite(249+(j-4)*2,datad[19]);
//					I2cWrite_2(0+(j-4)*2,datad[20]);
//					I2cWrite_2(1+(j-4)*2,datad[21]);
//					I2cWrite_2(6+(j-4)*2,datad[22]);
//					I2cWrite_2(7+(j-4)*2,datad[23]);
//					I2cWrite_2(12+(j-4)*2,datad[24]);
//					I2cWrite_2(13+(j-4)*2,datad[25]);					
//			}
//		}
//		if(datad[14]==0x02 && datad[15]==0x00)
//		{		
//			  for(i=0; i<3; i++)
//        {			
//					Total_Cur[i][1]=datad[18]*256+datad[19]; 
//					Total_Cur[i][2]=datad[20]*256+datad[21];	
//					Total_Cur[i][3]=datad[22]*256+datad[23]; 
//					Total_Cur[i][4]=datad[24]*256+datad[25];					
//					
//					I2cWrite(248+i*2,datad[18]);
//					I2cWrite(249+i*2,datad[19]);
//					I2cWrite_2(0+i*2,datad[20]);
//					I2cWrite_2(1+i*2,datad[21]);
//					I2cWrite_2(6+i*2,datad[22]);
//					I2cWrite_2(7+i*2,datad[23]);
//					I2cWrite_2(12+i*2,datad[24]);
//					I2cWrite_2(13+i*2,datad[25]);	
//				}
//		}		
//		for(j=1; j<4; j++)
//		{
//			if(datad[14]==0x01&&datad[15]==j)
//			{			
//					Tvol[j-1][1]=(datad[18]*256+datad[19])/10;
//					Tvol[j-1][2]=(datad[20]*256+datad[21])/10;
//					datad[18]=Tvol[j-1][1]/256%256;
//					datad[19]=Tvol[j-1][1]%256;							
//					datad[20]=Tvol[j-1][2]/256%256;
//					datad[21]=Tvol[j-1][2]%256;		
//					
//					I2cWrite(236+(j-1)*2,datad[18]);
//					I2cWrite(237+(j-1)*2,datad[19]);
//					I2cWrite(242+(j-1)*2,datad[20]);
//					I2cWrite(243+(j-1)*2,datad[21]);				
//			}					
//	  }	
//		if(datad[14]==0x01&&datad[15]==0x00)
//		{	
//        for(i=0; i<3; i++)
//				{
//					Tvol[i][1]=(datad[18]*256+datad[19])/10;
//					Tvol[i][2]=(datad[20]*256+datad[21])/10;
//					datad[18]=Tvol[i][1]/256%256;
//					datad[19]=Tvol[i][1]%256;							
//					datad[20]=Tvol[i][2]/256%256;
//					datad[21]=Tvol[i][2]%256;		
//					
//					I2cWrite(236+i*2,datad[18]);
//					I2cWrite(237+i*2,datad[19]);
//					I2cWrite(242+i*2,datad[20]);
//					I2cWrite(243+i*2,datad[21]);
//				}
//		}		
//		for(j=1; j<3; j++)
//		{
//			if(datad[14]==0x03&&datad[15]==j)
//			{			
//				tem[j-1][1]=(datad[18]*256+datad[19])/10;
//				tem[j-1][2]=(datad[20]*256+datad[21])/10;	
//					
//			  I2cWrite_2(66+(j-1),tem[j-1][1]);
//			  I2cWrite_2(68+(j-1),tem[j-1][2]);					
//			}	
//			if(datad[14]==0x04&&datad[15]==j)
//			{			
//				hum[j-1][1]=(datad[18]*256+datad[19])/10;
//				hum[j-1][2]=(datad[20]*256+datad[21])/10;	
//					
//			  I2cWrite_2(70+(j-1),hum[j-1][1]);
//			  I2cWrite_2(72+(j-1),hum[j-1][2]);					
//			}				
//	  }	
//		if(datad[14]==0x03&&datad[15]==0x00)
//		{	
//      for(i=0; i<2; i++)	
//			{
//				tem[i][1]=(datad[18]*256+datad[19])/10;
//				tem[i][2]=(datad[20]*256+datad[21])/10;	
//				I2cWrite_2(66+i,tem[i][1]);
//				I2cWrite_2(68+i,tem[i][2]);				
//			}					
//		}	
//		if(datad[14]==0x04&&datad[15]==0x00)
//		{	
//      for(i=0; i<2; i++)	
//			{
//				hum[i][1]=(datad[18]*256+datad[19])/10;
//				hum[i][2]=(datad[20]*256+datad[21])/10;	
//				I2cWrite_2(70+i,hum[i][1]);
//				I2cWrite_2(72+i,hum[i][2]);				
//			}					
//		}			
//		if(datad[14]==0x14&&datad[15]==0x03&&datad[18]==0x01)   //重启设备
//		{	
//			devicedown();	
//			return;						
//		}	
//		if(datad[14]==0x14&&datad[15]==0x02&&datad[18]==0x01)   //重置设备
//		{	
//			upgrade_set=0;
//			IIC_Reset=1;
//			I2cWrite_2(235,IIC_Reset); 
//			devicedown();
//			return;					
//		}		
//		if(datad[14]==0x07&&datad[15]==0x11)
//		{	
//				char udpip[20];	
//				char udpip1;
//				char udpip2;
//				char udpip3;
//				char udpip4;					
//				for(i=0;i<4;i++)
//				{
//					I2cWrite(i,0);
//				}
//				for(i=0;i<datad[17];i++)
//				{
//					udpip[i]=datad[18+i];
//				}		
//				ip1=udpip1 =myto(udpip,0);
//				ip2=udpip2 =myto(udpip,1);
//				ip3=udpip3 =myto(udpip,2);
//				ip4=udpip4 =myto(udpip,3);
//				I2cWrite(0,udpip1);
//				I2cWrite(1,udpip2);
//				I2cWrite(2,udpip3);
//				I2cWrite(3,udpip4);					
//		}	
//		if(datad[14]==0x07&&datad[15]==0x13)
//		{	
//				char udpmask[20];	
//				char udpmask1;
//				char udpmask2;
//				char udpmask3;
//				char udpmask4;					
//				for(i=4;i<8;i++)
//				{
//					I2cWrite(i,0);
//				}
//				for(i=0;i<datad[17];i++)
//				{
//					udpmask[i]=datad[18+i];
//				}		
//				ms1=udpmask1 =myto(udpmask,0);
//				ms2=udpmask2 =myto(udpmask,1);
//				ms3=udpmask3 =myto(udpmask,2);
//				ms4=udpmask4 =myto(udpmask,3);
//				I2cWrite(4,udpmask1);
//				I2cWrite(5,udpmask2);
//				I2cWrite(6,udpmask3);
//				I2cWrite(7,udpmask4);						
//				
//		}	
//		if(datad[14]==0x07&&datad[15]==0x12)
//		{	
//				char udpgw[20];	
//				char udpgw1;
//				char udpgw2;
//				char udpgw3;
//				char udpgw4;					
//				for(i=8;i<12;i++)
//				{
//					I2cWrite(i,0);
//				}
//				for(i=0;i<datad[17];i++)
//				{
//					udpgw[i]=datad[18+i];
//				}		
//				gw1=udpgw1 =myto(udpgw,0);
//				gw2=udpgw2 =myto(udpgw,1);
//				gw3=udpgw3 =myto(udpgw,2);
//				gw4=udpgw4 =myto(udpgw,3);
//				I2cWrite(8,udpgw1);
//				I2cWrite(9,udpgw2);
//				I2cWrite(10,udpgw3);
//				I2cWrite(11,udpgw4);						
//				
//		}		
//		if(datad[14]==0x07&&datad[15]==0x14)
//		{	
//				char udpdns[20];	
//				char udpdns1;
//				char udpdns2;
//				char udpdns3;
//				char udpdns4;					
//				for(i=12;i<16;i++)
//				{
//					I2cWrite(i,0);
//				}
//				for(i=0;i<datad[17];i++)
//				{
//					udpdns[i]=datad[18+i];
//				}		
//				dns_info[0]=udpdns1 =myto(udpdns,0);
//				dns_info[1]=udpdns2 =myto(udpdns,1);
//				dns_info[2]=udpdns3 =myto(udpdns,2);
//				dns_info[3]=udpdns4 =myto(udpdns,3);
//			  memset(dnsinfo,0,sizeof(char)*16);
//		    sprintf(dnsinfo,"%d.%d.%d.%d",dns_info[0],dns_info[1],dns_info[2],dns_info[3]);
//				I2cWrite(12,udpdns1);
//				I2cWrite(13,udpdns2);
//				I2cWrite(14,udpdns3);
//				I2cWrite(15,udpdns4);										
//		}	
//		if(datad[14]==0x07&&datad[15]==0x84)
//		{	
//				char udptrapa[20];	
//				char udptrapa1;
//				char udptrapa2;
//				char udptrapa3;
//				char udptrapa4;					
//				for(i=205;i<209;i++)
//				{
//					I2cWrite(i,0);
//				}
//				for(i=0;i<datad[17];i++)
//				{
//					udptrapa[i]=datad[18+i];
//				}		
//				trapip1[0]=udptrapa1 =myto(udptrapa,0);
//				trapip1[1]=udptrapa2 =myto(udptrapa,1);
//				trapip1[2]=udptrapa3 =myto(udptrapa,2);
//				trapip1[3]=udptrapa4 =myto(udptrapa,3);
//				I2cWrite(205,udptrapa1);
//				I2cWrite(206,udptrapa2);
//				I2cWrite(207,udptrapa3);
//				I2cWrite(208,udptrapa4);									
//		}
//		if(datad[14]==0x07&&datad[15]==0x85)
//		{	
//				char udptrapb[20];	
//				char udptrapb1;
//				char udptrapb2;
//				char udptrapb3;
//				char udptrapb4;					
//				for(i=209;i<213;i++)
//				{
//					I2cWrite(i,0);
//				}
//				for(i=0;i<datad[17];i++)
//				{
//					udptrapb[i]=datad[18+i];
//				}		
//				trapip2[0]=udptrapb1 =myto(udptrapb,0);
//				trapip2[1]=udptrapb2 =myto(udptrapb,1);
//				trapip2[2]=udptrapb3 =myto(udptrapb,2);
//				trapip2[3]=udptrapb4 =myto(udptrapb,3);
//				I2cWrite(209,udptrapb1);
//				I2cWrite(210,udptrapb2);
//				I2cWrite(211,udptrapb3);
//				I2cWrite(212,udptrapb4);						
//				
//		}			
}
	
 
 
 
 
 
void udpTask(void *param)
{	
	udp_recv_headPacket();
}

void udpControl(void *param)
{
	udp_recv_control();
}

void reques(char *urlinfo, char *req)
{
	char *rec;
	int index,beg,i;
	rec = req;
	index=0;
	beg=0;
	
	while(index <45)
	{
		if((char)(*rec) == 0x23 && beg==0)     
		{
			beg = index; 
		}
		else if(beg)
		{
			for(i=0;i<beg;i++)
			{
		    *urlinfo++=*req++;
			}
			return;
		}
		rec++;
		index++;
	}
}

void tcpControl(void *param)
{
	error_t error;
	uint8_t buffer[45];
	uint8_t tcp_data_buf[45];
	Socket *serverSocket;
  Socket *clientSocket;
	IpAddr clientIpAddr;
	size_t length=45;
  uint16_t clientPort;
	
	
  serverSocket = socketOpen(SOCKET_TYPE_STREAM, SOCKET_IP_PROTO_TCP);

	if(!serverSocket) 
	{
		return;
	}

	error = socketBind(serverSocket, &IP_ADDR_ANY, 12707);
	
	if(error)
	{
		return;
	}
	error = socketListen(serverSocket, 0);
	if(error)
	{
		return;
	}
	while(1)
	{
	  clientSocket = socketAccept(serverSocket, &clientIpAddr, &clientPort);
	  while(1)
	  {
		memset(buffer,0, sizeof(char)*45);
		error = socketReceive(clientSocket, buffer, sizeof(buffer), &length, 0);
		if(!error)
		{
			memset(tcp_data_buf,0,sizeof(char)*45);
			reques((char*)tcp_data_buf,(char*)buffer);
			
			if(tcp_data_buf[0]==0x7E&&tcp_data_buf[1]==0x5E)	
				device_control((char*)tcp_data_buf);				
		} else {
			socketClose(clientSocket);			
			break;
		}
		
	  }
		
	}
	socketClose(clientSocket);
}

void appread(void *param)
{
	error_t error;
	uint8_t buffer[45];
//	uint8_t tcp_data_buf[45];
	Socket *serverSocketa;
//  Socket *clientSocketa;
//	IpAddr clientIpAddrr;
	size_t lengtht = 45;
  uint16_t clientPortt;
	char *cluser;
	char *clpassword;
 	char cuser[15];
	char cpassword[15];
	int i;
	
	
  serverSocketa = socketOpen(SOCKET_TYPE_STREAM, SOCKET_IP_PROTO_TCP);

	if(!serverSocketa) 
	{
		return;
	}

	error = socketBind(serverSocketa, &IP_ADDR_ANY, 11283);

	if(error)
	{
		return;
	}
	error = socketListen(serverSocketa, 0);
	if(error)
	{
		return;
	}
	while(1)
	{
	  clientSocketa = socketAccept(serverSocketa, &clientIpAddrr, &clientPortt);	
		memset(buffer,0, sizeof(char)*45);
		error = socketReceive(clientSocketa, buffer, sizeof(buffer), &lengtht, 0);			
		if(error)
		{
			socketClose(clientSocketa);			
			continue;
		}	
			
//		cluser =mytokk(buffer,0);
//		for(i=0; i<10; i++)
//		{
//		  cuser[i] = *cluser++;		
//		}		
//		clpassword =mytokk(buffer,1);
//		for(i=0; i<10; i++)
//		{
//		  cpassword[i] = clpassword[i+2];			

//    }	
//		for(i=0; i<5; i++)
//		{

//			  if(strcmp(&user[i][0],cuser)==0 && strcmp(&psd[i][0],cpassword)==0)
//				{
//					socketSend(clientSocketa, "OK", 2, NULL, 0);
//					login = 1;
//					while(clientSocketa) 
//					{		
//						  
//						  if(lock==0) 
//							{
//								lock = 1;
//								sent_test();
//								lock = 0;
//							}
//				
//						  osDelayTask(800);		
//					}
//					 login = 0;	
//			  }	
//		}
 
	}
// 	socketClose(clientSocketa); 
}

void IAP_udp_init(void)
{
   osCreateTask("clevermanager_udp", udpTask, NULL, 1000, 1);
}
void IAP_udp_control(void)
{
   osCreateTask("clevermanager_udp_control", udpControl, NULL, 1000, 1);  
}
void IAP_tcp_control(void)
{
   osCreateTask("clevermanager_tcp_control", tcpControl, NULL, 1000, 1);  
}
void IAP_app_read(void)
{
   osCreateTask("clevermanager_app_read", appread, NULL, 1000, 1);
}