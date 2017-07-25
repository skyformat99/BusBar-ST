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
*	�� �� ��: AppObjCreate
*	����˵��: ��������ͨ�Ż���
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void AppObjCreate (void)
{
	/* �����¼���־�� */
	xCreatedEventGroup = xEventGroupCreate();
	
	if(xCreatedEventGroup == NULL)
    {
        /* û�д����ɹ����û�������������봴��ʧ�ܵĴ������ */
    }
}

void get_dhcp(void *param)
{
	 Ipv4Addr dhcp_addr;
	 Ipv4Addr dhcp_mask;      // ��ȡDHCP��������
	 Ipv4Addr dhcp_gateway;  //DHCPĬ������
	 Ipv4Addr dhcp_DNS;  

		//Point to the network interface
   NetInterface *interface = &netInterface[0];	
	
	while(1)
	{	
		
#if (IPV4_SUPPORT == ENABLED)
		
//		 ipv4GetHostAddr(interface, &dhcp_addr);                 //�������õ�IP��ַ
//		 ipv4GetSubnetMask(interface, &dhcp_mask);                 //�������õ���������
//		 ipv4GetDefaultGateway(interface, &dhcp_gateway);                 //�������õ�����
//		 ipv4GetDnsServer(interface,0, &dhcp_DNS);                 //�������õ�DNS
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
    /* ��ʼ��KEY������GPIO�ܽţ�����Ϊ������������ */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;			     //ѡ��ڶ˿� PA6
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;            //����Ϊ�����
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;           //����Ϊ�������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	     //50Mʱ���ٶ�
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;         //������������
		GPIO_Init(GPIOA, &GPIO_InitStructure);				     //GPIO���ú���	
	
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
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//����ϵͳ�ж����ȼ�����4
	 IICinit();
	 KEY_Init();
	 LED_Init();   
   EXTIX_Init();
	 Time2_Init();   //ɨ�谴��		
	 LCD_Init();
//	 W25QXX_Init();			//W25QXX��ʼ��	
	 
	 if(button_init_softset())            //�ָ���������
	 {
			iicresetdata();    //�ָ���������
	 }
//	 
	 iicreaddata();
	 
	 bsp_InitUart();   //��������
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
   NetInterface *interface;      //����һ������ӿ�   NetInterface�ṹ��
   size_t oidLen;                             //OID����
   uint8_t oid[SNMP_MAX_OID_SIZE];            // OID		
   MacAddr macAddr;               //mac��ַ   
#if (APP_USE_DHCP == ENABLED)
   Ipv4Addr ipv4Addr;
  //  
#endif
	
   //Initialize kernel        ��ʼ���ں�
   osInitKernel();
	 
	
	 board_init();

	    //Enable RNG peripheral clock
   RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_RNG, ENABLE);
   //Enable RNG
   RNG_Cmd(ENABLE);
	 
   //Standard MIB-II initialization  ��ʼ��MIB-II
   error = mib2Init();
   //Any error to report?
   if(error)
   {
      //Debug message
      TRACE_ERROR("Failed to initialize MIB!\r\n");
   }	
	 
   //Private MIB initialization   ��ʼ��˽��MIB
   error = privateMibInit();
   //Any error to report?
   if(error)
   {
      //Debug message
      TRACE_ERROR("Failed to initialize MIB!\r\n");
   }		 
//	
   //TCP/IP stack initialization   ��ʼ��TCP/IPЭ��ջ
   error = netInit();
   //Any error to report?
   if(error)
   {
      //Debug message
      TRACE_ERROR("Failed to initialize TCP/IP stack!\r\n");
   }

   //Configure the first Ethernet interface  ���õ�һ����̫���ӿ�
   interface = &netInterface[0];

   //Set interface name   ���ýӿ�����
   netSetInterfaceName(interface, "eth0");
   //Set host name  ������������
   netSetHostname(interface, "WebServerDemo");
   //Select the relevant network adapter ѡ����ص�����������
   netSetDriver(interface, &stm32f4x7EthDriver);
   netSetPhyDriver(interface, &lan8720PhyDriver);
   //Set host MAC address  ����Mac��ַ
   macStringToAddr(mac_v4, &macAddr);
   netSetMacAddr(interface, &macAddr);  

   //Initialize network interface  ��ʼ������ӿ�
   error = netConfigInterface(interface);
   //Any error to report?
   if(error)
   {
      //Debug message
      TRACE_ERROR("Failed to configure interface %s!\r\n", interface->name);
   }

#if (IPV4_SUPPORT == ENABLED)   //����IPV4
#if (APP_USE_DHCP == ENABLED)   //����DHCP
	 
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
		 //Set IPv4 host address  ����IPV4����IP��ַ
		 ipv4StringToAddr(ip_v4, &ipv4Addr);
		 ipv4SetHostAddr(interface, ipv4Addr);

		 //Set subnet mask  ������������
		 ipv4StringToAddr(ms_v4, &ipv4Addr);
		 ipv4SetSubnetMask(interface, ipv4Addr);

		 //Set default gateway ����Ĭ������
		 ipv4StringToAddr(gw_v4, &ipv4Addr);
		 ipv4SetDefaultGateway(interface, ipv4Addr);

		 //Set primary and secondary DNS servers  ����DNS
		 ipv4StringToAddr(dnsinfo, &ipv4Addr);
		 ipv4SetDnsServer(interface, 0, ipv4Addr); 
		 
	 }
		 

