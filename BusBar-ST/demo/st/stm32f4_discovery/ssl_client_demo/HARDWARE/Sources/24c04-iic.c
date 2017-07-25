#include <24c04-iic.h>
#include "ip_info.h"

//u32 FLASH_SIZE=16*1024*1024;	//FLASH 大小为16字节;	

void DelayNop_iic(int tm)
{
		int i=0;
		for(i=0;i<tm;i++)
		{
		}
}
void wp_eeprom(char ch)
{
		if(ch)
			GPIO_ResetBits(GPIOB, GPIO_Pin_5);
		else 
			GPIO_SetBits(GPIOB, GPIO_Pin_5);
}

void SCL(char hl)
{
		if(hl==0)
				GPIO_ResetBits(GPIOB, GPIO_Pin_6);
		else
				GPIO_SetBits(GPIOB, GPIO_Pin_6);
}
void SDA(char hl)
{
		if(hl==0)
				GPIO_ResetBits(GPIOB, GPIO_Pin_7);
		else
				GPIO_SetBits(GPIOB, GPIO_Pin_7);
}

char readSDA()
{
		if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7))
				return 1;
		else
				return 0;	
}

void IICstart()
{
		SDA(1);
		DelayNop_iic(100);
		SCL(1);
		DelayNop_iic(100);
		SDA(0);
		DelayNop_iic(100);
		SCL(0);
		DelayNop_iic(100);
}
void IICstop()
{
		SCL(0);
		DelayNop_iic(100);
		SDA(0);
		DelayNop_iic(100);
		SCL(1);
		DelayNop_iic(100);
		SDA(1);
		DelayNop_iic(100);
}
void IICack()
{
		unsigned char i=0;
		SCL(0);
		DelayNop_iic(100);
		SCL(1);
		DelayNop_iic(100);
		while(!readSDA() && i<200)
		{
				i++;
				DelayNop_iic(20);
		}
		SCL(0);
		DelayNop_iic(100);
}
void IICwritebyte(unsigned char data)
{
		char i;
		unsigned char buf;
		buf	= data;
	
		SCL(0);
		DelayNop_iic(100);
		for(i=0;i<8;i++)
		{
				if(buf>=128)
						SDA(1);
				else
						SDA(0);
				buf = buf<<1;
				SCL(1);
				DelayNop_iic(100);
				SCL(0);
				DelayNop_iic(100);
		}		

}
unsigned char IICreadbyte()
{
	unsigned char i;
	unsigned char rec=0;
	for(i=0;i<8;i++)
	{
			unsigned char data=0;
			SCL(0);
			DelayNop_iic(100);
			SCL(1);
			DelayNop_iic(100);
			data = readSDA();
			rec = rec<<1;
			rec = rec |	data;
			SCL(0);
			DelayNop_iic(100);
	}
	SCL(1);
	DelayNop_iic(100);
	SCL(0);
	DelayNop_iic(100);
	return rec;
}
/**************************************************************************************************************************/
//unsigned char I2cRead(unsigned int addr)                      // AT24C64:0-8191
//{
//		unsigned char data;
//		IICstart();
//		IICwritebyte(0xA0);
//		IICack();
//		IICwritebyte(addr>>8);   //写入地址高字节
//		IICack();
//		IICwritebyte(addr&0x00ff); //写入地址低字节
//		IICack();	
//		IICstart();
//		IICwritebyte(0xA1);
//		IICack();
//		data = IICreadbyte();
//		IICstop();
//		return data;	
//}
//int I2cWrite(unsigned int addr,unsigned char dat)
//{
//		char i=0;

//		IICstart();
//		IICwritebyte(0xA0);
//		IICack();
//		IICwritebyte(addr>>8);//写入地址高字节
//		IICack();
//		IICwritebyte(addr&0x00ff);//写入地址低字节
//		IICack();	
//		IICwritebyte(dat);
//		IICack();
//		IICstop();
//		DelayNop_iic(200);
//		while(I2cRead(addr) != dat && i<5)
//		{
//				IICstart();
//				IICwritebyte(0xA0);
//				IICack();
//				IICwritebyte(addr);
//				IICack();
//				IICwritebyte(dat);
//				IICack();
//				IICstop();
//				DelayNop_iic(200);
//				DelayNop_iic(200);
//				i++;
//		}
//		if(i>=4)
//				return 1;	
//		return 0;

