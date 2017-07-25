//#include "lcd.h"
//#include "font.h"
//#include <stdio.h>
//#include <stdlib.h>

////管理LCD重要参数
////默认为竖屏
//_lcd_dev lcddev;

////画笔颜色,背景颜色
//u16 POINT_COLOR = 0x0000,BACK_COLOR = 0xFFFF;  
//u16 DeviceCode;	 


//void DelayNop_lcd(int rm)
//{
//		int i=0;
//		for(i=0;i<rm;i++)
//		{
//		}
//}

////******************************************************************
////函数名：  LCD_Reset
////功能：    LCD复位函数，液晶初始化前要调用此函数
////输入参数：无
////返回值：  无
////修改记录：无
////******************************************************************
//void LCD_RESET(void)
//{
//	TFT_REST(1);          //  RST = 0
//	DelayNop_lcd(100);	
//	TFT_REST(0);            // RST = 1
//	DelayNop_lcd(50);
//}

////******************************************************************
////函数名：  LCD_WR_REG
////功能：    向液晶屏总线写入写16位指令
////输入参数：Reg:待写入的指令值
////返回值：  无
////修改记录：无
////******************************************************************
//void LCD_WR_REG(u16 data)
//{ 
//   TFT_CS(1);            // CS=0
//	 TFT_RS(1);            // RS=0:	写指令
//   TFT_SCK(1);             // SCK=0
//#if USE_HARDWARE_SPI   
//   SPI3_ReadWriteByte(data);
//#else
//   SPIv_WriteData(data);
//#endif 
//	 DelayNop_lcd(120);
//   TFT_SCK(0);               //CS=1
//}

////******************************************************************
////函数名：  LCD_WR_DATA
////功能：    向液晶屏总线写入写8位数据
////输入参数：Data:待写入的数据
////返回值：  无
////修改记录：无
////******************************************************************
//void LCD_WR_DATA(u8 data)
//{
//	
//   TFT_CS(1);            // CS=0
//	 TFT_RS(0);            // RS=1:	写数据
//#if USE_HARDWARE_SPI   
//   SPI3_ReadWriteByte(data);
//#else
//   SPIv_WriteData(data);
//#endif 
//	 DelayNop_lcd(120);
//   TFT_SCK(0);            // CS=1
//}

////******************************************************************
////函数名：  LCD_WriteReg
////功能：    写寄存器数据
////输入参数：LCD_Reg:寄存器地址
////			LCD_RegValue:要写入的数据
////返回值：  无
////修改记录：无
////******************************************************************
//void LCD_WriteReg(u16 LCD_Reg, u16 LCD_RegValue)
//{	
//	LCD_WR_REG(LCD_Reg);  
//	LCD_WR_DATA(LCD_RegValue);	    		 
//}

////******************************************************************
////函数名：  LCD_WriteRAM_Prepare
////作者：    xiao冯@全动电子
////日期：    2013-02-22
////功能：    开始写GRAM
////			在给液晶屏传送RGB数据前，应该发送写GRAM指令
////输入参数：无
////返回值：  无
////修改记录：无
////******************************************************************
//void LCD_WriteRAM_Prepare(void)
//{
//	LCD_WR_REG(lcddev.wramcmd);
//}	

////******************************************************************
////函数名：  LCD_DrawPoint_16Bit
////功能：    8位总线下如何写入一个16位数据
////输入参数：(x,y):光标坐标
////返回值：  无
////修改记录：无
////******************************************************************
//void LCD_WR_DATA_16Bit(u16 data)
//{	
//   TFT_CS(1);             //  CS=0
//   TFT_RS(0);							// RS=1
//#if USE_HARDWARE_SPI   
//   SPI3_ReadWriteByte(data>>8);
//   SPI3_ReadWriteByte(data);
//#else
//   SPIv_WriteData(data>>8);
//   SPIv_WriteData(data);
//#endif 
//   TFT_CS(0);                // CS=1
//}

////设置LCD参数
////方便进行横竖屏模式切换
//void LCD_SetParam(void)
//{ 	
//	lcddev.wramcmd=0x2C;
//#if USE_HORIZONTAL==1	//使用横屏	  
//	lcddev.dir=1;//横屏
//	lcddev.width=128;
//	lcddev.height=128;
//	lcddev.setxcmd=0x2A;            //设置x坐标指令
//	lcddev.setycmd=0x2B;			     //设置Y坐标指令
//	LCD_WriteReg(0x36,0xA8);

//#else//竖屏
//	lcddev.dir=0;//竖屏				 	 		
//	lcddev.width=128;
//	lcddev.height=128;
//	lcddev.setxcmd=0x2A;
//	lcddev.setycmd=0x2B;	
//	LCD_WriteReg(0x36,0xC8);
//#endif
//}


////******************************************************************
////函数名：  LCD_Init
////功能：    LCD初始化
////输入参数：无
////返回值：  无
////修改记录：无
////******************************************************************
//void LCD_Init(void)
//{  
//	
//#if USE_HARDWARE_SPI //使用硬件SPI
//	SPI3_Init();
//	SPI3_SetSpeed(SPI_BaudRatePrescaler_16);		//设置为42M时钟,高速模式 
//#else	
//	LCD_GPIOInit();//使用模拟SPI
//#endif  

//	LCD_RESET(); //液晶屏复位	

//	//************* Start Initial Sequence **********//		
//	//开始初始化液晶屏
//	LCD_WR_REG(0x11);//Sleep exit 
////	DelayNop_lcd(120);		
//	//ST7735S Frame Rate
//	LCD_WR_REG(0xB1); 
//	LCD_WR_DATA(0x05); 
//	LCD_WR_DATA(0x3C); 
//	LCD_WR_DATA(0x3C); 

//	LCD_WR_REG(0xB2); 
//	LCD_WR_DATA(0x05); 
//	LCD_WR_DATA(0x3C); 
//	LCD_WR_DATA(0x3C); 

