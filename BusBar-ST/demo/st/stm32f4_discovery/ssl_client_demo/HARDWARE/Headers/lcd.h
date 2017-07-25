#ifndef _LCD_H_
#define _LCD_H_

#include "stm32f4xx.h" 
#include "spi3.h"
#include "stdlib.h"

//LCD重要参数集
typedef struct  
{										    
	u16 width;			//LCD 宽度
	u16 height;			//LCD 高度
	u16 id;				//LCD ID
	u8  dir;			//横屏还是竖屏控制：0，竖屏；1，横屏。	
	u16	 wramcmd;		//开始写gram指令
	u16  setxcmd;		//设置x坐标指令
	u16  setycmd;		//设置y坐标指令	 
}_lcd_dev; 	

typedef struct 
{
		u16 lcd_gram[128][128];		
}lcd;	


//LCD参数
extern _lcd_dev lcddev;	//管理LCD重要参数
/////////////////////////////////////用户配置区///////////////////////////////////	 
//支持横竖屏快速定义切换，支持8/16位模式切换
#define USE_HORIZONTAL  	0	//定义是否使用横屏 		0,不使用.1,使用.
//使用硬件SPI 还是模拟SPI作为测试
#define USE_HARDWARE_SPI    1  //1:Enable Hardware SPI使用硬件SPI;0:USE Soft SPI  模拟SPI总线


//定义LCD的尺寸
#if USE_HORIZONTAL==1	//使用横屏
#define LCD_W 128
#define LCD_H 128
#else                      //竖屏     
#define LCD_W 128
#define LCD_H 128
#endif

//TFTLCD部分外要调用的函数		   
extern u16  POINT_COLOR;//默认红色    
extern u16  BACK_COLOR; //背景颜色.默认为白色

//画笔颜色
#define WHITE       0xFFFF
#define BLACK      	0x0000	  
#define BLUE       	0x001F  
#define BRED        0XF81F   
#define GRED 			 	0XFFE0   //深黄
#define GBLUE			 	0X07FF
#define RED         0xF800
#define MAGENTA     0xF81F     //紫色
#define GREEN       0x07E0     //绿
#define CYAN        0x7FFF     //浅蓝
#define YELLOW      0xFFE0     //黄
#define BROWN 			0XBC40 //棕色
#define BRRED 			0XFC07 //棕红色
#define GRAY  			0X8430 //灰色
//GUI颜色

#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色
//以上三色为PANEL的颜色 
 
#define LIGHTGREEN     	0X841F //浅绿色
//#define LIGHTGRAY     0XEF5B //浅灰色(PANNEL)
#define LGRAY 			 		0XC618 //浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE      	0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE          0X2B12 //浅棕蓝色(选择条目的反色)
	
void LCD_Init(void);
//void LCD_Clear(u16 Color);
void LCD_Clear(u16 Color,u8 select);
void LCD_WR_DATA_16Bit(u16 data);
void LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd);

#endif




