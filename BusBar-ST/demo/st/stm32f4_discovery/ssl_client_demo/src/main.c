/**
 * @file main.c
 * @brief Main routine
 *
 * @section License
 *
 * Copyright (C) 2010-2016 Oryx Embedded SARL. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * @author Oryx Embedded SARL (www.oryx-embedded.com)
 * @version 1.7.2
 **/

//Dependencies
#include "ip_info.h"

//#define APP_MAC_ADDR "00-AB-CD-EF-84-01"
//#define APP_MAC_ADDR "2C-26-5F-37-A1-01"


#if (APP_SET_CIPHER_SUITES == ENABLED)

//List of preferred ciphersuites
static const unsigned short cipherSuites[] =
{
   TLS_RSA_WITH_CAMELLIA_256_GCM_SHA384,
   TLS_DHE_RSA_WITH_CAMELLIA_256_GCM_SHA384,
   TLS_RSA_WITH_AES_256_GCM_SHA384,
   TLS_DHE_RSA_WITH_AES_256_GCM_SHA384,
   TLS_RSA_WITH_CAMELLIA_128_GCM_SHA256,
   TLS_DHE_RSA_WITH_CAMELLIA_128_GCM_SHA256,
   TLS_RSA_WITH_AES_128_GCM_SHA256,
   TLS_DHE_RSA_WITH_AES_128_GCM_SHA256,
   TLS_RSA_WITH_CAMELLIA_256_CBC_SHA256,
   TLS_DHE_RSA_WITH_CAMELLIA_256_CBC_SHA256,
   TLS_RSA_WITH_AES_256_CBC_SHA256,
   TLS_DHE_RSA_WITH_AES_256_CBC_SHA256,
   TLS_RSA_WITH_CAMELLIA_128_CBC_SHA256,
   TLS_DHE_RSA_WITH_CAMELLIA_128_CBC_SHA256,
   TLS_RSA_WITH_AES_128_CBC_SHA256,
   TLS_DHE_RSA_WITH_AES_128_CBC_SHA256,
   TLS_RSA_WITH_CAMELLIA_256_CBC_SHA,
   TLS_DHE_RSA_WITH_CAMELLIA_256_CBC_SHA,
   TLS_RSA_WITH_AES_256_CBC_SHA,
   TLS_DHE_RSA_WITH_AES_256_CBC_SHA,
   TLS_RSA_WITH_CAMELLIA_128_CBC_SHA,
   TLS_DHE_RSA_WITH_CAMELLIA_128_CBC_SHA,
   TLS_RSA_WITH_AES_128_CBC_SHA,
   TLS_DHE_RSA_WITH_AES_128_CBC_SHA,
   TLS_RSA_WITH_SEED_CBC_SHA,
   TLS_DHE_RSA_WITH_SEED_CBC_SHA,
   TLS_RSA_WITH_3DES_EDE_CBC_SHA,
   TLS_DHE_RSA_WITH_3DES_EDE_CBC_SHA,
   TLS_RSA_WITH_RC4_128_SHA
};

#endif

DhcpClientSettings dhcpClientSettings;
DhcpClientCtx dhcpClientContext;
SlaacSettings slaacSettings;
SlaacContext slaacContext;
YarrowContext yarrowContext;
uint8_t seed[32];

uint_t hitCounter = 0;

SnmpAgentSettings snmpAgentSettings;
SnmpAgentSettings snmpAgentSettings;
SnmpAgentContext snmpAgentContext;