//	LCD_WR_REG(0xB3); 
//	LCD_WR_DATA(0x05); 
//	LCD_WR_DATA(0x3C); 
//	LCD_WR_DATA(0x3C); 
//	LCD_WR_DATA(0x05); 
//	LCD_WR_DATA(0x3C); 
//	LCD_WR_DATA(0x3C); 
//	
//	LCD_WR_REG(0xB4); //Column inversion 
//	LCD_WR_DATA(0x03); 
//	
//	//ST7735S Power Sequence
//	LCD_WR_REG(0xC0); 
//	LCD_WR_DATA(0x28); 
//	LCD_WR_DATA(0x08); 
//	LCD_WR_DATA(0x04); 
//	
//	LCD_WR_REG(0xC1); 
//	LCD_WR_DATA(0xC0); 

//	LCD_WR_REG(0xC2); 
//	LCD_WR_DATA(0x0D); 
//	LCD_WR_DATA(0x00); 

//	LCD_WR_REG(0xC3); 
//	LCD_WR_DATA(0x8D); 
//	LCD_WR_DATA(0x2A); 
//	
//	LCD_WR_REG(0xC4); 
//	LCD_WR_DATA(0x8D); 
//	LCD_WR_DATA(0xEE); 
//	
//	LCD_WR_REG(0xC5); //VCOM 
//	LCD_WR_DATA(0x1A); 
//	
//	LCD_WR_REG(0x36); //MX, MY, RGB mode 				 
//	LCD_WR_DATA(0x08); 
//	
//	//ST7735S Gamma Sequence
//	LCD_WR_REG(0xe0); 
//	LCD_WR_DATA(0x04); 
//	LCD_WR_DATA(0x22); 
//	LCD_WR_DATA(0x07); 
//	LCD_WR_DATA(0x0A); 
//	LCD_WR_DATA(0x2E); 
//	LCD_WR_DATA(0x30); 
//	LCD_WR_DATA(0x25); 
//	LCD_WR_DATA(0x2A); 
//	LCD_WR_DATA(0x28); 
//	LCD_WR_DATA(0x26); 
//	LCD_WR_DATA(0x2E); 
//	LCD_WR_DATA(0x3A); 
//	LCD_WR_DATA(0x00); 	
//	LCD_WR_DATA(0x01); 
//	LCD_WR_DATA(0x03); 
//	LCD_WR_DATA(0x13); 

//	LCD_WR_REG(0xe1); 
//	LCD_WR_DATA(0x04); 
//	LCD_WR_DATA(0x16); 
//	LCD_WR_DATA(0x06); 
//	LCD_WR_DATA(0x0D); 
//	LCD_WR_DATA(0x2D); 
//	LCD_WR_DATA(0x26); 
//	LCD_WR_DATA(0x23); 
//	LCD_WR_DATA(0x27); 
//	LCD_WR_DATA(0x27); 
//	LCD_WR_DATA(0x25); 
//	LCD_WR_DATA(0x2D); 
//	LCD_WR_DATA(0x3B); 
//	LCD_WR_DATA(0x00); 
//	LCD_WR_DATA(0x01); 
//	LCD_WR_DATA(0x04); 
//	LCD_WR_DATA(0x13);  
//		
//	LCD_WR_REG(0x3A); //65k mode 
//	LCD_WR_DATA(0x05); 	
//	LCD_WR_REG(0x29);//Display on	

//	LCD_SetParam();//设置LCD参数	 
//	TFT_LEDA(0);   //点亮背光	  LEDA = 1
//	
//}

///*************************************************
//函数名：LCD_SetWindows
//功能：设置lcd显示窗口，在此区域写点数据自动换行
//入口参数：xy起点和终点
//返回值：无
//*************************************************/
//void LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd)
//{
//#if USE_HORIZONTAL==1	//使用横屏
//	LCD_WR_REG(lcddev.setxcmd);	
//	LCD_WR_DATA(xStar>>8);
//	LCD_WR_DATA(0x00FF&xStar+3);		
//	LCD_WR_DATA(xEnd>>8);
//	LCD_WR_DATA(0x00FF&xEnd+3);

//	LCD_WR_REG(lcddev.setycmd);	
//	LCD_WR_DATA(yStar>>8);
//	LCD_WR_DATA(0x00FF&yStar+2);		
//	LCD_WR_DATA(yEnd>>8);
//	LCD_WR_DATA(0x00FF&yEnd+2);	

//#else
//	
//	LCD_WR_REG(lcddev.setxcmd);	
//	LCD_WR_DATA(xStar>>8);
//	LCD_WR_DATA(0x00FF&xStar+2);		
//	LCD_WR_DATA(xEnd>>8);
//	LCD_WR_DATA(0x00FF&xEnd+2);

//	LCD_WR_REG(lcddev.setycmd);	
//	LCD_WR_DATA(yStar>>8);
//	LCD_WR_DATA(0x00FF&yStar+3);		
//	LCD_WR_DATA(yEnd>>8);
//	LCD_WR_DATA(0x00FF&yEnd+3);	
//#endif

//	LCD_WriteRAM_Prepare();	//开始写入GRAM				
//} 


//void LCD_Clear(u16 Color)
//{
//	u16 i,j;      
//	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);	  
//	for(i=0;i<lcddev.width;i++)
//	{
//		for(j=0;j<lcddev.height;j++)
//		LCD_WR_DATA_16Bit(Color);	//写入数据 	 
//	}
//} 

/********************************************************************************************************************************************************/
/********************************************************************************************************************************************************/
#include "LCD.h" 
#include "font.h"
#include <stdio.h>
#include <stdlib.h>

/*********************************
PB3 -- SCL
PB5 -- SDA
PB6 -- RS
PB7 -- RES
PD4 -- CS
PE5 -- LEDA
**********************************/

//管理LCD重要参数
//默认为竖屏
_lcd_dev lcddev;

lcd *_lcd_gram ;
lcd *_gram_lcd ;


//画笔颜色,背景颜色
u16 POINT_COLOR = 0x0000,BACK_COLOR = 0xFFFF;  
u16 DeviceCode;	

//更新显存到LCD		 
void LCD_Refresh_Gram(u8 select)
{
	u8 i,n;	
	
	if(select==1)
	{
			for(i=0;i<128;i++)  
			{   
				for(n=0;n<128;n++)
				{
					LCD_WR_DATA_16Bit(_lcd_gram->lcd_gram[n][i]);
				}
			}	
			vPortFree(_lcd_gram);
	 }
	 else if(select==2)
	 {
			for(i=0;i<128;i++)  
			{   
				for(n=0;n<128;n++)
				{
					LCD_WR_DATA_16Bit(_gram_lcd->lcd_gram[n][i]);
				}
			}
			vPortFree(_gram_lcd);
	 }
   	
}



