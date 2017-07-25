#ifndef  _DEBUGUDP_H_
#define  _DEBUGUDP_H_
#include "core/net.h"
#include "core/ip.h"
#include "core/udp.h"
#include "core/socket.h"
#include "ipv4/ipv4.h"

#define DATA_MSG_SIZE	512		/*数据缓冲区大小*/
#define DEV_CODE_SIZE	4		/*设备代号位数*/
#define DATA_MSG_CODE_SIZE	9

#define DATA_MSG_HDR	0x7E	/*信息头~*/
#define DATA_MSG_STX	0x5E	/*标识字^*/
#define DATA_MSG_ED	0x23	/*结束符*/

#define DATA_MSG_SERVICE	0x10	/*服务端标志*/
#define DATA_MSG_CLIENT		0x03	/*客户端标志*/

#define DATA_DEV_VERSION		1 /*设备通讯类型*/

//#define  UDP_Port          28720           //UDP port
#define UDP_BUF_SIZE	256 /*数据缓冲区大小， IP设备使用256， ARM9系列设备使用512*/     

static struct udp_pcb *g_pcb;

/*定义通讯类型*/
typedef enum {
	TRA_TYPR_UDP=1, /*UDP通讯*/
	TRA_TYPR_TCP,
	//===    请在这里增加所需要的通讯类型
}data_traffic_type;


/*代号段结构体*/
typedef struct
{
	uint8_t devCode[DEV_CODE_SIZE]; /*设备代号*/
	uint8_t type; /*通讯类型*/
	uint8_t version; /*版本号*/
	uint8_t trans;	/*服务端发送标志：10H 客户端应答标志：03H */
	uint16_t reserve; /*预留2字节*/
}data_code;

/**
 * 数据包结构体，
 */
typedef struct
{
	uint8_t hdr;	/*信息头 0x7E*/
	uint8_t stx;	/*标识字0x5E*/
	data_code code; /*代号段*/
	uint16_t len; /*数据长度 */
	uint8_t *data;	/*数据域*/
	uint16_t XOR; /*校验码*/
	uint8_t ED; /*结束符*/
}data_packet;

/**
 * 在网络中传输 数据库包
 */
typedef struct
{
    uint8_t addr;	/*地址*/
    uint8_t fn[2];	/*功能码*/
    uint16_t len; /*数据长度*/
    uint8_t *data; /*数据*/
}dev_data_packet;

/*数据单元结构体*/
typedef struct
{
		uint16_t		*value; // 当前值
    uint16_t 		*min; //最小值
    uint16_t 		*max; //最大值
    uint8_t 		*alrm; // 报警状态

    uint16_t 		*crMin; //临界最小值
    uint16_t 		*crMax; //临界最大值
    uint8_t 		*crAlrm; //临界报警状态
}_devDataUnit;

typedef struct
{
	uint16_t 		len; // 长度
	_devDataUnit		vol; // 电流
	_devDataUnit 		cur; //电压

    uint32_t 		*pow; // 功率
    uint32_t 		*ele; // 电能

    uint16_t 		*pf; //功率因素
    uint8_t 		*sw; //开关状态

    uint16_t		*carbon; // 排C量
    uint16_t 		*rate; //电压频率

}_devDataObj;

typedef struct
{
	uint8_t 		len; // 长度
	_devDataUnit		tem; // 温度
	_devDataUnit 		hum; //湿度
    uint8_t 		*door; // 门禁
    uint8_t 		*water; // 水浸
    uint8_t 		*smoke; //烟雾
}_envDataObjct;

typedef struct
{
	uint8_t 		len; // 长度
	uint8_t 		*devname; // 设备名称

}_dataObjct;

typedef struct
{
	uint8_t 		len; // 长度
	uint8_t 		*userpsd; // 用户名和密码

}_userObjct;

typedef struct
{
	uint8_t 		len; // 长度
	uint8_t 		*ipaddr; // ip地址
	uint8_t    *gateway;//网关
	uint8_t 		*mask; // 子网掩码
	uint8_t 		*udns; // DNS	
	uint8_t 		*gcommunity; // get共同体		
	uint8_t 		*scommunity; // set共同体	
	uint8_t 		*trapa; // trap1	
	uint8_t 		*trapb; // trap2	
	uint8_t 		*smtpuse; // smtp用户		
	uint8_t 		*smtppass; // smtp密码	
	uint8_t 		*smtpserve; // smtp服务器	
	uint8_t 		*smtpmail; // smtp接受账号		
}_netObjct;

typedef struct
{
	_devDataObj		    group; // 输入组
	_devDataObj		    line; // 输入相
	_devDataObj 		output; //输出位
	_envDataObjct 		env; // 环境
	_dataObjct        dev; //设备信息
	_userObjct        userp; //设备信息	
	_netObjct        network; //设备信息	
}pduDevData;

void IAP_udp_init(void);
void IAP_udp_control(void);
void IAP_tcp_control(void);
void IAP_app_control(void);


#endif