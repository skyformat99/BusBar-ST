#ifndef  _DEBUGUDP_H_
#define  _DEBUGUDP_H_
#include "core/net.h"
#include "core/ip.h"
#include "core/udp.h"
#include "core/socket.h"
#include "ipv4/ipv4.h"

#define DATA_MSG_SIZE	512		/*���ݻ�������С*/
#define DEV_CODE_SIZE	4		/*�豸����λ��*/
#define DATA_MSG_CODE_SIZE	9

#define DATA_MSG_HDR	0x7E	/*��Ϣͷ~*/
#define DATA_MSG_STX	0x5E	/*��ʶ��^*/
#define DATA_MSG_ED	0x23	/*������*/

#define DATA_MSG_SERVICE	0x10	/*����˱�־*/
#define DATA_MSG_CLIENT		0x03	/*�ͻ��˱�־*/

#define DATA_DEV_VERSION		1 /*�豸ͨѶ����*/

//#define  UDP_Port          28720           //UDP port
#define UDP_BUF_SIZE	256 /*���ݻ�������С�� IP�豸ʹ��256�� ARM9ϵ���豸ʹ��512*/     

static struct udp_pcb *g_pcb;

/*����ͨѶ����*/
typedef enum {
	TRA_TYPR_UDP=1, /*UDPͨѶ*/
	TRA_TYPR_TCP,
	//===    ����������������Ҫ��ͨѶ����
}data_traffic_type;


/*���Ŷνṹ��*/
typedef struct
{
	uint8_t devCode[DEV_CODE_SIZE]; /*�豸����*/
	uint8_t type; /*ͨѶ����*/
	uint8_t version; /*�汾��*/
	uint8_t trans;	/*����˷��ͱ�־��10H �ͻ���Ӧ���־��03H */
	uint16_t reserve; /*Ԥ��2�ֽ�*/
}data_code;

/**
 * ���ݰ��ṹ�壬
 */
typedef struct
{
	uint8_t hdr;	/*��Ϣͷ 0x7E*/
	uint8_t stx;	/*��ʶ��0x5E*/
	data_code code; /*���Ŷ�*/
	uint16_t len; /*���ݳ��� */
	uint8_t *data;	/*������*/
	uint16_t XOR; /*У����*/
	uint8_t ED; /*������*/
}data_packet;

/**
 * �������д��� ���ݿ��
 */
typedef struct
{
    uint8_t addr;	/*��ַ*/
    uint8_t fn[2];	/*������*/
    uint16_t len; /*���ݳ���*/
    uint8_t *data; /*����*/
}dev_data_packet;

/*���ݵ�Ԫ�ṹ��*/
typedef struct
{
		uint16_t		*value; // ��ǰֵ
    uint16_t 		*min; //��Сֵ
    uint16_t 		*max; //���ֵ
    uint8_t 		*alrm; // ����״̬

    uint16_t 		*crMin; //�ٽ���Сֵ
    uint16_t 		*crMax; //�ٽ����ֵ
    uint8_t 		*crAlrm; //�ٽ籨��״̬
}_devDataUnit;

typedef struct
{
	uint16_t 		len; // ����
	_devDataUnit		vol; // ����
	_devDataUnit 		cur; //��ѹ

    uint32_t 		*pow; // ����
    uint32_t 		*ele; // ����

    uint16_t 		*pf; //��������
    uint8_t 		*sw; //����״̬

    uint16_t		*carbon; // ��C��
    uint16_t 		*rate; //��ѹƵ��

}_devDataObj;

typedef struct
{
	uint8_t 		len; // ����
	_devDataUnit		tem; // �¶�
	_devDataUnit 		hum; //ʪ��
    uint8_t 		*door; // �Ž�
    uint8_t 		*water; // ˮ��
    uint8_t 		*smoke; //����
}_envDataObjct;

typedef struct
{
	uint8_t 		len; // ����
	uint8_t 		*devname; // �豸����

}_dataObjct;

typedef struct
{
	uint8_t 		len; // ����
	uint8_t 		*userpsd; // �û���������

}_userObjct;

typedef struct
{
	uint8_t 		len; // ����
	uint8_t 		*ipaddr; // ip��ַ
	uint8_t    *gateway;//����
	uint8_t 		*mask; // ��������
	uint8_t 		*udns; // DNS	
	uint8_t 		*gcommunity; // get��ͬ��		
	uint8_t 		*scommunity; // set��ͬ��	
	uint8_t 		*trapa; // trap1	
	uint8_t 		*trapb; // trap2	
	uint8_t 		*smtpuse; // smtp�û�		
	uint8_t 		*smtppass; // smtp����	
	uint8_t 		*smtpserve; // smtp������	
	uint8_t 		*smtpmail; // smtp�����˺�		
}_netObjct;

typedef struct
{
	_devDataObj		    group; // ������
	_devDataObj		    line; // ������
	_devDataObj 		output; //���λ
	_envDataObjct 		env; // ����
	_dataObjct        dev; //�豸��Ϣ
	_userObjct        userp; //�豸��Ϣ	
	_netObjct        network; //�豸��Ϣ	
}pduDevData;

void IAP_udp_init(void);
void IAP_udp_control(void);
void IAP_tcp_control(void);
void IAP_app_control(void);


#endif