void DelayNop_lcd(int rm)
{
		int i=0;
		for(i=0;i<rm;i++)
		{
		}
}

//******************************************************************
//函数名：  LCD_Reset
//功能：    LCD复位函数，液晶初始化前要调用此函数
//输入参数：无
//返回值：  无
//修改记录：无
//******************************************************************
void LCD_RESET(void)
{
	TFT_REST(1);          //  RST = 0
	DelayNop_lcd(100);	
	TFT_REST(0);            // RST = 1
	DelayNop_lcd(50);
}


//******************************************************************
//函数名：  LCD_WR_REG
//功能：    向液晶屏总线写入写16位指令
//输入参数：Reg:待写入的指令值
//返回值：  无
//修改记录：无
//******************************************************************
void LCD_WR_REG(u16 data)
{ 
   TFT_CS(1);            // CS=0
	 TFT_RS(1);            // RS=0:	写指令
   TFT_SCK(1);             // SCK=0
#if USE_HARDWARE_SPI   
   SPI3_ReadWriteByte(data);
#else
   SPIv_WriteData(data);
#endif 
	 DelayNop_lcd(120);
   TFT_SCK(0);               //CS=1
}

//******************************************************************
//函数名：  LCD_WR_DATA
//功能：    向液晶屏总线写入写8位数据
//输入参数：Data:待写入的数据
//返回值：  无
//修改记录：无
//******************************************************************
void LCD_WR_DATA(u8 data)
{
	
   TFT_CS(1);            // CS=0
	 TFT_RS(0);            // RS=1:	写数据
#if USE_HARDWARE_SPI   
   SPI3_ReadWriteByte(data);
#else
   SPIv_WriteData(data);
#endif 
	 DelayNop_lcd(120);
   TFT_SCK(0);            // CS=1

}

//******************************************************************
//函数名：  LCD_WriteReg
//功能：    写寄存器数据
//输入参数：LCD_Reg:寄存器地址
//			LCD_RegValue:要写入的数据
//返回值：  无
//修改记录：无
//******************************************************************
void LCD_WriteReg(u16 LCD_Reg, u16 LCD_RegValue)
{	
	LCD_WR_REG(LCD_Reg);  
	LCD_WR_DATA(LCD_RegValue);	    		 
}

//******************************************************************
//函数名：  LCD_WriteRAM_Prepare
//功能：    开始写GRAM
//			在给液晶屏传送RGB数据前，应该发送写GRAM指令
//输入参数：无
//返回值：  无
//修改记录：无
//******************************************************************
void LCD_WriteRAM_Prepare(void)
{
	LCD_WR_REG(lcddev.wramcmd);
}	 

//******************************************************************
//函数名：  LCD_DrawPoint_16Bit
//功能：    8位总线下如何写入一个16位数据
//输入参数：(x,y):光标坐标
//返回值：  无
//修改记录：无
//******************************************************************
void LCD_WR_DATA_16Bit(u16 data)
{	
   TFT_CS(1);             //  CS=0
   TFT_RS(0);							// RS=1
#if USE_HARDWARE_SPI   
   SPI3_ReadWriteByte(data>>8);
   SPI3_ReadWriteByte(data);
#else
   SPIv_WriteData(data>>8);
   SPIv_WriteData(data);
#endif 
   TFT_CS(0);                // CS=1
}

/*************************************************
函数名：LCD_SetCursor
功能：设置光标位置
入口参数：xy坐标
返回值：无
*************************************************/
void LCD_SetCursor(u16 Xpos, u16 Ypos)
{	  	    			
	LCD_SetWindows(Xpos,Ypos,Xpos,Ypos);
} 

//设置LCD参数
//方便进行横竖屏模式切换
void LCD_SetParam(void)
{ 	
	lcddev.wramcmd=0x2C;
#if USE_HORIZONTAL==1	//使用横屏	  
	lcddev.dir=1;//横屏
	lcddev.width=128;
	lcddev.height=128;
	lcddev.setxcmd=0x2A;            //设置x坐标指令
	lcddev.setycmd=0x2B;			     //设置Y坐标指令
	LCD_WriteReg(0x36,0xA8);

#else//竖屏
	lcddev.dir=0;//竖屏				 	 		
	lcddev.width=128;
	lcddev.height=128;
	lcddev.setxcmd=0x2A;
	lcddev.setycmd=0x2B;	
	LCD_WriteReg(0x36,0xC8);
#endif
}	


//******************************************************************
//函数名：  LCD_DrawPoint
//功能：    在指定位置写入一个像素点数据
//输入参数：(x,y):光标坐标
//返回值：  无
//修改记录：无
//******************************************************************
void LCD_DrawPoint(u16 x,u16 y)
{
	LCD_SetCursor(x,y);//设置光标位置 
//	LCD_WR_DATA_16Bit(RED);
//	_lcd_gram->lcd_gram[x][y]=RED;
}



