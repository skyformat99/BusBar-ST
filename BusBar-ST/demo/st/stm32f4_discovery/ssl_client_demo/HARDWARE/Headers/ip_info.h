#ifndef  _IP_INFO_H_
#define  _IP_INFO_H_
#include "led.h" 
#include "bsp_key.h"
#include <24c04-iic.h>
#include <stdlib.h>
#include "stm32f4xx.h"
#include "os_port.h"
#include "resource_manager.h"
#include "core/net.h"
#include "drivers/stm32f4x7_eth.h"
#include "drivers/lan8720.h"
#include "dhcp/dhcp_client.h"
#include "ipv6/slaac.h"
#include "tls.h"
#include "tls_cipher_suites.h"
#include "yarrow.h"
#include "error.h"
#include "debug.h"
#include "http/http_server.h"
#include "tftpserver.h"
#include "stm324xg_eval_fsmc_sram.h"
#include "mibs/mib2_impl.h"
#include "private_mib_impl.h"
#include "snmp/snmp_agent.h"
#include "oid.h"
#include "private_mib_module.h"
#include "mibs/mib2_impl.h"
#include <temhum.h>
#include <humtem.h>
#include <string.h>
#include "TIM.h"
#include "smtp/smtp_client.h"
#include "http/http_server.h"
#include "http/mime.h"
#include "str.h"
#include "path.h"
#include "date_time.h"
//#include "spi.h"
//#include "w25qxx.h"
#include "function.h"
#include "telnet.h"
#include "modbus.h"
#include "send_smtp.h"
#include "snmp_trap.h"
//#include "debugudp.h"
#include "sntp/sntp_client.h"
#include "usart_fifo.h"
#include "event_groups.h"
#include "rn8207.h"
#include "lcd.h"
#include "lcd_dispaly.h"
#include "web.h"
#include "tftpserver.h"


#define LINE_NUM  3

//Application configuration
//#define APP_MAC_ADDR "00-AB-CD-EF-84-01"
//#define APP_MAC_ADDR "2C-26-5F-37-A1-01"

#define APP_USE_DHCP ENABLED
//#define APP_IPV4_HOST_ADDR "192.168.1.165"
//#define APP_IPV4_SUBNET_MASK "255.255.255.0"
//#define APP_IPV4_DEFAULT_GATEWAY "192.168.1.1"
//#define APP_IPV4_PRIMARY_DNS "202.96.128.86"
//#define APP_IPV4_SECONDARY_DNS "202.96.134.133"

//#define APP_USE_SLAAC ENABLED
//#define APP_IPV6_LINK_LOCAL_ADDR "fe80::407"
//#define APP_IPV6_PREFIX "2001:db8::"
//#define APP_IPV6_PREFIX_LENGTH 64
//#define APP_IPV6_GLOBAL_ADDR "2001:db8::407"
//#define APP_IPV6_ROUTER "fe80::1"
//#define APP_IPV6_PRIMARY_DNS "2001:4860:4860::8888"
//#define APP_IPV6_SECONDARY_DNS "2001:4860:4860::8844"

//Server hostname and port 服务器主机名和端口
//#define APP_SERVER_NAME "192.168.1.196"
////Server port
//#define APP_SERVER_PORT 443

#define APP_HTTP_MAX_CONNECTIONS 15


//Compilation options 编辑选项
#define APP_SET_CIPHER_SUITES DISABLED
#define APP_SET_SERVER_NAME DISABLED
#define APP_SET_TRUSTED_CA_LIST DISABLED
#define APP_SET_CLIENT_CERT DISABLED


//Diffie-Hellman parameters
#define APP_SERVER_DH_PARAMS "certs/dh_params.pem"

//Server's RSA certificate and private key
#define APP_SERVER_RSA_CERT "certs/server_rsa_cert.pem"
#define APP_SERVER_RSA_PRIVATE_KEY "certs/server_rsa_key.pem"

//Server's DSA certificate and private key
#define APP_SERVER_DSA_CERT "certs/server_dsa_cert.pem"
#define APP_SERVER_DSA_PRIVATE_KEY "certs/server_dsa_key.pem"