//}
/**************************************************************************************************************************/
unsigned char I2cRead(unsigned char addr)                      // AT24C02 : 0-255
{
		unsigned char data;
		IICstart();
		IICwritebyte(0xA0);
		IICack();
		IICwritebyte(addr);
		IICack();
		IICstart();
		IICwritebyte(0xA1);
		IICack();
		data = IICreadbyte();
		IICstop();
		return data;
}
int I2cWrite(unsigned char addr,unsigned char dat)
{
		char i=0;
		wp_eeprom(1);   //WP拉低
		IICstart();
		IICwritebyte(0xA0);
		IICack();
		IICwritebyte(addr);
		IICack();
		IICwritebyte(dat);
		IICack();
		IICstop();
		DelayNop_iic(200);
		while(I2cRead(addr) != dat && i<5)
		{
				IICstart();
				IICwritebyte(0xA0);
				IICack();
				IICwritebyte(addr);
				IICack();
				IICwritebyte(dat);
				IICack();
				IICstop();
				DelayNop_iic(200);
				DelayNop_iic(200);
				i++;
		}
		if(i>=4)
		{
				wp_eeprom(0);   //WP拉高
				return 1;
		}
		wp_eeprom(0);   //WP拉高
		return 0;
}


unsigned char I2cRead_2(unsigned char Addr)     // AT24C04 : 256-511
{
		unsigned char data;
		IICstart();
		IICwritebyte(0xA2);
		IICack();
		IICwritebyte(Addr);
		IICack();
		IICstart();
		IICwritebyte(0xA3);        // AT24C04
		IICack();
		data = IICreadbyte();
		IICstop();
		return data;	
}
int I2cWrite_2(unsigned char addr,unsigned char dat)
{
		char i=0;
		wp_eeprom(1);   //WP拉低
		IICstart();
		IICwritebyte(0xA2);
		IICack();
		IICwritebyte(addr);
		IICack();
		IICwritebyte(dat);
		IICack();
		IICstop();
		DelayNop_iic(200);
		while(I2cRead(addr) != dat && i<5)
		{
				IICstart();
				IICwritebyte(0xA2);
				IICack();
				IICwritebyte(addr);
				IICack();
				IICwritebyte(dat);
				IICack();
				IICstop();
				DelayNop_iic(200);
				DelayNop_iic(200);
				i++;
		}
		if(i>=4)
		{
				wp_eeprom(0);   //WP拉高
				return 1;
		}
		wp_eeprom(0);   //WP拉高
		return 0;
}

void IICinit(void)
{
	//SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
		GPIO_InitTypeDef  GPIO_InitStructure;
    /* GPIOD Periph clock enable */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    /* Configure PD12, PD13, PD14 and PD15 in output pushpull mode */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOB, &GPIO_InitStructure);                // PB6--SCL
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOB, &GPIO_InitStructure);               //PB7--SDA     

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;              //WP-PB5
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOB, &GPIO_InitStructure);		

		wp_eeprom(0);   //WP拉高
}