//******************************************************************
//函数名：  LCD_Init
//功能：    LCD初始化
//输入参数：无
//返回值：  无
//修改记录：无
//******************************************************************
void LCD_Init(void)
{  
	
#if USE_HARDWARE_SPI //使用硬件SPI
	SPI3_Init();
	SPI3_SetSpeed(SPI_BaudRatePrescaler_2);		//设置为42M时钟,高速模式 
#else	
	LCD_GPIOInit();//使用模拟SPI
#endif  

	LCD_RESET(); //液晶屏复位	

	//************* Start Initial Sequence **********//		
	//开始初始化液晶屏
	LCD_WR_REG(0x11);//Sleep exit 
//	DelayNop_lcd(120);		
	//ST7735S Frame Rate
	LCD_WR_REG(0xB1); 
	LCD_WR_DATA(0x05); 
	LCD_WR_DATA(0x3C); 
	LCD_WR_DATA(0x3C); 

	LCD_WR_REG(0xB2); 
	LCD_WR_DATA(0x05); 
	LCD_WR_DATA(0x3C); 
	LCD_WR_DATA(0x3C); 

	LCD_WR_REG(0xB3); 
	LCD_WR_DATA(0x05); 
	LCD_WR_DATA(0x3C); 
	LCD_WR_DATA(0x3C); 
	LCD_WR_DATA(0x05); 
	LCD_WR_DATA(0x3C); 
	LCD_WR_DATA(0x3C); 
	
	LCD_WR_REG(0xB4); //Column inversion 
	LCD_WR_DATA(0x03); 
	
	//ST7735S Power Sequence
	LCD_WR_REG(0xC0); 
	LCD_WR_DATA(0x28); 
	LCD_WR_DATA(0x08); 
	LCD_WR_DATA(0x04); 
	
	LCD_WR_REG(0xC1); 
	LCD_WR_DATA(0xC0); 

	LCD_WR_REG(0xC2); 
	LCD_WR_DATA(0x0D); 
	LCD_WR_DATA(0x00); 

	LCD_WR_REG(0xC3); 
	LCD_WR_DATA(0x8D); 
	LCD_WR_DATA(0x2A); 
	
	LCD_WR_REG(0xC4); 
	LCD_WR_DATA(0x8D); 
	LCD_WR_DATA(0xEE); 
	
	LCD_WR_REG(0xC5); //VCOM 
	LCD_WR_DATA(0x1A); 
	
	LCD_WR_REG(0x36); //MX, MY, RGB mode 				 
	LCD_WR_DATA(0x08); 
	
	//ST7735S Gamma Sequence
	LCD_WR_REG(0xe0); 
	LCD_WR_DATA(0x04); 
	LCD_WR_DATA(0x22); 
	LCD_WR_DATA(0x07); 
	LCD_WR_DATA(0x0A); 
	LCD_WR_DATA(0x2E); 
	LCD_WR_DATA(0x30); 
	LCD_WR_DATA(0x25); 
	LCD_WR_DATA(0x2A); 
	LCD_WR_DATA(0x28); 
	LCD_WR_DATA(0x26); 
	LCD_WR_DATA(0x2E); 
	LCD_WR_DATA(0x3A); 
	LCD_WR_DATA(0x00); 	
	LCD_WR_DATA(0x01); 
	LCD_WR_DATA(0x03); 
	LCD_WR_DATA(0x13); 

	LCD_WR_REG(0xe1); 
	LCD_WR_DATA(0x04); 
	LCD_WR_DATA(0x16); 
	LCD_WR_DATA(0x06); 
	LCD_WR_DATA(0x0D); 
	LCD_WR_DATA(0x2D); 
	LCD_WR_DATA(0x26); 
	LCD_WR_DATA(0x23); 
	LCD_WR_DATA(0x27); 
	LCD_WR_DATA(0x27); 
	LCD_WR_DATA(0x25); 
	LCD_WR_DATA(0x2D); 
	LCD_WR_DATA(0x3B); 
	LCD_WR_DATA(0x00); 
	LCD_WR_DATA(0x01); 
	LCD_WR_DATA(0x04); 
	LCD_WR_DATA(0x13);  
		
	LCD_WR_REG(0x3A); //65k mode 
	LCD_WR_DATA(0x05); 	
	LCD_WR_REG(0x29);//Display on	

	LCD_SetParam();//设置LCD参数	 
	TFT_LEDA(0);   //点亮背光	  LEDA = 1

	LCD_Clear(CYAN,1); 
	LCD_Refresh_Gram(1);
	
}

/*************************************************
函数名：LCD_SetWindows
功能：设置lcd显示窗口，在此区域写点数据自动换行
入口参数：xy起点和终点
返回值：无
*************************************************/
void LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd)
{
#if USE_HORIZONTAL==1	//使用横屏
	LCD_WR_REG(lcddev.setxcmd);	
	LCD_WR_DATA(xStar>>8);
	LCD_WR_DATA(0x00FF&xStar+3);		
	LCD_WR_DATA(xEnd>>8);
	LCD_WR_DATA(0x00FF&xEnd+3);

	LCD_WR_REG(lcddev.setycmd);	
	LCD_WR_DATA(yStar>>8);
	LCD_WR_DATA(0x00FF&yStar+2);		
	LCD_WR_DATA(yEnd>>8);
	LCD_WR_DATA(0x00FF&yEnd+2);	

#else
	
	LCD_WR_REG(lcddev.setxcmd);	
	LCD_WR_DATA(xStar>>8);
	LCD_WR_DATA(0x00FF&xStar+2);		
	LCD_WR_DATA(xEnd>>8);
	LCD_WR_DATA(0x00FF&xEnd+2);

	LCD_WR_REG(lcddev.setycmd);	
	LCD_WR_DATA(yStar>>8);
	LCD_WR_DATA(0x00FF&yStar+3);		
	LCD_WR_DATA(yEnd>>8);
	LCD_WR_DATA(0x00FF&yEnd+3);	
#endif

	LCD_WriteRAM_Prepare();	//开始写入GRAM				
}  

/******************************************* GUI  ******************************************************************/


//******************************************************************
//函数名：  GUI_DrawPoint
//功能：    GUI描绘一个点
//输入参数：x:光标位置x坐标
//        	y:光标位置y坐标
//			color:要填充的颜色
//			select:选择相应更新数组
//返回值：  无
//修改记录：无
//******************************************************************
void GUI_DrawPoint(u16 x,u16 y,u16 color,u8 select)
{
	LCD_SetCursor(x,y);//设置光标位置 
	if(select==1)
		_lcd_gram->lcd_gram[x][y]=color;
	else if(select==2)
	  _gram_lcd->lcd_gram[x][y]=color;
}