char ip1;
char ip2;
char ip3;
char ip4;
char ip_v4[16];
char ms1;
char ms2;
char ms3;
char ms4;
char ms_v4[16];
char gw1;
char gw2;
char gw3;
char gw4;
char gw_v4[16];
char mac1;
char mac2;
char mac3;
char mac4;
char mac5;
char mac6;
char mac_v4[25];
char dnsinfo[16];
char dns_info[4];
char webport[2]; 
char https_port[2];
char ONorrOFF_DHCP;
char ONorrOFF_SSL;
char ONorrOFF_SNMPv3;
char ONorrOFF_telnet;
char cur_dc_ac;
char ONorOFF_sound;
char language;
char SMTPorSMTPS;
char devicename[11];
char user[11];
char psd[11];
char snmpsysname[11];
char snmpsysuser[17];
char snmp_authkey[17];
char snmp_privkey[17];
char trapip1[4];
char trapip2[4];
char trap_ip[2][15];
char smtpport;
char smtpsport;
char smtpuser[26];
char smtppsd[26];
char smtpserver[26];
char To_Email[26];
char ser;
char baud;
int VoltageA;
int VoltageB;
int VoltageC;
int CurrentA;
int CurrentB;
int CurrentC;
int CurrentAK;
int CurrentBK;
int CurrentCK;
int VoltageAK;
int VoltageBK;
int VoltageCK;
int active_power[4];
int apparent_power[4];
int PF[3];
int Tvol[3][3];
int Tcur[3][3];
char tem[3];
char hum[3];
char Tvol_alarm[3];
char Tcur_alarm[3];
char Tem_Hum_alarm[2]={0,0};
int Energy8207[3];
int Energy8207_dc;
int hzperHz[3];
int dc_correct_v; 
int dc_correct_a;
char button_menu[2]={0,0};
char button_up=0;
char button_down=0;
int register_GPQ[4];
char register_Phs[4];
char register_dc_DCIH[2];
char register_dc_DCL[2];
int register_dc_UCUH;
int IARMSOS_reg;

EventGroupHandle_t xCreatedEventGroup = NULL;


/*
*********************************************************************************************************
*	函 数 名: AppObjCreate
*	功能说明: 创建任务通信机制
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
static void AppObjCreate (void)
{
	/* 创建事件标志组 */
	xCreatedEventGroup = xEventGroupCreate();
	
	if(xCreatedEventGroup == NULL)
    {
        /* 没有创建成功，用户可以在这里加入创建失败的处理机制 */
    }
}

void get_dhcp(void *param)
{
	 Ipv4Addr dhcp_addr;
	 Ipv4Addr dhcp_mask;      // 获取DHCP子网掩码
	 Ipv4Addr dhcp_gateway;  //DHCP默认网关
	 Ipv4Addr dhcp_DNS;  

		//Point to the network interface
   NetInterface *interface = &netInterface[0];	
	
	while(1)
	{	
		
#if (IPV4_SUPPORT == ENABLED)
		
//		 ipv4GetHostAddr(interface, &dhcp_addr);                 //从网卡得到IP地址
//		 ipv4GetSubnetMask(interface, &dhcp_mask);                 //从网卡得到子网掩码
//		 ipv4GetDefaultGateway(interface, &dhcp_gateway);                 //从网卡得到网关
//		 ipv4GetDnsServer(interface,0, &dhcp_DNS);                 //从网卡得到DNS
//		 
//		 ip4 = dhcp_addr>>24;ip3 = dhcp_addr>>16&0x00ff;
//		 ip2 = dhcp_addr>>8&0x0000ff;ip1 = dhcp_addr&0x000000ff;
//		 ms4 = dhcp_mask>>24;ms3 = dhcp_mask>>16&0x00ff;
//		 ms2 = dhcp_mask>>8&0x0000ff;ms1 = dhcp_mask&0x000000ff;
//		 gw4 = dhcp_gateway>>24;gw3 = dhcp_gateway>>16&0x00ff;
//		 gw2 = dhcp_gateway>>8&0x0000ff;gw1 = dhcp_gateway&0x000000ff;	
//		 dns_info[3] = dhcp_DNS>>24;dns_info[2] = dhcp_DNS>>16&0x00ff;
//		 dns_info[1] = dhcp_DNS>>8&0x0000ff;dns_info[0] = dhcp_DNS&0x000000ff;		

//		 memset(ip_v4,0,sizeof(char)*16);
//		 sprintf(ip_v4,"%d.%d.%d.%d",ip1,ip2,ip3,ip4);
//		 memset(ms_v4,0,sizeof(char)*16);
//		 sprintf(ms_v4,"%d.%d.%d.%d",ms1,ms2,ms3,ms4);	
//		 memset(gw_v4,0,sizeof(char)*16);
//		 sprintf(gw_v4,"%d.%d.%d.%d",gw1,gw2,gw3,gw4);		
//		 memset(dnsinfo,0,sizeof(char)*16);
//		 sprintf(dnsinfo,"%d.%d.%d.%d",dns_info[0],dns_info[1],dns_info[2],dns_info[3]);	
		 
#endif		
		osDelayTask(300);
	
	}
}