//Server's ECDSA certificate and private key
#define APP_SERVER_ECDSA_CERT "certs/server_ecdsa_cert.pem"
#define APP_SERVER_ECDSA_PRIVATE_KEY "certs/server_ecdsa_key.pem"

//Trusted CA bundle
#define APP_CA_CERT_BUNDLE "certs/ca_cert_bundle.pem"

//#define APP_SNMP_ENTERPRISE_OID "1.3.6.1.4.1.8072.9999.9999"
#define APP_SNMP_ENTERPRISE_OID "1.3.6.1.4.1.30966.10.2"
#define APP_SNMP_CONTEXT_ENGINE "\x80\x00\x00\x00\x01\x02\x03\x04"
#define APP_SNMP_TRAP_DEST_IP_ADDR "192.168.1.196"

#define TASK_BIT_0	 (1 << 0)
#define TASK_BIT_1	 (1 << 1)
#define TASK_BIT_2	 (1 << 2)
#define TASK_BIT_3	 (1 << 3)


#define TASK_BIT_ALL (TASK_BIT_0 | TASK_BIT_1 | TASK_BIT_2 | TASK_BIT_3  )

extern char ip1;
extern char ip2;
extern char ip3;
extern char ip4;
extern char ip_v4[16];
extern char ms1;
extern char ms2;
extern char ms3;
extern char ms4;
extern char ms_v4[16];
extern char gw1;
extern char gw2;
extern char gw3;
extern char gw4;
extern char gw_v4[16];
extern char mac1;
extern char mac2;
extern char mac3;
extern char mac4;
extern char mac5;
extern char mac6;
extern char mac_v4[25];
extern char dnsinfo[16];
extern char dns_info[4];
extern char webport[2];
extern char https_port[2];
extern char ONorrOFF_DHCP;
extern char ONorrOFF_SSL;
extern char ONorrOFF_SNMPv3;
extern char ONorrOFF_telnet;
extern char cur_dc_ac;
extern char ONorOFF_sound;
extern char language;
extern char SMTPorSMTPS;
extern char devicename[11];
extern char user[11];
extern char psd[11];
extern char snmpsysname[11];
extern char snmpsysuser[17];
extern char snmp_authkey[17];
extern char snmp_privkey[17];
extern char trapip1[4];
extern char trapip2[4];
extern char trap_ip[2][15];
extern char smtpport;
extern char smtpsport;
extern char smtpuser[26];
extern char smtppsd[26];
extern char smtpserver[26];
extern char To_Email[26];
extern char ser;
extern char baud;
extern int VoltageA;
extern int VoltageB;
extern int VoltageC;
extern int CurrentA;
extern int CurrentB;
extern int CurrentC;
extern int CurrentAK;
extern int CurrentBK;
extern int CurrentCK;
extern int VoltageAK;
extern int VoltageBK;
extern int VoltageCK;
extern int active_power[4];
extern int apparent_power[4];
extern int PF[3];
extern int Tvol[3][3];
extern int Tcur[3][3];
extern char Tvol_alarm[3];
extern char Tcur_alarm[3];
extern char Tem_Hum_alarm[2];
extern int Energy8207[3];
extern int Energy8207_dc;
extern int hzperHz[3];
extern char tem[3];
extern char hum[3];
extern int dc_correct_v; 
extern int dc_correct_a;
extern char button_menu[2];
extern char button_up;
extern char button_down;
extern int register_GPQ[4];
extern char register_Phs[4];
extern char register_dc_DCIH[2];
extern char register_dc_DCL[2];
extern int register_dc_UCUH;
extern int IARMSOS_reg;


extern uint_t hitCounter ;
extern DhcpClientSettings dhcpClientSettings;
extern DhcpClientCtx dhcpClientContext;
extern SlaacSettings slaacSettings;
extern SlaacContext slaacContext;
extern YarrowContext yarrowContext;
extern uint8_t seed[32];

extern SnmpAgentContext snmpAgentContext;
extern EventGroupHandle_t xCreatedEventGroup;


void application(void);
//void sendtouser(Socket *socket,char *uri,char *requrl,uint32_t ip);
void sendtouser(TlsContext *context,char *uri,char *requrl,uint32_t ip);
error_t snmpAgentRandCallback(uint8_t *data, size_t length);

#endif