//******************************************************************
//函数名：  LCD_Clear
//功能：    LCD全屏填充清屏函数
//输入参数：Color:要清屏的填充色
//返回值：  无
//修改记录：无
//******************************************************************
void LCD_Clear(u16 Color,u8 select)
{
	u16 i,j; 

	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);
	if(select==1)
	{
		_lcd_gram=(lcd *) pvPortMalloc(sizeof(lcd));   //申请动态内存		
		for(i=0;i<lcddev.width;i++)
		{
			for(j=0;j<lcddev.height ;j++)
				_lcd_gram->lcd_gram[i][j]=Color;
		}	
	}
	else if(select==2)
	{
		_gram_lcd=(lcd *) pvPortMalloc(sizeof(lcd));  //申请动态内存
		for(i=0;i<lcddev.width;i++)
		{		
			for(j=0;j<lcddev.height ;j++)
				_gram_lcd->lcd_gram[i][j]=Color;
		}		
	}

}

//******************************************************************
//函数名：  LCD_DrawLine
//功能：    画线
//输入参数：x1,y1:起点坐标
//        	x2,y2:终点坐标 
//返回值：  无
//修改记录：无
//****************************************************************** 
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2,u16 color,u8 select)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 

	delta_x=x2-x1; //计算坐标增量 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)
		incx=1; //设置单步方向 
	else if(delta_x==0)
		incx=0;//垂直线 
	else 
	{
		incx=-1;
		delta_x=-delta_x;
	} 
	if(delta_y>0)
		incy=1; 
	else if(delta_y==0)
		incy=0;//水平线 
	else
	{
		incy=-1;
		delta_y=-delta_y;
	} 
	if( delta_x>delta_y)
		distance=delta_x; //选取基本增量坐标轴 
	else 
		distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//画线输出 
	{  
		GUI_DrawPoint(uRow,uCol,color,select);  //画点 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
} 

//******************************************************************
//函数名：  LCD_DrawRectangle
//功能：    画矩形(非填充)
//输入参数：(x1,y1),(x2,y2):矩形的对角坐标
//返回值：  无
//修改记录：无
//******************************************************************  
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2,u16 color,u8 select)
{
	LCD_DrawLine(x1,y1,x2,y1,color,select);
	LCD_DrawLine(x1,y1,x1,y2,color,select);
	LCD_DrawLine(x1,y2,x2,y2,color,select);
	LCD_DrawLine(x2,y1,x2,y2,color,select);
} 

//******************************************************************
//函数名：  LCD_DrawFillRectangle
//功能：    GUI画矩形(填充)
//输入参数：(x1,y1),(x2,y2):矩形的对角坐标
//返回值：  无
//修改记录：无
//******************************************************************   
void LCD_DrawFillRectangle(u16 x1, u16 y1, u16 x2, u16 y2,u16 color,u8 select)
{
//	LCD_Fill(x1,y1,x2,y2,color,select);

}

//******************************************************************
//函数名：  _draw_circle_8

//功能：    8对称性画圆算法(内部调用)
//输入参数：(xc,yc) :圆中心坐标
// 			(x,y):光标相对于圆心的坐标
//         	c:填充的颜色
//返回值：  无
//修改记录：无
//******************************************************************  
void _draw_circle_8(int xc, int yc, int x, int y, u16 c,u8 select)
{
	GUI_DrawPoint(xc + x, yc + y, c, select);

	GUI_DrawPoint(xc - x, yc + y, c, select);

	GUI_DrawPoint(xc + x, yc - y, c, select);

	GUI_DrawPoint(xc - x, yc - y, c, select);

	GUI_DrawPoint(xc + y, yc + x, c, select);

	GUI_DrawPoint(xc - y, yc + x, c, select);

	GUI_DrawPoint(xc + y, yc - x, c, select);

	GUI_DrawPoint(xc - y, yc - x, c, select);
}

//******************************************************************
//函数名：  gui_circle
//功能：    在指定位置画一个指定大小的圆(填充)
//输入参数：(xc,yc) :圆中心坐标
//         	c:填充的颜色
//		 	r:圆半径
//		 	fill:填充判断标志，1-填充，0-不填充
//返回值：  无
//修改记录：无
//******************************************************************  
void gui_circle(int xc, int yc,u16 c,int r, int fill,u8 select)
{
	int x = 0, y = r, yi, d;

	d = 3 - 2 * r;


	if (fill) 
	{
		// 如果填充（画实心圆）
		while (x <= y) 
		{
			for (yi = x; yi <= y; yi++)
				_draw_circle_8(xc, yc, x, yi, c,select);

			if (d < 0) 
			{
				d = d + 4 * x + 6;
			}
			else 
			{
				d = d + 4 * (x - y) + 10;
				y--;
			}
			x++;
		}
	}
	else 
	{
		// 如果不填充（画空心圆）
		while (x <= y) 
		{
			_draw_circle_8(xc, yc, x, y, c,select);
			if (d < 0) 
			{
				d = d + 4 * x + 6;
			} 
			else 
			{
				d = d + 4 * (x - y) + 10;
				y--;
			}
			x++;
		}
	}
}

