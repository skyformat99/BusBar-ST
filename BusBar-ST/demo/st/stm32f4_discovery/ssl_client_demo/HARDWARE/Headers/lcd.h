#ifndef _LCD_H_
#define _LCD_H_

#include "stm32f4xx.h" 
#include "spi3.h"
#include "stdlib.h"

//LCD��Ҫ������
typedef struct  
{										    
	u16 width;			//LCD ���
	u16 height;			//LCD �߶�
	u16 id;				//LCD ID
	u8  dir;			//���������������ƣ�0��������1��������	
	u16	 wramcmd;		//��ʼдgramָ��
	u16  setxcmd;		//����x����ָ��
	u16  setycmd;		//����y����ָ��	 
}_lcd_dev; 	

typedef struct 
{
		u16 lcd_gram[128][128];		
}lcd;	


//LCD����
extern _lcd_dev lcddev;	//����LCD��Ҫ����
/////////////////////////////////////�û�������///////////////////////////////////	 
//֧�ֺ��������ٶ����л���֧��8/16λģʽ�л�
#define USE_HORIZONTAL  	0	//�����Ƿ�ʹ�ú��� 		0,��ʹ��.1,ʹ��.
//ʹ��Ӳ��SPI ����ģ��SPI��Ϊ����
#define USE_HARDWARE_SPI    1  //1:Enable Hardware SPIʹ��Ӳ��SPI;0:USE Soft SPI  ģ��SPI����


//����LCD�ĳߴ�
#if USE_HORIZONTAL==1	//ʹ�ú���
#define LCD_W 128
#define LCD_H 128
#else                      //����     
#define LCD_W 128
#define LCD_H 128
#endif

//TFTLCD������Ҫ���õĺ���		   
extern u16  POINT_COLOR;//Ĭ�Ϻ�ɫ    
extern u16  BACK_COLOR; //������ɫ.Ĭ��Ϊ��ɫ

//������ɫ
#define WHITE       0xFFFF
#define BLACK      	0x0000	  
#define BLUE       	0x001F  
#define BRED        0XF81F   
#define GRED 			 	0XFFE0   //���
#define GBLUE			 	0X07FF
#define RED         0xF800
#define MAGENTA     0xF81F     //��ɫ
#define GREEN       0x07E0     //��
#define CYAN        0x7FFF     //ǳ��
#define YELLOW      0xFFE0     //��
#define BROWN 			0XBC40 //��ɫ
#define BRRED 			0XFC07 //�غ�ɫ
#define GRAY  			0X8430 //��ɫ
//GUI��ɫ

#define DARKBLUE      	 0X01CF	//����ɫ
#define LIGHTBLUE      	 0X7D7C	//ǳ��ɫ  
#define GRAYBLUE       	 0X5458 //����ɫ
//������ɫΪPANEL����ɫ 
 
#define LIGHTGREEN     	0X841F //ǳ��ɫ
//#define LIGHTGRAY     0XEF5B //ǳ��ɫ(PANNEL)
#define LGRAY 			 		0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ

#define LGRAYBLUE      	0XA651 //ǳ����ɫ(�м����ɫ)
#define LBBLUE          0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)
	
void LCD_Init(void);
//void LCD_Clear(u16 Color);
void LCD_Clear(u16 Color,u8 select);
void LCD_WR_DATA_16Bit(u16 data);
void LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd);

#endif




