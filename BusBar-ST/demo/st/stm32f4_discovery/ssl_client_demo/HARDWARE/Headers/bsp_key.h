#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h" 
#include "exti.h"
#include "ip_info.h"
#include "lcd_dispaly.h"

//////////////////////////////////////////////////////////////////////////////////	 
/*����ķ�ʽ��ͨ��ֱ�Ӳ����⺯����ʽ��ȡIO*/
#define KEY0 		GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4) //PE4
#define KEY1 		GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)	//PE5
#define KEY2 		GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6) //PE6


/*���淽ʽ��ͨ��λ��������ʽ��ȡIO*/
/*
#define KEY0 		PAin(4)   	//PA4
#define KEY1 		PAin(5)		//PA5 
#define KEY2 		PAin(6)		//PA6
*/


#define KEY0_PRES 	1
#define KEY1_PRES	  2
#define KEY2_PRES	  3
#define WKUP_PRES   4

#define   KEY_ON	  0
#define   KEY_OFF	  1

#define N_key    0             //�޼� 
#define S_key    1             //���� 
#define D_key    2             //˫�� 
#define L_key    3             //���� 

#define key_state_0   0 
#define key_state_1   1 
#define key_state_2   2 
#define key_state_3   3 



unsigned char key_read(void);
void key_scan(void);

void KEY_Init(void);	//IO��ʼ��
u8 KEY_Scan(u8);  		//����ɨ�躯��	

#endif