void LCD_ShowChar(u16 x,u16 y,u16 fc, u16 bc, u8 num,u8 size,u8 mode,u8 select)
{  
    u8 temp;
    u8 pos,t;
		u16 x0=x;
		u8 csize=(size/8+((size%8)?1:0))*(size/2);		//得到字体一个字符对应点阵集所占的字节数	     
		   
		num=num-' ';//得到偏移后的值
		LCD_SetWindows(x,y,x+size/2-1,y+size-1);//设置单个文字显示窗口
		if(!mode) //非叠加方式
		{
			if(size==20)
			{
				for(pos=0;pos<(csize+8);pos++)
				{
					temp=asc2_2010[num][pos];//调用2412字体				
					for(t=0;t<8;t++)
					{                 
							if(temp&0x01)
								GUI_DrawPoint(x,y,fc,select);//画一个点
							temp>>=1;
							x++;
							if(x>=lcddev.width)return;		//超区域了
							if((x-x0)==size/2)
							{
								x=x0;
								y++;
								if(y>=lcddev.height)return;	//超区域了
								break;
							}						
					 }	
				 }					
			 }
			else if(size==22)
			{
				for(pos=0;pos<(csize+8);pos++)
				{
					temp=asc2_2211[num][pos];//调用2412字体				
					for(t=0;t<8;t++)
					{                 
							if(temp&0x01)
								GUI_DrawPoint(x,y,fc,select);//画一个点
							temp>>=1;
							x++;
							if(x>=lcddev.width)return;		//超区域了
							if((x-x0)==size/2)
							{
								x=x0;
								y++;
								if(y>=lcddev.height)return;	//超区域了
								break;
							}						
					 }	
				 }					
			 }			
			else if(size==24)
			{
				for(pos=0;pos<(csize+8);pos++)
				{
					temp=asc2_2412[num][pos];//调用2412字体				
					for(t=0;t<8;t++)
					{                 
							if(temp&0x01)
								GUI_DrawPoint(x,y,fc,select);//画一个点
							temp>>=1;
							x++;
							if(x>=lcddev.width)return;		//超区域了
							if((x-x0)==size/2)
							{
								x=x0;
								y++;
								if(y>=lcddev.height)return;	//超区域了
								break;
							}						
					 }	
				 }					
			 }
			else if(size==28)
			{
				for(pos=0;pos<(csize+8);pos++)
				{
					temp=asc2_2814[num][pos];//调用2412字体				
					for(t=0;t<8;t++)
					{                 
							if(temp&0x01)
								GUI_DrawPoint(x,y,fc,select);//画一个点
							temp>>=1;
							x++;
							if(x>=lcddev.width)return;		//超区域了
							if((x-x0)==size/2)
							{
								x=x0;
								y++;
								if(y>=lcddev.height)return;	//超区域了
								break;
							}						
					 }	
				 }					
			 }			
			 else
			 {
				for(pos=0;pos<csize;pos++)
				{
					if(size==12)
						temp=asc2_1206[num][pos];//调用1206字体		
					else
						temp=asc2_1608[num][pos];		 //调用1608字体
					for(t=0;t<8;t++)
					{                 
							if(temp&0x01)
								GUI_DrawPoint(x,y,fc,select);//画一个点
							temp>>=1;
							x++;
							if(x>=lcddev.width)return;		//超区域了
							if((x-x0)==size/2)
							{
								x=x0;
								y++;
								if(y>=lcddev.height)return;	//超区域了
								break;
							}						
					 }	
				 }
			 }				
		}	
		else//叠加方式
		{	
			if(size==20)
			{
				for(pos=0;pos<(csize+8);pos++)
				{
					temp=asc2_2010[num][pos];//调用2412字体				
					for(t=0;t<8;t++)
					{                 
							if(temp&0x01)
								GUI_DrawPoint(x,y,fc,select);//画一个点
							else 
								GUI_DrawPoint(x,y,bc,select);//画一个点		
							temp>>=1;
							x++;
							if(x>=lcddev.width)return;		//超区域了
							if((x-x0)==size/2)
							{
								x=x0;
								y++;
								if(y>=lcddev.height)return;	//超区域了
								break;
							}						
					 }	
				 }					
			 }
			else if(size==22)
			{
				for(pos=0;pos<(csize+8);pos++)
				{
					temp=asc2_2211[num][pos];//调用2412字体				
					for(t=0;t<8;t++)
					{                 
							if(temp&0x01)
								GUI_DrawPoint(x,y,fc,select);//画一个点
							else 
								GUI_DrawPoint(x,y,bc,select);//画一个点		
							temp>>=1;
							x++;
							if(x>=lcddev.width)return;		//超区域了
							if((x-x0)==size/2)
							{
								x=x0;
								y++;
								if(y>=lcddev.height)return;	//超区域了
								break;
							}						
					 }	
				 }					
			 }			
			else if( size==24)
			{
				for(pos=0;pos<(csize+8);pos++)
				{
					temp=asc2_2412[num][pos];//调用2412字体				
					for(t=0;t<8;t++)
					{                 
							if(temp&0x01)
								GUI_DrawPoint(x,y,fc,select);//画一个点
							else 
								GUI_DrawPoint(x,y,bc,select);//画一个点							
							temp>>=1;
							x++;
							if(x>=lcddev.width)return;		//超区域了
							if((x-x0)==size/2)
							{
								x=x0;
								y++;
								if(y>=lcddev.height)return;	//超区域了
								break;
							}						
					 }	
				 }					
			 }
			else if(size==28)
			{
				for(pos=0;pos<(csize+8);pos++)
				{
					temp=asc2_2814[num][pos];//调用2412字体				
					for(t=0;t<8;t++)
					{                 
							if(temp&0x01)
								GUI_DrawPoint(x,y,fc,select);//画一个点
							else 
								GUI_DrawPoint(x,y,bc,select);//画一个点	
							temp>>=1;
							x++;
							if(x>=lcddev.width)return;		//超区域了
							if((x-x0)==size/2)
							{
								x=x0;
								y++;
								if(y>=lcddev.height)return;	//超区域了
								break;
							}						
					 }	
				 }					
			 }				
			 else
			 {
				for(pos=0;pos<csize;pos++)
				{
					if(size==12)
						temp=asc2_1206[num][pos];//调用1206字体		
					else
						temp=asc2_1608[num][pos];		 //调用1608字体
					for(t=0;t<8;t++)
					{                 
							if(temp&0x01)
								GUI_DrawPoint(x,y,fc,select);//画一个点
							else 
								GUI_DrawPoint(x,y,bc,select);//画一个点
							temp>>=1;
							x++;
							if(x>=lcddev.width)return;		//超区域了
							if((x-x0)==size/2)
							{
								x=x0;
								y++;
								if(y>=lcddev.height)return;	//超区域了
								break;
							}						
					 }	
				 }
			 }	
	  }	
		LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);//恢复窗口为全屏    	   	 	  
} 