char button_init_softset()
{
		int i;
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    /* Configure Button pin as input floating */
    /* 初始化KEY按键的GPIO管脚，配置为带上拉的输入 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;			     //选择第端口 PA6
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;            //配置为输出口
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;           //配置为推挽输出
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	     //50M时钟速度
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;         //无上拉或下拉
		GPIO_Init(GPIOA, &GPIO_InitStructure);				     //GPIO配置函数	
	
		for(i=0;i<1000000;i++)
		{}
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)==0)            // PA6
			return 1;
		else
			return 0;
}

void board_init()
{
	 char n;
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//设置系统中断优先级分组4
	 IICinit();
	 KEY_Init();
	 LED_Init();   
   EXTIX_Init();
	 Time2_Init();   //扫描按键		
	 LCD_Init();
//	 W25QXX_Init();			//W25QXX初始化	
	 
	 if(button_init_softset())            //恢复出厂设置
	 {
			iicresetdata();    //恢复出厂设置
	 }
//	 
	 iicreaddata();
	 
	 bsp_InitUart();   //串口设置
	 if(baud==0)
		USART_SetBaudRate(USART3,1200);
	 else if(baud==1)
		 USART_SetBaudRate(USART3,2400);
	 else if(baud==2)
		 USART_SetBaudRate(USART3,4800);
	 else if(baud==3)
		 USART_SetBaudRate(USART3,9600);
	 else if(baud==4)
		 USART_SetBaudRate(USART3,19200);	 
	 else if(baud==5)
		 USART_SetBaudRate(USART3,38400);	 
	 else USART_SetBaudRate(USART3,9600);	  
	 
	 for(n=0;n<3;n++)
	{
			Tvol[n][0] = 0;
			Tcur[n][0] = 0;
	}
	tem[0]=0;
	hum[0]=0;
}

/**
 * @brief Main entry point
 * @return Unused value
 **/

int_t main(void)
{
   error_t error;
   NetInterface *interface;      //定义一个网络接口   NetInterface结构体
   size_t oidLen;                             //OID长度
   uint8_t oid[SNMP_MAX_OID_SIZE];            // OID		
   MacAddr macAddr;               //mac地址   
#if (APP_USE_DHCP == ENABLED)
   Ipv4Addr ipv4Addr;
  //  
#endif
	
   //Initialize kernel        初始化内核
   osInitKernel();
	 
	
	 board_init();

	    //Enable RNG peripheral clock
   RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_RNG, ENABLE);
   //Enable RNG
   RNG_Cmd(ENABLE);
	 
   //Standard MIB-II initialization  初始化MIB-II
   error = mib2Init();
   //Any error to report?
   if(error)
   {
      //Debug message
      TRACE_ERROR("Failed to initialize MIB!\r\n");
   }	
	 
   //Private MIB initialization   初始化私有MIB
   error = privateMibInit();
   //Any error to report?
   if(error)
   {
      //Debug message
      TRACE_ERROR("Failed to initialize MIB!\r\n");
   }		 
//	
   //TCP/IP stack initialization   初始化TCP/IP协议栈
   error = netInit();
   //Any error to report?
   if(error)
   {
      //Debug message
      TRACE_ERROR("Failed to initialize TCP/IP stack!\r\n");
   }

   //Configure the first Ethernet interface  配置第一个以太网接口
   interface = &netInterface[0];

   //Set interface name   设置接口名称
   netSetInterfaceName(interface, "eth0");
   //Set host name  设置主机名称
   netSetHostname(interface, "WebServerDemo");
   //Select the relevant network adapter 选择相关的网络适配器
   netSetDriver(interface, &stm32f4x7EthDriver);
   netSetPhyDriver(interface, &lan8720PhyDriver);
   //Set host MAC address  设置Mac地址
   macStringToAddr(mac_v4, &macAddr);
   netSetMacAddr(interface, &macAddr);  

   //Initialize network interface  初始化网络接口
   error = netConfigInterface(interface);
   //Any error to report?
   if(error)
   {
      //Debug message
      TRACE_ERROR("Failed to configure interface %s!\r\n", interface->name);
   }

#if (IPV4_SUPPORT == ENABLED)   //开启IPV4
#if (APP_USE_DHCP == ENABLED)   //开启DHCP
	 
	 if(ONorrOFF_DHCP)                 //DHCP  : ON
	 {
		 //Get default settings
		 dhcpClientGetDefaultSettings(&dhcpClientSettings);
		 //Set the network interface to be configured by DHCP
		 dhcpClientSettings.interface = interface;
		 //Disable rapid commit option
		 dhcpClientSettings.rapidCommit = FALSE;

		 //DHCP client initialization
		 error = dhcpClientInit(&dhcpClientContext, &dhcpClientSettings);
		 //Failed to initialize DHCP client?
		 if(error)
		 {
				//Debug message
				TRACE_ERROR("Failed to initialize DHCP client!\r\n");
		 }

		 //Start DHCP client
		 error = dhcpClientStart(&dhcpClientContext);
		 //Failed to start DHCP client?
		 if(error)
		 {
				//Debug message
				TRACE_ERROR("Failed to start DHCP client!\r\n");
		 }
		 
	 }
	 else
	 {
		 //Set IPv4 host address  设置IPV4主机IP地址
		 ipv4StringToAddr(ip_v4, &ipv4Addr);
		 ipv4SetHostAddr(interface, ipv4Addr);

		 //Set subnet mask  设置子网掩码
		 ipv4StringToAddr(ms_v4, &ipv4Addr);
		 ipv4SetSubnetMask(interface, ipv4Addr);

		 //Set default gateway 设置默认网关
		 ipv4StringToAddr(gw_v4, &ipv4Addr);
		 ipv4SetDefaultGateway(interface, ipv4Addr);

		 //Set primary and secondary DNS servers  设置DNS
		 ipv4StringToAddr(dnsinfo, &ipv4Addr);
		 ipv4SetDnsServer(interface, 0, ipv4Addr); 
		 
	 }
		 

#endif
#endif
	 
	 	 
   //Get default settings   得到默认设置
   snmpAgentGetDefaultSettings(&snmpAgentSettings);
   //Bind SNMP agent to the desired network interface  绑定 SNMP agent到所需的网络接口
   snmpAgentSettings.interface = interface;
   //Minimum version accepted by the SNMP agent   SNMP agent接收最小版本
   snmpAgentSettings.versionMin = SNMP_VERSION_1;
   //Maximum version accepted by the SNMP agent    SNMP agent接收的最大版本
   snmpAgentSettings.versionMax = SNMP_VERSION_2C;
#if (SNMP_V3_SUPPORT == ENABLED)
   //Maximum version accepted by the SNMP agent    SNMP agent接收的最大版本
   snmpAgentSettings.versionMax = SNMP_VERSION_3;
   //Random data generation callback function      生成随机数据回调函数
   snmpAgentSettings.randCallback = snmpAgentRandCallback;
#endif

   //SNMP agent initialization    初始化SNMP agent
   error = snmpAgentInit(&snmpAgentContext, &snmpAgentSettings);
   //Failed to initialize SNMP agent?
   if(error)
   {
      //Debug message
      TRACE_ERROR("Failed to initialize SNMP agent!\r\n");
   }

   //Load standard MIB-II  加载标准MIB-II
   snmpAgentLoadMib(&snmpAgentContext, &mib2Module);
   //Load private MIB   加载私有MIB
   snmpAgentLoadMib(&snmpAgentContext, &privateMibModule);	 
	 
   //Convert enterprise OID from string representation 从字符串转换成企业OID来显示
   oidFromString(APP_SNMP_ENTERPRISE_OID, oid, sizeof(oid), &oidLen);               //APP_SNMP_ENTERPRISE_OID "1.3.6.1.4.1.8072.9999.9999"
   //Set enterprise OID   设置企业OID
   snmpAgentSetEnterpriseOid(&snmpAgentContext, oid, oidLen);	 
	 
   //Set read-only community string  设置只读公共字符
   error = snmpAgentCreateCommunity(&snmpAgentContext, "public",
      SNMP_ACCESS_READ_ONLY);	 
	 
   //Set read-write community string  设置读写公共字符
   snmpAgentCreateCommunity(&snmpAgentContext, "private",
      SNMP_ACCESS_READ_WRITE);	 

	 if(ONorrOFF_SNMPv3==1)
	 {	 
#if (SNMP_V3_SUPPORT == ENABLED)
   //Set context engine identifier  设置标识引擎符的上下文
   snmpAgentSetContextEngine(&snmpAgentContext,
      APP_SNMP_CONTEXT_ENGINE, sizeof(APP_SNMP_CONTEXT_ENGINE) - 1);    //APP_SNMP_CONTEXT_ENGINE "\x80\x00\x00\x00\x01\x02\x03\x04"

   //Add a new user  添加新用户
//   snmpAgentCreateUser(&snmpAgentContext, "des-clever",
//      SNMP_ACCESS_READ_WRITE, SNMP_KEY_FORMAT_TEXT,          // SNMP_KEY_FORMAT_TEXT：ASCII秘钥
//      SNMP_AUTH_PROTOCOL_MD5, "key123456",                    //SNMP_AUTH_PROTOCOL_MD5：认证协议     authkey1
//      SNMP_PRIV_PROTOCOL_NONE, "");  

   //Add a new user  添加新用户
   error = snmpAgentCreateUser(&snmpAgentContext, snmpsysuser,
      SNMP_ACCESS_READ_WRITE, SNMP_KEY_FORMAT_TEXT,          // SNMP_KEY_FORMAT_TEXT：ASCII秘钥
      SNMP_AUTH_PROTOCOL_MD5, snmp_authkey,                    //SNMP_AUTH_PROTOCOL_MD5：认证协议     authkey1
      SNMP_PRIV_PROTOCOL_DES, snmp_privkey);                  // SNMP_PRIV_PROTOCOL_DES: 隐私协议   privkey1
			
		if(error)
		{
      //Debug message
      TRACE_ERROR("Failed to Create SNMP agent!\r\n");			
		}
#endif
	}		
	 
   //Start SNMP agent  启动SNMP agent
   error = snmpAgentStart(&snmpAgentContext);
   //Failed to start SNMP agent?
   if(error)
   {
      //Debug message
      TRACE_ERROR("Failed to start SNMP agent!\r\n");
   }
	 
//   if(ONorrOFF_DHCP)                 //DHCP  : ON	 
//	 {
//		 osCreateTask("DHCP", get_dhcp, NULL, 500, 3);
//	 }
	 
		application();
	 
	  	/* 创建任务通信机制 */
		AppObjCreate();
	 
   //Start the execution of tasks  开始执行任务
   osStartKernel();	 
   //This function should never return
   return 0;
}