void iicresetdata(void)
{
		char i,j;
		//ip
		I2cWrite(0,192);
		I2cWrite(1,168);
		I2cWrite(2,1);
		I2cWrite(3,163);
		//mask
		I2cWrite(4,255);
		I2cWrite(5,255);
		I2cWrite(6,255);
		I2cWrite(7,0);
		//gw
		I2cWrite(8,192);
		I2cWrite(9,168);
		I2cWrite(10,1);
		I2cWrite(11,1);
	//dns
		I2cWrite(12,202);
		I2cWrite(13,96);
		I2cWrite(14,128);
		I2cWrite(15,86);	
		
		//webport
		I2cWrite(22,0);
		I2cWrite(23,80);        //HTTP
		I2cWrite(24,1);
		I2cWrite(25,187);		   //HTTPS
//		
		I2cWrite(26,0);           //DHCP
		I2cWrite(27,0);           //SSL
		I2cWrite(28,0);           //SNMPv3
		I2cWrite(29,1);           //telnet       
		I2cWrite(30,0);          //消音   
		I2cWrite(32,0);          //SMTP/SMTPS
		I2cWrite(33,0);          //IAP		

		memset(devicename,0,sizeof(char)*10);
		strcpy(devicename,"IP-PDU");
		memset(user,0,sizeof(char)*10);
		strncpy(user,"admin",10);
		memset(psd,0,sizeof(char)*10);
		strncpy(psd,"admin",10);
		memset(snmpsysname,0,sizeof(char)*10);
		strcpy(snmpsysname,"IP-PDU");		
		for(i=0;i<10;i++)
		{
				I2cWrite(34+i,devicename[i]);
				I2cWrite(44+i,user[i]);
				I2cWrite(54+i,psd[i]); 
				I2cWrite(64+i,snmpsysname[i]);
		}
		memset(snmpsysuser,0,sizeof(char)*16);
		strcpy(snmpsysuser,"clever");
		memset(snmp_authkey,0,sizeof(char)*16);
		strcpy(snmp_authkey,"authkey1");
		memset(snmp_privkey,0,sizeof(char)*16);
		strcpy(snmp_privkey,"privkey1");		
		for(i=0;i<16;i++)
		{
				I2cWrite(74+i,snmpsysuser[i]);
			  I2cWrite(90+i,snmp_authkey[i]);              //end-105
				I2cWrite_2(68+i,snmp_privkey[i]);
		}
		
		I2cWrite(112,0);//trap1
		I2cWrite(113,0);
		I2cWrite(114,0);
		I2cWrite(115,0);
		
		I2cWrite(116,0);//trap2
		I2cWrite(117,0);
		I2cWrite(118,0);
		I2cWrite(119,0);	

		I2cWrite(120,0);    //smtppost :25
		I2cWrite(121,25);
		I2cWrite(122,1);    //smtpspost :465
		I2cWrite(123,209);			

		memset(smtpuser,0,sizeof(char)*25);
		strcpy(smtpuser,"");
		memset(smtppsd,0,sizeof(char)*25);
		strcpy(smtppsd,"");
		memset(smtpserver,0,sizeof(char)*25);
		strcpy(smtpserver,"");
		memset(To_Email,0,sizeof(char)*25);
		strcpy(To_Email,"");		
		for(i=0;i<25;i++)
		{
				I2cWrite(124+i,smtpuser[i]);
			  I2cWrite(149+i,smtppsd[i]);
				I2cWrite(174+i,smtpserver[i]);
				I2cWrite(199+i,To_Email[i]);
		}		
		I2cWrite(224,1);     //从机地址
		I2cWrite(225,3);		 //波特率
		
		I2cWrite(226,0);   //tem[1]
		I2cWrite(227,60);   //tem[2]
		I2cWrite(228,0);   //hum[1]
		I2cWrite(229,90);   //hum[2]	
		
//		for(i=0;i<3;i++)                    //阈值设置
//		{
//				I2cWrite_2(9+i*8,0);I2cWrite_2(10+i*8,0);
//				I2cWrite_2(11+i*8,0);I2cWrite_2(12+i*8,250);
//				I2cWrite_2(13+i*8,0);I2cWrite_2(14+i*8,0);
//				I2cWrite_2(15+i*8,0);I2cWrite_2(16+i*8,5);        //end-32
//		}				
		
}