//******************************************************************
//函数名：  LCD_ShowChar
//功能：    显示单个英文字符
//输入参数：(x,y):字符显示位置起始坐标
//        	fc:前置画笔颜色
//			bc:背景颜色
//			num:数值（0-94）
//			size:字体大小
//			mode:模式  0,填充模式;1,叠加模式
//返回值：  无
//修改记录：无
//******************************************************************  
void LCD_ShowNum2412(u16 x,u16 y,u16 fc, u16 bc,u8 *p ,u8 size,u8 mode,u8 select)
{  
    u16 temp;
    u8 pos,t;     
		u16 x0=x;
		u16 y0=y; 
		u8 num=0;
	
    while((*p<='~')&&(*p>=' '))//判断是不是非法字符!
    {   
			if(x>(lcddev.width-1)||y>(lcddev.height-1)) 
				return;   
			num=*p;
			if(':'==num) //特殊字符":"
				num=10;	
			else if('.'==num)//特殊字符"."
				num=11;	
			else  //纯数字   	
				num=num-'0';   
			x0=x;
					
			for(pos=0;pos<48;pos++)
			{
				temp=asc2_2412[num][pos];
				for(t=0;t<8;t++)
				{               
					if(temp&0x01)
						GUI_DrawPoint(x,y,fc,select);//画一个点  
					temp>>=1; 
					x++;
					if((x-x0)==12)
					{
						x=x0;
						y++;
						break;
					}
				}
			}
			if(num<10)
				x+=16;	//人为控制字距，使得排版更好看，原值为12
			else
				x+=8; //人为控制字距，使得排版更好看，原值为12

			y=y0;
			p++;
    }  
	 	  
}

//******************************************************************
//函数名：  LCD_ShowString
//功能：    显示英文字符串
//输入参数：x,y :起点坐标	 
//			size:字体大小
//			*p:字符串起始地址
//			mode:模式	0,填充模式;1,叠加模式
//返回值：  无
//修改记录：无
//******************************************************************  	  
void LCD_ShowString(u16 x,u16 y,u8 size,u8 *p,u8 mode,u8 select)
{         
    while((*p<='~')&&(*p>=' '))//判断是不是非法字符!
    {   
			if(x>(lcddev.width-1)||y>(lcddev.height-1)) 
				return;     
      LCD_ShowChar(x,y,POINT_COLOR,BACK_COLOR,*p,size,mode,select);
      x+=size/2;
      p++;
    }  
} 

//******************************************************************
//函数名：  mypow
//功能：    求m的n次方(gui内部调用)
//输入参数：m:乘数
//	        n:幂
//返回值：  m的n次方
//修改记录：无
//******************************************************************  
u32 mypow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)
		result*=m;    
	return result;
}

//******************************************************************
//函数名：  LCD_ShowNum
//功能：    显示单个数字变量值
//输入参数：x,y :起点坐标	 
//			len :指定显示数字的位数
//			size:字体大小(12,16)
//			color:颜色
//			num:数值(0~4294967295)
//返回值：  无
//修改记录：无
//******************************************************************  			 
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 select)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/mypow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x+(size/2)*t,y,POINT_COLOR,BACK_COLOR,' ',size,0,select);
				continue;
			}
			else 
				enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,POINT_COLOR,BACK_COLOR,temp+'0',size,0,select); 
	}
} 

//显示数字,高位为0,还是显示
//x,y:起点坐标
// fc:前置画笔颜色，bc:背景颜色
//num:数值(0~999999999);	 
//len:长度(即要显示的位数)
//size:字体大小
//mode:
//[7]:0,不填充;1,填充0.
//[6:1]:保留
//[0]:0,非叠加显示;1,叠加显示.
void LCD_ShowxNum(u16 x,u16 y,u16 fc, u16 bc,u32 num,u8 len,u8 size,u8 mode,u8 select)
{  
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/mypow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				if(mode&0X01)
					LCD_ShowChar(x+(size/2)*t,y,fc,bc,'0',size,(mode),select);  
				else 
					LCD_ShowChar(x+(size/2)*t,y,fc,bc,' ',size,mode,select);  
 				continue;
			}
			else 
				enshow=1;  
		}
	 	LCD_ShowChar(x+(size/2)*t,y,fc,bc,temp+'0',size,mode,select);
	}
} 

//******************************************************************
//函数名：  GUI_DrawFont16
//功能：    显示单个16X16中文字体
//输入参数：x,y :起点坐标
//			fc:前置画笔颜色
//			bc:背景颜色	 
//			s:字符串地址
//			mode:模式	0,填充模式;1,叠加模式
//返回值：  无
//修改记录：无
//******************************************************************
void GUI_DrawFont16(u16 x, u16 y, u16 fc, u16 bc, u8 *s,u8 mode,u8 select)
{
	u8 i,j;
	u16 k;
	u16 HZnum;
	u16 x0=x;
	HZnum=sizeof(tfont16)/sizeof(typFNT_GB16);	//自动统计汉字数目		
	for (k=0;k<HZnum;k++) 
	{
	  if ((tfont16[k].Index[0]==*(s))&&(tfont16[k].Index[1]==*(s+1)))
	  { 
				LCD_SetWindows(x,y,x+16-1,y+16-1);
		    for(i=0;i<16*2;i++)
		    {
					for(j=0;j<8;j++)
					{	
						if(!mode) //非叠加方式
						{
							if(tfont16[k].Msk[i]&(0x80>>j))
								GUI_DrawPoint(x,y,fc,select);//画一个点
							else
								GUI_DrawPoint(x,y,bc,select);//画一个点		
						}
						else
						{
							if(tfont16[k].Msk[i]&(0x80>>j))
								GUI_DrawPoint(x,y,fc,select);//画一个点
						}
						x++;
						if((x-x0)==16)
						{
							x=x0;
							y++;
							break;
						}
					}			
				}		
		}				  	
		continue;  //查找到对应点阵字库立即退出，防止多个汉字重复取模带来影响
	}
	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);//恢复窗口为全屏  
} 

//******************************************************************
//函数名：  GUI_DrawFont24
//功能：    显示单个24X24中文字体
//输入参数：x,y :起点坐标
//			fc:前置画笔颜色
//			bc:背景颜色	 
//			s:字符串地址
//			mode:模式	0,填充模式;1,叠加模式
//返回值：  无
//修改记录：无
//******************************************************************
void GUI_DrawFont24(u16 x, u16 y, u16 fc, u16 bc, u8 *s,u8 mode,u8 select)
{
	u8 i,j;
	u16 k;
	u16 HZnum;
	u16 x0=x;
	HZnum=sizeof(tfont24)/sizeof(typFNT_GB24);	//自动统计汉字数目
		
			for (k=0;k<HZnum;k++) 
			{
			  if ((tfont24[k].Index[0]==*(s))&&(tfont24[k].Index[1]==*(s+1)))
			  { 	
						LCD_SetWindows(x,y,x+24-1,y+24-1);
				    for(i=0;i<24*3;i++)
				    {
							for(j=0;j<8;j++)
							{
								if(!mode) //非叠加方式
								{
									if(tfont24[k].Msk[i]&(0x80>>j))	
										GUI_DrawPoint(x,y,fc,select);//画一个点
									else 
										GUI_DrawPoint(x,y,bc,select);//画一个点
								}
								else
								{
									if(tfont24[k].Msk[i]&(0x80>>j))	
										GUI_DrawPoint(x,y,fc,select);//画一个点
								}
								x++;
								if((x-x0)==24)
								{
										x=x0;
										y++;
										break;
								}
								
							}
						}			
					}				  	
					continue;  //查找到对应点阵字库立即退出，防止多个汉字重复取模带来影响
			}
	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);//恢复窗口为全屏  
}