#endif
#endif
	 
	 	 
   //Get default settings   �õ�Ĭ������
   snmpAgentGetDefaultSettings(&snmpAgentSettings);
   //Bind SNMP agent to the desired network interface  �� SNMP agent�����������ӿ�
   snmpAgentSettings.interface = interface;
   //Minimum version accepted by the SNMP agent   SNMP agent������С�汾
   snmpAgentSettings.versionMin = SNMP_VERSION_1;
   //Maximum version accepted by the SNMP agent    SNMP agent���յ����汾
   snmpAgentSettings.versionMax = SNMP_VERSION_2C;
#if (SNMP_V3_SUPPORT == ENABLED)
   //Maximum version accepted by the SNMP agent    SNMP agent���յ����汾
   snmpAgentSettings.versionMax = SNMP_VERSION_3;
   //Random data generation callback function      ����������ݻص�����
   snmpAgentSettings.randCallback = snmpAgentRandCallback;
#endif

   //SNMP agent initialization    ��ʼ��SNMP agent
   error = snmpAgentInit(&snmpAgentContext, &snmpAgentSettings);
   //Failed to initialize SNMP agent?
   if(error)
   {
      //Debug message
      TRACE_ERROR("Failed to initialize SNMP agent!\r\n");
   }

   //Load standard MIB-II  ���ر�׼MIB-II
   snmpAgentLoadMib(&snmpAgentContext, &mib2Module);
   //Load private MIB   ����˽��MIB
   snmpAgentLoadMib(&snmpAgentContext, &privateMibModule);	 
	 
   //Convert enterprise OID from string representation ���ַ���ת������ҵOID����ʾ
   oidFromString(APP_SNMP_ENTERPRISE_OID, oid, sizeof(oid), &oidLen);               //APP_SNMP_ENTERPRISE_OID "1.3.6.1.4.1.8072.9999.9999"
   //Set enterprise OID   ������ҵOID
   snmpAgentSetEnterpriseOid(&snmpAgentContext, oid, oidLen);	 
	 
   //Set read-only community string  ����ֻ�������ַ�
   error = snmpAgentCreateCommunity(&snmpAgentContext, "public",
      SNMP_ACCESS_READ_ONLY);	 
	 
   //Set read-write community string  ���ö�д�����ַ�
   snmpAgentCreateCommunity(&snmpAgentContext, "private",
      SNMP_ACCESS_READ_WRITE);	 

	 if(ONorrOFF_SNMPv3==1)
	 {	 
#if (SNMP_V3_SUPPORT == ENABLED)
   //Set context engine identifier  ���ñ�ʶ�������������
   snmpAgentSetContextEngine(&snmpAgentContext,
      APP_SNMP_CONTEXT_ENGINE, sizeof(APP_SNMP_CONTEXT_ENGINE) - 1);    //APP_SNMP_CONTEXT_ENGINE "\x80\x00\x00\x00\x01\x02\x03\x04"

   //Add a new user  ������û�
//   snmpAgentCreateUser(&snmpAgentContext, "des-clever",
//      SNMP_ACCESS_READ_WRITE, SNMP_KEY_FORMAT_TEXT,          // SNMP_KEY_FORMAT_TEXT��ASCII��Կ
//      SNMP_AUTH_PROTOCOL_MD5, "key123456",                    //SNMP_AUTH_PROTOCOL_MD5����֤Э��     authkey1
//      SNMP_PRIV_PROTOCOL_NONE, "");  

   //Add a new user  ������û�
   error = snmpAgentCreateUser(&snmpAgentContext, snmpsysuser,
      SNMP_ACCESS_READ_WRITE, SNMP_KEY_FORMAT_TEXT,          // SNMP_KEY_FORMAT_TEXT��ASCII��Կ
      SNMP_AUTH_PROTOCOL_MD5, snmp_authkey,                    //SNMP_AUTH_PROTOCOL_MD5����֤Э��     authkey1
      SNMP_PRIV_PROTOCOL_DES, snmp_privkey);                  // SNMP_PRIV_PROTOCOL_DES: ��˽Э��   privkey1
			
		if(error)
		{
      //Debug message
      TRACE_ERROR("Failed to Create SNMP agent!\r\n");			
		}
#endif
	}		
	 
   //Start SNMP agent  ����SNMP agent
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
	 
	  	/* ��������ͨ�Ż��� */
		AppObjCreate();
	 
   //Start the execution of tasks  ��ʼִ������
   osStartKernel();	 
   //This function should never return
   return 0;
}