void iicreaddata(void)
{
		char i,j;
		//ip
		ip1=I2cRead(0);
		ip2=I2cRead(1);
		ip3=I2cRead(2);
		ip4=I2cRead(3);
		memset(ip_v4,0,sizeof(char)*16);
		sprintf(ip_v4,"%d.%d.%d.%d",ip1,ip2,ip3,ip4);
	
		//mask
		ms1=I2cRead(4);
		ms2=I2cRead(5);
		ms3=I2cRead(6);
		ms4=I2cRead(7);
		memset(ms_v4,0,sizeof(char)*16);
		sprintf(ms_v4,"%d.%d.%d.%d",ms1,ms2,ms3,ms4);	
	
		//gw
		gw1=I2cRead(8);
		gw2=I2cRead(9);
		gw3=I2cRead(10);
		gw4=I2cRead(11);
		memset(gw_v4,0,sizeof(char)*16);
		sprintf(gw_v4,"%d.%d.%d.%d",gw1,gw2,gw3,gw4);			
	
		memset(dns_info,0,sizeof(char)*4);	
		//dnsinfo
		dns_info[0]=I2cRead(12);
		dns_info[1]=I2cRead(13);
		dns_info[2]=I2cRead(14);
		dns_info[3]=I2cRead(15);
		memset(dnsinfo,0,sizeof(char)*16);
		sprintf(dnsinfo,"%d.%d.%d.%d",dns_info[0],dns_info[1],dns_info[2],dns_info[3]);
		
		//mac
		mac1=I2cRead(16);
		mac2=I2cRead(17);
		mac3=I2cRead(18);
		mac4=I2cRead(19);
		mac5=I2cRead(20);
		mac6=I2cRead(21);		

		memset(mac_v4,0,sizeof(char)*25);
		sprintf(mac_v4,"%02x-%02x-%02x-%02x-%02x-%02x",mac1,mac2,mac3,mac4,mac5,mac6);	
		
		webport[0]=I2cRead(22);
		webport[1]=I2cRead(23);	
		https_port[0]=I2cRead(24);
		https_port[1]=I2cRead(25);			
    ONorrOFF_DHCP = I2cRead(26);		         // 0:off  1:on		
		ONorrOFF_SSL = I2cRead(27);		         // 0:off  1: on
		ONorrOFF_SNMPv3 = I2cRead(28);		         // 0:off   1:on	
		ONorrOFF_telnet = I2cRead(29);		         // 0:off   1:on	
		ONorOFF_sound = I2cRead(30);		         // 0:off   1:on	
		language = I2cRead(31);
		SMTPorSMTPS = I2cRead(32);
		I2cWrite(33,0);          //IAP	
		
		memset(devicename,0,sizeof(char)*10);
		memset(user,0,sizeof(char)*10);
		memset(psd,0,sizeof(char)*10);
		for(i=0;i<10;i++)
		{
				devicename[i]=I2cRead(34+i);
				user[i]=I2cRead(44+i);
				psd[i]=I2cRead(54+i);
        snmpsysname[i] = I2cRead(64+i);		
		}	
		
    memset(snmpsysuser,0,sizeof(char)*16);
		memset(snmp_authkey,0,sizeof(char)*16);
		memset(snmp_privkey,0,sizeof(char)*16);
		for(i=0;i<16;i++)
		{
				snmpsysuser[i]=I2cRead(74+i);
				snmp_authkey[i]=I2cRead(90+i);
				snmp_privkey[i]=I2cRead_2(68+i);
		}
		
		trapip1[0]=I2cRead(112);
		trapip1[1]=I2cRead(113);
		trapip1[2]=I2cRead(114);
		trapip1[3]=I2cRead(115);
		sprintf(&trap_ip[0][0],"%d.%d.%d.%d",trapip1[0],trapip1[1],trapip1[2],trapip1[3]);
		
		trapip2[0]=I2cRead(116);
		trapip2[1]=I2cRead(117);
		trapip2[2]=I2cRead(118);
		trapip2[3]=I2cRead(119);	
		sprintf(&trap_ip[1][0],"%d.%d.%d.%d",trapip2[0],trapip2[1],trapip2[2],trapip2[3]);		
		
		smtpport=I2cRead(120)*256+I2cRead(121);
		smtpsport=I2cRead(122)*256+I2cRead(123);	

		for(i=0;i<25;i++)
		{
				smtpuser[i]=I2cRead(124+i);
				smtppsd[i]=I2cRead(149+i);
				smtpserver[i]=I2cRead(174+i);
				To_Email[i]=I2cRead(199+i);
		}		

		ser = I2cRead(224);
		baud = I2cRead(225);	

		tem[1]=I2cRead(226);//min
		tem[2]=I2cRead(227);//max
		hum[1]=I2cRead(228);//min
		hum[2]=I2cRead(229);//max		
	
		CurrentAK=CurrentBK=CurrentCK=VoltageAK=VoltageBK=VoltageCK=dc_correct_v=dc_correct_a=0;//EnergyAK=EnergyBK=EnergyCK=0;
		CurrentAK=I2cRead(230)*256*256*256+I2cRead(231)*256*256+I2cRead(232)*256+I2cRead(234);
		CurrentBK=I2cRead(235)*256*256*256+I2cRead(236)*256*256+I2cRead(237)*256+I2cRead(238);
		CurrentCK=I2cRead(239)*256*256*256+I2cRead(240)*256*256+I2cRead(241)*256+I2cRead(242);
		
		VoltageAK=I2cRead(243)*256*256*256+I2cRead(244)*256*256+I2cRead(245)*256+I2cRead(246);
		VoltageBK=I2cRead(247)*256*256*256+I2cRead(248)*256*256+I2cRead(249)*256+I2cRead(250);
		VoltageCK=I2cRead(251)*256*256*256+I2cRead(252)*256*256+I2cRead(253)*256+I2cRead(254);	

		Energy8207[0]=I2cRead_2(0)*256*256+I2cRead_2(1)*256+I2cRead_2(2);
		Energy8207[1]=I2cRead_2(3)*256*256+I2cRead_2(4)*256+I2cRead_2(5);
		Energy8207[2]=I2cRead_2(6)*256*256+I2cRead_2(7)*256+I2cRead_2(8);		
		
		for(i=0;i<3;i++)
		{
				Tvol[i][1]=I2cRead_2(9+i*8)*256+I2cRead_2(10+i*8);
				Tvol[i][2]=I2cRead_2(11+i*8)*256+I2cRead_2(12+i*8);
				Tcur[i][1]=I2cRead_2(13+i*8)*256+I2cRead_2(14+i*8);
				Tcur[i][2]=I2cRead_2(15+i*8)*256+I2cRead_2(16+i*8);          //end-32
		}			
		
		dc_correct_v=I2cRead_2(40)*256*256+I2cRead_2(41)*256+I2cRead_2(42);    //直流校正电压
		dc_correct_a=I2cRead_2(43)*256*256+I2cRead_2(44)*256+I2cRead_2(45);    //直流校正电流	
		
		register_GPQ[0] = I2cRead_2(46)*256+I2cRead_2(47);
		register_GPQ[1] = I2cRead_2(48)*256+I2cRead_2(49);
		register_GPQ[2] = I2cRead_2(50)*256+I2cRead_2(51);
		register_Phs[0] = I2cRead_2(52);
		register_Phs[1] = I2cRead_2(53);
		register_Phs[2] = I2cRead_2(54);
		register_dc_DCIH[0] = I2cRead_2(55);
		register_dc_DCIH[1] = I2cRead_2(56);
		register_dc_DCL[0] = I2cRead_2(57);
		register_GPQ[3] = I2cRead_2(58)*256+I2cRead_2(59);
		IARMSOS_reg = I2cRead_2(60)*256+I2cRead_2(61);
//		register_dc_UCUH = I2cRead_2(62)*256+I2cRead_2(63);
		register_dc_DCL[1] = I2cRead_2(64);		
				
		Energy8207_dc = I2cRead_2(65)*256*256+I2cRead_2(66)*256+I2cRead_2(67);
		
}








