//******************************************************************
//函数名：  GUI_DrawFont32
//功能：    显示单个32X32中文字体
//输入参数：x,y :起点坐标
//			fc:前置画笔颜色
//			bc:背景颜色	 
//			s:字符串地址
//			mode:模式	0,填充模式;1,叠加模式
//返回值：  无
//修改记录：无
//****************************************************************** 
void GUI_DrawFont32(u16 x, u16 y, u16 fc, u16 bc, u8 *s,u8 mode,u8 select)
{
	u8 i,j;
	u16 k;
	u16 HZnum;
	u16 x0=x;
	HZnum=sizeof(tfont32)/sizeof(typFNT_GB32);	//自动统计汉字数目
	for (k=0;k<HZnum;k++) 
	{
			  if ((tfont32[k].Index[0]==*(s))&&(tfont32[k].Index[1]==*(s+1)))
			  { 	
						LCD_SetWindows(x,y,x+32-1,y+32-1);
				    for(i=0;i<32*4;i++)
				    {
							for(j=0;j<8;j++)
							{
								if(!mode) //非叠加方式
								{
									if(tfont32[k].Msk[i]&(0x80>>j))	
										GUI_DrawPoint(x,y,fc,select);//画一个点
									
									else 
										GUI_DrawPoint(x,y,bc,select);//画一个点
									
								}
								else
								{
									if(tfont32[k].Msk[i]&(0x80>>j))	
										GUI_DrawPoint(x,y,fc,select);//画一个点
								}
								x++;
								if((x-x0)==32)
								{
									x=x0;
									y++;
									break;
								}
							}
						}				
				}				  	
				continue;  //查找到对应点阵字库立即退出，防止多个汉字重复取模带来影响
			}
	
	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);//恢复窗口为全屏  
} 

//******************************************************************
//函数名：  Show_Str
//功能：    显示一个字符串,包含中英文显示
//输入参数：x,y :起点坐标
// 			fc:前置画笔颜色
//			bc:背景颜色
//			str :字符串	 
//			size:字体大小
//			mode:模式	0,填充模式;1,叠加模式
//返回值：  无
//修改记录：无
//******************************************************************    	   		   
void Show_Str(u16 x, u16 y, u16 fc, u16 bc, u8 *str,u8 size,u8 mode,u8 select)
{					
		u16 x0=x;							  	  
  	u8 bHz=0;     //字符或者中文 
    while(*str!=0)//数据未结束
    { 
        if(!bHz)
        {
					if(x>(lcddev.width-size/2)||y>(lcddev.height-size)) 
					return; 
	        if(*str>0x80)
						bHz=1;//中文 
	        else              //字符
	        {          
		        if(*str==0x0D)//换行符号
		        {         
		            y+=size;
								x=x0;
		            str++; 
		        }  
		        else
						{
							if(size==12||size==16||size==20||size==22)
							{  
								LCD_ShowChar(x,y,fc,bc,*str,size,mode,select);
								x+=size/2; //字符,为全字的一半 
							}
							else//字库中没有集成16X32的英文字体,用8X16代替
							{
								LCD_ShowChar(x,y,fc,bc,*str,24,mode,select);
//								x+=12; //字符,为全字的一半 
								x+=size/2; //字符,为全字的一半 
							}
						} 
						str++; 
		        
						}
        }
				else//中文 
        {   
					if(x>(lcddev.width-size)||y>(lcddev.height-size)) 
					return;  
            bHz=0;//有汉字库    
					if(size==32)
						GUI_DrawFont32(x,y,fc,bc,str,mode,select);	 	
					else if(size==24)
						GUI_DrawFont24(x,y,fc,bc,str,mode,select);	
					else
						GUI_DrawFont16(x,y,fc,bc,str,mode,select);
				
	        str+=2; 
	        x+=size;//下一个汉字偏移	    
        }						 
    }   
}


//******************************************************************
//函数名：  Gui_StrCenter

//功能：    居中显示一个字符串,包含中英文显示
//输入参数：x,y :起点坐标
// 			fc:前置画笔颜色
//			bc:背景颜色
//			str :字符串	 
//			size:字体大小
//			mode:模式	0,填充模式;1,叠加模式
//返回值：  无
//修改记录：无
//******************************************************************   
void Gui_StrCenter(u16 x, u16 y, u16 fc, u16 bc, u8 *str,u8 size,u8 mode,u8 select)
{
	u16 len=strlen((const char *)str);
	u16 x1=(lcddev.width-len*8)/2;
	Show_Str(x+x1,y,fc,bc,str,size,mode,select);
} 






//******************************************************************
//函数名：  Gui_Drawbmp16
//功能：    显示一副16位BMP图像
//输入参数：x,y :起点坐标
// 			*p :图像数组起始地址
//返回值：  无
//修改记录：无
//******************************************************************  
void Gui_Drawbmp16(u16 x,u16 y,const unsigned char *p) //显示40*40 QQ图片
{
  	int i; 
	unsigned char picH,picL; 
	LCD_SetWindows(x,y,x+40-1,y+40-1);//窗口设置
    for(i=0;i<40*40;i++)
	{	
	 	picL=*(p+i*2);	//数据低位在前
		picH=*(p+i*2+1);				
		LCD_WR_DATA_16Bit(picH<<8|picL);  						
	}	
	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);//恢复显示窗口为全屏	

}






/********************************************************************************************************************************************************/
/********************************************************************************************************************************************************/


























